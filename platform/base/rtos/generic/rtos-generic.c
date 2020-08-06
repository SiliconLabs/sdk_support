/***************************************************************************//**
 * @file
 * @brief Basic RTOS API wrapper that includes pieces which don't
 * really fit cleanly anywhere else.
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

// These initialization functions are defined in other rtos api files
// but we call them here so extern them.
extern void sleepManagerInit(void);
extern void threadLocalStorageInit(void);

// Call the various API initialization functions that we know about
void rtosApiInit(void)
{
  // Initialize the RTOS thread local storage
  threadLocalStorageInit();

  // Initialize the RTOS sleep manager
  sleepManagerInit();
}
