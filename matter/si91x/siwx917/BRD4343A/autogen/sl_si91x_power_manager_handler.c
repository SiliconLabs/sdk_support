/***************************************************************************//**
 * @file sl_si91x_power_manager_handler.c.jinja
 * @brief Power Manager Service Handler
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_si91x_power_manager.h"

/***************************************************************************//**
 * Check if the MCU can sleep at that time. This function is called when the system
 * is about to go sleeping, with the interrupts disabled. It allows the software to
 * cancel going to sleep in case of a last-minute event occurred (window between the
 * function call and interrupt disable).
 *
 * @return  True, if the system can go to sleep.
 *          False, otherwise.
 *
 * @note  This function is called with the interrupt disabled and it MUST NOT be
 *        re-enabled.
 ******************************************************************************/
__WEAK boolean_t app_is_ok_to_sleep(void)
{
  return true;
}

/***************************************************************************//**
 * Check if the MCU can sleep after an interrupt. This function is called after an
 * interrupt occured and was processed. It allows the power manger to know if it must
 * go back to sleep or wakeup.
 *
 * @return  SL_SI91X_POWER_MANAGER_IGNORE, if the module did not trigger an ISR and it
 *          won't to contribute to the decision.
 *
 *          SL_SI91X_POWER_MANAGER_SLEEP, The module was the one that caused the system
 *          wakeup and the system SHOULD go back to sleep.
 *
 *          SL_SI91X_POWER_MANAGER_WAKEUP, The module was the one that caused the system
 *          wakeup and the system MUST NOT go back to sleep.
 *
 * @note  This function must not have any side effects. It is not guaranteed to be
 *        called for every ISR. If a prior hook function requires to wakeup, such
 *        as a wireless stack, the application hook function won't be called.
 ******************************************************************************/
__WEAK sl_si91x_power_manager_on_isr_exit_t app_sleep_on_isr_exit(void)
{
  return SL_SI91X_POWER_MANAGER_ISR_IGNORE;
}
/***************************************************************************//**
 * Mandatory callback that must validate if the MCU can sleep after having
 * processed an interrupt when the system was sleeping.
 ******************************************************************************/
boolean_t sl_si91x_power_manager_sleep_on_isr_exit(void)
{
  sl_si91x_power_manager_on_isr_exit_t answer;
  boolean_t sleep = false;
  boolean_t force_wakeup = false;
   

  // Application hook
  answer = app_sleep_on_isr_exit();
  if (answer == SL_SI91X_POWER_MANAGER_ISR_WAKEUP) {
    force_wakeup = true;
  } else if (answer == SL_SI91X_POWER_MANAGER_ISR_SLEEP) {
    sleep = true;
  }
  
  if (force_wakeup) {
    sleep = false;
  }

  return sleep;
}
