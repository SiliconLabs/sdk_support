/***************************************************************************//**
 * @file
 * @brief Header file for RAIL antenna functionality
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

#ifndef __RAILAPP_ANTENNA_H__
#define __RAILAPP_ANTENNA_H__

#include "rail_chip_specific.h"

void RAILAPP_SetRfPath(RAIL_AntennaSel_t rfPath);

#ifdef CLI_INTERFACE
#ifdef _SILICON_LABS_32B_SERIES_2
#define ANTENNA_CI_COMMANDS                                                  \
  RAILCMD_SEPARATOR("Antenna Commands")                                      \
  RAILCMD_ENTRY("setRfPath", "w", CI_SetRfPath, "[rfPath] 0=Path0, 1=Path1") \
  RAILCMD_SEPARATOR("End of Antenna Commands") // Please keep this line below last RAILCMD_ENTRY
#else
#define ANTENNA_CI_COMMANDS /* none */
#endif

// Prototypes of CLI functions
#define RAILCMD_ENTRY(command, args, callback, helpStr) \
  extern void callback(int argc, char **argv);
#define RAILCMD_SEPARATOR(string) /* no-op */
ANTENNA_CI_COMMANDS
#undef  RAILCMD_ENTRY
#undef  RAILCMD_SEPARATOR
#endif

#ifdef _SILICON_LABS_32B_SERIES_2
void RAILAPP_SetRfPath(RAIL_AntennaSel_t rfPath);
#endif //_SILICON_LABS_32B_SERIES_2

#endif
