/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Key Management functions.
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
#include "ba414ep_config.h"
#include "sx_ecc_keygen_alg.h"
#include "sx_ecc_curves.h"
#include "sx_primitives.h"
#include "sx_memcmp.h"
#include "sx_trng.h"
#include "sx_errors.h"
#include "cryptolib_types.h"
#include <string.h>

psa_status_t sli_cryptoacc_transparent_generate_key(const psa_key_attributes_t *attributes,
                                                    uint8_t *key_buffer,
                                                    size_t key_buffer_size,
                                                    size_t *key_length)
{
  // Argument check.
  if (attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  // Currently only supports secp{192, 224, 256}r1 curves. This check will also
  // capture all non-ECC key types, as PSA_KEY_TYPE_GET_CURVE will return
  // zero in those cases.
  if (curve_type != PSA_ECC_CURVE_SECP_R1) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Check sufficient buffer size.
  if ((PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)
       && key_buffer_size < PSA_BITS_TO_BYTES(key_bits))
      || (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)
          && key_buffer_size < PSA_BITS_TO_BYTES(key_bits) * 2 + 1)) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Always generate private key.
  block_t n = NULL_blk;
  switch (key_bits) {
    case 192:
      // The order n is stored as the second element in the curve-parameter tuple
      // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
      // dependent on the length of the corresponding key.
      n = block_t_convert(sx_ecc_curve_p192.params.addr + (1 * sx_ecc_curve_p192.bytesize),
                          sx_ecc_curve_p192.bytesize);
      break;
    case 224:
      // The order n is stored as the second element in the curve-parameter tuple
      // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
      // dependent on the length of the corresponding key.
      n = block_t_convert(sx_ecc_curve_p224.params.addr + (1 * sx_ecc_curve_p224.bytesize),
                          sx_ecc_curve_p224.bytesize);
      break;
    case 256:
      // The order n is stored as the second element in the curve-parameter tuple
      // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
      // dependent on the length of the corresponding key.
      n = block_t_convert(sx_ecc_curve_p256.params.addr + (1 * sx_ecc_curve_p256.bytesize),
                          sx_ecc_curve_p256.bytesize);
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));

  psa_status_t status = cryptoacc_trng_initialize();
  if (status != PSA_SUCCESS) {
    return status;
  }

  // Get random number < n -> private key.
  status = cryptoacc_management_acquire();
  if (status != PSA_SUCCESS) {
    return status;
  }

  struct sx_rng trng = { NULL, sx_trng_fill_blk };
  uint32_t sx_ret = ecc_generate_private_key(n, priv, trng);
  status = cryptoacc_management_release();
  if (sx_ret != CRYPTOLIB_SUCCESS
      || status != PSA_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // If public key is requested, get it by performing point multiplication of the private key.
  if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
    block_t *domain_ptr = NULL;
    uint32_t curve_flags = 0;
    switch (key_bits) {
      case 192:
        curve_flags = sx_ecc_curve_p192.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p192.params;
        break;
      case 224:
        curve_flags = sx_ecc_curve_p224.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p224.params;
        break;
      case 256:
        curve_flags = sx_ecc_curve_p256.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p256.params;
        break;
    }

    block_t pub = block_t_convert(key_buffer + 1, PSA_BITS_TO_BYTES(key_bits) * 2);

    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    sx_ret = ecc_generate_public_key(*domain_ptr,
                                     pub,
                                     priv,
                                     PSA_BITS_TO_BYTES(key_bits),
                                     curve_flags);
    status = cryptoacc_management_release();
    if (sx_ret != CRYPTOLIB_SUCCESS
        || status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    key_buffer[0] = 0x04;
    *key_length = PSA_BITS_TO_BYTES(key_bits) * 2 + 1;
  } else {
    *key_length = PSA_BITS_TO_BYTES(key_bits);
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_export_public_key(const psa_key_attributes_t *attributes,
                                                         const uint8_t *key_buffer,
                                                         size_t key_buffer_size,
                                                         uint8_t *data,
                                                         size_t data_size,
                                                         size_t *data_length)
{
  // Argument check.
  if (key_buffer == NULL
      || key_buffer_size == 0
      || data == NULL
      || data_size == 0
      || data_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);
  size_t key_bits = psa_get_key_bits(attributes);

  if (PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(key_type)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (curve_type == PSA_ECC_CURVE_SECP_R1) {
    // Check sufficient output buffer size.
    if (data_size < PSA_BITS_TO_BYTES(key_bits) * 2 + 1) {
      return PSA_ERROR_BUFFER_TOO_SMALL;
    }

    block_t *domain_ptr = NULL;
    uint32_t curve_flags = 0;
    switch (key_bits) {
      case 192:
        curve_flags = sx_ecc_curve_p192.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p192.params;
        break;
      case 224:
        curve_flags = sx_ecc_curve_p224.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p224.params;
        break;
      case 256:
        curve_flags = sx_ecc_curve_p256.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p256.params;
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }

    block_t priv = block_t_convert(key_buffer, PSA_BITS_TO_BYTES(key_bits));
    block_t pub = block_t_convert(data + 1, PSA_BITS_TO_BYTES(key_bits) * 2);

    psa_status_t status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    uint32_t sx_ret = ecc_generate_public_key(*domain_ptr,
                                              pub,
                                              priv,
                                              PSA_BITS_TO_BYTES(key_bits),
                                              curve_flags);
    status = cryptoacc_management_release();
    if (sx_ret != CRYPTOLIB_SUCCESS
        || status != PSA_SUCCESS) {
      return PSA_ERROR_HARDWARE_FAILURE;
    }

    data[0] = 0x04;
    *data_length = PSA_BITS_TO_BYTES(key_bits) * 2 + 1;
  } else {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_cryptoacc_transparent_validate_key(const psa_key_attributes_t *attributes,
                                                    const uint8_t *data,
                                                    size_t data_length,
                                                    size_t *bits)
{
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

  // Argument check.
  if (attributes == NULL
      || data == NULL
      || data_length == 0
      || bits == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);

  // Transparent driver is not involved in validation of symmetric keys.
  if (!PSA_KEY_TYPE_IS_ASYMMETRIC(key_type)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Currently only supports secp{192, 224, 256}r1 curves.
  if (curve_type != PSA_ECC_CURVE_SECP_R1) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  if (PSA_KEY_TYPE_IS_ECC_KEY_PAIR(key_type)) { // Private key.
    // Determine key bit size.
    *bits = data_length * 8;

    uint8_t *modulo_ptr = NULL;
    switch (*bits) {
      case 192:
        // The order n is stored as the second element in the curve-parameter tuple
        // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
        // dependent on the length of the corresponding key.
        modulo_ptr = sx_ecc_curve_p192.params.addr + (1 * sx_ecc_curve_p192.bytesize);
        break;
      case 224:
        // The order n is stored as the second element in the curve-parameter tuple
        // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
        // dependent on the length of the corresponding key.
        modulo_ptr = sx_ecc_curve_p224.params.addr + (1 * sx_ecc_curve_p224.bytesize);
        break;
      case 256:
        // The order n is stored as the second element in the curve-parameter tuple
        // consisting of (q, n, Gx, Gy, a, b). The length of the parameters is
        // dependent on the length of the corresponding key.
        modulo_ptr = sx_ecc_curve_p256.params.addr + (1 * sx_ecc_curve_p256.bytesize);
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }

    uint32_t non_zero_accumulator = 0;
    uint8_t key_is_valid = 0;
    if ((((uint32_t)data) & 0x3) == 0) { // Word-aligned.
      // Compare private key to maximum allowed key and check that it is non-zero.
      for (size_t i = 0; i < data_length / 4; ++i) {
        non_zero_accumulator |= *(uint32_t*)&data[i * 4];

        if (*(uint32_t*)&data[i * 4] < *(uint32_t*)&modulo_ptr[i * 4]) {
          // Lesser than n - 1.
          key_is_valid = 1;
        } else if (*(uint32_t*)&data[i * 4] > *(uint32_t*)&modulo_ptr[i * 4]
                   && key_is_valid != 1) {
          return PSA_ERROR_INVALID_ARGUMENT;
        } else if (i == data_length / 4 - 1
                   && key_is_valid != 1) {
          // Equal to modulus.
          return PSA_ERROR_INVALID_ARGUMENT;
        }
      }
    } else { // Not word-aligned.
      // Compare private key to maximum allowed key and check that it is non-zero.
      for (size_t i = 0; i < data_length; ++i) {
        non_zero_accumulator |= data[i];

        if (data[i] < modulo_ptr[i]) {
          // Lesser than n - 1.
          key_is_valid = 1;
        } else if (data[i] > modulo_ptr[i]
                   && key_is_valid != 1) {
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
      status = PSA_SUCCESS;
    }
  } else { // Public key.
    block_t *domain_ptr = NULL;
    uint32_t curve_flags = 0;

    // Check that uncompressed representation is given.
    if (data[0] != 0x04) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    // Determine key bit size.
    *bits = (data_length - 1) * 8 / 2;

    switch (*bits) {
      case 192:
        curve_flags = sx_ecc_curve_p192.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p192.params;
        break;
      case 224:
        curve_flags = sx_ecc_curve_p224.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p224.params;
        break;
      case 256:
        curve_flags = sx_ecc_curve_p256.pk_flags;
        domain_ptr = (block_t*)&sx_ecc_curve_p256.params;
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }

    block_t point = block_t_convert(data + 1, PSA_BITS_TO_BYTES(*bits) * 2);

    status = cryptoacc_management_acquire();
    if (status != PSA_SUCCESS) {
      return status;
    }
    uint32_t sx_ret = ecc_is_point_on_curve(*domain_ptr,
                                            point,
                                            PSA_BITS_TO_BYTES(*bits),
                                            curve_flags);
    status = cryptoacc_management_release();
    if (status != PSA_SUCCESS) {
      return status;
    }
    if (sx_ret != CRYPTOLIB_SUCCESS) {
      return PSA_ERROR_INVALID_ARGUMENT;
    } else {
      status = PSA_SUCCESS;
    }
  }

  return status;
}

#endif // defined(CRYPTOACC_PRESENT)
