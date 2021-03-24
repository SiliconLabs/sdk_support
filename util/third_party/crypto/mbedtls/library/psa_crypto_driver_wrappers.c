/*
 *  Functions to delegate cryptographic operations to an available
 *  and appropriate accelerator.
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

#include "psa_crypto_core.h"
#include "psa_crypto_driver_wrappers.h"
#include "mbedtls/platform.h"

#if defined(MBEDTLS_PSA_CRYPTO_DRIVERS)

/* Include test driver definition when running tests */
#if defined(PSA_CRYPTO_DRIVER_TEST)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "test/drivers/test_driver.h"
#endif /* PSA_CRYPTO_DRIVER_TEST */

/* Repeat above block for each JSON-declared driver during autogeneration */
#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "sli_se_transparent_types.h"
#include "sli_se_transparent_functions.h"
#endif /* SEMAILBOX_PRESENT */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "sli_se_opaque_types.h"
#include "sli_se_opaque_functions.h"
#endif /* SEMAILBOX_PRESENT  && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) */

#if defined(CRYPTOACC_PRESENT)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "sli_cryptoacc_transparent_types.h"
#include "sli_cryptoacc_transparent_functions.h"
#endif /* CRYPTOACC_PRESENT */

#if defined(CRYPTO_PRESENT)
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#ifndef PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#endif
#include "sli_crypto_transparent_types.h"
#include "sli_crypto_transparent_functions.h"
#endif /* CRYPTO_PRESENT */


/* Auto-generated values depending on which drivers are registered. ID 0 is
 * reserved for unallocated operations.
 * NOTE: these values have no correlation with the driver 'location' as defined
 * by the accelerator specification document. The driver IDs are runtime values
 * to indicate which driver is handling a multi-part operation that is in
 * process. */
#if defined(PSA_CRYPTO_DRIVER_TEST)
/* Test driver gets IDs 1 and 2 */
#define PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID (1)
#define PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID (2)
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
/* Other drivers get unique IDs assigned in sequence */
#define SLI_SE_TRANSPARENT_DRIVER_ID (3)
#define SLI_SE_OPAQUE_DRIVER_ID (4)
#define SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID (5)
#define SLI_CRYPTO_TRANSPARENT_DRIVER_ID (6)
#endif

#endif /* MBEDTLS_PSA_CRYPTO_DRIVERS */

/* Support the 'old' SE interface when asked to */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
/* PSA_CRYPTO_DRIVER_PRESENT is defined when either a new-style or old-style
 * SE driver is present, to avoid unused argument errors at compile time. */
#ifndef PSA_CRYPTO_DRIVER_PRESENT
#define PSA_CRYPTO_DRIVER_PRESENT
#endif
#include "psa_crypto_se.h"
#include "psa_crypto_storage.h"
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
/** Calculate the size to allocate for buffering a key with given attributes.
 *
 * This function provides a way to get the expected size for storing a key with
 * the given attributes. This will be the size of the export representation for
 * cleartext keys, and a driver-defined size for keys stored by opaque drivers.
 *
 * \param[in] attributes        The key attribute structure of the key to store.
 * \param[out] expected_size    On success, a byte size large enough to contain
 *                              the declared key.
 *
 * \retval #PSA_SUCCESS
 * \retval #PSA_ERROR_NOT_SUPPORTED
 */
static psa_status_t get_expected_key_size( const psa_key_attributes_t *attributes,
                                           size_t *expected_size )
{
    size_t buffer_size = 0;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION( attributes->core.lifetime );
    psa_key_type_t key_type = attributes->core.type;
    size_t key_bits = attributes->core.bits;

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            buffer_size = PSA_KEY_EXPORT_MAX_SIZE( key_type, key_bits );

            if( buffer_size == 0 )
                return( PSA_ERROR_NOT_SUPPORTED );

            *expected_size = buffer_size;
            return( PSA_SUCCESS );

#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            buffer_size = PSA_KEY_EXPORT_MAX_SIZE( key_type, key_bits );

            if( buffer_size == 0 )
                return( PSA_ERROR_INVALID_ARGUMENT );

            // Remove public key format byte
            if( PSA_KEY_TYPE_IS_PUBLIC_KEY( key_type ) ) {
                buffer_size--;
            }

            // Compensate for word alignment demands
            buffer_size = sli_se_word_align( buffer_size );
            if( PSA_BITS_TO_BYTES( attributes->core.bits ) & 0x3 ) {
                if( PSA_KEY_TYPE_IS_PUBLIC_KEY(attributes->core.type) ) {
                    // Allocate extra word for public keys, since alignment constrains
                    // May require that
                    buffer_size += sizeof(uint32_t);
                }
            }
            // Add wrapped context overhead
            buffer_size += sizeof(sli_se_opaque_wrapped_key_context_t);

            *expected_size = buffer_size;

            return ( PSA_SUCCESS );
#endif // VAULT

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
#ifdef TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION
            *expected_size = test_size_function( key_type, key_bits );
            return( PSA_SUCCESS );
#else /* TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION */
            if( PSA_KEY_TYPE_IS_KEY_PAIR( key_type ) )
            {
                int public_key_overhead = ( ( TEST_DRIVER_KEY_CONTEXT_STORE_PUBLIC_KEY == 1 ) ?
                                           PSA_KEY_EXPORT_MAX_SIZE( key_type, key_bits ) : 0 );
                *expected_size = TEST_DRIVER_KEY_CONTEXT_BASE_SIZE
                                 + TEST_DRIVER_KEY_CONTEXT_PUBLIC_KEY_SIZE
                                 + public_key_overhead;
            }
            else if( PSA_KEY_TYPE_IS_PUBLIC_KEY( attributes->core.type ) )
            {
                *expected_size = TEST_DRIVER_KEY_CONTEXT_BASE_SIZE
                                 + TEST_DRIVER_KEY_CONTEXT_PUBLIC_KEY_SIZE;
            }
            else if ( !PSA_KEY_TYPE_IS_KEY_PAIR( key_type ) &&
                      !PSA_KEY_TYPE_IS_PUBLIC_KEY ( attributes->core.type ) )
            {
                *expected_size = TEST_DRIVER_KEY_CONTEXT_BASE_SIZE
                                 + TEST_DRIVER_KEY_CONTEXT_SYMMETRIC_FACTOR
                                 * ( ( key_bits + 7 ) / 8 );
            }
            else
            {
                return( PSA_ERROR_NOT_SUPPORTED );
            }
            return( PSA_SUCCESS );
#endif /* TEST_DRIVER_KEY_CONTEXT_SIZE_FUNCTION */
#endif /* PSA_CRYPTO_DRIVER_TEST */

        default:
            return( PSA_ERROR_NOT_SUPPORTED );
    }
}
#endif /* PSA_CRYPTO_DRIVER_PRESENT */


/* Start delegation functions */

/*
 * Init function
 */
psa_status_t psa_driver_wrapper_init( void )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    psa_status_t status;

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    status = psa_init_all_se_drivers( );
    if( status != PSA_SUCCESS )
        return status;

    /* continue to driver init calls */
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    status = PSA_SUCCESS;

#if defined(SEMAILBOX_PRESENT)
    status = sli_se_transparent_driver_init();
    if( status != PSA_SUCCESS )
        return status;

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    status = sli_se_opaque_driver_init();
#endif /* Vault */

#endif /* SEMAILBOX_PRESENT */

#if defined(CRYPTOACC_PRESENT)
    status = sli_cryptoacc_transparent_driver_init();
#endif /* CRYPTOACC_PRESENT */

#if defined(CRYPTO_PRESENT)
    status = sli_crypto_transparent_driver_init();
#endif /* CRYPTO_PRESENT */

    return( status );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#else
    return( PSA_SUCCESS );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

/*
 * Key management functions
 */
psa_status_t psa_driver_wrapper_allocate_key(
    const psa_key_attributes_t *attributes )
{
    (void) attributes;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));

    switch( location )
    {
#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            {
                return PSA_SUCCESS;
            }
#endif // VAULT

        default:
            /* Key is declared with a lifetime not known to us */
            return( PSA_ERROR_NOT_SUPPORTED );
    }
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_copy_key(
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *source_slot,
    psa_key_slot_t *target_slot )
{
    (void) attributes;
    (void) source_slot;
    (void) target_slot;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    // psa_driver_wrapper_import_key;
    // psa_driver_wrapper_export_key;
    (void) psa_driver_wrapper_allocate_key( attributes );

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_import_key(
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *slot,
    const uint8_t *data,
    size_t data_length )
{
    (void) attributes;
    (void) slot;
    (void) data;
    (void) data_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    psa_status_t status;

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;
    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        /* The driver should set the number of key bits, however in
         * case it doesn't, we initialize bits to an invalid value. */
        size_t bits = PSA_MAX_KEY_BITS + 1;
        if( drv->key_management == NULL ||
            drv->key_management->p_import == NULL )
        {
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        status = drv->key_management->p_import(
            drv_context,
            slot->data.se.slot_number, attributes, data, data_length,
            &bits );
        if( status != PSA_SUCCESS )
            return status;
        if( bits > PSA_MAX_KEY_BITS )
        {
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        slot->attr.bits = (psa_key_bits_t) bits;

        return( PSA_SUCCESS );
    }

    /* fall through */
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            return PSA_ERROR_NOT_SUPPORTED;

#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            {
                psa_key_attributes_t attributes_copy = *attributes;
                size_t bits = 0;
                // Only allocate the key buffer for opaque, as transparent is
                // handled by the core
                size_t export_size = 0;
                if (attributes_copy.core.bits == 0) {
                    // Set bits from input length
                    attributes_copy.core.bits = 8 * data_length;
                    if( PSA_KEY_TYPE_IS_ECC_PUBLIC_KEY(attributes_copy.core.type) ) {
                        attributes_copy.core.bits -= 8;
                        attributes_copy.core.bits /= 2;
                    }
                    if( (PSA_KEY_TYPE_ECC_GET_FAMILY( attributes_copy.core.type )
                          ==  PSA_ECC_FAMILY_SECP_R1 )
                        && attributes_copy.core.bits == PSA_BITS_TO_BYTES(521) * 8 )
                        attributes_copy.core.bits = 521;
                }
                status = get_expected_key_size( &attributes_copy, &export_size );
                if( status != PSA_SUCCESS ) {
                    return( status );
                }
                slot->data.key.data = mbedtls_calloc(1, export_size);
                if( slot->data.key.data == NULL ) {
                    return( PSA_ERROR_INSUFFICIENT_MEMORY );
                }
                slot->data.key.bytes = export_size;

                // This seems to be something that is done in handling for the
                // SE driver, and is important to pass import_export tests.
                bits = attributes_copy.core.bits;

                status = sli_se_opaque_import_key( attributes,
                                                   data, data_length,
                                                   slot->data.key.data,
                                                   slot->data.key.bytes,
                                                   &slot->data.key.bytes,
                                                   &bits);
                slot->attr.bits = (psa_key_bits_t) bits;

                if( status != PSA_SUCCESS )
                {
                    /* free allocated buffer on failure */
                    mbedtls_free( slot->data.key.data );
                    slot->data.key.data = NULL;
                    slot->data.key.bytes = 0;
                }

                // Cannot have fallback for opaque drivers:
                return status;
            }
#endif // VAULT

        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_export_key(
    const psa_key_slot_t *slot,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length )
{
    (void) slot;
    (void) key_buffer;
    (void) key_buffer_size;
    (void) key_buffer_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;
    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        psa_drv_se_export_key_t method;
        if( drv->key_management == NULL )
            return( PSA_ERROR_NOT_SUPPORTED );
        method = drv->key_management->p_export;
        if( method == NULL )
            return( PSA_ERROR_NOT_SUPPORTED );
        return( method( drv_context,
                        slot->data.se.slot_number,
                        key_buffer, key_buffer_size, key_buffer_length ) );
    }

    /* fall through */
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

            return( PSA_ERROR_NOT_SUPPORTED );
#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            {
                psa_key_attributes_t attributes = {
                  .core = slot->attr
                };
                // We are on a vault device, call opaque driver
                status = sli_se_opaque_export_key( &attributes,
                                                   slot->data.key.data,
                                                   slot->data.key.bytes,
                                                   key_buffer,
                                                   key_buffer_size,
                                                   key_buffer_length );
                // Cannot have fallback for opaque drivers:
                return status;
            }
#endif // VAULT
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_export_public_key(
    const psa_key_slot_t *slot,
    uint8_t *key_buffer,
    size_t key_buffer_size,
    size_t *key_buffer_length )
{
    (void) slot;
    (void) key_buffer;
    (void) key_buffer_size;
    (void) key_buffer_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;
    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        psa_drv_se_export_key_t method;
        if( drv->key_management == NULL )
            return( PSA_ERROR_NOT_SUPPORTED );
        method = drv->key_management->p_export_public;
        if( method == NULL )
            return( PSA_ERROR_NOT_SUPPORTED );
        return( method( drv_context,
                        slot->data.se.slot_number,
                        key_buffer, key_buffer_size, key_buffer_length ) );
    }

    /* fall through */
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };
    (void) attributes;

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* If the key is stored transparently and is already a public key,
             * let the core handle it. */
            if( PSA_KEY_TYPE_IS_PUBLIC_KEY( psa_get_key_type( &attributes ) ) )
                return( PSA_ERROR_NOT_SUPPORTED );
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_export_public_key( &attributes,
                                                           slot->data.key.data,
                                                           slot->data.key.bytes,
                                                           key_buffer,
                                                           key_buffer_size,
                                                           key_buffer_length );

            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif // SEMAILBOX_PRESENT

#if defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_export_public_key( &attributes,
                                                                  slot->data.key.data,
                                                                  slot->data.key.bytes,
                                                                  key_buffer,
                                                                  key_buffer_size,
                                                                  key_buffer_length );

            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif // CRYPTOACC_PRESENT

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_export_public_key( &attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      key_buffer,
                                                      key_buffer_size,
                                                      key_buffer_length );
            // Cannot have fallback for opaque drivers:
            return status;
#endif // SEMAILBOX_PRESENT & VAULT
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_destroy_key(
    psa_key_slot_t *slot )
{
    (void) slot;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT; /* status of the last operation */
    psa_status_t overall_status = PSA_SUCCESS;

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)

    psa_se_drv_table_entry_t *driver;
    driver = psa_get_se_driver_entry( slot->attr.lifetime );
    if( driver != NULL )
    {
        /* For a key in a secure element, we need to do three things:
         * remove the key file in internal storage, destroy the
         * key inside the secure element, and update the driver's
         * persistent data. Start a transaction that will encompass these
         * three actions. */
        psa_crypto_prepare_transaction( PSA_CRYPTO_TRANSACTION_DESTROY_KEY );
        psa_crypto_transaction.key.lifetime = slot->attr.lifetime;
        psa_crypto_transaction.key.slot = slot->data.se.slot_number;
        psa_crypto_transaction.key.id = slot->attr.id;
        status = psa_crypto_save_transaction( );
        if( status != PSA_SUCCESS )
        {
            (void) psa_crypto_stop_transaction( );
            /* We should still try to destroy the key in the secure
             * element and the key metadata in storage. This is especially
             * important if the error is that the storage is full.
             * But how to do it exactly without risking an inconsistent
             * state after a reset?
             * https://github.com/ARMmbed/mbed-crypto/issues/215
             */
            overall_status = status;
            return( overall_status );
        }

        status = psa_destroy_se_key( driver, slot->data.se.slot_number );
        if( overall_status == PSA_SUCCESS )
            overall_status = status;
    }

    if( driver != NULL )
    {
        status = psa_save_se_persistent_data( driver );
        if( overall_status == PSA_SUCCESS )
            overall_status = status;
        status = psa_crypto_stop_transaction( );
        if( overall_status == PSA_SUCCESS )
            overall_status = status;

        return( overall_status );
    }

    /* fall through */
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    (void) status;
    (void) overall_status;

    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);

    switch( location )
    {
#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            /* TODO: add the driver code for destroying keys here... */
            return PSA_ERROR_NOT_SUPPORTED;
#endif
        default:
            return PSA_ERROR_INVALID_ARGUMENT;
    }
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_validate_key(
    const psa_key_attributes_t *attributes,
    const uint8_t *data,
    size_t data_length,
    size_t *bits )
{
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT) && ( defined(PSA_CRYPTO_DRIVER_TEST) || defined(CRYPTOACC_PRESENT) || defined(SEMAILBOX_PRESENT) )
    psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
    /* Try accelerators in turn */
#if defined(PSA_CRYPTO_DRIVER_TEST)
    status = test_transparent_validate_key( attributes,
                                            data,
                                            data_length,
                                            bits );
    /* Declared with fallback == true */
    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(CRYPTOACC_PRESENT)
    status = sli_cryptoacc_transparent_validate_key( attributes,
                                                     data,
                                                     data_length,
                                                     bits );
    /* Declared with fallback == true */
    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif /* CRYPTOACC_PRESENT */

#if defined(SEMAILBOX_PRESENT)
    status = sli_se_transparent_validate_key( attributes,
                                              data,
                                              data_length,
                                              bits );
    /* Declared with fallback == true */
    if( status != PSA_ERROR_NOT_SUPPORTED )
        return( status );
#endif /* SEMAILBOX_PRESENT */

    return( PSA_ERROR_NOT_SUPPORTED );
#else /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT && (TEST_DRIVER || CRYPTOACC)*/
    (void) attributes;
    (void) data;
    (void) data_length;
    (void) bits;
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && (TEST_DRIVER || CRYPTOACC) */
}


/*
 * Key derivation functions
 */
psa_status_t psa_driver_wrapper_key_derivation_setup(
    psa_operation_driver_context_t *operation,
    psa_algorithm_t alg )
{
    (void) operation;
    (void) alg;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_input_bytes(
    psa_operation_driver_context_t *operation,
    psa_algorithm_t alg,
    const uint8_t *data,
    size_t data_length )
{
    (void) operation;
    (void) alg;
    (void) data;
    (void) data_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_input_key(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg )
{
    (void) operation;
    (void) slot;
    (void) alg;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_output_bytes(
    psa_operation_driver_context_t *operation,
    uint8_t *output,
    size_t output_length )
{
    (void) operation;
    (void) output;
    (void) output_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_output_key(
    psa_operation_driver_context_t *operation,
    const psa_key_attributes_t *attributes,
    psa_key_slot_t *slot )
{
    (void) attributes;
    (void) operation;
    (void) slot;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)

#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    (void) psa_driver_wrapper_allocate_key( attributes );

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_opaque_key_derivation_oneshot(
    psa_algorithm_t alg,
    psa_key_slot_t *secret_key_slot,
    psa_key_derivation_input_buffer_t *input_array,
    size_t input_count,
    const psa_key_attributes_t *output_key_attributes,
    psa_key_slot_t *output_key_slot)
{
    (void)alg;
    (void)secret_key_slot;
    (void)input_array;
    (void)input_count;
    (void)output_key_attributes;
    (void)output_key_slot;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_key_location_t location =
      PSA_KEY_LIFETIME_GET_LOCATION( secret_key_slot->attr.lifetime );

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* This is a dedicated opaque wrapper. Should never be called for
             * transparent keys */
            return( PSA_ERROR_NOT_SUPPORTED );

#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            {
                psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
                /* Allocate memory for output key */
                size_t export_size = 0;

                status = get_expected_key_size( output_key_attributes, &export_size );
                if( status != PSA_SUCCESS )
                    return( status );

                output_key_slot->data.key.data = mbedtls_calloc( 1, export_size );
                if( output_key_slot->data.key.data == NULL )
                    return( PSA_ERROR_INSUFFICIENT_MEMORY );
                output_key_slot->data.key.bytes = export_size;

                psa_key_attributes_t secret_key_attributes = {
                    .core = secret_key_slot->attr,
                };
                status = sli_se_opaque_key_derivation_oneshot(
                    alg,
                    &secret_key_attributes,
                    secret_key_slot->data.key.data,
                    secret_key_slot->data.key.bytes,
                    input_array,
                    input_count,
                    output_key_attributes,
                    output_key_slot->data.key.data,
                    output_key_slot->data.key.bytes,
                    &output_key_slot->data.key.bytes );

                if( status != PSA_SUCCESS )
                {
                    mbedtls_free( output_key_slot->data.key.data );
                    output_key_slot->data.key.data = NULL;
                }
                /* No fallback for opaque keys */
                return( status );
            }
#endif /* _SILICON_LABS_SECURITY_FEATURE_VAULT */

        default:
            return( PSA_ERROR_INVALID_ARGUMENT );
    }
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_set_capacity(
    psa_operation_driver_context_t *operation,
    size_t capacity )
{
    (void) operation;
    (void) capacity;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_key_derivation_abort(
    psa_operation_driver_context_t *operation )
{
    (void) operation;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

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
    size_t *shared_secret_length )
{
    (void) alg;
    (void) private_key;
    (void) peer_key;
    (void) peer_key_length;
    (void) shared_secret;
    (void) shared_secret_size;
    (void) shared_secret_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(private_key->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = private_key->attr
    };
    (void) attributes;

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_key_agreement( alg,
                                                       &attributes,
                                                       private_key->data.key.data,
                                                       private_key->data.key.bytes,
                                                       peer_key,
                                                       peer_key_length,
                                                       shared_secret,
                                                       shared_secret_size,
                                                       shared_secret_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* SEMAILBOX_PRESENT */

#if defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_key_agreement( alg,
                                                              &attributes,
                                                              private_key->data.key.data,
                                                              private_key->data.key.bytes,
                                                              peer_key,
                                                              peer_key_length,
                                                              shared_secret,
                                                              shared_secret_size,
                                                              shared_secret_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* CRYPTOACC_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_key_agreement( alg,
                                                  &attributes,
                                                  private_key->data.key.data,
                                                  private_key->data.key.bytes,
                                                  peer_key,
                                                  peer_key_length,
                                                  shared_secret,
                                                  shared_secret_size,
                                                  shared_secret_length );

            // Cannot have fallback for opaque drivers:
            return ( status );
#endif /* SEMAILBOX_PRESENT && VAULT */

        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

/*
 * Hash functions
 */
psa_status_t psa_driver_wrapper_hash_setup( psa_operation_driver_context_t *operation,
                                            psa_algorithm_t alg )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT)

#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

#if defined(SEMAILBOX_PRESENT)
    operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_transparent_hash_operation_t ) );
    if ( operation->ctx == NULL )
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    status = sli_se_transparent_hash_setup( operation->ctx, alg );

    if( status == PSA_SUCCESS )
        operation->id = SLI_SE_TRANSPARENT_DRIVER_ID;
    else
    {
        mbedtls_free( operation->ctx );
        operation->ctx = NULL;
    }

    return( status );
#elif defined(CRYPTOACC_PRESENT)
    operation->ctx = mbedtls_calloc( 1, sizeof( sli_cryptoacc_transparent_hash_operation_t ) );
    if ( operation->ctx == NULL )
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    status = sli_cryptoacc_transparent_hash_setup( operation->ctx, alg );

    if( status == PSA_SUCCESS )
        operation->id = SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID;
    else
    {
        mbedtls_free( operation->ctx );
        operation->ctx = NULL;
    }

    return( status );
#elif defined(CRYPTO_PRESENT)
    operation->ctx = mbedtls_calloc( 1, sizeof(sli_crypto_transparent_hash_operation_t) );
    if ( operation->ctx == NULL )
        return PSA_ERROR_INSUFFICIENT_MEMORY;
    status = sli_crypto_transparent_hash_setup( operation->ctx, alg );

    if( status == PSA_SUCCESS )
        operation->id = SLI_CRYPTO_TRANSPARENT_DRIVER_ID;
    else
    {
        mbedtls_free( operation->ctx );
        operation->ctx = NULL;
    }

    return( status );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */

#else
    (void) operation;
    (void) alg;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#else
    (void) operation;
    (void) alg;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_hash_clone( const psa_operation_driver_context_t *source_operation,
                                            psa_operation_driver_context_t *target_operation )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    switch( source_operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            target_operation->ctx = mbedtls_calloc( 1, sizeof(sli_se_transparent_hash_operation_t) );
            if( target_operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_se_transparent_hash_clone( source_operation->ctx,
                                                    target_operation->ctx );
            if( status == PSA_SUCCESS )
                target_operation->id = SLI_SE_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_free( target_operation->ctx );
                target_operation->ctx = NULL;
            }
            return( status );
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            target_operation->ctx = mbedtls_calloc( 1, sizeof(sli_cryptoacc_transparent_hash_operation_t) );
            if( target_operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_cryptoacc_transparent_hash_clone( source_operation->ctx,
                                                           target_operation->ctx );
            if( status == PSA_SUCCESS )
                target_operation->id = SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_free( target_operation->ctx );
                target_operation->ctx = NULL;
            }
            return( status );
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            target_operation->ctx = mbedtls_calloc( 1, sizeof(sli_crypto_transparent_hash_operation_t) );
            if( target_operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_crypto_transparent_hash_clone( source_operation->ctx,
                                                        target_operation->ctx );
            if( status == PSA_SUCCESS )
                target_operation->id = SLI_CRYPTO_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_free( target_operation->ctx );
                target_operation->ctx = NULL;
            }
            return( status );
#endif /* CRYPTO_PRESENT */
        default:
            /* Operation is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }

#else
    (void) source_operation;
    (void) target_operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}


psa_status_t psa_driver_wrapper_hash_update( psa_operation_driver_context_t *operation,
                                             const uint8_t *input,
                                             size_t input_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return( sli_se_transparent_hash_update( operation->ctx, input, input_length ) );
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return( sli_cryptoacc_transparent_hash_update( operation->ctx, input, input_length ) );
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return( sli_crypto_transparent_hash_update( operation->ctx, input, input_length ) );
#endif /* CRYPTO_PRESENT */
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }

#else
    (void) operation;
    (void) input;
    (void) input_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_hash_finish( psa_operation_driver_context_t *operation,
                                             uint8_t *hash,
                                             size_t hash_size,
                                             size_t *hash_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return( sli_se_transparent_hash_finish( operation->ctx,
                                                   hash,
                                                   hash_size,
                                                   hash_length ) );
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return( sli_cryptoacc_transparent_hash_finish( operation->ctx,
                                                          hash,
                                                          hash_size,
                                                          hash_length ) );
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return( sli_crypto_transparent_hash_finish( operation->ctx,
                                                        hash,
                                                        hash_size,
                                                        hash_length ) );
#endif /* CRYPTO_PRESENT */
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }

#else
    (void) operation;
    (void) hash;
    (void) hash_size;
    (void) hash_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT*/
}

psa_status_t psa_driver_wrapper_hash_abort( psa_operation_driver_context_t *operation )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    if( operation->ctx == NULL && operation->id == 0 )
        return( PSA_SUCCESS );

    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            status = sli_se_transparent_hash_abort( operation->ctx );
            break;
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            status = sli_cryptoacc_transparent_hash_abort( operation->ctx );
            break;
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            status = sli_crypto_transparent_hash_abort( operation->ctx );
            break;
#endif /* CRYPTO_PRESENT */
        default:
            /* Operation is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
    mbedtls_free( operation->ctx );
    operation->ctx = NULL;
    operation->id = 0;
    return( status );
#else
    (void) operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

/*
 * Signature functions
 */
psa_status_t psa_driver_wrapper_sign_hash( psa_key_slot_t *slot,
                                           psa_algorithm_t alg,
                                           const uint8_t *hash,
                                           size_t hash_length,
                                           uint8_t *signature,
                                           size_t signature_size,
                                           size_t *signature_length )
{
    (void) slot;
    (void) alg;
    (void) hash;
    (void) hash_length;
    (void) signature;
    (void) signature_size;
    (void) signature_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        if( drv->asymmetric == NULL ||
            drv->asymmetric->p_sign == NULL )
        {
            /* Key is defined in SE, but we have no way to exercise it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->asymmetric->p_sign( drv_context,
                                         slot->data.se.slot_number,
                                         alg,
                                         hash, hash_length,
                                         signature, signature_size,
                                         signature_length ) );
    }
#endif /* PSA_CRYPTO_SE_C */

    /* Then try accelerator API */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = test_transparent_signature_sign_hash( &attributes,
                                                           slot->data.key.data,
                                                           slot->data.key.bytes,
                                                           alg,
                                                           hash,
                                                           hash_length,
                                                           signature,
                                                           signature_size,
                                                           signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_sign_hash( &attributes,
                                                   slot->data.key.data,
                                                   slot->data.key.bytes,
                                                   alg,
                                                   hash,
                                                   hash_length,
                                                   signature,
                                                   signature_size,
                                                   signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_sign_hash( &attributes,
                                                          slot->data.key.data,
                                                          slot->data.key.bytes,
                                                          alg,
                                                          hash,
                                                          hash_length,
                                                          signature,
                                                          signature_size,
                                                          signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#else
            (void) attributes;
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
        /* Add cases for opaque driver here */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_sign_hash( &attributes,
                                              slot->data.key.data,
                                              slot->data.key.bytes,
                                              alg,
                                              hash,
                                              hash_length,
                                              signature,
                                              signature_size,
                                              signature_length );
            /* No fallback for opaque */
            return( status );
#endif /* VAULT */

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            return( test_opaque_signature_sign_hash( &attributes,
                                                     slot->data.key.data,
                                                     slot->data.key.bytes,
                                                     alg,
                                                     hash,
                                                     hash_length,
                                                     signature,
                                                     signature_size,
                                                     signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_verify_hash( psa_key_slot_t *slot,
                                             psa_algorithm_t alg,
                                             const uint8_t *hash,
                                             size_t hash_length,
                                             const uint8_t *signature,
                                             size_t signature_length )
{
    (void) slot;
    (void) alg;
    (void) hash;
    (void) hash_length;
    (void) signature;
    (void) signature_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        if( drv->asymmetric == NULL ||
            drv->asymmetric->p_verify == NULL )
        {
            /* Key is defined in SE, but we have no way to exercise it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->asymmetric->p_verify( drv_context,
                                           slot->data.se.slot_number,
                                           alg,
                                           hash, hash_length,
                                           signature, signature_length ) );
    }
#endif /* PSA_CRYPTO_SE_C */

    /* Then try accelerator API */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = test_transparent_signature_verify_hash( &attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             alg,
                                                             hash,
                                                             hash_length,
                                                             signature,
                                                             signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_verify_hash( &attributes,
                                                     slot->data.key.data,
                                                     slot->data.key.bytes,
                                                     alg,
                                                     hash,
                                                     hash_length,
                                                     signature,
                                                     signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_verify_hash( &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg,
                                                            hash,
                                                            hash_length,
                                                            signature,
                                                            signature_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#else
            (void)attributes;
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT*/

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
        /* Add cases for opaque driver here */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_verify_hash( &attributes,
                                                slot->data.key.data,
                                                slot->data.key.bytes,
                                                alg,
                                                hash,
                                                hash_length,
                                                signature,
                                                signature_length );
            /* No fallback for opaque */
            return( status );
#endif /* VAULT */

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            return( test_opaque_signature_verify_hash( &attributes,
                                                       slot->data.key.data,
                                                       slot->data.key.bytes,
                                                       alg,
                                                       hash,
                                                       hash_length,
                                                       signature,
                                                       signature_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#else /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void)slot;
    (void)alg;
    (void)hash;
    (void)hash_length;
    (void)signature;
    (void)signature_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_generate_key( const psa_key_attributes_t *attributes,
                                              psa_key_slot_t *slot )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT)
    /* Try dynamically-registered SE interface first */
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
    const psa_drv_se_t *drv;
    psa_drv_se_context_t *drv_context;

    if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
    {
        size_t pubkey_length = 0; /* We don't support this feature yet */
        if( drv->key_management == NULL ||
            drv->key_management->p_generate == NULL )
        {
            /* Key is defined as being in SE, but we have no way to generate it */
            return( PSA_ERROR_NOT_SUPPORTED );
        }
        return( drv->key_management->p_generate(
            drv_context,
            slot->data.se.slot_number, attributes,
            NULL, 0, &pubkey_length ) );
    }
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */

    /* Then try accelerator API */
#if defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);

    size_t export_size = 0;

    status = get_expected_key_size( attributes, &export_size );
    if( status != PSA_SUCCESS )
        return( status );

    slot->data.key.data = mbedtls_calloc(1, export_size);
    if( slot->data.key.data == NULL )
        return( PSA_ERROR_INSUFFICIENT_MEMORY );
    slot->data.key.bytes = export_size;

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */

            /* Transparent drivers are limited to generating asymmetric keys */
            if( ! PSA_KEY_TYPE_IS_ASYMMETRIC( slot->attr.type ) )
            {
                status = PSA_ERROR_NOT_SUPPORTED;
                break;
            }
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = test_transparent_generate_key( attributes,
                                                    slot->data.key.data,
                                                    slot->data.key.bytes,
                                                    &slot->data.key.bytes );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                break;
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_generate_key( attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      &slot->data.key.bytes );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                break;
#endif /* SEMAILBOX_PRESENT */

#if defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_generate_key( attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             &slot->data.key.bytes );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                break;
#endif /* CRYPTOACC_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            status = PSA_ERROR_NOT_SUPPORTED;
            break;
        /* Add cases for opaque driver here */

#if defined(SEMAILBOX_PRESENT) && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            // Call opaque driver API
            status = sli_se_opaque_generate_key( attributes,
                                                 slot->data.key.data,
                                                 slot->data.key.bytes,
                                                 &slot->data.key.bytes);
            /* No fallback for opaque drivers */
            return status;

#endif /* SEMAILBOX_PRESENT && VAULT*/
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            status = test_opaque_generate_key( attributes,
                                               slot->data.key.data,
                                               slot->data.key.bytes,
                                               &slot->data.key.bytes );
            break;
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            status = PSA_ERROR_INVALID_ARGUMENT;
            break;
    }

    if( status != PSA_SUCCESS )
    {
        /* free allocated buffer */
        mbedtls_free( slot->data.key.data );
        slot->data.key.data = NULL;
        slot->data.key.bytes = 0;
    }

    return( status );
#else /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) attributes;
    (void) slot;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

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
    size_t *output_length )
{
    (void) slot;
    (void) alg;
    (void) input;
    (void) input_length;
    (void) salt;
    (void) salt_length;
    (void) output;
    (void) output_size;
    (void) output_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_asymmetric_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    const uint8_t *salt,
    size_t salt_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
    (void) slot;
    (void) alg;
    (void) input;
    (void) input_length;
    (void) salt;
    (void) salt_length;
    (void) output;
    (void) output_size;
    (void) output_length;
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)

    return( PSA_ERROR_NOT_SUPPORTED );
#else
    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

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
    size_t *ciphertext_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_aead_encrypt( &attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      alg,
                                                      nonce,
                                                      nonce_length,
                                                      additional_data,
                                                      additional_data_length,
                                                      plaintext,
                                                      plaintext_length,
                                                      ciphertext,
                                                      ciphertext_size,
                                                      ciphertext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_aead_encrypt( &attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             alg,
                                                             nonce,
                                                             nonce_length,
                                                             additional_data,
                                                             additional_data_length,
                                                             plaintext,
                                                             plaintext_length,
                                                             ciphertext,
                                                             ciphertext_size,
                                                             ciphertext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTO_PRESENT)
            status = sli_crypto_transparent_aead_encrypt( &attributes,
                                                          slot->data.key.data,
                                                          slot->data.key.bytes,
                                                          alg,
                                                          nonce,
                                                          nonce_length,
                                                          additional_data,
                                                          additional_data_length,
                                                          plaintext,
                                                          plaintext_length,
                                                          ciphertext,
                                                          ciphertext_size,
                                                          ciphertext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#else
            (void)attributes;
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            // We are on a vault device, call opaque driver
            status = sli_se_opaque_aead_encrypt( &attributes,
                                                 slot->data.key.data,
                                                 slot->data.key.bytes,
                                                 alg,
                                                 nonce,
                                                 nonce_length,
                                                 additional_data,
                                                 additional_data_length,
                                                 plaintext,
                                                 plaintext_length,
                                                 ciphertext,
                                                 ciphertext_size,
                                                 ciphertext_length );
            // Cannot have fallback for opaque drivers:
            return status;
#endif // VAULT
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#else
    (void) slot;
    (void) alg;
    (void) nonce;
    (void) nonce_length;
    (void) additional_data;
    (void) additional_data_length;
    (void) plaintext;
    (void) plaintext_length;
    (void) ciphertext;
    (void) ciphertext_size;
    (void) ciphertext_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

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
    size_t *plaintext_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_aead_decrypt( &attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      alg,
                                                      nonce,
                                                      nonce_length,
                                                      additional_data,
                                                      additional_data_length,
                                                      ciphertext,
                                                      ciphertext_length,
                                                      plaintext,
                                                      plaintext_size,
                                                      plaintext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_aead_decrypt( &attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             alg,
                                                             nonce,
                                                             nonce_length,
                                                             additional_data,
                                                             additional_data_length,
                                                             ciphertext,
                                                             ciphertext_length,
                                                             plaintext,
                                                             plaintext_size,
                                                             plaintext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#elif defined(CRYPTO_PRESENT)
            status = sli_crypto_transparent_aead_decrypt( &attributes,
                                                          slot->data.key.data,
                                                          slot->data.key.bytes,
                                                          alg,
                                                          nonce,
                                                          nonce_length,
                                                          additional_data,
                                                          additional_data_length,
                                                          ciphertext,
                                                          ciphertext_length,
                                                          plaintext,
                                                          plaintext_size,
                                                          plaintext_length );
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#else
            (void) attributes;
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            // We are on a vault device, call opaque driver
            status = sli_se_opaque_aead_decrypt( &attributes,
                                                 slot->data.key.data,
                                                 slot->data.key.bytes,
                                                 alg,
                                                 nonce,
                                                 nonce_length,
                                                 additional_data,
                                                 additional_data_length,
                                                 ciphertext,
                                                 ciphertext_length,
                                                 plaintext,
                                                 plaintext_size,
                                                 plaintext_length );
            // Cannot have fallback for opaque drivers:
            return status;
#endif // VAULT
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }
#else
    (void) slot;
    (void) alg;
    (void) nonce;
    (void) nonce_length;
    (void) additional_data;
    (void) additional_data_length;
    (void) ciphertext;
    (void) ciphertext_length;
    (void) plaintext;
    (void) plaintext_size;
    (void) plaintext_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

/*
 * MAC functions
 */
psa_status_t psa_driver_wrapper_mac_sign_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(SEMAILBOX_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_transparent_mac_operation_t ) );
            if ( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_se_transparent_mac_sign_setup( operation->ctx,
                                                        &attributes,
                                                        slot->data.key.data,
                                                        slot->data.key.bytes,
                                                        alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_transparent_mac_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTOACC_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_cryptoacc_transparent_mac_operation_t ) );
            status = sli_cryptoacc_transparent_mac_sign_setup( operation->ctx,
                                                              &attributes,
                                                              slot->data.key.data,
                                                              slot->data.key.bytes,
                                                              alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_cryptoacc_transparent_mac_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTO_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof(sli_crypto_transparent_mac_operation_t) );
            if ( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_crypto_transparent_mac_sign_setup( operation->ctx,
                                                            &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTO_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_crypto_transparent_mac_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#else
            return( PSA_ERROR_NOT_SUPPORTED );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            // We are on a vault device, call opaque driver
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_opaque_mac_operation_t ) );
            if ( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;
            status = sli_se_opaque_mac_sign_setup( operation->ctx,
                                                   &attributes,
                                                   slot->data.key.data,
                                                   slot->data.key.bytes,
                                                   alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_OPAQUE_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_opaque_mac_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            // Cannot have fallback for opaque drivers:
            return status;
#endif // VAULT
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }

#else
    (void) operation;
    (void) slot;
    (void) alg;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_mac_verify_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg )
{
    /* For now there is no driver implementations for the verify setup function
       so call sign setup function instead, which should allow us to perform verify finish
       step by first calculating the mac and checking it against the input mac. */
    return psa_driver_wrapper_mac_sign_setup(operation, slot, alg);
}

psa_status_t psa_driver_wrapper_mac_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return( sli_se_transparent_mac_update( operation->ctx, input, input_length ) );
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return( sli_cryptoacc_transparent_mac_update( operation->ctx, input, input_length ) );
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return( sli_crypto_transparent_mac_update( operation->ctx, input, input_length ) );
#endif /* CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return( sli_se_opaque_mac_update( operation->ctx, input, input_length ) );
#endif // VAULT
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }

#else
    (void) operation;
    (void) input;
    (void) input_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_mac_sign_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *mac,
    size_t mac_size,
    size_t *mac_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return( sli_se_transparent_mac_sign_finish( operation->ctx,
                                                        mac,
                                                        mac_size,
                                                        mac_length ) );
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return( sli_cryptoacc_transparent_mac_sign_finish( operation->ctx,
                                                               mac,
                                                               mac_size,
                                                               mac_length ) );
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return( sli_crypto_transparent_mac_sign_finish( operation->ctx,
                                                            mac,
                                                            mac_size,
                                                            mac_length ) );
#endif /* CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return( sli_se_opaque_mac_sign_finish( operation->ctx,
                                                   mac,
                                                   mac_size,
                                                   mac_length ) );
#endif // VAULT
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
#else
    (void) operation;
    (void) mac;
    (void) mac_size;
    (void) mac_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_mac_abort(
    psa_operation_driver_context_t *operation )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    if( operation->ctx == NULL && operation->id == 0 )
        return( PSA_SUCCESS );

    switch( operation->id )
    {
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            status = sli_se_transparent_mac_abort( operation->ctx );
            break;
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            status = sli_cryptoacc_transparent_mac_abort( operation->ctx );
            break;
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            status = sli_crypto_transparent_mac_abort( operation->ctx );
            break;
#endif /* CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            status = sli_se_transparent_mac_abort( operation->ctx );
            break;
#endif // VAULT
        default:
            /* Operation is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
    mbedtls_free( operation->ctx );
    operation->ctx = NULL;
    operation->id = 0;
    return( status );
#else
    (void) operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT && PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT */
}

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
    size_t *output_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = test_transparent_cipher_encrypt( &attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      alg,
                                                      input,
                                                      input_length,
                                                      output,
                                                      output_size,
                                                      output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_cipher_encrypt( &attributes,
                                                       slot->data.key.data,
                                                       slot->data.key.bytes,
                                                       alg,
                                                       input,
                                                       input_length,
                                                       output,
                                                       output_size,
                                                       output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* SEMAILBOX_PRESENT */

#if defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_cipher_encrypt( &attributes,
                                                              slot->data.key.data,
                                                              slot->data.key.bytes,
                                                              alg,
                                                              input,
                                                              input_length,
                                                              output,
                                                              output_size,
                                                              output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* CRYPTOACC_PRESENT */

#if defined(CRYPTO_PRESENT)
            status = sli_crypto_transparent_cipher_encrypt( &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg,
                                                            input,
                                                            input_length,
                                                            output,
                                                            output_size,
                                                            output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* CRYPTO_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
        /* Add cases for opaque driver here */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_cipher_encrypt( &attributes,
                                                    slot->data.key.data,
                                                    slot->data.key.bytes,
                                                    alg,
                                                    input,
                                                    input_length,
                                                    output,
                                                    output_size,
                                                    output_length );
            /* No fallback for opaque drivers */
            return( status );
#endif /* SEMAILBOX_PRESENT && VAULT*/

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            return( test_opaque_cipher_encrypt( &attributes,
                                                slot->data.key.data,
                                                slot->data.key.bytes,
                                                alg,
                                                input,
                                                input_length,
                                                output,
                                                output_size,
                                                output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) slot;
    (void) alg;
    (void) input;
    (void) input_length;
    (void) output;
    (void) output_size;
    (void) output_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_decrypt(
    psa_key_slot_t *slot,
    psa_algorithm_t alg,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            status = test_transparent_cipher_decrypt( &attributes,
                                                      slot->data.key.data,
                                                      slot->data.key.bytes,
                                                      alg,
                                                      input,
                                                      input_length,
                                                      output,
                                                      output_size,
                                                      output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            status = sli_se_transparent_cipher_decrypt( &attributes,
                                                       slot->data.key.data,
                                                       slot->data.key.bytes,
                                                       alg,
                                                       input,
                                                       input_length,
                                                       output,
                                                       output_size,
                                                       output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* SEMAILBOX_PRESENT */

#if defined(CRYPTOACC_PRESENT)
            status = sli_cryptoacc_transparent_cipher_decrypt( &attributes,
                                                              slot->data.key.data,
                                                              slot->data.key.bytes,
                                                              alg,
                                                              input,
                                                              input_length,
                                                              output,
                                                              output_size,
                                                              output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* CRYPTOACC_PRESENT */

#if defined(CRYPTO_PRESENT)
            status = sli_crypto_transparent_cipher_decrypt( &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg,
                                                            input,
                                                            input_length,
                                                            output,
                                                            output_size,
                                                            output_length );
            /* Declared with fallback == true */
            if( status != PSA_ERROR_NOT_SUPPORTED )
                return( status );
#endif /* CRYPTO_PRESENT */

            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
        /* Add cases for opaque driver here */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            status = sli_se_opaque_cipher_decrypt( &attributes,
                                                   slot->data.key.data,
                                                   slot->data.key.bytes,
                                                   alg,
                                                   input,
                                                   input_length,
                                                   output,
                                                   output_size,
                                                   output_length );
            /* No fallback for opaque drivers */
            return( status );
#endif /* SEMAILBOX_PRESENT && VAULT */

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            return( test_opaque_cipher_decrypt( &attributes,
                                                slot->data.key.data,
                                                slot->data.key.bytes,
                                                alg,
                                                input,
                                                input_length,
                                                output,
                                                output_size,
                                                output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( status );
    }

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) slot;
    (void) alg;
    (void) input;
    (void) input_length;
    (void) output;
    (void) output_size;
    (void) output_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_encrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            operation->ctx = mbedtls_calloc( 1, sizeof( test_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = test_transparent_cipher_encrypt_setup( operation->ctx,
                                                            &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( test_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_se_transparent_cipher_encrypt_setup( operation->ctx,
                                                             &attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTOACC_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_cryptoacc_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_cryptoacc_transparent_cipher_encrypt_setup( operation->ctx,
                                                                    &attributes,
                                                                    slot->data.key.data,
                                                                    slot->data.key.bytes,
                                                                    alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_cryptoacc_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTO_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof(sli_crypto_transparent_cipher_operation_t) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_crypto_transparent_cipher_encrypt_setup( operation->ctx,
                                                                  &attributes,
                                                                  slot->data.key.data,
                                                                  slot->data.key.bytes,
                                                                  alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTO_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_crypto_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#else
            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_opaque_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_se_opaque_cipher_encrypt_setup( operation->ctx,
                                                         &attributes,
                                                         slot->data.key.data,
                                                         slot->data.key.bytes,
                                                         alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_OPAQUE_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_opaque_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }
            /* No fallback for opaque drivers */
            return( status );
#endif /* SEMAILBOX_PRESENT && VAULT */

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            operation->ctx = mbedtls_calloc( 1, sizeof(test_opaque_cipher_operation_t) );
            if( operation->ctx == NULL )
                return( PSA_ERROR_INSUFFICIENT_MEMORY );

            status = test_opaque_cipher_encrypt_setup( operation->ctx,
                                                       &attributes,
                                                       slot->data.key.data,
                                                       slot->data.key.bytes,
                                                       alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( test_opaque_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( PSA_ERROR_NOT_SUPPORTED );
    }

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) slot;
    (void) alg;
    (void) operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_decrypt_setup(
    psa_operation_driver_context_t *operation,
    psa_key_slot_t *slot,
    psa_algorithm_t alg )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;
    psa_key_location_t location = PSA_KEY_LIFETIME_GET_LOCATION(slot->attr.lifetime);
    psa_key_attributes_t attributes = {
      .core = slot->attr
    };

    switch( location )
    {
        case PSA_KEY_LOCATION_LOCAL_STORAGE:
            /* Key is stored in the slot in export representation, so
             * cycle through all known transparent accelerators */
#if defined(PSA_CRYPTO_DRIVER_TEST)
            operation->ctx = mbedtls_calloc( 1, sizeof( test_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return( PSA_ERROR_INSUFFICIENT_MEMORY );

            status = test_transparent_cipher_decrypt_setup( operation->ctx,
                                                            &attributes,
                                                            slot->data.key.data,
                                                            slot->data.key.bytes,
                                                            alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( test_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */

#if defined(SEMAILBOX_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_se_transparent_cipher_decrypt_setup( operation->ctx,
                                                             &attributes,
                                                             slot->data.key.data,
                                                             slot->data.key.bytes,
                                                             alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTOACC_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_cryptoacc_transparent_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_cryptoacc_transparent_cipher_decrypt_setup( operation->ctx,
                                                                     &attributes,
                                                                     slot->data.key.data,
                                                                     slot->data.key.bytes,
                                                                     alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_cryptoacc_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#elif defined(CRYPTO_PRESENT)
            operation->ctx = mbedtls_calloc( 1, sizeof(sli_crypto_transparent_cipher_operation_t) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_crypto_transparent_cipher_decrypt_setup( operation->ctx,
                                                                  &attributes,
                                                                  slot->data.key.data,
                                                                  slot->data.key.bytes,
                                                                  alg );
            /* Declared with fallback == true */
            if( status == PSA_SUCCESS )
                operation->id = SLI_CRYPTO_TRANSPARENT_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_crypto_transparent_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#else
            /* Fell through, meaning no accelerator supports this operation */
            return( PSA_ERROR_NOT_SUPPORTED );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */

#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case PSA_KEY_LOCATION_SLI_SE_OPAQUE:
            operation->ctx = mbedtls_calloc( 1, sizeof( sli_se_opaque_cipher_operation_t ) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = sli_se_opaque_cipher_decrypt_setup( operation->ctx,
                                                         &attributes,
                                                         slot->data.key.data,
                                                         slot->data.key.bytes,
                                                         alg );
            if( status == PSA_SUCCESS )
                operation->id = SLI_SE_OPAQUE_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( sli_se_opaque_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }
            /* No fallback for opaque drivers */
            return( status );
#endif /* SEMAILBOX_PRESENT && VAULT */

#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TEST_DRIVER_LIFETIME:
            operation->ctx = mbedtls_calloc( 1, sizeof(test_opaque_cipher_operation_t) );
            if( operation->ctx == NULL )
                return PSA_ERROR_INSUFFICIENT_MEMORY;

            status = test_opaque_cipher_decrypt_setup( operation->ctx,
                                                       &attributes,
                                                       slot->data.key.data,
                                                       slot->data.key.bytes,
                                                       alg );
            if( status == PSA_SUCCESS )
                operation->id = PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID;
            else
            {
                mbedtls_platform_zeroize(
                    operation->ctx,
                    sizeof( test_opaque_cipher_operation_t ) );
                mbedtls_free( operation->ctx );
                operation->ctx = NULL;
            }

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
        default:
            /* Key is declared with a lifetime not known to us */
            return( PSA_ERROR_NOT_SUPPORTED );
    }

#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) slot;
    (void) alg;
    (void) operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_generate_iv(
    psa_operation_driver_context_t *operation,
    uint8_t *iv,
    size_t iv_size,
    size_t *iv_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID:
            return( test_transparent_cipher_generate_iv( operation->ctx,
                                                         iv,
                                                         iv_size,
                                                         iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID:
            return( test_opaque_cipher_generate_iv( operation->ctx,
                                                    iv,
                                                    iv_size,
                                                    iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return ( sli_se_transparent_cipher_generate_iv( operation->ctx,
                                                           iv,
                                                           iv_size,
                                                           iv_length) );

#elif defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return ( sli_cryptoacc_transparent_cipher_generate_iv( operation->ctx,
                                                                  iv,
                                                                  iv_size,
                                                                  iv_length) );

#elif defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return ( sli_crypto_transparent_cipher_generate_iv( operation->ctx,
                                                                iv,
                                                                iv_size,
                                                                iv_length) );

#else
            return( PSA_ERROR_BAD_STATE );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return ( sli_se_opaque_cipher_generate_iv( operation->ctx,
                                                       iv,
                                                       iv_size,
                                                       iv_length) );
#endif /* SEMAILBOX_PRESENT && VAULT */


        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) operation;
    (void) iv;
    (void) iv_size;
    (void) iv_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_set_iv(
    psa_operation_driver_context_t *operation,
    const uint8_t *iv,
    size_t iv_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID:
            return( test_transparent_cipher_set_iv( operation->ctx,
                                                    iv,
                                                    iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID:
            return( test_opaque_cipher_set_iv( operation->ctx,
                                               iv,
                                               iv_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return ( sli_se_transparent_cipher_set_iv( operation->ctx,
                                                      iv,
                                                      iv_length) );

#elif defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return ( sli_cryptoacc_transparent_cipher_set_iv( operation->ctx,
                                                             iv,
                                                             iv_length) );

#elif defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return ( sli_crypto_transparent_cipher_set_iv( operation->ctx,
                                                           iv,
                                                           iv_length) );

#else
            return( PSA_ERROR_BAD_STATE );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return ( sli_se_opaque_cipher_set_iv( operation->ctx,
                                                  iv,
                                                  iv_length) );
#endif /* SEMAILBOX_PRESENT && VAULT */
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) operation;
    (void) iv;
    (void) iv_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_update(
    psa_operation_driver_context_t *operation,
    const uint8_t *input,
    size_t input_length,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID:
            return( test_transparent_cipher_update( operation->ctx,
                                                    input,
                                                    input_length,
                                                    output,
                                                    output_size,
                                                    output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID:
            return( test_opaque_cipher_update( operation->ctx,
                                               input,
                                               input_length,
                                               output,
                                               output_size,
                                               output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return ( sli_se_transparent_cipher_update( operation->ctx,
                                                      input,
                                                      input_length,
                                                      output,
                                                      output_size,
                                                      output_length ) );

#elif defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return ( sli_cryptoacc_transparent_cipher_update( operation->ctx,
                                                             input,
                                                             input_length,
                                                             output,
                                                             output_size,
                                                             output_length ) );

#elif defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return ( sli_crypto_transparent_cipher_update( operation->ctx,
                                                           input,
                                                           input_length,
                                                           output,
                                                           output_size,
                                                           output_length ) );

#else
            return( PSA_ERROR_BAD_STATE );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return ( sli_se_opaque_cipher_update( operation->ctx,
                                                  input,
                                                  input_length,
                                                  output,
                                                  output_size,
                                                  output_length ) );
#endif /* SEMAILBOX_PRESENT && VAULT */
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) operation;
    (void) input;
    (void) input_length;
    (void) output;
    (void) output_length;
    (void) output_size;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_finish(
    psa_operation_driver_context_t *operation,
    uint8_t *output,
    size_t output_size,
    size_t *output_length )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    switch( operation->id )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID:
            return( test_transparent_cipher_finish( operation->ctx,
                                                    output,
                                                    output_size,
                                                    output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID:
            return( test_opaque_cipher_finish( operation->ctx,
                                               output,
                                               output_size,
                                               output_length ) );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            return ( sli_se_transparent_cipher_finish( operation->ctx,
                                                      output,
                                                      output_size,
                                                      output_length ) );
#elif defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            return ( sli_cryptoacc_transparent_cipher_finish( operation->ctx,
                                                             output,
                                                             output_size,
                                                             output_length ) );
#elif defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            return ( sli_crypto_transparent_cipher_finish( operation->ctx,
                                                           output,
                                                           output_size,
                                                           output_length ) );
#else
            return( PSA_ERROR_BAD_STATE );
#endif /* SEMAILBOX_PRESENT CRYPTOACC_PRESENT CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            return ( sli_se_opaque_cipher_finish( operation->ctx,
                                                  output,
                                                  output_size,
                                                  output_length ) );
#endif /* SEMAILBOX_PRESENT && VAULT */
        default:
            /* Key is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) operation;
    (void) output;
    (void) output_size;
    (void) output_length;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

psa_status_t psa_driver_wrapper_cipher_abort(
    psa_operation_driver_context_t *operation )
{
#if defined(PSA_CRYPTO_DRIVER_PRESENT) && defined(PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT)
    psa_status_t status = PSA_ERROR_INVALID_ARGUMENT;

    /* The object has (apparently) been initialized but it is not in use. It's
     * ok to call abort on such an object, and there's nothing to do. */
    if( operation->ctx == NULL && operation->id == 0 )
        return( PSA_SUCCESS );

    switch( operation->id )
    {
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_TRANSPARENT_TEST_DRIVER_ID:
            status = test_transparent_cipher_abort( operation->ctx );
            operation->ctx = NULL;
            operation->id = 0;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(PSA_CRYPTO_DRIVER_TEST)
        case PSA_CRYPTO_OPAQUE_TEST_DRIVER_ID:
            status = test_opaque_cipher_abort( operation->ctx );
            operation->ctx = NULL;
            operation->id = 0;

            return( status );
#endif /* PSA_CRYPTO_DRIVER_TEST */
#if defined(SEMAILBOX_PRESENT)
        case SLI_SE_TRANSPARENT_DRIVER_ID:
            status = sli_se_transparent_cipher_abort( operation->ctx );
            break;
#endif /* SEMAILBOX_PRESENT */
#if defined(CRYPTOACC_PRESENT)
        case SLI_CRYPTOACC_TRANSPARENT_DRIVER_ID:
            status = sli_cryptoacc_transparent_cipher_abort( operation->ctx );
            break;
#endif /* CRYPTOACC_PRESENT */
#if defined(CRYPTO_PRESENT)
        case SLI_CRYPTO_TRANSPARENT_DRIVER_ID:
            status = sli_crypto_transparent_cipher_abort( operation->ctx );
            break;
#endif /* CRYPTO_PRESENT */
#if defined(SEMAILBOX_PRESENT) && \
  ( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT) || \
    defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) )
        case SLI_SE_OPAQUE_DRIVER_ID:
            status = sli_se_opaque_cipher_abort( operation->ctx );
            break;
#endif /* SEMAILBOX_PRESENT && VAULT */
        default:
            /* Operation is attached to a driver not known to us */
            return( PSA_ERROR_BAD_STATE );
    }
    mbedtls_free( operation->ctx );
    operation->ctx = NULL;
    operation->id = 0;

    return ( status );
#else /* PSA_CRYPTO_DRIVER_PRESENT */
    (void) operation;

    return( PSA_ERROR_NOT_SUPPORTED );
#endif /* PSA_CRYPTO_DRIVER_PRESENT */
}

/* End of automatically generated file. */
