/***************************************************************************//**
 * @file
 * @brief Manufacturing token handling
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
#include "btl_security_tokens.h"
#include "em_device.h"

#if defined(LOCKBITS_BASE)
#define PUBKEY_OFFSET_X (0x34A)
#define PUBKEY_OFFSET_Y (0x36A)
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#include <stddef.h>
#include "config/btl_config.h"
// Lockbits are placed in the topmost flash page
#define LOCKBITS_BASE ((FLASH_BASE) + (FLASH_SIZE) -(FLASH_PAGE_SIZE))
#if defined(BOOTLOADER_FALLBACK_LEGACY_KEY)
#include "em_se.h"
#define PUBKEY_OFFSET_X (0x34C)
#define PUBKEY_OFFSET_Y (0x36C)
#endif
// #elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205)
// Lockbits are placed in the topmost flash page
#define LOCKBITS_BASE ((FLASH_BASE) + (FLASH_SIZE) -(FLASH_PAGE_SIZE))
#define PUBKEY_OFFSET_X (0x34C)
#define PUBKEY_OFFSET_Y (0x36C)
// #elif defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205)
#else
#error "Lockbits location unknown"
#endif

const uint8_t* btl_getSignedBootloaderKeyXPtr(void)
{
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#if defined(BOOTLOADER_FALLBACK_LEGACY_KEY)
  uint8_t se_platform_pubKey[64];
  SE_Response_t ret = SE_readPubkey(SE_KEY_TYPE_BOOT, &se_platform_pubKey, 64, false);
  if (ret == SE_RESPONSE_INTERNAL_ERROR) {
    return (const uint8_t*)(LOCKBITS_BASE + PUBKEY_OFFSET_X);
  } else {
    return NULL;
  }
#else
  return NULL;
#endif
// defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#else
  return (const uint8_t*)(LOCKBITS_BASE + PUBKEY_OFFSET_X);
#endif
}

const uint8_t* btl_getSignedBootloaderKeyYPtr(void)
{
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#if defined(BOOTLOADER_FALLBACK_LEGACY_KEY)
  uint8_t se_platform_pubKey[64];
  SE_Response_t ret = SE_readPubkey(SE_KEY_TYPE_BOOT, &se_platform_pubKey, 64, false);
  if (ret == SE_RESPONSE_INTERNAL_ERROR) {
    return (const uint8_t*)(LOCKBITS_BASE + PUBKEY_OFFSET_Y);
  } else {
    return NULL;
  }
#else
  return NULL;
#endif
// defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200)
#else
  return (const uint8_t*)(LOCKBITS_BASE + PUBKEY_OFFSET_Y);
#endif
}

const uint8_t* btl_getImageFileEncryptionKeyPtr(void)
{
  return (const uint8_t*)(LOCKBITS_BASE + 0x286);
}
