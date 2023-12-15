/***************************************************************************/ /**
 * @file RTE_led_config.h
 * @brief Led Driver Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************/

#ifndef SL_SI91X_LED_CONFIG_H
#define SL_SI91X_LED_CONFIG_H

#include "RTE_Device_917.h"

#define SL_SI91x_LED_COUNT 2

#define SL_LED_LED0_PIN    RTE_LED0_PIN
#define SL_LED_LED0_PORT   RTE_LED0_PORT
#define SL_LED_LED0_NUMBER RTE_LED0_NUMBER

#define SL_LED_LED1_PIN    RTE_LED1_PIN
#define SL_LED_LED1_PORT   RTE_LED1_PORT
#define SL_LED_LED1_NUMBER RTE_LED1_NUMBER
#define SL_LED_LED1_PAD    RTE_LED1_PAD

#endif // SL_SI91X_LED_CONFIG_H
