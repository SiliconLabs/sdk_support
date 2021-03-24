/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Driver Key Management functions.
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

#ifdef __cplusplus
extern "C" {
#endif

#if defined(SEMAILBOX_PRESENT)
#include <string.h>

#include "psa/crypto.h"

#include "sli_se_opaque_types.h"
#include "sli_se_driver_key_management.h"
#include "sli_psa_driver_common.h"

#include "sli_se_manager_internal.h"
#include "sl_se_manager_key_derivation.h"

// -----------------------------------------------------------------------------
// Static consts

// Define group orders (n) for secp_r1 curves.
static const uint8_t ecc_p192_n[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x99, 0xde, 0xf8, 0x36, 0x14, 0x6b, 0xc9, 0xb1, 0xb4, 0xd2, 0x28, 0x31
};
static const uint8_t ecc_p256_n[] = {
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84, 0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51
};
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
static const uint8_t ecc_p384_n[] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0x63, 0x4d, 0x81, 0xf4, 0x37, 0x2d, 0xdf, 0x58, 0x1a, 0x0d, 0xb2, 0x48, 0xb0, 0xa7, 0x7a, 0xec, 0xec, 0x19, 0x6a, 0xcc, 0xc5, 0x29, 0x73
};
static const uint8_t ecc_p521_n[] = {
  0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x51, 0x86, 0x87, 0x83, 0xbf, 0x2f, 0x96, 0x6b, 0x7f, 0xcc, 0x01, 0x48, 0xf7, 0x09, 0xa5, 0xd0, 0x3b, 0xb5, 0xc9, 0xb8, 0x89, 0x9c, 0x47, 0xae, 0xbb, 0x6f, 0xb7, 0x1e, 0x91, 0x38, 0x64, 0x09
};
#endif

// -----------------------------------------------------------------------------
// Static functions

/**
 * @brief
 *   Validate that the key descriptor mathces the PSA attributes struct.
 *
 * @param attributes
 *   The PSA attributes struct representing a key
 * @param key_size
 *   Size of the key
 * @param key_desc
 *   The SE manager key struct representing the same key
 * @returns
 *   PSA_SUCCESS if the structures match,
 *   PSA_ERROR_INVALID_ARGUMENT otherwise
 */
static psa_status_t validate_key_desc(const psa_key_attributes_t* attributes,
                                      size_t key_size,
                                      const sl_se_key_descriptor_t *key_desc)
{
  if (key_desc == NULL || attributes == NULL || key_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // Build a new key descriptor from attributes and check that they match
  sl_se_key_descriptor_t new_key_desc = { 0 };
  psa_status_t status =
    sli_se_key_desc_from_psa_attributes(attributes, key_size, &new_key_desc);
  if (status != PSA_SUCCESS) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (new_key_desc.type != key_desc->type
      || new_key_desc.size != key_desc->size
      || new_key_desc.flags != key_desc->flags
      || new_key_desc.password != key_desc->password
      || new_key_desc.domain != key_desc->domain) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return PSA_SUCCESS;
}

/**
 * @brief
 *   Set the number of bytes of key buffer used for storing the key.
 *
 * @param attributes[in]
 *   The PSA attributes struct representing a key
 * @param data_size[in]
 *   Size of the data that has been stored (excluding the 0x04 byte for public
 *   keys)
 * @param key_buffer_length[out]
 *   Actually used key buffer space
 * @returns
 *   PSA_SUCCESS if key_buffer_length can be set properly,
 *   PSA_ERROR_NOT_SUPPORTED if unsupported location is encountered.
 */
static psa_status_t
set_key_buffer_length(const psa_key_attributes_t *attributes,
                      size_t data_size,
                      size_t *key_buffer_length)
{
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  *key_buffer_length = 0;
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      if (sli_se_has_format_byte(psa_get_key_type(attributes))) {
        data_size++; // Add the format byte offset
      }
      *key_buffer_length =  data_size;
      break;
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      *key_buffer_length = sizeof(sli_se_opaque_wrapped_key_context_t)
                           + sli_se_word_align(data_size);
      break;
    #endif
    default:
      return PSA_ERROR_NOT_SUPPORTED;
      break;
  }
  return PSA_SUCCESS;
}

// -----------------------------------------------------------------------------
// Function implementations

/**
 * @brief
 *   Get the length of the key buffer required for storing the given key
 */
psa_status_t
sli_se_get_key_buffer_length(const psa_key_attributes_t *attributes,
                             sl_se_key_descriptor_t *key_desc,
                             size_t *key_buffer_length)
{
  uint32_t storage_size = 0;
  sl_status_t sl_status = sli_key_get_storage_size(key_desc,
                                                   &storage_size);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return set_key_buffer_length(attributes, storage_size, key_buffer_length);
}

/**
 * @brief
 *   Build a key descriptor from a PSA attributes struct
 *
 * @param attributes
 *   The PSA attributes struct representing a key
 * @param key_size
 *    Size of the key
 * @param key_desc
 *   The SE manager key struct representing the same key
 * @returns
 *   PSA_SUCCESS on success
 *   PSA_ERROR_INVALID_ARGUMENT on invalid attributes
 */
psa_status_t
sli_se_key_desc_from_psa_attributes(const psa_key_attributes_t *attributes,
                                    size_t key_size,
                                    sl_se_key_descriptor_t *key_desc)
{
  size_t attributes_key_size =
    PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  if (attributes_key_size != 0) {
    // If attributes key size is nonzero, it must be equal to key_size
    if (attributes_key_size != key_size) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }
  psa_key_type_t type = psa_get_key_type(attributes);
  psa_key_usage_t usage = psa_get_key_usage_flags(attributes);
  psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
  psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(lifetime);

  memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));

  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT;
      break;
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      /* For the time being, volatile keys directly in SE internal RAM are
       * not supported. Once they are, use the persistence info from the
       * key lifetime to switch between EXTERNAL_WRAPPED and INTERNAL_VOLATILE. */
      key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED;
      break;
    #endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }

  // Dont't accept zero-length keys
  if (key_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (type == PSA_KEY_TYPE_RAW_DATA
      || type == PSA_KEY_TYPE_AES
      || type == PSA_KEY_TYPE_HMAC
      || type == PSA_KEY_TYPE_DERIVE) {
    if (type == PSA_KEY_TYPE_AES) {
      switch (key_size) {
        case 16:
          key_desc->type = SL_SE_KEY_TYPE_AES_128;
          break;
        case 24:
          key_desc->type = SL_SE_KEY_TYPE_AES_192;
          break;
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_AES_256;
          break;
        default:
          // SE doesn't support off-size AES keys
          return PSA_ERROR_INVALID_ARGUMENT;
      }
    } else {
      // Set attributes
      key_desc->type = SL_SE_KEY_TYPE_SYMMETRIC;
    }
    key_desc->size = key_size;
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  } else if (type == PSA_KEY_TYPE_CHACHA20) {
    if (key_size != 0x20) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    // Set attributes
    key_desc->type = SL_SE_KEY_TYPE_CHACHA20;
    key_desc->size = 0x20;
  #endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
  } else if (PSA_KEY_TYPE_IS_ECC(type)) {
    if (PSA_KEY_TYPE_GET_CURVE(type) == PSA_ECC_CURVE_SECP_R1) {
      // Find key size and set key type
      switch (key_size) {
        case 24:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P192;
          break;
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
          break;
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case 48:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P384;
          break;
        case 66:
          key_desc->type = SL_SE_KEY_TYPE_ECC_P521;
          break;
        #endif
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    } else if (PSA_KEY_TYPE_GET_CURVE(type) == PSA_ECC_CURVE_MONTGOMERY) {
      // Find key size and set key type
      switch (key_size) {
        case 32:
          key_desc->type = SL_SE_KEY_TYPE_ECC_X25519;
          break;
        case 56:
          key_desc->type = SL_SE_KEY_TYPE_ECC_X448;
          break;
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }
    #endif
    } else {
      return PSA_ERROR_NOT_SUPPORTED;
    }

    // Set asymmetric args
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(type)) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY;
    } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(type)) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
    } else {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    // Decide whether the key will be used for signing or derivation
    bool is_signing = (usage & (PSA_KEY_USAGE_SIGN_HASH | PSA_KEY_USAGE_VERIFY_HASH)) != 0;
    bool is_deriving = (usage & (PSA_KEY_USAGE_DERIVE | PSA_KEY_USAGE_ENCRYPT | PSA_KEY_USAGE_DECRYPT)) != 0;

    if (is_signing && !is_deriving) {
      key_desc->flags |= SL_SE_KEY_FLAG_ASYMMMETRIC_SIGNING_ONLY;
    } else if (!is_signing && is_deriving) {
      key_desc->flags = (key_desc->flags & ~SL_SE_KEY_FLAG_ASYMMMETRIC_SIGNING_ONLY);
    } else if (is_signing && is_deriving) {
      // SE does not support a key to be used for both signing and derivation operations.
      return PSA_ERROR_NOT_SUPPORTED;
    }
  } else {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Add key restrictions. Only relevant for opaque drivers. If these properties
  // are set for transparent drivers, key generation becomes illegal, as the SE
  // does not allow writing a protected key to a plaintext buffer.
  if (location != PSA_KEY_LOCATION_LOCAL_STORAGE) {
    bool can_export = usage & PSA_KEY_USAGE_EXPORT;
    bool can_copy = usage & PSA_KEY_USAGE_COPY;

    if (can_copy) {
      // We do not support copying opaque keys (currently).
      return PSA_ERROR_NOT_SUPPORTED;
    }
    if (!can_export) {
      key_desc->flags |= SL_SE_KEY_FLAG_NON_EXPORTABLE;
    }
  }

  return PSA_SUCCESS;
}

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
/**
 * @brief
 *   Store the required parts of the key descriptor in the context placed the
 *   start of the given key buffer.
 */
psa_status_t
store_key_desc_in_context(sl_se_key_descriptor_t *key_desc,
                          uint8_t *key_buffer,
                          size_t key_buffer_size)
{
  if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  sli_se_opaque_wrapped_key_context_t *key_context =
    (sli_se_opaque_wrapped_key_context_t *)key_buffer;
  key_context->header.struct_version = SLI_SE_OPAQUE_KEY_CONTEXT_VERSION;
  key_context->header.builtin_key_id = 0;
  memset(&key_context->header.reserved, 0, sizeof(key_context->header.reserved));
  key_context->key_type = key_desc->type;
  key_context->key_size = key_desc->size;
  key_context->key_flags = key_desc->flags;

  return PSA_SUCCESS;
}
#endif

/**
 * @brief
 *   Get the key descriptor from the key buffer and attributes
 */
psa_status_t
sli_se_key_desc_from_input(const psa_key_attributes_t* attributes,
                           const uint8_t *key_buffer,
                           size_t key_buffer_size,
                           sl_se_key_descriptor_t *key_desc)
{
  psa_key_lifetime_t lifetime = psa_get_key_lifetime(attributes);
  psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(lifetime);
  uint32_t key_size = 0; // Retrieved in different ways for different locations
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
    {
      psa_key_type_t key_type = psa_get_key_type(attributes);
      uint8_t *actual_key_buffer = (uint8_t *)key_buffer;
      size_t actual_key_buffer_size = key_buffer_size;

      if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
        // For ECC public keys, the attributes key size is always the factor
        // determining the curve size
        key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
        if (sli_se_has_format_byte(key_type)) {
          // Need to account for the format byte
          if (*key_buffer != 0x04) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
          actual_key_buffer += 1;
          actual_key_buffer_size -= 1;
          if (actual_key_buffer_size != 2 * key_size) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        } else if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type)
                   == PSA_ECC_FAMILY_MONTGOMERY) {
          if (actual_key_buffer_size != key_size) {
            return PSA_ERROR_INVALID_ARGUMENT;
          }
        #endif // VAULT
        } else {
          // No other curves supported yet.
          return PSA_ERROR_NOT_SUPPORTED;
        }
      } else {
        key_size = key_buffer_size;
      }
      // Fill the key desc from attributes
      psa_status_t psa_status = sli_se_key_desc_from_psa_attributes(attributes,
                                                                    key_size,
                                                                    key_desc);
      if (psa_status != PSA_SUCCESS) {
        return psa_status;
      }
      sli_se_key_descriptor_set_plaintext(key_desc,
                                          actual_key_buffer,
                                          actual_key_buffer_size);
      break;
    }
    #if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) || (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
    {
      if (key_buffer_size < sizeof(sli_se_opaque_key_context_header_t)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      sli_se_opaque_key_context_header_t *key_context_header =
        (sli_se_opaque_key_context_header_t *)key_buffer;

      if (key_context_header->struct_version != SLI_SE_OPAQUE_KEY_CONTEXT_VERSION) {
        return PSA_ERROR_STORAGE_FAILURE;
      }

      if (key_context_header->builtin_key_id != 0) {
        switch (key_context_header->builtin_key_id) {
          case SL_SE_KEY_SLOT_APPLICATION_SECURE_BOOT_KEY:
            key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
            key_desc->flags = SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY
                              | SL_SE_KEY_FLAG_ASYMMETRIC_SIGNING_ONLY;
            key_desc->storage.method = SL_SE_KEY_STORAGE_INTERNAL_IMMUTABLE;
            key_desc->storage.location.slot = SL_SE_KEY_SLOT_APPLICATION_SECURE_BOOT_KEY;
            return PSA_SUCCESS;
          case SL_SE_KEY_SLOT_APPLICATION_SECURE_DEBUG_KEY:
            key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
            key_desc->flags = SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY
                              | SL_SE_KEY_FLAG_ASYMMETRIC_SIGNING_ONLY;
            key_desc->storage.method = SL_SE_KEY_STORAGE_INTERNAL_IMMUTABLE;
            key_desc->storage.location.slot = SL_SE_KEY_SLOT_APPLICATION_SECURE_DEBUG_KEY;
            return PSA_SUCCESS;
          case SL_SE_KEY_SLOT_APPLICATION_AES_128_KEY:
            key_desc->type = SL_SE_KEY_TYPE_AES_128;
            key_desc->flags = SL_SE_KEY_FLAG_NON_EXPORTABLE;
            key_desc->storage.method = SL_SE_KEY_STORAGE_INTERNAL_IMMUTABLE;
            key_desc->storage.location.slot = SL_SE_KEY_SLOT_APPLICATION_AES_128_KEY;
            return PSA_SUCCESS;
          #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
          case SL_SE_KEY_SLOT_APPLICATION_ATTESTATION_KEY:
            key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
            key_desc->flags = SL_SE_KEY_FLAG_NON_EXPORTABLE
                              | SL_SE_KEY_FLAG_IS_DEVICE_GENERATED
                              | SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY
                              | SL_SE_KEY_FLAG_ASYMMETRIC_SIGNING_ONLY;
            key_desc->storage.method = SL_SE_KEY_STORAGE_INTERNAL_IMMUTABLE;
            key_desc->storage.location.slot = SL_SE_KEY_SLOT_APPLICATION_ATTESTATION_KEY;
            return PSA_SUCCESS;
          case SL_SE_KEY_SLOT_SE_ATTESTATION_KEY:
            key_desc->type = SL_SE_KEY_TYPE_ECC_P256;
            key_desc->flags = SL_SE_KEY_FLAG_NON_EXPORTABLE
                              | SL_SE_KEY_FLAG_IS_DEVICE_GENERATED
                              | SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY
                              | SL_SE_KEY_FLAG_ASYMMETRIC_SIGNING_ONLY;
            key_desc->storage.method = SL_SE_KEY_STORAGE_INTERNAL_IMMUTABLE;
            key_desc->storage.location.slot = SL_SE_KEY_SLOT_SE_ATTESTATION_KEY;
            return PSA_SUCCESS;
          #endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
          default:
            return PSA_ERROR_DOES_NOT_EXIST;
        }
      } else {
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        // Refer to wrapped key context in input
        sli_se_opaque_wrapped_key_context_t *key_context =
          (sli_se_opaque_wrapped_key_context_t *)key_buffer;

        // Reconstruct key_desc from the key context
        memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));

        key_desc->type = key_context->key_type;
        key_desc->size = key_context->key_size;
        key_desc->flags = key_context->key_flags;

        key_desc->storage.method = SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED;
        key_desc->storage.location.buffer.pointer =
          (uint8_t *)&(key_context->wrapped_buffer);
        key_desc->storage.location.buffer.size = key_buffer_size - (offsetof(sli_se_opaque_wrapped_key_context_t, wrapped_buffer));

        if (sli_key_get_size(key_desc, &key_size) != SL_STATUS_OK) {
          memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        uint32_t key_full_size = key_size;
        if (PSA_KEY_TYPE_ECC_GET_FAMILY(psa_get_key_type(attributes)) == PSA_ECC_CURVE_SECP_R1 && PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(psa_get_key_type(attributes))) {
          key_full_size = 2 * key_full_size;
        }
        if (key_desc->storage.location.buffer.size < key_full_size + SLI_SE_WRAPPED_KEY_OVERHEAD) {
          memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
          return PSA_ERROR_INVALID_ARGUMENT;
        }
        #else // _SILICON_LABS_SECURITY_FEATURE_VAULT
        return PSA_ERROR_NOT_SUPPORTED;
        #endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
      }
      break;
    }
    #endif // MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS || (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }

  // Run a general validation routine once the key desc has been populated
  psa_status_t status = validate_key_desc(attributes, key_size, key_desc);
  if (status != PSA_SUCCESS) {
    memset(key_desc, 0, sizeof(sl_se_key_descriptor_t));
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  return PSA_SUCCESS;
}

/**
 * @brief
 *   Set the relevant location field of the key descriptor
 */
psa_status_t
sli_se_set_key_desc_output(const psa_key_attributes_t* attributes,
                           uint8_t *key_buffer,
                           size_t key_buffer_size,
                           size_t key_size,
                           sl_se_key_descriptor_t *key_desc)
{
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  switch (location) {
    case PSA_KEY_LOCATION_LOCAL_STORAGE:
      if (key_buffer_size < key_size) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
      }
      key_desc->storage.location.buffer.pointer = key_buffer;
      // TODO: Improve SE manager alignment requirements
      key_desc->storage.location.buffer.size =
        sli_se_word_align(key_buffer_size);
      break;
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      key_size = sli_se_word_align(key_size);

      if (key_buffer_size < sizeof(sli_se_opaque_wrapped_key_context_t)
          + key_size) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
      }
      key_desc->storage.location.buffer.pointer =
        key_buffer + offsetof(sli_se_opaque_wrapped_key_context_t,
                              wrapped_buffer);
      key_desc->storage.location.buffer.size =
        key_size + SLI_SE_WRAPPED_KEY_OVERHEAD;
      break;
    #endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
    default:
      return PSA_ERROR_DOES_NOT_EXIST;
  }
  return PSA_SUCCESS;
}

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
/**
 * \brief Import a key in binary format.
 *
 * This function supports any output from psa_export_key(). Refer to the
 * documentation of psa_export_public_key() for the format of public keys
 * and to the documentation of psa_export_key() for the format for
 * other key types.
 *
 * The key data determines the key size. The attributes may optionally
 * specify a key size; in this case it must match the size determined
 * from the key data. A key size of 0 in \p attributes indicates that
 * the key size is solely determined by the key data.
 *
 * Implementations must reject an attempt to import a key of size 0.
 *
 * This specification supports a single format for each key type.
 * Implementations may support other formats as long as the standard
 * format is supported. Implementations that support other formats
 * should ensure that the formats are clearly unambiguous so as to
 * minimize the risk that an invalid input is accidentally interpreted
 * according to a different format.
 *
 * \param[in] attributes    The attributes for the new key.
 *                          The key size is always determined from the
 *                          \p data buffer.
 *                          If the key size in \p attributes is nonzero,
 *                          it must be equal to the size from \p data.
 * \param[out] handle       On success, a handle to the newly created key.
 *                          \c 0 on failure.
 * \param[in] data    Buffer containing the key data. The content of this
 *                    buffer is interpreted according to the type declared
 *                    in \p attributes.
 *                    All implementations must support at least the format
 *                    described in the documentation
 *                    of psa_export_key() or psa_export_public_key() for
 *                    the chosen type. Implementations may allow other
 *                    formats, but should be conservative: implementations
 *                    should err on the side of rejecting content if it
 *                    may be erroneous (e.g. wrong type or truncated data).
 * \param data_length Size of the \p data buffer in bytes.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 *         If the key is persistent, the key material and the key's metadata
 *         have been saved to persistent storage.
 * \retval #PSA_ERROR_ALREADY_EXISTS
 *         This is an attempt to create a persistent key, and there is
 *         already a persistent key with the given identifier.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         The key type or key size is not supported, either by the
 *         implementation in general or in this particular persistent location.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key attributes, as a whole, are invalid.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key data is not correctly formatted.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The size in \p attributes is nonzero and does not match the size
 *         of the key data.
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_INSUFFICIENT_STORAGE
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_opaque_import_key(const psa_key_attributes_t *attributes,
                                      const uint8_t *data,
                                      size_t data_length,
                                      uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      size_t *key_buffer_length,
                                      size_t *bits)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_length == 0
      || key_buffer_length == NULL
      || bits == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  *key_buffer_length = 0;

  psa_key_type_t key_type = psa_get_key_type(attributes);

  // Store bits value for imported key
  *bits = 8 * data_length;
  if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_SECP_R1) {
    if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
      *bits -= 8;
      *bits /= 2;
    }
    if (*bits == PSA_BITS_TO_BYTES(521) * 8) {
      *bits = 521;
    }
  } else if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_MONTGOMERY) {
    if (data_length == 32) {
      *bits = 255;
    }
  }

  size_t offset = 0;
  size_t padding = 0;
  size_t key_size = 0;
  if (PSA_KEY_TYPE_IS_ECC(key_type)) {
    // Validate key and get size.
    psa_status = sli_se_driver_validate_key(attributes,
                                            data,
                                            data_length,
                                            &key_size);
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
    key_size = PSA_BITS_TO_BYTES(key_size);
    if (sli_se_has_format_byte(key_type)) {
      data_length -= 1;
      data += 1;
    }
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_SECP_R1) {
      // We must add some padding if offset is nonzero
      offset = sli_se_get_padding(key_size);
    }
  } else {
    key_size = data_length;
  }

  // Size must at least fit max ECC key size plus padding
  uint8_t temp_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };

  // Create a key desc that will represent the wrapped key
  sl_se_key_descriptor_t imported_key_desc = { 0 };
  psa_status =
    sli_se_key_desc_from_psa_attributes(attributes,
                                        key_size,
                                        &imported_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  // Create a key desc representing the plaintext input key
  sl_se_key_descriptor_t plaintext_key_desc = imported_key_desc;
  if (offset == 0) {
    sli_se_key_descriptor_set_plaintext(&plaintext_key_desc, data, data_length);
  } else {
    // We must account for the offset.
    // Write the key data to offset position in temp buffer
    if (sizeof(temp_buffer) < data_length + 2 * offset) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_FAMILY_SECP_R1) {
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
        sli_se_pad_big_endian(temp_buffer, data, key_size);
        padding = offset;
      } else {
        // Must be public key
        sli_se_pad_curve_point(temp_buffer, data, key_size);
        padding = 2 * offset;
      }
      sli_se_key_descriptor_set_plaintext(&plaintext_key_desc,
                                          temp_buffer,
                                          data_length + padding);
    } else {
      return PSA_ERROR_CORRUPTION_DETECTED;
    }
  }
  sl_se_command_context_t cmd_ctx = SL_SE_COMMAND_CONTEXT_INIT;
  sl_status_t sl_status = SL_STATUS_OK;
  // Set location specific properties for the output key buffer
  psa_status = sli_se_set_key_desc_output(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          data_length + padding,
                                          &imported_key_desc);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  }

  // Call SE manager to import the key
  sl_status = sl_se_import_key(&cmd_ctx,
                               &plaintext_key_desc,
                               &imported_key_desc);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    // Add the key desc parameters to the output array
    psa_status = store_key_desc_in_context(&imported_key_desc, key_buffer, key_buffer_size);
    if (psa_status != PSA_SUCCESS) {
      goto exit;
    }

    psa_status = set_key_buffer_length(attributes,
                                       data_length + padding,
                                       key_buffer_length);
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  }
  exit:
  memset(temp_buffer, 0, sizeof(temp_buffer));
  return psa_status;
}

/**
 * \brief Export a key in binary format.
 *
 * The output of this function can be passed to psa_import_key() to
 * create an equivalent object.
 *
 * If the implementation of psa_import_key() supports other formats
 * beyond the format specified here, the output from psa_export_key()
 * must use the representation specified here, not the original
 * representation.
 *
 * For standard key types, the output format is as follows:
 *
 * - For symmetric keys (including MAC keys), the format is the
 *   raw bytes of the key.
 * - For DES, the key data consists of 8 bytes. The parity bits must be
 *   correct.
 * - For Triple-DES, the format is the concatenation of the
 *   two or three DES keys.
 * - For RSA key pairs (#PSA_KEY_TYPE_RSA_KEY_PAIR), the format
 *   is the non-encrypted DER encoding of the representation defined by
 *   PKCS\#1 (RFC 8017) as `RSAPrivateKey`, version 0.
 *   ```
 *   RSAPrivateKey ::= SEQUENCE {
 *       version             INTEGER,  -- must be 0
 *       modulus             INTEGER,  -- n
 *       publicExponent      INTEGER,  -- e
 *       privateExponent     INTEGER,  -- d
 *       prime1              INTEGER,  -- p
 *       prime2              INTEGER,  -- q
 *       exponent1           INTEGER,  -- d mod (p-1)
 *       exponent2           INTEGER,  -- d mod (q-1)
 *       coefficient         INTEGER,  -- (inverse of q) mod p
 *   }
 *   ```
 * - For elliptic curve key pairs (key types for which
 *   #PSA_KEY_TYPE_IS_ECC_KEY_PAIR is true), the format is
 *   a representation of the private value as a `ceiling(m/8)`-byte string
 *   where `m` is the bit size associated with the curve, i.e. the bit size
 *   of the order of the curve's coordinate field. This byte string is
 *   in little-endian order for Montgomery curves (curve types
 *   `PSA_ECC_FAMILY_CURVEXXX`), and in big-endian order for Weierstrass
 *   curves (curve types `PSA_ECC_FAMILY_SECTXXX`, `PSA_ECC_FAMILY_SECPXXX`
 *   and `PSA_ECC_FAMILY_BRAINPOOL_PXXX`).
 *   For Weierstrass curves, this is the content of the `privateKey` field of
 *   the `ECPrivateKey` format defined by RFC 5915.  For Montgomery curves,
 *   the format is defined by RFC 7748, and output is masked according to §5.
 * - For Diffie-Hellman key exchange key pairs (key types for which
 *   #PSA_KEY_TYPE_IS_DH_KEY_PAIR is true), the
 *   format is the representation of the private key `x` as a big-endian byte
 *   string. The length of the byte string is the private key size in bytes
 *   (leading zeroes are not stripped).
 * - For public keys (key types for which #PSA_KEY_TYPE_IS_PUBLIC_KEY is
 *   true), the format is the same as for psa_export_public_key().
 *
 * The policy on the key must have the usage flag #PSA_KEY_USAGE_EXPORT set.
 *
 * \param handle            Handle to the key to export.
 * \param[out] data         Buffer where the key data is to be written.
 * \param data_size         Size of the \p data buffer in bytes.
 * \param[out] data_length  On success, the number of bytes
 *                          that make up the key data.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 *         The key does not have the #PSA_KEY_USAGE_EXPORT flag.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_BUFFER_TOO_SMALL
 *         The size of the \p data buffer is too small. You can determine a
 *         sufficient buffer size by calling
 *         #PSA_KEY_EXPORT_MAX_SIZE(\c type, \c bits)
 *         where \c type is the key type
 *         and \c bits is the key size in bits.
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_opaque_export_key(const psa_key_attributes_t *attributes,
                                      const uint8_t *key_buffer,
                                      size_t key_buffer_size,
                                      uint8_t *data,
                                      size_t data_size,
                                      size_t *data_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_size == 0
      || data_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  // Check that key can be exported
  if (!(psa_get_key_usage_flags(attributes) & PSA_KEY_USAGE_EXPORT)) {
    return PSA_ERROR_NOT_PERMITTED;
  }

  sl_se_key_descriptor_t imported_key = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &imported_key);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Create a plaintext key for the output
  sl_se_key_descriptor_t plaintext_key = imported_key;
  uint32_t storage_size = 0;
  psa_key_type_t key_type = psa_get_key_type(attributes);
  sl_status_t sl_status = sli_key_get_storage_size(&plaintext_key, &storage_size);
  uint32_t prepend_format_byte = sli_se_has_format_byte(key_type);
  if (prepend_format_byte == 1) {
    // Make room for the format byte
    *data = 0x04;
    data += 1;
    data_size -= 1;
  }
  // We must handle non-word-aligned keys with a temporary buffer
  uint8_t temp_key_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  size_t key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  size_t padding = 0;
  if (PSA_KEY_TYPE_IS_ECC(key_type)) {
    padding = sli_se_get_padding(key_size);
  }
  if (padding > 0) {
    if (storage_size > sizeof(temp_key_buffer)) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
    sli_se_key_descriptor_set_plaintext(&plaintext_key,
                                        temp_key_buffer,
                                        sizeof(temp_key_buffer));
    storage_size -= padding;
    if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
      // Padding must be applied twice for public keys
      storage_size -= padding;
    }
  } else {
    if ((storage_size - imported_key.size) < 4) {
      // SE manager has rounded the storage size up for word-alignment
      storage_size = imported_key.size;
    }
    sli_se_key_descriptor_set_plaintext(&plaintext_key, data, data_size);
  }
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  if (storage_size > data_size) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Export key
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  sl_status = sl_se_export_key(&cmd_ctx, &imported_key, &plaintext_key);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    psa_status = PSA_SUCCESS;

    // Handle padding.
    if (padding > 0) {
      // Copy out the padded key
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
        sli_se_unpad_big_endian(temp_key_buffer, data, key_size);
      } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
        sli_se_unpad_curve_point(temp_key_buffer, data, key_size);
      } else {
        // This should never happen
        return PSA_ERROR_BAD_STATE;
      }
    }

    // Apply masking.
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)
        && PSA_KEY_TYPE_GET_CURVE(key_type) == PSA_ECC_CURVE_MONTGOMERY) {
      if (psa_get_key_bits(attributes) == 255) {
        data[0] &= 248U;
        data[31] &= 127U;
        data[31] |= 64U;
      } else if (psa_get_key_bits(attributes) == 448) {
        data[0] &= 252U;
        data[55] |= 128U;
      }
    }

    // Successful operation. Set ouput length
    *data_length = storage_size + prepend_format_byte;
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT

/**
 * \brief Generate a key or key pair.
 *
 * The key is generated randomly.
 * Its location, usage policy, type and size are taken from \p attributes.
 *
 * Implementations must reject an attempt to generate a key of size 0.
 *
 * The following type-specific considerations apply:
 * - For RSA keys (#PSA_KEY_TYPE_RSA_KEY_PAIR),
 *   the public exponent is 65537.
 *   The modulus is a product of two probabilistic primes
 *   between 2^{n-1} and 2^n where n is the bit size specified in the
 *   attributes.
 *
 * \param[in] attributes    The attributes for the new key.
 * \param[out] handle       On success, a handle to the newly created key.
 *                          \c 0 on failure.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 *         If the key is persistent, the key material and the key's metadata
 *         have been saved to persistent storage.
 * \retval #PSA_ERROR_ALREADY_EXISTS
 *         This is an attempt to create a persistent key, and there is
 *         already a persistent key with the given identifier.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_INSUFFICIENT_ENTROPY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_INSUFFICIENT_STORAGE
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_generate_key(const psa_key_attributes_t *attributes,
                                        uint8_t *key_buffer,
                                        size_t key_buffer_size,
                                        size_t *key_buffer_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  size_t key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  if (key_size == 0) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  if (PSA_KEY_TYPE_IS_PUBLIC_KEY(key_type)) {
    // Does not make sense to generate a public key for itself
    // The remainder of the function does not support outputting public keys,
    // so error out here.
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Generate a key desc
  sl_se_key_descriptor_t key_desc = { 0 };
  psa_status_t psa_status =
    sli_se_key_desc_from_psa_attributes(attributes,
                                        key_size,
                                        &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  psa_status = sli_se_set_key_desc_output(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          key_size,
                                          &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Generate the key using SE manager
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status_t sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  sl_status = sl_se_generate_key(&cmd_ctx, &key_desc);
  if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  } else {
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    if (PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes))
        != PSA_KEY_LOCATION_LOCAL_STORAGE) {
      // Add the key desc to the output array for opaque keys
      psa_status = store_key_desc_in_context(&key_desc, key_buffer, key_buffer_size);
      if (psa_status != PSA_SUCCESS) {
        goto exit;
      }
    }
  #endif
    if (PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes))
        == PSA_KEY_LOCATION_LOCAL_STORAGE
        && PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)
        && PSA_KEY_TYPE_GET_CURVE(key_type) == PSA_ECC_CURVE_MONTGOMERY) {
      // Take care of masking.
      if (psa_get_key_bits(attributes) == 255) {
        key_buffer[0] &= 248U;
        key_buffer[31] &= 127U;
        key_buffer[31] |= 64U;
      } else if (psa_get_key_bits(attributes) == 448) {
        key_buffer[0] &= 252U;
        key_buffer[55] |= 128U;
      }
    }
    psa_status = set_key_buffer_length(attributes, key_size, key_buffer_length);
  }
  // Cleanup
  exit:
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

// Map the opaque function to the general implementation
psa_status_t
sli_se_opaque_generate_key(const psa_key_attributes_t *attributes,
                           uint8_t *key_buffer,
                           size_t key_buffer_size,
                           size_t *key_buffer_length)
{
  return sli_se_driver_generate_key(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    key_buffer_length);
}

// Map the transparent function to the general implementation
psa_status_t
sli_se_transparent_generate_key(const psa_key_attributes_t *attributes,
                                uint8_t *key_buffer,
                                size_t key_buffer_size,
                                size_t *key_buffer_length)
{
  psa_key_type_t type = psa_get_key_type(attributes);

  // We don't support generating symmetric keys with transparent drivers;
  // it should be done by the core instead.
  if (PSA_KEY_TYPE_IS_UNSTRUCTURED(type)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return sli_se_driver_generate_key(attributes,
                                    key_buffer,
                                    key_buffer_size,
                                    key_buffer_length);
}

/**
 * \brief Export a public key or the public part of a key pair in binary format.
 *
 * The output of this function can be passed to psa_import_key() to
 * create an object that is equivalent to the public key.
 *
 * This specification supports a single format for each key type.
 * Implementations may support other formats as long as the standard
 * format is supported. Implementations that support other formats
 * should ensure that the formats are clearly unambiguous so as to
 * minimize the risk that an invalid input is accidentally interpreted
 * according to a different format.
 *
 * For standard key types, the output format is as follows:
 * - For RSA public keys (#PSA_KEY_TYPE_RSA_PUBLIC_KEY), the DER encoding of
 *   the representation defined by RFC 3279 &sect;2.3.1 as `RSAPublicKey`.
 *   ```
 *   RSAPublicKey ::= SEQUENCE {
 *      modulus            INTEGER,    -- n
 *      publicExponent     INTEGER  }  -- e
 *   ```
 * - For elliptic curve public keys (key types for which
 *   #PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY is true), the format is the uncompressed
 *   representation defined by SEC1 &sect;2.3.3 as the content of an ECPoint.
 *   Let `m` be the bit size associated with the curve, i.e. the bit size of
 *   `q` for a curve over `F_q`. The representation consists of:
 *      - The byte 0x04;
 *      - `x_P` as a `ceiling(m/8)`-byte string, big-endian;
 *      - `y_P` as a `ceiling(m/8)`-byte string, big-endian.
 * - For Diffie-Hellman key exchange public keys (key types for which
 *   #PSA_KEY_TYPE_IS_DH_PUBLIC_KEY is true),
 *   the format is the representation of the public key `y = g^x mod p` as a
 *   big-endian byte string. The length of the byte string is the length of the
 *   base prime `p` in bytes.
 *
 * Exporting a public key object or the public part of a key pair is
 * always permitted, regardless of the key's usage flags.
 *
 * \param handle            Handle to the key to export.
 * \param[out] data         Buffer where the key data is to be written.
 * \param data_size         Size of the \p data buffer in bytes.
 * \param[out] data_length  On success, the number of bytes
 *                          that make up the key data.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The key is neither a public key nor a key pair.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_BUFFER_TOO_SMALL
 *         The size of the \p data buffer is too small. You can determine a
 *         sufficient buffer size by calling
 *         #PSA_KEY_EXPORT_MAX_SIZE(#PSA_KEY_TYPE_PUBLIC_KEY_OF_KEY_PAIR(\c type), \c bits)
 *         where \c type is the key type
 *         and \c bits is the key size in bits.
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t
sli_se_driver_export_public_key(const psa_key_attributes_t *attributes,
                                const uint8_t *key_buffer,
                                size_t key_buffer_size,
                                uint8_t *data,
                                size_t data_size,
                                size_t *data_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_size == 0
      || data_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  psa_key_type_t key_type = psa_get_key_type(attributes);

  // Build key descs for the private key
  sl_se_key_descriptor_t priv_key_desc = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &priv_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // ECC public keys are written in uncompressed format with a preceeding 0x04
  // format byte. This byte should however not be present for Montgomery keys
  uint32_t prepend_format_byte = 1;
  if (PSA_KEY_TYPE_ECC_GET_FAMILY(key_type) == PSA_ECC_CURVE_MONTGOMERY) {
    prepend_format_byte = 0;
  }

  sl_se_key_descriptor_t pub_key_desc = priv_key_desc;
  size_t padding = 0;
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  // Since we were able to successfully build a key desc, we know that the key
  // is supported. However, we must also account for non-word-aligned keys
  uint8_t temp_pub_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  uint8_t temp_priv_buffer[SLI_SE_MAX_PADDED_KEY_PAIR_SIZE] = { 0 };
  if (PSA_KEY_TYPE_IS_ECC(key_type)) {
    padding = sli_se_get_padding(PSA_BITS_TO_BYTES(psa_get_key_bits(attributes)));
  }
  if (padding > 0) {
    if (priv_key_desc.storage.method == SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT) {
      // We must only fix the padding for plaintext private keys. Opaque padding
      // is already handled in import_key
      size_t priv_key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
      if (key_buffer_size < priv_key_size) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      sli_se_pad_big_endian(temp_priv_buffer, key_buffer, priv_key_size);
      sli_se_key_descriptor_set_plaintext(&priv_key_desc,
                                          temp_priv_buffer,
                                          sizeof(temp_priv_buffer));
    }
    // Point the key desc to the temp buffer
    sli_se_key_descriptor_set_plaintext(&pub_key_desc,
                                        temp_pub_buffer,
                                        sizeof(temp_pub_buffer));
  } else
  #endif // VAULT
  {
    // Account for format byte where applicable
    sli_se_key_descriptor_set_plaintext(&pub_key_desc,
                                        data + prepend_format_byte,
                                        data_size - prepend_format_byte);
  }
  // Clear non exportable and private key flags from the public key desc,
  // And set the public flag
  pub_key_desc.flags &= ~(SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY
                          | SL_SE_KEY_FLAG_NON_EXPORTABLE);
  pub_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
  uint32_t storage_size = 0;
  sl_status_t sl_status =
    sli_key_get_storage_size(&pub_key_desc, &storage_size);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  // We must fit entire output key + possibly a format byte
  // We don't have to fit the padding bytes into the data buffer.
  storage_size = storage_size + prepend_format_byte - (2 * padding);
  if (data_size < storage_size) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  sl_status = sl_se_export_public_key(&cmd_ctx, &priv_key_desc, &pub_key_desc);
  if (sl_status == SL_STATUS_FAIL) {
    // This specific code maps to 'does not exist' for builtin keys
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
  } else if (sl_status != SL_STATUS_OK) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  } else {
    psa_status = PSA_SUCCESS;
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    if (padding > 0) {
      // Now it is time to copy the actual ket from the temp buffer to the
      // output buffer. Write to an offset if applicable, to account for the
      // format byte
      sli_se_unpad_curve_point(temp_pub_buffer,
                               data + prepend_format_byte,
                               (storage_size - prepend_format_byte) / 2);
      memset(temp_pub_buffer, 0, sizeof(temp_pub_buffer));
    }
    #endif // VAULT
    // Write the uncompressed format byte and actual data length
    if (prepend_format_byte == 1) {
      *data = 0x04;
    }
    *data_length = storage_size;
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

// Simple wrapper for opaque driver
psa_status_t
sli_se_opaque_export_public_key(const psa_key_attributes_t *attributes,
                                const uint8_t *key_buffer,
                                size_t key_buffer_size,
                                uint8_t *data,
                                size_t data_size,
                                size_t *data_length)
{
  return sli_se_driver_export_public_key(attributes,
                                         key_buffer,
                                         key_buffer_size,
                                         data,
                                         data_size,
                                         data_length);
}

// Simple wrapper for transparent driver
psa_status_t
sli_se_transparent_export_public_key(const psa_key_attributes_t *attributes,
                                     const uint8_t *key_buffer,
                                     size_t key_buffer_size,
                                     uint8_t *data,
                                     size_t data_size,
                                     size_t *data_length)
{
  return sli_se_driver_export_public_key(attributes,
                                         key_buffer,
                                         key_buffer_size,
                                         data,
                                         data_size,
                                         data_length);
}

psa_status_t sli_se_driver_validate_key(const psa_key_attributes_t *attributes,
                                        const uint8_t *data,
                                        size_t data_length,
                                        size_t *bits)
{
  psa_status_t return_status = PSA_ERROR_CORRUPTION_DETECTED;

  // Argument check.
  if (attributes == NULL
      || data == NULL
      || data_length == 0
      || bits == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);

  // Driver can only handle ECC keys.
  if (!PSA_KEY_TYPE_IS_ECC(key_type)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);

  switch (curve_type) {
    case PSA_ECC_CURVE_SECP_R1: {
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) { // Private key.
        // Determine key bit-size (including possible padding).
        *bits = data_length * 8;

        uint8_t *modulus_ptr = NULL;
        switch (data_length * 8) {
          case 192:
            modulus_ptr = (uint8_t*)ecc_p192_n;
            break;
          case 224:
            return PSA_ERROR_NOT_SUPPORTED;
            break;
          case 256:
            modulus_ptr = (uint8_t*)ecc_p256_n;
            break;
          #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
          case 384:
            modulus_ptr = (uint8_t*)ecc_p384_n;
            break;
          case 528:
            // Actually a 521 bit long key which has been padded to 66 bytes.
            *bits = 521;
            modulus_ptr = (uint8_t*)ecc_p521_n;
            break;
          #else
          case 384: // fall through
          case 528:
            return PSA_ERROR_NOT_SUPPORTED;
            break;
          #endif
          default:
            return PSA_ERROR_INVALID_ARGUMENT;
            break;
        }

        // Compare private key to maximum allowed key and check that it is non-zero.
        uint32_t non_zero_accumulator = 0;
        uint8_t key_is_valid = 0;
        if ((((uint32_t)data) & 0x3) == 0
            && *bits != 521) { // Word-aligned.
          for (size_t i = 0; i < data_length / 4; ++i) {
            non_zero_accumulator |= *(uint32_t*)&data[i * 4];

            if (*(uint32_t*)&data[i * 4] < *(uint32_t*)&modulus_ptr[i * 4]) {
              // Lesser than n - 1.
              key_is_valid = 1;
            } else if (*(uint32_t*)&data[i * 4] > *(uint32_t*)&modulus_ptr[i * 4]
                       && key_is_valid != 1) {
              // Greater than modulus.
              return PSA_ERROR_INVALID_ARGUMENT;
            } else if (i == data_length / 4 - 1
                       && key_is_valid != 1) {
              // Equal to modulus.
              return PSA_ERROR_INVALID_ARGUMENT;
            }
          }
        } else { // Not word-aligned.
          for (size_t i = 0; i < data_length; ++i) {
            non_zero_accumulator |= data[i];

            if (data[i] < modulus_ptr[i]) {
              // Lesser than n - 1.
              key_is_valid = 1;
            } else if (data[i] > modulus_ptr[i]
                       && key_is_valid != 1) {
              // Greater than modulus.
              return PSA_ERROR_INVALID_ARGUMENT;
            } else if (i == data_length - 1
                       && key_is_valid != 1) {
              // Equal to modulus.
              return PSA_ERROR_INVALID_ARGUMENT;
            }
          }
        }

        if (key_is_valid != 1
            || non_zero_accumulator == 0) {
          return PSA_ERROR_INVALID_ARGUMENT;
        } else {
          return_status = PSA_SUCCESS;
        }
      } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) { // Public key.
        // Check that uncompressed representation is given.
        if (data[0] != 0x04) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }

        // Temporary buffer for storing ECDH input private key,
        // possibly padded input public key, and output shared key.
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        // If input public key requires padding, it will be stored
        // starting from the third element. By doing this, and setting
        // the first half-word equal to 1, we are guaranteed to not end up
        // with a private key that is acidentally greater than the order
        // n of the curve group (since the fields size q is greater than n).
        uint8_t tmp_key_buffer[2 + SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
        #else
        uint8_t tmp_key_buffer[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
        #endif
        // Make sure that ECDH private key is non-zero.
        tmp_key_buffer[0] = 1;

        // Input public key descriptor.
        sl_se_key_descriptor_t input_public_key_desc = {
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = (uint8_t*)data + 1,
          .storage.location.buffer.size = data_length - 1,
        };

        // Temporary private key descriptor.
        sl_se_key_descriptor_t tmp_private_key_desc = {
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = tmp_key_buffer,
          .storage.location.buffer.size = sizeof(tmp_key_buffer),
        };

        // Temporary shared key descriptor.
        sl_se_key_descriptor_t tmp_shared_key_desc = {
          .type = SL_SE_KEY_TYPE_SYMMETRIC,
          .storage.method = SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT,
          .storage.location.buffer.pointer = tmp_key_buffer,
          .storage.location.buffer.size = sizeof(tmp_key_buffer),
        };

        // Determine key bit size (including padding).
        *bits = (data_length - 1) * 8 / 2;

        uint8_t padding_bytes = 0;
        switch (*bits) {
          case 192:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P192;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P192;
            break;
          case 224:
            return PSA_ERROR_NOT_SUPPORTED;
            break;
          case 256:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P256;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P256;
            break;
          #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
          case 384:
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P384;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P384;
            break;
          case 528:
            // Actually a 521 bit long key which has been padded to 66 bytes.
            *bits = 521;
            padding_bytes = 2;
            input_public_key_desc.type = SL_SE_KEY_TYPE_ECC_P521;
            tmp_private_key_desc.type = SL_SE_KEY_TYPE_ECC_P521;
            break;
          #else
          case 384: // fall through
          case 528:
            return PSA_ERROR_NOT_SUPPORTED;
            break;
          #endif
          default:
            return PSA_ERROR_INVALID_ARGUMENT;
            break;
        }

        // Set missing key descriptor attributes.
        input_public_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
        tmp_private_key_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY;
        tmp_shared_key_desc.size = (PSA_BITS_TO_BYTES(*bits) + padding_bytes) * 2;

        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        // Should currently only happen for curve P521.
        if (padding_bytes > 0) {
          // Pad public key. Offset +2 in order to avoid problem with invalid private key.
          sli_se_pad_curve_point(tmp_key_buffer + 2,
                                 (uint8_t*)data + 1,
                                 PSA_BITS_TO_BYTES(*bits));
          sli_se_key_descriptor_set_plaintext(&input_public_key_desc,
                                              tmp_key_buffer + 2,
                                              sizeof(tmp_key_buffer) - 2);
        }
        #endif // (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

        // Create ephemeral SE command context.
        sl_se_command_context_t cmd_ctx = SL_SE_COMMAND_CONTEXT_INIT;
        sl_status_t sl_status = sl_se_init_command_context(&cmd_ctx);
        if (sl_status != SL_STATUS_OK) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        // Perform key agreement algorithm (ECDH).
        sl_status = sl_se_ecdh_compute_shared_secret(&cmd_ctx,
                                                     &tmp_private_key_desc,
                                                     &input_public_key_desc,
                                                     &tmp_shared_key_desc);

        // Zero out intermediate results.
        if (padding_bytes == 0) {
          sli_psa_zeroize(tmp_key_buffer, (PSA_BITS_TO_BYTES(*bits)) * 2);
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        } else {
          sli_psa_zeroize(tmp_key_buffer, 2 + (PSA_BITS_TO_BYTES(*bits) + padding_bytes) * 2);
        #endif
        }

        if (sl_status != SL_STATUS_OK) {
          return PSA_ERROR_INVALID_ARGUMENT;
        } else {
          return_status = PSA_SUCCESS;
        }
      }
      break;
    }
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_ECC_CURVE_MONTGOMERY:
      switch (data_length) {
        case 32:
          // For private keys, validate clamping.
          if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
            if ((data[0] & 7U) != 0
                || (data[31] & 128U) != 0
                || (data[31] & 64U) != 64U) {
              return PSA_ERROR_INVALID_ARGUMENT;
            }
          }
          *bits = 255;
          return_status = PSA_SUCCESS;
          break;
        case 56:
          // For private keys, validate clamping.
          if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
            if ((data[0] & 3U) != 0
                || (data[55] & 128U) != 128U) {
              return PSA_ERROR_INVALID_ARGUMENT;
            }
          }
          *bits = 448;
          return_status = PSA_SUCCESS;
          break;
        default:
          return PSA_ERROR_INVALID_ARGUMENT;
          break;
      }
      break;
    #endif // (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    default:
      return PSA_ERROR_NOT_SUPPORTED;
      break;
  }
  return return_status;
}

// Transparent wrapper.
psa_status_t sli_se_transparent_validate_key(const psa_key_attributes_t *attributes,
                                             const uint8_t *data,
                                             size_t data_length,
                                             size_t *bits)
{
  return sli_se_driver_validate_key(attributes,
                                    data,
                                    data_length,
                                    bits);
}

#endif // SEMAILBOX_PRESENT

#ifdef __cplusplus
}
#endif
