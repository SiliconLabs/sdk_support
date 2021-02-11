/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto common driver functions.
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
#ifndef SLI_PSA_DRIVER_COMMON_H
#define SLI_PSA_DRIVER_COMMON_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @brief
 *   Clear a memory location in a way that is guaranteed not be optimized away
 *   by the compiler.
 *
 * @param[in]  v
 *   Pointer to memory location.
 *
 * @param[in] n
 *   Number of bytes to clear.
 ******************************************************************************/
__STATIC_INLINE
void sli_psa_zeroize(void *v, size_t n)
{
  volatile unsigned char *p = v;
  while (n--) {
    *p++ = 0;
  }
}

#ifdef __cplusplus
}
#endif

/// @endcond

#endif // SLI_PSA_DRIVER_COMMON_H
