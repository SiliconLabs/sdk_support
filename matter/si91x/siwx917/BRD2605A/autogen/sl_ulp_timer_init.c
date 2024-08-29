/***************************************************************************//**
 * @file sl_ulp_timer_init.c.jinja
 * @brief ULP timer Instance Initialization
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_si91x_ulp_timer.h"

#include "sl_si91x_ulp_timer_init_timer0_config.h"


#include "sl_ulp_timer_instances.h"



ulp_timer_config_t sl_timer_handle_timer0 = {
		.timer_num =              SL_ULP_TIMER_TIMER0,
		.timer_mode =             SL_ULP_TIMER_TIMER0_MODE,
		.timer_type =             SL_ULP_TIMER_TIMER0_TYPE,
		.timer_match_value =      SL_TIMER_MATCH_VALUE_DEFAULT,
		.timer_direction =        SL_ULP_TIMER_TIMER0_DIRECTION,
};



