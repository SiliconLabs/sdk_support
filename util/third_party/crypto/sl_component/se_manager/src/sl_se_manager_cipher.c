/***************************************************************************//**
 * @file
 * @brief Silicon Labs Secure Engine Manager API.
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
#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)

#include "sl_se_manager.h"
#include "sli_se_manager_internal.h"
#include "em_se.h"
#include "em_assert.h"
#include <string.h>

/// @addtogroup sl_se_manager
/// @{

// -----------------------------------------------------------------------------
// Global Functions

/***************************************************************************//**
 * AES-ECB block encryption/decryption.
 ******************************************************************************/
sl_status_t sl_se_aes_crypt_ecb(sl_se_command_context_t *cmd_ctx,
                                const sl_se_key_descriptor_t *key,
                                sl_se_cipher_operation_t mode,
                                size_t length,
                                const unsigned char *input,
                                unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  if (cmd_ctx == NULL || key == NULL || input == NULL || output == NULL
      || (length & 0xFU) != 0U) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx,
                      (mode == SL_SE_ENCRYPT
                       ? SLI_SE_COMMAND_AES_ENCRYPT : SLI_SE_COMMAND_AES_DECRYPT)
                      | SLI_SE_COMMAND_OPTION_MODE_ECB
                      | SLI_SE_COMMAND_OPTION_CONTEXT_WHOLE);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &in);

  SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(output, length);
  SE_addDataOutput(se_cmd, &out);

  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * AES-CBC buffer encryption/decryption.
 ******************************************************************************/
sl_status_t sl_se_aes_crypt_cbc(sl_se_command_context_t *cmd_ctx,
                                const sl_se_key_descriptor_t *key,
                                sl_se_cipher_operation_t mode,
                                size_t length,
                                unsigned char iv[16],
                                const unsigned char *input,
                                unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  if (cmd_ctx == NULL || key == NULL || input == NULL || output == NULL
      || iv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Input length must be a multiple of 16 bytes which is the AES block length
  if (length & 0xf) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx,
                      (mode == SL_SE_ENCRYPT
                       ? SLI_SE_COMMAND_AES_ENCRYPT : SLI_SE_COMMAND_AES_DECRYPT)
                      | SLI_SE_COMMAND_OPTION_MODE_CBC
                      | SLI_SE_COMMAND_OPTION_CONTEXT_ADD);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, 16);
  SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &iv_in);
  SE_addDataInput(se_cmd, &in);

  SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(output, length);
  SE_DataTransfer_t iv_out = SE_DATATRANSFER_DEFAULT(iv, 16);
  SE_addDataOutput(se_cmd, &out);
  SE_addDataOutput(se_cmd, &iv_out);

  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * AES-CFB128 buffer encryption/decryption.
 ******************************************************************************/
sl_status_t sl_se_aes_crypt_cfb128(sl_se_command_context_t *cmd_ctx,
                                   const sl_se_key_descriptor_t *key,
                                   sl_se_cipher_operation_t mode,
                                   size_t length,
                                   uint32_t *iv_off,
                                   unsigned char iv[16],
                                   const unsigned char *input,
                                   unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  uint32_t n = iv_off ? *iv_off : 0;
  uint32_t processed = 0;
  sl_status_t command_status = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL || input == NULL || output == NULL
      || iv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  while (processed < length) {
    if (n > 0) {
      // start by filling up the IV
      if (mode == SL_SE_ENCRYPT) {
        iv[n] = output[processed] = (unsigned char)(iv[n] ^ input[processed]);
      } else {
        int c = input[processed];
        output[processed] = (unsigned char)(c ^ iv[n]);
        iv[n] = (unsigned char) c;
      }
      n = (n + 1) & 0x0F;
      processed++;
      continue;
    } else {
      // process one ore more blocks of data
      uint32_t iterations = (length - processed) / 16;

      if (iterations > 0) {
        sli_se_command_init(cmd_ctx,
                            (mode == SL_SE_ENCRYPT
                             ? SLI_SE_COMMAND_AES_ENCRYPT : SLI_SE_COMMAND_AES_DECRYPT)
                            | SLI_SE_COMMAND_OPTION_MODE_CFB
                            | SLI_SE_COMMAND_OPTION_CONTEXT_ADD);

        // Add key parameters to command
        sli_add_key_parameters(cmd_ctx, key, command_status);
        // Message size (number of bytes)
        SE_addParameter(se_cmd, iterations * 16);

        // Add key metadata block to command
        sli_add_key_metadata(cmd_ctx, key, command_status);
        // Add key input block to command
        sli_add_key_input(cmd_ctx, key, command_status);

        SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, 16);
        SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(&input[processed], iterations * 16);
        SE_addDataInput(se_cmd, &iv_in);
        SE_addDataInput(se_cmd, &in);

        SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(&output[processed], iterations * 16);
        SE_DataTransfer_t iv_out = SE_DATATRANSFER_DEFAULT(iv, 16);
        SE_addDataOutput(se_cmd, &out);
        SE_addDataOutput(se_cmd, &iv_out);

        command_status = sli_se_execute_and_wait(cmd_ctx);
        processed += iterations * 16;
        if (command_status != SL_STATUS_OK) {
          return command_status;
        }
      }

      while ((length - processed) > 0) {
        if (n == 0) {
          // Need to update the IV but don't have a full block of input to pass
          // to the SE.
          command_status = sl_se_aes_crypt_ecb(cmd_ctx, key, SL_SE_ENCRYPT, 16U, iv, iv);
          if (command_status != SL_STATUS_OK) {
            return command_status;
          }
        }
        // Save remainder to IV
        if (mode == SL_SE_ENCRYPT) {
          iv[n] = output[processed] = (unsigned char)(iv[n] ^ input[processed]);
        } else {
          int c = input[processed];
          output[processed] = (unsigned char)(c ^ iv[n]);
          iv[n] = (unsigned char) c;
        }
        n = (n + 1) & 0x0F;
        processed++;
      }
    }
  }

  if ( iv_off ) {
    *iv_off = n;
  }

  return command_status;
}

/***************************************************************************//**
 * AES-CFB8 buffer encryption/decryption.
 ******************************************************************************/
sl_status_t sl_se_aes_crypt_cfb8(sl_se_command_context_t *cmd_ctx,
                                 const sl_se_key_descriptor_t *key,
                                 sl_se_cipher_operation_t mode,
                                 size_t length,
                                 unsigned char iv[16],
                                 const unsigned char *input,
                                 unsigned char *output)
{
  unsigned char c;
  unsigned char ov[17];
  sl_status_t ret = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL || input == NULL || output == NULL
      || iv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  while (length--) {
    memcpy(ov, iv, 16U);
    if ((ret = sl_se_aes_crypt_ecb(cmd_ctx, key, SL_SE_ENCRYPT, 16U, iv, iv))
        != SL_STATUS_OK) {
      return ret;
    }

    if (mode == SL_SE_DECRYPT) {
      ov[16] = *input;
    }

    c = *output++ = (unsigned char)(iv[0] ^ *input++);

    if (mode == SL_SE_ENCRYPT) {
      ov[16] = c;
    }

    memcpy(iv, ov + 1, 16U);
  }

  return ret;
}
/***************************************************************************//**
 * AES-CTR buffer encryption/decryption.
 ******************************************************************************/
sl_status_t sl_se_aes_crypt_ctr(sl_se_command_context_t *cmd_ctx,
                                const sl_se_key_descriptor_t *key,
                                size_t length,
                                uint32_t *nc_off,
                                unsigned char nonce_counter[16],
                                unsigned char stream_block[16],
                                const unsigned char *input,
                                unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  uint32_t n = nc_off ? *nc_off : 0;
  uint32_t processed = 0;
  sl_status_t command_status = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL
      || (length != 0 && (input == NULL || output == NULL))
      || nonce_counter == NULL || stream_block == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  while (processed < length) {
    if (n > 0) {
      // start by filling up the IV
      output[processed] = (unsigned char)(input[processed] ^ stream_block[n]);
      n = (n + 1) & 0x0F;
      processed++;
      continue;
    } else {
      // process one or more blocks of data
      uint32_t iterations = (length - processed) / 16;

      if (iterations > 0) {
        sli_se_command_init(cmd_ctx,
                            SLI_SE_COMMAND_AES_ENCRYPT
                            | SLI_SE_COMMAND_OPTION_MODE_CTR
                            | SLI_SE_COMMAND_OPTION_CONTEXT_ADD);

        // Add key parameters to command
        sli_add_key_parameters(cmd_ctx, key, command_status);
        // Message size (number of bytes)
        SE_addParameter(se_cmd, iterations * 16);

        // Add key metadata block to command
        sli_add_key_metadata(cmd_ctx, key, command_status);
        // Add key input block to command
        sli_add_key_input(cmd_ctx, key, command_status);

        SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(nonce_counter, 16);
        SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(&input[processed], iterations * 16);
        SE_addDataInput(se_cmd, &iv_in);
        SE_addDataInput(se_cmd, &in);

        SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(&output[processed], iterations * 16);
        SE_DataTransfer_t iv_out = SE_DATATRANSFER_DEFAULT(nonce_counter, 16);
        SE_addDataOutput(se_cmd, &out);
        SE_addDataOutput(se_cmd, &iv_out);

        command_status = sli_se_execute_and_wait(cmd_ctx);
        processed += iterations * 16;
        if (command_status != SL_STATUS_OK) {
          return command_status;
        }
      }

      while ((length - processed) > 0) {
        if (n == 0) {
          // Get a new stream block
          command_status = sl_se_aes_crypt_ecb(cmd_ctx,
                                               key,
                                               SL_SE_ENCRYPT,
                                               16U,
                                               nonce_counter,
                                               stream_block);
          if (command_status != SL_STATUS_OK) {
            return command_status;
          }
          // increment nonce counter
          for (uint32_t i = 0; i < 16; i++) {
            nonce_counter[15 - i] = nonce_counter[15 - i] + 1;
            if (nonce_counter[15 - i] != 0) {
              break;
            }
          }
        }
        // Save remainder to IV
        output[processed] = (unsigned char)(input[processed] ^ stream_block[n]);
        n = (n + 1) & 0x0F;
        processed++;
      }
    }
  }

  if ( nc_off ) {
    *nc_off = n;
  }

  return command_status;
}

/***************************************************************************//**
 * AES-CCM buffer encryption.
 ******************************************************************************/
sl_status_t sl_se_ccm_encrypt_and_tag(sl_se_command_context_t *cmd_ctx,
                                      const sl_se_key_descriptor_t *key,
                                      size_t length,
                                      const unsigned char *iv, size_t iv_len,
                                      const unsigned char *add, size_t add_len,
                                      const unsigned char *input,
                                      unsigned char *output,
                                      unsigned char *tag, size_t tag_len)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  unsigned char q;
  sl_status_t command_status = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL || tag == NULL || iv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (add_len > 0 && add == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (length > 0 && (input == NULL || output == NULL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Test for invalid (too long) message length. This test is included here because
  // the SE does not implement the test. When the SE ultimately implements the test
  // the following test can be removed.
  q = 16 - 1 - (unsigned char) iv_len;
  if ((q < sizeof(length)) && (length >= (1UL << (q * 8)))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (tag_len == 2 || tag_len > 16 || tag_len % 2 != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Also implies q is within bounds
  if (iv_len < 7 || iv_len > 13) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((uint32_t)output + length > RAM_MEM_END) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_AES_CCM_ENCRYPT);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, command_status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, ((iv_len & 0xFFFF) << 16) | (tag_len & 0xFFFF));
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, command_status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, command_status);

  SE_DataTransfer_t in_data = SE_DATATRANSFER_DEFAULT(input, length);
  SE_DataTransfer_t in_add = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_DataTransfer_t in_nonce = SE_DATATRANSFER_DEFAULT(iv, iv_len);
  SE_addDataInput(se_cmd, &in_nonce);
  SE_addDataInput(se_cmd, &in_add);
  SE_addDataInput(se_cmd, &in_data);

  SE_DataTransfer_t out_data = SE_DATATRANSFER_DEFAULT(output, length);
  SE_DataTransfer_t out_tag = SE_DATATRANSFER_DEFAULT(tag, tag_len);
  SE_addDataOutput(se_cmd, &out_data);
  SE_addDataOutput(se_cmd, &out_tag);

  command_status = sli_se_execute_and_wait(cmd_ctx);
  return command_status;
}

/***************************************************************************//**
 * AES-CCM buffer decryption.
 ******************************************************************************/
sl_status_t sl_se_ccm_auth_decrypt(sl_se_command_context_t *cmd_ctx,
                                   const sl_se_key_descriptor_t *key,
                                   size_t length,
                                   const unsigned char *iv, size_t iv_len,
                                   const unsigned char *add, size_t add_len,
                                   const unsigned char *input,
                                   unsigned char *output,
                                   const unsigned char *tag, size_t tag_len)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  unsigned char q;
  sl_status_t command_status = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL || tag == NULL || iv == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (add_len > 0 && add == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (length > 0 && (input == NULL || output == NULL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Test for invalid (too long) message length. This test is included here because
  // the SE does not implement the test. When the SE ultimately implements the test
  // the following test can be removed.
  q = 16 - 1 - (unsigned char) iv_len;
  if ((q < sizeof(length)) && (length >= (1UL << (q * 8)))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (tag_len == 2 || tag_len > 16 || tag_len % 2 != 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Also implies q is within bounds */
  if (iv_len < 7 || iv_len > 13) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if ((uint32_t)output + length > RAM_MEM_END) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_AES_CCM_DECRYPT);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, command_status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, ((iv_len & 0xFFFF) << 16) | (tag_len & 0xFFFF));
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, command_status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, command_status);

  SE_DataTransfer_t in_data = SE_DATATRANSFER_DEFAULT(input, length);
  SE_DataTransfer_t in_add = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_DataTransfer_t in_nonce = SE_DATATRANSFER_DEFAULT(iv, iv_len);
  SE_addDataInput(se_cmd, &in_nonce);
  SE_addDataInput(se_cmd, &in_add);
  SE_addDataInput(se_cmd, &in_data);

  SE_DataTransfer_t out_data = SE_DATATRANSFER_DEFAULT(output, length);
  SE_addDataOutput(se_cmd, &out_data);
  SE_DataTransfer_t in_tag = SE_DATATRANSFER_DEFAULT(tag, tag_len);
  SE_addDataInput(se_cmd, &in_tag);

  command_status = sli_se_execute_and_wait(cmd_ctx);
  if (command_status == SL_STATUS_OK) {
    return SL_STATUS_OK;
  } else {
    memset(output, 0, length);
    return command_status;
  }
}

/***************************************************************************//**
 * This function calculates the full generic CMAC on the input buffer with
 * the provided key.
 ******************************************************************************/
sl_status_t sl_se_cmac(sl_se_command_context_t *cmd_ctx,
                       const sl_se_key_descriptor_t *key,
                       const unsigned char *input,
                       size_t input_len,
                       unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status = SL_STATUS_OK;

  if (cmd_ctx == NULL || key == NULL || input == NULL || output == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (key->type) {
    case SL_SE_KEY_TYPE_AES_128:
    case SL_SE_KEY_TYPE_AES_192:
    case SL_SE_KEY_TYPE_AES_256:
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_AES_CMAC);

  // Add key parameter to command.
  sli_add_key_parameters(cmd_ctx, key, status);

  // Message size parameter.
  SE_addParameter(se_cmd, input_len);

  // Key metadata.
  sli_add_key_metadata(cmd_ctx, key, status);
  sli_add_key_input(cmd_ctx, key, status);

  // Data input.
  SE_DataTransfer_t in_data = SE_DATATRANSFER_DEFAULT(input, input_len);
  SE_addDataInput(se_cmd, &in_data);

  // Data output.
  SE_DataTransfer_t out_tag = SE_DATATRANSFER_DEFAULT(output, 16);
  SE_addDataOutput(se_cmd, &out_tag);

  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 *   Finish a CMAC streaming operation and return the resulting CMAC tag.
 *   It is called after sl_se_cmac_update().
 ******************************************************************************/
sl_status_t sl_se_cmac_finish(sl_se_cmac_streaming_context_t *cmac_ctx,
                              uint8_t *output)
{
  sl_status_t status = SL_STATUS_OK;

  if (cmac_ctx == NULL || output == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (cmac_ctx->length >= 16U) {
    // Compute previous input block by decryption of current data.
    status = sl_se_aes_crypt_ecb(cmac_ctx->cmd_ctx,
                                 cmac_ctx->key,
                                 SL_SE_DECRYPT,
                                 16U,
                                 cmac_ctx->data_out,
                                 cmac_ctx->state);  // Keep decrypted data in 'state'
  }

  if (status == SL_STATUS_OK) {
    // Feed previous block and unprocessed data (if any) to CMAC,
    // or on data < 16 just use accumulated data in context.
    SE_Command_t *se_cmd = &cmac_ctx->cmd_ctx->command;
    sli_se_command_init(cmac_ctx->cmd_ctx, SLI_SE_COMMAND_AES_CMAC);

    // Add key parameter to command.
    sli_add_key_parameters(cmac_ctx->cmd_ctx, cmac_ctx->key, status);

    // Message size parameter.
    if (cmac_ctx->length >= 16U) {
      SE_addParameter(se_cmd, 16U + (cmac_ctx->length & 0xFU));
    } else {
      SE_addParameter(se_cmd, cmac_ctx->length);
    }

    // Key metadata.
    sli_add_key_metadata(cmac_ctx->cmd_ctx, cmac_ctx->key, status);
    sli_add_key_input(cmac_ctx->cmd_ctx, cmac_ctx->key, status);

    SE_DataTransfer_t in_data1 = SE_DATATRANSFER_DEFAULT(cmac_ctx->state, 16U);
    SE_DataTransfer_t in_data2 = SE_DATATRANSFER_DEFAULT(cmac_ctx->data_in,
                                                         cmac_ctx->length & 0xFU);
    SE_DataTransfer_t in_data = SE_DATATRANSFER_DEFAULT(cmac_ctx->data_in,
                                                        cmac_ctx->length);
    // Data input.
    if (cmac_ctx->length >= 16U) {
      // Collect data from two sources.
      in_data1.length &= ~SE_DATATRANSFER_REALIGN;
      SE_addDataInput(se_cmd, &in_data1);
      SE_addDataInput(se_cmd, &in_data2);
    } else {
      SE_addDataInput(se_cmd, &in_data);
    }

    // Data output.
    SE_DataTransfer_t out_tag = SE_DATATRANSFER_DEFAULT(output, 16U);
    SE_addDataOutput(se_cmd, &out_tag);

    status = sli_se_execute_and_wait(cmac_ctx->cmd_ctx);
  }
  return status;
}

/***************************************************************************//**
 *   Prepare a CMAC streaming command context object to be used in subsequent
 *   CMAC streaming function calls.
 ******************************************************************************/
sl_status_t sl_se_cmac_starts(sl_se_cmac_streaming_context_t *cmac_ctx,
                              sl_se_command_context_t *cmd_ctx,
                              const sl_se_key_descriptor_t *key)
{
  if (cmac_ctx == NULL || cmd_ctx == NULL || key == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (key->type) {
    case SL_SE_KEY_TYPE_AES_128:
    case SL_SE_KEY_TYPE_AES_192:
    case SL_SE_KEY_TYPE_AES_256:
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  memset(cmac_ctx, 0, sizeof(sl_se_cmac_streaming_context_t));
  cmac_ctx->cmd_ctx = cmd_ctx;
  cmac_ctx->key = key;
  return SL_STATUS_OK;
}

/***************************************************************************//**
 *   This function feeds an input buffer into an ongoing CMAC computation.
 *   It is called between sl_se_cmac_starts() and sl_se_cmac_finish().
 *   Can be called repeatedly.
 ******************************************************************************/
sl_status_t sl_se_cmac_update(sl_se_cmac_streaming_context_t *cmac_ctx,
                              const uint8_t *input,
                              size_t input_len)
{
  sl_status_t status = SL_STATUS_OK;

  if (cmac_ctx == NULL || input == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  size_t pending = cmac_ctx->length & 0xFU;

  if ((cmac_ctx->length / 16U) != ((cmac_ctx->length + input_len) / 16U)) {
    // Process one or more 16 byte blocks.
    size_t bytes_to_process = (pending + input_len) & 0xFFFFFFF0U;

    SE_Command_t *se_cmd = &cmac_ctx->cmd_ctx->command;
    sli_se_command_init(cmac_ctx->cmd_ctx,
                        SLI_SE_COMMAND_AES_ENCRYPT
                        | SLI_SE_COMMAND_OPTION_MODE_CBC
                        | SLI_SE_COMMAND_OPTION_CONTEXT_ADD);

    // Add key parameters to command.
    sli_add_key_parameters(cmac_ctx->cmd_ctx, cmac_ctx->key, status);
    // Message size (number of bytes)
    SE_addParameter(se_cmd, bytes_to_process);

    // Add key metadata block to command.
    sli_add_key_metadata(cmac_ctx->cmd_ctx, cmac_ctx->key, status);
    // Add key input block to command.
    sli_add_key_input(cmac_ctx->cmd_ctx, cmac_ctx->key, status);

    SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(cmac_ctx->state, 16U);
    SE_addDataInput(se_cmd, &iv_in);

    // Data input, collect data from two sources.
    SE_DataTransfer_t in1 = SE_DATATRANSFER_DEFAULT(cmac_ctx->data_in, pending);
    SE_DataTransfer_t in2 = SE_DATATRANSFER_DEFAULT(input, bytes_to_process - pending);
    in1.length &= ~SE_DATATRANSFER_REALIGN;
    SE_addDataInput(se_cmd, &in1);
    SE_addDataInput(se_cmd, &in2);

    // Data output, discard everything except the last 16 bytes.
    SE_DataTransfer_t out1 = SE_DATATRANSFER_DEFAULT(NULL, bytes_to_process - 16U);
    SE_DataTransfer_t out2 = SE_DATATRANSFER_DEFAULT(cmac_ctx->data_out, 16U);
    out1.length |= SE_DATATRANSFER_DISCARD;
    out1.length &= ~SE_DATATRANSFER_REALIGN;
    SE_addDataOutput(se_cmd, &out1);
    SE_addDataOutput(se_cmd, &out2);

    SE_DataTransfer_t iv_out = SE_DATATRANSFER_DEFAULT(cmac_ctx->state, 16U);
    SE_addDataOutput(se_cmd, &iv_out);

    status = sli_se_execute_and_wait(cmac_ctx->cmd_ctx);

    // Store leftover data.
    size_t leftover = pending + input_len - bytes_to_process;
    memcpy(cmac_ctx->data_in, input + input_len - leftover, leftover);
  } else {
    // Not a complete 16 byte block yet, save input data for later.
    memcpy(cmac_ctx->data_in + pending, input, input_len);
  }
  cmac_ctx->length += input_len;
  return status;
}

/***************************************************************************//**
 *   Compute a HMAC on a full message.
 ******************************************************************************/
sl_status_t sl_se_hmac(sl_se_command_context_t *cmd_ctx,
                       const sl_se_key_descriptor_t *key,
                       sl_se_hash_type_t hash_type,
                       const uint8_t *message,
                       size_t message_len,
                       uint8_t *output,
                       size_t output_len)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status = SL_STATUS_OK;
  uint32_t command_word;
  size_t hmac_len;

  if (cmd_ctx == NULL || key == NULL || message == NULL || output == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  switch (hash_type) {
    case SL_SE_HASH_SHA1:
      command_word = SLI_SE_COMMAND_HMAC | SLI_SE_COMMAND_OPTION_HASH_SHA1;
      // SHA1 digest size is 20 bytes
      hmac_len = 20;
      break;

    case SL_SE_HASH_SHA224:
      command_word = SLI_SE_COMMAND_HMAC | SLI_SE_COMMAND_OPTION_HASH_SHA224;
      // SHA224 digest size is 28 bytes
      hmac_len = 28;
      break;

    case SL_SE_HASH_SHA256:
      command_word = SLI_SE_COMMAND_HMAC | SLI_SE_COMMAND_OPTION_HASH_SHA256;
      // SHA256 digest size is 32 bytes
      hmac_len = 32;
      break;

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
    case SL_SE_HASH_SHA384:
      command_word = SLI_SE_COMMAND_HMAC | SLI_SE_COMMAND_OPTION_HASH_SHA384;
      // SHA384 digest size is 48 bytes
      hmac_len = 48;
      break;

    case SL_SE_HASH_SHA512:
      command_word = SLI_SE_COMMAND_HMAC | SLI_SE_COMMAND_OPTION_HASH_SHA512;
      // SHA512 digest size is 64 bytes
      hmac_len = 64;
      break;

#endif
    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  if (output_len < hmac_len) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, command_word);

  // Add key parameter to command.
  sli_add_key_parameters(cmd_ctx, key, status);

  // Message size parameter.
  SE_addParameter(se_cmd, message_len);

  // Key metadata.
  sli_add_key_metadata(cmd_ctx, key, status);

  sli_add_key_input(cmd_ctx, key, status);

  // Data input.
  SE_DataTransfer_t in_data = SE_DATATRANSFER_DEFAULT(message, message_len);
  SE_addDataInput(se_cmd, &in_data);

  // Data output.
  SE_DataTransfer_t out_hmac = SE_DATATRANSFER_DEFAULT(output, hmac_len);
  SE_addDataOutput(se_cmd, &out_hmac);

  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * GCM buffer encryption or decryption.
 ******************************************************************************/
sl_status_t sl_se_gcm_crypt_and_tag(sl_se_command_context_t *cmd_ctx,
                                    const sl_se_key_descriptor_t *key,
                                    sl_se_cipher_operation_t mode,
                                    size_t length,
                                    const unsigned char *iv,
                                    size_t iv_len,
                                    const unsigned char *add,
                                    size_t add_len,
                                    const unsigned char *input,
                                    unsigned char *output,
                                    size_t tag_len,
                                    unsigned char *tag)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  uint8_t tagbuf[16];
  sl_status_t status = SL_STATUS_OK;

  // Check input parameters.
  if (cmd_ctx == NULL || key == NULL || iv == NULL || tag == NULL
      || ((add_len > 0) && (add == NULL))
      || ((length > 0) && (input == NULL || output == NULL))
      || ((tag_len < 4) || (tag_len > 16))) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (// IV length is required to be 96 bits for SE.
    (iv_len != 96 / 8)
    // AD is limited to 2^64 bits, so 2^61 bytes.
    // However, on 32 bit platforms, that amount of continous data cannot be
    // available.
    // || (((uint64_t)add_len) >> 61 != 0)
    ) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  switch (key->type) {
    case SL_SE_KEY_TYPE_AES_128:
    case SL_SE_KEY_TYPE_AES_192:
    case SL_SE_KEY_TYPE_AES_256:
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  if (mode == SL_SE_DECRYPT) {
    // Extract plaintext first.
    sli_se_command_init(cmd_ctx,
                        SLI_SE_COMMAND_AES_GCM_DECRYPT | ((tag_len & 0xFF) << 8));

    sli_add_key_parameters(cmd_ctx, key, status);
    SE_addParameter(se_cmd, add_len);
    SE_addParameter(se_cmd, length);

    sli_add_key_metadata(cmd_ctx, key, status);
    sli_add_key_input(cmd_ctx, key, status);

    SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, iv_len);
    SE_addDataInput(se_cmd, &iv_in);

    SE_DataTransfer_t aad_in = SE_DATATRANSFER_DEFAULT(add, add_len);
    SE_addDataInput(se_cmd, &aad_in);

    SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, length);
    SE_addDataInput(se_cmd, &data_in);

    SE_DataTransfer_t tag_in = SE_DATATRANSFER_DEFAULT(tag, tag_len);
    SE_addDataInput(se_cmd, &tag_in);

    SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
    if (output == NULL) {
      data_out.length |= SE_DATATRANSFER_DISCARD;
    }
    SE_addDataOutput(se_cmd, &data_out);

    // Execute GCM operation.
    status = sli_se_execute_and_wait(cmd_ctx);
    if ((status != SL_STATUS_OK) && (status != SL_STATUS_INVALID_SIGNATURE)) {
      memset(output, 0, length);
      return status;
    }

    // Re-encrypt the extracted plaintext to generate the tag to match.
    input = output;
    output = NULL;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_AES_GCM_ENCRYPT);

  sli_add_key_parameters(cmd_ctx, key, status);
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  sli_add_key_metadata(cmd_ctx, key, status);
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, iv_len);
  SE_addDataInput(se_cmd, &iv_in);

  SE_DataTransfer_t aad_in = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_addDataInput(se_cmd, &aad_in);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &data_in);

  SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
  if (output == NULL) {
    data_out.length |= SE_DATATRANSFER_DISCARD;
  }
  SE_addDataOutput(se_cmd, &data_out);

  SE_DataTransfer_t mac_out = SE_DATATRANSFER_DEFAULT(tagbuf, sizeof(tagbuf));
  SE_addDataOutput(se_cmd, &mac_out);

  // Execute GCM operation.
  status = sli_se_execute_and_wait(cmd_ctx);
  if (status == SL_STATUS_OK) {
    // For encryption, copy requested tag size to output tag buffer.
    memcpy(tag, tagbuf, tag_len);
  } else {
    memset(output, 0, length);
  }

  return status;
}

/***************************************************************************//**
 * GCM buffer decryption and authentication.
 ******************************************************************************/
sl_status_t sl_se_gcm_auth_decrypt(sl_se_command_context_t *cmd_ctx,
                                   const sl_se_key_descriptor_t *key,
                                   size_t length,
                                   const unsigned char *iv,
                                   size_t iv_len,
                                   const unsigned char *add,
                                   size_t add_len,
                                   const unsigned char *input,
                                   unsigned char *output,
                                   size_t tag_len,
                                   const unsigned char *tag)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status = SL_STATUS_OK;

  // Check input parameters.
  if (cmd_ctx == NULL || key == NULL || iv == NULL || tag == NULL
      || ((add_len > 0) && (add == NULL))
      || ((length > 0) && (input == NULL || output == NULL))
      || ((tag_len < 4) || (tag_len > 16))) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (// IV length is required to be 96 bits for SE.
    (iv_len != 96 / 8)
    // AD is limited to 2^64 bits, so 2^61 bytes.
    // However, on 32 bit platforms, that amount of continous data cannot be
    // available.
    // || (((uint64_t)add_len) >> 61 != 0)
    ) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  switch (key->type) {
    case SL_SE_KEY_TYPE_AES_128: // Fallthrough
    case SL_SE_KEY_TYPE_AES_192: // Fallthrough
    case SL_SE_KEY_TYPE_AES_256:
      break;

    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx,
                      SLI_SE_COMMAND_AES_GCM_DECRYPT | ((tag_len & 0xFF) << 8));

  sli_add_key_parameters(cmd_ctx, key, status);
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  sli_add_key_metadata(cmd_ctx, key, status);
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, iv_len);
  SE_addDataInput(se_cmd, &iv_in);

  SE_DataTransfer_t aad_in = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_addDataInput(se_cmd, &aad_in);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &data_in);

  SE_DataTransfer_t tag_in = SE_DATATRANSFER_DEFAULT(tag, tag_len);
  SE_addDataInput(se_cmd, &tag_in);

  SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
  if (output == NULL) {
    data_out.length |= SE_DATATRANSFER_DISCARD;
  }
  SE_addDataOutput(se_cmd, &data_out);

  // Execute GCM operation.
  status = sli_se_execute_and_wait(cmd_ctx);

  if (status != SL_STATUS_OK) {
    memset(output, 0, length);
  }

  return status;
}

/***************************************************************************//**
 * GCM streaming encryption/decryption, initial stage.
 ******************************************************************************/
sl_status_t sl_se_gcm_starts(sl_se_gcm_streaming_context_t *gcm_ctx,
                             sl_se_command_context_t *cmd_ctx,
                             const sl_se_key_descriptor_t *key,
                             sl_se_cipher_operation_t mode,
                             const uint8_t *iv,
                             size_t iv_len,
                             const uint8_t *add,
                             size_t add_len)
{
  sl_status_t status = SL_STATUS_OK;

  // Check input parameters.
  if (gcm_ctx == NULL || cmd_ctx == NULL || key == NULL || iv == NULL
      || (add_len > 0 && add == NULL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if ((iv_len != 12)
      // AD are limited to 2^64 bits, so 2^61 bytes.
      // However, on 32 bit platforms, that amount of continous data cannot be
      // available.
      // || (((uint64_t)add_len) >> 61 != 0)
      ) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  memset(gcm_ctx, 0, sizeof(sl_se_gcm_streaming_context_t));

  gcm_ctx->mode = mode;
  gcm_ctx->len = 0;
  gcm_ctx->add_len = add_len;
  gcm_ctx->last_op = false;
  gcm_ctx->cmd_ctx = cmd_ctx;
  gcm_ctx->key = key;

  if ( add_len > 0 ) {
    // Start with encryption
    // Need to do encryption twice: once to create the context, the other to
    // pre-compute the tag in case there's no more data coming.
    // (SE doesn't support a type of 'finalize' command. All operations with
    // 'END' set need to contain some data).

    SE_Command_t *se_cmd = &cmd_ctx->command;
    SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, iv_len);
    SE_DataTransfer_t add_in = SE_DATATRANSFER_DEFAULT(add, add_len);
    SE_DataTransfer_t tag_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->tagbuf,
                                                        sizeof(gcm_ctx->tagbuf));

    sli_se_command_init(cmd_ctx,
                        SLI_SE_COMMAND_AES_GCM_ENCRYPT
                        | SLI_SE_COMMAND_OPTION_CONTEXT_WHOLE);

    sli_add_key_parameters(cmd_ctx, key, status);
    SE_addParameter(se_cmd, add_len);
    SE_addParameter(se_cmd, 0);

    sli_add_key_metadata(cmd_ctx, key, status);
    sli_add_key_input(cmd_ctx, key, status);

    SE_addDataInput(se_cmd, &iv_in);
    SE_addDataInput(se_cmd, &add_in);
    SE_addDataOutput(se_cmd, &tag_out);

    status = sli_se_execute_and_wait(cmd_ctx);
    if (status != SL_STATUS_OK) {
      memset(gcm_ctx->tagbuf, 0, sizeof(gcm_ctx->tagbuf));
      return status;
    }

    {
      SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT(iv, iv_len);
      SE_DataTransfer_t add_in = SE_DATATRANSFER_DEFAULT(add, add_len);
      SE_DataTransfer_t ctx_out =
        SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_enc, sizeof(gcm_ctx->se_ctx_enc));

      sli_se_command_init(cmd_ctx,
                          SLI_SE_COMMAND_AES_GCM_ENCRYPT
                          | SLI_SE_COMMAND_OPTION_CONTEXT_START);

      sli_add_key_parameters(cmd_ctx, key, status);
      SE_addParameter(se_cmd, add_len);
      SE_addParameter(se_cmd, 0);

      sli_add_key_metadata(cmd_ctx, key, status);
      sli_add_key_input(cmd_ctx, key, status);

      SE_addDataInput(se_cmd, &iv_in);
      SE_addDataInput(se_cmd, &add_in);
      SE_addDataOutput(se_cmd, &ctx_out);

      status = sli_se_execute_and_wait(cmd_ctx);
      if (status != SL_STATUS_OK) {
        memset(gcm_ctx->se_ctx_enc, 0, sizeof(gcm_ctx->se_ctx_enc));
        return status;
      }
    }

    // Do decryption if requested
    if (gcm_ctx->mode == SL_SE_DECRYPT) {
      SE_DataTransfer_t iv_in = SE_DATATRANSFER_DEFAULT((void*)iv, iv_len);
      SE_DataTransfer_t add_in = SE_DATATRANSFER_DEFAULT((void*)add, add_len);
      SE_DataTransfer_t ctx_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_dec,
                                                          sizeof(gcm_ctx->se_ctx_dec));

      sli_se_command_init(cmd_ctx,
                          SLI_SE_COMMAND_AES_GCM_DECRYPT
                          | SLI_SE_COMMAND_OPTION_CONTEXT_START);

      sli_add_key_parameters(cmd_ctx, key, status);
      SE_addParameter(se_cmd, add_len);
      SE_addParameter(se_cmd, 0);

      sli_add_key_metadata(cmd_ctx, key, status);
      sli_add_key_input(cmd_ctx, key, status);

      SE_addDataInput(se_cmd, &iv_in);
      SE_addDataInput(se_cmd, &add_in);
      SE_addDataOutput(se_cmd, &ctx_out);

      status = sli_se_execute_and_wait(cmd_ctx);
      if (status != SL_STATUS_OK) {
        memset(gcm_ctx->se_ctx_dec, 0, sizeof(gcm_ctx->se_ctx_dec));
        return status;
      }
    }
  } else {
    memcpy(gcm_ctx->se_ctx_enc, iv, iv_len);
  }

  return status;
}

/***************************************************************************//**
 * GCM streaming encryption/decryption, update stage.
 ******************************************************************************/
sl_status_t sl_se_gcm_update(sl_se_gcm_streaming_context_t *gcm_ctx,
                             size_t length,
                             const uint8_t *input,
                             uint8_t *output)
{
  uint32_t lena_lenc[4];
  sl_status_t status = SL_STATUS_OK;

  // Check input parameters.
  if (gcm_ctx == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (length == 0) {
    return SL_STATUS_OK;
  }
  if (length > 0 && (input == NULL || output == NULL)) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  // Total length is restricted to 2^39 - 256 bits, ie 2^36 - 2^5 bytes.
  // Also check for possible overflow.
  if (gcm_ctx->len + length < gcm_ctx->len
      || (uint64_t)gcm_ctx->len + length > 0xFFFFFFFE0ULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (gcm_ctx->last_op == true) {
    // We've already closed the input stream, no way back.
    return SL_STATUS_INVALID_PARAMETER;
  }

  SE_Command_t *se_cmd = &gcm_ctx->cmd_ctx->command;
  sl_se_command_context_t *cmd_ctx = gcm_ctx->cmd_ctx;

  // Approach:
  // Encryption: encrypt regularly with context store. If input length is not
  // a block multiple, close the operation and store the resulting tag in a
  // tag buffer.
  // Decryption: decrypt regularly with context store. For each decryption,
  // re-encrypt the decrypted data with context store. If input length is not a
  // block multiple, close both operations and store the tag from the re-encrypt
  // in a tag buffer.
  // In both cases, the (re-)encryption is done twice: once assuming there is
  // more data to follow, and once assuming this is the final block.
  //   Explanation: SE doesn't support a type of 'finalize' command. All
  //   operations with 'END' set need to contain some data.

  // Figure out whether we'll be closing out
  bool first_op = (gcm_ctx->add_len == 0 && gcm_ctx->len == 0) ? true : false;
  if ( length % 16 != 0) {
    // Indicate that this is our last op
    gcm_ctx->last_op = true;
  }
  if (first_op && gcm_ctx->last_op) {
    // Need to store length in context for later.
    gcm_ctx->len = length;
    return sl_se_gcm_crypt_and_tag(gcm_ctx->cmd_ctx,
                                   gcm_ctx->key,
                                   (sl_se_cipher_operation_t)gcm_ctx->mode,
                                   length,
                                   gcm_ctx->se_ctx_enc, 12,
                                   NULL, 0,
                                   input, output,
                                   // Compute max tag size (16 bytes)
                                   // and store it in the context
                                   16, gcm_ctx->tagbuf);
  }
  lena_lenc[0] = __REV(gcm_ctx->add_len >> 29);
  lena_lenc[1] = __REV((gcm_ctx->add_len << 3) & 0xFFFFFFFFUL);
  lena_lenc[2] = __REV((gcm_ctx->len + length) >> 29);
  lena_lenc[3] = __REV(((gcm_ctx->len + length) << 3) & 0xFFFFFFFFUL);

  gcm_ctx->len += length;

  if (gcm_ctx->mode == SL_SE_DECRYPT) {
    // Run decryption first
    SE_DataTransfer_t iv_ctx_in = SE_DATATRANSFER_DEFAULT(
      first_op ? gcm_ctx->se_ctx_enc : gcm_ctx->se_ctx_dec,
      first_op ? 12 : sizeof(gcm_ctx->se_ctx_dec));

    SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT((void*)input, length);
    SE_DataTransfer_t lenalenc_in = SE_DATATRANSFER_DEFAULT(lena_lenc, sizeof(lena_lenc));
    SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
    SE_DataTransfer_t ctx_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_dec,
                                                        sizeof(gcm_ctx->se_ctx_dec));
    SE_DataTransfer_t mac_in = SE_DATATRANSFER_DEFAULT(gcm_ctx->tagbuf,
                                                       sizeof(gcm_ctx->tagbuf));

    sli_se_command_init(cmd_ctx,
                        SLI_SE_COMMAND_AES_GCM_DECRYPT
                        | (first_op
                           ? SLI_SE_COMMAND_OPTION_CONTEXT_START
                           : (gcm_ctx->last_op
                              ? SLI_SE_COMMAND_OPTION_CONTEXT_END
                              : SLI_SE_COMMAND_OPTION_CONTEXT_ADD)));

    sli_add_key_parameters(cmd_ctx, gcm_ctx->key, status);
    SE_addParameter(se_cmd, 0);
    SE_addParameter(se_cmd, length);

    sli_add_key_metadata(cmd_ctx, gcm_ctx->key, status);
    sli_add_key_input(cmd_ctx, gcm_ctx->key, status);

    SE_addDataInput(se_cmd, &iv_ctx_in);
    SE_addDataInput(se_cmd, &data_in);
    SE_addDataOutput(se_cmd, &data_out);
    if (!gcm_ctx->last_op) {
      SE_addDataOutput(se_cmd, &ctx_out);
    } else {
      SE_addDataInput(se_cmd, &lenalenc_in);
      SE_addDataInput(se_cmd, &mac_in);
    }

    status = sli_se_execute_and_wait(cmd_ctx);
    if ((status != SL_STATUS_OK) && (status != SL_STATUS_INVALID_SIGNATURE)) {
      memset(output, 0, length);
      memset(gcm_ctx->se_ctx_dec, 0, sizeof(gcm_ctx->se_ctx_dec));
      return status;
    }
  }

  if (!gcm_ctx->last_op) {
    // We need to do the final calculation first, such that we keep the input
    // context intact.

    SE_DataTransfer_t iv_ctx_in =
      SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_enc,
                              first_op ? 12 : sizeof(gcm_ctx->se_ctx_enc));
    SE_DataTransfer_t data_in =
      SE_DATATRANSFER_DEFAULT(gcm_ctx->mode == SL_SE_ENCRYPT
                              ? (void*)input : (void*)output,
                              length);
    SE_DataTransfer_t lenalenc_in = SE_DATATRANSFER_DEFAULT(&lena_lenc[0],
                                                            sizeof(lena_lenc));
    SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(NULL, length);
    SE_DataTransfer_t tag_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->tagbuf,
                                                        sizeof(gcm_ctx->tagbuf));

    sli_se_command_init(cmd_ctx,
                        SLI_SE_COMMAND_AES_GCM_ENCRYPT
                        | (first_op
                           ? SLI_SE_COMMAND_OPTION_CONTEXT_WHOLE
                           : SLI_SE_COMMAND_OPTION_CONTEXT_END));

    sli_add_key_parameters(cmd_ctx, gcm_ctx->key, status);
    SE_addParameter(se_cmd, 0);
    SE_addParameter(se_cmd, length);

    sli_add_key_metadata(cmd_ctx, gcm_ctx->key, status);
    sli_add_key_input(cmd_ctx, gcm_ctx->key, status);

    SE_addDataInput(se_cmd, &iv_ctx_in);
    SE_addDataInput(se_cmd, &data_in);
    if (!first_op) {
      SE_addDataInput(se_cmd, &lenalenc_in);
    }
    data_out.length |= SE_DATATRANSFER_DISCARD;
    SE_addDataOutput(se_cmd, &data_out);
    SE_addDataOutput(se_cmd, &tag_out);

    status = sli_se_execute_and_wait(cmd_ctx);
    if (status != SL_STATUS_OK) {
      memset(gcm_ctx->tagbuf, 0, sizeof(gcm_ctx->tagbuf));
      return status;
    }
  }

  {
    SE_DataTransfer_t iv_ctx_in =
      SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_enc,
                              first_op ? 12 : sizeof(gcm_ctx->se_ctx_enc));
    SE_DataTransfer_t data_in =
      SE_DATATRANSFER_DEFAULT(gcm_ctx->mode == SL_SE_ENCRYPT
                              ? (void*)input
                              : (void*)output, length);
    SE_DataTransfer_t lenalenc_in = SE_DATATRANSFER_DEFAULT(&lena_lenc[0],
                                                            sizeof(lena_lenc));

    SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
    SE_DataTransfer_t tag_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->tagbuf,
                                                        sizeof(gcm_ctx->tagbuf));
    SE_DataTransfer_t ctx_out = SE_DATATRANSFER_DEFAULT(gcm_ctx->se_ctx_enc,
                                                        sizeof(gcm_ctx->se_ctx_enc));

    sli_se_command_init(cmd_ctx,
                        SLI_SE_COMMAND_AES_GCM_ENCRYPT
                        | (first_op
                           ? SLI_SE_COMMAND_OPTION_CONTEXT_START
                           : (gcm_ctx->last_op
                              ? SLI_SE_COMMAND_OPTION_CONTEXT_END
                              : SLI_SE_COMMAND_OPTION_CONTEXT_ADD)));

    sli_add_key_parameters(cmd_ctx, gcm_ctx->key, status);
    SE_addParameter(se_cmd, 0);
    SE_addParameter(se_cmd, length);

    sli_add_key_metadata(cmd_ctx, gcm_ctx->key, status);
    sli_add_key_input(cmd_ctx, gcm_ctx->key, status);

    SE_addDataInput(se_cmd, &iv_ctx_in);
    SE_addDataInput(se_cmd, &data_in);
    if (gcm_ctx->last_op) {
      SE_addDataInput(se_cmd, &lenalenc_in);
    }
    if (gcm_ctx->mode == SL_SE_DECRYPT) {
      data_out.data = NULL;
      data_out.length |= SE_DATATRANSFER_DISCARD;
    }
    SE_addDataOutput(se_cmd, &data_out);

    if (gcm_ctx->last_op) {
      SE_addDataOutput(se_cmd, &tag_out);
    } else {
      SE_addDataOutput(se_cmd, &ctx_out);
    }

    status = sli_se_execute_and_wait(cmd_ctx);

    if (status != SL_STATUS_OK) {
      if (gcm_ctx->last_op) {
        memset(gcm_ctx->tagbuf, 0, sizeof(gcm_ctx->tagbuf));
      } else {
        memset(gcm_ctx->se_ctx_enc, 0, sizeof(gcm_ctx->se_ctx_enc));
      }
    }

    return status;
  }
}

/***************************************************************************//**
 * GCM streaming encryption/decryption, finish stage.
 ******************************************************************************/
sl_status_t sl_se_gcm_finish(sl_se_gcm_streaming_context_t *gcm_ctx,
                             uint8_t *tag,
                             size_t   tag_len)
{
  if (gcm_ctx == NULL || tag == NULL || tag_len < 4 || tag_len > 16) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (gcm_ctx->add_len == 0 && gcm_ctx->len == 0) {
    return sl_se_gcm_crypt_and_tag(gcm_ctx->cmd_ctx,
                                   gcm_ctx->key,
                                   SL_SE_ENCRYPT,
                                   0,
                                   gcm_ctx->se_ctx_enc,
                                   12,
                                   NULL, 0,
                                   NULL, NULL,
                                   tag_len, tag);
  }

  memcpy(tag, gcm_ctx->tagbuf, tag_len);
  return SL_STATUS_OK;
}

#if (defined(_SILICON_LABS_SECURITY_FEATURE) \
  && (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT))
/***************************************************************************//**
 * ChaCha20 buffer encryption/decryption, as defined by RFC8439 section 2.4.
 ******************************************************************************/
sl_status_t sl_se_chacha20_crypt(sl_se_command_context_t *cmd_ctx,
                                 sl_se_cipher_operation_t mode,
                                 const sl_se_key_descriptor_t *key,
                                 size_t length,
                                 const unsigned char initial_counter[4],
                                 const unsigned char nonce[12],
                                 const unsigned char *input,
                                 unsigned char *output)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  if (cmd_ctx == NULL || key == NULL || initial_counter == NULL || nonce == NULL
      || input == NULL || output == NULL) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (key->type != SL_SE_KEY_TYPE_CHACHA20) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx,
                      (mode == SL_SE_ENCRYPT
                       ? SLI_SE_COMMAND_CHACHA20_ENCRYPT
                       : SLI_SE_COMMAND_CHACHA20_DECRYPT)
                      | SLI_SE_COMMAND_OPTION_CONTEXT_WHOLE);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, status);

  // Add initial counter to command
  SE_DataTransfer_t counter = SE_DATATRANSFER_DEFAULT(initial_counter, 4);
  SE_addDataInput(se_cmd, &counter);

  // Add nonce/IV to command
  SE_DataTransfer_t iv = SE_DATATRANSFER_DEFAULT(nonce, 12);
  SE_addDataInput(se_cmd, &iv);

  // Add input data to command
  SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &in);

  // Request output data from command
  SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(output, length);
  SE_addDataOutput(se_cmd, &out);

  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * ChaCha20-Poly1305 authenticated encryption with additional data, as defined
 * by RFC8439 section 2.8.
 ******************************************************************************/
sl_status_t sl_se_chacha20_poly1305_encrypt_and_tag(sl_se_command_context_t *cmd_ctx,
                                                    const sl_se_key_descriptor_t *key,
                                                    size_t length,
                                                    const unsigned char nonce[12],
                                                    const unsigned char *add, size_t add_len,
                                                    const unsigned char *input,
                                                    unsigned char *output,
                                                    unsigned char *tag)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  // Check input parameters.
  if (cmd_ctx == NULL || key == NULL || nonce == NULL
      || ((add_len > 0) && (add == NULL))
      || ((length > 0) && (input == NULL))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (key->type != SL_SE_KEY_TYPE_CHACHA20) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_CHACHAPOLY_ENCRYPT);

  sli_add_key_parameters(cmd_ctx, key, status);
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  sli_add_key_metadata(cmd_ctx, key, status);
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t nonce_in = SE_DATATRANSFER_DEFAULT(nonce, 12);
  SE_addDataInput(se_cmd, &nonce_in);

  SE_DataTransfer_t aad_in = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_addDataInput(se_cmd, &aad_in);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &data_in);

  SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
  if (output == NULL) {
    data_out.length |= SE_DATATRANSFER_DISCARD;
  }
  SE_addDataOutput(se_cmd, &data_out);

  SE_DataTransfer_t mac_out = SE_DATATRANSFER_DEFAULT(tag, 16);
  if (tag == NULL) {
    mac_out.length |= SE_DATATRANSFER_DISCARD;
  }
  SE_addDataOutput(se_cmd, &mac_out);

  // Execute AEAD operation.
  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * ChaCha20-Poly1305 authenticated decryption with additional data, as defined
 * by RFC8439 section 2.8.
 ******************************************************************************/
sl_status_t sl_se_chacha20_poly1305_auth_decrypt(sl_se_command_context_t *cmd_ctx,
                                                 const sl_se_key_descriptor_t *key,
                                                 size_t length,
                                                 const unsigned char nonce[12],
                                                 const unsigned char *add, size_t add_len,
                                                 const unsigned char *input,
                                                 unsigned char *output,
                                                 const unsigned char tag[16])
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  // Check input parameters.
  if (cmd_ctx == NULL || key == NULL || nonce == NULL || tag == NULL
      || ((add_len > 0) && (add == NULL))
      || ((length > 0) && (input == NULL))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (key->type != SL_SE_KEY_TYPE_CHACHA20) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_CHACHAPOLY_DECRYPT);

  sli_add_key_parameters(cmd_ctx, key, status);
  SE_addParameter(se_cmd, add_len);
  SE_addParameter(se_cmd, length);

  sli_add_key_metadata(cmd_ctx, key, status);
  sli_add_key_input(cmd_ctx, key, status);

  SE_DataTransfer_t nonce_in = SE_DATATRANSFER_DEFAULT(nonce, 12);
  SE_addDataInput(se_cmd, &nonce_in);

  SE_DataTransfer_t aad_in = SE_DATATRANSFER_DEFAULT(add, add_len);
  SE_addDataInput(se_cmd, &aad_in);

  SE_DataTransfer_t data_in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &data_in);

  SE_DataTransfer_t mac_in = SE_DATATRANSFER_DEFAULT(tag, 16);
  SE_addDataInput(se_cmd, &mac_in);

  SE_DataTransfer_t data_out = SE_DATATRANSFER_DEFAULT(output, length);
  if (output == NULL) {
    data_out.length |= SE_DATATRANSFER_DISCARD;
  }
  SE_addDataOutput(se_cmd, &data_out);

  // Execute AEAD operation.
  return sli_se_execute_and_wait(cmd_ctx);
}

/***************************************************************************//**
 * Generate a MAC (message authentication code) for a given message, according
 * to RFC8439 section 2.8 but bypassing the encryption step.
 ******************************************************************************/
sl_status_t sl_se_poly1305_genkey_tag(sl_se_command_context_t *cmd_ctx,
                                      const sl_se_key_descriptor_t *key,
                                      size_t length,
                                      const unsigned char nonce[12],
                                      const unsigned char *input,
                                      unsigned char *tag)
{
  SE_Command_t *se_cmd = &cmd_ctx->command;
  sl_status_t status;

  if (cmd_ctx == NULL || key == NULL || nonce == NULL || tag == NULL
      || ((length > 0) && (input == NULL))) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  if (key->type != SL_SE_KEY_TYPE_CHACHA20) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  sli_se_command_init(cmd_ctx, SLI_SE_COMMAND_POLY1305_KEY_MAC);

  // Add key parameters to command
  sli_add_key_parameters(cmd_ctx, key, status);
  // Message size (number of bytes)
  SE_addParameter(se_cmd, length);

  // Add key metadata block to command
  sli_add_key_metadata(cmd_ctx, key, status);
  // Add key input block to command
  sli_add_key_input(cmd_ctx, key, status);

  // Add nonce/IV to command
  SE_DataTransfer_t iv = SE_DATATRANSFER_DEFAULT(nonce, 12);
  SE_addDataInput(se_cmd, &iv);

  // Add input data to command
  SE_DataTransfer_t in = SE_DATATRANSFER_DEFAULT(input, length);
  SE_addDataInput(se_cmd, &in);

  // Request tag from command
  SE_DataTransfer_t out = SE_DATATRANSFER_DEFAULT(tag, 16);
  SE_addDataOutput(se_cmd, &out);

  return sli_se_execute_and_wait(cmd_ctx);
}
#endif

/** @} (end addtogroup sl_se) */

#endif // defined(SEMAILBOX_PRESENT)
