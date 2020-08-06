/***************************************************************************//**
 * @file
 * @brief Image parser for Silicon Labs bootloader
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
#include "config/btl_config.h"

#include <stdbool.h>
#include "api/btl_interface.h"

#include "em_common.h"

bool parser_requireAuthenticity(void)
{
#if defined(BOOTLOADER_ENFORCE_SIGNED_UPGRADE)
  return true;
#else
  return false;
#endif
}

bool parser_requireConfidentiality(void)
{
#if defined(BOOTLOADER_ENFORCE_ENCRYPTED_UPGRADE)
  return true;
#else
  return false;
#endif
}

bool parser_requireCertificateAuthenticity(void)
{
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
  return true;
#else
  return false;
#endif
}

bool parser_requireCertificateSignedImage(void)
{
#if defined(BOOTLOADER_REJECT_DIRECT_SIGNED_IMG)
  return true;
#else
  return false;
#endif
}

uint32_t parser_getApplicationAddress(void)
{
  return (uint32_t)(&(mainBootloaderTable->startOfAppSpace->stackTop));
}

#if defined(BOOTLOADER_HAS_FIRST_STAGE)
uint32_t parser_getFirstStageBootloaderTable(void)
{
  return (uint32_t)firstBootloaderTable;
}
#endif

uint32_t parser_getMainBootloaderTable(void)
{
  return (uint32_t)mainBootloaderTable;
}

uint32_t parser_getBootloaderUpgradeAddress(void)
{
#if defined(BOOTLOADER_HAS_FIRST_STAGE)
  if (firstBootloaderTable->header.type == BOOTLOADER_MAGIC_FIRST_STAGE) {
    return (uint32_t)(firstBootloaderTable->upgradeLocation);
  } else {
    return 0UL;
  }
#else
  return BTL_UPGRADE_LOCATION_BASE;
#endif
}

SL_WEAK bool parser_applicationUpgradeValidCallback(ApplicationData_t *app)
{
  (void) app;
  // By default, all applications are considered valid
  return true;
}
