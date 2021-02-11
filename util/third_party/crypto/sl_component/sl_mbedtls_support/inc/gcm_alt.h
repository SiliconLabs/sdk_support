/***************************************************************************//**
 * @file
 * @brief Accelerated mbed TLS Galois/Counter Mode (GCM) for AES-128-bit block ciphers
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
#ifndef GCM_ALT_H
#define GCM_ALT_H

/***************************************************************************//**
 * \addtogroup sl_crypto
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_crypto_gcm Accelerated GCM AES-128 Cipher
 * \brief Accelerated AES-GCM-128 cipher for the mbed TLS API using the CRYPTOACC
 *        or SE peripheral
 *
 * \{
 * This module implements the GCM AES-128 cipher, as defined in
 * <em>D. McGrew, J. Viega, The Galois/Counter Mode of Operation
 *        (GCM), Natl. Inst. Stand. Technol.</em>
 * For more information on GCM, see <em>NIST SP 800-38D: Recommendation for
 * Block Cipher Modes of Operation: Galois/Counter Mode (GCM) and GMAC</em>.
 *
 ******************************************************************************/

#if defined(MBEDTLS_GCM_ALT)
/* SiliconLabs CRYPTO hardware acceleration implementation */

#include "em_device.h"

#if defined(CRYPTO_PRESENT)
#include "em_crypto.h"
#elif defined(SEMAILBOX_PRESENT)
#include "em_se.h"
#elif defined(CRYPTOACC_PRESENT)
#include "ba411e_config.h"
#include "sx_aes.h"
#endif

#include <stdint.h>

#define MBEDTLS_GCM_ENCRYPT     1
#define MBEDTLS_GCM_DECRYPT     0

#define MBEDTLS_ERR_GCM_AUTH_FAILED                       -0x0012  /**< Authenticated decryption failed. */
#define MBEDTLS_ERR_GCM_HW_ACCEL_FAILED                   -0x0013  /**< GCM hardware accelerator failed. */
#define MBEDTLS_ERR_GCM_BAD_INPUT                         -0x0014  /**< Bad input parameters to function. */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief          The GCM context structure.
 */
typedef struct {
  unsigned int         keybits;       /*!< Size of key */
  uint64_t             len;           /*!< Total length of encrypted data. */
  uint64_t             add_len;       /*!< Total length of additional data. */

#if defined(CRYPTO_PRESENT)

  CRYPTO_DData_TypeDef key;              /*!< AES key, 128 or 256 bits */
  int                  mode;             /*!< Encryption or decryption */
  CRYPTO_TypeDef*      device;           /*!< CRYPTO device to use */
  CRYPTO_Data_TypeDef  ghash_state;      /*!< GHASH state */
  CRYPTO_Data_TypeDef  gctr_state;       /*!< GCTR counter value */
  CRYPTO_Data_TypeDef  ghash_key;        /*!< GHASH key (is a constant value
                                              which is faster to restore than
                                              to reconstruct each time). */
#elif defined(SEMAILBOX_PRESENT)
  unsigned char        key[32];          /*!< AES key 128, 192 or 256 bits */
  int                  mode;             /*!< Encryption or decryption */
  bool                 last_op;          /*!< Last streaming block identified */
  uint8_t              tagbuf[16];       /*!< Buffer for storing tag */
  uint8_t              se_ctx_enc[32];   /*!< SE GCM encryption state */
  uint8_t              se_ctx_dec[32];   /*!< SE GCM decryption state */

#elif defined(CRYPTOACC_PRESENT)
  unsigned char        key[32];          /*!< AES key 128, 192 or 256 bits */
  sx_aes_mode_t        dir;              /*!< Encryption or decryption */
  uint8_t              sx_ctx[AES_CTX_xCM_SIZE];   /*!< CRYPTOACC GCM state */
#endif
}
mbedtls_gcm_context;

/**
 * \brief           This function initializes the specified GCM context,
 *                  to make references valid, and prepares the context
 *                  for mbedtls_gcm_setkey() or mbedtls_gcm_free().
 *
 *                  The function does not bind the GCM context to a particular
 *                  cipher, nor set the key. For this purpose, use
 *                  mbedtls_gcm_setkey().
 *
 * \param ctx       The GCM context to initialize.
 */
void mbedtls_gcm_init(mbedtls_gcm_context *ctx);

/**
 * \brief           This function associates a GCM context with a
 *                  cipher algorithm and a key.
 *
 * \param ctx       The GCM context to initialize.
 * \param cipher    The 128-bit block cipher to use.
 * \param key       The encryption key.
 * \param keybits   The key size in bits. Valid options are:
 *                  <ul><li>128 bits</li>
 *                  <li>192 bits</li>
 *                  <li>256 bits</li></ul>
 *
 * \return          \c 0 on success, or a cipher specific error code.
 */
int mbedtls_gcm_setkey(mbedtls_gcm_context *ctx,
                       mbedtls_cipher_id_t cipher,
                       const unsigned char *key,
                       unsigned int keybits);

/**
 * \brief           This function performs GCM encryption or decryption of a buffer.
 *
 * \note For encryption, the output buffer can be the same as the input buffer.
 *       For decryption, the output buffer cannot be the same as input buffer.
 *       If the buffers overlap, the output buffer must trail at least 8 Bytes
 *       behind the input buffer.
 *
 * \warning         When this function performs a decryption, it outputs the
 *                  authentication tag and does not verify that the data is
 *                  authentic. You should use this function to perform encryption
 *                  only. For decryption, use mbedtls_gcm_auth_decrypt() instead.
 *
 * \param ctx       The GCM context to use for encryption or decryption.
 * \param mode      The operation to perform:
 *                  - #MBEDTLS_GCM_ENCRYPT to perform authenticated encryption.
 *                    The ciphertext is written to \p output and the
 *                    authentication tag is written to \p tag.
 *                  - #MBEDTLS_GCM_DECRYPT to perform decryption.
 *                    The plaintext is written to \p output and the
 *                    authentication tag is written to \p tag.
 *                    Note that this mode is not recommended, because it does
 *                    not verify the authenticity of the data. For this reason,
 *                    you should use mbedtls_gcm_auth_decrypt() instead of
 *                    calling this function in decryption mode.
 * \param length    The length of the input data, which is equal to the length
 *                  of the output data.
 * \param iv        The initialization vector.
 * \param iv_len    The length of the IV.
 * \param add       The buffer holding the additional data.
 * \param add_len   The length of the additional data.
 * \param input     The buffer holding the input data. Its size is \b length.
 * \param output    The buffer for holding the output data. It must have room
 *                  for \b length bytes.
 * \param tag_len   The length of the tag to generate.
 * \param tag       The buffer for holding the tag.
 *
 * \return          \c 0 if the encryption or decryption was performed
 *                  successfully. Note that in #MBEDTLS_GCM_DECRYPT mode,
 *                  this does not indicate that the data is authentic.
 * \return          #MBEDTLS_ERR_GCM_BAD_INPUT if the lengths are not valid.
 * \return          #MBEDTLS_ERR_GCM_HW_ACCEL_FAILED or a cipher-specific
 *                  error code if the encryption or decryption failed.
 */
int mbedtls_gcm_crypt_and_tag(mbedtls_gcm_context *ctx,
                              int mode,
                              size_t length,
                              const unsigned char *iv,
                              size_t iv_len,
                              const unsigned char *add,
                              size_t add_len,
                              const unsigned char *input,
                              unsigned char *output,
                              size_t tag_len,
                              unsigned char *tag);

/**
 * \brief           This function performs a GCM authenticated decryption of a
 *                  buffer.
 *
 * \note For decryption, the output buffer cannot be the same as input buffer.
 *       If the buffers overlap, the output buffer must trail at least 8 Bytes
 *       behind the input buffer.
 *
 * \param ctx       The GCM context.
 * \param length    The length of the ciphertext to decrypt, which is also
 *                  the length of the decrypted plaintext.
 * \param iv        The initialization vector.
 * \param iv_len    The length of the IV.
 * \param add       The buffer holding the additional data.
 * \param add_len   The length of the additional data.
 * \param tag       The buffer holding the tag to verify.
 * \param tag_len   The length of the tag to verify.
 * \param input     The buffer holding the ciphertext. Its size is \b length.
 * \param output    The buffer for holding the decrypted plaintext. It must
 *                  have room for \b length bytes.
 *
 * \return          \c 0 if successful and authenticated.
 * \return          #MBEDTLS_ERR_GCM_AUTH_FAILED if the tag does not match.
 * \return          #MBEDTLS_ERR_GCM_BAD_INPUT if the lengths are not valid.
 * \return          #MBEDTLS_ERR_GCM_HW_ACCEL_FAILED or a cipher-specific
 *                  error code if the decryption failed.
 */
int mbedtls_gcm_auth_decrypt(mbedtls_gcm_context *ctx,
                             size_t length,
                             const unsigned char *iv,
                             size_t iv_len,
                             const unsigned char *add,
                             size_t add_len,
                             const unsigned char *tag,
                             size_t tag_len,
                             const unsigned char *input,
                             unsigned char *output);

/**
 * \brief           This function starts a GCM encryption or decryption
 *                  operation.
 *
 * \param ctx       The GCM context.
 * \param mode      The operation to perform: #MBEDTLS_GCM_ENCRYPT or
 *                  #MBEDTLS_GCM_DECRYPT.
 * \param iv        The initialization vector.
 * \param iv_len    The length of the IV.
 * \param add       The buffer holding the additional data, or NULL if \p add_len is 0.
 * \param add_len   The length of the additional data. If 0, \p  add is NULL.
 *
 * \return         \c 0 on success.
 */
int mbedtls_gcm_starts(mbedtls_gcm_context *ctx,
                       int mode,
                       const unsigned char *iv,
                       size_t iv_len,
                       const unsigned char *add,
                       size_t add_len);

/**
 * \brief           This function feeds an input buffer into an ongoing GCM
 *                  encryption or decryption operation.
 *
 *    `             The function expects input to be a multiple of 16
 *                  Bytes. Only the last call before calling
 *                  mbedtls_gcm_finish() can be less than 16 Bytes.
 *
 * \note For decryption, the output buffer cannot be the same as input buffer.
 *       If the buffers overlap, the output buffer must trail at least 8 Bytes
 *       behind the input buffer.
 *
 * \param ctx       The GCM context.
 * \param length    The length of the input data. This must be a multiple of 16 except in the last call before mbedtls_gcm_finish().
 * \param input     The buffer holding the input data.
 * \param output    The buffer for holding the output data.
 *
 * \return         \c 0 on success, or #MBEDTLS_ERR_GCM_BAD_INPUT on failure.
 */
int mbedtls_gcm_update(mbedtls_gcm_context *ctx,
                       size_t length,
                       const unsigned char *input,
                       unsigned char *output);

/**
 * \brief           This function finishes the GCM operation and generates
 *                  the authentication tag.
 *
 *                  It wraps up the GCM stream, and generates the
 *                  tag. The tag can have a maximum length of 16 Bytes.
 *
 * \param ctx       The GCM context.
 * \param tag       The buffer for holding the tag.
 * \param tag_len   The length of the tag to generate. Must be at least four.
 *
 * \return          \c 0 on success, or #MBEDTLS_ERR_GCM_BAD_INPUT on failure.
 */
int mbedtls_gcm_finish(mbedtls_gcm_context *ctx,
                       unsigned char *tag,
                       size_t tag_len);

/**
 * \brief           This function clears a GCM context and the underlying
 *                  cipher sub-context.
 *
 * \param ctx       The GCM context to clear.
 */
void mbedtls_gcm_free(mbedtls_gcm_context *ctx);

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_GCM_ALT */

/** \} (end addtogroup sl_crypto_gcm) */
/** \} (end addtogroup sl_crypto) */

#endif /* GCM_ALT_H */
