#include "em_device.h"

#if defined(CRYPTOACC_PRESENT)

#include "sli_cryptoacc_transparent_functions.h"
#include "cryptoacc_management.h"
// Replace inclusion of psa/crypto_xxx.h with the new psa driver commong
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"
#include "sx_aes.h"
#include "sx_errors.h"
#include <string.h>

psa_status_t sli_cryptoacc_transparent_mac_compute(const psa_key_attributes_t *attributes,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   psa_algorithm_t alg,
                                                   const uint8_t *input,
                                                   size_t input_length,
                                                   uint8_t *mac,
                                                   size_t mac_size,
                                                   size_t *mac_length)
{
  if (key_buffer == NULL
      || attributes == NULL
      || mac == NULL
      || mac_length == NULL ) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  int status;
  uint32_t sx_ret;
  block_t key_sxblk;
  block_t input_sxblk;
  block_t mac_sxblk;
  uint8_t sx_mac_buf[BLK_CIPHER_MAC_SIZE];
  size_t key_size;

  // Check key info and store if supported
  key_size = psa_get_key_bits(attributes) / 8;
  switch (key_size) {
    case 16:
    case 24:
    case 32:
      if (key_buffer_size != key_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  switch (alg) {
    case PSA_ALG_CMAC:

      // Setup DMA descriptors
      key_sxblk = block_t_convert(key_buffer, key_size);
      input_sxblk = block_t_convert(input, input_length);
      mac_sxblk = block_t_convert(sx_mac_buf, BLK_CIPHER_MAC_SIZE);

      // Acquire exclusive access to the CRYPTOACC hardware
      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }

      // Execute the CMAC operation
      sx_ret = sx_aes_cmac_generate((const block_t *)&key_sxblk, (const block_t *)&input_sxblk, &mac_sxblk);

      status = cryptoacc_management_release();

      if (sx_ret != CRYPTOLIB_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      if (status != PSA_SUCCESS) {
        return status;
      }

      // Copy the requested number of bytes (max 16 for CMAC) to the user buffer.
      if (mac_size > BLK_CIPHER_MAC_SIZE) {
        mac_size = BLK_CIPHER_MAC_SIZE;
      }
      memcpy(mac, sx_mac_buf, mac_size);
      *mac_length = mac_size;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_mac_sign_setup(sli_cryptoacc_transparent_mac_operation_t *operation,
                                                      const psa_key_attributes_t *attributes,
                                                      const uint8_t *key_buffer,
                                                      size_t key_buffer_size,
                                                      psa_algorithm_t alg)
{
  size_t key_size;

  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check key type
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // start by resetting context
  memset(operation, 0, sizeof(*operation));

  // Check algorithm and store if supported
  switch (alg) {
    case PSA_ALG_CMAC:
      operation->alg = alg;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Check key info and store if supported
  key_size = psa_get_key_bits(attributes) / 8;
  switch (key_size) {
    case 16:
    case 24:
    case 32:
      if (key_buffer_size != key_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, key_size);
      operation->key_len = key_size;
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Set DMA descriptors for CMAC state context
  operation->key_sxblk = block_t_convert(operation->key, key_size);
  operation->cmac_ctx_sxblk = block_t_convert(operation->cmac_ctx, sizeof(operation->cmac_ctx));

  return PSA_SUCCESS;
}

static psa_status_t cryptoacc_cmac_update_blk(sli_cryptoacc_transparent_mac_operation_t *operation,
                                              block_t *input_sxblk)
{
  psa_status_t status;
  uint32_t sx_ret;

  // Acquire exclusive access to the CRYPTOACC hardware
  status = cryptoacc_management_acquire();
  if (status != PSA_SUCCESS) {
    return status;
  }

  // CMAC state context is already initialized, do update.
  sx_ret = sx_aes_cmac_generate_update((const block_t *)&operation->key_sxblk,
                                       (const block_t *)input_sxblk,
                                       (const block_t *)&operation->cmac_ctx_sxblk,
                                       &operation->cmac_ctx_sxblk);

  status = cryptoacc_management_release();

  if (sx_ret != CRYPTOLIB_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  if (status != PSA_SUCCESS) {
    return status;
  }
  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_mac_update(sli_cryptoacc_transparent_mac_operation_t *operation,
                                                  const uint8_t *input,
                                                  size_t input_length)
{
  if (operation == NULL
      || input == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  psa_status_t status;
  block_t input_sxblk;
  size_t current_block_len;

  if (input_length == 0 ) {
    return PSA_SUCCESS;
  }

  // Check algorithm and store if supported
  switch (operation->alg) {
    case PSA_ALG_CMAC:

      // if the potential last block include data
      // we need to process them first
      current_block_len = operation->current_block_len;
      if (current_block_len) {
        size_t bytes_to_boundary = 16 - current_block_len;
        // if the total of bytes is smaller than a block, just copy and return
        // else fill up the potential last block
        if (input_length < bytes_to_boundary) {
          memcpy(&operation->current_block[current_block_len], input, input_length);
          operation->current_block_len = current_block_len + input_length;
          return PSA_SUCCESS;
        } else {
          // fill up the potential last block
          memcpy(&operation->current_block[current_block_len], input, bytes_to_boundary);
          operation->current_block_len = 16;
          input_length -= bytes_to_boundary;
          input += bytes_to_boundary;
        }

        // if there are more input data, the potential last block is not
        // the last block, which means we can process it now,
        if (input_length) {
          // Setup DMA descriptor
          input_sxblk = block_t_convert(operation->current_block, 16);

          // Execute CMAC operation on the single context block
          status = cryptoacc_cmac_update_blk(operation, &input_sxblk);
          if (status != PSA_SUCCESS) {
            return status;
          }
          operation->current_block_len = 0;
        }
      }

      // Process complete input blocks
      if (input_length > 16) {
        // Calculate the number of bytes in complete blocks to process.
        // If the last block is complete we need to postpone processing it
        // since it may be the last block which should go to sx_aes_cmac_generate_final.
        size_t bytes_to_copy = (input_length - 1) & ~0xFUL;

        // Setup DMA descriptor
        input_sxblk = block_t_convert(input, bytes_to_copy);

        // Execute CMAC operation on the single context block
        status = cryptoacc_cmac_update_blk(operation, &input_sxblk);
        if (status != PSA_SUCCESS) {
          return status;
        }

        input_length -= bytes_to_copy;
        input += bytes_to_copy;
      }

      // Store remaining input bytes
      if (input_length) {
        memcpy(operation->current_block, input, input_length);
        operation->current_block_len = input_length;
      }

      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_mac_sign_finish(sli_cryptoacc_transparent_mac_operation_t *operation,
                                                       uint8_t *mac,
                                                       size_t mac_size,
                                                       size_t *mac_length)
{
  if (operation == NULL
      || mac == NULL
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  int status;
  uint32_t sx_ret;
  block_t input_sxblk;

  // Check algorithm and store if supported
  switch (operation->alg) {
    case PSA_ALG_CMAC:

      // Setup DMA descriptors
      input_sxblk = block_t_convert(operation->current_block,
                                    operation->current_block_len);

      // Acquire exclusive access to the CRYPTOACC hardware
      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }

      // Execute the first CMAC operation.
      // Receive the final mac in the cmac_ctx buffer and copy the requested
      // number of bytes to the user buffer after.
      sx_ret = sx_aes_cmac_generate_final((const block_t *)&operation->key_sxblk,
                                          (const block_t *)&input_sxblk,
                                          (const block_t *)&operation->cmac_ctx_sxblk,
                                          &operation->cmac_ctx_sxblk);

      status = cryptoacc_management_release();

      if (sx_ret != CRYPTOLIB_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      if (status != PSA_SUCCESS) {
        return status;
      }

      // Copy the requested number of bytes (max 16 for CMAC) to the user buffer.
      if (mac_size > BLK_CIPHER_MAC_SIZE) {
        mac_size = BLK_CIPHER_MAC_SIZE;
      }
      memcpy(mac, operation->cmac_ctx, mac_size);
      *mac_length = mac_size;
      break;

    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_mac_abort(sli_cryptoacc_transparent_mac_operation_t *operation)
{
  // There's no state in hardware that we need to preserve, so zeroing out the context suffices.
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memset(operation, 0, sizeof(*operation));
  return PSA_SUCCESS;
}

#endif // defined(CRYPTOACC_PRESENT)
