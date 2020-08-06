/***************************************************************************//**
 * @file
 * @brief This is an implementation of the Silicon Labs RTOS API for
 * Micrium. It provides some required functions
 * to tie together Micrium and EM3XX HAL code.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
// Include the RTOS API header for types and function prototypes
#include "../rtos.h"

// Micrium
#include "kernel/include/os.h"
#include "common/source/rtos/rtos_utils_priv.h"

// Ember includes
#include PLATFORM_HEADER

static uint8_t rtosSchedulerActive;
static uint8_t rtosInCritical;

// Scheduler Layer
// Start the RTOS scheduler
void rtosStartScheduler(void)
{
  rtosSchedulerActive = 1;
  OSSched();
}

// Suspend the scheduler
void rtosSuspendScheduler(void)
{
  RTOS_ERR err;
  rtosSchedulerActive++;
  OSSchedLock(&err);
}

// Resume the schduler
void rtosResumeScheduler(void)
{
  RTOS_ERR err;
  rtosSchedulerActive--;
  OSSchedUnlock(&err);
}

// Enter a critical section
uint8_t rtosEnterCritical(void)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  RTOS_ASSERT_CRITICAL(rtosInCritical < UINT8_MAX,
                       RTOS_ERR_NULL_PTR,
                       DEF_NULL);
  return ++rtosInCritical;
}

// Exit a critical section
uint8_t rtosExitCritical(void)
{
  uint8_t ret;
  CORE_DECLARE_IRQ_STATE;
  RTOS_ASSERT_CRITICAL(rtosInCritical > 0,
                       RTOS_ERR_NULL_PTR,
                       DEF_NULL);
  ret = --rtosInCritical;
  CORE_EXIT_ATOMIC();
  return ret;
}

RtosTask_t rtosGetCurrentTask(void)
{
  return (RtosTask_t)OSTCBCurPtr;
}

// EMIPSTACK-2135 TODO: how to allocate these?
static uint8_t mutexIndex = 0;
#define MUTEX_POOL_SIZE 3
OS_MUTEX mutexPool[MUTEX_POOL_SIZE];

// Mutex/Semaphore
RtosMutex_t rtosMutexCreate(void)
{
  RTOS_ERR err;
  assert(mutexIndex < MUTEX_POOL_SIZE);
  OS_MUTEX *mutex = mutexPool + mutexIndex;
  OSMutexCreate(mutex, "App Mutex", &err);
  assert(RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE);
  mutexIndex++;
  return (RtosMutex_t)mutex;
}

bool rtosMutexTake(RtosMutex_t mutex, uint32_t millisecs)
{
  RTOS_ERR  err;
  OSMutexPend((OS_MUTEX *)mutex,
              millisecs,             // These are OS ticks.
              OS_OPT_PEND_BLOCKING,  // Task will block.
              DEF_NULL,              // Timestamp is not used.
              &err);
  return (RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE);
}

bool rtosMutexGive(RtosMutex_t mutex)
{
  RTOS_ERR  err;
  OSMutexPost((OS_MUTEX *)mutex,
              OS_OPT_POST_NONE,
              &err);
  return (RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE);
}

void rtosMutexDelete(RtosMutex_t mutex)
{
  RTOS_ERR    err;
  OSMutexDel((OS_MUTEX *)mutex, OS_OPT_DEL_NO_PEND, &err);
  assert(RTOS_ERR_CODE_GET(err) == RTOS_ERR_NONE);
}
