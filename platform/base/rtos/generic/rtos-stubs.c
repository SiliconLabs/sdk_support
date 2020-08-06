/***************************************************************************//**
 * @file
 * @brief This file implements functions required by the RTOS that are
 * expected to be replaced with customer specific versions. In a final
 * customer application this should be removed and replaced with your
 * own version.
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
// Declaration for the standard watch dog API
void halInternalResetWatchDog(void);

// Simple watchdog reset that just calls the regular HAL function. Most
// people will want to implement a more thread aware watchdog that makes
// sure all threads are running and checking in and not just one thread
// constantly resetting the watchdog.
void rtosResetWatchdog(void)
{
  halInternalResetWatchDog();
}
