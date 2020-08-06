/***************************************************************************//**
 * @file
 * @brief TEMPDRV configuration file.
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
#ifndef __SILICON_LABS_TEMPDRV_CONFIG_H__
#define __SILICON_LABS_TEMPDRV_CONFIG_H__

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup TEMPDRV
 * @{
 ******************************************************************************/

// Callback table depth (for high and low callbacks each)
#ifndef TEMPDRV_CUSTOM_CALLBACK_DEPTH
#define TEMPDRV_CUSTOM_CALLBACK_DEPTH 5
#endif

// Allow temperature sensor to wake the device up from EM4
#ifndef TEMPDRV_EM4WAKEUP
#define TEMPDRV_EM4WAKEUP false
#endif

// Allow TEMPDRV to define the EMU_IRQ_Handler. Enable if EMU_IRQ_Handler is
// defined elsewhere.
#ifndef EMU_CUSTOM_IRQ_HANDLER
#define EMU_CUSTOM_IRQ_HANDLER false
#endif

/** @} (end addtogroup TEMPDRV) */
/** @} (end addtogroup emdrv) */

#endif /* __SILICON_LABS_TEMPDRV_CONFIG_H__ */
