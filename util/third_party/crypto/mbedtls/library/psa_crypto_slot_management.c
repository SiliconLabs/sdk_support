/*
 *  PSA crypto layer on top of Mbed TLS crypto
 */
/*
 *  Copyright The Mbed TLS Contributors
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

#include "common.h"

#if defined(MBEDTLS_PSA_CRYPTO_C)

#include "psa_crypto_service_integration.h"
#include "psa/crypto.h"

#include "psa_crypto_core.h"
#include "psa_crypto_slot_management.h"
#include "psa_crypto_storage.h"
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
#include "psa_crypto_se.h"
#endif

#include <stdlib.h>
#include <string.h>
#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#define mbedtls_calloc calloc
#define mbedtls_free   free
#endif

#define ARRAY_LENGTH( array ) ( sizeof( array ) / sizeof( *( array ) ) )

typedef struct
{
    psa_key_slot_t key_slots[PSA_KEY_SLOT_COUNT];
    unsigned key_slots_initialized : 1;
} psa_global_data_t;

static psa_global_data_t global_data;

/* Access a key slot at the given handle. The handle of a key slot is
 * the index of the slot in the global slot array, plus one so that handles
 * start at 1 and not 0. */
psa_status_t psa_get_key_slot( psa_key_handle_t handle,
                               psa_key_slot_t **p_slot )
{
    psa_key_slot_t *slot = NULL;

    if( ! global_data.key_slots_initialized )
        return( PSA_ERROR_BAD_STATE );

    /* 0 is not a valid handle under any circumstance. This
     * implementation provides slots number 1 to N where N is the
     * number of available slots. */
    if( handle == 0 || handle > ARRAY_LENGTH( global_data.key_slots ) )
        return( PSA_ERROR_INVALID_HANDLE );
    slot = &global_data.key_slots[handle - 1];

    /* If the slot isn't occupied, the handle is invalid. */
    if( ! psa_is_key_slot_occupied( slot ) )
        return( PSA_ERROR_INVALID_HANDLE );

    *p_slot = slot;
    return( PSA_SUCCESS );
}

psa_status_t psa_initialize_key_slots( void )
{
    /* Nothing to do: program startup and psa_wipe_all_key_slots() both
     * guarantee that the key slots are initialized to all-zero, which
     * means that all the key slots are in a valid, empty state. */
    global_data.key_slots_initialized = 1;
    return( PSA_SUCCESS );
}

void psa_wipe_all_key_slots( void )
{
    psa_key_handle_t key;
    for( key = 1; key <= PSA_KEY_SLOT_COUNT; key++ )
    {
        psa_key_slot_t *slot = &global_data.key_slots[key - 1];
        (void) psa_wipe_key_slot( slot );
    }
    global_data.key_slots_initialized = 0;
}

psa_status_t psa_get_empty_key_slot( psa_key_handle_t *handle,
                                             psa_key_slot_t **p_slot )
{
    if( ! global_data.key_slots_initialized )
        return( PSA_ERROR_BAD_STATE );

    for( *handle = PSA_KEY_SLOT_COUNT; *handle != 0; --( *handle ) )
    {
        *p_slot = &global_data.key_slots[*handle - 1];
        if( ! psa_is_key_slot_occupied( *p_slot ) )
            return( PSA_SUCCESS );
    }
    *p_slot = NULL;
    return( PSA_ERROR_INSUFFICIENT_MEMORY );
}

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C)
static psa_status_t psa_load_persistent_key_into_slot( psa_key_slot_t *slot )
{
    psa_status_t status = PSA_SUCCESS;
    uint8_t *key_data = NULL;
    size_t key_data_length = 0;

    status = psa_load_persistent_key( &slot->attr,
                                      &key_data, &key_data_length );
    if( status != PSA_SUCCESS )
        goto exit;

    if( psa_key_lifetime_is_external( slot->attr.lifetime ) )
    {
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
        const psa_drv_se_t *drv;
        psa_drv_se_context_t *drv_context;
        if( psa_get_se_driver( slot->attr.lifetime, &drv, &drv_context ) )
        {
            psa_se_key_data_storage_t *data;
            if( key_data_length != sizeof( *data ) )
            {
                status = PSA_ERROR_STORAGE_FAILURE;
                goto exit;
            }
            data = (psa_se_key_data_storage_t *) key_data;
            memcpy( &slot->data.se.slot_number, &data->slot_number,
                    sizeof( slot->data.se.slot_number ) );
        }
        else
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */
        {
            if ( key_data == NULL )
            {
                status = PSA_ERROR_STORAGE_FAILURE;
                goto exit;
            }

            status = psa_copy_key_material_into_slot( slot, key_data, key_data_length );
        }
    }
    else
    {
        status = psa_copy_key_material_into_slot( slot, key_data, key_data_length );
    }

exit:
    psa_free_persistent_key_data( key_data, key_data_length );
    return( status );
}
#endif /* defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) */

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
/** Check whether a key identifier is acceptable.
 *
 * For backward compatibility, key identifiers that were valid in a
 * past released version must remain valid, unless a migration path
 * is provided.
 *
 * \param key        The key identifier to check.
 * \param vendor_ok  Nonzero to allow key ids in the vendor range.
 *                   0 to allow only key ids in the application range.
 *
 * \return           1 if \p key is acceptable, otherwise 0.
 */
static int psa_is_key_id_valid( mbedtls_svc_key_id_t key, int vendor_ok )
{
    psa_key_id_t key_id = MBEDTLS_SVC_KEY_ID_GET_KEY_ID( key );
    if( PSA_KEY_ID_USER_MIN <= key_id && key_id <= PSA_KEY_ID_USER_MAX )
        return( 1 );
    else if( vendor_ok &&
             PSA_KEY_ID_VENDOR_MIN <= key_id &&
             key_id <= PSA_KEY_ID_VENDOR_MAX )
        return( 1 );
    else
        return( 0 );
}
#endif /* defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) */

psa_status_t psa_validate_key_location( psa_key_lifetime_t lifetime,
                                        psa_se_drv_table_entry_t **p_drv )
{
    if ( psa_key_lifetime_is_external( lifetime ) )
    {
#if defined(MBEDTLS_PSA_CRYPTO_SE_C)
        psa_se_drv_table_entry_t *driver = psa_get_se_driver_entry( lifetime );
        if( driver == NULL )
            return( PSA_SUCCESS );
        else
        {
            if (p_drv != NULL)
                *p_drv = driver;
            return( PSA_SUCCESS );
        }
#else
        (void) p_drv;
        return( PSA_SUCCESS );
#endif /* MBEDTLS_PSA_CRYPTO_SE_C */
    }
    else
        /* Local/internal keys are always valid */
        return( PSA_SUCCESS );
}

psa_status_t psa_validate_key_persistence( psa_key_lifetime_t lifetime,
                                           mbedtls_svc_key_id_t key )
{
    if ( PSA_KEY_LIFETIME_IS_VOLATILE( lifetime ) )
    {
        /* Volatile keys are always supported */
        return( PSA_SUCCESS );
    }
    else
    {
        /* Persistent keys require storage support */
#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C)
        if( psa_is_key_id_valid( key,
                                 psa_key_lifetime_is_external( lifetime ) ) )
            return( PSA_SUCCESS );
        else
            return( PSA_ERROR_INVALID_ARGUMENT );
#else /* MBEDTLS_PSA_CRYPTO_STORAGE_C */
        (void) key;
        return( PSA_ERROR_NOT_SUPPORTED );
#endif /* !MBEDTLS_PSA_CRYPTO_STORAGE_C */
    }
}

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
static psa_status_t get_builtin_key( psa_key_id_t key_id,
                                     psa_key_slot_t *slot )
{
    if( ! ( key_id >= MBEDTLS_PSA_KEY_ID_BUILTIN_MIN &&
            key_id <= MBEDTLS_PSA_KEY_ID_BUILTIN_MAX ) )
    {
        return( PSA_ERROR_DOES_NOT_EXIST );
    }

    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_set_key_id( &attributes, key_id );
    psa_status_t status =
        mbedtls_psa_platform_get_builtin_key( &attributes,
                                              &slot->data.key.data,
                                              &slot->data.key.bytes );
    if( status != PSA_SUCCESS )
    {
        slot->data.key.data = NULL;
        slot->data.key.bytes = 0;
        return( status );
    }

    slot->attr = attributes.core;
    return( PSA_SUCCESS );
}
#endif /* MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS */

psa_status_t psa_open_key( mbedtls_svc_key_id_t key, psa_key_handle_t *handle )
{
    psa_status_t status = PSA_ERROR_NOT_SUPPORTED;
    *handle = 0;

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    if( ! psa_is_key_id_valid( key, 1 ) )
        return( PSA_ERROR_INVALID_ARGUMENT );

    psa_key_slot_t *slot;
    status = psa_get_empty_key_slot( handle, &slot );
    if( status != PSA_SUCCESS )
        return( status );

#if defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS)
    status = get_builtin_key( MBEDTLS_SVC_KEY_ID_GET_KEY_ID( key ), slot );
    if( status != PSA_ERROR_DOES_NOT_EXIST )
        goto exit;
#endif

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C)
    slot->attr.lifetime = PSA_KEY_LIFETIME_PERSISTENT;
    slot->attr.id = key;

    status = psa_load_persistent_key_into_slot( slot );
    if( status != PSA_ERROR_DOES_NOT_EXIST )
        goto exit;
#endif

exit:
    if( status != PSA_SUCCESS )
    {
        psa_wipe_key_slot( slot );
        *handle = 0;
    }
#else /* defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) */
    (void) key;
#endif /* !( defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) || defined(MBEDTLS_PSA_CRYPTO_BUILTIN_KEYS) ) */
    return( status );
}

psa_status_t psa_close_key( psa_key_handle_t handle )
{
    psa_status_t status;
    psa_key_slot_t *slot;

    if( handle == 0 )
        return( PSA_SUCCESS );

    status = psa_get_key_slot( handle, &slot );
    if( status != PSA_SUCCESS )
        return( status );

    return( psa_wipe_key_slot( slot ) );
}

void mbedtls_psa_get_stats( mbedtls_psa_stats_t *stats )
{
    psa_key_handle_t key;
    memset( stats, 0, sizeof( *stats ) );
    for( key = 1; key <= PSA_KEY_SLOT_COUNT; key++ )
    {
        const psa_key_slot_t *slot = &global_data.key_slots[key - 1];
        if( ! psa_is_key_slot_occupied( slot ) )
        {
            ++stats->empty_slots;
            continue;
        }
        if( slot->attr.lifetime == PSA_KEY_LIFETIME_VOLATILE )
            ++stats->volatile_slots;
        else if( slot->attr.lifetime == PSA_KEY_LIFETIME_PERSISTENT )
        {
            psa_key_id_t id = MBEDTLS_SVC_KEY_ID_GET_KEY_ID( slot->attr.id );
            ++stats->persistent_slots;
            if( id > stats->max_open_internal_key_id )
                stats->max_open_internal_key_id = id;
        }
        else
        {
            psa_key_id_t id = MBEDTLS_SVC_KEY_ID_GET_KEY_ID( slot->attr.id );
            ++stats->external_slots;
            if( id > stats->max_open_external_key_id )
                stats->max_open_external_key_id = id;
        }
    }
}

#endif /* MBEDTLS_PSA_CRYPTO_C */
