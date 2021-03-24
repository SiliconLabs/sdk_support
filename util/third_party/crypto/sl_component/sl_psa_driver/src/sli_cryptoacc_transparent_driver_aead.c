/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver AEAD functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "em_device.h"

#if defined(CRYPTOACC_PRESENT)

#include "sli_cryptoacc_transparent_types.h"
#include "sli_cryptoacc_transparent_functions.h"
#include "cryptoacc_management.h"
// Replace inclusion of psa/crypto_xxx.h with the new psa driver common
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"
#include "sx_aes.h"
#include "sx_errors.h"
#include "cryptolib_types.h"

#include <string.h>

#ifndef PSA_AEAD_TAG_MAX_SIZE
// TODO: Remove when macro has been added to the core
#define PSA_AEAD_TAG_MAX_SIZE 16
#endif

static psa_status_t check_aead_parameters(psa_algorithm_t alg,
                                          size_t nonce_length,
                                          size_t additional_data_length,
                                          size_t key_bits)
{
  switch (key_bits) {
    case 128: // fallthrough
    case 192: // fallthrough
    case 256:
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }
  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);

  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      if (tag_length == 0
          || tag_length == 2
          || tag_length > 16
          || tag_length % 2 != 0
          || nonce_length < 7
          || nonce_length > 13) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):
      // AD are limited to 2^64 bits, so 2^61 bytes.
      // We need not check if SIZE_MAX (max of size_t) is less than 2^61 (0x2000000000000000)
#if SIZE_MAX > 0x2000000000000000ull
      if (additional_data_length >> 61 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
#else
      (void) additional_data_length;
#endif
      if (nonce_length != AES_IV_GCM_SIZE) {
        // Libcryptosoc only supports 12 bytes long IVs.
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
      break;
  }
  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_aead_encrypt(const psa_key_attributes_t *attributes,
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
  if (key_buffer == NULL
      || attributes == NULL
      || nonce == NULL
      || (additional_data == NULL && additional_data_length > 0)
      || (plaintext == NULL && plaintext_length > 0)
      || (plaintext_length > 0 && (ciphertext == NULL || ciphertext_size == 0))
      || ciphertext_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  size_t key_bits = psa_get_key_bits(attributes);
  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);

  // Verify that the driver supports the given parameters.
  psa_status_t status = check_aead_parameters(alg, nonce_length, additional_data_length,
                                              key_bits);
  if (status != PSA_SUCCESS) {
    return status;
  }

  // Verify key type.
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check input-key size.
  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check sufficient output buffer size.
  if (ciphertext_size < plaintext_length + tag_length) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((ciphertext > plaintext) && (ciphertext < (plaintext + plaintext_length))) {
    memmove(ciphertext, plaintext, plaintext_length);
    plaintext = ciphertext;
  }

  psa_status_t return_status = PSA_ERROR_CORRUPTION_DETECTED;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t key = NULL_blk;
  block_t aad_block = NULL_blk;
  block_t tag_block = NULL_blk;
  block_t nonce_internal = NULL_blk;
  block_t data_in = NULL_blk;
  block_t data_out = NULL_blk;
  uint8_t tagbuf[16];
  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):

      // Check length of plaintext.
    {
      unsigned char q = 16 - 1 - (unsigned char) nonce_length;
      if (q < sizeof(plaintext_length)
          && plaintext_length >= (1UL << (q * 8))) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }

      key = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      aad_block = block_t_convert(additional_data, additional_data_length);
      tag_block = block_t_convert(ciphertext + plaintext_length, tag_length);
      nonce_internal = block_t_convert(nonce, nonce_length);
      data_in = block_t_convert(plaintext, plaintext_length);
      data_out = block_t_convert(ciphertext, plaintext_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = sx_aes_ccm_encrypt((const block_t *)&key,
                                  (const block_t *)&data_in,
                                  &data_out,
                                  (const block_t *)&nonce_internal,
                                  &tag_block,
                                  (const block_t *)&aad_block);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      *ciphertext_length = plaintext_length + tag_length;
      return_status = PSA_SUCCESS;
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):

      key = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      aad_block = block_t_convert(additional_data, additional_data_length);
      tag_block = block_t_convert(tagbuf, sizeof(tagbuf));
      nonce_internal = block_t_convert(nonce, nonce_length);
      data_in = block_t_convert(plaintext, plaintext_length);
      data_out = block_t_convert(ciphertext, plaintext_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = sx_aes_gcm_encrypt((const block_t *)&key,
                                  (const block_t *)&data_in,
                                  &data_out,
                                  (const block_t *)&nonce_internal,
                                  &tag_block,
                                  (const block_t *)&aad_block);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      // Copy only requested part of computed tag to user output buffer.
      memcpy(ciphertext + plaintext_length, tagbuf, tag_length);
      *ciphertext_length = plaintext_length + tag_length;
      return_status = PSA_SUCCESS;
      break;
  }
  return return_status;
}

psa_status_t sli_cryptoacc_transparent_aead_decrypt(const psa_key_attributes_t *attributes,
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
  if (key_buffer == NULL
      || attributes == NULL
      || nonce == NULL
      || (additional_data == NULL && additional_data_length > 0)
      || (ciphertext == NULL && ciphertext_length > 0)
      || (ciphertext_length > tag_length && (plaintext == NULL || plaintext_size == 0))
      || ciphertext_length == 0
      || ciphertext_length < tag_length
      || plaintext_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Verify that the driver supports the given parameters.
  size_t key_bits = psa_get_key_bits(attributes);
  psa_status_t status = check_aead_parameters(alg, nonce_length,
                                              additional_data_length,
                                              key_bits);
  if (status != PSA_SUCCESS) {
    return status;
  }

  // Check input-key size.
  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Verify key type.
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check sufficient output buffer size.
  if (plaintext_size < ciphertext_length - tag_length) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // We have to copy the tag in case the decryption corrupts it in the case
  // of overlapping input/output buffers
  uint8_t check_tag[PSA_AEAD_TAG_MAX_SIZE];
  memcpy(check_tag, &ciphertext[ciphertext_length - tag_length], tag_length);

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((plaintext > ciphertext) && (plaintext < (ciphertext + ciphertext_length))) {
    memmove(plaintext, ciphertext, ciphertext_length - tag_length);
    ciphertext = plaintext;
  }

  psa_status_t return_status = PSA_ERROR_CORRUPTION_DETECTED;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t key = NULL_blk;
  block_t aad_block = NULL_blk;
  block_t tag_block = NULL_blk;
  block_t nonce_internal = NULL_blk;
  block_t data_in = NULL_blk;
  block_t data_out = NULL_blk;
  uint8_t tagbuf[16];
  uint32_t diff = 0;
  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):

    {
      // Check length of ciphertext.
      unsigned char q = 16 - 1 - (unsigned char) nonce_length;
      if (q < sizeof(ciphertext_length)
          && ciphertext_length >= (1UL << (q * 8))) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    }

      key = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      aad_block = block_t_convert(additional_data, additional_data_length);
      tag_block = block_t_convert(check_tag, tag_length);
      nonce_internal = block_t_convert(nonce, nonce_length);
      data_in = block_t_convert(ciphertext, ciphertext_length - tag_length);
      data_out = block_t_convert(plaintext, ciphertext_length - tag_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = sx_aes_ccm_decrypt_verify((const block_t *)&key,
                                         (const block_t *)&data_in,
                                         &data_out,
                                         (const block_t *)&nonce_internal,
                                         &tag_block,
                                         (const block_t *)&aad_block);
      status = cryptoacc_management_release();
      if (sx_ret == CRYPTOLIB_INVALID_SIGN_ERR) {
        return_status = PSA_ERROR_INVALID_SIGNATURE;
      } else if (sx_ret != CRYPTOLIB_SUCCESS || status != PSA_SUCCESS) {
        return_status = PSA_ERROR_HARDWARE_FAILURE;
      } else {
        *plaintext_length = ciphertext_length - tag_length;
        return_status = PSA_SUCCESS;
      }
      break;

    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):

      key = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      aad_block = block_t_convert(additional_data, additional_data_length);
      tag_block = block_t_convert(tagbuf, sizeof(tagbuf));
      nonce_internal = block_t_convert(nonce, nonce_length);
      data_in = block_t_convert(ciphertext, ciphertext_length - tag_length);
      data_out = block_t_convert(plaintext, ciphertext_length - tag_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = sx_aes_gcm_decrypt((const block_t *)&key,
                                  (const block_t *)&data_in,
                                  &data_out,
                                  (const block_t *)&nonce_internal,
                                  &tag_block,
                                  (const block_t *)&aad_block);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS || status != PSA_SUCCESS) {
        return_status = PSA_ERROR_HARDWARE_FAILURE;
      } else {
        // Check that the provided tag equals the calculated one
        // (in constant time). Note that the tag returned by ccm_auth_crypt
        // is encrypted, so we don't have to decrypt check_tag.
        diff = 0;
        for (uint32_t i = 0; i < tag_length; ++i) {
          diff |= tagbuf[i] ^ check_tag[i];
        }

        if (diff != 0) {
          return_status = PSA_ERROR_INVALID_SIGNATURE;
        } else {
          *plaintext_length = ciphertext_length - tag_length;
          return_status = PSA_SUCCESS;
        }
        break;
      }
  }

  if (return_status != PSA_SUCCESS) {
    *plaintext_length = 0;
    memset(plaintext, 0, ciphertext_length - tag_length);
  }

  return return_status;
}

#if defined(PSA_CRYPTO_AEAD_MULTIPART_SUPPORTED)

psa_status_t sli_cryptoacc_transparent_aead_encrypt_setup(sli_cryptoacc_transparent_aead_operation_t *operation,
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

psa_status_t sli_cryptoacc_transparent_aead_decrypt_setup(sli_cryptoacc_transparent_aead_operation_t *operation,
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

psa_status_t sli_cryptoacc_transparent_aead_generate_nonce(sli_cryptoacc_transparent_aead_operation_t *operation,
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

psa_status_t sli_cryptoacc_transparent_aead_set_nonce(sli_cryptoacc_transparent_aead_operation_t *operation,
                                                      const uint8_t *nonce,
                                                      size_t nonce_size)
{
  (void)operation;
  (void)nonce;
  (void)nonce_size;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_cryptoacc_transparent_aead_set_lengths(sli_cryptoacc_transparent_aead_operation_t *operation,
                                                        size_t ad_length,
                                                        size_t plaintext_length)
{
  (void)operation;
  (void)ad_length;
  (void)plaintext_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_cryptoacc_transparent_aead_update_ad(sli_cryptoacc_transparent_aead_operation_t *operation,
                                                      const uint8_t *input,
                                                      size_t input_length)
{
  (void)operation;
  (void)input;
  (void)input_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_cryptoacc_transparent_aead_update(sli_cryptoacc_transparent_aead_operation_t *operation,
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

psa_status_t sli_cryptoacc_transparent_aead_finish(sli_cryptoacc_transparent_aead_operation_t *operation,
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

psa_status_t sli_cryptoacc_transparent_aead_verify(sli_cryptoacc_transparent_aead_operation_t *operation,
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

#endif // defined(PSA_CRYPTO_AEAD_MULTIPART_SUPPORTED)

#endif // defined(SEMAILBOX_PRESENT)
