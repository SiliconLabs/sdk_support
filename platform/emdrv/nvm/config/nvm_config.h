/***************************************************************************//**
 * @file
 * @brief NVM driver configuration
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
#ifndef __NVMCONFIG_H
#define __NVMCONFIG_H

#include <stdint.h>
#include <stdbool.h>
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
 ****************************   CONFIGURATION   ********************************
 ******************************************************************************/

/** Without this define the wear pages are no longer supported */
#define NVM_FEATURE_WEAR_PAGES_ENABLED               true

/** Include and activate the static wear leveling functionality */
#define NVM_FEATURE_STATIC_WEAR_ENABLED              true

/** The threshold used to decide when to do static wear leveling */
#define NVM_STATIC_WEAR_THRESHOLD                    100

/** Validate data against checksums on every read operation */
#define NVM_FEATURE_READ_VALIDATION_ENABLED          true

/** Validate data against checksums after every write operation */
#define NVM_FEATURE_WRITE_VALIDATION_ENABLED         true

/** Include the NVM_WearLevelGet function. */
#define NVM_FEATURE_WEARLEVELGET_ENABLED             true

/** Check if data has been updated before writing update to the NVM */
#define NVM_FEATURE_WRITE_NECESSARY_CHECK_ENABLED    true

/** define maximum number of flash pages that can be used as NVM */
#define NVM_MAX_NUMBER_OF_PAGES                      32

/** Configure extra pages to allocate for data security and wear leveling.
    Minimum 1, but the more you add the better lifetime your system will have. */
#define NVM_PAGES_SCRATCH                            1

/** Set the NVM driver page size to the size of the flash. */
#define NVM_PAGE_SIZE                                FLASH_PAGE_SIZE

/*******************************************************************************
 ******************************   TYPEDEFS   ***********************************
 ******************************************************************************/

/** Enum describing the type of logical page we have; normal or wear. */
typedef enum {
  nvmPageTypeNormal = 0, /**< Normal page, always rewrite. */
  nvmPageTypeWear   = 1  /**< Wear page. Can be used several times before rewrite. */
} NVM_Page_Type_t;

/** Describes the properties of an object in a page. */
typedef struct {
  uint8_t  *location;  /**< A pointer to the location of the object in RAM. */
  uint16_t size;       /**< The size of the object in bytes. */
  uint8_t  objectId;   /**< An object ID used to reference the object. Must be unique in the page. */
} NVM_Object_Descriptor_t;

/** A collection of object descriptors that make up a page. */
typedef NVM_Object_Descriptor_t   NVM_Page_t[];

/** Describes the properties of a page. */
typedef struct {
  uint8_t           pageId;    /**< A page ID used when referring to the page. Must be unique. */
  NVM_Page_t const *page;      /**< A pointer to the list of all the objects in the page. */
  uint8_t           pageType;  /**< The type of page, normal or wear. */
} NVM_Page_Descriptor_t;

/** The list of pages registered for use. */
typedef NVM_Page_Descriptor_t   NVM_Page_Table_t[];

/** Configuration structure. */
typedef struct
{ NVM_Page_Table_t const *nvmPages;  /**< Pointer to table defining NVM pages. */
  uint8_t          const pages;      /**< Total number of physical pages. */
  uint8_t          const userPages;  /**< Number of defined (used) pages. */
  uint8_t          const *nvmArea;   /**< Pointer to nvm area in flash. */
} NVM_Config_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

NVM_Config_t const *NVM_ConfigGet(void);

/** @} (end addtogroup NVM) */
/** @} (end addtogroup emdrv) */

#ifdef __cplusplus
}
#endif

#endif /* __NVMCONFIG_H */
