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
#include "stack/include/ember-types.h"
#include "hal/plugin/humidity-temperature-si7021/humidity.h"

EmberEventControl emberAfPluginHumiditySi7021InitEventControl;
EmberEventControl emberAfPluginHumiditySi7021ReadEventControl;

void emberAfPluginHumiditySi7021InitEventHandler(void)
{
}

void emberAfPluginHumiditySi7021ReadEventHandler(void)
{
}

void emberAfPluginHumiditySi7021InitCallback(void)
{
}

void halHumidityStartRead(void)
{
  halHumidityReadingCompleteCallback(4321, 1);
}

uint16_t halHumidityGetMaxMeasureableHumidityDeciPercent(void)
{
  return 9999;
}

uint16_t halHumidityGetMinMeasureableHumidityDeciPercent(void)
{
  return 0001;
}

void halHumidityInit(void)
{
}
