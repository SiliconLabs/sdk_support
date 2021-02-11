/***************************************************************************//**
 * @file
 * @brief Accelerated mbed TLS SHA-1 cryptographic hash function
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
#ifndef SHA1_ALT_H
#define SHA1_ALT_H

/***************************************************************************//**
 * \addtogroup sl_crypto
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_crypto_sha1 Accelerated SHA-1 Hash Function
 * \brief Accelerated mbed TLS SHA-1 cryptographic hash function for the mbed
 *        TLS API using Silicon Labs peripherals. This implementation builds on
 *        the PSA Crypto drivers (\ref sl_psa_drivers).
 *
 * \{
 ******************************************************************************/

#if defined(MBEDTLS_SHA1_ALT)

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#include "sli_se_transparent_types.h"
#define SL_HASH_OPERATION_CTX_TYPE sli_se_transparent_hash_operation_t
#elif defined(CRYPTO_PRESENT)
#include "sli_crypto_transparent_types.h"
#define SL_HASH_OPERATION_CTX_TYPE sli_crypto_transparent_hash_operation_t
#elif defined(CRYPTOACC_PRESENT)
#include "sli_cryptoacc_transparent_types.h"
#define SL_HASH_OPERATION_CTX_TYPE sli_cryptoacc_transparent_hash_operation_t
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SHA-1 context structure
 */
typedef SL_HASH_OPERATION_CTX_TYPE mbedtls_sha1_context;

/**
 * \brief          Initialize SHA-1 context
 *
 * \param ctx      SHA-1 context to be initialized
 */
void mbedtls_sha1_init(mbedtls_sha1_context *ctx);

/**
 * \brief          Clear SHA-1 context
 *
 * \param ctx      SHA-1 context to be cleared
 */
void mbedtls_sha1_free(mbedtls_sha1_context *ctx);

/**
 * \brief          Clone (the state of) a SHA-1 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void mbedtls_sha1_clone(mbedtls_sha1_context *dst,
                        const mbedtls_sha1_context *src);

/**
 * \brief          SHA-1 context setup
 *
 * \param ctx      context to be initialized
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha1_starts_ret(mbedtls_sha1_context *ctx);

/**
 * \brief          SHA-1 process buffer
 *
 * \param ctx      SHA-1 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha1_update_ret(mbedtls_sha1_context *ctx, const unsigned char *input, size_t ilen);

/**
 * \brief          SHA-1 final digest
 *
 * \param ctx      SHA-1 context
 * \param output   SHA-1 checksum result
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha1_finish_ret(mbedtls_sha1_context *ctx, unsigned char output[20]);

/**
 * \brief          SHA-1 process data block (internal use only)
 *
 * \param ctx      SHA-1 context
 * \param data     The data block being processed.
 *
 * \return         \c 0 if successful
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
int mbedtls_internal_sha1_process(mbedtls_sha1_context *ctx,
                                  const unsigned char data[64]);

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief          SHA-1 context setup
 *
 * \deprecated     Superseded by mbedtls_sha1_starts_ret() in 2.7.0
 *
 * \param ctx      The SHA-1 context to be initialized.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_starts(mbedtls_sha1_context *ctx);

/**
 * \brief          SHA-1 process buffer
 *
 * \deprecated     Superseded by mbedtls_sha1_update_ret() in 2.7.0
 *
 * \param ctx      The SHA-1 context.
 * \param input    The buffer holding the input data.
 * \param ilen     The length of the input data.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_update(mbedtls_sha1_context *ctx,
                                            const unsigned char *input,
                                            size_t ilen);

/**
 * \brief          SHA-1 final digest
 *
 * \deprecated     Superseded by mbedtls_sha1_finish_ret() in 2.7.0
 *
 * \param ctx      The SHA-1 context.
 * \param output   The SHA-1 checksum result.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_finish(mbedtls_sha1_context *ctx,
                                            unsigned char output[20]);

/**
 * \brief          SHA-1 process data block (internal use only)
 *
 * \deprecated     Superseded by mbedtls_internal_sha1_process() in 2.7.0
 *
 * \param ctx      The SHA-1 context.
 * \param data     The data block being processed.
 *
 * \warning        SHA-1 is considered a weak message digest and its use
 *                 constitutes a security risk. We recommend considering
 *                 stronger message digests instead.
 *
 */
MBEDTLS_DEPRECATED void mbedtls_sha1_process(mbedtls_sha1_context *ctx,
                                             const unsigned char data[64]);

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#ifdef __cplusplus
}
#endif

#endif /* #if defined(MBEDTLS_SHA1_ALT) */

/** \} (end addtogroup sl_crypto_sha1) */
/** \} (end addtogroup sl_crypto) */

#endif /* SHA1_ALT_H */
