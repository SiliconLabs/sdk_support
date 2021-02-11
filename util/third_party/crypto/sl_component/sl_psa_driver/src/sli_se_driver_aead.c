#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "psa/crypto.h"
#include "sli_se_driver_key_management.h"
#include "sli_se_driver_aead.h"

#include "sl_se_manager.h"
#include "sl_se_manager_cipher.h"
#include "sl_se_manager_entropy.h"
#include "sli_se_manager_internal.h"

#include <string.h>

#ifndef PSA_AEAD_TAG_MAX_SIZE
// TODO: Remove when macro has been added to the core
#define PSA_AEAD_TAG_MAX_SIZE 16
#endif

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
      if (nonce_length != 12 || (tag_length < 4) || (tag_length > 16)) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CHACHA20_POLY1305, 0):
      if (nonce_length != 12 || tag_length != 16) {
        return PSA_ERROR_NOT_SUPPORTED;
      }
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_aead_encrypt(const psa_key_attributes_t *attributes,
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

  sl_status_t status;
  psa_status_t psa_status;

  // Verify that the driver supports the given parameters
  psa_status = check_aead_parameters(alg, nonce_length);
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

  size_t tag_length = PSA_AEAD_TAG_LENGTH(alg);

  psa_status = PSA_ERROR_BAD_STATE;
  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (ciphertext_size < plaintext_length + tag_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = sl_se_ccm_encrypt_and_tag(&cmd_ctx,
                                         &key_desc,
                                         plaintext_length,
                                         nonce, nonce_length,
                                         additional_data, additional_data_length,
                                         plaintext,
                                         ciphertext,
                                         &ciphertext[plaintext_length], tag_length);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_OK) {
        *ciphertext_length = plaintext_length + tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (ciphertext_size < plaintext_length + tag_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = sl_se_gcm_crypt_and_tag(&cmd_ctx,
                                       &key_desc,
                                       SL_SE_ENCRYPT,
                                       plaintext_length,
                                       nonce, nonce_length,
                                       additional_data, additional_data_length,
                                       plaintext,
                                       ciphertext,
                                       tag_length, &ciphertext[plaintext_length]);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_OK) {
        *ciphertext_length = plaintext_length + tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CHACHA20_POLY1305, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_CHACHA20) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (ciphertext_size < plaintext_length + 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      if (nonce_length < 12) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // We currently don't support the special case where both the message
      // and additional data length are zero, because of a bug in the
      // accelerator firmware.
      if (plaintext_length == 0 && additional_data_length == 0) {
        return PSA_ERROR_NOT_SUPPORTED;
      }

      status = sl_se_chacha20_poly1305_encrypt_and_tag(&cmd_ctx,
                                                       &key_desc,
                                                       plaintext_length,
                                                       nonce,
                                                       additional_data, additional_data_length,
                                                       plaintext,
                                                       ciphertext,
                                                       &ciphertext[plaintext_length]);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_OK) {
        *ciphertext_length = plaintext_length + 16;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return psa_status;
}

psa_status_t sli_se_driver_aead_decrypt(const psa_key_attributes_t *attributes,
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
      || ciphertext_length < tag_length) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sl_status_t status;
  psa_status_t psa_status;

  // Verify that the driver supports the given parameters
  psa_status = check_aead_parameters(alg, nonce_length);
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

  psa_status = PSA_ERROR_BAD_STATE;
  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CCM, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (plaintext_size < ciphertext_length - tag_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = sl_se_ccm_auth_decrypt(&cmd_ctx,
                                      &key_desc,
                                      ciphertext_length - tag_length,
                                      nonce, nonce_length,
                                      additional_data, additional_data_length,
                                      ciphertext,
                                      plaintext,
                                      check_tag, tag_length);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_INVALID_SIGNATURE) {
        return PSA_ERROR_INVALID_SIGNATURE;
      } else if (status == SL_STATUS_OK) {
        *plaintext_length = ciphertext_length - tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (plaintext_size < ciphertext_length - tag_length) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      status = sl_se_gcm_auth_decrypt(&cmd_ctx,
                                      &key_desc,
                                      ciphertext_length - tag_length,
                                      nonce, nonce_length,
                                      additional_data, additional_data_length,
                                      ciphertext,
                                      plaintext,
                                      tag_length, check_tag);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_INVALID_SIGNATURE) {
        return PSA_ERROR_INVALID_SIGNATURE;
      } else if (status == SL_STATUS_OK) {
        *plaintext_length = ciphertext_length - tag_length;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_CHACHA20_POLY1305, 0):
      // verify key type
      if (psa_get_key_type(attributes) != PSA_KEY_TYPE_CHACHA20) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      if (plaintext_size < ciphertext_length - 16) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      if (nonce_length < 12) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      // We currently don't support the special case where both the message
      // and additional data length are zero, because of a bug in the
      // accelerator firmware.
      if (ciphertext_length == tag_length && additional_data_length == 0) {
        return PSA_ERROR_NOT_SUPPORTED;
      }

      status = sl_se_chacha20_poly1305_auth_decrypt(&cmd_ctx,
                                                    &key_desc,
                                                    ciphertext_length - 16,
                                                    nonce,
                                                    additional_data, additional_data_length,
                                                    ciphertext,
                                                    plaintext,
                                                    check_tag);

      if (status == SL_STATUS_INVALID_PARAMETER) {
        return PSA_ERROR_INVALID_ARGUMENT;
      } else if (status == SL_STATUS_INVALID_SIGNATURE) {
        return PSA_ERROR_INVALID_SIGNATURE;
      } else if (status == SL_STATUS_OK) {
        *plaintext_length = ciphertext_length - 16;
        psa_status = PSA_SUCCESS;
      } else {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
      break;
#endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return psa_status;
}

psa_status_t sli_se_driver_aead_encrypt_decrypt_setup(sli_se_driver_aead_operation_t *operation,
                                                      const psa_key_attributes_t *attributes,
                                                      const uint8_t *key_buffer,
                                                      size_t key_buffer_size,
                                                      psa_algorithm_t alg,
                                                      sl_se_cipher_operation_t operation_direction,
                                                      uint8_t *key_storage_buffer,
                                                      size_t key_storage_buffer_size,
                                                      size_t key_storage_overhead)
{
  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Validate key type
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context
  memset(operation, 0, sizeof(*operation));

  // Validate operation
  switch (PSA_ALG_AEAD_WITH_TAG_LENGTH(alg, 0)) {
    case PSA_ALG_AEAD_WITH_TAG_LENGTH(PSA_ALG_GCM, 0):
      operation->alg = alg;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Prepare key descriptor
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &(operation->key_desc));
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Verify length and copy key material to context
  uint32_t key_len;
  sl_status_t status = sli_key_get_size(&(operation->key_desc), &key_len);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  switch (key_len) {
    case 16: // Fallthrough
    case 24: // Fallthrough
    case 32:
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (key_storage_buffer_size < key_storage_overhead + key_len) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  memcpy(key_storage_buffer, operation->key_desc.storage.location.buffer.pointer, key_storage_overhead + key_len);

  // Point key_descriptor at internal copy of key
  operation->key_desc.storage.location.buffer.pointer = key_storage_buffer;

  // Set direction of operation
  operation->ctx.preinit.direction = operation_direction;
  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_aead_generate_nonce(sli_se_driver_aead_operation_t *operation,
                                               uint8_t *nonce,
                                               size_t nonce_size,
                                               size_t *nonce_length)
{
  if (operation == NULL
      || nonce == NULL
      || nonce_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Setting nonce twice isn't supported
  if (operation->ctx.preinit.nonce_length != 0) {
    return PSA_ERROR_BAD_STATE;
  }

  if (nonce_size <= sizeof(operation->ctx.preinit.nonce)) {
    sl_se_command_context_t cmd_ctx = { 0 };

    sl_status_t status = sl_se_init_command_context(&cmd_ctx);
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    // generate IV and write to output
    status = sl_se_get_random(&cmd_ctx, operation->ctx.preinit.nonce, sizeof(operation->ctx.preinit.nonce));
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    status = sl_se_deinit_command_context(&cmd_ctx);
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    // Todo: generate the right nonce length for each specific operation

    memcpy(nonce, operation->ctx.preinit.nonce, nonce_size);
    operation->ctx.preinit.nonce_length = nonce_size;
    *nonce_length = nonce_size;
    return PSA_SUCCESS;
  } else {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
}

psa_status_t sli_se_driver_aead_set_nonce(sli_se_driver_aead_operation_t *operation,
                                          const uint8_t *nonce,
                                          size_t nonce_size)
{
  if (operation == NULL
      || nonce == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Setting nonce twice isn't supported
  if (operation->ctx.preinit.nonce_length != 0) {
    return PSA_ERROR_BAD_STATE;
  }

  if (nonce_size <= sizeof(operation->ctx.preinit.nonce)) {
    memcpy(operation->ctx.preinit.nonce, nonce, nonce_size);
    operation->ctx.preinit.nonce_length = nonce_size;
    return PSA_SUCCESS;
  } else {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
}

psa_status_t sli_se_driver_aead_set_lengths(sli_se_driver_aead_operation_t *operation,
                                            size_t ad_length,
                                            size_t plaintext_length)
{
  // TODO: when implementing AES-CCM, this will need to be fleshed out
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Context is not active
  if (operation->alg == 0) {
    return PSA_ERROR_BAD_STATE;
  }

  if (operation->ad_len != 0 || operation->pt_len != 0) {
    return PSA_ERROR_BAD_STATE;
  }

  // TODO: when full suite is implemented, add checks for already-begun operation

  operation->ctx.preinit.ad_length = ad_length;
  operation->ctx.preinit.pt_length = plaintext_length;
  return PSA_SUCCESS;
}

static void update_context_pointers(sli_se_driver_aead_operation_t *operation,
                                    uint8_t *key_buffer)
{
  if (operation == NULL) {
    return;
  }

  // Update key buffer pointer in stored key_desc
  if (key_buffer != NULL) {
    operation->key_desc.storage.location.buffer.pointer = key_buffer;
  }

  // If we have started an operation, we need to update the GCM context pointers
  if (operation->ad_len != 0 || operation->pt_len != 0) {
    operation->ctx.gcm.cmd_ctx = &(operation->cmd_ctx);
    operation->ctx.gcm.key = &(operation->key_desc);
  }
}

static psa_status_t aead_start(sli_se_driver_aead_operation_t *operation,
                               const uint8_t *input,
                               size_t input_length)
{
  // Ephemeral contexts
  sli_se_driver_aead_preinit_t preinit = operation->ctx.preinit;

  sl_status_t status = sl_se_init_command_context(&operation->cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  switch (operation->alg) {
    case PSA_ALG_GCM:
      status = sl_se_gcm_starts(&operation->ctx.gcm,
                                &operation->cmd_ctx,
                                &operation->key_desc,
                                preinit.direction,
                                preinit.nonce,
                                preinit.nonce_length,
                                input,
                                input_length);
      if (status != SL_STATUS_OK) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      operation->ad_len += input_length;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_aead_update_ad(sli_se_driver_aead_operation_t *operation,
                                          uint8_t *key_buffer,
                                          const uint8_t *input,
                                          size_t input_length)
{
  if (operation == NULL
      || key_buffer == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->alg == 0) {
    return PSA_ERROR_BAD_STATE;
  }

  if (operation->ad_len > 0 || operation->pt_len > 0) {
    return PSA_ERROR_BAD_STATE;
  }

  // Start operation
  if (input_length == 0) {
    return PSA_SUCCESS;
  }

  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  return aead_start(operation, input, input_length);
}

psa_status_t sli_se_driver_aead_update(sli_se_driver_aead_operation_t *operation,
                                       uint8_t *key_buffer,
                                       const uint8_t *input,
                                       size_t input_length,
                                       uint8_t *output,
                                       size_t output_size,
                                       size_t *output_length)
{
  if (operation == NULL
      || ((input == NULL || output == NULL) && input_length > 0)
      || (output_size < input_length)
      || output_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->alg == 0) {
    return PSA_ERROR_BAD_STATE;
  }

  // Start operation
  if (input_length == 0) {
    return PSA_SUCCESS;
  }

  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  sl_status_t status;
  psa_status_t psa_status;

  // Operation isn't initialised unless we have either AD or PT, so if we are
  // still at 0, we need to run the start step.
  if (operation->ad_len == 0 && operation->pt_len == 0) {
    psa_status = aead_start(operation, NULL, 0);
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
  }

  switch (operation->alg) {
    case PSA_ALG_GCM:
      status = sl_se_gcm_update(&operation->ctx.gcm,
                                input_length,
                                input,
                                output);
      if (status != SL_STATUS_OK) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      operation->pt_len += input_length;
      *output_length = input_length;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_driver_aead_finish(sli_se_driver_aead_operation_t *operation,
                                       uint8_t *key_buffer,
                                       uint8_t *ciphertext,
                                       size_t ciphertext_size,
                                       size_t *ciphertext_length,
                                       uint8_t *tag,
                                       size_t tag_size,
                                       size_t *tag_length)
{
  (void)ciphertext;
  (void)ciphertext_size;

  sl_status_t status;
  psa_status_t psa_status;

  if (operation == NULL
      || ciphertext_length == NULL
      || tag == NULL
      || tag_length == NULL) {
    psa_status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (operation->alg == 0) {
    psa_status = PSA_ERROR_BAD_STATE;
    goto exit;
  }

  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  // Operation isn't initialised unless we have either AD or PT, so  if we are
  // still at 0, we need to run the start step.
  if (operation->ad_len == 0 && operation->pt_len == 0) {
    psa_status = aead_start(operation, NULL, 0);
    if (psa_status != PSA_SUCCESS) {
      goto exit;
    }
  }

  switch (operation->alg) {
    case PSA_ALG_GCM:
      status = sl_se_gcm_finish(&operation->ctx.gcm,
                                tag,
                                (tag_size > 16 ? 16 : tag_size));
      if (status != SL_STATUS_OK) {
        psa_status = PSA_ERROR_HARDWARE_FAILURE;
        goto exit;
      }

      *tag_length = (tag_size > 16 ? 16 : tag_size);
      break;
    default:
      psa_status = PSA_ERROR_NOT_SUPPORTED;
      goto exit;
  }

  psa_status = PSA_SUCCESS;

  exit:
  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  status = sl_se_deinit_command_context(&operation->cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return psa_status;
}

psa_status_t sli_se_driver_aead_verify(sli_se_driver_aead_operation_t *operation,
                                       uint8_t *key_buffer,
                                       uint8_t *plaintext,
                                       size_t plaintext_size,
                                       size_t *plaintext_length,
                                       const uint8_t *tag,
                                       size_t tag_length)
{
  (void)plaintext;
  (void)plaintext_size;

  sl_status_t status;
  psa_status_t psa_status;

  if (operation == NULL
      || plaintext_length == NULL
      || tag == NULL
      || tag_length == 0) {
    psa_status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (operation->alg == 0) {
    psa_status = PSA_ERROR_BAD_STATE;
    goto exit;
  }

  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  // Operation isn't initialised unless we have either AD or PT, so  if we are
  // still at 0, we need to run the start step.
  if (operation->ad_len == 0 && operation->pt_len == 0) {
    psa_status = aead_start(operation, NULL, 0);
    if (psa_status != PSA_SUCCESS) {
      goto exit;
    }
  }

  switch (operation->alg) {
    case PSA_ALG_GCM:
      status = sl_se_gcm_finish(&operation->ctx.gcm,
                                (uint8_t *)tag,
                                (tag_length > 16 ? 16 : tag_length));
      if (status == SL_STATUS_INVALID_SIGNATURE) {
        psa_status = PSA_ERROR_INVALID_SIGNATURE;
        goto exit;
      } else if (status != SL_STATUS_OK) {
        psa_status = PSA_ERROR_HARDWARE_FAILURE;
        goto exit;
      }
      break;
    default:
      psa_status = PSA_ERROR_NOT_SUPPORTED;
      goto exit;
  }

  psa_status = PSA_SUCCESS;

  exit:
  // Refresh internal pointers in operation context before use
  update_context_pointers(operation, key_buffer);

  status = sl_se_deinit_command_context(&operation->cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return psa_status;
}

#endif // defined(SEMAILBOX_PRESENT)
