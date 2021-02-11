/***************************************************************************//**
 * @file
 * @brief Power Manager API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_power_manager.h"
#include "sl_power_manager_config.h"
#include "sli_power_manager_private.h"
#include "sli_power_manager.h"
#include "sli_sleeptimer.h"
#include "em_assert.h"
#include "sl_atomic.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

#if ((SL_POWER_MANAGER_LOWEST_EM_ALLOWED != 2) \
  && (SL_POWER_MANAGER_LOWEST_EM_ALLOWED != 3))
#error "Lowest Energy mode allowed is invalid."
#endif

// Default overhead value for the wake-up time used for the schedule wake-up
// functionality.
#define SCHEDULE_WAKEUP_DEFAULT_RESTORE_TIME_OVERHEAD_TICK  0

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// Initialization flag.
static bool is_initialized = false;

// Table of energy modes counters. Each counter indicates the presence (not zero)
// or absence (zero) of requirements on a given energy mode. The table doesn't
// contain requirement on EM0.
static uint8_t requirement_em_table[SLI_POWER_MANAGER_EM_TABLE_SIZE] = {
  0,  // EM1 requirement counter
  0,  // EM2 requirement counter
};

// Counter variable to save the number of High Accuracy HF clock requirements requested.
uint8_t requirement_high_accuracy_hf_clock_counter = 0;

// Current active energy mode.
static sl_power_manager_em_t current_em = SL_POWER_MANAGER_EM0;

// Saved energy mode we are coming from in an Early Wake-up.
static sl_power_manager_em_t early_wakeup_from_em = SL_POWER_MANAGER_EM0;

// Flag indicating if the system states (clocks) are saved and should be restored
static bool is_states_saved = false;

// Events subscribers lists
static sl_slist_node_t *power_manager_em_transition_event_list = NULL;

// Timer that it is used for enabling the clock for the scheduled wakeup
static sl_sleeptimer_timer_handle_t clock_wakeup_timer_handle = { 0 };

// Store if requirement on EM1 has been added before sleeping;
// i.e. only possible if sleeping for less than minimum off time
static bool requirement_on_em1_added = false;

// Store the sleeptimer tick count at the beginning of the wake-up process.
uint32_t wakeup_start_tick_count = 0;

// Threshold delay in sleeptimer ticks indicating the minimum time required
// to make the shut down of external high frequency oscillator worthwhile before
// the next synchronous high frequency oscillator requirement. Shorter than this
// delay, the power gain of shutting down is invalidated.
uint32_t high_frequency_min_offtime_tick = 0;

// Store the configuration overhead value in sleeptimer tick to add/remove to the wake-up time.
int32_t wakeup_time_config_overhead_tick = 0;

// Store the sleeptimer module clock frequency for conversion calculation
static uint32_t sleeptimer_frequency;

static bool is_hf_x_oscillator_not_preserved;

/*
 *********************************************************************************************************
 *                                           HOOK REFERENCES
 *********************************************************************************************************
 */

bool sl_power_manager_sleep_on_isr_exit(void);

// Callback to application after wakeup but before restoring interrupts.
// For internal Silicon Labs use only
__WEAK void sli_power_manager_on_wakeup(void);

/***************************************************************************//**
 * Mandatory callback that allows to cancel sleeping action.
 ******************************************************************************/
bool sl_power_manager_is_ok_to_sleep(void);

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

static sl_power_manager_em_t get_lowest_em(void);

static void evaluate_wakeup(sl_power_manager_em_t to);

static void power_manager_notify_em_transition(sl_power_manager_em_t from,
                                               sl_power_manager_em_t to);

static void on_clock_wakeup_timeout(sl_sleeptimer_timer_handle_t *handle,
                                    void *data);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize Power Manager module.
 ******************************************************************************/
sl_status_t sl_power_manager_init(void)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  if (!is_initialized) {
    sl_status_t status = SL_STATUS_OK;

    // Initialize Sleeptimer module in case not already done.
    status = sl_sleeptimer_init();
    if (status != SL_STATUS_OK) {
      CORE_EXIT_CRITICAL();
      return status;
    }

    // Get the sleeptimer frequency
    sleeptimer_frequency = sl_sleeptimer_get_timer_frequency();

  #if (SL_POWER_MANAGER_DEBUG == 1)
    sli_power_manager_debug_init();
  #endif
    sl_slist_init(&power_manager_em_transition_event_list);

    // Set the default wake-up overhead value
    wakeup_time_config_overhead_tick = SCHEDULE_WAKEUP_DEFAULT_RESTORE_TIME_OVERHEAD_TICK;
  }

  // Do all necessary hardware initialization.
  sli_power_manager_init_hardware();
  // Set the HF minimum offtime in sleeptimer ticks
  high_frequency_min_offtime_tick = sli_power_manager_get_default_high_frequency_minimum_offtime();

  is_initialized = true;
  CORE_EXIT_CRITICAL();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Sleep at the lowest allowed energy mode.
 ******************************************************************************/
void sl_power_manager_sleep(void)
{
  sl_power_manager_em_t lowest_em;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();

  if (sl_power_manager_is_ok_to_sleep() != true) {
    CORE_EXIT_CRITICAL();
    return;
  }

  // Go to another energy mode (same, higher to lower or lower to higher)
  do {
    // Remove any previous EM1 requirement added internally by the power manager itself
    if (requirement_on_em1_added) {
#if (SL_POWER_MANAGER_DEBUG == 1)
      sli_power_manager_debug_log_em_requirement(SL_POWER_MANAGER_EM1, false, CURRENT_MODULE_NAME);
#endif
      // Decrement energy mode counter.
      requirement_em_table[SL_POWER_MANAGER_EM1 - 1] -= 1;
      requirement_on_em1_added = false;
    }

    lowest_em = get_lowest_em();
    evaluate_wakeup(lowest_em);
    lowest_em = get_lowest_em();  // Reevaluate as a requirement can be added from evaluate_wakeup()

    if ((lowest_em >= SL_POWER_MANAGER_EM2)
        && (is_states_saved == false)) {
      sli_power_manager_save_states();
    }

    // Notify listeners if transition to another energy mode
    if (lowest_em != current_em) {
      power_manager_notify_em_transition(current_em, lowest_em);
      current_em = lowest_em;           // Keep new active energy mode
    }

    // Pre-sleep operations if any are necessary
    if ((lowest_em >= SL_POWER_MANAGER_EM2)
        && (is_states_saved == false)) {
      // Only do pre-sleep operations if there is no requirement on High Accuracy Clock.
      // Else we must not touch the clock tree.
      if (requirement_high_accuracy_hf_clock_counter == 0) {
        sli_power_manager_handle_pre_deepsleep_operations();
        is_hf_x_oscillator_not_preserved = true;
      }
      is_states_saved = true;
    }

    // Apply lowest reachable energy mode
    sli_power_manager_apply_em(current_em);

    // Notify consumer of wakeup while interrupts are still off
    // For internal Silicon Labs use only
    sli_power_manager_on_wakeup();

    CORE_EXIT_CRITICAL();
    CORE_ENTER_CRITICAL();

    // Stop the internal power manager sleeptimer.
    sl_sleeptimer_stop_timer(&clock_wakeup_timer_handle);
  } while (sl_power_manager_sleep_on_isr_exit() == true);

  if (is_states_saved == true) {
    is_states_saved = false;
    // Restore clocks
    if (is_hf_x_oscillator_not_preserved) {
      sli_power_manager_restore_high_freq_accuracy_clk();
      is_hf_x_oscillator_not_preserved = false;
    }
    // If possible, go back to sleep in EM1 while waiting for HF accuracy restore
    while (!sli_power_manager_is_high_freq_accuracy_clk_ready(false)) {
      sli_power_manager_apply_em(SL_POWER_MANAGER_EM1);
      CORE_EXIT_CRITICAL();
      CORE_ENTER_CRITICAL();
    }
    (void)sli_power_manager_restore_states(RESTORE_CALLER_ID_SLEEP_EXIT);
  }

  evaluate_wakeup(SL_POWER_MANAGER_EM0);

  // Indicate back to EM0
  power_manager_notify_em_transition(current_em, SL_POWER_MANAGER_EM0);
  current_em = SL_POWER_MANAGER_EM0;

  CORE_EXIT_CRITICAL();
}

/***************************************************************************//**
 * Updates requirement on the given energy mode.
 *
 * @param   em    Energy mode. Possible values are:
 *                SL_POWER_MANAGER_EM1
 *                SL_POWER_MANAGER_EM2
 *                SL_POWER_MANAGER_EM3
 *
 * @param   add   Flag indicating if requirement is added (true) or removed
 *                (false).
 ******************************************************************************/
void sli_power_manager_update_em_requirement(sl_power_manager_em_t em,
                                             bool add,
                                             const char *name)
{
  CORE_DECLARE_IRQ_STATE;

  // EM0 is not allowed
  EFM_ASSERT((em > SL_POWER_MANAGER_EM0) && (em < SL_POWER_MANAGER_EM3));

  CORE_ENTER_CRITICAL();
  // Cannot increment above 255 (wraparound not allowed)
  EFM_ASSERT(!((requirement_em_table[em - 1] == UINT8_MAX) && (add == true)));
  // Cannot decrement below 0 (wraparound not allowed)
  EFM_ASSERT(!((requirement_em_table[em - 1] == 0) && (add == false)));

#if (SL_POWER_MANAGER_DEBUG == 1)
  sli_power_manager_debug_log_em_requirement(em, add, name);
#else
  (void)name;
#endif

  // Increment (add) or decrement (remove) energy mode counter.
  requirement_em_table[em - 1] += (add) ? 1 : -1;

  if (current_em >= SL_POWER_MANAGER_EM2) {  // if currently sleeping at a level that can require a clock restore; i.e. called from ISR
    sl_power_manager_em_t lowest_em;
    // If requirement added when sleeping, restore the clock before continuing the processing.
    // Retrieve lowest reachable energy mode
    lowest_em = get_lowest_em();

    if (lowest_em < current_em) {
      // If new lowest requirement is greater than the current
      // Restore clock; Everything is restored (HF and LF Clocks), the sleep loop will
      // shutdown the clocks when returning sleeping

      if (is_hf_x_oscillator_not_preserved) {
        sli_power_manager_restore_high_freq_accuracy_clk();
        is_hf_x_oscillator_not_preserved = false;
      }

      if (is_states_saved) {
        is_states_saved = false;
        sli_power_manager_is_high_freq_accuracy_clk_ready(true);
        (void)sli_power_manager_restore_states(RESTORE_CALLER_ID_ADD_REQUIREMENT);
      }
      power_manager_notify_em_transition(current_em, lowest_em);
      current_em = lowest_em;           // Keep new active energy mode
    }

    // if going to a lower level, the loop in sl_power_manager_sleep() will save the
    // states if required and notify the subscriber
  }

  CORE_EXIT_CRITICAL();
}

#if defined(SLI_DEVICE_SUPPORTS_EM1P)
/***************************************************************************//**
 * Updates requirement on preservation of High Frequency Clocks settings.
 *
 * @param   add   Flag indicating if requirement is added (true) or removed
 *                (false).
 ******************************************************************************/
void sli_power_manager_update_hf_clock_settings_preservation_requirement(bool add)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  // Cannot increment above 255 (wraparound not allowed)
  EFM_ASSERT(!((requirement_high_accuracy_hf_clock_counter == UINT8_MAX) && (add == true)));
  // Cannot decrement below 0 (wraparound not allowed)
  EFM_ASSERT(!((requirement_high_accuracy_hf_clock_counter == 0) && (add == false)));

  // Cannot add requirement if the "normal" clock settings are not currently applied
  EFM_ASSERT(!((current_em != SL_POWER_MANAGER_EM0) && (add == true)));

  // Increment (add) or decrement (remove) energy mode counter.
  requirement_high_accuracy_hf_clock_counter += (add) ? 1 : -1;

  CORE_EXIT_CRITICAL();
}
#endif

/***************************************************************************//**
 * Registers a callback to be called on given Energy Mode transition(s).
 *
 * @note Adding/Removing requirement(s) from the callback is not supported.
 ******************************************************************************/
void sl_power_manager_subscribe_em_transition_event(sl_power_manager_em_transition_event_handle_t *event_handle,
                                                    const sl_power_manager_em_transition_event_info_t *event_info)
{
  CORE_DECLARE_IRQ_STATE;

  event_handle->info = (sl_power_manager_em_transition_event_info_t *)event_info;
  CORE_ENTER_CRITICAL();
  sl_slist_push(&power_manager_em_transition_event_list, &event_handle->node);
  CORE_EXIT_CRITICAL();
}

/***************************************************************************//**
 * Unregisters an event callback handle on Energy mode transition.
 ******************************************************************************/
void sl_power_manager_unsubscribe_em_transition_event(sl_power_manager_em_transition_event_handle_t *event_handle)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  sl_slist_remove(&power_manager_em_transition_event_list, &event_handle->node);
  CORE_EXIT_CRITICAL();
}

/***************************************************************************//**
 * Get configurable overhead value for early restore time in Sleeptimer ticks
 * when a schedule wake-up is set.
 *
 * @return  Current overhead value for early wake-up time.
 ******************************************************************************/
int32_t sl_power_manager_schedule_wakeup_get_restore_overhead_tick(void)
{
  int32_t overhead_tick;

  sl_atomic_load(overhead_tick, wakeup_time_config_overhead_tick);
  return overhead_tick;
}

/***************************************************************************//**
 * Set configurable overhead value for early restore time in Sleeptimer ticks
 * used for schedule wake-up.
 * Must be called after initialization else the value will be overwritten.
 *
 * @param overhead_tick Overhead value to set for early restore time.
 *
 * @note The overhead value can also be negative to remove time from the restore
 *       process.
 ******************************************************************************/
void sl_power_manager_schedule_wakeup_set_restore_overhead_tick(int32_t overhead_tick)
{
  sl_atomic_store(wakeup_time_config_overhead_tick, overhead_tick);
}

/***************************************************************************//**
 * Get configurable minimum off-time value for schedule wake-up in Sleeptimer
 * ticks.
 *
 * @return  Current minimum off-time value for schedule wake-up.
 *
 * @note  Turning on external high frequency oscillator, such as HFXO, requires
 *        more energy since we must supply higher current for the wake-up.
 *        Therefore, when an 'external high frequency oscillator enable' is
 *        scheduled in 'x' time, there is a threshold 'x' value where turning
 *        off the oscillator is not worthwhile since the energy consumed by
 *        taking into account the wake-up will be greater than if we just keep
 *        the oscillator on until the next scheduled oscillator enabled. This
 *        threshold value is what we refer as the minimum off-time.
 ******************************************************************************/
uint32_t sl_power_manager_schedule_wakeup_get_minimum_offtime_tick(void)
{
  uint32_t offtime_tick;

  sl_atomic_load(offtime_tick, high_frequency_min_offtime_tick);
  return offtime_tick;
}

/***************************************************************************//**
 * Set configurable minimum off-time value for schedule wake-up in Sleeptimer
 * ticks.
 *
 * @param minimum_offtime_tick  minimum off-time value to set for schedule
 *                              wake-up.
 *
 * @note  Turning on external high frequency oscillator, such as HFXO, requires
 *        more energy since we must supply higher current for the wake-up.
 *        Therefore, when an 'external high frequency oscillator enable' is
 *        scheduled in 'x' time, there is a threshold 'x' value where turning
 *        off the oscillator is not worthwhile since the energy consumed by
 *        taking into account the wake-up will be greater than if we just keep
 *        the oscillator on until the next scheduled oscillator enabled. This
 *        threshold value is what we refer as the minimum off-time.
 ******************************************************************************/
void sl_power_manager_schedule_wakeup_set_minimum_offtime_tick(uint32_t minimum_offtime_tick)
{
  sl_atomic_store(high_frequency_min_offtime_tick, minimum_offtime_tick);
}

/*******************************************************************************
 * Converts microseconds time in sleeptimer ticks.
 ******************************************************************************/
uint32_t sli_power_manager_convert_delay_us_to_tick(uint32_t time_us)
{
  return (((time_us * sleeptimer_frequency) + (1000000 - 1)) / 1000000);
}

/***************************************************************************//**
 * Last-chance check before sleep.
 *
 * @return  True, if the system should actually sleep.
 *          False, if not.
 *
 * @note This is the fallback implementation of the callback, it can be
 * overridden by the application or other components.
 ******************************************************************************/
__WEAK bool sl_power_manager_is_ok_to_sleep(void)
{
  return true;
}

/***************************************************************************//**
 * Check if the MCU can sleep after an interrupt.
 *
 * @return  True, if the system can sleep after the interrupt.
 *          False, otherwise.
 *
 * @note This is the fallback implementation of the callback, it can be
 * overridden by the application or other components.
 ******************************************************************************/
__WEAK bool sl_power_manager_sleep_on_isr_exit(void)
{
  return false;
}

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * Get lowest energy mode to apply given the requirements on the different
 * energy modes.
 *
 * @return  Lowest energy mode: EM1, EM2 or EM3.
 *
 * @note If no requirement for any energy mode (EM1 and EM2), lowest energy mode
 * is EM3.
 ******************************************************************************/
static sl_power_manager_em_t get_lowest_em(void)
{
  uint32_t em_ix;
  sl_power_manager_em_t em;

  // Retrieve lowest Energy mode allowed given the requirements
  for (em_ix = 1; (em_ix < SL_POWER_MANAGER_LOWEST_EM_ALLOWED) && (requirement_em_table[em_ix - 1] == 0); em_ix++) {
    ;
  }

  em = (sl_power_manager_em_t)em_ix;

  return em;
}

/***************************************************************************//**
 * Notify subscribers about energy mode transition.
 *
 * @param  from  Energy mode from which CPU comes from.
 *
 * @param  to    Energy mode to which CPU is going to.
 ******************************************************************************/
static void power_manager_notify_em_transition(sl_power_manager_em_t from,
                                               sl_power_manager_em_t to)
{
  sl_power_manager_em_transition_event_handle_t *handle;
  sl_power_manager_em_transition_event_t transition = 0;

  switch (to) {
    case SL_POWER_MANAGER_EM0:
      transition = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0;
      break;

    case SL_POWER_MANAGER_EM1:
      transition = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM1;
      break;

    case SL_POWER_MANAGER_EM2:
      transition = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2;
      break;

    case SL_POWER_MANAGER_EM3:
      transition = SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3;
      break;

    default:
      EFM_ASSERT(0);
  }

  switch (from) {
    case SL_POWER_MANAGER_EM0:
      transition |= SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0;
      break;

    case SL_POWER_MANAGER_EM1:
      transition |= SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM1;
      break;

    case SL_POWER_MANAGER_EM2:
      transition |= SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2;
      break;

    case SL_POWER_MANAGER_EM3:
      transition |= SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3;
      break;

    default:
      EFM_ASSERT(0);
  }

  SL_SLIST_FOR_EACH_ENTRY(power_manager_em_transition_event_list, handle, sl_power_manager_em_transition_event_handle_t, node) {
    if ((handle->info->event_mask & transition) > 0) {
      handle->info->on_event(from, to);
    }
  }
}

/***************************************************************************//**
 * Evaluates scheduled wakeup and restart timer based on the wakeup time.
 * If the remaining time is shorter than the wakeup time then add a requirement
 * on EM1 for avoiding the wakeup delay time.
 *
 * @note Must be called in a critical section.
 ******************************************************************************/
static void evaluate_wakeup(sl_power_manager_em_t to)
{
  sl_status_t status;
  uint32_t tick_remaining;

  switch (to) {
    case SL_POWER_MANAGER_EM0:
      // Coming back from Sleep.
      if (requirement_on_em1_added) {
        sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
        requirement_on_em1_added = false;
      }
      break;

    case SL_POWER_MANAGER_EM1:
      // External high frequency clock, such as HFXO, already enabled; No wakeup delay
      break;

    case SL_POWER_MANAGER_EM2:
    case SL_POWER_MANAGER_EM3:
      // Get the time remaining until the next sleeptimer requiring early wake-up
      status = sl_sleeptimer_get_remaining_time_of_first_timer(0, &tick_remaining);
      if (status == SL_STATUS_OK) {
        if (tick_remaining <= high_frequency_min_offtime_tick) {
          // Add EM1 requirement if time remaining is to short to be energy efficient
          // if going back to deepsleep.
          sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
          requirement_on_em1_added = true;
        } else {
          int32_t wakeup_delay = 0;
          int32_t cfg_overhead_tick = 0;

          // Calculate overall wake-up delay.
          sl_atomic_load(cfg_overhead_tick, wakeup_time_config_overhead_tick);
          wakeup_delay += cfg_overhead_tick;
          wakeup_delay += sli_power_manager_get_wakeup_process_time_overhead();
          EFM_ASSERT(wakeup_delay >= 0);
          if (tick_remaining <= (uint32_t)wakeup_delay) {
            // Add EM1 requirement if time remaining is smaller than wake-up delay.
            sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
            requirement_on_em1_added = true;
          } else {
            // Start internal sleeptimer to do the early wake-up.
            sl_sleeptimer_restart_timer(&clock_wakeup_timer_handle,
                                        (tick_remaining - (uint32_t)wakeup_delay),
                                        on_clock_wakeup_timeout,
                                        NULL,
                                        0,
                                        SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG);
          }
        }
      }
      break;

    default:
      EFM_ASSERT(false);
  }
}

/***************************************************************************//**
 * Callback for clock enable timer.
 *
 * @param   handle  Pointer to sleeptimer handle
 *
 * @param   data    Pointer to callback data
 *
 * @note We restore the HF clocks and go to EM1 here to be ready in time for the
 *       Application sleeptimer callback. But no EM1 requirement is added
 *       here. Since the time until the Application sleeptimer times out is <=
 *       than the wake-up delay, it protects us from going back to sleep lower
 *       than EM1. After that, it's up to the Application sleeptimer callback to
 *       put a EM1 requirement if still needed.
 ******************************************************************************/
static void on_clock_wakeup_timeout(sl_sleeptimer_timer_handle_t *handle,
                                    void *data)
{
  (void)handle;
  (void)data;

  if (is_states_saved == true) {
    if (is_hf_x_oscillator_not_preserved) {
      sli_power_manager_restore_high_freq_accuracy_clk();
      is_hf_x_oscillator_not_preserved = false;
    }
    if (sli_power_manager_restore_states(RESTORE_CALLER_ID_EARLY_WAKEUP_TIMEOUT)) {
      // We reset the variable only when the restore is completed.
      is_states_saved = false;
    }
  }

  if (is_states_saved == false) {
    // We do the notification only when the restore is completed.
    power_manager_notify_em_transition(current_em, SL_POWER_MANAGER_EM1);
  }

  early_wakeup_from_em = current_em;
  current_em = SL_POWER_MANAGER_EM1; // Keep new active energy mode
}

/***************************************************************************//**
 * HFXO ready notification callback for internal use with power manager
 *
 * @note Will only be used on series 2 devices when HFXO Manager is present.
 ******************************************************************************/
void sli_hfxo_manager_notify_ready_for_power_manager(void)
{
  // Notify transition to EM1 once HFXO is ready
  // We should only notify here in the case of early wakeup, since we go back
  // to sleep in EM1 during the wait for HFXO ready.
  if (current_em != SL_POWER_MANAGER_EM0
      && is_states_saved == true) {
    sli_power_manager_restore_states(RESTORE_CALLER_ID_RESTORE_READY_NOTIFICATION);
    power_manager_notify_em_transition(early_wakeup_from_em, SL_POWER_MANAGER_EM1);
    current_em = SL_POWER_MANAGER_EM1;
    is_states_saved = false;
  }
}
