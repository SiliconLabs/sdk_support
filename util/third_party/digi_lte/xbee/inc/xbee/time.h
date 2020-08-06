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
 * Copyright (c) 2010-2012 Digi International Inc.,
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
	@addtogroup xbee_time
	@{
	@file xbee/time.h

	Header for portable time functions using January 1, 2000 a the epoch.
*/

#ifndef __XBEE_TIME_H
#define __XBEE_TIME_H

#include <time.h>
#include "xbee/platform.h"

XBEE_BEGIN_DECLS

typedef uint32_t xbee_utctime_t;
#define XBEE_UTCTIME_INVALID		0xFFFFFFFF

// Convert a 1/1/2000-based timestamp into a struct tm which can be used with
// the Standard C Library's <time.h>.
struct tm *xbee_gmtime( struct tm *tm, xbee_utctime_t timestamp);

// Convert a struct tm to a 1/1/2000-based timestamp.
xbee_utctime_t xbee_mktime( struct tm *time_rec);

XBEE_END_DECLS

// If compiling in Dynamic C, automatically #use the appropriate C file.
#ifdef __DC__
	#use "xbee_time.c"
#endif

#endif	// __XBEE_TIME_H defined
