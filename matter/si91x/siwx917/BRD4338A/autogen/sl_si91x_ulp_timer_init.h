/***************************************************************************/
/**
 * @file sl_si91x_ulp_timer_init.h
 * @brief ULP Timer Instances
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_SI91X_ULP_TIMER_INIT_H_
#define SL_SI91X_ULP_TIMER_INIT_H_

#include "sl_si91x_ulp_timer.h"
// Include instance config 
 
#include "sl_si91x_ulp_timer_timer0_config.h"

#if defined(SL_ULP_TIMER_TIMER0) // To verify UC inputs existance
ulp_timer_config_t sl_timer_handle_timer0 = {
		.timer_num =              SL_ULP_TIMER_TIMER0,
		.timer_mode =             SL_ULP_TIMER_MODE,
		.timer_type =             SL_ULP_TIMER_TYP,
		.timer_match_value =      SL_TIMER_MATCH_VALUE_DEFAULT,
		.timer_direction =        SL_ULP_TIMER_DIRECTION,
};
#endif // SL_ULP_TIMER_INSTANCE

#if defined(SL_ULP_TIMER_CLK_TYPE) // To verify UC inputs existence
ulp_timer_clk_src_config_t sl_timer_clk_handle = {
		.ulp_timer_clk_type =             SL_ULP_TIMER_CLK_TYPE,
		.ulp_timer_sync_to_ulpss_pclk =   SL_ULP_TIMER_SYNC_TO_ULPSS_PCLK,
		.ulp_timer_clk_input_src =        SL_ULP_TIMER_CLK_INPUT_SOURCE,
		.ulp_timer_skip_switch_time =     SL_ULP_TIMER_SKIP_SWITCH_TIME,
};
#endif // SL_ULP_TIMER_CLK_TYPE

#endif // SL_SI91X_ULP_TIMER_INIT_H_
