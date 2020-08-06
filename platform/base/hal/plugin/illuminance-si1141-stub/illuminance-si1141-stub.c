/***************************************************************************//**
 * @file
 * @brief
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
#include "hal/plugin/illuminance-si1141/illuminance.h"
#include "stack/include/ember-types.h"

//------------------------------------------------------------------------------
// Plugin events
EmberEventControl emberAfPluginIlluminanceSi1141InitEventControl;
EmberEventControl emberAfPluginIlluminanceSi1141ReadEventControl;

void emberAfPluginIlluminanceSi1141InitEventHandler(void)
{
}

void emberAfPluginIlluminanceSi1141ReadEventHandler(void)
{
}

void emberAfPluginIlluminanceSi1141InitCallback(void)
{
}

void halIlluminanceInit(void)
{
}

uint8_t halIlluminanceCalibrate(uint32_t extLux)
{
  return 0;
}

uint16_t halIlluminanceStartRead(uint8_t multiplier)
{
  halIlluminanceReadingCompleteCallback(0xBEEF);
  return 0;
}

uint16_t halIlluminanceGetMaxMeasureableIlluminanceLogLux(void)
{
  return 0xFFFD;
}

uint16_t halIlluminanceGetMinMeasureableIlluminanceLogLux(void)
{
  return 0x0002;
}
