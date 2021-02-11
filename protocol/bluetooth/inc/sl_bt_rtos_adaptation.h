/***************************************************************************//**
 * @brief Adaptation for running Bluetooth in RTOS
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_BT_RTOS_ADAPTATION_H
#define SL_BT_RTOS_ADAPTATION_H

#include "sl_bt_api.h"

/***************************************************************************//**
 * @addtogroup bluetooth_rtos_adaptation
 * @{
 *
 * @brief Bluetooth RTOS adaptation
 *
 * The Bluetooth RTOS adaptation component implements the relevant interfaces
 * for running the Bluetooth stack in an RTOS. When initialized in @ref
 * sl_bt_rtos_init(), the component creates the required RTOS tasks for the
 * Bluetooth stack itself, and an event task that is used to deliver @ref
 * sl_bt_process_event() and @ref sl_bt_on_event() callbacks to the application.
 *
 * To guarantee thread safety and avoid the risk of deadlocks, the Bluetooth
 * RTOS adaptation implementation makes the following promises with regard to
 * the locking mechanism provided in the API:
 *
 * 1. The stack will never directly call @ref sl_bt_process_event() or @ref
 *    sl_bt_on_event() from within the same callstack that is calling a command
 *    function. The callbacks always come from a processing loop in an event
 *    task created for this purpose.
 *
 * 2. The stack will never internally obtain the @ref sl_bt_bluetooth_pend()
 *    lock. It is safe for the application to obtain the lock also from within
 *    the @ref sl_bt_on_event() callback.
 */

/**
 * @brief Hooks for API, called from tasks using Bluetooth API
 */
void sli_bt_cmd_handler_rtos_delegate(uint32_t header, sl_bgapi_handler handler, const void* payload);

/**
 * @brief Check if there any Bluetooth stack event waiting
 * This API will not clear the event waiting flag.
 * @note This API is meant to be used in applications define own Bluetooth event handler,
 * it should be only used if SL_BT_DISABLE_EVENT_TASK is defined.
 * @return SL_STATUS_OK if event is waiting, otherwise SL_STATUS_FAIL or error
 */
sl_status_t sl_bt_rtos_has_event_waiting();

/**
 * @brief Wait Bluetooth stack to generate an event
 * This API will clear the event waiting flag.
 * @note This API is meant to be used in applications define own Bluetooth event handler,
 * it should be only used if SL_BT_DISABLE_EVENT_TASK is defined.
 * @param[in] blocking specifies if the function would block until event is generated
 * @return SL_STATUS_OK if the event is generated or some error
 */
sl_status_t sl_bt_rtos_event_wait(bool blocking);

/**
 * @brief Message Bluetooth stack that event is handled
 * This will set event handled flag.
 * @note This API is meant to be used in applications define own Bluetooth event handler,
 * it should be only used if SL_BT_DISABLE_EVENT_TASK is defined.
 * @return SL_STATUS_OK if successful or some error
 */
sl_status_t sl_bt_rtos_set_event_handled();

/**
 * @brief Mutex functions for using Bluetooth from multiple tasks
 * @return SL_STATUS_OK if mutex has been obtained
 */
sl_status_t sl_bt_bluetooth_pend();

/**
 * @brief Mutex functions for using Bluetooth from multiple tasks
 * @return SL_STATUS_OK the mutex has been released
 */
sl_status_t sl_bt_bluetooth_post();

/**
 * @brief Initialize Bluetooth for running in RTOS.
 * @return SL_STATUS_OK if succeeds, otherwise error
 */
sl_status_t sl_bt_rtos_init();

/**
 * @brief Gets the pointer to current Bluetooth event.
 *
 * Caller needs to make sure this is used for Bluetooth event processing
 * only when @ref sl_bt_rtos_event_wait indicates an event is waiting to be
 * processed. Otherwise the event may contain outdated data.
 *
 * @return pointer to the Bluetooth event
 */
const sl_bt_msg_t* sl_bt_rtos_get_event();

/** @} end bluetooth_rtos_adaptation */

#endif //SL_BT_RTOS_ADAPTATION_H
