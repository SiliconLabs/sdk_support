/***************************************************************************//**
 * @file
 * @brief AES decryption functionality for Silicon Labs bootloader
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
#ifndef BTL_SECURITY_TYPES_H
#define BTL_SECURITY_TYPES_H

#include "core/btl_util.h"

MISRAC_DISABLE
#include "mbedtls/aes.h"
#include "mbedtls/sha256.h"
MISRAC_ENABLE

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup Security
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup AES
 * @{
 ******************************************************************************/

/// Context variable type for AES-ECB
typedef struct AesContext {
  mbedtls_aes_context   aesContext;       ///< mbedTLS AES context
} AesContext_t;

/// Context variable type for AES-CTR (and AES-CCM)
typedef struct AesCtrContext {
  mbedtls_aes_context   aesContext;       ///< mbedTLS AES context
  size_t                offsetInBlock;    ///< @brief Position in block of last
                                          ///< byte en/decrypted
  uint8_t               streamBlock[16];  ///< Current CTR encrypted block
  uint8_t               counter[16];      ///< Current counter/CCM value
} AesCtrContext_t;

/** @} addtogroup AES */

/***************************************************************************//**
 * @addtogroup SHA_256
 * @{
 ******************************************************************************/

/// Context type for SHA algorithm
typedef union Sha256Context {
  mbedtls_sha256_context  shaContext;       ///< mbedTLS SHA256 context struct
  uint8_t                 sha[32];          ///< resulting SHA hash
} Sha256Context_t;

/** @} addtogroup SHA_256 */

/***************************************************************************//**
 * @addtogroup Decryption
 * @{
 * @brief Generic decryption functionality for bootloader
 * @details
 ******************************************************************************/

/// Generic decryption context
typedef union {
  AesCtrContext_t aesCtr; ///< Context for AES-CTR-128 decryption
} DecryptContext_t;

/// Generic authentication context
typedef union {
  Sha256Context_t sha256; ///< Context for SHA-256 digest
} AuthContext_t;

/** @} addtogroup Decryption */

/** @} addtogroup Security */
/** @} addtogroup Plugin */

#endif // BTL_SECURITY_TYPES_H
