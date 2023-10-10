/***************************************************************************/ /**
                                                                               * @file
                                                                               * @brief SL USART Config.
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

#ifndef SL_USART_CONFIG_H
#define SL_USART_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sl_si91x_usart.h"

// <<< Use Configuration Wizard in Context Menu >>>
// <h>USART Configuration

#define ENABLE 1
#define DISABLE 0

// <o SL_USART_BAUDRATE> Baud Rate (Baud/Second) <9600-7372800>
// <i> Default: 115200
#define SL_USART_BAUDRATE 115200

// <o SL_USART_MODE> Mode
// <SL_USART_MODE_ASYNCHRONOUS=> Asynchronous
// <SL_USART_MODE_SYNCHRONOUS_MASTER=> Synchronous Master
// <SL_USART_MODE_SYNCHRONOUS_SLAVE=> Synchronous
// <SL_USART_MODE_SINGLE_WIRE=> Single Wire
// <SL_USART_MODE_IRDA=> IRDA
// <i> Default: SL_USART_MODE_ASYNCHRONOUS
#define SL_USART_MODE SL_USART_MODE_ASYNCHRONOUS

// <o SL_USART_PARITY> Parity
// <SL_USART_NO_PARITY=> No Parity
// <SL_USART_EVEN_PARITY=> Even
// <SL_USART_ODD_PARITY=> Odd
// <i> Default: SL_USART_NO_PARITY
#define SL_USART_PARITY SL_USART_NO_PARITY

// <o SL_USART_STOP_BITS> Stop Bits
// <SL_USART_STOP_BITS_0_5=> 0.5
// <SL_USART_STOP_BITS_1=> 1
// <SL_USART_STOP_BITS_1_5=> 1.5
// <SL_USART_STOP_BITS_2=> 2
// <i> Default: USART_STOP_BITS_1
#define SL_USART_STOP_BITS SL_USART_STOP_BITS_1

// <o SL_USART_DATA_BITS> Data Width
// <SL_USART_DATA_BITS_5=> 5
// <SL_USART_DATA_BITS_6=> 6
// <SL_USART_DATA_BITS_7=> 7
// <SL_USART_DATA_BITS_8=> 8
// <SL_USART_DATA_BITS_9=> 9
// <i> Default: USART_DATA_BITS_8
#define SL_USART_DATA_BITS SL_USART_DATA_BITS_8

// <o SL_USART_FLOW_CONTROL_TYPE> Flow control
// <SL_USART_FLOW_CONTROL_NONE=> None
// <SL_USART_FLOW_CONTROL_CTS=> CTS
// <SL_USART_FLOW_CONTROL_RTS=> RTS
// <SL_USART_FLOW_CONTROL_RTS_CTS=> CTS/RTS
// <i> Default: USART_FLOW_CONTROL_NONE
#define SL_USART_FLOW_CONTROL_TYPE SL_USART_FLOW_CONTROL_NONE

#define USART0_MODULE 0
#define UART1_MODULE 1
#define ULP_UART_MODULE 2
// <o SL_USART_MODULE> Module
// <USART0_MODULE=> USART0 / UART0
// <UART1_MODULE=> UART1
// <ULP_UART_MODULE=> ULP_UART
// <i> Default: USART0
#define SL_USART_MODULE USART0_MODULE

// </h>
#ifdef __cplusplus
}
#endif
// <<< end of configuration section >>>

#if defined(SL_USART_MODULE)
sl_si91x_usart_control_config_t usart_configuration = {
    .baudrate = SL_USART_BAUDRATE,
    .mode = SL_USART_MODE,
    .parity = SL_USART_PARITY,
    .stopbits = SL_USART_STOP_BITS,
    .hwflowcontrol = SL_USART_FLOW_CONTROL_TYPE,
    .databits = SL_USART_DATA_BITS,
    .usart_module = SL_USART_MODULE};
#endif // SL_USART_MODULE

#endif // SL_USART_CONFIG_H
