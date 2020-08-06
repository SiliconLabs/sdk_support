/***************************************************************************//**
 * @file
 * @brief HAL configuration legacy ember support header
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
#ifndef EMBER_HAL_CONFIG_H
#define EMBER_HAL_CONFIG_H
/* BUTTON */
// Support legacy BUTTONn parameter
  #ifdef BSP_BUTTON0_PIN
  #define BUTTON0 BSP_BUTTON0_PIN
  #endif
  #ifdef BSP_BUTTON1_PIN
  #define BUTTON1 BSP_BUTTON1_PIN
  #endif
  #ifdef BSP_BUTTON2_PIN
  #define BUTTON2 BSP_BUTTON2_PIN
  #endif
  #ifdef BSP_BUTTON3_PIN
  #define BUTTON3 BSP_BUTTON3_PIN
  #endif
  #ifdef BSP_BUTTON4_PIN
  #define BUTTON4 BSP_BUTTON4_PIN
  #endif
  #ifdef BSP_BUTTON5_PIN
  #define BUTTON5 BSP_BUTTON5_PIN
  #endif
  #ifdef BSP_BUTTON6_PIN
  #define BUTTON6 BSP_BUTTON6_PIN
  #endif
  #ifdef BSP_BUTTON7_PIN
  #define BUTTON7 BSP_BUTTON7_PIN
  #endif

/* SERIAL */
// Override legacy APP_SERIAL define with BSP_SERIAL_APP_PORT
  #ifdef BSP_SERIAL_APP_PORT
  #undef APP_SERIAL
  #define APP_SERIAL BSP_SERIAL_APP_PORT
  #else // support alternatively APP_SERIAL or BSP_SERIAL_APP_PORT
  #ifdef APP_SERIAL
    #define BSP_SERIAL_APP_PORT APP_SERIAL
  #endif
  #endif
  #define EMBER_AF_SERIAL_PORT_INIT() emberSerialInit(BSP_SERIAL_APP_PORT, HAL_SERIAL_APP_BAUD_RATE, PARITY_NONE, 1);
  #if defined(EMBER_ASSERT_SERIAL_PORT) && defined (BSP_SERIAL_ASSERT_PORT)
  #undef EMBER_ASSERT_SERIAL_PORT
  #endif
  #ifdef BSP_SERIAL_ASSERT_PORT
  #define EMBER_ASSERT_SERIAL_PORT BSP_SERIAL_ASSERT_PORT
  #endif

/* EXTDEV/EZRADIOPRO */
  #if HAL_EZRADIOPRO_ENABLE
    #define HAL_EXTDEV_ENABLE    1
    #ifndef HAL_EZRADIOPRO_FREQ
      #define HAL_EZRADIOPRO_FREQ 1000000
    #endif
    #define BSP_EXTDEV_CS_PIN    BSP_EZRADIOPRO_CS_PIN
    #define BSP_EXTDEV_CS_PORT   BSP_EZRADIOPRO_CS_PORT
    #define BSP_EXTDEV_INT_PIN   BSP_EZRADIOPRO_INT_PIN
    #define BSP_EXTDEV_INT_PORT  BSP_EZRADIOPRO_INT_PORT
    #define BSP_EXTDEV_SDN_PIN   BSP_EZRADIOPRO_SDN_PIN
    #define BSP_EXTDEV_SDN_PORT  BSP_EZRADIOPRO_SDN_PORT
  #endif //HAL_EZRADIOPRO_ENABLE

#endif //EMBER_HAL_CONFIG_H
