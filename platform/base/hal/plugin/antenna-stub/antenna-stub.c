/***************************************************************************//**
 * @file
 * @brief stub implementation of antenna control HAL
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
#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "hal/hal.h" // includes antenna.h

#ifdef EMBER_STACK_CONNECT
#include "stack/include/error.h"
#endif

// Stubs in case someone insists on referencing them

#if     (PHY_RAIL || PHY_DUALRAIL)

// RAIL Antenna Configuration

#include "rail.h"

EmberStatus halInitAntenna(void)
{
 #ifdef  _SILICON_LABS_32B_SERIES_2
  // On EFR32XG2 tell RAIL to configure the RfPath
  RAIL_AntennaConfig_t antennaConfig = { false, }; // Zero out structure
  antennaConfig.defaultPath = BSP_ANTDIV_SEL_LOC;
  if (RAIL_ConfigAntenna(RAIL_EFR32_HANDLE, &antennaConfig)
      != RAIL_STATUS_NO_ERROR) {
    return EMBER_ERR_FATAL;
  }
 #endif//_SILICON_LABS_32B_SERIES_2
  return EMBER_SUCCESS;
}

#else//!(PHY_RAIL || PHY_DUALRAIL)

// Non-RAIL HAL-Config Antenna Configuration

EmberStatus halInitAntenna(void)
{
  return EMBER_SUCCESS;
}

#endif//(PHY_RAIL || PHY_DUALRAIL)

HalAntennaMode halGetAntennaRxMode(void)
{
  return HAL_ANTENNA_MODE_DISABLED;
}

EmberStatus halSetAntennaRxMode(HalAntennaMode mode)
{
  return ((mode == HAL_ANTENNA_MODE_DISABLED) ? EMBER_SUCCESS : EMBER_BAD_ARGUMENT);
}

HalAntennaSelection halGetAntennaSelected(void)
{
  return HAL_ANTENNA_SELECT_ANTENNA1;
}

HalAntennaMode halGetAntennaMode(void)
{
  return HAL_ANTENNA_MODE_ENABLE1;
}

EmberStatus halSetAntennaMode(HalAntennaMode mode)
{
  return ((mode == HAL_ANTENNA_MODE_ENABLE1) ? EMBER_SUCCESS : EMBER_BAD_ARGUMENT);
}

EmberStatus halToggleAntenna(void)
{
  return EMBER_ERR_FATAL;
}

EmberStatus halSetAntenna(HalAntennaSelection txAntenna)
{
  return ((txAntenna == HAL_ANTENNA_SELECT_ANTENNA1)
          ? EMBER_SUCCESS : EMBER_ERR_FATAL);
}
