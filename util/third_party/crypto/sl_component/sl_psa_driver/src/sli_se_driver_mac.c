#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "psa/crypto.h"
#include "sli_se_transparent_types.h"
#include "sli_se_transparent_functions.h"

#include "sl_se_manager.h"
#include "sl_se_manager_cipher.h"
#include "sl_se_manager_entropy.h"

#include <string.h>

sl_se_hash_type_t sli_se_hash_type_from_psa_hmac_alg(psa_algorithm_t alg, size_t *length)
{
  if (PSA_ALG_IS_HMAC(alg)) {
    psa_algorithm_t hash_alg = PSA_ALG_HMAC_GET_HASH(alg);
    switch (hash_alg) {
      case PSA_ALG_SHA_1:
        *length = 20;
        return SL_SE_HASH_SHA1;
      case PSA_ALG_SHA_224:
        *length = 28;
        return SL_SE_HASH_SHA224;
      case PSA_ALG_SHA_256:
        *length = 32;
        return SL_SE_HASH_SHA256;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || defined(DOXYGEN)
      case PSA_ALG_SHA_384:
        *length = 48;
        return SL_SE_HASH_SHA384;
      case PSA_ALG_SHA_512:
        *length = 64;
        return SL_SE_HASH_SHA512;
#endif
      default:
        return SL_SE_HASH_NONE;
    }
  }
  return SL_SE_HASH_NONE;
}

psa_status_t sli_se_driver_mac_compute(sl_se_key_descriptor_t *key_desc,
                                       psa_algorithm_t alg,
                                       const uint8_t *input,
                                       size_t input_length,
                                       uint8_t *mac,
                                       size_t mac_size,
                                       size_t *mac_length)
{
  if (mac == NULL
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sl_status_t status; // Used for SE manager returns
  psa_status_t psa_status = PSA_ERROR_INVALID_ARGUMENT; // Used to track return value
  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };
  uint8_t tmp_mac[16] = { 0 };

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  if (PSA_ALG_IS_HMAC(alg)) {
    status = sl_se_hmac(&cmd_ctx,
                        key_desc,
                        sli_se_hash_type_from_psa_hmac_alg(alg, mac_length),
                        input,
                        input_length,
                        mac,
                        mac_size);
  } else {
    switch (alg) {
      case PSA_ALG_CBC_MAC:
        // CBC-MAC: Do an AES-CBC encrypt with zero IV, keeping only the last block
        if (input_length % 16 != 0 || input_length < 16) {
          psa_status = PSA_ERROR_INVALID_ARGUMENT;
          goto exit;
        }
        uint8_t tmp_buf[16];

        while (input_length > 0) {
          status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                       key_desc,
                                       SL_SE_ENCRYPT,
                                       16,
                                       tmp_mac,
                                       input,
                                       tmp_buf);

          input_length -= 16;
          input += 16;
        }

        // Copy the requested number of bytes (max 16) to the user buffer.
        if (mac_size > 16) {
          mac_size = 16;
        }
        memcpy(mac, tmp_mac, mac_size);
        *mac_length = mac_size;
        break;
      case PSA_ALG_CMAC:
        status = sl_se_cmac(&cmd_ctx,
                            key_desc,
                            input,
                            input_length,
                            tmp_mac);
        // Copy the requested number of bytes (max 16) to the user buffer.
        if (mac_size > 16) {
          mac_size = 16;
        }
        memcpy(mac, tmp_mac, mac_size);
        *mac_length = mac_size;
        break;
      default:
        psa_status = PSA_ERROR_NOT_SUPPORTED;
        goto exit;
    }
  }

  if (status == SL_STATUS_INVALID_PARAMETER) {
    psa_status = PSA_ERROR_INVALID_ARGUMENT;
  } else if (status == SL_STATUS_FAIL) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
  } else if (status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    psa_status = PSA_SUCCESS;
  }

  exit:
  // Cleanup
  status = sl_se_deinit_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return psa_status;
}

psa_status_t sli_se_driver_mac_sign_setup(sli_se_driver_mac_operation_t *operation,
                                          const psa_key_attributes_t *attributes,
                                          psa_algorithm_t alg)
{
  if (operation == NULL
      || attributes == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Start by resetting context
  memset(operation, 0, sizeof(*operation));

  // Check for supported algorithm
  switch (PSA_ALG_FULL_LENGTH_MAC(alg)) {
    case PSA_ALG_CBC_MAC:
      operation->alg = alg;
      break;
    case PSA_ALG_CMAC:
      operation->alg = alg;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Take in key
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_mac_update(sli_se_driver_mac_operation_t *operation,
                                      sl_se_key_descriptor_t *key_desc,
                                      const uint8_t *input,
                                      size_t input_length)
{
  if (operation == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sl_status_t status; // Used for SE manager returns
  psa_status_t psa_status = PSA_ERROR_INVALID_ARGUMENT; // Used to track return value
  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  psa_status = PSA_ERROR_NOT_SUPPORTED;
  switch (PSA_ALG_FULL_LENGTH_MAC(operation->alg)) {
    case PSA_ALG_CBC_MAC:
      if (input_length == 0) {
        psa_status = PSA_SUCCESS;
        goto exit;
      }
      // Add bytes to the streaming buffer up to the next block boundary
      if (operation->ctx.cbcmac.processed_length % 16 != 0) {
        size_t bytes_to_boundary = 16 - operation->ctx.cbcmac.processed_length % 16;
        if (input_length < bytes_to_boundary) {
          memcpy(&operation->ctx.cbcmac.streaming_block[16 - bytes_to_boundary],
                 input,
                 input_length);
          operation->ctx.cbcmac.processed_length += input_length;
          psa_status = PSA_SUCCESS;
          goto exit;
        }

        memcpy(&operation->ctx.cbcmac.streaming_block[16 - bytes_to_boundary],
               input,
               bytes_to_boundary);
        input_length -= bytes_to_boundary;
        input += bytes_to_boundary;
        operation->ctx.cbcmac.processed_length += bytes_to_boundary;

        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     key_desc,
                                     SL_SE_ENCRYPT,
                                     16,
                                     operation->ctx.cbcmac.iv,
                                     operation->ctx.cbcmac.streaming_block,
                                     operation->ctx.cbcmac.iv);

        if (status == SL_STATUS_FAIL) {
          psa_status = PSA_ERROR_DOES_NOT_EXIST;
          goto exit;
        } else if (status != SL_STATUS_OK) {
          psa_status = PSA_ERROR_HARDWARE_FAILURE;
          goto exit;
        }
      }

      // Draw all full blocks
      while (input_length >= 16) {
        status = sl_se_aes_crypt_cbc(&cmd_ctx,
                                     key_desc,
                                     SL_SE_ENCRYPT,
                                     16,
                                     operation->ctx.cbcmac.iv,
                                     input,
                                     operation->ctx.cbcmac.iv);

        if (status != SL_STATUS_OK) {
          psa_status = PSA_ERROR_HARDWARE_FAILURE;
          goto exit;
        }

        operation->ctx.cbcmac.processed_length += 16;
        input += 16;
        input_length -= 16;
      }

      if (input_length > 0) {
        memcpy(operation->ctx.cbcmac.streaming_block,
               input,
               input_length);
        operation->ctx.cbcmac.processed_length += input_length;
      }
      psa_status = PSA_SUCCESS;
      goto exit;
    case PSA_ALG_CMAC:
      if (input_length == 0) {
        psa_status = PSA_SUCCESS;
        goto exit;
      }

      operation->ctx.cmac.cmd_ctx = &cmd_ctx;
      operation->ctx.cmac.key = key_desc;

      status = sl_se_cmac_update(&operation->ctx.cmac,
                                 input,
                                 input_length);
      if (status == SL_STATUS_FAIL) {
        psa_status = PSA_ERROR_DOES_NOT_EXIST;
        goto exit;
      } else if (status != SL_STATUS_OK) {
        psa_status = PSA_ERROR_HARDWARE_FAILURE;
        goto exit;
      }
      psa_status = PSA_SUCCESS;
      goto exit;
    default:
      psa_status = PSA_ERROR_BAD_STATE;
      goto exit;
  }

  exit:
  // Cleanup
  status = sl_se_deinit_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return psa_status;
}

psa_status_t sli_se_driver_mac_sign_finish(sli_se_driver_mac_operation_t *operation,
                                           sl_se_key_descriptor_t *key_desc,
                                           uint8_t *mac,
                                           size_t mac_size,
                                           size_t *mac_length)
{
  if (operation == NULL
      || mac == NULL
      || mac_size == 0
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Set maximum output size to 16 or truncated length
  if (mac_size > 16) {
    mac_size = 16;
  }

  size_t truncated_length = PSA_MAC_TRUNCATED_LENGTH(operation->alg);
  if (truncated_length != 0
      && mac_size > truncated_length) {
    mac_size = truncated_length;
  }

  if (PSA_ALG_FULL_LENGTH_MAC(operation->alg) == PSA_ALG_CBC_MAC) {
    if (operation->ctx.cbcmac.processed_length % 16 != 0) {
      return PSA_ERROR_BAD_STATE;
    }
    // Copy the requested number of bytes (max 16) to the user buffer.
    memcpy(mac, operation->ctx.cbcmac.iv, mac_size);
    *mac_length = mac_size;
    return PSA_SUCCESS;
  } else if (PSA_ALG_FULL_LENGTH_MAC(operation->alg) == PSA_ALG_CMAC) {
    // Ephemeral contexts
    sl_se_command_context_t cmd_ctx = { 0 };
    uint8_t tmp_mac[16];
    sl_status_t status = sl_se_init_command_context(&cmd_ctx);
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    operation->ctx.cmac.cmd_ctx = &cmd_ctx;
    operation->ctx.cmac.key = key_desc;

    status = sl_se_cmac_finish(&operation->ctx.cmac, tmp_mac);

    // Cleanup
    status = sl_se_deinit_command_context(&cmd_ctx);
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    if (status == SL_STATUS_OK) {
      // Copy the requested number of bytes (max 16) to the user buffer.
      memcpy(mac, tmp_mac, mac_size);
      *mac_length = mac_size;
      return PSA_SUCCESS;
    } else {
      *mac_length = 0;
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  }

  return PSA_ERROR_NOT_SUPPORTED;
}

#endif // defined(SEMAILBOX_PRESENT)
