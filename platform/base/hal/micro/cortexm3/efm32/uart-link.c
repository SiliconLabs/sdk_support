/***************************************************************************//**
 * @file
 * @brief low-level driver for sending typed blocks of data on EFM
 * or in simulation.
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
#include PLATFORM_HEADER
#if defined(EMBER_STACK_CONNECT)
#include "stack/include/ember.h"
#else
#include "stack/core/ember-stack.h"
#endif
#include "hal/hal.h"
#include "hal/micro/uart-link.h"
#include "hal/micro/generic/ash-v3.h"
#include "serial/com.h"
#include "uart_link_config.h"

#define BUFFER_SIZE 100

void halHostSerialInit(void)
{
  COM_Init_t initData = (COM_Init_t) NCP_COM_INIT;
  COM_Init(UART_PORT, &initData);
}

void halHostSerialTick(void)
{
  uint8_t byte;
  uint8_t ashInput[BUFFER_SIZE] = { 0 };
  uint8_t i = 0;

  while (COM_ReadByte(UART_PORT, &byte) == EMBER_SUCCESS
         && i < BUFFER_SIZE) {
    ashInput[i] = byte;
    i++;
  }

  if (COM_InternalTxIsIdle(UART_PORT)) {
    emAshNotifyTxComplete();
  }

  if (i > 0) {
    emProcessAshRxInput(ashInput, i);
  }
}

void halHostUartLinkTx(const uint8_t *data, uint16_t length)
{
  COM_WriteData(UART_PORT, (uint8_t *)data, length);
}

bool halHostUartTxIdle(void)
{
  return (COM_InternalTxIsIdle(UART_PORT));
}
