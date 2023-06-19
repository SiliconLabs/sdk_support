// This is an autogenerated config file, any changes to this file will be overwritten

#ifndef MBEDTLS_CONFIG_AUTOGEN_H
#define MBEDTLS_CONFIG_AUTOGEN_H


#define MBEDTLS_MPI_MAX_SIZE    32


#define MBEDTLS_AES_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CIPHER_C
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CMAC_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ENTROPY_HARDWARE_ALT
#define MBEDTLS_ENTROPY_RAIL_PRESENT
#define MBEDTLS_MD_C
#define MBEDTLS_BIGNUM_C
#define MBEDTLS_OID_C
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_PEM_WRITE_C
#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C
#define MBEDTLS_PLATFORM_C
#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_CALLOC_MACRO sl_calloc
#define MBEDTLS_PLATFORM_FREE_MACRO   sl_free
#define MBEDTLS_ENTROPY_C
#define MBEDTLS_ENTROPY_FORCE_SHA256
#define MBEDTLS_ENTROPY_MAX_SOURCES  2
#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_CTR_DRBG_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA224_C
#define MBEDTLS_THREADING_C
#define MBEDTLS_THREADING_ALT
#define MBEDTLS_SSL_TLS_C
#define MBEDTLS_SSL_CLI_C
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CREATE_C
#define MBEDTLS_X509_CRT_PARSE_C
#define MBEDTLS_X509_CRT_WRITE_C
#define MBEDTLS_X509_CRL_PARSE_C
#define MBEDTLS_X509_CSR_PARSE_C
#define MBEDTLS_X509_CSR_WRITE_C
#define MBEDTLS_PSA_CRYPTO_C
#define MBEDTLS_USE_PSA_CRYPTO
#define MBEDTLS_PSA_CRYPTO_CONFIG
#define MBEDTLS_PSA_CRYPTO_DRIVERS


#if defined(SL_TRUSTZONE_NONSECURE)

#endif // #if defined(SL_TRUSTZONE_NONSECURE)

#if defined(SL_TRUSTZONE_SECURE)

#endif // #if defined(SL_TRUSTZONE_SECURE)

#include "config-device-acceleration.h"

// By default MBEDTLS_PLATFORM_CALLOC_MACRO and MBEDTLS_PLATFORM_FREE_MACRO are
// defined in mbedtls_platform_dynamic_memory_allocation_config_default.slcc.
// Alternative implementations can configure MBEDTLS_PLATFORM_CALLOC_MACRO and
// MBEDTLS_PLATFORM_FREE_MACRO to use other platform specific implementations.
// Alternatively some use cases may select runtime initialisation in the
// application by explicitly calling mbedtls_platform_set_calloc_free() by
// selecting mbedtls_platform_dynamic_memory_allocation_config_init_runtime.

#if defined(MBEDTLS_PLATFORM_CALLOC_MACRO) && defined(MBEDTLS_PLATFORM_FREE_MACRO)
#include <stddef.h>  // size_t
extern void *MBEDTLS_PLATFORM_CALLOC_MACRO( size_t n, size_t size );
extern void MBEDTLS_PLATFORM_FREE_MACRO( void *ptr );
#endif



#endif
