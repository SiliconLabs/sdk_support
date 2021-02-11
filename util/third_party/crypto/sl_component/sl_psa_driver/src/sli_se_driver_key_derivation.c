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
#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "psa/crypto.h"
#include "sli_se_transparent_types.h"
#include "sli_se_transparent_functions.h"
#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"

#include "sli_se_driver_key_management.h"
#include "sli_se_driver_key_derivation.h"
#include "sl_se_manager_key_derivation.h"
#include "mbedtls/platform.h" // calloc

#include "sl_se_manager.h"
#include "sli_se_manager_internal.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Statics

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

/**
 * @brief
 *   Get the digest size of the given hash algorithm
 *
 * @param hash_algo
 *   The hash algorithm to get digest size for
 * @returns
 *   The digest size in bytes
 */
static size_t get_digest_size(sl_se_hash_type_t hash_algo)
{
  switch (hash_algo) {
    case SL_SE_HASH_SHA1:
      return 20;
    case SL_SE_HASH_SHA224:
      return 28;
    case SL_SE_HASH_SHA256:
      return 32;
    case SL_SE_HASH_SHA384:
      return 48;
    case SL_SE_HASH_SHA512:
      return 64;
    default:
      return 0;
  }
}

/**
 * @brief
 *   Perform a HKDF operation and store output in output key desc
 *
 * @param operation
 *   Operation struct containing key derivation input
 * @param output_key_desc
 *   Key descriptor containing output info
 * @returns
 *   PSA_SUCCESS on success
 */
static psa_status_t derive_key_hkdf(
  sli_se_driver_key_derivation_operation_t *operation,
  sl_se_key_descriptor_t * output_key_desc)
{
  if (operation == NULL
      || output_key_desc == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Implementations must reject generating zero-length output
  if (output_key_desc->size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Make the input key desc ready for running the operation. Reset the pointer,
  // since struct may have moved since it was set
  switch (operation->key_in.storage.method) {
    case SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT: // Fallthrough
    case SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED:
      operation->key_in.storage.location.buffer.pointer = operation->key_buffer;
      break;
    case SL_SE_KEY_STORAGE_INTERNAL_VOLATILE:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  sl_status_t sl_status = sl_se_validate_key(&operation->key_in);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_BAD_STATE;
  }

  // Check that number of requested bytes is not above capacity
  if (output_key_desc->size > operation->capacity) {
    operation->capacity = 0;
    return PSA_ERROR_INSUFFICIENT_DATA;
  }

  // Check that we don't request more than 255 times the hash digest size
  // Note: This was a requirement found in multiple software implementations
  // that I found on the web. I am guessing the algorithm is weakened after this
  // many output blocks, but I haven't found any clear reasoning for this.
  if (output_key_desc->size > 255 * get_digest_size(operation->hash_algo)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check location specific properties
  switch (output_key_desc->storage.method) {
    case SL_SE_KEY_STORAGE_EXTERNAL_PLAINTEXT:
      if (output_key_desc->size
          > output_key_desc->storage.location.buffer.size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }
      break;
    case SL_SE_KEY_STORAGE_EXTERNAL_WRAPPED:
      if (output_key_desc->size + SLI_SE_WRAPPED_KEY_OVERHEAD
          > output_key_desc->storage.location.buffer.size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }
      break;
    case SL_SE_KEY_STORAGE_INTERNAL_VOLATILE:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_BAD_STATE;
  }

  // Execute the SE command
  sl_se_command_context_t cmd_ctx = { 0 };
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  sl_status = sl_se_derive_key_hkdf(&cmd_ctx,
                                    &operation->key_in,
                                    operation->hash_algo,
                                    operation->salt,
                                    operation->salt_len,
                                    operation->info,
                                    operation->info_len,
                                    output_key_desc);
  psa_status_t psa_status = PSA_ERROR_INVALID_ARGUMENT;
  if (sl_status != SL_STATUS_OK) {
    if (sl_status == SL_STATUS_FAIL) {
      // This specific code maps to 'does not exist' for builtin keys
      psa_status = PSA_ERROR_DOES_NOT_EXIST;
    } else {
      psa_status = PSA_ERROR_HARDWARE_FAILURE;
    }
  } else {
    psa_status = PSA_SUCCESS;
    operation->capacity = 0; // Single-shot only
  }

  // Cleanup
  sl_status = sl_se_deinit_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }
  return psa_status;
}

// -----------------------------------------------------------------------------
// Driver functions

/** Set up a key derivation operation.
 *
 * A key derivation algorithm takes some inputs and uses them to generate
 * a byte stream in a deterministic way.
 * This byte stream can be used to produce keys and other
 * cryptographic material.
 *
 * To derive a key:
 * -# Start with an initialized object of type #psa_key_derivation_operation_t.
 * -# Call psa_key_derivation_setup() to select the algorithm.
 * -# Provide the inputs for the key derivation by calling
 *    psa_key_derivation_input_bytes() or psa_key_derivation_input_key()
 *    as appropriate. Which inputs are needed, in what order, and whether
 *    they may be keys and if so of what type depends on the algorithm.
 * -# Optionally set the operation's maximum capacity with
 *    psa_key_derivation_set_capacity(). You may do this before, in the middle
 *    of or after providing inputs. For some algorithms, this step is mandatory
 *    because the output depends on the maximum capacity.
 * -# To derive a key, call psa_key_derivation_output_key().
 *    To derive a byte string for a different purpose, call
 *    psa_key_derivation_output_bytes().
 *    Successive calls to these functions use successive output bytes
 *    calculated by the key derivation algorithm.
 * -# Clean up the key derivation operation object with
 *    psa_key_derivation_abort().
 *
 * If this function returns an error, the key derivation operation object is
 * not changed.
 *
 * If an error occurs at any step after a call to psa_key_derivation_setup(),
 * the operation will need to be reset by a call to psa_key_derivation_abort().
 *
 * Implementations must reject an attempt to derive a key of size 0.
 *
 * \param[in,out] operation       The key derivation operation object
 *                                to set up. It must
 *                                have been initialized but not set up yet.
 * \param alg                     The key derivation algorithm to compute
 *                                (\c PSA_ALG_XXX value such that
 *                                #PSA_ALG_IS_KEY_DERIVATION(\p alg) is true).
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \c alg is not a key derivation algorithm.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         \c alg is not supported or is not a key derivation algorithm.
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid (it must be inactive).
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_setup(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_algorithm_t alg)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (!PSA_ALG_IS_KEY_DERIVATION(alg)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Be sure to start out with a cleared context
  memset(operation, 0, sizeof(sli_se_driver_key_derivation_operation_t));

  // Find SE manager hash algorithm
  sl_se_hash_type_t hash_algo = SL_SE_HASH_SHA256;
  if (PSA_ALG_IS_HKDF(alg)) {
    switch (PSA_ALG_HKDF_GET_HASH(alg)) {
      case PSA_ALG_SHA_1:
        hash_algo = SL_SE_HASH_SHA1;
        break;
      case PSA_ALG_SHA_224:
        hash_algo = SL_SE_HASH_SHA224;
        break;
      case PSA_ALG_SHA_256:
        hash_algo = SL_SE_HASH_SHA256;
        break;
      case PSA_ALG_SHA_384:
        hash_algo = SL_SE_HASH_SHA384;
        break;
      case PSA_ALG_SHA_512:
        hash_algo = SL_SE_HASH_SHA512;
        break;
      default:
        return PSA_ERROR_NOT_SUPPORTED;
    }
  } else {
    // The TLS 1.2 KDFs are partially accellerated through fallback
    // implementation for transparent drivers.
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Set the properties now that we are sure it is a succeess
  operation->capacity = PSA_KEY_DERIVATION_UNLIMITED_CAPACITY;
  operation->derivation_algo = alg;
  operation->hash_algo = hash_algo;
  // Make sure the pointers are NULL'ed
  operation->key_buffer = NULL;
  operation->info = NULL;
  operation->salt = NULL;
  return PSA_SUCCESS;
}

/** Set the maximum capacity of a key derivation operation.
 *
 * The capacity of a key derivation operation is the maximum number of bytes
 * that the key derivation operation can return from this point onwards.
 *
 * \param[in,out] operation The key derivation operation object to modify.
 * \param capacity          The new capacity of the operation.
 *                          It must be less or equal to the operation's
 *                          current capacity.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \p capacity is larger than the operation's current capacity.
 *         In this case, the operation object remains valid and its capacity
 *         remains unchanged.
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid (it must be active).
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_set_capacity(
  sli_se_driver_key_derivation_operation_t *operation,
  size_t capacity)
{
  // This entry point is optional.
  // The overlaying psa operation struct also has a capacity field, but we can't
  // see that one from the driver. Therefore, we need our own capacity in order
  // to determine the number of key bytes to ask for.
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (!PSA_ALG_IS_HKDF(operation->derivation_algo)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  if (capacity > operation->capacity) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  operation->capacity = capacity;
  return PSA_SUCCESS;
}

/** Provide an input for key derivation or key agreement.
 *
 * Which inputs are required and in what order depends on the algorithm.
 * Refer to the documentation of each key derivation or key agreement
 * algorithm for information.
 *
 * This function passes direct inputs, which is usually correct for
 * non-secret inputs. To pass a secret input, which should be in a key
 * object, call psa_key_derivation_input_key() instead of this function.
 * Refer to the documentation of individual step types
 * (`PSA_KEY_DERIVATION_INPUT_xxx` values of type ::psa_key_derivation_step_t)
 * for more information.
 *
 * If this function returns an error status, the operation enters an error
 * state and must be aborted by calling psa_key_derivation_abort().
 *
 * \param[in,out] operation       The key derivation operation object to use.
 *                                It must have been set up with
 *                                psa_key_derivation_setup() and must not
 *                                have produced any output yet.
 * \param step                    Which step the input data is for.
 * \param[in] data                Input data to use.
 * \param data_length             Size of the \p data buffer in bytes.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \c step is not compatible with the operation's algorithm.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \c step does not allow direct inputs.
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid for this input \p step.
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_input_bytes(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_key_derivation_step_t step,
  const uint8_t *data,
  size_t data_length)
{
  if (operation == NULL
      || data == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (!PSA_ALG_IS_HKDF(operation->derivation_algo)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }
  if (data_length > SLI_SE_KEY_DERIVATION_MAX_INPUT_SIZE) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }

  uint8_t **data_storage_ptr = NULL;
  switch (step) {
    case PSA_KEY_DERIVATION_INPUT_SECRET:
      data_storage_ptr = &operation->key_buffer;
      operation->key_buffer_size = data_length;
      {
        // We must create a key descriptor representing the input
        sl_se_key_descriptor_t input_key_desc = {
          .flags = 0,
          .size = data_length,
          .type = SL_SE_KEY_TYPE_SYMMETRIC,
        };
        sli_se_key_descriptor_set_plaintext(&input_key_desc, data, data_length);
        operation->key_in = input_key_desc;
      }
      break;
    case PSA_KEY_DERIVATION_INPUT_INFO:
      data_storage_ptr = &operation->info;
      operation->info_len = data_length;
      break;
    case PSA_KEY_DERIVATION_INPUT_SALT:
      data_storage_ptr = &operation->salt;
      operation->salt_len = data_length;
      break;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (*data_storage_ptr != NULL) {
    // The field has already been populated
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Allocate memory now that we know the arguments are okay
  *data_storage_ptr = mbedtls_calloc(1, data_length);
  if (*data_storage_ptr == NULL) {
    // Allocation failed
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memcpy(*data_storage_ptr, data, data_length);

  return PSA_SUCCESS;
}

/** Provide an input for key derivation in the form of a key.
 *
 * Which inputs are required and in what order depends on the algorithm.
 * Refer to the documentation of each key derivation or key agreement
 * algorithm for information.
 *
 * This function obtains input from a key object, which is usually correct for
 * secret inputs or for non-secret personalization strings kept in the key
 * store. To pass a non-secret parameter which is not in the key store,
 * call psa_key_derivation_input_bytes() instead of this function.
 * Refer to the documentation of individual step types
 * (`PSA_KEY_DERIVATION_INPUT_xxx` values of type ::psa_key_derivation_step_t)
 * for more information.
 *
 * If this function returns an error status, the operation enters an error
 * state and must be aborted by calling psa_key_derivation_abort().
 *
 * \param[in,out] operation       The key derivation operation object to use.
 *                                It must have been set up with
 *                                psa_key_derivation_setup() and must not
 *                                have produced any output yet.
 * \param step                    Which step the input data is for.
 * \param handle                  Handle to the key. It must have an
 *                                appropriate type for \p step and must
 *                                allow the usage #PSA_KEY_USAGE_DERIVE.
 *
 * \retval #PSA_SUCCESS
 *         Success.
 * \retval #PSA_ERROR_INVALID_HANDLE
 * \retval #PSA_ERROR_NOT_PERMITTED
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \c step is not compatible with the operation's algorithm.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         \c step does not allow key inputs of the given type
 *         or does not allow key inputs at all.
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid for this input \p step.
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_input_key(
  sli_se_driver_key_derivation_operation_t *operation,
  psa_key_derivation_step_t step,
  const psa_key_attributes_t *attributes,
  const uint8_t *key_buffer,
  size_t key_buffer_size)
{
  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL
      || key_buffer_size == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (!PSA_ALG_IS_HKDF(operation->derivation_algo)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Only the "Secret" input step allows a key as input
  if (step != PSA_KEY_DERIVATION_INPUT_SECRET) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (operation->key_buffer != NULL) {
    // We already have a key
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  sl_se_key_descriptor_t input_key_desc = { 0 };
  psa_status_t psa_status = sli_se_key_desc_from_input(attributes,
                                                       key_buffer,
                                                       key_buffer_size,
                                                       &input_key_desc);

  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  size_t key_buffer_length = 0; // Actual used key buffer length
  psa_status = sli_se_get_key_buffer_length(attributes,
                                            &input_key_desc,
                                            &key_buffer_length);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  size_t offset = 0;
  switch (location) {
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      offset = offsetof(sli_se_opaque_wrapped_key_context_t, wrapped_buffer);
      if (key_buffer_length < offset
          || (key_buffer_length - offset)
          > input_key_desc.storage.location.buffer.size) {
        return PSA_ERROR_BUFFER_TOO_SMALL;
      }
      key_buffer_length -= offset;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Copy the buffer
  if (key_buffer_length
      > SLI_SE_KEY_DERIVATION_MAX_INPUT_SIZE + SLI_SE_WRAPPED_KEY_OVERHEAD) {
    // Key buffer is too large
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Allocate and copy as last step
  operation->key_buffer = mbedtls_calloc(1, key_buffer_length);
  if (operation->key_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memcpy(operation->key_buffer, key_buffer + offset, key_buffer_length);
  operation->key_in = input_key_desc;
  operation->key_buffer_size = key_buffer_length;
  return PSA_SUCCESS;
}

/** Derive a key from an ongoing key derivation operation.
 *
 * This function calculates output bytes from a key derivation algorithm
 * and uses those bytes to generate a key deterministically.
 * The key's location, usage policy, type and size are taken from
 * \p attributes.
 *
 * If you view the key derivation's output as a stream of bytes, this
 * function destructively reads as many bytes as required from the
 * stream.
 * The operation's capacity decreases by the number of bytes read.
 *
 * If this function returns an error status other than
 * #PSA_ERROR_INSUFFICIENT_DATA, the operation enters an error
 * state and must be aborted by calling psa_key_derivation_abort().
 *
 * How much output is produced and consumed from the operation, and how
 * the key is derived, depends on the key type:
 *
 * - For key types for which the key is an arbitrary sequence of bytes
 *   of a given size, this function is functionally equivalent to
 *   calling #psa_key_derivation_output_bytes
 *   and passing the resulting output to #psa_import_key.
 *   However, this function has a security benefit:
 *   if the implementation provides an isolation boundary then
 *   the key material is not exposed outside the isolation boundary.
 *   As a consequence, for these key types, this function always consumes
 *   exactly (\p bits / 8) bytes from the operation.
 *   The following key types defined in this specification follow this scheme:
 *
 *     - #PSA_KEY_TYPE_AES;
 *     - #PSA_KEY_TYPE_ARC4;
 *     - #PSA_KEY_TYPE_CAMELLIA;
 *     - #PSA_KEY_TYPE_DERIVE;
 *     - #PSA_KEY_TYPE_HMAC.
 *
 * - For ECC keys on a Montgomery elliptic curve
 *   (#PSA_KEY_TYPE_ECC_KEY_PAIR(\c curve) where \c curve designates a
 *   Montgomery curve), this function always draws a byte string whose
 *   length is determined by the curve, and sets the mandatory bits
 *   accordingly. That is:
 *
 *     - Curve25519 (#PSA_ECC_FAMILY_MONTGOMERY, 255 bits): draw a 32-byte
 *       string and process it as specified in RFC 7748 &sect;5.
 *     - Curve448 (#PSA_ECC_FAMILY_MONTGOMERY, 448 bits): draw a 56-byte
 *       string and process it as specified in RFC 7748 &sect;5.
 *
 * - For key types for which the key is represented by a single sequence of
 *   \p bits bits with constraints as to which bit sequences are acceptable,
 *   this function draws a byte string of length (\p bits / 8) bytes rounded
 *   up to the nearest whole number of bytes. If the resulting byte string
 *   is acceptable, it becomes the key, otherwise the drawn bytes are discarded.
 *   This process is repeated until an acceptable byte string is drawn.
 *   The byte string drawn from the operation is interpreted as specified
 *   for the output produced by psa_export_key().
 *   The following key types defined in this specification follow this scheme:
 *
 *     - #PSA_KEY_TYPE_DES.
 *       Force-set the parity bits, but discard forbidden weak keys.
 *       For 2-key and 3-key triple-DES, the three keys are generated
 *       successively (for example, for 3-key triple-DES,
 *       if the first 8 bytes specify a weak key and the next 8 bytes do not,
 *       discard the first 8 bytes, use the next 8 bytes as the first key,
 *       and continue reading output from the operation to derive the other
 *       two keys).
 *     - Finite-field Diffie-Hellman keys (#PSA_KEY_TYPE_DH_KEY_PAIR(\c group)
 *       where \c group designates any Diffie-Hellman group) and
 *       ECC keys on a Weierstrass elliptic curve
 *       (#PSA_KEY_TYPE_ECC_KEY_PAIR(\c curve) where \c curve designates a
 *       Weierstrass curve).
 *       For these key types, interpret the byte string as integer
 *       in big-endian order. Discard it if it is not in the range
 *       [0, *N* - 2] where *N* is the boundary of the private key domain
 *       (the prime *p* for Diffie-Hellman, the subprime *q* for DSA,
 *       or the order of the curve's base point for ECC).
 *       Add 1 to the resulting integer and use this as the private key *x*.
 *       This method allows compliance to NIST standards, specifically
 *       the methods titled "key-pair generation by testing candidates"
 *       in NIST SP 800-56A &sect;5.6.1.1.4 for Diffie-Hellman,
 *       in FIPS 186-4 &sect;B.1.2 for DSA, and
 *       in NIST SP 800-56A &sect;5.6.1.2.2 or
 *       FIPS 186-4 &sect;B.4.2 for elliptic curve keys.
 *
 * - For other key types, including #PSA_KEY_TYPE_RSA_KEY_PAIR,
 *   the way in which the operation output is consumed is
 *   implementation-defined.
 *
 * In all cases, the data that is read is discarded from the operation.
 * The operation's capacity is decreased by the number of bytes read.
 *
 * For algorithms that take an input step #PSA_KEY_DERIVATION_INPUT_SECRET,
 * the input to that step must be provided with psa_key_derivation_input_key().
 * Future versions of this specification may include additional restrictions
 * on the derived key based on the attributes and strength of the secret key.
 *
 * \param[in] attributes    The attributes for the new key.
 * \param[in,out] operation The key derivation operation object to read from.
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
 * \retval #PSA_ERROR_INSUFFICIENT_DATA
 *         There was not enough data to create the desired key.
 *         Note that in this case, no output is written to the output buffer.
 *         The operation's capacity is set to 0, thus subsequent calls to
 *         this function will not succeed, even with a smaller output buffer.
 * \retval #PSA_ERROR_NOT_SUPPORTED
 *         The key type or key size is not supported, either by the
 *         implementation in general or in this particular location.
 * \retval #PSA_ERROR_INVALID_ARGUMENT
 *         The provided key attributes are not valid for the operation.
 * \retval #PSA_ERROR_NOT_PERMITTED
 *         The #PSA_KEY_DERIVATION_INPUT_SECRET input was not provided through
 *         a key.
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid (it must be active and completed
 *         all required input steps).
 * \retval #PSA_ERROR_INSUFFICIENT_MEMORY
 * \retval #PSA_ERROR_INSUFFICIENT_STORAGE
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_STORAGE_FAILURE
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_output_key(
  const psa_key_attributes_t *attributes,
  sli_se_driver_key_derivation_operation_t *operation,
  uint8_t *key_buffer,
  size_t key_buffer_size,
  size_t *key_buffer_length) // Assuming this parameter is required here?
{
  if (attributes == NULL
      || operation == NULL
      || key_buffer == NULL
      || key_buffer_size == 0
      || key_buffer_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (!PSA_ALG_IS_HKDF(operation->derivation_algo)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }
  if (PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes))
      == PSA_KEY_LOCATION_LOCAL_STORAGE) {
    // Output key should never be called when output is plaintext
    return PSA_ERROR_NOT_PERMITTED;
  }
  *key_buffer_length = 0;

  // The attributes object is the only way to determine key size here
  size_t key_size = PSA_BITS_TO_BYTES(psa_get_key_bits(attributes));
  sl_se_key_descriptor_t output_key_desc = { 0 };
  psa_status_t psa_status =
    sli_se_key_desc_from_psa_attributes(attributes, key_size, &output_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  psa_status = sli_se_set_key_desc_output(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          key_size,
                                          &output_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  // Set output length explicitly since it is authoritative for the key
  // generation
  output_key_desc.size = key_size;

  psa_status = derive_key_hkdf(operation, &output_key_desc);
  if (psa_status == PSA_SUCCESS) {
    // Add the key desc to the output array
    psa_status = store_key_desc_in_context(&output_key_desc, key_buffer, key_buffer_size);
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }

    // Populate the output argument upon success
    psa_status = sli_se_get_key_buffer_length(attributes,
                                              &output_key_desc,
                                              key_buffer_length);
  }
  return psa_status;
}

/** Read some data from a key derivation operation.
 *
 * This function calculates output bytes from a key derivation algorithm and
 * return those bytes.
 * If you view the key derivation's output as a stream of bytes, this
 * function destructively reads the requested number of bytes from the
 * stream.
 * The operation's capacity decreases by the number of bytes read.
 *
 * If this function returns an error status other than
 * #PSA_ERROR_INSUFFICIENT_DATA, the operation enters an error
 * state and must be aborted by calling psa_key_derivation_abort().
 *
 * \param[in,out] operation The key derivation operation object to read from.
 * \param[out] output       Buffer where the output will be written.
 * \param output_length     Number of bytes to output.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_INSUFFICIENT_DATA
 *                          The operation's capacity was less than
 *                          \p output_length bytes. Note that in this case,
 *                          no output is written to the output buffer.
 *                          The operation's capacity is set to 0, thus
 *                          subsequent calls to this function will not
 *                          succeed, even with a smaller output buffer.
 * \retval #PSA_ERROR_BAD_STATE
 *         The operation state is not valid (it must be active and completed
 *         all required input steps).
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
psa_status_t sli_se_driver_key_derivation_output_bytes(
  sli_se_driver_key_derivation_operation_t *operation,
  uint8_t *output,
  size_t output_length)
{
  if (operation == NULL
      || output == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (!PSA_ALG_IS_HKDF(operation->derivation_algo)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Since we only have a one-shot implementation in SE manager, we have to
  // generate the entire output when requested to output some data

  // Create a plaintext output key pointing to the output buffer
  sl_se_key_descriptor_t output_key_desc = {
    .size = output_length,
    .type = SL_SE_KEY_TYPE_SYMMETRIC,
  };
  sli_se_key_descriptor_set_plaintext(&output_key_desc, output, output_length);

  return derive_key_hkdf(operation, &output_key_desc);
}

/** Abort a key derivation operation.
 *
 * Aborting an operation frees all associated resources except for the \c
 * operation structure itself. Once aborted, the operation object can be reused
 * for another operation by calling psa_key_derivation_setup() again.
 *
 * This function may be called at any time after the operation
 * object has been initialized as described in #psa_key_derivation_operation_t.
 *
 * In particular, it is valid to call psa_key_derivation_abort() twice, or to
 * call psa_key_derivation_abort() on an operation that has not been set up.
 *
 * \param[in,out] operation    The operation to abort.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_COMMUNICATION_FAILURE
 * \retval #PSA_ERROR_HARDWARE_FAILURE
 * \retval #PSA_ERROR_CORRUPTION_DETECTED
 * \retval #PSA_ERROR_BAD_STATE
 *         The library has not been previously initialized by psa_crypto_init().
 *         It is implementation-dependent whether a failure to initialize
 *         results in this error code.
 */
psa_status_t sli_se_driver_key_derivation_abort(
  sli_se_driver_key_derivation_operation_t *operation)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Free allocated memory
  if (operation->key_buffer != NULL) {
    mbedtls_free(operation->key_buffer);
  }
  if (operation->info != NULL) {
    mbedtls_free(operation->info);
  }
  if (operation->salt != NULL) {
    mbedtls_free(operation->salt);
  }

  // Zero out the entire struct last
  memset(operation, 0, sizeof(sli_se_driver_key_derivation_operation_t));
  return PSA_SUCCESS;
}

/**
 * @brief
 *   Dedicated oneshot function for opaque drivers. Defined in mbedtls ticket
 *   3718: https://github.com/ARMmbed/mbedtls/issues/3718
 */
psa_status_t sli_se_opaque_key_derivation_oneshot(
  psa_algorithm_t alg,
  const psa_key_attributes_t *secret_key_attributes,
  const uint8_t *secret_key_buffer,
  size_t secret_key_size,
  const psa_key_derivation_input_buffer_t *input_array,
  size_t input_count,
  const psa_key_attributes_t *output_key_attributes,
  uint8_t *output_key_buffer,
  size_t output_key_size,
  size_t *output_key_length)
{
  // Argument check
  if (secret_key_attributes == NULL
      || secret_key_buffer == NULL
      || input_array == NULL
      || input_count == 0
      || output_key_attributes == NULL
      || output_key_buffer == NULL
      || output_key_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Use a operation object to be able to utilize the same framework as the
  // step-by-step implementation
  sli_se_driver_key_derivation_operation_t operation = { 0 };
  psa_status_t psa_status = sli_se_driver_key_derivation_setup(&operation, alg);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Create key descriptor object for input
  sl_se_key_descriptor_t input_key_desc = { 0 };
  psa_status = sli_se_key_desc_from_input(secret_key_attributes,
                                          secret_key_buffer,
                                          secret_key_size,
                                          &input_key_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }
  operation.key_in = input_key_desc;
  psa_key_location_t location =
    PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(secret_key_attributes));
  size_t offset = 0;
  switch (location) {
    case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
      offset = offsetof(sli_se_opaque_wrapped_key_context_t, wrapped_buffer);
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }
  if (secret_key_size < offset) {
    return PSA_ERROR_INSUFFICIENT_DATA;
  }
  operation.key_buffer = (uint8_t *)(secret_key_buffer + offset);
  operation.key_buffer_size = secret_key_size - offset;

  // Set the remaining input. PSA guarantees that the input is present in
  // correct order, but we will do a few double checks either way
  if (input_count != 2) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if (input_array[0].step != PSA_KEY_DERIVATION_INPUT_SALT
      || input_array[1].step != PSA_KEY_DERIVATION_INPUT_INFO) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  psa_key_derivation_input_buffer_t salt_input = input_array[0];
  psa_key_derivation_input_buffer_t info_input = input_array[1];
  operation.salt = (uint8_t *)salt_input.data;
  operation.salt_len = salt_input.length;
  operation.info = (uint8_t *)info_input.data;
  operation.info_len = info_input.length;

  // All input is prepared. Just use the existing key output function to
  // derive the key
  return sli_se_driver_key_derivation_output_key(output_key_attributes,
                                                 &operation,
                                                 output_key_buffer,
                                                 output_key_size,
                                                 output_key_length);
}
#endif // Vault

psa_status_t sli_se_driver_key_agreement(psa_algorithm_t alg,
                                         const psa_key_attributes_t *attributes,
                                         const uint8_t *key_buffer,
                                         size_t key_buffer_size,
                                         const uint8_t *peer_key,
                                         size_t peer_key_length,
                                         uint8_t *output,
                                         size_t output_size,
                                         size_t *output_length)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sl_status_t sl_status = SL_STATUS_FAIL;
  sl_se_key_descriptor_t priv_desc = { 0 };
  sl_se_key_descriptor_t pub_desc = { 0 };
  sl_se_key_descriptor_t shared_desc = { 0 };
  size_t padding_bytes = 0;
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  uint8_t tmp_output_buf[SLI_SE_MAX_PADDED_ECP_PUBLIC_KEY_SIZE] = { 0 };
  #else
  uint8_t tmp_output_buf[PSA_BITS_TO_BYTES(256) * 2] = { 0 };
  #endif

  // Argument check.
  if (key_buffer == NULL
      || peer_key == NULL
      || output == NULL
      || output_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_type_t key_type = psa_get_key_type(attributes);
  size_t key_bits = psa_get_key_bits(attributes);
  psa_ecc_curve_t curve_type = PSA_KEY_TYPE_GET_CURVE(key_type);

  // Check that key_buffer contains private key.
  if (PSA_KEY_TYPE_IS_PUBLIC_KEY(key_type)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Only accelerate ECDH.
  if (!PSA_ALG_IS_ECDH(alg)) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  // Check private key buffer.
  if (key_buffer_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check sufficient output buffer size.
  if (output_size < PSA_BITS_TO_BYTES(key_bits)) {
    return PSA_ERROR_BUFFER_TOO_SMALL;
  }

  // Initialize ephemeral key attributes struct.
  psa_key_attributes_t tmp_peer_key_attributes = psa_key_attributes_init();
  psa_set_key_type(&tmp_peer_key_attributes,
                   PSA_KEY_TYPE_ECC_PUBLIC_KEY(curve_type));
  psa_set_key_bits(&tmp_peer_key_attributes, key_bits);

  // Validate key.
  size_t bits = 0;
  psa_status = sli_se_driver_validate_key(&tmp_peer_key_attributes,
                                          peer_key,
                                          peer_key_length,
                                          &bits);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Check that validated key is actally on the same curve as expected.
  if (bits != key_bits) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  switch (key_type) {
    case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_CURVE_SECP_R1):
      switch (key_bits) {
        case 192:
          pub_desc.type = SL_SE_KEY_TYPE_ECC_P192;
          break;
        case 256:
          pub_desc.type = SL_SE_KEY_TYPE_ECC_P256;
          break;
        #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case 384:
          pub_desc.type = SL_SE_KEY_TYPE_ECC_P384;
          break;
        case 521:
          pub_desc.type = SL_SE_KEY_TYPE_ECC_P521;
          padding_bytes = 2;
          break;
        #endif // (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }

      // Set key descriptor attributes.
      // If padding is required, this will be done later.
      if (padding_bytes == 0) {
        sli_se_key_descriptor_set_plaintext(&pub_desc,
                                            peer_key + 1,
                                            peer_key_length - 1);
        sli_se_key_descriptor_set_plaintext(&shared_desc,
                                            tmp_output_buf,
                                            sizeof(tmp_output_buf));
        shared_desc.size = PSA_BITS_TO_BYTES(key_bits) * 2;
      }
      break;
    #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_CURVE_MONTGOMERY):

      // Check peer_key is of sufficient size.
      if (peer_key_length < PSA_BITS_TO_BYTES(key_bits)) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }

      switch (key_bits) {
        case 255:
          pub_desc.type = SL_SE_KEY_TYPE_ECC_X25519;
          break;
        default:
          return PSA_ERROR_NOT_SUPPORTED;
      }

      // Set key descriptor attributes.
      sli_se_key_descriptor_set_plaintext(&pub_desc,
                                          peer_key,
                                          peer_key_length);
      sli_se_key_descriptor_set_plaintext(&shared_desc,
                                          output,
                                          output_size);
      shared_desc.size = PSA_BITS_TO_BYTES(key_bits);
      break;
    #endif // (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  // Generate a key descriptor for private key.
  psa_status = sli_se_key_desc_from_input(attributes,
                                          key_buffer,
                                          key_buffer_size,
                                          &priv_desc);
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  // Panther crypto engine requires alignment on word boundries instead of byte
  // boundaries which is used in the PSA crypto API.
  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  uint8_t tmp_priv_padded_buf[SLI_SE_MAX_PADDED_ECP_PRIVATE_KEY_SIZE] = { 0 };
  uint8_t tmp_pub_padded_buf[SLI_SE_MAX_PADDED_ECP_PUBLIC_KEY_SIZE] = { 0 };

  // Should currently only happen for curve P521.
  if (padding_bytes > 0) {
    // Can only do padding on non-wrapped keys.
    if (PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes))
        == PSA_KEY_LOCATION_LOCAL_STORAGE) {
      // Pad private key.
      sli_se_pad_big_endian(tmp_priv_padded_buf, key_buffer,
                            PSA_BITS_TO_BYTES(key_bits));

      // Re-set key descriptor attributes.
      sli_se_key_descriptor_set_plaintext(&priv_desc,
                                          tmp_priv_padded_buf,
                                          sizeof(tmp_priv_padded_buf));
    }

    // Pad public key.
    sli_se_pad_curve_point(tmp_pub_padded_buf, peer_key + 1,
                           PSA_BITS_TO_BYTES(key_bits));

    // Set key descriptor attributes.
    sli_se_key_descriptor_set_plaintext(&pub_desc,
                                        tmp_pub_padded_buf,
                                        sizeof(tmp_pub_padded_buf));
    sli_se_key_descriptor_set_plaintext(&shared_desc,
                                        tmp_output_buf,
                                        sizeof(tmp_output_buf));
    shared_desc.size = (PSA_BITS_TO_BYTES(key_bits) + padding_bytes) * 2;
  }
  #endif // (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

  // Set key descriptor attributes that are common to all supported curves.
  pub_desc.flags |= SL_SE_KEY_FLAG_ASYMMETRIC_BUFFER_HAS_PUBLIC_KEY;
  shared_desc.type = SL_SE_KEY_TYPE_SYMMETRIC;

  // Create ephemeral SE command context.
  sl_se_command_context_t cmd_ctx = SL_SE_COMMAND_CONTEXT_INIT;
  sl_status = sl_se_init_command_context(&cmd_ctx);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Perform key agreement algorithm (ECDH).
  sl_status = sl_se_ecdh_compute_shared_secret(&cmd_ctx,
                                               &priv_desc,
                                               &pub_desc,
                                               &shared_desc);
  if (sl_status != SL_STATUS_OK) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  #if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
  // Remove padding bytes and clean up temporary key storage.
  if (padding_bytes > 0) {
    sli_se_unpad_curve_point(tmp_output_buf,
                             tmp_output_buf,
                             PSA_BITS_TO_BYTES(key_bits));
    memset(tmp_priv_padded_buf, 0, sizeof(tmp_priv_padded_buf));
  }
  #endif // VAULT

  // Montgomery curve computations do not require the temporary buffer to store the y-coord.
  if (key_type == PSA_KEY_TYPE_ECC_KEY_PAIR(PSA_ECC_CURVE_SECP_R1)) {
    memcpy(output, tmp_output_buf, PSA_BITS_TO_BYTES(key_bits));
    memset(tmp_output_buf, 0, sizeof(tmp_output_buf));
  }

  *output_length = PSA_BITS_TO_BYTES(key_bits);

  return PSA_SUCCESS;
}

#ifdef __cplusplus
}
#endif
#endif // SEMAILBOX_PRESENT
