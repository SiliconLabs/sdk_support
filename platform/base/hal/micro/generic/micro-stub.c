/***************************************************************************//**
 * @file
 * @brief stub implementation of HAL
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

void halInit(void)
{
}

void halReboot(void)
{
  fprintf(stderr, "[rebooting]\n");
  exit(1);
}

void halPowerDown(void)
{
}

void halPowerUp(void)
{
}

void halSleep(SleepModes sleepMode)
{
}

PGM_P halGetResetString(void)
{
  static PGM_P resetString = "UNKWN";
  return (resetString);
}

uint8_t halGetResetInfo(void)
{
  return 0;
}
