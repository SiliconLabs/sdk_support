/***************************************************************************//**
 * @file
 * @brief Source file for RAIL HAL common functionality
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "hal_common.h"
#include "rail_types.h"

#include "em_common.h"
#include "em_cmu.h"

SL_WEAK void halInitChipSpecific(void)
{
  // Do nothing, but allow each chip to override this if necessary
}

void halInit(void)
{
  // Call the chip specific hal init
  halInitChipSpecific();
}

void halCommonMemMove(void *dest, const void *src, uint16_t bytes)
{
  uint8_t *d = (uint8_t *)dest;
  uint8_t *s = (uint8_t *)src;

  if (d > s) {
    d += bytes - 1;
    s += bytes - 1;
    #ifndef _HAL_SMALL_MEMUTILS_
    while (bytes >= 4) {
      bytes -= 4;
      *d-- = *s--;
      *d-- = *s--;
      *d-- = *s--;
      *d-- = *s--;
    }
    #endif // _HAL_SMALL_MEMUTILS_
    for (; bytes; bytes--) {
      *d-- = *s--;
    }
  } else {
    #ifndef _HAL_SMALL_MEMUTILS_
    while (bytes >= 4) {
      bytes -= 4;
      *d++ = *s++;
      *d++ = *s++;
      *d++ = *s++;
      *d++ = *s++;
    }
    #endif // _HAL_SMALL_MEMUTILS_
    for (; bytes; bytes--) {
      *d++ = *s++;
    }
  }
}
