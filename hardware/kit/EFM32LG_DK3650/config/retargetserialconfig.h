/***************************************************************************//**
 * @file
 * @brief Provide stdio retargeting configuration parameters.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef __RETARGETSERIALCONFIG_H
#define __RETARGETSERIALCONFIG_H

#include "bsp.h"

/* Override if needed with commandline parameter -DRETARGET_xxx */

#if !defined(RETARGET_UART1) && !defined(RETARGET_LEUART1)
#define RETARGET_UART1    /* Use UART1 by default. */
#endif

#if defined(RETARGET_UART1)
  #define RETARGET_IRQ_NAME    UART1_RX_IRQHandler          /* UART IRQ Handler */
  #define RETARGET_CLK         cmuClock_UART1               /* HFPER Clock */
  #define RETARGET_IRQn        UART1_RX_IRQn                /* IRQ number */
  #define RETARGET_UART        UART1                        /* UART instance */
  #define RETARGET_TX          USART_Tx                     /* Set TX to USART_Tx */
  #define RETARGET_RX          USART_Rx                     /* Set RX to USART_Rx */
  #define RETARGET_LOCATION    USART_ROUTE_LOCATION_LOC2    /* Location of of the USART I/O pins */
  #define RETARGET_TXPORT      gpioPortB                    /* UART transmission port */
  #define RETARGET_TXPIN       9                            /* UART transmission pin */
  #define RETARGET_RXPORT      gpioPortB                    /* UART reception port */
  #define RETARGET_RXPIN       10                           /* UART reception pin */
  #define RETARGET_USART       1                            /* Includes em_usart.h */
  #define RETARGET_PERIPHERAL_ENABLE()  BSP_PeripheralAccess(BSP_RS232_UART, true)

#elif defined(RETARGET_LEUART1)
  #define RETARGET_IRQ_NAME    LEUART1_IRQHandler           /* LEUART IRQ Handler */
  #define RETARGET_CLK         cmuClock_LEUART1             /* LFB Clock */
  #define RETARGET_IRQn        LEUART1_IRQn                 /* IRQ number */
  #define RETARGET_UART        LEUART1                      /* LEUART instance */
  #define RETARGET_TX          LEUART_Tx                    /* Set TX to LEUART_Tx */
  #define RETARGET_RX          LEUART_Rx                    /* Set RX to LEUART_Rx */
  #define RETARGET_TXPORT      gpioPortC                    /* LEUART transmission port */
  #define RETARGET_TXPIN       6                            /* LEUART transmission pin */
  #define RETARGET_RXPORT      gpioPortC                    /* LEUART reception port */
  #define RETARGET_RXPIN       7                            /* LEUART reception pin */
  #define RETARGET_LOCATION    LEUART_ROUTE_LOCATION_LOC0   /* Location of of the LEUART I/O pins */
  #define RETARGET_LEUART      1                            /* Includes em_leuart.h */
  #define RETARGET_PERIPHERAL_ENABLE()  BSP_PeripheralAccess(BSP_RS232_LEUART, true)

#else
#error "Illegal UART/LEUART selection."
#endif

#endif
