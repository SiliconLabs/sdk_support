/***************************************************************************//**
 * @file
 * @brief Serial hardware abstraction layer interfaces.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SERIAL_H
#define SERIAL_H

#include <stdarg.h>
#include "em_usart.h"

#ifndef DEFINE_BAUD
#define DEFINE_BAUD(num) BAUD_##num
#endif
typedef uint32_t SerialBaudRate;
enum {
  DEFINE_BAUD(300) = 300,  // BAUD_300
  DEFINE_BAUD(600) = 600,  // BAUD_600
  DEFINE_BAUD(900) = 900,  // etc...
  DEFINE_BAUD(1200) = 1200,
  DEFINE_BAUD(2400) = 2400,
  DEFINE_BAUD(4800) = 4800,
  DEFINE_BAUD(9600) = 9600,
  DEFINE_BAUD(14400) = 14400,
  DEFINE_BAUD(19200) = 19200,
  DEFINE_BAUD(28800) = 28800,
  DEFINE_BAUD(38400) = 38400,
  DEFINE_BAUD(50000) = 50000,
  DEFINE_BAUD(57600) = 57600,
  DEFINE_BAUD(76800) = 76800,
  DEFINE_BAUD(100000) = 100000,
  DEFINE_BAUD(115200) = 115200
};

typedef USART_Parity_TypeDef SerialParity;
#define PARITY_NONE usartNoParity
#define PARITY_ODD  usartOddParity
#define PARITY_EVEN usartEvenParity

EmberStatus emberSerialInit(uint8_t port,
                            SerialBaudRate rate,
                            SerialParity parity,
                            uint8_t stopBits);

EmberStatus emberSerialReadByte(uint8_t port, uint8_t *dataByte);

EmberStatus emberSerialReadData(uint8_t port,
                                uint8_t *data,
                                uint16_t length,
                                uint16_t *bytesRead);

EmberStatus emberSerialPrintf(uint8_t port, const char * formatString, ...);

EmberStatus emberSerialPrintfLine(uint8_t port, const char * formatString, ...);

EmberStatus emberSerialPrintCarriageReturn(uint8_t port);

EmberStatus emberSerialPrintfVarArg(uint8_t port, const char * formatString, va_list ap);

EmberStatus emberSerialWaitSend(uint8_t port);

EmberStatus emberSerialGuaranteedPrintf(uint8_t port, const char * formatString, ...);

#endif // SERIAL_H
