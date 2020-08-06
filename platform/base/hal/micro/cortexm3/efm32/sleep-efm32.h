/***************************************************************************//**
 * @file
 * @brief EFM32/EFR32 specific sleep functions.
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
#ifndef __SLEEP_EFM32_H__
#define __SLEEP_EFM32_H__

typedef struct {
  uint32_t gpioFlags;
} Em4WakeupCause_t;

/**
 * @brief This function should be called when waking up from EM4 to classify
 * the wakeup reason and also to clear the wakeup flags so that application
 * is able to enter EM4 again.
 */
void halInternalEm4Wakeup(void);

/**
 * @brief This function can be used to figure out why the device was woken up
 * from EM4.
 *
 * @return a pointer to the recorded wakeup cause
 */
const Em4WakeupCause_t * halInternalEm4WakeupCause(void);

#endif
