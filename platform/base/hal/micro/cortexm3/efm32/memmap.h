/***************************************************************************//**
 * @file
 * @brief Definition of efr32 family specific memory map information
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
#ifndef __MEMMAP_H__
  #error This header should not be included directly, use hal/micro/cortexm3/memmap.h
#endif

#ifndef EFM32_MEMMAP_H
#define EFM32_MEMMAP_H

#include "em_device.h"

#define RAM_BOTTOM          SRAM_BASE
#define RAM_SIZE_B          SRAM_SIZE
#define RAM_SIZE_W          (RAM_SIZE_B / 4)
#define RAM_TOP             (RAM_BOTTOM + RAM_SIZE_B - 1)

#define MFB_BOTTOM          FLASH_BASE
#define MFB_SIZE_B          FLASH_SIZE
#define MFB_SIZE_W          (MFB_SIZE_B / 4)
#define MFB_TOP             (MFB_BOTTOM + MFB_SIZE_B - 1)
#define MFB_PAGE_SIZE_B     FLASH_PAGE_SIZE
#define MFB_PAGE_SIZE_W     (MFB_PAGE_SIZE_B / 4)
#define MFB_PAGE_MASK_B     (~(FLASH_PAGE_SIZE - 1))
#define MFB_REGION_SIZE     (1)  // Size of a write protect region in pages
#define MFB_ADDR_MASK       (FLASH_SIZE - 1)

// Default to a 16 kB bootloader on all EFR32
#define BOOTLOADER_16K

// Size in bytes that one RAM retention bit covers
#define RAM_RETAIN_BLOCK_SIZE (0)

//Translation between page number and code addresses, used by bootloaders
#if FLASH_PAGE_SIZE == 1024
#  define PROG_ADDR_TO_PAGE(x)    ((uint8_t)((((uint32_t)(x)) & MFB_ADDR_MASK) >> 10))
#  define PAGE_TO_PROG_ADDR(x)    ((((uint32_t)(x)) << 10) | MFB_BOTTOM)
#elif FLASH_PAGE_SIZE == 2048
#  define PROG_ADDR_TO_PAGE(x)    ((uint8_t)((((uint32_t)(x)) & MFB_ADDR_MASK) >> 11))
#  define PAGE_TO_PROG_ADDR(x)    ((((uint32_t)(x)) << 11) | MFB_BOTTOM)
#elif FLASH_PAGE_SIZE == 8192
#  define PROG_ADDR_TO_PAGE(x)    ((uint8_t)((((uint32_t)(x)) & MFB_ADDR_MASK) >> 13))
#  define PAGE_TO_PROG_ADDR(x)    ((((uint32_t)(x)) << 13) | MFB_BOTTOM)
#else
#  error "Unknown flash page size; cannot create PAGE_TO_PROG_ADDR macro."
#endif

#endif // EFM32_MEMMAP_H
