/***************************************************************************//**
 * @file
 * @brief Reset cause signalling for the Silicon Labs bootloader
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef BTL_RESET_H
#define BTL_RESET_H

#include "core/btl_util.h"

MISRAC_DISABLE
#include "em_common.h"
MISRAC_ENABLE

/***************************************************************************//**
 * @addtogroup Core Bootloader Core
 * @{
 * @addtogroup Reset
 * @brief Methods to reset from the bootloader to the app
 * @details
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Reset from the bootloader with a reset cause.
 *
 * @note This function does not return.
 *
 * @param resetReason A reset reason as defined in
 *                    [the bootloader interface](@ref ResetInterface)
 ******************************************************************************/
void reset_resetWithReason(uint16_t resetReason);

/***************************************************************************//**
 * Set a reset reason.
 *
 * @param resetReason A reset reason as defined in
 *                    [the bootloader interface](@ref ResetInterface)
 ******************************************************************************/
void reset_setResetReason(uint16_t resetReason);

/***************************************************************************//**
 * Get the reset reason without verifying it.
 *
 * @return The reset reason
 ******************************************************************************/
uint16_t reset_getResetReason(void);

/***************************************************************************//**
 * Invalidate the reset reason.
 ******************************************************************************/
void reset_invalidateResetReason(void);

/***************************************************************************//**
 * Classify reset and get the reset reason.
 *
 * @return Reset cause or @ref BOOTLOADER_RESET_REASON_UNKNOWN
 ******************************************************************************/
uint16_t reset_classifyReset(void);

/** @} addtogroup reset */
/** @} addtogroup core */

#endif // BTL_RESET_H
