/***************************************************************************//**
 * @file
 * @brief Device specific COM settings.
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
#ifndef __COM_DEVICE_H__
#define __COM_DEVICE_H__

// Toggle COM ports to optimize code size
#if HAL_SERIAL_USART0_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART0) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART0)
#define COM_USART0_ENABLE
#endif
#if HAL_SERIAL_USART1_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART1) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART1)
#define COM_USART1_ENABLE
#endif
#if HAL_SERIAL_USART2_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART2) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART2)
#define COM_USART2_ENABLE
#endif
#if HAL_SERIAL_USART3_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART3) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART3)
#define COM_USART3_ENABLE
#endif
#if HAL_SERIAL_LEUART0_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_LEUART0) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_LEUART0)
#define COM_LEUART0_ENABLE
#endif
#if HAL_SERIAL_LEUART1_ENABLE                            \
  || (BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_LEUART1) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_LEUART1)
#define COM_LEUART1_ENABLE
#endif
#if HAL_SERIAL_VUART_ENABLE
#define COM_VCP_ENABLE
#endif

// Define the number of com ports. This should never change
#define COM_PORTS 5
#define COM_UART_PORTS 4
#define COM_USB_PORTS 0
#define COM_VCP_PORTS 1

#if (COM_UART_PORTS + COM_USB_PORTS + COM_VCP_PORTS) != COM_PORTS
  #error COM ports not defined properly
#endif

#endif //__COM_DEVICE_H__
