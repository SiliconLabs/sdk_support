/***************************************************************************//**
 * @file
 * @brief Antenna mode control functions.
 * See @ref micro for documentation.
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
/** @addtogroup micro
 * See also hal/plugin/antenna/antenna.c for source code.
 *@{
 */

#ifndef __ANTENNA_H__
#define __ANTENNA_H__

/** @brief Antenna modes
 */
typedef int8_t HalAntennaMode;
#define HAL_ANTENNA_MODE_DISABLED  0 /**< Don't alter antenna selection */
#define HAL_ANTENNA_MODE_ENABLE1   1 /**< Use antenna 1 */
#define HAL_ANTENNA_MODE_ENABLE2   2 /**< Use antenna 2 */
#define HAL_ANTENNA_MODE_DIVERSITY 3 /**< Choose antenna 1 or 2 dynamically */

/** @name Antenna Selection
 *
 * Define the antenna select pins ANTENNA_SELECT_GPIO and ANTENNA_nSELECT_GPIO
 * ANTENNA_SELECT_GPIO - low,  ANTENNA_nSELECT_GPIO - low:  undefined
 * ANTENNA_SELECT_GPIO - low,  ANTENNA_nSELECT_GPIO - high: select antenna 2
 * ANTENNA_SELECT_GPIO - high, ANTENNA_nSELECT_GPIO - low:  select antenna 1
 * ANTENNA_SELECT_GPIO - high, ANTENNA_nSELECT_GPIO - high: undefined
 *
 * @note The antenna selection can normally be configured at runtime
 * via halSetAntennaMode(); when using \ref HAL_ANTENNA_MODE_DIVERSITY
 * it can be changed via halSetAntenna() or halToggleAntenna().
 */
//@{
typedef int8_t HalAntennaSelection;
#define HAL_ANTENNA_SELECT_ANTENNA1 1 /**< Select antenna 1 */
#define HAL_ANTENNA_SELECT_ANTENNA2 2 /**< Select antenna 2 */

// The existence of Antenna GPIO location information on EFR32XG1 series
// parts enables use of the more flexible RAIL scheme va. legacy GPIO scheme
// for Tx-only diversity. However, the EFR32XG2 series doesn't use locations
// so the HAL configurator doesn't provide any. But EFR32XG2 does have RfPath
// selection, and BSP_ANTDIV_SEL_LOC is used for that.
// On EFR32XG1 series, default location(s) to -1 to select legacy GPIO scheme.
// On EFR32XG2 series, default location(s) to 1 to select RAIL scheme RfPath 1;
// to force use of legacy GPIO scheme (because their GPIO choice for Tx-only
// diversity isn't supported by the radio), user must define each respective
// BSP_ANTDIV_[N]SEL_LOC as -1 in their HAL config include.
#ifdef  _SILICON_LABS_32B_SERIES_2
  #define ANTENNA_UNSPECIFIED_LOC  1 // Location to use RAIL scheme on RfPath 1
#else//!_SILICON_LABS_32B_SERIES_2
  #define ANTENNA_UNSPECIFIED_LOC -1 // Dummy location to select legacy GPIO scheme
#endif//_SILICON_LABS_32B_SERIES_2
#ifndef BSP_ANTDIV_SEL_LOC
  #define BSP_ANTDIV_SEL_LOC ANTENNA_UNSPECIFIED_LOC
#endif
#ifndef BSP_ANTDIV_NSEL_LOC
  #define BSP_ANTDIV_NSEL_LOC ANTENNA_UNSPECIFIED_LOC
#endif

#if    HAL_ANTDIV_ENABLE // EFR32 HAL Config way

// Establish Tx default mode
#ifdef  HAL_ANTDIV_TX_MODE
  #define ANTENNA_TX_DEFAULT_MODE HAL_ANTDIV_TX_MODE
#else//!HAL_ANTDIV_TX_MODE
  #define ANTENNA_TX_DEFAULT_MODE HAL_ANTENNA_MODE_DIVERSITY
#endif//HAL_ANTDIV_TX_MODE

// Establish Rx default mode
#ifdef  HAL_ANTDIV_RX_MODE
  #define ANTENNA_RX_DEFAULT_MODE HAL_ANTDIV_RX_MODE
#else//!HAL_ANTDIV_RX_MODE
  #define ANTENNA_RX_DEFAULT_MODE HAL_ANTENNA_MODE_DISABLED
#endif//HAL_ANTDIV_RX_MODE

// Determine scheme to use based on platform, PHY, debug, and GPIO location(s):
#if ((PHY_RAIL || PHY_DUALRAIL)                                       \
  && !defined(_SILICON_LABS_32B_SERIES_1_CONFIG_1)                    \
  && (defined(DEBUG_ANT_DIV)                                          \
  || ((defined(BSP_ANTDIV_SEL_PORT) || defined(BSP_ANTDIV_NSEL_PORT)) \
  && (!defined(BSP_ANTDIV_SEL_PORT) || (BSP_ANTDIV_SEL_LOC >= 0))     \
  && (!defined(BSP_ANTDIV_NSEL_PORT) || (BSP_ANTDIV_NSEL_LOC >= 0)))))
  #define ANTENNA_USE_RAIL_SCHEME 1
#else
  #define ANTENNA_USE_RAIL_SCHEME 0
#endif

// Check antenna selection GPIO configuration
#ifndef GPIO_PIN_DEF
// Define GPIO macros based on external port and pin macros
#define GPIO_PIN_DEF__(port, pin) ((port << 4) | pin)
#define GPIO_PIN_DEF_(port, pin) GPIO_PIN_DEF__(port, pin)
#define GPIO_PIN_DEF(gpio) GPIO_PIN_DEF_(gpio ## _PORT, gpio ## _PIN)
#endif //GPIO_PIN_DEF

#ifdef BSP_ANTDIV_SEL_PORT
  #define ANTENNA_SELECT_GPIO \
  GPIO_PIN_DEF__(BSP_ANTDIV_SEL_PORT, BSP_ANTDIV_SEL_PIN)
#endif
#ifdef BSP_ANTDIV_NSEL_PORT
  #define ANTENNA_nSELECT_GPIO \
  GPIO_PIN_DEF__(BSP_ANTDIV_NSEL_PORT, BSP_ANTDIV_NSEL_PIN)
#endif

/**
 * @brief GPIO used to control antenna select(low for antenna 1, high for antenna 2).
 */
#if defined(ANTENNA_SELECT_GPIO_PORT) && defined(ANTENNA_SELECT_GPIO_PIN) && !defined(ANTENNA_SELECT_GPIO)
  #define ANTENNA_SELECT_GPIO GPIO_PIN_DEF(ANTENNA_SELECT_GPIO)
#endif //(defined(ANTENNA_SELECT_GPIO_PORT) && defined(ANTENNA_SELECT_GPIO_PIN))

/**
 * @brief GPIO used to control inverted antenna select(high for antenna 1, low for antenna 2).
 */
#if defined(ANTENNA_nSELECT_GPIO_PORT) && defined(ANTENNA_nSELECT_GPIO_PIN) && !defined(ANTENNA_nSELECT_GPIO)
  #define ANTENNA_nSELECT_GPIO GPIO_PIN_DEF(ANTENNA_nSELECT_GPIO)
#endif

#else//!HAL_ANTDIV_ENABLE // em3xx way

// Neither the RAIL scheme nor Rx diversity are supported
#define ANTENNA_USE_RAIL_SCHEME 0 // Tx-only Only GPIO scheme supported
#define ANTENNA_RX_DEFAULT_MODE HAL_ANTENNA_MODE_DISABLED
#ifdef  ANTENNA_DIVERSITY_DEFAULT_ENABLED
  #define ANTENNA_TX_DEFAULT_MODE HAL_ANTENNA_MODE_DIVERSITY
#else//!ANTENNA_DIVERSITY_DEFAULT_ENABLED
  #define ANTENNA_TX_DEFAULT_MODE HAL_ANTENNA_MODE_ENABLE1
#endif//ANTENNA_DIVERSITY_DEFAULT_ENABLED

// Antenna GPIO configuration is specified by the board header

#endif//HAL_ANTDIV_ENABLE

//@} //END OF ANTENNA SELECTION

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifndef __EMBERSTATUS_TYPE__
#define __EMBERSTATUS_TYPE__
//This is necessary here because halSetAntennaMode returns an
//EmberStatus and not adding this typedef to this file breaks a
//whole lot of builds due to include mis-ordering
typedef uint8_t EmberStatus;
#endif //__EMBERSTATUS_TYPE__
#endif // DOXYGEN_SHOULD_SKIP_THIS

/** @brief Initialize antenna GPIOs
 *
 * @return EMBER_SUCCESS if antenna GPIOs are configured successfully
 * and the default Tx antenna mode is established, or an error otherwise.
 */
EmberStatus halInitAntenna(void);

/** @brief Sets the Tx antenna mode.
 *
 * @param mode The antenna mode to use for transmit.
 * @return EMBER_SUCCESS if Tx antenna mode is configured as desired
 * or EMBER_BAD_ARGUMENT if Tx antenna mode is unsupported.
 */
EmberStatus halSetAntennaMode(HalAntennaMode mode);

/** @brief Returns the current Tx antenna mode.
 *
 * @return The current Tx antenna mode.
 */
HalAntennaMode halGetAntennaMode(void);

/** @brief Returns the current Tx antenna selected.
 *
 * @return The current Tx antenna selected.
 */
HalAntennaSelection halGetAntennaSelected(void);

/** @brief Toggles the enabled Tx antenna.
 *
 * @return EMBER_SUCCESS if Tx antenna was toggled, EMBER_ERR_FATAL otherwise
 */
EmberStatus halToggleAntenna(void);

/** @brief Sets the enabled Tx antenna.
 *
 * @param txAntenna The antenna to use for transmit.
 * @return EMBER_SUCCESS if Tx antenna was set, EMBER_ERR_FATAL otherwise
 */
EmberStatus halSetAntenna(HalAntennaSelection txAntenna);

/** @brief Sets the Rx antenna mode.
 *
 * @param mode The antenna mode to use for receive.
 * @return EMBER_SUCCESS if Rx antenna mode is configured as desired
 * or EMBER_BAD_ARGUMENT if Rx antenna mode is unsupported.
 */
EmberStatus halSetAntennaRxMode(HalAntennaMode mode);

/** @brief Returns the current Rx antenna mode.
 *
 * @return The current Rx antenna mode.
 */
HalAntennaMode halGetAntennaRxMode(void);

#endif //__ANTENNA_H__

/**@} END micro group
 */
