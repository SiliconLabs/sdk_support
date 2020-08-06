/***************************************************************************//**
 * @file
 * @brief Hardware driver layer for simple delay on EXX32.
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

#include "btl_driver_delay.h"
#include "btl_driver_util.h"
#include "em_timer.h"

// The processors that have been tested "so far" use 7 ticks per iteration.
// This assumption might not be correct for all the existing processors,
// however since we cannot use any peripheral to count the actual time passed,
// this is, for now, the best solution to assume 7 ticks per iteration.
#define TICKS_PER_ITERATION 7

static uint16_t delayTarget = 0;
static bool expectOverflow;
static uint32_t ticksPerMillisecond = 0;

void delay_microseconds(uint32_t usecs)
{
  uint32_t ticksPerMicrosecond = util_getClockFreq() / 1000000UL;
  volatile uint32_t iterations = ((ticksPerMicrosecond * usecs) / TICKS_PER_ITERATION) + 1U;
  while (iterations--) {
    // Do nothing
  }
}

void delay_init(void)
{
  // Enable clocks to TIMER0
#if defined(CMU_CTRL_HFPERCLKEN)
  CMU->CTRL |= CMU_CTRL_HFPERCLKEN;
  CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER0;
#endif
#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_SET = CMU_CLKEN0_TIMER0;
#endif

  // Calculate the length of a tick
  ticksPerMillisecond = (util_getClockFreq() / 1000UL) / 1024UL;

  // Initialize timer
  TIMER_Init_TypeDef init = TIMER_INIT_DEFAULT;
  init.prescale = timerPrescale1024;
  TIMER_Init(TIMER0, &init);
}

void delay_milliseconds(uint32_t msecs, bool blocking)
{
  // TODO: Assert msecs within a single TIMER0 overflow (approx. 3300 ms)

  uint16_t count = TIMER0->CNT;
  delayTarget = count + (msecs * ticksPerMillisecond);
  expectOverflow = (delayTarget < count);

  if (blocking) {
    while (TIMER0->CNT != delayTarget) {
      // Do nothing
    }
  }
#if defined(TIMER_IFC_OF)
  TIMER0->IFC = TIMER_IFC_OF;
#else
  TIMER0->IF_CLR = TIMER_IF_OF;
#endif
  TIMER0->IEN = TIMER_IEN_OF;
}

bool delay_expired(void)
{
  // Expecting overflow, but it hasn't happened yet
  if (expectOverflow && !(TIMER0->IF & TIMER_IF_OF)) {
    return false;
  }
  // Not expecting overflow, but it still happened
  if (!expectOverflow && (TIMER0->IF & TIMER_IF_OF)) {
    return true;
  }

  // Return true if CNT has passed the target
  return TIMER0->CNT >= delayTarget;
}
