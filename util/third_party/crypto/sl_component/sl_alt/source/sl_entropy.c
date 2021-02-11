/***************************************************************************//**
 * @file
 * @brief Entropy driver for Silicon Labs devices.
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

#if !defined(MBEDTLS_CONFIG_FILE)
#include "config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT) && defined(MBEDTLS_ENTROPY_C)
#include "mbedtls/entropy.h"

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
  #include "sl_se_manager.h"
  #include "sl_se_manager_entropy.h"
#endif

#if defined(CRYPTOACC_PRESENT)
  #include "sx_trng.h"
  #include "sx_errors.h"
  #include "cryptolib_types.h"
  #include "cryptoacc_management.h"
#endif

#if defined(TRNG_PRESENT) \
  && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95)
  #include "em_cmu.h"
  #include <string.h>
#endif

#if defined(_EFR_DEVICE)                            \
  && (defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)  \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95) )
  #include "rail.h"
  #include <string.h>
#endif

#if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)
#include "em_system.h"    // SYSTEM_ChipRevisionGet()
#endif

// -------------------------------------
// Defines

#define SL_ENTROPY_OK 0

#if defined(SEMAILBOX_PRESENT)
  #define SL_ENTROPY_SE_PRESENT
#endif

#if defined(CRYPTOACC_PRESENT)
  #define SL_ENTROPY_CRYPTOACC_PRESENT
#endif

#if defined(TRNG_PRESENT) \
  && !defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95)
  #define SL_ENTROPY_TRNG_PRESENT
  #define SL_TRNG_STARTUP_WAIT_RETRY 10000
#endif

#if defined(_EFR_DEVICE)                            \
  && (defined(_SILICON_LABS_GECKO_INTERNAL_SDID_80) \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)  \
  || defined(_SILICON_LABS_GECKO_INTERNAL_SDID_95) )
  #define SL_ENTROPY_RAIL_PRESENT
#endif

// -------------------------------------
// Local function prototypes

#if defined(SL_ENTROPY_SE_PRESENT)
static int se_get_random(unsigned char *output,
                         size_t len,
                         size_t *out_len);
#endif

#if defined(SL_ENTROPY_CRYPTOACC_PRESENT)
static int cryptoacc_get_random(unsigned char *output,
                                size_t len,
                                size_t *out_len);
#endif

#if defined(SL_ENTROPY_TRNG_PRESENT)
static int trng_init(void);
static void trng_soft_reset(void);
static void trng_clear_fifo(void);
static int trng_check_status(void);
static void trng_read_chunk(unsigned char *output, size_t len);
static int trng_get_random(unsigned char *output,
                           size_t len,
                           size_t *out_len);
#endif

#if defined(SL_ENTROPY_RAIL_PRESENT)
static int rail_get_random(unsigned char *output,
                           size_t len,
                           size_t *out_len);
#endif

// -------------------------------------
// Local function definitions

#if defined(SL_ENTROPY_SE_PRESENT)
static int se_get_random(unsigned char *output,
                         size_t len,
                         size_t *out_len)
{
  sl_status_t ret;
  sl_se_command_context_t cmd_ctx;

  // Initialize the SE manager.
  ret = sl_se_init();
  if (ret != SL_STATUS_OK) {
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
  }

  // Initialize command context
  ret = sl_se_init_command_context(&cmd_ctx);
  if (ret != SL_STATUS_OK) {
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
  }

  // Get entropy
  ret = sl_se_get_random(&cmd_ctx, output, len);

  if (ret == SL_STATUS_OK) {
    *out_len = len;
    return SL_ENTROPY_OK;
  } else {
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
  }
}
#endif // SL_ENTROPY_SE_PRESENT

#if defined(SL_ENTROPY_CRYPTOACC_PRESENT)
static int cryptoacc_get_random(unsigned char *output,
                                size_t len,
                                size_t *out_len)
{
  int lock_status;
  int trng_status;
  size_t requested_entropy_len = len;
  block_t data_out;
  size_t surplus_bytes = 0;
  uint32_t surplus_word = 0;

  trng_status = cryptoacc_trng_initialize();
  if (trng_status != 0) {
    return trng_status;
  }

  // The sx_rng_get_rand_blk function returns full 32-bit words
  // of random data. If the requested number of bytes (and output buffer)
  // is not a multiple of 4 bytes we need to get the remaining/surplus
  // bytes in an additional call.
  surplus_bytes = requested_entropy_len & 0x3;
  requested_entropy_len &= ~0x3;

  if (requested_entropy_len > 0U) {
    data_out = block_t_convert(output, requested_entropy_len);
    lock_status = cryptoacc_management_acquire();
    if (lock_status != 0) {
      return lock_status;
    }
    sx_trng_get_rand_blk(data_out);
    cryptoacc_management_release();
  }

  if (surplus_bytes != 0U) {
    data_out = block_t_convert(&surplus_word, 4U);
    lock_status = cryptoacc_management_acquire();
    if (lock_status != 0) {
      return lock_status;
    }
    sx_trng_get_rand_blk(data_out);
    cryptoacc_management_release();
    for (size_t i = 0; i < surplus_bytes; i++) {
      output[requested_entropy_len + i] = (surplus_word >> (i * 8)) & 0xFF;
    }
  }

  *out_len = len;
  return SL_ENTROPY_OK;
}
#endif // SL_ENTROPY_CRYPTOACC_PRESENT

#if defined(SL_ENTROPY_TRNG_PRESENT)
static int trng_init(void)
{
  TRNG0->CONTROL = TRNG_CONTROL_ENABLE
                   | TRNG_CONTROL_REPCOUNTIEN
                   | TRNG_CONTROL_APT64IEN
                   | TRNG_CONTROL_APT4096IEN
                   | TRNG_CONTROL_PREIEN
                   | TRNG_CONTROL_ALMIEN;

  trng_soft_reset();

  // Wait for TRNG to complete startup tests and start filling the FIFO.
  for (uint32_t i = 0; (TRNG0->FIFOLEVEL == 0) && (i < SL_TRNG_STARTUP_WAIT_RETRY); i++) {
    ;
  }

  if (TRNG0->FIFOLEVEL == 0) {
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
  }

  // Wait for FIFO to be filled before setting the keys
  while (TRNG0->FIFOLEVEL < 4u) ;

  TRNG0->KEY0 = TRNG0->FIFO;
  TRNG0->KEY1 = TRNG0->FIFO;
  TRNG0->KEY2 = TRNG0->FIFO;
  TRNG0->KEY3 = TRNG0->FIFO;

  trng_soft_reset();

  return SL_ENTROPY_OK;
}

static void trng_soft_reset(void)
{
  TRNG_TypeDef *trng = TRNG0;
  uint32_t ctrl = trng->CONTROL;

  ctrl |= TRNG_CONTROL_SOFTRESET;
  trng->CONTROL = ctrl;
  ctrl &= ~TRNG_CONTROL_SOFTRESET;
  trng->CONTROL = ctrl;
}

static void trng_clear_fifo(void)
{
  TRNG_TypeDef *trng = TRNG0;
  volatile uint32_t val32;

  // Empty FIFO
  while (trng->FIFOLEVEL) {
    val32 = trng->FIFO;
    (void)val32;
  }
}

static int trng_check_status(void)
{
  TRNG_TypeDef *trng = TRNG0;
  uint32_t status = trng->STATUS;

  if ((status & (TRNG_STATUS_PREIF
                 | TRNG_STATUS_REPCOUNTIF
                 | TRNG_STATUS_APT64IF
                 | TRNG_STATUS_APT4096IF
                 | TRNG_STATUS_ALMIF)) == 0) {
    return SL_ENTROPY_OK;
  }

  if (status & TRNG_STATUS_PREIF) {
    // On a preliminary noise alarm we clear the FIFO and clear
    // the alarm. The preliminary noise alarm is not critical.
    status &= ~TRNG_STATUS_PREIF;
    trng->STATUS = status;
    trng_clear_fifo();
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
  } else {
    // Clear alarm conditions by doing a TRNG soft reset.
    trng_soft_reset();
    if ((status & TRNG_STATUS_REPCOUNTIF)
        || (status & TRNG_STATUS_APT64IF)
        || (status & TRNG_STATUS_APT4096IF)
        || (status & TRNG_STATUS_ALMIF)) {
      return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    }
  }

  return SL_ENTROPY_OK;
}

static void trng_read_chunk(unsigned char *output, size_t len)
{
  TRNG_TypeDef *trng = TRNG0;
  uint32_t* out32 = (uint32_t *)output;
  uint32_t tmp;

  // Read known good available data.
  while (len >= 4) {
    *out32 = trng->FIFO;
    len -= 4;
    out32++;
  }
  if (len == 0) {
    return;
  }

  // Handle the case where len is not a multiple of 4
  // and FIFO data is available.
  tmp = trng->FIFO;
  memcpy((uint8_t *)out32, (const uint8_t *)&tmp, len);
}

static int trng_get_random(unsigned char *output,
                           size_t len,
                           size_t *out_len)
{
  TRNG_TypeDef *trng = TRNG0;
  unsigned char *outptr = output;

  size_t output_len = 0;
  size_t count = 0;
  size_t available_entropy;
  int ret = SL_ENTROPY_OK;

  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TRNG0;
  if ((trng->CONTROL & TRNG_CONTROL_ENABLE) == 0u) {
    ret = trng_init();
    if (ret != SL_ENTROPY_OK) {
      return ret;
    }
  }

  while (len > 0) {
    available_entropy = trng->FIFOLEVEL * 4;
    if (available_entropy == 0) {
      break;
    }

    // Check status for current data in FIFO
    // and handle any error conditions.
    ret = trng_check_status();

    // The TRNG output data did not pass the internal TRNG random tests.
    // Discard the bad data by setting output length to zero.
    // Return 0 (OK) in order to keep the entropy accumulator of mbedtls
    // running.
    if (ret != SL_ENTROPY_OK) {
      memset(output, 0, output_len);
      output_len = 0;
      ret = SL_ENTROPY_OK;
      break;
    }

    count = (len > available_entropy) ? available_entropy : len;
    trng_read_chunk(outptr, count);
    outptr += count;
    output_len += count;
    len -= count;
  }

  *out_len = output_len;
  return ret;
}
#endif // SL_ENTROPY_TRNG_PRESENT

#if defined(SL_ENTROPY_RAIL_PRESENT)
static int rail_get_random(unsigned char *output,
                           size_t len,
                           size_t *out_len)
{
  uint16_t rail_entropy_request_len;
  if (len > UINT16_MAX) {
    rail_entropy_request_len = UINT16_MAX;
  } else {
    rail_entropy_request_len = (uint16_t)len;
  }

  *out_len = (size_t)RAIL_GetRadioEntropy(RAIL_EFR32_HANDLE,
                                          (uint8_t *)output,
                                          rail_entropy_request_len);
  return SL_ENTROPY_OK;
}
#endif // SL_ENTROPY_RAIL_PRESENT

// -------------------------------------
// Global function definitions

int mbedtls_hardware_poll(void *data,
                          unsigned char *output,
                          size_t len,
                          size_t *olen)
{
  (void)data;

#if defined(SL_ENTROPY_SE_PRESENT)
  return se_get_random(output, len, olen);

#elif defined(SL_ENTROPY_CRYPTOACC_PRESENT)
  return cryptoacc_get_random(output, len, olen);

#elif defined(SL_ENTROPY_TRNG_PRESENT)
  // TRNG should be chosen if both RAIL and TRNG entropies are available,
  // except on xG13 devices with revision >= A3 ( see below ).

  #if defined(_SILICON_LABS_GECKO_INTERNAL_SDID_89)
  SYSTEM_ChipRevision_TypeDef rev;
  SYSTEM_ChipRevisionGet(&rev);

  // TRNG entropy on xG13 is only supported for >= Rev A3
  if ((rev.major == 1) && (rev.minor < 3)) {
    #if defined(SL_ENTROPY_RAIL_PRESENT)
    return rail_get_random(output, len, olen);
    #else
    return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;
    #endif
  }
  #endif // SDID_89

  return trng_get_random(output, len, olen);

#elif defined(SL_ENTROPY_RAIL_PRESENT)
  return rail_get_random(output, len, olen);

#else // SL_ENTROPY_SE/SL_ENTROPY_CRYPTOACC/SL_ENTROPY_TRNG/SL_ENTROPY_RAIL
  (void) output;
  (void) len;
  (void) olen;
  return MBEDTLS_ERR_ENTROPY_SOURCE_FAILED;

#endif
}

#endif // MBEDTLS_ENTROPY_HARDWARE_ALT && MBEDTLS_ENTROPY_C
