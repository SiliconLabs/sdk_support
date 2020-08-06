/***************************************************************************//**
 * @file
 * @brief  Generic firmware source for Endian conversions.
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
#include "hal/micro/endian.h"

#if (!defined(EMBER_STACK_OWL_RX))
#include "stack/include/ember-types.h"
#endif /* EMBER_STACK_OWL_RX */

// Endian conversion APIs.
// Network byte order is big endian, so these APIs are only necessary on
//  platforms which have a natural little endian byte order.  On big-endian
//  platforms, the APIs are macro'd away to nothing

#ifndef NTOHS
// Network to Host Short
uint16_t NTOHS(uint16_t val)
{
  uint8_t *fldPtr;

  fldPtr = (uint8_t *)&val;
  return (HIGH_LOW_TO_INT(*fldPtr, *(fldPtr + 1)));
}

#endif

#ifndef NTOHL
// Network to Host Long
uint32_t NTOHL(uint32_t val)
{
  uint16_t *fldPtr;
  uint16_t field;
  uint16_t field2;

  fldPtr = (uint16_t *)&val;
  field = NTOHS(*fldPtr);
  field2 = NTOHS(*(fldPtr + 1));
  return ((uint32_t)field << 16) | ((uint32_t)field2);
}

#endif

/* Swap byte order, e.g. LE to BE or BE to LE.
 * This function is used when working with 802.15.4 frames on 8051 MCUs. */
uint32_t SwapEndiannessInt32u(uint32_t val)
{
  uint32_t ret;

  ((uint8_t*)&ret)[0] = ((uint8_t*)&val)[3];
  ((uint8_t*)&ret)[1] = ((uint8_t*)&val)[2];
  ((uint8_t*)&ret)[2] = ((uint8_t*)&val)[1];
  ((uint8_t*)&ret)[3] = ((uint8_t*)&val)[0];

  return ret;
}
