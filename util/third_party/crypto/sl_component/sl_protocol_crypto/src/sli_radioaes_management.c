/***************************************************************************//**
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
#include "em_device.h"

#if defined(RADIOAES_PRESENT)
/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

#include "sli_radioaes_management.h"
#include "sli_se_manager_osal.h"
#include "em_core.h"

#if defined(SL_SE_MANAGER_THREADING)
static se_manager_osal_mutex_t      radioaes_lock;
static volatile bool                radioaes_lock_initialized = false;
#endif

int sli_radioaes_acquire(void)
{
#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0 |= CMU_CLKEN0_RADIOAES;
#endif
  CMU->RADIOCLKCTRL = CMU_RADIOCLKCTRL_EN;
  if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U) {
    // IRQ: need to store & restore RADIOAES registers
    while (RADIOAES->STATUS & (AES_STATUS_FETCHERBSY | AES_STATUS_PUSHERBSY | AES_STATUS_SOFTRSTBSY)) {
      // Wait for completion
    }
    return 1;
  } else {
#if defined(SL_SE_MANAGER_THREADING)
    // Non-IRQ, RTOS available: take mutex
    // Initialize mutex if that hasn't happened yet
    CORE_DECLARE_IRQ_STATE;

    // Check flag first before going into a critical section, to avoid going into
    // a critical section on every single acquire() call. Since the _initialized
    // flag only transitions false -> true, we can in 99% of the calls avoid the
    // critical section.
    if (!radioaes_lock_initialized) {
      CORE_ENTER_CRITICAL();

      // Check the flag again after entering the critical section. Now that we're
      // in the critical section, we can be sure that we are the only ones looking
      // at the flag and no-one is interrupting us during its manipulation.
      if (!radioaes_lock_initialized) {
        se_manager_osal_init_mutex(&radioaes_lock);
        radioaes_lock_initialized = true;
      }

      CORE_EXIT_CRITICAL();
    }
    return (se_manager_osal_take_mutex(&radioaes_lock) != 0 ? -1 : 0);
#else
    // Non-IRQ, no RTOS: busywait
    while (RADIOAES->STATUS & (AES_STATUS_FETCHERBSY | AES_STATUS_PUSHERBSY | AES_STATUS_SOFTRSTBSY)) {
      // Wait for completion
    }
    return 0;
#endif
  }
}

int sli_radioaes_release(void)
{
  // IRQ: nothing to do
  if ((SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U) {
    return 0;
  }
#if defined(SL_SE_MANAGER_THREADING)
  // Non-IRQ, RTOS available: free mutex
  return (0L - se_manager_osal_give_mutex(&radioaes_lock) );
#else
  // Non-IRQ, no RTOS: nothing to do.
  return 0;
#endif
}

int sli_radioaes_save_state(sli_radioaes_state_t *ctx)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  ctx->FETCHADDR = RADIOAES->FETCHADDR;
#if defined(_AES_FETCHDESCR_MASK)
  ctx->FETCHDESCR = RADIOAES->FETCHDESCR;
#endif
  ctx->FETCHLEN = RADIOAES->FETCHLEN;
  ctx->FETCHTAG = RADIOAES->FETCHTAG;
  ctx->PUSHADDR = RADIOAES->PUSHADDR;
#if defined(_AES_PUSHDESCR_MASK)
  ctx->PUSHDESCR = RADIOAES->PUSHDESCR;
#endif
  ctx->PUSHLEN = RADIOAES->PUSHLEN;
  ctx->CTRL = RADIOAES->CTRL;
  CORE_EXIT_CRITICAL();
  return 0;
}

int sli_radioaes_restore_state(sli_radioaes_state_t *ctx)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  RADIOAES->FETCHADDR = ctx->FETCHADDR;
#if defined(_AES_FETCHDESCR_MASK)
  RADIOAES->FETCHDESCR = ctx->FETCHDESCR;
#endif
  RADIOAES->FETCHLEN = ctx->FETCHLEN;
  RADIOAES->FETCHTAG = ctx->FETCHTAG;
  RADIOAES->PUSHADDR = ctx->PUSHADDR;
#if defined(_AES_PUSHDESCR_MASK)
  RADIOAES->PUSHDESCR = ctx->PUSHDESCR;
#endif
  RADIOAES->PUSHLEN = ctx->PUSHLEN;
  RADIOAES->CTRL = ctx->CTRL;
  CORE_EXIT_CRITICAL();
  return 0;
}

/// @endcond
#endif //defined(RADIOAES_PRESENT)
