/***************************************************************************//**
 * @file
 * @brief This file implements informational commands for RAIL test applications.
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
#include "command_interpreter.h"
#include "response_print.h"

#include "rail.h"
#include "rail_types.h"
#include "rail_features.h"
#include "rail_ieee802154.h"
#include "app_common.h"

static void printBitField(uint32_t bitField,
                          char** fieldNames,
                          uint8_t numFields)
{
  uint8_t i;
  for (i = 0; i < numFields; ++i) {
    responsePrintContinue("%s:%u", fieldNames[i], bitField & 1);
    bitField >>= 1;
  }
}

static void printRailState(void)
{
  static char* railStates[] = { "RAIL_state_active",
                                "RAIL_state_rx",
                                "RAIL_state_tx" };
  RAIL_RadioState_t rfState = RAIL_GetRadioState(railHandle);
  responsePrintContinue("RfState:%s",
                        getRfStateName(rfState));
  printBitField(rfState,
                railStates,
                sizeof(railStates) / sizeof(railStates[0])
                );
}

const char *getStatusMessage(RAIL_Status_t status)
{
  switch (status) {
    case RAIL_STATUS_NO_ERROR:
      return "Success";
    case RAIL_STATUS_INVALID_PARAMETER:
      return "InvalidParameter";
    case RAIL_STATUS_INVALID_STATE:
      return "InvalidState";
    case RAIL_STATUS_INVALID_CALL:
      return "InvalidCall";
    default:
      return "Unknown";
  }
}

void getStatus(int argc, char **argv)
{
  responsePrintStart(argv[0]);
  responsePrintContinue("UserTxCount:%u,"
                        "AckTxCount:%u,"
                        "UserTxAborted:%u,"
                        "AckTxAborted:%u,"
                        "UserTxBlocked:%u,"
                        "AckTxBlocked:%u,"
                        "UserTxUnderflow:%u,"
                        "AckTxUnderflow:%u,"
                        "RxCount:%u,"
                        "SyncDetect:%u,"
                        "NoRxBuffer:%u,"
                        "RfSensed:%u",
                        counters.userTx,
                        counters.ackTx,
                        counters.userTxAborted,
                        counters.ackTxAborted,
                        counters.userTxBlocked,
                        counters.ackTxBlocked,
                        counters.userTxUnderflow,
                        counters.ackTxUnderflow,
                        counters.receive,
                        counters.syncDetect,
                        counters.noRxBuffer,
                        counters.rfSensedEvent
                        );
  responsePrintContinue("ackTimeout:%u,"
                        "ackTxFpSet:%u,"
                        "ackTxFpFail:%u,"
                        "ackTxFpAddrFail:%u",
                        counters.ackTimeout,
                        counters.ackTxFpSet,
                        counters.ackTxFpFail,
                        counters.ackTxFpAddrFail
                        );
  printRailState();
  responsePrintContinue("Channel:%u,"
                        "AppMode:%s,"
                        "TimingLost:%u,"
                        "TimingDetect:%u,"
                        "FrameErrors:%u,"
                        "RxFifoFull:%u,"
                        "RxOverflow:%u,"
                        "AddrFilt:%u,"
                        "Aborted:%u",
                        channel,
                        appModeNames(currentAppMode()),
                        counters.timingLost,
                        counters.timingDetect,
                        counters.frameError,
                        counters.rxFifoFull,
                        counters.rxOfEvent,
                        counters.addrFilterEvent,
                        counters.rxFail
                        );
  responsePrintEnd("RxBeams:%u,"
                   "DataRequests:%u,"
                   "Calibrations:%u,"
                   "TxChannelBusy:%u,"
                   "TxClear:%u,"
                   "TxCca:%u,"
                   "TxRetry:%u,"
                   "UserTxStarted:%u",
                   counters.rxBeams,
                   counters.dataRequests,
                   counters.calibrations,
                   counters.txChannelBusy,
                   counters.lbtSuccess,
                   counters.lbtStartCca,
                   counters.lbtRetry,
                   counters.userTxStarted
                   );
}

void fifoStatus(int argc, char**argv)
{
  uint16_t spaceCount =  RAIL_GetTxFifoSpaceAvailable(railHandle);
  uint16_t byteCount = RAIL_GetRxFifoBytesAvailable(railHandle);
  responsePrint(argv[0],
                "TxSpaceCount:%u,"
                "RxByteCount:%u,"
                "TxFifoThreshold:%d,"
                "RxFifoThreshold:%d,"
                "TxFifoAlmostEmpty:%u,"
                "RxFifoAlmostFull:%u,"
                "RxFifoFull:%u,"
                "RxOverflow:%u,"
                "UserTxUnderflow:%u,"
                "AckTxUnderflow:%u",
                spaceCount,
                byteCount,
                RAIL_GetTxFifoThreshold(railHandle),
                RAIL_GetRxFifoThreshold(railHandle),
                counters.txFifoAlmostEmpty,
                counters.rxFifoAlmostFull,
                counters.rxFifoFull,
                counters.rxOfEvent,
                counters.userTxUnderflow,
                counters.ackTxUnderflow
                );
}

void getVersion(int argc, char **argv)
{
  RAIL_Version_t rail_ver;
  RAIL_GetVersion(&rail_ver, false);
  responsePrint(argv[0], "App:%d.%d.%d,RAIL:%d.%d.%d,Multiprotocol:%s,"
                         "Built:%s",
                rail_ver.major, rail_ver.minor, rail_ver.rev,
                rail_ver.major, rail_ver.minor, rail_ver.rev,
                rail_ver.multiprotocol ? "True" : "False",
                buildDateTime);
}

void setPtiProtocol(int argc, char **argv)
{
  RAIL_Status_t status = RAIL_SetPtiProtocol(railHandle,
                                             (RAIL_PtiProtocol_t) ciGetUnsigned(argv[1]));
  responsePrint(argv[0], "Pti:%s", status ? "Error" : "Set");
}

void getVersionVerbose(int argc, char **argv)
{
  RAIL_Version_t rail_ver;
  RAIL_GetVersion(&rail_ver, true);
  responsePrint(argv[0], "App:%d.%d.%d,RAIL:%d.%d.%d.%d",
                rail_ver.major, rail_ver.minor, rail_ver.rev,
                rail_ver.major, rail_ver.minor, rail_ver.rev, rail_ver.build);
  responsePrint(argv[0], "hash:0x%.8X,flags:0x%.2X",
                rail_ver.hash, rail_ver.flags);
}

void offsetLqi(int argc, char **argv)
{
  int32_t offset = ciGetSigned(argv[1]);
  if ((offset > 0xFF) || (offset < -0xFF)) {
    responsePrintError(argv[0], 0x08,
                       "Invalid value. Must be between -255 and 255.");
    return;
  }
  lqiOffset = (int16_t)offset;
  responsePrint(argv[0], "lqiOffset:%d", lqiOffset);
}

void getRssi(int argc, char **argv)
{
  char bufRssi[10];
  bool wait = false;

  if (argc == 2) {
    wait = !!ciGetUnsigned(argv[1]);
  }
  CHECK_RAIL_HANDLE(argv[0]);
  int16_t rssi = RAIL_GetRssi(railHandle, wait);

  // The lowest negative value is used to indicate an error reading the RSSI
  if (rssi == RAIL_RSSI_INVALID) {
    responsePrintError(argv[0], 0x08, "Could not read RSSI. Ensure Rx is enabled");
    return;
  }

  sprintfFloat(bufRssi, sizeof(bufRssi), ((float) rssi / 4), 2);
  if (RAIL_IEEE802154_IsEnabled(railHandle)) {
    uint8_t energyDetect = RAIL_IEEE802154_ConvertRssiToEd(rssi / 4);
    responsePrint(argv[0], "rssi:%s,ed154:%u", bufRssi, energyDetect);
  } else {
    responsePrint(argv[0], "rssi:%s", bufRssi);
  }
}

void startAvgRssi(int argc, char **argv)
{
  uint32_t averageTimeUs = ciGetUnsigned(argv[1]);
  uint8_t avgChannel = channel;
  if (argc == 3) {
    avgChannel = ciGetUnsigned(argv[2]);
  }
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, NULL)) {
    responsePrintError(argv[0], 0x08, "Could not read RSSI. Ensure RX is disabled.");
    return;
  } else if (RAIL_StartAverageRssi(railHandle, avgChannel, averageTimeUs, NULL) != RAIL_STATUS_NO_ERROR) {
    responsePrintError(argv[0], 0x08, "Could not read RSSI.");
    return;
  }
}
void getAvgRssi(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  int16_t rssi = RAIL_GetAverageRssi(railHandle);
  char bufRssi[10];
  if (rssi == RAIL_RSSI_INVALID) {
    responsePrintError(argv[0], 0x08, "Invalid RSSI. Make sure startAvgRssi ran successfully.");
    return;
  }
  sprintfFloat(bufRssi, sizeof(bufRssi), ((float) rssi / 4), 2);
  responsePrint(argv[0], "rssi:%s", bufRssi);
}
void setRssiOffset(int argc, char **argv)
{
  int8_t rssiOffset = ciGetSigned(argv[1]);
  CHECK_RAIL_HANDLE(argv[0]);
  if (RAIL_STATUS_NO_ERROR != RAIL_SetRssiOffset(railHandle, rssiOffset)) {
    responsePrint(argv[0], "Error setting the rssiOffset");
  } else {
    rssiOffset = RAIL_GetRssiOffset(railHandle);
    responsePrint(argv[0], "rssiOffset:%d", rssiOffset);
  }
}
void getRssiOffset(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  int8_t rssiOffset = RAIL_GetRssiOffset(railHandle);
  responsePrint(argv[0], "rssiOffset:%d", rssiOffset);
}
void sweepPower(int argc, char **argv)
{
  int32_t lowPower = ciGetUnsigned(argv[1]);
  int32_t hiPower = ciGetUnsigned(argv[2]);
  int32_t period = ciGetUnsigned(argv[3]);
  int32_t halfPeriodStepUs = period / 2;
  uint32_t expired = RAIL_GetTime() + (uint32_t)5000000;
  while (expired > RAIL_GetTime()) {
    RAIL_StopTxStream(railHandle);
    RAIL_Idle(railHandle, RAIL_IDLE_ABORT, false);
    RAIL_SetTxPower(railHandle, lowPower);
    RAIL_StartTxStream(railHandle, channel, RAIL_STREAM_CARRIER_WAVE);
    usDelay(halfPeriodStepUs);
    RAIL_StopTxStream(railHandle);
    RAIL_Idle(railHandle, RAIL_IDLE_ABORT, false);
    RAIL_SetTxPower(railHandle, hiPower);
    RAIL_StartTxStream(railHandle, channel, RAIL_STREAM_CARRIER_WAVE);
    usDelay(halfPeriodStepUs);
  }
  RAIL_StopTxStream(railHandle);
}

void isRssiRdy(int argc, char **argv)
{
  if (RAIL_IsAverageRssiReady(railHandle)) {
    responsePrint(argv[0], "isReady:True");
  } else {
    responsePrint(argv[0], "isReady:False");
  }
  return;
}

void resetCounters(int argc, char **argv)
{
  memset(&counters, 0, sizeof(counters));
  getStatus(1, argv);
}

void getTime(int argc, char **argv)
{
  responsePrint(argv[0], "Time:%u", RAIL_GetTime());
}

void setTime(int argc, char **argv)
{
  uint32_t timeUs = ciGetUnsigned(argv[1]);
  if (RAIL_STATUS_NO_ERROR == RAIL_SetTime(timeUs)) {
    responsePrint(argv[0], "Status:Success,CurrentTime:%u", RAIL_GetTime());
  } else {
    responsePrint(argv[0], "Status:Error,CurrentTime:%u", RAIL_GetTime());
  }
}

void printChipFeatures(int argc, char **argv)
{
  RAIL_TxPowerLevel_t maxPowerLevel;
  responsePrintHeader(argv[0], "Feature:%s,CompileTime:%s,RunTime:%s");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_DUAL_BAND",
                     RAIL_SUPPORTS_DUAL_BAND ? "Yes" : "No",
                     RAIL_SupportsDualBand(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_2P4GHZ_BAND",
                     RAIL_SUPPORTS_2P4GHZ_BAND ? "Yes" : "No",
                     RAIL_Supports2p4GHzBand(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_SUBGHZ_BAND",
                     RAIL_SUPPORTS_SUBGHZ_BAND ? "Yes" : "No",
                     RAIL_SupportsSubGHzBand(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_ALTERNATE_TX_POWER",
                     RAIL_SUPPORTS_ALTERNATE_TX_POWER ? "Yes" : "No",
                     RAIL_SupportsAlternateTxPower(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_ANTENNA_DIVERSITY",
                     RAIL_SUPPORTS_ANTENNA_DIVERSITY ? "Yes" : "No",
                     RAIL_SupportsAntennaDiversity(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_CHANNEL_HOPPING",
                     RAIL_SUPPORTS_CHANNEL_HOPPING ? "Yes" : "No",
                     RAIL_SupportsChannelHopping(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_DUAL_SYNC_WORDS",
                     RAIL_SUPPORTS_DUAL_SYNC_WORDS ? "Yes" : "No",
                     RAIL_SupportsDualSyncWords(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_EXTERNAL_THERMISTOR",
                     RAIL_SUPPORTS_EXTERNAL_THERMISTOR ? "Yes" : "No",
                     RAIL_SupportsExternalThermistor(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_PRECISION_LFRCO",
                     RAIL_SUPPORTS_PRECISION_LFRCO ? "Yes" : "No",
                     RAIL_SupportsPrecisionLFRCO(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_RADIO_ENTROPY",
                     RAIL_SUPPORTS_RADIO_ENTROPY ? "Yes" : "No",
                     RAIL_SupportsRadioEntropy(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK",
                     RAIL_SUPPORTS_RFSENSE_SELECTIVE_OOK ? "Yes" : "No",
                     RAIL_SupportsRfSenseSelectiveOok(railHandle) ? "Yes" : "No");
 #ifdef  RAIL_TX_POWER_MODE_2P4GIG_HIGHEST
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_2P4GIG_HIGHEST,
                               &maxPowerLevel)
      && (maxPowerLevel != RAIL_TX_POWER_LEVEL_INVALID)) {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%u",
                       "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST", "Yes",
                       maxPowerLevel);
  } else {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                       "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST", "Yes", "No");
  }
 #else
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST", "N/A", "N/A");
 #endif//RAIL_TX_POWER_MODE_2P4GIG_HIGHEST
 #ifdef  RAIL_TX_POWER_MODE_2P4GIG_HP
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_2P4GIG_HP,
                               &maxPowerLevel)
      && (maxPowerLevel != RAIL_TX_POWER_LEVEL_INVALID)) {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%u",
                       "RAIL_TX_POWER_MODE_2P4GIG_HP", "Yes",
                       maxPowerLevel);
  } else {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                       "RAIL_TX_POWER_MODE_2P4GIG_HP", "Yes", "No");
  }
 #else
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_TX_POWER_MODE_2P4GIG_HP", "N/A", "N/A");
 #endif//RAIL_TX_POWER_MODE_2P4GIG_HP
 #ifdef  RAIL_TX_POWER_MODE_2P4GIG_MP
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_2P4GIG_MP,
                               &maxPowerLevel)
      && (maxPowerLevel != RAIL_TX_POWER_LEVEL_INVALID)) {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%u",
                       "RAIL_TX_POWER_MODE_2P4GIG_MP", "Yes",
                       maxPowerLevel);
  } else {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                       "RAIL_TX_POWER_MODE_2P4GIG_MP", "Yes", "No");
  }
 #else
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_TX_POWER_MODE_2P4GIG_MP", "N/A", "N/A");
 #endif//RAIL_TX_POWER_MODE_2P4GIG_LP
 #ifdef  RAIL_TX_POWER_MODE_2P4GIG_LP
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_2P4GIG_LP,
                               &maxPowerLevel)
      && (maxPowerLevel != RAIL_TX_POWER_LEVEL_INVALID)) {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%u",
                       "RAIL_TX_POWER_MODE_2P4GIG_LP", "Yes",
                       maxPowerLevel);
  } else {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                       "RAIL_TX_POWER_MODE_2P4GIG_LP", "Yes", "No");
  }
 #else
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_TX_POWER_MODE_2P4GIG_LP", "N/A", "N/A");
 #endif//RAIL_TX_POWER_MODE_2P4GIG_LP
 #ifdef  RAIL_TX_POWER_MODE_SUBGIG
  if (RAIL_SupportsTxPowerMode(railHandle,
                               RAIL_TX_POWER_MODE_SUBGIG,
                               &maxPowerLevel)
      && (maxPowerLevel != RAIL_TX_POWER_LEVEL_INVALID)) {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%u",
                       "RAIL_TX_POWER_MODE_SUBGIG", "Yes",
                       maxPowerLevel);
  } else {
    responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                       "RAIL_TX_POWER_MODE_SUBGIG", "Yes", "No");
  }
 #else
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_TX_POWER_MODE_SUBGIG", "N/A", "N/A");
 #endif//RAIL_TX_POWER_MODE_SUBGIG
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_PROTOCOL_BLE",
                     RAIL_SUPPORTS_PROTOCOL_BLE ? "Yes" : "No",
                     RAIL_SupportsProtocolBLE(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI",
                     RAIL_BLE_SUPPORTS_1MBPS_NON_VITERBI ? "Yes" : "No",
                     RAIL_BLE_Supports1MbpsNonViterbi(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_1MBPS_VITERBI",
                     RAIL_BLE_SUPPORTS_1MBPS_VITERBI ? "Yes" : "No",
                     RAIL_BLE_Supports1MbpsViterbi(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_1MBPS",
                     RAIL_BLE_SUPPORTS_1MBPS ? "Yes" : "No",
                     RAIL_BLE_Supports1Mbps(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI",
                     RAIL_BLE_SUPPORTS_2MBPS_NON_VITERBI ? "Yes" : "No",
                     RAIL_BLE_Supports2MbpsNonViterbi(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_2MBPS_VITERBI",
                     RAIL_BLE_SUPPORTS_2MBPS_VITERBI ? "Yes" : "No",
                     RAIL_BLE_Supports2MbpsViterbi(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_2MBPS",
                     RAIL_BLE_SUPPORTS_2MBPS ? "Yes" : "No",
                     RAIL_BLE_Supports2Mbps(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING",
                     RAIL_BLE_SUPPORTS_ANTENNA_SWITCHING ? "Yes" : "No",
                     RAIL_BLE_SupportsAntennaSwitching(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_CODED_PHY",
                     RAIL_BLE_SUPPORTS_CODED_PHY ? "Yes" : "No",
                     RAIL_BLE_SupportsCodedPhy(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_CTE",
                     RAIL_BLE_SUPPORTS_CTE ? "Yes" : "No",
                     RAIL_BLE_SupportsCte(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_IQ_SAMPLING",
                     RAIL_BLE_SUPPORTS_IQ_SAMPLING ? "Yes" : "No",
                     RAIL_BLE_SupportsIQSampling(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX",
                     RAIL_BLE_SUPPORTS_PHY_SWITCH_TO_RX ? "Yes" : "No",
                     RAIL_BLE_SupportsPhySwitchToRx(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_PROTOCOL_IEEE802154",
                     RAIL_SUPPORTS_PROTOCOL_IEEE802154 ? "Yes" : "No",
                     RAIL_SupportsProtocolIEEE802154(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_COEX_PHY",
                     RAIL_IEEE802154_SUPPORTS_COEX_PHY ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsCoexPhy(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868",
                     RAIL_IEEE802154_SUPPORTS_E_SUBSET_GB868 ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsESubsetGB868(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK",
                     RAIL_IEEE802154_SUPPORTS_E_ENHANCED_ACK ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsEEnhancedAck(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868",
                     RAIL_IEEE802154_SUPPORTS_G_SUBSET_GB868 ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsGSubsetGB868(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX",
                     RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_RX ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsGUnwhitenedRx(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX",
                     RAIL_IEEE802154_SUPPORTS_G_UNWHITENED_TX ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsGUnwhitenedTx(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC",
                     RAIL_IEEE802154_SUPPORTS_G_4BYTE_CRC ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsG4ByteCrc(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP",
                     RAIL_IEEE802154_SUPPORTS_CANCEL_FRAME_PENDING_LOOKUP ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsCancelFramePendingLookup(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP",
                     RAIL_IEEE802154_SUPPORTS_EARLY_FRAME_PENDING_LOOKUP ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsEarlyFramePendingLookup(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES",
                     RAIL_IEEE802154_SUPPORTS_E_MULTIPURPOSE_FRAMES ? "Yes" : "No",
                     RAIL_IEEE802154_SupportsEMultipurposeFrames(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_SUPPORTS_PROTOCOL_ZWAVE",
                     RAIL_SUPPORTS_PROTOCOL_ZWAVE ? "Yes" : "No",
                     RAIL_SupportsProtocolZWave(railHandle) ? "Yes" : "No");
  responsePrintMulti("Feature:%s,CompileTime:%s,RunTime:%s",
                     "RAIL_ZWAVE_SUPPORTS_REGION_PTI",
                     RAIL_ZWAVE_SUPPORTS_REGION_PTI ? "Yes" : "No",
                     RAIL_ZWAVE_SupportsRegionPti(railHandle) ? "Yes" : "No");
}
