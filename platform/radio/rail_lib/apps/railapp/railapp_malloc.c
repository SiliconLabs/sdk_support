/***************************************************************************//**
 * @file
 * @brief Header file for RAIL error rate functionality
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

#include "rail.h"
#include "em_core.h"

static volatile bool mallocLock = false;
#define RAIL_HEAP_SIZE 0x1400
__ALIGNED(4) uint8_t railMallocBuffer[RAIL_HEAP_SIZE];

void *RAILAPP_Malloc(uint32_t size)
{
  CORE_DECLARE_IRQ_STATE;
  void *buffer;
  CORE_ENTER_CRITICAL();
  if (mallocLock || size > sizeof(railMallocBuffer)) {
    buffer = NULL;
  } else {
    mallocLock = true;
    buffer = railMallocBuffer;
  }
  CORE_EXIT_CRITICAL();
  return buffer;
}

void RAILAPP_Free(void * buffer)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_CRITICAL();
  if (buffer == railMallocBuffer) {
    mallocLock = false;
  }
  CORE_EXIT_CRITICAL();
}
