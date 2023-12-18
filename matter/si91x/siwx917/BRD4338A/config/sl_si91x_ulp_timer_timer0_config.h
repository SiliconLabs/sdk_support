/***************************************************************************/
/**
 * @file sl_si91x_ulp_timer_inst_config.h
 * @brief ULP Timer configuration file.
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

#ifndef SL_SI91X_ULP_TIMER_TIMER0_CONFIG_H
#define SL_SI91X_ULP_TIMER_TIMER0_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Clock Configuration
#define SL_ULP_TIMER_CLK_TYPE_STATIC 1
#define SL_ULP_TIMER_CLK_TYPE_DYNAMIC 0

// <o SL_ULP_TIMER_CLK_TYPE> Clock Type
//   <SL_ULP_TIMER_CLK_TYPE_STATIC=> Static (auto select)
//   <SL_ULP_TIMER_CLK_TYPE_DYNAMIC=> Dynamic
// <i> Selection of the Timer CLK Type.
#define SL_ULP_TIMER_CLK_TYPE SL_ULP_TIMER_CLK_TYPE_STATIC

// <q SL_ULP_TIMER_SYNC_TO_ULPSS_PCLK> Sync to ULPSS PCLK
// <i> Enable or disable sync to ULPSS pclock.
// <i> Default: 0
#define SL_ULP_TIMER_SYNC_TO_ULPSS_PCLK 0

// <q SL_ULP_TIMER_SKIP_SWITCH_TIME> Wait for switching timer clock
// <i> 1 : Enable waiting for switching timer clk & 0 : Skip waiting for
// switching timer clk. <i> Default: 0
#define SL_ULP_TIMER_SKIP_SWITCH_TIME 0

#define SL_ULP_TIMER_REF_CLK 0
#define SL_ULP_TIMER_32KHZ_RO_CLK 1
#define SL_ULP_TIMER_32KHZ_RC_CLK 2
#define SL_ULP_TIMER_32KHZ_XTAL_CLK 3
#define SL_ULP_TIMER_32MHZ_RC_CLK 4
#define SL_ULP_TIMER_20MHZ_RO_CLK 5
#define SL_ULP_TIMER_ULP_SOC_CLK 6

// <o SL_ULP_TIMER_CLK_INPUT_SOURCE> clock source
//   <SL_ULP_TIMER_REF_CLK=> Ref clock
//   <SL_ULP_TIMER_32KHZ_RO_CLK=> 32KHZ_RO
//   <SL_ULP_TIMER_32KHZ_RC_CLK=> 32KHZ_RC
//   <SL_ULP_TIMER_32KHZ_XTAL_CLK=> 32KHZ_XTAL
//   <SL_ULP_TIMER_32MHZ_RC_CLK=> 32MHZ_RC (auto select)
//   <SL_ULP_TIMER_20MHZ_RO_CLK=> 20MHZ_RO
//   <SL_ULP_TIMER_ULP_SOC_CLK=> SOC_CLK
// <i> Selection of the Clock source
#define SL_ULP_TIMER_CLK_INPUT_SOURCE                                          \
  SL_ULP_TIMER_32MHZ_RC_CLK // default timer clock input source is ref clock

// </h>

// <h>ULP Timer Configuration

#define SL_ULP_TIMER_TIMER0 0
#define SL_ULP_TIMER_TIMER1 1
#define SL_ULP_TIMER_TIMER2 2
#define SL_ULP_TIMER_TIMER3 3

// <o SL_ULP_TIMER_DEFAULT> Timer instance
//   <SL_ULP_TIMER_TIMER0=> Timer 0
//   <SL_ULP_TIMER_TIMER1=> Timer 1
//   <SL_ULP_TIMER_TIMER2=> Timer 2
//   <SL_ULP_TIMER_TIMER3=> Timer 3
// <i> Selection of the Timer instance
#define SL_ULP_TIMER_DEFAULT SL_ULP_TIMER_TIMER0

#define SL_ULP_TIMER_TYP_DOWN_COUNTER 0
#define SL_ULP_TIMER_TYP_1US 1
#define SL_ULP_TIMER_TYP_256US 2

// <o SL_ULP_TIMER_TYP> Timer type
//   <SL_ULP_TIMER_TYP_DOWN_COUNTER=> Down Counter (auto select)
//   <SL_ULP_TIMER_TYP_1US=> 1 Micro-Sec
//   <SL_ULP_TIMER_TYP_256US=> 256-Micro-Sec
// <i> Selection of the Timer type
#define SL_ULP_TIMER_TYP SL_ULP_TIMER_TYP_DOWN_COUNTER // default type is 1MS

#define SL_ULP_TIMER_MODE_ONESHOT 0
#define SL_ULP_TIMER_MODE_PERIODIC 1

// <o SL_ULP_TIMER_MODE> Timer mode
//   <SL_ULP_TIMER_MODE_ONESHOT=> One-shot
//   <SL_ULP_TIMER_MODE_PERIODIC=> Periodic (auto select)
// <i> Selection of the Timer mode
#define SL_ULP_TIMER_MODE SL_ULP_TIMER_MODE_PERIODIC // default mode is periodic

#define SL_ULP_DOWN_COUNTER 0
#define SL_ULP_UP_COUNTER 1
// <o SL_ULP_TIMER_DIRECTION> Timer direction
//   <SL_ULP_DOWN_COUNTER=> Down (auto select)
//   <SL_ULP_UP_COUNTER=> Up
// <i> Selection of the Timer direction
#define SL_ULP_TIMER_DIRECTION SL_ULP_DOWN_COUNTER

// </h>

// <<< end of configuration section >>>

#endif /* SL_SI91X_ULP_TIMER_TIMER0_CONFIG_H */
