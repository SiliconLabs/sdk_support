/***************************************************************************//**
 * @file
 * @brief EM300 series memory map fixed address table definition
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
#ifndef __MEMMAP_FAT_H__
#define __MEMMAP_FAT_H__

#ifndef __MEMMAP_TABLES_H__
// if we weren't included via memmap-tables.h, define a dummy type for the BAT
typedef void HalBootloaderAddressTableType;
#endif

#include "hal/micro/cortexm3/bootloader/fib-bootloader.h"

// ****************************************************************************
// If any of these address table definitions ever need to change, it is highly
// desirable to only add new entries, and only add them on to the end of an
// existing address table... this will provide the best compatibility with
// any existing code which may utilize the tables, and which may not be able to
// be updated to understand a new format (example: bootloader which reads the
// application address table)

// Description of the Fixed Address Table (FAT)
typedef struct {
  HalBaseAddressTableType baseTable;
  void *CustomerInformationBlock;
  HalBootloaderAddressTableType *bootloaderAddressTable;
  void *startOfUnusedRam;
  // ** pointers to shared functions **
  FibStatus (* fibFlashWrite)(uint32_t address, uint8_t *data,
                              uint32_t writeLength, uint32_t verifyLength);
  FibStatus (* fibFlashErase)(FibEraseType eraseType, uint32_t address);
} HalFixedAddressTableType;

extern const HalFixedAddressTableType halFixedAddressTable;

#define FIXED_ADDRESS_TABLE_TYPE        (0x0FA7)

// The current versions of the address tables.
// Note that the major version should be updated only when a non-backwards
// compatible change is introduced (like removing or rearranging fields)
// adding new fields is usually backwards compatible, and their presence can
// be indicated by incrementing only the minor version
#define FAT_VERSION                     (0x0003)
#define FAT_MAJOR_VERSION               (0x0000)
#define FAT_MAJOR_VERSION_MASK          (0xFF00)

// *** FAT Version history: ***
// 0x0003 - Cstartup chip initialization update
// 0x0002 - Add function pointers for shared flash drivers, Restore peripheral
//          registers before resetting
// 0x0001 - Initial version

#endif //__MEMMAP_FAT_H__
