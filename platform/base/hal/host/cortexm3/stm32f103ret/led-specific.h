/***************************************************************************//**
 * @file
 * @brief See @ref led and @ref stm32f103ret_led for documentation.
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
/** @addtogroup stm32f103ret_led
 * @brief  Sample micro specific API funtions and defines for controlling LEDs.
 *
 * See @ref led for common documentation.
 *
 * The definitions in the micro specific header provide the necessary
 * pieces to link the common functionality to a specific micro.
 *
 * See led-specific.h for source code.
 *@{
 */

#ifndef __LED_SPECIFIC_H__
#define __LED_SPECIFIC_H__

/**
 * @brief Assign each LED to a convenient name that is a simple identifier.
 * BOARD_ACTIVITY_LED and BOARD_HEARTBEAT_LED provide a further layer of
 * abstraction ontop of the LEDs for verbose coding.
 */
enum HalBoardLedPins {
  BOARDLED0 = 0, //Just a simple identifier for switch statements
  BOARDLED1 = 1, //Just a simple identifier for switch statements
  BOARD_ACTIVITY_LED  = BOARDLED0,
  BOARD_HEARTBEAT_LED = BOARDLED1
};

/**
 * @brief The actual pin that BOARDLED0 is connected to.
 */
#define BOARDLED0_PIN   GPIO_Pin_8

/**
 * @brief The actual port that BOARDLED0 is connected to.
 */
#define BOARDLED0_PORT  GPIOB

/**
 * @brief The actual pin that BOARDLE1 is connected to.
 */
#define BOARDLED1_PIN   GPIO_Pin_9

/**
 * @brief The actual port that BOARDLED1 is connected to.
 */
#define BOARDLED1_PORT  GPIOB

#endif //__LED_SPECIFIC_H__

/**@}END addtogroup
 */
