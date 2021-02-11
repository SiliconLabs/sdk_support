/***************************************************************************//**
 * # License
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 *
 ******************************************************************************/
/*
 *  NIST SP800-38C compliant CCM implementation
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include "em_device.h"

#if defined(CRYPTO_PRESENT)

#include "sli_crypto_transparent_types.h"
#include "sli_crypto_transparent_functions.h"
#include "sli_psa_driver_common.h"
#include "crypto_management.h"
// Replace inclusion of psa/crypto_xxx.h with the new psa driver commong
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"
#include "em_crypto.h"
#include "em_core.h"
#include <string.h>

#ifndef PSA_AEAD_TAG_MAX_SIZE
// TODO: Remove when macro has been added to the core
#define PSA_AEAD_TAG_MAX_SIZE 16
#endif

/*
 * ccm_auth_crypt has been taken from mbed TLS and adapted to use the
 * CRYPTO accelerator, hence the above copyright notice.
 */
static psa_status_t ccm_auth_crypt(const unsigned char *key_buffer, size_t key_buffer_size,
                                   psa_encrypt_or_decrypt_t mode, size_t length,
                                   const unsigned char *iv, size_t iv_len,
                                   const unsigned char *add, size_t add_len,
                                   const unsigned char *input, unsigned char *output,
                                   unsigned char *tag, size_t tag_len);

static psa_status_t sli_gcm_crypt_and_tag(sli_crypto_transparent_aead_operation_t *operation,
                                          psa_encrypt_or_decrypt_t mode,
                                          size_t length,
                                          const unsigned char *iv,
                                          size_t iv_len,
                                          const unsigned char *add,
                                          size_t add_len,
                                          const unsigned char *input,
                                          unsigned char *output,
                                          size_t tag_len,
                                          unsigned char *tag);

static psa_status_t check_aead_parameters(psa_algorithm_t alg,
                                          size_t nonce_length)
{
  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);

  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      if (tag_length == 0 || tag_length == 2 || tag_length > 16 || tag_length % 2 != 0 || nonce_length < 7 || nonce_length > 13) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):
      if (tag_length > 16 || tag_length < 4 || nonce_length != 12) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  return PSA_SUCCESS;
}

psa_status_t sli_crypto_transparent_aead_encrypt(const psa_key_attributes_t *attributes,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 psa_algorithm_t alg,
                                                 const uint8_t *nonce,
                                                 size_t nonce_length,
                                                 const uint8_t *additional_data,
                                                 size_t additional_data_length,
                                                 const uint8_t *plaintext,
                                                 size_t plaintext_length,
                                                 uint8_t *ciphertext,
                                                 size_t ciphertext_size,
                                                 size_t *ciphertext_length)
{
  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);
  size_t key_length = psa_get_key_bits(attributes) / 8;

  if (key_buffer == NULL
      || attributes == NULL
      || nonce == NULL
      || (additional_data == NULL && additional_data_length > 0)
      || (plaintext == NULL && plaintext_length > 0)
      || (plaintext_length > 0 && (ciphertext == NULL || ciphertext_size == 0))
      || ciphertext_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  int status = -1;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  // Verify that the driver supports the given parameters
  psa_status = check_aead_parameters(alg, nonce_length);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Check that the supplied key is valid
  switch (key_length) {
    case 16U:
    case 32U:
      if (key_buffer_size < key_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    case 24U:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((ciphertext > plaintext) && (ciphertext < (plaintext + plaintext_length))) {
    // Sanity check before copying.
    if (ciphertext_size < plaintext_length) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    memmove(ciphertext, plaintext, plaintext_length);
    plaintext = ciphertext;
  }

  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      // Verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      status = ccm_auth_crypt(key_buffer,
                              key_buffer_size,
                              PSA_CRYPTO_DRIVER_ENCRYPT,
                              plaintext_length,
                              nonce,
                              nonce_length,
                              additional_data,
                              additional_data_length,
                              plaintext,
                              ciphertext,
                              &ciphertext[plaintext_length],
                              tag_length);

      if (status == PSA_SUCCESS) {
        *ciphertext_length = plaintext_length + tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0): {
      // Verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Populate the operation struct directly until we have implemented
      // the multi-part functions
      sli_crypto_transparent_aead_operation_t operation = { 0 };
      operation.key_len = key_length;
      memcpy(operation.key, key_buffer, key_length);

      status = sli_gcm_crypt_and_tag(&operation,
                                     PSA_CRYPTO_DRIVER_ENCRYPT,
                                     plaintext_length,
                                     nonce,
                                     nonce_length,
                                     additional_data,
                                     additional_data_length,
                                     plaintext,
                                     ciphertext,
                                     tag_length,
                                     &ciphertext[plaintext_length]);

      sli_psa_zeroize(&operation, sizeof(operation));

      if (status == PSA_SUCCESS) {
        *ciphertext_length = plaintext_length + tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    }
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return psa_status;
}

psa_status_t sli_crypto_transparent_aead_decrypt(const psa_key_attributes_t *attributes,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 psa_algorithm_t alg,
                                                 const uint8_t *nonce,
                                                 size_t nonce_length,
                                                 const uint8_t *additional_data,
                                                 size_t additional_data_length,
                                                 const uint8_t *ciphertext,
                                                 size_t ciphertext_length,
                                                 uint8_t *plaintext,
                                                 size_t plaintext_size,
                                                 size_t *plaintext_length)
{
  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);
  size_t key_length = psa_get_key_bits(attributes) / 8;

  if (key_buffer == NULL
      || attributes == NULL
      || nonce == NULL
      || (additional_data == NULL && additional_data_length > 0)
      || (ciphertext == NULL && ciphertext_length > 0)
      || (ciphertext_length > tag_length && (plaintext == NULL || plaintext_size == 0))
      || ciphertext_length == 0
      || ciphertext_length < tag_length) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  int status = -1;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  // Verify that the driver supports the given parameters
  psa_status = check_aead_parameters(alg, nonce_length);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Check that the supplied key is valid
  switch (key_length) {
    case 16U:
    case 32U:
      if (key_buffer_size < key_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    case 24U:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  // We have to copy the tag before the potential mmemove below
  uint8_t check_tag[PSA_AEAD_TAG_MAX_SIZE];
  memcpy(check_tag, &ciphertext[ciphertext_length - tag_length], tag_length);

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((plaintext > ciphertext) && (plaintext < (ciphertext + ciphertext_length))) {
    // Sanity check before copying.
    if (plaintext_size < (ciphertext_length - tag_length)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    memmove(plaintext, ciphertext, ciphertext_length - tag_length);
    ciphertext = plaintext;
  }

  uint8_t tag[16];
  uint32_t diff = 0;

  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      // Verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Check sufficient output buffer size
      if (plaintext_size < ciphertext_length - tag_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = ccm_auth_crypt(key_buffer,
                              key_buffer_size,
                              PSA_CRYPTO_DRIVER_DECRYPT,
                              ciphertext_length - tag_length,
                              nonce,
                              nonce_length,
                              additional_data,
                              additional_data_length,
                              ciphertext,
                              plaintext,
                              tag,
                              tag_length);

      if (status != PSA_SUCCESS) {
        *plaintext_length = 0;
        memset(plaintext, 0, ciphertext_length - tag_length);
        return status;
      }

      // Check that the provided tag equals the calculated one
      // (in constant time). Note that the tag returned by ccm_auth_crypt
      // is encrypted, so we don't have to decrypt check_tag.
      diff = 0;
      for (uint32_t i = 0; i < tag_length; ++i) {
        diff |= tag[i] ^ check_tag[i];
      }

      if (diff != 0) {
        *plaintext_length = 0;
        memset(plaintext, 0, ciphertext_length - tag_length);
        return PSA_ERROR_INVALID_SIGNATURE;
      }

      if (status == PSA_SUCCESS) {
        *plaintext_length = ciphertext_length - tag_length;
        psa_status = PSA_SUCCESS;;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0): {
      // Verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Populate the operation struct directly until we have implemented
      // the multi-part functions
      sli_crypto_transparent_aead_operation_t operation = { 0 };
      operation.key_len = key_length;
      memcpy(operation.key, key_buffer, key_length);

      status = sli_gcm_crypt_and_tag(&operation,
                                     PSA_CRYPTO_DRIVER_DECRYPT,
                                     ciphertext_length - tag_length,
                                     nonce,
                                     nonce_length,
                                     additional_data,
                                     additional_data_length,
                                     ciphertext,
                                     plaintext,
                                     tag_length,
                                     tag);

      sli_psa_zeroize(&operation, sizeof(operation));

      if (status != PSA_SUCCESS) {
        *plaintext_length = 0;
        memset(plaintext, 0, ciphertext_length - tag_length);
        return status;
      }

      // Check that the provided tag equals the calculated one
      // (in constant time). Note that the tag returned by ccm_auth_crypt
      // is encrypted, so we don't have to decrypt check_tag.
      diff = 0;
      for (uint32_t i = 0; i < tag_length; ++i) {
        diff |= tag[i] ^ check_tag[i];
      }

      if (diff != 0) {
        *plaintext_length = 0;
        memset(plaintext, 0, ciphertext_length - tag_length);
        return PSA_ERROR_INVALID_SIGNATURE;
      }

      if (status == PSA_SUCCESS) {
        *plaintext_length = ciphertext_length - tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    }
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return psa_status;
}

psa_status_t sli_crypto_transparent_aead_encrypt_setup(sli_crypto_transparent_aead_operation_t *operation,
                                                       const psa_key_attributes_t *attributes,
                                                       const uint8_t *key_buffer,
                                                       size_t key_buffer_size,
                                                       psa_algorithm_t alg)
{
  (void)operation;
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_decrypt_setup(sli_crypto_transparent_aead_operation_t *operation,
                                                       const psa_key_attributes_t *attributes,
                                                       const uint8_t *key_buffer,
                                                       size_t key_buffer_size,
                                                       psa_algorithm_t alg)
{
  (void)operation;
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_generate_nonce(sli_crypto_transparent_aead_operation_t *operation,
                                                        uint8_t *nonce,
                                                        size_t nonce_size,
                                                        size_t *nonce_length)
{
  (void)operation;
  (void)nonce;
  (void)nonce_size;
  (void)nonce_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_set_nonce(sli_crypto_transparent_aead_operation_t *operation,
                                                   const uint8_t *nonce,
                                                   size_t nonce_size)
{
  (void)operation;
  (void)nonce;
  (void)nonce_size;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_set_lengths(sli_crypto_transparent_aead_operation_t *operation,
                                                     size_t ad_length,
                                                     size_t plaintext_length)
{
  (void)operation;
  (void)ad_length;
  (void)plaintext_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_update_ad(sli_crypto_transparent_aead_operation_t *operation,
                                                   const uint8_t *input,
                                                   size_t input_length)
{
  (void)operation;
  (void)input;
  (void)input_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_update(sli_crypto_transparent_aead_operation_t *operation,
                                                const uint8_t *input,
                                                size_t input_length,
                                                uint8_t *output,
                                                size_t output_size,
                                                size_t *output_length)
{
  (void)operation;
  (void)input;
  (void)input_length;
  (void)output;
  (void)output_size;
  (void)output_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_finish(sli_crypto_transparent_aead_operation_t *operation,
                                                uint8_t *ciphertext,
                                                size_t ciphertext_size,
                                                size_t *ciphertext_length,
                                                uint8_t *tag,
                                                size_t tag_size,
                                                size_t *tag_length)
{
  (void)operation;
  (void)ciphertext;
  (void)ciphertext_size;
  (void)ciphertext_length;
  (void)tag;
  (void)tag_size;
  (void)tag_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_crypto_transparent_aead_verify(sli_crypto_transparent_aead_operation_t *operation,
                                                uint8_t *plaintext,
                                                size_t plaintext_size,
                                                size_t *plaintext_length,
                                                const uint8_t *tag,
                                                size_t tag_length)
{
  (void)operation;
  (void)plaintext;
  (void)plaintext_size;
  (void)plaintext_length;
  (void)tag;
  (void)tag_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

/*******************************************************************************
 **************************    LOCAL FUNCTIONS   *******************************
 ******************************************************************************/
__STATIC_INLINE
void update_cbc_mac(CRYPTO_TypeDef *crypto, unsigned char *b)
{
  // Every call to the crypto accelerator follows the following conventions:
  //  DATA0: Data to be processed
  //  DATA1: Counter
  //  DATA2: Tag
  //  DATA3: Temporary register
  while ((crypto->STATUS & CRYPTO_STATUS_SEQRUNNING) != 0) ;
  CRYPTO_DataWriteUnaligned(&crypto->DATA0, (uint8_t *)b);
  CRYPTO_EXECUTE_3(crypto,
                   CRYPTO_CMD_INSTR_DATA2TODATA0XOR,
                   CRYPTO_CMD_INSTR_AESENC,
                   CRYPTO_CMD_INSTR_DATA0TODATA2);
}

/*
 * Definition of CCM:
 * http://csrc.nist.gov/publications/nistpubs/800-38C/SP800-38C_updated-July20_2007.pdf
 * RFC 3610 "Counter with CBC-MAC (CCM)"
 *
 * Related:
 * RFC 5116 "An Interface and Algorithms for Authenticated Encryption"
 */
static psa_status_t ccm_auth_crypt(const unsigned char *key_buffer, size_t key_buffer_size,
                                   psa_encrypt_or_decrypt_t mode, size_t length,
                                   const unsigned char *iv, size_t iv_len,
                                   const unsigned char *add, size_t add_len,
                                   const unsigned char *input, unsigned char *output,
                                   unsigned char *tag, size_t tag_len)
{
  CORE_DECLARE_IRQ_STATE;

  unsigned char i;
  unsigned char q;
  size_t len_left;
  unsigned char b[16];
  unsigned char ctr[16];
  const unsigned char *src;
  unsigned char *dst;

  /*
   * Check length requirements: SP800-38C A.1
   * Additional requirement: a < 2^16 - 2^8 to simplify the code.
   * 'length' checked later (when writing it to the first block)
   *
   * Also, loosen the requirements to enable support for CCM* (IEEE 802.15.4).
   */
  if (tag_len == 2 || tag_len > 16 || tag_len % 2 != 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  /* Also implies q is within bounds */
  if (iv_len < 7 || iv_len > 13) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (add_len >= 0xFF00) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  q = 16 - 1 - (unsigned char) iv_len;

  /*
   * First block B_0:
   * 0        .. 0        flags
   * 1        .. iv_len   nonce (aka iv)
   * iv_len+1 .. 15       length
   *
   * With flags as (bits):
   * 7        0
   * 6        add present?
   * 5 .. 3   (t - 2) / 2
   * 2 .. 0   q - 1
   */
  b[0] = 0;
  b[0] |= (add_len > 0) << 6;
  b[0] |= ((tag_len - 2) / 2) << 3;
  b[0] |= q - 1;

  memcpy(b + 1, iv, iv_len);

  for (i = 0, len_left = length; i < q; i++, len_left >>= 8) {
    b[15 - i] = (unsigned char)(len_left & 0xFF);
  }

  if (len_left > 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  CRYPTO_TypeDef *crypto = crypto_management_acquire();
  crypto->WAC = 0;
  crypto->CTRL = 0;

  // Set the encryption key
  CORE_ENTER_CRITICAL();
  CRYPTO_KeyBufWriteUnaligned(crypto,
                              key_buffer,
                              (key_buffer_size == 16U) ? cryptoKey128Bits
                              : cryptoKey256Bits);

  // Clear tag register (DATA2)
  for (uint32_t i = 0; i < 4; ++i) {
    crypto->DATA2 = 0;
  }

  /* Start CBC-MAC with first block */
  update_cbc_mac(crypto, b);
  CORE_EXIT_CRITICAL();

  /*
   * If there is additional data, update CBC-MAC with
   * add_len, add, 0 (padding to a block boundary)
   */
  if (add_len > 0) {
    size_t use_len;
    len_left = add_len;
    src = add;

    memset(b, 0, 16);
    b[0] = (unsigned char)((add_len >> 8) & 0xFF);
    b[1] = (unsigned char)((add_len) & 0xFF);

    use_len = len_left < 16 - 2 ? len_left : 16 - 2;
    memcpy(b + 2, src, use_len);
    len_left -= use_len;
    src += use_len;

    CORE_ENTER_CRITICAL();
    update_cbc_mac(crypto, b);

    while (len_left > 0) {
      use_len = len_left > 16 ? 16 : len_left;

      memset(b, 0, 16);
      memcpy(b, src, use_len);
      update_cbc_mac(crypto, b);

      len_left -= use_len;
      src += use_len;
    }
    CORE_EXIT_CRITICAL();
  }

  /*
   * Prepare counter block for encryption:
   * 0        .. 0        flags
   * 1        .. iv_len   nonce (aka iv)
   * iv_len+1 .. 15       counter (initially 1)
   *
   * With flags as (bits):
   * 7 .. 3   0
   * 2 .. 0   q - 1
   */
  ctr[0] = q - 1;
  memcpy(ctr + 1, iv, iv_len);
  memset(ctr + 1 + iv_len, 0, q);
  ctr[15] = 1;

  // Write the counter to CRYPTO
  CORE_ENTER_CRITICAL();
  CRYPTO_DataWriteUnaligned(&crypto->DATA1, (uint8_t *)ctr);

  /*
   * Authenticate and {en,de}crypt the message.
   *
   * The only difference between encryption and decryption is
   * the respective order of authentication and {en,de}cryption.
   */
  len_left = length;
  src = input;
  dst = output;

  uint8_t out_buf[16];

  while (len_left > 0) {
    size_t use_len = len_left > 16 ? 16 : len_left;

    if (mode == PSA_CRYPTO_DRIVER_ENCRYPT) {
      memset(b, 0, 16);
      memcpy(b, src, use_len);
      update_cbc_mac(crypto, b);
    }

    // Encrypt a message block with CTR
    CRYPTO_DataWriteUnaligned(&crypto->DATA3, (uint8_t *)src);
    CRYPTO_EXECUTE_4(crypto,
                     // Generate key stream block
                     CRYPTO_CMD_INSTR_DATA1TODATA0,
                     CRYPTO_CMD_INSTR_AESENC,
                     // Apply the key stream block to input
                     CRYPTO_CMD_INSTR_DATA3TODATA0XOR,
                     // Increment counter
                     CRYPTO_CMD_INSTR_DATA1INC);
    while ((crypto->STATUS & CRYPTO_STATUS_SEQRUNNING) != 0) ;
    CRYPTO_DataReadUnaligned(&crypto->DATA0, (uint8_t *)out_buf);

    memcpy(dst, out_buf, use_len);

    if (mode == PSA_CRYPTO_DRIVER_DECRYPT) {
      memset(b, 0, 16);
      memcpy(b, dst, use_len);
      update_cbc_mac(crypto, b);
    }

    dst += use_len;
    src += use_len;
    len_left -= use_len;
  }

  /*
   * Authentication: reset counter and crypt/mask internal tag
   */
  for (i = 0; i < q; i++) {
    ctr[15 - i] = 0;
  }

  // Encrypt the tag with CTR
  CRYPTO_DataWriteUnaligned(&crypto->DATA0, (uint8_t *)ctr);
  CRYPTO_EXECUTE_2(crypto,
                   // Generate key stream block
                   CRYPTO_CMD_INSTR_AESENC,
                   // Apply the key stream block to the tag
                   CRYPTO_CMD_INSTR_DATA2TODATA0XOR);
  while ((crypto->STATUS & CRYPTO_STATUS_SEQRUNNING) != 0) ;
  CRYPTO_DataReadUnaligned(&crypto->DATA0, (uint8_t *)out_buf);
  CORE_EXIT_CRITICAL();

  memcpy(tag, out_buf, tag_len);

  crypto_management_release(crypto);

  return PSA_SUCCESS;
}

/*
 * The GCM algorithm is based on two main functions, GHASH and GCTR, defined
 * in http://csrc.nist.gov/publications/nistpubs/800-38D/SP-800-38D.pdf
 *
 * The GHASH and GCTR fuctions can be implemented with the following
 * instruction sequences that can be executed by the CRYPTO peripheral.
 */

/*
 * GCTR_SEQUENCE for encryption and decryption.
 *
 * Procedure is executed with following assumptions:
 * - data to be processed is in DATA0
 * - DATA1 contains counter which is preincremented
 * - DATA3 is used as temporary register
 * - result is stored in DATA0
 *
 *   CRYPTO_CMD_INSTR_DATA0TODATA3
 *   CRYPTO_CMD_INSTR_DATA1INC
 *   CRYPTO_CMD_INSTR_DATA1TODATA0
 *   CRYPTO_CMD_INSTR_AESENC
 *   CRYPTO_CMD_INSTR_DATA3TODATA0XOR
 */

/*
 * GHASH_SEQUENCE for encryption, decryption and tag
 *
 * Procedure is executed with following assumptions:
 * - data to be processed is in DATA0 ( A[i] or C[i] )
 * - temporary GHASH is stored in DDATA0
 * - H is stored in DATA2 (part of DDATA3)
 * - DDATA1 is used temporary for holding input to the MMUL instruction
 *   (MMUL DDATA0 = (DDATA1 * V1) mod P V1 != DDATA0,DDATA1)
 *
 *  Note: The DDATA3 in SELDDATA0DDATA3 is for the BBSWAP128.
 *
 *  CRYPTO_CMD_INSTR_SELDDATA0DDATA2
 *  CRYPTO_CMD_INSTR_XOR
 *  CRYPTO_CMD_INSTR_BBSWAP128
 *  CRYPTO_CMD_INSTR_DDATA0TODDATA1
 *  CRYPTO_CMD_INSTR_SELDDATA0DDATA3
 *  CRYPTO_CMD_INSTR_MMUL
 *  CRYPTO_CMD_INSTR_BBSWAP128
 */

/*
 * CRYPTO register usage:
 *  DATA0 - temporary result and plaintext
 *  DATA1 - Counter state
 *  DATA2 - Hash key
 *  DATA3 - used temporary
 *
 *  DDATA0 - temporary results in the GHASH function (Xi-1)
 *  DDATA1 - temporary for MMUL operands
 *  DDATA2 - overlaps DATA0 and DATA1
 *  DDATA3 - overlaps DATA2 and DATA3
 *  DDATA4 - KEYBUF
 */

// Write data in an unaligned RAM buffer into CRYPTO DATA register
__STATIC_INLINE void gcm_restore_crypto_state(sli_crypto_transparent_aead_operation_t *operation,
                                              CRYPTO_TypeDef *crypto)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();

  // Restore state
  if (operation->key_len == 16U) {
    // Set AES-128 mode
    crypto->CTRL = CRYPTO_CTRL_AES_AES128
                   | CRYPTO_CTRL_INCWIDTH_INCWIDTH4 | CRYPTO_CTRL_DMA0RSEL_DATA0;
  } else {
    // Set AES-256 mode
    crypto->CTRL = CRYPTO_CTRL_AES_AES256
                   | CRYPTO_CTRL_INCWIDTH_INCWIDTH4 | CRYPTO_CTRL_DMA0RSEL_DATA0;
  }

  CRYPTO_KeyBufWriteUnaligned(crypto,
                              operation->key,
                              (operation->key_len == 16U) ? cryptoKey128Bits
                              : cryptoKey256Bits);

  crypto->WAC = CRYPTO_WAC_MODULUS_GCMBIN128 | CRYPTO_WAC_RESULTWIDTH_128BIT;
  CRYPTO_DataWrite(&crypto->DATA2, operation->gcm_ctx.ghash_key);
  CRYPTO_DataWrite(&crypto->DATA1, operation->gcm_ctx.gctr_state);
  // Write GHASH state (128 bits) temporarily to DATA0 (in DDATA2) then
  // move it to DDATA0 (256 bits) where CRYPTO expects it.
  CRYPTO_DataWrite(&crypto->DATA0, operation->gcm_ctx.ghash_state);
  crypto->CMD = CRYPTO_CMD_INSTR_DDATA2TODDATA0;

  CORE_EXIT_CRITICAL();
}

// Start GCM streaming operation
static psa_status_t sli_gcm_starts(sli_crypto_transparent_aead_operation_t *operation,
                                   CRYPTO_TypeDef *device,
                                   psa_encrypt_or_decrypt_t mode,
                                   const unsigned char *iv,
                                   size_t iv_len,
                                   const unsigned char *add,
                                   size_t add_len)
{
  bool            store_state_and_release;
  CRYPTO_TypeDef *crypto;
  uint32_t        temp[4];
  CORE_DECLARE_IRQ_STATE;

  if (iv_len != 12
      ||// AD are limited to 2^64 bits, so 2^61 bytes.
      ((uint64_t) add_len) >> 61 != 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check if this context has already acquired a crypto device, which means
  // the caller should be mbedtls_gcm_crypt_and_tag() which will perform GCM
  // on a full block and call starts, update, finish in a sequence meaning we
  // will not need to store the state in between.
  if (device == NULL) {
    crypto = crypto_management_acquire();
    store_state_and_release = true;
  } else {
    store_state_and_release = false;
    crypto = device;
  }

  // Setup CRTL and KEY
  //   - AES-128 or AES-256 mode
  //   - width of counter in CTR cipher mode to 4 bytes.
  //   - associate DATA0 with DMA instructions which are used in order to
  //     synchronize with MCU load/store during instruction sequence loops
  //     (a DMA engine is not used).
  if (operation->key_len == 16U) {
    // Set AES-128 mode
    crypto->CTRL = CRYPTO_CTRL_AES_AES128
                   | CRYPTO_CTRL_INCWIDTH_INCWIDTH4 | CRYPTO_CTRL_DMA0RSEL_DATA0;
  } else {
    // Set AES-256 mode
    crypto->CTRL = CRYPTO_CTRL_AES_AES256
                   | CRYPTO_CTRL_INCWIDTH_INCWIDTH4 | CRYPTO_CTRL_DMA0RSEL_DATA0;
  }

  CRYPTO_KeyBufWriteUnaligned(crypto,
                              operation->key,
                              (operation->key_len == 16U) ? cryptoKey128Bits
                              : cryptoKey256Bits);

  // Set GCM modulus, operand and result widths
  crypto->WAC   = CRYPTO_WAC_MODULUS_GCMBIN128 | CRYPTO_WAC_RESULTWIDTH_128BIT;
  crypto->SEQCTRL  = 16;
  crypto->SEQCTRLB = 0;

  // Load the initial counter value Y0 into DATA1.
  //   Y0 = IV | 1
  //   That is, the 12 byte Initial Vector concatenated with the initial
  //   counter value 1 in the least significant 32bit word.
  memcpy(operation->gcm_ctx.gctr_state, iv, 12);
  operation->gcm_ctx.gctr_state[3] = 0x01000000;
  CRYPTO_DataWrite(&crypto->DATA1, operation->gcm_ctx.gctr_state);

  CORE_ENTER_CRITICAL();

  // Organize and Compute the initial values.
  CRYPTO_EXECUTE_6(crypto,
                   // Compute hash key H=E(K,0) in DATA2 (LSB DDATA3)
                   CRYPTO_CMD_INSTR_DATA0TODATA0XOR,// DATA0 = 0
                   CRYPTO_CMD_INSTR_AESENC,         // DATA0 = AESENC(DATA0)
                   CRYPTO_CMD_INSTR_SELDDATA2DDATA2,// Select DATA0 for BBSWAP
                   CRYPTO_CMD_INSTR_BBSWAP128,      // Swap bit in H, for GMAC
                   // Move resulting hash key (DDATA0 LSB) to DATA2 (DDATA3 LSB)
                   CRYPTO_CMD_INSTR_DDATA0TODDATA3,
                   // Prepare GHASH(H,A)
                   CRYPTO_CMD_INSTR_CLR             // DDATA0 = 0
                   );

  CORE_EXIT_CRITICAL();

  // Remember mode and additional authentication length
  operation->direction = mode;
  operation->add_len = add_len;

  // Process additional authentication data if present.
  if (add_len) {
    crypto->SEQCTRLB = 0; // Sequence B is not used for auth data

    // Set SEQCTRL_LENGTHA to loop through all blocks
    // We need to do set SEQCTRL_LENGTHA to 16*num_complete_blocks, plus 16 if
    // there is an in-complete block at the end.
    crypto->SEQCTRL = (add_len & 0xFFFFFFF0u) + ((add_len & 0xF) ? 16 : 0);

    CORE_ENTER_CRITICAL();

    // Run GHASH sequence on additional authentication data
    CRYPTO_EXECUTE_8(crypto,
                     // Load additional auth data
                     CRYPTO_CMD_INSTR_DMA0TODATA,
                     // GHASH_SEQUENCE (see desc above)
                     CRYPTO_CMD_INSTR_SELDDATA0DDATA2,
                     CRYPTO_CMD_INSTR_XOR,
                     CRYPTO_CMD_INSTR_BBSWAP128,
                     CRYPTO_CMD_INSTR_DDATA0TODDATA1,
                     CRYPTO_CMD_INSTR_SELDDATA0DDATA3,
                     CRYPTO_CMD_INSTR_MMUL,
                     CRYPTO_CMD_INSTR_BBSWAP128
                     );

    // First loop through and write data for all complete blocks
    while (add_len >= 16) {
      add_len  -= 16;
      // Wait for sequencer to accept data
      while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
      CRYPTO_DataWriteUnaligned(&crypto->DATA0, add);
      add      += 16;
    }
    if (add_len > 0) {
      // For last in-complete block, use temporary buffer for zero padding.
      memset(temp, 0, 16);
      memcpy(temp, add, add_len);
      while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
      CRYPTO_DataWrite(&crypto->DATA0, temp);
    }
    // Wait for completion
    while (!CRYPTO_InstructionSequenceDone(crypto)) ;

    CORE_EXIT_CRITICAL();
  }

  if (store_state_and_release) {
    CORE_ENTER_CRITICAL();
    // Move GHASH state in DDATA0 temporarily to DATA0 (in DDATA2) in order to
    // read only the 128 bits value (since DDATA0 is 256 bits wide).
    crypto->CMD = CRYPTO_CMD_INSTR_DDATA0TODDATA2;
    CRYPTO_DataRead(&crypto->DATA0, operation->gcm_ctx.ghash_state);
    CRYPTO_DataRead(&crypto->DATA2, operation->gcm_ctx.ghash_key);
    CORE_EXIT_CRITICAL();

    crypto_management_release(crypto);
  }

  return PSA_SUCCESS;
}

// Update a GCM streaming operation with more input data to be
// encrypted or decrypted.
static psa_status_t sli_gcm_update(sli_crypto_transparent_aead_operation_t *operation,
                                   CRYPTO_TypeDef *device,
                                   size_t length,
                                   const unsigned char *input,
                                   unsigned char *output)
{
  bool            restore_state_and_release;
  CRYPTO_TypeDef *crypto;
  uint32_t        temp[4];
  unsigned int    sequence_loop_length;
  bool            last_block_is_incomplete;
  CORE_DECLARE_IRQ_STATE;

  if (length == 0) {
    return 0;
  }

  // Total length is restricted to 2^39 - 256 bits, ie 2^36 - 2^5 bytes
  // Also check for possible overflow.
  if (operation->processed_len + length < operation->processed_len
      || (uint64_t) operation->processed_len + length > 0xFFFFFFFE0ull) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check if this context has already acquired a crypto device, which means
  // the caller should be mbedtls_gcm_crypt_and_tag() which will perform GCM
  // on a full block and call starts, update, finish in a sequence meaning we
  // will not need to store the state in between.
  if (device == NULL) {
    crypto = crypto_management_acquire();
    restore_state_and_release = true;
    gcm_restore_crypto_state(operation, crypto);
  } else {
    restore_state_and_release = false;
    crypto = device;
  }

  operation->processed_len += length;

  // Calculate total sequence length 16*num_complete_blocks, plus 16 if
  // there is an in-complete block at the end.
  last_block_is_incomplete = length & 0xF;
  sequence_loop_length =
    (length & 0xFFFFFFF0u) + (last_block_is_incomplete ? 16 : 0);

  CORE_ENTER_CRITICAL();

  if (operation->direction == PSA_CRYPTO_DRIVER_DECRYPT) {
    crypto->SEQCTRL  = sequence_loop_length;
    crypto->SEQCTRLB = 0;

    // Start decryption sequence
    CRYPTO_EXECUTE_14(crypto,
                      CRYPTO_CMD_INSTR_DMA0TODATA,  // Load Ciphertext

                      // GHASH_SEQUENCE (see desc above)
                      CRYPTO_CMD_INSTR_SELDDATA0DDATA2,
                      CRYPTO_CMD_INSTR_XOR,
                      CRYPTO_CMD_INSTR_BBSWAP128,
                      CRYPTO_CMD_INSTR_DDATA0TODDATA1,
                      CRYPTO_CMD_INSTR_SELDDATA0DDATA3,
                      CRYPTO_CMD_INSTR_MMUL,
                      CRYPTO_CMD_INSTR_BBSWAP128,

                      // GCTR_SEQUENCE (see desc above)
                      CRYPTO_CMD_INSTR_DATA0TODATA3,
                      CRYPTO_CMD_INSTR_DATA1INC,
                      CRYPTO_CMD_INSTR_DATA1TODATA0,
                      CRYPTO_CMD_INSTR_AESENC,
                      CRYPTO_CMD_INSTR_DATA3TODATA0XOR,
                      CRYPTO_CMD_INSTR_DATATODMA0   // Store Plaintext
                      );
  } else {
    // For encryption we need to handle the last block differently if it is
    // incomplete. We need to zeroize bits outside len(PT) in DATA0 before
    // the GHASH operation. We do this by using a DMA0TODATA instruction in
    // the B sequence, meaning that the sequencer will wait for the MCU core
    // to zeroize bits and write them back to DATA0.
    if (last_block_is_incomplete) {
      crypto->SEQCTRL  = sequence_loop_length - 16;
      crypto->SEQCTRLB = 16;
    } else {
      crypto->SEQCTRL  = sequence_loop_length;
      crypto->SEQCTRLB = 0;
    }

    // Start encryption sequence
    CRYPTO_EXECUTE_17(crypto,
                      CRYPTO_CMD_INSTR_DMA0TODATA,  // Load Plaintext

                      // GCTR_SEQUENCE (see desc above)
                      CRYPTO_CMD_INSTR_DATA0TODATA3,
                      CRYPTO_CMD_INSTR_DATA1INC,
                      CRYPTO_CMD_INSTR_DATA1TODATA0,
                      CRYPTO_CMD_INSTR_AESENC,
                      CRYPTO_CMD_INSTR_DATA3TODATA0XOR,
                      CRYPTO_CMD_INSTR_DATATODMA0,  // Store Ciphertext

                      CRYPTO_CMD_INSTR_EXECIFB,
                      CRYPTO_CMD_INSTR_DMA0TODATA,  // Load X XOR MSB(CIPH(CB))
                      CRYPTO_CMD_INSTR_EXECALWAYS,

                      // GHASH_SEQUENCE (see desc above)
                      CRYPTO_CMD_INSTR_SELDDATA0DDATA2,
                      CRYPTO_CMD_INSTR_XOR,
                      CRYPTO_CMD_INSTR_BBSWAP128,
                      CRYPTO_CMD_INSTR_DDATA0TODDATA1,
                      CRYPTO_CMD_INSTR_SELDDATA0DDATA3,
                      CRYPTO_CMD_INSTR_MMUL,
                      CRYPTO_CMD_INSTR_BBSWAP128
                      );
  }

  while (length >= 16) {
    length  -= 16;
    // Wait for sequencer to accept data
    while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
    CRYPTO_DataWriteUnaligned(&crypto->DATA0, input);
    input   += 16;
    // Wait for sequencer to finish iteration and make data available
    while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
    CRYPTO_DataReadUnaligned(&crypto->DATA0, output);
    output  += 16;
  }

  if (length > 0) {
    // The last block is incomplete, so we need to zero pad bits outside len(PT)
    // Use temporary buffer for zero padding
    memset(temp, 0, 16);
    memcpy(temp, input, length);

    while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
    // Write last input data (PT/CT)
    CRYPTO_DataWrite(&crypto->DATA0, temp);
    while (!(crypto->STATUS & CRYPTO_STATUS_DMAACTIVE)) ;
    // Read last output data (CT/PT)
    CRYPTO_DataRead(&crypto->DATA0, temp);

    if (operation->direction == PSA_CRYPTO_DRIVER_ENCRYPT) {
      // For encryption, when the last block is incomplete we need to
      // zeroize bits outside len(PT) in DATA0 before the GHASH operation.
      memset(&((uint8_t*)temp)[length], 0, 16 - length);
      CRYPTO_DataWrite(&crypto->DATA0, temp);
    }

    // Copy to output buffer now while CRYPTO performs GHASH.
    memcpy(output, temp, length);
  }

  // Wait for completion
  while (!CRYPTO_InstructionSequenceDone(crypto)) ;

  CORE_EXIT_CRITICAL();

  if (restore_state_and_release) {
    CORE_ENTER_CRITICAL();
    CRYPTO_DataRead(&crypto->DATA1, operation->gcm_ctx.gctr_state);
    // Move GHASH state in DDATA0 temporarily to DATA2 (in DDATA3) in order to
    // read only the 128 bits value (since DDATA0 is 256 bits wide).
    crypto->CMD = CRYPTO_CMD_INSTR_DDATA0TODDATA3;
    CRYPTO_DataRead(&crypto->DATA2, operation->gcm_ctx.ghash_state);
    CORE_EXIT_CRITICAL();

    crypto_management_release(crypto);
  }

  return PSA_SUCCESS;
}

// Finish GCM streaming operation
static psa_status_t sli_gcm_finish(sli_crypto_transparent_aead_operation_t *operation,
                                   CRYPTO_TypeDef *device,
                                   unsigned char *tag,
                                   size_t tag_len)
{
  bool            restore_state_and_release;
  uint64_t        bit_len;
  uint32_t        temp[4];
  CRYPTO_TypeDef *crypto;
  CORE_DECLARE_IRQ_STATE;

  // Check if this context has already acquired a crypto device, which means
  // the caller should be mbedtls_gcm_crypt_and_tag() which will perform GCM
  // on a full block and call starts, update, finish in a sequence meaning we
  // will not need to store the state in between.
  if (device == NULL) {
    crypto = crypto_management_acquire();
    restore_state_and_release = true;
    gcm_restore_crypto_state(operation, crypto);
  } else {
    restore_state_and_release = false;
    crypto = device;
  }

  // Compute last part of the GHASH and authentication tag:
  //
  // Xm+n+1 = (Xm+n XOR (len(A)|len(C))) * H
  //
  // Compute the final authentication tag now.
  // T = MSBt (GHASH(H, A, C) XOR E(K, Y0))
  // where GHASH(H, A, C) is Xm+n+1 which is stored in DATA0 (LSWord of DDATA2)
  // and Counter value Yn is stored in DATA1. We assume N (in Yn) is not bigger
  // than 2^32 so E(K, Y0) derived by clearing DATA1 which gives Y0.
  crypto->SEQCTRL = 16;
  crypto->SEQCTRLB = 0;

  CORE_ENTER_CRITICAL();

  // Temporarily load length fields value 128 bits into DATA0 register
  // Then move it into LSB of DDATA1 (for optimal performance)
  bit_len = operation->add_len * 8;
  crypto->DATA0 = __REV((uint32_t) (bit_len >> 32));
  crypto->DATA0 = __REV((uint32_t) bit_len);
  bit_len = operation->processed_len * 8;
  crypto->DATA0 = __REV((uint32_t) (bit_len >> 32));
  crypto->DATA0 = __REV((uint32_t) bit_len);

  // Calculate last part of GHASH (in DDATA0)
  // adding in length fields in DATA0 ( LSB of DDATA2 )
  CRYPTO_EXECUTE_16(crypto,
                    // Move length fields in DATA0 (in DDATA2) to DDATA1
                    CRYPTO_CMD_INSTR_DDATA2TODDATA1,
                    // See descripton of GHASH_SEQUENCE above.
                    CRYPTO_CMD_INSTR_SELDDATA0DDATA1, // A[i] and Xi-1
                    CRYPTO_CMD_INSTR_XOR,
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_DDATA0TODDATA1,
                    CRYPTO_CMD_INSTR_SELDDATA0DDATA3, // temp result and H
                    CRYPTO_CMD_INSTR_MMUL,       // Xi is stored in DDATA0
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_DDATA0TODDATA3,
                    CRYPTO_CMD_INSTR_DATA2TODATA0,
                    // Calculate AuthTag
                    CRYPTO_CMD_INSTR_DATA1INCCLR,
                    CRYPTO_CMD_INSTR_DATA0TODATA3,
                    CRYPTO_CMD_INSTR_DATA1INC,
                    CRYPTO_CMD_INSTR_DATA1TODATA0,
                    CRYPTO_CMD_INSTR_AESENC,
                    CRYPTO_CMD_INSTR_DATA3TODATA0XOR
                    ); // DATA0 = DATA0 ^ DATA3

  // Wait for completion
  while (!CRYPTO_InstructionSequenceDone(crypto)) ;

  if (tag_len) {
    CRYPTO_DataRead(&crypto->DATA0, temp);
    memcpy(tag, temp, tag_len);
  }

  CORE_EXIT_CRITICAL();

  if (restore_state_and_release) {
    crypto_management_release(crypto);
  }

  return PSA_SUCCESS;
}

// Perform full GCM block encryption or decryption operation with tag
static psa_status_t sli_gcm_crypt_and_tag(sli_crypto_transparent_aead_operation_t *operation,
                                          psa_encrypt_or_decrypt_t mode,
                                          size_t length,
                                          const unsigned char *iv,
                                          size_t iv_len,
                                          const unsigned char *add,
                                          size_t add_len,
                                          const unsigned char *input,
                                          unsigned char *output,
                                          size_t tag_len,
                                          unsigned char *tag)
{
  psa_status_t status = PSA_ERROR_HARDWARE_FAILURE;

  CRYPTO_TypeDef *device = crypto_management_acquire();

  status = sli_gcm_starts(operation, device, mode, iv, iv_len, add, add_len);
  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = sli_gcm_update(operation, device, length, input, output);
  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = sli_gcm_finish(operation, device, tag, tag_len);
  if (status != PSA_SUCCESS) {
    goto exit;
  }

  exit:
  crypto_management_release(device);
  return status;
}

#endif // defined(CRYPTO_PRESENT)
