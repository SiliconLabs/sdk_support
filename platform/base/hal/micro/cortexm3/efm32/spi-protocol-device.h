/***************************************************************************//**
 * @file
 * @brief Internal SPI Protocol Device Header for USART and Pin Configuration
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
#ifndef __SPI_PROTOCOL_DEVICE_H__
#define __SPI_PROTOCOL_DEVICE_H__

//The maximum SPI Protocol message size is 136 bytes. We define a buffer of
//142 specifically for error detection during the Response Section.  By using
//a buffer of 142, we can use the SCx_REG(TXCNT) register to monitor the state
//of the transaction and know that if a DMA TX unload occurs we have an error.
#define SPIP_BUFFER_SIZE             142
#define SPIP_ERROR_RESPONSE_SIZE     2
#define MAX_PAYLOAD_FRAME_LENGTH     133
#define EZSP_LENGTH_INDEX            1
#define RX_DMA_BYTES_LEFT_THRESHOLD  4
// Timeout (ms) for SPI transfers
#ifndef SPI_NCP_TIMEOUT
#define SPI_NCP_TIMEOUT 0
#endif

#ifndef SPI_NCP_RX_BUFFERS
#define SPI_NCP_RX_BUFFERS 1
#endif

// SPI NCP USART selection
#if (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART0)
  #define SPI_NCP_USART           USART0
  #define SPI_NCP_USART_IRQn      USART0_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART0_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART0
#elif (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART1)
  #define SPI_NCP_USART           USART1
  #define SPI_NCP_USART_IRQn      USART1_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART1_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART1
#elif (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART2)
  #define SPI_NCP_USART           USART2
  #define SPI_NCP_USART_IRQn      USART2_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART2_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART2
#elif (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART3)
  #define SPI_NCP_USART           USART3
  #define SPI_NCP_USART_IRQn      USART3_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART3_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART3
#elif (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART4)
  #define SPI_NCP_USART           USART4
  #define SPI_NCP_USART_IRQn      USART4_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART4_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART4
#elif (BSP_SPINCP_USART_PORT == HAL_SPI_PORT_USART5)
  #define SPI_NCP_USART           USART5
  #define SPI_NCP_USART_IRQn      USART5_RX_IRQn
  #define SPI_NCP_USART_IRQ_NAME  USART5_RX_IRQHandler
  #define SPI_NCP_USART_CLOCK     cmuClock_USART5
#else
  #error Invalid USART selected for SPI NCP
#endif

#if defined(BSP_SPINCP_MOSI_LOC)
  #define SPI_NCP_MOSI_LOC        BSP_SPINCP_MOSI_LOC
  #define SPI_NCP_MISO_LOC        BSP_SPINCP_MISO_LOC
  #define SPI_NCP_CLK_LOC         BSP_SPINCP_CLK_LOC
  #define SPI_NCP_CS_LOC          BSP_SPINCP_CS_LOC
#endif
#define SPI_NCP_MOSI_PORT       BSP_SPINCP_MOSI_PORT
#define SPI_NCP_MOSI_PIN        BSP_SPINCP_MOSI_PIN
#define SPI_NCP_MISO_PORT       BSP_SPINCP_MISO_PORT
#define SPI_NCP_MISO_PIN        BSP_SPINCP_MISO_PIN
#define SPI_NCP_CLK_PORT        BSP_SPINCP_CLK_PORT
#define SPI_NCP_CLK_PIN         BSP_SPINCP_CLK_PIN
#define SPI_NCP_CS_PORT         BSP_SPINCP_CS_PORT
#define SPI_NCP_CS_PIN          BSP_SPINCP_CS_PIN
// Configuration data for SPI NCP slave.
#if defined(SPI_NCP_MOSI_LOC)
#define SPI_NCP_USART_INIT                                             \
  {                                                                    \
    SPI_NCP_USART,              /* USART port                       */ \
    SPI_NCP_MOSI_LOC,           /* USART Tx/MOSI pin location number*/ \
    SPI_NCP_MISO_LOC,           /* USART Rx/MISO pin location number*/ \
    SPI_NCP_CLK_LOC,            /* USART Clk pin location number    */ \
    SPI_NCP_CS_LOC,             /* USART Cs pin location number     */ \
    0,                          /* Bitrate                          */ \
    8,                          /* Frame length                     */ \
    0xFF,                       /* Dummy tx value for rx only funcs */ \
    spidrvSlave,                /* SPI mode                         */ \
    spidrvBitOrderMsbFirst,     /* Bit order on bus                 */ \
    spidrvClockMode0,           /* SPI clock/phase mode             */ \
    spidrvCsControlAuto,        /* CS controlled by the driver      */ \
    spidrvSlaveStartImmediate   /* Slave start transfers immediately*/ \
  }
#else
#define SPI_NCP_USART_INIT                                             \
  {                                                                    \
    SPI_NCP_USART,              /* USART port                       */ \
    SPI_NCP_MOSI_PORT,          /* USART Tx/MOSI port               */ \
    SPI_NCP_MISO_PORT,          /* USART Rx/MISO port               */ \
    SPI_NCP_CLK_PORT,           /* USART Clk port                   */ \
    SPI_NCP_CS_PORT,            /* USART CS port                    */ \
    SPI_NCP_MOSI_PIN,           /* USART Tx/MOSI pin                */ \
    SPI_NCP_MISO_PIN,           /* USART Rx/MISO pin                */ \
    SPI_NCP_CLK_PIN,            /* USART Clk pin                    */ \
    SPI_NCP_CS_PIN,             /* USART CS pin                     */ \
    0,                          /* Bitrate                          */ \
    8,                          /* Frame length                     */ \
    0xFF,                       /* Dummy tx value for rx only funcs */ \
    spidrvSlave,                /* SPI mode                         */ \
    spidrvBitOrderMsbFirst,     /* Bit order on bus                 */ \
    spidrvClockMode0,           /* SPI clock/phase mode             */ \
    spidrvCsControlAuto,        /* CS controlled by the driver      */ \
    spidrvSlaveStartImmediate   /* Slave start transfers immediately*/ \
  }
#endif

#ifndef SPI_BTL_USART_INIT
#define SPI_BTL_USART_INIT                                                \
  {                                                                       \
    usartEnable,   /*enable*/                                             \
    0,             /*refFreq*/                                            \
    1000,          /*baudrate*/                                           \
    usartDatabits8, /*databits*/                                          \
    false,         /*master:  false = slave mode*/                        \
    true,          /*msfb: true = msb first  false = lsb first*/          \
    usartClockMode0, /*clockMode: clock idle low, sample on rising edge*/ \
  }
#endif

#if (!defined(DISABLE_NWAKE)) && (!defined(HAL_CONFIG) || defined(BSP_SPINCP_NWAKE_PIN))
static inline bool nWAKE_IS_NEGATED(void)
{
  return (GPIO_PinInGet(BSP_SPINCP_NWAKE_PORT, BSP_SPINCP_NWAKE_PIN) != 0);
}

static inline bool nWAKE_IS_ASSERTED(void)
{
  return (GPIO_PinInGet(BSP_SPINCP_NWAKE_PORT, BSP_SPINCP_NWAKE_PIN) == 0);
}
#else
#define nWAKE_IS_NEGATED() true
#define nWAKE_IS_ASSERTED() false
#endif

static inline bool nSSEL_IS_NEGATED(void)
{
  return (GPIO_PinInGet(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN) != 0);
}

static inline bool nSSEL_IS_ASSERTED(void)
{
  return (GPIO_PinInGet(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN) == 0);
}

static inline void SET_nHOST_INT(void)
{
  GPIO_PinOutSet(BSP_SPINCP_NHOSTINT_PORT, BSP_SPINCP_NHOSTINT_PIN);
}

static inline void CLR_nHOST_INT(void)
{
  GPIO_PinOutClear(BSP_SPINCP_NHOSTINT_PORT, BSP_SPINCP_NHOSTINT_PIN);
}

#endif // __SPI_PROTOCOL_DEVICE_H__
