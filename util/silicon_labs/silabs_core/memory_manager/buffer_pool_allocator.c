/***************************************************************************//**
 * @file
 * @brief The source for a simple memory allocator that statically creates pools
 *        of fixed size buffers to allocate from.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdlib.h>

#include "buffer_pool_allocator.h"

#include "em_core.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif

// -----------------------------------------------------------------------------
// Configuration Macros
// -----------------------------------------------------------------------------

// Default to a buffer pool one buffer long with a size of 256 bytes per buffer
#ifndef BUFFER_POOL_SIZE
#define BUFFER_POOL_SIZE 2
#endif
#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 256
#endif

#define INVALID_BUFFER_OBJ ((void*)0xFFFFFFFF)

typedef struct {
  // Ensure the alignment is 32 bits for data. This will prevent issues with the
  // load and store multiple instructions if we overlay a structure on the
  // memory returned by the allocator.
  uint32_t refCount;
  uint8_t data[MAX_BUFFER_SIZE];
} BufferPoolObj_t;

static BufferPoolObj_t memoryObjs[BUFFER_POOL_SIZE];

void* memoryAllocate(uint32_t size)
{
  uint32_t i = 0;
  void *handle = INVALID_BUFFER_OBJ;

  // We can't support sizes greater than the maximum heap buffer size
  if (size > MAX_BUFFER_SIZE) {
    return INVALID_BUFFER_OBJ;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  for (i = 0; i < BUFFER_POOL_SIZE; i++) {
    if (memoryObjs[i].refCount == 0) {
      memoryObjs[i].refCount = 1;
      handle = (void*)i;
      break;
    }
  }
  CORE_EXIT_CRITICAL();

  return handle;
}

void *memoryPtrFromHandle(void *handle)
{
  void *ptr = NULL;

  // Make sure we were given a valid handle
  if ((handle == INVALID_BUFFER_OBJ) || ((uint32_t)handle >= BUFFER_POOL_SIZE)) {
    return NULL;
  }

  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  if (memoryObjs[(uint32_t)handle].refCount > 0) {
    ptr = memoryObjs[(uint32_t)handle].data;
  }
  CORE_EXIT_CRITICAL();

  return ptr;
}

void memoryFree(void *handle)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  if (memoryPtrFromHandle(handle) != NULL) {
    memoryObjs[(uint32_t)handle].refCount--;
  }
  CORE_EXIT_CRITICAL();
}

void memoryTakeReference(void *handle)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  if (memoryPtrFromHandle(handle) != NULL) {
    memoryObjs[(uint32_t)handle].refCount++;
  }
  CORE_EXIT_CRITICAL();
}
