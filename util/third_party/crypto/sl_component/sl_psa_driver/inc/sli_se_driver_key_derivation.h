/***************************************************************************//**
 * @file
 * @brief SE Driver for Silicon Labs devices with an embedded SE, for use with
 *        PSA Crypto and Mbed TLS
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

#ifndef SLI_SE_DRIVER_KEY_DERIVATION
#define SLI_SE_DRIVER_KEY_DERIVATION

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

/***************************************************************************//**
 * \addtogroup sl_psa_drivers
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_psa_drivers_se
 * \{
 ******************************************************************************/

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "sl_se_manager.h"
#include "sl_se_manager_defines.h"
// Replace inclusion of crypto_driver_common.h with the new psa driver interface
// header file when it becomes available.
#include "psa/crypto_driver_common.h"
#include "psa/crypto_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Structs and typedefs

// Upper limit to not allocate too much memory
#define SLI_SE_KEY_DERIVATION_MAX_INPUT_SIZE  128

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  #define SLI_SE_MAX_PADDED_ECP_PRIVATE_KEY_SIZE \
  (PSA_BITS_TO_BYTES(521)                        \
   + sli_se_get_padding(PSA_BITS_TO_BYTES(521)))
#else
  #define SLI_SE_MAX_PADDED_ECP_PRIVATE_KEY_SIZE \
  (PSA_BITS_TO_BYTES(256)                        \
   + sli_se_get_padding(PSA_BITS_TO_BYTES(256)))
#endif

#define SLI_SE_MAX_PADDED_ECP_PUBLIC_KEY_SIZE \
  (SLI_SE_MAX_PADDED_ECP_PRIVATE_KEY_SIZE * 2)

typedef struct {
  size_t capacity;
  psa_algorithm_t derivation_algo;
  sl_se_hash_type_t hash_algo;
  sl_se_key_descriptor_t key_in;
  uint8_t *key_buffer;
  size_t key_buffer_size;
  uint8_t *salt;
  size_t salt_len;
  uint8_t *info;
  size_t info_len;
} sli_se_driver_key_derivation_operation_t;

typedef sli_se_driver_key_derivation_operation_t
  sli_se_transparent_key_derivation_operation_t;
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
typedef sli_se_driver_key_derivation_operation_t
  sli_se_opaque_key_derivation_operation_t;
#endif

// -----------------------------------------------------------------------------
// Function declarations

psa_status_t sli_se_driver_key_derivation_setup(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_algorithm_t alg);

psa_status_t sli_se_driver_key_derivation_set_capacity(
  sli_se_driver_key_derivation_operation_t *operation,
  size_t capacity);

psa_status_t sli_se_driver_key_derivation_input_bytes(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_key_derivation_step_t step,
  const uint8_t *data,
  size_t data_length);

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) \
  || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
psa_status_t sli_se_driver_key_derivation_input_key(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_key_derivation_step_t step,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size);
#endif

psa_status_t sli_se_driver_key_derivation_output_key(
  const psa_key_attributes_t *attributes,
  sli_se_driver_key_derivation_operation_t *operation,
  uint8_t *key_buffer,
  size_t key_buffer_size,
  size_t *key_buffer_length);

psa_status_t sli_se_driver_key_derivation_output_bytes(
  sli_se_driver_key_derivation_operation_t *operation,
  uint8_t *output,
  size_t output_length);

psa_status_t sli_se_driver_key_derivation_abort(
  sli_se_driver_key_derivation_operation_t *operation);

psa_status_t sli_se_driver_key_agreement(
  psa_algorithm_t alg,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  const uint8_t *peer_key,
  size_t peer_key_length,
  uint8_t *output,
  size_t output_size,
  size_t *output_length);

#ifdef __cplusplus
}
#endif

#endif // SEMAILBOX_PRESENT

/** \} (end addtogroup sl_psa_drivers_se) */
/** \} (end addtogroup sl_psa_drivers) */

/// @endcond

#endif // SLI_SE_DRIVER_KEY_DERIVATION
