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

/***************************************************************************
 * @file
 * @brief WFX FMAC driver main bus communication task
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc.
 *www.silabs.com</b>
 *******************************************************************************
 *
 * Licensed under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in
 *compliance with the License. You may obtain a copy
 *of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 *writing, software distributed under the License is
 *distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
 *OR CONDITIONS OF ANY KIND, either express or
 *implied. See the License for the specific language
 *governing permissions and limitations under the
 *License.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "em_gpio.h"

#include "sl_wfx.h"
#include "sl_wfx_board.h"
#include "sl_wfx_host.h"
#include "sl_wfx_task.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

#include "AppConfig.h"

#define	CHECK_VAL			0
#define WFX_BUS_TASK_PRIORITY    	2
#define BUS_TASK_STACK_SIZE 		1024
static StackType_t busStack[BUS_TASK_STACK_SIZE];
StaticTask_t busTaskStruct;
TaskHandle_t wfx_bus_task_handle;

wfx_frame_q_item wfx_bus_tx_frame;
SemaphoreHandle_t wfxtask_tx_complete;
SemaphoreHandle_t wfxtask_mutex;
EventGroupHandle_t wfx_bus_events;
sl_wfx_packet_queue_t sl_wfx_tx_queue_context;

#if defined(EFR32MG12)
// Flag to indicate receive frames is currently running.
static bool wfx_bus_rx_in_process = false;

/***************************************************************************
 * Check receive frame status
 ******************************************************************************/
bool wfx_bus_is_receive_processing(void)
{
  return wfx_bus_rx_in_process;
}

/*****************************************************************************
 * Receives frames from the WFX.
 ******************************************************************************/
static sl_status_t receive_frames()
{
  sl_status_t result;
  uint16_t control_register = 0;
  wfx_bus_rx_in_process     = true;
  do {
    result = sl_wfx_receive_frame(&control_register);
    SL_WFX_ERROR_CHECK(result);
  } while ((control_register & SL_WFX_CONT_NEXT_LEN_MASK) != CHECK_VAL);

error_handler:
  wfx_bus_rx_in_process = false;
  return result;
}
#endif

#if defined(EFR32MG24)
/***************************************************************************//**
 * Receives frames from the WF200.
 ******************************************************************************/
static sl_status_t sl_wfx_rx_process(uint16_t control_register)
{
 // RTOS_ERR err;
  sl_status_t result;

  result = sl_wfx_receive_frame(&control_register);
  if ((control_register & SL_WFX_CONT_NEXT_LEN_MASK) != 0) {
    /* if a packet is still available in the WF200, set an RX event */
   // OSFlagPost(&bus_events, SL_WFX_BUS_EVENT_FLAG_RX, OS_OPT_POST_FLAG_SET, &err); /* Micrium os replace with the free RTOS call */
    xEventGroupSetBits(wfx_bus_events, SL_WFX_BUS_EVENT_FLAG_RX);
  }

  return result;
}
/**************************************************************************//**
 * Wfx process tx queue
 *****************************************************************************/
static sl_status_t sl_wfx_tx_process(void)
{
 // RTOS_ERR err;
  sl_status_t result;
  sl_wfx_packet_queue_item_t *item_to_free;

  if (sl_wfx_tx_queue_context.head_ptr == NULL) {
    return SL_STATUS_EMPTY;
  }

  /* Take TX queue mutex */
 // OSMutexPend(&sl_wfx_tx_queue_mutex, 0, OS_OPT_PEND_BLOCKING, 0, &err); /* Micrium os replace with the free RTOS call */

  if (xSemaphoreTake(wfxtask_mutex, portMAX_DELAY) != pdTRUE) {
    result = SL_STATUS_TIMEOUT;
  }

  /* Send the packet */
  result = sl_wfx_send_ethernet_frame(&sl_wfx_tx_queue_context.head_ptr->buffer,
                                      sl_wfx_tx_queue_context.head_ptr->data_length,
                                      sl_wfx_tx_queue_context.head_ptr->interface,
                                      WFM_PRIORITY_BE0);

  if (result != SL_STATUS_OK) {
    /* If the packet is not successfully sent, set the associated event and return */
   // OSFlagPost(&bus_events, SL_WFX_BUS_EVENT_FLAG_TX, OS_OPT_POST_FLAG_SET, &err); /* Micrium os replace with the free RTOS call */
    xEventGroupSetBits(wfx_bus_events, SL_WFX_BUS_EVENT_FLAG_TX);
    //OSMutexPost(&sl_wfx_tx_queue_mutex, OS_OPT_POST_NONE, &err); /* Micrium os replace with the free RTOS call */
    xSemaphoreGive(wfxtask_mutex);
    return SL_STATUS_FULL;
  }

  /* The packet has been successfully sent, free it  */
  item_to_free = sl_wfx_tx_queue_context.head_ptr;

  /* Move the queue pointer to process the next packet */
  sl_wfx_tx_queue_context.head_ptr = sl_wfx_tx_queue_context.head_ptr->next;

  /* The packet has been sent, release the packet  */
  sl_wfx_free_command_buffer((sl_wfx_generic_message_t*) item_to_free,
                             SL_WFX_SEND_FRAME_REQ_ID,
                             SL_WFX_TX_FRAME_BUFFER);

  /* If a packet is available, set the associated event */
  if (sl_wfx_tx_queue_context.head_ptr != NULL) {
    //OSFlagPost(&bus_events, SL_WFX_BUS_EVENT_FLAG_TX, OS_OPT_POST_FLAG_SET, &err); /* Micrium os replace with the free RTOS call */
    xEventGroupSetBits(wfx_bus_events, SL_WFX_BUS_EVENT_FLAG_TX);
  }

  /* Release TX queue mutex */
//OSMutexPost(&sl_wfx_tx_queue_mutex, OS_OPT_POST_NONE, &err); /* Micrium os replace with the free RTOS call */
  xSemaphoreGive(wfxtask_mutex);

  return result;
}
#endif
/*
 * WFX bus communication task.
 * receives frames from the Bus interface
 */
static void wfx_bus_task(void *p_arg)
{
  EFR32_LOG("SPI: Bus Task started");
#if defined(EFR32MG12)
  sl_wfx_host_start_platform_interrupt();
  for (;;) {
    /*Wait for an interrupt from WFX*/
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    /*Disable the interrupt while treating frames received to avoid
         *the case where the interrupt is set but there is no frame left to treat.*/
    sl_wfx_host_disable_platform_interrupt();

    /*Receive the frame(s) pending in WFX*/
    receive_frames();

    /*Re-enable the interrupt*/
    sl_wfx_host_enable_platform_interrupt();
  }
#elif defined(EFR32MG24)
 // RTOS_ERR err;
  uint16_t control_register = 0;
  EventBits_t flags;

  (void)p_arg;

  //sl_wfx_host_setup_memory_pools(); /* need to to replace Micrium os call with the free RTOS call */

  while (1) {
  #ifdef SLEEP_ENABLED
  #ifdef SL_WFX_USE_SPI
    if (GPIO_PinInGet(SL_WFX_HOST_PINOUT_SPI_WIRQ_PORT, SL_WFX_HOST_PINOUT_SPI_WIRQ_PIN)) //wfx messages pending
  #else
    if (GPIO_PinInGet(SL_WFX_HOST_PINOUT_GPIO_WIRQ_PORT, SL_WFX_HOST_PINOUT_GPIO_WIRQ_PIN))
  #endif
    {
     // OSFlagPost(&bus_events, SL_WFX_BUS_EVENT_FLAG_RX, OS_OPT_POST_FLAG_SET, &err); /* Micrium os replace with the free RTOS call */
      xEventGroupSetBits(wfx_bus_events, SL_WFX_BUS_EVENT_FLAG_RX);
    }
  #endif
  /*Wait for an event*/
  /*flags = OSFlagPend(&bus_events, 0xF, SL_WFX_EVENT_TIMEOUT_MS,
                       OS_OPT_PEND_FLAG_SET_ANY | OS_OPT_PEND_BLOCKING | OS_OPT_PEND_FLAG_CONSUME,
                       0, &err);*/ /* Micrium os replace with the free RTOS call */
   flags = xEventGroupWaitBits(wfx_bus_events,
                                SL_WFX_BUS_EVENT_FLAG_RX |
                                SL_WFX_BUS_EVENT_FLAG_TX,
                                pdTRUE,
                                pdFALSE,
                                pdMS_TO_TICKS(250));
  if (flags & SL_WFX_BUS_EVENT_FLAG_TX) {
    /* Process TX packets */
    sl_wfx_tx_process();
  }
  if (flags & SL_WFX_BUS_EVENT_FLAG_RX) {
    /* Process RX packets */
    sl_wfx_rx_process(control_register);
  #ifdef SL_WFX_USE_SDIO
    /* Reenable interrupt (req for sdio)*/
    sl_wfx_host_enable_platform_interrupt();
  #endif
  }
}
#endif
}

/***************************************************************************
 * Creates WFX bus communication task.
 ******************************************************************************/
void wfx_bus_start()
{
  wfxtask_mutex = xSemaphoreCreateMutex();

   /* create an event group to track Bus events */
  wfx_bus_events = xEventGroupCreate();

  sl_wfx_tx_queue_context.head_ptr = NULL;
  sl_wfx_tx_queue_context.tail_ptr = NULL;

  wfx_bus_task_handle =
    xTaskCreateStatic(wfx_bus_task, "wfxbus", BUS_TASK_STACK_SIZE, NULL, WFX_BUS_TASK_PRIORITY, busStack, &busTaskStruct);
  if (wfx_bus_task_handle == NULL) {
    EFR32_LOG("*ERR*WFX BusTask");
  }
}
