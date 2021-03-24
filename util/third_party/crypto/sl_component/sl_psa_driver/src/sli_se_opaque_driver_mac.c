/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Opaque Driver Mac functions.
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

#if defined(SEMAILBOX_PRESENT)
#include "psa/crypto_platform.h"

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)

#include "psa/crypto.h"
#include "sli_se_driver_key_management.h"
#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"

#include <string.h>

psa_status_t sli_se_opaque_mac_compute(const psa_key_attributes_t *attributes,
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
      || attributes == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Ephemeral contexts
  sl_se_key_descriptor_t key_desc = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  return sli_se_driver_mac_compute(&key_desc,
                                   alg,
                                   input,
                                   input_length,
                                   mac,
                                   mac_size,
                                   mac_length);
}

psa_status_t sli_se_opaque_mac_verify(const psa_key_attributes_t *attributes,
                                      const uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      psa_algorithm_t alg,
                                      const uint8_t *input,
                                      size_t input_length,
                                      const uint8_t *mac,
                                      size_t mac_length)
{
  // There's no point in providing this functionality, since we'd do the same as the PSA core
  // either way: compute through mac_compute, and constant-time compare on the provided vs
  // calculated mac.
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  (void)input;
  (void)input_length;
  (void)mac;
  (void)mac_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_se_opaque_mac_sign_setup(sli_se_opaque_mac_operation_t *operation,
                                          const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg)
{
  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t psa_status;

  // start by resetting context
  memset(operation, 0, sizeof(*operation));

  psa_status = sli_se_driver_mac_sign_setup(&(operation->operation),
                                            attributes,
                                            alg);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  psa_status = sli_se_key_desc_from_input(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          &(operation->key_desc));
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  operation->key_len = psa_get_key_bits(attributes) / 8;
  switch (operation->key_len) {
    case 16: // Fallthrough
    case 24: // Fallthrough
    case 32:
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (operation->key_desc.storage.location.buffer.size < SLI_SE_WRAPPED_KEY_OVERHEAD + operation->key_len) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  memcpy(operation->key, operation->key_desc.storage.location.buffer.pointer, SLI_SE_WRAPPED_KEY_OVERHEAD + operation->key_len);

  // Point key_descriptor at internal copy of key
  operation->key_desc.storage.location.buffer.pointer = operation->key;

  return PSA_SUCCESS;
}

psa_status_t sli_se_opaque_mac_verify_setup(sli_se_opaque_mac_operation_t *operation,
                                            const psa_key_attributes_t *attributes,
                                            const uint8_t *key_buffer,
                                            size_t key_buffer_size,
                                            psa_algorithm_t alg)
{
  // There's no point in providing this functionality, since we'd do the same as the PSA core
  // either way: compute through mac_compute, and constant-time compare on the provided vs
  // calculated mac.
  (void)operation;
  (void)attributes;
  (void)key_buffer;
  (void)key_buffer_size;
  (void)alg;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_se_opaque_mac_update(sli_se_opaque_mac_operation_t *operation,
                                      const uint8_t *input,
                                      size_t input_length)
{
  if (operation == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return sli_se_driver_mac_update(&(operation->operation),
                                  &(operation->key_desc),
                                  input,
                                  input_length);
}

psa_status_t sli_se_opaque_mac_sign_finish(sli_se_opaque_mac_operation_t *operation,
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

  return sli_se_driver_mac_sign_finish(&(operation->operation),
                                       &(operation->key_desc),
                                       mac,
                                       mac_size,
                                       mac_length);
}

psa_status_t sli_se_opaque_mac_verify_finish(sli_se_opaque_mac_operation_t *operation,
                                             const uint8_t *mac,
                                             size_t mac_length)
{
  // There's no point in providing this functionality, since we'd do the same as the PSA core
  // either way: compute through mac_compute, and constant-time compare on the provided vs
  // calculated mac.
  (void)operation;
  (void)mac;
  (void)mac_length;
  return PSA_ERROR_NOT_SUPPORTED;
}

psa_status_t sli_se_opaque_mac_abort(sli_se_opaque_mac_operation_t *operation)
{
  // There's no state in hardware that we need to preserve, so zeroing out the context suffices.
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memset(operation, 0, sizeof(*operation));
  return PSA_SUCCESS;
}

#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT || MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS
#endif // defined(SEMAILBOX_PRESENT)
