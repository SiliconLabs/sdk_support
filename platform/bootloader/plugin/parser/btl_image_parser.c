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
#include <stdbool.h>
#include <string.h>

#include "config/btl_config.h"
#include "api/btl_interface.h"

#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
#include "core/btl_bootload.h"
#endif

#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
#include "plugin/security/btl_security_sha256.h"
#include "plugin/security/btl_security_ecdsa.h"
#include "plugin/parser/ebl/btl_ebl_parser.h"
#endif

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

bool parser_requireAntiRollbackProtection(void)
{
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  return true;
#else
  return false;
#endif
}

uint32_t parser_applicationMinimumVersionValid(void)
{
#if defined(BOOTLOADER_ROLLBACK_PROTECTION_MINIMUM_VERSION)
  return BOOTLOADER_ROLLBACK_PROTECTION_MINIMUM_VERSION;
#else
  return 0UL;
#endif
}

bool parser_applicationUpgradeVersionValid(ApplicationData_t *app, bool checkRemainingAppUpgrades)
{
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  if (app == NULL) {
    return false;
  }
  return bootload_verifyApplicationVersion(app->version, checkRemainingAppUpgrades);
#else
  (void)app;
  (void)checkRemainingAppUpgrades;
  return true;
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
  return FLASH_BASE + BTL_UPGRADE_LOCATION_BASE;
#endif
}

SL_WEAK bool parser_applicationUpgradeValidCallback(ApplicationData_t *app)
{
  (void) app;
  // By default, all applications are considered valid
  return true;
}

int32_t parser_verifyCertificate(void *context,
                                 void *input,
                                 void *blProperties,
                                 void *shaState)
{
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
  ParserContext_t *parserContext = (ParserContext_t *)context;
  GblInputBuffer_t *inputBuffer = (GblInputBuffer_t*)input;
  ApplicationProperties_t *blAppProperties = (ApplicationProperties_t*)blProperties;
  Sha256Context_t *certShaState = (Sha256Context_t*)shaState;
  uint8_t tagBuffer[GBL_PARSER_BUFFER_SIZE];
  int32_t retval = BOOTLOADER_ERROR_PARSER_UNEXPECTED;

  volatile int32_t signatureVerifyResp = BOOTLOADER_ERROR_SECURITY_REJECTED;

  if (parserContext->offsetInTag < 4UL) {
    retval = gbl_getData(context,
                         inputBuffer,
                         tagBuffer,
                         4UL,
                         true,
                         false);
    if (retval != BOOTLOADER_ERROR_PARSER_PARSED) {
      return retval;
    }
    memcpy(&(parserContext->certificate.structVersion), tagBuffer, 4U);
  } else if (parserContext->offsetInTag < 68UL) {
    // Get ECDSA public key.
    retval = gbl_getData(context,
                         inputBuffer,
                         tagBuffer,
                         64UL,
                         true,
                         false);
    if (retval != BOOTLOADER_ERROR_PARSER_PARSED) {
      return retval;
    }
    // Save ECDSA public key in the context
    // for verification of the GBL.
    memcpy(parserContext->certificate.key, tagBuffer, 64U);
  } else if (parserContext->offsetInTag < 72UL) {
    // Get version of this certificate.
    retval = gbl_getData(context,
                         inputBuffer,
                         tagBuffer,
                         4UL,
                         true,
                         false);
    if (retval != BOOTLOADER_ERROR_PARSER_PARSED) {
      return retval;
    }
    memcpy(&(parserContext->certificate.version), tagBuffer, 4U);
    if ((blAppProperties->cert == NULL)) {
      return BOOTLOADER_ERROR_PARSER_SIGNATURE;
    }
    if ((blAppProperties->cert->version > parserContext->certificate.version)) {
      return BOOTLOADER_ERROR_PARSER_SIGNATURE;
    }
  } else {
    // Get signature of the certificate.
    retval = gbl_getData(context,
                         inputBuffer,
                         tagBuffer,
                         64UL,
                         true,
                         false);
    if (retval != BOOTLOADER_ERROR_PARSER_PARSED) {
      return retval;
    }
    memcpy(parserContext->certificate.signature, tagBuffer, 64U);
    // SHA-256 of the certificate.
    btl_initSha256(certShaState);
    btl_updateSha256(certShaState,
                     (const uint8_t*)&(parserContext->certificate),
                     72U);
    btl_finalizeSha256(certShaState);
    // Use the public key stored in the bootloader certificate to verify the GBL certificate.
    signatureVerifyResp = btl_verifyEcdsaP256r1(certShaState->sha,
                                                &(parserContext->certificate.signature[0]),
                                                &(parserContext->certificate.signature[32]),
                                                &(blAppProperties->cert->key[0]),
                                                &(blAppProperties->cert->key[32]));
#if defined(SEMAILBOX_PRESENT)
    if (signatureVerifyResp == BOOTLOADER_ERROR_SECURITY_REJECTED) {
    // Check if the OTP platform key can verify the certificate.
    signatureVerifyResp = btl_verifyEcdsaP256r1(certShaState->sha,
                                                &(parserContext->certificate.signature[0]),
                                                &(parserContext->certificate.signature[32]),
                                                NULL,
                                                NULL);
    }
#endif
    if (signatureVerifyResp != BOOTLOADER_OK) {
      return BOOTLOADER_ERROR_PARSER_SIGNATURE;
    }
    parserContext->gotCertificate = true;
    parserContext->internalState = EblParserStateIdle;
  }
  return retval;
#else
  (void)context;
  (void)input;
  (void)blProperties;
  (void)shaState;
  return BOOTLOADER_ERROR_PARSER_SIGNATURE;
#endif
}
