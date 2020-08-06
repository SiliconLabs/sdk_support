/***************************************************************************//**
 * @file
 * @brief Default configuration for COM peripherals
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
#if !defined(COM_CONFIG_H)
#define COM_CONFIG_H

#if defined(COM_RETARGET_SERIAL)
  #include "retargetserialconfig.h"
#endif

/* Map serial app port settings*/
#ifdef BSP_SERIAL_APP_PORT
  #include "com_vcom.h"
#endif //BSP_SERIAL_APP_PORT

#define HAL_FC_NONE = 1
#define HAL_FC_HW = 2
#define HAL_FC_SW = 3

#ifdef COM_USART0_ENABLE
  #ifndef HAL_USART0_BAUD_RATE
    #define HAL_USART0_BAUD_RATE 115200
    #endif

  #if (HAL_USART0_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_USART0_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_USART0_CTS_PORT
    #undef BSP_USART0_CTS_PIN
    #undef BSP_USART0_RTS_PORT
    #undef BSP_USART0_RTS_PIN
    #undef BSP_USART0_CTS_LOC
    #undef BSP_USART0_RTS_LOC
    #define BSP_USART0_CTS_PORT gpioPortA
    #define BSP_USART0_CTS_PIN  0
    #define BSP_USART0_RTS_PORT gpioPortA
    #define BSP_USART0_RTS_PIN  0
    #define BSP_USART0_CTS_LOC  0
    #define BSP_USART0_RTS_LOC  0
  #endif

  #if defined(_USART_ROUTELOC0_MASK)
  #define USART0_INIT                                                                                        \
  {                                                                                                          \
    USART0,                                                               /* USART port                   */ \
    HAL_USART0_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART0_TX_LOC,                                                    /* USART Tx pin location number */ \
    BSP_USART0_RX_LOC,                                                    /* USART Rx pin location number */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART0_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART0_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART0_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART0_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART0_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
    BSP_USART0_CTS_LOC,                                                   /* CTS pin location             */ \
    BSP_USART0_RTS_LOC                                                    /* RTS pin location             */ \
  }
  #elif defined(_GPIO_USART_ROUTEEN_MASK) // #define USART0_INIT
  #define USART0_INIT                                                                                        \
  {                                                                                                          \
    USART0,                                                               /* USART port                   */ \
    HAL_USART0_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART0_TX_PORT,                                                   /* TX port number               */ \
    BSP_USART0_RX_PORT,                                                   /* RX port number               */ \
    BSP_USART0_TX_PIN,                                                    /* TX pin number                */ \
    BSP_USART0_RX_PIN,                                                    /* RX pin number                */ \
    0,                                                                    /* UART instance number         */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART0_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART0_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART0_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART0_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART0_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
  }
  #else
  #define USART0_INIT                                                                                        \
  {                                                                                                          \
    USART0,                                                               /* USART port                   */ \
    HAL_USART0_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART0_ROUTE_LOC,                                                 /* USART pins location number   */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    (UARTDRV_FlowControlType_t)HAL_USART0_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART0_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART0_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART0_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART0_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL                                                                  /* TX operation queue           */ \
  }
  #endif //defined( _USART_ROUTELOC0_MASK )

  #ifndef HAL_USART0_RXSTOP
    #define HAL_USART0_RXSTOP 16
  #endif
  #ifndef HAL_USART0_RXSTART
    #define HAL_USART0_RXSTART HAL_USART0_RXSTOP
  #endif

  #define COM_USART0_DEFAULT                                                   \
  {                                                                            \
    USART0_INIT,                                   /* USART initdata        */ \
    HAL_USART0_RXSTOP,                             /* RX stop threshold     */ \
    HAL_USART0_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_USART0_ENABLE
#ifdef COM_USART1_ENABLE
  #ifndef HAL_USART1_BAUD_RATE
    #define HAL_USART1_BAUD_RATE 115200
  #endif

  #if (HAL_USART1_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_USART1_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_USART1_CTS_PORT
    #undef BSP_USART1_CTS_PIN
    #undef BSP_USART1_RTS_PORT
    #undef BSP_USART1_RTS_PIN
    #undef BSP_USART1_CTS_LOC
    #undef BSP_USART1_RTS_LOC
    #define BSP_USART1_CTS_PORT gpioPortA
    #define BSP_USART1_CTS_PIN  0
    #define BSP_USART1_RTS_PORT gpioPortA
    #define BSP_USART1_RTS_PIN  0
    #define BSP_USART1_CTS_LOC  0
    #define BSP_USART1_RTS_LOC  0
  #endif

  #if defined(_USART_ROUTELOC0_MASK)
  #define USART1_INIT                                                                                        \
  {                                                                                                          \
    USART1,                                                               /* USART port                   */ \
    HAL_USART1_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART1_TX_LOC,                                                    /* USART Tx pin location number */ \
    BSP_USART1_RX_LOC,                                                    /* USART Rx pin location number */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART1_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART1_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART1_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART1_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART1_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
    BSP_USART1_CTS_LOC,                                                   /* CTS pin location             */ \
    BSP_USART1_RTS_LOC                                                    /* RTS pin location             */ \
  }
  #elif defined(_GPIO_USART_ROUTEEN_MASK)
  #define USART1_INIT                                                                                        \
  {                                                                                                          \
    USART1,                                                               /* USART port                   */ \
    HAL_USART1_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART1_TX_PORT,                                                   /* TX port number               */ \
    BSP_USART1_RX_PORT,                                                   /* RX port number               */ \
    BSP_USART1_TX_PIN,                                                    /* TX pin number                */ \
    BSP_USART1_RX_PIN,                                                    /* RX pin number                */ \
    1,                                                                    /* UART instance number         */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART1_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART1_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART1_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART1_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART1_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
  }
  #else //defined( _USART_ROUTELOC0_MASK )
  #define USART1_INIT                                                                                        \
  {                                                                                                          \
    USART1,                                                               /* USART port                   */ \
    HAL_USART1_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART1_ROUTE_LOC,                                                 /* USART pins location number   */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    (UARTDRV_FlowControlType_t)HAL_USART1_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART1_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART1_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART1_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART1_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL                                                                  /* TX operation queue           */ \
  }
  #endif //defined( _USART_ROUTELOC0_MASK )

  #ifndef HAL_USART1_RXSTOP
    #define HAL_USART1_RXSTOP 16
  #endif
  #ifndef HAL_USART1_RXSTART
    #define HAL_USART1_RXSTART HAL_USART1_RXSTOP
  #endif

  #define COM_USART1_DEFAULT                                                   \
  {                                                                            \
    (UARTDRV_Init_t) USART1_INIT,                  /* USART initdata        */ \
    HAL_USART1_RXSTOP,                             /* RX stop threshold     */ \
    HAL_USART1_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_USART1_ENABLE

#ifdef COM_USART2_ENABLE
  #ifndef HAL_USART2_BAUD_RATE
    #define HAL_USART2_BAUD_RATE 115200
  #endif

  #if (HAL_USART2_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_USART2_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_USART2_CTS_PORT
    #undef BSP_USART2_CTS_PIN
    #undef BSP_USART2_RTS_PORT
    #undef BSP_USART2_RTS_PIN
    #undef BSP_USART2_CTS_LOC
    #undef BSP_USART2_RTS_LOC
    #define BSP_USART2_CTS_PORT gpioPortA
    #define BSP_USART2_CTS_PIN  0
    #define BSP_USART2_RTS_PORT gpioPortA
    #define BSP_USART2_RTS_PIN  0
    #define BSP_USART2_CTS_LOC  0
    #define BSP_USART2_RTS_LOC  0
  #endif

  #if defined(_USART_ROUTELOC0_MASK)
  #define USART2_INIT                                                                                        \
  {                                                                                                          \
    USART2,                                                               /* USART port                   */ \
    HAL_USART2_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART2_TX_LOC,                                                    /* USART Tx pin location number */ \
    BSP_USART2_RX_LOC,                                                    /* USART Rx pin location number */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART2_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART2_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART2_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART2_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART2_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
    BSP_USART2_CTS_LOC,                                                   /* CTS pin location             */ \
    BSP_USART2_RTS_LOC                                                    /* RTS pin location             */ \
  }
  #elif defined(_GPIO_USART_ROUTEEN_MASK)
  #define USART2_INIT                                                                                        \
  {                                                                                                          \
    USART2,                                                               /* USART port                   */ \
    HAL_USART2_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART2_TX_PORT,                                                   /* TX port number               */ \
    BSP_USART2_RX_PORT,                                                   /* RX port number               */ \
    BSP_USART2_TX_PIN,                                                    /* TX pin number                */ \
    BSP_USART2_RX_PIN,                                                    /* RX pin number                */ \
    2,                                                                    /* UART instance number         */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART2_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART2_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART2_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART2_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART2_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
  }
  #else //defined( _USART_ROUTELOC0_MASK )
  #define USART2_INIT                                                                                        \
  {                                                                                                          \
    USART2,                                                               /* USART port                   */ \
    HAL_USART2_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART2_ROUTE_LOC,                                                 /* USART pins location number   */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    (UARTDRV_FlowControlType_t)HAL_USART2_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART2_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART2_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART2_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART2_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL                                                                  /* TX operation queue           */ \
  }
  #endif //defined( _USART_ROUTELOC0_MASK )

  #ifndef HAL_USART2_RXSTOP
    #define HAL_USART2_RXSTOP 16
  #endif
  #ifndef HAL_USART2_RXSTART
    #define HAL_USART2_RXSTART HAL_USART2_RXSTOP
  #endif

  #define COM_USART2_DEFAULT                                                   \
  {                                                                            \
    (UARTDRV_Init_t) USART2_INIT,                  /* USART initdata        */ \
    HAL_USART2_RXSTOP,                             /* RX stop threshold     */ \
    HAL_USART2_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_USART2_ENABLE

#ifdef COM_USART3_ENABLE
  #ifndef HAL_USART3_BAUD_RATE
    #define HAL_USART3_BAUD_RATE 115200
  #endif

  #if (HAL_USART3_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_USART3_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_USART3_CTS_PORT
    #undef BSP_USART3_CTS_PIN
    #undef BSP_USART3_RTS_PORT
    #undef BSP_USART3_RTS_PIN
    #undef BSP_USART3_CTS_LOC
    #undef BSP_USART3_RTS_LOC
    #define BSP_USART3_CTS_PORT gpioPortA
    #define BSP_USART3_CTS_PIN  0
    #define BSP_USART3_RTS_PORT gpioPortA
    #define BSP_USART3_RTS_PIN  0
    #define BSP_USART3_CTS_LOC  0
    #define BSP_USART3_RTS_LOC  0
  #endif

  #if defined(_USART_ROUTELOC0_MASK)
  #define USART3_INIT                                                                                        \
  {                                                                                                          \
    USART3,                                                               /* USART port                   */ \
    HAL_USART3_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART3_TX_LOC,                                                    /* USART Tx pin location number */ \
    BSP_USART3_RX_LOC,                                                    /* USART Rx pin location number */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART3_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART3_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART3_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART3_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART3_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
    BSP_USART3_CTS_LOC,                                                   /* CTS pin location             */ \
    BSP_USART3_RTS_LOC                                                    /* RTS pin location             */ \
  }
  #elif defined(_GPIO_USART_ROUTEEN_MASK)
  #define USART3_INIT                                                                                        \
  {                                                                                                          \
    USART3,                                                               /* USART port                   */ \
    HAL_USART3_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART3_TX_PORT,                                                   /* TX port number               */ \
    BSP_USART3_RX_PORT,                                                   /* RX port number               */ \
    BSP_USART3_TX_PIN,                                                    /* TX pin number                */ \
    BSP_USART3_RX_PIN,                                                    /* RX pin number                */ \
    3,                                                                    /* UART instance number         */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    false,                                                                /* Majority vote disable        */ \
    (UARTDRV_FlowControlType_t)HAL_USART3_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART3_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART3_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART3_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART3_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL,                                                                 /* TX operation queue           */ \
  }
  #else //defined( _USART_ROUTELOC0_MASK )
  #define USART3_INIT                                                                                        \
  {                                                                                                          \
    USART3,                                                               /* USART port                   */ \
    HAL_USART3_BAUD_RATE,                                                 /* Baud rate                    */ \
    BSP_USART3_ROUTE_LOC,                                                 /* USART pins location number   */ \
    (USART_Stopbits_TypeDef)USART_FRAME_STOPBITS_ONE,                     /* Stop bits                    */ \
    (USART_Parity_TypeDef)USART_FRAME_PARITY_NONE,                        /* Parity                       */ \
    (USART_OVS_TypeDef)USART_CTRL_OVS_X16,                                /* Oversampling mode            */ \
    (UARTDRV_FlowControlType_t)HAL_USART3_FLOW_CONTROL,                   /* Flow control                 */ \
    BSP_USART3_CTS_PORT,                                                  /* CTS port number              */ \
    BSP_USART3_CTS_PIN,                                                   /* CTS pin number               */ \
    BSP_USART3_RTS_PORT,                                                  /* RTS port number              */ \
    BSP_USART3_RTS_PIN,                                                   /* RTS pin number               */ \
    NULL,                                                                 /* RX operation queue           */ \
    NULL                                                                  /* TX operation queue           */ \
  }
  #endif //defined( _USART_ROUTELOC0_MASK )

  #ifndef HAL_USART3_RXSTOP
    #define HAL_USART3_RXSTOP 16
  #endif
  #ifndef HAL_USART3_RXSTART
    #define HAL_USART3_RXSTART HAL_USART3_RXSTOP
  #endif

  #define COM_USART3_DEFAULT                                                   \
  {                                                                            \
    (UARTDRV_Init_t) USART3_INIT,                  /* USART initdata        */ \
    HAL_USART3_RXSTOP,                             /* RX stop threshold     */ \
    HAL_USART3_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_USART3_ENABLE

#ifdef COM_LEUART0_ENABLE
  #ifndef HAL_LEUART0_BAUD_RATE
    #define HAL_LEUART0_BAUD_RATE 115200
  #endif

  #if (HAL_LEUART0_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_LEUART0_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_LEUART0_CTS_PORT
    #undef BSP_LEUART0_CTS_PIN
    #undef BSP_LEUART0_RTS_PORT
    #undef BSP_LEUART0_RTS_PIN
    #undef BSP_LEUART0_CTS_LOC
    #undef BSP_LEUART0_RTS_LOC
    #define BSP_LEUART0_CTS_PORT gpioPortA
    #define BSP_LEUART0_CTS_PIN  0
    #define BSP_LEUART0_RTS_PORT gpioPortA
    #define BSP_LEUART0_RTS_PIN  0
    #define BSP_LEUART0_CTS_LOC  0
    #define BSP_LEUART0_RTS_LOC  0
  #endif

  #ifdef _LEUART_ROUTELOC0_MASK
    #define LEUART0_INIT                                                                                       \
  {                                                                                                            \
    LEUART0,                                                                /* LEUART port                  */ \
    HAL_LEUART0_BAUD_RATE,                                                  /* Baud rate                    */ \
    BSP_LEUART0_TX_LOC,                                                     /* LEUART TX location number    */ \
    BSP_LEUART0_RX_LOC,                                                     /* LEUART TX location number    */ \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                      /* Stop bits                    */ \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                         /* Parity                       */ \
    (UARTDRV_FlowControlType_t)HAL_LEUART0_FLOW_CONTROL,                    /* Flow control                 */ \
    BSP_LEUART0_CTS_PORT,                                                   /* CTS port number              */ \
    BSP_LEUART0_CTS_PIN,                                                    /* CTS pin number               */ \
    BSP_LEUART0_RTS_PORT,                                                   /* RTS port number              */ \
    BSP_LEUART0_RTS_PIN,                                                    /* RTS pin number               */ \
    NULL,                                                                   /* RX operation queue           */ \
    NULL                                                                    /* TX operation queue           */ \
  }
  #else // _LEUART_ROUTELOC0_MASK
    #define LEUART0_INIT                                                                                        \
  {                                                                                                             \
    LEUART0,                                                                /* LEUART port                   */ \
    HAL_LEUART0_BAUD_RATE,                                                  /* Baud rate                    */  \
    BSP_LEUART0_ROUTE_LOC,                                                  /* LEUART location number       */  \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                      /* Stop bits                    */  \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                         /* Parity                       */  \
    (UARTDRV_FlowControlType_t)HAL_LEUART0_FLOW_CONTROL,                    /* Flow control                 */  \
    BSP_LEUART0_CTS_PORT,                                                   /* CTS port number              */  \
    BSP_LEUART0_CTS_PIN,                                                    /* CTS pin number               */  \
    BSP_LEUART0_RTS_PORT,                                                   /* RTS port number              */  \
    BSP_LEUART0_RTS_PIN,                                                    /* RTS pin number               */  \
    NULL,                                                                   /* RX operation queue           */  \
    NULL                                                                    /* TX operation queue           */  \
  }
  #endif // _LEUART_ROUTELOC0_MASK

  #ifndef HAL_LEUART0_RXSTOP
    #define HAL_LEUART0_RXSTOP 16
  #endif
  #ifndef HAL_LEUART0_RXSTART
    #define HAL_LEUART0_RXSTART HAL_LEUART0_RXSTOP
  #endif

  #define COM_LEUART0_DEFAULT                                                   \
  {                                                                             \
    { .leuartinit = LEUART0_INIT },            /* LEUART initdata       */      \
    HAL_LEUART0_RXSTOP,                             /* RX stop threshold     */ \
    HAL_LEUART0_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_LEUART0_ENABLE

#ifdef COM_LEUART1_ENABLE
  #ifndef HAL_LEUART1_BAUD_RATE
    #define HAL_LEUART1_BAUD_RATE 115200
  #endif

  #if (HAL_LEUART1_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HW) \
  && (HAL_LEUART1_FLOW_CONTROL != HAL_USART_FLOW_CONTROL_HWUART)
    #undef BSP_LEUART1_CTS_PORT
    #undef BSP_LEUART1_CTS_PIN
    #undef BSP_LEUART1_RTS_PORT
    #undef BSP_LEUART1_RTS_PIN
    #undef BSP_LEUART1_CTS_LOC
    #undef BSP_LEUART1_RTS_LOC
    #define BSP_LEUART1_CTS_PORT gpioPortA
    #define BSP_LEUART1_CTS_PIN  0
    #define BSP_LEUART1_RTS_PORT gpioPortA
    #define BSP_LEUART1_RTS_PIN  0
    #define BSP_LEUART1_CTS_LOC  0
    #define BSP_LEUART1_RTS_LOC  0
  #endif

  #ifdef _LEUART_ROUTELOC0_MASK
    #define LEUART1_INIT                                                                                       \
  {                                                                                                            \
    LEUART1,                                                                /* LEUART port                  */ \
    HAL_LEUART1_BAUD_RATE,                                                  /* Baud rate                    */ \
    BSP_LEUART1_TX_LOC,                                                     /* LEUART TX location number    */ \
    BSP_LEUART1_RX_LOC,                                                     /* LEUART TX location number    */ \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                      /* Stop bits                    */ \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                         /* Parity                       */ \
    (UARTDRV_FlowControlType_t)HAL_LEUART1_FLOW_CONTROL,                    /* Flow control                 */ \
    BSP_LEUART1_CTS_PORT,                                                   /* CTS port number              */ \
    BSP_LEUART1_CTS_PIN,                                                    /* CTS pin number               */ \
    BSP_LEUART1_RTS_PORT,                                                   /* RTS port number              */ \
    BSP_LEUART1_RTS_PIN,                                                    /* RTS pin number               */ \
    NULL,                                                                   /* RX operation queue           */ \
    NULL                                                                    /* TX operation queue           */ \
  }
  #else // _LEUART_ROUTELOC0_MASK
    #define LEUART1_INIT                                                                                        \
  {                                                                                                             \
    LEUART1,                                                                /* LEUART port                   */ \
    HAL_LEUART1_BAUD_RATE,                                                  /* Baud rate                    */  \
    BSP_LEUART1_ROUTE_LOC,                                                  /* LEUART location number       */  \
    (LEUART_Stopbits_TypeDef)LEUART_CTRL_STOPBITS_ONE,                      /* Stop bits                    */  \
    (LEUART_Parity_TypeDef)LEUART_CTRL_PARITY_NONE,                         /* Parity                       */  \
    (UARTDRV_FlowControlType_t)HAL_LEUART1_FLOW_CONTROL,                    /* Flow control                 */  \
    BSP_LEUART1_CTS_PORT,                                                   /* CTS port number              */  \
    BSP_LEUART1_CTS_PIN,                                                    /* CTS pin number               */  \
    BSP_LEUART1_RTS_PORT,                                                   /* RTS port number              */  \
    BSP_LEUART1_RTS_PIN,                                                    /* RTS pin number               */  \
    NULL,                                                                   /* RX operation queue           */  \
    NULL                                                                    /* TX operation queue           */  \
  }
  #endif // _LEUART_ROUTELOC0_MASK

  #ifndef HAL_LEUART1_RXSTOP
    #define HAL_LEUART1_RXSTOP 16
  #endif
  #ifndef HAL_LEUART1_RXSTART
    #define HAL_LEUART1_RXSTART HAL_LEUART1_RXSTOP
  #endif

  #define COM_LEUART1_DEFAULT                                                   \
  {                                                                             \
    { .leuartinit = LEUART1_INIT },            /* LEUART initdata       */      \
    HAL_LEUART1_RXSTOP,                             /* RX stop threshold     */ \
    HAL_LEUART1_RXSTART                             /* RX start threshold    */ \
  }
#endif //COM_LEUART1_ENABLE

#ifndef UART_RX_INT_PORT
  #if ((BSP_SERIAL_APP_PORT == 1) || (BSP_SERIAL_APP_PORT == 0x20))
    #define UART_RX_INT_PORT BSP_USART0_RX_PORT
  #elif ((BSP_SERIAL_APP_PORT == 2) || (BSP_SERIAL_APP_PORT == 0x21))
    #define UART_RX_INT_PORT BSP_USART1_RX_PORT
  #elif ((BSP_SERIAL_APP_PORT == 3) || (BSP_SERIAL_APP_PORT == 0x22))
    #define UART_RX_INT_PORT BSP_USART2_RX_PORT
  #elif (BSP_SERIAL_APP_PORT == 0x23)
    #define UART_RX_INT_PORT BSP_USART3_RX_PORT
  #elif ((BSP_SERIAL_APP_PORT == 5) || (BSP_SERIAL_APP_PORT == 0x40))
    #define UART_RX_INT_PORT BSP_LEUART0_RX_PORT
  #elif ((BSP_SERIAL_APP_PORT == 6) || (BSP_SERIAL_APP_PORT == 0x41))
    #define UART_RX_INT_PORT BSP_LEUART1_RX_PORT
#endif
#endif
#ifndef UART_RX_INT_PIN
  #if ((BSP_SERIAL_APP_PORT == 1) || (BSP_SERIAL_APP_PORT == 0x20))
    #define UART_RX_INT_PIN BSP_USART0_RX_PIN
  #elif ((BSP_SERIAL_APP_PORT == 2) || (BSP_SERIAL_APP_PORT == 0x21))
    #define UART_RX_INT_PIN BSP_USART1_RX_PIN
  #elif ((BSP_SERIAL_APP_PORT == 3) || (BSP_SERIAL_APP_PORT == 0x22))
    #define UART_RX_INT_PIN BSP_USART2_RX_PIN
  #elif (BSP_SERIAL_APP_PORT == 0x23)
    #define UART_RX_INT_PIN BSP_USART3_RX_PIN
  #elif ((BSP_SERIAL_APP_PORT == 5) || (BSP_SERIAL_APP_PORT == 0x40))
    #define UART_RX_INT_PIN BSP_LEUART0_RX_PIN
  #elif ((BSP_SERIAL_APP_PORT == 6) || (BSP_SERIAL_APP_PORT == 0x41))
    #define UART_RX_INT_PIN BSP_LEUART1_RX_PIN
#endif
#endif

#endif // COM_CONFIG_H
