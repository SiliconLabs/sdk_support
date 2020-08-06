/***************************************************************************//**
 * @file
 * @brief See @ref button and @ref stm32f103ret_button for documentation.
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
/** @addtogroup stm32f103ret_button
 * @brief  Sample micro specific API funtions and defines for using
 * push-buttons.
 *
 * See @ref button for common documentation.
 *
 * The definitions in the micro specific header provide the necessary
 * pieces to link the common functionality to a specific micro.
 *
 * See button-specific.h for source code.
 *@{
 */

#ifndef __BUTTON_SPECIFIC_H__
#define __BUTTON_SPECIFIC_H__

/** @brief Simple numerical definition of BUTTON0.
 */
#define BUTTON0                   0  //Just a simple identifier for comparisons

/** @brief The actual pin that BUTTON0 is connected to.
 */
#define BUTTON0_PIN               GPIO_Pin_10

/** @brief The actual port that BUTTON0 is connected to.
 */
#define BUTTON0_PORT              GPIOB

/** @brief The actual source port that BUTTON0 is connected to for external
 * interrupts.
 */
#define BUTTON0_EXTI_SOURCE_PORT  GPIO_PortSourceGPIOB

/** @brief The actual source pin that BUTTON0 is connected to for external
 * interrupts.
 */
#define BUTTON0_EXTI_SOURCE_PIN   GPIO_PinSource10

/** @brief The actual external interrupt IRQ number for BUTTON0.
 */
#define BUTTON0_IRQ               EXTI15_10_IRQn

/** @brief Simple numerical definition of BUTTON1.
 */
#define BUTTON1                   1  //Just a simple identifier for comparisons

/** @brief The actual pin that BUTTON1 is connected to.
 */
#define BUTTON1_PIN               GPIO_Pin_11

/** @brief The actual port that BUTTON1 is connected to.
 */
#define BUTTON1_PORT              GPIOB

/** @brief The actual source port that BUTTON1 is connected to for external
 * interrupts.
 */
#define BUTTON1_EXTI_SOURCE_PORT  GPIO_PortSourceGPIOB

/** @brief The actual source pin that BUTTON1 is connected to for external
 * interrupts.
 */
#define BUTTON1_EXTI_SOURCE_PIN   GPIO_PinSource11

/** @brief The actual external interrupt IRQ number for BUTTON1.
 */
#define BUTTON1_IRQ               EXTI15_10_IRQn

/** @brief The actual external interrupt ISR handler.  Due to the choice
 * of GPIO, BUTTON0 and BUTTON1 share the same ISR handler.
 */
#define BUTTON01_ISR              EXTI15_10_IRQHandler

#endif //__BUTTON_SPECIFIC_H__

/**@}END addtogroup
 */
