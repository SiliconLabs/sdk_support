/***************************************************************************//**
 * @file
 * @brief Application interface for ember bootloader
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "em_core.h"
#include "em_device.h"
#include "em_emu.h"

#include "ember_btl_interface.h"
#include "btl_errorcode.h"

extern const BootloaderAddressTable_t *bootloaderAddressTable;

int32_t bootloader_init(void)
{
  if (bootloaderAddressTable->init() == BOOTLOADER_OK) {
    return BOOTLOADER_OK;
  } else {
    return BOOTLOADER_ERROR_INIT_STORAGE;
  }
}

void bootloader_getInfo(BootloaderInformation_t *info)
{
  BootloaderInformation_t *storageInfo;
  storageInfo = (BootloaderInformation_t *)bootloaderAddressTable->storageInfo();

  info->version = storageInfo->version;
  info->capabilitiesMask = storageInfo->capabilitiesMask;
  info->pageEraseMs = storageInfo->pageEraseMs;
  info->partEraseTime = storageInfo->partEraseTime;
  info->pageSize = storageInfo->pageSize;
  info->partSize = storageInfo->partSize;
  info->wordSizeBytes = storageInfo->wordSizeBytes;
}

int32_t bootloader_deinit(void)
{
  bootloaderAddressTable->deinit();
  return BOOTLOADER_OK;
}

// Workaround for brownouts on Dumbo when DCDC is retimed and radio subsystem is reset
__STATIC_INLINE void disableDcdcRetimingAndRcosync(void)
{
  // Ensure access to EMU registers
  EMU_Unlock();
  EMU_PowerUnlock();

  // Don't need to disable retiming if DCDC is not powering DVDD
  if ((EMU->PWRCFG & _EMU_PWRCFG_PWRCFG_MASK) != EMU_PWRCFG_PWRCFG_DCDCTODVDD) {
    return;
  }

  // Ensure sequencer is halted
  uint32_t clockEnable = *(volatile uint32_t *)(0x400E4000 + 0xC8);
  volatile uint32_t *reg;
  if (clockEnable & 0x4UL) {
    reg = (volatile uint32_t *)(0x40084000UL + 0x40);
    *reg = 0x1UL;
  }

  // If DCDC is in use, ensure retiming and rcosync are disabled
  uint32_t dcdcMode = EMU->DCDCCTRL & _EMU_DCDCCTRL_DCDCMODE_MASK;
  if ((dcdcMode == EMU_DCDCCTRL_DCDCMODE_LOWNOISE)
      || (dcdcMode == EMU_DCDCCTRL_DCDCMODE_LOWPOWER)) {
    BUS_RegBitWrite(&EMU->DCDCTIMING, 28, 0);
    // EMU->DCDCRCOSC is internal, _EMU_DCDCRCOSC_RCOSYNC_SHIFT = 0
    BUS_RegBitWrite((void *)(EMU_BASE + 0x74), 0, 0);
  }
}

void bootloader_rebootAndInstall(void)
{
  CORE_ATOMIC_IRQ_DISABLE();

  // Set reset reason to bootloader entry
  BootloaderResetCause_t* resetCause = (BootloaderResetCause_t*) (RAM_MEM_BASE);
  resetCause->reason = EMBER_BOOTLOADER_RESET_REASON_BOOTLOAD;
  resetCause->signature = EMBER_BOOTLOADER_RESET_SIGNATURE_VALID;

  disableDcdcRetimingAndRcosync();

#if defined(RMU_PRESENT)
  // Clear resetcause
  RMU->CMD = RMU_CMD_RCCLR;
  // Trigger a software system reset
  RMU->CTRL = (RMU->CTRL & ~_RMU_CTRL_SYSRMODE_MASK) | RMU_CTRL_SYSRMODE_FULL;
#endif

  NVIC_SystemReset();
}

static uint8_t buff[EEPROM_PAGE_SIZE];
BootloaderStorageState_t storageState;
EblConfig_t eblConfig;

int32_t bootloader_initVerifyImage(uint32_t slotId, void *context, size_t contextSize)
{
  (void)slotId;
  (void)context;
  (void)contextSize;

  storageState.address = 0;
  storageState.pages = 0;
  storageState.pageBufFinger = 0;
  storageState.pageBufLen = 0;
  bootloaderAddressTable->eblProcessInit(&eblConfig,
                                         &storageState,
                                         buff,
                                         EBL_MIN_TAG_SIZE,
                                         true);

  return BOOTLOADER_OK;
}

int32_t bootloader_continueVerifyImage(void *context, BootloaderParserCallback_t metadataCallback)
{
  (void)context;
  (void)metadataCallback;

  uint8_t status;
  status = bootloaderAddressTable->eblProcess(bootloaderAddressTable->eblDataFunctions,
                                              &eblConfig,
                                              NULL);

  if (status == EMBER_BOOTLOADER_PARSE_CONTINUE) {
    return BOOTLOADER_ERROR_PARSE_CONTINUE;
  } else if (status == BOOTLOADER_OK) {
    return BOOTLOADER_ERROR_PARSE_SUCCESS;
  } else {
    return BOOTLOADER_ERROR_PARSE_FAILED;
  }
}

int32_t bootloader_verifyImage(uint32_t slotId, BootloaderParserCallback_t metadataCallback)
{
  (void)slotId;
  (void)metadataCallback;

  int32_t retval;

  void *context = NULL;
  size_t contextSize = 0;
  bootloader_initVerifyImage(slotId, context, contextSize);

  do {
    retval = bootloader_continueVerifyImage(context, metadataCallback);
  } while (retval == BOOTLOADER_ERROR_PARSE_CONTINUE);

  if (retval == BOOTLOADER_ERROR_PARSE_SUCCESS) {
    return BOOTLOADER_OK;
  } else {
    return retval;
  }
}

bool bootloader_storageIsBusy(void)
{
  return bootloaderAddressTable->storageBusy();
}

int32_t bootloader_readRawStorage(uint32_t address, uint8_t *buffer, size_t length)
{
  if (bootloaderAddressTable->storageReadRaw(address, buffer, length) == BOOTLOADER_OK) {
    return BOOTLOADER_OK;
  } else {
    return BOOTLOADER_ERROR_STORAGE_GENERIC;
  }
}

int32_t bootloader_writeRawStorage(uint32_t address, uint8_t *buffer, size_t length)
{
  if (bootloaderAddressTable->storageReadRaw(address, buffer, length) == BOOTLOADER_OK) {
    return BOOTLOADER_OK;
  } else {
    return BOOTLOADER_ERROR_STORAGE_GENERIC;
  }
}

int32_t bootloader_eraseRawStorage(uint32_t address, size_t length)
{
  if (bootloaderAddressTable->storageEraseRaw(address, length) == BOOTLOADER_OK) {
    return BOOTLOADER_OK;
  } else {
    return BOOTLOADER_ERROR_STORAGE_GENERIC;
  }
}
