/***************************************************************************//**
 * @file
 * @brief Stubs for ASHv3 for images that don't need it.
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
#include "stack/core/ember-stack.h"
#include "hal/hal.h"
#include "hal/micro/serial.h"
#include "hal/micro/uart-link.h"

bool uartTxSpaceAvailable(void)
{
  return true;
}

void uartFlushTx(void)
{
}

void uartLinkReset(void)
{
  halHostSerialInit();
}

extern bool halHostTxIsIdle(void);

bool emAshPreparingForPowerDown(void)
{
  // if the HAL TX is idle, then we return false
  // (we're not preparing to power down anymore)
  return !halHostTxIsIdle();
}

void emAshNotifyTxComplete(void)
{
}

void emAshConfigUart(uint8_t dropPercentage, uint8_t corruptPercentage)
{
}
