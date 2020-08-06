/***************************************************************************//**
 * @file
 * @brief GPIO Activation plugin for Silicon Labs bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef BTL_GPIO_ACTIVATION_H
#define BTL_GPIO_ACTIVATION_H

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup GpioActivation GPIO Activation
 * @brief Enter bootloader based on GPIO state.
 * @details
 * @{
 * @addtogroup ButtonGPIO Button GPIO
 * @brief Enter bootloader based on Button GPIO state.
 * @details
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Enter the bootlader if the GPIO pin is active.
 *
 * @return True if the bootloader should be entered
 ******************************************************************************/
bool gpio_enterBootloader(void);

/** @} (end addtogroup Button GPIO) */
/** @} (end addtogroup GpioActivation) */
/** @} (end addtogroup Plugin) */

#endif // BTL_GPIO_ACTIVATION_H
