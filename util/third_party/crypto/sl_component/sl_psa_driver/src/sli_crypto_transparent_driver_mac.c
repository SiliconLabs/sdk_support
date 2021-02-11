#include "em_device.h"

#if defined(CRYPTO_PRESENT)

#include "sli_crypto_transparent_functions.h"
#include "crypto_management.h"
// Replace inclusion of psa/crypto_xxx.h with the new psa driver commong
// interface header file when it becomes available.
#include "psa/crypto_platform.h"
#include "psa/crypto_sizes.h"
#include "psa/crypto_struct.h"
#include "em_crypto.h"
#include "em_core.h"
#include <string.h>

// Magic value for CMAC calculation.
// const_rb should be 0x87 according to the spec, but the implementation
// requires a bit- and byteswapped constant.
static const uint32_t cmac_const_rb[4] = { 0x00000000u, 0x00000000u,
                                           0x00000000u, 0xe1000000u };

static psa_status_t sli_crypto_cmac_compute(const uint8_t *pData,
                                            uint32_t dataLengthBits,
                                            const uint8_t *key,
                                            const uint32_t keyLength,
                                            uint8_t *iv,
                                            uint8_t *digest,
                                            uint16_t digestLengthBits,
                                            const bool encrypt);

static psa_status_t sli_crypto_cmac_finalize(CRYPTO_TypeDef *crypto,
                                             bool encrypt,
                                             uint8_t *digest,
                                             uint16_t digestLengthBits);

static psa_status_t sli_crypto_aes_crypt_cbc(const uint8_t *key_buffer,
                                             size_t key_buffer_size,
                                             psa_encrypt_or_decrypt_t mode,
                                             size_t length,
                                             uint8_t iv[16],
                                             const uint8_t *input,
                                             uint8_t *output);

psa_status_t sli_crypto_transparent_mac_compute(const psa_key_attributes_t *attributes,
                                                const uint8_t *key_buffer,
                                                size_t key_buffer_size,
                                                psa_algorithm_t alg,
                                                const uint8_t *input,
                                                size_t input_length,
                                                uint8_t *mac,
                                                size_t mac_size,
                                                size_t *mac_length)
{
  if (attributes == NULL
      || key_buffer == NULL
      || input == NULL
      || mac == NULL
      || mac_size == 0
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Take in the key
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  size_t key_len = psa_get_key_bits(attributes) / 8;
  switch (key_len) {
    case 16:
    case 32:
      if (key_buffer_size != key_len) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      break;
    case 24:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t status;
  uint16_t digest_length;
  uint8_t tmp_iv[16];

  switch (alg) {
    case PSA_ALG_CMAC:
      digest_length = (mac_size > PSA_BLOCK_CIPHER_BLOCK_SIZE(PSA_KEY_TYPE_AES))
                      ? PSA_BLOCK_CIPHER_BLOCK_SIZE(PSA_KEY_TYPE_AES)
                      : mac_size;

      // IV should always be zero when starting a new computation.
      memset(tmp_iv, 0, 16);
      status = sli_crypto_cmac_compute(input,
                                       input_length * 8,
                                       key_buffer,
                                       key_len,
                                       tmp_iv,
                                       mac,
                                       digest_length * 8,
                                       true);

      *mac_length = digest_length;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  return status;
}

psa_status_t sli_crypto_transparent_mac_sign_setup(sli_crypto_transparent_mac_operation_t *operation,
                                                   const psa_key_attributes_t *attributes,
                                                   const uint8_t *key_buffer,
                                                   size_t key_buffer_size,
                                                   psa_algorithm_t alg)
{
  if (operation == NULL
      || attributes == NULL
      || key_buffer == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Start by resetting the context
  memset(operation, 0, sizeof(*operation));

  // Take in the key
  if (psa_get_key_type(attributes) != PSA_KEY_TYPE_AES) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  switch (alg) {
    case PSA_ALG_CMAC:
      operation->alg = alg;
      break;
    default:
      return PSA_ERROR_NOT_SUPPORTED;
  }

  operation->key_len = psa_get_key_bits(attributes) / 8;
  switch (operation->key_len) {
    case 16:
    case 32:
      if (key_buffer_size != operation->key_len) {
        return PSA_ERROR_INVALID_ARGUMENT;
      }
      memcpy(operation->key, key_buffer, operation->key_len);
      break;
    case 24:
      return PSA_ERROR_NOT_SUPPORTED;
    default:
      return PSA_ERROR_INVALID_ARGUMENT;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_crypto_transparent_mac_update(sli_crypto_transparent_mac_operation_t *operation,
                                               const uint8_t *input,
                                               size_t input_length)
{
  if (operation == NULL
      || (input == NULL && input_length > 0)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t status;

  switch (operation->alg) {
    case PSA_ALG_CMAC: {
      // The streaming update operation of CMAC is like doing CBC-MAC but
      // always keeping the last block as a plaintext.
      if (input_length == 0) {
        return PSA_SUCCESS;
      }

      // Add the beginning of the input data to last unprocessed block and hash
      // it if the input is big enough to cause a new last block to be made.
      if ((operation->unprocessed_len > 0)
          && (input_length > 16 - operation->unprocessed_len)) {
        memcpy(&operation->unprocessed_block[operation->unprocessed_len],
               input,
               16 - operation->unprocessed_len);

        status = sli_crypto_aes_crypt_cbc(operation->key,
                                          operation->key_len,
                                          PSA_CRYPTO_DRIVER_ENCRYPT,
                                          16,
                                          operation->iv,
                                          operation->unprocessed_block,
                                          operation->iv);

        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        input += 16 - operation->unprocessed_len;
        input_length -= 16 - operation->unprocessed_len;
        operation->unprocessed_len = 0;
      }

      // Block count including last block
      size_t block_count = (input_length + 16 - 1) / 16;

      // Hash all full blocks except for the last one
      for (uint32_t i = 1; i < block_count; ++i) {
        status = sli_crypto_aes_crypt_cbc(operation->key,
                                          operation->key_len,
                                          PSA_CRYPTO_DRIVER_ENCRYPT,
                                          16,
                                          operation->iv,
                                          input,
                                          operation->iv);

        if (status != PSA_SUCCESS) {
          return PSA_ERROR_HARDWARE_FAILURE;
        }

        input_length -= 16;
        input += 16;
      }

      // Add remaining input data that wasn't aligned to a block
      if (input_length > 0) {
        memcpy(&operation->unprocessed_block[operation->unprocessed_len],
               input,
               input_length);
        operation->unprocessed_len += input_length;
      }
      break;
    }
    default:
      return PSA_ERROR_BAD_STATE;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_crypto_transparent_mac_sign_finish(sli_crypto_transparent_mac_operation_t *operation,
                                                    uint8_t *mac,
                                                    size_t mac_size,
                                                    size_t *mac_length)
{
  if (operation == NULL
      || mac == NULL
      || mac_size == 0
      || mac_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t status;
  uint16_t digest_length;

  switch (operation->alg) {
    case PSA_ALG_CMAC:
      digest_length = (mac_size > PSA_BLOCK_CIPHER_BLOCK_SIZE(PSA_KEY_TYPE_AES))
                      ? PSA_BLOCK_CIPHER_BLOCK_SIZE(PSA_KEY_TYPE_AES)
                      : mac_size;

      // Calling the cmac compute function with the input set to the last
      // block and the IV set to the current hash is equal to running the
      // finalize operation.
      status = sli_crypto_cmac_compute(operation->unprocessed_block,
                                       operation->unprocessed_len * 8,
                                       operation->key,
                                       operation->key_len,
                                       operation->iv,
                                       mac,
                                       digest_length * 8,
                                       true);

      if (status != PSA_SUCCESS) {
        return PSA_ERROR_HARDWARE_FAILURE;
      }

      *mac_length = digest_length;
      break;
    default:
      return PSA_ERROR_BAD_STATE;
  }

  return PSA_SUCCESS;
}

psa_status_t sli_crypto_transparent_mac_abort(sli_crypto_transparent_mac_operation_t *operation)
{
  if (operation == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // There's no state in hardware that we need to preserve, so zeroing out the context suffices.
  memset(operation, 0, sizeof(*operation));
  return PSA_SUCCESS;
}

/**
 * @brief
 *  Function is an implementation of CMAC-AES128
 * @details
 *  Function assumes fixed key length of 128bit, digest of max 128bit.
 *
 * @param[in] pData
 *  Pointer to data (message) Be careful: this memory should be allocated on
 *  block-size (128-bit) boundaries!
 *
 * @param[in] dataLengthBits
 *  length of actual data in bits
 *
 * @param[in] key
 *  Pointer to key buffer for the AES algorithm.
 *  Has to be 128-bit or 256-bit.
 *
 * @param[in] keyLength
 *   The length in bytes, of the @p pKey, i.e. the 'K' parameter in CCM.
 *
 * @param[in/out] digest
 *  128-bit (maximum) digest. If encrypting, the digest will be stored there.
 *  If verifying, the calculated digest will be compared to the one stored in
 *  this place.
 *  Warning: regardless of digestLengthBits, 128 bits will get written here.
 *
 * @param[in] iv
 *  128-bit initialization vector used in the CBC part of CMAC. Should be zero
 *  unless the call is used as a finalize operation of an unfinished digest, in
 *  which case it should be set to the current intermediate digest.
 *
 * @param[in] digestLengthBits
 *  Requested length of the message digest in bits. LSB's will be zeroed out.
 *
 * @param[in] encrypt
 *  true - Generate hash
 *  false - Verify hash
 *
 * @return
 *   PSA_SUCCESS if success. Error code if failure.
 *   Encryption will always succeed.
 *   Decryption may fail if the authentication fails.
 */
static psa_status_t sli_crypto_cmac_compute(const uint8_t *pData,
                                            uint32_t dataLengthBits,
                                            const uint8_t *key,
                                            const uint32_t keyLength,
                                            uint8_t *iv,
                                            uint8_t *digest,
                                            uint16_t digestLengthBits,
                                            const bool encrypt)

{
  CORE_DECLARE_IRQ_STATE;
  uint32_t i;
  uint32_t subKey[4];
  uint32_t lastBlock[4];
  uint8_t *lastBlockBytePtr = (uint8_t *)lastBlock;
  uint32_t *dataPointer = (uint32_t *)pData;
  uint8_t bitsToPad;
  psa_status_t status;
  CRYPTO_TypeDef *crypto = crypto_management_acquire();

  /* Check input arguments */
  /* Data length is currectly resticted to be a multiple of 8 bits. */
  if (dataLengthBits & 0x7
      || digestLengthBits > 128
      || digestLengthBits == 0) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  CORE_ENTER_CRITICAL();

  /* Reset CRYPTO registers */
  crypto->CTRL = 0;
  crypto->SEQCTRL  = 0;
  crypto->SEQCTRLB = 0;

  /* Calculate subkeys */
  /* magic value in DATA1 */
  CRYPTO_DataWrite(&crypto->DATA1, cmac_const_rb);

  /* Key in KeyBuf */
  CRYPTO_KeyBufWriteUnaligned(crypto,
                              key,
                              (keyLength == 16U) ? cryptoKey128Bits
                              : cryptoKey256Bits);

  /* Zero out DATA0 */
  for (i = 0; i < 4; i++) {
    crypto->DATA0 = 0x00;
  }

  CRYPTO_EXECUTE_17(crypto,
                    CRYPTO_CMD_INSTR_SELDATA0DATA1,
                    CRYPTO_CMD_INSTR_AESENC,
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_SELDDATA0DATA1,
                    CRYPTO_CMD_INSTR_SHR,
                    CRYPTO_CMD_INSTR_EXECIFCARRY,
                    CRYPTO_CMD_INSTR_XOR,
                    CRYPTO_CMD_INSTR_EXECALWAYS,
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_DDATA0TODDATA3, // subkey1 in DATA2
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_SHR,
                    CRYPTO_CMD_INSTR_EXECIFCARRY,
                    CRYPTO_CMD_INSTR_XOR,
                    CRYPTO_CMD_INSTR_EXECALWAYS,
                    CRYPTO_CMD_INSTR_BBSWAP128,
                    CRYPTO_CMD_INSTR_DDATA0TODDATA2 // subkey2 in DATA0
                    );
  CRYPTO_InstructionSequenceWait(crypto);

  /* Prepare input message for algorithm */
  bitsToPad = 128 - (dataLengthBits % 128);

  /* Determine which subKey we're going to use */
  if (bitsToPad != 128 || dataLengthBits == 0) {
    /* Input is treated as last block being incomplete */
    /* So store SubKey 2 */
    CRYPTO_DataRead(&crypto->DATA0, subKey);
  } else {
    /* Input is treated as block aligned, so store SubKey 1 */
    CRYPTO_DataRead(&crypto->DATA2, subKey);
  }

  /* We can take a break from using CRYPTO here */
  CORE_EXIT_CRITICAL();

  /* Copy the last block of data into our local copy because we need
     to change it */
  if (dataLengthBits < 128) {
    for (i = 0; i < 4; i++) {
      lastBlock[i] = dataPointer[i];
    }
  } else {
    for (i = 0; i < 4; i++) {
      lastBlock[i] = dataPointer[((dataLengthBits - 1) / 128) * 4 + i];
    }
  }

  if (bitsToPad != 128) {
    /* Input message needs to be padded */

    /* Apply first one bit */
    if ((bitsToPad % 8) == 0) {
      lastBlockBytePtr[16 - (bitsToPad / 8)] = 0x80;
      dataLengthBits += 8;
      bitsToPad -= 8;
    } else {
      lastBlockBytePtr[16 - (bitsToPad / 8)] |= (1 << ((bitsToPad - 1) % 8));
      dataLengthBits += bitsToPad % 8;
      bitsToPad -= bitsToPad % 8;
    }

    /* Apply zero-padding until block boundary */
    while (bitsToPad > 0) {
      lastBlockBytePtr[16 - (bitsToPad / 8)] = 0x00;
      dataLengthBits += 8;
      bitsToPad -= 8;
    }
  } else {
    if (dataLengthBits == 0) {
      /* Clear out the data */
      for (i = 0; i < 4; i++) {
        lastBlock[i] = 0x00000000;
      }
      /* Pad */
      lastBlockBytePtr[0] = 0x80;
      dataLengthBits = 128;
    } else {
      /* Input message was block-aligned, so no padding required */
    }
  }
  /* Store the XOR-ed version of the last block separate from the message */
  /* to avoid contamination of the input data */
  for (i = 0; i < 4; i++) {
    lastBlock[i] ^= subKey[i];
  }

  /* Calculate hash */
  CORE_ENTER_CRITICAL();

#if defined(MBEDTLS_INCLUDE_IO_MODE_DMA)
  crypto->CTRL |= CRYPTO_CTRL_DMA0RSEL_DATA0;
  crypto->SEQCTRL |= dataLengthBits / 8;
#else
  crypto->SEQCTRL |= 16;
#endif

  if (key) {
    CRYPTO_KeyBufWriteUnaligned(crypto,
                                key,
                                (keyLength == 16U) ? cryptoKey128Bits
                                : cryptoKey256Bits);
  }

  CRYPTO_DataWriteUnaligned(&crypto->DATA0, iv);

#if defined(MBEDTLS_INCLUDE_IO_MODE_DMA)
  CRYPTO_SEQ_LOAD_2(crypto,
                    CRYPTO_CMD_INSTR_DMA0TODATAXOR,
                    CRYPTO_CMD_INSTR_AESENC);
#else
  CRYPTO_SEQ_LOAD_1(crypto,
                    CRYPTO_CMD_INSTR_AESENC);
#endif

#if defined(MBEDTLS_INCLUDE_IO_MODE_DMA)
  CRYPTO_InstructionSequenceExecute(crypto);
#endif
  /* Push all blocks except the last one */
  for (i = 0; i < (dataLengthBits / 128) - 1; i++) {
    CRYPTO_DataWriteUnaligned(&crypto->DATA0XOR, (uint8_t*)&(dataPointer[i * 4]));
#if !defined(MBEDTLS_INCLUDE_IO_MODE_DMA)
    CRYPTO_InstructionSequenceExecute(crypto);
#endif
  }
  /* Don't forget to push the last block as well! */
  CRYPTO_DataWrite(&crypto->DATA0XOR, lastBlock);
#if !defined(MBEDTLS_INCLUDE_IO_MODE_DMA)
  CRYPTO_InstructionSequenceExecute(crypto);
#endif
  CRYPTO_InstructionSequenceWait(crypto);

  status = sli_crypto_cmac_finalize(crypto, encrypt, digest, digestLengthBits);

  CORE_EXIT_CRITICAL();

  crypto_management_release(crypto);

  return status;
}

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

/***************************************************************************//**
 * @brief
 *   Perform final CMAC processing.
 *
 * @param[in] encrypt
 *   True if encryption was requested. False if decryption was requested.
 *
 * @param[in] digest
 *   Pointer to location where digest should be stored.
 *
 * @param[in] digestLengthBits
 *   Length of digest in bits.
 ******************************************************************************/
static psa_status_t sli_crypto_cmac_finalize(CRYPTO_TypeDef *crypto,
                                             bool encrypt,
                                             uint8_t *digest,
                                             uint16_t digestLengthBits)
{
  int i;

  /* If needed, verify */
  if (encrypt) {
    /* Read final hash/digest from CRYPTO. */
    CRYPTO_DataReadUnaligned(&crypto->DATA0, digest);

    /* mask away unneeded bits */
    i = digestLengthBits;
    while (i < 128) {
      if (i % 8 == 0) {
        /* mask away a full byte */
        digest[i / 8] = 0;
        i += 8;
      } else {
        /* mask away partial byte */
        digest[i / 8] &= ~(1 << (7 - (i % 8)));
        i++;
      }
    }
  } else {
    /* Get hash from CRYPTO unintrusively */
    uint32_t hash128[4];
    uint8_t *hash = (uint8_t*) hash128;

    /* Read final hash/digest and compare it with expected. */
    CRYPTO_DataRead(&crypto->DATA0, hash128);

    /* Compare the full length of the digest */
    i = 0;
    while (i < digestLengthBits) {
      if (digestLengthBits - i >= 8) {
        /* If at least a full byte to go, use byte comparison */
        if (hash[i / 8] != digest[i / 8]) {
          return PSA_ERROR_INVALID_SIGNATURE;
        }
        i += 8;
      } else {
        /* If less then a byte to go, use bit comparison */
        if ((hash[i / 8] & (1 << (7 - (i % 8)))) != (digest[i / 8] & (1 << (7 - (i % 8))))) {
          return PSA_ERROR_INVALID_SIGNATURE;
        }
        i += 1;
      }
    }
  }
  return PSA_SUCCESS;
}

/*
 * AES-CBC buffer encryption/decryption
 *
 * NOTE: The input and output buffers must not overlap.
 */
static psa_status_t sli_crypto_aes_crypt_cbc(const uint8_t *key_buffer,
                                             size_t key_buffer_size,
                                             psa_encrypt_or_decrypt_t mode,
                                             size_t length,
                                             uint8_t iv[16],
                                             const uint8_t *input,
                                             uint8_t *output)
{
  CORE_DECLARE_IRQ_STATE;
  size_t processed = 0;

  CRYPTO_TypeDef *device = crypto_management_acquire();
  device->WAC = 0;
  device->CTRL = 0;

  // Set the encryption/decryption key and input data
  CORE_ENTER_CRITICAL();
  CRYPTO_KeyBufWriteUnaligned(device,
                              key_buffer,
                              (key_buffer_size == 16U) ? cryptoKey128Bits
                              : cryptoKey256Bits);
  if (mode == PSA_CRYPTO_DRIVER_ENCRYPT) {
    CRYPTO_DataWriteUnaligned(&device->DATA0, (uint8_t *)iv);
  } else {
    CRYPTO_DataWriteUnaligned(&device->DATA2, (uint8_t *)iv);
  }
  CORE_EXIT_CRITICAL();

  while (processed < length) {
    if (mode == PSA_CRYPTO_DRIVER_ENCRYPT) {
      CORE_ENTER_CRITICAL();
      CRYPTO_DataWriteUnaligned(&device->DATA0XOR, (uint8_t *)(&input[processed]));

      // Initiate encryption and wait for it to complete
      device->CMD = CRYPTO_CMD_INSTR_AESENC;
      while ((device->STATUS & CRYPTO_STATUS_INSTRRUNNING) != 0) ;

      CRYPTO_DataReadUnaligned(&device->DATA0, output);
      CORE_EXIT_CRITICAL();
    } else {
      // Decrypt input block, XOR IV to decrypted text, set ciphertext as next IV
      CORE_ENTER_CRITICAL();
      CRYPTO_DataWriteUnaligned(&device->DATA0, (uint8_t *)(&input[processed]));

      // Initiate decryption sequence and wait for it to complete
      CRYPTO_EXECUTE_4(device,
                       CRYPTO_CMD_INSTR_DATA0TODATA1,
                       CRYPTO_CMD_INSTR_AESDEC,
                       CRYPTO_CMD_INSTR_DATA2TODATA0XOR,
                       CRYPTO_CMD_INSTR_DATA1TODATA2);

      while ((device->STATUS & CRYPTO_STATUS_SEQRUNNING) != 0) ;

      CRYPTO_DataReadUnaligned(&device->DATA0, &output[processed]);
      CORE_EXIT_CRITICAL();
    }
    processed += 16;
  }

  if (processed >= 16) {
    // Update the supplied IV
    if (mode == PSA_CRYPTO_DRIVER_ENCRYPT) {
      memcpy(iv, &output[processed - 16], 16);
    } else {
      CORE_ENTER_CRITICAL();
      CRYPTO_DataReadUnaligned(&device->DATA2, iv);
      CORE_EXIT_CRITICAL();
    }
  }

  crypto_management_release(device);

  return PSA_SUCCESS;
}

#endif // defined(CRYPTO_PRESENT)
