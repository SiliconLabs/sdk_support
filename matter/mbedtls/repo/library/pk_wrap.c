/*
 *  Public Key abstraction layer: wrapper functions
 *
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

/*
 *  Copyright (C) 2017 by Intel Corporation, All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *	- Redistributions of source code must retain the above copyright notice,
 *	 this list of conditions and the following disclaimer.
 *
 *	- Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 *	- Neither the name of Intel Corporation nor the names of its contributors
 *	may be used to endorse or promote products derived from this software
 *	without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#include "common.h"

#if defined(MBEDTLS_PK_C)
#include "mbedtls/pk_internal.h"
#include "mbedtls/error.h"

/* Even if RSA not activated, for the sake of RSA-alt */
#include "mbedtls/rsa.h"

#include <string.h>

#if defined(MBEDTLS_ECP_C)
#include "mbedtls/ecp.h"
#endif

#if defined(MBEDTLS_ECDSA_C)
#include "mbedtls/ecdsa.h"
#endif

#if defined(TINYCRYPT_PRIMITIVES)
#include "ecc.h"
#include "ecc_dsa.h"
#include "mbedtls/asn1.h"
#include "mbedtls/asn1write.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/platform.h"
#include "mbedtls/pk.h"

#if !defined(MBEDTLS_PLATFORM_C)
#include <stdlib.h>
#define mbedtls_calloc    calloc
#define mbedtls_free       free
#endif

#endif /* TINYCRYPT_PRIMITIVES */

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "mbedtls/asn1write.h"
#endif

#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
#include "mbedtls/platform_util.h"
#endif

#if defined(MBEDTLS_USE_PSA_CRYPTO)
#include "psa/crypto.h"
#include "mbedtls/psa_util.h"
#include "mbedtls/asn1.h"
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#define mbedtls_calloc    calloc
#define mbedtls_free       free
#endif

#include <limits.h>
#include <stdint.h>

#if defined(MBEDTLS_RSA_C)
static int rsa_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_RSA ||
            type == MBEDTLS_PK_RSASSA_PSS );
}

static size_t rsa_get_bitlen( const void *ctx )
{
    const mbedtls_rsa_context * rsa = (const mbedtls_rsa_context *) ctx;
    return( 8 * mbedtls_rsa_get_len( rsa ) );
}

static int rsa_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   const unsigned char *sig, size_t sig_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx;
    size_t rsa_len = mbedtls_rsa_get_len( rsa );

#if SIZE_MAX > UINT_MAX
    if( md_alg == MBEDTLS_MD_NONE && UINT_MAX < hash_len )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* SIZE_MAX > UINT_MAX */

    if( sig_len < rsa_len )
        return( MBEDTLS_ERR_RSA_VERIFY_FAILED );

    if( ( ret = mbedtls_rsa_pkcs1_verify( rsa, NULL, NULL,
                                  MBEDTLS_RSA_PUBLIC, md_alg,
                                  (unsigned int) hash_len, hash, sig ) ) != 0 )
        return( ret );

    /* The buffer contains a valid signature followed by extra data.
     * We have a special error code for that so that so that callers can
     * use mbedtls_pk_verify() to check "Does the buffer start with a
     * valid signature?" and not just "Does the buffer contain a valid
     * signature?". */
    if( sig_len > rsa_len )
        return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

    return( 0 );
}

static int rsa_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx;

#if SIZE_MAX > UINT_MAX
    if( md_alg == MBEDTLS_MD_NONE && UINT_MAX < hash_len )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* SIZE_MAX > UINT_MAX */

    *sig_len = mbedtls_rsa_get_len( rsa );

    return( mbedtls_rsa_pkcs1_sign( rsa, f_rng, p_rng, MBEDTLS_RSA_PRIVATE,
                md_alg, (unsigned int) hash_len, hash, sig ) );
}

static int rsa_decrypt_wrap( void *ctx,
                    const unsigned char *input, size_t ilen,
                    unsigned char *output, size_t *olen, size_t osize,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx;

    if( ilen != mbedtls_rsa_get_len( rsa ) )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    return( mbedtls_rsa_pkcs1_decrypt( rsa, f_rng, p_rng,
                MBEDTLS_RSA_PRIVATE, olen, input, output, osize ) );
}

static int rsa_encrypt_wrap( void *ctx,
                    const unsigned char *input, size_t ilen,
                    unsigned char *output, size_t *olen, size_t osize,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_context * rsa = (mbedtls_rsa_context *) ctx;
    *olen = mbedtls_rsa_get_len( rsa );

    if( *olen > osize )
        return( MBEDTLS_ERR_RSA_OUTPUT_TOO_LARGE );

    return( mbedtls_rsa_pkcs1_encrypt( rsa, f_rng, p_rng, MBEDTLS_RSA_PUBLIC,
                                       ilen, input, output ) );
}

static int rsa_check_pair_wrap( const void *pub, const void *prv )
{
    return( mbedtls_rsa_check_pub_priv( (const mbedtls_rsa_context *) pub,
                                (const mbedtls_rsa_context *) prv ) );
}

static void *rsa_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_rsa_context ) );

    if( ctx != NULL )
        mbedtls_rsa_init( (mbedtls_rsa_context *) ctx, 0, 0 );

    return( ctx );
}

static void rsa_free_wrap( void *ctx )
{
    mbedtls_rsa_free( (mbedtls_rsa_context *) ctx );
    mbedtls_free( ctx );
}

static void rsa_debug( const void *ctx, mbedtls_pk_debug_item *items )
{
    items->type = MBEDTLS_PK_DEBUG_MPI;
    items->name = "rsa.N";
    items->value = &( ((mbedtls_rsa_context *) ctx)->N );

    items++;

    items->type = MBEDTLS_PK_DEBUG_MPI;
    items->name = "rsa.E";
    items->value = &( ((mbedtls_rsa_context *) ctx)->E );
}

const mbedtls_pk_info_t mbedtls_rsa_info = {
    MBEDTLS_PK_RSA,
    "RSA",
    rsa_get_bitlen,
    rsa_can_do,
    rsa_verify_wrap,
    rsa_sign_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    rsa_decrypt_wrap,
    rsa_encrypt_wrap,
    rsa_check_pair_wrap,
    rsa_alloc_wrap,
    rsa_free_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    rsa_debug,
};
#endif /* MBEDTLS_RSA_C */

#if defined(MBEDTLS_ECP_C)
/*
 * Generic EC key
 */
static int eckey_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_ECKEY ||
            type == MBEDTLS_PK_ECKEY_DH ||
            type == MBEDTLS_PK_ECDSA );
}

static size_t eckey_get_bitlen( const void *ctx )
{
    return( ((mbedtls_ecp_keypair *) ctx)->grp.pbits );
}

#if defined(MBEDTLS_ECDSA_C)
/* Forward declarations */
static int ecdsa_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len );

static int ecdsa_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng );

static int eckey_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_ecdsa_context ecdsa;

    mbedtls_ecdsa_init( &ecdsa );

    if( ( ret = mbedtls_ecdsa_from_keypair( &ecdsa, ctx ) ) == 0 )
        ret = ecdsa_verify_wrap( &ecdsa, md_alg, hash, hash_len, sig, sig_len );

    mbedtls_ecdsa_free( &ecdsa );

    return( ret );
}

static int eckey_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_ecdsa_context ecdsa;

    mbedtls_ecdsa_init( &ecdsa );

    if( ( ret = mbedtls_ecdsa_from_keypair( &ecdsa, ctx ) ) == 0 )
        ret = ecdsa_sign_wrap( &ecdsa, md_alg, hash, hash_len, sig, sig_len,
                               f_rng, p_rng );

    mbedtls_ecdsa_free( &ecdsa );

    return( ret );
}

#if defined(MBEDTLS_ECP_RESTARTABLE)
/* Forward declarations */
static int ecdsa_verify_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len,
                       void *rs_ctx );

static int ecdsa_sign_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                   void *rs_ctx );

/*
 * Restart context for ECDSA operations with ECKEY context
 *
 * We need to store an actual ECDSA context, as we need to pass the same to
 * the underlying ecdsa function, so we can't create it on the fly every time.
 */
typedef struct
{
    mbedtls_ecdsa_restart_ctx ecdsa_rs;
    mbedtls_ecdsa_context ecdsa_ctx;
} eckey_restart_ctx;

static void *eckey_rs_alloc( void )
{
    eckey_restart_ctx *rs_ctx;

    void *ctx = mbedtls_calloc( 1, sizeof( eckey_restart_ctx ) );

    if( ctx != NULL )
    {
        rs_ctx = ctx;
        mbedtls_ecdsa_restart_init( &rs_ctx->ecdsa_rs );
        mbedtls_ecdsa_init( &rs_ctx->ecdsa_ctx );
    }

    return( ctx );
}

static void eckey_rs_free( void *ctx )
{
    eckey_restart_ctx *rs_ctx;

    if( ctx == NULL)
        return;

    rs_ctx = ctx;
    mbedtls_ecdsa_restart_free( &rs_ctx->ecdsa_rs );
    mbedtls_ecdsa_free( &rs_ctx->ecdsa_ctx );

    mbedtls_free( ctx );
}

static int eckey_verify_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len,
                       void *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    eckey_restart_ctx *rs = rs_ctx;

    /* Should never happen */
    if( rs == NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    /* set up our own sub-context if needed (that is, on first run) */
    if( rs->ecdsa_ctx.grp.pbits == 0 )
        MBEDTLS_MPI_CHK( mbedtls_ecdsa_from_keypair( &rs->ecdsa_ctx, ctx ) );

    MBEDTLS_MPI_CHK( ecdsa_verify_rs_wrap( &rs->ecdsa_ctx,
                                           md_alg, hash, hash_len,
                                           sig, sig_len, &rs->ecdsa_rs ) );

cleanup:
    return( ret );
}

static int eckey_sign_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                       void *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    eckey_restart_ctx *rs = rs_ctx;

    /* Should never happen */
    if( rs == NULL )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    /* set up our own sub-context if needed (that is, on first run) */
    if( rs->ecdsa_ctx.grp.pbits == 0 )
        MBEDTLS_MPI_CHK( mbedtls_ecdsa_from_keypair( &rs->ecdsa_ctx, ctx ) );

    MBEDTLS_MPI_CHK( ecdsa_sign_rs_wrap( &rs->ecdsa_ctx, md_alg,
                                         hash, hash_len, sig, sig_len,
                                         f_rng, p_rng, &rs->ecdsa_rs ) );

cleanup:
    return( ret );
}
#endif /* MBEDTLS_ECP_RESTARTABLE */
#endif /* MBEDTLS_ECDSA_C */

/*
 * Internal wrappers around ECC functions - based on TinyCrypt
 */
#if defined(TINYCRYPT_PRIMITIVES)
/*
 * An ASN.1 encoded signature is a sequence of two ASN.1 integers. Parse one of
 * those integers and convert it to the fixed-length encoding.
 */
static int extract_ecdsa_sig_int( unsigned char **from, const unsigned char *end,
                                  unsigned char *to, size_t to_len )
{
    int ret;
    size_t unpadded_len, padding_len;

    if( ( ret = mbedtls_asn1_get_tag( from, end, &unpadded_len,
                                      MBEDTLS_ASN1_INTEGER ) ) != 0 )
    {
        return( ret );
    }

    while( unpadded_len > 0 && **from == 0x00 )
    {
        ( *from )++;
        unpadded_len--;
    }

    if( unpadded_len > to_len || unpadded_len == 0 )
        return( MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    padding_len = to_len - unpadded_len;
    memset( to, 0x00, padding_len );
    mbedtls_platform_memcpy( to + padding_len, *from, unpadded_len );
    ( *from ) += unpadded_len;

    return( 0 );
}

/*
 * Convert a signature from an ASN.1 sequence of two integers
 * to a raw {r,s} buffer. Note: the provided sig buffer must be at least
 * twice as big as int_size.
 */
static int extract_ecdsa_sig( unsigned char **p, const unsigned char *end,
                              unsigned char *sig, size_t int_size )
{
    int ret;
    size_t tmp_size;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &tmp_size,
                MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( ret );

    /* Extract r */
    if( ( ret = extract_ecdsa_sig_int( p, end, sig, int_size ) ) != 0 )
        return( ret );
    /* Extract s */
    if( ( ret = extract_ecdsa_sig_int( p, end, sig + int_size, int_size ) ) != 0 )
        return( ret );

    return( 0 );
}

static size_t uecc_eckey_get_bitlen( const void *ctx )
{
    (void) ctx;
    return( (size_t) ( NUM_ECC_BYTES * 8 ) );
}

/* This function compares public keys of two keypairs */
static int uecc_eckey_check_pair( const void *pub, const void *prv )
{
    const mbedtls_uecc_keypair *uecc_pub =
        (const mbedtls_uecc_keypair *) pub;
    const mbedtls_uecc_keypair *uecc_prv =
        (const mbedtls_uecc_keypair *) prv;

    if( mbedtls_platform_memequal( uecc_pub->public_key,
                uecc_prv->public_key,
                2 * NUM_ECC_BYTES ) == 0 )
    {
        return( 0 );
    }

    return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
}

static int uecc_eckey_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_ECDSA ||
            type == MBEDTLS_PK_ECKEY );
}

static int uecc_eckey_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    int ret = MBEDTLS_ERR_PLATFORM_FAULT_DETECTED;
    volatile int ret_fi = UECC_FAULT_DETECTED;
    uint8_t signature[2*NUM_ECC_BYTES];
    unsigned char *p;
    const mbedtls_uecc_keypair *keypair = (const mbedtls_uecc_keypair *) ctx;

    ((void) md_alg);
    p = (unsigned char*) sig;

    ret = extract_ecdsa_sig( &p, sig + sig_len, signature, NUM_ECC_BYTES );
    if( ret != 0 )
        return( ret );

    ret_fi = uECC_verify( keypair->public_key, hash,
                          (unsigned) hash_len, signature );

    if( ret_fi == UECC_FAULT_DETECTED )
        return( MBEDTLS_ERR_PLATFORM_FAULT_DETECTED );

    if( ret_fi == UECC_SUCCESS )
    {
        mbedtls_platform_random_delay();
        if( ret_fi == UECC_SUCCESS )
            return( 0 );
        else
            return( MBEDTLS_ERR_PLATFORM_FAULT_DETECTED );
    }

    return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );
}

/*
 * Simultaneously convert and move raw MPI from the beginning of a buffer
 * to an ASN.1 MPI at the end of the buffer.
 * See also mbedtls_asn1_write_mpi().
 *
 * p: pointer to the end of the output buffer
 * start: start of the output buffer, and also of the mpi to write at the end
 * n_len: length of the mpi to read from start
 *
 * Warning:
 * The total length of the output buffer must be smaller than 128 Bytes.
 */
static int asn1_write_mpibuf( unsigned char **p, unsigned char *start,
                              size_t n_len )
{
    size_t len = n_len;
    int ret = MBEDTLS_ERR_PLATFORM_FAULT_DETECTED;

    if( (size_t)( *p - start ) < len )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    *p -= len;
    ret = mbedtls_platform_memmove( *p, start, len );
    if( ret != 0 )
    {
        return( ret );
    }

    /* ASN.1 DER encoding requires minimal length, so skip leading 0s.
     * Neither r nor s should be 0, but as a failsafe measure, still detect
     * that rather than overflowing the buffer in case of an error. */
    while( len > 0 && **p == 0x00 )
    {
        ++(*p);
        --len;
    }

    /* this is only reached if the signature was invalid */
    if( len == 0 )
        return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );

    /* if the msb is 1, ASN.1 requires that we prepend a 0.
     * Neither r nor s can be 0, so we can assume len > 0 at all times. */
    if( **p & 0x80 )
    {
        if( *p - start < 1 )
            return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

        *--(*p) = 0x00;
        len += 1;
    }

    /* Ensure that there is still space for len and ASN1_INTEGER */
    if( ( *p - start ) < 2 )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    /* The ASN.1 length encoding is just a single Byte containing the length,
     * as we assume that the total buffer length is smaller than 128 Bytes. */
    *--(*p) = len;
    *--(*p) = MBEDTLS_ASN1_INTEGER;
    len += 2;

    return( (int) len );
}

/* Transcode signature from uECC format to ASN.1 sequence.
 * See ecdsa_signature_to_asn1 in ecdsa.c, but with byte buffers instead of
 * MPIs, and in-place.
 *
 * [in/out] sig: the signature pre- and post-transcoding
 * [in/out] sig_len: signature length pre- and post-transcoding
 * [in] buf_len: the available size the in/out buffer
 *
 * Warning: buf_len must be smaller than 128 Bytes.
 */
static int pk_ecdsa_sig_asn1_from_uecc( unsigned char *sig, size_t *sig_len,
                                        size_t buf_len )
{
    int ret = MBEDTLS_ERR_PLATFORM_FAULT_DETECTED;
    size_t len = 0;
    const size_t rs_len = *sig_len / 2;
    unsigned char *p = sig + buf_len;

    MBEDTLS_ASN1_CHK_ADD( len, asn1_write_mpibuf( &p, sig + rs_len, rs_len ) );
    MBEDTLS_ASN1_CHK_ADD( len, asn1_write_mpibuf( &p, sig, rs_len ) );

    if( p - sig < 2 )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    /* The ASN.1 length encoding is just a single Byte containing the length,
     * as we assume that the total buffer length is smaller than 128 Bytes. */
    *--p = len;
    *--p = MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE;
    len += 2;

    ret = mbedtls_platform_memmove( sig, p, len );
    if( ret != 0 )
    {
        return( ret );
    }
    *sig_len = len;

    return( ret );
}

static int uecc_eckey_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    const mbedtls_uecc_keypair *keypair = (const mbedtls_uecc_keypair *) ctx;
    int ret;

    /*
     * RFC-4492 page 20:
     *
     *     Ecdsa-Sig-Value ::= SEQUENCE {
     *         r       INTEGER,
     *         s       INTEGER
     *     }
     *
     * Size is at most
     *    1 (tag) + 1 (len) + 1 (initial 0) + NUM_ECC_BYTES for each of r and s,
     *    twice that + 1 (tag) + 2 (len) for the sequence
     *
     * (The ASN.1 length encodings are all 1-Byte encodings because
     *  the total size is smaller than 128 Bytes).
     */
     #define MAX_SECP256R1_ECDSA_SIG_LEN ( 3 + 2 * ( 3 + NUM_ECC_BYTES ) )

    ret = uECC_sign( keypair->private_key, hash, hash_len, sig );
    if( ret == UECC_FAULT_DETECTED )
        return( MBEDTLS_ERR_PLATFORM_FAULT_DETECTED );
    if( ret != UECC_SUCCESS )
        return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );

    *sig_len = 2 * NUM_ECC_BYTES;

    /* uECC owns its rng function pointer */
    (void) f_rng;
    (void) p_rng;
    (void) md_alg;

    return( pk_ecdsa_sig_asn1_from_uecc( sig, sig_len,
                                         MAX_SECP256R1_ECDSA_SIG_LEN ) );

    #undef MAX_SECP256R1_ECDSA_SIG_LEN
}
static void *uecc_eckey_alloc_wrap( void )
{
    return( mbedtls_calloc( 1, sizeof( mbedtls_uecc_keypair ) ) );
}

static void uecc_eckey_free_wrap( void *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_platform_zeroize( ctx, sizeof( mbedtls_uecc_keypair ) );
    mbedtls_free( ctx );
}
#endif /* TINYCRYPT_PRIMITIVES */

static int eckey_check_pair( const void *pub, const void *prv )
{
    return( mbedtls_ecp_check_pub_priv( (const mbedtls_ecp_keypair *) pub,
                                (const mbedtls_ecp_keypair *) prv ) );
}

static void *eckey_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_ecp_keypair ) );

    if( ctx != NULL )
        mbedtls_ecp_keypair_init( ctx );

    return( ctx );
}

static void eckey_free_wrap( void *ctx )
{
    mbedtls_ecp_keypair_free( (mbedtls_ecp_keypair *) ctx );
    mbedtls_free( ctx );
}

static void eckey_debug( const void *ctx, mbedtls_pk_debug_item *items )
{
    items->type = MBEDTLS_PK_DEBUG_ECP;
    items->name = "eckey.Q";
    items->value = &( ((mbedtls_ecp_keypair *) ctx)->Q );
}

const mbedtls_pk_info_t mbedtls_eckey_info = {
    MBEDTLS_PK_ECKEY,
    "EC",
    eckey_get_bitlen,
    eckey_can_do,
#if defined(MBEDTLS_ECDSA_C)
    eckey_verify_wrap,
    eckey_sign_wrap,
#if defined(MBEDTLS_ECP_RESTARTABLE)
    eckey_verify_rs_wrap,
    eckey_sign_rs_wrap,
#endif
#else /* MBEDTLS_ECDSA_C */
    NULL,
    NULL,
#endif /* MBEDTLS_ECDSA_C */
    NULL,
    NULL,
    eckey_check_pair,
    eckey_alloc_wrap,
    eckey_free_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    eckey_rs_alloc,
    eckey_rs_free,
#endif
    eckey_debug,
};

/*
 * EC key restricted to ECDH
 */
static int eckeydh_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_ECKEY ||
            type == MBEDTLS_PK_ECKEY_DH );
}

const mbedtls_pk_info_t mbedtls_eckeydh_info = {
    MBEDTLS_PK_ECKEY_DH,
    "EC_DH",
    eckey_get_bitlen,         /* Same underlying key structure */
    eckeydh_can_do,
    NULL,
    NULL,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    NULL,
    NULL,
    eckey_check_pair,
    eckey_alloc_wrap,       /* Same underlying key structure */
    eckey_free_wrap,        /* Same underlying key structure */
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    eckey_debug,            /* Same underlying key structure */
};
#endif /* MBEDTLS_ECP_C */

#if defined(MBEDTLS_ECDSA_C)
static int ecdsa_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_ECDSA );
}

#if defined(MBEDTLS_USE_PSA_CRYPTO)
/*
 * An ASN.1 encoded signature is a sequence of two ASN.1 integers. Parse one of
 * those integers and convert it to the fixed-length encoding expected by PSA.
 */
static int extract_ecdsa_sig_int( unsigned char **from, const unsigned char *end,
                                  unsigned char *to, size_t to_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t unpadded_len, padding_len;

    if( ( ret = mbedtls_asn1_get_tag( from, end, &unpadded_len,
                                      MBEDTLS_ASN1_INTEGER ) ) != 0 )
    {
        return( ret );
    }

    while( unpadded_len > 0 && **from == 0x00 )
    {
        ( *from )++;
        unpadded_len--;
    }

    if( unpadded_len > to_len || unpadded_len == 0 )
        return( MBEDTLS_ERR_ASN1_LENGTH_MISMATCH );

    padding_len = to_len - unpadded_len;
    memset( to, 0x00, padding_len );
    memcpy( to + padding_len, *from, unpadded_len );
    ( *from ) += unpadded_len;

    return( 0 );
}

/*
 * Convert a signature from an ASN.1 sequence of two integers
 * to a raw {r,s} buffer. Note: the provided sig buffer must be at least
 * twice as big as int_size.
 */
static int extract_ecdsa_sig( unsigned char **p, const unsigned char *end,
                              unsigned char *sig, size_t int_size )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t tmp_size;

    if( ( ret = mbedtls_asn1_get_tag( p, end, &tmp_size,
                MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) ) != 0 )
        return( ret );

    /* Extract r */
    if( ( ret = extract_ecdsa_sig_int( p, end, sig, int_size ) ) != 0 )
        return( ret );
    /* Extract s */
    if( ( ret = extract_ecdsa_sig_int( p, end, sig + int_size, int_size ) ) != 0 )
        return( ret );

    return( 0 );
}

static int ecdsa_verify_wrap( void *ctx_arg, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    mbedtls_ecdsa_context *ctx = ctx_arg;
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_key_id_t key_id = 0;
    psa_status_t status;
    mbedtls_pk_context key;
    int key_len;
    /* see ECP_PUB_DER_MAX_BYTES in pkwrite.c */
    unsigned char buf[30 + 2 * MBEDTLS_ECP_MAX_BYTES];
    unsigned char *p;
    mbedtls_pk_info_t pk_info = mbedtls_eckey_info;
    psa_algorithm_t psa_sig_md = PSA_ALG_ECDSA_ANY;
    size_t curve_bits;
    psa_ecc_family_t curve =
        mbedtls_ecc_group_to_psa( ctx->grp.id, &curve_bits );
    const size_t signature_part_size = ( ctx->grp.nbits + 7 ) / 8;
    ((void) md_alg);

    if( curve == 0 )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    /* mbedtls_pk_write_pubkey() expects a full PK context;
     * re-construct one to make it happy */
    key.pk_info = &pk_info;
    key.pk_ctx = ctx;
    p = buf + sizeof( buf );
    key_len = mbedtls_pk_write_pubkey( &p, buf, &key );
    if( key_len <= 0 )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    psa_set_key_type( &attributes, PSA_KEY_TYPE_ECC_PUBLIC_KEY( curve ) );
    psa_set_key_usage_flags( &attributes, PSA_KEY_USAGE_VERIFY_HASH );
    psa_set_key_algorithm( &attributes, psa_sig_md );

    status = psa_import_key( &attributes,
                             buf + sizeof( buf ) - key_len, key_len,
                             &key_id );
    if( status != PSA_SUCCESS )
    {
        ret = mbedtls_psa_err_translate_pk( status );
        goto cleanup;
    }

    /* We don't need the exported key anymore and can
     * reuse its buffer for signature extraction. */
    if( 2 * signature_part_size > sizeof( buf ) )
    {
        ret = MBEDTLS_ERR_PK_BAD_INPUT_DATA;
        goto cleanup;
    }

    p = (unsigned char*) sig;
    if( ( ret = extract_ecdsa_sig( &p, sig + sig_len, buf,
                                   signature_part_size ) ) != 0 )
    {
        goto cleanup;
    }

    if( psa_verify_hash( key_id, psa_sig_md,
                         hash, hash_len,
                         buf, 2 * signature_part_size )
         != PSA_SUCCESS )
    {
         ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
         goto cleanup;
    }

    if( p != sig + sig_len )
    {
        ret = MBEDTLS_ERR_PK_SIG_LEN_MISMATCH;
        goto cleanup;
    }
    ret = 0;

cleanup:
    psa_destroy_key( key_id );
    return( ret );
}
#else /* MBEDTLS_USE_PSA_CRYPTO */
static int ecdsa_verify_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    ((void) md_alg);

    ret = mbedtls_ecdsa_read_signature( (mbedtls_ecdsa_context *) ctx,
                                hash, hash_len, sig, sig_len );

    if( ret == MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH )
        return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

    return( ret );
}
#endif /* MBEDTLS_USE_PSA_CRYPTO */

static int ecdsa_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    return( mbedtls_ecdsa_write_signature( (mbedtls_ecdsa_context *) ctx,
                md_alg, hash, hash_len, sig, sig_len, f_rng, p_rng ) );
}

#if defined(MBEDTLS_ECP_RESTARTABLE)
static int ecdsa_verify_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                       const unsigned char *hash, size_t hash_len,
                       const unsigned char *sig, size_t sig_len,
                       void *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    ((void) md_alg);

    ret = mbedtls_ecdsa_read_signature_restartable(
            (mbedtls_ecdsa_context *) ctx,
            hash, hash_len, sig, sig_len,
            (mbedtls_ecdsa_restart_ctx *) rs_ctx );

    if( ret == MBEDTLS_ERR_ECP_SIG_LEN_MISMATCH )
        return( MBEDTLS_ERR_PK_SIG_LEN_MISMATCH );

    return( ret );
}

static int ecdsa_sign_rs_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                   void *rs_ctx )
{
    return( mbedtls_ecdsa_write_signature_restartable(
                (mbedtls_ecdsa_context *) ctx,
                md_alg, hash, hash_len, sig, sig_len, f_rng, p_rng,
                (mbedtls_ecdsa_restart_ctx *) rs_ctx ) );

}
#endif /* MBEDTLS_ECP_RESTARTABLE */

static void *ecdsa_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_ecdsa_context ) );

    if( ctx != NULL )
        mbedtls_ecdsa_init( (mbedtls_ecdsa_context *) ctx );

    return( ctx );
}

static void ecdsa_free_wrap( void *ctx )
{
    mbedtls_ecdsa_free( (mbedtls_ecdsa_context *) ctx );
    mbedtls_free( ctx );
}

#if defined(MBEDTLS_ECP_RESTARTABLE)
static void *ecdsa_rs_alloc( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_ecdsa_restart_ctx ) );

    if( ctx != NULL )
        mbedtls_ecdsa_restart_init( ctx );

    return( ctx );
}

static void ecdsa_rs_free( void *ctx )
{
    mbedtls_ecdsa_restart_free( ctx );
    mbedtls_free( ctx );
}
#endif /* MBEDTLS_ECP_RESTARTABLE */

const mbedtls_pk_info_t mbedtls_ecdsa_info = {
    MBEDTLS_PK_ECDSA,
    "ECDSA",
    eckey_get_bitlen,     /* Compatible key structures */
    ecdsa_can_do,
    ecdsa_verify_wrap,
    ecdsa_sign_wrap,
#if defined(MBEDTLS_ECP_RESTARTABLE)
    ecdsa_verify_rs_wrap,
    ecdsa_sign_rs_wrap,
#endif
    NULL,
    NULL,
    eckey_check_pair,   /* Compatible key structures */
    ecdsa_alloc_wrap,
    ecdsa_free_wrap,
#if defined(MBEDTLS_ECP_RESTARTABLE)
    ecdsa_rs_alloc,
    ecdsa_rs_free,
#endif
    eckey_debug,        /* Compatible key structures */
};
#endif /* MBEDTLS_ECDSA_C */

#if defined(TINYCRYPT_PRIMITIVES)
const mbedtls_pk_info_t mbedtls_uecc_eckey_info = {
	MBEDTLS_PK_ECKEY,
    "EC",
	uecc_eckey_get_bitlen,     /* Compatible key structures */
	uecc_eckey_can_do,
	uecc_eckey_verify_wrap,
	uecc_eckey_sign_wrap,
#if defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    NULL,
    NULL,
	uecc_eckey_check_pair,   /* Compatible key structures */
	uecc_eckey_alloc_wrap,
	uecc_eckey_free_wrap,
#if defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    NULL,        /* Compatible key structures */
};
#endif /* TINYCRYPT_PRIMITIVES */

#if defined(MBEDTLS_PK_RSA_ALT_SUPPORT)
/*
 * Support for alternative RSA-private implementations
 */

static int rsa_alt_can_do( mbedtls_pk_type_t type )
{
    return( type == MBEDTLS_PK_RSA );
}

static size_t rsa_alt_get_bitlen( const void *ctx )
{
    const mbedtls_rsa_alt_context *rsa_alt = (const mbedtls_rsa_alt_context *) ctx;

    return( 8 * rsa_alt->key_len_func( rsa_alt->key ) );
}

static int rsa_alt_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_alt_context *rsa_alt = (mbedtls_rsa_alt_context *) ctx;

#if SIZE_MAX > UINT_MAX
    if( UINT_MAX < hash_len )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );
#endif /* SIZE_MAX > UINT_MAX */

    *sig_len = rsa_alt->key_len_func( rsa_alt->key );
    if( *sig_len > MBEDTLS_PK_SIGNATURE_MAX_SIZE )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    return( rsa_alt->sign_func( rsa_alt->key, f_rng, p_rng, MBEDTLS_RSA_PRIVATE,
                md_alg, (unsigned int) hash_len, hash, sig ) );
}

static int rsa_alt_decrypt_wrap( void *ctx,
                    const unsigned char *input, size_t ilen,
                    unsigned char *output, size_t *olen, size_t osize,
                    int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    mbedtls_rsa_alt_context *rsa_alt = (mbedtls_rsa_alt_context *) ctx;

    ((void) f_rng);
    ((void) p_rng);

    if( ilen != rsa_alt->key_len_func( rsa_alt->key ) )
        return( MBEDTLS_ERR_RSA_BAD_INPUT_DATA );

    return( rsa_alt->decrypt_func( rsa_alt->key,
                MBEDTLS_RSA_PRIVATE, olen, input, output, osize ) );
}

#if defined(MBEDTLS_RSA_C)
static int rsa_alt_check_pair( const void *pub, const void *prv )
{
    unsigned char sig[MBEDTLS_MPI_MAX_SIZE];
    unsigned char hash[32];
    size_t sig_len = 0;
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    if( rsa_alt_get_bitlen( prv ) != rsa_get_bitlen( pub ) )
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );

    memset( hash, 0x2a, sizeof( hash ) );

    if( ( ret = rsa_alt_sign_wrap( (void *) prv, MBEDTLS_MD_NONE,
                                   hash, sizeof( hash ),
                                   sig, &sig_len, NULL, NULL ) ) != 0 )
    {
        return( ret );
    }

    if( rsa_verify_wrap( (void *) pub, MBEDTLS_MD_NONE,
                         hash, sizeof( hash ), sig, sig_len ) != 0 )
    {
        return( MBEDTLS_ERR_RSA_KEY_CHECK_FAILED );
    }

    return( 0 );
}
#endif /* MBEDTLS_RSA_C */

static void *rsa_alt_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( mbedtls_rsa_alt_context ) );

    if( ctx != NULL )
        memset( ctx, 0, sizeof( mbedtls_rsa_alt_context ) );

    return( ctx );
}

static void rsa_alt_free_wrap( void *ctx )
{
    mbedtls_platform_zeroize( ctx, sizeof( mbedtls_rsa_alt_context ) );
    mbedtls_free( ctx );
}

const mbedtls_pk_info_t mbedtls_rsa_alt_info = {
    MBEDTLS_PK_RSA_ALT,
    "RSA-alt",
    rsa_alt_get_bitlen,
    rsa_alt_can_do,
    NULL,
    rsa_alt_sign_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    rsa_alt_decrypt_wrap,
    NULL,
#if defined(MBEDTLS_RSA_C)
    rsa_alt_check_pair,
#else
    NULL,
#endif
    rsa_alt_alloc_wrap,
    rsa_alt_free_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL,
    NULL,
#endif
    NULL,
};

#endif /* MBEDTLS_PK_RSA_ALT_SUPPORT */

#if defined(MBEDTLS_USE_PSA_CRYPTO)

static void *pk_opaque_alloc_wrap( void )
{
    void *ctx = mbedtls_calloc( 1, sizeof( psa_key_id_t ) );

    /* no _init() function to call, an calloc() already zeroized */

    return( ctx );
}

static void pk_opaque_free_wrap( void *ctx )
{
    mbedtls_platform_zeroize( ctx, sizeof( psa_key_id_t ) );
    mbedtls_free( ctx );
}

static size_t pk_opaque_get_bitlen( const void *ctx )
{
    const psa_key_id_t *key = (const psa_key_id_t *) ctx;
    size_t bits;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;

    if( PSA_SUCCESS != psa_get_key_attributes( *key, &attributes ) )
        return( 0 );

    bits = psa_get_key_bits( &attributes );
    psa_reset_key_attributes( &attributes );
    return( bits );
}

static int pk_opaque_can_do( mbedtls_pk_type_t type )
{
    /* For now opaque PSA keys can only wrap ECC keypairs,
     * as checked by setup_psa().
     * Also, ECKEY_DH does not really make sense with the current API. */
    return( type == MBEDTLS_PK_ECKEY ||
            type == MBEDTLS_PK_ECDSA );
}

#if defined(MBEDTLS_ECDSA_C)

/*
 * Simultaneously convert and move raw MPI from the beginning of a buffer
 * to an ASN.1 MPI at the end of the buffer.
 * See also mbedtls_asn1_write_mpi().
 *
 * p: pointer to the end of the output buffer
 * start: start of the output buffer, and also of the mpi to write at the end
 * n_len: length of the mpi to read from start
 */
static int asn1_write_mpibuf( unsigned char **p, unsigned char *start,
                              size_t n_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t len = 0;

    if( (size_t)( *p - start ) < n_len )
        return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

    len = n_len;
    *p -= len;
    memmove( *p, start, len );

    /* ASN.1 DER encoding requires minimal length, so skip leading 0s.
     * Neither r nor s should be 0, but as a failsafe measure, still detect
     * that rather than overflowing the buffer in case of a PSA error. */
    while( len > 0 && **p == 0x00 )
    {
        ++(*p);
        --len;
    }

    /* this is only reached if the signature was invalid */
    if( len == 0 )
        return( MBEDTLS_ERR_PK_HW_ACCEL_FAILED );

    /* if the msb is 1, ASN.1 requires that we prepend a 0.
     * Neither r nor s can be 0, so we can assume len > 0 at all times. */
    if( **p & 0x80 )
    {
        if( *p - start < 1 )
            return( MBEDTLS_ERR_ASN1_BUF_TOO_SMALL );

        *--(*p) = 0x00;
        len += 1;
    }

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( p, start, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( p, start,
                                                MBEDTLS_ASN1_INTEGER ) );

    return( (int) len );
}

/* Transcode signature from PSA format to ASN.1 sequence.
 * See ecdsa_signature_to_asn1 in ecdsa.c, but with byte buffers instead of
 * MPIs, and in-place.
 *
 * [in/out] sig: the signature pre- and post-transcoding
 * [in/out] sig_len: signature length pre- and post-transcoding
 * [int] buf_len: the available size the in/out buffer
 */
static int pk_ecdsa_sig_asn1_from_psa( unsigned char *sig, size_t *sig_len,
                                       size_t buf_len )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t len = 0;
    const size_t rs_len = *sig_len / 2;
    unsigned char *p = sig + buf_len;

    MBEDTLS_ASN1_CHK_ADD( len, asn1_write_mpibuf( &p, sig + rs_len, rs_len ) );
    MBEDTLS_ASN1_CHK_ADD( len, asn1_write_mpibuf( &p, sig, rs_len ) );

    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_len( &p, sig, len ) );
    MBEDTLS_ASN1_CHK_ADD( len, mbedtls_asn1_write_tag( &p, sig,
                          MBEDTLS_ASN1_CONSTRUCTED | MBEDTLS_ASN1_SEQUENCE ) );

    memmove( sig, p, len );
    *sig_len = len;

    return( 0 );
}

#endif /* MBEDTLS_ECDSA_C */

static int pk_opaque_sign_wrap( void *ctx, mbedtls_md_type_t md_alg,
                   const unsigned char *hash, size_t hash_len,
                   unsigned char *sig, size_t *sig_len,
                   int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
#if !defined(MBEDTLS_ECDSA_C)
    ((void) ctx);
    ((void) md_alg);
    ((void) hash);
    ((void) hash_len);
    ((void) sig);
    ((void) sig_len);
    ((void) f_rng);
    ((void) p_rng);
    return( MBEDTLS_ERR_PK_FEATURE_UNAVAILABLE );
#else /* !MBEDTLS_ECDSA_C */
    const psa_key_id_t *key = (const psa_key_id_t *) ctx;
    psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
    psa_algorithm_t alg = PSA_ALG_ECDSA( mbedtls_psa_translate_md( md_alg ) );
    size_t buf_len;
    psa_status_t status;

    /* PSA has its own RNG */
    (void) f_rng;
    (void) p_rng;

    /* PSA needs an output buffer of known size, but our API doesn't provide
     * that information. Assume that the buffer is large enough for a
     * maximal-length signature with that key (otherwise the application is
     * buggy anyway). */
    status = psa_get_key_attributes( *key, &attributes );
    if( status != PSA_SUCCESS )
        return( mbedtls_psa_err_translate_pk( status ) );
    buf_len = MBEDTLS_ECDSA_MAX_SIG_LEN( psa_get_key_bits( &attributes ) );
    psa_reset_key_attributes( &attributes );
    if( buf_len > MBEDTLS_PK_SIGNATURE_MAX_SIZE )
        return( MBEDTLS_ERR_PK_BAD_INPUT_DATA );

    /* make the signature */
    status = psa_sign_hash( *key, alg, hash, hash_len,
                            sig, buf_len, sig_len );
    if( status != PSA_SUCCESS )
        return( mbedtls_psa_err_translate_pk( status ) );

    /* transcode it to ASN.1 sequence */
    return( pk_ecdsa_sig_asn1_from_psa( sig, sig_len, buf_len ) );
#endif /* !MBEDTLS_ECDSA_C */
}

const mbedtls_pk_info_t mbedtls_pk_opaque_info = {
    MBEDTLS_PK_OPAQUE,
    "Opaque",
    pk_opaque_get_bitlen,
    pk_opaque_can_do,
    NULL, /* verify - will be done later */
    pk_opaque_sign_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL, /* restartable verify - not relevant */
    NULL, /* restartable sign - not relevant */
#endif
    NULL, /* decrypt - will be done later */
    NULL, /* encrypt - will be done later */
    NULL, /* check_pair - could be done later or left NULL */
    pk_opaque_alloc_wrap,
    pk_opaque_free_wrap,
#if defined(MBEDTLS_ECDSA_C) && defined(MBEDTLS_ECP_RESTARTABLE)
    NULL, /* restart alloc - not relevant */
    NULL, /* restart free - not relevant */
#endif
    NULL, /* debug - could be done later, or even left NULL */
};

#endif /* MBEDTLS_USE_PSA_CRYPTO */

#endif /* MBEDTLS_PK_C */
