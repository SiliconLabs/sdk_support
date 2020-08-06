/***************************************************************************//**
 * @file
 * @brief Application bootloader
 * See @ref cbh_app for detailed documentation.
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
/** @addtogroup cbh_app
 * @brief Application bootloader and generic EEPROM Interface
 *
 * See app-bootloader.h for source code.
 *@{
 */

#ifndef __APP_BOOTLOADER_H__
#define __APP_BOOTLOADER_H__

///////////////////////////////////////////////////////////////////////////////

/** @name Required Custom Functions
 *@{
 */
void bootloaderInit();
void bootloaderInitCustom();

/** @brief Drives the app bootloader.  If the ::runRecovery parameter is ::true,
 * the recovery mode should be activated, otherwise it should attempt to
 * install an image.  This function should not return.  It should always exit
 * by resetting the the bootloader.
 *
 * @param runRecovery If ::true, recover mode is activated.  Otherwise, normal
 * image installation is activated.
 */
void bootloaderAction(bool runRecovery);

/**@} */

///////////////////////////////////////////////////////////////////////////////

/** @name Available Bootloader Library Functions
 * Functions implemented by the bootloader library that may be used by
 * custom functions.
 *@{
 */

/** @brief Activates ::recoveryMode to receive a new image over xmodem.
 * @return ::BL_SUCCESS if an image was successfully received.
 */
BL_Status recoveryMode(void);

/** @brief Processes an image in the external eeprom.
 * @param install If ::false, it will simply validate the image without
 * touching main flash.  If ::true, the image will be programmed to main flash.
 * @return ::BL_SUCCESS if an image was successfully installed/validated
 */
BL_Status processImage(bool install);

/**@} */

#endif //__APP_BOOTLOADER_H__

/**@} end of group*/
