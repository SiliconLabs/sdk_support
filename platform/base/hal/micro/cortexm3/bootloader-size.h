/***************************************************************************//**
 * @file
 * @brief File to create defines for the size of the bootloader
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
#ifndef __BOOTLOADER_SIZE_H__
#define __BOOTLOADER_SIZE_H__

#include "hal/micro/cortexm3/memmap.h"

// Create the BOOTLOADER_SIZE_B define
#if defined(NULL_BTL)                 \
  || defined(GECKO_INFO_PAGE_BTL)     \
  || defined(APP_GECKO_INFO_PAGE_BTL) \
  || defined(STA_GECKO_INFO_PAGE_BTL) \
  || defined(LOCAL_STORAGE_GECKO_INFO_PAGE_BTL)
  #define BOOTLOADER_SIZE_B (0)
#elif defined(BOOTLOADER_16K)
  #define BOOTLOADER_SIZE_B (16 * 1024)
#elif defined(BOOTLOADER_10K)
  #define BOOTLOADER_SIZE_B (10 * 1024)
#elif defined(BOOTLOADER_8K)
  #define BOOTLOADER_SIZE_B (8 * 1024)
#elif defined(BOOTLOADER_4K)
  #define BOOTLOADER_SIZE_B (4 * 1024)
#else
// Choose whatever the default is for this chip
  #define BOOTLOADER_SIZE_B (DEFAULT_BTL_SIZE_B)
#endif

#endif //__BOOTLOADER_SIZE_H__
