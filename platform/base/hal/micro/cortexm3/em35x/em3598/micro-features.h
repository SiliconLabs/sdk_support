/***************************************************************************//**
 * @file
 * @brief Constants to indicate which features the em3598 has available
 * THIS IS A GENERATED FILE. DO NOT EDIT.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __MICRO_FEATURES_H__
#define __MICRO_FEATURES_H__

#define CORTEXM3_EM35X_GEN4 1
#define CORTEXM3_EM359X 1

// Masks of which GPIO this chip has on which ports
#define EMBER_MICRO_PORT_A_GPIO 0xFF // 7 6 5 4 3 2 1 0
#define EMBER_MICRO_PORT_B_GPIO 0xFF // 7 6 5 4 3 2 1 0
#define EMBER_MICRO_PORT_C_GPIO 0xFF // 7 6 5 4 3 2 1 0
#define EMBER_MICRO_PORT_D_GPIO 0x1E //       4 3 2 1
#define EMBER_MICRO_PORT_E_GPIO 0x0F //         3 2 1 0

// Which physical serial ports are available
#define EMBER_MICRO_HAS_SC1 1
#define EMBER_MICRO_HAS_SC2 1
#define EMBER_MICRO_HAS_SC3 1
#define EMBER_MICRO_HAS_SC4 1
#define EMBER_MICRO_SERIAL_CONTROLLERS_MASK 0x0F

#define EMBER_MICRO_HAS_GPTIMERS 1

#define EMBER_MICRO_HAS_ADC 1

#ifndef NO_USB
  #define CORTEXM3_EM35X_USB 1
#endif // NO_USB

#endif // __MICRO_FEATURES_H__
