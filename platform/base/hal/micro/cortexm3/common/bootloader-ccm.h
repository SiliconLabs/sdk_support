/***************************************************************************//**
 * @file
 * @brief This file contains the definitions to various CCM encryption functions
 * used in the secure bootloader.
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
#ifndef BOOTLOADER_CCM_H
#define BOOTLOADER_CCM_H

// Length defines
#define NONCE_LENGTH (12)
#define COUNTER_LENGTH (3)
#define MAC_LENGTH (16)
#define SECURITY_BLOCK_SIZE 16
#define PAYLOAD_SIZE_BYTES 3   // Number of bytes used to hold the payload size

// Offsets of various bits of CCM data after formatting
#define CCM_FLAGS_INDEX (0)
#define CCM_NONCE_INDEX (1)
#define CCM_COUNTER_INDEX (CCM_NONCE_INDEX + NONCE_LENGTH)

// The CCM state struct holds all configuration information needed to
// decrypt and validate a CCM message.
typedef struct ccmState_s {
  uint32_t msgLen;                     /* Length of the encrypted data */
  uint8_t nonce[NONCE_LENGTH];         /* The random nonce for this message */
  uint8_t mac[SECURITY_BLOCK_SIZE];    /* The full rolling MAC value */
  uint32_t blockCount;                 /* Current AES block we're processing in this message */
  uint8_t blockOffset;                 /* Offset within the current AES block [0, SECURITY_BLOCK_SIZE] */
  uint8_t macOffset;                   /* Last byte written to in the MAC buffer */
} ccmState_t;

// Initialize the CCM state structure
void initCcmState(ccmState_t *ccmState);

// Verify that the secure bootloader key is set and accessbile
bool validateSecureBootloaderKey(void);

// Functions for creating the MAC
void initCcmMac(ccmState_t *ccmState, uint32_t aDataLen);
void updateCcmMac(ccmState_t *ccmState, uint8_t *data, uint32_t len);
void finalizeCcmMac(ccmState_t *ccmState);
bool verifyCcmMac(ccmState_t *ccmState, uint8_t *mac, uint8_t macLen);
void encryptDecryptCcmMac(ccmState_t *ccmState, uint8_t *mac);

// Define functions for authenticating unencrypted data. In CCM these
// are really just updating the MAC and finalizing, but use these names
// to make porting easier in the future
#define processAssociatedData updateCcmMac
#define finalizeAssociatedData finalizeCcmMac

// Counter mode decrypt functions
void decryptCcmBlock(ccmState_t *ccmState, uint8_t *data, uint32_t len);

#endif // BOOTLOADER_CCM_H
