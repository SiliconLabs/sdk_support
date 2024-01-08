/*****************************************************************************
                                                                               * @file sl_si91x_m4_ps.h
                                                                               * @brief  M4 power save
                                                                               *******************************************************************************
                                                                               * # License
                                                                               * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
                                                                               *******************************************************************************
                                                                               *
                                                                               * The licenser of this software is Silicon Laboratories Inc. Your use of this
                                                                               * software is governed by the terms of Silicon Labs Master Software License
                                                                               * Agreement (MSLA) available at
                                                                               * www.silabs.com/about-us/legal/master-software-license-agreement. This
                                                                               * software is distributed to you in Source Code format and is governed by the
                                                                               * sections of the MSLA applicable to Source Code.
                                                                               *
                                                                               ******************************************************************************/

#ifndef SL_SI91X_M4_POWERSAVE_H_
#define SL_SI91X_M4_POWERSAVE_H_

#ifdef DEBUG_UART
#include "rsi_debug.h"
#endif
#ifdef SLI_SI91X_MCU_INTERFACE
#include "rsi_ds_timer.h"
#include "rsi_m4.h"
#include "rsi_rom_power_save.h"
#include "rsi_rom_timer.h"
#include "rsi_rom_ulpss_clk.h"
#include "rsi_rtc.h"
#include "rsi_wisemcu_hardware_setup.h"
#include "sl_event_handler.h"

/*=======================================================================*/
//! Power save command parameters
/*=======================================================================*/
//! set handshake type of power mode
#define RSI_HAND_SHAKE_TYPE M4_BASED
#define WIRELESS_WAKEUP_IRQ_PRI 8
#define portNVIC_SHPR3_REG (*((volatile uint32_t *)0xe000ed20))
#define portNVIC_PENDSV_PRI (((uint32_t)(0x3f << 4)) << 16UL)
#define portNVIC_SYSTICK_PRI (((uint32_t)(0x3f << 4)) << 24UL)

// -----------------------------------------------------------------------------
// Prototypes
/**
 * @fn         sl_si91x_m4_sleep_wakeup
 * @brief      Keeps the M4 In the Sleep
 * @param[in]  none
 * @return    none.
 * @section description
 * This function is used to trigger sleep in the M4 and in the case of the
 * retention submitting the buffer valid to the TA for the rx packets.
 */
void sl_si91x_m4_sleep_wakeup(void);

/**
 * @fn           initialize_m4_alarm.
 * @brief        This function is to initialize Alarm block .
 * @param[in]  none
 * @return    none.
 */
void initialize_m4_alarm(void);
void IRQ026_Handler();

void wakeup_source_config(void);
#endif /* SLI_SI91X_MCU_INTERFACE */
#endif /* SL_SI91X_M4_POWERSAVE_H_ */
