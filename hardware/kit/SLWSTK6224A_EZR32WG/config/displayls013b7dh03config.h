/***************************************************************************//**
 * @file
 * @brief EFM32ZG_STK3200 specific configuration for the display driver for
 *        the Sharp Memory LCD model LS013B7DH03.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_
#define __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_

#include "displayconfigapp.h"

/* Display device name. */
#define SHARP_MEMLCD_DEVICE_NAME   "Sharp LS013B7DH03 #1"

/* LCD and SPI GPIO pin connections on the EZR32LG. */
#define LCD_PORT_SCLK             (3)  /* = gpioPortD */
#define LCD_PIN_SCLK              (2)
#define LCD_PORT_SI               (3)  /* = gpioPortD */
#define LCD_PIN_SI                (0)
#define LCD_PORT_SCS              (0)  /* = gpioPortA */
#define LCD_PIN_SCS              (13)
#define LCD_PORT_EXTCOMIN         (5)  /* = gpioPortF */
#define LCD_PIN_EXTCOMIN          (4)
#define LCD_PORT_DISP_SEL         (0)  /* = gpioPortF */
#define LCD_PIN_DISP_SEL          (0)
#define LCD_PORT_DISP_PWR         (0)  /* = gpioPortA */
#define LCD_PIN_DISP_PWR         (14)

/*
 * Select how LCD polarity inversion should be handled:
 *
 * If POLARITY_INVERSION_EXTCOMIN is defined,
 * the polarity inversion is armed for every rising edge of the EXTCOMIN
 * pin. The actual polarity inversion is triggered at the next transision of
 * SCS. This mode is recommended because it causes less CPU and SPI load than
 * the alternative mode, see below.
 * If POLARITY_INVERSION_EXTCOMIN is undefined,
 * the polarity inversion is toggled by sending an SPI command. This mode
 * causes more CPU and SPI load than using the EXTCOMIN pin mode.
 */
#define POLARITY_INVERSION_EXTCOMIN

/* Define POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE if you want the PAL
 * (Platform Abstraction Layer interface) to automatically toggle the EXTCOMIN
 *  pin.
 * If the PAL_TIMER_REPEAT function is defined the EXTCOMIN toggling is handled
 * by a timer repeat system, therefore we must undefine
 * POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE;
 */
#ifndef PAL_TIMER_REPEAT_FUNCTION
  #define POLARITY_INVERSION_EXTCOMIN_PAL_AUTO_TOGGLE
#endif

/* Frequency of LCD polarity inversion. */
#define LS013B7DH03_POLARITY_INVERSION_FREQUENCY (64)

#endif /* __SILICON_LABS_DISPLAY_LS013B7DH03_CONFIG_H_ */
