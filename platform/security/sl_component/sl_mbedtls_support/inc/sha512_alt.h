/*******************************************************************************
 * @file
 * @brief Accelerated mbed TLS SHA-384 and SHA-512 cryptographic hash functions
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
#ifndef SHA512_ALT_H
#define SHA512_ALT_H

/*******************************************************************************
 * \addtogroup sl_crypto
 * \{
 ******************************************************************************/

/*******************************************************************************
 * \addtogroup sl_crypto_sha512 Accelerated SHA-384/SHA-512 Hash Function
 * \brief Accelerated mbed TLS SHA-384/SHA-512 cryptographic hash function for
 *        the mbed TLS API using Silicon Labs peripherals. This implementation
 *        builds on the PSA Crypto drivers (\ref sl_psa_drivers).
 *
 * \{
 ******************************************************************************/

#if defined(MBEDTLS_SHA512_ALT)

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#include "sli_se_transparent_types.h"
#define SL_HASH_OPERATION_CTX_TYPE sli_se_transparent_hash_operation_t
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          SHA-512 context structure
 */
typedef SL_HASH_OPERATION_CTX_TYPE mbedtls_sha512_context;

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_SHA512_ALT */

/** \} (end addtogroup sl_crypto_sha512) */
/** \} (end addtogroup sl_crypto) */

#endif /* SHA512_ALT_H */
