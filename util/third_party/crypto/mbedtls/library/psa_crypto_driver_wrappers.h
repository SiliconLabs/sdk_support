/*
 *  Function signatures for functionality that can be provided by
 *  cryptographic accelerators.
 *  Warning: This file will be auto-generated in the future.
 */
/*  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef PSA_CRYPTO_DRIVER_WRAPPERS_H
#define PSA_CRYPTO_DRIVER_WRAPPERS_H

#include "psa/crypto.h"
#include "psa/crypto_driver_common.h"

/*
 * Init function
 */
psa_status_t psa_driver_wrapper_init( void );

/*
 * Key generation functions
 */
psa_status_t psa_driver_wrapper_generate_key(
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *slot );

/*
 * Key management functions
 */
psa_status_t psa_driver_wrapper_allocate_key(
    const psa_key_attributes_t *attributes );

psa_status_t psa_driver_wrapper_copy_key(
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *source_slot,
    psa_key_slot_t *target_slot );

psa_status_t psa_driver_wrapper_import_key(
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *slot,
    const uint8_t *key_buffer,
    size_t key_buffer_size );

psa_status_t psa_driver_wrapper_export_key(
    const psa_key_slot_t *slot,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length );

psa_status_t psa_driver_wrapper_export_public_key(
    const psa_key_slot_t *slot,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length );

psa_status_t psa_driver_wrapper_destroy_key(
    psa_key_slot_t *slot );

psa_status_t psa_driver_wrapper_validate_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    size_t *bits );

/*
 * Key derivation functions
 */
psa_status_t psa_driver_wrapper_key_derivation_setup(
    psa_operation_driver_context_t *operation,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_key_derivation_input_bytes(
    psa_operation_driver_context_t *operation,
    psa_algorithm_t alg,
    const uint8_t *data,
    size_t data_length );

psa_status_t psa_driver_wrapper_key_derivation_input_key(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_key_derivation_output_bytes(
    psa_operation_driver_context_t *operation,
    uint8_t *output,
    size_t output_length );

psa_status_t psa_driver_wrapper_key_derivation_output_key(
    psa_operation_driver_context_t *operation,
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *slot );

psa_status_t psa_driver_wrapper_opaque_key_derivation_oneshot(
    psa_algorithm_t alg,
    psa_key_slot_t *secret_key_slot,
    psa_key_derivation_input_buffer_t *input_array,
    size_t input_count,
    const psa_key_attributes_t *output_key_attributes,
    psa_key_slot_t *output_key_slot);

psa_status_t psa_driver_wrapper_key_derivation_set_capacity(
    psa_operation_driver_context_t *operation,
    size_t capacity );

psa_status_t psa_driver_wrapper_key_derivation_abort(
    psa_operation_driver_context_t *operation );

/*
 * Key agreement functions
 */
psa_status_t psa_driver_wrapper_key_agreement(
    psa_algorithm_t alg,
    psa_key_slot_t *private_key,
    const uint8_t *peer_key,
    size_t peer_key_length,
    uint8_t *shared_secret,
    size_t shared_secret_size,
    size_t *shared_secret_length );

/*
 * Hash functions
 */
psa_status_t psa_driver_wrapper_hash_setup(
    psa_operation_driver_context_t *operation,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_hash_clone(
    const psa_operation_driver_context_t *source_operation,
    psa_operation_driver_context_t *target_operation );

psa_status_t psa_driver_wrapper_hash_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length );

psa_status_t psa_driver_wrapper_hash_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *hash,
    size_t hash_size,
    size_t *hash_length );

psa_status_t psa_driver_wrapper_hash_abort(
    psa_operation_driver_context_t *operation );

/*
 * Signature functions
 */
psa_status_t psa_driver_wrapper_sign_hash(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *hash,
    size_t hash_length,
    uint8_t *signature,
    size_t signature_size,
    size_t *signature_length );

psa_status_t psa_driver_wrapper_verify_hash(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *hash,
    size_t hash_length,
    const uint8_t *signature,
    size_t signature_length );

/*
 * Asymmetric functions
 */
psa_status_t psa_driver_wrapper_asymmetric_encrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *salt,
    size_t salt_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_asymmetric_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *salt,
    size_t salt_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

/*
 * AEAD functions
 */
psa_status_t psa_driver_wrapper_aead_encrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *nonce,
    size_t nonce_length,
    const uint8_t *additional_data,
    size_t additional_data_length,
    const uint8_t *plaintext,
    size_t plaintext_length,
    uint8_t *ciphertext,
    size_t ciphertext_size,
    size_t *ciphertext_length );

psa_status_t psa_driver_wrapper_aead_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *nonce,
    size_t nonce_length,
    const uint8_t *additional_data,
    size_t additional_data_length,
    const uint8_t *ciphertext,
    size_t ciphertext_length,
    uint8_t *plaintext,
    size_t plaintext_size,
    size_t *plaintext_length );

/*
 * MAC functions
 */
psa_status_t psa_driver_wrapper_mac_sign_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_mac_verify_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_mac_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length );

psa_status_t psa_driver_wrapper_mac_sign_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length );

psa_status_t psa_driver_wrapper_mac_abort(
    psa_operation_driver_context_t *operation );

/*
 * Cipher functions
 */
psa_status_t psa_driver_wrapper_cipher_encrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_encrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_cipher_decrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg );

psa_status_t psa_driver_wrapper_cipher_generate_iv(
    psa_operation_driver_context_t *operation,
    uint8_t *iv,
    size_t iv_size,
    size_t *iv_length );

psa_status_t psa_driver_wrapper_cipher_set_iv(
    psa_operation_driver_context_t *operation,
    const uint8_t *iv,
    size_t iv_length );

psa_status_t psa_driver_wrapper_cipher_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length );

psa_status_t psa_driver_wrapper_cipher_abort(
    psa_operation_driver_context_t *operation );

#endif /* PSA_CRYPTO_DRIVER_WRAPPERS_H */

/* End of automatically generated file. */
