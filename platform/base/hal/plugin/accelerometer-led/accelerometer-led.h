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
// Copyright 2014 Silicon Laboratories, Inc.
//
// Some implementations of this function may make use of ::EmberEventControl
// events.  If so, the application framework will generally manage the events
// automatically.  Customers who do not use the framework must ensure the events
// are run, by calling either ::emberRunEvents or ::emberRunTask.  See the
// specific implementation for more information.
#ifndef __ACCELEROMETER_LED_H__
#define __ACCELEROMETER_LED_H__

/** @brief Returns X, Y and Z value from accelerometer
 *
 * This function reads out the X, Y and Z values from the accelerometer and
 * returns them.
 *
 * @param x A pointer to the X axis value
 *
 * @param y A pointer to the Y axis value
 *
 * @param z A pointer to the Z axis value
 */
void halAccelerometerLedReadXyz(int8_t *x, int8_t *y, int8_t *z);

/** @brief Initializes accelerometer and LED. The application framework will
 * generally initialize this plugin automatically. Customers who do not use the
 * framework must ensure the plugin is initialized by calling this function.
 *
 * This function initializes the accelerometer to the following settings:
 * 1. Drive INT1 into EM3xx pin when acceleration slope exceeds 156mg/50ms
 * 2. Operate in low-power mode 1 (LPM1) to minimize power consumption
 *
 * This function also sets up an interrupt on the GPIO pin connected to the
 * INT1 signal from the accelerometer.
 *
 * @param none
 */
void halAccelerometerLedInitialize(void);

#endif  //  __ACCELEROMETER_LED_H__
