/***************************************************************************//**
 * @file dotdot-mfg-certs.c
 * @brief Dotdot MFG Certificates HAL APIs
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

// NOTE: These functions and metadata expect an x509 certificate.

#include PLATFORM_HEADER
#if defined(CONFIGURATION_HEADER)
  #include CONFIGURATION_HEADER
#endif
#include EMBER_AF_API_HAL
#include EMBER_AF_API_STACK

#include "stack/include/ember.h"
#include "stack/include/ember-types.h"
#include "stack/core/ember-stack.h"
#include "stack/include/error.h"
#include "hal/hal.h"
#include "hal/plugin/serial/serial.h"
#include "dotdot-mfg-certs.h"
#include "hal/micro/cortexm3/efm32/long-token.h"
#include "hal/micro/bootloader-interface.h"

// Device Key
uint8_t   *dotdotDeviceKeyPtr = NULL; // pointer to the start of the device key
uint16_t  dotdotDeviceKeySize = 0xFFFF; // size of the device key in bytes
// Device Cert
uint8_t   *dotdotDeviceCertPtr = NULL; // pointer to the start of the device cert
uint16_t  dotdotDeviceCertSize = 0xFFFF; // size of the device cert in bytes
// Ca Cert Chain
uint8_t   *dotdotCaChainPtr = NULL; // the pointer to the head of the block
uint16_t  dotdotCaChainSize = 0xFFFF; // This holds the size of the entire chain block
uint8_t   dotdotCaChainLength = 0xFF; // this holds the number of certs in the ca chain

#ifndef UNIX
// If we can, we will initialize the pointers. This means that the section has
// been flashed previously. If not, we will just write the magic header and
// version and let the certificate pointers get initialized later.
void halDotdotMfgCertsInit(void)
{
  EmberStatus result;
  DotdotPageHeader header;
  result = halCommonGetLongTokenData(&header, longTokenAddress, sizeof(DotdotPageHeader));
  if (result != EMBER_SUCCESS) {
    emberSerialPrintf(APP_SERIAL, "Dotdot MFG Cert header not read correctly!\n");
    return;
  }

  if (header.magic != LONG_TOKEN_MAGIC_HEADER) {
    emberSerialPrintf(APP_SERIAL, "Magic header not found!\n");
  } else {
    // The magic header is found so lets reset the pointers
    result = initCertPointers();
    if (result != EMBER_SUCCESS) {
      emberSerialPrintf(APP_SERIAL, "Dotdot MFG Cert pointers not set correctly!\n");
      dotdotDeviceKeySize = 0xFFFF;
      dotdotDeviceCertSize = 0xFFFF;
      dotdotCaChainSize = 0xFFFF;
    }
  }
}

EmberStatus initCertPointers(void)
{
  DotdotPageHeader header;
  EmberStatus result;
  result = halCommonGetLongTokenData(&header, longTokenAddress, sizeof(DotdotPageHeader));

  if (result != EMBER_SUCCESS) {
    emberSerialPrintf(APP_SERIAL, "Dotdot MFG Cert header not read correctly!\n");
    return result;
  }

  if (header.magic != LONG_TOKEN_MAGIC_HEADER) {
    emberSerialPrintf(APP_SERIAL, "header.magic = %4x\n", header.magic);
    emberSerialPrintf(APP_SERIAL, "Magic Header is corrupt!\n");
    return EMBER_ERR_FATAL;
  }

  if (header.version != LONG_TOKEN_VERSION_NUMBER) {
    emberSerialPrintf(APP_SERIAL, "Version number is %d\n", header.version);
    emberSerialPrintf(APP_SERIAL, "Version of section is incorrect!\n");
    return EMBER_ERR_FATAL;
  }

  // Start the pointer at the tag of the device key
  uint8_t *ptr = ((uint8_t *)longTokenAddress);
  ptr += 6;
  uint8_t tag = 0;
  uint16_t length = 0;
  uint16_t lengthSwapped = 0;
  uint16_t totalBytes = sizeof(DotdotPageHeader);
  uint8_t i;

  // Set the pointers for the 3 different pieces of Dotdot Security
  for (i = 1; i < 4; i++) {
    halCommonGetLongTokenData(&tag, ptr, 1);
    if (result != EMBER_SUCCESS) {
      emberSerialPrintf(APP_SERIAL, "Tag not read correctly!\n");
      return result;
    }
    ptr += 1;
    halCommonGetLongTokenData(&length, ptr, 2);
    if (result != EMBER_SUCCESS) {
      emberSerialPrintf(APP_SERIAL, "Length not read correctly!\n");
      return result;
    }
    lengthSwapped = (length >> 8) | (length << 8);
    ptr += 2;
    totalBytes += 3;
    switch (tag) {
      case DOTDOT_DEVICE_KEY_TAG: {
        dotdotDeviceKeyPtr = ptr; // start of the payload
        dotdotDeviceKeySize = lengthSwapped;
        emberSerialPrintf(APP_SERIAL, "Device Key Length = %2x %d\n", lengthSwapped, lengthSwapped);
        break;
      }
      case DOTDOT_DEVICE_CERT_TAG: {
        dotdotDeviceCertPtr = ptr; // start of the payload
        dotdotDeviceCertSize = lengthSwapped;
        emberSerialPrintf(APP_SERIAL, "Device Cert Length = %2x %d\n", lengthSwapped, lengthSwapped);
        break;
      }
      case DOTDOT_CA_CHAIN_TAG: {
        // In this case, the pointer will point to the first cert length so that the lengths
        // can be iterated over more easily
        dotdotCaChainPtr = ptr;
        dotdotCaChainSize = lengthSwapped;
        emberSerialPrintf(APP_SERIAL, "CA Chain Length = %2x %d\n", lengthSwapped, lengthSwapped);
        break;
      }
      default: {
        emberSerialPrintf(APP_SERIAL, "Tag = %d\n", tag);
        emberSerialPrintf(APP_SERIAL, "Tag did not match any of the structs!\n");
        return EMBER_ERR_FATAL;
      }
    }
    // Move to the end of the current cert
    ptr += lengthSwapped;

    // Check to make sure that we are not past the end of the block before going on
    totalBytes += lengthSwapped;
    if (((totalBytes & 1) == 1) && (tag == DOTDOT_CA_CHAIN_TAG)) {
      // The length is odd and need to add in padding for a byte that would have been
      // added at the end.
      ptr++;
      totalBytes++;
    }

    if (totalBytes > 4095) {
      emberSerialPrintf(APP_SERIAL, "totalBytes = %d\n", totalBytes);
      emberSerialPrintf(APP_SERIAL, "The current cert extends past the end of the block\n");
      return EMBER_ERR_FATAL;
    }
  }

  emberSerialPrintf(APP_SERIAL, "Dotdot Secruity pointers have been set.\n");
  return EMBER_SUCCESS;
}

// In order to save RAM space, we don't want to retreive the entire 4096 byte block
// This function will retrieve a specific cert in the block of certs
// We will have to special case the internal get functions to use the index as an offset
uint8_t halDotdotMfgCertsGetCertData(uint8_t certNumber, void *data, DotdotCertType type)
{
  EmberStatus status = EMBER_ERR_FATAL;

  // Check to make sure that the pointers have been initialized
  if ((dotdotDeviceCertSize == 0xFFFF) || (dotdotDeviceKeySize == 0xFFFF)) {
    status = initCertPointers();
    if (status == EMBER_ERR_FATAL) {
      emberSerialPrintf(APP_SERIAL, "Error in initializing the pointers\n");
      return status;
    }
  }

  // Check to make sure the location is page aligned
  if (((size_t)longTokenAddress % FLASH_PAGE_SIZE) != 0U) {
    emberSerialPrintf(APP_SERIAL, "Long token memory section is not page aligned\n");
    return EMBER_ERR_FATAL;
  }

  // Check the header and version
  DotdotPageHeader header;
  status = halCommonGetLongTokenData(&header, longTokenAddress, sizeof(DotdotPageHeader));
  if (status != EMBER_SUCCESS) {
    emberSerialPrintf(APP_SERIAL, "Dotdot MFG Cert pointers not set correctly!\n");
    return status;
  }

  if (header.magic != LONG_TOKEN_MAGIC_HEADER) {
    emberSerialPrintf(APP_SERIAL, "The section is uninitialized or corrupt! Please flash with commander\n");
    return EMBER_ERR_FATAL;
  } else if (header.version != 1) {
    emberSerialPrintf(APP_SERIAL, "The section version is incorrect. Please check version, and reflash with commander\n");
    return EMBER_ERR_FATAL;
  }

  // Grab the data for the requested certificate
  switch (type) {
    case DEVICE_KEY: {
      dotdot_device_key key = { 0 };
      key.deviceKeyTag = DOTDOT_DEVICE_KEY_TAG;
      key.deviceKeyLength = dotdotDeviceKeySize;
      key.deviceKeyPayload = dotdotDeviceKeyPtr;
      MEMCOPY(data, &key, sizeof(dotdot_device_key));
      break;
    }
    case DEVICE_CERT: {
      dotdot_device_cert cert = { 0 };
      cert.deviceCertTag = DOTDOT_DEVICE_CERT_TAG;
      cert.deviceCertLength = dotdotDeviceCertSize;
      cert.deviceCertPayload = dotdotDeviceCertPtr;
      MEMCOPY(data, &cert, sizeof(dotdot_device_cert));
      break;
    }
    case CA_CERT: {
      dotdot_ca_cert caCert = { 0 };
      // This will grab a single cert from the chain
      uint8_t i;
      uint16_t length = 0;
      uint8_t *ptr = dotdotCaChainPtr;
      uint8_t *certPtr = (dotdotCaChainPtr + 6);
      // The lengths of each of the three certs are stored in order at the beginning
      // of the ca chain payload. So if we are looking for the root certificate,
      // the length will be in the two bytes at the address pointed to by dotdotCaChainPtr, and so on.
      uint16_t lengthSwapped = 0;
      for (i = 0; i < certNumber; i++) {
        // Move the pointer to the cert to the start of the appropriate cert
        status = halCommonGetLongTokenData(&length, ptr, 2);
        if (status != EMBER_SUCCESS) {
          emberSerialPrintf(APP_SERIAL, "Length not read correctly!\n");
          return status;
        }
        ptr += 2; // Move to the next length bytes
        lengthSwapped = (length >> 8) | (length << 8);
        certPtr += lengthSwapped; // Moving to the start of the next cert
      }

      // Finally, get the length of the cert we want
      status = halCommonGetLongTokenData(&length, ptr, 2);
      if (status != EMBER_SUCCESS) {
        emberSerialPrintf(APP_SERIAL, "Length not read correctly!\n");
        return status;
      }
      lengthSwapped = (length >> 8) | (length << 8);

      caCert.caCertTag = DOTDOT_CA_CERT_TAG;
      caCert.caCertLength = lengthSwapped;
      caCert.caCertPayload = certPtr;

      MEMCOPY(data, &caCert, sizeof(dotdot_ca_cert));
      break;
    }
    case CA_CHAIN: {
      // This will grab the entire chain with the lengths
      dotdot_ca_cert_chain chain = { 0 };
      chain.caChainTag = DOTDOT_CA_CHAIN_TAG;
      chain.caChainLength = dotdotCaChainSize;
      chain.caChainPayload = dotdotCaChainPtr;
      MEMCOPY(data, &chain, sizeof(dotdot_ca_cert_chain));
      break;
    }
    default: {
      emberSerialPrintf(APP_SERIAL, "The type of cert requested is incorrect.\n");
      return EMBER_ERR_FATAL;
    }
  }
  return EMBER_SUCCESS;
}

// This function will get all of the CA Chain Certs and create a block
// of the certs, placed end to end. Then copy this to the given location.
EmberStatus halDotdotMfgCertsGetCaChainData(void *data)
{
  dotdot_ca_cert_chain chain = { 0 };
  chain.caChainTag = DOTDOT_CA_CHAIN_TAG;
  chain.caChainLength = (dotdotCaChainSize - 6);
  chain.caChainPayload = (dotdotCaChainPtr + 6);
  MEMCOPY(data, &chain, sizeof(dotdot_ca_cert_chain));
  return EMBER_SUCCESS;
}

#else
void halDotdotMfgCertsInit(void)
{
}
#endif // UNIX
