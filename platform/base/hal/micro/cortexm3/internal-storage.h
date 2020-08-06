/***************************************************************************//**
 * @file
 * @brief Header for an internal flash storage region on the em35x.
 * This file creates some useful #defines for the internal storage
 * region and do some basic storage size error checking.
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
#ifndef __INTERNAL_STORAGE_H_
#define __INTERNAL_STORAGE_H_

#include PLATFORM_HEADER
#include "hal/micro/cortexm3/memmap.h"
#include "hal/micro/cortexm3/bootloader-size.h"

// Loader does not have a fixed SIMEE (or even page) size, which is assumed by
// the following header
#ifndef LOADER
#include "hal/plugin/sim-eeprom/sim-eeprom-size.h"
#endif

#ifdef USE_NVM3
#define NVMDATA_SIZE_B (NVM3_DEFAULT_NVM_SIZE)
#else
#define NVMDATA_SIZE_B SIMEE_SIZE_B
#endif

// Create some min/max sizes for the storage region to prevent problems
//  The logic here is that we don't want to have this size accidentally set to a value
//  that is so small we can never bootload a new image into it to fix things. Since
//  our standalone bootloader is 8KiB make sure that there is alway 8KiB available in
//  storage AND that storage is never so big that we can't fit an 8KiB app in the MFB.
#define MIN_RECOVERY_IMAGE_SIZE      (8 * 1024)
#define MIN_INTERNAL_STORAGE_SIZE_B  (MIN_RECOVERY_IMAGE_SIZE)
#define MAX_INTERNAL_STORAGE_SIZE_B  (MFB_SIZE_B - BOOTLOADER_SIZE_B - MIN_RECOVERY_IMAGE_SIZE)

#ifndef PSSTORE_SIZE
  #define PSSTORE_SIZE (0U)
#endif

#ifndef LOCKBITS_IN_MAINFLASH_SIZE
  #define LOCKBITS_IN_MAINFLASH_SIZE (0U)
#endif

#ifndef LONGTOKEN_SIZE
  #define LONGTOKEN_SIZE (0U)
#endif

// If we're using a local storage bootloader then attempt to calculate the size
// of internal storage unless it's already been specified.
#if defined(INTERNAL_STORAGE_SIZE_KB)
// Use the size specified on the command line if it's available
  #define INTERNAL_STORAGE_SIZE_B (INTERNAL_STORAGE_SIZE_KB * 1024U)
#else
  #if defined(LOCAL_STORAGE_BTL) || defined(LOCAL_STORAGE_GECKO_INFO_PAGE_BTL)
// The logical storage size is roughly half the "application" flash. Application
// flash is the MFB less sections that are not loaded with the app (simee/nvm3,
// bootloader, MFB replacement lockbits, psstore, and long token).

    #define HALF_APP_SPACE   ((MFB_SIZE_B                   \
                               - NVMDATA_SIZE_B             \
                               - BOOTLOADER_SIZE_B          \
                               - LOCKBITS_IN_MAINFLASH_SIZE \
                               - PSSTORE_SIZE               \
                               - LONGTOKEN_SIZE)            \
                              / 2U)

// HALF_APP_SPACE above may not be a multiple of the flash page size (because,
// for instance, LOCKBITS_IN_MAINFLASH_SIZE, LONGTOKEN_SIZE, or NVMDATA_SIZE_B
// is an odd number of pages in size). Round up to the next multiple if so.
    #if (HALF_APP_SPACE % MFB_PAGE_SIZE_B) != 0
      #define ROUNDED_HALF_APP_SPACE (HALF_APP_SPACE    \
                                      + MFB_PAGE_SIZE_B \
                                      - (HALF_APP_SPACE % MFB_PAGE_SIZE_B))
    #else
      #define ROUNDED_HALF_APP_SPACE (HALF_APP_SPACE)
    #endif

// Add another flash page to account for the overhead in the upgrade image
    #define INTERNAL_STORAGE_SIZE_B  (ROUNDED_HALF_APP_SPACE + MFB_PAGE_SIZE_B)

  #else
    #define INTERNAL_STORAGE_SIZE_B (0U)
  #endif
#endif

// If we're using an internal storage region then add some error checking of the
// specified size since there are invalid values
#if INTERNAL_STORAGE_SIZE_B > 0
// Check to make sure that the internal storage region size is a multiple of the
// flash page size. If this was not true we wouldn't be able to erase storage
// pages independently from regular flash
  #if (INTERNAL_STORAGE_SIZE_B % MFB_PAGE_SIZE_B) != 0
    #error INTERNAL_STORAGE_SIZE_B must be a multiple of the flash page size!
  #endif

// Enforce the min and max internal storage sizes defined above
  #if INTERNAL_STORAGE_SIZE_B < MIN_INTERNAL_STORAGE_SIZE_B
    #error INTERNAL_STORAGE_SIZE_B is smaller than the minimum
  #endif
  #if INTERNAL_STORAGE_SIZE_B > MAX_INTERNAL_STORAGE_SIZE_B
    #error INTERNAL_STORAGE_SIZE_B is larger than the maximum
  #endif
#endif

#endif //__INTERNAL_STORAGE_H_
