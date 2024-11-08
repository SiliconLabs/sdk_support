/*
 * Common and shared functions used by multiple modules in the Mbed TLS
 * library.
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

// This files is not part of the tinycript librairy. It is used to define function tinycript requires that are not present in the Simplicity SDK mbedtls fork

#include "mbedtls/platform_util.h"
#include <tinycrypt/tinycrypt_util.h>

#if defined(MBEDTLS_PLATFORM_FAULT_CALLBACKS)
#include "platform_fault.h"
#else
static void mbedtls_platform_fault()
{
}
#endif

/* Parameters for the linear congruential generator used as a non-cryptographic
 * random number generator. The same parameters are used by e.g. ANSI C. */
#define RAND_MULTIPLIER 1103515245
#define RAND_INCREMENT  12345
#define RAND_MODULUS    0x80000000

/* Max number of loops for mbedtls_platform_random_delay. */
#define MAX_RAND_DELAY 100

/* This function implements a non-cryptographic random number generator based
 * on the linear congruential generator algorithm. Additionally, if the
 * MBEDTLS_ENTROPY_HARDWARE_ALT flag is defined, the seed is set at the first
 * call of this function with using a hardware random number generator and
 * changed every RAND_SEED_LIFE number of iterations.
 *
 * The value of the returned number is in the range [0; 0xffff].
 *
 * Note: The range of values with a 16-bit precision is related to the modulo
 * parameter of the generator and the fact that the function does not return the
 * full value of the internal state of the generator.
 */
static uint32_t mbedtls_platform_random_uint16(void)
{
  /* Set random_state - the first random value should not be zero. */
  static uint32_t random_state = RAND_INCREMENT;
#if defined(MBEDTLS_ENTROPY_HARDWARE_ALT)
  static uint32_t random_seed_life = 0;
  if (0 < random_seed_life) {
    --random_seed_life;
  } else {
    size_t olen = 0;
    uint32_t hw_random;
    mbedtls_hardware_poll(NULL, (unsigned char *)&hw_random, sizeof(hw_random), &olen);
    if (olen == sizeof(hw_random)) {
      random_state ^= hw_random;
      random_seed_life = RAND_SEED_LIFE;
    }
  }
#endif /* MBEDTLS_ENTROPY_HARDWARE_ALT */
  random_state = ((random_state * RAND_MULTIPLIER) + RAND_INCREMENT) % RAND_MODULUS;
  /* Do not return the entire random_state to hide generator predictability for
     * the next iteration */
  return ((random_state >> 15) & 0xffff);
}

uint32_t mbedtls_platform_random_uint32(void)
{
  return ((mbedtls_platform_random_uint16() << 16) | mbedtls_platform_random_uint16());
}

uint32_t mbedtls_platform_random_in_range(uint32_t num)
{
  return mbedtls_platform_random_uint32() % num;
}

void mbedtls_platform_random_delay(void)
{
#if defined(MBEDTLS_FI_COUNTERMEASURES)
  uint32_t rn_1, rn_2, rn_3;
  volatile size_t i = 0;
  uint8_t shift;
  rn_1 = mbedtls_platform_random_in_range(MAX_RAND_DELAY);
  rn_2 = mbedtls_platform_random_in_range(0xffffffff) + 1;
  rn_3 = mbedtls_platform_random_in_range(0xffffffff) + 1;
  do {
    i++;
    /* Dummy calculations to increase the time between iterations and
         * make side channel attack more difficult by reducing predictability
         * of its behaviour. */
    shift = (rn_2 & 0x07) + 1;
    if (i % 2)
      rn_2 = (rn_2 >> shift) | (rn_2 << (32 - shift));
    else
      rn_3 = (rn_3 << shift) | (rn_3 >> (32 - shift));
    rn_2 ^= rn_3;
  } while (i < rn_1 || rn_2 == 0 || rn_3 == 0);
#endif /* MBEDTLS_FI_COUNTERMEASURES */
  return;
}

void mbedtls_platform_random_buf(uint8_t *buf, size_t len)
{
  volatile size_t flow_control = 0, flow_control_check = len;
  uint16_t val;
  while (len > 1) {
    val          = mbedtls_platform_random_uint16();
    buf[len - 1] = (uint8_t)val;
    buf[len - 2] = (uint8_t)(val >> 8);
    len -= 2;
    flow_control += 2;
  }
  if (len == 1) {
    buf[0] = (uint8_t)mbedtls_platform_random_uint16();
    flow_control++;
  }
  if (flow_control == flow_control_check) {
    return;
  }
  mbedtls_platform_fault();
}

void *mbedtls_platform_memset(void *ptr, int value, size_t num)
{
  size_t i, start_offset = 0;
  volatile size_t flow_counter = 0;
  volatile char *b             = ptr;
  char rnd_data;
  if (num > 0) {
    start_offset = (size_t)mbedtls_platform_random_in_range((uint32_t)num);
    rnd_data     = (char)mbedtls_platform_random_in_range(256);
    /* Perform a memset operations with random data and start from a random
         * location */
    for (i = start_offset; i < num; ++i) {
      b[i] = rnd_data;
      flow_counter++;
    }
    /* Start from a random location with target data */
    for (i = start_offset; i < num; ++i) {
      b[i] = value;
      flow_counter++;
    }
    /* Second memset operation with random data */
    for (i = 0; i < start_offset; ++i) {
      b[i] = rnd_data;
      flow_counter++;
    }
    /* Finish memset operation with correct data */
    for (i = 0; i < start_offset; ++i) {
      b[i] = value;
      flow_counter++;
    }
  }
  /* check the correct number of iterations */
  if (flow_counter == 2 * num) {
    mbedtls_platform_random_delay();
    if (flow_counter == 2 * num) {
      return ptr;
    }
  }
  mbedtls_platform_fault();
  return NULL;
}

void *mbedtls_platform_memcpy(void *dst, const void *src, size_t num)
{
  size_t i;
  volatile size_t flow_counter = 0;
  if (num > 0) {
    /* Randomize start offset. */
    size_t start_offset = (size_t)mbedtls_platform_random_in_range((uint32_t)num);
    /* Randomize initial data to prevent leakage while copying */
    uint32_t data = mbedtls_platform_random_in_range(256);
    /* Use memset with random value at first to increase security - memset is
        not normally part of the memcpy function and here can be useed
        with regular, unsecured implementation */
    memset((void *)dst, data, num);
    /* Make a copy starting from a random location. */
    i = start_offset;
    do {
      ((char *)dst)[i] = ((char *)src)[i];
      flow_counter++;
    } while ((i = (i + 1) % num) != start_offset);
  }
  /* check the correct number of iterations */
  if (flow_counter == num) {
    mbedtls_platform_random_delay();
    if (flow_counter == num) {
      return dst;
    }
  }
  mbedtls_platform_fault();
  return NULL;
}