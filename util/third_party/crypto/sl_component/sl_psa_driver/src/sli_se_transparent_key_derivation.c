/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Transparent Driver Key derivation functions.
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

#include "sli_se_driver_key_derivation.h"

#ifdef __cplusplus
extern "C" {
#endif

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

psa_status_t sli_se_transparent_key_derivation_setup(
  sli_se_transparent_key_derivation_operation_t *operation,
  psa_algorithm_t alg)
{
  return sli_se_driver_key_derivation_setup(operation, alg);
}

psa_status_t sli_se_transparent_key_derivation_set_capacity(
  sli_se_transparent_key_derivation_operation_t *operation,
  size_t capacity)
{
  return sli_se_driver_key_derivation_set_capacity(operation, capacity);
}

psa_status_t sli_se_transparent_key_derivation_input_bytes(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_key_derivation_step_t step,
  const uint8_t *data,
  size_t data_length)
{
  return sli_se_driver_key_derivation_input_bytes(operation,
                                                  step,
                                                  data,
                                                  data_length);
}

psa_status_t sli_se_transparent_key_derivation_output_key(
  const psa_key_attributes_t *attributes,
  sli_se_transparent_key_derivation_operation_t *operation,
  uint8_t *key_buffer,
  size_t key_buffer_size,
  size_t *key_buffer_length)
{
  return sli_se_driver_key_derivation_output_key(attributes,
                                                 operation,
                                                 key_buffer,
                                                 key_buffer_size,
                                                 key_buffer_length);
}

psa_status_t sli_se_transparent_key_derivation_output_bytes(
  sli_se_transparent_key_derivation_operation_t *operation,
  uint8_t *output,
  size_t output_length)
{
  return sli_se_driver_key_derivation_output_bytes(operation,
                                                   output,
                                                   output_length);
}

psa_status_t sli_se_transparent_key_derivation_abort(
  sli_se_transparent_key_derivation_operation_t *operation)
{
  return sli_se_driver_key_derivation_abort(operation);
}

#endif // Vault

psa_status_t sli_se_transparent_key_agreement(
  psa_algorithm_t alg,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size,
  const uint8_t *peer_key,
  size_t peer_key_length,
  uint8_t *output,
  size_t output_size,
  size_t *output_length)
{
  return sli_se_driver_key_agreement(alg,
                                     attributes,
                                     key_buffer,
                                     key_buffer_size,
                                     peer_key,
                                     peer_key_length,
                                     output,
                                     output_size,
                                     output_length);
}

#ifdef __cplusplus
}
#endif
#endif // SEMAILBOX_PRESENT
