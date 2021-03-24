/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Secure Element Signature Driver functions.
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
#include "sli_se_driver_key_management.h"

#include "sl_se_manager.h"
#include "sl_se_manager_hash.h"
#include "sl_se_manager_signature.h"
#include <string.h>

/*******************************************************************************
 * Statics *
 ******************************************************************************/

/**
 * @brief
 *   Validate that the curve is supported by hardware and
 */
static psa_status_t
check_curve_availability(const psa_key_attributes_t *attributes)
{
  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curvetype = PSA_KEY_TYPE_GET_CURVE(key_type);
  if (curvetype == PSA_ECC_CURVE_SECP_R1) {
    size_t key_bits = psa_get_key_bits(attributes);
    switch (key_bits) {
      case 192: // Intentional
      case 256: // Intentional
      #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
      case 384: // Intentional
      case 521: // Intentional
      #endif
        break; // This break catches all the supported curves
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }
  } else if (curvetype == PSA_ECC_CURVE_SECP_K1) {
    // TODO: introduce custom domains to enable secpxxxk1
    return PSA_ERROR_NOT_SUPPORTED;
  } else {
    return PSA_ERROR_NOT_SUPPORTED;
  }
  return PSA_SUCCESS;
}

/*******************************************************************************
 * Driver functions *
 ******************************************************************************/

/**
 * \brief Sign a hash or short message with a private key.
 *
 * Note that to perform a hash-and-sign signature algorithm, you must
 * first calculate the hash by calling psa_hash_setup(), psa_hash_update()
 * and psa_hash_finish(). Then pass the resulting hash as the \p hash
 * parameter to this function. You can use #PSA_ALG_SIGN_GET_HASH(\p alg)
 * to determine the hash algorithm to use.
 *
 * \param handle                Handle to the key to use for the operation.
 *                              It must be an asymmetric key pair.
 * \param alg                   A signature algorithm that is compatible with
 *                              the type of \p handle.
 * \param[in] hash              The hash or message to sign.
 * \param hash_length           Size of the \p hash buffer in bytes.
 * \param[out] signature        Buffer where the signature is to be written.
 * \param signature_size        Size of the \p signature buffer in bytes.
 * \param[out] signature_length On success, the number of bytes
 *                              that make up the returned signature value.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 * \retval #PSA_ERROR_BUFFER_TOO_SMALL
 *         The size of the \p signature buffer is too small. You can
 *         determine a sufficient buffer size by calling
 *         #PSA_SIGN_OUTPUT_SIZE(\c key_type, \c key_bits, \p alg)
 *         where \c key_type and \c key_bits are the type and bit-size
 *         respectively of \p handle.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_INSUFFICIENT_ENTROPY
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_sign_hash(const psa_key_attributes_t *attributes,
                              const uint8_t *key_buffer,
                              size_t key_buffer_size,
                              psa_algorithm_t alg,
                              const uint8_t *hash,
                              size_t hash_length,
                              uint8_t *signature,
                              size_t signature_size,
                              size_t *signature_length)
{
  uint8_t* tmp_signature_p = signature;
  size_t tmp_signature_size = signature_size;

  // Argument check
  if (hash == NULL
      || hash_length == 0
      || signature == NULL
      || signature_length == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check the requested algorithm is ECDSA with randomized k
  if (!PSA_ALG_IS_RANDOMIZED_ECDSA(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_se_key_descriptor_t key_desc = { 0 };

  // Initialize key descriptor and verify key buffer size
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Verify and set key attributes
  psa_key_type_t keytype = psa_get_key_type(attributes);

  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(keytype)) {
    // Validate that the input
    psa_status = check_curve_availability(attributes);
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
    if (signature_size
        < PSA_ECDSA_SIGNATURE_SIZE(psa_get_key_bits(attributes))) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }
  } else {
    // Not able to sign using non-ECC keys, or using public keys
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  size_t key_bits = psa_get_key_bits(attributes);
  size_t key_size = PSA_BITS_TO_BYTES(key_bits);
  size_t offset = sli_se_get_padding(key_size);
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  // P-521 (or any curve size that's not word-multiple) requires alignment on
  // word boundaries, instead of byte boundaries such as PSA Crypto defines as
  // input here.
  uint8_t temp_key_buf[SLI_SE_MAX_PADDED_KEY_PAIR_SIZE] = { 0 };
  uint8_t temp_signature_buffer[SLI_SE_MAX_PADDED_SIGNATURE_SIZE] = { 0 };
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

  if (offset > 0) {
    // We can only manipulate the input key for transparent keys.
    // For opaque keys, we will just have to rely on the key import operation
    // handling this
    if (location == PSA_KEY_LOCATION_LOCAL_STORAGE) {
      if ((offset + key_buffer_size) > sizeof(temp_key_buf)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      sli_se_pad_big_endian(temp_key_buf, key_buffer, key_buffer_size);
      // Since we know that this must be a plaintext key, we can freely
      // modify the key descriptor
      key_desc.storage.location.buffer.pointer = temp_key_buf;
      key_desc.storage.location.buffer.size = sizeof(temp_key_buf);
    }

    tmp_signature_p = temp_signature_buffer;
    tmp_signature_size = sizeof(temp_signature_buffer);
  }
#endif
  if (tmp_signature_size < 2 * (offset + key_size)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  tmp_signature_size = 2 * (offset + key_size);

  sl_status_t status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Run signature generation
  status = sl_se_ecc_sign(&cmd_ctx,
                          &key_desc,
                          SL_SE_HASH_NONE,
                          true,
                          hash,
                          hash_length,
                          tmp_signature_p,
                          tmp_signature_size
                          );

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  if (offset > 0) {
    memset(temp_key_buf, 0, sizeof(temp_key_buf));
    // Copy over from temp signature
    sli_se_unpad_curve_point(temp_signature_buffer, signature, key_size);
  }
#endif

  if (status == SL_STATUS_OK) {
    *signature_length = PSA_ECDSA_SIGNATURE_SIZE(key_bits);
    psa_status = PSA_SUCCESS;
  } else {
    if (status == SL_STATUS_FAIL) {
      psa_status = PSA_ERROR_DOES_NOT_EXIST;
    } else {
      psa_status = PSA_ERROR_HARDWARE_FAILURE;
    }
  }

  // Cleanup
  status = sl_se_deinit_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

// Transparent wrapper
psa_status_t sli_se_transparent_sign_hash(const psa_key_attributes_t *attributes,
                                          const uint8_t *key_buffer,
                                          size_t key_buffer_size,
                                          psa_algorithm_t alg,
                                          const uint8_t *hash,
                                          size_t hash_length,
                                          uint8_t *signature,
                                          size_t signature_size,
                                          size_t *signature_length)
{
  return sli_se_sign_hash(attributes,
                          key_buffer,
                          key_buffer_size,
                          alg,
                          hash,
                          hash_length,
                          signature,
                          signature_size,
                          signature_length);
}

// Opaque wrapper
psa_status_t sli_se_opaque_sign_hash(const psa_key_attributes_t *attributes,
                                     const uint8_t *key_buffer,
                                     size_t key_buffer_size,
                                     psa_algorithm_t alg,
                                     const uint8_t *hash,
                                     size_t hash_length,
                                     uint8_t *signature,
                                     size_t signature_size,
                                     size_t *signature_length)
{
  return sli_se_sign_hash(attributes,
                          key_buffer,
                          key_buffer_size,
                          alg,
                          hash,
                          hash_length,
                          signature,
                          signature_size,
                          signature_length);
}

/**
 * \brief Verify the signature a hash or short message using a public key.
 *
 * Note that to perform a hash-and-sign signature algorithm, you must
 * first calculate the hash by calling psa_hash_setup(), psa_hash_update()
 * and psa_hash_finish(). Then pass the resulting hash as the \p hash
 * parameter to this function. You can use #PSA_ALG_SIGN_GET_HASH(\p alg)
 * to determine the hash algorithm to use.
 *
 * \param handle            Handle to the key to use for the operation.
 *                          It must be a public key or an asymmetric key pair.
 * \param alg               A signature algorithm that is compatible with
 *                          the type of \p handle.
 * \param[in] hash          The hash or message whose signature is to be
 *                          verified.
 * \param hash_length       Size of the \p hash buffer in bytes.
 * \param[in] signature     Buffer containing the signature to verify.
 * \param signature_length  Size of the \p signature buffer in bytes.
 *
 * \retval #PSA_SUCCESS
 *         The signature is valid.
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 * \retval #PSA_ERROR_INVALID_SIGNATURE
 *         The calculation was perfomed successfully, but the passed
 *         signature is not a valid signature.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
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
psa_status_t sli_se_verify_hash(const psa_key_attributes_t *attributes,
                                const uint8_t *key_buffer,
                                size_t key_buffer_size,
                                psa_algorithm_t alg,
                                const uint8_t *hash,
                                size_t hash_length,
                                const uint8_t *signature,
                                size_t signature_length)
{
  // Check the requested algorithm is ECDSA with randomized k
  if (!PSA_ALG_IS_RANDOMIZED_ECDSA(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Argument check
  if (hash == NULL
      || hash_length == 0
      || signature == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Ephemeral contexts
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_se_key_descriptor_t key_desc = { 0 };

  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Verify and set key attributes
  if (signature_length
      != PSA_ECDSA_SIGNATURE_SIZE(psa_get_key_bits(attributes))) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }
  psa_status = check_curve_availability(attributes);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  uint8_t temp_key_buf[SLI_SE_MAX_PADDED_PUBLIC_KEY_SIZE] = { 0 };
  psa_key_type_t keytype = psa_get_key_type(attributes);
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  // P-521 (or any curve size that's not word-multiple) requires alignment on word
  // boundaries, instead of byte boundaries such as PSA Crypto defines as input here.
  uint8_t temp_signature_buffer[SLI_SE_MAX_PADDED_SIGNATURE_SIZE] = { 0 };
  size_t key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  size_t offset = sli_se_get_padding(key_size);
  if (offset > 0) {
    psa_key_location_t location =
      PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

    // Only pad transparent keys.
    if (location == PSA_KEY_LOCATION_LOCAL_STORAGE) {
      if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(keytype)) {
        if (offset + key_size > sizeof(temp_key_buf)) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }
        sli_se_pad_big_endian(temp_key_buf,
                              key_desc.storage.location.buffer.pointer,
                              key_size);
      } else if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(keytype)) {
        if ((2 * offset) + (2 * key_size) > sizeof(temp_key_buf)) {
          return PSA_ERROR_INVALID_ARGUMENT;
        }
        sli_se_pad_curve_point(temp_key_buf,
                               key_desc.storage.location.buffer.pointer,
                               key_size);
      } else {
        return PSA_ERROR_CORRUPTION_DETECTED;
      }
      key_desc.storage.location.buffer.pointer = temp_key_buf;
      key_desc.storage.location.buffer.size = sizeof(temp_key_buf);
    }

    // Always pad signature
    if ((2 * offset) + (2 * key_size) > sizeof(temp_signature_buffer)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
    sli_se_pad_curve_point(temp_signature_buffer, signature, key_size);

    signature = temp_signature_buffer;
    signature_length = signature_length + 2 * offset;
  }
#endif

  // SE manager only accepts public keys for signature verification,
  // so we must generate a public key if we are passed a private one
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(keytype)) {
    sl_se_key_descriptor_t pubkey_desc = key_desc;
    // Unset private key flag and set public
    pubkey_desc.flags &= ~SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PRIVATE_KEY;
    pubkey_desc.flags &= ~SL_SE_KEY_FLAG_IS_RESTRICTED;
    pubkey_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
    sli_se_key_descriptor_set_plaintext(&pubkey_desc, temp_key_buf, sizeof(temp_key_buf));
    // Same input output region
    status = sl_se_init_command_context(&cmd_ctx);
    if (status != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    status = sl_se_export_public_key(&cmd_ctx, &key_desc, &pubkey_desc);
    if (sl_se_deinit_command_context(&cmd_ctx) != SL_STATUS_OK) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    if (status) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
    // Set the key desc to the public key, and go on
    key_desc = pubkey_desc;
  }

  status = sl_se_init_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Run signature verification
  status = sl_se_ecc_verify(&cmd_ctx,
                            &key_desc,
                            SL_SE_HASH_NONE,
                            true,
                            hash,
                            hash_length,
                            signature,
                            signature_length);

  if (status == SL_STATUS_OK) {
    psa_status = PSA_SUCCESS;
  } else if (status == SL_STATUS_INVALID_SIGNATURE) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
  } else if (status == SL_STATUS_FAIL) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
  } else {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
  }

  // Cleanup
  status = sl_se_deinit_command_context(&cmd_ctx);
  if (status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return psa_status;
}

// Transparent wrapper
psa_status_t
sli_se_transparent_verify_hash(const psa_key_attributes_t *attributes,
                               const uint8_t *key_buffer,
                               size_t key_buffer_size,
                               psa_algorithm_t alg,
                               const uint8_t *hash,
                               size_t hash_length,
                               const uint8_t *signature,
                               size_t signature_length)
{
  return sli_se_verify_hash(attributes,
                            key_buffer,
                            key_buffer_size,
                            alg,
                            hash,
                            hash_length,
                            signature,
                            signature_length);
}

// Opaque wrapper
psa_status_t sli_se_opaque_verify_hash(const psa_key_attributes_t *attributes,
                                       const uint8_t *key_buffer,
                                       size_t key_buffer_size,
                                       psa_algorithm_t alg,
                                       const uint8_t *hash,
                                       size_t hash_length,
                                       const uint8_t *signature,
                                       size_t signature_length)
{
  return sli_se_verify_hash(attributes,
                            key_buffer,
                            key_buffer_size,
                            alg,
                            hash,
                            hash_length,
                            signature,
                            signature_length);
}

#endif // defined(SEMAILBOX_PRESENT)
