/***************************************************************************//**
 * @file
 * @brief UART NCP Config Header
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
#ifndef NCP_UART_CONFIG_H
#define NCP_UART_CONFIG_H

#ifdef CORTEXM3_EFM32_MICRO
  #include "serial/com.h"
  #define UART_PORT ((COM_Port_t) BSP_UARTNCP_USART_PORT)
  #if (BSP_UARTNCP_USART_PORT >= HAL_SERIAL_PORT_USART0) \
  && (BSP_UARTNCP_USART_PORT <= HAL_SERIAL_PORT_USART5)

// Select USART
    #if BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART0
      #define NCP_USART       USART0
      #define NCP_USART_NUM   0
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART1
      #define NCP_USART       USART1
      #define NCP_USART_NUM   1
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART2
      #define NCP_USART       USART2
      #define NCP_USART_NUM   2
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART3
      #define NCP_USART       USART3
      #define NCP_USART_NUM   3
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART4
      #define NCP_USART       USART4
      #define NCP_USART_NUM   4
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_USART5
      #define NCP_USART       USART5
      #define NCP_USART_NUM   5
    #endif

// Define null flow control pins if HW flow control is not specified to
// prevent compiler errors
    #if (HAL_UARTNCP_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_UARTNCP_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
      #undef BSP_UARTNCP_CTS_PORT
      #undef BSP_UARTNCP_CTS_PIN
      #undef BSP_UARTNCP_RTS_PORT
      #undef BSP_UARTNCP_RTS_PIN
      #undef BSP_UARTNCP_CTS_LOC
      #undef BSP_UARTNCP_RTS_LOC
      #define BSP_UARTNCP_CTS_PORT gpioPortA
      #define BSP_UARTNCP_CTS_PIN  0
      #define BSP_UARTNCP_RTS_PORT gpioPortA
      #define BSP_UARTNCP_RTS_PIN  0
      #define BSP_UARTNCP_CTS_LOC  0
      #define BSP_UARTNCP_RTS_LOC  0
    #endif

    #if defined(_USART_ROUTELOC0_MASK)
    #define USART_INIT                                                                                         \
  {                                                                                                            \
    NCP_USART,                                                              /* USART port                   */ \
    HAL_UARTNCP_BAUD_RATE,                                                  /* Baud rate                    */ \
    BSP_UARTNCP_TX_LOC,                                                     /* USART Tx pin location number */ \
    BSP_UARTNCP_RX_LOC,                                                     /* USART Rx pin location number */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                       /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                          /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                  /* Oversampling mode            */ \
    false,                                                                  /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_UARTNCP_FLOW_CONTROL,                    /* Flow control                 */ \
    BSP_UARTNCP_CTS_PORT,                                                   /* CTS port number              */ \
    BSP_UARTNCP_CTS_PIN,                                                    /* CTS pin number               */ \
    BSP_UARTNCP_RTS_PORT,                                                   /* RTS port number              */ \
    BSP_UARTNCP_RTS_PIN,                                                    /* RTS pin number               */ \
    NULL,                                                                   /* RX operation queue           */ \
    NULL,                                                                   /* TX operation queue           */ \
    BSP_UARTNCP_CTS_LOC,                                                    /* CTS pin location             */ \
    BSP_UARTNCP_RTS_LOC                                                     /* RTS pin location             */ \
  }
    #elif defined(_GPIO_USART_ROUTEEN_MASK)
    #define USART_INIT                                                                                         \
  {                                                                                                            \
    NCP_USART,                                                              /* USART port                   */ \
    HAL_UARTNCP_BAUD_RATE,                                                  /* Baud rate                    */ \
    BSP_UARTNCP_TX_PORT,                                                    /* TX port number               */ \
    BSP_UARTNCP_RX_PORT,                                                    /* RX port number               */ \
    BSP_UARTNCP_TX_PIN,                                                     /* TX pin number                */ \
    BSP_UARTNCP_RX_PIN,                                                     /* RX pin number                */ \
    NCP_USART_NUM,                                                          /* UART instance number         */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                       /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                          /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                  /* Oversampling mode            */ \
    false,                                                                  /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_UARTNCP_FLOW_CONTROL,                    /* Flow control                 */ \
    BSP_UARTNCP_CTS_PORT,                                                   /* CTS port number              */ \
    BSP_UARTNCP_CTS_PIN,                                                    /* CTS pin number               */ \
    BSP_UARTNCP_RTS_PORT,                                                   /* RTS port number              */ \
    BSP_UARTNCP_RTS_PIN,                                                    /* RTS pin number               */ \
    NULL,                                                                   /* RX operation queue           */ \
    NULL,                                                                   /* TX operation queue           */ \
  }
    #else //defined( _USART_ROUTELOC0_MASK )
    #define USART_INIT                                                                                         \
  {                                                                                                            \
    NCP_USART,                                                              /* USART port                   */ \
    HAL_UARTNCP_BAUD_RATE,                                                  /* Baud rate                    */ \
    BSP_UARTNCP_ROUTE_LOC,                                                  /* USART pins location number   */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                       /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                          /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                  /* Oversampling mode            */ \
    (UARTDRV_FlowControlType_t)HAL_UARTNCP_FLOW_CONTROL,                    /* Flow control                 */ \
    BSP_UARTNCP_CTS_PORT,                                                   /* CTS port number              */ \
    BSP_UARTNCP_CTS_PIN,                                                    /* CTS pin number               */ \
    BSP_UARTNCP_RTS_PORT,                                                   /* RTS port number              */ \
    BSP_UARTNCP_RTS_PIN,                                                    /* RTS pin number               */ \
    NULL,                                                                   /* RX operation queue           */ \
    NULL                                                                    /* TX operation queue           */ \
  }
    #endif //defined( _USART_ROUTELOC0_MASK )

    #define NCP_COM_INIT                                                         \
  {                                                                              \
    (UARTDRV_Init_t) USART_INIT,                     /* USART initdata        */ \
    HAL_UARTNCP_RXSTOP,                              /* RX stop threshold     */ \
    HAL_UARTNCP_RXSTART                              /* RX start threshold    */ \
  }
  #elif (BSP_UARTNCP_USART_PORT >= HAL_SERIAL_PORT_LEUART0) \
  && (BSP_UARTNCP_USART_PORT <= HAL_SERIAL_PORT_LEUART1)

// Select LEUART
    #if BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_LEUART0
      #define NCP_LEUART LEUART0
    #elif BSP_UARTNCP_USART_PORT == HAL_SERIAL_PORT_LEUART1
      #define NCP_LEUART LEUART1
    #endif

// Define null flow control pins if HW flow control is not specified to
// prevent compiler errors
    #if (HAL_UARTNCP_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_UARTNCP_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
      #undef BSP_UARTNCP_CTS_PORT
      #undef BSP_UARTNCP_CTS_PIN
      #undef BSP_UARTNCP_RTS_PORT
      #undef BSP_UARTNCP_RTS_PIN
      #undef BSP_UARTNCP_CTS_LOC
      #undef BSP_UARTNCP_RTS_LOC
      #define BSP_UARTNCP_CTS_PORT gpioPortA
      #define BSP_UARTNCP_CTS_PIN  0
      #define BSP_UARTNCP_RTS_PORT gpioPortA
      #define BSP_UARTNCP_RTS_PIN  0
      #define BSP_UARTNCP_CTS_LOC  0
      #define BSP_UARTNCP_RTS_LOC  0
    #endif

    #ifdef _LEUART_ROUTELOC0_MASK
      #define LEUART_INIT                                                                                        \
  {                                                                                                              \
    NCP_LEUART,                                                               /* LEUART port                  */ \
    HAL_UARTNCP_BAUD_RATE,                                                    /* Baud rate                    */ \
    BSP_UARTNCP_TX_LOC,                                                       /* LEUART TX location number    */ \
    BSP_UARTNCP_RX_LOC,                                                       /* LEUART TX location number    */ \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                        /* Stop bits                    */ \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                           /* Parity                       */ \
    (UARTDRV_FlowControlType_t)HAL_UARTNCP_FLOW_CONTROL,                      /* Flow control                 */ \
    BSP_UARTNCP_CTS_PORT,                                                     /* CTS port number              */ \
    BSP_UARTNCP_CTS_PIN,                                                      /* CTS pin number               */ \
    BSP_UARTNCP_RTS_PORT,                                                     /* RTS port number              */ \
    BSP_UARTNCP_RTS_PIN,                                                      /* RTS pin number               */ \
    NULL,                                                                     /* RX operation queue           */ \
    NULL                                                                      /* TX operation queue           */ \
  }
    #else // _LEUART_ROUTELOC0_MASK
      #define LEUART_INIT                                                                                         \
  {                                                                                                               \
    NCP_LEUART,                                                               /* LEUART port                   */ \
    HAL_UARTNCP_BAUD_RATE,                                                    /* Baud rate                    */  \
    BSP_UARTNCP_ROUTE_LOC,                                                    /* LEUART location number       */  \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                        /* Stop bits                    */  \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                           /* Parity                       */  \
    (UARTDRV_FlowControlType_t)HAL_UARTNCP_FLOW_CONTROL,                      /* Flow control                 */  \
    BSP_UARTNCP_CTS_PORT,                                                     /* CTS port number              */  \
    BSP_UARTNCP_CTS_PIN,                                                      /* CTS pin number               */  \
    BSP_UARTNCP_RTS_PORT,                                                     /* RTS port number              */  \
    BSP_UARTNCP_RTS_PIN,                                                      /* RTS pin number               */  \
    NULL,                                                                     /* RX operation queue           */  \
    NULL                                                                      /* TX operation queue           */  \
  }
    #endif // _LEUART_ROUTELOC0_MASK
    #define NCP_COM_INIT                                                          \
  {                                                                               \
    { .leuartinit = LEUART_INIT },                    /* LEUART initdata       */ \
    HAL_UARTNCP_RXSTOP,                               /* RX stop threshold     */ \
    HAL_UARTNCP_RXSTART                               /* RX start threshold    */ \
  }
  #else
    #error Only USART and LEUART supported for UART NCP
  #endif
#endif
#endif //NCP_UART_CONFIG_H
