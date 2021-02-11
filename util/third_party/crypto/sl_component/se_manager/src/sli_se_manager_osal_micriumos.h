/**************************************************************************/ /**
 * @file
 * @brief OS abstraction primitives for the SE Manager on MicriumOS
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

#ifndef SE_MANAGER_OSAL_MICRIUMOS_H
#define SE_MANAGER_OSAL_MICRIUMOS_H

#include <kernel/include/os.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Defines

/// In order to wait forever in blocking functions the user can pass the
/// following value.
#define SE_MANAGER_OSAL_WAIT_FOREVER  (0)
/// In order to return immediately in blocking functions the user can pass the
/// following value.
#define SE_MANAGER_OSAL_NON_BLOCKING  (-1)

/// Priority to use for SEMBRX IRQ
#if defined(SE_MANAGER_USER_SEMBRX_IRQ_PRIORITY)
  #define SE_MANAGER_SEMBRX_IRQ_PRIORITY SE_MANAGER_USER_SEMBRX_IRQ_PRIORITY
#else
  #define SE_MANAGER_SEMBRX_IRQ_PRIORITY (0)
#endif

/// Determine if executing at interrupt level on ARM Cortex-M.
#define RUNNING_AT_INTERRUPT_LEVEL (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk)

// -----------------------------------------------------------------------------
// Typedefs

/// Completion type used to wait for and signal end of operation.
typedef OS_SEM   se_manager_osal_completion_t;

/// SE manager mutex definition for MicriumOS.
typedef OS_MUTEX se_manager_osal_mutex_t;

// -----------------------------------------------------------------------------
// Functions

/// Initialize a given mutex
__STATIC_INLINE
sl_status_t se_manager_osal_init_mutex(se_manager_osal_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexCreate(mutex, "dynamic", &err);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Free a given mutex
__STATIC_INLINE
sl_status_t se_manager_osal_free_mutex(se_manager_osal_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexDel(mutex, OS_OPT_DEL_ALWAYS, &err);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Acquire ownership of a mutex. If busy, wait until available.
__STATIC_INLINE
sl_status_t se_manager_osal_take_mutex(se_manager_osal_mutex_t *mutex)
{
  RTOS_ERR err;

  if ( (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U ) {
    // Illegal call from ISR
    return SL_STATUS_ISR;
  }

  OSMutexPend(mutex,
              0,
              OS_OPT_PEND_BLOCKING,
              NULL,
              &err);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Try to acquire ownership of a mutex without waiting.
__STATIC_INLINE sl_status_t
se_manager_osal_take_mutex_non_blocking(se_manager_osal_mutex_t *mutex)
{
  RTOS_ERR err;

  if ( (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U ) {
    // Illegal call from ISR
    return SL_STATUS_ISR;
  }

  OSMutexPend(mutex,
              0,
              OS_OPT_PEND_NON_BLOCKING,
              NULL,
              &err);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Release ownership of a mutex.
__STATIC_INLINE
sl_status_t se_manager_osal_give_mutex(se_manager_osal_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexPost(mutex, OS_OPT_POST_NONE, &err);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Initialize a given completion object
__STATIC_INLINE
sl_status_t se_manager_osal_init_completion(se_manager_osal_completion_t *p_comp)
{
  RTOS_ERR err;
  OSSemCreate((OS_SEM *) p_comp, NULL, (OS_SEM_CTR) 0, &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Free a given completion object
__STATIC_INLINE
sl_status_t se_manager_osal_free_completion(se_manager_osal_completion_t *p_comp)
{
  RTOS_ERR err;
  OSSemDel((OS_SEM *) p_comp, OS_OPT_DEL_ALWAYS, &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Wait for a completion object to be completed.
__STATIC_INLINE sl_status_t
se_manager_osal_wait_completion(se_manager_osal_completion_t *p_comp, int ticks)
{
  RTOS_ERR err;
  int ret;
  OSSemPend((OS_SEM *) p_comp,
            (OS_TICK) ticks,
            (OS_OPT) (ticks == SE_MANAGER_OSAL_NON_BLOCKING
                      ? OS_OPT_PEND_NON_BLOCKING : OS_OPT_PEND_BLOCKING),
            NULL,
            &err);
  if (err.Code == RTOS_ERR_NONE) {
    ret = SL_STATUS_OK;
  } else {
    if ( (err.Code == RTOS_ERR_TIMEOUT) || (err.Code == RTOS_ERR_WOULD_BLOCK) ) {
      ret = SL_STATUS_TIMEOUT;
    } else {
      /* Assert that no other error codes occur. */
      EFM_ASSERT(false);
      ret = SL_STATUS_FAIL;
    }
  }
  return ret;
}

// Complete a completion object.
__STATIC_INLINE
sl_status_t se_manager_osal_complete(se_manager_osal_completion_t* p_comp)
{
  RTOS_ERR err;
  OSSemPost((OS_SEM*) p_comp, (OS_OPT) OS_OPT_POST_1, &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
  return (err.Code == RTOS_ERR_NONE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

#ifdef __cplusplus
}
#endif

#endif // SE_MANAGER_OSAL_MICRIUMOS_H
