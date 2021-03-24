/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Cipher functions.
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
// Replace inclusion of psa/crypto_xxx.h with the new psa driver commong
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"
#include "mbedtls/entropy_poll.h"
#include "cryptolib_def.h"
#include "sx_errors.h"
#include "sx_aes.h"

#include <string.h>

/** Encrypt a message using a symmetric cipher.
 *
 * This function encrypts a message with a random IV (initialization
 * vector). Use the multipart operation interface with a
 * #psa_cipher_operation_t object to provide other forms of IV.
 *
 * \param handle                Handle to the key to use for the operation.
 *                              It must remain valid until the operation
 *                              terminates.
 * \param alg                   The cipher algorithm to compute
 *                              (\c PSA_ALG_XXX value such that
 *                              #PSA_ALG_IS_CIPHER(\p alg) is true).
 * \param[in] input             Buffer containing the message to encrypt.
 * \param input_length          Size of the \p input buffer in bytes.
 * \param[out] output           Buffer where the output is to be written.
 *                              The output contains the IV followed by
 *                              the ciphertext proper.
 * \param output_size           Size of the \p output buffer in bytes.
 * \param[out] output_length    On success, the number of bytes
 *                              that make up the output.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \p handle is not compatible with \p alg.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         \p alg is not supported or is not a cipher algorithm.
 * \retval #PSA_ERROR_BUFFER_TOO_SMALL
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_cryptoacc_transparent_cipher_encrypt(const psa_key_attributes_t *attributes,
                                                      const uint8_t *key_buffer,
                                                      size_t key_buffer_size,
                                                      psa_algorithm_t alg,
                                                      const uint8_t *input,
                                                      size_t input_length,
                                                      uint8_t *output,
                                                      size_t output_size,
                                                      size_t *output_length)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  int trng_ret = -1;
  block_t key;
  block_t iv_block;
  block_t data_in;
  block_t data_out;
  uint8_t iv_buf[AES_IV_SIZE];
  uint8_t tmp_buf[16];
  size_t iv_length;

  // Argument check
  if (key_buffer == NULL
      || key_buffer_size == 0
      || input == NULL
      || input_length == 0
      || output == NULL
      || output_length == NULL
      || output_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check key type and size.
  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      if (key_buffer_size < (psa_get_key_bits(attributes) / 8)
          || !(psa_get_key_bits(attributes) == 128
               || psa_get_key_bits(attributes) == 192
               || psa_get_key_bits(attributes) == 256)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((output > input) && (output < (input + input_length))) {
    // Sanity check before copying. Some ciphers have a stricter requirement
    // than this (if an IV is included), but no ciphers will have an output
    // smaller than the input.
    if (output_size < input_length) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    memmove(output, input, input_length);
    input = output;
  }

  // Encrypt.
  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING: {
      // Check buffer sizes.
      if (output_size < input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // We cannot do ECB on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      key = block_t_convert(key_buffer, key_buffer_size);
      data_in = block_t_convert(input, input_length);
      data_out = block_t_convert(output, input_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      sx_ret = sx_aes_ecb_encrypt((const block_t*)&key,
                                  (const block_t*)&data_in,
                                  &data_out);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      *output_length = input_length;
      break;
    }
    case PSA_ALG_CTR: {
      // Check buffer sizes.
      if (output_size < AES_IV_SIZE + input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Generate nonce.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, AES_IV_SIZE, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(iv_buf, AES_IV_SIZE);
      data_in = block_t_convert(input, input_length);
      data_out = block_t_convert(output + AES_IV_SIZE, input_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      sx_ret = sx_aes_ctr_encrypt((const block_t*)&key,
                                  (const block_t*)&data_in,
                                  &data_out,
                                  (const block_t*)&iv_block);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Write IV to output after performing encryption in
      // order to avoid overwriting the first input-byte.
      memcpy(output, iv_buf, AES_IV_SIZE);

      *output_length = AES_IV_SIZE + input_length;
      break;
    }
    case PSA_ALG_CFB: {
      // Check buffer sizes.
      if (output_size < AES_IV_SIZE + input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, AES_IV_SIZE, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Copy final input bytes before they are overwritten (in case of overlap with output buffer).
      memcpy(tmp_buf, input + (input_length / 16) * 16, input_length % 16);

      key = block_t_convert(key_buffer, key_buffer_size);

      size_t input_length_full_blocks = (input_length / 16) * 16;

      // Process full blocks.
      if (input_length_full_blocks > 0) {
        iv_block = block_t_convert(iv_buf, AES_IV_SIZE);
        data_in = block_t_convert(input, input_length_full_blocks);
        data_out = block_t_convert(output + AES_IV_SIZE,
                                   input_length_full_blocks);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cfb_encrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Write IV to output after performing encryption in
      // order to avoid overwriting the first input-byte.
      memcpy(output, iv_buf, AES_IV_SIZE);

      // Process final bytes.
      if (input_length % 16 != 0) {
        iv_block = block_t_convert(&output[AES_IV_SIZE + input_length_full_blocks - 16],
                                   AES_IV_SIZE);
        data_in = block_t_convert(tmp_buf, 16);
        data_out = block_t_convert(tmp_buf, 16);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cfb_encrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        memcpy(output + AES_IV_SIZE + input_length_full_blocks,
               tmp_buf,
               input_length % 16);
      }

      *output_length = AES_IV_SIZE + input_length;
      break;
    }
    case PSA_ALG_OFB: {
      uint8_t final_block[16];

      // Check buffer sizes.
      if (output_size < AES_IV_SIZE + input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, AES_IV_SIZE, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Copy final input bytes before they are overwritten (in case of overlap with output buffer).
      memcpy(final_block, input + (input_length / 16) * 16, input_length % 16);

      // Copy IV to tmp buf in order to avoid overwriting it with intermediate IV.
      memcpy(tmp_buf, iv_buf, AES_IV_SIZE);

      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(tmp_buf, AES_IV_SIZE);

      size_t input_length_full_blocks = (input_length / 16) * 16;

      // Process full blocks.
      if (input_length_full_blocks > 0) {
        data_in = block_t_convert(input, input_length_full_blocks);
        data_out = block_t_convert(output + AES_IV_SIZE,
                                   input_length_full_blocks);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_ofb_encrypt_update((const block_t*)&key,
                                           (const block_t*)&data_in,
                                           &data_out,
                                           (const block_t*)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Write IV to output after performing encryption in
      // order to avoid overwriting the first input-byte.
      memcpy(output, iv_buf, AES_IV_SIZE);

      // Process leftover bytes.
      if (input_length % 16 != 0) {
        data_in = block_t_convert(final_block, 16);
        data_out = block_t_convert(final_block, 16);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_ofb_encrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        memcpy(output + AES_IV_SIZE + input_length_full_blocks,
               final_block,
               input_length % 16);
      }

      *output_length = AES_IV_SIZE + input_length;
      break;
    }
    case PSA_ALG_CBC_NO_PADDING:
      // We cannot do CBC without padding on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    // fall through
    case PSA_ALG_CBC_PKCS7: {
      uint8_t final_block[16];

      // Check buffer sizes.
      if (alg == PSA_ALG_CBC_NO_PADDING) {
        if (output_size < AES_IV_SIZE + input_length) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
      } else {
        if (output_size < AES_IV_SIZE + (input_length & ~0xF) + 16) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, AES_IV_SIZE, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Copy IV to tmp buf in order to avoid overwriting it with intermediate IV.
      memcpy(tmp_buf, iv_buf, AES_IV_SIZE);

      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(tmp_buf, AES_IV_SIZE);
      data_in = block_t_convert(input, input_length & ~0xF);
      data_out = block_t_convert(output + AES_IV_SIZE, input_length & ~0xF);

      // Store last block (if non-blocksize input-length) to temporary buffer to be used in padding.
      if (alg == PSA_ALG_CBC_PKCS7) {
        memcpy(final_block,
               &input[input_length & ~0xF],
               input_length & 0xF);
      }

      if ((input_length & ~0xF) > 0) {
        // CBC-encrypt all but the last block.
        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cbc_encrypt_update((const block_t *)&key,
                                           (const block_t *)&data_in,
                                           &data_out,
                                           (const block_t *)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Write IV to output after performing encryption in
      // order to avoid overwriting the first input-byte.
      memcpy(output, iv_buf, AES_IV_SIZE);

      // Process final block.
      if (alg == PSA_ALG_CBC_PKCS7) {
        // Add PKCS7 padding.
        memset(&final_block[input_length & 0xF],
               16 - (input_length & 0xF),
               16 - (input_length & 0xF));

        // CBC-encrypt the last block.
        data_in = block_t_convert(final_block, 16);
        data_out = block_t_convert(final_block, 16);
        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cbc_encrypt_update((const block_t *)&key,
                                           (const block_t *)&data_in,
                                           &data_out,
                                           (const block_t *)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        // Copy to output.
        memcpy(&output[AES_IV_SIZE + (input_length & ~0xF)],
               final_block,
               16);

        *output_length = AES_IV_SIZE + (input_length & ~0xF) + 16;
      } else {
        *output_length = AES_IV_SIZE + input_length;
      }
      break;
    }
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

/** Decrypt a message using a symmetric cipher.
 *
 * This function decrypts a message encrypted with a symmetric cipher.
 *
 * \param handle                Handle to the key to use for the operation.
 *                              It must remain valid until the operation
 *                              terminates.
 * \param alg                   The cipher algorithm to compute
 *                              (\c PSA_ALG_XXX value such that
 *                              #PSA_ALG_IS_CIPHER(\p alg) is true).
 * \param[in] input             Buffer containing the message to decrypt.
 *                              This consists of the IV followed by the
 *                              ciphertext proper.
 * \param input_length          Size of the \p input buffer in bytes.
 * \param[out] output           Buffer where the plaintext is to be written.
 * \param output_size           Size of the \p output buffer in bytes.
 * \param[out] output_length    On success, the number of bytes
 *                              that make up the output.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \p handle is not compatible with \p alg.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         \p alg is not supported or is not a cipher algorithm.
 * \retval #PSA_ERROR_BUFFER_TOO_SMALL
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_cryptoacc_transparent_cipher_decrypt(const psa_key_attributes_t *attributes,
                                                      const uint8_t *key_buffer,
                                                      size_t key_buffer_size,
                                                      psa_algorithm_t alg,
                                                      const uint8_t *input,
                                                      size_t input_length,
                                                      uint8_t *output,
                                                      size_t output_size,
                                                      size_t *output_length)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t key;
  block_t iv_block;
  block_t data_in;
  block_t data_out;
  uint8_t tmp_buf[16];

  // Argument check
  if (key_buffer == NULL
      || key_buffer_size == 0
      || input == NULL
      || input_length == 0
      || output == NULL
      || output_length == NULL
      || output_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check key type and size.
  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      if (key_buffer_size < (psa_get_key_bits(attributes) / 8)
          || !(psa_get_key_bits(attributes) == 128
               || psa_get_key_bits(attributes) == 192
               || psa_get_key_bits(attributes) == 256)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((output > input) && (output < (input + input_length))) {
    // Sanity check before copying. Some ciphers have a stricter requirement
    // than this (if an IV is included), but no ciphers will have an output
    // smaller than the input.
    if (output_size < input_length) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    memmove(output, input, input_length);
    input = output;
  }

  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING: {
      // Check buffer sizes.
      if (output_size < input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // We cannot do ECB on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      key = block_t_convert(key_buffer, key_buffer_size);
      data_in = block_t_convert(input, input_length);
      data_out = block_t_convert(output, input_length);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      sx_ret = sx_aes_ecb_decrypt((const block_t*)&key,
                                  (const block_t*)&data_in,
                                  &data_out);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      *output_length = input_length;
      break;
    }
    case PSA_ALG_CTR: {
      // Check buffer sizes.
      if (output_size < input_length - AES_IV_SIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(input, AES_IV_SIZE);
      data_in = block_t_convert(input + AES_IV_SIZE,
                                input_length - AES_IV_SIZE);
      data_out = block_t_convert(output, input_length - AES_IV_SIZE);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      sx_ret = sx_aes_ctr_decrypt((const block_t*)&key,
                                  (const block_t*)&data_in,
                                  &data_out,
                                  (const block_t*)&iv_block);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      *output_length = input_length - AES_IV_SIZE;
      break;
    }
    case PSA_ALG_CFB: {
      // Check buffer sizes.
      if (output_size < input_length - AES_IV_SIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      key = block_t_convert(key_buffer, key_buffer_size);

      size_t input_length_full_blocks = ((input_length - AES_IV_SIZE) / 16) * 16;

      // Process full blocks.
      if (input_length_full_blocks > 0) {
        iv_block = block_t_convert(input, AES_IV_SIZE);
        data_in = block_t_convert(input + AES_IV_SIZE,
                                  input_length_full_blocks);
        data_out = block_t_convert(output, input_length_full_blocks);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cfb_decrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Process final bytes.
      if (input_length % 16 != 0) {
        iv_block = block_t_convert(input + input_length_full_blocks,
                                   AES_IV_SIZE);
        data_in = block_t_convert(input + AES_IV_SIZE + input_length_full_blocks,
                                  16);
        data_out = block_t_convert(tmp_buf, 16);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cfb_decrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        memcpy(output + input_length_full_blocks,
               tmp_buf,
               input_length % 16);
      }

      *output_length = input_length - AES_IV_SIZE;
      break;
    }
    case PSA_ALG_OFB: {
      // Check buffer sizes.
      if (output_size < input_length - AES_IV_SIZE) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Move IV into tmp buffer in order to avoid messing up output (in case of overlap with input).
      memcpy(tmp_buf, input, AES_IV_SIZE);

      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(tmp_buf, AES_IV_SIZE);

      size_t input_length_full_blocks = ((input_length - AES_IV_SIZE) / 16) * 16;

      // Process full blocks.
      if (input_length_full_blocks > 0) {
        data_in = block_t_convert(input + AES_IV_SIZE,
                                  input_length_full_blocks);
        data_out = block_t_convert(output, input_length_full_blocks);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_ofb_decrypt_update((const block_t*)&key,
                                           (const block_t*)&data_in,
                                           &data_out,
                                           (const block_t*)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Process final bytes.
      if (input_length % 16 != 0) {
        data_in = block_t_convert(input + AES_IV_SIZE + input_length_full_blocks,
                                  16);
        data_out = block_t_convert(tmp_buf, 16);

        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_ofb_decrypt((const block_t*)&key,
                                    (const block_t*)&data_in,
                                    &data_out,
                                    (const block_t*)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        memcpy(output + input_length_full_blocks,
               tmp_buf,
               input_length % 16);
      }

      *output_length = input_length - AES_IV_SIZE;
      break;
    }
    case PSA_ALG_CBC_NO_PADDING:
    // fall through
    case PSA_ALG_CBC_PKCS7: {
      size_t input_length_full_blocks;
      uint8_t iv_buf[AES_IV_SIZE];

      // We cannot do CBC decryption on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (alg == PSA_ALG_CBC_NO_PADDING) {
        if (output_size < input_length - AES_IV_SIZE) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        input_length_full_blocks = ((input_length - AES_IV_SIZE) / 16) * 16;
      } else {
        // Check output has enough room for at least n-1 blocks.
        if (input_length < AES_IV_SIZE + 16
            || output_size < (input_length - AES_IV_SIZE - 16)) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        input_length_full_blocks = ((input_length - AES_IV_SIZE - 16) / 16) * 16;
      }

      // Write IV to temporary buf to be used by sx_aes_cbc_decrypt_update.
      memcpy(iv_buf, input, AES_IV_SIZE);
      key = block_t_convert(key_buffer, key_buffer_size);
      iv_block = block_t_convert(iv_buf, AES_IV_SIZE);

      if (input_length_full_blocks > 0) {
        data_in = block_t_convert(input + AES_IV_SIZE,
                                  input_length_full_blocks);
        data_out = block_t_convert(output, input_length_full_blocks);

        // CBC-decrypt all but the last block.
        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cbc_decrypt_update((const block_t *)&key,
                                           (const block_t *)&data_in,
                                           &data_out,
                                           (const block_t *)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
      }

      // Process final block.
      if (alg == PSA_ALG_CBC_PKCS7) {
        // Store last block to temporary buffer to be used in removing the padding.
        memcpy(tmp_buf, &input[input_length - 16], 16);

        data_in = block_t_convert(tmp_buf, 16);
        data_out = block_t_convert(tmp_buf, 16);

        // CBC-decrypt the last block.
        status = cryptoacc_management_acquire();
        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }
        sx_ret = sx_aes_cbc_decrypt_update((const block_t *)&key,
                                           (const block_t *)&data_in,
                                           &data_out,
                                           (const block_t *)&iv_block,
                                           &iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        // Check how many bytes of padding to subtract.
        uint8_t pad_bytes = tmp_buf[15];
        if (pad_bytes == 0 || pad_bytes > 16) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (output_size < (input_length - AES_IV_SIZE - pad_bytes)) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }

        // Check all padding bytes.
        for (size_t i = pad_bytes; i > 0; i--) {
          if (tmp_buf[16 - pad_bytes] != pad_bytes) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
        }

        // Copy non-padding bytes.
        memcpy(&output[input_length_full_blocks], tmp_buf, 16 - pad_bytes);

        *output_length = input_length - AES_IV_SIZE - pad_bytes;
      } else {
        *output_length = input_length - AES_IV_SIZE;
      }
      break;
    }
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_cipher_encrypt_setup(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                            const psa_key_attributes_t *attributes,
                                                            const uint8_t *key_buffer,
                                                            size_t key_buffer_size,
                                                            psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context.
  memset(operation, 0, sizeof(sli_cryptoacc_transparent_cipher_operation_t));

  // Set up context.
  memcpy(&operation->alg, &alg, sizeof(alg));
  operation->direction = ENC;

  // Validate combination of key and algorithm.
  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Copy key into context.
  switch (psa_get_key_bits(attributes)) {
    case 128:
      if (key_buffer_size < 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 16);
      operation->key_len = 16;
      break;
    case 192:
      if (key_buffer_size < 24) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 24);
      operation->key_len = 24;
      break;
    case 256:
      if (key_buffer_size < 32) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 32);
      operation->key_len = 32;
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_cipher_decrypt_setup(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                            const psa_key_attributes_t *attributes,
                                                            const uint8_t *key_buffer,
                                                            size_t key_buffer_size,
                                                            psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context.
  memset(operation, 0, sizeof(sli_cryptoacc_transparent_cipher_operation_t));

  // Set up context.
  memcpy(&operation->alg, &alg, sizeof(alg));
  operation->direction = DEC;

  // Validate combination of key and algorithm.
  switch (alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Copy key into context.
  switch (psa_get_key_bits(attributes)) {
    case 128:
      if (key_buffer_size < 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 16);
      operation->key_len = 16;
      break;
    case 192:
      if (key_buffer_size < 24) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 24);
      operation->key_len = 24;
      break;
    case 256:
      if (key_buffer_size < 32) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 32);
      operation->key_len = 32;
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_cipher_generate_iv(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                          uint8_t *iv,
                                                          size_t iv_size,
                                                          size_t *iv_length)
{
  if (operation == NULL || iv == NULL || iv_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Generate & output random IV (output because application may want to record and/or transmit IV).
  if (operation->iv_len != 0) {
    // IV was set previously.
    return PSA_ERROR_BAD_STATE;
  }

  if (operation->key_len == 0) {
    // context hasn't been properly initialised.
    return PSA_ERROR_BAD_STATE;
  }

  // Same IV size for all modes except GCM.
  if (iv_size < AES_IV_SIZE) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Generate IV.
  int trng_ret = mbedtls_hardware_poll(NULL, iv, AES_IV_SIZE, iv_length);
  if (trng_ret != 0) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return sli_cryptoacc_transparent_cipher_set_iv(operation, iv, *iv_length);
}

psa_status_t sli_cryptoacc_transparent_cipher_set_iv(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                     const uint8_t *iv,
                                                     size_t iv_length)
{
  if (operation == NULL || iv == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (iv_length > sizeof(operation->iv)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->iv_len != 0) {
    // IV was set previously.
    return PSA_ERROR_BAD_STATE;
  }

  if (operation->key_len == 0) {
    // context hasn't been properly initialised.
    return PSA_ERROR_BAD_STATE;
  }

  operation->iv_len = iv_length;

  memcpy(operation->iv, iv, iv_length);
  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_cipher_update(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                     const uint8_t *input,
                                                     size_t input_length,
                                                     uint8_t *output,
                                                     size_t output_size,
                                                     size_t *output_length)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t key;
  block_t iv_block;
  block_t data_in;
  block_t data_out;
  block_t tmp_iv_block;
  uint8_t tmp_buf[16];

  // Argument check.
  if (operation == NULL
      || input == NULL
      || output == NULL
      || output_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check if IV has been set.
  if ((operation->alg != PSA_ALG_ECB_NO_PADDING)
      && (operation->iv_len == 0)) {
    return PSA_ERROR_BAD_STATE;
  }

  // Figure out whether the operation is on a lagging or forward-looking cipher
  // Lagging: needs a full block of input data before being able to output
  // Non-lagging: can output the same amount of data as getting fed
  bool lagging = true;
  switch (operation->alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      lagging = true;
      break;
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
      lagging = false;
      break;
    default:
      return PSA_ERROR_BAD_STATE;
  }

  size_t bytes_to_boundary = 16 - (operation->processed_length % 16);
  size_t actual_output_length = 0;
  *output_length = 0;

  // We need to cache (not return) the whole last block for decryption with
  // padding, otherwise it won't be possible to remove a potential padding block
  // during finish.
  bool cache_full_block = (operation->alg == PSA_ALG_CBC_PKCS7
                           && operation->direction == DEC);

  // Early processing if not getting to a full block for lagging ciphers.
  if (lagging) {
    if (cache_full_block
        && bytes_to_boundary == 16
        && operation->processed_length > 0) {
      // Don't overwrite the streaming block if it's currently full.
    } else {
      if (input_length < bytes_to_boundary) {
        memcpy(&operation->streaming_block[operation->processed_length % 16],
               input,
               input_length);
        operation->processed_length += input_length;
        *output_length = actual_output_length;
        return PSA_SUCCESS;
      }
    }
  }

  // Early failure if output buffer is too small. Failing here prevents messing
  // with the context, such that operation can be retried with larger output buffer
  if (lagging) {
    size_t output_blocks = ((input_length + operation->processed_length) / 16) - (operation->processed_length / 16);
    if (output_size < output_blocks) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
  } else {
    if (output_size < input_length) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
  }

  // Our drivers only support full or no overlap between input and output
  // buffers. So in the case of partial overlap, copy the input buffer into
  // the output buffer and process it in place as if the buffers fully
  // overlapped.
  if ((output > input) && (output < (input + input_length))) {
    // Sanity check before copying. Some ciphers have a stricter requirement
    // than this (if an IV is included), but no ciphers will have an output
    // smaller than the input.
    if (output_size < input_length) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    memmove(output, input, input_length);
    input = output;
  }

  key = block_t_convert(operation->key, operation->key_len);
  iv_block = block_t_convert(operation->iv, operation->iv_len);
  tmp_iv_block = block_t_convert(tmp_buf, 16);

  if (bytes_to_boundary != 16) {
    // Read in up to full streaming input block.
    memcpy(&operation->streaming_block[operation->processed_length % 16],
           input,
           bytes_to_boundary);

    data_in = block_t_convert(operation->streaming_block, 16);
    data_out = block_t_convert(operation->streaming_block, 16);

    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    if (operation->direction == ENC) {
      switch (operation->alg) {
        case PSA_ALG_ECB_NO_PADDING:
          sx_ret = sx_aes_ecb_encrypt((const block_t*)&key,
                                      (const block_t*)&data_in,
                                      &data_out);
          break;
        case PSA_ALG_CTR:
          sx_ret = sx_aes_ctr_encrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_CFB:
          sx_ret = sx_aes_cfb_encrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_OFB:
          sx_ret = sx_aes_ofb_encrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_CBC_NO_PADDING:
          sx_ret = sx_aes_cbc_encrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &iv_block);
          break;
        case PSA_ALG_CBC_PKCS7:
          if (cache_full_block && (bytes_to_boundary == input_length)) {
            // Don't process the streaming block if there is no more input data
            sx_ret = CRYPTOLIB_SUCCESS;
          } else {
            sx_ret = sx_aes_cbc_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
          }
          break;
      }
    } else {
      switch (operation->alg) {
        case PSA_ALG_ECB_NO_PADDING:
          sx_ret = sx_aes_ecb_decrypt((const block_t*)&key,
                                      (const block_t*)&data_in,
                                      &data_out);
          break;
        case PSA_ALG_CTR:
          sx_ret = sx_aes_ctr_decrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_CFB:
          sx_ret = sx_aes_cfb_decrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_OFB:
          sx_ret = sx_aes_ofb_decrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &tmp_iv_block);
          break;
        case PSA_ALG_CBC_NO_PADDING:
          sx_ret = sx_aes_cbc_decrypt_update((const block_t*)&key,
                                             (const block_t*)&data_in,
                                             &data_out,
                                             (const block_t*)&iv_block,
                                             &iv_block);
          break;
        case PSA_ALG_CBC_PKCS7:
          if (cache_full_block && (bytes_to_boundary == input_length)) {
            // Don't process the streaming block if there is no more input data
            sx_ret = CRYPTOLIB_SUCCESS;
          } else {
            sx_ret = sx_aes_cbc_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
          }
          break;
      }
    }
    status = cryptoacc_management_release();
    if (sx_ret != CRYPTOLIB_SUCCESS
        || status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    if (lagging) {
      memcpy(output, operation->streaming_block, 16);
      // Don't increase output if no encryption/decryption was done
      if (!(cache_full_block && (bytes_to_boundary == input_length))) {
        output += 16;
        actual_output_length += 16;
      }
      operation->processed_length += bytes_to_boundary;
      input += bytes_to_boundary;
      input_length -= bytes_to_boundary;
    } else {
      if (input_length < bytes_to_boundary) {
        bytes_to_boundary = input_length;
      }

      memcpy(output, operation->streaming_block + (operation->processed_length % 16), bytes_to_boundary);
      output += bytes_to_boundary;
      actual_output_length += bytes_to_boundary;
      operation->processed_length += bytes_to_boundary;
      input += bytes_to_boundary;
      input_length -= bytes_to_boundary;

      // Only want to update IV if we actually finished an entire block.
      if (operation->processed_length % 16 == 0) {
        if (operation->alg == PSA_ALG_CFB) {
          if (operation->direction == ENC) {
            memcpy(operation->iv, output - 16, 16);
          } else {
            memcpy(operation->iv, input - 16, 16);
          }
        } else {
          memcpy(operation->iv, tmp_buf, 16);
        }
      }
    }
  }

  // Do multi-block operation if applicable.
  if (input_length >= 16) {
    size_t operation_size = (input_length / 16) * 16;

    if (cache_full_block && (input_length % 16 == 0)) {
      // Don't decrypt the last block until finish is called, so that we
      // can properly remove the padding before returning it.
      operation_size -= 16;
    }

    if (operation_size > 0) {
      data_in = block_t_convert(input, operation_size);
      data_out = block_t_convert(output, operation_size);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      if (operation->direction == ENC) {
        switch (operation->alg) {
          case PSA_ALG_ECB_NO_PADDING:
            sx_ret = sx_aes_ecb_encrypt((const block_t*)&key,
                                        (const block_t*)&data_in,
                                        &data_out);
            break;
          case PSA_ALG_CTR:
            sx_ret = sx_aes_ctr_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_CFB:
            sx_ret = sx_aes_cfb_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_OFB:
            sx_ret = sx_aes_ofb_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_CBC_NO_PADDING:
          // fall through
          case PSA_ALG_CBC_PKCS7:
            sx_ret = sx_aes_cbc_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
        }
      } else {
        switch (operation->alg) {
          case PSA_ALG_ECB_NO_PADDING:
            sx_ret = sx_aes_ecb_decrypt((const block_t*)&key,
                                        (const block_t*)&data_in,
                                        &data_out);
            break;
          case PSA_ALG_CTR:
            sx_ret = sx_aes_ctr_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_CFB:
            sx_ret = sx_aes_cfb_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_OFB:
            sx_ret = sx_aes_ofb_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
          case PSA_ALG_CBC_NO_PADDING:
          // fall through
          case PSA_ALG_CBC_PKCS7:
            sx_ret = sx_aes_cbc_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &iv_block);
            break;
        }
      }
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
    }

    input += operation_size;
    input_length -= operation_size;
    actual_output_length += operation_size;
    output += operation_size;
    operation->processed_length += operation_size;
  }

  // Process final block.
  if (input_length > 0) {
    if (!lagging) {
      data_in = block_t_convert(input, 16);
      data_out = block_t_convert(operation->streaming_block, 16);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      if (operation->direction == ENC) {
        switch (operation->alg) {
          case PSA_ALG_CTR:
            sx_ret = sx_aes_ctr_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
          case PSA_ALG_CFB:
            sx_ret = sx_aes_cfb_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
          case PSA_ALG_OFB:
            sx_ret = sx_aes_ofb_encrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
        }
      } else {
        switch (operation->alg) {
          case PSA_ALG_CTR:
            sx_ret = sx_aes_ctr_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
          case PSA_ALG_CFB:
            sx_ret = sx_aes_cfb_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
          case PSA_ALG_OFB:
            sx_ret = sx_aes_ofb_decrypt_update((const block_t*)&key,
                                               (const block_t*)&data_in,
                                               &data_out,
                                               (const block_t*)&iv_block,
                                               &tmp_iv_block);
            break;
        }
      }
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      memcpy(output,
             operation->streaming_block,
             input_length);

      actual_output_length += input_length;
      operation->processed_length += input_length;
    } else {
      if ((input_length >= 16 && !cache_full_block)
          || (input_length > 16 && cache_full_block)) {
        *output_length = 0;
        return PSA_ERROR_BAD_STATE;
      }
      memcpy(operation->streaming_block,
             input,
             input_length);
      operation->processed_length += input_length;
    }
  }

  *output_length = actual_output_length;
  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_cipher_finish(sli_cryptoacc_transparent_cipher_operation_t *operation,
                                                     uint8_t *output,
                                                     size_t output_size,
                                                     size_t *output_length)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
  block_t key;
  block_t iv_block;
  block_t data_in;
  block_t data_out;

  // Argument check.
  if (operation == NULL) {
    *output_length = 0;
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  switch (operation->alg) {
    // Blocksize-only modes without padding.
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CBC_NO_PADDING:
      // Can't finish if they haven't processed block-size input.
      if (operation->processed_length % 16 != 0) {
        status = PSA_ERROR_INVALID_ARGUMENT;
      } else {
        status = PSA_SUCCESS;
      }
      *output_length = 0;
      break;
    // Stream cipher modes.
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
      status = PSA_SUCCESS;
      *output_length = 0;
      break;
    // Padding mode.
    case PSA_ALG_CBC_PKCS7:
      if (output == NULL
          || output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      if (output_size < 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      key = block_t_convert(operation->key, operation->key_len);
      iv_block = block_t_convert(operation->iv, operation->iv_len);
      data_in = block_t_convert(operation->streaming_block, 16);
      data_out = block_t_convert(output, 16);

      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      if (operation->direction == ENC) {
        size_t padding_bytes = 16 - (operation->processed_length % 16);
        memset(&operation->streaming_block[16 - padding_bytes],
               padding_bytes,
               padding_bytes);

        sx_ret = sx_aes_cbc_encrypt((const block_t *)&key,
                                    (const block_t *)&data_in,
                                    &data_out,
                                    (const block_t *)&iv_block);
        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          status = PSA_ERROR_HARDWARE_FAILURE;
        } else {
          *output_length = 16;
          status = PSA_SUCCESS;
        }
      } else {
        // Expect full-block input.
        if (operation->processed_length % 16 != 0
            || operation->processed_length < 16) {
          status = PSA_ERROR_INVALID_ARGUMENT;
          break;
        }

        uint8_t out_buf[16];
        block_t out_buf_block = block_t_convert(&out_buf, 16);

        // Decrypt the last block
        sx_ret = sx_aes_cbc_decrypt((const block_t *)&key,
                                    (const block_t *)&data_in,
                                    &out_buf_block,
                                    (const block_t *)&iv_block);

        status = cryptoacc_management_release();
        if (sx_ret != CRYPTOLIB_SUCCESS
            || status != PSA_SUCCESS) {
          status = PSA_ERROR_HARDWARE_FAILURE;
          break;
        }

        size_t invalid_padding = 0;
        size_t padding_bytes = out_buf[15];

        // Check that the last padding byte is valid (in the range 0x1 to 0x10).
        // Note that the below checks are valid for both partial block padding
        // and complete padding blocks.
        invalid_padding = 0;
        invalid_padding |= (padding_bytes > 0x10);
        invalid_padding |= (padding_bytes == 0);

        // Check that every padding byte is correct (equal to padding_bytes)
        size_t pad_index = 16 - padding_bytes;
        for (size_t i = 0; i < 16; ++i) {
          // The number of checks should be independent of padding_bytes,
          // so use pad_index instead to make the result zero for non-padding
          // bytes in out_buf.
          invalid_padding |= (out_buf[i] ^ padding_bytes) * (i >= pad_index);
        }

        if (invalid_padding == 0) {
          // The padding was valid
          memcpy(output, out_buf, 16 - padding_bytes);
          *output_length = 16 - padding_bytes;
          status = PSA_SUCCESS;
        } else {
          status = PSA_ERROR_INVALID_PADDING;
        }
      }
      break;
    default:
      status = PSA_ERROR_BAD_STATE;
      break;
  }

  if (status != PSA_SUCCESS) {
    *output_length = 0;
  }

  // Wipe context.
  memset(operation, 0, sizeof(sli_cryptoacc_transparent_cipher_operation_t));

  return status;
}

psa_status_t sli_cryptoacc_transparent_cipher_abort(sli_cryptoacc_transparent_cipher_operation_t *operation)
{
  if (operation != NULL) {
    // Wipe context.
    memset(operation, 0, sizeof(*operation));
  }

  return PSA_SUCCESS;
}

#endif // defined(CRYPTOACC_PRESENT)
