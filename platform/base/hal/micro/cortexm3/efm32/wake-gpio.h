/***************************************************************************//**
 * @file
 * @brief
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
#ifndef WAKE_GPIO_H
#define WAKE_GPIO_H

// create some handy macros for referring to whole ports
// A monolithic constant for all GPIO wake sources
#define EMBER_WAKE_GPIO_BITMASK_ARRAY { \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
}

// TODO: Extend for Jumbo, which will have 12 ports

#endif // WAKE_GPIO_H
