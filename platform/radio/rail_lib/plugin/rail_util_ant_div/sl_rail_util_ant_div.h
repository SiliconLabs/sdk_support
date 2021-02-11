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
 * See also plugin/sl_rail_util_ant_div/sl_rail_util_ant_div.c for source code.
 *@{
 */

#ifndef __SL_RAIL_UTIL_ANT_DIV_H__
#define __SL_RAIL_UTIL_ANT_DIV_H__

#include "rail.h"
#include "sl_status.h"
#include "sl_rail_util_ant_div_config.h"

/** @brief Antenna modes
 */
typedef int8_t sl_rail_util_antenna_mode_t;
#define SL_RAIL_UTIL_ANTENNA_MODE_DISABLED  0 /**< Don't alter antenna selection */
#define SL_RAIL_UTIL_ANTENNA_MODE_ENABLE1   1 /**< Use antenna 1 */
#define SL_RAIL_UTIL_ANTENNA_MODE_ENABLE2   2 /**< Use antenna 2 */
#define SL_RAIL_UTIL_ANTENNA_MODE_DIVERSITY 3 /**< Choose antenna 1 or 2 dynamically */

/** @name Antenna Selection
 *
 * Define the antenna select pins ANTENNA_SELECT_GPIO and ANTENNA_nSELECT_GPIO
 * ANTENNA_SELECT_GPIO - low,  ANTENNA_nSELECT_GPIO - low:  undefined
 * ANTENNA_SELECT_GPIO - low,  ANTENNA_nSELECT_GPIO - high: select antenna 2
 * ANTENNA_SELECT_GPIO - high, ANTENNA_nSELECT_GPIO - low:  select antenna 1
 * ANTENNA_SELECT_GPIO - high, ANTENNA_nSELECT_GPIO - high: undefined
 *
 * @note The antenna selection can normally be configured at runtime
 * via sl_rail_util_set_antenna_mode(); when using \ref SL_RAIL_UTIL_ANTENNA_MODE_DIVERSITY
 * it can be changed via sl_rail_util_set_antenna() or sl_rail_util_toggle_antenna().
 */
//@{
typedef int8_t sl_rail_util_antenna_selection_t;
#define SL_RAIL_UTIL_ANTENNA_SELECT_ANTENNA1 1 /**< Select antenna 1 */
#define SL_RAIL_UTIL_ANTENNA_SELECT_ANTENNA2 2 /**< Select antenna 2 */

// The existence of Antenna GPIO location information on EFR32XG1 series
// parts enables use of the more flexible RAIL scheme va. legacy GPIO scheme
// for Tx-only diversity. However, the EFR32XG2 series doesn't use locations
// so the HAL configurator doesn't provide any. But EFR32XG2 does have RfPath
// selection, and SL_RAIL_UTIL_ANT_DIV_ANT0_LOC is used for that.
// On EFR32XG1 series, default location(s) to -1 to select legacy GPIO scheme.
// On EFR32XG2 series, default location(s) to 1 to select RAIL scheme RfPath 1;
// to force use of legacy GPIO scheme (because their GPIO choice for Tx-only
// diversity isn't supported by the radio), user must define each respective
// SL_RAIL_UTIL_ANT_DIV_[N]SEL_LOC as -1 in their HAL config include.
#ifdef  _SILICON_LABS_32B_SERIES_2
  #define ANTENNA_UNSPECIFIED_LOC  1 // Location to use RAIL scheme on RfPath 1
#else//!_SILICON_LABS_32B_SERIES_2
  #define ANTENNA_UNSPECIFIED_LOC -1 // Dummy location to select legacy GPIO scheme
#endif//_SILICON_LABS_32B_SERIES_2

// Establish Tx default mode
#ifdef  SL_RAIL_UTIL_ANT_DIV_TX_MODE
  #define ANTENNA_TX_DEFAULT_MODE SL_RAIL_UTIL_ANT_DIV_TX_MODE
#else//!SL_RAIL_UTIL_ANT_DIV_TX_MODE
  #define ANTENNA_TX_DEFAULT_MODE SL_RAIL_UTIL_ANTENNA_MODE_DIVERSITY
#endif//SL_RAIL_UTIL_ANT_DIV_TX_MODE

// Establish Rx default mode
#ifdef  SL_RAIL_UTIL_ANT_DIV_RX_MODE
  #define ANTENNA_RX_DEFAULT_MODE SL_RAIL_UTIL_ANT_DIV_RX_MODE
#else//!SL_RAIL_UTIL_ANT_DIV_RX_MODE
  #define ANTENNA_RX_DEFAULT_MODE SL_RAIL_UTIL_ANTENNA_MODE_DISABLED
#endif//SL_RAIL_UTIL_ANT_DIV_RX_MODE

// Determine scheme to use based on platform, PHY, debug, and GPIO location(s):
#if (!defined(_SILICON_LABS_32B_SERIES_1_CONFIG_1)                                          \
  && (((defined(SL_RAIL_UTIL_ANT_DIV_ANT0_PORT) || defined(SL_RAIL_UTIL_ANT_DIV_ANT1_PORT)) \
  && (!defined(SL_RAIL_UTIL_ANT_DIV_ANT0_PORT) || (SL_RAIL_UTIL_ANT_DIV_ANT0_LOC >= 0))     \
  && (!defined(SL_RAIL_UTIL_ANT_DIV_ANT1_PORT) || (SL_RAIL_UTIL_ANT_DIV_ANT1_LOC >= 0)))))
  #define ANTENNA_USE_RAIL_SCHEME 1
#else
  #define ANTENNA_USE_RAIL_SCHEME 0
#endif

//@} //END OF ANTENNA SELECTION

/** @brief Initialize antenna GPIOs
 *
 * @return SL_STATUS_OK if antenna GPIOs are configured successfully
 * and the default Tx antenna mode is established, or an error otherwise.
 */
sl_status_t sl_rail_util_ant_div_init(void);

/** @brief Sets the Tx antenna mode.
 *
 * @param mode The antenna mode to use for transmit.
 * @return SL_STATUS_OK if Tx antenna mode is configured as desired
 * or SL_STATUS_NOT_SUPPORTED if Tx antenna mode is unsupported.
 */
sl_status_t sl_rail_util_ant_div_set_antenna_mode(sl_rail_util_antenna_mode_t mode);

/** @brief Returns the current Tx antenna mode.
 *
 * @return The current Tx antenna mode.
 */
sl_rail_util_antenna_mode_t sl_rail_util_ant_div_get_antenna_mode(void);

/** @brief Returns the current Tx antenna selected.
 *
 * @return The current Tx antenna selected.
 */
sl_rail_util_antenna_selection_t sl_rail_util_ant_div_get_antenna_selected(void);

/** @brief Toggles the enabled Tx antenna.
 *
 * @return SL_STATUS_OK if Tx antenna was toggled, SL_STATUS_NOT_SUPPORTED otherwise
 */
sl_status_t sl_rail_util_ant_div_toggle_antenna(void);

/** @brief Sets the enabled Tx antenna.
 *
 * @param txAntenna The antenna to use for transmit.
 * @return SL_STATUS_OK if Tx antenna was set, SL_STATUS_NOT_SUPPORTED otherwise
 */
sl_status_t sl_rail_util_ant_div_set_antenna(sl_rail_util_antenna_selection_t txAntenna);

/** @brief Sets the Rx antenna mode.
 *
 * @param mode The antenna mode to use for receive.
 * @return SL_STATUS_OK if Rx antenna mode is configured as desired
 * or SL_STATUS_NOT_SUPPORTED if Rx antenna mode is unsupported.
 */
sl_status_t sl_rail_util_ant_div_set_antenna_rx_mode(sl_rail_util_antenna_mode_t mode);

/** @brief Returns the current Rx antenna mode.
 *
 * @return The current Rx antenna mode.
 */
sl_rail_util_antenna_mode_t sl_rail_util_ant_div_get_antenna_rx_mode(void);

/** @brief Returns the current Rx antenna diversity optimized PHY select
 *
 * @return Whether or not the RX antenna diversity optimized PHY is selected
 */
bool sl_rail_util_ant_div_get_phy_select(void);

/**
 * Initialize the RX antenna options.
 *
 * @param[out] rxOptions Update the RX antenna options in the provided
 * RX option feature mask.
 *
 * @note: Only the RX antenna option bits are altered by this function - other
 * options are left untouched.
 */
void sl_rail_util_ant_div_init_rx_options(RAIL_RxOptions_t *rxOptions);

/**
 * Initialize the TX antenna options.
 *
 * @param[out] txOptions Update the TX antenna options in the provided
 * TX option feature mask.
 *
 * @note: Only the TX antenna option bits are altered by this function - other
 * options are left untouched.
 */
void sl_rail_util_ant_div_init_tx_options(RAIL_TxOptions_t *txOptions);

/**
 * Get the antenna configuration.
 *
 * @param[out] antennaConfig The antenna configuration being used.
 */
void sl_rail_util_ant_div_get_antenna_config(RAIL_AntennaConfig_t *antennaConfig);

/**
 * Update the antenna configuration based on previously selected antenna mode
 *
 * @return SL_STATUS_OK if antenna is configured as desired
 * or SL_STATUS_NOT_SUPPORTED if antenna is unsupported.
 */
sl_status_t sl_rail_util_ant_div_update_antenna_config(void);
#endif //__SL_RAIL_UTIL_ANT_DIV_H__

/**@} END micro group
 */
