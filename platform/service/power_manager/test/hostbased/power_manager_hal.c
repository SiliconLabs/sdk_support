/***************************************************************************//**
 * @file power_manager_control_test.c
 * @brief Power Manager API implementation
 * @version 5.6.0
 *******************************************************************************
 * # License
 * <b>(C) Copyright 2018 Silicon Labs, www.silabs.com</b>
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

#include "power_manager_hal.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "sl_power_manager.h"
#include "sl_slist.h"
#include "emul_nvic.h"
#include "queue.h"
#include "emul_timer.h"
#include <windows.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*******************************************************************************
 ********************************** DEFINES  ***********************************
 ******************************************************************************/

#define POWER_TEST_CMU_IRQ_FLAG_HFXO_RDY        1u
#define POWER_TEST_CMU_IRQ_HFXO_RDY_DELAY_IN_MS 10u

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// HFXO ready IRQ variables
HANDLE  hfxo_ready_event;
HANDLE  hfxo_ready_mutex;
uint8_t cmu_irq_flag = 0;
volatile bool hfxo_ready = false;

// Current active energy mode.
sl_power_manager_em_t sl_power_manager_test_em_last_applied = SL_POWER_MANAGER_EM0;
sl_power_manager_em_t sl_power_manager_test_em_current = SL_POWER_MANAGER_EM0;

// Table of oscillators turn on/off flags. It simulates an oscillator up and
// running or stopped.
bool sl_power_manager_test_high_frequency_oscillator_on_off;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

static void power_em_on_event(sl_power_manager_em_t from,
                              sl_power_manager_em_t to);

static void power_em_on_all_events(sl_power_manager_em_t from,
                                   sl_power_manager_em_t to);

static void power_test_cmu_irq_handler(uint8_t flag);

/*******************************************************************************
 *****************************   EVENT SETUP   *********************************
 ******************************************************************************/

// EM Events
typedef  struct {
  sl_slist_node_t node;
  sl_power_manager_em_t from;
  sl_power_manager_em_t to;
} power_test_em_event_t;

#define POWER_TEST_EM_EVENT_MASK_ALL      (POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0   \
                                           | POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0 \
                                           | POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0  \
                                           | POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM1 \
                                           | POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM1  \
                                           | POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2 \
                                           | POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2  \
                                           | POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3 \
                                           | POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3)

sl_power_manager_em_transition_event_info_t power_test_em_transition_on_all_events_info =
{
  .event_mask = POWER_TEST_EM_EVENT_MASK_ALL,
  .on_event = power_em_on_all_events,
};

sl_power_manager_em_transition_event_handle_t power_test_em_transition_on_all_events_handle;
sl_power_manager_em_transition_event_handle_t power_test_em_transition_on_event_handle;

sl_power_manager_em_transition_event_info_t power_test_em_transition_on_event_info =
{
  .on_event = power_em_on_event,
};

sl_power_manager_em_t sl_power_manager_on_events_em_state_applied = SL_POWER_MANAGER_EM0;
sl_power_manager_em_t sl_power_manager_test_em_applied_on_all_events = SL_POWER_MANAGER_EM0;
sl_slist_node_t *power_em_event_list = NULL;

/*******************************************************************************
 ******************************   FUNCTIONS   **********************************
 ******************************************************************************/

#if POWER_MANAGER_EARLY_HFXO_REQUIREMENT
/******************************************************************************
 * Enables CMU interrupts for HFXO Ready.
 *****************************************************************************/
void sli_power_manager_hfxo_enable_int(void)
{
  cmu_irq_flag = 0;

  hfxo_ready_event = CreateEvent(NULL, TRUE, FALSE, NULL);
  if (hfxo_ready_event == NULL) {
    printf("CreateEvent error: %d\n", (INT)GetLastError());
  }

  hfxo_ready_mutex = CreateMutex(NULL, FALSE, NULL);
  if (hfxo_ready_mutex == NULL) {
    printf("CreateMutex error: %d\n", (INT)GetLastError());
  }
}
#endif

/***************************************************************************//**
 * Applies energy mode.
 *
 * @param em  Energy mode to apply:
 *            SL_POWER_MANAGER_EM0
 *            SL_POWER_MANAGER_EM1
 *            SL_POWER_MANAGER_EM2
 ******************************************************************************/
void sli_power_manager_apply_em(sl_power_manager_em_t em)
{
  // Emulate activation of selected energy mode
  sl_power_manager_test_em_last_applied = em;
  sl_power_manager_test_em_current = em;
}

/***************************************************************************//**
 * Enables or disables the given oscillator source.
 *
 * @param oscillator  oscillator source:
 *                    SL_POWER_OSCILLATOR_HFXO
 *                    SL_POWER_OSCILLATOR_HFRCO
 *                    SL_POWER_OSCILLATOR_AUXHFRCO
 *                    SL_POWER_OSCILLATOR_USHFRCO
 *                    SL_POWER_OSCILLATOR_LFXO
 *                    SL_POWER_OSCILLATOR_LFRCO
 *
 * @param enable      Flag indicating if oscillator is enable (true) or disable
 *                    (false).
 *
 * @note If the oscillator is available at EM3, no need to add or remove
 *       explicitly the requirement on EM3. The requirement is implicit if no
 *       requirement exist on EM0, EM1 and EM2.
 ******************************************************************************/
void sli_power_manager_enable_high_frequency_oscillator(bool enable)
{
  // Emulate enabling/disabling a given oscillator
  sl_power_manager_test_high_frequency_oscillator_on_off = enable;

  // Add proper energy mode requirement given the oscillator enabled or disabled
  if (enable) {
    sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
    sli_generate_hfxo_ready_interrupt(POWER_TEST_CMU_IRQ_HFXO_RDY_DELAY_IN_MS);
  } else {
    hfxo_ready = false;
    sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
  }
}

/***************************************************************************//**
 * Generate energy mode add interrupt (Simulation).
 *
 * @param em  Energy mode to apply:
 *            SL_POWER_MANAGER_EM0
 *            SL_POWER_MANAGER_EM1
 *            SL_POWER_MANAGER_EM2
 ******************************************************************************/
void sli_generate_add_interrupt(sl_power_manager_em_t em, uint32_t msec)
{
  sli_nvic_trigger_delayed_isr(msec,
                               (nvic_callback_t)sl_power_manager_add_em_requirement,
                               (void *)&em);
}

/***************************************************************************//**
 * Generate energy mode remove interrupt (Simulation).
 *
 * @param em  Energy mode to apply:
 *            SL_POWER_MANAGER_EM0
 *            SL_POWER_MANAGER_EM1
 *            SL_POWER_MANAGER_EM2
 ******************************************************************************/
void sli_generate_remove_interrupt(sl_power_manager_em_t em, uint32_t msec)
{
  sli_nvic_trigger_delayed_isr(msec,
                               (nvic_callback_t)sl_power_manager_remove_em_requirement,
                               (void *)&em);
}

/***************************************************************************//**
 * Generate HFXO ready interrupt (Simulation).
 *
 * @param msec  Delay for the ISR
 ******************************************************************************/
void sli_generate_hfxo_ready_interrupt(uint32_t msec)
{
  cmu_irq_flag = POWER_TEST_CMU_IRQ_FLAG_HFXO_RDY;
  sli_nvic_trigger_delayed_isr(msec,
                               power_test_cmu_irq_handler,
                               &cmu_irq_flag);
}

/***************************************************************************//**
 * Reset events counters.
 ******************************************************************************/
void sli_reset_test_objects(sl_power_manager_em_t  em_init)
{
  sl_power_manager_test_em_applied_on_all_events = em_init;
  sl_power_manager_test_em_last_applied = em_init;
  sl_power_manager_test_em_current = em_init;
}

/***************************************************************************//**
 * Reset events list.
 ******************************************************************************/
void sli_reset_em_event_list(void)
{
  sl_slist_node_t *node;
  node = sl_slist_pop(&power_em_event_list);
  while (node != NULL) {
    power_test_em_event_t  *em_event;
    em_event = SL_SLIST_ENTRY(node, power_test_em_event_t, node);

    free(em_event);
    node = sl_slist_pop(&power_em_event_list);
  }
}

/***************************************************************************//**
 * Pop a em event.
 *
 * @param from return from where the transition started
 *
 * @param to return to where the transition went
 ******************************************************************************/
void sli_pop_em_event(sl_power_manager_em_t *from,
                      sl_power_manager_em_t *to)
{
  sl_slist_node_t *node;
  power_test_em_event_t  *em_event;

  *from = POWER_MANAGER_EM_QTY;
  *to = POWER_MANAGER_EM_QTY;

  node = sl_slist_pop(&power_em_event_list);
  if (node == NULL) {
    return;
  }

  em_event = SL_SLIST_ENTRY(node, power_test_em_event_t, node);
  *from = em_event->from;
  *to = em_event->to;

  free(em_event);
}

/***************************************************************************//**
 * On All Events callback
 *
 * @param from EM level from where we start from
 *
 * @param to   EM level where we are going
 ******************************************************************************/
static void power_em_on_all_events(sl_power_manager_em_t from,
                                   sl_power_manager_em_t to)
{
  power_test_em_event_t  *em_event;

  em_event = malloc(sizeof(power_test_em_event_t));
  em_event->from = from;
  em_event->to = to;
  sl_slist_push_back(&power_em_event_list, &em_event->node);
}

/***************************************************************************//**
 * On specific EM Event(s) callback
 *
 * @param from EM level from where we start from
 *
 * @param to   EM level where we are going
 ******************************************************************************/
static void power_em_on_event(sl_power_manager_em_t from,
                              sl_power_manager_em_t to)
{
  power_test_em_event_t  *em_event;

  em_event = malloc(sizeof(power_test_em_event_t));
  em_event->from = from;
  em_event->to = to;
  sl_slist_push_back(&power_em_event_list, &em_event->node);
}

/***************************************************************************//**
 * Simulation for CMU IRQ Handler.
 *
 * @param flag  IRQ Flag.
 ******************************************************************************/
static void power_test_cmu_irq_handler(uint8_t flag)
{
#if POWER_MANAGER_EARLY_HFXO_REQUIREMENT
  sli_power_manager_process_hfxo_ready_irq();
#endif

  if (!SetEvent(hfxo_ready_event)) {
    printf("SetEvent failed (%d)\n", (INT)GetLastError());
  }

  cmu_irq_flag = 0;
}
