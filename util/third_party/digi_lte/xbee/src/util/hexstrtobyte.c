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
	@addtogroup util
	@{
	@file util/hexstrtobyte.c

	ANSI C hexstrtobyte() implementation if not available natively on a given
	platform.  Used in sample programs to convert a hex string to an array
	of byte values.
*/

#include "xbee/platform.h"

// See xbee/platform.h for function documentation.
int hexstrtobyte (const char *p)
{
	uint_fast8_t b = 0;
	char ch;
	int_fast8_t i;

	for (i = 2; i; --i)
	{
		b <<= 4;
		ch = *p++;
		if ('0' <= ch && ch <= '9')
		{
			b += ch - '0';
		}
		else if ('a' <= ch && ch <= 'f')
		{
			b += ch - ('a' - 10);
		}
		else if ('A' <= ch && ch <= 'F')
		{
			b += ch - ('A' - 10);
		}
		else
		{
			return -1;
		}
	}

	return b;
}
