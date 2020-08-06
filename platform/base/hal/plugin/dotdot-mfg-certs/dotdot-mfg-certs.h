/***************************************************************************//**
 * @file dotdot-mfg-certs.h
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
#ifndef __DOTDOT_MFG_CERTS_H__
#define __DOTDOT_MFG_CERTS_H__

#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "stack/include/error.h"
#include "hal/hal.h"
#include "hal/plugin/serial/serial.h"

#define LONG_TOKEN_HEADER_SIZE sizeof(DotdotPageHeader)

// Magic header value, should not use any assembler instructions
#define LONG_TOKEN_MAGIC_SIZE 4
#define LONG_TOKEN_MAGIC_HEADER 0xE830EB7EU

#define DOTDOT_DEVICE_KEY_TAG   0x01
#define DOTDOT_DEVICE_CERT_TAG  0x02
#define DOTDOT_CA_CHAIN_TAG     0x03
#define DOTDOT_CA_CERT_TAG      0x04

#define LONG_TOKEN_VERSION_NUMBER 1

#define MAX_NUMBER_OF_CA_CERTS 3

// Structs for Dotdot Security
typedef struct {
  uint8_t deviceKeyTag;
  uint16_t deviceKeyLength;
  uint8_t *deviceKeyPayload;
} dotdot_device_key;

typedef struct {
  uint8_t deviceCertTag;
  uint16_t deviceCertLength;
  uint8_t *deviceCertPayload;
} dotdot_device_cert;

typedef struct {
  uint8_t caChainTag;
  uint16_t caChainLength;
  uint8_t *caChainPayload;
} dotdot_ca_cert_chain;

typedef struct {
  uint8_t caCertTag;
  uint16_t caCertLength;
  uint8_t *caCertPayload;
} dotdot_ca_cert;

typedef enum {
  DEVICE_KEY,
  DEVICE_CERT,
  CA_CHAIN,
  CA_CERT
} DotdotCertType;

// This will hold the magic header value and version number
typedef struct {
  uint32_t magic;
  uint16_t version;
} DotdotPageHeader;

// This function will retrieve a specific cert in the block of certs
// The cert number is only used for the CA Cert chain, and is indexed from 0.
uint8_t halDotdotMfgCertsGetCertData(uint8_t certNumber, void *data, DotdotCertType type);

// This function will grab all of the data from all of the certs in the CA Chain
// and create one block of them, end to end.
EmberStatus halDotdotMfgCertsGetCaChainData(void *data);

// This function will be called by the bookkeeping to initialize the certificate pointers.
void halDotdotMfgCertsInit(void);
EmberStatus initCertPointers(void);

// Global
extern uint8_t *longTokenAddress;
// Device Key
extern uint8_t   *dotdotDeviceKeyPtr; // pointer to the start of the device key
extern uint16_t  dotdotDeviceKeySize; // size of the device key in bytes
// Device Cert
extern uint8_t   *dotdotDeviceCertPtr; // pointer to the start of the device cert
extern uint16_t  dotdotDeviceCertSize; // size of the device cert in bytes
// Ca Cert Chain
extern uint8_t   *dotdotCaChainPtr; // the pointer to the head of the block
extern uint16_t  dotdotCaChainSize; // This holds the size of the entire chain block
extern uint8_t   dotdotCaChainLength; // this holds the number of certs in the ca chain

#endif // __DOTDOT_MFG_CERTS_H__
