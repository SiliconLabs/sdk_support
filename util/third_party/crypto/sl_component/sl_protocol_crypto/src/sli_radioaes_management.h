/**************************************************************************/ /**
 * @file
 * @brief Threadsafe utilities for RADIOAES peripheral.
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
#ifndef SLI_RADIOAES_MANAGEMENT_H
#define SLI_RADIOAES_MANAGEMENT_H

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#include <stdint.h>

#if defined(RADIOAES_PRESENT)

/***************************************************************************//**
 * @addtogroup sli_protocol_crypto
 * @{
 ******************************************************************************/

typedef struct {
  uint32_t FETCHADDR;   ///< Fetcher Address
#if defined(_AES_FETCHDESCR_MASK)
  uint32_t FETCHDESCR;  ///< Fetcher Descriptor
#endif
  uint32_t FETCHLEN;    ///< Fetcher Length
  uint32_t FETCHTAG;    ///< Fetcher Tag
  uint32_t PUSHADDR;    ///< Pusher Address
#if defined(_AES_PUSHDESCR_MASK)
  uint32_t PUSHDESCR;   ///< Pusher Descriptor
#endif
  uint32_t PUSHLEN;     ///< Pusher Length
  uint32_t CTRL;        ///< Control register
} sli_radioaes_state_t;

/***************************************************************************//**
 * @brief          Acquire RADIOAES access
 *
 * @return         0 if successful, positive if preempted, negative on error
 ******************************************************************************/
int sli_radioaes_acquire(void);

/***************************************************************************//**
 * @brief          Release RADIOAES access
 *
 * @return         0 if successful, negative on error
 ******************************************************************************/
int sli_radioaes_release(void);

/***************************************************************************//**
 * @brief          Save RADIOAES register state to RAM
 *
 * @param ctx      Context struct to save register state into
 *
 * @return         0 if successful, negative on error
 ******************************************************************************/
int sli_radioaes_save_state(sli_radioaes_state_t *ctx);

/***************************************************************************//**
 * @brief          Restore RADIOAES register state from RAM
 *
 * @param ctx      Context struct to restore register state from
 *
 * @return         0 if successful, negative on error
 ******************************************************************************/
int sli_radioaes_restore_state(sli_radioaes_state_t *ctx);

#ifdef __cplusplus
}
#endif

/// @} (end addtogroup sli_protocol_crypto)
#endif // RADIOAES_PRESENT
/// @endcond
#endif // SLI_RADIOAES_MANAGEMENT_H
