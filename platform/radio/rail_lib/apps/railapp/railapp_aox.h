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

#ifndef __RAILAPP_AOX_H__
#define __RAILAPP_AOX_H__

#include "em_device.h"
#include "rail_features.h"

#if RAIL_FEAT_BLE_AOX_SUPPORTED

#ifdef CLI_INTERFACE
#define AOX_CI_COMMANDS                                                                                                                                                                                                                   \
  RAILCMD_SEPARATOR("BLE AoX Mode (Internal Use Only)")                                                                                                                                                                                   \
  RAILCMD_ENTRY("configAox", "vu*", CI_configAox, "[options (port, pin)] BLE specific feature,antenna port and pin set. Every port must have a pin. RAIL lib takes a maximum of 6 sets of ports and pins. See rail_types.h for options.") \
  RAILCMD_ENTRY("getRawCteSamples", "", CI_getRawCteSamples, "Retrieve raw CTE RX samples.")                                                                                                                                              \
  RAILCMD_ENTRY("getCteSampleRate", "", CI_getCteSampleRate, "Get the sample rate used to capture the CTE samples.")                                                                                                                      \
  RAILCMD_ENTRY("setCteBufferLock", "u", CI_setCteBufferLock, "[enable] Enable (1) or Disable (0) the CTE Buffer lock.")                                                                                                                  \
  RAILCMD_ENTRY("getCteBufferLock", "", CI_getCteBufferLock, "Get the current status of the CTE Buffer lock.")                                                                                                                            \
  RAILCMD_ENTRY("enableRxAutoCteBufferUnlock", "u", CI_enableRxAutoCteBufferUnlock, "Unlock the CTE buffer whenever a packet is received.")                                                                                               \
  RAILCMD_ENTRY("setCteCalibration", "uv", CI_setCteCalibration, "Set the CTE calibration[index] to [value].")                                                                                                                            \
  RAILCMD_ENTRY("getCteCalibration", "", CI_getCteCalibration, "Get current CTE calibrations.")                                                                                                                                           \
  RAILCMD_SEPARATOR("End of BLE AoX Mode (Internal Use Only)") // Please keep this line below last RAILCMD_ENTRY
#endif // CLI_INTERFACE

bool RAILAPP_SetCteBufferLock(bool lock);
#endif // RAIL_FEAT_BLE_AOX_SUPPORTED
#endif //__RAILAPP_AOX_H__0
