/***************************************************************************//**
 * @file
 * @brief Source file for RAIL antenna functionality
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

#include "command_interpreter.h"
#include "response_print.h"

#include "rail.h"
#include "rail_types.h"
#include "rail_chip_specific.h"

extern RAIL_Handle_t railHandle;
extern RAIL_AntennaConfig_t halAntennaConfig;

/***************************************************************************//**
 * @brief
 *   Select the RF Path to use for TX and RX.
 *
 * @details
 *   Provide access to set system function, where its source file changes for
 *   for each platform. Allows use with existing RPC config for all platforms.
 *
 * @param rfPath Sets the default antenna path.
 *
 ******************************************************************************/
void RAILAPP_SetRfPath(RAIL_AntennaSel_t rfPath)
{
 #ifdef  _SILICON_LABS_32B_SERIES_2
  halAntennaConfig.defaultPath = rfPath;
  RAIL_ConfigAntenna(railHandle, &halAntennaConfig);
 #else//!_SILICON_LABS_32B_SERIES_2
  (void) rfPath;
 #endif//_SILICON_LABS_32B_SERIES_2
}

#ifdef CLI_INTERFACE
void CI_SetRfPath(int argc, char **argv)
{
  uint32_t rfPath = ciGetUnsigned(argv[1]);
  RAILAPP_SetRfPath(rfPath);
  responsePrint(argv[0], "RfPath:%d", rfPath);
}
#endif
