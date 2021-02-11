#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "psa/crypto.h"
#include "sli_se_driver_cipher.h"
#include "mbedtls/entropy_poll.h"

#include "sl_se_manager.h"
#include "sl_se_manager_cipher.h"
#include "sl_se_manager_entropy.h"

#include "sli_se_driver_key_management.h"

#include <string.h>

/**
 * @brief
 *   Validate that the given key desc has the correct properties
 *   to be used for a cipher operation
 * @param key_desc
 *   Pointer to a key descriptor
 * @return
 *   PSA_SUCCESS if all is good
 *   PSA_ERROR_INVALID_ARGUMENT otherwise
 */
static psa_status_t validate_key_type(const sl_se_key_descriptor_t *key_desc)
{
  sl_se_key_type_t sl_key_type = key_desc->type;
  // Check with if (..) since switch does not support multiple equal entries
  // (AES 256 and CHACHA20 has same sl_key_type value)
  if (sl_key_type == SL_SE_KEY_TYPE_AES_128
      || sl_key_type == SL_SE_KEY_TYPE_AES_192
      || sl_key_type == SL_SE_KEY_TYPE_AES_256
      #if _SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT
      || sl_key_type == SL_SE_KEY_TYPE_CHACHA20
      #endif // VAULT
      ) {
    return PSA_SUCCESS;
  }

  return PSA_ERROR_INVALID_ARGUMENT;
}

// Validate combination of key and algorithm
static psa_status_t
validate_key_algorithm_match(psa_algorithm_t alg,
                             const psa_key_attributes_t *attributes)
{
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
    #if _SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT
      // ChaCha20 is not supported yet. Tracked in CRDSW-8947
      // case PSA_ALG_CHACHA20:
      //   if (psa_get_key_type(attributes) != PSA_KEY_TYPE_CHACHA20) {
      //     return PSA_ERROR_INVALID_ARGUMENT;
      //   }
      //   break;
    #endif // VAULT
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  return PSA_SUCCESS;
}

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
psa_status_t sli_se_driver_cipher_encrypt(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *input,
                                          size_t input_length,
                                          uint8_t *output,
                                          size_t output_size,
                                          size_t *output_length)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  int trng_ret = -1;
  uint8_t tmp_buf[16] = { 0 };
  uint8_t iv_buf[16] = { 0 };
  uint8_t final_block[16] = { 0 };
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

  psa_status_t psa_status = validate_key_algorithm_match(alg, attributes);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_se_key_descriptor_t key_desc = { 0 };

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  psa_status = sli_se_key_desc_from_input(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  psa_status = validate_key_type(&key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
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
    case PSA_ALG_ECB_NO_PADDING:
      // Check buffer sizes
      if (output_size < input_length) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // We cannot do ECB on non-block sizes
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // do the operation
      status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                   &key_desc,
                                   SL_SE_ENCRYPT,
                                   input_length,
                                   input,
                                   output);
      *output_length = input_length;
      break;
    case PSA_ALG_CTR:
      // Check buffer sizes
      if (output_size < input_length + 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Generate nonce.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, 16, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Write nonce to temporary buf to be used internally by sl_se_aes_crypt_ctr.
      memcpy(tmp_buf, iv_buf, 16);

      // Store final block in a temporary buffer in order to avoid in being overwritten
      // inside of sl_se_aes_crypt_ctr() (hence the separation into two calls).
      if ((input_length & 0x0F) > 0) {
        memcpy(final_block, &input[input_length & ~0x0F], 16);
      }

      // Do multi-block operation if applicable.
      if ((input_length & ~0x0F) > 0) {
        status = sl_se_aes_crypt_ctr(&cmd_ctx,
                                     &key_desc,
                                     input_length & ~0x0F,
                                     NULL,
                                     tmp_buf,
                                     tmp_buf,
                                     input,
                                     &output[16]);
      }

      // Encrypt final block if there is any.
      if ((input_length & 0x0F) > 0) {
        status = sl_se_aes_crypt_ctr(&cmd_ctx,
                                     &key_desc,
                                     input_length & 0x0F,
                                     NULL,
                                     tmp_buf,
                                     tmp_buf,
                                     final_block,
                                     &output[16 + (input_length & ~0x0F)]);
      }

      // Write IV to output.
      memcpy(output, iv_buf, 16);

      *output_length = input_length + 16;
      break;
    case PSA_ALG_CFB:
      // Check buffer sizes
      if (output_size < input_length + 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, 16, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_cbf128.
      memcpy(tmp_buf, iv_buf, 16);

      // Store final block in a temporary buffer in order to avoid in being overwritten
      // inside of sl_se_aes_crypt_ctr() (hence the separation into two calls).
      if ((input_length & 0x0F) > 0) {
        memcpy(final_block, &input[input_length & ~0x0F], 16);
      }

      // Do multi-block operation if applicable.
      if ((input_length & ~0x0F) > 0) {
        status = sl_se_aes_crypt_cfb128(&cmd_ctx,
                                        &key_desc,
                                        SL_SE_ENCRYPT,
                                        input_length & ~0x0F,
                                        NULL,
                                        tmp_buf,
                                        input,
                                        &output[16]);
      }

      // Encrypt final block if there is any.
      if ((input_length & 0x0F) > 0) {
        status = sl_se_aes_crypt_cfb128(&cmd_ctx,
                                        &key_desc,
                                        SL_SE_ENCRYPT,
                                        input_length & 0x0F,
                                        NULL,
                                        tmp_buf,
                                        final_block,
                                        &output[16 + (input_length & ~0x0F)]);
      }

      // Write IV to output.
      memcpy(output, iv_buf, 16);

      *output_length = input_length + 16;
      break;
    case PSA_ALG_OFB:
    {
      // Check buffer sizes
      if (output_size < input_length + 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, 16, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_ecb.
      memcpy(tmp_buf, iv_buf, 16);

      size_t data_length = input_length;
      size_t n = 0;

      // Use final_block as a temporary storage in order to avoid input being
      // overwritten by the output (in case of buffer overlap).
      memcpy(final_block, input, 16);

      // Loop over input data to create output.
      do {
        if (n == 0) {
          status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                       &key_desc,
                                       SL_SE_ENCRYPT,
                                       16,
                                       tmp_buf,
                                       tmp_buf);
          if (status != SL_STATUS_OK) {
            goto exit;
          }
        }
        uint8_t tmp_input_val = final_block[n];
        final_block[n] = input[16 + input_length - data_length];
        output[16 + input_length - data_length] = tmp_input_val ^ tmp_buf[n];
        n = (n + 1) & 0x0F;
      } while (data_length--);

      // Write IV to output.
      memcpy(output, iv_buf, 16);

      *output_length = input_length + 16;
    }
    break;
    case PSA_ALG_CBC_NO_PADDING:
      // We cannot do CBC without padding on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    // fall through
    case PSA_ALG_CBC_PKCS7:
      // Check buffer sizes
      if (alg == PSA_ALG_CBC_NO_PADDING) {
        if (output_size < input_length + 16) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
      } else {
        if (output_size < 16 + (input_length & ~0xF) + 16) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
      }

      // Generate IV.
      trng_ret = mbedtls_hardware_poll(NULL, iv_buf, 16, &iv_length);
      if (trng_ret != 0) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      // Store last block (if non-blocksize input-length) to temporary buffer to be used in padding.
      if (alg == PSA_ALG_CBC_PKCS7) {
        memcpy(final_block, &input[input_length & ~0xF], input_length & 0xF);
      }

      // CBC-encrypt all but the last block
      if (input_length >= 16) {
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     &key_desc,
                                     SL_SE_ENCRYPT,
                                     input_length & ~0xF,
                                     iv_buf,
                                     input,
                                     &output[16]);
        if (status != SL_STATUS_OK) {
          goto exit;
        }
      }

      // Write IV to output.
      memcpy(output, iv_buf, 16);

      // Process final block.
      if (alg == PSA_ALG_CBC_PKCS7) {
        // Add PKCS7 padding.
        memset(&final_block[input_length & 0xF], 16 - (input_length & 0xF), 16 - (input_length & 0xF));

        // Store IV (last ciphertext block) in temp buffer to avoid messing up output.
        memcpy(iv_buf, &output[16 + (input_length & ~0xF) - 16], 16);

        // CBC-encrypt the last block.
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     &key_desc,
                                     SL_SE_ENCRYPT,
                                     16,
                                     iv_buf,
                                     final_block,
                                     final_block);

        // Copy to output.
        memcpy(&output[16 + (input_length & ~0xF)], final_block, 16);
        *output_length = 16 + (input_length & ~0xF) + 16;
      } else {
        *output_length = 16 + input_length;
      }
      break;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ALG_CHACHA20:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_CHACHA20) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // check buffer sizes
      if (output_size < input_length + 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // generate IV and write to output
      status = sl_se_get_random(&cmd_ctx, output, 12);
      if (status != SL_STATUS_OK) {
        goto exit;
      }

      // set initial counter to 1 (preferred by RFC8439)
      output[12] = 0;
      output[13] = 0;
      output[14] = 0;
      output[15] = 1;

      status = sl_se_chacha20_crypt(&cmd_ctx,
                                    SL_SE_ENCRYPT,
                                    &key_desc,
                                    input_length,
                                    &output[12],
                                    output,
                                    input,
                                    &output[16]);

      *output_length = 16 + input_length;
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  exit:
  if (status != SL_STATUS_OK) {
    memset(output, 0, output_size);
    *output_length = 0;
    if (status == SL_STATUS_FAIL) {
      // This specific code maps to 'does not exist' for builtin keys
      return PSA_ERROR_DOES_NOT_EXIST;
    } else {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    return PSA_SUCCESS;
  }
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
psa_status_t sli_se_driver_cipher_decrypt(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *input,
                                          size_t input_length,
                                          uint8_t *output,
                                          size_t output_size,
                                          size_t *output_length)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  uint8_t tmp_buf[16] = { 0 };
  uint8_t iv_buf[16] = { 0 };

  // Argument check.
  if (key_buffer == NULL
      || key_buffer_size == 0
      || input == NULL
      || input_length == 0
      || output == NULL
      || output_length == NULL
      || output_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t psa_status = validate_key_algorithm_match(alg, attributes);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Ephemeral contexts.
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_se_key_descriptor_t key_desc = { 0 };

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  psa_status = sli_se_key_desc_from_input(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  psa_status = validate_key_type(&key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
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
    case PSA_ALG_ECB_NO_PADDING:
      // Check buffer sizes.
      if (output_size < input_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // We cannot do ECB on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Do the operation.
      status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                   &key_desc,
                                   SL_SE_DECRYPT,
                                   input_length,
                                   input,
                                   output);

      *output_length = input_length;
      break;
    case PSA_ALG_CTR:
      // Check buffer sizes.
      if (output_size < input_length - 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_ctr.
      memcpy(iv_buf, input, 16);

      status = sl_se_aes_crypt_ctr(&cmd_ctx,
                                   &key_desc,
                                   input_length - 16,
                                   NULL,
                                   iv_buf,
                                   tmp_buf,
                                   &input[16],
                                   output);

      *output_length = input_length - 16;
      break;
    case PSA_ALG_CFB:
      // Check buffer sizes.
      if (output_size < input_length - 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_cfb128.
      memcpy(iv_buf, input, 16);

      status = sl_se_aes_crypt_cfb128(&cmd_ctx,
                                      &key_desc,
                                      SL_SE_DECRYPT,
                                      input_length - 16,
                                      NULL,
                                      iv_buf,
                                      &input[16],
                                      output);

      *output_length = input_length - 16;
      break;
    case PSA_ALG_OFB:
    {
      // Check buffer sizes.
      if (output_size < input_length - 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_ecb.
      memcpy(iv_buf, input, 16);

      input += 16;
      size_t data_length = input_length - 16;
      size_t n = 0;

      // Loop over input data to create output.
      while (data_length--) {
        if (n == 0) {
          status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                       &key_desc,
                                       SL_SE_ENCRYPT,
                                       16,
                                       iv_buf,
                                       iv_buf);
          if (status != SL_STATUS_OK) {
            goto exit;
          }
        }
        *output++ = *input++ ^ iv_buf[n];

        n = (n + 1) & 0x0F;
      }

      *output_length = input_length - 16;
    }
    break;
    case PSA_ALG_CBC_NO_PADDING:
      // We cannot do CBC without padding on non-block sizes.
      if (input_length % 16 != 0) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
    // fall through
    case PSA_ALG_CBC_PKCS7: {
      size_t full_blocks;
      if (alg == PSA_ALG_CBC_NO_PADDING) {
        if (output_size < input_length - 16) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        full_blocks = (input_length - 16) / 16;
      } else {
        // Check output has enough room for at least n-1 blocks.
        if (input_length < 32
            || ((input_length & 0xF) != 0)
            || output_size < (input_length - 32)) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }
        full_blocks = (input_length - 32) / 16;
      }

      // Write IV to temporary buf to be used internally by sl_se_aes_crypt_cbc.
      memcpy(iv_buf, input, 16);

      // CBC-decrypt all but the last block.
      if (full_blocks > 0) {
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     &key_desc,
                                     SL_SE_DECRYPT,
                                     full_blocks * 16,
                                     iv_buf,
                                     &input[16],
                                     output);
        if (status != SL_STATUS_OK) {
          goto exit;
        }
      }

      // Process final block.
      if (alg == PSA_ALG_CBC_PKCS7) {
        // Store last block to temporary buffer to be used in removing the padding.
        memcpy(tmp_buf, &input[input_length - 16], 16);

        // CBC-decrypt the last block.
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     &key_desc,
                                     SL_SE_DECRYPT,
                                     16,
                                     iv_buf,
                                     tmp_buf,
                                     tmp_buf);

        // Check how many bytes of padding to subtract.
        uint8_t pad_bytes = tmp_buf[15];
        if (pad_bytes == 0 || pad_bytes > 16) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        if (output_size < (input_length - 16 - pad_bytes)) {
          return PSA_ERROR_BUFFER_TOO_SMALL;
        }

        // Check all padding bytes.
        for (size_t i = pad_bytes; i > 0; i--) {
          if (tmp_buf[16 - pad_bytes] != pad_bytes) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
        }

        // Copy non-padding bytes.
        memcpy(&output[full_blocks * 16], tmp_buf, 16 - pad_bytes);
        *output_length = input_length - 16 - pad_bytes;
      } else {
        *output_length = input_length - 16;
      }
      break;
    }
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ALG_CHACHA20:
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_CHACHA20) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // check buffer sizes.
      if (output_size < input_length - 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = sl_se_chacha20_crypt(&cmd_ctx,
                                    SL_SE_ENCRYPT,
                                    &key_desc,
                                    input_length,
                                    &input[12],
                                    input,
                                    &input[16],
                                    output);

      *output_length = input_length - 16;
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  exit:
  if (status != SL_STATUS_OK) {
    memset(output, 0, output_size);
    *output_length = 0;
    if (status == SL_STATUS_FAIL) {
      // This specific code maps to 'does not exist' for builtin keys
      return PSA_ERROR_DOES_NOT_EXIST;
    } else {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    return PSA_SUCCESS;
  }
}

psa_status_t sli_se_driver_cipher_encrypt_setup(sli_se_driver_cipher_operation_t *operation,
                                                const psa_key_attributes_t *attributes,
                                                psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context
  memset(operation, 0, sizeof(*operation));

  // Set up context
  memcpy(&operation->alg, &alg, sizeof(alg));
  operation->direction = SL_SE_ENCRYPT;

  // Validate combination of key and algorithm
  return validate_key_algorithm_match(alg, attributes);
}

psa_status_t sli_se_driver_cipher_decrypt_setup(sli_se_driver_cipher_operation_t *operation,
                                                const psa_key_attributes_t *attributes,
                                                psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context
  memset(operation, 0, sizeof(*operation));

  // Set up context
  memcpy(&operation->alg, &alg, sizeof(alg));
  operation->direction = SL_SE_DECRYPT;

  // Validate combination of key and algorithm
  return validate_key_algorithm_match(alg, attributes);
}

psa_status_t sli_se_driver_cipher_generate_iv(sli_se_driver_cipher_operation_t *operation,
                                              uint8_t *iv,
                                              size_t iv_size,
                                              size_t *iv_length)
{
  if (operation == NULL || iv == NULL || iv_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Generate & output random IV (output because application may want to record and/or transmit IV)
  if (operation->iv_len != 0) {
    // IV was set previously
    return PSA_ERROR_BAD_STATE;
  }

  // Todo: do any of the supported algorithms have a shorter IV length?
  if (iv_size < 16) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  int trng_ret = mbedtls_hardware_poll(NULL, iv, iv_size, iv_length);
  if (trng_ret != 0) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *iv_length = 16;

  // Set generated IV as current IV
  return sli_se_driver_cipher_set_iv(operation, iv, *iv_length);
}

psa_status_t sli_se_driver_cipher_set_iv(sli_se_driver_cipher_operation_t *operation,
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
    // IV was set previously
    return PSA_ERROR_BAD_STATE;
  }

  memcpy(operation->iv, iv, iv_length);
  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_cipher_update(sli_se_driver_cipher_operation_t *operation,
                                         const uint8_t *input,
                                         size_t input_length,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length)
{
  // Argument check
  if (operation == NULL
      || (input == NULL && input_length > 0)
      || output == NULL
      || output_length == NULL
      || output_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Key desc has been properly set by wrapper function
  const sl_se_key_descriptor_t *key_desc = &operation->key_desc;
  psa_status_t psa_status = validate_key_type(key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  bool lagging;
  size_t bytes_to_boundary = 16 - (operation->processed_length % 16);
  size_t actual_output_length = 0;

  // We need to cache (not return) the whole last block for decryption with
  // padding, otherwise it won't be possible to remove a potential padding block
  // during finish.
  bool cache_full_block = (operation->alg == PSA_ALG_CBC_PKCS7
                           && operation->direction == SL_SE_DECRYPT);

  // Figure out whether the operation is on a lagging or forward-looking cipher
  // Lagging: needs a full block of input data before being able to output
  // Non-lagging: can output the same amount of data as getting fed
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

  if (input_length == 0) {
    // We don't need to do anything if the input length is zero.
    *output_length = 0;
    return PSA_SUCCESS;
  }

  if (lagging) {
    // Early processing if not getting to a full block
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

    // Early failure if output buffer is too small. Failing here prevents messing
    // with the context, such that operation can be retried with larger output buffer
    size_t output_blocks = ((input_length + operation->processed_length) / 16) - (operation->processed_length / 16);
    if (output_size < output_blocks) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
  } else {
    // Early failure if output buffer is too small
    if (output_size < input_length) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
  }

  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
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

  switch (operation->alg) {
    case PSA_ALG_ECB_NO_PADDING:
      // Read in up to full streaming input block
      if (bytes_to_boundary != 16) {
        memcpy(&operation->streaming_block[operation->processed_length % 16],
               input,
               bytes_to_boundary);
        input += bytes_to_boundary;
        input_length -= bytes_to_boundary;

        status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                     key_desc,
                                     operation->direction,
                                     16,
                                     operation->streaming_block,
                                     output);
        if (status != SL_STATUS_OK) {
          goto exit;
        }

        output += 16;
        actual_output_length += 16;
        operation->processed_length += bytes_to_boundary;
      }

      // Do multi-block operation if applicable
      if (input_length >= 16) {
        size_t operation_size = (input_length / 16) * 16;
        status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                     key_desc,
                                     operation->direction,
                                     operation_size,
                                     input,
                                     output);

        if (status != SL_STATUS_OK) {
          goto exit;
        }

        input += operation_size;
        input_length -= operation_size;
        output += operation_size;
        actual_output_length += operation_size;
        operation->processed_length += operation_size;
      }

      // What's left over in the input buffer will be cleaned up after switch-case
      break;
    case PSA_ALG_CBC_NO_PADDING:
    case PSA_ALG_CBC_PKCS7:
      if (bytes_to_boundary != 16) {
        memcpy(&operation->streaming_block[operation->processed_length % 16],
               input,
               bytes_to_boundary);
        if (cache_full_block && (bytes_to_boundary == input_length)) {
          // Don't process the streaming block if there is no more input data
        } else {
          status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                       key_desc,
                                       operation->direction,
                                       16,
                                       operation->iv,
                                       operation->streaming_block,
                                       output);
          if (status != PSA_SUCCESS) {
            goto exit;
          }
          output += 16;
          actual_output_length += 16;
        }

        input += bytes_to_boundary;
        input_length -= bytes_to_boundary;
        operation->processed_length += bytes_to_boundary;
      }

      // Do multi-block operation if applicable
      if (input_length >= 16) {
        size_t operation_size = (input_length / 16) * 16;
        if (cache_full_block && (input_length % 16 == 0)) {
          // Don't decrypt the last block until finish is called, so that we
          // can properly remove the padding before returning it.
          operation_size -= 16;
        }

        if (operation_size > 0) {
          status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                       key_desc,
                                       operation->direction,
                                       operation_size,
                                       operation->iv,
                                       input,
                                       output);
          if (status != PSA_SUCCESS) {
            goto exit;
          }
        } else {
          status = PSA_SUCCESS;
        }

        input += operation_size;
        input_length -= operation_size;
        output += operation_size;
        actual_output_length += operation_size;
        operation->processed_length += operation_size;
      }

      // What's left over in the input buffer will be cleaned up after switch-case
      break;
    case PSA_ALG_CTR:
    {
      uint32_t offset = operation->processed_length % 16;

      status = sl_se_aes_crypt_ctr(&cmd_ctx,
                                   key_desc,
                                   input_length,
                                   &offset,
                                   operation->iv,
                                   operation->streaming_block,
                                   input,
                                   output);

      if (status != SL_STATUS_OK) {
        goto exit;
      }

      input += input_length;
      output += input_length;
      actual_output_length += input_length;
      operation->processed_length += input_length;
      input_length -= input_length;
      break;
    }
    case PSA_ALG_CFB:
    {
      uint32_t offset = operation->processed_length % 16;
      status = sl_se_aes_crypt_cfb128(&cmd_ctx,
                                      key_desc,
                                      operation->direction,
                                      input_length,
                                      &offset,
                                      operation->iv,
                                      input,
                                      output);

      if (status != SL_STATUS_OK) {
        goto exit;
      }

      input += input_length;
      output += input_length;
      actual_output_length += input_length;
      operation->processed_length += input_length;
      input_length -= input_length;
      break;
    }
    case PSA_ALG_OFB:
    {
      size_t data_length = input_length;
      size_t n = operation->processed_length % 16;

      // loop over input data to create output
      while (data_length--) {
        if (n == 0) {
          status = sl_se_aes_crypt_ecb(&cmd_ctx,
                                       key_desc,
                                       SL_SE_ENCRYPT,
                                       16,
                                       operation->iv,
                                       operation->iv);
          if (status != SL_STATUS_OK) {
            goto exit;
          }
        }
        *output++ =  *input++ ^ operation->iv[n];

        n = (n + 1) & 0x0F;
      }
    }

      input += input_length;
      output += input_length;
      actual_output_length += input_length;
      operation->processed_length += input_length;
      input_length -= input_length;
      break;
    default:
      return PSA_ERROR_BAD_STATE;
  }

  // If there's anything left in the input buffer, copy it to the context
  // This'll only be the case for lagging ciphers
  if (input_length > 0) {
    if (!lagging
        || (input_length >= 16 && !cache_full_block)
        || (input_length > 16 && cache_full_block)) {
      *output_length = 0;
      return PSA_ERROR_BAD_STATE;
    }

    memcpy(operation->streaming_block,
           input,
           input_length);
    operation->processed_length += input_length;
  }

  exit:
  if (status != SL_STATUS_OK) {
    *output_length = 0;
    if (status == SL_STATUS_FAIL) {
      // This specific code maps to 'does not exist' for builtin keys
      return PSA_ERROR_DOES_NOT_EXIST;
    } else {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    *output_length = actual_output_length;
    return PSA_SUCCESS;
  }
}

psa_status_t sli_se_driver_cipher_finish(sli_se_driver_cipher_operation_t *operation,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length)
{
  // Finalize cipher operation. This will only output data for algorithms which include padding.
  // This is currently only AES-CBC with PKCS#7.
  psa_status_t psa_status = PSA_ERROR_BAD_STATE;

  // Argument check
  if (operation == NULL || output == NULL || output_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Key desc has been properly set by wrapper function
  const sl_se_key_descriptor_t *key_desc = &operation->key_desc;
  psa_status = validate_key_type(key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  switch (operation->alg) {
    case PSA_ALG_ECB_NO_PADDING:
    case PSA_ALG_CBC_NO_PADDING:
      // No-padding operations can't finish if they haven't processed block-size input
      *output_length = 0;
      if (operation->processed_length % 16 != 0) {
        psa_status = PSA_ERROR_INVALID_ARGUMENT;
      } else {
        psa_status = PSA_SUCCESS;
      }
      break;
    case PSA_ALG_CBC_PKCS7:
    {
      if (output == NULL
          || output_size < 16
          || output_length == NULL) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // Ephemeral contexts
      sl_se_command_context_t cmd_ctx = { 0 };

      sl_status_t status = sl_se_init_command_context(&cmd_ctx);
      if (status != SL_STATUS_OK) {
        psa_status = PSA_ERROR_HARDWARE_FAILURE;
        break;
      }

      // Calculate padding, update, output final block
      if (operation->direction == SL_SE_ENCRYPT) {
        size_t padding_bytes = 16 - (operation->processed_length % 16);
        memset(&operation->streaming_block[16 - padding_bytes], padding_bytes, padding_bytes);

        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     key_desc,
                                     SL_SE_ENCRYPT,
                                     16,
                                     operation->iv,
                                     operation->streaming_block,
                                     output);
        if (status != SL_STATUS_OK) {
          *output_length = 0;
          psa_status = PSA_ERROR_HARDWARE_FAILURE;
        } else {
          *output_length = 16;
          psa_status = PSA_SUCCESS;
        }
      } else {
        // Expect full-block input
        if (operation->processed_length % 16 != 0 || operation->processed_length < 16) {
          psa_status = PSA_ERROR_INVALID_ARGUMENT;
          break;
        }

        uint8_t out_buf[16];

        // Decrypt the last block
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     key_desc,
                                     SL_SE_DECRYPT,
                                     16,
                                     operation->iv,
                                     operation->streaming_block,
                                     out_buf);

        if (status != SL_STATUS_OK) {
          *output_length = 0;
          psa_status = PSA_ERROR_HARDWARE_FAILURE;
          break;
        } else {
          psa_status = PSA_SUCCESS;
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
        } else {
          psa_status = PSA_ERROR_INVALID_PADDING;
        }
      }
    }
    break;
    case PSA_ALG_CTR:
    case PSA_ALG_CFB:
    case PSA_ALG_OFB:
      // Actual stream ciphers: nothing to do here.
      *output_length = 0;
      psa_status = PSA_SUCCESS;
      break;
    default:
      psa_status = PSA_ERROR_BAD_STATE;
  }
  if (psa_status != PSA_SUCCESS) {
    *output_length = 0;
  }
  return psa_status;
}

#endif // defined(SEMAILBOX_PRESENT)
