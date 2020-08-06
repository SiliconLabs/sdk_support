/***************************************************************************//**
 * @file
 * @brief Definitions for the Silicon Labs GBL format
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
#ifndef BTL_GBL_FORMAT_H
#define BTL_GBL_FORMAT_H

#include <stdint.h>
#include "api/application_properties.h"

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup ImageParser Image Parser
 * @{
 * @addtogroup EblParser GBL Parser
 * @{
 * @addtogroup EblParserFormat GBL Format
 * @{
 ******************************************************************************/

// -------------------------------
// Structs

/// GBL tag header. Must be the first element in all GBL tags.
typedef struct {
  uint32_t  tagId;            ///< Tag ID
  uint32_t  length;           ///< Length (in bytes) of the rest of the tag
} EblTagHeader_t;

/// GBL header tag type.
typedef struct {
  EblTagHeader_t header;      ///< Tag ID and length
  uint32_t       version;     ///< Version of the GBL spec used in this file
  uint32_t       type;        ///< Type of GBL
} EblHeader_t;

/// GBL application tag type.
typedef struct {
  EblTagHeader_t    header;   ///< Tag ID and length
  ApplicationData_t appInfo;  ///< Information about the application
} EblApplication_t;

/// GBL bootloader tag type.
typedef struct {
  EblTagHeader_t header;             ///< Tag ID and length
  uint32_t       bootloaderVersion;  ///< Version number of the bootloader
  uint32_t       address;            ///< Address of the bootloader
  uint8_t        *data;              ///< Array of data for bootloader upgrade
} EblBootloader_t;

/// GBL SE upgrade tag type.
typedef struct {
  EblTagHeader_t header;             ///< Tag ID and length
  uint32_t       blobSize;           ///< Size of the SE upgrade blob
  uint32_t       version;            ///< Version of the SE image
  uint8_t        *data;              ///< Array of data for SE upgrade
} EblSeUpgrade_t;

/// GBL metadata tag type.
typedef struct {
  EblTagHeader_t header;      ///< Tag ID and length
  uint8_t        *metaData;   ///< Array of metadata
} EblMetadata_t;

/// GBL flash program tag type.
typedef struct {
  EblTagHeader_t header;            ///< Tag ID and length
  uint32_t       flashStartAddress; ///< Address to start flashing
  uint8_t        *data;             ///< Array of data to flash
} EblProg_t;

/// GBL end tag type.
typedef struct {
  EblTagHeader_t header;      ///< Tag ID and length
  uint32_t       eblCrc;      ///< CRC32 of the entire GBL file.
} EblEnd_t;

/// GBL encryption header tag type.
typedef struct {
  EblTagHeader_t header;          ///< Tag ID and length
  uint32_t       version;         ///< Version of the GBL spec used in this file
  uint32_t       magicWord;       ///< Magic word (GBL_IMAGE_MAGIC_WORD)
  uint32_t       encryptionType;  ///< Type of encryption used. 1 = AES-CTR
} EblEncryptionHeader_t;

/// GBL encryption init tag type. Used with AES-CCM encryption.
typedef struct {
  EblTagHeader_t header;      ///< Tag ID and length
  uint32_t       msgLen;      ///< Length of the cipher text in bytes
  uint8_t        nonce[12];   ///< @brief Random nonce used for AES-CTR in
                              ///< this message
} EblEncryptionInitAesCcm_t;

/// GBL encryption data tag type.
typedef struct {
  EblTagHeader_t header;            ///< Tag ID and length
  uint8_t        *encryptedEblData; ///< @brief Encrypted data
                                    ///< @details After decryption, this data
                                    ///< must represent one or more complete
                                    ///< unencrypted GBL tags.
} EblEncryptionData_t;

/// @brief GBL encryption AES-CCM MAC tag type.
/// @deprecated This tag is deprecated. Use ECDSA instead for signature.
typedef struct {
  EblTagHeader_t header;      ///< Tag ID and length
  uint8_t        eblMac[16];  ///< AES-CCM MAC
} EblEncryptionAesCcmSignature_t;

/// GBL certificate chain for signing
typedef struct {
  EblTagHeader_t header;                ///< Tag ID and length
  ApplicationCertificate_t certificate; ///< Certificate used to verify GBL
} EblCertificateEcdsaP256_t;

/// GBL ECDSA secp256r1 signature tag type.
typedef struct {
  EblTagHeader_t header;  ///< Tag ID and length
  uint8_t        r[32];   ///< R-point of ECDSA secp256r1 signature
  uint8_t        s[32];   ///< S-point of ECDSA secp256r1 signature
} EblSignatureEcdsaP256_t;

/** @} addtogroup EblParserFormat */
/** @} addtogroup EblParser */
/** @} addtogroup ImageParser */
/** @} addtogroup Plugin */

#endif // BTL_GBL_FORMAT_H
