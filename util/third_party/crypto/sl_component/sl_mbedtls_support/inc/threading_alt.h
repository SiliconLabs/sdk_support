/**************************************************************************/ /**
 * @file
 * @brief Threading primitive implementation for mbed TLS
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

#ifndef THREADING_ALT_H
#define THREADING_ALT_H

/***************************************************************************//**
 * \addtogroup sl_crypto
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_crypto_threading Threading Primitives
 * \brief Threading primitive implementation for mbed TLS
 *
 * This file contains the glue logic between the mbed TLS threading API and
 * two RTOS'es supported, being Micrium OS and FreeRTOS.
 * In order to enable support for Micrium OS the user must make sure
 * SL_CATALOG_MICRIUMOS_KERNEL_PRESENT is defined.
 * In order to enable support for FreeRTOS the user must make sure
 * SL_CATALOG_FREERTOS_KERNEL_PRESENT is defined.
 * For UC based applications the sl_component_catalog.h file should include
 * one of the above in order to determine the presence of a specific RTOS.
 * For non-UC based applications the application must explicitly define
 * one of the above in order to specify the presence of a specific RTOS.
 *
 * \note
 * In order to use the Silicon Labs Hardware Acceleration plugins in
 * multi-threaded applications, select
 * <b>Mbed TLS support for EFM32/EFR32 crypto acceleration</b> component.
 *
 * \{
 ******************************************************************************/

#include "mbedtls/threading.h"
#if defined(MBEDTLS_THREADING_ALT) && defined(MBEDTLS_THREADING_C)

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined(SL_CATALOG_MICRIUMOS_KERNEL_PRESENT)

#define SL_THREADING_ALT

#include "em_assert.h"
#include <kernel/include/os.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef OS_MUTEX mbedtls_threading_mutex_t;

/**
 * \brief          Initialize a given mutex
 *
 * \param mutex    Pointer to the mutex needing initialization
 */
static inline void THREADING_InitMutex(mbedtls_threading_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexCreate(mutex, "dynamic", &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
}

/**
 * \brief          Free a given mutex
 *
 * \param mutex    Pointer to the mutex being freed
 */
static inline void THREADING_FreeMutex(mbedtls_threading_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexDel(mutex, OS_OPT_DEL_ALWAYS, &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
}

/**
 * \brief          Pend on a mutex
 *
 * \param mutex    Pointer to the mutex being pended on
 *
 * \return         RTOS_ERR_NONE on success, error code otherwise.
 */
static inline int THREADING_TakeMutexBlocking(mbedtls_threading_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexPend(mutex,
              0,
              OS_OPT_PEND_BLOCKING,
              NULL,
              &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
  return (err.Code == RTOS_ERR_NONE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

/**
 * \brief          Try to own a mutex without waiting
 *
 * \param mutex    Pointer to the mutex being tested
 *
 * \return         RTOS_ERR_NONE on success (= mutex successfully owned), error code otherwise.
 */
static inline int THREADING_TakeMutexNonBlocking(mbedtls_threading_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexPend(mutex,
              0,
              OS_OPT_PEND_NON_BLOCKING,
              NULL,
              &err);
  return (err.Code == RTOS_ERR_NONE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

/**
 * \brief          Release a mutex
 *
 * \param mutex    Pointer to the mutex being released
 *
 * \return         RTOS_ERR_NONE on success, error code otherwise.
 */
static inline int THREADING_GiveMutex(mbedtls_threading_mutex_t *mutex)
{
  RTOS_ERR err;
  OSMutexPost(mutex, OS_OPT_POST_NONE, &err);
  EFM_ASSERT(err.Code == RTOS_ERR_NONE);
  return (err.Code == RTOS_ERR_NONE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

#ifdef __cplusplus
}
#endif

#endif /* SL_CATALOG_MICRIUMOS_KERNEL_PRESENT */

#if defined(SL_CATALOG_FREERTOS_KERNEL_PRESENT)

#define SL_THREADING_ALT

#include "em_assert.h"
#include "FreeRTOS.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef StaticSemaphore_t mbedtls_threading_mutex_t;

static inline void THREADING_InitMutex(mbedtls_threading_mutex_t *mutex)
{
  SemaphoreHandle_t handle = xSemaphoreCreateMutexStatic(mutex);

  // Sanity check that the returned handle is equal to the mutex address, as
  // it should be by design. This means that we don't have to explicitly store
  // the handle, but can rather derive it from the mutex directly instead.
  EFM_ASSERT(handle == (SemaphoreHandle_t)mutex);
}

static inline void THREADING_FreeMutex(mbedtls_threading_mutex_t *mutex)
{
  vSemaphoreDelete((SemaphoreHandle_t)mutex);
}

static inline int THREADING_TakeMutexBlocking(mbedtls_threading_mutex_t *mutex)
{
  BaseType_t status =
    xSemaphoreTake((SemaphoreHandle_t)mutex, (TickType_t) portMAX_DELAY);
  return (status == pdTRUE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

static inline int THREADING_TakeMutexNonBlocking(mbedtls_threading_mutex_t *mutex)
{
  BaseType_t status =
    xSemaphoreTake((SemaphoreHandle_t)mutex, (TickType_t) 0);
  return (status == pdTRUE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

static inline int THREADING_GiveMutex(mbedtls_threading_mutex_t *mutex)
{
  BaseType_t status = xSemaphoreGive((SemaphoreHandle_t)mutex);
  EFM_ASSERT(status == pdTRUE);
  return (status == pdTRUE ? 0 : MBEDTLS_ERR_THREADING_MUTEX_ERROR);
}

#ifdef __cplusplus
}
#endif

#endif /* SL_CATALOG_FREERTOS_KERNEL_PRESENT */

#ifdef __cplusplus
extern "C" {
#endif

/* Forward declaration of threading_set_alt */
void mbedtls_threading_set_alt(void (*mutex_init)(mbedtls_threading_mutex_t *),
                               void (*mutex_free)(mbedtls_threading_mutex_t *),
                               int (*mutex_lock)(mbedtls_threading_mutex_t *),
                               int (*mutex_unlock)(mbedtls_threading_mutex_t *) );

/**
 * \brief          Helper function for setting up the mbed TLS threading subsystem
 */
static inline void THREADING_setup(void)
{
  mbedtls_threading_set_alt(&THREADING_InitMutex,
                            &THREADING_FreeMutex,
                            &THREADING_TakeMutexBlocking,
                            &THREADING_GiveMutex);
}

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_THREADING_ALT && MBEDTLS_THREADING_C */

/** \} (end addtogroup sl_crypto_threading) */
/** \} (end addtogroup sl_crypto) */

#endif /* THREADING_ALT_H */
