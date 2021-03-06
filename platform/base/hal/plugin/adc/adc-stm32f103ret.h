/***************************************************************************//**
 * @file
 * @brief See @ref stm32f103ret_adc for documentation.
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
/** @addtogroup stm32f103ret_adc
 * @brief Example API functions for operating an ADC.
 *
 * @note On the STM32F103RET example host, this driver is written
 * specifically to interact with the breakout board temp sensor.
 *
 * See adc.h for source code.
 *@{
 */

#ifndef __ADC_H__
#define __ADC_H__

/** @brief The actual pin that the temp sensor is connected to.
 */
#define TEMP_SENSOR_PIN       GPIO_Pin_0

/** @brief The actual port that the temp sensor is connected to.
 */
#define TEMP_SENSOR_PORT      GPIOC

/** @brief The actual ADC that the temp sensor is connected to.
 */
#define TEMP_SENSOR_ADC       ADC1

/** @brief The actual ADC channel that the temp sensor is connected to.
 */
#define TEMP_SENSOR_ADC_CHAN  10

/** @brief The actual pin that the temp sensor enable is connected to.
 */
#define TEMP_ENABLE_PIN       GPIO_Pin_8

/** @brief The actual port that the temp sensor enable is connected to.
 */
#define TEMP_ENABLE_PORT      GPIOA

/** @brief Initialize the ADC.
 */
void halInternalInitAdc(void);

/** @brief Take a raw reading of the ADC.
 *
 * @note This function is blocking.
 *
 * @return The raw value read from the ADC.
 */
uint16_t halSampleAdc(void);

/** @brief Convert the raw register value (the unaltered value taken
 * directly from the ADC's data register) into a signed fixed point value
 * with units 10^-4 Volts.
 *
 * @param value  An uint16_t to be converted.
 *
 * @return Volts as signed fixed point with units 10^-4 Volts.
 */
int32_t halConvertValueToVolts(uint16_t value);

#endif //__ADC_H__

/**@}END addtogroup
 */
