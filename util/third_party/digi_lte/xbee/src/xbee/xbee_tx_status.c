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
 * Copyright (c) 2009-2013 Digi International Inc.,
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
	@addtogroup xbee_tx_status
	@{
	@file xbee_tx_status.c
	Code for handling tx_status frames (not transmit frames).
*/
#include <stddef.h>
#include <stdio.h>

#include "xbee/platform.h"
#include "xbee/device.h"
#include "xbee/tx_status.h"

int xbee_frame_dump_tx_status( xbee_dev_t *xbee,
	const void FAR *frame, uint16_t length, void FAR *context)
{
	XBEE_UNUSED_PARAMETER( xbee);
	XBEE_UNUSED_PARAMETER( length);
	XBEE_UNUSED_PARAMETER( context);
	
	const xbee_frame_tx_status_t FAR* status_frame = frame;
	
	printf("%s: id: 0x%02x \t status: 0x%x\n", __FUNCTION__, status_frame->frame_id,
		status_frame->delivery);
	
	return 0;	
}
//TODO everything