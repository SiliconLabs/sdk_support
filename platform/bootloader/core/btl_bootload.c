/***************************************************************************//**
 * @file
 * @brief Bootloading functionality for the Silicon Labs bootloader
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
#include "config/btl_config.h"

#include "btl_bootload.h"
#include "api/btl_interface.h"
#include "api/application_properties.h"
#include "plugin/parser/btl_image_parser.h"
#include "plugin/security/btl_security_types.h"
#include "plugin/security/btl_security_ecdsa.h"
#include "core/flash/btl_internal_flash.h"

//
// Option validation
//
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) || defined(MAIN_BOOTLOADER_IN_MAIN_FLASH)
#error "Rollback protection not supported"
#endif
#endif // defined(BOOTLOADER_ROLLBACK_PROTECTION)

#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
#if !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_200) && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_205)
#error "Certificate not supported"
#endif
#endif // defined(BOOTLOADER_SUPPORT_CERTIFICATES)

// --------------------------------
// Local type declarations

#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
static bool checkResetMagic(void);
static bool checkMaxVersionMagic(void);
static uint32_t getHighestApplicationVersionSeen(void);
#endif

// --------------------------------
// Defines

#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
#define SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY 6UL
#define SL_GBL_APPLICATION_VERSION_MAX_MAGIC        0x1234DCBAUL
#define SL_GBL_APPLICATION_VERSION_RESET_MAGIC      0x5839FBACUL
#define SL_GBL_UINT32_MAX_NUMBER                    0xFFFFFFFFUL
#endif

// --------------------------------
// Local functions

#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
static bool checkMaxVersionMagic(void) {
  uint32_t *versionMaxMagicPtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY);
  if (*versionMaxMagicPtr == SL_GBL_APPLICATION_VERSION_MAX_MAGIC) {
    return true;
  }
  return false;
}

static bool checkResetMagic(void) {
  uint32_t *versionResetMagicPtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY + 1UL);
  if (*versionResetMagicPtr == SL_GBL_APPLICATION_VERSION_RESET_MAGIC) {
    return true;
  }
  return false;
}

static uint32_t getHighestApplicationVersionSeen(void) {
  uint32_t *appVersionStoragePtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY);
  if (checkMaxVersionMagic()) {
    return SL_GBL_UINT32_MAX_NUMBER;
  }

  for (uint32_t i = 0UL; i < SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY; i++) {
    ++appVersionStoragePtr;
    if (*appVersionStoragePtr != SL_GBL_UINT32_MAX_NUMBER) {
      return *appVersionStoragePtr;
    }
  }

  return parser_applicationMinimumVersionValid();
}
#endif

// --------------------------------
// Global functions

uint32_t bootload_getApplicationVersionStorageCapacity(void) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  return SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY;
#else
  return 0UL;
#endif
}

uint32_t* bootload_getApplicationVersionStoragePtr(uint32_t index) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  uint32_t endOfBLpage = BTL_FIRST_STAGE_BASE + BTL_FIRST_STAGE_SIZE + BTL_MAIN_STAGE_MAX_SIZE;
  uint32_t *appVersionStoragePtr = (uint32_t*)endOfBLpage - (index + 1UL);
  return appVersionStoragePtr;
#else
  (void)index;
  return NULL;
#endif
}

bool bootload_storeApplicationVersion(uint32_t startAddress) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  BareBootTable_t *appStart = (BareBootTable_t *)startAddress;
  ApplicationProperties_t *appProperties = (ApplicationProperties_t *)(appStart->signature);
  uint32_t appVersion = appProperties->app.version;
  uint32_t emptySlots = bootload_remainingApplicationUpgrades();
  uint32_t highestVersionSeen = getHighestApplicationVersionSeen();
  uint32_t *appVersionStoragePtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY);

  if (!bootload_checkApplicationPropertiesMagic(appProperties)) {
    return false;
  }
  if (!bootload_checkApplicationPropertiesVersion(appProperties)) {
    return false;
  }

  if (checkMaxVersionMagic()) {
    // The highest allowed version is seen, which is the maximum version allowed
    // so we do not need to remember any new application versions.
    return true;
  }
  if (*appVersionStoragePtr != SL_GBL_UINT32_MAX_NUMBER) {
    return false;
  }
  if (highestVersionSeen == appVersion) {
    // Do not need to store a new version.
    return true;
  }

  if (appVersion == SL_GBL_UINT32_MAX_NUMBER) {
    appVersion = SL_GBL_APPLICATION_VERSION_MAX_MAGIC;
    // Return true eventhough the flash pages are locked to avoid bricking devices.
    (void)flash_writeBuffer_dma((uint32_t)appVersionStoragePtr, &appVersion, 4UL, SL_GBL_MSC_LDMA_CHANNEL);
    return true;
  }

  // The application that is about to boot has a higher version than the highest seen version.
  // However, this version can't be stored, so do not allow the application to boot to prevent
  // downgrade later. This will "never" happen as the number of empty slots is checked before getting to this point.
  // Unless the slots are already filled for some unexpected reason.
  if (emptySlots == 0UL) {
    return false;
  }

  appVersionStoragePtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY - emptySlots);
  (void)flash_writeBuffer_dma((uint32_t)appVersionStoragePtr, &appVersion, 4UL, SL_GBL_MSC_LDMA_CHANNEL);
  return true;
#else
  (void)startAddress;
  return false;
#endif
}

bool bootload_verifyApplicationVersion(uint32_t appVersion, bool checkRemainingAppUpgrades) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  uint32_t highestVersionSeen = getHighestApplicationVersionSeen();

  // Check for the minimum application version that should be allowed.
  if (parser_applicationMinimumVersionValid() > appVersion) {
    return false;
  }
  if (highestVersionSeen > appVersion) {
    return false;
  }

  // Application version is higher/equal than the saved application versions.
  // Check if we have empty spaces left for storing new application versions.
  if ((appVersion > highestVersionSeen) && checkRemainingAppUpgrades) {
    // The new application version needs to be stored, check we have empty spaces left.
    if (bootload_remainingApplicationUpgrades() == 0UL) {
      return false;
    }
  }

  return true;
#else
  (void)appVersion;
  (void)checkRemainingAppUpgrades;
  return false;
#endif
}

uint32_t bootload_remainingApplicationUpgrades(void) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  uint32_t *appVersionStoragePtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY);
  if (checkMaxVersionMagic()) {
    return 0UL;
  }

  for (uint32_t i = 0UL; i < SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY; i++) {
    appVersionStoragePtr = bootload_getApplicationVersionStoragePtr(i);
    if (*appVersionStoragePtr == SL_GBL_UINT32_MAX_NUMBER) {
      return (SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY - i);
    }
  }

  return 0UL;
#else
  return 0UL;
#endif
}

void bootload_storeApplicationVersionResetMagic(void) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  uint32_t *appVersionResetPtr = bootload_getApplicationVersionStoragePtr(bootload_getApplicationVersionStorageCapacity() + 1UL);
  uint32_t appVersionResetMagic = SL_GBL_APPLICATION_VERSION_RESET_MAGIC;
  (void)flash_writeBuffer_dma((uint32_t)appVersionResetPtr, &appVersionResetMagic, 4UL, SL_GBL_MSC_LDMA_CHANNEL);
#else
  return;
#endif
}

void bootload_removeStoredApplicationVersions(void) {
#if defined(BOOTLOADER_ROLLBACK_PROTECTION)
  uint32_t *appVersionResetPtr = bootload_getApplicationVersionStoragePtr(SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY + 1UL);
  if ((bootload_remainingApplicationUpgrades() < SL_GBL_APPLICATION_VERSION_STORAGE_CAPACITY)
      && checkResetMagic()) {
    // Not empty and reset requested.
    uint32_t versionStorageAddr = ((uint32_t)appVersionResetPtr / FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
    (void)flash_erasePage(versionStorageAddr);
  }
#else
  return;
#endif
}

bool bootload_gotCertificate(void *appProp)
{
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
  if (appProp == NULL) {
    return false;
  }

  ApplicationProperties_t *appProperties = (ApplicationProperties_t *)(appProp);
  // Compatibility check of the application properties struct.
  // The application properties struct with the major version 0
  // does not contain the certificate struct.
  if (((appProperties->structVersion & APPLICATION_PROPERTIES_VERSION_MAJOR_MASK)
       >> APPLICATION_PROPERTIES_VERSION_MAJOR_SHIFT) < 1UL) {
    return false;
  }

  if (((appProperties->structVersion & APPLICATION_PROPERTIES_VERSION_MINOR_MASK)
       >> APPLICATION_PROPERTIES_VERSION_MINOR_SHIFT) < 1UL) {
    return false;
  }

  if (appProperties->cert == NULL) {
    return false;
  }

  return true;
#else
  (void)appProp;
  return false;
#endif
}

bool bootload_verifyCertificate(void *cert) {
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
  if (cert == NULL) {
    return false;
  }
  ApplicationCertificate_t *appCertificate = (ApplicationCertificate_t *)(cert);

  volatile int32_t retVal = BOOTLOADER_ERROR_SECURITY_REJECTED;
  Sha256Context_t shaState;

  // Access word 13 to read sl_app_properties of the bootloader.
  ApplicationProperties_t *blProperties =
    (ApplicationProperties_t *)(*(uint32_t *)(BTL_MAIN_STAGE_BASE + 52UL));
  if (!bootload_checkApplicationPropertiesMagic(blProperties)) {
    return false;
  }
#if !defined(MAIN_BOOTLOADER_TEST)
  if ((uint32_t)blProperties > (BTL_APPLICATION_BASE - sizeof(ApplicationProperties_t))) {
    // Make sure that this pointer is within the bootloader space.
    return false;
  }
#endif

  // Application cert version need to be higher or equal than
  // the running bootloader version.
  if (blProperties->cert->version > appCertificate->version) {
    return false;
  } else {
    // Check ECDSA signing.
    btl_initSha256(&shaState);
    btl_updateSha256(&shaState,
                     (const uint8_t*)appCertificate,
                     72U);
    btl_finalizeSha256(&shaState);

    // Use the public key stored in bootloader certificate
    // to verify the certificate. The bootloader cerfiticate
    // has been validated by SE.
    retVal = btl_verifyEcdsaP256r1(shaState.sha,
                                   &(appCertificate->signature[0]),
                                   &(appCertificate->signature[32]),
                                   &(blProperties->cert->key[0]),
                                   &(blProperties->cert->key[32]));
    if (retVal != BOOTLOADER_OK) {
      return false;
    }
    return true;
  }
#else
  (void)cert;
  return false;
#endif
}

bool bootload_verifyApplicationCertificate(void *appProp, void *gotCert) {
#if defined(BOOTLOADER_SUPPORT_CERTIFICATES)
  ApplicationProperties_t *appProperties = (ApplicationProperties_t *)(appProp);
  bool *gotCertificate = (bool *)gotCert;
  *gotCertificate = bootload_gotCertificate(appProperties);
  if (*gotCertificate) {
    // Validate Cert
    if (!bootload_verifyCertificate(appProperties->cert)) {
      // Cert found, but it contains an invalid signature.
      return false;
    }
  }
#if defined(BOOTLOADER_REJECT_DIRECT_SIGNED_IMG)
  else {
    return false;
  }
#endif
  return true;
#else
  (void)appProp;
  (void)gotCert;
  return true;
#endif
}
