/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Signature functions.
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
#include "sx_ecdsa_alg.h"
#include "sx_ecc_keygen_alg.h"
#include "sx_trng.h"
#include "sx_errors.h"
#include "cryptolib_types.h"
#include <string.h>

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
psa_status_t sli_cryptoacc_transparent_sign_hash(const psa_key_attributes_t *attributes,
                                                 const uint8_t *key_buffer,
                                                 size_t key_buffer_size,
                                                 psa_algorithm_t alg,
                                                 const uint8_t *hash,
                                                 size_t hash_length,
                                                 uint8_t *signature,
                                                 size_t signature_size,
                                                 size_t *signature_length)
{
  // Argument check.
  if (key_buffer_size == 0
      || hash == NULL
      || hash_length == 0
      || signature == NULL
      || signature_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check the requested algorithm is ECDSA with randomized k.
  if (!PSA_ALG_IS_RANDOMIZED_ECDSA(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sx_ecc_curve_t *curve = NULL;
  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
    if (curve_type == PSA_ECC_CURVE_SECP_R1) {
      switch (key_bits) {
        case 192:
          curve = (sx_ecc_curve_t*)&sx_ecc_curve_p192;
          break;
        case 224:
          curve = (sx_ecc_curve_t*)&sx_ecc_curve_p224;
          break;
        case 256:
          curve = (sx_ecc_curve_t*)&sx_ecc_curve_p256;
          break;
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }

      // Check sufficient outout buffer size.
      if (signature_size < PSA_ECDSA_SIGNATURE_SIZE(key_bits)) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }

      block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      block_t data_in = block_t_convert(hash, hash_length);
      block_t data_out = block_t_convert(signature, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

      psa_status_t status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      struct sx_rng trng = { NULL, sx_trng_fill_blk };
      uint32_t sx_ret = ecdsa_generate_signature_digest(curve,
                                                        data_in,
                                                        priv,
                                                        data_out,
                                                        trng);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
    } else if (curve_type == PSA_ECC_CURVE_SECP_K1) {
      // TODO: introduce custom domains to enable secpxxxk1.
      return PSA_ERROR_NOT_SUPPORTED;
    } else {
      return PSA_ERROR_NOT_SUPPORTED;
    }
  } else {
    // Not able to sign using non-ECC keys, or using public keys.
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  *signature_length = PSA_ECDSA_SIGNATURE_SIZE(key_bits);

  return PSA_SUCCESS;
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
psa_status_t sli_cryptoacc_transparent_verify_hash(const psa_key_attributes_t *attributes,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   psa_algorithm_t alg,
                                                   const uint8_t *hash,
                                                   size_t hash_length,
                                                   const uint8_t *signature,
                                                   size_t signature_length)
{
  // Argument check.
  if (key_buffer_size == 0
      || hash == NULL
      || hash_length == 0
      || signature == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check the requested algorithm is ECDSA with randomized k.
  if (!PSA_ALG_IS_RANDOMIZED_ECDSA(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  uint32_t curve_flags = 0;
  sx_ecc_curve_t *curve_ptr = NULL;
  if (curve_type == PSA_ECC_CURVE_SECP_R1) {
    switch (key_bits) {
      case 192:
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p192;
        curve_flags = sx_ecc_curve_p192.pk_flags;
        break;
      case 224:
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p224;
        curve_flags = sx_ecc_curve_p224.pk_flags;
        break;
      case 256:
        curve_ptr = (sx_ecc_curve_t*)&sx_ecc_curve_p256;
        curve_flags = sx_ecc_curve_p256.pk_flags;
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }

    if (signature_length != PSA_ECDSA_SIGNATURE_SIZE(key_bits)) {
      return PSA_ERROR_INVALID_SIGNATURE;
    }

    // Export public key if necessary.
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    uint32_t sx_ret = CRYPTOLIB_CRYPTO_ERR;
    block_t pub = NULL_blk;
    uint8_t pub_buf[64] = { 0 };
    if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) {
      block_t curve = block_t_convert(curve_ptr->params.addr, 6 * PSA_BITS_TO_BYTES(key_bits));
      block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
      pub = block_t_convert(pub_buf, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

      // Perform point multiplication in order to get public key.
      status = cryptoacc_management_acquire();
      if (status != PSA_SUCCESS) {
        return status;
      }
      sx_ret = ecc_generate_public_key(curve, pub, priv, PSA_BITS_TO_BYTES(key_bits), curve_flags);
      status = cryptoacc_management_release();
      if (sx_ret != CRYPTOLIB_SUCCESS
          || status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }
    } else {
      pub = block_t_convert(key_buffer + 1, PSA_ECDSA_SIGNATURE_SIZE(key_bits));
    }

    block_t digest = block_t_convert(hash, hash_length);
    block_t signature_internal = block_t_convert(signature, PSA_ECDSA_SIGNATURE_SIZE(key_bits));

    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    sx_ret = ecdsa_verify_signature_digest(curve_ptr,
                                           digest,
                                           pub,
                                           signature_internal);
    status = cryptoacc_management_release();
    if (sx_ret == CRYPTOLIB_INVALID_SIGN_ERR) {
      return PSA_ERROR_INVALID_SIGNATURE;
    }
    if (sx_ret != CRYPTOLIB_SUCCESS
        || status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }
  } else if (curve_type == PSA_ECC_CURVE_SECP_K1) {
    // TODO: introduce custom domains to enable secpxxxk1.
    return PSA_ERROR_NOT_SUPPORTED;
  } else {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

#endif // defined(CRYPTOACC_PRESENT)
