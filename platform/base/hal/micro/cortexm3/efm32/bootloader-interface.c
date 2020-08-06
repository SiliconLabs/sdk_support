/***************************************************************************//**
 * @file
 * @brief EFR32 common bootloader HAL functions
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
#include PLATFORM_HEADER
#if defined(CONFIGURATION_HEADER)
  #include CONFIGURATION_HEADER
#endif
#include "stack/include/ember-types.h"
#include "hal/micro/bootloader-interface.h"
#include "hal/micro/cortexm3/memmap.h"
#include "hal/micro/cortexm3/common/bootloader-common.h"
#include "api/btl_interface.h"  // for ApplicationProperties_t and other
// Gecko bootloader related definitions.

//////////////////////
// Generic bootloader functionality
///////////

#ifdef EMBER_AF_PLUGIN_DOTDOT_MFG_CERTS

// The long token section is expected to be an integer number of flash pages
// so that there's no chance erasure of adjacent sections will disturb its
// data. We first calculate a default size if one was not provided and then
// verify that expectation.
  #if !defined(LONG_TOKEN_DEFAULT_SIZE)
    #if FLASH_PAGE_SIZE == 2048U
      #define LONG_TOKEN_DEFAULT_SIZE (2 * FLASH_PAGE_SIZE)
    #elif FLASH_PAGE_SIZE == 8192U
      #define LONG_TOKEN_DEFAULT_SIZE (FLASH_PAGE_SIZE)
    #else
      #error "Unsupported FLASH_PAGE_SIZE."
    #endif
  #endif

  #if (LONG_TOKEN_DEFAULT_SIZE % FLASH_PAGE_SIZE) != 0U
    #error "Long token section size must be a multiple of FLASH_PAGE_SIZE."
  #endif

  #ifndef LONG_TOKEN_BASE

// IAR
    #if defined (__ICCARM__)

      #ifndef __LONGTOKEN__
        #define __LONGTOKEN__ "LONGTOKEN"
      #endif

__root uint8_t longTokenStorage[LONG_TOKEN_DEFAULT_SIZE] @ __LONGTOKEN__;
      #define LONG_TOKEN_BASE (longTokenStorage)

// GCC
    #elif defined (__GNUC__)

      #ifndef __LONGTOKEN__
        #define __LONGTOKEN__ ".longtoken"
      #endif

__attribute__((used)) uint8_t longTokenStorage[LONG_TOKEN_DEFAULT_SIZE] __attribute__ ((section(__LONGTOKEN__)));
// If the linker doesn't provide __longTokenBase symbol, then use longTokenStorage
extern char __longTokenBase __attribute__((alias("longTokenStorage")));
      #define LONG_TOKEN_BASE (&__longTokenBase)

    #else
      #error "Unsupported toolchain"
    #endif // __ICCARM__

  #endif // LONG_TOKEN_BASE
uint8_t *longTokenAddress = (uint8_t *)LONG_TOKEN_BASE;
#else
  #define LONG_TOKEN_BASE NULL
#endif // EMBER_AF_PLUGIN_DOTDOT_MFG_CERTS

NO_STRIPPING const ApplicationProperties_t appProperties = {
  .magic = APPLICATION_PROPERTIES_MAGIC,
  .structVersion = APPLICATION_PROPERTIES_VERSION,
  .signatureType = APPLICATION_SIGNATURE_NONE,
  .signatureLocation = 0xFFFFFFFFU,
  .app = {
#if defined(EMBER_STACK_CONNECT)
    .type = APPLICATION_TYPE_FLEX,
#elif defined(EMBER_STACK_IP)
    .type = APPLICATION_TYPE_THREAD,
#else
    .type = APPLICATION_TYPE_ZIGBEE,
#endif
    .version = CUSTOMER_APPLICATION_VERSION,
    .capabilities = APPLICATION_PROPERTIES_CAPABILITIES,
    .productId = CUSTOMER_APPLICATION_PRODUCT_ID
  },
  .longTokenSectionAddress = (uint8_t *)LONG_TOKEN_BASE,
};

#if defined GECKO_INFO_PAGE_BTL      \
  || defined APP_GECKO_INFO_PAGE_BTL \
  || defined STA_GECKO_INFO_PAGE_BTL \
  || defined LOCAL_STORAGE_GECKO_INFO_PAGE_BTL
#define NO_BAT

static bool bootloaderIsCommonBootloader(void)
{
  return true;
}

#else

static bool bootloaderIsCommonBootloader(void)
{
  if (halBootloaderAddressTable.baseTable.type == BOOTLOADER_ADDRESS_TABLE_TYPE) {
    return false;
  } else {
    return true;
  }
}

#endif

/** @description Returns the bootloader type the application was
 *  built for.
 *
 * @return BL_TYPE_NULL, BL_TYPE_STANDALONE or BL_TYPE_APPLICATION
 */
BlBaseType halBootloaderGetType(void)
{
  // Important distinction:
  //   this returns what bootloader the app was built for
  #ifdef NULL_BTL
  BLDEBUG_PRINT("built for NULL bootloader\r\n");
  return BL_TYPE_NULL;
  #elif defined APP_BTL
  // Deprecated
  BLDEBUG_PRINT("built for APP bootloader\r\n");
  return BL_TYPE_APPLICATION;
  #elif defined SERIAL_UART_BTL
  // Deprecated
  BLDEBUG_PRINT("built for SERIAL UART standalone bootloader\r\n");
  return BL_TYPE_STANDALONE;
  #elif defined SERIAL_USB_BTL
  // Deprecated
  BLDEBUG_PRINT("built for SERIAL USB standalone bootloader\r\n");
  return BL_TYPE_STANDALONE;
  #elif defined SERIAL_OTA_BTL
  // Deprecated
  BLDEBUG_PRINT("built for SERIAL OTA standalone bootloader\r\n");
  return BL_TYPE_STANDALONE;
  #elif defined GECKO_INFO_PAGE_BTL  \
  || defined APP_GECKO_INFO_PAGE_BTL \
  || defined STA_GECKO_INFO_PAGE_BTL \
  || defined LOCAL_STORAGE_GECKO_INFO_PAGE_BTL
  BLDEBUG_PRINT("built for Gecko info page bootloader\r\n");
  return BL_TYPE_STANDALONE;
  #else
  BLDEBUG_PRINT("built for generic bootloader\r\n");
  return BL_TYPE_BOOTLOADER;
  #endif
}

/** @description Returns the bootloader type present on the device.
 *
 * @return BL_TYPE_NULL, BL_TYPE_STANDALONE, BL_TYPE_APPLICATION or
 *         BL_TYPE_COMMON
 */
BlExtendedType halBootloaderGetInstalledType(void)
{
  // Important distinction:
  //   this returns what bootloader is actually present on the chip
  if (bootloaderIsCommonBootloader()) {
    // TODO: Assert that mainBootloaderTable pointer is sane
    if (mainBootloaderTable->capabilities & BOOTLOADER_CAPABILITY_STORAGE) {
      return BL_EXT_TYPE_APP_UNKNOWN;
    } else if (mainBootloaderTable->capabilities & BOOTLOADER_CAPABILITY_COMMUNICATION) {
      return BL_EXT_TYPE_STANDALONE_UNKNOWN;
    } else {
      return BL_EXT_TYPE_NULL;
    }
  } else {
#ifndef NO_BAT
    return halBootloaderAddressTable.bootloaderType;
#else
    return BL_EXT_TYPE_NULL;
#endif
  }
}

uint16_t halGetBootloaderVersion(void)
{
  if (bootloaderIsCommonBootloader()) {
    return mainBootloaderTable->header.version >> 16;
  } else {
#ifndef NO_BAT
    return halBootloaderAddressTable.bootloaderVersion;
#else
    return BOOTLOADER_INVALID_VERSION;
#endif
  }
}

void halGetExtendedBootloaderVersion(uint32_t* getEmberVersion, uint32_t* customerVersion)
{
  uint32_t ember = 0xFFFFFFFFU, customer = 0xFFFFFFFFU;

  if (bootloaderIsCommonBootloader()) {
    ember = mainBootloaderTable->header.version;
    customer = mainBootloaderTable->header.version;
  } else {
#ifndef NO_BAT
    // check BAT version to figure out how to create the emberVersion
    if (halBootloaderAddressTable.baseTable.version >= 0x0109) {
      // Newer BATs have a bootloaderVersion and bootloaderBuild that need to be combined
      ember = ((uint32_t)halBootloaderAddressTable.bootloaderVersion) << 16 | halBootloaderAddressTable.bootloaderBuild;
      customer = halBootloaderAddressTable.customerBootloaderVersion;
    } else {
      // Older BATs had these fields grouped together. Reformat them to be in the new format
      ember  = (((uint32_t)halBootloaderAddressTable.bootloaderVersion) << 16) & 0xFF000000;
      ember |= halBootloaderAddressTable.bootloaderVersion & 0x000000FF;
    }
#endif
  }

  // If the pointers aren't NULL copy the results over
  if (getEmberVersion != NULL) {
    *getEmberVersion = ember;
  }
  if (customerVersion != NULL) {
    *customerVersion = customer;
  }
}
