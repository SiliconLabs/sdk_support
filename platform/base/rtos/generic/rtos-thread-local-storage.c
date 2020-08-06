/***************************************************************************//**
 * @file
 * @brief RTOS API functions related to thread local storage.
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
// Include the RTOS API header
#include "../rtos.h"

// Ember includes
#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "hal/hal.h"

// The number of global variables that can be tracked
#ifndef THREAD_LOCAL_STORAGE_COUNT
  #define THREAD_LOCAL_STORAGE_COUNT 3
#endif //THREAD_LOCAL_STORAGE_COUNT

// The number of threads sharing global variables in the system
#ifndef NUMBER_OF_THREADS
  #define NUMBER_OF_THREADS 2
#endif //NUMBER_OF_THREADS

// Globals for thread local storage
static void** tlsAddress[THREAD_LOCAL_STORAGE_COUNT];
static void*  tlsValues[NUMBER_OF_THREADS][THREAD_LOCAL_STORAGE_COUNT];
static RtosTask_t tlsThreadHandles[NUMBER_OF_THREADS];
static RtosMutex_t tlsGlobalMutex = NULL;

///////////////////////////////////////////////////////////////////////////////
// Simple Thread Local Storage Implementation
///////////////////////////////////////////////////////////////////////////////

void threadLocalStorageInit(void)
{
  // Initialize the mutex used for registering global variables
  if (tlsGlobalMutex == NULL) {
    tlsGlobalMutex = rtosMutexCreate();
  }
  assert(tlsGlobalMutex != NULL);
}

// Register a global variable that is shared by multiple threadsacross threads
int rtosRegisterSharedGlobal(void** address)
{
  RtosTask_t currentThread = rtosGetCurrentTask();
  int addrIndex, threadIndex;

  // Return an error if the mutex could not be initialized
  if (tlsGlobalMutex == NULL) {
    return EMBER_ERR_FATAL;
  }
  rtosMutexTake(tlsGlobalMutex, RTOS_MAX_DELAY);

  // Check for an open address slot for this global variable
  for (addrIndex = 0; addrIndex < THREAD_LOCAL_STORAGE_COUNT; addrIndex++) {
    if (tlsAddress[addrIndex] == 0 || tlsAddress[addrIndex] == address) {
      break;
    }
  }

  // Check for an open thread slot to track globals for this thread
  for (threadIndex = 0; threadIndex < NUMBER_OF_THREADS; threadIndex++) {
    if (tlsThreadHandles[threadIndex] == 0
        || tlsThreadHandles[threadIndex] == currentThread) {
      break;
    }
  }

  // Make sure that we found a valid address and thread index
  if ((addrIndex >= THREAD_LOCAL_STORAGE_COUNT)
      || (threadIndex >= NUMBER_OF_THREADS)) {
    rtosMutexGive(tlsGlobalMutex);
    return EMBER_ERR_FATAL;
  }

  // Now that we're sure we've found open slots add the address and thread id
  tlsAddress[addrIndex] = address;
  tlsThreadHandles[threadIndex] = currentThread;

  // Return the mutex
  rtosMutexGive(tlsGlobalMutex);

  return EMBER_SUCCESS;
}

static void taskReallySwitchIn(RtosTask_t task)
{
  int i, threadIndex;

  for (threadIndex = 0; threadIndex < NUMBER_OF_THREADS; threadIndex++) {
    if (tlsThreadHandles[threadIndex] == task) {
      break;
    }
  }
  if (threadIndex >= NUMBER_OF_THREADS) {
    return;
  }

  // Update all the globals to what they were set to by this thread
  for (i = 0; i < THREAD_LOCAL_STORAGE_COUNT; i++) {
    // Exit when we find the first 0 address
    if (tlsAddress[i] == 0) {
      break;
    }
    // Only use the values that have actually been defined
    *tlsAddress[i] = tlsValues[threadIndex][i];
  }
}

/**
 *  This function is called after a task is switched out. Use this to update
 *  the global variables used by all the tasks.
 */
void taskSwitchIn(void)
{
  taskReallySwitchIn(rtosGetCurrentTask());
}

/**
 *  This function is called before a task is switched out. Use this to store
 *  that current value of all the globals that we're backing up before a task
 *  is switched out.
 */
void taskSwitchOut(void)
{
  RtosTask_t currentThread;
  int i, threadIndex;

  // Get the handle of the task about to be switched out
  currentThread = rtosGetCurrentTask();
  for (threadIndex = 0; threadIndex < NUMBER_OF_THREADS; threadIndex++) {
    if (tlsThreadHandles[threadIndex] == currentThread) {
      break;
    }
  }
  if (threadIndex >= NUMBER_OF_THREADS) {
    return;
  }

  // Update all the globals to what they were set to by this thread
  for (i = 0; i < THREAD_LOCAL_STORAGE_COUNT; i++) {
    // Exit when we find the first 0 address
    if (tlsAddress[i] == 0) {
      break;
    }
    // Only use the values that have actually been defined
    tlsValues[threadIndex][i] = *tlsAddress[i];
  }
}

/** Micrium provides only one task swith hook, called before the current task
 * is switched out. This function performs both the switching out of the current
 * taks and the switching in for the upcoming task, which is passed in the
 * argument.
 */
void taskSwitchOutAndIn(RtosTask_t inTask)
{
  taskSwitchOut();
  taskReallySwitchIn(inTask);
}
