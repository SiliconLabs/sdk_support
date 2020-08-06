/***************************************************************************//**
 * @file
 * @brief  Automatic serial controller selection for EZSP SPI EM3XX NCP
 *
 * The old default for an EZSP SPI NCP was to use SC2, however some newer
 * variants don't have SC2 (or some of the extra required GPIO). When this is
 * the case, this file will define EZSP_SPI_PORT as 1 so the implementation will
 * use SC1.
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
//The maximum SPI Protocol message size is 136 bytes. We define a buffer of
//142 specifically for error detection during the Response Section.  By using
//a buffer of 142, we can use the TXCNT register to monitor the state of
//the transaction and know that if a DMA TX unload occurs we have an error.
#define SPIP_BUFFER_SIZE             142
#define SPIP_ERROR_RESPONSE_SIZE     2
#define MAX_PAYLOAD_FRAME_LENGTH     133
#define EZSP_LENGTH_INDEX            1
#define RX_DMA_BYTES_LEFT_THRESHOLD  4

 #ifndef EZSP_SPI_PORT
  #if EMBER_MICRO_SERIAL_CONTROLLERS_MASK == 1 // only has SC1
    #define EZSP_SPI_PORT 1
  #elif EMBER_MICRO_SERIAL_CONTROLLERS_MASK == 2 // only has SC2
    #define EZSP_SPI_PORT 2
  #else // has multiple serial controllers (or only 3 or 4, which we don't handle)
// test that the micro has all of the GPIO required for port 2.  this is
// the default for backwards compatibility reasons
  #if (PORT_A_PIN_MASK & _GPIO_P_OUT_Px0_MASK)                             \
  && (PORT_A_PIN_MASK & _GPIO_P_OUT_Px1_MASK)                              \
  && (PORT_A_PIN_MASK & _GPIO_P_OUT_Px2_MASK)                              \
  && (PORT_A_PIN_MASK & _GPIO_P_OUT_Px3_MASK)                              \
  && (PORT_B_PIN_MASK & _GPIO_P_OUT_Px2_MASK)                              \
  && (PORT_B_PIN_MASK & _GPIO_P_OUT_Px3_MASK)                              \
  && (PORT_B_PIN_MASK & _GPIO_P_OUT_Px6_MASK)                              \
  && (!PHY_DUAL)             /* DUAL  reserves SC2 so EZSP must use SC1 */ \
  && (!PHY_PRO2PLUS)         /* PRO2+ reserves SC2 so EZSP must use SC1 */
      #define EZSP_SPI_PORT 2
    #else
      #define EZSP_SPI_PORT 1
    #endif
  #endif
#endif
// only serial controllers 1 through 4 are valid
#if EZSP_SPI_PORT < 1 || EZSP_SPI_PORT > 4
  #error "EZSP_SPI_PORT out of range"
#endif
// only serial controllers actually present on the micro are valid
#if (EMBER_MICRO_SERIAL_CONTROLLERS_MASK & (1 << (EZSP_SPI_PORT - 1))) == 0
  #error "EZSP_SPI_PORT specifies an invalid serial controller for this micro"
#endif
#undef  SCx_REG // Need to obliterate the micro-common.h UART-focused one
#if EZSP_SPI_PORT == 1
// Pin assignments - uses SC1, IRQA or IRQB, IRQC
// P[1].0 - nWAKE (IRQA) [except PHY_DUAL / PHY_PRO2PLUS]
// P[1].1 - MISO
// P[1].2 - MOSI
// P[1].3 - SCLK
// P[1].4 - nSSEL (IRQC)
// P[1].6 - nWAKE (IRQB) [only PHY_DUAL / PHY_PRO2PLUS]
// P[2].7 - nHOST_INT
// serial controller abstraction
  #define SCx_REG(reg) SC1->reg
  #define SCx_MODE(mode) SC_MODE_MODE_##mode
  #define INT_SCxCFG EVENT_SC1->CFG
  #define INT_SCxFLAG EVENT_SC1->FLAG
  #define INT_SCx SC1_IRQn
  #define SCx_ISR halSc1Isr
// serial controller GPIO configuration
// configure all the pins in one register at once to avoid glitches as much
// as possible
  #define CFG_SPI_GPIO()                                                                   \
  do {                                                                                     \
    GPIO->P[1].CFGL = ((GPIO->P[1].CFGL & _GPIO_P_CFGL_Px0_MASK)                           \
                       | (_GPIO_P_CFGL_Px1_OUT_ALT << _GPIO_P_CFGL_Px1_SHIFT) /* MISO */   \
                       | (_GPIO_P_CFGL_Px2_IN      << _GPIO_P_CFGL_Px2_SHIFT) /* MOSI */   \
                       | (_GPIO_P_CFGL_Px3_IN      << _GPIO_P_CFGL_Px3_SHIFT));/* SCLK */  \
    GPIO->P[1].CFGH = ((GPIO->P[1].CFGH & (~_GPIO_P_CFGH_Px4_MASK))                        \
                       | (_GPIO_P_CFGH_Px4_IN      << _GPIO_P_CFGH_Px4_SHIFT));/* nSSEL */ \
  } while (0)
// SC1nSSEL:  P[1].4, configured as a input with pullup
// nSSEL interrupt: IRQC (assigned to pin P[1].4, rising edge with no filtering)
  #define PULLUP_nSSEL()      (GPIO->P[1].SET = GPIO_P_SET_Px4)
  #define nSSEL_IS_NEGATED()  (((GPIO->P[1].IN) & GPIO_P_IN_Px4) != 0)
  #define nSSEL_IS_ASSERTED() (((GPIO->P[1].IN) & GPIO_P_IN_Px4) == 0)
  #define nSSEL_IRQSEL        GPIO->IRQCSEL
  #define nSSEL_IRQSEL_MASK   12
  #define nSSEL_INTCFG        EVENT_GPIO->CFGC
  #define nSSEL_INT           IRQC_IRQn
  #define nSSEL_GPIOFLAG      EVENT_GPIO_FLAG_IRQC
  #define nSSEL_ISR           halIrqCIsr
// nHOST_INT: P[2].7, configured as a push-pull output
  #define CFG_nHOST_INT(cfg)  do { uint32_t temp;                                   \
                                   temp = GPIO->P[2].CFGH & ~_GPIO_P_CFGH_Px7_MASK; \
                                   temp |= cfg << _GPIO_P_CFGH_Px7_SHIFT;           \
                                   GPIO->P[2].CFGH = temp; } while (0)
  #define SET_nHOST_INT()     do { GPIO->P[2].SET = GPIO_P_SET_Px7; } while (0)
  #define CLR_nHOST_INT()     do { GPIO->P[2].CLR = GPIO_P_CLR_Px7; } while (0)

// nSSEL_INT is not used on this serial controller
  #define CFG_nSSEL_INT(cfg)  do {} while (0)

 #if     (PHY_DUAL || PHY_PRO2PLUS)
// nWAKE: P[1].6, configured as input with a pull-up
// nWAKE interrupt: IRQB (fixed at pin P[1].6, falling edge with no filtering)
  #define CFG_nWAKE(cfg)      do { uint32_t temp;                                   \
                                   temp = GPIO->P[1].CFGH & ~_GPIO_P_CFGH_Px6_MASK; \
                                   temp |= cfg << _GPIO_P_CFGH_Px6_SHIFT;           \
                                   GPIO->P[1].CFGH = temp; } while (0)
  #define PULLUP_nWAKE()      (GPIO->P[1].SET = GPIO_P_SET_Px6)
  #define nWAKE_IS_NEGATED()  (((GPIO->P[1].IN) & GPIO_P_IN_Px6) != 0)
  #define nWAKE_IS_ASSERTED() (((GPIO->P[1].IN) & GPIO_P_IN_Px6) == 0)
  #define nWAKE_INTCFG        EVENT_GPIO->CFGB
  #define nWAKE_INT           IRQB_IRQn
  #define nWAKE_GPIOFLAG      EVENT_GPIO_FLAG_IRQB
  #define nWAKE_ISR           halIrqBIsr
 #else//!(PHY_DUAL || PHY_PRO2PLUS)
// nWAKE: P[1].0, configured as input with a pull-up
// nWAKE interrupt: IRQA (fixed at pin P[1].0, falling edge with no filtering)
  #define CFG_nWAKE(cfg)      do { uint32_t temp;                                   \
                                   temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px0_MASK; \
                                   temp |= cfg << _GPIO_P_CFGL_Px0_SHIFT;           \
                                   GPIO->P[1].CFGL = temp; } while (0)
  #define PULLUP_nWAKE()      (GPIO->P[1].SET = GPIO_P_SET_Px0)
  #define nWAKE_IS_NEGATED()  (((GPIO->P[1].IN) & GPIO_P_IN_Px0) != 0)
  #define nWAKE_IS_ASSERTED() (((GPIO->P[1].IN) & GPIO_P_IN_Px0) == 0)
  #define nWAKE_INTCFG        EVENT_GPIO->CFGA
  #define nWAKE_INT           IRQA_IRQn
  #define nWAKE_GPIOFLAG      EVENT_GPIO_FLAG_IRQA
  #define nWAKE_ISR           halIrqAIsr
 #endif//(PHY_DUAL || PHY_PRO2PLUS)
// ENABLE_NSIMRST is not compatible with SC1
#elif EZSP_SPI_PORT == 2
// Pin assignments - uses SC2, IRQB, IRQC
// P[0].0 - MOSI
// P[0].1 - MISO
// P[0].2 - SCLK
// P[0].3 - nSSEL (IRQC)
// P[1].2 - nHOST_INT
// P[1].3 - nSSEL_INT (for EM260 compatibility - not used by EM35X)
// P[1].6 - nWAKE (IRQB)
// P[1].0 - nSIMRST (IRQA replaces nRESET for debugging only)
// serial controller abstraction
  #define SCx_REG(reg) SC2->reg
  #define SCx_MODE(mode) SC_MODE_MODE_##mode
  #define INT_SCxCFG EVENT_SC2->CFG
  #define INT_SCxFLAG EVENT_SC2->FLAG
  #define INT_SCx SC2_IRQn
  #define SCx_ISR halSc2Isr
// serial controller GPIO configuration
// To avoid glitches, refresh configuration for all 4 pins in P[0].CFGL at once.
  #define CFG_SPI_GPIO()                                                                   \
  do {                                                                                     \
    GPIO->P[0].CFGL = ((_GPIO_P_CFGL_Px0_IN       << _GPIO_P_CFGL_Px0_SHIFT)   /* MOSI */  \
                       | (_GPIO_P_CFGL_Px1_OUT_ALT << _GPIO_P_CFGL_Px1_SHIFT)  /* MISO */  \
                       | (_GPIO_P_CFGL_Px2_IN      << _GPIO_P_CFGL_Px2_SHIFT)  /* SCLK */  \
                       | (_GPIO_P_CFGL_Px2_IN_PUD  << _GPIO_P_CFGL_Px3_SHIFT));/* nSSEL */ \
  } while (0)
// SC2nSSEL:  P[0].3, configured as a input with pullup
// nSSEL interrupt: IRQC (assigned to pin P[0].3, rising edge with no filtering)
  #define nSSEL_BIT           3
  #define PULLUP_nSSEL()      (GPIO->P[0].SET = (1 << nSSEL_BIT))
  #define nSSEL_IS_NEGATED()  ((GPIO->P[0].IN & (1 << nSSEL_BIT)) != 0)
  #define nSSEL_IS_ASSERTED() ((GPIO->P[0].IN & (1 << nSSEL_BIT)) == 0)
  #define nSSEL_IRQSEL        GPIO->IRQCSEL
  #define nSSEL_IRQSEL_MASK   3
  #define nSSEL_INTCFG        EVENT_GPIO->CFGC
  #define nSSEL_INT           IRQC_IRQn
  #define nSSEL_GPIOFLAG      EVENT_GPIO_FLAG_IRQC
  #define nSSEL_ISR           halIrqCIsr
// nHOST_INT: P[1].2, configured as a push-pull output
  #define nHOST_INT_BIT       2
  #define CFG_nHOST_INT(cfg)  do { uint32_t temp;                                   \
                                   temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px2_MASK; \
                                   temp |= cfg << _GPIO_P_CFGL_Px2_SHIFT;           \
                                   GPIO->P[1].CFGL = temp; } while (0)
  #define SET_nHOST_INT()     do { GPIO->P[1].SET = (1 << nHOST_INT_BIT); } while (0)
  #define CLR_nHOST_INT()     do { GPIO->P[1].CLR = (1 << nHOST_INT_BIT); } while (0)

// nSSEL_INT: P[1].3, configured as a floating input
// For EM260 compatibility, can be connected to nSSEL; it is unused on the 35x
  #define nSSEL_INT_BIT       3
  #define CFG_nSSEL_INT(cfg)  do { uint32_t temp;                                   \
                                   temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px3_MASK; \
                                   temp |= cfg << _GPIO_P_CFGL_Px3_SHIFT;           \
                                   GPIO->P[1].CFGL = temp; } while (0)

// nWAKE: P[1].6, configured as input with a pull-up
// nWAKE interrupt: IRQB (fixed at pin P[1].6, falling edge with no filtering)
  #define nWAKE_BIT           6
  #define CFG_nWAKE(cfg)      do { uint32_t temp;                                   \
                                   temp = GPIO->P[1].CFGH & ~_GPIO_P_CFGH_Px6_MASK; \
                                   temp |= cfg << _GPIO_P_CFGH_Px6_SHIFT;           \
                                   GPIO->P[1].CFGH = temp; } while (0)
  #define PULLUP_nWAKE()      (GPIO->P[1].SET = (1 << nWAKE_BIT))
  #define nWAKE_IS_NEGATED()  (((GPIO->P[1].IN) & (1 << nWAKE_BIT)) != 0)
  #define nWAKE_IS_ASSERTED() (((GPIO->P[1].IN) & (1 << nWAKE_BIT)) == 0)
  #define nWAKE_INTCFG        EVENT_GPIO->CFGB
  #define nWAKE_INT           IRQB_IRQn
  #define nWAKE_GPIOFLAG      EVENT_GPIO_FLAG_IRQB
  #define nWAKE_ISR           halIrqBIsr
// For debugging, use P[1].0/IRQA in place of nRESET.  Use the the board file
// dev0680spi-test.h to enable this functionality (the board file configures
// the gpio and defines ENABLE_NSIMRST).
  #ifdef ENABLE_NSIMRST
// nSIMRST: P[1].0, configured as input with a pull-up
// nSIMRST interrupt: IRQA (fixed at pin P[1].0, falling edge with no filtering)
    #define nSIMRST_BIT         0
    #define CFG_nSIMRST(cfg)    do { uint32_t temp;                                   \
                                     temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px0_MASK; \
                                     temp |= cfg << _GPIO_P_CFGL_Px0_SHIFT;           \
                                     GPIO->P[1].CFGL = temp; } while (0)
    #define PULLUP_nSIMRST()    (GPIO->P[1].SET = (1 << nSIMRST_BIT))
    #define nSIMRST_IS_HIGH     (((GPIO->P[1].IN) & (1 << nSIMRST_BIT)) != 0)
    #define nSIMRST_IS_LOW      (((GPIO->P[1].IN) & (1 << nSIMRST_BIT)) == 0)
    #define nSIMRST_INTCFG      EVENT_GPIO->CFGA
    #define nSIMRST_INT         IRQA_IRQn
    #define nSIMRST_GPIOFLAG    EVENT_GPIO_FLAG_IRQA
  #endif
#elif EZSP_SPI_PORT == 3
// TODO
// serial controller abstraction
  #define SCx_REG(reg) SC3x_##reg
  #define SCx_MODE(mode) SC_MODE_MODE_##mode
  #define INT_SCxCFG INT_SC3CFG
  #define INT_SCxFLAG INT_SC3FLAG
  #define INT_SCx SC3_IRQn

  #error "ESPI_SPI_PORT == 3 is not fully implemented yet"
#elif EZSP_SPI_PORT == 4
// TODO
// serial controller abstraction
  #define SCx_REG(reg) SC4x_##reg
  #define SCx_MODE(mode) SC_MODE_MODE_##mode
  #define INT_SCxCFG INT_SC4CFG
  #define INT_SCxFLAG INT_SC4FLAG
  #define INT_SCx SC4_IRQn
  #error "ESPI_SPI_PORT == 4 is not fully implemented yet"
#endif
