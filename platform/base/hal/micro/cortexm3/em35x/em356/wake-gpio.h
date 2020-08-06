/***************************************************************************//**
 * @file
 * @brief Condense WAKE_ON_P* macros into port-specific and monolithic macros.
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

#ifndef __WAKE_GPIO_H__
#define __WAKE_GPIO_H__

// create some handy macros for referring to whole ports
#define EMBER_WAKE_PORT_A                  \
  ((WAKE_ON_PA0 << _GPIO_P_IN_Px0_SHIFT)   \
   | (WAKE_ON_PA1 << _GPIO_P_IN_Px1_SHIFT) \
   | (WAKE_ON_PA2 << _GPIO_P_IN_Px2_SHIFT) \
   | (WAKE_ON_PA3 << _GPIO_P_IN_Px3_SHIFT) \
   | (WAKE_ON_PA4 << _GPIO_P_IN_Px4_SHIFT) \
   | (WAKE_ON_PA5 << _GPIO_P_IN_Px5_SHIFT) \
   | (WAKE_ON_PA7 << _GPIO_P_IN_Px7_SHIFT) \
  )

#define EMBER_WAKE_PORT_B                  \
  ((WAKE_ON_PB0 << _GPIO_P_IN_Px0_SHIFT)   \
   | (WAKE_ON_PB1 << _GPIO_P_IN_Px1_SHIFT) \
   | (WAKE_ON_PB2 << _GPIO_P_IN_Px2_SHIFT) \
   | (WAKE_ON_PB3 << _GPIO_P_IN_Px3_SHIFT) \
   | (WAKE_ON_PB4 << _GPIO_P_IN_Px4_SHIFT) \
  )

#define EMBER_WAKE_PORT_C                  \
  ((WAKE_ON_PC0 << _GPIO_P_IN_Px0_SHIFT)   \
   | (WAKE_ON_PC1 << _GPIO_P_IN_Px1_SHIFT) \
   | (WAKE_ON_PC2 << _GPIO_P_IN_Px2_SHIFT) \
   | (WAKE_ON_PC3 << _GPIO_P_IN_Px3_SHIFT) \
   | (WAKE_ON_PC4 << _GPIO_P_IN_Px4_SHIFT) \
   | (WAKE_ON_PC5 << _GPIO_P_IN_Px5_SHIFT) \
   | (WAKE_ON_PC6 << _GPIO_P_IN_Px6_SHIFT) \
   | (WAKE_ON_PC7 << _GPIO_P_IN_Px7_SHIFT) \
  )

// A monolithic constant for all GPIO wake sources
#define EMBER_WAKE_GPIO_BITMASK_ARRAY { \
    EMBER_WAKE_PORT_A,                  \
    EMBER_WAKE_PORT_B,                  \
    EMBER_WAKE_PORT_C,                  \
    0,                                  \
    0,                                  \
    0,                                  \
}

#endif // __WAKE_GPIO_H__
