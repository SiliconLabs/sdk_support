/***************************************************************************//**
 * @file
 * @brief This file implements the LBT commands for RAIL test applications.
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
#include "app_common.h"

RailTxType_t txType = TX_TYPE_NORMAL;
RAIL_LbtConfig_t *lbtConfig = NULL;
RAIL_CsmaConfig_t *csmaConfig = NULL;

static RAIL_LbtConfig_t lbtParams = RAIL_CSMA_CONFIG_802_15_4_2003_2p4_GHz_OQPSK_CSMA;

void setLbtMode(int argc, char **argv)
{
  if (argc > 1) {
    if (memcmp(argv[1], "off", 3) == 0) {
      txType = TX_TYPE_NORMAL;
    } else if (memcmp(argv[1], "csma", 4) == 0) {
      txType = TX_TYPE_CSMA;
      csmaConfig = (RAIL_CsmaConfig_t*)&lbtParams;
    } else if (memcmp(argv[1], "lbt", 3) == 0) {
      txType = TX_TYPE_LBT;
      lbtConfig = &lbtParams; // Used for CSMA and LBT
    } else {
      responsePrintError(argv[0], 0x70, "Unknown LBT mode specified.");
      return;
    }
  }
  if (txType == TX_TYPE_NORMAL) {
    responsePrint(argv[0], "LbtMode:off");
  } else if (txType == TX_TYPE_CSMA) {
    responsePrint(argv[0], "LbtMode:CSMA");
  } else if (txType == TX_TYPE_LBT) {
    responsePrint(argv[0], "LbtMode:LBT");
  }
}

void getLbtParams(int argc, char **argv)
{
  responsePrint(argv[0],
                "MinBo:%u,"
                "MaxBo:%u,"
                "Tries:%u,"
                "Threshold:%d,"
                "Backoff:%u,"
                "Duration:%u,"
                "Timeout:%u",
                lbtParams.lbtMinBoRand,
                lbtParams.lbtMaxBoRand,
                lbtParams.lbtTries,
                lbtParams.lbtThreshold,
                lbtParams.lbtBackoff,
                lbtParams.lbtDuration,
                lbtParams.lbtTimeout);
}

void setLbtParams(int argc, char **argv)
{
  lbtParams.lbtMinBoRand = ciGetUnsigned(argv[1]);
  lbtParams.lbtMaxBoRand = ciGetUnsigned(argv[2]);
  lbtParams.lbtTries     = ciGetUnsigned(argv[3]);
  lbtParams.lbtThreshold = ciGetSigned(argv[4]);
  lbtParams.lbtBackoff   = ciGetUnsigned(argv[5]);
  lbtParams.lbtDuration  = ciGetUnsigned(argv[6]);
  lbtParams.lbtTimeout   = ciGetUnsigned(argv[7]);

  getLbtParams(1, argv);
}
