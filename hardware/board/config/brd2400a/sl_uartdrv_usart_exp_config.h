/***************************************************************************//**
 * @file
 * @brief UARTDRV_USART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_UARTDRV_USART_EXP_CONFIG_H
#define SL_UARTDRV_USART_EXP_CONFIG_H

#include "em_usart.h"
// <<< Use Configuration Wizard in Context Menu >>>

// <h> UART settings
// <o SL_UARTDRV_USART_EXP_BAUDRATE> Baud rate
// <i> Default: 115200
#define SL_UARTDRV_USART_EXP_BAUDRATE        115200

// <o SL_UARTDRV_USART_EXP_PARITY> Parity mode to use
// <usartNoParity=> No Parity
// <usartEvenParity=> Even parity
// <usartOddParity=> Odd parity
// <i> Default: usartNoParity
#define SL_UARTDRV_USART_EXP_PARITY          usartNoParity

// <o SL_UARTDRV_USART_EXP_STOP_BITS> Number of stop bits to use.
// <usartStopbits0p5=> 0.5 stop bits
// <usartStopbits1=> 1 stop bits
// <usartStopbits1p5=> 1.5 stop bits
// <usartStopbits2=> 2 stop bits
// <i> Default: usartStopbits1
#define SL_UARTDRV_USART_EXP_STOP_BITS       usartStopbits1

// <o SL_UARTDRV_USART_EXP_FLOW_CONTROL_TYPE> Flow control method
// <uartdrvFlowControlNone=> None
// <uartdrvFlowControlSw=> Software XON/XOFF
// <uartdrvFlowControlHw=> nRTS/nCTS hardware handshake
// <i> Default: uartdrvFlowControlHw
#define SL_UARTDRV_USART_EXP_FLOW_CONTROL_TYPE uartdrvFlowControlNone

// <o SL_UARTDRV_USART_EXP_OVERSAMPLING> Oversampling selection
// <usartOVS16=> 16x oversampling
// <usartOVS8=> 8x oversampling
// <usartOVS6=> 6x oversampling
// <usartOVS4=> 4x oversampling
// <i> Default: usartOVS16
#define SL_UARTDRV_USART_EXP_OVERSAMPLING      usartOVS4

// <o SL_UARTDRV_USART_EXP_MVDIS> Majority vote disable for 16x, 8x and 6x oversampling modes
// <true=> True
// <false=> False
#define SL_UARTDRV_USART_EXP_MVDIS             false

// <o SL_UARTDRV_USART_EXP_RX_BUFFER_SIZE> Size of the receive operation queue
// <i> Default: 6
#define SL_UARTDRV_USART_EXP_RX_BUFFER_SIZE  6

// <o SL_UARTDRV_USART_EXP_TX_BUFFER_SIZE> Size of the transmit operation queue
// <i> Default: 6
#define SL_UARTDRV_USART_EXP_TX_BUFFER_SIZE 6
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX> SL_UARTDRV_USART_EXP
// $[USART_SL_UARTDRV_USART_EXP]
#define SL_UARTDRV_USART_EXP_PERIPHERAL          USART1
#define SL_UARTDRV_USART_EXP_PERIPHERAL_NO       1

// USART1 TX on PD0
#define SL_UARTDRV_USART_EXP_TX_PORT             gpioPortD
#define SL_UARTDRV_USART_EXP_TX_PIN              0
#define SL_UARTDRV_USART_EXP_ROUTE_LOC           1

// USART1 RX on PD1
#define SL_UARTDRV_USART_EXP_RX_PORT             gpioPortD
#define SL_UARTDRV_USART_EXP_RX_PIN              1

// [USART_SL_UARTDRV_USART_EXP]$
// <gpio> SL_UARTDRV_USART_EXP_CTS
// $[GPIO_SL_UARTDRV_USART_EXP_CTS]

// [GPIO_SL_UARTDRV_USART_EXP_CTS]$

// <gpio> SL_UARTDRV_USART_EXP_RTS
// $[GPIO_SL_UARTDRV_USART_EXP_RTS]

// [GPIO_SL_UARTDRV_USART_EXP_RTS]$
// <<< sl:end pin_tool >>>
#endif // SL_UARTDRV_USART_EXP_CONFIG_H
