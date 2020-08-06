/***************************************************************************//**
 * @file
 * @brief Bootloader GPIO definitions.
 * See @ref cbhc_gpio for detailed documentation.
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
/** @addtogroup cbhc_gpio
 * @brief Bootloader GPIO definitions.
 *
 * See bootloader-gpio.h for source code.
 *@{
 */

#ifndef __BOOTLOADER_GPIO_H__
#define __BOOTLOADER_GPIO_H__

/** @name State Indicator Macros
 * The bootloader indicates which state it is in by calling these
 *    // macros. Map them to the ::halBootloadStateIndicator function
 *    // (in bootloder-gpio.c) if you want to display that bootloader state.
 *    // Used to blink the LED's or otherwise signal bootloader activity.
 *@{
 */
//

/** @brief Finished init sequence, ready for bootload.
 */
#define BL_STATE_UP() do { bootloadStateIndicator(BL_ST_UP); } while (0)

/** @brief Called right before bootloader resets to application. Use to
 * cleanup and reset GPIO's to leave node in known state for app start,
 * if necessary.
 */
#define BL_STATE_DOWN() do { bootloadStateIndicator(BL_ST_DOWN); } while (0)

/** @brief Standalone bootloader polling serial/radio interface.
 */
#define BL_STATE_POLLING_LOOP() do { bootloadStateIndicator(BL_ST_POLLING_LOOP); } while (0)

/** @brief Processing download image.
 */
#define BL_STATE_DOWNLOAD_LOOP() do { bootloadStateIndicator(BL_ST_DOWNLOAD_LOOP); } while (0)

/** @brief Download process was a success.
 */
#define BL_STATE_DOWNLOAD_SUCCESS() do { bootloadStateIndicator(BL_ST_DOWNLOAD_SUCCESS); } while (0)

/** @brief Download process failed.
 */
#define BL_STATE_DOWNLOAD_FAILURE() do { bootloadStateIndicator(BL_ST_DOWNLOAD_FAILURE); } while (0)

/**@} */

/** @brief Defines various bootloader states.  Use in LED code to signal
 * bootload activity.
 */
enum blState_e {
  /** bootloader up */
  BL_ST_UP,

  /** bootloader going down */
  BL_ST_DOWN,

  /** polling interfaces */
  BL_ST_POLLING_LOOP,

  /** downloading */
  BL_ST_DOWNLOAD_LOOP,

  /** download failure */
  BL_ST_DOWNLOAD_FAILURE,

  /** download success */
  BL_ST_DOWNLOAD_SUCCESS
};

/** @brief Initialize GPIO.
 */
void bootloadGpioInit(void);

/** @brief Helper function used for displaying bootloader state (for example:
 * with LEDs).
 */
void bootloadStateIndicator(enum blState_e state);

/** @brief Force activation of bootloader.
 */
bool bootloadForceActivation(void);

#endif // __BOOTLOADER_GPIO_H__

/**@} end of group*/
