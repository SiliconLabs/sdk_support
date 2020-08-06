/***************************************************************************//**
 * @file
 * @brief NVM3 system for wear leveling token storage across flash.
 * See @ref nvm3 for documentation.
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
#ifndef __NVM3_TOKEN_H__
#define __NVM3_TOKEN_H__

#include "nvm3.h"

/** @addtogroup nvm3
 * The NVM3 system is designed to operate under the @ref tokens API and provide
 * a non-volatile storage system.  Since the flash write cycles
 * are finite, the NVM3's primary purpose is to perform wear
 * leveling across several hardware flash pages, ultimately increasing the
 * number of times tokens may be written before a hardware failure.
 *
 * See platform/emdrv/nvm3/inc/nvm3.h for source code.
 *@{
 */

//application functions

/** @brief The NVM3 callback function, implemented by the
 * application.
 *
 * @param status  An ::Ecode_t error code indicating one of the conditions
 * described in nvm3.h
 *
 * This callback will report any Ecode_t error codes passed back from the NVM3
 * API functions when they are called through the token API.
 *
 */
void halNvm3Callback(Ecode_t status);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// These interfaces serve only as a glue layer
// to link NVM3 keys to tokens (primarily for *test code)
  #define INVALID_EE_ADDRESS 0xFFFF
uint16_t getNvm3TokenAddress(uint32_t nvm3Key);
uint8_t getNvm3TokenSize(uint32_t nvm3Key);
uint8_t getNvm3TokenArraySize(uint32_t nvm3Key);

#endif //DOXYGEN_SHOULD_SKIP_THIS

#endif //__NVM3_TOKEN_H__

/**@} END nvm3 group
 */
