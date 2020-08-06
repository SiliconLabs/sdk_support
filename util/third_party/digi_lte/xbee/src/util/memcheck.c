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
 * Copyright (c) 2008-2012 Digi International Inc.,
 * All rights not expressly granted are reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Digi International Inc. 11001 Bren Road East, Minnetonka, MN 55343
 * =======================================================================
 */

/*** BeginHeader */
#include <stddef.h>
#include "xbee/platform.h"
/*** EndHeader */

/*** BeginHeader memcheck */
/*** EndHeader */
// documented in xbee/platform.h
int memcheck( const void FAR *src, int ch, size_t length)
{
	const uint8_t FAR *s;
	uint8_t c = (ch & 0xFF);

	for (s = src; length--; ++s)
	{
		if (*s != c)
		{
			return (*s > c) ? 1 : -1;
		}
	}

	return 0;
}

