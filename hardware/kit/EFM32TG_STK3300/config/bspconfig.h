/***************************************************************************//**
 * @file
 * @brief Provide BSP (board support package) configuration parameters.
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

#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H

#define BSP_STK
#define BSP_STK_BRD2100

#define BSP_BCC_USART       USART1
#define BSP_BCC_CLK         cmuClock_USART1
#define BSP_BCC_LOCATION    USART_ROUTE_LOCATION_LOC2
#define BSP_BCC_TXPORT      gpioPortD
#define BSP_BCC_TXPIN       7
#define BSP_BCC_RXPORT      gpioPortD
#define BSP_BCC_RXPIN       6
#define BSP_BCC_ENABLE_PORT gpioPortC
#define BSP_BCC_ENABLE_PIN  14

#define BSP_GPIO_LEDS
#define BSP_NO_OF_LEDS          1
#define BSP_GPIO_LED0_PORT      gpioPortD
#define BSP_GPIO_LED0_PIN       7
#define BSP_GPIO_LEDARRAY_INIT { { BSP_GPIO_LED0_PORT, BSP_GPIO_LED0_PIN } }

#define BSP_GPIO_BUTTONS
#define BSP_NO_OF_BUTTONS       2
#define BSP_GPIO_PB0_PORT       gpioPortD
#define BSP_GPIO_PB0_PIN        8
#define BSP_GPIO_PB1_PORT       gpioPortB
#define BSP_GPIO_PB1_PIN        11

#define BSP_GPIO_BUTTONARRAY_INIT { { BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN }, { BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN } }

#define BSP_INIT_DEFAULT  0

#define BSP_BCP_VERSION 1
#include "bsp_bcp.h"

#endif
