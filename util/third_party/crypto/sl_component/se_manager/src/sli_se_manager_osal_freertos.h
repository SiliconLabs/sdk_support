/**************************************************************************/ /**
 * @file
 * @brief OS abstraction layer primitives for SE manager on FreeRTOS
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

#ifndef SE_MANAGER_OSAL_FREERTOS_H
#define SE_MANAGER_OSAL_FREERTOS_H

#include "FreeRTOS.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Defines

/// In order to wait forever in blocking functions the user can pass the
/// following value.
#define SE_MANAGER_OSAL_WAIT_FOREVER  ((int)portMAX_DELAY)
/// In order to return immediately in blocking functions the user can pass the
/// following value.
#define SE_MANAGER_OSAL_NON_BLOCKING  (0)

/// Priority to use for SEMBRX IRQ
#if defined(SE_MANAGER_USER_SEMBRX_IRQ_PRIORITY)
  #define SE_MANAGER_SEMBRX_IRQ_PRIORITY SE_MANAGER_USER_SEMBRX_IRQ_PRIORITY
#else
  #define SE_MANAGER_SEMBRX_IRQ_PRIORITY (configMAX_SYSCALL_INTERRUPT_PRIORITY >> (8U - __NVIC_PRIO_BITS) )
#endif

#if  (SE_MANAGER_SEMBRX_IRQ_PRIORITY < (configMAX_SYSCALL_INTERRUPT_PRIORITY >> (8U - __NVIC_PRIO_BITS) ) )
  #error SEMBRX IRQ priority should be numerically higher than or equal to the syscall interrupt.
#endif

/// Determine if executing at interrupt level on ARM Cortex-M.
#define RUNNING_AT_INTERRUPT_LEVEL (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk)

// -----------------------------------------------------------------------------
// Typedefs

/// Completion object used to wait for and signal end of an operation.
typedef StaticSemaphore_t se_manager_osal_completion_t;
/// SE manager mutex definition for FreeRTOS.
typedef StaticSemaphore_t se_manager_osal_mutex_t;

// -----------------------------------------------------------------------------
// Functions

/// Initialize a mutex object.
__STATIC_INLINE
sl_status_t se_manager_osal_init_mutex(se_manager_osal_mutex_t *mutex)
{
  SemaphoreHandle_t handle = xSemaphoreCreateMutexStatic(mutex);

  // Sanity check that the returned handle is equal to the mutex address, as
  // it should be by design. This means that we don't have to explicitly store
  // the handle, but can rather derive it from the mutex directly instead.
  return (handle != (SemaphoreHandle_t)mutex ? SL_STATUS_FAIL : SL_STATUS_OK);
}

/// Free a mutex object.
__STATIC_INLINE
sl_status_t se_manager_osal_free_mutex(se_manager_osal_mutex_t *mutex)
{
  vSemaphoreDelete((SemaphoreHandle_t)mutex);
  return SL_STATUS_OK;
}

/// Acquire ownership of a mutex. If busy, wait until available.
__STATIC_INLINE
sl_status_t se_manager_osal_take_mutex(se_manager_osal_mutex_t *mutex)
{
  BaseType_t status;

  if ( (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U ) {
    // Illegal call from ISR
    return SL_STATUS_ISR;
  }

  status = xSemaphoreTake((SemaphoreHandle_t)mutex, (TickType_t) portMAX_DELAY);
  return (status == pdTRUE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Try to acquire ownership of a mutex without waiting.
__STATIC_INLINE
sl_status_t se_manager_osal_take_mutex_non_blocking(se_manager_osal_mutex_t *mutex)
{
  BaseType_t status;

  if ( (SCB->ICSR & SCB_ICSR_VECTACTIVE_Msk) != 0U ) {
    // Illegal call from ISR
    return SL_STATUS_ISR;
  }

  status = xSemaphoreTake((SemaphoreHandle_t)mutex, (TickType_t) 0);
  return (status == pdTRUE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Release ownership of a mutex.
__STATIC_INLINE
sl_status_t se_manager_osal_give_mutex(se_manager_osal_mutex_t *mutex)
{
  BaseType_t status = xSemaphoreGive((SemaphoreHandle_t)mutex);
  return (status == pdTRUE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

/// Initialize a completion object.
__STATIC_INLINE sl_status_t
se_manager_osal_init_completion(se_manager_osal_completion_t *p_comp)
{
  SemaphoreHandle_t handle = xSemaphoreCreateBinaryStatic(p_comp);
  EFM_ASSERT(handle == (SemaphoreHandle_t)p_comp);
  return (handle != (SemaphoreHandle_t)p_comp ? SL_STATUS_FAIL : SL_STATUS_OK);
}

/// Free a completion object.
__STATIC_INLINE sl_status_t
se_manager_osal_free_completion(se_manager_osal_completion_t *p_comp)
{
  vSemaphoreDelete((SemaphoreHandle_t)p_comp);
  return SL_STATUS_OK;
}

// Wait for a completion object to be completed.
__STATIC_INLINE sl_status_t
se_manager_osal_wait_completion(se_manager_osal_completion_t *p_comp, int ticks)
{
  return xSemaphoreTake( (SemaphoreHandle_t)p_comp, (TickType_t) ticks)
         == pdTRUE ? SL_STATUS_OK : SL_STATUS_TIMEOUT;
}

// Complete a completion object.
__STATIC_INLINE sl_status_t
se_manager_osal_complete(se_manager_osal_completion_t* p_comp)
{
  BaseType_t status;
  if (RUNNING_AT_INTERRUPT_LEVEL) {
    BaseType_t higher_priority_task_woken;
    status = xSemaphoreGiveFromISR( (SemaphoreHandle_t)p_comp,
                                    &higher_priority_task_woken);
  } else {
    status = xSemaphoreGive( (SemaphoreHandle_t)p_comp);
  }
  EFM_ASSERT(status == pdTRUE);
  return (status == pdTRUE ? SL_STATUS_OK : SL_STATUS_FAIL);
}

#ifdef __cplusplus
}
#endif

#endif // SE_MANAGER_OSAL_FREERTOS_H
