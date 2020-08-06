/***************************************************************************//**
 * @file
 * @brief EFM32/EFR32 specific watchdog functions.
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
#ifndef WATCHDOG_H
#define WATCHDOG_H

/**
 * @brief This function should be called before going to EM2 or EM3. This will
 * make sure that the watchdog is in a safe state before the device enters
 * the sleep mode.
 */
void halInternalWatchDogSleep(void);

#endif
