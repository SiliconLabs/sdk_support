/***************************************************************************//**
 * @file
 * @brief @ref host and @ref stm32f103ret_host for documentation.
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
/** @addtogroup stm32f103ret_host
 * @brief HAL functions specific to this micro.
 *
 * See @ref host for common documentation.
 *
 * The definitions in the micro specific header provide the necessary
 * pieces to link the common functionality to a specific micro.
 *
 * See micro-specific.h for source code.
 *@{
 */

#ifndef __MICRO_SPECIFIC_H__
#define __MICRO_SPECIFIC_H__

/** @brief The number of ticks specific to this host (as returned from
 * ::halCommonGetInt32uMillisecondTick) that represent an actual
 * second.
 */
#define MILLISECOND_TICKS_PER_SECOND 1024UL

/** @brief A name given to a reset event. The name is derived from the
 * datasheet and the value is the index into the resetString structure.
 *@{
 */
#define RESET_UNKNOWN                0
#define RESET_LOW_POWER              1
#define RESET_WINDOW_WATCHDOG        2
#define RESET_INDEPENDENT_WATCHDOG   3
#define RESET_SOFTWARE               4
#define RESET_POR_PDR                5
#define RESET_PIN                    6
#define RESET_UNSET                255

/**@}*/

/** @brief Initialize the SysTick timer to provide a microsecond time
 * base for use by halCommonDelayMicroseconds().
 */
void halInternalInitSysTick(void);

#endif //__MICRO_SPECIFIC_H__

/**@}END addtogroup
 */
