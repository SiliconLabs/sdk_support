/***************************************************************************//**
 * @file
 * @brief The Z-Wave specific header file for the RAIL library.
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

#ifndef __RAIL_ZWAVE_H__
#define __RAIL_ZWAVE_H__

#include "rail_types.h"
#include "rail_chip_specific.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @addtogroup Z_Wave Z-Wave
/// @ingroup Protocol_Specific
/// @brief Z-Wave configuration routines
///
/// The functions in this group configure RAIL Z-Wave hardware
/// acceleration features.
///
/// To configure Z-Wave functionality, the application must first set up
/// a RAIL instance with RAIL_Init() and other setup functions.
///
/// @code{.c}
///
/// RAIL_ZWAVE_NodeId_t gRecentBeamNodeId;
/// uint8_t gRecentBeamChannelIndex;
///
/// // Main RAIL_EVENT callback
/// static void RAILCb_Event(RAIL_Handle_t railHandle, RAIL_Events_t events)
/// {
///   // Get beamNodeId and channel index from Beam Packet
///   if (events & RAIL_EVENT_ZWAVE_BEAM) {
///     if (RAIL_ZWAVE_IsEnabled(railHandle)) {
///       if ((RAIL_ZWAVE_GetBeamNodeId(railHandle, &gRecentBeamNodeId)
///            != RAIL_STATUS_NO_ERROR)
///           || (RAIL_ZWAVE_GetBeamChannelIndex(railHandle, &gRecentBeamChannelIndex)
///               != RAIL_STATUS_NO_ERROR)) {
///         return;
///       }
///     }
///   }
/// }
///
/// static const RAIL_ZWAVE_Config_t zwaveConfig = {
///   .options = RAIL_ZWAVE_OPTIONS_DEFAULT
/// };
///
/// RAIL_Status_t zwaveInit(void)
/// {
///   // initialize Z-Wave
///   RAIL_Status_t status = RAIL_ZWAVE_Init(railHandle, &zwaveConfig);
///
///   if (status != RAIL_STATUS_NO_ERROR) {
///     return status;
///   }
///
///   uint8_t myHomeId[4] = { 0xDE, 0xAD, 0xBE, 0xEF };
///   RAIL_ZWAVE_SetNodeId(railHandle, RAIL_ZWAVE_NODE_ID_DEFAULT);
///   RAIL_ZWAVE_SetHomeId(railHandle, myHomeId, RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE);
///
///   // configure region to EU(European Union)
///   return RAIL_ZWAVE_ConfigRegion(railHandle, RAIL_ZWAVE_REGION_EU);
/// }
/// @endcode
///
/// @{

/// Number of channels in each of Z-Wave's region-based PHYs
#define RAIL_NUM_ZWAVE_CHANNELS (3U)

/**
 * @enum RAIL_ZWAVE_Options_t
 * @brief Z-Wave options.
 */
RAIL_ENUM_GENERIC(RAIL_ZWAVE_Options_t, uint32_t) {
  // Z-Wave Option Bit Shifts

  /** Shift position of \ref RAIL_ZWAVE_OPTION_PROMISCUOUS_MODE bit */
  RAIL_ZWAVE_OPTION_PROMISCUOUS_MODE_SHIFT = 0,
  /** Shift position of \ref RAIL_ZWAVE_OPTION_DETECT_BEAM_FRAMES bit */
  RAIL_ZWAVE_OPTION_DETECT_BEAM_FRAMES_SHIFT,
  /** Shift position of \ref RAIL_ZWAVE_OPTION_NODE_ID_FILTERING bit */
  RAIL_ZWAVE_OPTION_NODE_ID_FILTERING_SHIFT,
};

// RAIL_ZWAVE_Options_t bitmasks

/** A value representing no options */
#define RAIL_ZWAVE_OPTIONS_NONE 0U

/** All options are disabled by default. */
#define RAIL_ZWAVE_OPTIONS_DEFAULT RAIL_ZWAVE_OPTIONS_NONE

/**
 * An option to configure promiscuous mode, accepting packets regardless
 * of HomeId. Defaults to false, filtering packets based on the HomeId.
 * When true, such filtering is disabled.
 */
#define RAIL_ZWAVE_OPTION_PROMISCUOUS_MODE \
  (1u << RAIL_ZWAVE_OPTION_PROMISCUOUS_MODE_SHIFT)
/**
 * An option to configure Beam frame recognition. Defaults to false.
 * When true, Beam frames that are broadcast or match the NodeId and
 * HomeIdHash values will trigger \ref RAIL_EVENT_ZWAVE_BEAM event,
 * in addition to \ref RAIL_EVENT_RX_PACKET_ABORTED which occurs for
 * every received Beam frame.
 *
 * @note This option takes precedence over \ref
 *   RAIL_ZWAVE_OPTION_PROMISCUOUS_MODE when receiving a beam frame.
 *   If this option is false, beam frames are not considered special
 *   and will be received as if they were normal Z-Wave frames, assuredly
 *   triggering \ref RAIL_EVENT_RX_FRAME_ERROR.
 */
#define RAIL_ZWAVE_OPTION_DETECT_BEAM_FRAMES \
  (1u << RAIL_ZWAVE_OPTION_DETECT_BEAM_FRAMES_SHIFT)
/**
 * An option to filter packets based on Node ID when not
 * promiscuous.
 */
#define RAIL_ZWAVE_OPTION_NODE_ID_FILTERING \
  (1u << RAIL_ZWAVE_OPTION_NODE_ID_FILTERING_SHIFT)

/** A value representing all options */
#define RAIL_ZWAVE_OPTIONS_ALL 0xFFFFFFFFU

/**
 * @enum RAIL_ZWAVE_NodeId_t
 * @brief A Z-Wave Node Id.
 *
 * @note Values 0xE9..0xFE are reserved.
 */
RAIL_ENUM(RAIL_ZWAVE_NodeId_t) {
  RAIL_ZWAVE_NODE_ID_NONE = 0x00U, /**< The unknown NodeId for uninitialized nodes. */
  RAIL_ZWAVE_NODE_ID_BROADCAST = 0xFFU, /**< The broadcast NodeId. */
  RAIL_ZWAVE_NODE_ID_DEFAULT
    = RAIL_ZWAVE_NODE_ID_BROADCAST, /**< Default to the broadcast NodeId. */
  // All other values between 0x00 and 0xFE are valid nodeId's.
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ZWAVE_NODE_ID_NONE      ((RAIL_ZWAVE_NodeId_t) RAIL_ZWAVE_NODE_ID_NONE)
#define RAIL_ZWAVE_NODE_ID_BROADCAST ((RAIL_ZWAVE_NodeId_t) RAIL_ZWAVE_NODE_ID_BROADCAST)
#define RAIL_ZWAVE_NODE_ID_DEFAULT   ((RAIL_ZWAVE_NodeId_t) RAIL_ZWAVE_NODE_ID_DEFAULT)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @enum RAIL_ZWAVE_HomeId_t
 * @brief A Z-Wave Home Id.
 *
 * @note Home Id's in the range 0x54000000..0x55FFFFFF are illegal.
 */
RAIL_ENUM_GENERIC(RAIL_ZWAVE_HomeId_t, uint32_t) {
  RAIL_ZWAVE_HOME_ID_UNKNOWN = 0x00000000U, /**< The unknown HomeId. */
  RAIL_ZWAVE_HOME_ID_DEFAULT = 0x54545454U, /**< An impossible and unlikely HomeId. */
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ZWAVE_HOME_ID_UNKNOWN ((RAIL_ZWAVE_HomeId_t) RAIL_ZWAVE_HOME_ID_UNKNOWN)
#define RAIL_ZWAVE_HOME_ID_DEFAULT ((RAIL_ZWAVE_HomeId_t) RAIL_ZWAVE_HOME_ID_DEFAULT)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @enum RAIL_ZWAVE_HomeIdHash_t
 * @brief A Z-Wave Home Id hash.
 *
 * @note Certain values (as shown) are illegal.
 */
RAIL_ENUM(RAIL_ZWAVE_HomeIdHash_t) {
  RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_1 = 0x0AU, /**< An illegal HomeIdHash value. */
  RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_2 = 0x4AU, /**< An illegal HomeIdHash value. */
  RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_3 = 0x55U, /**< An illegal HomeIdHash value. */
  RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE = 0x55U, /**< Illegal HomeIdHash value that
                                                  suppresses checking the
                                                  HomeIdHash field of Beam
                                                  packets. */
  RAIL_ZWAVE_HOME_ID_HASH_DEFAULT
    = RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE, /**< Default to don't care. */
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_1 ((RAIL_ZWAVE_HomeIdHash_t) RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_1)
#define RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_2 ((RAIL_ZWAVE_HomeIdHash_t) RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_2)
#define RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_3 ((RAIL_ZWAVE_HomeIdHash_t) RAIL_ZWAVE_HOME_ID_HASH_ILLEGAL_3)
#define RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE ((RAIL_ZWAVE_HomeIdHash_t) RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE)
#define RAIL_ZWAVE_HOME_ID_HASH_DEFAULT   ((RAIL_ZWAVE_HomeIdHash_t) RAIL_ZWAVE_HOME_ID_HASH_DEFAULT)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAIL_ZWAVE_Config_t
 * @brief A configuration structure for Z-Wave in RAIL.
 */
typedef struct RAIL_ZWAVE_Config {
  /**
   * Defines Z-Wave options.
   */
  RAIL_ZWAVE_Options_t options;
  /**
   * Defines Z-Wave ACKing configuration.
   */
  RAIL_AutoAckConfig_t ackConfig;
  /**
   * Defines state timings for Z-Wave.
   */
  RAIL_StateTiming_t timings;
} RAIL_ZWAVE_Config_t;

/**
 * @enum RAIL_ZWAVE_Baud_t
 * @brief Z-Wave supported baudrates.
 */
RAIL_ENUM(RAIL_ZWAVE_Baud_t) {
  RAIL_ZWAVE_BAUD_9600,    /**< 9.6kbps baudrate*/
  RAIL_ZWAVE_BAUD_40K,     /**< 40kbps baudrate*/
  RAIL_ZWAVE_BAUD_100K,    /**< 100kbps baudrate*/
  RAIL_ZWAVE_ENERGY_DETECT /**< Energy detection phy*/
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ZWAVE_BAUD_9600 ((RAIL_ZWAVE_Baud_t) RAIL_ZWAVE_BAUD_9600)
#define RAIL_ZWAVE_BAUD_40K  ((RAIL_ZWAVE_Baud_t) RAIL_ZWAVE_BAUD_40K)
#define RAIL_ZWAVE_BAUD_100K ((RAIL_ZWAVE_Baud_t) RAIL_ZWAVE_BAUD_100K)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @enum RAIL_ZWAVE_RegionId_t
 * @brief Z-Wave region identifications.
 */
RAIL_ENUM(RAIL_ZWAVE_RegionId_t) {
  RAIL_ZWAVE_REGIONID_UNKNOWN, /**< Unknown/Invalid*/
  RAIL_ZWAVE_REGIONID_EU,      /**< European Union*/
  RAIL_ZWAVE_REGIONID_US,      /**< United States*/
  RAIL_ZWAVE_REGIONID_ANZ,     /**< Australia/New Zealand*/
  RAIL_ZWAVE_REGIONID_HK,      /**< Hong Kong*/
  RAIL_ZWAVE_REGIONID_MY,      /**< Malaysia*/
  RAIL_ZWAVE_REGIONID_IN,      /**< India*/
  RAIL_ZWAVE_REGIONID_JP,      /**< Japan*/
  RAIL_ZWAVE_REGIONID_RU,      /**< Russian Federation*/
  RAIL_ZWAVE_REGIONID_IL,      /**< Israel*/
  RAIL_ZWAVE_REGIONID_KR,      /**< Korea*/
  RAIL_ZWAVE_REGIONID_CN,      /**< China*/
  RAIL_ZWAVE_REGIONID_COUNT    /**< Count of known regions, must be last*/
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ZWAVE_REGIONID_UNKNOWN ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_UNKNOWN)
#define RAIL_ZWAVE_REGIONID_EU ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_EU)
#define RAIL_ZWAVE_REGIONID_US ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_US)
#define RAIL_ZWAVE_REGIONID_ANZ ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_ANZ)
#define RAIL_ZWAVE_REGIONID_HK ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_HK)
#define RAIL_ZWAVE_REGIONID_MY ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_MY)
#define RAIL_ZWAVE_REGIONID_IN ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_IN)
#define RAIL_ZWAVE_REGIONID_JP ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_JP)
#define RAIL_ZWAVE_REGIONID_RU ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_RU)
#define RAIL_ZWAVE_REGIONID_IL ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_IL)
#define RAIL_ZWAVE_REGIONID_KR ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_KR)
#define RAIL_ZWAVE_REGIONID_CN ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_CN)
#define RAIL_ZWAVE_REGIONID_COUNT ((RAIL_ZWAVE_RegionId_t) RAIL_ZWAVE_REGIONID_COUNT)
#endif//DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Largest ACK timeout period based on
// aPhyTurnaroundTimeRxTx (1 ms max)+ (aMacTransferAckTimeTX (168 bits)* (1/data rate))
// For slowest Data Rate R1 (19.6 kbit/s)
#define RAIL_ZWAVE_MAX_ACK_TIMEOUT_US        (9600U)

// Defines for Transition timing
#define RAIL_ZWAVE_TIME_IDLE_TO_RX_US        (100U)
#define RAIL_ZWAVE_TIME_TX_TO_RX_US          (0U)
#define RAIL_ZWAVE_TIME_IDLE_TO_TX_US        (0U)
#define RAIL_ZWAVE_TIME_RX_TO_TX_US          (1000U)

#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAIL_ZWAVE_BeamRxConfig_t
 * @brief Configuration structure for Z-Wave Beam Detection.
 * This structure should not be used without direct instruction
 * by Silicon Labs. Appropriate defaults for this are built into
 * the RAIL library.
 */
typedef struct RAIL_ZWAVE_BeamRxConfig {
  /// Channel hopping pattern to use for beam detection.
  RAIL_RxChannelHoppingConfig_t channelHoppingConfig;
  /// Amount of time to spend trying to receive a beam once detected.
  /// 100kbps only
  RAIL_RxDutyCycleConfig_t receiveConfig_100;
  /// Amount of time to spend trying to receive a beam once detected.
  /// 40kbps only
  RAIL_RxDutyCycleConfig_t receiveConfig_40;
} RAIL_ZWAVE_BeamRxConfig_t;

/**
 * @struct RAIL_ZWAVE_RegionConfig_t
 * @brief Each Z-Wave region supports 3 channels.
 */
typedef struct RAIL_ZWAVE_RegionConfig {
  uint32_t frequency[RAIL_NUM_ZWAVE_CHANNELS];                        /**< Channel frequency in hertz*/
  RAIL_TxPower_t maxPower[RAIL_NUM_ZWAVE_CHANNELS];                   /**< The maximum power allowed on the channel*/
  RAIL_ZWAVE_Baud_t baudRate[RAIL_NUM_ZWAVE_CHANNELS];                /**< Channel baud rate index*/
  RAIL_ZWAVE_RegionId_t regionId;                                     /**< Identification number for the region*/
} RAIL_ZWAVE_RegionConfig_t;

/**
 * Switch the Z-Wave region.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] regionCfg Z-Wave channel configuration for the selected region
 * @return Status code indicating success of the function call.
 *
 * @note Setting a new Z-Wave Region will default any Low Power values to
 * Normal Power values for the region.
 * Z-Wave Region configuration must always be followed by a Low Power setup
 * in case one desires to have the Low Power ACKing functionality.
 */
RAIL_Status_t RAIL_ZWAVE_ConfigRegion(RAIL_Handle_t railHandle,
                                      const RAIL_ZWAVE_RegionConfig_t *regionCfg);

/**
 * Initialize RAIL for Z-Wave features.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] config A Z-Wave configuration structure.
 * @return A status code indicating success of the function call.
 *
 * This function is the entry point for working with Z-Wave within
 * RAIL. It will set up relevant hardware acceleration for Z-Wave-specific
 * features, such as HomeId filtering and beam packets (as
 * specified in the configuration) and allows users to select the
 * relevant Z-Wave region-specific PHY via \ref RAIL_ZWAVE_ConfigRegion.
 */
RAIL_Status_t RAIL_ZWAVE_Init(RAIL_Handle_t railHandle,
                              const RAIL_ZWAVE_Config_t *config);

/**
 * De-initialize Z-Wave hardware acceleration.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Disables and resets all Z-Wave hardware acceleration features. This
 * function should only be called when the radio is IDLE.
 */
RAIL_Status_t RAIL_ZWAVE_Deinit(RAIL_Handle_t railHandle);

/**
 * Returns whether Z-Wave hardware acceleration is currently enabled.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @return True if Z-Wave hardware acceleration was enabled to start with
 * and false otherwise.
 */
bool RAIL_ZWAVE_IsEnabled(RAIL_Handle_t railHandle);

/**
 * Configure Z-Wave options.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] mask A bitmask containing which options should be modified.
 * @param[in] options A bitmask containing desired configuration settings.
 *   Bit positions for each option are found in the \ref RAIL_ZWAVE_Options_t.
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_ZWAVE_ConfigOptions(RAIL_Handle_t railHandle,
                                       RAIL_ZWAVE_Options_t mask,
                                       RAIL_ZWAVE_Options_t options);

/**
 * Inform RAIL of the Z-Wave node's NodeId for receive filtering purposes.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] nodeId A Z-Wave Node Id.
 * @return Status code indicating success of the function call.
 *
 * @note Until this API is called, RAIL will assume the NodeId is
 *   \ref RAIL_ZWAVE_NODE_ID_DEFAULT.
 */
RAIL_Status_t RAIL_ZWAVE_SetNodeId(RAIL_Handle_t railHandle,
                                   RAIL_ZWAVE_NodeId_t nodeId);

/**
 * Informs RAIL of the Z-Wave node's HomeId and its hash for receive filtering
 * purposes.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] homeId A Z-Wave Home Id.
 * @param[in] homeIdHash The hash of the Home Id expected in Beam frames.
 *   If this is \ref RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE, Beam frame detection
 *   will not check the HomeIdHash in a received Beam frame at all, and
 *   \ref RAIL_EVENT_ZWAVE_BEAM will trigger based solely on the nodeId
 *   in the Beam frame.
 * @return Status code indicating success of the function call.
 *
 * @note Until this API is called, RAIL will assume the HomeId is an
 *   illegal one of \ref RAIL_ZWAVE_HOME_ID_DEFAULT, and its hash is \ref
 *   RAIL_ZWAVE_HOME_ID_HASH_DONT_CARE.
 */
RAIL_Status_t RAIL_ZWAVE_SetHomeId(RAIL_Handle_t railHandle,
                                   RAIL_ZWAVE_HomeId_t homeId,
                                   RAIL_ZWAVE_HomeIdHash_t homeIdHash);

/**
 * Get the NodeId of the most recently seen Beam frame that targeted this
 * node.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[out] pNodeId A pointer to \ref RAIL_ZWAVE_NodeId_t to populate.
 * @return Status code indicating success of the function call.
 *
 * @note This is best called while handling the \ref RAIL_EVENT_ZWAVE_BEAM
 *   event; if multiple beams are received only the most recent beam's NodeId
 *   is provided.
 */
RAIL_Status_t RAIL_ZWAVE_GetBeamNodeId(RAIL_Handle_t railHandle,
                                       RAIL_ZWAVE_NodeId_t *pNodeId);

/**
 * Get the channel hopping index of the most recently seen Beam frame that
 * targeted this node.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[out] pChannelIndex A pointer to a uint8_t to populate with
 *   the channel hopping index. If channel-hopping was off at the time
 *   the beam packet was received, \ref RAIL_CHANNEL_HOPPING_INVALID_INDEX
 *   is emplaced.
 * @return Status code indicating success of the function call.
 *
 * @note This is best called while handling the \ref RAIL_EVENT_ZWAVE_BEAM
 *   event; if multiple beams are received only the most recent beam's
 *   channel hopping index is provided.
 */
RAIL_Status_t RAIL_ZWAVE_GetBeamChannelIndex(RAIL_Handle_t railHandle,
                                             uint8_t *pChannelIndex);

/**
 * Sets the Raw Low Power settings.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] powerLevel Desired low power raw level.
 * @return Status code indicating success of the function call.
 *
 * Low Power settings are required during ACK transmissions when
 * the Low Power Bit is set. This setting is only valid for one
 * subsequent transmission, after which all transmissions will be
 * at the nominal power setting, until re-invoked.
 */

RAIL_Status_t RAIL_ZWAVE_SetTxLowPower(RAIL_Handle_t railHandle,
                                       uint8_t powerLevel);

/**
 * Set the Low Power settings in dBm.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] powerLevel Desired low power level dBm.
 * @return Status code indicating success of the function call.
 *
 * Low Power settings are required during ACK transmissions when
 * the Low Power Bit is set. This setting is only valid for one
 * subsequent transmission, after which all transmissions will be
 * at the nominal power setting, until re-invoked.
 */
RAIL_Status_t RAIL_ZWAVE_SetTxLowPowerDbm(RAIL_Handle_t railHandle,
                                          RAIL_TxPower_t powerLevel);

/**
 * Get the TX low power in raw units (see \ref rail_chip_specific.h for
 * value ranges).
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return The chip-specific \ref RAIL_TxPowerLevel_t raw value of the low
 * transmit power.
 *
 * This API returns the low raw power value that was set by
 * \ref RAIL_ZWAVE_SetTxLowPower.
 *
 * Calling this function before configuring the Low Power PA
 * (i.e., before a successful
 * call to \ref RAIL_ZWAVE_SetTxLowPowerDbm or \ref RAIL_ZWAVE_SetTxLowPower)
 * will return the low power value same as the nominal power.
 * Also, calling this function before configuring the PA
 * (i.e., before a successful call to \ref RAIL_ConfigTxPower) will return an error
 * (RAIL_TX_POWER_LEVEL_INVALID).
 */
RAIL_TxPowerLevel_t RAIL_ZWAVE_GetTxLowPower(RAIL_Handle_t railHandle);

/**
 * Get the TX low power in terms of deci-dBm instead of raw power level.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return The chip-specific \ref RAIL_TxPower_t value of the low
 * transmit power in deci-dBm.
 */
RAIL_TxPower_t RAIL_ZWAVE_GetTxLowPowerDbm(RAIL_Handle_t railHandle);

/**
 * This function is used to implement beam detection and reception
 * algorithms. It will take care of all configuration and radio setup to
 * detect and receive beams in the current Z-Wave region.
 * If a beam is detected, RAIL will provide
 * the usual \ref RAIL_EVENT_ZWAVE_BEAM event, during which time users can
 * process the beam as normal. However, normal packets may also be
 * received during this time (thus triggering \ref RAIL_EVENTS_RX_COMPLETION
 * events), in which case, this API may need to be re-called to receive
 * a beam. Users should also listen for
 * \ref RAIL_EVENT_RX_CHANNEL_HOPPING_COMPLETE which will indicate
 * that no beam is heard, and that the radio can be turned off until the next
 * time the user wants to listen for beams. Until one of these events are
 * received, users should not try to attempt to reconfigure radio settings or
 * start another radio operation. If an application needs to do some other
 * operation or configuration, it must first call \ref RAIL_Idle and wait
 * for the radio to idle.
 *
 * @note: The radio must be idle before calling this function.
 *
 * @note: \ref RAIL_ConfigRxChannelHopping must have been called successfully
 * in Z-Wave before this function is called to provide a valid memory buffer
 * for internal use (see \ref RAIL_RxChannelHoppingConfig_t::buffer).
 *
 * @note: This function alters radio functionality substantially. After calling
 * it, the user should call \ref RAIL_ZWAVE_ConfigRegion,
 * \ref RAIL_ConfigRxChannelHopping, \ref RAIL_EnableRxChannelHopping,
 * and \ref RAIL_SetRxTransitions to reset these parameters to whatever
 * behaviors were desired before calling this function. Additionally,
 * this function will idle the radio upon on exit.
 *
 * @param[in]  railHandle A RAIL instance handle.
 * @param[out] beamDetectIndex Indicator of whether or not a beam was detected
 * at all, regardless of if it was received, generally for use only by instruction
 * from Silicon Labs. Can be NULL.
 * @param[out] schedulerInfo While Z-Wave is currently not supported in
 * RAIL Multiprotocol, this scheduler info is added to future proof
 * against any future version of multiprotocol which may support it. For now,
 * this argument can be NULL.
 *
 * @return status indicating whether or not the radio was able to configure
 * beam packet detection/reception. Reasons for failure include an un-idled
 * radio or a non Japan or Korea region configured before calling this function.
 */
RAIL_Status_t RAIL_ZWAVE_ReceiveBeam(RAIL_Handle_t railHandle,
                                     uint8_t *beamDetectIndex,
                                     const RAIL_SchedulerInfo_t *schedulerInfo);

/**
 * Configure the receive algorithm used in \ref RAIL_ZWAVE_ReceiveBeam.
 * This function should not be used without direct instruction by Silicon Labs.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] config Configuration for beam detection algorithm.
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_ZWAVE_ConfigBeamRx(RAIL_Handle_t railHandle, RAIL_ZWAVE_BeamRxConfig_t *config);

/** EU-European Union", RAIL_ZWAVE_REGION_EU */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_EU;

/** US-United States", RAIL_ZWAVE_REGION_US */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_US;

/** ANZ-Australia/New Zealand", RAIL_ZWAVE_REGION_ANZ */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_ANZ;

/** HK-Hong Kong", RAIL_ZWAVE_REGION_HK */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_HK;

/** MY-Malaysia", RAIL_ZWAVE_REGION_MY */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_MY;

/** IN-India", RAIL_ZWAVE_REGION_IN */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_IN;

/** JP-Japan", RAIL_ZWAVE_REGION_JP */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_JP;

/** JP-Japan", RAIL_ZWAVE_REGION_JP */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_JPED;

/** RU-Russia", RAIL_ZWAVE_REGION_RU */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_RU;

/** IL-Israel", RAIL_ZWAVE_REGION_IL */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_IL;

/** KR-Korea", RAIL_ZWAVE_REGION_KR */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_KR;

/** KR-Korea", RAIL_ZWAVE_REGION_KR */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_KRED;

/** CN-China", RAIL_ZWAVE_REGION_CN */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_CN;

/** Invalid Region */
extern const RAIL_ZWAVE_RegionConfig_t RAIL_ZWAVE_REGION_INVALID;

/** @} */ // end of Z_Wave

#ifdef __cplusplus
}
#endif

#endif // __RAIL_ZWAVE_H__
