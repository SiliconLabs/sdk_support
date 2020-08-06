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
// *****************************************************************************
// * temperature.h
// *
// * API for reading temperature data from a temperature sensor
// *
// * Copyright 2015 Silicon Laboratories, Inc.                              *80*
// *****************************************************************************

// Some implementations of this function may make use of ::EmberEventControl
// events.  If so, the application framework will generally manage the events
// automatically.  Customers who do not use the framework must ensure the events
// are run, by calling either ::emberRunEvents or ::emberRunTask.  See the
// specific implementation for more information.

#ifndef __TEMPERATURE_H__
#define __TEMPERATURE_H__

/** @brief Initiate a temperature read
 *
 * This function will initiate a read of the temperature sensor.  This read will
 * then trigger a driver specific callback when the read has completed.
 *
 */
void halTemperatureStartRead(void);

/** @brief Initializes the temperature hardware, along with any hardware
 * peripherals necessary to interface with the hardware.  The application
 * framework will generally initialize this plugin automatically.  Customers who
 * do not use the framework must ensure the plugin is initialized by calling
 * this function.
 */
void halTemperatureInit(void);

int32_t halTemperatureGetMaxMeasureableTemperatureMilliC(void);
int32_t halTemperatureGetMinMeasureableTemperatureMilliC(void);

/** @brief Temperature Reading Complete
 *
 * This callback is called when a temperature reading is complete.
 *
 * @param temperature The temperature, represented in milli degrees Celsius
 * @param readSuccess if temperature reading is successful
 */
void halTemperatureReadingCompleteCallback(int32_t temperature,
                                           bool readSuccess);

#endif //__TEMPERATURE_H__
