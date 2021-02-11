#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#include "psa/crypto_platform.h"

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)

#include "psa/crypto.h"
#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"

#include "mbedtls/entropy_poll.h"

#include "sl_se_manager.h"
#include "sl_se_manager_cipher.h"
#include "sl_se_manager_entropy.h"

#include "sli_se_driver_cipher.h"
#include "sli_se_driver_key_management.h"

#include <string.h>

static void update_key_from_context(sli_se_opaque_cipher_operation_t* ctx)
{
  // Point the key to the buffer
  ctx->operation.key_desc.storage.location.buffer.pointer = ctx->key;
}

static psa_status_t initialize_key_in_context(const psa_key_attributes_t *attributes,
                                              sli_se_opaque_cipher_operation_t *operation,
                                              const uint8_t *key_buffer,
                                              size_t key_buffer_size)
{
  // Initialize the key descriptor
  const size_t key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  psa_status_t psa_status = sli_se_key_desc_from_psa_attributes(attributes,
                                                                key_size,
                                                                &operation->operation.key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  if (key_buffer_size < key_size + sizeof(sli_se_opaque_wrapped_key_context_t)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // The key desc will always point to the key buffer in the operation struct
  // so we can set its size value once and forget about it.
  operation->operation.key_desc.storage.location.buffer.size
    = sizeof(operation->key);

  // Copy the key material
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  size_t offset = 0;
  switch (location) {
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      offset = offsetof(sli_se_opaque_wrapped_key_context_t, wrapped_buffer);
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  if (key_buffer_size < offset) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (key_size + SLI_SE_WRAPPED_KEY_OVERHEAD > sizeof(operation->key)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (key_size + SLI_SE_WRAPPED_KEY_OVERHEAD + offset > key_buffer_size) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  memcpy(operation->key,
         key_buffer + offset,
         key_size + SLI_SE_WRAPPED_KEY_OVERHEAD);
  operation->key_len = key_size + SLI_SE_WRAPPED_KEY_OVERHEAD;

  return PSA_SUCCESS;
}

psa_status_t sli_se_opaque_cipher_encrypt(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *input,
                                          size_t input_length,
                                          uint8_t *output,
                                          size_t output_size,
                                          size_t *output_length)
{
  return sli_se_driver_cipher_encrypt(attributes,
                                      key_buffer,
                                      key_buffer_size,
                                      alg,
                                      input,
                                      input_length,
                                      output,
                                      output_size,
                                      output_length);
}

psa_status_t sli_se_opaque_cipher_decrypt(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *input,
                                          size_t input_length,
                                          uint8_t *output,
                                          size_t output_size,
                                          size_t *output_length)
{
  return sli_se_driver_cipher_decrypt(attributes,
                                      key_buffer,
                                      key_buffer_size,
                                      alg,
                                      input,
                                      input_length,
                                      output,
                                      output_size,
                                      output_length);
}

psa_status_t sli_se_opaque_cipher_encrypt_setup(sli_se_opaque_cipher_operation_t *operation,
                                                const psa_key_attributes_t *attributes,
                                                const uint8_t *key_buffer,
                                                size_t key_buffer_size,
                                                psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // Reset context
  memset(operation, 0, sizeof(*operation));

  psa_status_t psa_status = sli_se_driver_cipher_encrypt_setup(&operation->operation,
                                                               attributes,
                                                               alg);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Copy key into context
  psa_status = initialize_key_in_context(attributes,
                                         operation,
                                         key_buffer,
                                         key_buffer_size);
  return psa_status;
}

psa_status_t sli_se_opaque_cipher_decrypt_setup(sli_se_opaque_cipher_operation_t *operation,
                                                const psa_key_attributes_t *attributes,
                                                const uint8_t *key_buffer,
                                                size_t key_buffer_size,
                                                psa_algorithm_t alg)
{
  if (operation == NULL || attributes == NULL || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Reset context
  memset(operation, 0, sizeof(*operation));

  psa_status_t psa_status = sli_se_driver_cipher_decrypt_setup(&operation->operation,
                                                               attributes,
                                                               alg);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Copy key into context
  psa_status = initialize_key_in_context(attributes,
                                         operation,
                                         key_buffer,
                                         key_buffer_size);
  return psa_status;
}

psa_status_t sli_se_opaque_cipher_generate_iv(sli_se_opaque_cipher_operation_t *operation,
                                              uint8_t *iv,
                                              size_t iv_size,
                                              size_t *iv_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->key_len == 0) {
    // context hasn't been properly initialised
    return PSA_ERROR_BAD_STATE;
  }

  return sli_se_driver_cipher_generate_iv(&operation->operation, iv, iv_size, iv_length);
}

psa_status_t sli_se_opaque_cipher_set_iv(sli_se_opaque_cipher_operation_t *operation,
                                         const uint8_t *iv,
                                         size_t iv_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->key_len == 0) {
    // context hasn't been properly initialised
    return PSA_ERROR_BAD_STATE;
  }

  return sli_se_driver_cipher_set_iv(&operation->operation, iv, iv_length);
}

psa_status_t sli_se_opaque_cipher_update(sli_se_opaque_cipher_operation_t *operation,
                                         const uint8_t *input,
                                         size_t input_length,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length)
{
  // Argument check
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Set the key correctly
  update_key_from_context(operation);

  // Compute
  return sli_se_driver_cipher_update(&operation->operation,
                                     input,
                                     input_length,
                                     output,
                                     output_size,
                                     output_length);
}

psa_status_t sli_se_opaque_cipher_finish(sli_se_opaque_cipher_operation_t *operation,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Set the key correctly
  update_key_from_context(operation);

  // Compute
  return sli_se_driver_cipher_finish(&operation->operation,
                                     output,
                                     output_size,
                                     output_length);
}

psa_status_t sli_se_opaque_cipher_abort(sli_se_opaque_cipher_operation_t *operation)
{
  if (operation != NULL) {
    // Wipe context
    memset(operation, 0, sizeof(sli_se_opaque_cipher_operation_t));
  }

  return PSA_SUCCESS;
}

#endif // VAULT || MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS
#endif // defined(SEMAILBOX_PRESENT)
