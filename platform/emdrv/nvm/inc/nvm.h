/***************************************************************************//**
 * @file
 * @brief Non-Volatile Memory Wear-Leveling driver API
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

#ifndef __NVM_H
#define __NVM_H

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "nvm_hal.h"
#include "nvm_config.h"
#include "ecode.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup emdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup NVM
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** Return/error codes */
#define ECODE_EMDRV_NVM_OK                      (ECODE_OK)                                   ///< Success return value
#define ECODE_EMDRV_NVM_ADDR_INVALID            (ECODE_EMDRV_NVM_BASE | 0x00000001)          ///< Invalid address
#define ECODE_EMDRV_NVM_ALIGNMENT_INVALID       (ECODE_EMDRV_NVM_BASE | 0x00000002)          ///< Invalid data alignment
#define ECODE_EMDRV_NVM_DATA_INVALID            (ECODE_EMDRV_NVM_BASE | 0x00000003)          ///< Invalid input data or format
#define ECODE_EMDRV_NVM_WRITE_LOCK              (ECODE_EMDRV_NVM_BASE | 0x00000004)          ///< A write is currently in progress
#define ECODE_EMDRV_NVM_NO_PAGES_AVAILABLE      (ECODE_EMDRV_NVM_BASE | 0x00000005)          ///< Initialization didn't find any pages available to allocate
#define ECODE_EMDRV_NVM_PAGE_INVALID            (ECODE_EMDRV_NVM_BASE | 0x00000006)          ///< Could not find the page specified
#define ECODE_EMDRV_NVM_ERROR                   (ECODE_EMDRV_NVM_BASE | 0x00000007)          ///< General error

/** All objects are written from RAM. */
#define NVM_WRITE_ALL_CMD         0xff
/** All objects are copied from the old page. */
#define NVM_WRITE_NONE_CMD        0xfe
/** All objects are read to RAM. */
#define NVM_READ_ALL_CMD          0xff

/** Retains the registered erase count when eraseing a page. */
#define NVM_ERASE_RETAINCOUNT    0xffffffffUL

/** Structure defining end of pages table. */
#define NVM_PAGE_TERMINATION    { NULL, 0, (NVM_Object_Ids) 0 }

/*******************************************************************************
 ***************************   PROTOTYPES   ************************************
 ******************************************************************************/

Ecode_t NVM_Init(NVM_Config_t const *nvmConfig);
Ecode_t NVM_Erase(uint32_t eraseCount);
Ecode_t NVM_Write(uint16_t pageId, uint8_t objectId);
Ecode_t NVM_Read(uint16_t pageId, uint8_t objectId);

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#ifndef NVM_FEATURE_WEARLEVELGET_ENABLED
#define NVM_FEATURE_WEARLEVELGET_ENABLED    true
#endif
/** @endcond */
#if (NVM_FEATURE_WEARLEVELGET_ENABLED)
uint32_t NVM_WearLevelGet(void);
#endif

/** @} (end defgroup NVM) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* __NVM_H */
