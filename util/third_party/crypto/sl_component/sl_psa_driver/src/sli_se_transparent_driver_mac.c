/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Mac functions.
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

#include "psa/crypto.h"
#include "sli_se_transparent_types.h"
#include "sli_se_transparent_functions.h"

#include <string.h>

static psa_status_t sli_se_transparent_driver_symmetric_key_from_context(
  sl_se_key_descriptor_t* key_desc,
  sli_se_transparent_mac_operation_t* transparent_operation)
{
  // Point to transparent key buffer as storage location
  key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT;
  key_desc->storage.location.buffer.pointer = transparent_operation->key;
  key_desc->storage.location.buffer.size = sizeof(transparent_operation->key);
  key_desc->size = transparent_operation->key_len;

  switch (PSA_ALG_FULL_LENGTH_MAC(transparent_operation->operation.alg)) {
    case PSA_ALG_CBC_MAC:
    case PSA_ALG_CMAC:
      if (key_desc->size == 16) {
        key_desc->type = SL_SE_KEY_TYPE_AES_128;
      } else if (key_desc->size == 24) {
        key_desc->type = SL_SE_KEY_TYPE_AES_192;
      } else if (key_desc->size == 32) {
        key_desc->type = SL_SE_KEY_TYPE_AES_256;
      } else {
        return PSA_ERROR_BAD_STATE;
      }
      break;
    default:
      return PSA_ERROR_BAD_STATE;
  }

  return PSA_SUCCESS;
}

static psa_status_t sli_se_transparent_driver_symmetric_key_from_psa(sl_se_key_descriptor_t* key_desc,
                                                                     const psa_key_attributes_t *attributes,
                                                                     const uint8_t *key_buffer,
                                                                     size_t key_buffer_size)
{
  // Point to transparent key buffer as storage location
  key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT;
  key_desc->storage.location.buffer.pointer = (uint8_t *)key_buffer;
  key_desc->storage.location.buffer.size = key_buffer_size;

  // Verify and set key attributes
  psa_key_type_t keytype = psa_get_key_type(attributes);

  if (keytype == PSA_KEY_TYPE_AES) {
    switch (psa_get_key_bits(attributes)) {
      case 128:
        key_desc->size = 16;
        key_desc->type = SL_SE_KEY_TYPE_AES_128;
        break;
      case 192:
        key_desc->size = 24;
        key_desc->type = SL_SE_KEY_TYPE_AES_192;
        break;
      case 256:
        key_desc->size = 32;
        key_desc->type = SL_SE_KEY_TYPE_AES_256;
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }
  } else if (keytype == PSA_KEY_TYPE_HMAC) {
    key_desc->size = psa_get_key_bits(attributes) / 8;
    key_desc->type = SL_SE_KEY_TYPE_SYMMETRIC;
  } else {
    // Unknown key type to us
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (key_buffer_size < key_desc->size) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_transparent_mac_compute(const psa_key_attributes_t *attributes,
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
  psa_status_t psa_status = sli_se_transparent_driver_symmetric_key_from_psa(&key_desc,
                                                                             attributes,
                                                                             key_buffer,
                                                                             key_buffer_size);
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

psa_status_t sli_se_transparent_mac_verify(const psa_key_attributes_t *attributes,
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

psa_status_t sli_se_transparent_mac_sign_setup(sli_se_transparent_mac_operation_t *operation,
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

  // start by resetting context
  memset(operation, 0, sizeof(*operation));

  psa_status_t psa_status = sli_se_driver_mac_sign_setup(&(operation->operation),
                                                         attributes,
                                                         alg);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  operation->key_len = psa_get_key_bits(attributes) / 8;
  switch (operation->key_len) {
    case 16:
      if (key_buffer_size < 16) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 16);
      break;
    case 24:
      if (key_buffer_size < 24) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 24);
      break;
    case 32:
      if (key_buffer_size < 32) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, 32);
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_se_transparent_mac_verify_setup(sli_se_transparent_mac_operation_t *operation,
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

psa_status_t sli_se_transparent_mac_update(sli_se_transparent_mac_operation_t *operation,
                                           const uint8_t *input,
                                           size_t input_length)
{
  if (operation == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Ephemeral contexts
  sl_se_key_descriptor_t key_desc = { 0 };

  psa_status_t psa_status = sli_se_transparent_driver_symmetric_key_from_context(&key_desc,
                                                                                 operation);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  return sli_se_driver_mac_update(&(operation->operation),
                                  &key_desc,
                                  input,
                                  input_length);
}

psa_status_t sli_se_transparent_mac_sign_finish(sli_se_transparent_mac_operation_t *operation,
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

  // Ephemeral contexts
  sl_se_key_descriptor_t key_desc = { 0 };

  psa_status_t psa_status = sli_se_transparent_driver_symmetric_key_from_context(&key_desc,
                                                                                 operation);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  return sli_se_driver_mac_sign_finish(&(operation->operation),
                                       &key_desc,
                                       mac,
                                       mac_size,
                                       mac_length);
}

psa_status_t sli_se_transparent_mac_verify_finish(sli_se_transparent_mac_operation_t *operation,
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

psa_status_t sli_se_transparent_mac_abort(sli_se_transparent_mac_operation_t *operation)
{
  // There's no state in hardware that we need to preserve, so zeroing out the context suffices.
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  memset(operation, 0, sizeof(*operation));
  return PSA_SUCCESS;
}

#endif // defined(SEMAILBOX_PRESENT)
