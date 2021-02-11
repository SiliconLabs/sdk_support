/***************************************************************************//**
 * @file
 * @brief PSA ITS implementation based on Silicon Labs NVM3
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

// -------------------------------------
// Includes

#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#else
#include "mbedtls/config.h"
#endif

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && !defined(MBEDTLS_PSA_ITS_FILE_C)

#include "psa/internal_trusted_storage.h"

#include "nvm3_default.h"

#include <stdbool.h>
#include <string.h>

// -------------------------------------
// Defines

#define SL_ITS_META_MAGIC_V1    (0x05E175D1UL)

#define SL_ITS_NVM3_RANGE_BASE  (0x83100UL)
#define SL_ITS_NVM3_RANGE_SIZE  (0x00080UL)

#ifndef SL_ITS_MAX_FILES
#define SL_ITS_MAX_FILES        SL_ITS_NVM3_RANGE_SIZE
#endif

#define SL_ITS_NVM3_RANGE_START SL_ITS_NVM3_RANGE_BASE
#define SL_ITS_NVM3_RANGE_END   SL_ITS_NVM3_RANGE_START + SL_ITS_MAX_FILES

#define SL_ITS_MAX_KEY_SIZE     (256)

#define SL_ITS_NVM3_INVALID_KEY (0)
#define SL_ITS_NVM3_UNKNOWN_KEY (1)

#if SL_ITS_MAX_FILES > SL_ITS_NVM3_RANGE_SIZE
#error "Trying to store more ITS files then our NVM3 range allows for"
#endif

#define SL_ITS_CACHE_INIT_CHUNK_SIZE 16

// -------------------------------------
// Local global static variables

static bool nvm3_uid_set_cache_initialized = false;
static uint32_t nvm3_uid_set_cache[(SL_ITS_MAX_FILES + 31) / 32] = { 0 };

typedef struct {
  psa_storage_uid_t uid;
  nvm3_ObjectKey_t object_id;
  bool set;
} previous_lookup_t;

static previous_lookup_t previous_lookup = {
  0, 0, false
};

// -------------------------------------
// Structs

typedef struct {
  uint32_t magic;
  psa_storage_uid_t uid;
  psa_storage_create_flags_t flags;
} sl_its_file_meta_t;

// -------------------------------------
// Local function prototypes

static nvm3_ObjectKey_t get_nvm3_id(psa_storage_uid_t uid, bool find_empty_slot);
static nvm3_ObjectKey_t prepare_its_get_nvm3_id(psa_storage_uid_t uid);

// -------------------------------------
// Local function definitions

static inline void cache_set(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SL_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  nvm3_uid_set_cache[bin] |= (1 << offset);
}

static inline void cache_clear(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SL_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  nvm3_uid_set_cache[bin] ^= (1 << offset);
}

static inline bool cache_lookup(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SL_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  return (bool)(nvm3_uid_set_cache[bin] >> offset);
}

static void init_cache()
{
  size_t num_keys_referenced_by_nvm3;
  nvm3_ObjectKey_t keys_referenced_by_nvm3[SL_ITS_CACHE_INIT_CHUNK_SIZE];

  for (nvm3_ObjectKey_t range_start = SL_ITS_NVM3_RANGE_START; range_start < SL_ITS_NVM3_RANGE_END; range_start += SL_ITS_CACHE_INIT_CHUNK_SIZE) {
    nvm3_ObjectKey_t range_end = range_start + SL_ITS_CACHE_INIT_CHUNK_SIZE;
    if (range_end > SL_ITS_NVM3_RANGE_END) {
      range_end = SL_ITS_NVM3_RANGE_END;
    }

    num_keys_referenced_by_nvm3 = nvm3_enumObjects(nvm3_defaultHandle,
                                                   keys_referenced_by_nvm3,
                                                   sizeof(keys_referenced_by_nvm3) / sizeof(nvm3_ObjectKey_t),
                                                   range_start,
                                                   range_end);

    for (size_t i = 0; i < num_keys_referenced_by_nvm3; i++) {
      cache_set(keys_referenced_by_nvm3[i]);
    }
  }

  nvm3_uid_set_cache_initialized = true;
}

// Search through NVM3 for uid
static nvm3_ObjectKey_t get_nvm3_id(psa_storage_uid_t uid, bool find_empty_slot)
{
  Ecode_t status;
  sl_its_file_meta_t key_meta;

  if (find_empty_slot) {
    for (size_t i = 0; i < SL_ITS_MAX_FILES; i++) {
      if (!cache_lookup(i + SL_ITS_NVM3_RANGE_START)) {
        return i + SL_ITS_NVM3_RANGE_START;
      }
    }
  } else {
    if (previous_lookup.set) {
      if (previous_lookup.uid == uid) {
        return previous_lookup.object_id;
      }
    }

    for (size_t i = 0; i < SL_ITS_MAX_FILES; i++) {
      if (!cache_lookup(i + SL_ITS_NVM3_RANGE_START)) {
        continue;
      }
      nvm3_ObjectKey_t object_id = i + SL_ITS_NVM3_RANGE_START;

      status = nvm3_readPartialData(nvm3_defaultHandle, object_id, &key_meta, 0, sizeof(sl_its_file_meta_t));

      if (status != ECODE_NVM3_OK) {
        continue;
      }

      // ensure that the buffer stores an PSA ITS UID
      if (key_meta.magic != SL_ITS_META_MAGIC_V1) {
        // we don't expect any other data in our range then PSA ITS files.
        // delete the file if the magic doesn't match
        status = nvm3_deleteObject(nvm3_defaultHandle, object_id);
        if (status != ECODE_NVM3_OK) {
          return SL_ITS_NVM3_RANGE_END + 1U;
        }
        continue;
      }

      if (key_meta.uid == uid) {
        previous_lookup.set = true;
        previous_lookup.object_id = object_id;
        previous_lookup.uid = uid;

        return object_id;
      }
    }
  }

  return SL_ITS_NVM3_RANGE_END + 1U;
}

// Perform NVM3 open and fill the look-up table.
// Try to find the mapping NVM3 object ID with PSA ITS UID.
static nvm3_ObjectKey_t prepare_its_get_nvm3_id(psa_storage_uid_t uid)
{
  if (nvm3_initDefault() != ECODE_NVM3_OK) {
    return SL_ITS_NVM3_RANGE_END + 1U;
  }

  if (nvm3_uid_set_cache_initialized == false) {
    init_cache();
  }

  return get_nvm3_id(uid, false);
}

// -------------------------------------
// Global function definitions

/**
 * \brief create a new or modify an existing uid/value pair
 *
 * \param[in] uid           the identifier for the data
 * \param[in] data_length   The size in bytes of the data in `p_data`
 * \param[in] p_data        A buffer containing the data
 * \param[in] create_flags  The flags that the data will be stored with
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_NOT_PERMITTED          The operation failed because the provided `uid` value was already created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_NOT_SUPPORTED          The operation failed because one or more of the flags provided in `create_flags` is not supported or is not valid
 * \retval      PSA_ERROR_INSUFFICIENT_STORAGE   The operation failed because there was insufficient space on the storage medium
 * \retval      PSA_ERROR_STORAGE_FAILURE        The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one of the provided pointers(`p_data`)
 *                                               is invalid, for example is `NULL` or references memory the caller cannot access
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,
                         uint32_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags)
{
  if (data_length > SL_ITS_MAX_KEY_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if ((data_length != 0U) && (p_data == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (create_flags != PSA_STORAGE_FLAG_WRITE_ONCE
      && create_flags != PSA_STORAGE_FLAG_NONE) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);

  Ecode_t status;
  nvm3_ObjectKey_t empty_key_slot;
  sl_its_file_meta_t* its_file_meta;
  uint8_t key_buffer[SL_ITS_MAX_KEY_SIZE + sizeof(sl_its_file_meta_t)] = { 0 };

  if (nvm3_object_id > SL_ITS_NVM3_RANGE_END) {
    // ITS UID was not found.
    empty_key_slot = get_nvm3_id(0ULL, true);

    if (empty_key_slot > SL_ITS_NVM3_RANGE_END) {
      // The storage is full.
      return PSA_ERROR_INSUFFICIENT_STORAGE;
    }

    its_file_meta = (sl_its_file_meta_t *)key_buffer;
    its_file_meta->uid = uid;
    its_file_meta->flags = create_flags;
    its_file_meta->magic = SL_ITS_META_MAGIC_V1;

    if (data_length != 0U) {
      memcpy((uint8_t*)key_buffer + sizeof(sl_its_file_meta_t), ((uint8_t*)p_data), data_length);
    }

    status = nvm3_writeData(nvm3_defaultHandle,
                            empty_key_slot,
                            key_buffer,
                            data_length + sizeof(sl_its_file_meta_t));

    if (status == ECODE_NVM3_OK) {
      // Power-loss might occur, however upon boot, the look-up table will be
      // re-filled as long as the data has been successfully written to NVM3.
      cache_set(empty_key_slot);
      return PSA_SUCCESS;
    } else {
      return PSA_ERROR_STORAGE_FAILURE;
    }
  }

  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, key_buffer, 0, sizeof(sl_its_file_meta_t));

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  its_file_meta = (sl_its_file_meta_t *)key_buffer;
  if (its_file_meta->magic != SL_ITS_META_MAGIC_V1) {
    // un-expected error at this point it should read an ITS object.
    return PSA_ERROR_STORAGE_FAILURE;
  }

  if (its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE) {
    return PSA_ERROR_NOT_PERMITTED;
  }

  its_file_meta->flags = create_flags;
  if (data_length != 0U) {
    memmove((uint8_t*)key_buffer + sizeof(sl_its_file_meta_t), ((uint8_t*)p_data), data_length);
  }
  status = nvm3_writeData(nvm3_defaultHandle,
                          nvm3_object_id,
                          key_buffer,
                          data_length + sizeof(sl_its_file_meta_t));

  if (status == ECODE_NVM3_OK) {
    return PSA_SUCCESS;
  } else {
    return PSA_ERROR_STORAGE_FAILURE;
  }
}

/**
 * \brief Retrieve the value associated with a provided uid
 *
 * \param[in] uid               The uid value
 * \param[in] data_offset       The starting offset of the data requested
 * \param[in] data_length       the amount of data requested (and the minimum allocated size of the `p_data` buffer)
 * \param[out] p_data           The buffer where the data will be placed upon successful completion
 * \param[out] p_data_length    The amount of data returned in the p_data buffer
 *
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided `uid` value was not found in the storage
 * \retval      PSA_ERROR_BUFFER_TOO_SMALL   The operation failed because the data associated with provided uid is larger than `data_size`
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_data`, `p_data_length`)
 *                                           is invalid. For example is `NULL` or references memory the caller cannot access.
 *                                           In addition, this can also happen if an invalid offset was provided.
 */
psa_status_t psa_its_get(psa_storage_uid_t uid,
                         uint32_t data_offset,
                         uint32_t data_length,
                         void *p_data,
                         size_t *p_data_length)
{
  if (data_length > SL_ITS_MAX_KEY_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if ((data_length != 0U) && (p_data_length == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (data_length != 0U) {
    // If the request amount of data is 0, allow invalid pointer of the output buffer.
    if ((p_data == NULL)
        || ((uint32_t)p_data < SRAM_BASE)
        || ((uint32_t)p_data > (SRAM_BASE + SRAM_SIZE - data_length))) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SL_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_t its_file_meta;
  size_t key_obj_size;

  status = nvm3_getObjectInfo(nvm3_defaultHandle, nvm3_object_id, NVM3_OBJECTTYPE_DATA, &key_obj_size);
  status += nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, &its_file_meta, 0, sizeof(sl_its_file_meta_t));
  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  if (key_obj_size < sizeof(sl_its_file_meta_t)) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  key_obj_size = key_obj_size - sizeof(sl_its_file_meta_t);
  if (data_length != 0U) {
    if ((data_offset >= key_obj_size) && (key_obj_size != 0U)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ((key_obj_size == 0U) && (data_offset != 0U)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  } else {
    // Allow the offset at the data size boundary if the requested amount of data is zero.
    if (data_offset > key_obj_size) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

  if (data_length > (key_obj_size - data_offset)) {
    *p_data_length = key_obj_size - data_offset;
  } else {
    *p_data_length = data_length;
  }

  // Ensure that the buffer stores an PSA ITS UID
  if (its_file_meta.magic != SL_ITS_META_MAGIC_V1) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  status += nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, p_data, sizeof(sl_its_file_meta_t) + data_offset, *p_data_length);

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  return PSA_SUCCESS;
}

/**
 * \brief Retrieve the metadata about the provided uid
 *
 * \param[in] uid           The uid value
 * \param[out] p_info       A pointer to the `psa_storage_info_t` struct that will be populated with the metadata
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided uid value was not found in the storage
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_info`)
 *                                           is invalid, for example is `NULL` or references memory the caller cannot access
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info)
{
  if (p_info == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SL_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_t its_file_meta;
  size_t key_obj_size;

  status = nvm3_getObjectInfo(nvm3_defaultHandle, nvm3_object_id, NVM3_OBJECTTYPE_DATA, &key_obj_size);
  status += nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, &its_file_meta, 0, sizeof(sl_its_file_meta_t));

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  // ensure that the buffer stores an PSA ITS UID
  if (its_file_meta.magic != SL_ITS_META_MAGIC_V1) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  p_info->flags = its_file_meta.flags;
  p_info->size = key_obj_size - sizeof(sl_its_file_meta_t);
  return PSA_SUCCESS;
}

/**
 * \brief Remove the provided key and its associated data from the storage
 *
 * \param[in] uid   The uid value
 *
 * \return  A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided key value was not found in the storage
 * \retval      PSA_ERROR_NOT_PERMITTED      The operation failed because the provided key value was created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 */
psa_status_t psa_its_remove(psa_storage_uid_t uid)
{
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SL_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_t its_file_meta;

  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, &its_file_meta, 0, sizeof(sl_its_file_meta_t));

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  // ensure that the buffer stores an PSA ITS UID
  if (its_file_meta.magic != SL_ITS_META_MAGIC_V1) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE) {
    return PSA_ERROR_NOT_PERMITTED;
  }

  status = nvm3_deleteObject(nvm3_defaultHandle, nvm3_object_id);

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    if (previous_lookup.set && previous_lookup.uid == uid) {
      previous_lookup.set = false;
    }
    cache_clear(nvm3_object_id);

    return PSA_SUCCESS;
  } else {
    return PSA_ERROR_STORAGE_FAILURE;
  }
}

#endif // MBEDTLS_PSA_CRYPTO_STORAGE_C && !MBEDTLS_PSA_ITS_FILE_C
