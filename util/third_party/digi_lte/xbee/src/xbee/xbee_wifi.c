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
 * Copyright (c) 2008-2013 Digi International Inc.,
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
	@addtogroup xbee_wifi
	@{
	@file xbee_wifi.c
	Features related to the Wi-Fi XBee module (S6B).
*/

#include <stdio.h>

#include "xbee/wifi.h"

const char *xbee_wifi_encryption_name( uint8_t type)
{
	static char unknown[sizeof "0xXX"];

	switch (type)
	{
		case XBEE_WIFI_ENCRYPTION_OPEN:		return "open";
		case XBEE_WIFI_ENCRYPTION_WPA:		return "WPA";
		case XBEE_WIFI_ENCRYPTION_WPA2:		return "WPA2";
		case XBEE_WIFI_ENCRYPTION_WEP:		return "WEP";
	}

	sprintf( unknown, "0x%02X", type);
	return unknown;
}
