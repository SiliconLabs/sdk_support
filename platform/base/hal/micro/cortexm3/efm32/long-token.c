/**
 * @file hal/micro/cortexm3/emf32/long-token.c
 * @brief Functions to set and retreive data in the new Long Token Section of memory
 *
 * Copyright 2018 by Silicon Labs. All rights reserved.
 */

#include PLATFORM_HEADER
#if defined(CONFIGURATION_HEADER)
  #include CONFIGURATION_HEADER
#endif
#include "include/error.h"
#include "hal/micro/cortexm3/flash.h"

EmberStatus halCommonGetLongTokenData(void *data, uint8_t *address, uint32_t length)
{
  if (length == 0) {
    return EMBER_BAD_ARGUMENT;
  }

  uint8_t *ram = (uint8_t *)data;

  MEMCOPY(ram, address, length);

  return EMBER_SUCCESS;
}

EmberStatus halCommonSetLongTokenData(void *data, uint8_t *address, uint32_t length)
{
  EmberStatus flashStatus = EMBER_ERR_FATAL;

  // The flash library requires the address and length to both
  // be multiples of 32 bits.
  assert((length & 3) == 0);

  // Taken from the mfg-token.c write
  //Remember, the flash library's token support operates in 16bit quantities,
  //but the token system operates in 8bit quantities.  Hence the divide by 2.
  //NOTE: The actual flash for the EFM32 device prefer to work with 32b writes,
  //but 16b is possible and supported by the flash driver - primarily for the
  //purposes of the SimEE/Token system that likes to use 8b and 16b.
  // THIS LENGTH IS A 32 BIT LENGTH
  flashStatus = halInternalFlashWrite((uint32_t)address, data, (uint32_t)(length / 2));
  assert(flashStatus == EMBER_SUCCESS);

  return flashStatus;
}
