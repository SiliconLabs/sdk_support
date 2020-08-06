/***************************************************************************//**
 * @file
 * @brief Bootloader serial interface functions for a uart
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
#include PLATFORM_HEADER  // should be iar.h
#include "bootloader-common.h"
#include "bootloader-serial.h"
#include "stack/include/ember-types.h"
#include "hal.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#if HAL_SERIAL_VCOM_ENABLE
#if BSP_VCOM_USART == HAL_SERIAL_PORT_USART0
  #ifdef _USART_ROUTELOC0_MASK
    #define BSP_USART0_RX_LOC      BSP_VCOM_RX_LOC
    #define BSP_USART0_TX_LOC      BSP_VCOM_TX_LOC
  #else
    #define BSP_USART0_ROUTE_LOC   BSP_VCOM_ROUTE_LOC
  #endif
#define BSP_USART0_RX_PIN      BSP_VCOM_RX_PIN
#define BSP_USART0_RX_PORT     BSP_VCOM_RX_PORT
#define BSP_USART0_TX_PIN      BSP_VCOM_TX_PIN
#define BSP_USART0_TX_PORT     BSP_VCOM_TX_PORT
#endif
#endif
#if ((BSP_SERIAL_APP_PORT == 1) || (BSP_SERIAL_APP_PORT == 0x20))
  #define BTL_UART USART0
  #define BTL_UART_CLK cmuClock_USART0
#else
  #error UART bootloader must select USART0 as BSP_SERIAL_APP_PORT
#endif

// Function Name: serInit
// Description:   This function configures the UART. These are default
//                settings and can be modified for custom applications.
// Parameters:    none
// Returns:       none
//
bool initState;
void serInit(void)
{
  if (initState) {
    return;
  }

  /* Configure GPIO pins */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* To avoid false start, configure output as high */
  GPIO_PinModeSet(BSP_USART0_TX_PORT, BSP_USART0_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(BSP_USART0_RX_PORT, BSP_USART0_RX_PIN, gpioModeInput, 0);

  USART_TypeDef           *usart = BTL_UART;
  USART_InitAsync_TypeDef init   = USART_INITASYNC_DEFAULT;

  /* Enable peripheral clocks */
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(BTL_UART_CLK, true);

  /* Configure USART for basic async operation */
  init.enable = usartDisable;
  USART_InitAsync(usart, &init);

  /* Enable pins at correct UART/USART location. */
  #if defined(USART_ROUTEPEN_RXPEN)
  usart->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
  usart->ROUTELOC0 = (usart->ROUTELOC0
                      & ~(_USART_ROUTELOC0_TXLOC_MASK
                          | _USART_ROUTELOC0_RXLOC_MASK) )
                     | (BSP_USART0_TX_LOC << _USART_ROUTELOC0_TXLOC_SHIFT)
                     | (BSP_USART0_RX_LOC << _USART_ROUTELOC0_RXLOC_SHIFT);
  #else
  usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | BSP_USART0_ROUTE_LOC;
  #endif

  /* Finally enable it */
  USART_Enable(usart, usartEnable);

  #if (defined(HAL_SERIAL_VCOM_ENABLE) && !defined(ENABLE_EXP_UART))
  // Don't add IOEXP BSP init code to bootloader to minimize size
  #if !BSP_VCOM_IOEXP_ENABLE
  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT, BSP_VCOM_ENABLE_PIN, gpioModePushPull, 1);
  #endif
  #endif
  initState = true;
}

void serPutFlush(void)
{
#ifdef _USART_STATUS_TXIDLE_MASK

  /*wait for txidle*/
  while ( !(USART_StatusGet(BTL_UART) & _USART_STATUS_TXIDLE_MASK)) ;
#else

  /*wait for tx buffer to clear*/
  while ((USART_StatusGet(BTL_UART) & _USART_STATUS_TXBL_SHIFT)) ;
#endif
}

// wait for transmit free then send char
void serPutChar(uint8_t ch)
{
  USART_Tx(BTL_UART, ch);
}

void serPutStr(const char *str)
{
  while (*str) {
    serPutChar(*str);
    str++;
  }
}

void serPutBuf(const uint8_t buf[], uint8_t size)
{
  uint16_t i;

  for (i = 0; i < size; i++) {
    serPutChar(buf[i]);
  }
}

void serPutDecimal(uint16_t val)
{
  char outStr[] = { '0', '0', '0', '0', '0', '\0' };
  int8_t i = sizeof(outStr) / sizeof(char) - 1;
  uint8_t remainder, lastDigit = i - 1;

  // Convert the integer into a string.
  while (--i >= 0) {
    remainder = val % 10;
    val /= 10;
    outStr[i] = remainder + '0';
    if (remainder != 0) {
      lastDigit = i;
    }
  }

  // Print the final string
  serPutStr(outStr + lastDigit);
}

void serPutHex(uint8_t byte)
{
  uint8_t val;
  val = ((byte & 0xF0) >> 4);
  serPutChar((val > 9) ? (val - 10 + 'A') : (val + '0'));
  val = (byte & 0x0F);
  serPutChar((val > 9) ? (val - 10 + 'A') : (val + '0'));
}

void serPutHexInt(uint16_t word)
{
  serPutHex(HIGH_BYTE(word));
  serPutHex(LOW_BYTE(word));
}

bool serCharAvailable(void)
{
  if (USART_StatusGet(BTL_UART) & _USART_STATUS_RXDATAV_MASK) {
    return true;
  } else {
    return false;
  }
}

// get char if available, else return error
BL_Status serGetChar(uint8_t* ch)
{
  if (serCharAvailable()) {
    *ch = USART_Rx(BTL_UART);
    return BL_SUCCESS;
  } else {
    return BL_ERR;
  }
}

// get chars until rx buffer is empty
void serGetFlush(void)
{
  uint8_t status = BL_SUCCESS;
  uint8_t tmp;
  do {
    status = serGetChar(&tmp);
  } while (status == BL_SUCCESS);
}
