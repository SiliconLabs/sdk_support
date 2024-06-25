/***************************************************************************//**
 * @file
 * @brief Bluetooth initialization and event processing
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in a
 *    product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include <sl_common.h>
#include "sl_bluetooth.h"
#include "sl_assert.h"
#include "sl_bt_stack_init.h"
#include "sl_component_catalog.h"
/**
 * Internal stack function to start the Bluetooth stack.
 *
 * @return SL_STATUS_OK if the stack was successfully started
 */
extern sl_status_t sli_bt_system_start_bluetooth();

void sl_bt_init(void)
{
  // Stack initialization could fail, e.g., due to out of memory.
  // The failure could not be returned to user as the system initialization
  // does not return an error code. Use the EFM_ASSERT to catch the failure,
  // which requires either DEBUG_EFM or DEBUG_EFM_USER is defined.
  sl_status_t err = sl_bt_stack_init();
  EFM_ASSERT(err == SL_STATUS_OK);

  // When neither Bluetooth on-demand start feature nor an RTOS is present, the
  // Bluetooth stack is always started already at init-time.
#if !defined(SL_CATALOG_BLUETOOTH_ON_DEMAND_START_PRESENT) && !defined(SL_CATALOG_KERNEL_PRESENT)
  err = sli_bt_system_start_bluetooth();
  EFM_ASSERT(err == SL_STATUS_OK);
#endif
}

SL_WEAK void sl_bt_on_event(sl_bt_msg_t* evt)
{
  (void)(evt);
}

void sl_bt_process_event(sl_bt_msg_t *evt)
{
  sl_bt_on_event(evt);
}

#if !defined(SL_CATALOG_KERNEL_PRESENT)
// When running in an RTOS, the stack events are processed in a dedicated
// event processing task, and these functions are not used at all.

SL_WEAK bool sl_bt_can_process_event(uint32_t len)
{
  (void)(len);
  return true;
}

void sl_bt_step(void)
{
  sl_bt_msg_t evt;

  sl_bt_run();
  uint32_t event_len = sl_bt_event_pending_len();
  // For preventing from data loss, the event will be kept in the stack's queue
  // if application cannot process it at the moment.
  if ((event_len == 0) || (!sl_bt_can_process_event(event_len))) {
    return;
  }

  // Pop (non-blocking) a Bluetooth stack event from event queue.
  sl_status_t status = sl_bt_pop_event(&evt);
  if(status != SL_STATUS_OK){
    return;
  }
  sl_bt_process_event(&evt);
}
#endif // !defined(SL_CATALOG_KERNEL_PRESENT)
