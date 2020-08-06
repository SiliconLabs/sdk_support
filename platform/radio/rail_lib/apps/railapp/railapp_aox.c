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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "em_cmu.h"
#include "em_gpio.h"
#include "em_common.h"
#include "rail_types.h"
#include "rail_ble.h"
#include "railapp_aox.h"
#include "railapp_malloc.h"
#include "response_print.h"
#include "command_interpreter.h"

extern RAIL_Handle_t railHandle;
bool autoUnlockCteBuffer = false;
RAIL_BLE_AoxAntennaConfig_t antennaConfig = { 0 };
RAIL_BLE_AoxAntennaPortPins_t antennaPortPin[6] = { 0 };

// AoX-related variables
// Number of samples to capture, each element represents a single I or Q sample
// Sample rate is either 4.8 or 4.0 MS/sec = 4.8 or 4.0 Samples/us
// Max number of CTE periods is 160 us (20 units of 8 us)
#if _SILICON_LABS_32B_SERIES_1_CONFIG == 3
// Max number of samples is given by: 4.8 Samples/us x 160 us = 768 Samples * 2 (I & Q) = 1536 Samples
#define CTE_SAMPLE_COUNT (1536)
// Max number of samples is given by:
// 1Mbps - 4.0 Samples/us x 160 us =  640 Samples * 2 (I & Q) = 1280 Samples
// 2Mbps - 8.0 Samples/us x 160 us = 1280 Samples * 2 (I & Q) = 2560 Samples
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 2
#define CTE_SAMPLE_COUNT (2560)
#else
#define CTE_SAMPLE_COUNT (0)
#endif

uint16_t *cteBuffer = NULL;

#define CTE_BUFFER_SIZE (CTE_SAMPLE_COUNT * sizeof(uint16_t))
uint32_t antennaSwitchingPattern[64] = { 1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0,
                                         1, 0, 1, 0, 1, 0, 1, 0 };
RAIL_BLE_AoxConfig_t aoxConfig =
{
  .aoxOptions = 0,
  .cteBuffAddr = NULL,
  .cteBuffSize = 0U,
  .antArrayAddr = antennaSwitchingPattern,
  .antArraySize = sizeof(antennaSwitchingPattern) / sizeof(antennaSwitchingPattern[0]),
};

RAIL_Status_t RAILAPP_ConfigAox(const RAIL_BLE_AoxOptions_t aoxOptions,
                                RAIL_BLE_AoxAntennaConfig_t *antennaConfig)
{
  if (cteBuffer == NULL) {
    cteBuffer = (uint16_t*)RAILAPP_Malloc(CTE_BUFFER_SIZE);
  }
  aoxConfig.cteBuffAddr = (uint32_t *)cteBuffer;
  if (aoxConfig.cteBuffAddr != NULL) {
    aoxConfig.cteBuffSize = CTE_BUFFER_SIZE;
  } else {
    aoxConfig.cteBuffSize = 0U;
    return RAIL_STATUS_INVALID_CALL;
  }

  aoxConfig.aoxOptions = aoxOptions;
  if (aoxConfig.aoxOptions & RAIL_BLE_AOX_OPTIONS_ENABLED) {
    // Turn on the GPIO clock since we're going to need that
    CMU_ClockEnable(cmuClock_GPIO, true);
  }
  RAIL_Status_t returnStatus = RAIL_STATUS_NO_ERROR;

  returnStatus = RAIL_BLE_ConfigAoxAntenna(railHandle, antennaConfig);
  if (returnStatus == RAIL_STATUS_NO_ERROR) {
    returnStatus = RAIL_BLE_InitCte(railHandle);
    if (returnStatus == RAIL_STATUS_NO_ERROR) {
      returnStatus = RAIL_BLE_ConfigAox(railHandle, &aoxConfig);
    }
  }

  return returnStatus;
}

uint32_t RAILAPP_GetCteSampleRate(void)
{
  return RAIL_BLE_GetCteSampleRate(railHandle);
}

bool RAILAPP_SetCteBufferLock(bool lock)
{
  return RAIL_BLE_LockCteBuffer(railHandle, lock);
}

bool RAILAPP_GetCteBufferLock(void)
{
  return RAIL_BLE_CteBufferIsLocked(railHandle);
}

#if defined(CLI_INTERFACE) && RAIL_FEAT_BLE_AOX_SUPPORTED

void CI_configAox(int argc, char **argv)
{
  if (argc > 1) {
    RAIL_BLE_AoxOptions_t aoxOptions = ciGetUnsigned(argv[1]);
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 2
    if (argc > 2) {
      if ((argc - 2) % 2 == 0) { //Matching ports and pins
        antennaConfig.antCount = (argc - 2) / 2;
        for (int i = 0; i < antennaConfig.antCount; i++) {
          antennaPortPin[i].antPort = ciGetUnsigned(argv[2 + (2 * i)]);
          antennaPortPin[i].antPin =  ciGetUnsigned(argv[3 + (2 * i)]);
        }
        antennaConfig.antPortPin = antennaPortPin;
      }
    }
#endif
    RAIL_Status_t status = RAILAPP_ConfigAox(aoxOptions, &antennaConfig);
    responsePrint(argv[0], "Result:%s",
                  status == RAIL_STATUS_NO_ERROR ? "Success" : "Failure");
  } else {
    responsePrint(argv[0], "Result:Error");
  }
}

void CI_getRawCteSamples(int argc, char **argv)
{
  uint16_t cteLength = CTE_SAMPLE_COUNT;
  responsePrintStart(argv[0]);
  responsePrintContinue("len:%d", cteLength);
  if (cteBuffer != NULL) {
    // Manually print out CTE words (IQ pairs) iteratively, so that we don't
    // need to reserve a RAM buffer. Finish the response here.
    printf("{CTE:");
    for (int i = 0; i < cteLength; i++) {
      printf(" 0x%.4x", cteBuffer[i]);
    }
    printf("}");
  }
  printf("}\n");
}

void CI_getCteSampleRate(int argc, char **argv)
{
  // Get the current sample rate used to capture the CTE samples
  uint32_t sampleRate = RAILAPP_GetCteSampleRate();
  responsePrint(argv[0], "CTE Sample Rate:%d", sampleRate);
}

void CI_setCteBufferLock(int argc, char **argv)
{
  bool cteBufferLock = !!ciGetUnsigned(argv[1]);

  // Report the current state of the CTE buffer after calling
  // RAILAPP_SetCteBufferLock
  bool cteBufferLocked = RAILAPP_SetCteBufferLock(cteBufferLock);
  responsePrint(argv[0], "CTE buffer:%s", cteBufferLocked ? "Locked" : "Unlocked");
}

void CI_getCteBufferLock(int argc, char **argv)
{
  bool cteBufferLocked = RAILAPP_GetCteBufferLock();

  // Report the current state of the CTE buffer
  responsePrint(argv[0], "CTE buffer:%s", cteBufferLocked ? "Locked" : "Unlocked");
}

void CI_enableRxAutoCteBufferUnlock(int argc, char **argv)
{
  autoUnlockCteBuffer = ciGetUnsigned(argv[1]);
  responsePrint(argv[0], "Enabled:%s", autoUnlockCteBuffer ? "Success" : "Failure");
}

#endif
