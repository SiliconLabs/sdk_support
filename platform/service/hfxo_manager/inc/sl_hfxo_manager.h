/***************************************************************************//**
 * @file
 * @brief HFXO Manager API definition.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

/***************************************************************************//**
 * @addtogroup hfxo_manager HFXO Manager
 * @{
 ******************************************************************************/

#ifndef SL_HFXO_MANAGER_H
#define SL_HFXO_MANAGER_H

#include "sl_status.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Sleepy Crystal settings
typedef struct sl_hfxo_manager_sleepy_xtal_settings {
  uint32_t ana_ctune;         ///<Tuning Capacitance values for XI and XO during startup intermediate and steady stages
  uint32_t core_bias_current; ///< Core Bias current value during all stages
} sl_hfxo_manager_sleepy_xtal_settings_t;

/***************************************************************************//**
 * HFXO Manager module hardware specific initialization.
 ******************************************************************************/
void sl_hfxo_manager_init_hardware(void);

/***************************************************************************//**
 * Initialize HFXO Manager module.
 *
 * @return Status Code.
 ******************************************************************************/
sl_status_t sl_hfxo_manager_init(void);

/***************************************************************************//**
 * Updates Sleepy Crystal settings.
 *
 * @param  settings  Pointer to settings structure
 *
 * @return Status Code.
 *
 * @note Those settings are temporarily used to force oscillation on sleepy
 *       crystal.
 *       Default values should be enough to wake-up sleepy crystals. Otherwise,
 *       this function can be used.
 ******************************************************************************/
sl_status_t sl_hfxo_manager_update_sleepy_xtal_settings(sl_hfxo_manager_sleepy_xtal_settings_t *settings);

/***************************************************************************//**
 * When this callback function is called, it means that HFXO failed twice in
 * a row to start with normal configurations. This may mean that there is a
 * bad crystal. When getting this callback, HFXO is running but its properties
 * (frequency, precision) are not guaranteed. This should be considered as an
 * error situation.
 ******************************************************************************/
void sl_hfxo_manager_notify_consecutive_failed_startups(void);

/***************************************************************************//**
 * HFXO Manager HFXO interrupt handler.
 *
 * @note  This function must be called by the HFXO interrupt handler in order
 *        to support the HFXO Manager module.
 *        This function handles the HFXO_IF_RDY, HFXO_IF_DNSERR and
 *        HFXO_XTALCTRL_SKIPCOREBIASOPT interrupt flags.
 ******************************************************************************/
void sl_hfxo_manager_irq_handler(void);

/** @} (end addtogroup hfxo_manager) */

#ifdef __cplusplus
}
#endif

#endif // SL_HFXO_MANAGER_H
