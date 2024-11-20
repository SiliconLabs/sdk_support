#ifndef TINYCRYPT_PLATFORM_UTIL_H
#define TINYCRYPT_PLATFORM_UTIL_H

#include <stddef.h>
#include <stdint.h>

#if defined(SL_MBEDTLS_USE_TINYCRYPT)
void mbedtls_platform_random_buf(uint8_t *buf, size_t len);
void *mbedtls_platform_memset(void *, int, size_t);
void *mbedtls_platform_memcpy(void *dst, const void *src, size_t num);
void mbedtls_platform_random_delay(void);
uint32_t mbedtls_platform_random_in_range(uint32_t num);
// int mbedtls_platform_memmove(void *dst, const void *src, size_t num);
// int mbedtls_platform_memequal(const void *buf1, const void *buf2, size_t num);
#endif // defined(SL_MBEDTLS_USE_TINYCRYPT)

#endif // TINYCRYPT_PLATFORM_UTIL_H