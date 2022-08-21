
/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/****************************************************************************
 * Copyright 2019, Silicon Laboratories Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in
 *compliance with the License. You may obtain a copy of
 *the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 *writing, software distributed under the License is
 *distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
 *OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing
 *permissions and limitations under the License.
 *****************************************************************************/
#pragma once

#include <stdbool.h>

#include "FreeRTOS.h"
#include "sl_wfx_constants.h"
#include "task.h"
#define SL_WFX_BUS_EVENT_FLAG_RX      1
#define SL_WFX_BUS_EVENT_FLAG_TX      2
#define SL_WFX_BUS_EVENT_WAKE         4
#define SL_WFX_BUS_QUEUE_SIZE        10
typedef struct {
  sl_wfx_send_frame_req_t *frame;
  uint32_t data_length;
  sl_wfx_interface_t interface;
  uint8_t priority;
} wfx_frame_q_item;

/* Packet Queue */
typedef struct sl_wfx_packet_queue_item_t{
  struct sl_wfx_packet_queue_item_t *next;
  sl_wfx_interface_t interface;
  uint32_t data_length;
  sl_wfx_send_frame_req_t buffer;
}sl_wfx_packet_queue_item_t;

/* Packet Queue */
typedef struct {
  sl_wfx_packet_queue_item_t *head_ptr;
  sl_wfx_packet_queue_item_t *tail_ptr;
}sl_wfx_packet_queue_t;

extern wfx_frame_q_item wfxtask_tx_frame;
extern TaskHandle_t wfx_bus_task_handle;

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 * Start wfx bus communication task.
 *****************************************************************************/
void wfx_bus_start(void);

/****************************************************************************
 * Returns status of wfx receive frames.
 *****************************************************************************/
bool wfx_bus_is_receive_processing(void);

/***************************************************************************//**
 * Receives frames from the WF200.
 ******************************************************************************/
static sl_status_t sl_wfx_rx_process(uint16_t control_register);

/**************************************************************************//**
 * Wfx process tx queue
 *****************************************************************************/
static sl_status_t sl_wfx_tx_process(void);

#ifdef __cplusplus
}
#endif
