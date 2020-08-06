/***************************************************************************//**
 * @file
 * @brief stub implementation of button functions.
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
#include "stack/include/ember-types.h"
#include "hal/hal.h"

void halInternalInitButton(void)
{
}

uint8_t halButtonState(uint8_t button)
{
  return BUTTON_RELEASED;
}

uint8_t halButtonPinState(uint8_t button)
{
  return BUTTON_RELEASED;
}

uint16_t halGpioIsr(uint16_t interrupt, uint16_t pcbContext)
{
  return 0;
}

uint16_t halTimerIsr(uint16_t interrupt, uint16_t pcbContext)
{
  return 0;
}

void simulatedButtonIsr(uint8_t button, bool isPress)
{
}
