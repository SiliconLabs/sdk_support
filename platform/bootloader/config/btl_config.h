/***************************************************************************//**
 * @file
 * @brief Configuration for bootloader
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
#ifndef BTL_CONFIG_H
#define BTL_CONFIG_H

//
// Bootloader Version
//
#define BOOTLOADER_VERSION_MAIN_MAJOR             1
#define BOOTLOADER_VERSION_MAIN_MINOR             10
#ifndef BOOTLOADER_VERSION_MAIN_CUSTOMER
#define BOOTLOADER_VERSION_MAIN_CUSTOMER          3
#endif

#define BOOTLOADER_VERSION_MAIN (BOOTLOADER_VERSION_MAIN_MAJOR   << 24 \
                                 | BOOTLOADER_VERSION_MAIN_MINOR << 16 \
                                 | BOOTLOADER_VERSION_MAIN_CUSTOMER)

#include "core/btl_util.h"

MISRAC_DISABLE
#include "em_device.h"
MISRAC_ENABLE

//
// Bootloader configuration
//
#include BTL_CONFIG_FILE

#ifdef BTL_SLOT_CONFIGURATION
  #include BTL_SLOT_CONFIGURATION
#endif

//
// HAL Configuration
//
#ifndef LIBRARY_BUILD
#include "hal-config.h"
#endif
//
// Option validation
//

#if defined(BTL_UPGRADE_LOCATION_BASE)
// BTL_UPGRADE_LOCATION_BASE is fixed on Series-1 devices.
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
// The upgrade location needs to fit upgrades of up to 42k
#if ((BTL_UPGRADE_LOCATION_BASE + 0x0000C000UL) > FLASH_SIZE) \
  || (BTL_UPGRADE_LOCATION_BASE % FLASH_PAGE_SIZE)
#error "Invalid bootloader upgrade base address"
#endif
#elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
// The upgrade location needs to fit upgrades of up to 24k
#if ((BTL_UPGRADE_LOCATION_BASE + 0x00006000UL) > FLASH_SIZE) \
  || (BTL_UPGRADE_LOCATION_BASE % FLASH_PAGE_SIZE)
#error "Invalid bootloader upgrade base address"
#endif
#endif

#if defined(_SILICON_LABS_32B_SERIES_2)
#include "api/btl_interface.h"
#if (BTL_UPGRADE_LOCATION_BASE < (BTL_MAIN_STAGE_MAX_SIZE + BTL_FIRST_STAGE_SIZE))
#error "Invalid bootloader upgrade base address"
#endif
#endif // defined(_SILICON_LABS_32B_SERIES_2)

#endif // defined(BTL_UPGRADE_LOCATION_BASE)
#endif // BTL_CONFIG_H
