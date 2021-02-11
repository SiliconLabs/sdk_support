/***************************************************************************//**
 * @file
 * @brief Accelerated mbed TLS SHA-224 and SHA-256 cryptographic hash functions
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
#ifndef SHA256_ALT_H
#define SHA256_ALT_H

/***************************************************************************//**
 * \addtogroup sl_crypto
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_crypto_sha256 Accelerated SHA-224/SHA-256 Hash Function
 * \brief Accelerated mbed TLS SHA-224/SHA-256 cryptographic hash functions for
 *        the mbed TLS API using Silicon Labs peripherals. This implementation
 *        builds on the PSA Crypto drivers (\ref sl_psa_drivers).
 *
 * \{
 ******************************************************************************/

#if defined(MBEDTLS_SHA256_ALT)

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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SHA-256 context structure
 */
typedef SL_HASH_OPERATION_CTX_TYPE mbedtls_sha256_context;

/**
 * \brief          Initialize SHA-256 context
 *
 * \param ctx      SHA-256 context to be initialized
 */
void mbedtls_sha256_init(mbedtls_sha256_context *ctx);

/**
 * \brief          Clear SHA-256 context
 *
 * \param ctx      SHA-256 context to be cleared
 */
void mbedtls_sha256_free(mbedtls_sha256_context *ctx);

/**
 * \brief          Clone (the state of) a SHA-256 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void mbedtls_sha256_clone(mbedtls_sha256_context *dst,
                          const mbedtls_sha256_context *src);

/**
 * \brief          SHA-256 context setup
 *
 * \param ctx      context to be initialized
 * \param is224    0 = use SHA256, 1 = use SHA224
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha256_starts_ret(mbedtls_sha256_context *ctx, int is224);

/**
 * \brief          SHA-256 process buffer
 *
 * \param ctx      SHA-256 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha256_update_ret(mbedtls_sha256_context *ctx, const unsigned char *input, size_t ilen);

/**
 * \brief          SHA-256 final digest
 *
 * \param ctx      SHA-256 context
 * \param output   SHA-224/256 checksum result
 *
 * \return         \c 0 if successful
 *
 */
int mbedtls_sha256_finish_ret(mbedtls_sha256_context *ctx, unsigned char output[32]);

/**
 * \brief          This function processes a single data block within
 *                 the ongoing SHA-256 computation. This function is for
 *                 internal use only.
 *
 * \param ctx      The SHA-256 context.
 * \param data     The buffer holding one block of data.
 *
 * \return         \c 0 on success.
 */
int mbedtls_internal_sha256_process(mbedtls_sha256_context *ctx,
                                    const unsigned char data[64]);

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
#if defined(MBEDTLS_DEPRECATED_WARNING)
#define MBEDTLS_DEPRECATED      __attribute__((deprecated))
#else
#define MBEDTLS_DEPRECATED
#endif
/**
 * \brief          This function starts a SHA-256 checksum calculation.
 *
 * \deprecated     Superseded by mbedtls_sha256_starts_ret() in 2.7.0.
 *
 * \param ctx      The SHA-256 context to initialize.
 * \param is224    Determines which function to use.
 *                 <ul><li>0: Use SHA-256.</li>
 *                 <li>1: Use SHA-224.</li></ul>
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_starts(mbedtls_sha256_context *ctx,
                                              int is224);

/**
 * \brief          This function feeds an input buffer into an ongoing
 *                 SHA-256 checksum calculation.
 *
 * \deprecated     Superseded by mbedtls_sha256_update_ret() in 2.7.0.
 *
 * \param ctx      The SHA-256 context to initialize.
 * \param input    The buffer holding the data.
 * \param ilen     The length of the input data.
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_update(mbedtls_sha256_context *ctx,
                                              const unsigned char *input,
                                              size_t ilen);

/**
 * \brief          This function finishes the SHA-256 operation, and writes
 *                 the result to the output buffer.
 *
 * \deprecated     Superseded by mbedtls_sha256_finish_ret() in 2.7.0.
 *
 * \param ctx      The SHA-256 context.
 * \param output   The SHA-224or SHA-256 checksum result.
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_finish(mbedtls_sha256_context *ctx,
                                              unsigned char output[32]);

/**
 * \brief          This function processes a single data block within
 *                 the ongoing SHA-256 computation. This function is for
 *                 internal use only.
 *
 * \deprecated     Superseded by mbedtls_internal_sha256_process() in 2.7.0.
 *
 * \param ctx      The SHA-256 context.
 * \param data     The buffer holding one block of data.
 */
MBEDTLS_DEPRECATED void mbedtls_sha256_process(mbedtls_sha256_context *ctx,
                                               const unsigned char data[64]);

#undef MBEDTLS_DEPRECATED
#endif /* !MBEDTLS_DEPRECATED_REMOVED */

#ifdef __cplusplus
}
#endif

#endif /* #if defined(MBEDTLS_SHA256_ALT) */

/** \} (end addtogroup sl_crypto_sha256) */
/** \} (end addtogroup sl_crypto) */

#endif /* SHA256_ALT_H */
