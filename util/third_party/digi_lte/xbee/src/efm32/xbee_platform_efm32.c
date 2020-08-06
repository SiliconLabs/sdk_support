/***************************************************************************//**
 * # License
 * 
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 * 
 ******************************************************************************/

/*
 * Copyright (c) 2017 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */
/**
	@addtogroup hal_efm32
	@{
	@file xbee_platform_efm32.c
	Platform-specific functions for use by the
	XBee Driver on EFM32 uC platform.
	Documented in platform.h
*/
#include "xbee/platform_efm32.h"
#include "sl_sleeptimer.h"

// The current implementation is using sleeptimer

void xbee_platform_init(void)
{
  // The sleeptimer will be initialized elsewhere.
}

uint32_t xbee_seconds_timer()
{
  sl_sleeptimer_timestamp_t seconds;

  // Get time in unix format
  seconds = sl_sleeptimer_get_time();
  return seconds;
}

uint32_t xbee_millisecond_timer()
{
  uint32_t ticks;
  uint32_t ms;

  ticks = sl_sleeptimer_get_tick_count();
  ms = sl_sleeptimer_tick_to_ms(ticks);
  return ms;
}
