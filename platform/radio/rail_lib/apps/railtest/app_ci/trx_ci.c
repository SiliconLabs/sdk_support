/***************************************************************************//**
 * @file
 * @brief This file implements the tx/rx commands for RAIL test applications.
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

#if !defined(__ICCARM__)
// IAR doesn't have strings.h and puts those declarations in string.h
#include <strings.h>
#endif

#include "command_interpreter.h"
#include "response_print.h"

#include "rail.h"
#include "app_common.h"
#include "app_trx.h"

RAIL_PacketTimePosition_t txTimePosition = RAIL_PACKET_TIME_DEFAULT;
RAIL_PacketTimePosition_t rxTimePosition = RAIL_PACKET_TIME_DEFAULT;

void tx(int argc, char **argv)
{
  uint32_t newTxCount = ciGetUnsigned(argv[1]);
  radioTransmit(newTxCount, argv[0]);
}

//deprecated
void txWithOptions(int argc, char **argv)
{
  tx(argc, argv);
}

static const char *configuredTxAntenna(RAIL_TxOptions_t txOptions)
{
  switch (txOptions & (RAIL_TX_OPTION_ANTENNA0 | RAIL_TX_OPTION_ANTENNA1)) {
    case (RAIL_TX_OPTION_ANTENNA0 | RAIL_TX_OPTION_ANTENNA1): {
      return "Any";
      break;
    }
    case (RAIL_TX_OPTION_ANTENNA0): {
      return "Antenna0";
      break;
    }
    case (RAIL_TX_OPTION_ANTENNA1): {
      return "Antenna1";
      break;
    }
    default: {
      return "Any";
      break;
    }
  }
}

void configTxOptions(int argc, char **argv)
{
  if (argc > 1) {
    txOptions = ciGetUnsigned(argv[1]);
  }

  responsePrint(argv[0], "waitForAck:%s,removeCrc:%s,syncWordId:%d,"
                         "txAntenna:%s,altPreambleLen:%s,ccaPeakRssi:%s,"
                         "ccaOnly:%s",
                ((txOptions & RAIL_TX_OPTION_WAIT_FOR_ACK) ? "True" : "False"),
                ((txOptions & RAIL_TX_OPTION_REMOVE_CRC) ? "True" : "False"),
                ((txOptions & RAIL_TX_OPTION_SYNC_WORD_ID) >> RAIL_TX_OPTION_SYNC_WORD_ID_SHIFT),
                configuredTxAntenna(txOptions),
                ((txOptions & RAIL_TX_OPTION_ALT_PREAMBLE_LEN) ? "True" : "False"),
                ((txOptions & RAIL_TX_OPTION_CCA_PEAK_RSSI) ? "True" : "False"),
                ((txOptions & RAIL_TX_OPTION_CCA_ONLY) ? "True" : "False"));
}

void txAtTime(int argc, char **argv)
{
  // DEFAULTS: 0 ms, absolute time, postponse tx during rx
  RAIL_ScheduleTxConfig_t scheduledTxOptions = { 0 };
  scheduledTxOptions.when = ciGetUnsigned(argv[1]);

  // Attempt to parse the time mode if specified
  if (argc >= 3) {
    if (!parseTimeModeFromString(argv[2], &scheduledTxOptions.mode)) {
      responsePrintError(argv[0], 28, "Invalid time mode");
      return;
    }
  }

  scheduledTxOptions.txDuringRx =
    (argc >= 4 && strcasecmp("abort", argv[3]) == 0)
    ? RAIL_SCHEDULED_TX_DURING_RX_ABORT_TX
    : RAIL_SCHEDULED_TX_DURING_RX_POSTPONE_TX;

  setNextPacketTime(&scheduledTxOptions);
  setNextAppMode(TX_SCHEDULED, argv[0]);
}

void txAfterRx(int argc, char **argv)
{
  uint32_t delay = ciGetUnsigned(argv[1]);
  txAfterRxDelay = delay;
  enableAppMode(SCHTX_AFTER_RX, (delay != 0), argv[0]);
}

void getTxDelay(int argc, char **argv)
{
  responsePrint(argv[0], "txDelay:%d", continuousTransferPeriod);
}

void setTxDelay(int argc, char **argv)
{
  uint32_t delay = ciGetUnsigned(argv[1]);

  continuousTransferPeriod = delay;
  getTxDelay(1, argv);
}

void setTxHoldOff(int argc, char **argv)
{
  uint32_t holdOff = ciGetUnsigned(argv[1]);

  RAIL_EnableTxHoldOff(railHandle, holdOff);
  responsePrint(argv[0], "TxHoldOff:%s",
                (RAIL_IsTxHoldOffEnabled(railHandle) ? "Enabled" : "Disabled"));
}

void setTxAltPreambleLen(int argc, char **argv)
{
  uint16_t length = (uint16_t)ciGetUnsigned(argv[1]);

  RAIL_Status_t status = RAIL_SetTxAltPreambleLength(railHandle, length);
  responsePrint(argv[0], "Result:%s",
                ((status == RAIL_STATUS_NO_ERROR) ? "Success" : "Failure"));
}

void stopInfinitePreambleTx(int argc, char **argv)
{
  RAIL_Status_t status = RAIL_StopInfinitePreambleTx(railHandle);
  responsePrint(argv[0], "Result:%s",
                ((status == RAIL_STATUS_NO_ERROR) ? "Success"
                 : (status == RAIL_STATUS_INVALID_CALL) ? "Invalid Call"
                 : (status == RAIL_STATUS_INVALID_STATE) ? "Invalid State"
                 : "Failure"
                ));
}

void getSyncWords(int argc, char **argv)
{
  RAIL_SyncWordConfig_t syncWordConfig = { 0, };
  RAIL_Status_t status = RAIL_GetSyncWords(railHandle, &syncWordConfig);
  responsePrint(argv[0],
                "Result:%s,bitlength:%u,syncWord1:%lu,syncWord2:%lu",
                status == RAIL_STATUS_NO_ERROR ? "Success" : "Failure",
                syncWordConfig.syncWordBits, syncWordConfig.syncWord1,
                syncWordConfig.syncWord2);
}

void configSyncWords(int argc, char **argv)
{
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  RAIL_SyncWordConfig_t syncWordConfig = { 0, };
  syncWordConfig.syncWordBits = (uint8_t)ciGetUnsigned(argv[1]);
  syncWordConfig.syncWord1 = (uint32_t)ciGetUnsigned(argv[2]);
  if (argc > 3) {
    syncWordConfig.syncWord2 = (uint32_t)ciGetUnsigned(argv[3]);
  } else {
    syncWordConfig.syncWord2 = syncWordConfig.syncWord1;
  }
  RAIL_Status_t status = RAIL_ConfigSyncWords(railHandle, &syncWordConfig);
  responsePrint(argv[0], "Result:%s",
                ((status == RAIL_STATUS_NO_ERROR) ? "Success" : "Failure"));
}

void rx(int argc, char **argv)
{
  bool enable = ciGetUnsigned(argv[1]);
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  // Don't allow Rx enable calls when scheduled Rx has been started
  if ((currentAppMode() == RX_SCHEDULED) && enable) {
    responsePrintError(argv[0], 29, "Can't turn on receive when in ScheduledRx");
    return;
  }

  // Only allow calls to Rx if we're in direct mode, no mode, or this is a
  // scheduled Rx disable call
  if ((currentAppMode() != DIRECT)
      && (currentAppMode() != RX_SCHEDULED)
      && (!inAppMode(NONE, argv[0]))) {
    return;
  }

  // Do the minimum amount of work to get into the correct state
  RAIL_RadioState_t currentState = RAIL_GetRadioState(railHandle);
  if ((enable && (currentState & RAIL_RF_STATE_RX))
      || (!enable && (currentState <= RAIL_RF_STATE_IDLE))) {
    // Do nothing since we're already in the right state
  } else if (enable) {
    status = RAIL_StartRx(railHandle, channel, NULL);
  } else {
    RAIL_Idle(railHandle, RAIL_IDLE_ABORT, false);

    // Turn off ScheduledRx if we were in it
    if (currentAppMode() == RX_SCHEDULED) {
      (void) enableAppModeSync(RX_SCHEDULED, false, NULL);
    }
  }
  if (status == RAIL_STATUS_NO_ERROR) {
    receiveModeEnabled = enable;

    // Print out the current status of receive mode
    responsePrint(argv[0],
                  "Rx:%s,Idle:%s,Time:%u",
                  (enable ? "Enabled" : "Disabled"),
                  ((!enable) ? "Enabled" : "Disabled"),
                  RAIL_GetTime());
  } else {
    responsePrintError(argv[0],
                       40,
                       "Could not change receive state '%d'",
                       status);
  }
}

void rxAt(int argc, char **argv)
{
  uint32_t startTime, endTime;
  RAIL_TimeMode_t startMode, endMode;
  bool rxTransitionEndSchedule = false, hardEnd = false;
  bool scheduledRxUpdate = false;
  RAIL_ScheduleRxConfig_t rxCfg;

  // Only allow this when app is idle or to reconfigure an active scheduled Rx
  if (!inAppMode(NONE, NULL) && !inAppMode(RX_SCHEDULED, NULL)) {
    responsePrintError(argv[0], 30, "Cannot enter ScheduledRx when not in Idle.");
    return;
  }

  // Parse out the command line parameters
  startTime = ciGetUnsigned(argv[1]);
  endTime   = ciGetUnsigned(argv[3]);

  if (!parseTimeModeFromString(argv[2], &startMode)) {
    responsePrintError(argv[0], 25, "Invalid startMode specified");
    return;
  }
  if (!parseTimeModeFromString(argv[4], &endMode)) {
    responsePrintError(argv[0], 26, "Invalid endMode specified");
    return;
  }

  // Read the rxTransitionEndSchedule option if available
  if (argc > 5) {
    rxTransitionEndSchedule = !!ciGetUnsigned(argv[5]);
  }
  // Read the hardEnd option if available
  if (argc > 6) {
    hardEnd = !!ciGetUnsigned(argv[6]);
  }

  // Configure scheduled receive as requested
  rxCfg.start = startTime;
  rxCfg.startMode = startMode;
  rxCfg.end = endTime;
  rxCfg.endMode = endMode;
  rxCfg.rxTransitionEndSchedule = rxTransitionEndSchedule;
  rxCfg.hardWindowEnd = hardEnd;

  // Tell the app what we're doing so it can correctly track the end of the
  // scheduled receive state
  schRxStopOnRxEvent = rxTransitionEndSchedule;

  // Store whether this is an update or not
  if (inAppMode(RX_SCHEDULED, NULL)) {
    scheduledRxUpdate = true;
  }

  if (!scheduledRxUpdate) {
    // Attempt to put the app into scheduled receive mode
    if (!enableAppModeSync(RX_SCHEDULED, true, argv[0])) {
      return;
    }
  }

  // Enable scheduled receive mode
  uint8_t res = RAIL_ScheduleRx(railHandle, channel, &rxCfg, NULL);
  if (res != RAIL_STATUS_NO_ERROR) {
    responsePrintError(argv[0], 27, "Could not start scheduled receive %d", res);
    if (!scheduledRxUpdate) {
      (void) enableAppModeSync(RX_SCHEDULED, false, argv[0]);
    }
    return;
  }
}

void setRxOptions(int argc, char **argv)
{
  // Only update the rxOptions if a parameter is given otherwise just print the
  // current settings
  if (argc > 1) {
    RAIL_RxOptions_t newRxOptions = ciGetUnsigned(argv[1]);
    RAIL_Status_t status = RAIL_ConfigRxOptions(railHandle,
                                                RAIL_RX_OPTIONS_ALL,
                                                newRxOptions);

    // Make sure there was no error setting the new options
    if (status != RAIL_STATUS_NO_ERROR) {
      responsePrintError(argv[0], 31, "RxOptions:Failed");
      return;
    }
    // Update the global rxOptions
    rxOptions = newRxOptions;
  }

  responsePrint(argv[0],
                "storeCrc:%s,ignoreCrcErrors:%s,enableDualSync:%s,"
                "trackAborted:%s,removeAppendedInfo:%s,rxAntenna:%s,"
                "frameDet:%s",
                (rxOptions & RAIL_RX_OPTION_STORE_CRC) ? "True" : "False",
                (rxOptions & RAIL_RX_OPTION_IGNORE_CRC_ERRORS) ? "True" : "False",
                (rxOptions & RAIL_RX_OPTION_ENABLE_DUALSYNC) ? "True" : "False",
                (rxOptions & RAIL_RX_OPTION_TRACK_ABORTED_FRAMES) ? "True" : "False",
                (rxOptions & RAIL_RX_OPTION_REMOVE_APPENDED_INFO) ? "True" : "False",
                configuredRxAntenna(rxOptions),
                (rxOptions & RAIL_RX_OPTION_DISABLE_FRAME_DETECTION) ? "Off" : "On");
}

void setTxTone(int argc, char **argv)
{
  uint8_t enable = ciGetUnsigned(argv[1]);
  streamMode = RAIL_STREAM_CARRIER_WAVE;
  antOptions = RAIL_TX_OPTIONS_DEFAULT;
  if (argc > 2) {
    uint8_t antenna = ciGetUnsigned(argv[2]);
    //Choose any antenna by default
    if (antenna == 1) {
      antOptions = RAIL_TX_OPTION_ANTENNA1;
    } else {
      antOptions = RAIL_TX_OPTION_ANTENNA0;
    }
  }
  enableAppMode(TX_STREAM, enable, argv[0]);
}

void setTxStream(int argc, char **argv)
{
  uint8_t enable = ciGetUnsigned(argv[1]);
  RAIL_StreamMode_t stream = RAIL_STREAM_PN9_STREAM;
  antOptions = RAIL_TX_OPTIONS_DEFAULT;
  if (argc > 3) {
    uint8_t antenna = ciGetUnsigned(argv[3]);
    //Choose any antenna by default
    if (antenna == 1) {
      antOptions = RAIL_TX_OPTION_ANTENNA1;
    } else {
      antOptions = RAIL_TX_OPTION_ANTENNA0;
    }
  }
  if (argc > 2) {
    stream = (RAIL_StreamMode_t) ciGetUnsigned(argv[2]);
    if (stream >= RAIL_STREAM_MODES_COUNT) {
      responsePrintError(argv[0], 1, "Invalid stream mode");
      return;
    }
  }
  streamMode = stream;
  enableAppMode(TX_STREAM, enable, argv[0]);
}

void setDirectMode(int argc, char **argv)
{
  uint8_t enable = ciGetUnsigned(argv[1]);
  enableAppMode(DIRECT, enable, argv[0]);
}

void setDirectTx(int argc, char **argv)
{
  uint8_t enable = ciGetUnsigned(argv[1]);
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  // Make sure that direct mode is enabled to do a direct Tx
  if (currentAppMode() != DIRECT) {
    responsePrintError(argv[0], 7, "DirectMode not enabled");
    return;
  }

  // Stop whatever we were doing so we can go into Tx
  RAIL_Idle(railHandle, RAIL_IDLE_ABORT, false);

  // Either enable or disable the transmitter
  if (enable) {
    // Turn on Tx
    status = RAIL_StartTx(railHandle, channel, RAIL_TX_OPTIONS_DEFAULT, NULL);
  } else {
    if (receiveModeEnabled) {
      status = RAIL_StartRx(railHandle, channel, NULL);
    }
  }
  if (status == RAIL_STATUS_NO_ERROR) {
    responsePrint(argv[0], "DirectTx:%s", (enable ? "Enabled" : "Disabled"));
  } else {
    responsePrintError(argv[0], 8, "DirectMode Rx/Tx not enabled '%d'", status);
  }
}

#include <stdio.h>
#include "em_gpio.h"
#include "em_emu.h"
#include "em_core.h"
#include "retargetserial.h"

#ifndef DEBUG_SLEEP_LOOP
#define DEBUG_SLEEP_LOOP 0
#endif//DEBUG_SLEEP_LOOP

static const char *rfBands[] = { "Off", "GHz", "MHz", "Any", };
static const char *rfSensitivity[] = { "High", "Low" };
static RAIL_RfSenseBand_t rfBand = RAIL_RFSENSE_OFF;
static uint32_t rfUs = 0;

static void RAILCb_SensedRf(void)
{
  counters.rfSensedEvent++;
  if (counters.rfSensedEvent == 0) { // Wrap it to 1 not 0
    counters.rfSensedEvent = 1;
  }
}

void sleep(int argc, char **argv)
{
  char* em4State = "";
  void (*em4Function)(void) = &EMU_EnterEM4;

  uint8_t emMode = ciGetUnsigned(argv[1]);
  uint8_t rfSenseSyncWordNumBytes = 0U;
  uint32_t rfSenseSyncWord = 0U;
  RailRfSenseMode_t mode = RAIL_RFSENSE_MODE_OFF;
  bool enableCb = (emMode & 0x80) ? false : true;
  emMode &= ~0x80;

  if (emMode <= 4) {
    if (emMode == 4) {
#ifdef _SILICON_LABS_32B_SERIES_1
      switch (argv[1][1]) {
        case 's': case 'S': // Configure EM4 Shutoff state
          em4Function = &EMU_EnterEM4S;
          em4State = "s";
          break;
        case 'h': case 'H': // Configure EM4 Hibernate state
          em4Function = &EMU_EnterEM4H;
          em4State = "h";
          break;
        default:
          // Use whatever prior EM4 state was specified
          em4State = (((EMU->EM4CTRL & EMU_EM4CTRL_EM4STATE)
                       == EMU_EM4CTRL_EM4STATE_EM4S) ? "s" : "h");
          break;
      }
#elif _SILICON_LABS_32B_SERIES_2_CONFIG >= 1
      em4State = "s"; // Only EM4 Shutoff supported
#endif
    }
    // Check for Selective(OOK) Mode
    if (argc > 4) {
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 2
      rfSenseSyncWordNumBytes = (ciGetUnsigned(argv[2]) > 4)
                                ? 0 : ciGetUnsigned(argv[2]);
      rfSenseSyncWord = ciGetUnsigned(argv[3]);
      rfBand = ((RAIL_RfSenseBand_t) ciGetUnsigned(argv[4])
                & RAIL_RFENSE_ANY_LOW_SENSITIVITY); // mask off illegal values
      mode = ((rfBand != RAIL_RFSENSE_OFF) && (rfSenseSyncWordNumBytes > 0))
             ? RAIL_RFSENSE_MODE_SELECTIVE_OOK : RAIL_RFSENSE_MODE_OFF;
#else
      responsePrintError(argv[0], 0x15, "RFSENSE Selective OOK Mode Unsupported");
      return;
#endif
    } else {
      // sleep is MODAL -- we'll block here in foreground.
      // If there are new RfSense parameters, grab 'em:
      if (argc > 2) {
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1
        responsePrintError(argv[0], 0x15, "RFSENSE Energy Detect Mode Unsupported");
        return;
#else
        rfUs = ciGetUnsigned(argv[2]);
        if (argc > 3) {
          rfBand = ((RAIL_RfSenseBand_t) ciGetUnsigned(argv[3])
                    & RAIL_RFENSE_ANY_LOW_SENSITIVITY); // mask off illegal values
        }
        mode = ((rfBand != RAIL_RFSENSE_OFF) && (rfUs > 0))
               ? RAIL_RFSENSE_MODE_ENERGY_DETECTION : RAIL_RFSENSE_MODE_OFF;
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG == 1
      }
    }
    // Only call if we plan to enable RFSENSE later.
    if (mode != RAIL_RFSENSE_MODE_OFF) {
      if (!enableAppModeSync(RF_SENSE, true, argv[0])) {
        return;
      }
    } else {
      rfBand = RAIL_RFSENSE_OFF; // rfUs == 0
    }

    // Shut down Peripherals for EM2+ sleep. If the radio is still enabled,
    // the chip will go into EM1P if supported
    if (emMode >= 2) {
      PeripheralDisable();
      GPIO_EM4SetPinRetention(true);
    }

    // We cannot configure UART RxD for EM4 wakeup on our EFR32's so the
    // *only* wakeup possible out of EM4 is RFsense (or reset).
    responsePrint(argv[0], "EM:%u%s,SerialWakeup:%s,RfSense:%s,RfSensitivity:%s",
                  emMode, em4State,
                  (emMode < 4) ? "On" : "Off",
                  rfBands[rfBand & RAIL_RFSENSE_ANY],
                  rfSensitivity[(rfBand & 0x20U) >> 5U]);
    serialWaitForTxIdle();

    // Disable interrupts heading into RAIL_StartRfSense() so we don't miss
    // the event occurring before we try to sleep.
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_CRITICAL();

#ifdef _SILICON_LABS_32B_SERIES_2
    // Sleep the USART Tx pin on series 2 devices to save energy
    if (emMode >= 2) {
      GPIO_PinModeSet(RETARGET_TXPORT, RETARGET_TXPIN, gpioModeDisabled, 1);
    }
#endif
    switch (mode) {
      case RAIL_RFSENSE_MODE_SELECTIVE_OOK:
      {
        RAIL_RfSenseSelectiveOokConfig_t config = {
          .band = rfBand,
          .syncWordNumBytes = rfSenseSyncWordNumBytes,
          .syncWord = rfSenseSyncWord,
          .cb = enableCb ? (&RAILCb_SensedRf) : NULL
        };
        (void) RAIL_StartSelectiveOokRfSense(railHandle, &config);
        break;
      }
      case RAIL_RFSENSE_MODE_ENERGY_DETECTION:
        rfUs = RAIL_StartRfSense(railHandle, rfBand,
                                 rfUs, enableCb ? (&RAILCb_SensedRf) : NULL);
        if (rfUs != 0) {
          break;
        }
      // Fall through
      case RAIL_RFSENSE_MODE_OFF:
        if (currentAppMode() == RF_SENSE) {
          enableAppMode(RF_SENSE, false, NULL);
        }
        break;
    }

    // Configure the USART Rx pin as a GPIO interrupt for sleep-wake purposes,
    // falling-edge only
    GPIO_IntConfig(RETARGET_RXPORT, RETARGET_RXPIN, false, true, true);

    serEvent = false;
    rxPacketEvent = false;

    bool rfSensed;
   #if     DEBUG_SLEEP_LOOP
    uint64_t sleeps = 0;
    typedef struct wakeReasons{
      uint32_t scbInts;
      uint32_t nvicInts[2];
      uint32_t gpioInts;
    } wakeReasons_t;
    // Maintain the most recent two wakeup events in 'circular' list
    wakeReasons_t wakeReasons[2] = { { 0, 0, }, { 0, 0, }, };
   #endif//DEBUG_SLEEP_LOOP

    do { // Loop modally here until either RfSense or Serial event occurs
         //@TODO Should we WDOG_Feed()??
      switch (emMode) {
        case 0:                      break;
        case 1:  EMU_EnterEM1(    ); break;
        case 2:  EMU_EnterEM2(true); break;
        case 3:  EMU_EnterEM3(true); break;
        case 4:  em4Function(    );  break; // NOTREACHED
        default:                     break;
      }
      // After waking, interrupts need to be re-enabled so ISRs can run
     #if     DEBUG_SLEEP_LOOP
      // But grab why we woke first (of course this is meaningless for EM0):
      sleeps++;
      wakeReasons[sleeps & 1].gpioInts = GPIO_IntGetEnabled();
      // No NVIC_ API for this
      wakeReasons[sleeps & 1].nvicInts[0] = NVIC->ISPR[0] /*& NVIC->ISER[0]*/;
      wakeReasons[sleeps & 1].nvicInts[1] = NVIC->ISPR[1] /*& NVIC->ISER[1]*/;
      wakeReasons[sleeps & 1].scbInts = SCB->ICSR;
     #endif//DEBUG_SLEEP_LOOP
      CORE_EXIT_CRITICAL(); // Briefly enable IRQs to let them run
      CORE_ENTER_CRITICAL(); // but shut back off in case we loop
      rfSensed = RAIL_IsRfSensed(railHandle);
    } while (!rfSensed && !serEvent && !rxPacketEvent);
    CORE_EXIT_CRITICAL(); // Back on permanently

    // Here we've awoken for at least one of the desired events.
    // If we woke on serial, don't need RFSense active any more.
    if (currentAppMode() == RF_SENSE) {
      enableAppMode(RF_SENSE, false, NULL);
    }
    // Disable serial interrupt so it's not bothersome
    GPIO_IntConfig(RETARGET_RXPORT, RETARGET_RXPIN, false, true, false);

#ifdef _SILICON_LABS_32B_SERIES_2
    // Wake the USART Tx pin back up
    if (emMode >= 2) {
      GPIO_PinModeSet(RETARGET_TXPORT, RETARGET_TXPIN, gpioModePushPull, 1);
    }
#endif

    responsePrint("sleepWoke",
                  "EM:%u%s,"
                  "SerialWakeup:%s,"
                  "RfSensed:%s,"
                  "PacketRx:%s,"
                  "RfUs:%u"
                 #if     DEBUG_SLEEP_LOOP
                  ",\nSleeps:%llu,"
                  "\nScb[-]:0x%08x,"
                  "Nvic[-]:0x%x.%08x,Gpios[-]:0x%08x,"
                  "\nScb[0]:0x%08x,"
                  "Nvic[0]:0x%x.%08x,Gpios[0]:0x%08x"
                 #endif//DEBUG_SLEEP_LOOP
                  , emMode,
                  em4State,
                  serEvent ? "Yes" : "No",
                  rfSensed ? "Yes" : "No",
                  rxPacketEvent ? "Yes" : "No",
                  rfUs
                 #if     DEBUG_SLEEP_LOOP
                  , sleeps,
                  wakeReasons[(sleeps - 1) & 1].scbInts,
                  wakeReasons[(sleeps - 1) & 1].nvicInts[1],
                  wakeReasons[(sleeps - 1) & 1].nvicInts[0],
                  wakeReasons[(sleeps - 1) & 1].gpioInts,
                  wakeReasons[(sleeps) & 1].scbInts,
                  wakeReasons[(sleeps) & 1].nvicInts[1],
                  wakeReasons[(sleeps) & 1].nvicInts[0],
                  wakeReasons[(sleeps) & 1].gpioInts
                 #endif//DEBUG_SLEEP_LOOP
                  );

    if (serEvent) { // Consume the character entered
      if (emMode >= 2) {
        // If UART was shut down, delay and gobble likely junk
        usDelay(250000); // Pause for 250 ms
        (void) getchar();
        (void) getchar();
        (void) getchar();
        (void) getchar();
      } else {
        while (getchar() < 0) {
        }                         // Gobble the character entered
      }
    }

    // Restart Rx if we're in Rx mode
    if (receiveModeEnabled) {
      if (RAIL_StartRx(railHandle, channel, NULL) != RAIL_STATUS_NO_ERROR) {
        responsePrintError(argv[0], 1, "Could not start receive after sleep");
      }
    }
    // Restart peripherals if they were active before sleeping
    if ((emMode >= 2) && (logLevel & PERIPHERAL_ENABLE)) {
      PeripheralEnable();
    }
  } else {
    responsePrintError(argv[0], 1, "Invalid EM mode %u (valid 0-4)", emMode);
  }
}

void rfSense(int argc, char **argv)
{
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1
  responsePrintError(argv[0], 0x15, "RFSENSE Unsupported");
  return;
#else
  RailRfSenseMode_t mode = RAIL_RFSENSE_MODE_OFF;
  uint8_t rfSenseSyncWordNumBytes = 0U;
  uint32_t rfSenseSyncWord = 0U;
  // Check for Selective(OOK) Mode
  if (argc > 3) {
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 2
    rfSenseSyncWordNumBytes = (ciGetUnsigned(argv[1]) > 4)
                              ? 0 : ciGetUnsigned(argv[1]);
    rfSenseSyncWord = ciGetUnsigned(argv[2]);
    rfBand = ((RAIL_RfSenseBand_t) ciGetUnsigned(argv[3])
              & RAIL_RFENSE_ANY_LOW_SENSITIVITY); // mask off illegal values
    mode = ((rfBand != RAIL_RFSENSE_OFF) && (rfSenseSyncWordNumBytes > 0))
           ? RAIL_RFSENSE_MODE_SELECTIVE_OOK : RAIL_RFSENSE_MODE_OFF;
#else
    responsePrintError(argv[0], 0x15, "RFSENSE Selective OOK Mode Unsupported");
    return;
#endif
  } else {
    // If there are RfSense parameters, grab 'em; otherwise use prior settings
    if (argc > 1) {
      rfUs = ciGetUnsigned(argv[1]);
      if (argc > 2) {
        rfBand = ((RAIL_RfSenseBand_t) ciGetUnsigned(argv[2])
                  & RAIL_RFENSE_ANY_LOW_SENSITIVITY); // mask off illegal values
      }
      mode = ((rfBand != RAIL_RFSENSE_OFF) && (rfUs > 0))
             ? RAIL_RFSENSE_MODE_ENERGY_DETECTION : RAIL_RFSENSE_MODE_OFF;
    }
  }

  if (!enableAppModeSync(RF_SENSE, mode != RAIL_RFSENSE_MODE_OFF, argv[0])) {
    return;
  }

  switch (mode) {
    case RAIL_RFSENSE_MODE_SELECTIVE_OOK:
    {
      RAIL_RfSenseSelectiveOokConfig_t config = {
        .band = rfBand,
        .syncWordNumBytes = rfSenseSyncWordNumBytes,
        .syncWord = rfSenseSyncWord,
        .cb = &RAILCb_SensedRf
      };
      (void) RAIL_StartSelectiveOokRfSense(railHandle, &config);
      break;
    }
    case RAIL_RFSENSE_MODE_ENERGY_DETECTION:
      rfUs = RAIL_StartRfSense(railHandle, rfBand, rfUs, &RAILCb_SensedRf);
      if (rfUs != 0) {
        break;
      }
    // Fall through
    case RAIL_RFSENSE_MODE_OFF:
      rfBand = RAIL_RFSENSE_OFF;
      if (currentAppMode() == RF_SENSE) {
        enableAppMode(RF_SENSE, false, NULL);
      }
      break;
  }

  responsePrint(argv[0], "RfBand:%s,RfUs:%u,RfSensitivity:%s",
                rfBands[rfBand & RAIL_RFSENSE_ANY],
                rfUs,
                rfSensitivity[(rfBand & 0x20U) >> 5U]);
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG == 1
}

void rfSensedCheck(void)
{
  // If in RfSensing background mode, see if Rf got sensed
  if ((currentAppMode() == RF_SENSE) && RAIL_IsRfSensed(railHandle)) {
    // Yes, it did!  Terminate RfSensing background mode
    enableAppMode(RF_SENSE, false, NULL);
    responsePrint("rfSensedCheck", "RfSensed:%s,RfUs:%u",
                  rfBands[rfBand & RAIL_RFSENSE_ANY], rfUs);
  }
}

/**
 * Routine to parse a RAIL timer mode from a string.
 *
 * @param str The string to parse. Must be one of the following:
 * - 'rel': RAIL_TIME_DELAY
 * - 'abs': RAIL_TIME_ABSOLUTE
 * - 'dis': RAIL_TIME_DISABLED
 * @param mode The RAIL_TimeMode_t variable to fill in with the result of this
 * conversion.
 * @return Returns true if we were able to successfully convert the string into
 * a time mode and false if we could not.
 */
bool parseTimeModeFromString(char *str, RAIL_TimeMode_t *mode)
{
  if (strcasecmp("dis", str) == 0) {
    *mode = RAIL_TIME_DISABLED;
  } else if (strcasecmp("rel", str) == 0) {
    *mode = RAIL_TIME_DELAY;
  } else if (strcasecmp("abs", str) == 0) {
    *mode = RAIL_TIME_ABSOLUTE;
  } else {
    *mode = RAIL_TIME_DISABLED;
    return false;
  }
  return true;
}

// Must match RAIL_TimePosition_t enum values as indices:
static const char *timePosStrings[RAIL_PACKET_TIME_COUNT] = {
  "INVALID",
  "DEFAULT",
  "PREAMBLE_START",
  "PREAMBLE_START_UT",
  "SYNC_END",
  "SYNC_END_UT",
  "PACKET_END",
  "PACKET_END_UT",
};

void setTxTimePos(int argc, char **argv)
{
  uint32_t pos = ciGetUnsigned(argv[1]);
  if (pos < RAIL_PACKET_TIME_COUNT) {
    txTimePosition = pos;
    responsePrint(argv[0], "txTimePos:%s", timePosStrings[pos]);
  } else {
    responsePrintError(argv[0], 1, "Invalid TimePosition %u (valid 0-%u)",
                       pos, RAIL_PACKET_TIME_COUNT - 1);
  }
}

void setRxTimePos(int argc, char **argv)
{
  uint32_t pos = ciGetUnsigned(argv[1]);
  if (pos < RAIL_PACKET_TIME_COUNT) {
    rxTimePosition = pos;
    responsePrint(argv[0], "rxTimePos:%s", timePosStrings[pos]);
  } else {
    responsePrintError(argv[0], 1, "Invalid TimePosition %u (valid 0-%u)",
                       pos, RAIL_PACKET_TIME_COUNT - 1);
  }
}

void holdRx(int argc, char **argv)
{
  rxHeld = (bool)ciGetUnsigned(argv[1]);
  rxProcessHeld = !rxHeld;
  responsePrint(argv[0], "HoldRx:%s",
                rxHeld ? "Enabled" : "Disabled");
}
