/***************************************************************************//**
 * @file
 * @brief  Sample API functions for using a timer to play tunes on a buzzer.
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
#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "hal/hal.h"

bool tuneDone = true;

void halPlayTune_P(uint8_t PGM *tune, bool bkg)
{
}

void halTimer1Isr(void)
{
}

void halStackIndicatePresence(void)
{
}
