/***************************************************************************//**
 * @file
 * @brief Default definition for COM queue sizes
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
#if !defined(COM_QUEUE_SIZE_H)
#define COM_QUEUE_SIZE_H

// --------------------------------
// HAL Config queue size defines

#if defined(HAL_USART0_RX_QUEUE_SIZE)
  #define COM_USART0_RX_QUEUE_SIZE HAL_USART0_RX_QUEUE_SIZE
#endif
#if defined (HAL_USART0_TX_QUEUE_SIZE)
  #define COM_USART0_TX_QUEUE_SIZE HAL_USART0_TX_QUEUE_SIZE
#endif
#if defined (HAL_USART1_RX_QUEUE_SIZE)
  #define COM_USART1_RX_QUEUE_SIZE HAL_USART1_RX_QUEUE_SIZE
#endif
#if defined (HAL_USART1_TX_QUEUE_SIZE)
  #define COM_USART1_TX_QUEUE_SIZE HAL_USART1_TX_QUEUE_SIZE
#endif
#if defined (HAL_USART2_RX_QUEUE_SIZE)
  #define COM_USART2_RX_QUEUE_SIZE HAL_USART2_RX_QUEUE_SIZE
#endif
#if defined (HAL_USART2_TX_QUEUE_SIZE)
  #define COM_USART2_TX_QUEUE_SIZE HAL_USART2_TX_QUEUE_SIZE
#endif
#if defined (HAL_USART3_RX_QUEUE_SIZE)
  #define COM_USART3_RX_QUEUE_SIZE HAL_USART3_RX_QUEUE_SIZE
#endif
#if defined (HAL_USART3_TX_QUEUE_SIZE)
  #define COM_USART3_TX_QUEUE_SIZE HAL_USART3_TX_QUEUE_SIZE
#endif
#if defined (HAL_LEUART0_RX_QUEUE_SIZE)
  #define COM_LEUART0_RX_QUEUE_SIZE HAL_LEUART0_RX_QUEUE_SIZE
#endif
#if defined (HAL_LEUART0_TX_QUEUE_SIZE)
  #define COM_LEUART0_TX_QUEUE_SIZE HAL_LEUART0_TX_QUEUE_SIZE
#endif
#if defined (HAL_LEUART1_RX_QUEUE_SIZE)
  #define COM_LEUART0_RX_QUEUE_SIZE HAL_LEUART1_RX_QUEUE_SIZE
#endif
#if defined (HAL_LEUART1_TX_QUEUE_SIZE)
  #define COM_LEUART0_TX_QUEUE_SIZE HAL_LEUART1_TX_QUEUE_SIZE
#endif

// --------------------------------
// Legacy queue size defines

#if defined(COM_0_RX_QUEUE_SIZE)
  #define COM_VCP_RX_QUEUE_SIZE COM_0_RX_QUEUE_SIZE
#endif

#if defined(COM_0_TX_QUEUE_SIZE)
  #define COM_VCP_TX_QUEUE_SIZE COM_0_TX_QUEUE_SIZE
#endif

#if defined(COM_1_RX_QUEUE_SIZE)
  #define COM_USART0_RX_QUEUE_SIZE COM_1_RX_QUEUE_SIZE
#endif

#if defined(COM_1_TX_QUEUE_SIZE)
  #define COM_USART0_TX_QUEUE_SIZE COM_1_TX_QUEUE_SIZE
#endif

#if defined(COM_2_RX_QUEUE_SIZE)
  #define COM_USART1_RX_QUEUE_SIZE COM_2_RX_QUEUE_SIZE
#endif

#if defined(COM_2_TX_QUEUE_SIZE)
  #define COM_USART1_TX_QUEUE_SIZE COM_2_TX_QUEUE_SIZE
#endif

#if defined(COM_3_RX_QUEUE_SIZE)
  #define COM_USB_RX_QUEUE_SIZE COM_3_RX_QUEUE_SIZE
#endif

#if defined(COM_3_TX_QUEUE_SIZE)
  #define COM_USB_TX_QUEUE_SIZE COM_3_TX_QUEUE_SIZE
#endif

#if defined(COM_4_RX_QUEUE_SIZE)
  #define COM_LEUART0_RX_QUEUE_SIZE COM_4_RX_QUEUE_SIZE
#endif

#if defined(COM_4_TX_QUEUE_SIZE)
  #define COM_LEUART0_TX_QUEUE_SIZE COM_4_TX_QUEUE_SIZE
#endif

#if defined(COM_5_RX_QUEUE_SIZE)
  #define COM_LEUART1_RX_QUEUE_SIZE COM_5_RX_QUEUE_SIZE
#endif

#if defined(COM_5_TX_QUEUE_SIZE)
  #define COM_LEUART1_TX_QUEUE_SIZE COM_5_TX_QUEUE_SIZE
#endif

// --------------------------------
// Default queue sizes

#if !defined(COM_VCP_RX_QUEUE_SIZE)
  #define COM_VCP_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_VCP_TX_QUEUE_SIZE)
  #define COM_VCP_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_USART0_RX_QUEUE_SIZE)
  #define COM_USART0_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_USART0_TX_QUEUE_SIZE)
  #define COM_USART0_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_USART1_RX_QUEUE_SIZE)
  #define COM_USART1_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_USART1_TX_QUEUE_SIZE)
  #define COM_USART1_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_USART2_RX_QUEUE_SIZE)
  #define COM_USART2_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_USART2_TX_QUEUE_SIZE)
  #define COM_USART2_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_USART3_RX_QUEUE_SIZE)
  #define COM_USART3_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_USART3_TX_QUEUE_SIZE)
  #define COM_USART3_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_USB_RX_QUEUE_SIZE)
  #define COM_USB_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_USB_TX_QUEUE_SIZE)
  #define COM_USB_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_LEUART0_RX_QUEUE_SIZE)
  #define COM_LEUART0_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_LEUART0_TX_QUEUE_SIZE)
  #define COM_LEUART0_TX_QUEUE_SIZE 128
#endif

#if !defined(COM_LEUART1_RX_QUEUE_SIZE)
  #define COM_LEUART1_RX_QUEUE_SIZE 64
#endif

#if !defined(COM_LEUART1_TX_QUEUE_SIZE)
  #define COM_LEUART1_TX_QUEUE_SIZE 128
#endif

#endif // COM_QUEUE_SIZE_H
