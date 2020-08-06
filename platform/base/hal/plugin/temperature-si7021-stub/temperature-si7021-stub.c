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
#include "hal/plugin/temperature/temperature.h"

EmberEventControl emberAfPluginTemperatureSi7021InitEventControl;
EmberEventControl emberAfPluginTemperatureSi7021ReadEventControl;

void emberAfPluginTemperatureSi7021InitEventHandler(void)
{
}

void emberAfPluginTemperatureSi7021ReadEventHandler(void)
{
}

void emberAfPluginTemperatureSi7021InitCallback(void)
{
}

void halTemperatureStartRead(void)
{
  halTemperatureReadingCompleteCallback(0xCAFE, false);
}

void halTemperatureInit(void)
{
}
