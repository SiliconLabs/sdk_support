/***************************************************************************//**
 * @file sl_ulp_timer_instances.h.jinja
 * @brief ULP Timer Instance
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ULP_TIMER_INSTANCES_H
#define SL_ULP_TIMER_INSTANCES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_si91x_ulp_timer.h"
#define SL_ULP_TIMER_TIMER0 0
#define SL_ULP_TIMER_TIMER1 1
#define SL_ULP_TIMER_TIMER2 2
#define SL_ULP_TIMER_TIMER3 3


extern ulp_timer_config_t sl_timer_handle_timer0 ;



#ifdef __cplusplus
}
#endif

#endif // SL_ULP_TIMER_INSTANCES_H
