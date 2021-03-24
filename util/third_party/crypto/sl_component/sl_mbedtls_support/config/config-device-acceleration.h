/***************************************************************************//**
 * @brief Configuration for enabling hardware acceleration for mbedtls features.
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

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

/**
 * @defgroup sl_config_device_acceleration Silicon Labs Hardware Acceleration Configuration
 * @addtogroup sl_config_device_acceleration
 *
 * @brief
 *  mbed TLS configuration for Silicon Labs device specific hardware acceleration
 *
 * @details
 *  mbed TLS configuration is composed of settings in this Silicon Labs device specific hardware acceleration
 *  file located in mbedtls/configs that will enable hardware acceleration of all features where this is
 *  supported. This file should be included from an application specific configuration file that
 *  configures what mbedtls features should be included.
 *
 * @{
 */

#ifndef MBEDTLS_CONFIG_DEVICE_ACCELERATION_H
#define MBEDTLS_CONFIG_DEVICE_ACCELERATION_H

#if !defined(NO_CRYPTO_ACCELERATION)
#include "em_device.h"
/**
 * @name SECTION: Silicon Labs Acceleration settings
 *
 * This section sets Silicon Labs Acceleration settings.
 * @{

 */

/** \def MBEDTLS_PSA_CRYPTO_DRIVERS
 *
 * Enable support for the experimental PSA crypto driver interface.
 *
 * Requires: \ref MBEDTLS_PSA_CRYPTO_C.
 *
 * \warning This interface is experimental and may change or be removed
 * without notice.
 */
#if defined(MBEDTLS_PSA_CRYPTO_C)
#define MBEDTLS_PSA_CRYPTO_DRIVERS
#endif

/**
 * \def MBEDTLS_AES_ALT
 *
 * Enable hardware acceleration for the AES block cipher modes through
 * the mbed TLS APIs.
 *
 * Module:  sl_mbedtls_support/src/crypto_aes.c for devices with CRYPTO,
 *          sl_mbedtls_support/src/se_aes.c for devices with SE,
 *          sl_mbedtls_support/src/cryptoacc_aes.c for devices with CRYPTOACC,
 *          sl_mbedtls_support/src/aes_aes.c for devices with AES
 *
 * See \ref MBEDTLS_AES_C for more information.
 */
#define MBEDTLS_AES_ALT

/**
 * \def MBEDTLS_ECP_INTERNAL_ALT
 * \def ECP_SHORTWEIERSTRASS
 * \def MBEDTLS_ECP_ADD_MIXED_ALT
 * \def MBEDTLS_ECP_DOUBLE_JAC_ALT
 * \def MBEDTLS_ECP_NORMALIZE_JAC_MANY_ALT
 * \def MBEDTLS_ECP_NORMALIZE_JAC_ALT
 *
 * Enable hardware acceleration for the elliptic curve over GF(p) library
 * in mbed TLS. This accelerates the raw arithmetic operations.
 *
 * Module:  sl_mbedtls_support/src/crypto_ecp.c
 *
 * Caller:  library/ecp.c
 *
 * Requires: \ref MBEDTLS_BIGNUM_C, \ref MBEDTLS_ECP_C and at least one
 * MBEDTLS_ECP_DP_XXX_ENABLED and (CRYPTO_COUNT > 0)
 */
#if defined(CRYPTO_COUNT) && (CRYPTO_COUNT > 0)
#define MBEDTLS_ECP_INTERNAL_ALT
#define ECP_SHORTWEIERSTRASS
#define MBEDTLS_ECP_ADD_MIXED_ALT
#define MBEDTLS_ECP_DOUBLE_JAC_ALT
#define MBEDTLS_ECP_NORMALIZE_JAC_MANY_ALT
#define MBEDTLS_ECP_NORMALIZE_JAC_ALT
#define MBEDTLS_ECP_RANDOMIZE_JAC_ALT
#endif

/**
 * \def MBEDTLS_SHA1_ALT
 *
 * Enable hardware acceleration for the SHA1 cryptographic hash algorithm
 * through the mbed TLS APIs.
 *
 * Module:  sl_mbedtls_support/src/mbedtls_sha.c for all devices, plus:
 *          - sl_psa_driver/src/sli_crypto_transparent_driver_hash.c for devices with CRYPTO,
 *          - sl_psa_driver/src/sli_se_transparent_driver_hash.c for devices with SE,
 *          - sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.c for devices with CRYPTOACC
 *
 * Caller:  library/mbedtls_md.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *          library/x509write_crt.c
 *
 * Requires: \ref MBEDTLS_SHA1_C and (CRYPTO_COUNT > 0 or CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See MBEDTLS_SHA1_C for more information.
 */
#if defined(CRYPTO_COUNT) && (CRYPTO_COUNT > 0)
#define MBEDTLS_SHA1_ALT
#endif

/**
 * \def MBEDTLS_SHA256_ALT
 *
 * Enable hardware acceleration for the SHA-224 and SHA-256 cryptographic
 * hash algorithms through the mbed TLS APIs.
 *
 * Module:  sl_mbedtls_support/src/mbedtls_sha.c for all devices, plus:
 *          - sl_psa_driver/src/sli_crypto_transparent_driver_hash.c for devices with CRYPTO,
 *          - sl_psa_driver/src/sli_se_transparent_driver_hash.c for devices with SE,
 *          - sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.c for devices with CRYPTOACC
 *
 * Caller:  library/entropy.c
 *          library/mbedtls_md.c
 *          library/ssl_cli.c
 *          library/ssl_srv.c
 *          library/ssl_tls.c
 *
 * Requires: \ref MBEDTLS_SHA256_C and (CRYPTO_COUNT > 0 or CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See MBEDTLS_SHA256_C for more information.
 */
#if defined(CRYPTO_COUNT) && (CRYPTO_COUNT > 0)
#define MBEDTLS_SHA256_ALT
#endif

/* EFR32xG22 Hardware Acceleration */

#if defined(CRYPTOACC_PRESENT) || defined(DOXY_DOC_ONLY)
#define MBEDTLS_AES_ALT
#define AES_192_SUPPORTED
/**
 * \def MBEDTLS_CCM_ALT
 *
 * Enable hardware acceleration of CCM through mbed TLS APIs.
 *
 * Module:  sl_mbedtls_support/src/se_ccm.c for devices with SE,
 *          sl_mbedtls_support/src/cryptoacc_ccm.c for devices with CRYPTOACC
 *
 * Requires: \ref MBEDTLS_AES_C and \ref MBEDTLS_CCM_C (CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See MBEDTLS_CCM_C for more information.
 */
#define MBEDTLS_CCM_ALT
/**
 * \def MBEDTLS_CMAC_ALT
 *
 * Enable hardware acceleration CMAC through mbed TLS APIs.
 *
 * Module:  sl_mbedtls_support/src/mbedtls_cmac.c for all devices, plus:
 *          - sl_psa_driver/src/sli_se_transparent_driver_mac.c and sl_psa_driver/src/sli_se_driver_mac.c for devices with SE,
 *          - sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.c for devices with CRYPTOACC
 *
 * Requires: \ref MBEDTLS_AES_C and \ref MBEDTLS_CMAC_C (CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See MBEDTLS_CMAC_C for more information.
 */
#define MBEDTLS_CMAC_ALT
/**
 * \def MBEDTLS_GCM_ALT
 *
 * Enable hardware acceleration GCM.
 *
 * Module:  sl_mbedtls_support/src/se_gcm.c for devices with SE,
 *          sl_mbedtls_support/src/cryptoacc_gcm.c for devices with CRYPTOACC
 *
 * Requires: \ref MBEDTLS_GCM_C (CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See MBEDTLS_GCM_C for more information.
 */
#define MBEDTLS_GCM_ALT
#define MBEDTLS_SHA1_ALT
#define MBEDTLS_SHA256_ALT

/**
 * \def MBEDTLS_ECDH_COMPUTE_SHARED_ALT
 * \def MBEDTLS_ECDH_GEN_PUBLIC_ALT
 * \def MBEDTLS_ECDSA_GENKEY_ALT
 * \def MBEDTLS_ECDSA_SIGN_ALT
 * \def MBEDTLS_ECDSA_VERIFY_ALT
 *
 * Enable hardware acceleration for certain ECC operations.
 *
 * Module:  sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c for all devices, plus:
 *          - sl_psa_driver/src/sli_se_driver_signature.c and sl_psa_driver/src/sli_se_driver_key_management.c for devices with SE,
 *          - sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.c and sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.c for devices with CRYPTOACC
 *
 * Requires: \ref MBEDTLS_ECP_C (CRYPTOACC_PRESENT or SEMAILBOX_PRESENT)
 *
 * See \ref MBEDTLS_ECP_C for more information.
 */
#if !(defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED) \
  || defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)  \
  || defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)  \
  || defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)  \
  || defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)  \
  || defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)    \
  || defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)    \
  || defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)    \
  || defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED) \
  || defined(MBEDTLS_ECP_DP_CURVE448_ENABLED) )
  #define MBEDTLS_ECDH_COMPUTE_SHARED_ALT
  #define MBEDTLS_ECDH_GEN_PUBLIC_ALT
  #define MBEDTLS_ECDSA_GENKEY_ALT
  #define MBEDTLS_ECDSA_SIGN_ALT
  #define MBEDTLS_ECDSA_VERIFY_ALT
#endif // #if !(   defined(MBEDTLS_ECP_DP_XXX_ENABLED) ...

#endif /* CRYPTOACC */

#if defined(SEMAILBOX_PRESENT) || defined(DOXY_DOC_ONLY)
#include "em_se.h"

#if defined(SE_COMMAND_OPTION_HASH_SHA1)
#define MBEDTLS_SHA1_ALT
#define MBEDTLS_SHA1_PROCESS_ALT
#endif
#if defined(SE_COMMAND_OPTION_HASH_SHA256) || defined(SE_COMMAND_OPTION_HASH_SHA224)
#define MBEDTLS_SHA256_ALT
#define MBEDTLS_SHA256_PROCESS_ALT
#endif
#if defined(SE_COMMAND_OPTION_HASH_SHA512) || defined(SE_COMMAND_OPTION_HASH_SHA384)
#define MBEDTLS_SHA512_ALT
#define MBEDTLS_SHA512_PROCESS_ALT
#endif

#if  !defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED) \
  && !defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED) \
  && !defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED) \
  && !defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED) \
  && !defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)   \
  && !defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)   \
  && !defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)   \
  && !defined(MBEDTLS_ECP_DP_CURVE448_ENABLED)

  #if !( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_SE) \
  && (defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)                               \
  || defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)                                 \
  || defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)  ) )
    #if defined(SE_COMMAND_CREATE_KEY)
      #define MBEDTLS_ECDH_GEN_PUBLIC_ALT
      #define MBEDTLS_ECDSA_GENKEY_ALT
    #endif

    #if defined(SE_COMMAND_DH)
      #define MBEDTLS_ECDH_COMPUTE_SHARED_ALT
    #endif

  #endif

  #if defined(SE_COMMAND_SIGNATURE_SIGN) \
  && !defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
    #if !( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_SE) \
  && (defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)                                  \
  || defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)  ) )
      #define MBEDTLS_ECDSA_SIGN_ALT
    #endif
  #endif

  #if defined(SE_COMMAND_SIGNATURE_VERIFY) \
  && !defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
    #if !( (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_SE) \
  && (defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)                                  \
  || defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)  ) )
      #define MBEDTLS_ECDSA_VERIFY_ALT
    #endif
  #endif

#endif // #if !defined(MBEDTLS_ECP_DP_XXXX_ENABLED) && ...

#if defined(SE_COMMAND_JPAKE_GEN_SESSIONKEY) || defined(DOXY_DOC_ONLY)
/**
 * \def MBEDTLS_ECJPAKE_ALT
 *
 * Enable hardware acceleration JPAKE.
 *
 * Module:  sl_mbedtls_support/src/se_jpake.c
 *
 * Requires: \ref MBEDTLS_ECJPAKE_C (SEMAILBOX_PRESENT)
 *
 * See \ref MBEDTLS_ECJPAKE_C for more information.
 */
#define MBEDTLS_ECJPAKE_ALT
#endif

#if defined(SE_COMMAND_AES_CCM_ENCRYPT) && defined(SE_COMMAND_AES_CCM_DECRYPT)
#define MBEDTLS_CCM_ALT
#endif
#if defined(SE_COMMAND_AES_CMAC)
#define MBEDTLS_CMAC_ALT
#endif
#endif /* SEMAILBOX_PRESENT */

/**
 * \def MBEDTLS_ENTROPY_ADC_PRESENT
 *
 * Decode if device supports retrieving entropy data from the ADC
 * incorporated on devices from Silicon Labs.
 *
 * Requires ADC_PRESENT && _ADC_SINGLECTRLX_VREFSEL_VENTROPY &&
 *          _SILICON_LABS_32B_SERIES_1
 */
#if defined(ADC_PRESENT)                        \
  && defined(_ADC_SINGLECTRLX_VREFSEL_VENTROPY) \
  && defined(_SILICON_LABS_32B_SERIES_1)
#define MBEDTLS_ENTROPY_ADC_PRESENT
#endif

/**
 * \def MBEDTLS_TRNG_PRESENT
 *
 * Determine whether mbedTLS supports the TRNG (if present) on the device.
 *
 * Requires TRNG_PRESENT and not _SILICON_LABS_GECKO_INTERNAL_SDID_95 (xg14)
 */
#if defined(TRNG_PRESENT) \
  && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95)
#undef MBEDTLS_TRNG_PRESENT
#define MBEDTLS_TRNG_PRESENT
#endif

/**
 * \def MBEDTLS_ENTROPY_RAIL_PRESENT
 *
 * Determine whether mbedTLS supports RAIL entropy on the device.
 * This is currently only available on a few series-1 devices
 * where there is no functional TRNG.
 *
 * Requires _EFR_DEVICE and one of
 * _SILICON_LABS_GECKO_INTERNAL_SDID_80
 * _SILICON_LABS_GECKO_INTERNAL_SDID_89
 * _SILICON_LABS_GECKO_INTERNAL_SDID_95
 */
#if defined(_EFR_DEVICE)                            \
  && (defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)  \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95) )
#undef MBEDTLS_ENTROPY_RAIL_PRESENT
#define MBEDTLS_ENTROPY_RAIL_PRESENT
#endif

/* Default ECC configuration for Silicon Labs devices: */

/* Save RAM by adjusting to our exact needs */
#ifndef MBEDTLS_ECP_MAX_BITS
#define MBEDTLS_ECP_MAX_BITS   256
#endif
#ifndef MBEDTLS_MPI_MAX_SIZE
#define MBEDTLS_MPI_MAX_SIZE    32 // 384 bits is 48 bytes
#endif

/*
   Set MBEDTLS_ECP_WINDOW_SIZE to configure
   ECC point multiplication window size, see ecp.h:
   2 = Save RAM at the expense of speed
   3 = Improve speed at the expense of RAM
   4 = Optimize speed at the expense of RAM
 */
#define MBEDTLS_ECP_WINDOW_SIZE        2
#define MBEDTLS_ECP_FIXED_POINT_OPTIM  0

/* Significant speed benefit at the expense of some ROM */
#define MBEDTLS_ECP_NIST_OPTIM

#endif /* !NO_CRYPTO_ACCELERATION */

/** @} (end section sl_config_device_acceleration) */
/** @} (end addtogroup sl_config_device_acceleration) */

#endif /* MBEDTLS_CONFIG_DEVICE_ACCELERATION_H */
/// @endcond
