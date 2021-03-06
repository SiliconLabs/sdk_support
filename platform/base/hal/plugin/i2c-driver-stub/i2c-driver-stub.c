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

void halI2cInitialize(void)
{
}

void emberAfPluginI2cDriverInitCallback(void)
{
}

uint8_t halI2cWriteBytes(uint8_t address, const uint8_t *buffer, uint8_t count)
{
  return 0;
}

uint8_t halI2cWriteBytesDelay(uint8_t address,
                              const uint8_t *buffer,
                              uint8_t count,
                              uint8_t delay)
{
  return 0;
}

uint8_t halI2cReadBytes(uint8_t address, uint8_t *buffer, uint8_t count)
{
  return 0;
}
