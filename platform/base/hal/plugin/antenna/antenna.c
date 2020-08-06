/***************************************************************************//**
 * @file
 * @brief HAL functions to control antenna mode
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
#include "stack/include/ember.h"
#include "include/error.h"

#include "hal/hal.h" // includes antenna.h

#ifdef DEBUG_ANT_DIV

extern uint32_t debugAntennaSelectGpio;
extern uint32_t debugAntennaNSelectGpio;
extern bool debugAntennaSelectEnabled;
extern bool debugAntennaNSelectEnabled;
extern uint8_t debugAntennaSelectLoc;
extern uint8_t debugAntennaNSelectLoc;

#undef  ANTENNA_SELECT_GPIO
#define ANTENNA_SELECT_GPIO  debugAntennaSelectGpio
#define ANTENNA_SELECT_LOC   debugAntennaSelectLoc

#undef  ANTENNA_nSELECT_GPIO
#define ANTENNA_nSELECT_GPIO debugAntennaNSelectGpio
#define ANTENNA_nSELECT_LOC  debugAntennaNSelectLoc

#define ANTENNA_SELECT_ENABLED  debugAntennaSelectEnabled
#define ANTENNA_nSELECT_ENABLED debugAntennaNSelectEnabled

#undef  HAL_ANTDIV_ENABLE
#define HAL_ANTDIV_ENABLE 1 // Force this flag on for rest of module

#else  //!DEBUG_ANT_DIV

#define RX_ANTENNA_SUPPORT (HAL_ANTDIV_RX_RUNTIME_PHY_SELECT \
                            || (ANTENNA_RX_DEFAULT_MODE != HAL_ANTENNA_MODE_DISABLED))

// Flag any mis-configuration
#if     ANTENNA_USE_RAIL_SCHEME
  #if     (defined(ANTENNA_SELECT_GPIO) && !defined(BSP_ANTDIV_SEL_LOC))
    #error "Antenna Diversity needs BSP_ANTDIV_SEL_LOC specified"
  #endif//(defined(ANTENNA_SELECT_GPIO) && !defined(BSP_ANTDIV_SEL_LOC))
  #if     (defined(ANTENNA_nSELECT_GPIO) && !defined(BSP_ANTDIV_NSEL_LOC))
    #error "Antenna Diversity needs BSP_ANTDIV_NSEL_LOC specified"
  #endif//(defined(ANTENNA_nSELECT_GPIO) && !defined(BSP_ANTDIV_NSEL_LOC))
#else//!ANTENNA_USE_RAIL_SCHEME
  #if RX_ANTENNA_SUPPORT
    #if (PHY_RAIL || PHY_DUALRAIL) && !defined(_SILICON_LABS_32B_SERIES_1_CONFIG_1)
      #error "Rx Antenna Diversity requires BSP_ANTDIV_[N]SEL_PORT/PIN/LOC to be defined."
    #else
      #error "Rx Antenna Diversity is not supported on this platform or PHY."
    #endif
  #endif//RX_ANTENNA_SUPPORT
#endif//ANTENNA_USE_RAIL_SCHEME

#define ANTENNA_SELECT_ENABLED  true
#define ANTENNA_SELECT_LOC      BSP_ANTDIV_SEL_LOC
#define ANTENNA_nSELECT_ENABLED true
#define ANTENNA_nSELECT_LOC     BSP_ANTDIV_NSEL_LOC

#endif //DEBUG_ANT_DIV

#if     (PHY_RAIL || PHY_DUALRAIL)

// RAIL Antenna Configuration

#include "rail.h"

EmberStatus halInitAntenna(void)
{
 #if     (HAL_ANTDIV_ENABLE || defined(_SILICON_LABS_32B_SERIES_2))
  // Tell RAIL to configure the antenna GPIOs
  RAIL_AntennaConfig_t antennaConfig = { false, }; // Zero out structure
 #ifdef  ANTENNA_SELECT_GPIO
  if (ANTENNA_SELECT_ENABLED) {
    antennaConfig.ant0PinEn = true;
    antennaConfig.ant0Port = (uint8_t)GPIO_PORT(ANTENNA_SELECT_GPIO);
    antennaConfig.ant0Pin = GPIO_PIN(ANTENNA_SELECT_GPIO);
    antennaConfig.ant0Loc = ANTENNA_SELECT_LOC;
  }
 #endif//ANTENNA_SELECT_GPIO
 #ifdef  _SILICON_LABS_32B_SERIES_2
  antennaConfig.defaultPath = ANTENNA_SELECT_LOC;
 #endif//_SILICON_LABS_32B_SERIES_2
 #ifdef  ANTENNA_nSELECT_GPIO
  if (ANTENNA_nSELECT_ENABLED) {
    antennaConfig.ant1PinEn = true;
    antennaConfig.ant1Port = (uint8_t)GPIO_PORT(ANTENNA_nSELECT_GPIO);
    antennaConfig.ant1Pin = GPIO_PIN(ANTENNA_nSELECT_GPIO);
    antennaConfig.ant1Loc = ANTENNA_nSELECT_LOC;
  }
 #endif//ANTENNA_nSELECT_GPIO
  if (RAIL_ConfigAntenna(RAIL_EFR32_HANDLE, &antennaConfig)
      != RAIL_STATUS_NO_ERROR) {
    return EMBER_ERR_FATAL;
  }
  return halSetAntennaMode(ANTENNA_TX_DEFAULT_MODE);
 #else//!(HAL_ANTDIV_ENABLE || defined(_SILICON_LABS_32B_SERIES_2))
  return EMBER_SUCCESS;
 #endif//(HAL_ANTDIV_ENABLE || defined(_SILICON_LABS_32B_SERIES_2))
}

#else//!(PHY_RAIL || PHY_DUALRAIL)

// Non-RAIL HAL-Config Antenna Configuration

#ifdef  CORTEXM3_EMBER_MICRO
#define ANTENNA_SELECT_GPIO_CFG GPIOCFG_OUT
#else//!CORTEXM3_EMBER_MICRO
#define ANTENNA_SELECT_GPIO_CFG gpioModePushPull
#endif//CORTEXM3_EMBER_MICRO

EmberStatus halInitAntenna(void)
{
  // Configure GPIOs to initally select Antenna 1
  // On em3xx, this might override board header configuration.
 #ifdef ANTENNA_SELECT_GPIO
  halGpioSet(ANTENNA_SELECT_GPIO);
  halGpioSetConfig(ANTENNA_SELECT_GPIO, ANTENNA_SELECT_GPIO_CFG);
 #endif
 #ifdef ANTENNA_nSELECT_GPIO
  halGpioClear(ANTENNA_nSELECT_GPIO);
  halGpioSetConfig(ANTENNA_nSELECT_GPIO, ANTENNA_SELECT_GPIO_CFG);
 #endif
  // Update 'em to select desired antenna based on default mode
  return halSetAntennaMode(ANTENNA_TX_DEFAULT_MODE);
}

#endif//(PHY_RAIL || PHY_DUALRAIL)

#if     (defined(ANTENNA_SELECT_GPIO) || defined(ANTENNA_nSELECT_GPIO))

static HalAntennaMode txAntennaMode = ANTENNA_TX_DEFAULT_MODE;
// Default to first antenna
static HalAntennaSelection txAntennaSelection = HAL_ANTENNA_SELECT_ANTENNA1;
static HalAntennaMode rxAntennaMode = ANTENNA_RX_DEFAULT_MODE;

// Rx Antenna Diversity
extern EmberStatus emRadioConfigRxAntenna(HalAntennaMode mode);

HalAntennaMode halGetAntennaRxMode(void)
{
  return rxAntennaMode;
}

EmberStatus halSetAntennaRxMode(HalAntennaMode mode)
{
 #if RX_ANTENNA_SUPPORT
  // Tell RAIL what Rx antenna mode to use, if we can
  EmberStatus status = emRadioConfigRxAntenna(mode);
  if (status == EMBER_SUCCESS) {
    rxAntennaMode = mode;
  }
  return status;
 #else//!RX_ANTENNA_SUPPORT
  return ((mode == HAL_ANTENNA_MODE_DISABLED) ? EMBER_SUCCESS : EMBER_BAD_ARGUMENT);
 #endif//RX_ANTENNA_SUPPORT
}

// Tx Antenna Diversity

static void selectTxAntenna(HalAntennaSelection txAntenna)
{
  txAntennaSelection = txAntenna;
 #if     ANTENNA_USE_RAIL_SCHEME
  // PHY does selection when a transmit is begun
 #else//!ANTENNA_USE_RAIL_SCHEME
  if (txAntenna == HAL_ANTENNA_SELECT_ANTENNA1) {
   #ifdef  ANTENNA_nSELECT_GPIO
    if (ANTENNA_nSELECT_ENABLED) {
      halGpioClear(ANTENNA_nSELECT_GPIO);
    }
   #endif//ANTENNA_nSELECT_GPIO
   #ifdef  ANTENNA_SELECT_GPIO
    if (ANTENNA_SELECT_ENABLED) {
      halGpioSet(ANTENNA_SELECT_GPIO);
    }
   #endif//ANTENNA_SELECT_GPIO
  } else { // (txAntenna == HAL_ANTENNA_SELECT_ANTENNA2)
   #ifdef  ANTENNA_SELECT_GPIO
    if (ANTENNA_SELECT_ENABLED) {
      halGpioClear(ANTENNA_SELECT_GPIO);
    }
   #endif//ANTENNA_SELECT_GPIO
   #ifdef  ANTENNA_nSELECT_GPIO
    if (ANTENNA_nSELECT_ENABLED) {
      halGpioSet(ANTENNA_nSELECT_GPIO);
    }
   #endif//ANTENNA_nSELECT_GPIO
  }
 #endif//ANTENNA_USE_RAIL_SCHEME
}

HalAntennaSelection halGetAntennaSelected(void)
{
  return txAntennaSelection;
}

HalAntennaMode halGetAntennaMode(void)
{
  return txAntennaMode;
}

EmberStatus halSetAntennaMode(HalAntennaMode mode)
{
  EmberStatus status = EMBER_SUCCESS;

  switch (mode) {
    case HAL_ANTENNA_MODE_DISABLED: // Leave antenna untouched (e.g. from Rx)
      break;
    case HAL_ANTENNA_MODE_ENABLE1:
      selectTxAntenna(HAL_ANTENNA_SELECT_ANTENNA1);
      break;
    case HAL_ANTENNA_MODE_ENABLE2:
      selectTxAntenna(HAL_ANTENNA_SELECT_ANTENNA2);
      break;
    case HAL_ANTENNA_MODE_DIVERSITY: // Ensure current selection is effected
      selectTxAntenna(txAntennaSelection);
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
      break;
  }

  if (status == EMBER_SUCCESS) {
    txAntennaMode = mode;
  }

  return status;
}

EmberStatus halToggleAntenna(void)
{
  if (txAntennaMode == HAL_ANTENNA_MODE_DIVERSITY) {
    selectTxAntenna(txAntennaSelection ^ 1);
    return EMBER_SUCCESS;
  }
  return EMBER_ERR_FATAL;
}

EmberStatus halSetAntenna(HalAntennaSelection txAntenna)
{
  if (txAntenna == txAntennaSelection) { // Already selected!
    return EMBER_SUCCESS;
  }
  return halToggleAntenna();
}

#else//!(defined(ANTENNA_SELECT_GPIO) || defined(ANTENNA_nSELECT_GPIO))

#ifndef JAMBUILD
#warning "Define either ANTENNA_SELECT_GPIO or ANTENNA_nSELECT_GPIO to enable antenna diversity"
#endif//JAMBUILD

// Stubs in case someone insists on referencing them

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

#endif//(defined(ANTENNA_SELECT_GPIO) || defined(ANTENNA_nSELECT_GPIO))
