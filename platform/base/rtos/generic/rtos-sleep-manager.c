/***************************************************************************//**
 * @file
 * @brief This module manages what level of sleep (idle or deep) that the chip
 * can enter at any given time and makes sure that the correct type of sleep
 * is chosen.
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
#include "../rtos.h"

#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "hal/hal.h"
#include "hal/micro/cortexm3/wake-gpio.h"

// ---- Configuration options for this module ----
// Defines that can be set globally to control sleep
#ifndef MIN_DEEP_SLEEP_DURATION_MS
  #define MIN_DEEP_SLEEP_DURATION_MS (50)
#endif
// Configure the number of wakeup callbacks we can handle
#ifndef NUM_SLEEP_WAKE_CALLBACKS
   #define NUM_SLEEP_WAKE_CALLBACKS 2
#endif
// Configure whether the RTOS manages GPIO wake sources
#ifndef RTOS_CONTROL_GPIO_WAKE
   #define RTOS_CONTROL_GPIO_WAKE 1
#endif

// Globals used by the sleep manager
static uint32_t dsBlockCount = 0;   // Counter for whether it's ok to deepsleep
static RtosMutex_t sleepManagerMutex = NULL;
static void(*sleepWakeCallbacks[NUM_SLEEP_WAKE_CALLBACKS])(WakeEvents);

#if RTOS_CONTROL_GPIO_WAKE
static WakeMask sleepGpioWakeBitMask = 0;
#endif

// Initialize any globals used in the sleep manager
void sleepManagerInit(void)
{
  #if RTOS_CONTROL_GPIO_WAKE
  // Configure the sleep GPIO wakeup bit mask from the board header
  sleepGpioWakeBitMask = (EMBER_WAKE_PORT_A << 0)
                         | (EMBER_WAKE_PORT_B << 8)
                         | (EMBER_WAKE_PORT_C << 16)
                           #ifdef EMBER_WAKE_PORT_D
                         | (EMBER_WAKE_PORT_D << 24)
                           #endif
                           #ifdef EMBER_WAKE_PORT_E
                         | ((uint64_t) EMBER_WAKE_PORT_E << 32)
                           #endif
                           #ifdef EMBER_WAKE_PORT_F
                         | ((uint64_t) EMBER_WAKE_PORT_F << 40)
                           #endif
  ;
  #endif // RTOS_CONTROL_GPIO_WAKE

  // Initialize the mutex used by the sleep manager
  if (sleepManagerMutex == NULL) {
    sleepManagerMutex = rtosMutexCreate();
  }
  assert(sleepManagerMutex != NULL);
}

// This API allows the user to register functions to be called when waking from
// deep sleep. These are called from within the scheduler, so they must not
// block.
bool rtosAddDeepSleepWakeCallback(void (*callback)(WakeEvents))
{
  int i;

  // Lock the sleep manager mutex
  if (!rtosMutexTake(sleepManagerMutex, RTOS_MAX_DELAY)) {
    assert(0);
  }

  // Walk the callback list and add this to the first empty slot
  for (i = 0; i < NUM_SLEEP_WAKE_CALLBACKS; i++) {
    if (sleepWakeCallbacks[i] == NULL) {
      sleepWakeCallbacks[i] = callback;
      break;
    }
  }

  // Return the mutex
  rtosMutexGive(sleepManagerMutex);

  // Return whether we were able to actually set this callback
  return (i < NUM_SLEEP_WAKE_CALLBACKS);
}

// Increment the deep sleep block count. This will prevent us from
// entering deep sleep until every thread that has blocked it calls
// the unblock function.
void rtosBlockDeepSleep(void)
{
  // This function is sometimes called from within ATOMIC so do not use
  // the mutex here or you can deadlock
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();
  // Increment the deep sleep block counter
  dsBlockCount++;
  RESTORE_INTERRUPTS();
}

// Decrement the deep sleep block count. This will allow us to go into
// deep sleep if the count goes down to zero.
void rtosUnblockDeepSleep(void)
{
  // This function is sometimes called from within ATOMIC so do not use
  // the mutex here or you can deadlock
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();
  // If this is already 0 then something is wrong here
  assert(dsBlockCount != 0);

  // Decrement the deep sleep block counter
  dsBlockCount--;
  RESTORE_INTERRUPTS();
}

// This function gets the state of the RTOS deep sleep count.
uint32_t rtosGetDeepSleepBlockCount(void)
{
  return dsBlockCount;
}

void rtosSetSleepWakeSource(WakeMask gpioWakeBitMask)
{
  // Lock the sleep manager mutex
  if (!rtosMutexTake(sleepManagerMutex, RTOS_MAX_DELAY)) {
    assert(0);
  }

  #if RTOS_CONTROL_GPIO_WAKE
  // Set the sleep wake bit mask
  sleepGpioWakeBitMask = gpioWakeBitMask;
  #endif

  // Return the mutex
  rtosMutexGive(sleepManagerMutex);
}

/* Check the wakeup info is valid and we were awoken by something
 * other than the sleep timer. The sleep timer is under OS control
 * and should not be managed by other threads.
 */
#ifdef CORTEXM3_EMBER_MICRO
int notSleepTimerWake(WakeEvents wakeInfo)
{
  return (wakeInfo.events.internal.bits.WakeInfoValid == true)
         && (!wakeInfo.events.internal.bits.TIMER_WAKE_COMPA
             && !wakeInfo.events.internal.bits.TIMER_WAKE_COMPB
             && !wakeInfo.events.internal.bits.TIMER_WAKE_WRAP);
}

#else
int notSleepTimerWake(WakeEvents wakeInfo)
{
  /*
   * When halGetWakeInfo() returns more then just "GPIO->IF" this
   * should also be fixed.  I.E. when WakeEvents is more then just a
   * uint32_t.  See hal/micro/cortexm3/efm32/sleep-efm32.c for more
   * info.
   */
  return 1;
}

#endif

/*
 * This function assumes that any tick interrupts are already configured
 * as needed for wakeup. It will set any additional wake sources and make the
 * final determination as to whether the chip goes into deep sleep or idle
 * sleep.
 */
void sleepManagerSleep(uint32_t durationMs)
{
  // NOTE: We do not protect our access to the dsBlockCount here because
  // we're just reading it and this routine is called from within the
  // scheduler so we can't block.

  // If we're over the minimum duration for deep sleep and no one is
  // blocking us from entering deep sleep then go to deep sleep.
  if ((durationMs > MIN_DEEP_SLEEP_DURATION_MS)
      && (dsBlockCount == 0)) {
    {
      DECLARE_INTERRUPT_STATE;
      DISABLE_INTERRUPTS();
      halPowerDown();
#if RTOS_CONTROL_GPIO_WAKE
      halSleepWithOptionsPreserveInts(SLEEPMODE_WAKETIMER, sleepGpioWakeBitMask);
#else
      halSleepPreserveInts(SLEEPMODE_WAKETIMER);
#endif
      RESTORE_INTERRUPTS();
    }
    halPowerUp();

    // Grab the wakeup info to pass to any registered callbacks
    WakeEvents wakeInfo = halGetWakeInfo();

    // Do not alert callback functions unless the wakeup info is valid and
    // we were awoken by something other than the sleep timer. The sleep timer
    // is under OS control and should not be managed by other threads.
    if ( notSleepTimerWake(wakeInfo)) {
      for (int i = 0; i < NUM_SLEEP_WAKE_CALLBACKS; i++) {
        if (sleepWakeCallbacks[i] != NULL) {
          sleepWakeCallbacks[i](wakeInfo);
        }
      }
    }
  } else {
    // Put the chip into idle sleep without modifying the wake sources
#if RTOS_CONTROL_GPIO_WAKE
    halSleepWithOptionsPreserveInts(SLEEPMODE_IDLE, WAKE_MASK_INVALID);
#else
    halSleepPreserveInts(SLEEPMODE_IDLE);
#endif
  }
}
