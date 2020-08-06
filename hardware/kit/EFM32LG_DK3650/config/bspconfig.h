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

#define BSP_DK
#define BSP_DK_BRD3201
#define BSP_MCUBOARD_USB
#define BSP_MCUBOARD_BRD3601

#define BSP_GPIO_INT_PORT       gpioPortE
#define BSP_GPIO_INT_PIN        0
#define BSP_USB_STATUSLED_PORT  gpioPortE
#define BSP_USB_STATUSLED_PIN   1
#define BSP_USB_OCFLAG_PORT     gpioPortE
#define BSP_USB_OCFLAG_PIN      2
#define BSP_USB_VBUSEN_PORT     gpioPortF
#define BSP_USB_VBUSEN_PIN      5

#define BSP_CONFIG_NORFLASH_EBI_BANK (EBI_BANK3)

#include "bsp_dk_bcreg_3201.h"

#define BSP_DK_LEDS
#define BSP_NO_OF_LEDS  16
#define BSP_LED_MASK    0xFFFF
#define BSP_LED_PORT    (&BC_REGISTER->UIF_LEDS)

#define BSP_INIT_DEFAULT  BSP_INIT_DK_EBI

#endif
