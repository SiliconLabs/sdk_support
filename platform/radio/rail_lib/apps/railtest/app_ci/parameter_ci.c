/***************************************************************************//**
 * @file
 * @brief This file implements the parameter commands for RAIL test applications.
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

#include <string.h>
#include <stdio.h>

#include "command_interpreter.h"
#include "response_print.h"

#include "rail.h"
#include "rail_types.h"
#include "app_common.h"
#include "em_core.h"

static const char *powerModes[] = RAIL_TX_POWER_MODE_NAMES;

void getChannel(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (RAIL_GetDebugMode(railHandle) & RAIL_DEBUG_MODE_FREQ_OVERRIDE) {
    responsePrintError(argv[0], 0x12, "Channels are not valid in Debug Mode");
  } else {
    responsePrint(argv[0], "channel:%d", channel);
  }
}

void setChannel(int argc, char **argv)
{
  uint16_t proposedChannel = ciGetUnsigned(argv[1]);
  bool success = false;

  // Make sure this is a valid channel
  if (RAIL_IsValidChannel(railHandle, proposedChannel)
      == RAIL_STATUS_NO_ERROR) {
    changeChannel(proposedChannel);
    success = true;
  }

  if (!success) {
    responsePrintError(argv[0], 0x11, "Invalid channel '%d'", proposedChannel);
    return;
  }

  getChannel(1, argv);
}

void setFreqOffset(int argc, char **argv)
{
  static RAIL_FrequencyOffset_t currentFreqOffset = 0;
  if (argc > 1) {
    RAIL_FrequencyOffset_t freqOffset = ciGetSigned(argv[1]);

    if ((freqOffset < RAIL_FREQUENCY_OFFSET_MIN)
        || (freqOffset > RAIL_FREQUENCY_OFFSET_MAX)) {
      responsePrintError(argv[0], RAIL_STATUS_INVALID_PARAMETER,
                         "Offset %d outside range of [%d, %d]",
                         freqOffset,
                         RAIL_FREQUENCY_OFFSET_MIN,
                         RAIL_FREQUENCY_OFFSET_MAX);
      return;
    }
    RAIL_Status_t status = RAIL_SetFreqOffset(railHandle, freqOffset);
    if (status != RAIL_STATUS_NO_ERROR) {
      responsePrintError(argv[0], status, "Could not set frequency offset");
      return;
    }
    currentFreqOffset = freqOffset;
  }
  responsePrint(argv[0], "freqOffset:%d", currentFreqOffset);
}

void getPowerConfig(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  RAIL_TxPowerConfig_t config;
  RAIL_Status_t status = RAIL_GetTxPowerConfig(railHandle, &config);

  responsePrint(argv[0], "success:%s,mode:%s,voltage:%d,rampTime:%d",
                status == RAIL_STATUS_NO_ERROR ? "true" : "false",
                powerModes[config.mode], config.voltage, config.rampTime);
}

void setPowerConfig(int argc, char **argv)
{
  RAIL_TxPowerMode_t mode = ciGetUnsigned(argv[1]);
  if (mode >= RAIL_TX_POWER_MODE_NONE) {
    responsePrintError(argv[0], 0x13, "Invalid PA enum value selected: %d", mode);
    return;
  }

  uint16_t voltage = ciGetUnsigned(argv[2]);
  uint16_t rampTime = ciGetUnsigned(argv[3]);

  txPowerConfig.mode = mode;
  txPowerConfig.voltage = voltage;
  txPowerConfig.rampTime = rampTime;

  CHECK_RAIL_HANDLE(argv[0]);
  RAIL_Status_t status = RAIL_ConfigTxPower(railHandle, &txPowerConfig);

  if ((status == RAIL_STATUS_NO_ERROR)
#ifdef _SILICON_LABS_32B_SERIES_1
      && mode != RAIL_TX_POWER_MODE_SUBGIG
#endif
      ) {
    default2p4Pa = mode;
  }

  if (status == RAIL_STATUS_NO_ERROR) {
    getPowerConfig(1, argv);
  } else {
    responsePrintError(argv[0], 0x26, "Could not set power config");
  }
}

void getPower(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  responsePrint(argv[0],
                "powerLevel:%d,power:%d",
                RAIL_GetTxPower(railHandle),
                RAIL_GetTxPowerDbm(railHandle));
}

void setPower(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  RAIL_TxPowerLevel_t powerLevel;
  RAIL_TxPower_t power;
  bool setPowerError = false;

  if (argc >= 3 && strcmp(argv[2], "raw") == 0) {
    RAIL_TxPowerLevel_t rawLevel = ciGetUnsigned(argv[1]);

    // Set the power and update the RAW level global
    if (RAIL_SetTxPower(railHandle, rawLevel) == RAIL_STATUS_NO_ERROR) {
      lastSetTxPowerLevel = rawLevel;
    } else {
      setPowerError = true;
    }
  } else {
    RAIL_TxPowerConfig_t tempCfg;
    RAIL_TxPower_t powerDbm = ciGetSigned(argv[1]);

    // Set the power in dBm and figure out what RAW level to store based on what
    // was requested NOT what is actually applied to the hardware after limits.
    if ((RAIL_SetTxPowerDbm(railHandle, powerDbm)
         == RAIL_STATUS_NO_ERROR)
        && (RAIL_GetTxPowerConfig(railHandle, &tempCfg)
            == RAIL_STATUS_NO_ERROR)) {
      lastSetTxPowerLevel = RAIL_ConvertDbmToRaw(railHandle,
                                                 tempCfg.mode,
                                                 powerDbm);
    } else {
      setPowerError = true;
    }
  }

  if (setPowerError) {
    responsePrintError(argv[0], 0x23, "Could not set power.");
  } else {
    // Get and print out the actual applied power and power level
    powerLevel = RAIL_GetTxPower(railHandle);
    power = RAIL_GetTxPowerDbm(railHandle);
    responsePrint(argv[0], "powerLevel:%d,power:%d", powerLevel, power);
  }
}

void sweepTxPower(int argc, char **argv)
{
  responsePrint(argv[0], "Sweeping:Started,Instructions:'q' to quit or 'enter' to continue.");
  RAIL_TxPowerConfig_t txPowerConfig;

  RAIL_GetTxPowerConfig(railHandle, &txPowerConfig);

  RAIL_TxPowerLevel_t start = 1;
  RAIL_TxPowerLevel_t end = 255;

  switch (txPowerConfig.mode) {
    case RAIL_TX_POWER_MODE_2P4_HP:
      end = RAIL_TX_POWER_LEVEL_HP_MAX;
      break;
    #if _SILICON_LABS_32B_SERIES_2_CONFIG == 1
    case RAIL_TX_POWER_MODE_2P4_MP:
      end = RAIL_TX_POWER_LEVEL_MP_MAX;
      break;
    #endif
    case RAIL_TX_POWER_MODE_2P4_LP:
      end = RAIL_TX_POWER_LEVEL_LP_MAX;
      break;
    #ifdef RAIL_TX_POWER_MODE_SUBGIG
    case RAIL_TX_POWER_MODE_SUBGIG:
      end = RAIL_TX_POWER_LEVEL_SUBGIG_MAX;
      break;
    #endif
    default:
      responsePrintError(argv[0], 0x21, "PA not configured.");
      return;
  }

  char input;
  RAIL_TxPowerLevel_t i;

  for (i = start; i <= end; i++) {
    responsePrint(argv[0], "PowerLevel:%u", i);
    RAIL_Idle(railHandle, RAIL_IDLE_FORCE_SHUTDOWN_CLEAR_FLAGS, true);
    RAIL_SetTxPower(railHandle, i);
    RAIL_StartTxStream(railHandle, channel, RAIL_STREAM_CARRIER_WAVE);

    input = getchar();

    while (1) {
      if (input == '\n' || input == '\r') {
        break;
      }
      if (input == 'q') {
        responsePrintError(argv[0], 0x20, "Sweep Aborted.");
        return;
      }
      input = getchar();
    }

    RAIL_Idle(railHandle, RAIL_IDLE_FORCE_SHUTDOWN_CLEAR_FLAGS, true);
  }

  responsePrint(argv[0], "Sweeping:Complete");
}

void getCtune(int argc, char **argv)
{
  uint32_t ctune = RAIL_GetTune(railHandle);

  responsePrint(argv[0], "CTUNE:0x%.3x", ctune);
}

void setCtune(int argc, char **argv)
{
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }

  RAIL_SetTune(railHandle, ciGetUnsigned(argv[1]));

  // Read out and print the current CTUNE value
  getCtune(1, argv);
}

void setPaCtune(int argc, char **argv)
{
  RAIL_Status_t status;
  uint8_t txVal = ciGetUnsigned(argv[1]);
  uint8_t rxVal = ciGetUnsigned(argv[2]);

  status = RAIL_SetPaCTune(railHandle, txVal, rxVal);

  if (status == RAIL_STATUS_NO_ERROR) {
    responsePrint(argv[0], "PACTUNETX:%d,PACTUNERX:%d", txVal, rxVal);
  } else {
    responsePrintError(argv[0], status, "Error");
  }
}

void enablePaCal(int argc, char **argv)
{
  uint8_t enable = ciGetUnsigned(argv[1]);
  RAIL_EnablePaCal(enable);
  responsePrint(argv[0], "paCal:%s", (enable ? "Enabled" : "Disabled"));
}

// Helper to convert two strings to two RAIL RadioStates
static int8_t stringsToStates(char **strings, RAIL_RadioState_t *states)
{
  for (int i = 0; i < 2; i++) {
    switch (strings[i][0]) {
      case 'i': case 'I':
        states[i] =  RAIL_RF_STATE_IDLE;
        break;

      case 'r': case 'R':
        states[i] =  RAIL_RF_STATE_RX;
        break;

      case 't': case 'T':
        states[i] =  RAIL_RF_STATE_TX;
        break;

      default:
        return 1;
    }
  }
  return 0;
}

void setTxTransitions(int argc, char **argv)
{
  RAIL_RadioState_t states[2];
  if (stringsToStates(&argv[1], &states[0])) {
    responsePrintError(argv[0], 0x16, "Invalid states");
    return;
  }

  RAIL_StateTransitions_t transitions = {
    .success = states[0],
    .error = states[1]
  };

  RAIL_Status_t ret = RAIL_SetTxTransitions(railHandle, &transitions);
  responsePrint(argv[0], "TxTransitions:%s", (ret ? "Error" : "Set"));
}

void setRxTransitions(int argc, char **argv)
{
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  RAIL_RadioState_t states[2];
  if (stringsToStates(&argv[1], &states[0])) {
    responsePrintError(argv[0], 0x16, "Invalid states");
    return;
  }
  RAIL_StateTransitions_t transitions = {
    .success = states[0],
    .error = states[1]
  };
  RAIL_Status_t ret = RAIL_SetRxTransitions(railHandle, &transitions);
  if (ret == RAIL_STATUS_NO_ERROR) {
    rxSuccessTransition = states[0];
  }
  responsePrint(argv[0], "RxTransitions:%s", (ret ? "Error" : "Set"));
}

void getRxTransitions(int argc, char **argv)
{
  RAIL_StateTransitions_t transitions;
  RAIL_Status_t ret = RAIL_GetRxTransitions(railHandle, &transitions);

  if (ret == RAIL_STATUS_NO_ERROR) {
    const char *success = getRfStateName(transitions.success);
    const char *error = getRfStateName(transitions.error);
    responsePrint(argv[0], "Success:%s,Error:%s", success, error);
  } else {
    responsePrintError(argv[0], 0x28, "Get rx transitions failed");
  }
}

void getTxTransitions(int argc, char **argv)
{
  RAIL_StateTransitions_t transitions;
  RAIL_Status_t ret = RAIL_GetTxTransitions(railHandle, &transitions);

  if (ret == RAIL_STATUS_NO_ERROR) {
    const char *success = getRfStateName(transitions.success);
    const char *error = getRfStateName(transitions.error);
    responsePrint(argv[0], "Success:%s,Error:%s", success, error);
  } else {
    responsePrintError(argv[0], 0x27, "Get tx transitions failed");
  }
}

void setTimings(int argc, char **argv)
{
  uint16_t timing[6] = { 0 };
  for (int i = 1; i < argc; i++) {
    timing[i - 1] = ciGetUnsigned(argv[i]);
  }
  CHECK_RAIL_HANDLE(argv[0]);
  RAIL_StateTiming_t timings =
  { timing[0], timing[1], timing[2], timing[3], timing[4], timing[5] };
  if (!RAIL_SetStateTiming(railHandle, &timings)) {
    responsePrint(argv[0], "IdleToRx:%u,RxToTx:%u,IdleToTx:%u,TxToRx:%u,"
                           "RxSearch:%u,Tx2RxSearch:%u",
                  timings.idleToRx, timings.rxToTx, timings.idleToTx,
                  timings.txToRx, timings.rxSearchTimeout, timings.txToRxSearchTimeout);
  } else {
    responsePrintError(argv[0], 0x18, "Setting timings failed");
  }
}

void setTxFifoThreshold(int argc, char **argv)
{
  if (railDataConfig.txMethod != FIFO_MODE) {
    responsePrintError(argv[0], 0x19, "Tx is not in FIFO mode");
    return;
  }

  uint16_t txFifoThreshold = ciGetUnsigned(argv[1]);
  txFifoThreshold = RAIL_SetTxFifoThreshold(railHandle, txFifoThreshold);
  responsePrint(argv[0], "TxFifoThreshold:%d", txFifoThreshold);
}

void setRxFifoThreshold(int argc, char **argv)
{
  uint16_t rxFifoThreshold = ciGetUnsigned(argv[1]);
  rxFifoThreshold = RAIL_SetRxFifoThreshold(railHandle, rxFifoThreshold);
  responsePrint(argv[0], "RxFifoThreshold:%d", rxFifoThreshold);
}

void setEventConfig(int argc, char **argv)
{
  RAIL_Events_t eventMask = ciGetUnsigned(argv[1]);
  RAIL_Events_t eventConfig = ciGetUnsigned(argv[2]);

  if (argc >= 5) {
    eventMask |= (((RAIL_Events_t)ciGetUnsigned(argv[3])) << 32U);
    eventConfig |= (((RAIL_Events_t)ciGetUnsigned(argv[4])) << 32U);
  }

  CHECK_RAIL_HANDLE(argv[0]);
  RAIL_ConfigEvents(railHandle, eventMask, eventConfig);
  // Avoid use of %ll long-long formats due to iffy printf library support
  if (argc >= 5) {
    responsePrint(argv[0], "Mask:0x%x%08x,Values:0x%x%08x",
                  (uint32_t)(eventMask >> 32),
                  (uint32_t)eventMask,
                  (uint32_t)(eventConfig >> 32),
                  (uint32_t)eventConfig);
  } else {
    responsePrint(argv[0], "Mask:0x%x,Values:0x%x",
                  (uint32_t)eventMask,
                  (uint32_t)eventConfig);
  }
}

void delayUs(int argc, char **argv)
{
  uint32_t delayUs = ciGetUnsigned(argv[1]);

  // Do not measure any interrupt processing overhead during the delay.
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();

  // Measure the actual delay vs expected.
  uint32_t startTime = RAIL_GetTime();
  RAIL_Status_t status = RAIL_DelayUs(delayUs);
  uint32_t actualDelay = RAIL_GetTime() - startTime;

  CORE_EXIT_CRITICAL();
  responsePrint(argv[0], "Success:%s,ActualDelay:%d",
                status == RAIL_STATUS_NO_ERROR ? "True" : "False",
                actualDelay);
}

#ifdef RAIL_PA_AUTO_MODE
#include "pa_auto_mode.h"
void configPaAutoMode(int argc, char **argv)
{
  uint8_t index = ciGetUnsigned(argv[1]);

  int16_t min = ciGetSigned(argv[2]);
  int16_t max = ciGetSigned(argv[3]);
  uint8_t mode = ciGetUnsigned(argv[4]);

  // Make sure the mode is valid
  if (mode > RAIL_TX_POWER_MODE_NONE) {
    responsePrintError(argv[0], 0x01, "Invalid mode (%d) specified", mode);
    return;
  }

  RAIL_PaAutoModeConfig[index].min = min;
  RAIL_PaAutoModeConfig[index].max = max;
  RAIL_PaAutoModeConfig[index].mode = mode;

  responsePrint(argv[0], "Min:%d,Max:%d,Mode:%s", min, max, powerModes[mode]);
}

void enablePaAutoMode(int argc, char **argv)
{
  bool enable = !!ciGetUnsigned(argv[1]);
  RAIL_EnablePaAutoMode(railHandle, enable);

  responsePrint(argv[0], "enable:%s", enable ? "True" : "False");
}
#else
void configPaAutoMode(int argc, char **argv)
{
  responsePrintError(argv[0], 0x01, "PA Auto Mode plugin must be enabled to use this feature!");
}

void enablePaAutoMode(int argc, char **argv)
{
  responsePrintError(argv[0], 0x01, "PA Auto Mode plugin must be enabled to use this feature!");
}
#endif
