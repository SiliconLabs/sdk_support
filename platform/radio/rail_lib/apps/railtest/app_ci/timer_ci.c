/***************************************************************************//**
 * @file
 * @brief This file is for testing the RAIL timer interface.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#include <stdio.h>
#include <string.h>

#include "bsp.h"
#include "command_interpreter.h"
#include "response_print.h"
#include "buffer_pool_allocator.h"

#include "rail_types.h"
#include "rail.h"
#include "app_common.h"

// Hardware-based, single timer functionality
// When the multiTimer is enabled, this API uses one instance of the
// software-based, multiTimer.
void printTimerStats(int argc, char **argv)
{
  bool enabled = RAIL_IsTimerRunning(railHandle);
  bool expired = RAIL_IsTimerExpired(railHandle);
  RAIL_Time_t expirationTime = RAIL_GetTimer(railHandle);
  RAIL_Time_t currentTime = RAIL_GetTime();

  responsePrint(argv[0],
                "timeUs:%u,ExpirationTime:%u,"
                "IsRunning:%s,IsExpired:%s",
                currentTime,
                expirationTime,
                (enabled ? "True" : "False"),
                (expired ? "True" : "False"));
}

void setTimer(int argc, char **argv)
{
  if (!inAppMode(NONE, argv[0])) {
    return;
  }

  uint32_t timeOut = ciGetUnsigned(argv[1]);
  RAIL_TimeMode_t mode = RAIL_TIME_DELAY;

  // If this is absolute mode then switch the delay mode
  if (strcmp(argv[2], "abs") == 0) {
    mode = RAIL_TIME_ABSOLUTE;
  }

  RAIL_CancelTimer(railHandle);
  if (RAIL_SetTimer(railHandle, timeOut, mode, &RAILCb_TimerExpired)
      != RAIL_STATUS_NO_ERROR) {
    responsePrintError(argv[0], 0x40, "SetTimer failed");
    return;
  }

  printTimerStats(1, argv);
}

void timerCancel(int argc, char** argv)
{
  if (inAppMode(NONE, argv[0])) {
    RAIL_CancelTimer(railHandle);
    printTimerStats(1, argv);
  }
}

// Software-based, multi-timer functionality
#define NUM_MULTI_TIMERS      3
static RAIL_MultiTimer_t multiTimer[NUM_MULTI_TIMERS];

void printMultiTimerStats(int argc, char **argv)
{
  uint8_t index = ciGetUnsigned(argv[1]);
  if (index >= NUM_MULTI_TIMERS) {
    responsePrintError(argv[0], 0x10,
                       "Invalid multiTimer index - start with 0. Number of multiTimers is %d",
                       NUM_MULTI_TIMERS);
    return;
  }

  bool enabled = RAIL_IsMultiTimerRunning(&multiTimer[index]);
  bool expired = RAIL_IsMultiTimerExpired(&multiTimer[index]);
  RAIL_Time_t expirationTime = RAIL_GetMultiTimer(&multiTimer[index],
                                                  RAIL_TIME_ABSOLUTE);
  RAIL_Time_t currentTime = RAIL_GetTime();

  responsePrint(argv[0],
                "timeUs:%u,"
                "ExpirationTime:%u,"
                "IsRunning:%s,"
                "IsExpired:%s,"
                "MultiTimerIndex:%d",
                currentTime,
                expirationTime,
                (enabled ? "True" : "False"),
                (expired ? "True" : "False"),
                index);
}

void enableMultiTimer(int argc, char **argv)
{
  if (!inAppMode(NONE, argv[0])) {
    return;
  }

  bool enable = !!ciGetUnsigned(argv[1]);
  bool multiTimerSuccess = RAIL_ConfigMultiTimer(enable);
  if (multiTimerSuccess) {
    responsePrint(argv[0],
                  "status:%s,numMultiTimers:%d",
                  (enable ? "enabled" : "disabled"),
                  NUM_MULTI_TIMERS);
  } else {
    responsePrintError(argv[0], 0x10, "Unable to configure the multiTimer.");
  }
}

static void RAILCb_MultiTimerExpired(RAIL_MultiTimer_t *tmr,
                                     RAIL_Time_t expectedTimeOfEvent,
                                     void *cbArg)
{
  void *multitimerHandle = memoryAllocate(sizeof(RailAppEvent_t));
  RailAppEvent_t *multitimer = (RailAppEvent_t *)memoryPtrFromHandle(multitimerHandle);
  if (multitimer == NULL) {
    eventsMissed++;
    return;
  }

  multitimer->type = MULTITIMER;
  multitimer->multitimer.index = (uint32_t)cbArg;
  multitimer->multitimer.currentTime = RAIL_GetTime();
  multitimer->multitimer.expirationTime = RAIL_GetMultiTimer(tmr, RAIL_TIME_ABSOLUTE);

  queueAdd(&railAppEventQueue, multitimerHandle);
}

void setMultiTimer(int argc, char **argv)
{
  if (!inAppMode(NONE, argv[0])) {
    return;
  }

  uint8_t index = ciGetUnsigned(argv[1]);
  if (index >= NUM_MULTI_TIMERS) {
    responsePrintError(argv[0], 0x10,
                       "Invalid multiTimer index - start with 0. Number of multiTimers is %d",
                       NUM_MULTI_TIMERS);
    return;
  }

  uint32_t timeOut = ciGetUnsigned(argv[2]);
  RAIL_TimeMode_t mode = RAIL_TIME_DELAY;

  // If this is absolute mode then switch the delay mode
  if (strcmp(argv[3], "abs") == 0) {
    mode = RAIL_TIME_ABSOLUTE;
  }

  RAIL_CancelTimer(railHandle);
  if (RAIL_SetMultiTimer(&multiTimer[index],
                         timeOut,
                         mode,
                         &RAILCb_MultiTimerExpired,
                         (void *)(uint32_t)index)
      != RAIL_STATUS_NO_ERROR) {
    responsePrintError(argv[0], 0x40, "SetMultiTimer failed");
    return;
  }

  printMultiTimerStats(1, argv);
}

void multiTimerCancel(int argc, char** argv)
{
  if (!inAppMode(NONE, argv[0])) {
    return;
  }

  uint8_t index = ciGetUnsigned(argv[1]);
  if (index >= NUM_MULTI_TIMERS) {
    responsePrintError(argv[0], 0x10,
                       "Invalid multiTimer index - start with 0. Number of multiTimers is %d",
                       NUM_MULTI_TIMERS);
    return;
  }

  if (RAIL_CancelMultiTimer((&multiTimer[index]))) {
    printMultiTimerStats(1, argv);
  } else {
    responsePrintError(argv[0], 0x10, "MultiTimer unable to cancel.");
  }
}
