/***************************************************************************//**
 * @file
 * @brief Power Manager HAL API implementation.
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
#include "em_device.h"
#if (defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1))
#include "em_emu.h"
#include "em_cmu.h"
#include "em_assert.h"
#include "sl_power_manager_config.h"
#include "sl_power_manager.h"
#include "sli_power_manager_private.h"
#include "sl_sleeptimer.h"
#include "sli_sleeptimer.h"

#include <stdbool.h>

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

#if defined(_SILICON_LABS_32B_SERIES_1)
#if !defined(PRORTC_PRESENT)
// RTCC prescaler affects the wakeup overhead
#define EM2_PRESCALER_TIMING (5 * (1 - (1 << ((RTCC->CTRL & _RTCC_CTRL_CNTPRESC_MASK) >> _RTCC_CTRL_CNTPRESC_SHIFT))))
#else
#define EM2_PRESCALER_TIMING (0)
#endif
#else
#define EM2_PRESCALER_TIMING (0)
#endif

// Time required by the hardware to come out of EM2 in microseconds.
// This value includes HW startup, emlib and sleepdrv execution time.
// Voltage scaling, HFXO startup and HFXO steady times are excluded from
// this because they are handled separately. RTCCSYNC time is also
// excluded and it is handled by RTCCSYNC code itself.
//TODO need to validate this value. how?
#define EM2_WAKEUP_PROCESS_TIME_OVERHEAD_US (100 + EM2_PRESCALER_TIMING) //(215 + EM2_PRESCALER_TIMING)

// Time it takes to upscale voltage after EM2 in microseconds.
#define EM2_WAKEUP_VSCALE_OVERHEAD_US (30)

// DPLL Locking delay
#define DPLL_COARSECOUNT_VALUE  (5u)

// Default time value in microseconds required to start-up the hfxo oscillator.
#define HFXO_START_UP_TIME_DEFAULT_VALUE_US  (600u)

// high frequency oscillator wake-up time margin for possible variation
// A shift by 3 will be like a division by 8, so a percentage of 12.5%.
#define HFXO_START_UP_TIME_OVERHEAD_LOG2   3

// Default time value in microseconds for the HFXO minimum off time.
#if defined(_SILICON_LABS_32B_SERIES_1) \
  && (_SILICON_LABS_GECKO_INTERNAL_SDID >= 100)
// Default value for series 1 EFM devices.
#define HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US  1000u
#elif defined(_CMU_HFXOCTRL_MASK)
// Default value for series 1 EFR devices.
#define HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US  600u
#else
// Default value for series 0 devices.
#define HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US  1200u
#endif

/*******************************************************************************
 *******************************  MACROS   *************************************
 ******************************************************************************/

/*******************************************************************************
* DPLL lock time can be approximately calculated by the equation:
*   COARSECOUNT * (N + 1) * Thfrco
* Where
*   - COARSECOUNT is calibration value in a hidden register. Its default value
*     is 5 and should not change with calibration.
*   - N is one the DPLL configuration parameter.
*   - Thfrco is the targeted HFRCO period.
*******************************************************************************/
#define DPLL_LOCKING_DELAY_US_FUNCTION(N, freq_hfrco) \
  ((uint64_t)(DPLL_COARSECOUNT_VALUE * ((N) +1)) * 1000000 + ((freq_hfrco) - 1)) / (freq_hfrco)

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// Time in ticks required for HFXO start-up after wake-up from sleep.
static uint32_t hfxo_wakeup_time_tick = 0;
static bool is_hf_x_oscillator_used = false;

static bool is_hf_x_oscillator_already_started = false;
static uint32_t hf_x_oscillator_wakeup_time_tc_inital = 0;

#if defined(_CMU_DPLLCTRL_MASK)
static bool is_dpll_used = false;
#endif

// Time in ticks required for the general wake-up process.
static uint32_t process_wakeup_overhead_tick = 0;

/***************************************************************************//**
 * Do some hardware initialization if necessary.
 ******************************************************************************/
void sli_power_manager_init_hardware(void)
{
  EMU_EM23Init_TypeDef em23_init = EMU_EM23INIT_DEFAULT;

  // Initializes EMU (voltage scaling in EM2/3)
#if defined(EMU_VSCALE_PRESENT)
  EMU_EM01Init_TypeDef em01_init = EMU_EM01INIT_DEFAULT;

  EMU_EM01Init(&em01_init);

#if (SL_POWER_MANAGER_CONFIG_VOLTAGE_SCALING_FAST_WAKEUP == 0)
  em23_init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
#else
  em23_init.vScaleEM23Voltage = emuVScaleEM23_FastWakeup;
#endif
#endif

  EMU_EM23Init(&em23_init);

  is_hf_x_oscillator_used = (CMU->STATUS & _CMU_STATUS_HFXOENS_MASK) == _CMU_STATUS_HFXOENS_MASK;
#if defined(_CMU_DPLLCTRL_MASK)
  is_dpll_used = (CMU->STATUS & CMU_STATUS_DPLLENS) == CMU_STATUS_DPLLENS;
#endif

  // Enable HFXO Interrupt if HFXO is used
  if (is_hf_x_oscillator_used) {
    // Initialize default values for HFXO start-up time
    hfxo_wakeup_time_tick = sli_power_manager_convert_delay_us_to_tick(HFXO_START_UP_TIME_DEFAULT_VALUE_US);
  }

  // Calculate DPLL locking delay from its configuration
#if defined(_CMU_DPLLCTRL_MASK)
  if (is_dpll_used) {
    uint32_t freq = CMU_ClockFreqGet(cmuClock_HF);
    freq = freq * (((CMU->HFPRESC & _CMU_HFPRESC_PRESC_MASK) >> _CMU_HFPRESC_PRESC_SHIFT) + 1);
    // Add DPLL Locking delay
    process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(DPLL_LOCKING_DELAY_US_FUNCTION((CMU->DPLLCTRL1 & _CMU_DPLLCTRL1_N_MASK) >> _CMU_DPLLCTRL1_N_SHIFT, freq));
  }
#endif

  // Calculate and add other wake-up delays in ticks
#if defined(EMU_VSCALE_PRESENT) && (SL_POWER_MANAGER_CONFIG_VOLTAGE_SCALING_FAST_WAKEUP == 0)
  // Add Voltage scaling delay if applicable
  process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(EM2_WAKEUP_VSCALE_OVERHEAD_US);
#endif
  process_wakeup_overhead_tick += sli_power_manager_convert_delay_us_to_tick(EM2_WAKEUP_PROCESS_TIME_OVERHEAD_US);
}

/***************************************************************************//**
 * Save the CMU HF clock select state, oscillator enable, and voltage scaling.
 ******************************************************************************/
void sli_power_manager_save_states(void)
{
  EMU_Save();
}

/***************************************************************************//**
 * Handle post-sleep operations. The idea is to start HFXO ASAP when we know we
 * will need it.
 ******************************************************************************/
void EMU_EM23PostsleepHook(void)
{
  // Poke sleeptimer to determine if power manager's timer expired before the
  // ISR handler executes.
  if (is_hf_x_oscillator_used
      && sli_sleeptimer_hal_is_int_status_set(SLEEPTIMER_EVENT_COMP)
      && sli_sleeptimer_is_power_manager_timer_next_to_expire()) {
    CMU_OscillatorEnable(cmuOsc_HFXO, true, false);

    hf_x_oscillator_wakeup_time_tc_inital = sl_sleeptimer_get_tick_count();
    is_hf_x_oscillator_already_started = true;
  }
}

/***************************************************************************//**
 * Handle pre-deepsleep operations if any are necessary, like manually disabling
 * oscillators, change clock settings, etc.
 ******************************************************************************/
void sli_power_manager_handle_pre_deepsleep_operations(void)
{
}

/***************************************************************************//**
 * Handle post-sleep operations if any are necessary, like manually enabling
 * oscillators, change clock settings, etc.
 ******************************************************************************/
void sli_power_manager_restore_high_freq_accuracy_clk(void)
{
}

/***************************************************************************//**
 * Checks if HF accuracy clocks is fully restored and, if needed, waits for it.
 *
 * @param wait  True, to wait for HF accuracy clocks to be ready
 *              False, otherwise.
 *
 * @return True, if HFXO ready.
 *         False, otherwise.
 ******************************************************************************/
bool sli_power_manager_is_high_freq_accuracy_clk_ready(bool wait)
{
  (void)wait;

  return true;
}

/***************************************************************************//**
 * Restore CMU HF clock select state, oscillator enable, and voltage scaling.
 *
 * @return True, if restore is complete
 *         False, otherwise.
 ******************************************************************************/
void sli_power_manager_restore_states(void)
{
  // For the cases where it's not started from an early wake up
  if (!is_hf_x_oscillator_already_started
      && is_hf_x_oscillator_used) {
    hf_x_oscillator_wakeup_time_tc_inital = sl_sleeptimer_get_tick_count();
  }

  EMU_Restore();

  if (is_hf_x_oscillator_used) {
    // If HFXO is needed but somehow doesn't clock the cpu, wait for it to be ready.
    while (!(CMU->STATUS & _CMU_STATUS_HFXORDY_MASK)) {
    }

    hfxo_wakeup_time_tick = sl_sleeptimer_get_tick_count() - hf_x_oscillator_wakeup_time_tc_inital;
    is_hf_x_oscillator_already_started = false;
  }

#if 0 // TODO This seems to cause issues in some cases. That has to be fixed.
#if defined(_CMU_DPLLCTRL_MASK)
  if (is_dpll_used) {
    // If DPLL is used, wait for it to be ready.
    while (!(CMU->STATUS & _CMU_STATUS_DPLLRDY_MASK)) {
    }
  }
#endif
#endif
}

/***************************************************************************//**
 * Applies energy mode.
 *
 * @param em  Energy mode to apply:
 *            SL_POWER_MANAGER_EM0
 *            SL_POWER_MANAGER_EM1
 *            SL_POWER_MANAGER_EM2
 *
 * @note EMU_EnterEM2() and EMU_EnterEM3() has the parameter 'restore' set to
 *       true in the Power Manager. When set to true, the parameter 'restore'
 *       allows the EMU driver to save and restore oscillators, clocks and
 *       voltage scaling. When the processor returns from EM2 or EM3, its
 *       execution resumes in a clean and stable state.
 ******************************************************************************/
void sli_power_manager_apply_em(sl_power_manager_em_t em)
{
  // Perform required actions according to energy mode
  switch (em) {
    case SL_POWER_MANAGER_EM1:
      EMU_EnterEM1();
      break;

    case SL_POWER_MANAGER_EM2:
      EMU_EnterEM2(false);
      break;

    case SL_POWER_MANAGER_EM3:
      EMU_EnterEM3(false);
      break;

    case SL_POWER_MANAGER_EM0:
    default:
      EFM_ASSERT(false);
      break;
  }
}

/*******************************************************************************
 * Returns if the HFXO is enabled or not.
 ******************************************************************************/
bool sli_power_manager_is_high_frequency_running(void)
{
  return is_hf_x_oscillator_used;
}

/*******************************************************************************
 * Returns the default minimum offtime for HFXO.
 ******************************************************************************/
uint32_t sli_power_manager_get_default_high_frequency_minimum_offtime(void)
{
  return sli_power_manager_convert_delay_us_to_tick(HFXO_MINIMUM_OFFTIME_DEFAULT_VALUE_US);
}

/*******************************************************************************
 * Gets the delay associated the wake-up process from EM23.
 *
 * @return Delay for the complete wake-up process with full restore.
 ******************************************************************************/
uint32_t sli_power_manager_get_wakeup_process_time_overhead(void)
{
  uint32_t delay = 0;
  uint32_t delay_temp = 0;

  // Add HFXO start-up delay if applicable
  if (hfxo_wakeup_time_tick != 0) {
    delay_temp = hfxo_wakeup_time_tick;
    delay_temp += delay_temp >> HFXO_START_UP_TIME_OVERHEAD_LOG2;
    delay += delay_temp;
  }

  // Add all additional overhead wake-up delays (DPLL, VSCALE, general wake-up process)
  delay += process_wakeup_overhead_tick;

  return delay;
}
#endif
