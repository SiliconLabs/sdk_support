/***************************************************************************//**
 * @file
 * @brief The MFM specific header file for the RAIL library.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __RAIL_MFM_H__
#define __RAIL_MFM_H__

#include "rail_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/// @addtogroup MFM Multi-Level Frequency Modulation
/// @ingroup Protocol_Specific
/// @brief MFM configuration routines
/// Note that this feature is only supported on EFR32xG23 devices.
///
/// This feature can be used to directly control the TX interpolation filter
/// input to allow for a more flexible frequency modulation scheme than our
/// standard MODEM. When doing this, the MFM buffer is treated as an array
/// of 8-bit signed data used as normalized frequency deviation to the SYNTH
/// frequency to directly controls the interpolation filter input.
/// No support for frame handling, coding, nor shaping is supported.
/// Only compatible with FSK modulations.
///
/// The functions in this group configure RAIL MFM (multi-level frequency modulation)
/// hardware acceleration features.
///
/// To configure MFM functionality, the application must first set up
/// a RAIL instance with RAIL_Init() and other setup functions.
///
/// @code{.c}
///
/// uint8_t txCount = 0;
///
/// // Main RAIL_EVENT callback
/// static void RAILCb_Event(RAIL_Handle_t railHandle, RAIL_Events_t events)
/// {
///   // Increment TX counter
///   if (events & RAIL_EVENT_MFM_BUF_DONE) {
///     if (RAIL_MFM_IsEnabled(railHandle)) {
///         txCount++;
///         return;
///       }
///     }
///   }
/// }
///
/// static const RAIL_MFM_Config_t mfmConfig = {
///   .pBuffer0 = (&channelHoppingBufferSpace[0]),
///   .pBuffer1 = (&channelHoppingBufferSpace[MFM_RAW_BUF_SZ_BYTES / 4]),
///   .bufferSizeWords = (MFM_RAW_BUF_SZ_BYTES / 4),
///   .options = RAIL_MFM_OPTION_DETECT_TX_BUFFER_DONE,
///   .timings = {
///     .idleToTx = 100,
///     .idleToRx = 0,
///     .rxToTx = 0,
///     .txToRx = 0,
///     .rxSearchTimeout = 0,
///     .txToRxSearchTimeout = 0
/// };
///
/// RAIL_Status_t mfmInit(void)
/// {
///   // initialize MFM
///   uint32_t idx;
///   uint32_t *pDst0 = mfmConfig.pBuffer0;
///   uint32_t *pDst1 = mfmConfig.pBuffer1;
///   RAIL_Status_t status;
///   for (idx = 0; idx < (MFM_RAW_BUF_SZ_BYTES / 16); idx++) {
///     pDst0[4 * idx + 0] = 0x755A3100;
///     pDst1[4 * idx + 0] = 0x755A3100;
///     pDst0[4 * idx + 1] = 0x315A757F;
///     pDst1[4 * idx + 1] = 0x315A757F;
///     pDst0[4 * idx + 2] = 0x8BA6CF00;
///     pDst1[4 * idx + 2] = 0x8BA6CF00;
///     pDst0[4 * idx + 3] = 0xCFA68B81;
///     pDst1[4 * idx + 3] = 0xCFA68B81;
///   }
///   status = RAIL_MFM_Init(railHandle, &mfmConfig);
///
///   // start transmitting
///   if (status == RAIL_STATUS_NO_ERROR) {
///     return (RAIL_StartTx(railHandle, 0, 0, &schedulerInfo));
///   }
///
/// }
///
/// RAIL_Status_t mfmDeInit(void)
/// {
///   // De-initialize MFM
///   return (RAIL_MFM_Deinit(railHandle));
/// }
/// @endcode
///
/// @{

/**
 * @enum RAIL_MFM_Options_t
 * @brief MFM options.
 */
RAIL_ENUM(RAIL_MFM_Options_t) {
  // MFM Option Bit Shifts

  /** Shift position of \ref RAIL_MFM_OPTION_DETECT_TX_BUFFER_DONE bit */
  RAIL_MFM_OPTION_DETECT_TX_BUFFER_DONE_SHIFT,
};

/** A value representing no options */
#define RAIL_MFM_OPTIONS_NONE 0U

/** All options are disabled by default. */
#define RAIL_MFM_OPTIONS_DEFAULT RAIL_MFM_OPTIONS_NONE

// RAIL_MFM_Options_t bitmasks
/**
 * An option to configure MFM TX buffer transmitted event. Defaults to false.
 * When true, a buffer has been completely transmitted and will trigger the
 * \ref RAIL_EVENT_MFM_TX_BUFFER_DONE event.
 *
 */
#define RAIL_MFM_OPTION_DETECT_TX_BUFFER_DONE \
  (1U << RAIL_MFM_OPTION_DETECT_TX_BUFFER_DONE_SHIFT)

/**
 * @struct RAIL_MFM_Config_t
 * @brief A configuration structure for MFM in RAIL.
 *
 * User should prepare a ping-pong buffer (called buffer0 and buffer1 below)
 * to be used with the MFM feature before start transmitting, and populate
 * them with the initial buffer content. Once a user start transmitting the data
 * in the ping-pong buffer, RAIL will manage the ping-pong buffer so it looks
 * like a continuous transmission to the receiver. Every time a buffer is
 * transmitted (one of the ping-pong buffer), user have a choice to get an
 * event (RAIL_EVENT_MFM_TX_BUFFER_DONE) such that user can update the data in
 * the buffer that was just transmitted, without the need to start/stop the
 * transmission. User can stop the transmit operation by disabling the MFM feature.
 *
 */
typedef struct RAIL_MFM_Config {
  /**
   * pointer to buffer0.  Need to be aligned to 32-bit boundary.
   */
  uint32_t *pBuffer0;
  /**
   * pointer to buffer1.  Need to be aligned to 32-bit boundary.
   */
  uint32_t *pBuffer1;
  /**
   * size of buffer A and B in 32-bit words.
   */
  uint32_t bufferSizeWords;
  /**
   * Defines MFM options.
   */
  RAIL_MFM_Options_t options;
  /**
   * Defines state timings for MFM.
   */
  RAIL_StateTiming_t timings;
} RAIL_MFM_Config_t;

/**
 * Initialize RAIL for MFM features.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] config A MFM configuration structure.
 * @return A status code indicating success of the function call.
 *
 * This function is the entry point for working with MFM within
 * RAIL. It will set up relevant hardware acceleration for MFM-specific
 * features, such as ping-pong buffer and TX baud rate (as
 * specified in the configuration).
 */
RAIL_Status_t RAIL_MFM_Init(RAIL_Handle_t railHandle,
                            const RAIL_MFM_Config_t *config);

/**
 * De-initialize MFM hardware acceleration.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Disables and resets all MFM hardware acceleration features. This
 * function will put the radio to IDLE.
 */
RAIL_Status_t RAIL_MFM_Deinit(RAIL_Handle_t railHandle);

/**
 * Return whether MFM hardware acceleration is currently enabled.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @return True if MFM hardware acceleration was enabled to start with
 * and false otherwise.
 */
bool RAIL_MFM_IsEnabled(RAIL_Handle_t railHandle);

/** @} */ // end of MFM

#endif //DOXYGEN_SHOULD_SKIP_THIS

#ifdef __cplusplus
}
#endif

#endif // __RAIL_MFM_H__
