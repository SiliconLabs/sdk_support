/*******************************************************************************
 * @file  FlashPrg.c
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "ccp_flash_prg.h" // FlashOS Structures
#include "RS1xxxx_9117.h"
#include "ccp_flash_intf.h"
#include <stdint.h>

/*
 *  Initialize Flash Programming Functions
 *    Parameter:      adr:  Device Base Address
 *                    clk:  Clock Frequency (Hz)
 *                    fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */
int Init(unsigned long adr, unsigned long clk, unsigned long fnc) {
  return RSI_FLASH_Initialize();
}

/*
 *  De-Initialize Flash Programming Functions
 *    Parameter:      fnc:  Function Code (1 - Erase, 2 - Program, 3 - Verify)
 *    Return Value:   0 - OK,  1 - Failed
 */

int UnInit(unsigned long fnc) { return RSI_FLASH_UnInitialize(); }

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseChip(void) { return RSI_FLASH_Erasechip(); }

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *    Return Value:   0 - OK,  1 - Failed
 */

int EraseSector(unsigned long adr) {
  // adr &= 0x00FFFFFF;
  return RSI_FLASH_EraseSector(adr);
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf) {
  // adr &= 0x00FFFFFF;
  // return RSI_FLASH_ProgramPage(adr, buf, sz);
  return RSI_FLASH_Write(adr, buf, sz);
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */

int ReadFlash(unsigned long adr, unsigned long sz, unsigned char *buf) {
  // adr &= 0x00FFFFFF;
  // return RSI_FLASH_ProgramPage(adr, buf, sz);
  return RSI_FLASH_Read(adr, buf, sz, 0); // 0 -> automode
}

/*
 *  Verify Flash Contents
 *    Parameter:      adr:  Start Address
 *                    sz:   Size (in bytes)
 *                    buf:  Data
 *    Return Value:   (adr+sz) - OK, Failed Address
 */
unsigned long Verify(unsigned long adr, unsigned long sz, unsigned char *buf) {
  return RSI_FLASH_Verify(adr, buf, sz);
}
