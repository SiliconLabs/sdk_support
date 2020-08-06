/***************************************************************************//**
 * @file
 * @brief
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
#ifndef __KEY_MATRIX_DRIVER_H__
#define __KEY_MATRIX_DRIVER_H__

#include PLATFORM_HEADER

/** @brief Initializes the key-matrix driver. The application framework will
 * generally initialize this plugin automatically. Customers who do not use the
 * framework must ensure the plugin is initialized by calling this function.
 */
void halKeyMatrixInitialize(void);

/** @brief Returns true if any key is held down
 *
 * This function checks if any inputs are being pulled low. indicating that a
 * key is pressed
 *
 * Note: This function must be run after halKeyMatrixPrepareForSleep() and
 * before halKeyMatrixRestoreFromSleep() as it requires all output pins to be
 * set to output high to detect key presses.
 *
 * @param none
 */
bool halKeyMatrixAnyKeyDown(void);

/** @brief Scans the key-matrix matrix and stores result
 *
 * This function scans the actual state of the key-matrix.
 *
 * @param none
 */
void halKeyMatrixScan(void);

/** @brief Scans one key and  stores result
 *
 * This function scans the actual state a key.
 *
 * @param key = input*NUM_OUTPUTS + output%NUM_OUTPUTS
 */
void halKeyMatrixScanSingle(uint8_t key);

/** @brief Get key-matrix scan state for a particular key.
 *
 *
 * @param key = input*NUM_OUTPUTS + output%NUM_OUTPUTS
 *
 * @return  false if the is key released and true if key is pressed
 *
 */
bool halKeyMatrixGetValue(uint8_t key);

/** @brief Config key-matrix GPIO pins before sleep, i.e. output pins set to
 * output driving to active level.
 *
 * @param none
 */
void halKeyMatrixPrepareForSleep(void);

/** @brief Config key-matrix GPIO pins after sleep, i.e. input pins set as
 * input with internal pull resistors pulling to inactive level
 *
 * @param none
 */
void halKeyMatrixRestoreFromSleep(void);

#endif // __KEY_MATRIX_DRIVER_H__
