/**************************************************************************//**
 * @file
 * @brief EFR32MG24 PRS register and bit field definitions
 ******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/
#ifndef EFR32MG24_PRS_H
#define EFR32MG24_PRS_H
#define PRS_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup EFR32MG24_PRS PRS
 * @{
 * @brief EFR32MG24 PRS Register Declaration.
 *****************************************************************************/

/** PRS ASYNC_CH Register Group Declaration. */
typedef struct {
  __IOM uint32_t CTRL;                               /**< Async Channel Control Register                     */
} PRS_ASYNC_CH_TypeDef;

/** PRS SYNC_CH Register Group Declaration. */
typedef struct {
  __IOM uint32_t CTRL;                               /**< Sync Channel Control Register                      */
} PRS_SYNC_CH_TypeDef;

/** PRS Register Declaration. */
typedef struct {
  __IM uint32_t        IPVERSION;                         /**< PRS IPVERSION                                      */
  uint32_t             RESERVED0[1U];                     /**< Reserved for future use                            */
  __IOM uint32_t       ASYNC_SWPULSE;                     /**< Software Pulse Register                            */
  __IOM uint32_t       ASYNC_SWLEVEL;                     /**< Software Level Register                            */
  __IM uint32_t        ASYNC_PEEK;                        /**< Async Channel Values                               */
  __IM uint32_t        SYNC_PEEK;                         /**< Sync Channel Values                                */
  PRS_ASYNC_CH_TypeDef ASYNC_CH[16U];                     /**< Async Channel registers                            */
  PRS_SYNC_CH_TypeDef  SYNC_CH[4U];                       /**< Sync Channel registers                             */
  __IOM uint32_t       CONSUMER_CMU_CALDN;                /**< CALDN consumer register                            */
  __IOM uint32_t       CONSUMER_CMU_CALUP;                /**< CALUP Consumer register                            */
  __IOM uint32_t       CONSUMER_EUSART0_CLK;              /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART0_RX;               /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART0_TRIGGER;          /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_EUSART1_CLK;              /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART1_RX;               /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART1_TRIGGER;          /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_FRC_RXRAW;                /**< RXRAW consumer register                            */
  __IOM uint32_t       CONSUMER_IADC0_SCANTRIGGER;        /**< SCAN consumer register                             */
  __IOM uint32_t       CONSUMER_IADC0_SINGLETRIGGER;      /**< SINGLE Consumer register                           */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ0;         /**< DMAREQ0 consumer register                          */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ1;         /**< DMAREQ1 Consumer register                          */
  __IOM uint32_t       CONSUMER_LETIMER0_CLEAR;           /**< CLEAR consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_START;           /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_STOP;            /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_MODEM_DIN;                /**< DIN consumer register                              */
  __IOM uint32_t       CONSUMER_MODEM_PAEN;               /**< PAEN Consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S0IN;               /**< S0IN consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S1IN;               /**< S1IN Consumer register                             */
  __IOM uint32_t       CONSUMER_PROTIMER_CC0;             /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC1;             /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC2;             /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC3;             /**< CC3 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC4;             /**< CC4 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTPAUSE;        /**< LBTPAUSE Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTART;        /**< LBTSTART Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTOP;         /**< LBTSTOP Consumer register                          */
  __IOM uint32_t       CONSUMER_PROTIMER_RTCCTRIGGER;     /**< RTCCTRIGGER Consumer register                      */
  __IOM uint32_t       CONSUMER_PROTIMER_START;           /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_PROTIMER_STOP;            /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_CLR;                  /**< CLR consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN0;               /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN1;               /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN2;               /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN3;               /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_FORCETX;              /**< FORCETX Consumer register                          */
  __IOM uint32_t       CONSUMER_RAC_RXDIS;                /**< RXDIS Consumer register                            */
  __IOM uint32_t       CONSUMER_RAC_RXEN;                 /**< RXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_TXEN;                 /**< TXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC25;     /**< TAMPERSRC25 consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC26;     /**< TAMPERSRC26 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC27;     /**< TAMPERSRC27 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC28;     /**< TAMPERSRC28 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC29;     /**< TAMPERSRC29 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC30;     /**< TAMPERSRC30 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC31;     /**< TAMPERSRC31 Consumer register                      */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN0;              /**< IN0 consumer register                              */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN1;              /**< IN1 Consumer register                              */
  __IOM uint32_t       CONSUMER_HFXO0_OSCREQ;             /**< OSCREQ consumer register                           */
  __IOM uint32_t       CONSUMER_HFXO0_TIMEOUT;            /**< TIMEOUT Consumer register                          */
  __IOM uint32_t       CONSUMER_CORE_CTIIN0;              /**< CTI consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN1;              /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN2;              /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN3;              /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_M33RXEV;             /**< M33 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC0;               /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC1;               /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC2;               /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTI;               /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS1;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS2;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC0;               /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC1;               /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC2;               /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTI;               /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS1;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS2;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC0;               /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC1;               /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC2;               /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTI;               /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS1;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS2;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC0;               /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC1;               /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC2;               /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTI;               /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS1;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS2;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC0;               /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC1;               /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC2;               /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTI;               /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS1;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS2;            /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_CLK;               /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_IR;                /**< IR Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_RX;                /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_TRIGGER;           /**< TRIGGER Consumer register                          */
  uint32_t             RESERVED1[3U];                     /**< Reserved for future use                            */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH0;       /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH1;       /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH0;        /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH1;        /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH0;       /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH1;       /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH0;        /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH1;        /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_WDOG0_SRC0;               /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG0_SRC1;               /**< SRC1 Consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC0;               /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC1;               /**< SRC1 Consumer register                             */
  __IOM uint32_t       RPURATD0;                          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD1;                          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD2;                          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD3;                          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD4;                          /**< Root Access Type Descriptor Register               */
  uint32_t             RESERVED2[888U];                   /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_SET;                     /**< PRS IPVERSION                                      */
  uint32_t             RESERVED3[1U];                     /**< Reserved for future use                            */
  __IOM uint32_t       ASYNC_SWPULSE_SET;                 /**< Software Pulse Register                            */
  __IOM uint32_t       ASYNC_SWLEVEL_SET;                 /**< Software Level Register                            */
  __IM uint32_t        ASYNC_PEEK_SET;                    /**< Async Channel Values                               */
  __IM uint32_t        SYNC_PEEK_SET;                     /**< Sync Channel Values                                */
  PRS_ASYNC_CH_TypeDef ASYNC_CH_SET[16U];                 /**< Async Channel registers                            */
  PRS_SYNC_CH_TypeDef  SYNC_CH_SET[4U];                   /**< Sync Channel registers                             */
  __IOM uint32_t       CONSUMER_CMU_CALDN_SET;            /**< CALDN consumer register                            */
  __IOM uint32_t       CONSUMER_CMU_CALUP_SET;            /**< CALUP Consumer register                            */
  __IOM uint32_t       CONSUMER_EUSART0_CLK_SET;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART0_RX_SET;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART0_TRIGGER_SET;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_EUSART1_CLK_SET;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART1_RX_SET;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART1_TRIGGER_SET;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_FRC_RXRAW_SET;            /**< RXRAW consumer register                            */
  __IOM uint32_t       CONSUMER_IADC0_SCANTRIGGER_SET;    /**< SCAN consumer register                             */
  __IOM uint32_t       CONSUMER_IADC0_SINGLETRIGGER_SET;  /**< SINGLE Consumer register                           */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ0_SET;     /**< DMAREQ0 consumer register                          */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ1_SET;     /**< DMAREQ1 Consumer register                          */
  __IOM uint32_t       CONSUMER_LETIMER0_CLEAR_SET;       /**< CLEAR consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_START_SET;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_STOP_SET;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_MODEM_DIN_SET;            /**< DIN consumer register                              */
  __IOM uint32_t       CONSUMER_MODEM_PAEN_SET;           /**< PAEN Consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S0IN_SET;           /**< S0IN consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S1IN_SET;           /**< S1IN Consumer register                             */
  __IOM uint32_t       CONSUMER_PROTIMER_CC0_SET;         /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC1_SET;         /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC2_SET;         /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC3_SET;         /**< CC3 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC4_SET;         /**< CC4 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTPAUSE_SET;    /**< LBTPAUSE Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTART_SET;    /**< LBTSTART Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTOP_SET;     /**< LBTSTOP Consumer register                          */
  __IOM uint32_t       CONSUMER_PROTIMER_RTCCTRIGGER_SET; /**< RTCCTRIGGER Consumer register                      */
  __IOM uint32_t       CONSUMER_PROTIMER_START_SET;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_PROTIMER_STOP_SET;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_CLR_SET;              /**< CLR consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN0_SET;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN1_SET;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN2_SET;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN3_SET;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_FORCETX_SET;          /**< FORCETX Consumer register                          */
  __IOM uint32_t       CONSUMER_RAC_RXDIS_SET;            /**< RXDIS Consumer register                            */
  __IOM uint32_t       CONSUMER_RAC_RXEN_SET;             /**< RXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_TXEN_SET;             /**< TXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC25_SET; /**< TAMPERSRC25 consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC26_SET; /**< TAMPERSRC26 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC27_SET; /**< TAMPERSRC27 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC28_SET; /**< TAMPERSRC28 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC29_SET; /**< TAMPERSRC29 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC30_SET; /**< TAMPERSRC30 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC31_SET; /**< TAMPERSRC31 Consumer register                      */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN0_SET;          /**< IN0 consumer register                              */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN1_SET;          /**< IN1 Consumer register                              */
  __IOM uint32_t       CONSUMER_HFXO0_OSCREQ_SET;         /**< OSCREQ consumer register                           */
  __IOM uint32_t       CONSUMER_HFXO0_TIMEOUT_SET;        /**< TIMEOUT Consumer register                          */
  __IOM uint32_t       CONSUMER_CORE_CTIIN0_SET;          /**< CTI consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN1_SET;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN2_SET;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN3_SET;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_M33RXEV_SET;         /**< M33 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC0_SET;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC1_SET;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC2_SET;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTI_SET;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS1_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS2_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC0_SET;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC1_SET;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC2_SET;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTI_SET;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS1_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS2_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC0_SET;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC1_SET;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC2_SET;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTI_SET;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS1_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS2_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC0_SET;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC1_SET;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC2_SET;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTI_SET;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS1_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS2_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC0_SET;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC1_SET;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC2_SET;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTI_SET;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS1_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS2_SET;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_CLK_SET;           /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_IR_SET;            /**< IR Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_RX_SET;            /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_TRIGGER_SET;       /**< TRIGGER Consumer register                          */
  uint32_t             RESERVED4[3U];                     /**< Reserved for future use                            */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH0_SET;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH1_SET;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH0_SET;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH1_SET;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH0_SET;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH1_SET;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH0_SET;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH1_SET;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_WDOG0_SRC0_SET;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG0_SRC1_SET;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC0_SET;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC1_SET;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       RPURATD0_SET;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD1_SET;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD2_SET;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD3_SET;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD4_SET;                      /**< Root Access Type Descriptor Register               */
  uint32_t             RESERVED5[888U];                   /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_CLR;                     /**< PRS IPVERSION                                      */
  uint32_t             RESERVED6[1U];                     /**< Reserved for future use                            */
  __IOM uint32_t       ASYNC_SWPULSE_CLR;                 /**< Software Pulse Register                            */
  __IOM uint32_t       ASYNC_SWLEVEL_CLR;                 /**< Software Level Register                            */
  __IM uint32_t        ASYNC_PEEK_CLR;                    /**< Async Channel Values                               */
  __IM uint32_t        SYNC_PEEK_CLR;                     /**< Sync Channel Values                                */
  PRS_ASYNC_CH_TypeDef ASYNC_CH_CLR[16U];                 /**< Async Channel registers                            */
  PRS_SYNC_CH_TypeDef  SYNC_CH_CLR[4U];                   /**< Sync Channel registers                             */
  __IOM uint32_t       CONSUMER_CMU_CALDN_CLR;            /**< CALDN consumer register                            */
  __IOM uint32_t       CONSUMER_CMU_CALUP_CLR;            /**< CALUP Consumer register                            */
  __IOM uint32_t       CONSUMER_EUSART0_CLK_CLR;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART0_RX_CLR;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART0_TRIGGER_CLR;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_EUSART1_CLK_CLR;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART1_RX_CLR;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART1_TRIGGER_CLR;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_FRC_RXRAW_CLR;            /**< RXRAW consumer register                            */
  __IOM uint32_t       CONSUMER_IADC0_SCANTRIGGER_CLR;    /**< SCAN consumer register                             */
  __IOM uint32_t       CONSUMER_IADC0_SINGLETRIGGER_CLR;  /**< SINGLE Consumer register                           */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ0_CLR;     /**< DMAREQ0 consumer register                          */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ1_CLR;     /**< DMAREQ1 Consumer register                          */
  __IOM uint32_t       CONSUMER_LETIMER0_CLEAR_CLR;       /**< CLEAR consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_START_CLR;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_STOP_CLR;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_MODEM_DIN_CLR;            /**< DIN consumer register                              */
  __IOM uint32_t       CONSUMER_MODEM_PAEN_CLR;           /**< PAEN Consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S0IN_CLR;           /**< S0IN consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S1IN_CLR;           /**< S1IN Consumer register                             */
  __IOM uint32_t       CONSUMER_PROTIMER_CC0_CLR;         /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC1_CLR;         /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC2_CLR;         /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC3_CLR;         /**< CC3 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC4_CLR;         /**< CC4 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTPAUSE_CLR;    /**< LBTPAUSE Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTART_CLR;    /**< LBTSTART Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTOP_CLR;     /**< LBTSTOP Consumer register                          */
  __IOM uint32_t       CONSUMER_PROTIMER_RTCCTRIGGER_CLR; /**< RTCCTRIGGER Consumer register                      */
  __IOM uint32_t       CONSUMER_PROTIMER_START_CLR;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_PROTIMER_STOP_CLR;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_CLR_CLR;              /**< CLR consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN0_CLR;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN1_CLR;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN2_CLR;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN3_CLR;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_FORCETX_CLR;          /**< FORCETX Consumer register                          */
  __IOM uint32_t       CONSUMER_RAC_RXDIS_CLR;            /**< RXDIS Consumer register                            */
  __IOM uint32_t       CONSUMER_RAC_RXEN_CLR;             /**< RXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_TXEN_CLR;             /**< TXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC25_CLR; /**< TAMPERSRC25 consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC26_CLR; /**< TAMPERSRC26 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC27_CLR; /**< TAMPERSRC27 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC28_CLR; /**< TAMPERSRC28 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC29_CLR; /**< TAMPERSRC29 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC30_CLR; /**< TAMPERSRC30 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC31_CLR; /**< TAMPERSRC31 Consumer register                      */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN0_CLR;          /**< IN0 consumer register                              */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN1_CLR;          /**< IN1 Consumer register                              */
  __IOM uint32_t       CONSUMER_HFXO0_OSCREQ_CLR;         /**< OSCREQ consumer register                           */
  __IOM uint32_t       CONSUMER_HFXO0_TIMEOUT_CLR;        /**< TIMEOUT Consumer register                          */
  __IOM uint32_t       CONSUMER_CORE_CTIIN0_CLR;          /**< CTI consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN1_CLR;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN2_CLR;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN3_CLR;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_M33RXEV_CLR;         /**< M33 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC0_CLR;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC1_CLR;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC2_CLR;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTI_CLR;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS1_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS2_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC0_CLR;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC1_CLR;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC2_CLR;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTI_CLR;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS1_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS2_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC0_CLR;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC1_CLR;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC2_CLR;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTI_CLR;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS1_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS2_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC0_CLR;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC1_CLR;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC2_CLR;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTI_CLR;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS1_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS2_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC0_CLR;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC1_CLR;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC2_CLR;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTI_CLR;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS1_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS2_CLR;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_CLK_CLR;           /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_IR_CLR;            /**< IR Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_RX_CLR;            /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_TRIGGER_CLR;       /**< TRIGGER Consumer register                          */
  uint32_t             RESERVED7[3U];                     /**< Reserved for future use                            */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH0_CLR;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH1_CLR;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH0_CLR;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH1_CLR;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH0_CLR;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH1_CLR;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH0_CLR;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH1_CLR;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_WDOG0_SRC0_CLR;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG0_SRC1_CLR;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC0_CLR;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC1_CLR;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       RPURATD0_CLR;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD1_CLR;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD2_CLR;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD3_CLR;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD4_CLR;                      /**< Root Access Type Descriptor Register               */
  uint32_t             RESERVED8[888U];                   /**< Reserved for future use                            */
  __IM uint32_t        IPVERSION_TGL;                     /**< PRS IPVERSION                                      */
  uint32_t             RESERVED9[1U];                     /**< Reserved for future use                            */
  __IOM uint32_t       ASYNC_SWPULSE_TGL;                 /**< Software Pulse Register                            */
  __IOM uint32_t       ASYNC_SWLEVEL_TGL;                 /**< Software Level Register                            */
  __IM uint32_t        ASYNC_PEEK_TGL;                    /**< Async Channel Values                               */
  __IM uint32_t        SYNC_PEEK_TGL;                     /**< Sync Channel Values                                */
  PRS_ASYNC_CH_TypeDef ASYNC_CH_TGL[16U];                 /**< Async Channel registers                            */
  PRS_SYNC_CH_TypeDef  SYNC_CH_TGL[4U];                   /**< Sync Channel registers                             */
  __IOM uint32_t       CONSUMER_CMU_CALDN_TGL;            /**< CALDN consumer register                            */
  __IOM uint32_t       CONSUMER_CMU_CALUP_TGL;            /**< CALUP Consumer register                            */
  __IOM uint32_t       CONSUMER_EUSART0_CLK_TGL;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART0_RX_TGL;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART0_TRIGGER_TGL;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_EUSART1_CLK_TGL;          /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_EUSART1_RX_TGL;           /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_EUSART1_TRIGGER_TGL;      /**< TRIGGER Consumer register                          */
  __IOM uint32_t       CONSUMER_FRC_RXRAW_TGL;            /**< RXRAW consumer register                            */
  __IOM uint32_t       CONSUMER_IADC0_SCANTRIGGER_TGL;    /**< SCAN consumer register                             */
  __IOM uint32_t       CONSUMER_IADC0_SINGLETRIGGER_TGL;  /**< SINGLE Consumer register                           */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ0_TGL;     /**< DMAREQ0 consumer register                          */
  __IOM uint32_t       CONSUMER_LDMAXBAR_DMAREQ1_TGL;     /**< DMAREQ1 Consumer register                          */
  __IOM uint32_t       CONSUMER_LETIMER0_CLEAR_TGL;       /**< CLEAR consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_START_TGL;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_LETIMER0_STOP_TGL;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_MODEM_DIN_TGL;            /**< DIN consumer register                              */
  __IOM uint32_t       CONSUMER_MODEM_PAEN_TGL;           /**< PAEN Consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S0IN_TGL;           /**< S0IN consumer register                             */
  __IOM uint32_t       CONSUMER_PCNT0_S1IN_TGL;           /**< S1IN Consumer register                             */
  __IOM uint32_t       CONSUMER_PROTIMER_CC0_TGL;         /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC1_TGL;         /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC2_TGL;         /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC3_TGL;         /**< CC3 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_CC4_TGL;         /**< CC4 Consumer register                              */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTPAUSE_TGL;    /**< LBTPAUSE Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTART_TGL;    /**< LBTSTART Consumer register                         */
  __IOM uint32_t       CONSUMER_PROTIMER_LBTSTOP_TGL;     /**< LBTSTOP Consumer register                          */
  __IOM uint32_t       CONSUMER_PROTIMER_RTCCTRIGGER_TGL; /**< RTCCTRIGGER Consumer register                      */
  __IOM uint32_t       CONSUMER_PROTIMER_START_TGL;       /**< START Consumer register                            */
  __IOM uint32_t       CONSUMER_PROTIMER_STOP_TGL;        /**< STOP Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_CLR_TGL;              /**< CLR consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN0_TGL;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN1_TGL;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN2_TGL;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_CTIIN3_TGL;           /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_RAC_FORCETX_TGL;          /**< FORCETX Consumer register                          */
  __IOM uint32_t       CONSUMER_RAC_RXDIS_TGL;            /**< RXDIS Consumer register                            */
  __IOM uint32_t       CONSUMER_RAC_RXEN_TGL;             /**< RXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_RAC_TXEN_TGL;             /**< TXEN Consumer register                             */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC25_TGL; /**< TAMPERSRC25 consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC26_TGL; /**< TAMPERSRC26 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC27_TGL; /**< TAMPERSRC27 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC28_TGL; /**< TAMPERSRC28 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC29_TGL; /**< TAMPERSRC29 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC30_TGL; /**< TAMPERSRC30 Consumer register                      */
  __IOM uint32_t       CONSUMER_SETAMPER_TAMPERSRC31_TGL; /**< TAMPERSRC31 Consumer register                      */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN0_TGL;          /**< IN0 consumer register                              */
  __IOM uint32_t       CONSUMER_SYSRTC0_IN1_TGL;          /**< IN1 Consumer register                              */
  __IOM uint32_t       CONSUMER_HFXO0_OSCREQ_TGL;         /**< OSCREQ consumer register                           */
  __IOM uint32_t       CONSUMER_HFXO0_TIMEOUT_TGL;        /**< TIMEOUT Consumer register                          */
  __IOM uint32_t       CONSUMER_CORE_CTIIN0_TGL;          /**< CTI consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN1_TGL;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN2_TGL;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_CTIIN3_TGL;          /**< CTI Consumer register                              */
  __IOM uint32_t       CONSUMER_CORE_M33RXEV_TGL;         /**< M33 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC0_TGL;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC1_TGL;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_CC2_TGL;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTI_TGL;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS1_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER0_DTIFS2_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC0_TGL;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC1_TGL;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_CC2_TGL;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTI_TGL;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS1_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER1_DTIFS2_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC0_TGL;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC1_TGL;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_CC2_TGL;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTI_TGL;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS1_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER2_DTIFS2_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC0_TGL;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC1_TGL;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_CC2_TGL;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTI_TGL;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS1_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER3_DTIFS2_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC0_TGL;           /**< CC0 consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC1_TGL;           /**< CC1 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_CC2_TGL;           /**< CC2 Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTI_TGL;           /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS1_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_TIMER4_DTIFS2_TGL;        /**< DTI Consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_CLK_TGL;           /**< CLK consumer register                              */
  __IOM uint32_t       CONSUMER_USART0_IR_TGL;            /**< IR Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_RX_TGL;            /**< RX Consumer register                               */
  __IOM uint32_t       CONSUMER_USART0_TRIGGER_TGL;       /**< TRIGGER Consumer register                          */
  uint32_t             RESERVED10[3U];                    /**< Reserved for future use                            */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH0_TGL;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_ASYNCTRIGCH1_TGL;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH0_TGL;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC0_SYNCTRIGCH1_TGL;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH0_TGL;   /**< ASYNCTRIG consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_ASYNCTRIGCH1_TGL;   /**< ASYNCTRIG Consumer register                        */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH0_TGL;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_VDAC1_SYNCTRIGCH1_TGL;    /**< SYNCTRIG Consumer register                         */
  __IOM uint32_t       CONSUMER_WDOG0_SRC0_TGL;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG0_SRC1_TGL;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC0_TGL;           /**< SRC0 consumer register                             */
  __IOM uint32_t       CONSUMER_WDOG1_SRC1_TGL;           /**< SRC1 Consumer register                             */
  __IOM uint32_t       RPURATD0_TGL;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD1_TGL;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD2_TGL;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD3_TGL;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t       RPURATD4_TGL;                      /**< Root Access Type Descriptor Register               */
} PRS_TypeDef;
/** @} End of group EFR32MG24_PRS */

/**************************************************************************//**
 * @addtogroup EFR32MG24_PRS
 * @{
 * @defgroup EFR32MG24_PRS_BitFields PRS Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for PRS IPVERSION */
#define _PRS_IPVERSION_RESETVALUE                            0x00000003UL                            /**< Default value for PRS_IPVERSION             */
#define _PRS_IPVERSION_MASK                                  0xFFFFFFFFUL                            /**< Mask for PRS_IPVERSION                      */
#define _PRS_IPVERSION_IPVERSION_SHIFT                       0                                       /**< Shift value for PRS_IPVERSION               */
#define _PRS_IPVERSION_IPVERSION_MASK                        0xFFFFFFFFUL                            /**< Bit mask for PRS_IPVERSION                  */
#define _PRS_IPVERSION_IPVERSION_DEFAULT                     0x00000003UL                            /**< Mode DEFAULT for PRS_IPVERSION              */
#define PRS_IPVERSION_IPVERSION_DEFAULT                      (_PRS_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_IPVERSION      */

/* Bit fields for PRS ASYNC_SWPULSE */
#define _PRS_ASYNC_SWPULSE_RESETVALUE                        0x00000000UL                                 /**< Default value for PRS_ASYNC_SWPULSE         */
#define _PRS_ASYNC_SWPULSE_MASK                              0x0000FFFFUL                                 /**< Mask for PRS_ASYNC_SWPULSE                  */
#define PRS_ASYNC_SWPULSE_CH0PULSE                           (0x1UL << 0)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH0PULSE_SHIFT                    0                                            /**< Shift value for PRS_CH0PULSE                */
#define _PRS_ASYNC_SWPULSE_CH0PULSE_MASK                     0x1UL                                        /**< Bit mask for PRS_CH0PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH0PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH0PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH0PULSE_DEFAULT << 0)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH1PULSE                           (0x1UL << 1)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH1PULSE_SHIFT                    1                                            /**< Shift value for PRS_CH1PULSE                */
#define _PRS_ASYNC_SWPULSE_CH1PULSE_MASK                     0x2UL                                        /**< Bit mask for PRS_CH1PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH1PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH1PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH1PULSE_DEFAULT << 1)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH2PULSE                           (0x1UL << 2)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH2PULSE_SHIFT                    2                                            /**< Shift value for PRS_CH2PULSE                */
#define _PRS_ASYNC_SWPULSE_CH2PULSE_MASK                     0x4UL                                        /**< Bit mask for PRS_CH2PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH2PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH2PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH2PULSE_DEFAULT << 2)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH3PULSE                           (0x1UL << 3)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH3PULSE_SHIFT                    3                                            /**< Shift value for PRS_CH3PULSE                */
#define _PRS_ASYNC_SWPULSE_CH3PULSE_MASK                     0x8UL                                        /**< Bit mask for PRS_CH3PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH3PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH3PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH3PULSE_DEFAULT << 3)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH4PULSE                           (0x1UL << 4)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH4PULSE_SHIFT                    4                                            /**< Shift value for PRS_CH4PULSE                */
#define _PRS_ASYNC_SWPULSE_CH4PULSE_MASK                     0x10UL                                       /**< Bit mask for PRS_CH4PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH4PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH4PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH4PULSE_DEFAULT << 4)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH5PULSE                           (0x1UL << 5)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH5PULSE_SHIFT                    5                                            /**< Shift value for PRS_CH5PULSE                */
#define _PRS_ASYNC_SWPULSE_CH5PULSE_MASK                     0x20UL                                       /**< Bit mask for PRS_CH5PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH5PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH5PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH5PULSE_DEFAULT << 5)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH6PULSE                           (0x1UL << 6)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH6PULSE_SHIFT                    6                                            /**< Shift value for PRS_CH6PULSE                */
#define _PRS_ASYNC_SWPULSE_CH6PULSE_MASK                     0x40UL                                       /**< Bit mask for PRS_CH6PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH6PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH6PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH6PULSE_DEFAULT << 6)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH7PULSE                           (0x1UL << 7)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH7PULSE_SHIFT                    7                                            /**< Shift value for PRS_CH7PULSE                */
#define _PRS_ASYNC_SWPULSE_CH7PULSE_MASK                     0x80UL                                       /**< Bit mask for PRS_CH7PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH7PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH7PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH7PULSE_DEFAULT << 7)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH8PULSE                           (0x1UL << 8)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH8PULSE_SHIFT                    8                                            /**< Shift value for PRS_CH8PULSE                */
#define _PRS_ASYNC_SWPULSE_CH8PULSE_MASK                     0x100UL                                      /**< Bit mask for PRS_CH8PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH8PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH8PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH8PULSE_DEFAULT << 8)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH9PULSE                           (0x1UL << 9)                                 /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH9PULSE_SHIFT                    9                                            /**< Shift value for PRS_CH9PULSE                */
#define _PRS_ASYNC_SWPULSE_CH9PULSE_MASK                     0x200UL                                      /**< Bit mask for PRS_CH9PULSE                   */
#define _PRS_ASYNC_SWPULSE_CH9PULSE_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH9PULSE_DEFAULT                   (_PRS_ASYNC_SWPULSE_CH9PULSE_DEFAULT << 9)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH10PULSE                          (0x1UL << 10)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH10PULSE_SHIFT                   10                                           /**< Shift value for PRS_CH10PULSE               */
#define _PRS_ASYNC_SWPULSE_CH10PULSE_MASK                    0x400UL                                      /**< Bit mask for PRS_CH10PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH10PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH10PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH10PULSE_DEFAULT << 10) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH11PULSE                          (0x1UL << 11)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH11PULSE_SHIFT                   11                                           /**< Shift value for PRS_CH11PULSE               */
#define _PRS_ASYNC_SWPULSE_CH11PULSE_MASK                    0x800UL                                      /**< Bit mask for PRS_CH11PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH11PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH11PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH11PULSE_DEFAULT << 11) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH12PULSE                          (0x1UL << 12)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH12PULSE_SHIFT                   12                                           /**< Shift value for PRS_CH12PULSE               */
#define _PRS_ASYNC_SWPULSE_CH12PULSE_MASK                    0x1000UL                                     /**< Bit mask for PRS_CH12PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH12PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH12PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH12PULSE_DEFAULT << 12) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH13PULSE                          (0x1UL << 13)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH13PULSE_SHIFT                   13                                           /**< Shift value for PRS_CH13PULSE               */
#define _PRS_ASYNC_SWPULSE_CH13PULSE_MASK                    0x2000UL                                     /**< Bit mask for PRS_CH13PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH13PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH13PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH13PULSE_DEFAULT << 13) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH14PULSE                          (0x1UL << 14)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH14PULSE_SHIFT                   14                                           /**< Shift value for PRS_CH14PULSE               */
#define _PRS_ASYNC_SWPULSE_CH14PULSE_MASK                    0x4000UL                                     /**< Bit mask for PRS_CH14PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH14PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH14PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH14PULSE_DEFAULT << 14) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */
#define PRS_ASYNC_SWPULSE_CH15PULSE                          (0x1UL << 15)                                /**< Channel pulse                               */
#define _PRS_ASYNC_SWPULSE_CH15PULSE_SHIFT                   15                                           /**< Shift value for PRS_CH15PULSE               */
#define _PRS_ASYNC_SWPULSE_CH15PULSE_MASK                    0x8000UL                                     /**< Bit mask for PRS_CH15PULSE                  */
#define _PRS_ASYNC_SWPULSE_CH15PULSE_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWPULSE          */
#define PRS_ASYNC_SWPULSE_CH15PULSE_DEFAULT                  (_PRS_ASYNC_SWPULSE_CH15PULSE_DEFAULT << 15) /**< Shifted mode DEFAULT for PRS_ASYNC_SWPULSE  */

/* Bit fields for PRS ASYNC_SWLEVEL */
#define _PRS_ASYNC_SWLEVEL_RESETVALUE                        0x00000000UL                                 /**< Default value for PRS_ASYNC_SWLEVEL         */
#define _PRS_ASYNC_SWLEVEL_MASK                              0x0000FFFFUL                                 /**< Mask for PRS_ASYNC_SWLEVEL                  */
#define PRS_ASYNC_SWLEVEL_CH0LEVEL                           (0x1UL << 0)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH0LEVEL_SHIFT                    0                                            /**< Shift value for PRS_CH0LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH0LEVEL_MASK                     0x1UL                                        /**< Bit mask for PRS_CH0LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH0LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH0LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH0LEVEL_DEFAULT << 0)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH1LEVEL                           (0x1UL << 1)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH1LEVEL_SHIFT                    1                                            /**< Shift value for PRS_CH1LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH1LEVEL_MASK                     0x2UL                                        /**< Bit mask for PRS_CH1LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH1LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH1LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH1LEVEL_DEFAULT << 1)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH2LEVEL                           (0x1UL << 2)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH2LEVEL_SHIFT                    2                                            /**< Shift value for PRS_CH2LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH2LEVEL_MASK                     0x4UL                                        /**< Bit mask for PRS_CH2LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH2LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH2LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH2LEVEL_DEFAULT << 2)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH3LEVEL                           (0x1UL << 3)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH3LEVEL_SHIFT                    3                                            /**< Shift value for PRS_CH3LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH3LEVEL_MASK                     0x8UL                                        /**< Bit mask for PRS_CH3LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH3LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH3LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH3LEVEL_DEFAULT << 3)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH4LEVEL                           (0x1UL << 4)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH4LEVEL_SHIFT                    4                                            /**< Shift value for PRS_CH4LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH4LEVEL_MASK                     0x10UL                                       /**< Bit mask for PRS_CH4LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH4LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH4LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH4LEVEL_DEFAULT << 4)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH5LEVEL                           (0x1UL << 5)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH5LEVEL_SHIFT                    5                                            /**< Shift value for PRS_CH5LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH5LEVEL_MASK                     0x20UL                                       /**< Bit mask for PRS_CH5LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH5LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH5LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH5LEVEL_DEFAULT << 5)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH6LEVEL                           (0x1UL << 6)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH6LEVEL_SHIFT                    6                                            /**< Shift value for PRS_CH6LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH6LEVEL_MASK                     0x40UL                                       /**< Bit mask for PRS_CH6LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH6LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH6LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH6LEVEL_DEFAULT << 6)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH7LEVEL                           (0x1UL << 7)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH7LEVEL_SHIFT                    7                                            /**< Shift value for PRS_CH7LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH7LEVEL_MASK                     0x80UL                                       /**< Bit mask for PRS_CH7LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH7LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH7LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH7LEVEL_DEFAULT << 7)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH8LEVEL                           (0x1UL << 8)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH8LEVEL_SHIFT                    8                                            /**< Shift value for PRS_CH8LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH8LEVEL_MASK                     0x100UL                                      /**< Bit mask for PRS_CH8LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH8LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH8LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH8LEVEL_DEFAULT << 8)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH9LEVEL                           (0x1UL << 9)                                 /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH9LEVEL_SHIFT                    9                                            /**< Shift value for PRS_CH9LEVEL                */
#define _PRS_ASYNC_SWLEVEL_CH9LEVEL_MASK                     0x200UL                                      /**< Bit mask for PRS_CH9LEVEL                   */
#define _PRS_ASYNC_SWLEVEL_CH9LEVEL_DEFAULT                  0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH9LEVEL_DEFAULT                   (_PRS_ASYNC_SWLEVEL_CH9LEVEL_DEFAULT << 9)   /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH10LEVEL                          (0x1UL << 10)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH10LEVEL_SHIFT                   10                                           /**< Shift value for PRS_CH10LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH10LEVEL_MASK                    0x400UL                                      /**< Bit mask for PRS_CH10LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH10LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH10LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH10LEVEL_DEFAULT << 10) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH11LEVEL                          (0x1UL << 11)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH11LEVEL_SHIFT                   11                                           /**< Shift value for PRS_CH11LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH11LEVEL_MASK                    0x800UL                                      /**< Bit mask for PRS_CH11LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH11LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH11LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH11LEVEL_DEFAULT << 11) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH12LEVEL                          (0x1UL << 12)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH12LEVEL_SHIFT                   12                                           /**< Shift value for PRS_CH12LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH12LEVEL_MASK                    0x1000UL                                     /**< Bit mask for PRS_CH12LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH12LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH12LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH12LEVEL_DEFAULT << 12) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH13LEVEL                          (0x1UL << 13)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH13LEVEL_SHIFT                   13                                           /**< Shift value for PRS_CH13LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH13LEVEL_MASK                    0x2000UL                                     /**< Bit mask for PRS_CH13LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH13LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH13LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH13LEVEL_DEFAULT << 13) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH14LEVEL                          (0x1UL << 14)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH14LEVEL_SHIFT                   14                                           /**< Shift value for PRS_CH14LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH14LEVEL_MASK                    0x4000UL                                     /**< Bit mask for PRS_CH14LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH14LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH14LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH14LEVEL_DEFAULT << 14) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */
#define PRS_ASYNC_SWLEVEL_CH15LEVEL                          (0x1UL << 15)                                /**< Channel Level                               */
#define _PRS_ASYNC_SWLEVEL_CH15LEVEL_SHIFT                   15                                           /**< Shift value for PRS_CH15LEVEL               */
#define _PRS_ASYNC_SWLEVEL_CH15LEVEL_MASK                    0x8000UL                                     /**< Bit mask for PRS_CH15LEVEL                  */
#define _PRS_ASYNC_SWLEVEL_CH15LEVEL_DEFAULT                 0x00000000UL                                 /**< Mode DEFAULT for PRS_ASYNC_SWLEVEL          */
#define PRS_ASYNC_SWLEVEL_CH15LEVEL_DEFAULT                  (_PRS_ASYNC_SWLEVEL_CH15LEVEL_DEFAULT << 15) /**< Shifted mode DEFAULT for PRS_ASYNC_SWLEVEL  */

/* Bit fields for PRS ASYNC_PEEK */
#define _PRS_ASYNC_PEEK_RESETVALUE                           0x00000000UL                            /**< Default value for PRS_ASYNC_PEEK            */
#define _PRS_ASYNC_PEEK_MASK                                 0x0000FFFFUL                            /**< Mask for PRS_ASYNC_PEEK                     */
#define PRS_ASYNC_PEEK_CH0VAL                                (0x1UL << 0)                            /**< Channel 0 Current Value                     */
#define _PRS_ASYNC_PEEK_CH0VAL_SHIFT                         0                                       /**< Shift value for PRS_CH0VAL                  */
#define _PRS_ASYNC_PEEK_CH0VAL_MASK                          0x1UL                                   /**< Bit mask for PRS_CH0VAL                     */
#define _PRS_ASYNC_PEEK_CH0VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH0VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH0VAL_DEFAULT << 0)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH1VAL                                (0x1UL << 1)                            /**< Channel 1 Current Value                     */
#define _PRS_ASYNC_PEEK_CH1VAL_SHIFT                         1                                       /**< Shift value for PRS_CH1VAL                  */
#define _PRS_ASYNC_PEEK_CH1VAL_MASK                          0x2UL                                   /**< Bit mask for PRS_CH1VAL                     */
#define _PRS_ASYNC_PEEK_CH1VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH1VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH1VAL_DEFAULT << 1)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH2VAL                                (0x1UL << 2)                            /**< Channel 2 Current Value                     */
#define _PRS_ASYNC_PEEK_CH2VAL_SHIFT                         2                                       /**< Shift value for PRS_CH2VAL                  */
#define _PRS_ASYNC_PEEK_CH2VAL_MASK                          0x4UL                                   /**< Bit mask for PRS_CH2VAL                     */
#define _PRS_ASYNC_PEEK_CH2VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH2VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH2VAL_DEFAULT << 2)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH3VAL                                (0x1UL << 3)                            /**< Channel 3 Current Value                     */
#define _PRS_ASYNC_PEEK_CH3VAL_SHIFT                         3                                       /**< Shift value for PRS_CH3VAL                  */
#define _PRS_ASYNC_PEEK_CH3VAL_MASK                          0x8UL                                   /**< Bit mask for PRS_CH3VAL                     */
#define _PRS_ASYNC_PEEK_CH3VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH3VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH3VAL_DEFAULT << 3)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH4VAL                                (0x1UL << 4)                            /**< Channel 4 Current Value                     */
#define _PRS_ASYNC_PEEK_CH4VAL_SHIFT                         4                                       /**< Shift value for PRS_CH4VAL                  */
#define _PRS_ASYNC_PEEK_CH4VAL_MASK                          0x10UL                                  /**< Bit mask for PRS_CH4VAL                     */
#define _PRS_ASYNC_PEEK_CH4VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH4VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH4VAL_DEFAULT << 4)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH5VAL                                (0x1UL << 5)                            /**< Channel 5 Current Value                     */
#define _PRS_ASYNC_PEEK_CH5VAL_SHIFT                         5                                       /**< Shift value for PRS_CH5VAL                  */
#define _PRS_ASYNC_PEEK_CH5VAL_MASK                          0x20UL                                  /**< Bit mask for PRS_CH5VAL                     */
#define _PRS_ASYNC_PEEK_CH5VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH5VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH5VAL_DEFAULT << 5)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH6VAL                                (0x1UL << 6)                            /**< Channel 6 Current Value                     */
#define _PRS_ASYNC_PEEK_CH6VAL_SHIFT                         6                                       /**< Shift value for PRS_CH6VAL                  */
#define _PRS_ASYNC_PEEK_CH6VAL_MASK                          0x40UL                                  /**< Bit mask for PRS_CH6VAL                     */
#define _PRS_ASYNC_PEEK_CH6VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH6VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH6VAL_DEFAULT << 6)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH7VAL                                (0x1UL << 7)                            /**< Channel 7 Current Value                     */
#define _PRS_ASYNC_PEEK_CH7VAL_SHIFT                         7                                       /**< Shift value for PRS_CH7VAL                  */
#define _PRS_ASYNC_PEEK_CH7VAL_MASK                          0x80UL                                  /**< Bit mask for PRS_CH7VAL                     */
#define _PRS_ASYNC_PEEK_CH7VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH7VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH7VAL_DEFAULT << 7)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH8VAL                                (0x1UL << 8)                            /**< Channel 8 Current Value                     */
#define _PRS_ASYNC_PEEK_CH8VAL_SHIFT                         8                                       /**< Shift value for PRS_CH8VAL                  */
#define _PRS_ASYNC_PEEK_CH8VAL_MASK                          0x100UL                                 /**< Bit mask for PRS_CH8VAL                     */
#define _PRS_ASYNC_PEEK_CH8VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH8VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH8VAL_DEFAULT << 8)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH9VAL                                (0x1UL << 9)                            /**< Channel 9 Current Value                     */
#define _PRS_ASYNC_PEEK_CH9VAL_SHIFT                         9                                       /**< Shift value for PRS_CH9VAL                  */
#define _PRS_ASYNC_PEEK_CH9VAL_MASK                          0x200UL                                 /**< Bit mask for PRS_CH9VAL                     */
#define _PRS_ASYNC_PEEK_CH9VAL_DEFAULT                       0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH9VAL_DEFAULT                        (_PRS_ASYNC_PEEK_CH9VAL_DEFAULT << 9)   /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH10VAL                               (0x1UL << 10)                           /**< Channel 10 Current Value                    */
#define _PRS_ASYNC_PEEK_CH10VAL_SHIFT                        10                                      /**< Shift value for PRS_CH10VAL                 */
#define _PRS_ASYNC_PEEK_CH10VAL_MASK                         0x400UL                                 /**< Bit mask for PRS_CH10VAL                    */
#define _PRS_ASYNC_PEEK_CH10VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH10VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH10VAL_DEFAULT << 10) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH11VAL                               (0x1UL << 11)                           /**< Channel 11 Current Value                    */
#define _PRS_ASYNC_PEEK_CH11VAL_SHIFT                        11                                      /**< Shift value for PRS_CH11VAL                 */
#define _PRS_ASYNC_PEEK_CH11VAL_MASK                         0x800UL                                 /**< Bit mask for PRS_CH11VAL                    */
#define _PRS_ASYNC_PEEK_CH11VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH11VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH11VAL_DEFAULT << 11) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH12VAL                               (0x1UL << 12)                           /**< Channel 12 Current Value                    */
#define _PRS_ASYNC_PEEK_CH12VAL_SHIFT                        12                                      /**< Shift value for PRS_CH12VAL                 */
#define _PRS_ASYNC_PEEK_CH12VAL_MASK                         0x1000UL                                /**< Bit mask for PRS_CH12VAL                    */
#define _PRS_ASYNC_PEEK_CH12VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH12VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH12VAL_DEFAULT << 12) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH13VAL                               (0x1UL << 13)                           /**< Channel 13 current value                    */
#define _PRS_ASYNC_PEEK_CH13VAL_SHIFT                        13                                      /**< Shift value for PRS_CH13VAL                 */
#define _PRS_ASYNC_PEEK_CH13VAL_MASK                         0x2000UL                                /**< Bit mask for PRS_CH13VAL                    */
#define _PRS_ASYNC_PEEK_CH13VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH13VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH13VAL_DEFAULT << 13) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH14VAL                               (0x1UL << 14)                           /**< Channel 14 current value                    */
#define _PRS_ASYNC_PEEK_CH14VAL_SHIFT                        14                                      /**< Shift value for PRS_CH14VAL                 */
#define _PRS_ASYNC_PEEK_CH14VAL_MASK                         0x4000UL                                /**< Bit mask for PRS_CH14VAL                    */
#define _PRS_ASYNC_PEEK_CH14VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH14VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH14VAL_DEFAULT << 14) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */
#define PRS_ASYNC_PEEK_CH15VAL                               (0x1UL << 15)                           /**< Channel 15 current value                    */
#define _PRS_ASYNC_PEEK_CH15VAL_SHIFT                        15                                      /**< Shift value for PRS_CH15VAL                 */
#define _PRS_ASYNC_PEEK_CH15VAL_MASK                         0x8000UL                                /**< Bit mask for PRS_CH15VAL                    */
#define _PRS_ASYNC_PEEK_CH15VAL_DEFAULT                      0x00000000UL                            /**< Mode DEFAULT for PRS_ASYNC_PEEK             */
#define PRS_ASYNC_PEEK_CH15VAL_DEFAULT                       (_PRS_ASYNC_PEEK_CH15VAL_DEFAULT << 15) /**< Shifted mode DEFAULT for PRS_ASYNC_PEEK     */

/* Bit fields for PRS SYNC_PEEK */
#define _PRS_SYNC_PEEK_RESETVALUE                            0x00000000UL                         /**< Default value for PRS_SYNC_PEEK             */
#define _PRS_SYNC_PEEK_MASK                                  0x0000000FUL                         /**< Mask for PRS_SYNC_PEEK                      */
#define PRS_SYNC_PEEK_CH0VAL                                 (0x1UL << 0)                         /**< Channel Value                               */
#define _PRS_SYNC_PEEK_CH0VAL_SHIFT                          0                                    /**< Shift value for PRS_CH0VAL                  */
#define _PRS_SYNC_PEEK_CH0VAL_MASK                           0x1UL                                /**< Bit mask for PRS_CH0VAL                     */
#define _PRS_SYNC_PEEK_CH0VAL_DEFAULT                        0x00000000UL                         /**< Mode DEFAULT for PRS_SYNC_PEEK              */
#define PRS_SYNC_PEEK_CH0VAL_DEFAULT                         (_PRS_SYNC_PEEK_CH0VAL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_SYNC_PEEK      */
#define PRS_SYNC_PEEK_CH1VAL                                 (0x1UL << 1)                         /**< Channel Value                               */
#define _PRS_SYNC_PEEK_CH1VAL_SHIFT                          1                                    /**< Shift value for PRS_CH1VAL                  */
#define _PRS_SYNC_PEEK_CH1VAL_MASK                           0x2UL                                /**< Bit mask for PRS_CH1VAL                     */
#define _PRS_SYNC_PEEK_CH1VAL_DEFAULT                        0x00000000UL                         /**< Mode DEFAULT for PRS_SYNC_PEEK              */
#define PRS_SYNC_PEEK_CH1VAL_DEFAULT                         (_PRS_SYNC_PEEK_CH1VAL_DEFAULT << 1) /**< Shifted mode DEFAULT for PRS_SYNC_PEEK      */
#define PRS_SYNC_PEEK_CH2VAL                                 (0x1UL << 2)                         /**< Channel Value                               */
#define _PRS_SYNC_PEEK_CH2VAL_SHIFT                          2                                    /**< Shift value for PRS_CH2VAL                  */
#define _PRS_SYNC_PEEK_CH2VAL_MASK                           0x4UL                                /**< Bit mask for PRS_CH2VAL                     */
#define _PRS_SYNC_PEEK_CH2VAL_DEFAULT                        0x00000000UL                         /**< Mode DEFAULT for PRS_SYNC_PEEK              */
#define PRS_SYNC_PEEK_CH2VAL_DEFAULT                         (_PRS_SYNC_PEEK_CH2VAL_DEFAULT << 2) /**< Shifted mode DEFAULT for PRS_SYNC_PEEK      */
#define PRS_SYNC_PEEK_CH3VAL                                 (0x1UL << 3)                         /**< Channel Value                               */
#define _PRS_SYNC_PEEK_CH3VAL_SHIFT                          3                                    /**< Shift value for PRS_CH3VAL                  */
#define _PRS_SYNC_PEEK_CH3VAL_MASK                           0x8UL                                /**< Bit mask for PRS_CH3VAL                     */
#define _PRS_SYNC_PEEK_CH3VAL_DEFAULT                        0x00000000UL                         /**< Mode DEFAULT for PRS_SYNC_PEEK              */
#define PRS_SYNC_PEEK_CH3VAL_DEFAULT                         (_PRS_SYNC_PEEK_CH3VAL_DEFAULT << 3) /**< Shifted mode DEFAULT for PRS_SYNC_PEEK      */

/* Bit fields for PRS ASYNC_CH_CTRL */
#define _PRS_ASYNC_CH_CTRL_RESETVALUE                        0x000C0000UL                                  /**< Default value for PRS_ASYNC_CH_CTRL         */
#define _PRS_ASYNC_CH_CTRL_MASK                              0x0F0F7F07UL                                  /**< Mask for PRS_ASYNC_CH_CTRL                  */
#define _PRS_ASYNC_CH_CTRL_SIGSEL_SHIFT                      0                                             /**< Shift value for PRS_SIGSEL                  */
#define _PRS_ASYNC_CH_CTRL_SIGSEL_MASK                       0x7UL                                         /**< Bit mask for PRS_SIGSEL                     */
#define _PRS_ASYNC_CH_CTRL_SIGSEL_DEFAULT                    0x00000000UL                                  /**< Mode DEFAULT for PRS_ASYNC_CH_CTRL          */
#define _PRS_ASYNC_CH_CTRL_SIGSEL_NONE                       0x00000000UL                                  /**< Mode NONE for PRS_ASYNC_CH_CTRL             */
#define PRS_ASYNC_CH_CTRL_SIGSEL_DEFAULT                     (_PRS_ASYNC_CH_CTRL_SIGSEL_DEFAULT << 0)      /**< Shifted mode DEFAULT for PRS_ASYNC_CH_CTRL  */
#define PRS_ASYNC_CH_CTRL_SIGSEL_NONE                        (_PRS_ASYNC_CH_CTRL_SIGSEL_NONE << 0)         /**< Shifted mode NONE for PRS_ASYNC_CH_CTRL     */
#define _PRS_ASYNC_CH_CTRL_SOURCESEL_SHIFT                   8                                             /**< Shift value for PRS_SOURCESEL               */
#define _PRS_ASYNC_CH_CTRL_SOURCESEL_MASK                    0x7F00UL                                      /**< Bit mask for PRS_SOURCESEL                  */
#define _PRS_ASYNC_CH_CTRL_SOURCESEL_DEFAULT                 0x00000000UL                                  /**< Mode DEFAULT for PRS_ASYNC_CH_CTRL          */
#define PRS_ASYNC_CH_CTRL_SOURCESEL_DEFAULT                  (_PRS_ASYNC_CH_CTRL_SOURCESEL_DEFAULT << 8)   /**< Shifted mode DEFAULT for PRS_ASYNC_CH_CTRL  */
#define _PRS_ASYNC_CH_CTRL_FNSEL_SHIFT                       16                                            /**< Shift value for PRS_FNSEL                   */
#define _PRS_ASYNC_CH_CTRL_FNSEL_MASK                        0xF0000UL                                     /**< Bit mask for PRS_FNSEL                      */
#define _PRS_ASYNC_CH_CTRL_FNSEL_DEFAULT                     0x0000000CUL                                  /**< Mode DEFAULT for PRS_ASYNC_CH_CTRL          */
#define _PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ZERO                0x00000000UL                                  /**< Mode LOGICAL_ZERO for PRS_ASYNC_CH_CTRL     */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_NOR_B                     0x00000001UL                                  /**< Mode A_NOR_B for PRS_ASYNC_CH_CTRL          */
#define _PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_AND_B                 0x00000002UL                                  /**< Mode NOT_A_AND_B for PRS_ASYNC_CH_CTRL      */
#define _PRS_ASYNC_CH_CTRL_FNSEL_NOT_A                       0x00000003UL                                  /**< Mode NOT_A for PRS_ASYNC_CH_CTRL            */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_AND_NOT_B                 0x00000004UL                                  /**< Mode A_AND_NOT_B for PRS_ASYNC_CH_CTRL      */
#define _PRS_ASYNC_CH_CTRL_FNSEL_NOT_B                       0x00000005UL                                  /**< Mode NOT_B for PRS_ASYNC_CH_CTRL            */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_XOR_B                     0x00000006UL                                  /**< Mode A_XOR_B for PRS_ASYNC_CH_CTRL          */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_NAND_B                    0x00000007UL                                  /**< Mode A_NAND_B for PRS_ASYNC_CH_CTRL         */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_AND_B                     0x00000008UL                                  /**< Mode A_AND_B for PRS_ASYNC_CH_CTRL          */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_XNOR_B                    0x00000009UL                                  /**< Mode A_XNOR_B for PRS_ASYNC_CH_CTRL         */
#define _PRS_ASYNC_CH_CTRL_FNSEL_B                           0x0000000AUL                                  /**< Mode B for PRS_ASYNC_CH_CTRL                */
#define _PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_OR_B                  0x0000000BUL                                  /**< Mode NOT_A_OR_B for PRS_ASYNC_CH_CTRL       */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A                           0x0000000CUL                                  /**< Mode A for PRS_ASYNC_CH_CTRL                */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_OR_NOT_B                  0x0000000DUL                                  /**< Mode A_OR_NOT_B for PRS_ASYNC_CH_CTRL       */
#define _PRS_ASYNC_CH_CTRL_FNSEL_A_OR_B                      0x0000000EUL                                  /**< Mode A_OR_B for PRS_ASYNC_CH_CTRL           */
#define _PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ONE                 0x0000000FUL                                  /**< Mode LOGICAL_ONE for PRS_ASYNC_CH_CTRL      */
#define PRS_ASYNC_CH_CTRL_FNSEL_DEFAULT                      (_PRS_ASYNC_CH_CTRL_FNSEL_DEFAULT << 16)      /**< Shifted mode DEFAULT for PRS_ASYNC_CH_CTRL  */
#define PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ZERO                 (_PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ZERO << 16) /**< Shifted mode LOGICAL_ZERO for PRS_ASYNC_CH_CTRL*/
#define PRS_ASYNC_CH_CTRL_FNSEL_A_NOR_B                      (_PRS_ASYNC_CH_CTRL_FNSEL_A_NOR_B << 16)      /**< Shifted mode A_NOR_B for PRS_ASYNC_CH_CTRL  */
#define PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_AND_B                  (_PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_AND_B << 16)  /**< Shifted mode NOT_A_AND_B for PRS_ASYNC_CH_CTRL*/
#define PRS_ASYNC_CH_CTRL_FNSEL_NOT_A                        (_PRS_ASYNC_CH_CTRL_FNSEL_NOT_A << 16)        /**< Shifted mode NOT_A for PRS_ASYNC_CH_CTRL    */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_AND_NOT_B                  (_PRS_ASYNC_CH_CTRL_FNSEL_A_AND_NOT_B << 16)  /**< Shifted mode A_AND_NOT_B for PRS_ASYNC_CH_CTRL*/
#define PRS_ASYNC_CH_CTRL_FNSEL_NOT_B                        (_PRS_ASYNC_CH_CTRL_FNSEL_NOT_B << 16)        /**< Shifted mode NOT_B for PRS_ASYNC_CH_CTRL    */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_XOR_B                      (_PRS_ASYNC_CH_CTRL_FNSEL_A_XOR_B << 16)      /**< Shifted mode A_XOR_B for PRS_ASYNC_CH_CTRL  */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_NAND_B                     (_PRS_ASYNC_CH_CTRL_FNSEL_A_NAND_B << 16)     /**< Shifted mode A_NAND_B for PRS_ASYNC_CH_CTRL */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_AND_B                      (_PRS_ASYNC_CH_CTRL_FNSEL_A_AND_B << 16)      /**< Shifted mode A_AND_B for PRS_ASYNC_CH_CTRL  */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_XNOR_B                     (_PRS_ASYNC_CH_CTRL_FNSEL_A_XNOR_B << 16)     /**< Shifted mode A_XNOR_B for PRS_ASYNC_CH_CTRL */
#define PRS_ASYNC_CH_CTRL_FNSEL_B                            (_PRS_ASYNC_CH_CTRL_FNSEL_B << 16)            /**< Shifted mode B for PRS_ASYNC_CH_CTRL        */
#define PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_OR_B                   (_PRS_ASYNC_CH_CTRL_FNSEL_NOT_A_OR_B << 16)   /**< Shifted mode NOT_A_OR_B for PRS_ASYNC_CH_CTRL*/
#define PRS_ASYNC_CH_CTRL_FNSEL_A                            (_PRS_ASYNC_CH_CTRL_FNSEL_A << 16)            /**< Shifted mode A for PRS_ASYNC_CH_CTRL        */
#define PRS_ASYNC_CH_CTRL_FNSEL_A_OR_NOT_B                   (_PRS_ASYNC_CH_CTRL_FNSEL_A_OR_NOT_B << 16)   /**< Shifted mode A_OR_NOT_B for PRS_ASYNC_CH_CTRL*/
#define PRS_ASYNC_CH_CTRL_FNSEL_A_OR_B                       (_PRS_ASYNC_CH_CTRL_FNSEL_A_OR_B << 16)       /**< Shifted mode A_OR_B for PRS_ASYNC_CH_CTRL   */
#define PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ONE                  (_PRS_ASYNC_CH_CTRL_FNSEL_LOGICAL_ONE << 16)  /**< Shifted mode LOGICAL_ONE for PRS_ASYNC_CH_CTRL*/
#define _PRS_ASYNC_CH_CTRL_AUXSEL_SHIFT                      24                                            /**< Shift value for PRS_AUXSEL                  */
#define _PRS_ASYNC_CH_CTRL_AUXSEL_MASK                       0xF000000UL                                   /**< Bit mask for PRS_AUXSEL                     */
#define _PRS_ASYNC_CH_CTRL_AUXSEL_DEFAULT                    0x00000000UL                                  /**< Mode DEFAULT for PRS_ASYNC_CH_CTRL          */
#define PRS_ASYNC_CH_CTRL_AUXSEL_DEFAULT                     (_PRS_ASYNC_CH_CTRL_AUXSEL_DEFAULT << 24)     /**< Shifted mode DEFAULT for PRS_ASYNC_CH_CTRL  */

/* Bit fields for PRS SYNC_CH_CTRL */
#define _PRS_SYNC_CH_CTRL_RESETVALUE                         0x00000000UL                               /**< Default value for PRS_SYNC_CH_CTRL          */
#define _PRS_SYNC_CH_CTRL_MASK                               0x00007F07UL                               /**< Mask for PRS_SYNC_CH_CTRL                   */
#define _PRS_SYNC_CH_CTRL_SIGSEL_SHIFT                       0                                          /**< Shift value for PRS_SIGSEL                  */
#define _PRS_SYNC_CH_CTRL_SIGSEL_MASK                        0x7UL                                      /**< Bit mask for PRS_SIGSEL                     */
#define _PRS_SYNC_CH_CTRL_SIGSEL_DEFAULT                     0x00000000UL                               /**< Mode DEFAULT for PRS_SYNC_CH_CTRL           */
#define _PRS_SYNC_CH_CTRL_SIGSEL_NONE                        0x00000000UL                               /**< Mode NONE for PRS_SYNC_CH_CTRL              */
#define PRS_SYNC_CH_CTRL_SIGSEL_DEFAULT                      (_PRS_SYNC_CH_CTRL_SIGSEL_DEFAULT << 0)    /**< Shifted mode DEFAULT for PRS_SYNC_CH_CTRL   */
#define PRS_SYNC_CH_CTRL_SIGSEL_NONE                         (_PRS_SYNC_CH_CTRL_SIGSEL_NONE << 0)       /**< Shifted mode NONE for PRS_SYNC_CH_CTRL      */
#define _PRS_SYNC_CH_CTRL_SOURCESEL_SHIFT                    8                                          /**< Shift value for PRS_SOURCESEL               */
#define _PRS_SYNC_CH_CTRL_SOURCESEL_MASK                     0x7F00UL                                   /**< Bit mask for PRS_SOURCESEL                  */
#define _PRS_SYNC_CH_CTRL_SOURCESEL_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for PRS_SYNC_CH_CTRL           */
#define PRS_SYNC_CH_CTRL_SOURCESEL_DEFAULT                   (_PRS_SYNC_CH_CTRL_SOURCESEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_SYNC_CH_CTRL   */

/* Bit fields for PRS CONSUMER_CMU_CALDN */
#define _PRS_CONSUMER_CMU_CALDN_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_CMU_CALDN    */
#define _PRS_CONSUMER_CMU_CALDN_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_CMU_CALDN             */
#define _PRS_CONSUMER_CMU_CALDN_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CMU_CALDN_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CMU_CALDN_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_CMU_CALDN     */
#define PRS_CONSUMER_CMU_CALDN_PRSSEL_DEFAULT                (_PRS_CONSUMER_CMU_CALDN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CMU_CALDN*/

/* Bit fields for PRS CONSUMER_CMU_CALUP */
#define _PRS_CONSUMER_CMU_CALUP_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_CMU_CALUP    */
#define _PRS_CONSUMER_CMU_CALUP_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_CMU_CALUP             */
#define _PRS_CONSUMER_CMU_CALUP_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CMU_CALUP_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CMU_CALUP_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_CMU_CALUP     */
#define PRS_CONSUMER_CMU_CALUP_PRSSEL_DEFAULT                (_PRS_CONSUMER_CMU_CALUP_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CMU_CALUP*/

/* Bit fields for PRS CONSUMER_EUSART0_CLK */
#define _PRS_CONSUMER_EUSART0_CLK_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_EUSART0_CLK  */
#define _PRS_CONSUMER_EUSART0_CLK_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_EUSART0_CLK           */
#define _PRS_CONSUMER_EUSART0_CLK_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART0_CLK_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART0_CLK_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_EUSART0_CLK   */
#define PRS_CONSUMER_EUSART0_CLK_PRSSEL_DEFAULT              (_PRS_CONSUMER_EUSART0_CLK_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART0_CLK*/

/* Bit fields for PRS CONSUMER_EUSART0_RX */
#define _PRS_CONSUMER_EUSART0_RX_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_EUSART0_RX   */
#define _PRS_CONSUMER_EUSART0_RX_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_EUSART0_RX            */
#define _PRS_CONSUMER_EUSART0_RX_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART0_RX_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART0_RX_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_EUSART0_RX    */
#define PRS_CONSUMER_EUSART0_RX_PRSSEL_DEFAULT               (_PRS_CONSUMER_EUSART0_RX_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART0_RX*/

/* Bit fields for PRS CONSUMER_EUSART0_TRIGGER */
#define _PRS_CONSUMER_EUSART0_TRIGGER_RESETVALUE             0x00000000UL                                        /**< Default value for PRS_CONSUMER_EUSART0_TRIGGER*/
#define _PRS_CONSUMER_EUSART0_TRIGGER_MASK                   0x0000000FUL                                        /**< Mask for PRS_CONSUMER_EUSART0_TRIGGER       */
#define _PRS_CONSUMER_EUSART0_TRIGGER_PRSSEL_SHIFT           0                                                   /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART0_TRIGGER_PRSSEL_MASK            0xFUL                                               /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART0_TRIGGER_PRSSEL_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for PRS_CONSUMER_EUSART0_TRIGGER*/
#define PRS_CONSUMER_EUSART0_TRIGGER_PRSSEL_DEFAULT          (_PRS_CONSUMER_EUSART0_TRIGGER_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART0_TRIGGER*/

/* Bit fields for PRS CONSUMER_EUSART1_CLK */
#define _PRS_CONSUMER_EUSART1_CLK_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_EUSART1_CLK  */
#define _PRS_CONSUMER_EUSART1_CLK_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_EUSART1_CLK           */
#define _PRS_CONSUMER_EUSART1_CLK_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART1_CLK_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART1_CLK_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_EUSART1_CLK   */
#define PRS_CONSUMER_EUSART1_CLK_PRSSEL_DEFAULT              (_PRS_CONSUMER_EUSART1_CLK_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART1_CLK*/

/* Bit fields for PRS CONSUMER_EUSART1_RX */
#define _PRS_CONSUMER_EUSART1_RX_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_EUSART1_RX   */
#define _PRS_CONSUMER_EUSART1_RX_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_EUSART1_RX            */
#define _PRS_CONSUMER_EUSART1_RX_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART1_RX_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART1_RX_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_EUSART1_RX    */
#define PRS_CONSUMER_EUSART1_RX_PRSSEL_DEFAULT               (_PRS_CONSUMER_EUSART1_RX_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART1_RX*/

/* Bit fields for PRS CONSUMER_EUSART1_TRIGGER */
#define _PRS_CONSUMER_EUSART1_TRIGGER_RESETVALUE             0x00000000UL                                        /**< Default value for PRS_CONSUMER_EUSART1_TRIGGER*/
#define _PRS_CONSUMER_EUSART1_TRIGGER_MASK                   0x0000000FUL                                        /**< Mask for PRS_CONSUMER_EUSART1_TRIGGER       */
#define _PRS_CONSUMER_EUSART1_TRIGGER_PRSSEL_SHIFT           0                                                   /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_EUSART1_TRIGGER_PRSSEL_MASK            0xFUL                                               /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_EUSART1_TRIGGER_PRSSEL_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for PRS_CONSUMER_EUSART1_TRIGGER*/
#define PRS_CONSUMER_EUSART1_TRIGGER_PRSSEL_DEFAULT          (_PRS_CONSUMER_EUSART1_TRIGGER_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_EUSART1_TRIGGER*/

/* Bit fields for PRS CONSUMER_FRC_RXRAW */
#define _PRS_CONSUMER_FRC_RXRAW_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_FRC_RXRAW    */
#define _PRS_CONSUMER_FRC_RXRAW_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_FRC_RXRAW             */
#define _PRS_CONSUMER_FRC_RXRAW_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_FRC_RXRAW_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_FRC_RXRAW_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_FRC_RXRAW     */
#define PRS_CONSUMER_FRC_RXRAW_PRSSEL_DEFAULT                (_PRS_CONSUMER_FRC_RXRAW_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_FRC_RXRAW*/

/* Bit fields for PRS CONSUMER_IADC0_SCANTRIGGER */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_RESETVALUE           0x00000000UL                                           /**< Default value for PRS_CONSUMER_IADC0_SCANTRIGGER*/
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_MASK                 0x0000030FUL                                           /**< Mask for PRS_CONSUMER_IADC0_SCANTRIGGER     */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_PRSSEL_SHIFT         0                                                      /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_PRSSEL_MASK          0xFUL                                                  /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_PRSSEL_DEFAULT       0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_IADC0_SCANTRIGGER*/
#define PRS_CONSUMER_IADC0_SCANTRIGGER_PRSSEL_DEFAULT        (_PRS_CONSUMER_IADC0_SCANTRIGGER_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_IADC0_SCANTRIGGER*/
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_SPRSSEL_SHIFT        8                                                      /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_SPRSSEL_MASK         0x300UL                                                /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_IADC0_SCANTRIGGER_SPRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_IADC0_SCANTRIGGER*/
#define PRS_CONSUMER_IADC0_SCANTRIGGER_SPRSSEL_DEFAULT       (_PRS_CONSUMER_IADC0_SCANTRIGGER_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_IADC0_SCANTRIGGER*/

/* Bit fields for PRS CONSUMER_IADC0_SINGLETRIGGER */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_RESETVALUE         0x00000000UL                                             /**< Default value for PRS_CONSUMER_IADC0_SINGLETRIGGER*/
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_MASK               0x0000030FUL                                             /**< Mask for PRS_CONSUMER_IADC0_SINGLETRIGGER   */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_PRSSEL_SHIFT       0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_PRSSEL_MASK        0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_PRSSEL_DEFAULT     0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_IADC0_SINGLETRIGGER*/
#define PRS_CONSUMER_IADC0_SINGLETRIGGER_PRSSEL_DEFAULT      (_PRS_CONSUMER_IADC0_SINGLETRIGGER_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_IADC0_SINGLETRIGGER*/
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_SPRSSEL_SHIFT      8                                                        /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_SPRSSEL_MASK       0x300UL                                                  /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_IADC0_SINGLETRIGGER_SPRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_IADC0_SINGLETRIGGER*/
#define PRS_CONSUMER_IADC0_SINGLETRIGGER_SPRSSEL_DEFAULT     (_PRS_CONSUMER_IADC0_SINGLETRIGGER_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_IADC0_SINGLETRIGGER*/

/* Bit fields for PRS CONSUMER_LDMAXBAR_DMAREQ0 */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ0_RESETVALUE            0x00000000UL                                         /**< Default value for PRS_CONSUMER_LDMAXBAR_DMAREQ0*/
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ0_MASK                  0x0000000FUL                                         /**< Mask for PRS_CONSUMER_LDMAXBAR_DMAREQ0      */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ0_PRSSEL_SHIFT          0                                                    /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ0_PRSSEL_MASK           0xFUL                                                /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ0_PRSSEL_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_CONSUMER_LDMAXBAR_DMAREQ0*/
#define PRS_CONSUMER_LDMAXBAR_DMAREQ0_PRSSEL_DEFAULT         (_PRS_CONSUMER_LDMAXBAR_DMAREQ0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_LDMAXBAR_DMAREQ0*/

/* Bit fields for PRS CONSUMER_LDMAXBAR_DMAREQ1 */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ1_RESETVALUE            0x00000000UL                                         /**< Default value for PRS_CONSUMER_LDMAXBAR_DMAREQ1*/
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ1_MASK                  0x0000000FUL                                         /**< Mask for PRS_CONSUMER_LDMAXBAR_DMAREQ1      */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ1_PRSSEL_SHIFT          0                                                    /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ1_PRSSEL_MASK           0xFUL                                                /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_LDMAXBAR_DMAREQ1_PRSSEL_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_CONSUMER_LDMAXBAR_DMAREQ1*/
#define PRS_CONSUMER_LDMAXBAR_DMAREQ1_PRSSEL_DEFAULT         (_PRS_CONSUMER_LDMAXBAR_DMAREQ1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_LDMAXBAR_DMAREQ1*/

/* Bit fields for PRS CONSUMER_LETIMER0_CLEAR */
#define _PRS_CONSUMER_LETIMER0_CLEAR_RESETVALUE              0x00000000UL                                       /**< Default value for PRS_CONSUMER_LETIMER0_CLEAR*/
#define _PRS_CONSUMER_LETIMER0_CLEAR_MASK                    0x0000000FUL                                       /**< Mask for PRS_CONSUMER_LETIMER0_CLEAR        */
#define _PRS_CONSUMER_LETIMER0_CLEAR_PRSSEL_SHIFT            0                                                  /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_LETIMER0_CLEAR_PRSSEL_MASK             0xFUL                                              /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_LETIMER0_CLEAR_PRSSEL_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for PRS_CONSUMER_LETIMER0_CLEAR*/
#define PRS_CONSUMER_LETIMER0_CLEAR_PRSSEL_DEFAULT           (_PRS_CONSUMER_LETIMER0_CLEAR_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_LETIMER0_CLEAR*/

/* Bit fields for PRS CONSUMER_LETIMER0_START */
#define _PRS_CONSUMER_LETIMER0_START_RESETVALUE              0x00000000UL                                       /**< Default value for PRS_CONSUMER_LETIMER0_START*/
#define _PRS_CONSUMER_LETIMER0_START_MASK                    0x0000000FUL                                       /**< Mask for PRS_CONSUMER_LETIMER0_START        */
#define _PRS_CONSUMER_LETIMER0_START_PRSSEL_SHIFT            0                                                  /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_LETIMER0_START_PRSSEL_MASK             0xFUL                                              /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_LETIMER0_START_PRSSEL_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for PRS_CONSUMER_LETIMER0_START*/
#define PRS_CONSUMER_LETIMER0_START_PRSSEL_DEFAULT           (_PRS_CONSUMER_LETIMER0_START_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_LETIMER0_START*/

/* Bit fields for PRS CONSUMER_LETIMER0_STOP */
#define _PRS_CONSUMER_LETIMER0_STOP_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_LETIMER0_STOP*/
#define _PRS_CONSUMER_LETIMER0_STOP_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_LETIMER0_STOP         */
#define _PRS_CONSUMER_LETIMER0_STOP_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_LETIMER0_STOP_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_LETIMER0_STOP_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_LETIMER0_STOP */
#define PRS_CONSUMER_LETIMER0_STOP_PRSSEL_DEFAULT            (_PRS_CONSUMER_LETIMER0_STOP_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_LETIMER0_STOP*/

/* Bit fields for PRS CONSUMER_MODEM_DIN */
#define _PRS_CONSUMER_MODEM_DIN_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_MODEM_DIN    */
#define _PRS_CONSUMER_MODEM_DIN_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_MODEM_DIN             */
#define _PRS_CONSUMER_MODEM_DIN_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_MODEM_DIN_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_MODEM_DIN_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_MODEM_DIN     */
#define PRS_CONSUMER_MODEM_DIN_PRSSEL_DEFAULT                (_PRS_CONSUMER_MODEM_DIN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_MODEM_DIN*/

/* Bit fields for PRS CONSUMER_MODEM_PAEN */
#define _PRS_CONSUMER_MODEM_PAEN_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_MODEM_PAEN   */
#define _PRS_CONSUMER_MODEM_PAEN_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_MODEM_PAEN            */
#define _PRS_CONSUMER_MODEM_PAEN_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_MODEM_PAEN_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_MODEM_PAEN_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_MODEM_PAEN    */
#define PRS_CONSUMER_MODEM_PAEN_PRSSEL_DEFAULT               (_PRS_CONSUMER_MODEM_PAEN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_MODEM_PAEN*/

/* Bit fields for PRS CONSUMER_PCNT0_S0IN */
#define _PRS_CONSUMER_PCNT0_S0IN_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_PCNT0_S0IN   */
#define _PRS_CONSUMER_PCNT0_S0IN_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_PCNT0_S0IN            */
#define _PRS_CONSUMER_PCNT0_S0IN_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PCNT0_S0IN_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PCNT0_S0IN_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_PCNT0_S0IN    */
#define PRS_CONSUMER_PCNT0_S0IN_PRSSEL_DEFAULT               (_PRS_CONSUMER_PCNT0_S0IN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PCNT0_S0IN*/

/* Bit fields for PRS CONSUMER_PCNT0_S1IN */
#define _PRS_CONSUMER_PCNT0_S1IN_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_PCNT0_S1IN   */
#define _PRS_CONSUMER_PCNT0_S1IN_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_PCNT0_S1IN            */
#define _PRS_CONSUMER_PCNT0_S1IN_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PCNT0_S1IN_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PCNT0_S1IN_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_PCNT0_S1IN    */
#define PRS_CONSUMER_PCNT0_S1IN_PRSSEL_DEFAULT               (_PRS_CONSUMER_PCNT0_S1IN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PCNT0_S1IN*/

/* Bit fields for PRS CONSUMER_PROTIMER_CC0 */
#define _PRS_CONSUMER_PROTIMER_CC0_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_PROTIMER_CC0 */
#define _PRS_CONSUMER_PROTIMER_CC0_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_PROTIMER_CC0          */
#define _PRS_CONSUMER_PROTIMER_CC0_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_CC0_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_CC0_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_CC0  */
#define PRS_CONSUMER_PROTIMER_CC0_PRSSEL_DEFAULT             (_PRS_CONSUMER_PROTIMER_CC0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_CC0*/

/* Bit fields for PRS CONSUMER_PROTIMER_CC1 */
#define _PRS_CONSUMER_PROTIMER_CC1_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_PROTIMER_CC1 */
#define _PRS_CONSUMER_PROTIMER_CC1_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_PROTIMER_CC1          */
#define _PRS_CONSUMER_PROTIMER_CC1_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_CC1_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_CC1_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_CC1  */
#define PRS_CONSUMER_PROTIMER_CC1_PRSSEL_DEFAULT             (_PRS_CONSUMER_PROTIMER_CC1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_CC1*/

/* Bit fields for PRS CONSUMER_PROTIMER_CC2 */
#define _PRS_CONSUMER_PROTIMER_CC2_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_PROTIMER_CC2 */
#define _PRS_CONSUMER_PROTIMER_CC2_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_PROTIMER_CC2          */
#define _PRS_CONSUMER_PROTIMER_CC2_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_CC2_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_CC2_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_CC2  */
#define PRS_CONSUMER_PROTIMER_CC2_PRSSEL_DEFAULT             (_PRS_CONSUMER_PROTIMER_CC2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_CC2*/

/* Bit fields for PRS CONSUMER_PROTIMER_CC3 */
#define _PRS_CONSUMER_PROTIMER_CC3_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_PROTIMER_CC3 */
#define _PRS_CONSUMER_PROTIMER_CC3_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_PROTIMER_CC3          */
#define _PRS_CONSUMER_PROTIMER_CC3_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_CC3_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_CC3_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_CC3  */
#define PRS_CONSUMER_PROTIMER_CC3_PRSSEL_DEFAULT             (_PRS_CONSUMER_PROTIMER_CC3_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_CC3*/

/* Bit fields for PRS CONSUMER_PROTIMER_CC4 */
#define _PRS_CONSUMER_PROTIMER_CC4_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_PROTIMER_CC4 */
#define _PRS_CONSUMER_PROTIMER_CC4_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_PROTIMER_CC4          */
#define _PRS_CONSUMER_PROTIMER_CC4_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_CC4_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_CC4_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_CC4  */
#define PRS_CONSUMER_PROTIMER_CC4_PRSSEL_DEFAULT             (_PRS_CONSUMER_PROTIMER_CC4_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_CC4*/

/* Bit fields for PRS CONSUMER_PROTIMER_LBTPAUSE */
#define _PRS_CONSUMER_PROTIMER_LBTPAUSE_RESETVALUE           0x00000000UL                                          /**< Default value for PRS_CONSUMER_PROTIMER_LBTPAUSE*/
#define _PRS_CONSUMER_PROTIMER_LBTPAUSE_MASK                 0x0000000FUL                                          /**< Mask for PRS_CONSUMER_PROTIMER_LBTPAUSE     */
#define _PRS_CONSUMER_PROTIMER_LBTPAUSE_PRSSEL_SHIFT         0                                                     /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_LBTPAUSE_PRSSEL_MASK          0xFUL                                                 /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_LBTPAUSE_PRSSEL_DEFAULT       0x00000000UL                                          /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTPAUSE*/
#define PRS_CONSUMER_PROTIMER_LBTPAUSE_PRSSEL_DEFAULT        (_PRS_CONSUMER_PROTIMER_LBTPAUSE_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTPAUSE*/

/* Bit fields for PRS CONSUMER_PROTIMER_LBTSTART */
#define _PRS_CONSUMER_PROTIMER_LBTSTART_RESETVALUE           0x00000000UL                                          /**< Default value for PRS_CONSUMER_PROTIMER_LBTSTART*/
#define _PRS_CONSUMER_PROTIMER_LBTSTART_MASK                 0x0000000FUL                                          /**< Mask for PRS_CONSUMER_PROTIMER_LBTSTART     */
#define _PRS_CONSUMER_PROTIMER_LBTSTART_PRSSEL_SHIFT         0                                                     /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_LBTSTART_PRSSEL_MASK          0xFUL                                                 /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_LBTSTART_PRSSEL_DEFAULT       0x00000000UL                                          /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTSTART*/
#define PRS_CONSUMER_PROTIMER_LBTSTART_PRSSEL_DEFAULT        (_PRS_CONSUMER_PROTIMER_LBTSTART_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTSTART*/

/* Bit fields for PRS CONSUMER_PROTIMER_LBTSTOP */
#define _PRS_CONSUMER_PROTIMER_LBTSTOP_RESETVALUE            0x00000000UL                                         /**< Default value for PRS_CONSUMER_PROTIMER_LBTSTOP*/
#define _PRS_CONSUMER_PROTIMER_LBTSTOP_MASK                  0x0000000FUL                                         /**< Mask for PRS_CONSUMER_PROTIMER_LBTSTOP      */
#define _PRS_CONSUMER_PROTIMER_LBTSTOP_PRSSEL_SHIFT          0                                                    /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_LBTSTOP_PRSSEL_MASK           0xFUL                                                /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_LBTSTOP_PRSSEL_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTSTOP*/
#define PRS_CONSUMER_PROTIMER_LBTSTOP_PRSSEL_DEFAULT         (_PRS_CONSUMER_PROTIMER_LBTSTOP_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_LBTSTOP*/

/* Bit fields for PRS CONSUMER_PROTIMER_RTCCTRIGGER */
#define _PRS_CONSUMER_PROTIMER_RTCCTRIGGER_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_PROTIMER_RTCCTRIGGER*/
#define _PRS_CONSUMER_PROTIMER_RTCCTRIGGER_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_PROTIMER_RTCCTRIGGER  */
#define _PRS_CONSUMER_PROTIMER_RTCCTRIGGER_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_RTCCTRIGGER_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_RTCCTRIGGER_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_RTCCTRIGGER*/
#define PRS_CONSUMER_PROTIMER_RTCCTRIGGER_PRSSEL_DEFAULT     (_PRS_CONSUMER_PROTIMER_RTCCTRIGGER_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_RTCCTRIGGER*/

/* Bit fields for PRS CONSUMER_PROTIMER_START */
#define _PRS_CONSUMER_PROTIMER_START_RESETVALUE              0x00000000UL                                       /**< Default value for PRS_CONSUMER_PROTIMER_START*/
#define _PRS_CONSUMER_PROTIMER_START_MASK                    0x0000000FUL                                       /**< Mask for PRS_CONSUMER_PROTIMER_START        */
#define _PRS_CONSUMER_PROTIMER_START_PRSSEL_SHIFT            0                                                  /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_START_PRSSEL_MASK             0xFUL                                              /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_START_PRSSEL_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_START*/
#define PRS_CONSUMER_PROTIMER_START_PRSSEL_DEFAULT           (_PRS_CONSUMER_PROTIMER_START_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_START*/

/* Bit fields for PRS CONSUMER_PROTIMER_STOP */
#define _PRS_CONSUMER_PROTIMER_STOP_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_PROTIMER_STOP*/
#define _PRS_CONSUMER_PROTIMER_STOP_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_PROTIMER_STOP         */
#define _PRS_CONSUMER_PROTIMER_STOP_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_PROTIMER_STOP_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_PROTIMER_STOP_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_PROTIMER_STOP */
#define PRS_CONSUMER_PROTIMER_STOP_PRSSEL_DEFAULT            (_PRS_CONSUMER_PROTIMER_STOP_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_PROTIMER_STOP*/

/* Bit fields for PRS CONSUMER_RAC_CLR */
#define _PRS_CONSUMER_RAC_CLR_RESETVALUE                     0x00000000UL                                /**< Default value for PRS_CONSUMER_RAC_CLR      */
#define _PRS_CONSUMER_RAC_CLR_MASK                           0x0000000FUL                                /**< Mask for PRS_CONSUMER_RAC_CLR               */
#define _PRS_CONSUMER_RAC_CLR_PRSSEL_SHIFT                   0                                           /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_CLR_PRSSEL_MASK                    0xFUL                                       /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_CLR_PRSSEL_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for PRS_CONSUMER_RAC_CLR       */
#define PRS_CONSUMER_RAC_CLR_PRSSEL_DEFAULT                  (_PRS_CONSUMER_RAC_CLR_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_CLR*/

/* Bit fields for PRS CONSUMER_RAC_CTIIN0 */
#define _PRS_CONSUMER_RAC_CTIIN0_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_RAC_CTIIN0   */
#define _PRS_CONSUMER_RAC_CTIIN0_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_RAC_CTIIN0            */
#define _PRS_CONSUMER_RAC_CTIIN0_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_CTIIN0_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_CTIIN0_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_RAC_CTIIN0    */
#define PRS_CONSUMER_RAC_CTIIN0_PRSSEL_DEFAULT               (_PRS_CONSUMER_RAC_CTIIN0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_CTIIN0*/

/* Bit fields for PRS CONSUMER_RAC_CTIIN1 */
#define _PRS_CONSUMER_RAC_CTIIN1_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_RAC_CTIIN1   */
#define _PRS_CONSUMER_RAC_CTIIN1_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_RAC_CTIIN1            */
#define _PRS_CONSUMER_RAC_CTIIN1_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_CTIIN1_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_CTIIN1_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_RAC_CTIIN1    */
#define PRS_CONSUMER_RAC_CTIIN1_PRSSEL_DEFAULT               (_PRS_CONSUMER_RAC_CTIIN1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_CTIIN1*/

/* Bit fields for PRS CONSUMER_RAC_CTIIN2 */
#define _PRS_CONSUMER_RAC_CTIIN2_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_RAC_CTIIN2   */
#define _PRS_CONSUMER_RAC_CTIIN2_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_RAC_CTIIN2            */
#define _PRS_CONSUMER_RAC_CTIIN2_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_CTIIN2_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_CTIIN2_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_RAC_CTIIN2    */
#define PRS_CONSUMER_RAC_CTIIN2_PRSSEL_DEFAULT               (_PRS_CONSUMER_RAC_CTIIN2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_CTIIN2*/

/* Bit fields for PRS CONSUMER_RAC_CTIIN3 */
#define _PRS_CONSUMER_RAC_CTIIN3_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_RAC_CTIIN3   */
#define _PRS_CONSUMER_RAC_CTIIN3_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_RAC_CTIIN3            */
#define _PRS_CONSUMER_RAC_CTIIN3_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_CTIIN3_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_CTIIN3_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_RAC_CTIIN3    */
#define PRS_CONSUMER_RAC_CTIIN3_PRSSEL_DEFAULT               (_PRS_CONSUMER_RAC_CTIIN3_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_CTIIN3*/

/* Bit fields for PRS CONSUMER_RAC_FORCETX */
#define _PRS_CONSUMER_RAC_FORCETX_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_RAC_FORCETX  */
#define _PRS_CONSUMER_RAC_FORCETX_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_RAC_FORCETX           */
#define _PRS_CONSUMER_RAC_FORCETX_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_FORCETX_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_FORCETX_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_RAC_FORCETX   */
#define PRS_CONSUMER_RAC_FORCETX_PRSSEL_DEFAULT              (_PRS_CONSUMER_RAC_FORCETX_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_FORCETX*/

/* Bit fields for PRS CONSUMER_RAC_RXDIS */
#define _PRS_CONSUMER_RAC_RXDIS_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_RAC_RXDIS    */
#define _PRS_CONSUMER_RAC_RXDIS_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_RAC_RXDIS             */
#define _PRS_CONSUMER_RAC_RXDIS_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_RXDIS_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_RXDIS_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_RAC_RXDIS     */
#define PRS_CONSUMER_RAC_RXDIS_PRSSEL_DEFAULT                (_PRS_CONSUMER_RAC_RXDIS_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_RXDIS*/

/* Bit fields for PRS CONSUMER_RAC_RXEN */
#define _PRS_CONSUMER_RAC_RXEN_RESETVALUE                    0x00000000UL                                 /**< Default value for PRS_CONSUMER_RAC_RXEN     */
#define _PRS_CONSUMER_RAC_RXEN_MASK                          0x0000000FUL                                 /**< Mask for PRS_CONSUMER_RAC_RXEN              */
#define _PRS_CONSUMER_RAC_RXEN_PRSSEL_SHIFT                  0                                            /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_RXEN_PRSSEL_MASK                   0xFUL                                        /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_RXEN_PRSSEL_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for PRS_CONSUMER_RAC_RXEN      */
#define PRS_CONSUMER_RAC_RXEN_PRSSEL_DEFAULT                 (_PRS_CONSUMER_RAC_RXEN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_RXEN*/

/* Bit fields for PRS CONSUMER_RAC_TXEN */
#define _PRS_CONSUMER_RAC_TXEN_RESETVALUE                    0x00000000UL                                 /**< Default value for PRS_CONSUMER_RAC_TXEN     */
#define _PRS_CONSUMER_RAC_TXEN_MASK                          0x0000000FUL                                 /**< Mask for PRS_CONSUMER_RAC_TXEN              */
#define _PRS_CONSUMER_RAC_TXEN_PRSSEL_SHIFT                  0                                            /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_RAC_TXEN_PRSSEL_MASK                   0xFUL                                        /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_RAC_TXEN_PRSSEL_DEFAULT                0x00000000UL                                 /**< Mode DEFAULT for PRS_CONSUMER_RAC_TXEN      */
#define PRS_CONSUMER_RAC_TXEN_PRSSEL_DEFAULT                 (_PRS_CONSUMER_RAC_TXEN_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_RAC_TXEN*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC25 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC25_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC25*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC25_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC25  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC25_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC25_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC25_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC25*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC25_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC25_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC25*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC26 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC26_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC26*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC26_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC26  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC26_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC26_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC26_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC26*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC26_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC26_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC26*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC27 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC27_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC27*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC27_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC27  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC27_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC27_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC27_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC27*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC27_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC27_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC27*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC28 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC28_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC28*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC28_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC28  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC28_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC28_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC28_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC28*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC28_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC28_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC28*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC29 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC29_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC29*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC29_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC29  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC29_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC29_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC29_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC29*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC29_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC29_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC29*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC30 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC30_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC30*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC30_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC30  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC30_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC30_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC30_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC30*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC30_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC30_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC30*/

/* Bit fields for PRS CONSUMER_SETAMPER_TAMPERSRC31 */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC31_RESETVALUE        0x00000000UL                                             /**< Default value for PRS_CONSUMER_SETAMPER_TAMPERSRC31*/
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC31_MASK              0x0000000FUL                                             /**< Mask for PRS_CONSUMER_SETAMPER_TAMPERSRC31  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC31_PRSSEL_SHIFT      0                                                        /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC31_PRSSEL_MASK       0xFUL                                                    /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SETAMPER_TAMPERSRC31_PRSSEL_DEFAULT    0x00000000UL                                             /**< Mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC31*/
#define PRS_CONSUMER_SETAMPER_TAMPERSRC31_PRSSEL_DEFAULT     (_PRS_CONSUMER_SETAMPER_TAMPERSRC31_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SETAMPER_TAMPERSRC31*/

/* Bit fields for PRS CONSUMER_SYSRTC0_IN0 */
#define _PRS_CONSUMER_SYSRTC0_IN0_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_SYSRTC0_IN0  */
#define _PRS_CONSUMER_SYSRTC0_IN0_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_SYSRTC0_IN0           */
#define _PRS_CONSUMER_SYSRTC0_IN0_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SYSRTC0_IN0_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SYSRTC0_IN0_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_SYSRTC0_IN0   */
#define PRS_CONSUMER_SYSRTC0_IN0_PRSSEL_DEFAULT              (_PRS_CONSUMER_SYSRTC0_IN0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SYSRTC0_IN0*/

/* Bit fields for PRS CONSUMER_SYSRTC0_IN1 */
#define _PRS_CONSUMER_SYSRTC0_IN1_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_SYSRTC0_IN1  */
#define _PRS_CONSUMER_SYSRTC0_IN1_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_SYSRTC0_IN1           */
#define _PRS_CONSUMER_SYSRTC0_IN1_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_SYSRTC0_IN1_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_SYSRTC0_IN1_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_SYSRTC0_IN1   */
#define PRS_CONSUMER_SYSRTC0_IN1_PRSSEL_DEFAULT              (_PRS_CONSUMER_SYSRTC0_IN1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_SYSRTC0_IN1*/

/* Bit fields for PRS CONSUMER_HFXO0_OSCREQ */
#define _PRS_CONSUMER_HFXO0_OSCREQ_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_HFXO0_OSCREQ */
#define _PRS_CONSUMER_HFXO0_OSCREQ_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_HFXO0_OSCREQ          */
#define _PRS_CONSUMER_HFXO0_OSCREQ_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_HFXO0_OSCREQ_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_HFXO0_OSCREQ_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_HFXO0_OSCREQ  */
#define PRS_CONSUMER_HFXO0_OSCREQ_PRSSEL_DEFAULT             (_PRS_CONSUMER_HFXO0_OSCREQ_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_HFXO0_OSCREQ*/

/* Bit fields for PRS CONSUMER_HFXO0_TIMEOUT */
#define _PRS_CONSUMER_HFXO0_TIMEOUT_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_HFXO0_TIMEOUT*/
#define _PRS_CONSUMER_HFXO0_TIMEOUT_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_HFXO0_TIMEOUT         */
#define _PRS_CONSUMER_HFXO0_TIMEOUT_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_HFXO0_TIMEOUT_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_HFXO0_TIMEOUT_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_HFXO0_TIMEOUT */
#define PRS_CONSUMER_HFXO0_TIMEOUT_PRSSEL_DEFAULT            (_PRS_CONSUMER_HFXO0_TIMEOUT_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_HFXO0_TIMEOUT*/

/* Bit fields for PRS CONSUMER_CORE_CTIIN0 */
#define _PRS_CONSUMER_CORE_CTIIN0_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_CORE_CTIIN0  */
#define _PRS_CONSUMER_CORE_CTIIN0_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_CORE_CTIIN0           */
#define _PRS_CONSUMER_CORE_CTIIN0_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CORE_CTIIN0_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CORE_CTIIN0_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_CORE_CTIIN0   */
#define PRS_CONSUMER_CORE_CTIIN0_PRSSEL_DEFAULT              (_PRS_CONSUMER_CORE_CTIIN0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CORE_CTIIN0*/

/* Bit fields for PRS CONSUMER_CORE_CTIIN1 */
#define _PRS_CONSUMER_CORE_CTIIN1_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_CORE_CTIIN1  */
#define _PRS_CONSUMER_CORE_CTIIN1_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_CORE_CTIIN1           */
#define _PRS_CONSUMER_CORE_CTIIN1_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CORE_CTIIN1_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CORE_CTIIN1_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_CORE_CTIIN1   */
#define PRS_CONSUMER_CORE_CTIIN1_PRSSEL_DEFAULT              (_PRS_CONSUMER_CORE_CTIIN1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CORE_CTIIN1*/

/* Bit fields for PRS CONSUMER_CORE_CTIIN2 */
#define _PRS_CONSUMER_CORE_CTIIN2_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_CORE_CTIIN2  */
#define _PRS_CONSUMER_CORE_CTIIN2_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_CORE_CTIIN2           */
#define _PRS_CONSUMER_CORE_CTIIN2_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CORE_CTIIN2_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CORE_CTIIN2_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_CORE_CTIIN2   */
#define PRS_CONSUMER_CORE_CTIIN2_PRSSEL_DEFAULT              (_PRS_CONSUMER_CORE_CTIIN2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CORE_CTIIN2*/

/* Bit fields for PRS CONSUMER_CORE_CTIIN3 */
#define _PRS_CONSUMER_CORE_CTIIN3_RESETVALUE                 0x00000000UL                                    /**< Default value for PRS_CONSUMER_CORE_CTIIN3  */
#define _PRS_CONSUMER_CORE_CTIIN3_MASK                       0x0000000FUL                                    /**< Mask for PRS_CONSUMER_CORE_CTIIN3           */
#define _PRS_CONSUMER_CORE_CTIIN3_PRSSEL_SHIFT               0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CORE_CTIIN3_PRSSEL_MASK                0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CORE_CTIIN3_PRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_CORE_CTIIN3   */
#define PRS_CONSUMER_CORE_CTIIN3_PRSSEL_DEFAULT              (_PRS_CONSUMER_CORE_CTIIN3_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CORE_CTIIN3*/

/* Bit fields for PRS CONSUMER_CORE_M33RXEV */
#define _PRS_CONSUMER_CORE_M33RXEV_RESETVALUE                0x00000000UL                                     /**< Default value for PRS_CONSUMER_CORE_M33RXEV */
#define _PRS_CONSUMER_CORE_M33RXEV_MASK                      0x0000000FUL                                     /**< Mask for PRS_CONSUMER_CORE_M33RXEV          */
#define _PRS_CONSUMER_CORE_M33RXEV_PRSSEL_SHIFT              0                                                /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_CORE_M33RXEV_PRSSEL_MASK               0xFUL                                            /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_CORE_M33RXEV_PRSSEL_DEFAULT            0x00000000UL                                     /**< Mode DEFAULT for PRS_CONSUMER_CORE_M33RXEV  */
#define PRS_CONSUMER_CORE_M33RXEV_PRSSEL_DEFAULT             (_PRS_CONSUMER_CORE_M33RXEV_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_CORE_M33RXEV*/

/* Bit fields for PRS CONSUMER_TIMER0_CC0 */
#define _PRS_CONSUMER_TIMER0_CC0_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER0_CC0   */
#define _PRS_CONSUMER_TIMER0_CC0_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER0_CC0            */
#define _PRS_CONSUMER_TIMER0_CC0_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_CC0_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_CC0_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC0    */
#define PRS_CONSUMER_TIMER0_CC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER0_CC0_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC0*/
#define _PRS_CONSUMER_TIMER0_CC0_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER0_CC0_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER0_CC0_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC0    */
#define PRS_CONSUMER_TIMER0_CC0_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER0_CC0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC0*/

/* Bit fields for PRS CONSUMER_TIMER0_CC1 */
#define _PRS_CONSUMER_TIMER0_CC1_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER0_CC1   */
#define _PRS_CONSUMER_TIMER0_CC1_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER0_CC1            */
#define _PRS_CONSUMER_TIMER0_CC1_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_CC1_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_CC1_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC1    */
#define PRS_CONSUMER_TIMER0_CC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER0_CC1_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC1*/
#define _PRS_CONSUMER_TIMER0_CC1_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER0_CC1_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER0_CC1_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC1    */
#define PRS_CONSUMER_TIMER0_CC1_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER0_CC1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC1*/

/* Bit fields for PRS CONSUMER_TIMER0_CC2 */
#define _PRS_CONSUMER_TIMER0_CC2_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER0_CC2   */
#define _PRS_CONSUMER_TIMER0_CC2_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER0_CC2            */
#define _PRS_CONSUMER_TIMER0_CC2_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_CC2_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_CC2_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC2    */
#define PRS_CONSUMER_TIMER0_CC2_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER0_CC2_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC2*/
#define _PRS_CONSUMER_TIMER0_CC2_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER0_CC2_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER0_CC2_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_CC2    */
#define PRS_CONSUMER_TIMER0_CC2_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER0_CC2_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_CC2*/

/* Bit fields for PRS CONSUMER_TIMER0_DTI */
#define _PRS_CONSUMER_TIMER0_DTI_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_TIMER0_DTI   */
#define _PRS_CONSUMER_TIMER0_DTI_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_TIMER0_DTI            */
#define _PRS_CONSUMER_TIMER0_DTI_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_DTI_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_DTI_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_DTI    */
#define PRS_CONSUMER_TIMER0_DTI_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER0_DTI_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_DTI*/

/* Bit fields for PRS CONSUMER_TIMER0_DTIFS1 */
#define _PRS_CONSUMER_TIMER0_DTIFS1_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER0_DTIFS1*/
#define _PRS_CONSUMER_TIMER0_DTIFS1_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER0_DTIFS1         */
#define _PRS_CONSUMER_TIMER0_DTIFS1_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_DTIFS1_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_DTIFS1_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_DTIFS1 */
#define PRS_CONSUMER_TIMER0_DTIFS1_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER0_DTIFS1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_DTIFS1*/

/* Bit fields for PRS CONSUMER_TIMER0_DTIFS2 */
#define _PRS_CONSUMER_TIMER0_DTIFS2_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER0_DTIFS2*/
#define _PRS_CONSUMER_TIMER0_DTIFS2_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER0_DTIFS2         */
#define _PRS_CONSUMER_TIMER0_DTIFS2_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER0_DTIFS2_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER0_DTIFS2_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER0_DTIFS2 */
#define PRS_CONSUMER_TIMER0_DTIFS2_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER0_DTIFS2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER0_DTIFS2*/

/* Bit fields for PRS CONSUMER_TIMER1_CC0 */
#define _PRS_CONSUMER_TIMER1_CC0_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER1_CC0   */
#define _PRS_CONSUMER_TIMER1_CC0_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER1_CC0            */
#define _PRS_CONSUMER_TIMER1_CC0_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_CC0_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_CC0_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC0    */
#define PRS_CONSUMER_TIMER1_CC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER1_CC0_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC0*/
#define _PRS_CONSUMER_TIMER1_CC0_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER1_CC0_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER1_CC0_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC0    */
#define PRS_CONSUMER_TIMER1_CC0_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER1_CC0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC0*/

/* Bit fields for PRS CONSUMER_TIMER1_CC1 */
#define _PRS_CONSUMER_TIMER1_CC1_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER1_CC1   */
#define _PRS_CONSUMER_TIMER1_CC1_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER1_CC1            */
#define _PRS_CONSUMER_TIMER1_CC1_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_CC1_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_CC1_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC1    */
#define PRS_CONSUMER_TIMER1_CC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER1_CC1_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC1*/
#define _PRS_CONSUMER_TIMER1_CC1_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER1_CC1_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER1_CC1_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC1    */
#define PRS_CONSUMER_TIMER1_CC1_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER1_CC1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC1*/

/* Bit fields for PRS CONSUMER_TIMER1_CC2 */
#define _PRS_CONSUMER_TIMER1_CC2_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER1_CC2   */
#define _PRS_CONSUMER_TIMER1_CC2_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER1_CC2            */
#define _PRS_CONSUMER_TIMER1_CC2_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_CC2_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_CC2_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC2    */
#define PRS_CONSUMER_TIMER1_CC2_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER1_CC2_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC2*/
#define _PRS_CONSUMER_TIMER1_CC2_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER1_CC2_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER1_CC2_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_CC2    */
#define PRS_CONSUMER_TIMER1_CC2_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER1_CC2_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_CC2*/

/* Bit fields for PRS CONSUMER_TIMER1_DTI */
#define _PRS_CONSUMER_TIMER1_DTI_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_TIMER1_DTI   */
#define _PRS_CONSUMER_TIMER1_DTI_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_TIMER1_DTI            */
#define _PRS_CONSUMER_TIMER1_DTI_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_DTI_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_DTI_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_DTI    */
#define PRS_CONSUMER_TIMER1_DTI_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER1_DTI_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_DTI*/

/* Bit fields for PRS CONSUMER_TIMER1_DTIFS1 */
#define _PRS_CONSUMER_TIMER1_DTIFS1_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER1_DTIFS1*/
#define _PRS_CONSUMER_TIMER1_DTIFS1_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER1_DTIFS1         */
#define _PRS_CONSUMER_TIMER1_DTIFS1_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_DTIFS1_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_DTIFS1_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_DTIFS1 */
#define PRS_CONSUMER_TIMER1_DTIFS1_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER1_DTIFS1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_DTIFS1*/

/* Bit fields for PRS CONSUMER_TIMER1_DTIFS2 */
#define _PRS_CONSUMER_TIMER1_DTIFS2_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER1_DTIFS2*/
#define _PRS_CONSUMER_TIMER1_DTIFS2_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER1_DTIFS2         */
#define _PRS_CONSUMER_TIMER1_DTIFS2_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER1_DTIFS2_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER1_DTIFS2_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER1_DTIFS2 */
#define PRS_CONSUMER_TIMER1_DTIFS2_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER1_DTIFS2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER1_DTIFS2*/

/* Bit fields for PRS CONSUMER_TIMER2_CC0 */
#define _PRS_CONSUMER_TIMER2_CC0_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER2_CC0   */
#define _PRS_CONSUMER_TIMER2_CC0_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER2_CC0            */
#define _PRS_CONSUMER_TIMER2_CC0_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_CC0_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_CC0_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC0    */
#define PRS_CONSUMER_TIMER2_CC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER2_CC0_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC0*/
#define _PRS_CONSUMER_TIMER2_CC0_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER2_CC0_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER2_CC0_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC0    */
#define PRS_CONSUMER_TIMER2_CC0_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER2_CC0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC0*/

/* Bit fields for PRS CONSUMER_TIMER2_CC1 */
#define _PRS_CONSUMER_TIMER2_CC1_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER2_CC1   */
#define _PRS_CONSUMER_TIMER2_CC1_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER2_CC1            */
#define _PRS_CONSUMER_TIMER2_CC1_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_CC1_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_CC1_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC1    */
#define PRS_CONSUMER_TIMER2_CC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER2_CC1_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC1*/
#define _PRS_CONSUMER_TIMER2_CC1_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER2_CC1_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER2_CC1_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC1    */
#define PRS_CONSUMER_TIMER2_CC1_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER2_CC1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC1*/

/* Bit fields for PRS CONSUMER_TIMER2_CC2 */
#define _PRS_CONSUMER_TIMER2_CC2_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER2_CC2   */
#define _PRS_CONSUMER_TIMER2_CC2_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER2_CC2            */
#define _PRS_CONSUMER_TIMER2_CC2_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_CC2_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_CC2_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC2    */
#define PRS_CONSUMER_TIMER2_CC2_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER2_CC2_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC2*/
#define _PRS_CONSUMER_TIMER2_CC2_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER2_CC2_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER2_CC2_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_CC2    */
#define PRS_CONSUMER_TIMER2_CC2_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER2_CC2_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_CC2*/

/* Bit fields for PRS CONSUMER_TIMER2_DTI */
#define _PRS_CONSUMER_TIMER2_DTI_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_TIMER2_DTI   */
#define _PRS_CONSUMER_TIMER2_DTI_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_TIMER2_DTI            */
#define _PRS_CONSUMER_TIMER2_DTI_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_DTI_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_DTI_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_DTI    */
#define PRS_CONSUMER_TIMER2_DTI_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER2_DTI_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_DTI*/

/* Bit fields for PRS CONSUMER_TIMER2_DTIFS1 */
#define _PRS_CONSUMER_TIMER2_DTIFS1_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER2_DTIFS1*/
#define _PRS_CONSUMER_TIMER2_DTIFS1_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER2_DTIFS1         */
#define _PRS_CONSUMER_TIMER2_DTIFS1_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_DTIFS1_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_DTIFS1_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_DTIFS1 */
#define PRS_CONSUMER_TIMER2_DTIFS1_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER2_DTIFS1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_DTIFS1*/

/* Bit fields for PRS CONSUMER_TIMER2_DTIFS2 */
#define _PRS_CONSUMER_TIMER2_DTIFS2_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER2_DTIFS2*/
#define _PRS_CONSUMER_TIMER2_DTIFS2_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER2_DTIFS2         */
#define _PRS_CONSUMER_TIMER2_DTIFS2_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER2_DTIFS2_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER2_DTIFS2_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER2_DTIFS2 */
#define PRS_CONSUMER_TIMER2_DTIFS2_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER2_DTIFS2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER2_DTIFS2*/

/* Bit fields for PRS CONSUMER_TIMER3_CC0 */
#define _PRS_CONSUMER_TIMER3_CC0_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER3_CC0   */
#define _PRS_CONSUMER_TIMER3_CC0_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER3_CC0            */
#define _PRS_CONSUMER_TIMER3_CC0_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_CC0_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_CC0_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC0    */
#define PRS_CONSUMER_TIMER3_CC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER3_CC0_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC0*/
#define _PRS_CONSUMER_TIMER3_CC0_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER3_CC0_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER3_CC0_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC0    */
#define PRS_CONSUMER_TIMER3_CC0_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER3_CC0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC0*/

/* Bit fields for PRS CONSUMER_TIMER3_CC1 */
#define _PRS_CONSUMER_TIMER3_CC1_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER3_CC1   */
#define _PRS_CONSUMER_TIMER3_CC1_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER3_CC1            */
#define _PRS_CONSUMER_TIMER3_CC1_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_CC1_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_CC1_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC1    */
#define PRS_CONSUMER_TIMER3_CC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER3_CC1_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC1*/
#define _PRS_CONSUMER_TIMER3_CC1_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER3_CC1_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER3_CC1_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC1    */
#define PRS_CONSUMER_TIMER3_CC1_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER3_CC1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC1*/

/* Bit fields for PRS CONSUMER_TIMER3_CC2 */
#define _PRS_CONSUMER_TIMER3_CC2_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER3_CC2   */
#define _PRS_CONSUMER_TIMER3_CC2_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER3_CC2            */
#define _PRS_CONSUMER_TIMER3_CC2_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_CC2_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_CC2_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC2    */
#define PRS_CONSUMER_TIMER3_CC2_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER3_CC2_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC2*/
#define _PRS_CONSUMER_TIMER3_CC2_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER3_CC2_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER3_CC2_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_CC2    */
#define PRS_CONSUMER_TIMER3_CC2_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER3_CC2_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_CC2*/

/* Bit fields for PRS CONSUMER_TIMER3_DTI */
#define _PRS_CONSUMER_TIMER3_DTI_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_TIMER3_DTI   */
#define _PRS_CONSUMER_TIMER3_DTI_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_TIMER3_DTI            */
#define _PRS_CONSUMER_TIMER3_DTI_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_DTI_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_DTI_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_DTI    */
#define PRS_CONSUMER_TIMER3_DTI_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER3_DTI_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_DTI*/

/* Bit fields for PRS CONSUMER_TIMER3_DTIFS1 */
#define _PRS_CONSUMER_TIMER3_DTIFS1_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER3_DTIFS1*/
#define _PRS_CONSUMER_TIMER3_DTIFS1_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER3_DTIFS1         */
#define _PRS_CONSUMER_TIMER3_DTIFS1_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_DTIFS1_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_DTIFS1_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_DTIFS1 */
#define PRS_CONSUMER_TIMER3_DTIFS1_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER3_DTIFS1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_DTIFS1*/

/* Bit fields for PRS CONSUMER_TIMER3_DTIFS2 */
#define _PRS_CONSUMER_TIMER3_DTIFS2_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER3_DTIFS2*/
#define _PRS_CONSUMER_TIMER3_DTIFS2_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER3_DTIFS2         */
#define _PRS_CONSUMER_TIMER3_DTIFS2_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER3_DTIFS2_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER3_DTIFS2_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER3_DTIFS2 */
#define PRS_CONSUMER_TIMER3_DTIFS2_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER3_DTIFS2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER3_DTIFS2*/

/* Bit fields for PRS CONSUMER_TIMER4_CC0 */
#define _PRS_CONSUMER_TIMER4_CC0_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER4_CC0   */
#define _PRS_CONSUMER_TIMER4_CC0_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER4_CC0            */
#define _PRS_CONSUMER_TIMER4_CC0_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_CC0_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_CC0_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC0    */
#define PRS_CONSUMER_TIMER4_CC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER4_CC0_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC0*/
#define _PRS_CONSUMER_TIMER4_CC0_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER4_CC0_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER4_CC0_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC0    */
#define PRS_CONSUMER_TIMER4_CC0_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER4_CC0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC0*/

/* Bit fields for PRS CONSUMER_TIMER4_CC1 */
#define _PRS_CONSUMER_TIMER4_CC1_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER4_CC1   */
#define _PRS_CONSUMER_TIMER4_CC1_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER4_CC1            */
#define _PRS_CONSUMER_TIMER4_CC1_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_CC1_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_CC1_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC1    */
#define PRS_CONSUMER_TIMER4_CC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER4_CC1_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC1*/
#define _PRS_CONSUMER_TIMER4_CC1_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER4_CC1_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER4_CC1_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC1    */
#define PRS_CONSUMER_TIMER4_CC1_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER4_CC1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC1*/

/* Bit fields for PRS CONSUMER_TIMER4_CC2 */
#define _PRS_CONSUMER_TIMER4_CC2_RESETVALUE                  0x00000000UL                                    /**< Default value for PRS_CONSUMER_TIMER4_CC2   */
#define _PRS_CONSUMER_TIMER4_CC2_MASK                        0x0000030FUL                                    /**< Mask for PRS_CONSUMER_TIMER4_CC2            */
#define _PRS_CONSUMER_TIMER4_CC2_PRSSEL_SHIFT                0                                               /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_CC2_PRSSEL_MASK                 0xFUL                                           /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_CC2_PRSSEL_DEFAULT              0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC2    */
#define PRS_CONSUMER_TIMER4_CC2_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER4_CC2_PRSSEL_DEFAULT << 0)  /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC2*/
#define _PRS_CONSUMER_TIMER4_CC2_SPRSSEL_SHIFT               8                                               /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_TIMER4_CC2_SPRSSEL_MASK                0x300UL                                         /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_TIMER4_CC2_SPRSSEL_DEFAULT             0x00000000UL                                    /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_CC2    */
#define PRS_CONSUMER_TIMER4_CC2_SPRSSEL_DEFAULT              (_PRS_CONSUMER_TIMER4_CC2_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_CC2*/

/* Bit fields for PRS CONSUMER_TIMER4_DTI */
#define _PRS_CONSUMER_TIMER4_DTI_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_TIMER4_DTI   */
#define _PRS_CONSUMER_TIMER4_DTI_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_TIMER4_DTI            */
#define _PRS_CONSUMER_TIMER4_DTI_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_DTI_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_DTI_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_DTI    */
#define PRS_CONSUMER_TIMER4_DTI_PRSSEL_DEFAULT               (_PRS_CONSUMER_TIMER4_DTI_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_DTI*/

/* Bit fields for PRS CONSUMER_TIMER4_DTIFS1 */
#define _PRS_CONSUMER_TIMER4_DTIFS1_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER4_DTIFS1*/
#define _PRS_CONSUMER_TIMER4_DTIFS1_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER4_DTIFS1         */
#define _PRS_CONSUMER_TIMER4_DTIFS1_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_DTIFS1_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_DTIFS1_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_DTIFS1 */
#define PRS_CONSUMER_TIMER4_DTIFS1_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER4_DTIFS1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_DTIFS1*/

/* Bit fields for PRS CONSUMER_TIMER4_DTIFS2 */
#define _PRS_CONSUMER_TIMER4_DTIFS2_RESETVALUE               0x00000000UL                                      /**< Default value for PRS_CONSUMER_TIMER4_DTIFS2*/
#define _PRS_CONSUMER_TIMER4_DTIFS2_MASK                     0x0000000FUL                                      /**< Mask for PRS_CONSUMER_TIMER4_DTIFS2         */
#define _PRS_CONSUMER_TIMER4_DTIFS2_PRSSEL_SHIFT             0                                                 /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_TIMER4_DTIFS2_PRSSEL_MASK              0xFUL                                             /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_TIMER4_DTIFS2_PRSSEL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for PRS_CONSUMER_TIMER4_DTIFS2 */
#define PRS_CONSUMER_TIMER4_DTIFS2_PRSSEL_DEFAULT            (_PRS_CONSUMER_TIMER4_DTIFS2_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_TIMER4_DTIFS2*/

/* Bit fields for PRS CONSUMER_USART0_CLK */
#define _PRS_CONSUMER_USART0_CLK_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_USART0_CLK   */
#define _PRS_CONSUMER_USART0_CLK_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_USART0_CLK            */
#define _PRS_CONSUMER_USART0_CLK_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_USART0_CLK_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_USART0_CLK_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_USART0_CLK    */
#define PRS_CONSUMER_USART0_CLK_PRSSEL_DEFAULT               (_PRS_CONSUMER_USART0_CLK_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_USART0_CLK*/

/* Bit fields for PRS CONSUMER_USART0_IR */
#define _PRS_CONSUMER_USART0_IR_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_USART0_IR    */
#define _PRS_CONSUMER_USART0_IR_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_USART0_IR             */
#define _PRS_CONSUMER_USART0_IR_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_USART0_IR_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_USART0_IR_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_USART0_IR     */
#define PRS_CONSUMER_USART0_IR_PRSSEL_DEFAULT                (_PRS_CONSUMER_USART0_IR_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_USART0_IR*/

/* Bit fields for PRS CONSUMER_USART0_RX */
#define _PRS_CONSUMER_USART0_RX_RESETVALUE                   0x00000000UL                                  /**< Default value for PRS_CONSUMER_USART0_RX    */
#define _PRS_CONSUMER_USART0_RX_MASK                         0x0000000FUL                                  /**< Mask for PRS_CONSUMER_USART0_RX             */
#define _PRS_CONSUMER_USART0_RX_PRSSEL_SHIFT                 0                                             /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_USART0_RX_PRSSEL_MASK                  0xFUL                                         /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_USART0_RX_PRSSEL_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for PRS_CONSUMER_USART0_RX     */
#define PRS_CONSUMER_USART0_RX_PRSSEL_DEFAULT                (_PRS_CONSUMER_USART0_RX_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_USART0_RX*/

/* Bit fields for PRS CONSUMER_USART0_TRIGGER */
#define _PRS_CONSUMER_USART0_TRIGGER_RESETVALUE              0x00000000UL                                       /**< Default value for PRS_CONSUMER_USART0_TRIGGER*/
#define _PRS_CONSUMER_USART0_TRIGGER_MASK                    0x0000000FUL                                       /**< Mask for PRS_CONSUMER_USART0_TRIGGER        */
#define _PRS_CONSUMER_USART0_TRIGGER_PRSSEL_SHIFT            0                                                  /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_USART0_TRIGGER_PRSSEL_MASK             0xFUL                                              /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_USART0_TRIGGER_PRSSEL_DEFAULT          0x00000000UL                                       /**< Mode DEFAULT for PRS_CONSUMER_USART0_TRIGGER*/
#define PRS_CONSUMER_USART0_TRIGGER_PRSSEL_DEFAULT           (_PRS_CONSUMER_USART0_TRIGGER_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_USART0_TRIGGER*/

/* Bit fields for PRS CONSUMER_VDAC0_ASYNCTRIGCH0 */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_RESETVALUE          0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC0_ASYNCTRIGCH0*/
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_MASK                0x0000000FUL                                           /**< Mask for PRS_CONSUMER_VDAC0_ASYNCTRIGCH0    */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_PRSSEL_SHIFT        0                                                      /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_PRSSEL_MASK         0xFUL                                                  /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_PRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC0_ASYNCTRIGCH0*/
#define PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_PRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC0_ASYNCTRIGCH0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC0_ASYNCTRIGCH0*/

/* Bit fields for PRS CONSUMER_VDAC0_ASYNCTRIGCH1 */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_RESETVALUE          0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC0_ASYNCTRIGCH1*/
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_MASK                0x0000000FUL                                           /**< Mask for PRS_CONSUMER_VDAC0_ASYNCTRIGCH1    */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_PRSSEL_SHIFT        0                                                      /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_PRSSEL_MASK         0xFUL                                                  /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_PRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC0_ASYNCTRIGCH1*/
#define PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_PRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC0_ASYNCTRIGCH1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC0_ASYNCTRIGCH1*/

/* Bit fields for PRS CONSUMER_VDAC0_SYNCTRIGCH0 */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH0_RESETVALUE           0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC0_SYNCTRIGCH0*/
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH0_MASK                 0x00000300UL                                           /**< Mask for PRS_CONSUMER_VDAC0_SYNCTRIGCH0     */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH0_SPRSSEL_SHIFT        8                                                      /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH0_SPRSSEL_MASK         0x300UL                                                /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH0_SPRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC0_SYNCTRIGCH0*/
#define PRS_CONSUMER_VDAC0_SYNCTRIGCH0_SPRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC0_SYNCTRIGCH0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC0_SYNCTRIGCH0*/

/* Bit fields for PRS CONSUMER_VDAC0_SYNCTRIGCH1 */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH1_RESETVALUE           0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC0_SYNCTRIGCH1*/
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH1_MASK                 0x00000300UL                                           /**< Mask for PRS_CONSUMER_VDAC0_SYNCTRIGCH1     */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH1_SPRSSEL_SHIFT        8                                                      /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH1_SPRSSEL_MASK         0x300UL                                                /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_VDAC0_SYNCTRIGCH1_SPRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC0_SYNCTRIGCH1*/
#define PRS_CONSUMER_VDAC0_SYNCTRIGCH1_SPRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC0_SYNCTRIGCH1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC0_SYNCTRIGCH1*/

/* Bit fields for PRS CONSUMER_VDAC1_ASYNCTRIGCH0 */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_RESETVALUE          0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC1_ASYNCTRIGCH0*/
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_MASK                0x0000000FUL                                           /**< Mask for PRS_CONSUMER_VDAC1_ASYNCTRIGCH0    */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_PRSSEL_SHIFT        0                                                      /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_PRSSEL_MASK         0xFUL                                                  /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_PRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC1_ASYNCTRIGCH0*/
#define PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_PRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC1_ASYNCTRIGCH0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC1_ASYNCTRIGCH0*/

/* Bit fields for PRS CONSUMER_VDAC1_ASYNCTRIGCH1 */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_RESETVALUE          0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC1_ASYNCTRIGCH1*/
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_MASK                0x0000000FUL                                           /**< Mask for PRS_CONSUMER_VDAC1_ASYNCTRIGCH1    */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_PRSSEL_SHIFT        0                                                      /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_PRSSEL_MASK         0xFUL                                                  /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_PRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC1_ASYNCTRIGCH1*/
#define PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_PRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC1_ASYNCTRIGCH1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC1_ASYNCTRIGCH1*/

/* Bit fields for PRS CONSUMER_VDAC1_SYNCTRIGCH0 */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH0_RESETVALUE           0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC1_SYNCTRIGCH0*/
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH0_MASK                 0x00000300UL                                           /**< Mask for PRS_CONSUMER_VDAC1_SYNCTRIGCH0     */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH0_SPRSSEL_SHIFT        8                                                      /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH0_SPRSSEL_MASK         0x300UL                                                /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH0_SPRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC1_SYNCTRIGCH0*/
#define PRS_CONSUMER_VDAC1_SYNCTRIGCH0_SPRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC1_SYNCTRIGCH0_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC1_SYNCTRIGCH0*/

/* Bit fields for PRS CONSUMER_VDAC1_SYNCTRIGCH1 */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH1_RESETVALUE           0x00000000UL                                           /**< Default value for PRS_CONSUMER_VDAC1_SYNCTRIGCH1*/
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH1_MASK                 0x00000300UL                                           /**< Mask for PRS_CONSUMER_VDAC1_SYNCTRIGCH1     */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH1_SPRSSEL_SHIFT        8                                                      /**< Shift value for PRS_SPRSSEL                 */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH1_SPRSSEL_MASK         0x300UL                                                /**< Bit mask for PRS_SPRSSEL                    */
#define _PRS_CONSUMER_VDAC1_SYNCTRIGCH1_SPRSSEL_DEFAULT      0x00000000UL                                           /**< Mode DEFAULT for PRS_CONSUMER_VDAC1_SYNCTRIGCH1*/
#define PRS_CONSUMER_VDAC1_SYNCTRIGCH1_SPRSSEL_DEFAULT       (_PRS_CONSUMER_VDAC1_SYNCTRIGCH1_SPRSSEL_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_CONSUMER_VDAC1_SYNCTRIGCH1*/

/* Bit fields for PRS CONSUMER_WDOG0_SRC0 */
#define _PRS_CONSUMER_WDOG0_SRC0_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_WDOG0_SRC0   */
#define _PRS_CONSUMER_WDOG0_SRC0_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_WDOG0_SRC0            */
#define _PRS_CONSUMER_WDOG0_SRC0_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_WDOG0_SRC0_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_WDOG0_SRC0_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_WDOG0_SRC0    */
#define PRS_CONSUMER_WDOG0_SRC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_WDOG0_SRC0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_WDOG0_SRC0*/

/* Bit fields for PRS CONSUMER_WDOG0_SRC1 */
#define _PRS_CONSUMER_WDOG0_SRC1_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_WDOG0_SRC1   */
#define _PRS_CONSUMER_WDOG0_SRC1_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_WDOG0_SRC1            */
#define _PRS_CONSUMER_WDOG0_SRC1_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_WDOG0_SRC1_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_WDOG0_SRC1_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_WDOG0_SRC1    */
#define PRS_CONSUMER_WDOG0_SRC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_WDOG0_SRC1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_WDOG0_SRC1*/

/* Bit fields for PRS CONSUMER_WDOG1_SRC0 */
#define _PRS_CONSUMER_WDOG1_SRC0_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_WDOG1_SRC0   */
#define _PRS_CONSUMER_WDOG1_SRC0_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_WDOG1_SRC0            */
#define _PRS_CONSUMER_WDOG1_SRC0_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_WDOG1_SRC0_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_WDOG1_SRC0_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_WDOG1_SRC0    */
#define PRS_CONSUMER_WDOG1_SRC0_PRSSEL_DEFAULT               (_PRS_CONSUMER_WDOG1_SRC0_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_WDOG1_SRC0*/

/* Bit fields for PRS CONSUMER_WDOG1_SRC1 */
#define _PRS_CONSUMER_WDOG1_SRC1_RESETVALUE                  0x00000000UL                                   /**< Default value for PRS_CONSUMER_WDOG1_SRC1   */
#define _PRS_CONSUMER_WDOG1_SRC1_MASK                        0x0000000FUL                                   /**< Mask for PRS_CONSUMER_WDOG1_SRC1            */
#define _PRS_CONSUMER_WDOG1_SRC1_PRSSEL_SHIFT                0                                              /**< Shift value for PRS_PRSSEL                  */
#define _PRS_CONSUMER_WDOG1_SRC1_PRSSEL_MASK                 0xFUL                                          /**< Bit mask for PRS_PRSSEL                     */
#define _PRS_CONSUMER_WDOG1_SRC1_PRSSEL_DEFAULT              0x00000000UL                                   /**< Mode DEFAULT for PRS_CONSUMER_WDOG1_SRC1    */
#define PRS_CONSUMER_WDOG1_SRC1_PRSSEL_DEFAULT               (_PRS_CONSUMER_WDOG1_SRC1_PRSSEL_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_CONSUMER_WDOG1_SRC1*/

/* Bit fields for PRS RPURATD0 */
#define _PRS_RPURATD0_RESETVALUE                             0x00000000UL                                     /**< Default value for PRS_RPURATD0              */
#define _PRS_RPURATD0_MASK                                   0xFFFFFFCEUL                                     /**< Mask for PRS_RPURATD0                       */
#define PRS_RPURATD0_RATDENABLE                              (0x1UL << 1)                                     /**< ENABLE Protection Bit                       */
#define _PRS_RPURATD0_RATDENABLE_SHIFT                       1                                                /**< Shift value for PRS_RATDENABLE              */
#define _PRS_RPURATD0_RATDENABLE_MASK                        0x2UL                                            /**< Bit mask for PRS_RATDENABLE                 */
#define _PRS_RPURATD0_RATDENABLE_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDENABLE_DEFAULT                      (_PRS_RPURATD0_RATDENABLE_DEFAULT << 1)          /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCSWPULSE                        (0x1UL << 2)                                     /**< ASYNC_SWPULSE Protection Bit                */
#define _PRS_RPURATD0_RATDASYNCSWPULSE_SHIFT                 2                                                /**< Shift value for PRS_RATDASYNCSWPULSE        */
#define _PRS_RPURATD0_RATDASYNCSWPULSE_MASK                  0x4UL                                            /**< Bit mask for PRS_RATDASYNCSWPULSE           */
#define _PRS_RPURATD0_RATDASYNCSWPULSE_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCSWPULSE_DEFAULT                (_PRS_RPURATD0_RATDASYNCSWPULSE_DEFAULT << 2)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCSWLEVEL                        (0x1UL << 3)                                     /**< ASYNC_SWLEVEL Protection Bit                */
#define _PRS_RPURATD0_RATDASYNCSWLEVEL_SHIFT                 3                                                /**< Shift value for PRS_RATDASYNCSWLEVEL        */
#define _PRS_RPURATD0_RATDASYNCSWLEVEL_MASK                  0x8UL                                            /**< Bit mask for PRS_RATDASYNCSWLEVEL           */
#define _PRS_RPURATD0_RATDASYNCSWLEVEL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCSWLEVEL_DEFAULT                (_PRS_RPURATD0_RATDASYNCSWLEVEL_DEFAULT << 3)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH0CTRL                         (0x1UL << 6)                                     /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH0CTRL_SHIFT                  6                                                /**< Shift value for PRS_RATDASYNCH0CTRL         */
#define _PRS_RPURATD0_RATDASYNCH0CTRL_MASK                   0x40UL                                           /**< Bit mask for PRS_RATDASYNCH0CTRL            */
#define _PRS_RPURATD0_RATDASYNCH0CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH0CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH0CTRL_DEFAULT << 6)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH1CTRL                         (0x1UL << 7)                                     /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH1CTRL_SHIFT                  7                                                /**< Shift value for PRS_RATDASYNCH1CTRL         */
#define _PRS_RPURATD0_RATDASYNCH1CTRL_MASK                   0x80UL                                           /**< Bit mask for PRS_RATDASYNCH1CTRL            */
#define _PRS_RPURATD0_RATDASYNCH1CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH1CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH1CTRL_DEFAULT << 7)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH2CTRL                         (0x1UL << 8)                                     /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH2CTRL_SHIFT                  8                                                /**< Shift value for PRS_RATDASYNCH2CTRL         */
#define _PRS_RPURATD0_RATDASYNCH2CTRL_MASK                   0x100UL                                          /**< Bit mask for PRS_RATDASYNCH2CTRL            */
#define _PRS_RPURATD0_RATDASYNCH2CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH2CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH2CTRL_DEFAULT << 8)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH3CTRL                         (0x1UL << 9)                                     /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH3CTRL_SHIFT                  9                                                /**< Shift value for PRS_RATDASYNCH3CTRL         */
#define _PRS_RPURATD0_RATDASYNCH3CTRL_MASK                   0x200UL                                          /**< Bit mask for PRS_RATDASYNCH3CTRL            */
#define _PRS_RPURATD0_RATDASYNCH3CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH3CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH3CTRL_DEFAULT << 9)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH4CTRL                         (0x1UL << 10)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH4CTRL_SHIFT                  10                                               /**< Shift value for PRS_RATDASYNCH4CTRL         */
#define _PRS_RPURATD0_RATDASYNCH4CTRL_MASK                   0x400UL                                          /**< Bit mask for PRS_RATDASYNCH4CTRL            */
#define _PRS_RPURATD0_RATDASYNCH4CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH4CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH4CTRL_DEFAULT << 10)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH5CTRL                         (0x1UL << 11)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH5CTRL_SHIFT                  11                                               /**< Shift value for PRS_RATDASYNCH5CTRL         */
#define _PRS_RPURATD0_RATDASYNCH5CTRL_MASK                   0x800UL                                          /**< Bit mask for PRS_RATDASYNCH5CTRL            */
#define _PRS_RPURATD0_RATDASYNCH5CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH5CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH5CTRL_DEFAULT << 11)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH6CTRL                         (0x1UL << 12)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH6CTRL_SHIFT                  12                                               /**< Shift value for PRS_RATDASYNCH6CTRL         */
#define _PRS_RPURATD0_RATDASYNCH6CTRL_MASK                   0x1000UL                                         /**< Bit mask for PRS_RATDASYNCH6CTRL            */
#define _PRS_RPURATD0_RATDASYNCH6CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH6CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH6CTRL_DEFAULT << 12)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH7CTRL                         (0x1UL << 13)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH7CTRL_SHIFT                  13                                               /**< Shift value for PRS_RATDASYNCH7CTRL         */
#define _PRS_RPURATD0_RATDASYNCH7CTRL_MASK                   0x2000UL                                         /**< Bit mask for PRS_RATDASYNCH7CTRL            */
#define _PRS_RPURATD0_RATDASYNCH7CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH7CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH7CTRL_DEFAULT << 13)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH8CTRL                         (0x1UL << 14)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH8CTRL_SHIFT                  14                                               /**< Shift value for PRS_RATDASYNCH8CTRL         */
#define _PRS_RPURATD0_RATDASYNCH8CTRL_MASK                   0x4000UL                                         /**< Bit mask for PRS_RATDASYNCH8CTRL            */
#define _PRS_RPURATD0_RATDASYNCH8CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH8CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH8CTRL_DEFAULT << 14)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH9CTRL                         (0x1UL << 15)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH9CTRL_SHIFT                  15                                               /**< Shift value for PRS_RATDASYNCH9CTRL         */
#define _PRS_RPURATD0_RATDASYNCH9CTRL_MASK                   0x8000UL                                         /**< Bit mask for PRS_RATDASYNCH9CTRL            */
#define _PRS_RPURATD0_RATDASYNCH9CTRL_DEFAULT                0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH9CTRL_DEFAULT                 (_PRS_RPURATD0_RATDASYNCH9CTRL_DEFAULT << 15)    /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH10CTRL                        (0x1UL << 16)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH10CTRL_SHIFT                 16                                               /**< Shift value for PRS_RATDASYNCH10CTRL        */
#define _PRS_RPURATD0_RATDASYNCH10CTRL_MASK                  0x10000UL                                        /**< Bit mask for PRS_RATDASYNCH10CTRL           */
#define _PRS_RPURATD0_RATDASYNCH10CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH10CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH10CTRL_DEFAULT << 16)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH11CTRL                        (0x1UL << 17)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH11CTRL_SHIFT                 17                                               /**< Shift value for PRS_RATDASYNCH11CTRL        */
#define _PRS_RPURATD0_RATDASYNCH11CTRL_MASK                  0x20000UL                                        /**< Bit mask for PRS_RATDASYNCH11CTRL           */
#define _PRS_RPURATD0_RATDASYNCH11CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH11CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH11CTRL_DEFAULT << 17)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH12CTRL                        (0x1UL << 18)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH12CTRL_SHIFT                 18                                               /**< Shift value for PRS_RATDASYNCH12CTRL        */
#define _PRS_RPURATD0_RATDASYNCH12CTRL_MASK                  0x40000UL                                        /**< Bit mask for PRS_RATDASYNCH12CTRL           */
#define _PRS_RPURATD0_RATDASYNCH12CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH12CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH12CTRL_DEFAULT << 18)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH13CTRL                        (0x1UL << 19)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH13CTRL_SHIFT                 19                                               /**< Shift value for PRS_RATDASYNCH13CTRL        */
#define _PRS_RPURATD0_RATDASYNCH13CTRL_MASK                  0x80000UL                                        /**< Bit mask for PRS_RATDASYNCH13CTRL           */
#define _PRS_RPURATD0_RATDASYNCH13CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH13CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH13CTRL_DEFAULT << 19)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH14CTRL                        (0x1UL << 20)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH14CTRL_SHIFT                 20                                               /**< Shift value for PRS_RATDASYNCH14CTRL        */
#define _PRS_RPURATD0_RATDASYNCH14CTRL_MASK                  0x100000UL                                       /**< Bit mask for PRS_RATDASYNCH14CTRL           */
#define _PRS_RPURATD0_RATDASYNCH14CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH14CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH14CTRL_DEFAULT << 20)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDASYNCH15CTRL                        (0x1UL << 21)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDASYNCH15CTRL_SHIFT                 21                                               /**< Shift value for PRS_RATDASYNCH15CTRL        */
#define _PRS_RPURATD0_RATDASYNCH15CTRL_MASK                  0x200000UL                                       /**< Bit mask for PRS_RATDASYNCH15CTRL           */
#define _PRS_RPURATD0_RATDASYNCH15CTRL_DEFAULT               0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDASYNCH15CTRL_DEFAULT                (_PRS_RPURATD0_RATDASYNCH15CTRL_DEFAULT << 21)   /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDSYNCH0CTRL                          (0x1UL << 22)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDSYNCH0CTRL_SHIFT                   22                                               /**< Shift value for PRS_RATDSYNCH0CTRL          */
#define _PRS_RPURATD0_RATDSYNCH0CTRL_MASK                    0x400000UL                                       /**< Bit mask for PRS_RATDSYNCH0CTRL             */
#define _PRS_RPURATD0_RATDSYNCH0CTRL_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDSYNCH0CTRL_DEFAULT                  (_PRS_RPURATD0_RATDSYNCH0CTRL_DEFAULT << 22)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDSYNCH1CTRL                          (0x1UL << 23)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDSYNCH1CTRL_SHIFT                   23                                               /**< Shift value for PRS_RATDSYNCH1CTRL          */
#define _PRS_RPURATD0_RATDSYNCH1CTRL_MASK                    0x800000UL                                       /**< Bit mask for PRS_RATDSYNCH1CTRL             */
#define _PRS_RPURATD0_RATDSYNCH1CTRL_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDSYNCH1CTRL_DEFAULT                  (_PRS_RPURATD0_RATDSYNCH1CTRL_DEFAULT << 23)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDSYNCH2CTRL                          (0x1UL << 24)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDSYNCH2CTRL_SHIFT                   24                                               /**< Shift value for PRS_RATDSYNCH2CTRL          */
#define _PRS_RPURATD0_RATDSYNCH2CTRL_MASK                    0x1000000UL                                      /**< Bit mask for PRS_RATDSYNCH2CTRL             */
#define _PRS_RPURATD0_RATDSYNCH2CTRL_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDSYNCH2CTRL_DEFAULT                  (_PRS_RPURATD0_RATDSYNCH2CTRL_DEFAULT << 24)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDSYNCH3CTRL                          (0x1UL << 25)                                    /**< CTRL Protection Bit                         */
#define _PRS_RPURATD0_RATDSYNCH3CTRL_SHIFT                   25                                               /**< Shift value for PRS_RATDSYNCH3CTRL          */
#define _PRS_RPURATD0_RATDSYNCH3CTRL_MASK                    0x2000000UL                                      /**< Bit mask for PRS_RATDSYNCH3CTRL             */
#define _PRS_RPURATD0_RATDSYNCH3CTRL_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDSYNCH3CTRL_DEFAULT                  (_PRS_RPURATD0_RATDSYNCH3CTRL_DEFAULT << 25)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDCMUCALDN                            (0x1UL << 26)                                    /**< CMU_CALDN Protection Bit                    */
#define _PRS_RPURATD0_RATDCMUCALDN_SHIFT                     26                                               /**< Shift value for PRS_RATDCMUCALDN            */
#define _PRS_RPURATD0_RATDCMUCALDN_MASK                      0x4000000UL                                      /**< Bit mask for PRS_RATDCMUCALDN               */
#define _PRS_RPURATD0_RATDCMUCALDN_DEFAULT                   0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDCMUCALDN_DEFAULT                    (_PRS_RPURATD0_RATDCMUCALDN_DEFAULT << 26)       /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDCMUCALUP                            (0x1UL << 27)                                    /**< CMU_CALUP Protection Bit                    */
#define _PRS_RPURATD0_RATDCMUCALUP_SHIFT                     27                                               /**< Shift value for PRS_RATDCMUCALUP            */
#define _PRS_RPURATD0_RATDCMUCALUP_MASK                      0x8000000UL                                      /**< Bit mask for PRS_RATDCMUCALUP               */
#define _PRS_RPURATD0_RATDCMUCALUP_DEFAULT                   0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDCMUCALUP_DEFAULT                    (_PRS_RPURATD0_RATDCMUCALUP_DEFAULT << 27)       /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDEUSART0CLK                          (0x1UL << 28)                                    /**< EUSART0_CLK Protection Bit                  */
#define _PRS_RPURATD0_RATDEUSART0CLK_SHIFT                   28                                               /**< Shift value for PRS_RATDEUSART0CLK          */
#define _PRS_RPURATD0_RATDEUSART0CLK_MASK                    0x10000000UL                                     /**< Bit mask for PRS_RATDEUSART0CLK             */
#define _PRS_RPURATD0_RATDEUSART0CLK_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDEUSART0CLK_DEFAULT                  (_PRS_RPURATD0_RATDEUSART0CLK_DEFAULT << 28)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDEUSART0RX                           (0x1UL << 29)                                    /**< EUSART0_RX Protection Bit                   */
#define _PRS_RPURATD0_RATDEUSART0RX_SHIFT                    29                                               /**< Shift value for PRS_RATDEUSART0RX           */
#define _PRS_RPURATD0_RATDEUSART0RX_MASK                     0x20000000UL                                     /**< Bit mask for PRS_RATDEUSART0RX              */
#define _PRS_RPURATD0_RATDEUSART0RX_DEFAULT                  0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDEUSART0RX_DEFAULT                   (_PRS_RPURATD0_RATDEUSART0RX_DEFAULT << 29)      /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDEUSART0TRIGGER                      (0x1UL << 30)                                    /**< EUSART0_TRIGGER Protection Bit              */
#define _PRS_RPURATD0_RATDEUSART0TRIGGER_SHIFT               30                                               /**< Shift value for PRS_RATDEUSART0TRIGGER      */
#define _PRS_RPURATD0_RATDEUSART0TRIGGER_MASK                0x40000000UL                                     /**< Bit mask for PRS_RATDEUSART0TRIGGER         */
#define _PRS_RPURATD0_RATDEUSART0TRIGGER_DEFAULT             0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDEUSART0TRIGGER_DEFAULT              (_PRS_RPURATD0_RATDEUSART0TRIGGER_DEFAULT << 30) /**< Shifted mode DEFAULT for PRS_RPURATD0       */
#define PRS_RPURATD0_RATDEUSART1CLK                          (0x1UL << 31)                                    /**< EUSART1_CLK Protection Bit                  */
#define _PRS_RPURATD0_RATDEUSART1CLK_SHIFT                   31                                               /**< Shift value for PRS_RATDEUSART1CLK          */
#define _PRS_RPURATD0_RATDEUSART1CLK_MASK                    0x80000000UL                                     /**< Bit mask for PRS_RATDEUSART1CLK             */
#define _PRS_RPURATD0_RATDEUSART1CLK_DEFAULT                 0x00000000UL                                     /**< Mode DEFAULT for PRS_RPURATD0               */
#define PRS_RPURATD0_RATDEUSART1CLK_DEFAULT                  (_PRS_RPURATD0_RATDEUSART1CLK_DEFAULT << 31)     /**< Shifted mode DEFAULT for PRS_RPURATD0       */

/* Bit fields for PRS RPURATD1 */
#define _PRS_RPURATD1_RESETVALUE                             0x00000000UL                                          /**< Default value for PRS_RPURATD1              */
#define _PRS_RPURATD1_MASK                                   0xFFFFFFFFUL                                          /**< Mask for PRS_RPURATD1                       */
#define PRS_RPURATD1_RATDEUSART1RX                           (0x1UL << 0)                                          /**< EUSART1_RX Protection Bit                   */
#define _PRS_RPURATD1_RATDEUSART1RX_SHIFT                    0                                                     /**< Shift value for PRS_RATDEUSART1RX           */
#define _PRS_RPURATD1_RATDEUSART1RX_MASK                     0x1UL                                                 /**< Bit mask for PRS_RATDEUSART1RX              */
#define _PRS_RPURATD1_RATDEUSART1RX_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDEUSART1RX_DEFAULT                   (_PRS_RPURATD1_RATDEUSART1RX_DEFAULT << 0)            /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDEUSART1TRIGGER                      (0x1UL << 1)                                          /**< EUSART1_TRIGGER Protection Bit              */
#define _PRS_RPURATD1_RATDEUSART1TRIGGER_SHIFT               1                                                     /**< Shift value for PRS_RATDEUSART1TRIGGER      */
#define _PRS_RPURATD1_RATDEUSART1TRIGGER_MASK                0x2UL                                                 /**< Bit mask for PRS_RATDEUSART1TRIGGER         */
#define _PRS_RPURATD1_RATDEUSART1TRIGGER_DEFAULT             0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDEUSART1TRIGGER_DEFAULT              (_PRS_RPURATD1_RATDEUSART1TRIGGER_DEFAULT << 1)       /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDFRCRXRAW                            (0x1UL << 2)                                          /**< FRC_RXRAW Protection Bit                    */
#define _PRS_RPURATD1_RATDFRCRXRAW_SHIFT                     2                                                     /**< Shift value for PRS_RATDFRCRXRAW            */
#define _PRS_RPURATD1_RATDFRCRXRAW_MASK                      0x4UL                                                 /**< Bit mask for PRS_RATDFRCRXRAW               */
#define _PRS_RPURATD1_RATDFRCRXRAW_DEFAULT                   0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDFRCRXRAW_DEFAULT                    (_PRS_RPURATD1_RATDFRCRXRAW_DEFAULT << 2)             /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDIADC0SCANTRIGGER                    (0x1UL << 3)                                          /**< IADC0_SCANTRIGGER Protection Bit            */
#define _PRS_RPURATD1_RATDIADC0SCANTRIGGER_SHIFT             3                                                     /**< Shift value for PRS_RATDIADC0SCANTRIGGER    */
#define _PRS_RPURATD1_RATDIADC0SCANTRIGGER_MASK              0x8UL                                                 /**< Bit mask for PRS_RATDIADC0SCANTRIGGER       */
#define _PRS_RPURATD1_RATDIADC0SCANTRIGGER_DEFAULT           0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDIADC0SCANTRIGGER_DEFAULT            (_PRS_RPURATD1_RATDIADC0SCANTRIGGER_DEFAULT << 3)     /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDIADC0SINGLETRIGGER                  (0x1UL << 4)                                          /**< IADC0_SINGLETRIGGER Protection Bit          */
#define _PRS_RPURATD1_RATDIADC0SINGLETRIGGER_SHIFT           4                                                     /**< Shift value for PRS_RATDIADC0SINGLETRIGGER  */
#define _PRS_RPURATD1_RATDIADC0SINGLETRIGGER_MASK            0x10UL                                                /**< Bit mask for PRS_RATDIADC0SINGLETRIGGER     */
#define _PRS_RPURATD1_RATDIADC0SINGLETRIGGER_DEFAULT         0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDIADC0SINGLETRIGGER_DEFAULT          (_PRS_RPURATD1_RATDIADC0SINGLETRIGGER_DEFAULT << 4)   /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDLDMAXBARDMAREQ0                     (0x1UL << 5)                                          /**< LDMAXBAR_DMAREQ0 Protection Bit             */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ0_SHIFT              5                                                     /**< Shift value for PRS_RATDLDMAXBARDMAREQ0     */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ0_MASK               0x20UL                                                /**< Bit mask for PRS_RATDLDMAXBARDMAREQ0        */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ0_DEFAULT            0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDLDMAXBARDMAREQ0_DEFAULT             (_PRS_RPURATD1_RATDLDMAXBARDMAREQ0_DEFAULT << 5)      /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDLDMAXBARDMAREQ1                     (0x1UL << 6)                                          /**< LDMAXBAR_DMAREQ1 Protection Bit             */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ1_SHIFT              6                                                     /**< Shift value for PRS_RATDLDMAXBARDMAREQ1     */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ1_MASK               0x40UL                                                /**< Bit mask for PRS_RATDLDMAXBARDMAREQ1        */
#define _PRS_RPURATD1_RATDLDMAXBARDMAREQ1_DEFAULT            0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDLDMAXBARDMAREQ1_DEFAULT             (_PRS_RPURATD1_RATDLDMAXBARDMAREQ1_DEFAULT << 6)      /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDLETIMERCLEAR                        (0x1UL << 7)                                          /**< LETIMER_CLEAR Protection Bit                */
#define _PRS_RPURATD1_RATDLETIMERCLEAR_SHIFT                 7                                                     /**< Shift value for PRS_RATDLETIMERCLEAR        */
#define _PRS_RPURATD1_RATDLETIMERCLEAR_MASK                  0x80UL                                                /**< Bit mask for PRS_RATDLETIMERCLEAR           */
#define _PRS_RPURATD1_RATDLETIMERCLEAR_DEFAULT               0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDLETIMERCLEAR_DEFAULT                (_PRS_RPURATD1_RATDLETIMERCLEAR_DEFAULT << 7)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDLETIMERSTART                        (0x1UL << 8)                                          /**< LETIMER_START Protection Bit                */
#define _PRS_RPURATD1_RATDLETIMERSTART_SHIFT                 8                                                     /**< Shift value for PRS_RATDLETIMERSTART        */
#define _PRS_RPURATD1_RATDLETIMERSTART_MASK                  0x100UL                                               /**< Bit mask for PRS_RATDLETIMERSTART           */
#define _PRS_RPURATD1_RATDLETIMERSTART_DEFAULT               0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDLETIMERSTART_DEFAULT                (_PRS_RPURATD1_RATDLETIMERSTART_DEFAULT << 8)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDLETIMERSTOP                         (0x1UL << 9)                                          /**< LETIMER_STOP Protection Bit                 */
#define _PRS_RPURATD1_RATDLETIMERSTOP_SHIFT                  9                                                     /**< Shift value for PRS_RATDLETIMERSTOP         */
#define _PRS_RPURATD1_RATDLETIMERSTOP_MASK                   0x200UL                                               /**< Bit mask for PRS_RATDLETIMERSTOP            */
#define _PRS_RPURATD1_RATDLETIMERSTOP_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDLETIMERSTOP_DEFAULT                 (_PRS_RPURATD1_RATDLETIMERSTOP_DEFAULT << 9)          /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDMODEMDIN                            (0x1UL << 10)                                         /**< MODEM_DIN Protection Bit                    */
#define _PRS_RPURATD1_RATDMODEMDIN_SHIFT                     10                                                    /**< Shift value for PRS_RATDMODEMDIN            */
#define _PRS_RPURATD1_RATDMODEMDIN_MASK                      0x400UL                                               /**< Bit mask for PRS_RATDMODEMDIN               */
#define _PRS_RPURATD1_RATDMODEMDIN_DEFAULT                   0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDMODEMDIN_DEFAULT                    (_PRS_RPURATD1_RATDMODEMDIN_DEFAULT << 10)            /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDMODEMPAEN                           (0x1UL << 11)                                         /**< MODEM_PAEN Protection Bit                   */
#define _PRS_RPURATD1_RATDMODEMPAEN_SHIFT                    11                                                    /**< Shift value for PRS_RATDMODEMPAEN           */
#define _PRS_RPURATD1_RATDMODEMPAEN_MASK                     0x800UL                                               /**< Bit mask for PRS_RATDMODEMPAEN              */
#define _PRS_RPURATD1_RATDMODEMPAEN_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDMODEMPAEN_DEFAULT                   (_PRS_RPURATD1_RATDMODEMPAEN_DEFAULT << 11)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPCNT0S0IN                           (0x1UL << 12)                                         /**< PCNT0_S0IN Protection Bit                   */
#define _PRS_RPURATD1_RATDPCNT0S0IN_SHIFT                    12                                                    /**< Shift value for PRS_RATDPCNT0S0IN           */
#define _PRS_RPURATD1_RATDPCNT0S0IN_MASK                     0x1000UL                                              /**< Bit mask for PRS_RATDPCNT0S0IN              */
#define _PRS_RPURATD1_RATDPCNT0S0IN_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPCNT0S0IN_DEFAULT                   (_PRS_RPURATD1_RATDPCNT0S0IN_DEFAULT << 12)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPCNT0S1IN                           (0x1UL << 13)                                         /**< PCNT0_S1IN Protection Bit                   */
#define _PRS_RPURATD1_RATDPCNT0S1IN_SHIFT                    13                                                    /**< Shift value for PRS_RATDPCNT0S1IN           */
#define _PRS_RPURATD1_RATDPCNT0S1IN_MASK                     0x2000UL                                              /**< Bit mask for PRS_RATDPCNT0S1IN              */
#define _PRS_RPURATD1_RATDPCNT0S1IN_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPCNT0S1IN_DEFAULT                   (_PRS_RPURATD1_RATDPCNT0S1IN_DEFAULT << 13)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERCC0                         (0x1UL << 14)                                         /**< PROTIMER_CC0 Protection Bit                 */
#define _PRS_RPURATD1_RATDPROTIMERCC0_SHIFT                  14                                                    /**< Shift value for PRS_RATDPROTIMERCC0         */
#define _PRS_RPURATD1_RATDPROTIMERCC0_MASK                   0x4000UL                                              /**< Bit mask for PRS_RATDPROTIMERCC0            */
#define _PRS_RPURATD1_RATDPROTIMERCC0_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERCC0_DEFAULT                 (_PRS_RPURATD1_RATDPROTIMERCC0_DEFAULT << 14)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERCC1                         (0x1UL << 15)                                         /**< PROTIMER_CC1 Protection Bit                 */
#define _PRS_RPURATD1_RATDPROTIMERCC1_SHIFT                  15                                                    /**< Shift value for PRS_RATDPROTIMERCC1         */
#define _PRS_RPURATD1_RATDPROTIMERCC1_MASK                   0x8000UL                                              /**< Bit mask for PRS_RATDPROTIMERCC1            */
#define _PRS_RPURATD1_RATDPROTIMERCC1_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERCC1_DEFAULT                 (_PRS_RPURATD1_RATDPROTIMERCC1_DEFAULT << 15)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERCC2                         (0x1UL << 16)                                         /**< PROTIMER_CC2 Protection Bit                 */
#define _PRS_RPURATD1_RATDPROTIMERCC2_SHIFT                  16                                                    /**< Shift value for PRS_RATDPROTIMERCC2         */
#define _PRS_RPURATD1_RATDPROTIMERCC2_MASK                   0x10000UL                                             /**< Bit mask for PRS_RATDPROTIMERCC2            */
#define _PRS_RPURATD1_RATDPROTIMERCC2_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERCC2_DEFAULT                 (_PRS_RPURATD1_RATDPROTIMERCC2_DEFAULT << 16)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERCC3                         (0x1UL << 17)                                         /**< PROTIMER_CC3 Protection Bit                 */
#define _PRS_RPURATD1_RATDPROTIMERCC3_SHIFT                  17                                                    /**< Shift value for PRS_RATDPROTIMERCC3         */
#define _PRS_RPURATD1_RATDPROTIMERCC3_MASK                   0x20000UL                                             /**< Bit mask for PRS_RATDPROTIMERCC3            */
#define _PRS_RPURATD1_RATDPROTIMERCC3_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERCC3_DEFAULT                 (_PRS_RPURATD1_RATDPROTIMERCC3_DEFAULT << 17)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERCC4                         (0x1UL << 18)                                         /**< PROTIMER_CC4 Protection Bit                 */
#define _PRS_RPURATD1_RATDPROTIMERCC4_SHIFT                  18                                                    /**< Shift value for PRS_RATDPROTIMERCC4         */
#define _PRS_RPURATD1_RATDPROTIMERCC4_MASK                   0x40000UL                                             /**< Bit mask for PRS_RATDPROTIMERCC4            */
#define _PRS_RPURATD1_RATDPROTIMERCC4_DEFAULT                0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERCC4_DEFAULT                 (_PRS_RPURATD1_RATDPROTIMERCC4_DEFAULT << 18)         /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERLBTPAUSE                    (0x1UL << 19)                                         /**< PROTIMER_LBTPAUSE Protection Bit            */
#define _PRS_RPURATD1_RATDPROTIMERLBTPAUSE_SHIFT             19                                                    /**< Shift value for PRS_RATDPROTIMERLBTPAUSE    */
#define _PRS_RPURATD1_RATDPROTIMERLBTPAUSE_MASK              0x80000UL                                             /**< Bit mask for PRS_RATDPROTIMERLBTPAUSE       */
#define _PRS_RPURATD1_RATDPROTIMERLBTPAUSE_DEFAULT           0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERLBTPAUSE_DEFAULT            (_PRS_RPURATD1_RATDPROTIMERLBTPAUSE_DEFAULT << 19)    /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERLBTSTART                    (0x1UL << 20)                                         /**< PROTIMER_LBTSTART Protection Bit            */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTART_SHIFT             20                                                    /**< Shift value for PRS_RATDPROTIMERLBTSTART    */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTART_MASK              0x100000UL                                            /**< Bit mask for PRS_RATDPROTIMERLBTSTART       */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTART_DEFAULT           0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERLBTSTART_DEFAULT            (_PRS_RPURATD1_RATDPROTIMERLBTSTART_DEFAULT << 20)    /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERLBTSTOP                     (0x1UL << 21)                                         /**< PROTIMER_LBTSTOP Protection Bit             */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTOP_SHIFT              21                                                    /**< Shift value for PRS_RATDPROTIMERLBTSTOP     */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTOP_MASK               0x200000UL                                            /**< Bit mask for PRS_RATDPROTIMERLBTSTOP        */
#define _PRS_RPURATD1_RATDPROTIMERLBTSTOP_DEFAULT            0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERLBTSTOP_DEFAULT             (_PRS_RPURATD1_RATDPROTIMERLBTSTOP_DEFAULT << 21)     /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER                 (0x1UL << 22)                                         /**< PROTIMER_RTCCTRIGGER Protection Bit         */
#define _PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER_SHIFT          22                                                    /**< Shift value for PRS_RATDPROTIMERRTCCTRIGGER */
#define _PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER_MASK           0x400000UL                                            /**< Bit mask for PRS_RATDPROTIMERRTCCTRIGGER    */
#define _PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER_DEFAULT        0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER_DEFAULT         (_PRS_RPURATD1_RATDPROTIMERRTCCTRIGGER_DEFAULT << 22) /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERSTART                       (0x1UL << 23)                                         /**< PROTIMER_START Protection Bit               */
#define _PRS_RPURATD1_RATDPROTIMERSTART_SHIFT                23                                                    /**< Shift value for PRS_RATDPROTIMERSTART       */
#define _PRS_RPURATD1_RATDPROTIMERSTART_MASK                 0x800000UL                                            /**< Bit mask for PRS_RATDPROTIMERSTART          */
#define _PRS_RPURATD1_RATDPROTIMERSTART_DEFAULT              0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERSTART_DEFAULT               (_PRS_RPURATD1_RATDPROTIMERSTART_DEFAULT << 23)       /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDPROTIMERSTOP                        (0x1UL << 24)                                         /**< PROTIMER_STOP Protection Bit                */
#define _PRS_RPURATD1_RATDPROTIMERSTOP_SHIFT                 24                                                    /**< Shift value for PRS_RATDPROTIMERSTOP        */
#define _PRS_RPURATD1_RATDPROTIMERSTOP_MASK                  0x1000000UL                                           /**< Bit mask for PRS_RATDPROTIMERSTOP           */
#define _PRS_RPURATD1_RATDPROTIMERSTOP_DEFAULT               0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDPROTIMERSTOP_DEFAULT                (_PRS_RPURATD1_RATDPROTIMERSTOP_DEFAULT << 24)        /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACCLR                              (0x1UL << 25)                                         /**< RAC_CLR Protection Bit                      */
#define _PRS_RPURATD1_RATDRACCLR_SHIFT                       25                                                    /**< Shift value for PRS_RATDRACCLR              */
#define _PRS_RPURATD1_RATDRACCLR_MASK                        0x2000000UL                                           /**< Bit mask for PRS_RATDRACCLR                 */
#define _PRS_RPURATD1_RATDRACCLR_DEFAULT                     0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACCLR_DEFAULT                      (_PRS_RPURATD1_RATDRACCLR_DEFAULT << 25)              /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACCTIIN0                           (0x1UL << 26)                                         /**< RAC_CTIIN0 Protection Bit                   */
#define _PRS_RPURATD1_RATDRACCTIIN0_SHIFT                    26                                                    /**< Shift value for PRS_RATDRACCTIIN0           */
#define _PRS_RPURATD1_RATDRACCTIIN0_MASK                     0x4000000UL                                           /**< Bit mask for PRS_RATDRACCTIIN0              */
#define _PRS_RPURATD1_RATDRACCTIIN0_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACCTIIN0_DEFAULT                   (_PRS_RPURATD1_RATDRACCTIIN0_DEFAULT << 26)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACCTIIN1                           (0x1UL << 27)                                         /**< RAC_CTIIN1 Protection Bit                   */
#define _PRS_RPURATD1_RATDRACCTIIN1_SHIFT                    27                                                    /**< Shift value for PRS_RATDRACCTIIN1           */
#define _PRS_RPURATD1_RATDRACCTIIN1_MASK                     0x8000000UL                                           /**< Bit mask for PRS_RATDRACCTIIN1              */
#define _PRS_RPURATD1_RATDRACCTIIN1_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACCTIIN1_DEFAULT                   (_PRS_RPURATD1_RATDRACCTIIN1_DEFAULT << 27)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACCTIIN2                           (0x1UL << 28)                                         /**< RAC_CTIIN2 Protection Bit                   */
#define _PRS_RPURATD1_RATDRACCTIIN2_SHIFT                    28                                                    /**< Shift value for PRS_RATDRACCTIIN2           */
#define _PRS_RPURATD1_RATDRACCTIIN2_MASK                     0x10000000UL                                          /**< Bit mask for PRS_RATDRACCTIIN2              */
#define _PRS_RPURATD1_RATDRACCTIIN2_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACCTIIN2_DEFAULT                   (_PRS_RPURATD1_RATDRACCTIIN2_DEFAULT << 28)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACCTIIN3                           (0x1UL << 29)                                         /**< RAC_CTIIN3 Protection Bit                   */
#define _PRS_RPURATD1_RATDRACCTIIN3_SHIFT                    29                                                    /**< Shift value for PRS_RATDRACCTIIN3           */
#define _PRS_RPURATD1_RATDRACCTIIN3_MASK                     0x20000000UL                                          /**< Bit mask for PRS_RATDRACCTIIN3              */
#define _PRS_RPURATD1_RATDRACCTIIN3_DEFAULT                  0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACCTIIN3_DEFAULT                   (_PRS_RPURATD1_RATDRACCTIIN3_DEFAULT << 29)           /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACFORCETX                          (0x1UL << 30)                                         /**< RAC_FORCETX Protection Bit                  */
#define _PRS_RPURATD1_RATDRACFORCETX_SHIFT                   30                                                    /**< Shift value for PRS_RATDRACFORCETX          */
#define _PRS_RPURATD1_RATDRACFORCETX_MASK                    0x40000000UL                                          /**< Bit mask for PRS_RATDRACFORCETX             */
#define _PRS_RPURATD1_RATDRACFORCETX_DEFAULT                 0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACFORCETX_DEFAULT                  (_PRS_RPURATD1_RATDRACFORCETX_DEFAULT << 30)          /**< Shifted mode DEFAULT for PRS_RPURATD1       */
#define PRS_RPURATD1_RATDRACRXDIS                            (0x1UL << 31)                                         /**< RAC_RXDIS Protection Bit                    */
#define _PRS_RPURATD1_RATDRACRXDIS_SHIFT                     31                                                    /**< Shift value for PRS_RATDRACRXDIS            */
#define _PRS_RPURATD1_RATDRACRXDIS_MASK                      0x80000000UL                                          /**< Bit mask for PRS_RATDRACRXDIS               */
#define _PRS_RPURATD1_RATDRACRXDIS_DEFAULT                   0x00000000UL                                          /**< Mode DEFAULT for PRS_RPURATD1               */
#define PRS_RPURATD1_RATDRACRXDIS_DEFAULT                    (_PRS_RPURATD1_RATDRACRXDIS_DEFAULT << 31)            /**< Shifted mode DEFAULT for PRS_RPURATD1       */

/* Bit fields for PRS RPURATD2 */
#define _PRS_RPURATD2_RESETVALUE                             0x00000000UL                                         /**< Default value for PRS_RPURATD2              */
#define _PRS_RPURATD2_MASK                                   0xFFFFFFFFUL                                         /**< Mask for PRS_RPURATD2                       */
#define PRS_RPURATD2_RATDRACRXEN                             (0x1UL << 0)                                         /**< RAC_RXEN Protection Bit                     */
#define _PRS_RPURATD2_RATDRACRXEN_SHIFT                      0                                                    /**< Shift value for PRS_RATDRACRXEN             */
#define _PRS_RPURATD2_RATDRACRXEN_MASK                       0x1UL                                                /**< Bit mask for PRS_RATDRACRXEN                */
#define _PRS_RPURATD2_RATDRACRXEN_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDRACRXEN_DEFAULT                     (_PRS_RPURATD2_RATDRACRXEN_DEFAULT << 0)             /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDRACTXEN                             (0x1UL << 1)                                         /**< RAC_TXEN Protection Bit                     */
#define _PRS_RPURATD2_RATDRACTXEN_SHIFT                      1                                                    /**< Shift value for PRS_RATDRACTXEN             */
#define _PRS_RPURATD2_RATDRACTXEN_MASK                       0x2UL                                                /**< Bit mask for PRS_RATDRACTXEN                */
#define _PRS_RPURATD2_RATDRACTXEN_DEFAULT                    0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDRACTXEN_DEFAULT                     (_PRS_RPURATD2_RATDRACTXEN_DEFAULT << 1)             /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC25                 (0x1UL << 2)                                         /**< SETAMPER_TAMPERSRC25 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC25_SHIFT          2                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC25 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC25_MASK           0x4UL                                                /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC25    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC25_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC25_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC25_DEFAULT << 2) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC26                 (0x1UL << 3)                                         /**< SETAMPER_TAMPERSRC26 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC26_SHIFT          3                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC26 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC26_MASK           0x8UL                                                /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC26    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC26_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC26_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC26_DEFAULT << 3) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC27                 (0x1UL << 4)                                         /**< SETAMPER_TAMPERSRC27 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC27_SHIFT          4                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC27 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC27_MASK           0x10UL                                               /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC27    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC27_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC27_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC27_DEFAULT << 4) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC28                 (0x1UL << 5)                                         /**< SETAMPER_TAMPERSRC28 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC28_SHIFT          5                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC28 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC28_MASK           0x20UL                                               /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC28    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC28_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC28_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC28_DEFAULT << 5) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC29                 (0x1UL << 6)                                         /**< SETAMPER_TAMPERSRC29 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC29_SHIFT          6                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC29 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC29_MASK           0x40UL                                               /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC29    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC29_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC29_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC29_DEFAULT << 6) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC30                 (0x1UL << 7)                                         /**< SETAMPER_TAMPERSRC30 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC30_SHIFT          7                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC30 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC30_MASK           0x80UL                                               /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC30    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC30_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC30_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC30_DEFAULT << 7) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC31                 (0x1UL << 8)                                         /**< SETAMPER_TAMPERSRC31 Protection Bit         */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC31_SHIFT          8                                                    /**< Shift value for PRS_RATDSETAMPERTAMPERSRC31 */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC31_MASK           0x100UL                                              /**< Bit mask for PRS_RATDSETAMPERTAMPERSRC31    */
#define _PRS_RPURATD2_RATDSETAMPERTAMPERSRC31_DEFAULT        0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSETAMPERTAMPERSRC31_DEFAULT         (_PRS_RPURATD2_RATDSETAMPERTAMPERSRC31_DEFAULT << 8) /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSYSRTC0IN0                          (0x1UL << 9)                                         /**< SYSRTC0_IN0 Protection Bit                  */
#define _PRS_RPURATD2_RATDSYSRTC0IN0_SHIFT                   9                                                    /**< Shift value for PRS_RATDSYSRTC0IN0          */
#define _PRS_RPURATD2_RATDSYSRTC0IN0_MASK                    0x200UL                                              /**< Bit mask for PRS_RATDSYSRTC0IN0             */
#define _PRS_RPURATD2_RATDSYSRTC0IN0_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSYSRTC0IN0_DEFAULT                  (_PRS_RPURATD2_RATDSYSRTC0IN0_DEFAULT << 9)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSYSRTC0IN1                          (0x1UL << 10)                                        /**< SYSRTC0_IN1 Protection Bit                  */
#define _PRS_RPURATD2_RATDSYSRTC0IN1_SHIFT                   10                                                   /**< Shift value for PRS_RATDSYSRTC0IN1          */
#define _PRS_RPURATD2_RATDSYSRTC0IN1_MASK                    0x400UL                                              /**< Bit mask for PRS_RATDSYSRTC0IN1             */
#define _PRS_RPURATD2_RATDSYSRTC0IN1_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSYSRTC0IN1_DEFAULT                  (_PRS_RPURATD2_RATDSYSRTC0IN1_DEFAULT << 10)         /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSYXO0OSCREQ                         (0x1UL << 11)                                        /**< SYXO0_OSCREQ Protection Bit                 */
#define _PRS_RPURATD2_RATDSYXO0OSCREQ_SHIFT                  11                                                   /**< Shift value for PRS_RATDSYXO0OSCREQ         */
#define _PRS_RPURATD2_RATDSYXO0OSCREQ_MASK                   0x800UL                                              /**< Bit mask for PRS_RATDSYXO0OSCREQ            */
#define _PRS_RPURATD2_RATDSYXO0OSCREQ_DEFAULT                0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSYXO0OSCREQ_DEFAULT                 (_PRS_RPURATD2_RATDSYXO0OSCREQ_DEFAULT << 11)        /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDSYXO0TIMEOUT                        (0x1UL << 12)                                        /**< SYXO0_TIMEOUT Protection Bit                */
#define _PRS_RPURATD2_RATDSYXO0TIMEOUT_SHIFT                 12                                                   /**< Shift value for PRS_RATDSYXO0TIMEOUT        */
#define _PRS_RPURATD2_RATDSYXO0TIMEOUT_MASK                  0x1000UL                                             /**< Bit mask for PRS_RATDSYXO0TIMEOUT           */
#define _PRS_RPURATD2_RATDSYXO0TIMEOUT_DEFAULT               0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDSYXO0TIMEOUT_DEFAULT                (_PRS_RPURATD2_RATDSYXO0TIMEOUT_DEFAULT << 12)       /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDCORECTIIN0                          (0x1UL << 13)                                        /**< CORE_CTIIN0 Protection Bit                  */
#define _PRS_RPURATD2_RATDCORECTIIN0_SHIFT                   13                                                   /**< Shift value for PRS_RATDCORECTIIN0          */
#define _PRS_RPURATD2_RATDCORECTIIN0_MASK                    0x2000UL                                             /**< Bit mask for PRS_RATDCORECTIIN0             */
#define _PRS_RPURATD2_RATDCORECTIIN0_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDCORECTIIN0_DEFAULT                  (_PRS_RPURATD2_RATDCORECTIIN0_DEFAULT << 13)         /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDCORECTIIN1                          (0x1UL << 14)                                        /**< CORE_CTIIN1 Protection Bit                  */
#define _PRS_RPURATD2_RATDCORECTIIN1_SHIFT                   14                                                   /**< Shift value for PRS_RATDCORECTIIN1          */
#define _PRS_RPURATD2_RATDCORECTIIN1_MASK                    0x4000UL                                             /**< Bit mask for PRS_RATDCORECTIIN1             */
#define _PRS_RPURATD2_RATDCORECTIIN1_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDCORECTIIN1_DEFAULT                  (_PRS_RPURATD2_RATDCORECTIIN1_DEFAULT << 14)         /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDCORECTIIN2                          (0x1UL << 15)                                        /**< CORE_CTIIN2 Protection Bit                  */
#define _PRS_RPURATD2_RATDCORECTIIN2_SHIFT                   15                                                   /**< Shift value for PRS_RATDCORECTIIN2          */
#define _PRS_RPURATD2_RATDCORECTIIN2_MASK                    0x8000UL                                             /**< Bit mask for PRS_RATDCORECTIIN2             */
#define _PRS_RPURATD2_RATDCORECTIIN2_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDCORECTIIN2_DEFAULT                  (_PRS_RPURATD2_RATDCORECTIIN2_DEFAULT << 15)         /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDCORECTIIN3                          (0x1UL << 16)                                        /**< CORE_CTIIN3 Protection Bit                  */
#define _PRS_RPURATD2_RATDCORECTIIN3_SHIFT                   16                                                   /**< Shift value for PRS_RATDCORECTIIN3          */
#define _PRS_RPURATD2_RATDCORECTIIN3_MASK                    0x10000UL                                            /**< Bit mask for PRS_RATDCORECTIIN3             */
#define _PRS_RPURATD2_RATDCORECTIIN3_DEFAULT                 0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDCORECTIIN3_DEFAULT                  (_PRS_RPURATD2_RATDCORECTIIN3_DEFAULT << 16)         /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDCOREM33RXEV                         (0x1UL << 17)                                        /**< CORE_M33RXEV Protection Bit                 */
#define _PRS_RPURATD2_RATDCOREM33RXEV_SHIFT                  17                                                   /**< Shift value for PRS_RATDCOREM33RXEV         */
#define _PRS_RPURATD2_RATDCOREM33RXEV_MASK                   0x20000UL                                            /**< Bit mask for PRS_RATDCOREM33RXEV            */
#define _PRS_RPURATD2_RATDCOREM33RXEV_DEFAULT                0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDCOREM33RXEV_DEFAULT                 (_PRS_RPURATD2_RATDCOREM33RXEV_DEFAULT << 17)        /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0CC0                           (0x1UL << 18)                                        /**< TIMER0_CC0 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER0CC0_SHIFT                    18                                                   /**< Shift value for PRS_RATDTIMER0CC0           */
#define _PRS_RPURATD2_RATDTIMER0CC0_MASK                     0x40000UL                                            /**< Bit mask for PRS_RATDTIMER0CC0              */
#define _PRS_RPURATD2_RATDTIMER0CC0_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0CC0_DEFAULT                   (_PRS_RPURATD2_RATDTIMER0CC0_DEFAULT << 18)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0CC1                           (0x1UL << 19)                                        /**< TIMER0_CC1 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER0CC1_SHIFT                    19                                                   /**< Shift value for PRS_RATDTIMER0CC1           */
#define _PRS_RPURATD2_RATDTIMER0CC1_MASK                     0x80000UL                                            /**< Bit mask for PRS_RATDTIMER0CC1              */
#define _PRS_RPURATD2_RATDTIMER0CC1_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0CC1_DEFAULT                   (_PRS_RPURATD2_RATDTIMER0CC1_DEFAULT << 19)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0CC2                           (0x1UL << 20)                                        /**< TIMER0_CC2 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER0CC2_SHIFT                    20                                                   /**< Shift value for PRS_RATDTIMER0CC2           */
#define _PRS_RPURATD2_RATDTIMER0CC2_MASK                     0x100000UL                                           /**< Bit mask for PRS_RATDTIMER0CC2              */
#define _PRS_RPURATD2_RATDTIMER0CC2_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0CC2_DEFAULT                   (_PRS_RPURATD2_RATDTIMER0CC2_DEFAULT << 20)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0DTI                           (0x1UL << 21)                                        /**< TIMER0_DTI Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER0DTI_SHIFT                    21                                                   /**< Shift value for PRS_RATDTIMER0DTI           */
#define _PRS_RPURATD2_RATDTIMER0DTI_MASK                     0x200000UL                                           /**< Bit mask for PRS_RATDTIMER0DTI              */
#define _PRS_RPURATD2_RATDTIMER0DTI_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0DTI_DEFAULT                   (_PRS_RPURATD2_RATDTIMER0DTI_DEFAULT << 21)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0DTIFS1                        (0x1UL << 22)                                        /**< TIMER0_DTIFS1 Protection Bit                */
#define _PRS_RPURATD2_RATDTIMER0DTIFS1_SHIFT                 22                                                   /**< Shift value for PRS_RATDTIMER0DTIFS1        */
#define _PRS_RPURATD2_RATDTIMER0DTIFS1_MASK                  0x400000UL                                           /**< Bit mask for PRS_RATDTIMER0DTIFS1           */
#define _PRS_RPURATD2_RATDTIMER0DTIFS1_DEFAULT               0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0DTIFS1_DEFAULT                (_PRS_RPURATD2_RATDTIMER0DTIFS1_DEFAULT << 22)       /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER0DTIFS2                        (0x1UL << 23)                                        /**< TIMER0_DTIFS2 Protection Bit                */
#define _PRS_RPURATD2_RATDTIMER0DTIFS2_SHIFT                 23                                                   /**< Shift value for PRS_RATDTIMER0DTIFS2        */
#define _PRS_RPURATD2_RATDTIMER0DTIFS2_MASK                  0x800000UL                                           /**< Bit mask for PRS_RATDTIMER0DTIFS2           */
#define _PRS_RPURATD2_RATDTIMER0DTIFS2_DEFAULT               0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER0DTIFS2_DEFAULT                (_PRS_RPURATD2_RATDTIMER0DTIFS2_DEFAULT << 23)       /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1CC0                           (0x1UL << 24)                                        /**< TIMER1_CC0 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER1CC0_SHIFT                    24                                                   /**< Shift value for PRS_RATDTIMER1CC0           */
#define _PRS_RPURATD2_RATDTIMER1CC0_MASK                     0x1000000UL                                          /**< Bit mask for PRS_RATDTIMER1CC0              */
#define _PRS_RPURATD2_RATDTIMER1CC0_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1CC0_DEFAULT                   (_PRS_RPURATD2_RATDTIMER1CC0_DEFAULT << 24)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1CC1                           (0x1UL << 25)                                        /**< TIMER1_CC1 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER1CC1_SHIFT                    25                                                   /**< Shift value for PRS_RATDTIMER1CC1           */
#define _PRS_RPURATD2_RATDTIMER1CC1_MASK                     0x2000000UL                                          /**< Bit mask for PRS_RATDTIMER1CC1              */
#define _PRS_RPURATD2_RATDTIMER1CC1_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1CC1_DEFAULT                   (_PRS_RPURATD2_RATDTIMER1CC1_DEFAULT << 25)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1CC2                           (0x1UL << 26)                                        /**< TIMER1_CC2 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER1CC2_SHIFT                    26                                                   /**< Shift value for PRS_RATDTIMER1CC2           */
#define _PRS_RPURATD2_RATDTIMER1CC2_MASK                     0x4000000UL                                          /**< Bit mask for PRS_RATDTIMER1CC2              */
#define _PRS_RPURATD2_RATDTIMER1CC2_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1CC2_DEFAULT                   (_PRS_RPURATD2_RATDTIMER1CC2_DEFAULT << 26)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1DTI                           (0x1UL << 27)                                        /**< TIMER1_DTI Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER1DTI_SHIFT                    27                                                   /**< Shift value for PRS_RATDTIMER1DTI           */
#define _PRS_RPURATD2_RATDTIMER1DTI_MASK                     0x8000000UL                                          /**< Bit mask for PRS_RATDTIMER1DTI              */
#define _PRS_RPURATD2_RATDTIMER1DTI_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1DTI_DEFAULT                   (_PRS_RPURATD2_RATDTIMER1DTI_DEFAULT << 27)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1DTIFS1                        (0x1UL << 28)                                        /**< TIMER1_DTIFS1 Protection Bit                */
#define _PRS_RPURATD2_RATDTIMER1DTIFS1_SHIFT                 28                                                   /**< Shift value for PRS_RATDTIMER1DTIFS1        */
#define _PRS_RPURATD2_RATDTIMER1DTIFS1_MASK                  0x10000000UL                                         /**< Bit mask for PRS_RATDTIMER1DTIFS1           */
#define _PRS_RPURATD2_RATDTIMER1DTIFS1_DEFAULT               0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1DTIFS1_DEFAULT                (_PRS_RPURATD2_RATDTIMER1DTIFS1_DEFAULT << 28)       /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER1DTIFS2                        (0x1UL << 29)                                        /**< TIMER1_DTIFS2 Protection Bit                */
#define _PRS_RPURATD2_RATDTIMER1DTIFS2_SHIFT                 29                                                   /**< Shift value for PRS_RATDTIMER1DTIFS2        */
#define _PRS_RPURATD2_RATDTIMER1DTIFS2_MASK                  0x20000000UL                                         /**< Bit mask for PRS_RATDTIMER1DTIFS2           */
#define _PRS_RPURATD2_RATDTIMER1DTIFS2_DEFAULT               0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER1DTIFS2_DEFAULT                (_PRS_RPURATD2_RATDTIMER1DTIFS2_DEFAULT << 29)       /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER2CC0                           (0x1UL << 30)                                        /**< TIMER2_CC0 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER2CC0_SHIFT                    30                                                   /**< Shift value for PRS_RATDTIMER2CC0           */
#define _PRS_RPURATD2_RATDTIMER2CC0_MASK                     0x40000000UL                                         /**< Bit mask for PRS_RATDTIMER2CC0              */
#define _PRS_RPURATD2_RATDTIMER2CC0_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER2CC0_DEFAULT                   (_PRS_RPURATD2_RATDTIMER2CC0_DEFAULT << 30)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */
#define PRS_RPURATD2_RATDTIMER2CC1                           (0x1UL << 31)                                        /**< TIMER2_CC1 Protection Bit                   */
#define _PRS_RPURATD2_RATDTIMER2CC1_SHIFT                    31                                                   /**< Shift value for PRS_RATDTIMER2CC1           */
#define _PRS_RPURATD2_RATDTIMER2CC1_MASK                     0x80000000UL                                         /**< Bit mask for PRS_RATDTIMER2CC1              */
#define _PRS_RPURATD2_RATDTIMER2CC1_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for PRS_RPURATD2               */
#define PRS_RPURATD2_RATDTIMER2CC1_DEFAULT                   (_PRS_RPURATD2_RATDTIMER2CC1_DEFAULT << 31)          /**< Shifted mode DEFAULT for PRS_RPURATD2       */

/* Bit fields for PRS RPURATD3 */
#define _PRS_RPURATD3_RESETVALUE                             0x00000000UL                                        /**< Default value for PRS_RPURATD3              */
#define _PRS_RPURATD3_MASK                                   0xFF8FFFFFUL                                        /**< Mask for PRS_RPURATD3                       */
#define PRS_RPURATD3_RATDTIMER2CC2                           (0x1UL << 0)                                        /**< TIMER2_CC2 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER2CC2_SHIFT                    0                                                   /**< Shift value for PRS_RATDTIMER2CC2           */
#define _PRS_RPURATD3_RATDTIMER2CC2_MASK                     0x1UL                                               /**< Bit mask for PRS_RATDTIMER2CC2              */
#define _PRS_RPURATD3_RATDTIMER2CC2_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER2CC2_DEFAULT                   (_PRS_RPURATD3_RATDTIMER2CC2_DEFAULT << 0)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER2DTI                           (0x1UL << 1)                                        /**< TIMER2_DTI Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER2DTI_SHIFT                    1                                                   /**< Shift value for PRS_RATDTIMER2DTI           */
#define _PRS_RPURATD3_RATDTIMER2DTI_MASK                     0x2UL                                               /**< Bit mask for PRS_RATDTIMER2DTI              */
#define _PRS_RPURATD3_RATDTIMER2DTI_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER2DTI_DEFAULT                   (_PRS_RPURATD3_RATDTIMER2DTI_DEFAULT << 1)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER2DTIFS1                        (0x1UL << 2)                                        /**< TIMER2_DTIFS1 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER2DTIFS1_SHIFT                 2                                                   /**< Shift value for PRS_RATDTIMER2DTIFS1        */
#define _PRS_RPURATD3_RATDTIMER2DTIFS1_MASK                  0x4UL                                               /**< Bit mask for PRS_RATDTIMER2DTIFS1           */
#define _PRS_RPURATD3_RATDTIMER2DTIFS1_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER2DTIFS1_DEFAULT                (_PRS_RPURATD3_RATDTIMER2DTIFS1_DEFAULT << 2)       /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER2DTIFS2                        (0x1UL << 3)                                        /**< TIMER2_DTIFS2 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER2DTIFS2_SHIFT                 3                                                   /**< Shift value for PRS_RATDTIMER2DTIFS2        */
#define _PRS_RPURATD3_RATDTIMER2DTIFS2_MASK                  0x8UL                                               /**< Bit mask for PRS_RATDTIMER2DTIFS2           */
#define _PRS_RPURATD3_RATDTIMER2DTIFS2_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER2DTIFS2_DEFAULT                (_PRS_RPURATD3_RATDTIMER2DTIFS2_DEFAULT << 3)       /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3CC0                           (0x1UL << 4)                                        /**< TIMER3_CC0 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER3CC0_SHIFT                    4                                                   /**< Shift value for PRS_RATDTIMER3CC0           */
#define _PRS_RPURATD3_RATDTIMER3CC0_MASK                     0x10UL                                              /**< Bit mask for PRS_RATDTIMER3CC0              */
#define _PRS_RPURATD3_RATDTIMER3CC0_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3CC0_DEFAULT                   (_PRS_RPURATD3_RATDTIMER3CC0_DEFAULT << 4)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3CC1                           (0x1UL << 5)                                        /**< TIMER3_CC1 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER3CC1_SHIFT                    5                                                   /**< Shift value for PRS_RATDTIMER3CC1           */
#define _PRS_RPURATD3_RATDTIMER3CC1_MASK                     0x20UL                                              /**< Bit mask for PRS_RATDTIMER3CC1              */
#define _PRS_RPURATD3_RATDTIMER3CC1_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3CC1_DEFAULT                   (_PRS_RPURATD3_RATDTIMER3CC1_DEFAULT << 5)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3CC2                           (0x1UL << 6)                                        /**< TIMER3_CC2 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER3CC2_SHIFT                    6                                                   /**< Shift value for PRS_RATDTIMER3CC2           */
#define _PRS_RPURATD3_RATDTIMER3CC2_MASK                     0x40UL                                              /**< Bit mask for PRS_RATDTIMER3CC2              */
#define _PRS_RPURATD3_RATDTIMER3CC2_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3CC2_DEFAULT                   (_PRS_RPURATD3_RATDTIMER3CC2_DEFAULT << 6)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3DTI                           (0x1UL << 7)                                        /**< TIMER3_DTI Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER3DTI_SHIFT                    7                                                   /**< Shift value for PRS_RATDTIMER3DTI           */
#define _PRS_RPURATD3_RATDTIMER3DTI_MASK                     0x80UL                                              /**< Bit mask for PRS_RATDTIMER3DTI              */
#define _PRS_RPURATD3_RATDTIMER3DTI_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3DTI_DEFAULT                   (_PRS_RPURATD3_RATDTIMER3DTI_DEFAULT << 7)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3DTIFS1                        (0x1UL << 8)                                        /**< TIMER3_DTIFS1 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER3DTIFS1_SHIFT                 8                                                   /**< Shift value for PRS_RATDTIMER3DTIFS1        */
#define _PRS_RPURATD3_RATDTIMER3DTIFS1_MASK                  0x100UL                                             /**< Bit mask for PRS_RATDTIMER3DTIFS1           */
#define _PRS_RPURATD3_RATDTIMER3DTIFS1_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3DTIFS1_DEFAULT                (_PRS_RPURATD3_RATDTIMER3DTIFS1_DEFAULT << 8)       /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER3DTIFS2                        (0x1UL << 9)                                        /**< TIMER3_DTIFS2 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER3DTIFS2_SHIFT                 9                                                   /**< Shift value for PRS_RATDTIMER3DTIFS2        */
#define _PRS_RPURATD3_RATDTIMER3DTIFS2_MASK                  0x200UL                                             /**< Bit mask for PRS_RATDTIMER3DTIFS2           */
#define _PRS_RPURATD3_RATDTIMER3DTIFS2_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER3DTIFS2_DEFAULT                (_PRS_RPURATD3_RATDTIMER3DTIFS2_DEFAULT << 9)       /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4CC0                           (0x1UL << 10)                                       /**< TIMER4_CC0 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER4CC0_SHIFT                    10                                                  /**< Shift value for PRS_RATDTIMER4CC0           */
#define _PRS_RPURATD3_RATDTIMER4CC0_MASK                     0x400UL                                             /**< Bit mask for PRS_RATDTIMER4CC0              */
#define _PRS_RPURATD3_RATDTIMER4CC0_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4CC0_DEFAULT                   (_PRS_RPURATD3_RATDTIMER4CC0_DEFAULT << 10)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4CC1                           (0x1UL << 11)                                       /**< TIMER4_CC1 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER4CC1_SHIFT                    11                                                  /**< Shift value for PRS_RATDTIMER4CC1           */
#define _PRS_RPURATD3_RATDTIMER4CC1_MASK                     0x800UL                                             /**< Bit mask for PRS_RATDTIMER4CC1              */
#define _PRS_RPURATD3_RATDTIMER4CC1_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4CC1_DEFAULT                   (_PRS_RPURATD3_RATDTIMER4CC1_DEFAULT << 11)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4CC2                           (0x1UL << 12)                                       /**< TIMER4_CC2 Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER4CC2_SHIFT                    12                                                  /**< Shift value for PRS_RATDTIMER4CC2           */
#define _PRS_RPURATD3_RATDTIMER4CC2_MASK                     0x1000UL                                            /**< Bit mask for PRS_RATDTIMER4CC2              */
#define _PRS_RPURATD3_RATDTIMER4CC2_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4CC2_DEFAULT                   (_PRS_RPURATD3_RATDTIMER4CC2_DEFAULT << 12)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4DTI                           (0x1UL << 13)                                       /**< TIMER4_DTI Protection Bit                   */
#define _PRS_RPURATD3_RATDTIMER4DTI_SHIFT                    13                                                  /**< Shift value for PRS_RATDTIMER4DTI           */
#define _PRS_RPURATD3_RATDTIMER4DTI_MASK                     0x2000UL                                            /**< Bit mask for PRS_RATDTIMER4DTI              */
#define _PRS_RPURATD3_RATDTIMER4DTI_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4DTI_DEFAULT                   (_PRS_RPURATD3_RATDTIMER4DTI_DEFAULT << 13)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4DTIFS1                        (0x1UL << 14)                                       /**< TIMER4_DTIFS1 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER4DTIFS1_SHIFT                 14                                                  /**< Shift value for PRS_RATDTIMER4DTIFS1        */
#define _PRS_RPURATD3_RATDTIMER4DTIFS1_MASK                  0x4000UL                                            /**< Bit mask for PRS_RATDTIMER4DTIFS1           */
#define _PRS_RPURATD3_RATDTIMER4DTIFS1_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4DTIFS1_DEFAULT                (_PRS_RPURATD3_RATDTIMER4DTIFS1_DEFAULT << 14)      /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDTIMER4DTIFS2                        (0x1UL << 15)                                       /**< TIMER4_DTIFS2 Protection Bit                */
#define _PRS_RPURATD3_RATDTIMER4DTIFS2_SHIFT                 15                                                  /**< Shift value for PRS_RATDTIMER4DTIFS2        */
#define _PRS_RPURATD3_RATDTIMER4DTIFS2_MASK                  0x8000UL                                            /**< Bit mask for PRS_RATDTIMER4DTIFS2           */
#define _PRS_RPURATD3_RATDTIMER4DTIFS2_DEFAULT               0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDTIMER4DTIFS2_DEFAULT                (_PRS_RPURATD3_RATDTIMER4DTIFS2_DEFAULT << 15)      /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDUSART0CLK                           (0x1UL << 16)                                       /**< USART0_CLK Protection Bit                   */
#define _PRS_RPURATD3_RATDUSART0CLK_SHIFT                    16                                                  /**< Shift value for PRS_RATDUSART0CLK           */
#define _PRS_RPURATD3_RATDUSART0CLK_MASK                     0x10000UL                                           /**< Bit mask for PRS_RATDUSART0CLK              */
#define _PRS_RPURATD3_RATDUSART0CLK_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDUSART0CLK_DEFAULT                   (_PRS_RPURATD3_RATDUSART0CLK_DEFAULT << 16)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDUSART0IR                            (0x1UL << 17)                                       /**< USART0_IR Protection Bit                    */
#define _PRS_RPURATD3_RATDUSART0IR_SHIFT                     17                                                  /**< Shift value for PRS_RATDUSART0IR            */
#define _PRS_RPURATD3_RATDUSART0IR_MASK                      0x20000UL                                           /**< Bit mask for PRS_RATDUSART0IR               */
#define _PRS_RPURATD3_RATDUSART0IR_DEFAULT                   0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDUSART0IR_DEFAULT                    (_PRS_RPURATD3_RATDUSART0IR_DEFAULT << 17)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDUSART0RX                            (0x1UL << 18)                                       /**< USART0_RX Protection Bit                    */
#define _PRS_RPURATD3_RATDUSART0RX_SHIFT                     18                                                  /**< Shift value for PRS_RATDUSART0RX            */
#define _PRS_RPURATD3_RATDUSART0RX_MASK                      0x40000UL                                           /**< Bit mask for PRS_RATDUSART0RX               */
#define _PRS_RPURATD3_RATDUSART0RX_DEFAULT                   0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDUSART0RX_DEFAULT                    (_PRS_RPURATD3_RATDUSART0RX_DEFAULT << 18)          /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDUSART0TRIGGER                       (0x1UL << 19)                                       /**< USART0_TRIGGER Protection Bit               */
#define _PRS_RPURATD3_RATDUSART0TRIGGER_SHIFT                19                                                  /**< Shift value for PRS_RATDUSART0TRIGGER       */
#define _PRS_RPURATD3_RATDUSART0TRIGGER_MASK                 0x80000UL                                           /**< Bit mask for PRS_RATDUSART0TRIGGER          */
#define _PRS_RPURATD3_RATDUSART0TRIGGER_DEFAULT              0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDUSART0TRIGGER_DEFAULT               (_PRS_RPURATD3_RATDUSART0TRIGGER_DEFAULT << 19)     /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0                   (0x1UL << 23)                                       /**< VDAC0_ASYNCTRIGCH0 Protection Bit           */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0_SHIFT            23                                                  /**< Shift value for PRS_RATDVDAC0ASYNCTRIGCH0   */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0_MASK             0x800000UL                                          /**< Bit mask for PRS_RATDVDAC0ASYNCTRIGCH0      */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0_DEFAULT           (_PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH0_DEFAULT << 23) /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1                   (0x1UL << 24)                                       /**< VDAC0_ASYNCTRIGCH1 Protection Bit           */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1_SHIFT            24                                                  /**< Shift value for PRS_RATDVDAC0ASYNCTRIGCH1   */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1_MASK             0x1000000UL                                         /**< Bit mask for PRS_RATDVDAC0ASYNCTRIGCH1      */
#define _PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1_DEFAULT           (_PRS_RPURATD3_RATDVDAC0ASYNCTRIGCH1_DEFAULT << 24) /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0                    (0x1UL << 25)                                       /**< VDAC0_SYNCTRIGCH0 Protection Bit            */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0_SHIFT             25                                                  /**< Shift value for PRS_RATDVDAC0SYNCTRIGCH0    */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0_MASK              0x2000000UL                                         /**< Bit mask for PRS_RATDVDAC0SYNCTRIGCH0       */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0_DEFAULT            (_PRS_RPURATD3_RATDVDAC0SYNCTRIGCH0_DEFAULT << 25)  /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1                    (0x1UL << 26)                                       /**< VDAC0_SYNCTRIGCH1 Protection Bit            */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1_SHIFT             26                                                  /**< Shift value for PRS_RATDVDAC0SYNCTRIGCH1    */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1_MASK              0x4000000UL                                         /**< Bit mask for PRS_RATDVDAC0SYNCTRIGCH1       */
#define _PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1_DEFAULT            (_PRS_RPURATD3_RATDVDAC0SYNCTRIGCH1_DEFAULT << 26)  /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0                   (0x1UL << 27)                                       /**< VDAC1_ASYNCTRIGCH0 Protection Bit           */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0_SHIFT            27                                                  /**< Shift value for PRS_RATDVDAC1ASYNCTRIGCH0   */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0_MASK             0x8000000UL                                         /**< Bit mask for PRS_RATDVDAC1ASYNCTRIGCH0      */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0_DEFAULT           (_PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH0_DEFAULT << 27) /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1                   (0x1UL << 28)                                       /**< VDAC1_ASYNCTRIGCH1 Protection Bit           */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1_SHIFT            28                                                  /**< Shift value for PRS_RATDVDAC1ASYNCTRIGCH1   */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1_MASK             0x10000000UL                                        /**< Bit mask for PRS_RATDVDAC1ASYNCTRIGCH1      */
#define _PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1_DEFAULT           (_PRS_RPURATD3_RATDVDAC1ASYNCTRIGCH1_DEFAULT << 28) /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0                    (0x1UL << 29)                                       /**< VDAC1_SYNCTRIGCH0 Protection Bit            */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0_SHIFT             29                                                  /**< Shift value for PRS_RATDVDAC1SYNCTRIGCH0    */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0_MASK              0x20000000UL                                        /**< Bit mask for PRS_RATDVDAC1SYNCTRIGCH0       */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0_DEFAULT            (_PRS_RPURATD3_RATDVDAC1SYNCTRIGCH0_DEFAULT << 29)  /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1                    (0x1UL << 30)                                       /**< VDAC1_SYNCTRIGCH1 Protection Bit            */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1_SHIFT             30                                                  /**< Shift value for PRS_RATDVDAC1SYNCTRIGCH1    */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1_MASK              0x40000000UL                                        /**< Bit mask for PRS_RATDVDAC1SYNCTRIGCH1       */
#define _PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1_DEFAULT            (_PRS_RPURATD3_RATDVDAC1SYNCTRIGCH1_DEFAULT << 30)  /**< Shifted mode DEFAULT for PRS_RPURATD3       */
#define PRS_RPURATD3_RATDWDOG0SRC0                           (0x1UL << 31)                                       /**< WDOG0_SRC0 Protection Bit                   */
#define _PRS_RPURATD3_RATDWDOG0SRC0_SHIFT                    31                                                  /**< Shift value for PRS_RATDWDOG0SRC0           */
#define _PRS_RPURATD3_RATDWDOG0SRC0_MASK                     0x80000000UL                                        /**< Bit mask for PRS_RATDWDOG0SRC0              */
#define _PRS_RPURATD3_RATDWDOG0SRC0_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for PRS_RPURATD3               */
#define PRS_RPURATD3_RATDWDOG0SRC0_DEFAULT                   (_PRS_RPURATD3_RATDWDOG0SRC0_DEFAULT << 31)         /**< Shifted mode DEFAULT for PRS_RPURATD3       */

/* Bit fields for PRS RPURATD4 */
#define _PRS_RPURATD4_RESETVALUE                             0x00000000UL                               /**< Default value for PRS_RPURATD4              */
#define _PRS_RPURATD4_MASK                                   0x00000007UL                               /**< Mask for PRS_RPURATD4                       */
#define PRS_RPURATD4_RATDWDOG0SRC1                           (0x1UL << 0)                               /**< WDOG0_SRC1 Protection Bit                   */
#define _PRS_RPURATD4_RATDWDOG0SRC1_SHIFT                    0                                          /**< Shift value for PRS_RATDWDOG0SRC1           */
#define _PRS_RPURATD4_RATDWDOG0SRC1_MASK                     0x1UL                                      /**< Bit mask for PRS_RATDWDOG0SRC1              */
#define _PRS_RPURATD4_RATDWDOG0SRC1_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for PRS_RPURATD4               */
#define PRS_RPURATD4_RATDWDOG0SRC1_DEFAULT                   (_PRS_RPURATD4_RATDWDOG0SRC1_DEFAULT << 0) /**< Shifted mode DEFAULT for PRS_RPURATD4       */
#define PRS_RPURATD4_RATDWDOG1SRC0                           (0x1UL << 1)                               /**< WDOG1_SRC0 Protection Bit                   */
#define _PRS_RPURATD4_RATDWDOG1SRC0_SHIFT                    1                                          /**< Shift value for PRS_RATDWDOG1SRC0           */
#define _PRS_RPURATD4_RATDWDOG1SRC0_MASK                     0x2UL                                      /**< Bit mask for PRS_RATDWDOG1SRC0              */
#define _PRS_RPURATD4_RATDWDOG1SRC0_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for PRS_RPURATD4               */
#define PRS_RPURATD4_RATDWDOG1SRC0_DEFAULT                   (_PRS_RPURATD4_RATDWDOG1SRC0_DEFAULT << 1) /**< Shifted mode DEFAULT for PRS_RPURATD4       */
#define PRS_RPURATD4_RATDWDOG1SRC1                           (0x1UL << 2)                               /**< WDOG1_SRC1 Protection Bit                   */
#define _PRS_RPURATD4_RATDWDOG1SRC1_SHIFT                    2                                          /**< Shift value for PRS_RATDWDOG1SRC1           */
#define _PRS_RPURATD4_RATDWDOG1SRC1_MASK                     0x4UL                                      /**< Bit mask for PRS_RATDWDOG1SRC1              */
#define _PRS_RPURATD4_RATDWDOG1SRC1_DEFAULT                  0x00000000UL                               /**< Mode DEFAULT for PRS_RPURATD4               */
#define PRS_RPURATD4_RATDWDOG1SRC1_DEFAULT                   (_PRS_RPURATD4_RATDWDOG1SRC1_DEFAULT << 2) /**< Shifted mode DEFAULT for PRS_RPURATD4       */

/** @} End of group EFR32MG24_PRS_BitFields */
/** @} End of group EFR32MG24_PRS */
/** @} End of group Parts */

#endif /* EFR32MG24_PRS_H */
