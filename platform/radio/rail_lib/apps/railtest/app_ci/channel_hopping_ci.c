/***************************************************************************//**
 * @file
 * @brief This file implements the autoack commands in RAIL test apps.
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

#include "command_interpreter.h"
#include "response_print.h"

#include "rail.h"
#include "rail_features.h"
#include "app_common.h"
#include "app_ci.h"

#if RAIL_FEAT_CHANNEL_HOPPING

RAIL_RxChannelHoppingConfigEntry_t channelHoppingEntries[MAX_NUMBER_CHANNELS];
RAIL_RxChannelHoppingConfig_t channelHoppingConfig = {
  .entries = channelHoppingEntries,
  .bufferLength = CHANNEL_HOPPING_BUFFER_SIZE,
  .numberOfChannels = 0
};

void configRxChannelHopping(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }

  channelHoppingConfig.buffer = channelHoppingBuffer;
  uint8_t i;
  for (i = 1; i * 4 < argc; i++) {
    if (ciGetUnsigned(argv[(i * 4) - 3]) > (uint32_t)UINT16_MAX) {
      responsePrintError(argv[0], 0x16, "Channel must be a 16 bit value.");
      return;
    }
    channelHoppingEntries[i - 1].channel = ciGetUnsigned(argv[(i * 4) - 3]);
    channelHoppingEntries[i - 1].mode = ciGetUnsigned(argv[(i * 4) - 2]);
    channelHoppingEntries[i - 1].parameter = ciGetUnsigned(argv[i * 4 - 1]);
    channelHoppingEntries[i - 1].delay = ciGetUnsigned(argv[i * 4]);
    channelHoppingEntries[i - 1].delayMode = RAIL_RX_CHANNEL_HOPPING_DELAY_MODE_STATIC;
  }
  channelHoppingConfig.numberOfChannels = i - 1;

  RAIL_Status_t status = RAIL_ConfigRxChannelHopping(railHandle, &channelHoppingConfig);
  responsePrint(argv[0], "numberOfChannels:%d,buffer:0x%x,Success:%s",
                i - 1,
                channelHoppingConfig.buffer,
                status == RAIL_STATUS_NO_ERROR ? "True" : "False");
}

void configChannelHoppingOptions(int argc, char **argv)
{
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }

  uint8_t index = ciGetUnsigned(argv[1]);
  uint32_t options = ciGetUnsigned(argv[2]);

  channelHoppingEntries[index].options = options;

  responsePrint(argv[0], "index:%u,options:%u", index, options);
}

void enableRxChannelHopping(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  bool enable = !!ciGetUnsigned(argv[1]);

  bool reset = false;
  if (argc > 2) {
    reset = !!ciGetUnsigned(argv[2]);
  }

  RAIL_Status_t status = RAIL_EnableRxChannelHopping(railHandle, enable, reset);
  responsePrint(argv[0], "Success:%s", status == RAIL_STATUS_NO_ERROR ? "True" : "False");
}

void getChannelHoppingRssi(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  uint8_t channelIndex = ciGetUnsigned(argv[1]);

  int16_t result = RAIL_GetChannelHoppingRssi(railHandle, channelIndex);

  char bufRssi[10];

  // The lowest negative value is used to indicate an error reading the RSSI
  if (result == RAIL_RSSI_INVALID) {
    responsePrintError(argv[0], 0x08, "Could not read RSSI. Ensure channel hopping was configured and enabled.");
    return;
  }

  sprintfFloat(bufRssi, sizeof(bufRssi), ((float) result / 4), 2);

  responsePrint(argv[0], "rssi:%s", bufRssi);
}

void configRxDutyCycle(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  RAIL_RxDutyCycleConfig_t config = {
    .mode = ciGetUnsigned(argv[1]),
    .parameter = ciGetUnsigned(argv[2]),
    .delay = ciGetUnsigned(argv[3]),
    .delayMode = RAIL_RX_CHANNEL_HOPPING_DELAY_MODE_STATIC
  };

  RAIL_Status_t status = RAIL_ConfigRxDutyCycle(railHandle, &config);

  responsePrint(argv[0], "Success:%s,Mode:%d,Parameter:%d,Delay:%d",
                status == RAIL_STATUS_NO_ERROR ? "True" : "False",
                config.mode,
                config.parameter,
                config.delay);
}

void enableRxDutyCycle(int argc, char **argv)
{
  CHECK_RAIL_HANDLE(argv[0]);
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }
  bool enable = !!ciGetUnsigned(argv[1]);

  RAIL_Status_t status = RAIL_EnableRxDutyCycle(railHandle, enable);
  responsePrint(argv[0], "Success:%s", status == RAIL_STATUS_NO_ERROR ? "True" : "False");
}

RAIL_ChannelMetadata_t channelMetadata[MAX_NUMBER_CHANNELS];
#define TIME_PER_CHANNEL (10000UL)
void spectrumAnalyzer(int argc, char **argv)
{
  if (!inRadioState(RAIL_RF_STATE_IDLE, argv[0])) {
    return;
  }

  uint16_t channelMetadataLength = MAX_NUMBER_CHANNELS;

  uint16_t minChannel = 0U;
  if (argc > 2) {
    minChannel = ciGetUnsigned(argv[2]);
  }

  uint16_t maxChannel = UINT16_MAX;
  if (argc > 3) {
    maxChannel = ciGetUnsigned(argv[3]);
  }

  RAIL_Status_t status = RAIL_GetChannelMetadata(railHandle,
                                                 channelMetadata,
                                                 &channelMetadataLength,
                                                 minChannel,
                                                 maxChannel);

  if (channelMetadataLength == 0) {
    responsePrintError(argv[0], 0x1, "No channels in range found");
    return;
  }
  bool graphics = false;
  if (argc > 1) {
    graphics = !!ciGetUnsigned(argv[1]);
  }

  if (status == RAIL_STATUS_INVALID_STATE) {
    responsePrintError(argv[0], 0x20, "Error in RAIL_GetChannelMetadata, channel config invalid.");
    return;
  }

  uint8_t length = MAX_NUMBER_CHANNELS < channelMetadataLength
                   ? MAX_NUMBER_CHANNELS : channelMetadataLength;
  for (uint16_t i = 0; i < length; i++) {
    channelHoppingEntries[i].channel = channelMetadata[i].channel;
    channelHoppingEntries[i].mode = RAIL_RX_CHANNEL_HOPPING_MODE_TIMEOUT;
    channelHoppingEntries[i].parameter = TIME_PER_CHANNEL;
    channelHoppingEntries[i].delay = 0;
    channelHoppingEntries[i].delayMode = RAIL_RX_CHANNEL_HOPPING_DELAY_MODE_STATIC;
  }
  channelHoppingConfig.numberOfChannels = channelMetadataLength;
  channelHoppingConfig.buffer = channelHoppingBuffer;

  RAIL_ConfigRxChannelHopping(railHandle, &channelHoppingConfig);
  RAIL_EnableRxChannelHopping(railHandle, true, true);
  RAIL_StartRx(railHandle, channelMetadata[0].channel, NULL);

  // Make sure we get into receive and then have enough time to
  // cycle through all the channels (time per channel * (num(channels) + safety buffer))
  while (RAIL_GetRadioState(railHandle) != RAIL_RF_STATE_RX) ;
  RAIL_DelayUs(TIME_PER_CHANNEL * (channelMetadataLength + 5));

  responsePrintHeader(argv[0], "channelIndex:%u,channel:%u,frequency:%u,rssi:%s");
  int16_t min = INT16_MAX;
  int16_t max = INT16_MIN;
  int16_t result[MAX_NUMBER_CHANNELS];
  for (uint16_t i = 0; i < channelMetadataLength; i++) {
    result[i] = RAIL_GetChannelHoppingRssi(railHandle, i);
    if (result[i] > max) {
      max = result[i];
    }
    if (result[i] < min) {
      min = result[i];
    }
    if (result[i] == RAIL_RSSI_INVALID) {
      continue;
    }
    char bufRssi[10];
    sprintfFloat(bufRssi, sizeof(bufRssi), ((float) result[i] / 4), 2);
    responsePrintMulti("channelIndex:%u,channel:%u,frequency:%u,rssi:%s",
                       i, channelMetadata[i].channel,
                       channelMetadata[i].frequency, bufRssi);
  }

  RAIL_Idle(railHandle, RAIL_IDLE_FORCE_SHUTDOWN_CLEAR_FLAGS, true);

  if (!graphics) {
    return;
  }

  printf("\n");
  printf("+----------------------------+\n");
  printf("| RSSI dBm by Channel Number |\n");
  printf("+----------------------------+\n");
  char bufRssi[10];
  for (uint8_t i = 0; i <= 20; i++) {
    for (uint8_t j = 0; j < channelMetadataLength; j++) {
      if (i != 20) {
        for (uint8_t k = 0; k < 4; k++) {
          if (result[j] >= (max - (((max - min) / 20) * i))) {
            printf("#");
          } else {
            printf(".");
          }
        }
      } else {
        printf("%-4d", channelMetadata[j].channel);
      }
    }
    sprintfFloat(bufRssi, sizeof(bufRssi), ((float) (max - (((max - min) / 20) * i)) / 4), 2);
    printf(" %s dBm\n", bufRssi);
  }
  printf("Channel Number\n");
}

#else

static void channelHoppingNotSupported(char **argv)
{
  responsePrintError(argv[0], 0x17, "Channel hopping not suppported on this chip");
}

void configRxChannelHopping(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void enableRxChannelHopping(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void getChannelHoppingRssi(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void configRxDutyCycle(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void enableRxDutyCycle(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void spectrumAnalyzer(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

void configChannelHoppingOptions(int argc, char **argv)
{
  channelHoppingNotSupported(argv);
}

#endif
