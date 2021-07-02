/**************************************************************************//**
 * @file
 * @brief MGM24 GPIO register and bit field definitions
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
#ifndef MGM24_GPIO_H
#define MGM24_GPIO_H
#define GPIO_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/

#include "mgm24_gpio_port.h"

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< ACMP0 pin enable                                   */
  __IOM uint32_t ACMPOUTROUTE;                       /**< ACMPOUT port/pin select                            */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_ACMPROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< CMU pin enable                                     */
  __IOM uint32_t CLKIN0ROUTE;                        /**< CLKIN0 port/pin select                             */
  __IOM uint32_t CLKOUT0ROUTE;                       /**< CLKOUT0 port/pin select                            */
  __IOM uint32_t CLKOUT1ROUTE;                       /**< CLKOUT1 port/pin select                            */
  __IOM uint32_t CLKOUT2ROUTE;                       /**< CLKOUT2 port/pin select                            */
  uint32_t       RESERVED0[2U];                      /**< Reserved for future use                            */
} GPIO_CMUROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< DCDC pin enable                                    */
  __IOM uint32_t DCDCCOREHIDDENROUTE;                /**< DCDCCOREHIDDEN port/pin select                     */
  uint32_t       RESERVED0[2U];                      /**< Reserved for future use                            */
} GPIO_DCDCROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< EUSART0 pin enable                                 */
  __IOM uint32_t CSROUTE;                            /**< CS port/pin select                                 */
  __IOM uint32_t CTSROUTE;                           /**< CTS port/pin select                                */
  __IOM uint32_t RTSROUTE;                           /**< RTS port/pin select                                */
  __IOM uint32_t RXROUTE;                            /**< RX port/pin select                                 */
  __IOM uint32_t SCLKROUTE;                          /**< SCLK port/pin select                               */
  __IOM uint32_t TXROUTE;                            /**< TX port/pin select                                 */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_EUSARTROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< FRC pin enable                                     */
  __IOM uint32_t DCLKROUTE;                          /**< DCLK port/pin select                               */
  __IOM uint32_t DFRAMEROUTE;                        /**< DFRAME port/pin select                             */
  __IOM uint32_t DOUTROUTE;                          /**< DOUT port/pin select                               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_FRCROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< I2C0 pin enable                                    */
  __IOM uint32_t SCLROUTE;                           /**< SCL port/pin select                                */
  __IOM uint32_t SDAROUTE;                           /**< SDA port/pin select                                */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_I2CROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< KEYPAD pin enable                                  */
  __IOM uint32_t COLOUT0ROUTE;                       /**< COLOUT0 port/pin select                            */
  __IOM uint32_t COLOUT1ROUTE;                       /**< COLOUT1 port/pin select                            */
  __IOM uint32_t COLOUT2ROUTE;                       /**< COLOUT2 port/pin select                            */
  __IOM uint32_t COLOUT3ROUTE;                       /**< COLOUT3 port/pin select                            */
  __IOM uint32_t COLOUT4ROUTE;                       /**< COLOUT4 port/pin select                            */
  __IOM uint32_t COLOUT5ROUTE;                       /**< COLOUT5 port/pin select                            */
  __IOM uint32_t COLOUT6ROUTE;                       /**< COLOUT6 port/pin select                            */
  __IOM uint32_t COLOUT7ROUTE;                       /**< COLOUT7 port/pin select                            */
  __IOM uint32_t ROWSENSE0ROUTE;                     /**< ROWSENSE0 port/pin select                          */
  __IOM uint32_t ROWSENSE1ROUTE;                     /**< ROWSENSE1 port/pin select                          */
  __IOM uint32_t ROWSENSE2ROUTE;                     /**< ROWSENSE2 port/pin select                          */
  __IOM uint32_t ROWSENSE3ROUTE;                     /**< ROWSENSE3 port/pin select                          */
  __IOM uint32_t ROWSENSE4ROUTE;                     /**< ROWSENSE4 port/pin select                          */
  __IOM uint32_t ROWSENSE5ROUTE;                     /**< ROWSENSE5 port/pin select                          */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_KEYSCANROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< LETIMER pin enable                                 */
  __IOM uint32_t OUT0ROUTE;                          /**< OUT0 port/pin select                               */
  __IOM uint32_t OUT1ROUTE;                          /**< OUT1 port/pin select                               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_LETIMERROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< MODEM pin enable                                   */
  __IOM uint32_t ANT0ROUTE;                          /**< ANT0 port/pin select                               */
  __IOM uint32_t ANT1ROUTE;                          /**< ANT1 port/pin select                               */
  __IOM uint32_t ANTROLLOVERROUTE;                   /**< ANTROLLOVER port/pin select                        */
  __IOM uint32_t ANTRR0ROUTE;                        /**< ANTRR0 port/pin select                             */
  __IOM uint32_t ANTRR1ROUTE;                        /**< ANTRR1 port/pin select                             */
  __IOM uint32_t ANTRR2ROUTE;                        /**< ANTRR2 port/pin select                             */
  __IOM uint32_t ANTRR3ROUTE;                        /**< ANTRR3 port/pin select                             */
  __IOM uint32_t ANTRR4ROUTE;                        /**< ANTRR4 port/pin select                             */
  __IOM uint32_t ANTRR5ROUTE;                        /**< ANTRR5 port/pin select                             */
  __IOM uint32_t ANTSWENROUTE;                       /**< ANTSWEN port/pin select                            */
  __IOM uint32_t ANTSWUSROUTE;                       /**< ANTSWUS port/pin select                            */
  __IOM uint32_t ANTTRIGROUTE;                       /**< ANTTRIG port/pin select                            */
  __IOM uint32_t ANTTRIGSTOPROUTE;                   /**< ANTTRIGSTOP port/pin select                        */
  __IOM uint32_t DCLKROUTE;                          /**< DCLK port/pin select                               */
  __IOM uint32_t DINROUTE;                           /**< DIN port/pin select                                */
  __IOM uint32_t DOUTROUTE;                          /**< DOUT port/pin select                               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_MODEMROUTE_TypeDef;

typedef struct {
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
  __IOM uint32_t S0INROUTE;                          /**< S0IN port/pin select                               */
  __IOM uint32_t S1INROUTE;                          /**< S1IN port/pin select                               */
  uint32_t       RESERVED1[1U];                      /**< Reserved for future use                            */
} GPIO_PCNTROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< PRS0 pin enable                                    */
  __IOM uint32_t ASYNCH0ROUTE;                       /**< ASYNCH0 port/pin select                            */
  __IOM uint32_t ASYNCH1ROUTE;                       /**< ASYNCH1 port/pin select                            */
  __IOM uint32_t ASYNCH2ROUTE;                       /**< ASYNCH2 port/pin select                            */
  __IOM uint32_t ASYNCH3ROUTE;                       /**< ASYNCH3 port/pin select                            */
  __IOM uint32_t ASYNCH4ROUTE;                       /**< ASYNCH4 port/pin select                            */
  __IOM uint32_t ASYNCH5ROUTE;                       /**< ASYNCH5 port/pin select                            */
  __IOM uint32_t ASYNCH6ROUTE;                       /**< ASYNCH6 port/pin select                            */
  __IOM uint32_t ASYNCH7ROUTE;                       /**< ASYNCH7 port/pin select                            */
  __IOM uint32_t ASYNCH8ROUTE;                       /**< ASYNCH8 port/pin select                            */
  __IOM uint32_t ASYNCH9ROUTE;                       /**< ASYNCH9 port/pin select                            */
  __IOM uint32_t ASYNCH10ROUTE;                      /**< ASYNCH10 port/pin select                           */
  __IOM uint32_t ASYNCH11ROUTE;                      /**< ASYNCH11 port/pin select                           */
  __IOM uint32_t ASYNCH12ROUTE;                      /**< ASYNCH12 port/pin select                           */
  __IOM uint32_t ASYNCH13ROUTE;                      /**< ASYNCH13 port/pin select                           */
  __IOM uint32_t ASYNCH14ROUTE;                      /**< ASYNCH14 port/pin select                           */
  __IOM uint32_t ASYNCH15ROUTE;                      /**< ASYNCH15 port/pin select                           */
  __IOM uint32_t SYNCH0ROUTE;                        /**< SYNCH0 port/pin select                             */
  __IOM uint32_t SYNCH1ROUTE;                        /**< SYNCH1 port/pin select                             */
  __IOM uint32_t SYNCH2ROUTE;                        /**< SYNCH2 port/pin select                             */
  __IOM uint32_t SYNCH3ROUTE;                        /**< SYNCH3 port/pin select                             */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_PRSROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< RAC pin enable                                     */
  __IOM uint32_t LNAENROUTE;                         /**< LNAEN port/pin select                              */
  __IOM uint32_t PAENROUTE;                          /**< PAEN port/pin select                               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_DBUSRACROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< RFECA0 pin enable                                  */
  __IOM uint32_t DATAOUT0ROUTE;                      /**< DATAOUT0 port/pin select                           */
  __IOM uint32_t DATAOUT1ROUTE;                      /**< DATAOUT1 port/pin select                           */
  __IOM uint32_t DATAOUT2ROUTE;                      /**< DATAOUT2 port/pin select                           */
  __IOM uint32_t DATAOUT3ROUTE;                      /**< DATAOUT3 port/pin select                           */
  __IOM uint32_t DATAOUT4ROUTE;                      /**< DATAOUT4 port/pin select                           */
  __IOM uint32_t DATAOUT5ROUTE;                      /**< DATAOUT5 port/pin select                           */
  __IOM uint32_t DATAOUT6ROUTE;                      /**< DATAOUT6 port/pin select                           */
  __IOM uint32_t DATAOUT7ROUTE;                      /**< DATAOUT7 port/pin select                           */
  __IOM uint32_t DATAOUT8ROUTE;                      /**< DATAOUT8 port/pin select                           */
  __IOM uint32_t DATAOUT9ROUTE;                      /**< DATAOUT9 port/pin select                           */
  __IOM uint32_t DATAOUT10ROUTE;                     /**< DATAOUT10 port/pin select                          */
  __IOM uint32_t DATAOUT11ROUTE;                     /**< DATAOUT11 port/pin select                          */
  __IOM uint32_t DATAOUT12ROUTE;                     /**< DATAOUT12 port/pin select                          */
  __IOM uint32_t DATAOUT13ROUTE;                     /**< DATAOUT13 port/pin select                          */
  __IOM uint32_t DATAOUT14ROUTE;                     /**< DATAOUT14 port/pin select                          */
  __IOM uint32_t DATAOUT15ROUTE;                     /**< DATAOUT15 port/pin select                          */
  __IOM uint32_t DATAOUT16ROUTE;                     /**< DATAOUT16 port/pin select                          */
  __IOM uint32_t DATAOUT17ROUTE;                     /**< DATAOUT17 port/pin select                          */
  __IOM uint32_t DATAOUT18ROUTE;                     /**< DATAOUT18 port/pin select                          */
  __IOM uint32_t DATAVALIDROUTE;                     /**< DATAVALID port/pin select                          */
  __IOM uint32_t TRIGGERINROUTE;                     /**< TRIGGERIN port/pin select                          */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_DBUSRFECAROUTE_TypeDef;

typedef struct {
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
  __IOM uint32_t BUFOUTREQINASYNCROUTE;              /**< BUFOUTREQINASYNC port/pin select                   */
  uint32_t       RESERVED1[1U];                      /**< Reserved for future use                            */
} GPIO_DBUSSYXOROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< TIMER0 pin enable                                  */
  __IOM uint32_t CC0ROUTE;                           /**< CC0 port/pin select                                */
  __IOM uint32_t CC1ROUTE;                           /**< CC1 port/pin select                                */
  __IOM uint32_t CC2ROUTE;                           /**< CC2 port/pin select                                */
  __IOM uint32_t CCC0ROUTE;                          /**< CCC0 port/pin select                               */
  __IOM uint32_t CCC1ROUTE;                          /**< CCC1 port/pin select                               */
  __IOM uint32_t CCC2ROUTE;                          /**< CCC2 port/pin select                               */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_TIMERROUTE_TypeDef;

typedef struct {
  __IOM uint32_t ROUTEEN;                            /**< USART0 pin enable                                  */
  __IOM uint32_t CSROUTE;                            /**< CS port/pin select                                 */
  __IOM uint32_t CTSROUTE;                           /**< CTS port/pin select                                */
  __IOM uint32_t RTSROUTE;                           /**< RTS port/pin select                                */
  __IOM uint32_t RXROUTE;                            /**< RX port/pin select                                 */
  __IOM uint32_t CLKROUTE;                           /**< SCLK port/pin select                               */
  __IOM uint32_t TXROUTE;                            /**< TX port/pin select                                 */
  uint32_t       RESERVED0[1U];                      /**< Reserved for future use                            */
} GPIO_USARTROUTE_TypeDef;

typedef struct {
  __IM uint32_t               IPVERSION;              /**< main                                               */
  uint32_t                    RESERVED0[11U];         /**< Reserved for future use                            */
  GPIO_PORT_TypeDef           P[4U];                  /**<                                                    */
  uint32_t                    RESERVED1[132U];        /**< Reserved for future use                            */
  __IOM uint32_t              LOCK;                   /**< Lock Register                                      */
  uint32_t                    RESERVED2[3U];          /**< Reserved for future use                            */
  __IM uint32_t               GPIOLOCKSTATUS;         /**< Lock Status                                        */
  uint32_t                    RESERVED3[3U];          /**< Reserved for future use                            */
  __IOM uint32_t              ABUSALLOC;              /**< A Bus allocation                                   */
  __IOM uint32_t              BBUSALLOC;              /**< B Bus allocation                                   */
  __IOM uint32_t              CDBUSALLOC;             /**< CD Bus allocation                                  */
  uint32_t                    RESERVED4[1U];          /**< Reserved for future use                            */
  __IOM uint32_t              AODD0SWITCH;            /**< AODD0 Switch Register                              */
  __IOM uint32_t              AODD1SWITCH;            /**< AODD1 Switch Register                              */
  __IOM uint32_t              AEVEN0SWITCH;           /**< AEVEN0 Switch Register                             */
  __IOM uint32_t              AEVEN1SWITCH;           /**< AEVEN1 Switch Register                             */
  __IOM uint32_t              BODD0SWITCH;            /**< BODD0 Switch Register                              */
  __IOM uint32_t              BODD1SWITCH;            /**< BODD1 Switch Register                              */
  __IOM uint32_t              BEVEN0SWITCH;           /**< BEVEN0 Switch Register                             */
  __IOM uint32_t              BEVEN1SWITCH;           /**< BEVEN1 Switch Register                             */
  __IOM uint32_t              CDODD0SWITCH;           /**< CDODD0 Switch Register                             */
  __IOM uint32_t              CDODD1SWITCH;           /**< CDODD1 Switch Register                             */
  __IOM uint32_t              CDEVEN0SWITCH;          /**< CDEVEN0 Switch Register                            */
  __IOM uint32_t              CDEVEN1SWITCH;          /**< CDEVEN1 Switch Register                            */
  uint32_t                    RESERVED5[40U];         /**< Reserved for future use                            */
  __IOM uint32_t              EXTIPSELL;              /**< External Interrupt Port Select Low                 */
  __IOM uint32_t              EXTIPSELH;              /**< External interrupt Port Select High                */
  __IOM uint32_t              EXTIPINSELL;            /**< External Interrupt Pin Select Low                  */
  __IOM uint32_t              EXTIPINSELH;            /**< External Interrupt Pin Select High                 */
  __IOM uint32_t              EXTIRISE;               /**< External Interrupt Rising Edge Trigger             */
  __IOM uint32_t              EXTIFALL;               /**< External Interrupt Falling Edge Trigger            */
  uint32_t                    RESERVED6[2U];          /**< Reserved for future use                            */
  __IOM uint32_t              IF;                     /**< Interrupt Flag                                     */
  __IOM uint32_t              IEN;                    /**< Interrupt Enable                                   */
  uint32_t                    RESERVED7[1U];          /**< Reserved for future use                            */
  __IOM uint32_t              EM4WUEN;                /**< EM4 wakeup enable                                  */
  __IOM uint32_t              EM4WUPOL;               /**< EM4 wakeup polarity                                */
  uint32_t                    RESERVED8[3U];          /**< Reserved for future use                            */
  __IOM uint32_t              DBGROUTEPEN;            /**< Debugger Route Pin enable                          */
  __IOM uint32_t              TRACEROUTEPEN;          /**< Trace Route Pin Enable                             */
  uint32_t                    RESERVED9[2U];          /**< Reserved for future use                            */
  GPIO_ACMPROUTE_TypeDef      ACMPROUTE[2U];          /**< acmp0 DBUS config registers                        */
  GPIO_CMUROUTE_TypeDef       CMUROUTE;               /**< cmu DBUS config registers                          */
  GPIO_DCDCROUTE_TypeDef      DCDCROUTE;              /**< dcdc DBUS config registers                         */
  GPIO_EUSARTROUTE_TypeDef    EUSARTROUTE[2U];        /**< eusart0 DBUS config registers                      */
  GPIO_FRCROUTE_TypeDef       FRCROUTE;               /**< frc DBUS config registers                          */
  GPIO_I2CROUTE_TypeDef       I2CROUTE[2U];           /**< i2c0 DBUS config registers                         */
  GPIO_KEYSCANROUTE_TypeDef   KEYSCANROUTE;           /**< keypad DBUS config registers                       */
  GPIO_LETIMERROUTE_TypeDef   LETIMERROUTE;           /**< letimer DBUS config registers                      */
  GPIO_MODEMROUTE_TypeDef     MODEMROUTE;             /**< modem DBUS config registers                        */
  GPIO_PCNTROUTE_TypeDef      PCNTROUTE[1U];          /**< pcnt0 DBUS config registers                        */
  GPIO_PRSROUTE_TypeDef       PRSROUTE[1U];           /**< prs0 DBUS config registers                         */
  GPIO_DBUSRACROUTE_TypeDef   DBUSRACROUTE;           /**< rac DBUS config registers                          */
  GPIO_DBUSRFECAROUTE_TypeDef DBUSRFECAROUTE[1U];     /**< rfeca0 DBUS config registers                       */
  GPIO_DBUSSYXOROUTE_TypeDef  DBUSSYXOROUTE[1U];      /**< syxo0 DBUS config registers                        */
  GPIO_TIMERROUTE_TypeDef     TIMERROUTE[5U];         /**< timer0 DBUS config registers                       */
  GPIO_USARTROUTE_TypeDef     USARTROUTE[1U];         /**< usart0 DBUS config registers                       */
  __IOM uint32_t              RPURATD0;               /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD1;               /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED10[4U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD6;               /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED11[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD8;               /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD9;               /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD10;              /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD11;              /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD12;              /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD13;              /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD14;              /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED12[545U];       /**< Reserved for future use                            */
  __IM uint32_t               IPVERSION_SET;          /**< main                                               */
  uint32_t                    RESERVED13[11U];        /**< Reserved for future use                            */
  GPIO_PORT_TypeDef           P_SET[4U];              /**<                                                    */
  uint32_t                    RESERVED14[132U];       /**< Reserved for future use                            */
  __IOM uint32_t              LOCK_SET;               /**< Lock Register                                      */
  uint32_t                    RESERVED15[3U];         /**< Reserved for future use                            */
  __IM uint32_t               GPIOLOCKSTATUS_SET;     /**< Lock Status                                        */
  uint32_t                    RESERVED16[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              ABUSALLOC_SET;          /**< A Bus allocation                                   */
  __IOM uint32_t              BBUSALLOC_SET;          /**< B Bus allocation                                   */
  __IOM uint32_t              CDBUSALLOC_SET;         /**< CD Bus allocation                                  */
  uint32_t                    RESERVED17[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              AODD0SWITCH_SET;        /**< AODD0 Switch Register                              */
  __IOM uint32_t              AODD1SWITCH_SET;        /**< AODD1 Switch Register                              */
  __IOM uint32_t              AEVEN0SWITCH_SET;       /**< AEVEN0 Switch Register                             */
  __IOM uint32_t              AEVEN1SWITCH_SET;       /**< AEVEN1 Switch Register                             */
  __IOM uint32_t              BODD0SWITCH_SET;        /**< BODD0 Switch Register                              */
  __IOM uint32_t              BODD1SWITCH_SET;        /**< BODD1 Switch Register                              */
  __IOM uint32_t              BEVEN0SWITCH_SET;       /**< BEVEN0 Switch Register                             */
  __IOM uint32_t              BEVEN1SWITCH_SET;       /**< BEVEN1 Switch Register                             */
  __IOM uint32_t              CDODD0SWITCH_SET;       /**< CDODD0 Switch Register                             */
  __IOM uint32_t              CDODD1SWITCH_SET;       /**< CDODD1 Switch Register                             */
  __IOM uint32_t              CDEVEN0SWITCH_SET;      /**< CDEVEN0 Switch Register                            */
  __IOM uint32_t              CDEVEN1SWITCH_SET;      /**< CDEVEN1 Switch Register                            */
  uint32_t                    RESERVED18[40U];        /**< Reserved for future use                            */
  __IOM uint32_t              EXTIPSELL_SET;          /**< External Interrupt Port Select Low                 */
  __IOM uint32_t              EXTIPSELH_SET;          /**< External interrupt Port Select High                */
  __IOM uint32_t              EXTIPINSELL_SET;        /**< External Interrupt Pin Select Low                  */
  __IOM uint32_t              EXTIPINSELH_SET;        /**< External Interrupt Pin Select High                 */
  __IOM uint32_t              EXTIRISE_SET;           /**< External Interrupt Rising Edge Trigger             */
  __IOM uint32_t              EXTIFALL_SET;           /**< External Interrupt Falling Edge Trigger            */
  uint32_t                    RESERVED19[2U];         /**< Reserved for future use                            */
  __IOM uint32_t              IF_SET;                 /**< Interrupt Flag                                     */
  __IOM uint32_t              IEN_SET;                /**< Interrupt Enable                                   */
  uint32_t                    RESERVED20[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              EM4WUEN_SET;            /**< EM4 wakeup enable                                  */
  __IOM uint32_t              EM4WUPOL_SET;           /**< EM4 wakeup polarity                                */
  uint32_t                    RESERVED21[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              DBGROUTEPEN_SET;        /**< Debugger Route Pin enable                          */
  __IOM uint32_t              TRACEROUTEPEN_SET;      /**< Trace Route Pin Enable                             */
  uint32_t                    RESERVED22[2U];         /**< Reserved for future use                            */
  GPIO_ACMPROUTE_TypeDef      ACMPROUTE_SET[2U];      /**< acmp0 DBUS config registers                        */
  GPIO_CMUROUTE_TypeDef       CMUROUTE_SET;           /**< cmu DBUS config registers                          */
  GPIO_DCDCROUTE_TypeDef      DCDCROUTE_SET;          /**< dcdc DBUS config registers                         */
  GPIO_EUSARTROUTE_TypeDef    EUSARTROUTE_SET[2U];    /**< eusart0 DBUS config registers                      */
  GPIO_FRCROUTE_TypeDef       FRCROUTE_SET;           /**< frc DBUS config registers                          */
  GPIO_I2CROUTE_TypeDef       I2CROUTE_SET[2U];       /**< i2c0 DBUS config registers                         */
  GPIO_KEYSCANROUTE_TypeDef   KEYSCANROUTE_SET;       /**< keypad DBUS config registers                       */
  GPIO_LETIMERROUTE_TypeDef   LETIMERROUTE_SET;       /**< letimer DBUS config registers                      */
  GPIO_MODEMROUTE_TypeDef     MODEMROUTE_SET;         /**< modem DBUS config registers                        */
  GPIO_PCNTROUTE_TypeDef      PCNTROUTE_SET[1U];      /**< pcnt0 DBUS config registers                        */
  GPIO_PRSROUTE_TypeDef       PRSROUTE_SET[1U];       /**< prs0 DBUS config registers                         */
  GPIO_DBUSRACROUTE_TypeDef   DBUSRACROUTE_SET;       /**< rac DBUS config registers                          */
  GPIO_DBUSRFECAROUTE_TypeDef DBUSRFECAROUTE_SET[1U]; /**< rfeca0 DBUS config registers                       */
  GPIO_DBUSSYXOROUTE_TypeDef  DBUSSYXOROUTE_SET[1U];  /**< syxo0 DBUS config registers                        */
  GPIO_TIMERROUTE_TypeDef     TIMERROUTE_SET[5U];     /**< timer0 DBUS config registers                       */
  GPIO_USARTROUTE_TypeDef     USARTROUTE_SET[1U];     /**< usart0 DBUS config registers                       */
  __IOM uint32_t              RPURATD0_SET;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD1_SET;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED23[4U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD6_SET;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED24[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD8_SET;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD9_SET;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD10_SET;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD11_SET;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD12_SET;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD13_SET;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD14_SET;          /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED25[545U];       /**< Reserved for future use                            */
  __IM uint32_t               IPVERSION_CLR;          /**< main                                               */
  uint32_t                    RESERVED26[11U];        /**< Reserved for future use                            */
  GPIO_PORT_TypeDef           P_CLR[4U];              /**<                                                    */
  uint32_t                    RESERVED27[132U];       /**< Reserved for future use                            */
  __IOM uint32_t              LOCK_CLR;               /**< Lock Register                                      */
  uint32_t                    RESERVED28[3U];         /**< Reserved for future use                            */
  __IM uint32_t               GPIOLOCKSTATUS_CLR;     /**< Lock Status                                        */
  uint32_t                    RESERVED29[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              ABUSALLOC_CLR;          /**< A Bus allocation                                   */
  __IOM uint32_t              BBUSALLOC_CLR;          /**< B Bus allocation                                   */
  __IOM uint32_t              CDBUSALLOC_CLR;         /**< CD Bus allocation                                  */
  uint32_t                    RESERVED30[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              AODD0SWITCH_CLR;        /**< AODD0 Switch Register                              */
  __IOM uint32_t              AODD1SWITCH_CLR;        /**< AODD1 Switch Register                              */
  __IOM uint32_t              AEVEN0SWITCH_CLR;       /**< AEVEN0 Switch Register                             */
  __IOM uint32_t              AEVEN1SWITCH_CLR;       /**< AEVEN1 Switch Register                             */
  __IOM uint32_t              BODD0SWITCH_CLR;        /**< BODD0 Switch Register                              */
  __IOM uint32_t              BODD1SWITCH_CLR;        /**< BODD1 Switch Register                              */
  __IOM uint32_t              BEVEN0SWITCH_CLR;       /**< BEVEN0 Switch Register                             */
  __IOM uint32_t              BEVEN1SWITCH_CLR;       /**< BEVEN1 Switch Register                             */
  __IOM uint32_t              CDODD0SWITCH_CLR;       /**< CDODD0 Switch Register                             */
  __IOM uint32_t              CDODD1SWITCH_CLR;       /**< CDODD1 Switch Register                             */
  __IOM uint32_t              CDEVEN0SWITCH_CLR;      /**< CDEVEN0 Switch Register                            */
  __IOM uint32_t              CDEVEN1SWITCH_CLR;      /**< CDEVEN1 Switch Register                            */
  uint32_t                    RESERVED31[40U];        /**< Reserved for future use                            */
  __IOM uint32_t              EXTIPSELL_CLR;          /**< External Interrupt Port Select Low                 */
  __IOM uint32_t              EXTIPSELH_CLR;          /**< External interrupt Port Select High                */
  __IOM uint32_t              EXTIPINSELL_CLR;        /**< External Interrupt Pin Select Low                  */
  __IOM uint32_t              EXTIPINSELH_CLR;        /**< External Interrupt Pin Select High                 */
  __IOM uint32_t              EXTIRISE_CLR;           /**< External Interrupt Rising Edge Trigger             */
  __IOM uint32_t              EXTIFALL_CLR;           /**< External Interrupt Falling Edge Trigger            */
  uint32_t                    RESERVED32[2U];         /**< Reserved for future use                            */
  __IOM uint32_t              IF_CLR;                 /**< Interrupt Flag                                     */
  __IOM uint32_t              IEN_CLR;                /**< Interrupt Enable                                   */
  uint32_t                    RESERVED33[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              EM4WUEN_CLR;            /**< EM4 wakeup enable                                  */
  __IOM uint32_t              EM4WUPOL_CLR;           /**< EM4 wakeup polarity                                */
  uint32_t                    RESERVED34[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              DBGROUTEPEN_CLR;        /**< Debugger Route Pin enable                          */
  __IOM uint32_t              TRACEROUTEPEN_CLR;      /**< Trace Route Pin Enable                             */
  uint32_t                    RESERVED35[2U];         /**< Reserved for future use                            */
  GPIO_ACMPROUTE_TypeDef      ACMPROUTE_CLR[2U];      /**< acmp0 DBUS config registers                        */
  GPIO_CMUROUTE_TypeDef       CMUROUTE_CLR;           /**< cmu DBUS config registers                          */
  GPIO_DCDCROUTE_TypeDef      DCDCROUTE_CLR;          /**< dcdc DBUS config registers                         */
  GPIO_EUSARTROUTE_TypeDef    EUSARTROUTE_CLR[2U];    /**< eusart0 DBUS config registers                      */
  GPIO_FRCROUTE_TypeDef       FRCROUTE_CLR;           /**< frc DBUS config registers                          */
  GPIO_I2CROUTE_TypeDef       I2CROUTE_CLR[2U];       /**< i2c0 DBUS config registers                         */
  GPIO_KEYSCANROUTE_TypeDef   KEYSCANROUTE_CLR;       /**< keypad DBUS config registers                       */
  GPIO_LETIMERROUTE_TypeDef   LETIMERROUTE_CLR;       /**< letimer DBUS config registers                      */
  GPIO_MODEMROUTE_TypeDef     MODEMROUTE_CLR;         /**< modem DBUS config registers                        */
  GPIO_PCNTROUTE_TypeDef      PCNTROUTE_CLR[1U];      /**< pcnt0 DBUS config registers                        */
  GPIO_PRSROUTE_TypeDef       PRSROUTE_CLR[1U];       /**< prs0 DBUS config registers                         */
  GPIO_DBUSRACROUTE_TypeDef   DBUSRACROUTE_CLR;       /**< rac DBUS config registers                          */
  GPIO_DBUSRFECAROUTE_TypeDef DBUSRFECAROUTE_CLR[1U]; /**< rfeca0 DBUS config registers                       */
  GPIO_DBUSSYXOROUTE_TypeDef  DBUSSYXOROUTE_CLR[1U];  /**< syxo0 DBUS config registers                        */
  GPIO_TIMERROUTE_TypeDef     TIMERROUTE_CLR[5U];     /**< timer0 DBUS config registers                       */
  GPIO_USARTROUTE_TypeDef     USARTROUTE_CLR[1U];     /**< usart0 DBUS config registers                       */
  __IOM uint32_t              RPURATD0_CLR;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD1_CLR;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED36[4U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD6_CLR;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED37[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD8_CLR;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD9_CLR;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD10_CLR;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD11_CLR;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD12_CLR;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD13_CLR;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD14_CLR;          /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED38[545U];       /**< Reserved for future use                            */
  __IM uint32_t               IPVERSION_TGL;          /**< main                                               */
  uint32_t                    RESERVED39[11U];        /**< Reserved for future use                            */
  GPIO_PORT_TypeDef           P_TGL[4U];              /**<                                                    */
  uint32_t                    RESERVED40[132U];       /**< Reserved for future use                            */
  __IOM uint32_t              LOCK_TGL;               /**< Lock Register                                      */
  uint32_t                    RESERVED41[3U];         /**< Reserved for future use                            */
  __IM uint32_t               GPIOLOCKSTATUS_TGL;     /**< Lock Status                                        */
  uint32_t                    RESERVED42[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              ABUSALLOC_TGL;          /**< A Bus allocation                                   */
  __IOM uint32_t              BBUSALLOC_TGL;          /**< B Bus allocation                                   */
  __IOM uint32_t              CDBUSALLOC_TGL;         /**< CD Bus allocation                                  */
  uint32_t                    RESERVED43[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              AODD0SWITCH_TGL;        /**< AODD0 Switch Register                              */
  __IOM uint32_t              AODD1SWITCH_TGL;        /**< AODD1 Switch Register                              */
  __IOM uint32_t              AEVEN0SWITCH_TGL;       /**< AEVEN0 Switch Register                             */
  __IOM uint32_t              AEVEN1SWITCH_TGL;       /**< AEVEN1 Switch Register                             */
  __IOM uint32_t              BODD0SWITCH_TGL;        /**< BODD0 Switch Register                              */
  __IOM uint32_t              BODD1SWITCH_TGL;        /**< BODD1 Switch Register                              */
  __IOM uint32_t              BEVEN0SWITCH_TGL;       /**< BEVEN0 Switch Register                             */
  __IOM uint32_t              BEVEN1SWITCH_TGL;       /**< BEVEN1 Switch Register                             */
  __IOM uint32_t              CDODD0SWITCH_TGL;       /**< CDODD0 Switch Register                             */
  __IOM uint32_t              CDODD1SWITCH_TGL;       /**< CDODD1 Switch Register                             */
  __IOM uint32_t              CDEVEN0SWITCH_TGL;      /**< CDEVEN0 Switch Register                            */
  __IOM uint32_t              CDEVEN1SWITCH_TGL;      /**< CDEVEN1 Switch Register                            */
  uint32_t                    RESERVED44[40U];        /**< Reserved for future use                            */
  __IOM uint32_t              EXTIPSELL_TGL;          /**< External Interrupt Port Select Low                 */
  __IOM uint32_t              EXTIPSELH_TGL;          /**< External interrupt Port Select High                */
  __IOM uint32_t              EXTIPINSELL_TGL;        /**< External Interrupt Pin Select Low                  */
  __IOM uint32_t              EXTIPINSELH_TGL;        /**< External Interrupt Pin Select High                 */
  __IOM uint32_t              EXTIRISE_TGL;           /**< External Interrupt Rising Edge Trigger             */
  __IOM uint32_t              EXTIFALL_TGL;           /**< External Interrupt Falling Edge Trigger            */
  uint32_t                    RESERVED45[2U];         /**< Reserved for future use                            */
  __IOM uint32_t              IF_TGL;                 /**< Interrupt Flag                                     */
  __IOM uint32_t              IEN_TGL;                /**< Interrupt Enable                                   */
  uint32_t                    RESERVED46[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              EM4WUEN_TGL;            /**< EM4 wakeup enable                                  */
  __IOM uint32_t              EM4WUPOL_TGL;           /**< EM4 wakeup polarity                                */
  uint32_t                    RESERVED47[3U];         /**< Reserved for future use                            */
  __IOM uint32_t              DBGROUTEPEN_TGL;        /**< Debugger Route Pin enable                          */
  __IOM uint32_t              TRACEROUTEPEN_TGL;      /**< Trace Route Pin Enable                             */
  uint32_t                    RESERVED48[2U];         /**< Reserved for future use                            */
  GPIO_ACMPROUTE_TypeDef      ACMPROUTE_TGL[2U];      /**< acmp0 DBUS config registers                        */
  GPIO_CMUROUTE_TypeDef       CMUROUTE_TGL;           /**< cmu DBUS config registers                          */
  GPIO_DCDCROUTE_TypeDef      DCDCROUTE_TGL;          /**< dcdc DBUS config registers                         */
  GPIO_EUSARTROUTE_TypeDef    EUSARTROUTE_TGL[2U];    /**< eusart0 DBUS config registers                      */
  GPIO_FRCROUTE_TypeDef       FRCROUTE_TGL;           /**< frc DBUS config registers                          */
  GPIO_I2CROUTE_TypeDef       I2CROUTE_TGL[2U];       /**< i2c0 DBUS config registers                         */
  GPIO_KEYSCANROUTE_TypeDef   KEYSCANROUTE_TGL;       /**< keypad DBUS config registers                       */
  GPIO_LETIMERROUTE_TypeDef   LETIMERROUTE_TGL;       /**< letimer DBUS config registers                      */
  GPIO_MODEMROUTE_TypeDef     MODEMROUTE_TGL;         /**< modem DBUS config registers                        */
  GPIO_PCNTROUTE_TypeDef      PCNTROUTE_TGL[1U];      /**< pcnt0 DBUS config registers                        */
  GPIO_PRSROUTE_TypeDef       PRSROUTE_TGL[1U];       /**< prs0 DBUS config registers                         */
  GPIO_DBUSRACROUTE_TypeDef   DBUSRACROUTE_TGL;       /**< rac DBUS config registers                          */
  GPIO_DBUSRFECAROUTE_TypeDef DBUSRFECAROUTE_TGL[1U]; /**< rfeca0 DBUS config registers                       */
  GPIO_DBUSSYXOROUTE_TypeDef  DBUSSYXOROUTE_TGL[1U];  /**< syxo0 DBUS config registers                        */
  GPIO_TIMERROUTE_TypeDef     TIMERROUTE_TGL[5U];     /**< timer0 DBUS config registers                       */
  GPIO_USARTROUTE_TypeDef     USARTROUTE_TGL[1U];     /**< usart0 DBUS config registers                       */
  __IOM uint32_t              RPURATD0_TGL;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD1_TGL;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED49[4U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD6_TGL;           /**< Root Access Type Descriptor Register               */
  uint32_t                    RESERVED50[1U];         /**< Reserved for future use                            */
  __IOM uint32_t              RPURATD8_TGL;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD9_TGL;           /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD10_TGL;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD11_TGL;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD12_TGL;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD13_TGL;          /**< Root Access Type Descriptor Register               */
  __IOM uint32_t              RPURATD14_TGL;          /**< Root Access Type Descriptor Register               */
} GPIO_TypeDef;

/* Bit fields for GPIO IPVERSION */
#define _GPIO_IPVERSION_RESETVALUE                                    0x00000003UL                             /**< Default value for GPIO_IPVERSION            */
#define _GPIO_IPVERSION_MASK                                          0xFFFFFFFFUL                             /**< Mask for GPIO_IPVERSION                     */
#define _GPIO_IPVERSION_IPVERSION_SHIFT                               0                                        /**< Shift value for GPIO_IPVERSION              */
#define _GPIO_IPVERSION_IPVERSION_MASK                                0xFFFFFFFFUL                             /**< Bit mask for GPIO_IPVERSION                 */
#define _GPIO_IPVERSION_IPVERSION_DEFAULT                             0x00000003UL                             /**< Mode DEFAULT for GPIO_IPVERSION             */
#define GPIO_IPVERSION_IPVERSION_DEFAULT                              (_GPIO_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_IPVERSION     */
#define GPIO_PORTA                                                    0x00000000UL                             /**< PORTA index                                  */
#define GPIO_PORTB                                                    0x00000001UL                             /**< PORTB index                                  */
#define GPIO_PORTC                                                    0x00000002UL                             /**< PORTC index                                  */
#define GPIO_PORTD                                                    0x00000003UL                             /**< PORTD index                                  */

/* Bit fields for GPIO LOCK */
#define _GPIO_LOCK_RESETVALUE                                         0x0000A534UL                      /**< Default value for GPIO_LOCK                 */
#define _GPIO_LOCK_MASK                                               0x0000FFFFUL                      /**< Mask for GPIO_LOCK                          */
#define _GPIO_LOCK_LOCKKEY_SHIFT                                      0                                 /**< Shift value for GPIO_LOCKKEY                */
#define _GPIO_LOCK_LOCKKEY_MASK                                       0xFFFFUL                          /**< Bit mask for GPIO_LOCKKEY                   */
#define _GPIO_LOCK_LOCKKEY_DEFAULT                                    0x0000A534UL                      /**< Mode DEFAULT for GPIO_LOCK                  */
#define _GPIO_LOCK_LOCKKEY_UNLOCK                                     0x0000A534UL                      /**< Mode UNLOCK for GPIO_LOCK                   */
#define GPIO_LOCK_LOCKKEY_DEFAULT                                     (_GPIO_LOCK_LOCKKEY_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_LOCK          */
#define GPIO_LOCK_LOCKKEY_UNLOCK                                      (_GPIO_LOCK_LOCKKEY_UNLOCK << 0)  /**< Shifted mode UNLOCK for GPIO_LOCK           */

/* Bit fields for GPIO GPIOLOCKSTATUS */
#define _GPIO_GPIOLOCKSTATUS_RESETVALUE                               0x00000000UL                              /**< Default value for GPIO_GPIOLOCKSTATUS       */
#define _GPIO_GPIOLOCKSTATUS_MASK                                     0x00000001UL                              /**< Mask for GPIO_GPIOLOCKSTATUS                */
#define GPIO_GPIOLOCKSTATUS_LOCK                                      (0x1UL << 0)                              /**< GPIO LOCK status                            */
#define _GPIO_GPIOLOCKSTATUS_LOCK_SHIFT                               0                                         /**< Shift value for GPIO_LOCK                   */
#define _GPIO_GPIOLOCKSTATUS_LOCK_MASK                                0x1UL                                     /**< Bit mask for GPIO_LOCK                      */
#define _GPIO_GPIOLOCKSTATUS_LOCK_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_GPIOLOCKSTATUS        */
#define _GPIO_GPIOLOCKSTATUS_LOCK_UNLOCKED                            0x00000000UL                              /**< Mode UNLOCKED for GPIO_GPIOLOCKSTATUS       */
#define _GPIO_GPIOLOCKSTATUS_LOCK_LOCKED                              0x00000001UL                              /**< Mode LOCKED for GPIO_GPIOLOCKSTATUS         */
#define GPIO_GPIOLOCKSTATUS_LOCK_DEFAULT                              (_GPIO_GPIOLOCKSTATUS_LOCK_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_GPIOLOCKSTATUS*/
#define GPIO_GPIOLOCKSTATUS_LOCK_UNLOCKED                             (_GPIO_GPIOLOCKSTATUS_LOCK_UNLOCKED << 0) /**< Shifted mode UNLOCKED for GPIO_GPIOLOCKSTATUS*/
#define GPIO_GPIOLOCKSTATUS_LOCK_LOCKED                               (_GPIO_GPIOLOCKSTATUS_LOCK_LOCKED << 0)   /**< Shifted mode LOCKED for GPIO_GPIOLOCKSTATUS */

/* Bit fields for GPIO ABUSALLOC */
#define _GPIO_ABUSALLOC_RESETVALUE                                    0x00000000UL                           /**< Default value for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_MASK                                          0x0F0F0F0FUL                           /**< Mask for GPIO_ABUSALLOC                     */
#define _GPIO_ABUSALLOC_AEVEN0_SHIFT                                  0                                      /**< Shift value for GPIO_AEVEN0                 */
#define _GPIO_ABUSALLOC_AEVEN0_MASK                                   0xFUL                                  /**< Bit mask for GPIO_AEVEN0                    */
#define _GPIO_ABUSALLOC_AEVEN0_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_ABUSALLOC             */
#define _GPIO_ABUSALLOC_AEVEN0_TRISTATE                               0x00000000UL                           /**< Mode TRISTATE for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN0_ADC0                                   0x00000001UL                           /**< Mode ADC0 for GPIO_ABUSALLOC                */
#define _GPIO_ABUSALLOC_AEVEN0_ACMP0                                  0x00000002UL                           /**< Mode ACMP0 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AEVEN0_ACMP1                                  0x00000003UL                           /**< Mode ACMP1 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AEVEN0_VDAC0CH0                               0x00000004UL                           /**< Mode VDAC0CH0 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN0_VDAC1CH0                               0x00000005UL                           /**< Mode VDAC1CH0 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN0_DIAGA                                  0x0000000EUL                           /**< Mode DIAGA for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AEVEN0_DEBUG                                  0x0000000FUL                           /**< Mode DEBUG for GPIO_ABUSALLOC               */
#define GPIO_ABUSALLOC_AEVEN0_DEFAULT                                 (_GPIO_ABUSALLOC_AEVEN0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_ABUSALLOC     */
#define GPIO_ABUSALLOC_AEVEN0_TRISTATE                                (_GPIO_ABUSALLOC_AEVEN0_TRISTATE << 0) /**< Shifted mode TRISTATE for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN0_ADC0                                    (_GPIO_ABUSALLOC_AEVEN0_ADC0 << 0)     /**< Shifted mode ADC0 for GPIO_ABUSALLOC        */
#define GPIO_ABUSALLOC_AEVEN0_ACMP0                                   (_GPIO_ABUSALLOC_AEVEN0_ACMP0 << 0)    /**< Shifted mode ACMP0 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AEVEN0_ACMP1                                   (_GPIO_ABUSALLOC_AEVEN0_ACMP1 << 0)    /**< Shifted mode ACMP1 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AEVEN0_VDAC0CH0                                (_GPIO_ABUSALLOC_AEVEN0_VDAC0CH0 << 0) /**< Shifted mode VDAC0CH0 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN0_VDAC1CH0                                (_GPIO_ABUSALLOC_AEVEN0_VDAC1CH0 << 0) /**< Shifted mode VDAC1CH0 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN0_DIAGA                                   (_GPIO_ABUSALLOC_AEVEN0_DIAGA << 0)    /**< Shifted mode DIAGA for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AEVEN0_DEBUG                                   (_GPIO_ABUSALLOC_AEVEN0_DEBUG << 0)    /**< Shifted mode DEBUG for GPIO_ABUSALLOC       */
#define _GPIO_ABUSALLOC_AEVEN1_SHIFT                                  8                                      /**< Shift value for GPIO_AEVEN1                 */
#define _GPIO_ABUSALLOC_AEVEN1_MASK                                   0xF00UL                                /**< Bit mask for GPIO_AEVEN1                    */
#define _GPIO_ABUSALLOC_AEVEN1_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_ABUSALLOC             */
#define _GPIO_ABUSALLOC_AEVEN1_TRISTATE                               0x00000000UL                           /**< Mode TRISTATE for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN1_ADC0                                   0x00000001UL                           /**< Mode ADC0 for GPIO_ABUSALLOC                */
#define _GPIO_ABUSALLOC_AEVEN1_ACMP0                                  0x00000002UL                           /**< Mode ACMP0 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AEVEN1_ACMP1                                  0x00000003UL                           /**< Mode ACMP1 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AEVEN1_VDAC0CH1                               0x00000004UL                           /**< Mode VDAC0CH1 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN1_VDAC1CH1                               0x00000005UL                           /**< Mode VDAC1CH1 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AEVEN1_DEBUG                                  0x0000000FUL                           /**< Mode DEBUG for GPIO_ABUSALLOC               */
#define GPIO_ABUSALLOC_AEVEN1_DEFAULT                                 (_GPIO_ABUSALLOC_AEVEN1_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_ABUSALLOC     */
#define GPIO_ABUSALLOC_AEVEN1_TRISTATE                                (_GPIO_ABUSALLOC_AEVEN1_TRISTATE << 8) /**< Shifted mode TRISTATE for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN1_ADC0                                    (_GPIO_ABUSALLOC_AEVEN1_ADC0 << 8)     /**< Shifted mode ADC0 for GPIO_ABUSALLOC        */
#define GPIO_ABUSALLOC_AEVEN1_ACMP0                                   (_GPIO_ABUSALLOC_AEVEN1_ACMP0 << 8)    /**< Shifted mode ACMP0 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AEVEN1_ACMP1                                   (_GPIO_ABUSALLOC_AEVEN1_ACMP1 << 8)    /**< Shifted mode ACMP1 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AEVEN1_VDAC0CH1                                (_GPIO_ABUSALLOC_AEVEN1_VDAC0CH1 << 8) /**< Shifted mode VDAC0CH1 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN1_VDAC1CH1                                (_GPIO_ABUSALLOC_AEVEN1_VDAC1CH1 << 8) /**< Shifted mode VDAC1CH1 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AEVEN1_DEBUG                                   (_GPIO_ABUSALLOC_AEVEN1_DEBUG << 8)    /**< Shifted mode DEBUG for GPIO_ABUSALLOC       */
#define _GPIO_ABUSALLOC_AODD0_SHIFT                                   16                                     /**< Shift value for GPIO_AODD0                  */
#define _GPIO_ABUSALLOC_AODD0_MASK                                    0xF0000UL                              /**< Bit mask for GPIO_AODD0                     */
#define _GPIO_ABUSALLOC_AODD0_DEFAULT                                 0x00000000UL                           /**< Mode DEFAULT for GPIO_ABUSALLOC             */
#define _GPIO_ABUSALLOC_AODD0_TRISTATE                                0x00000000UL                           /**< Mode TRISTATE for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD0_ADC0                                    0x00000001UL                           /**< Mode ADC0 for GPIO_ABUSALLOC                */
#define _GPIO_ABUSALLOC_AODD0_ACMP0                                   0x00000002UL                           /**< Mode ACMP0 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AODD0_ACMP1                                   0x00000003UL                           /**< Mode ACMP1 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AODD0_VDAC0CH0                                0x00000004UL                           /**< Mode VDAC0CH0 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD0_VDAC1CH0                                0x00000005UL                           /**< Mode VDAC1CH0 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD0_DIAGA                                   0x0000000EUL                           /**< Mode DIAGA for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AODD0_DEBUG                                   0x0000000FUL                           /**< Mode DEBUG for GPIO_ABUSALLOC               */
#define GPIO_ABUSALLOC_AODD0_DEFAULT                                  (_GPIO_ABUSALLOC_AODD0_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_ABUSALLOC     */
#define GPIO_ABUSALLOC_AODD0_TRISTATE                                 (_GPIO_ABUSALLOC_AODD0_TRISTATE << 16) /**< Shifted mode TRISTATE for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD0_ADC0                                     (_GPIO_ABUSALLOC_AODD0_ADC0 << 16)     /**< Shifted mode ADC0 for GPIO_ABUSALLOC        */
#define GPIO_ABUSALLOC_AODD0_ACMP0                                    (_GPIO_ABUSALLOC_AODD0_ACMP0 << 16)    /**< Shifted mode ACMP0 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AODD0_ACMP1                                    (_GPIO_ABUSALLOC_AODD0_ACMP1 << 16)    /**< Shifted mode ACMP1 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AODD0_VDAC0CH0                                 (_GPIO_ABUSALLOC_AODD0_VDAC0CH0 << 16) /**< Shifted mode VDAC0CH0 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD0_VDAC1CH0                                 (_GPIO_ABUSALLOC_AODD0_VDAC1CH0 << 16) /**< Shifted mode VDAC1CH0 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD0_DIAGA                                    (_GPIO_ABUSALLOC_AODD0_DIAGA << 16)    /**< Shifted mode DIAGA for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AODD0_DEBUG                                    (_GPIO_ABUSALLOC_AODD0_DEBUG << 16)    /**< Shifted mode DEBUG for GPIO_ABUSALLOC       */
#define _GPIO_ABUSALLOC_AODD1_SHIFT                                   24                                     /**< Shift value for GPIO_AODD1                  */
#define _GPIO_ABUSALLOC_AODD1_MASK                                    0xF000000UL                            /**< Bit mask for GPIO_AODD1                     */
#define _GPIO_ABUSALLOC_AODD1_DEFAULT                                 0x00000000UL                           /**< Mode DEFAULT for GPIO_ABUSALLOC             */
#define _GPIO_ABUSALLOC_AODD1_TRISTATE                                0x00000000UL                           /**< Mode TRISTATE for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD1_ADC0                                    0x00000001UL                           /**< Mode ADC0 for GPIO_ABUSALLOC                */
#define _GPIO_ABUSALLOC_AODD1_ACMP0                                   0x00000002UL                           /**< Mode ACMP0 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AODD1_ACMP1                                   0x00000003UL                           /**< Mode ACMP1 for GPIO_ABUSALLOC               */
#define _GPIO_ABUSALLOC_AODD1_VDAC0CH1                                0x00000004UL                           /**< Mode VDAC0CH1 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD1_VDAC1CH1                                0x00000005UL                           /**< Mode VDAC1CH1 for GPIO_ABUSALLOC            */
#define _GPIO_ABUSALLOC_AODD1_DEBUG                                   0x0000000FUL                           /**< Mode DEBUG for GPIO_ABUSALLOC               */
#define GPIO_ABUSALLOC_AODD1_DEFAULT                                  (_GPIO_ABUSALLOC_AODD1_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_ABUSALLOC     */
#define GPIO_ABUSALLOC_AODD1_TRISTATE                                 (_GPIO_ABUSALLOC_AODD1_TRISTATE << 24) /**< Shifted mode TRISTATE for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD1_ADC0                                     (_GPIO_ABUSALLOC_AODD1_ADC0 << 24)     /**< Shifted mode ADC0 for GPIO_ABUSALLOC        */
#define GPIO_ABUSALLOC_AODD1_ACMP0                                    (_GPIO_ABUSALLOC_AODD1_ACMP0 << 24)    /**< Shifted mode ACMP0 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AODD1_ACMP1                                    (_GPIO_ABUSALLOC_AODD1_ACMP1 << 24)    /**< Shifted mode ACMP1 for GPIO_ABUSALLOC       */
#define GPIO_ABUSALLOC_AODD1_VDAC0CH1                                 (_GPIO_ABUSALLOC_AODD1_VDAC0CH1 << 24) /**< Shifted mode VDAC0CH1 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD1_VDAC1CH1                                 (_GPIO_ABUSALLOC_AODD1_VDAC1CH1 << 24) /**< Shifted mode VDAC1CH1 for GPIO_ABUSALLOC    */
#define GPIO_ABUSALLOC_AODD1_DEBUG                                    (_GPIO_ABUSALLOC_AODD1_DEBUG << 24)    /**< Shifted mode DEBUG for GPIO_ABUSALLOC       */

/* Bit fields for GPIO BBUSALLOC */
#define _GPIO_BBUSALLOC_RESETVALUE                                    0x00000000UL                           /**< Default value for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_MASK                                          0x0F0F0F0FUL                           /**< Mask for GPIO_BBUSALLOC                     */
#define _GPIO_BBUSALLOC_BEVEN0_SHIFT                                  0                                      /**< Shift value for GPIO_BEVEN0                 */
#define _GPIO_BBUSALLOC_BEVEN0_MASK                                   0xFUL                                  /**< Bit mask for GPIO_BEVEN0                    */
#define _GPIO_BBUSALLOC_BEVEN0_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_BBUSALLOC             */
#define _GPIO_BBUSALLOC_BEVEN0_TRISTATE                               0x00000000UL                           /**< Mode TRISTATE for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN0_ADC0                                   0x00000001UL                           /**< Mode ADC0 for GPIO_BBUSALLOC                */
#define _GPIO_BBUSALLOC_BEVEN0_ACMP0                                  0x00000002UL                           /**< Mode ACMP0 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BEVEN0_ACMP1                                  0x00000003UL                           /**< Mode ACMP1 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BEVEN0_VDAC0CH0                               0x00000004UL                           /**< Mode VDAC0CH0 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN0_VDAC1CH0                               0x00000005UL                           /**< Mode VDAC1CH0 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN0_DEBUG                                  0x0000000FUL                           /**< Mode DEBUG for GPIO_BBUSALLOC               */
#define GPIO_BBUSALLOC_BEVEN0_DEFAULT                                 (_GPIO_BBUSALLOC_BEVEN0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_BBUSALLOC     */
#define GPIO_BBUSALLOC_BEVEN0_TRISTATE                                (_GPIO_BBUSALLOC_BEVEN0_TRISTATE << 0) /**< Shifted mode TRISTATE for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN0_ADC0                                    (_GPIO_BBUSALLOC_BEVEN0_ADC0 << 0)     /**< Shifted mode ADC0 for GPIO_BBUSALLOC        */
#define GPIO_BBUSALLOC_BEVEN0_ACMP0                                   (_GPIO_BBUSALLOC_BEVEN0_ACMP0 << 0)    /**< Shifted mode ACMP0 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BEVEN0_ACMP1                                   (_GPIO_BBUSALLOC_BEVEN0_ACMP1 << 0)    /**< Shifted mode ACMP1 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BEVEN0_VDAC0CH0                                (_GPIO_BBUSALLOC_BEVEN0_VDAC0CH0 << 0) /**< Shifted mode VDAC0CH0 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN0_VDAC1CH0                                (_GPIO_BBUSALLOC_BEVEN0_VDAC1CH0 << 0) /**< Shifted mode VDAC1CH0 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN0_DEBUG                                   (_GPIO_BBUSALLOC_BEVEN0_DEBUG << 0)    /**< Shifted mode DEBUG for GPIO_BBUSALLOC       */
#define _GPIO_BBUSALLOC_BEVEN1_SHIFT                                  8                                      /**< Shift value for GPIO_BEVEN1                 */
#define _GPIO_BBUSALLOC_BEVEN1_MASK                                   0xF00UL                                /**< Bit mask for GPIO_BEVEN1                    */
#define _GPIO_BBUSALLOC_BEVEN1_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_BBUSALLOC             */
#define _GPIO_BBUSALLOC_BEVEN1_TRISTATE                               0x00000000UL                           /**< Mode TRISTATE for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN1_ADC0                                   0x00000001UL                           /**< Mode ADC0 for GPIO_BBUSALLOC                */
#define _GPIO_BBUSALLOC_BEVEN1_ACMP0                                  0x00000002UL                           /**< Mode ACMP0 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BEVEN1_ACMP1                                  0x00000003UL                           /**< Mode ACMP1 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BEVEN1_VDAC0CH1                               0x00000004UL                           /**< Mode VDAC0CH1 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN1_VDAC1CH1                               0x00000005UL                           /**< Mode VDAC1CH1 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BEVEN1_DEBUG                                  0x0000000FUL                           /**< Mode DEBUG for GPIO_BBUSALLOC               */
#define GPIO_BBUSALLOC_BEVEN1_DEFAULT                                 (_GPIO_BBUSALLOC_BEVEN1_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_BBUSALLOC     */
#define GPIO_BBUSALLOC_BEVEN1_TRISTATE                                (_GPIO_BBUSALLOC_BEVEN1_TRISTATE << 8) /**< Shifted mode TRISTATE for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN1_ADC0                                    (_GPIO_BBUSALLOC_BEVEN1_ADC0 << 8)     /**< Shifted mode ADC0 for GPIO_BBUSALLOC        */
#define GPIO_BBUSALLOC_BEVEN1_ACMP0                                   (_GPIO_BBUSALLOC_BEVEN1_ACMP0 << 8)    /**< Shifted mode ACMP0 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BEVEN1_ACMP1                                   (_GPIO_BBUSALLOC_BEVEN1_ACMP1 << 8)    /**< Shifted mode ACMP1 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BEVEN1_VDAC0CH1                                (_GPIO_BBUSALLOC_BEVEN1_VDAC0CH1 << 8) /**< Shifted mode VDAC0CH1 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN1_VDAC1CH1                                (_GPIO_BBUSALLOC_BEVEN1_VDAC1CH1 << 8) /**< Shifted mode VDAC1CH1 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BEVEN1_DEBUG                                   (_GPIO_BBUSALLOC_BEVEN1_DEBUG << 8)    /**< Shifted mode DEBUG for GPIO_BBUSALLOC       */
#define _GPIO_BBUSALLOC_BODD0_SHIFT                                   16                                     /**< Shift value for GPIO_BODD0                  */
#define _GPIO_BBUSALLOC_BODD0_MASK                                    0xF0000UL                              /**< Bit mask for GPIO_BODD0                     */
#define _GPIO_BBUSALLOC_BODD0_DEFAULT                                 0x00000000UL                           /**< Mode DEFAULT for GPIO_BBUSALLOC             */
#define _GPIO_BBUSALLOC_BODD0_TRISTATE                                0x00000000UL                           /**< Mode TRISTATE for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD0_ADC0                                    0x00000001UL                           /**< Mode ADC0 for GPIO_BBUSALLOC                */
#define _GPIO_BBUSALLOC_BODD0_ACMP0                                   0x00000002UL                           /**< Mode ACMP0 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BODD0_ACMP1                                   0x00000003UL                           /**< Mode ACMP1 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BODD0_VDAC0CH0                                0x00000004UL                           /**< Mode VDAC0CH0 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD0_VDAC1CH0                                0x00000005UL                           /**< Mode VDAC1CH0 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD0_DEBUG                                   0x0000000FUL                           /**< Mode DEBUG for GPIO_BBUSALLOC               */
#define GPIO_BBUSALLOC_BODD0_DEFAULT                                  (_GPIO_BBUSALLOC_BODD0_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_BBUSALLOC     */
#define GPIO_BBUSALLOC_BODD0_TRISTATE                                 (_GPIO_BBUSALLOC_BODD0_TRISTATE << 16) /**< Shifted mode TRISTATE for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD0_ADC0                                     (_GPIO_BBUSALLOC_BODD0_ADC0 << 16)     /**< Shifted mode ADC0 for GPIO_BBUSALLOC        */
#define GPIO_BBUSALLOC_BODD0_ACMP0                                    (_GPIO_BBUSALLOC_BODD0_ACMP0 << 16)    /**< Shifted mode ACMP0 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BODD0_ACMP1                                    (_GPIO_BBUSALLOC_BODD0_ACMP1 << 16)    /**< Shifted mode ACMP1 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BODD0_VDAC0CH0                                 (_GPIO_BBUSALLOC_BODD0_VDAC0CH0 << 16) /**< Shifted mode VDAC0CH0 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD0_VDAC1CH0                                 (_GPIO_BBUSALLOC_BODD0_VDAC1CH0 << 16) /**< Shifted mode VDAC1CH0 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD0_DEBUG                                    (_GPIO_BBUSALLOC_BODD0_DEBUG << 16)    /**< Shifted mode DEBUG for GPIO_BBUSALLOC       */
#define _GPIO_BBUSALLOC_BODD1_SHIFT                                   24                                     /**< Shift value for GPIO_BODD1                  */
#define _GPIO_BBUSALLOC_BODD1_MASK                                    0xF000000UL                            /**< Bit mask for GPIO_BODD1                     */
#define _GPIO_BBUSALLOC_BODD1_DEFAULT                                 0x00000000UL                           /**< Mode DEFAULT for GPIO_BBUSALLOC             */
#define _GPIO_BBUSALLOC_BODD1_TRISTATE                                0x00000000UL                           /**< Mode TRISTATE for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD1_ADC0                                    0x00000001UL                           /**< Mode ADC0 for GPIO_BBUSALLOC                */
#define _GPIO_BBUSALLOC_BODD1_ACMP0                                   0x00000002UL                           /**< Mode ACMP0 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BODD1_ACMP1                                   0x00000003UL                           /**< Mode ACMP1 for GPIO_BBUSALLOC               */
#define _GPIO_BBUSALLOC_BODD1_VDAC0CH1                                0x00000004UL                           /**< Mode VDAC0CH1 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD1_VDAC1CH1                                0x00000005UL                           /**< Mode VDAC1CH1 for GPIO_BBUSALLOC            */
#define _GPIO_BBUSALLOC_BODD1_DEBUG                                   0x0000000FUL                           /**< Mode DEBUG for GPIO_BBUSALLOC               */
#define GPIO_BBUSALLOC_BODD1_DEFAULT                                  (_GPIO_BBUSALLOC_BODD1_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_BBUSALLOC     */
#define GPIO_BBUSALLOC_BODD1_TRISTATE                                 (_GPIO_BBUSALLOC_BODD1_TRISTATE << 24) /**< Shifted mode TRISTATE for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD1_ADC0                                     (_GPIO_BBUSALLOC_BODD1_ADC0 << 24)     /**< Shifted mode ADC0 for GPIO_BBUSALLOC        */
#define GPIO_BBUSALLOC_BODD1_ACMP0                                    (_GPIO_BBUSALLOC_BODD1_ACMP0 << 24)    /**< Shifted mode ACMP0 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BODD1_ACMP1                                    (_GPIO_BBUSALLOC_BODD1_ACMP1 << 24)    /**< Shifted mode ACMP1 for GPIO_BBUSALLOC       */
#define GPIO_BBUSALLOC_BODD1_VDAC0CH1                                 (_GPIO_BBUSALLOC_BODD1_VDAC0CH1 << 24) /**< Shifted mode VDAC0CH1 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD1_VDAC1CH1                                 (_GPIO_BBUSALLOC_BODD1_VDAC1CH1 << 24) /**< Shifted mode VDAC1CH1 for GPIO_BBUSALLOC    */
#define GPIO_BBUSALLOC_BODD1_DEBUG                                    (_GPIO_BBUSALLOC_BODD1_DEBUG << 24)    /**< Shifted mode DEBUG for GPIO_BBUSALLOC       */

/* Bit fields for GPIO CDBUSALLOC */
#define _GPIO_CDBUSALLOC_RESETVALUE                                   0x00000000UL                             /**< Default value for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_MASK                                         0x0F0F0F0FUL                             /**< Mask for GPIO_CDBUSALLOC                    */
#define _GPIO_CDBUSALLOC_CDEVEN0_SHIFT                                0                                        /**< Shift value for GPIO_CDEVEN0                */
#define _GPIO_CDBUSALLOC_CDEVEN0_MASK                                 0xFUL                                    /**< Bit mask for GPIO_CDEVEN0                   */
#define _GPIO_CDBUSALLOC_CDEVEN0_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_CDBUSALLOC            */
#define _GPIO_CDBUSALLOC_CDEVEN0_TRISTATE                             0x00000000UL                             /**< Mode TRISTATE for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN0_ADC0                                 0x00000001UL                             /**< Mode ADC0 for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDEVEN0_ACMP0                                0x00000002UL                             /**< Mode ACMP0 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDEVEN0_ACMP1                                0x00000003UL                             /**< Mode ACMP1 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0                             0x00000004UL                             /**< Mode VDAC0CH0 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN0_VDAC1CH0                             0x00000005UL                             /**< Mode VDAC1CH0 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN0_REPEFUSE                             0x0000000BUL                             /**< Mode REPEFUSE for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN0_PMON                                 0x0000000CUL                             /**< Mode PMON for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDEVEN0_EFUSE                                0x0000000DUL                             /**< Mode EFUSE for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDEVEN0_DEBUG                                0x0000000FUL                             /**< Mode DEBUG for GPIO_CDBUSALLOC              */
#define GPIO_CDBUSALLOC_CDEVEN0_DEFAULT                               (_GPIO_CDBUSALLOC_CDEVEN0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_CDBUSALLOC    */
#define GPIO_CDBUSALLOC_CDEVEN0_TRISTATE                              (_GPIO_CDBUSALLOC_CDEVEN0_TRISTATE << 0) /**< Shifted mode TRISTATE for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN0_ADC0                                  (_GPIO_CDBUSALLOC_CDEVEN0_ADC0 << 0)     /**< Shifted mode ADC0 for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDEVEN0_ACMP0                                 (_GPIO_CDBUSALLOC_CDEVEN0_ACMP0 << 0)    /**< Shifted mode ACMP0 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDEVEN0_ACMP1                                 (_GPIO_CDBUSALLOC_CDEVEN0_ACMP1 << 0)    /**< Shifted mode ACMP1 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0                              (_GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0 << 0) /**< Shifted mode VDAC0CH0 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN0_VDAC1CH0                              (_GPIO_CDBUSALLOC_CDEVEN0_VDAC1CH0 << 0) /**< Shifted mode VDAC1CH0 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN0_REPEFUSE                              (_GPIO_CDBUSALLOC_CDEVEN0_REPEFUSE << 0) /**< Shifted mode REPEFUSE for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN0_PMON                                  (_GPIO_CDBUSALLOC_CDEVEN0_PMON << 0)     /**< Shifted mode PMON for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDEVEN0_EFUSE                                 (_GPIO_CDBUSALLOC_CDEVEN0_EFUSE << 0)    /**< Shifted mode EFUSE for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDEVEN0_DEBUG                                 (_GPIO_CDBUSALLOC_CDEVEN0_DEBUG << 0)    /**< Shifted mode DEBUG for GPIO_CDBUSALLOC      */
#define _GPIO_CDBUSALLOC_CDEVEN1_SHIFT                                8                                        /**< Shift value for GPIO_CDEVEN1                */
#define _GPIO_CDBUSALLOC_CDEVEN1_MASK                                 0xF00UL                                  /**< Bit mask for GPIO_CDEVEN1                   */
#define _GPIO_CDBUSALLOC_CDEVEN1_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_CDBUSALLOC            */
#define _GPIO_CDBUSALLOC_CDEVEN1_TRISTATE                             0x00000000UL                             /**< Mode TRISTATE for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN1_ADC0                                 0x00000001UL                             /**< Mode ADC0 for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDEVEN1_ACMP0                                0x00000002UL                             /**< Mode ACMP0 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDEVEN1_ACMP1                                0x00000003UL                             /**< Mode ACMP1 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1                             0x00000004UL                             /**< Mode VDAC0CH1 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN1_VDAC1CH1                             0x00000005UL                             /**< Mode VDAC1CH1 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDEVEN1_DEBUG                                0x0000000FUL                             /**< Mode DEBUG for GPIO_CDBUSALLOC              */
#define GPIO_CDBUSALLOC_CDEVEN1_DEFAULT                               (_GPIO_CDBUSALLOC_CDEVEN1_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_CDBUSALLOC    */
#define GPIO_CDBUSALLOC_CDEVEN1_TRISTATE                              (_GPIO_CDBUSALLOC_CDEVEN1_TRISTATE << 8) /**< Shifted mode TRISTATE for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN1_ADC0                                  (_GPIO_CDBUSALLOC_CDEVEN1_ADC0 << 8)     /**< Shifted mode ADC0 for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDEVEN1_ACMP0                                 (_GPIO_CDBUSALLOC_CDEVEN1_ACMP0 << 8)    /**< Shifted mode ACMP0 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDEVEN1_ACMP1                                 (_GPIO_CDBUSALLOC_CDEVEN1_ACMP1 << 8)    /**< Shifted mode ACMP1 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1                              (_GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1 << 8) /**< Shifted mode VDAC0CH1 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN1_VDAC1CH1                              (_GPIO_CDBUSALLOC_CDEVEN1_VDAC1CH1 << 8) /**< Shifted mode VDAC1CH1 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDEVEN1_DEBUG                                 (_GPIO_CDBUSALLOC_CDEVEN1_DEBUG << 8)    /**< Shifted mode DEBUG for GPIO_CDBUSALLOC      */
#define _GPIO_CDBUSALLOC_CDODD0_SHIFT                                 16                                       /**< Shift value for GPIO_CDODD0                 */
#define _GPIO_CDBUSALLOC_CDODD0_MASK                                  0xF0000UL                                /**< Bit mask for GPIO_CDODD0                    */
#define _GPIO_CDBUSALLOC_CDODD0_DEFAULT                               0x00000000UL                             /**< Mode DEFAULT for GPIO_CDBUSALLOC            */
#define _GPIO_CDBUSALLOC_CDODD0_TRISTATE                              0x00000000UL                             /**< Mode TRISTATE for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD0_ADC0                                  0x00000001UL                             /**< Mode ADC0 for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDODD0_ACMP0                                 0x00000002UL                             /**< Mode ACMP0 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDODD0_ACMP1                                 0x00000003UL                             /**< Mode ACMP1 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDODD0_VDAC0CH0                              0x00000004UL                             /**< Mode VDAC0CH0 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD0_VDAC1CH0                              0x00000005UL                             /**< Mode VDAC1CH0 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD0_PMON                                  0x0000000CUL                             /**< Mode PMON for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDODD0_DEBUG                                 0x0000000FUL                             /**< Mode DEBUG for GPIO_CDBUSALLOC              */
#define GPIO_CDBUSALLOC_CDODD0_DEFAULT                                (_GPIO_CDBUSALLOC_CDODD0_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_CDBUSALLOC    */
#define GPIO_CDBUSALLOC_CDODD0_TRISTATE                               (_GPIO_CDBUSALLOC_CDODD0_TRISTATE << 16) /**< Shifted mode TRISTATE for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD0_ADC0                                   (_GPIO_CDBUSALLOC_CDODD0_ADC0 << 16)     /**< Shifted mode ADC0 for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDODD0_ACMP0                                  (_GPIO_CDBUSALLOC_CDODD0_ACMP0 << 16)    /**< Shifted mode ACMP0 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDODD0_ACMP1                                  (_GPIO_CDBUSALLOC_CDODD0_ACMP1 << 16)    /**< Shifted mode ACMP1 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDODD0_VDAC0CH0                               (_GPIO_CDBUSALLOC_CDODD0_VDAC0CH0 << 16) /**< Shifted mode VDAC0CH0 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD0_VDAC1CH0                               (_GPIO_CDBUSALLOC_CDODD0_VDAC1CH0 << 16) /**< Shifted mode VDAC1CH0 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD0_PMON                                   (_GPIO_CDBUSALLOC_CDODD0_PMON << 16)     /**< Shifted mode PMON for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDODD0_DEBUG                                  (_GPIO_CDBUSALLOC_CDODD0_DEBUG << 16)    /**< Shifted mode DEBUG for GPIO_CDBUSALLOC      */
#define _GPIO_CDBUSALLOC_CDODD1_SHIFT                                 24                                       /**< Shift value for GPIO_CDODD1                 */
#define _GPIO_CDBUSALLOC_CDODD1_MASK                                  0xF000000UL                              /**< Bit mask for GPIO_CDODD1                    */
#define _GPIO_CDBUSALLOC_CDODD1_DEFAULT                               0x00000000UL                             /**< Mode DEFAULT for GPIO_CDBUSALLOC            */
#define _GPIO_CDBUSALLOC_CDODD1_TRISTATE                              0x00000000UL                             /**< Mode TRISTATE for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD1_ADC0                                  0x00000001UL                             /**< Mode ADC0 for GPIO_CDBUSALLOC               */
#define _GPIO_CDBUSALLOC_CDODD1_ACMP0                                 0x00000002UL                             /**< Mode ACMP0 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDODD1_ACMP1                                 0x00000003UL                             /**< Mode ACMP1 for GPIO_CDBUSALLOC              */
#define _GPIO_CDBUSALLOC_CDODD1_VDAC0CH1                              0x00000004UL                             /**< Mode VDAC0CH1 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD1_VDAC1CH1                              0x00000005UL                             /**< Mode VDAC1CH1 for GPIO_CDBUSALLOC           */
#define _GPIO_CDBUSALLOC_CDODD1_DEBUG                                 0x0000000FUL                             /**< Mode DEBUG for GPIO_CDBUSALLOC              */
#define GPIO_CDBUSALLOC_CDODD1_DEFAULT                                (_GPIO_CDBUSALLOC_CDODD1_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_CDBUSALLOC    */
#define GPIO_CDBUSALLOC_CDODD1_TRISTATE                               (_GPIO_CDBUSALLOC_CDODD1_TRISTATE << 24) /**< Shifted mode TRISTATE for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD1_ADC0                                   (_GPIO_CDBUSALLOC_CDODD1_ADC0 << 24)     /**< Shifted mode ADC0 for GPIO_CDBUSALLOC       */
#define GPIO_CDBUSALLOC_CDODD1_ACMP0                                  (_GPIO_CDBUSALLOC_CDODD1_ACMP0 << 24)    /**< Shifted mode ACMP0 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDODD1_ACMP1                                  (_GPIO_CDBUSALLOC_CDODD1_ACMP1 << 24)    /**< Shifted mode ACMP1 for GPIO_CDBUSALLOC      */
#define GPIO_CDBUSALLOC_CDODD1_VDAC0CH1                               (_GPIO_CDBUSALLOC_CDODD1_VDAC0CH1 << 24) /**< Shifted mode VDAC0CH1 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD1_VDAC1CH1                               (_GPIO_CDBUSALLOC_CDODD1_VDAC1CH1 << 24) /**< Shifted mode VDAC1CH1 for GPIO_CDBUSALLOC   */
#define GPIO_CDBUSALLOC_CDODD1_DEBUG                                  (_GPIO_CDBUSALLOC_CDODD1_DEBUG << 24)    /**< Shifted mode DEBUG for GPIO_CDBUSALLOC      */

/* Bit fields for GPIO AODD0SWITCH */
#define _GPIO_AODD0SWITCH_RESETVALUE                                  0x00000000UL                                 /**< Default value for GPIO_AODD0SWITCH          */
#define _GPIO_AODD0SWITCH_MASK                                        0x0000001FUL                                 /**< Mask for GPIO_AODD0SWITCH                   */
#define _GPIO_AODD0SWITCH_AODD0SWITCH_SHIFT                           0                                            /**< Shift value for GPIO_AODD0SWITCH            */
#define _GPIO_AODD0SWITCH_AODD0SWITCH_MASK                            0x1FUL                                       /**< Bit mask for GPIO_AODD0SWITCH               */
#define _GPIO_AODD0SWITCH_AODD0SWITCH_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_AODD0SWITCH           */
#define GPIO_AODD0SWITCH_AODD0SWITCH_DEFAULT                          (_GPIO_AODD0SWITCH_AODD0SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_AODD0SWITCH   */

/* Bit fields for GPIO AODD1SWITCH */
#define _GPIO_AODD1SWITCH_RESETVALUE                                  0x00000000UL                                 /**< Default value for GPIO_AODD1SWITCH          */
#define _GPIO_AODD1SWITCH_MASK                                        0x0000001FUL                                 /**< Mask for GPIO_AODD1SWITCH                   */
#define _GPIO_AODD1SWITCH_AODD1SWITCH_SHIFT                           0                                            /**< Shift value for GPIO_AODD1SWITCH            */
#define _GPIO_AODD1SWITCH_AODD1SWITCH_MASK                            0x1FUL                                       /**< Bit mask for GPIO_AODD1SWITCH               */
#define _GPIO_AODD1SWITCH_AODD1SWITCH_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_AODD1SWITCH           */
#define GPIO_AODD1SWITCH_AODD1SWITCH_DEFAULT                          (_GPIO_AODD1SWITCH_AODD1SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_AODD1SWITCH   */

/* Bit fields for GPIO AEVEN0SWITCH */
#define _GPIO_AEVEN0SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_AEVEN0SWITCH         */
#define _GPIO_AEVEN0SWITCH_MASK                                       0x0000001FUL                                   /**< Mask for GPIO_AEVEN0SWITCH                  */
#define _GPIO_AEVEN0SWITCH_AEVEN0SWITCH_SHIFT                         0                                              /**< Shift value for GPIO_AEVEN0SWITCH           */
#define _GPIO_AEVEN0SWITCH_AEVEN0SWITCH_MASK                          0x1FUL                                         /**< Bit mask for GPIO_AEVEN0SWITCH              */
#define _GPIO_AEVEN0SWITCH_AEVEN0SWITCH_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_AEVEN0SWITCH          */
#define GPIO_AEVEN0SWITCH_AEVEN0SWITCH_DEFAULT                        (_GPIO_AEVEN0SWITCH_AEVEN0SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_AEVEN0SWITCH  */

/* Bit fields for GPIO AEVEN1SWITCH */
#define _GPIO_AEVEN1SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_AEVEN1SWITCH         */
#define _GPIO_AEVEN1SWITCH_MASK                                       0x0000001FUL                                   /**< Mask for GPIO_AEVEN1SWITCH                  */
#define _GPIO_AEVEN1SWITCH_AEVEN1SWITCH_SHIFT                         0                                              /**< Shift value for GPIO_AEVEN1SWITCH           */
#define _GPIO_AEVEN1SWITCH_AEVEN1SWITCH_MASK                          0x1FUL                                         /**< Bit mask for GPIO_AEVEN1SWITCH              */
#define _GPIO_AEVEN1SWITCH_AEVEN1SWITCH_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_AEVEN1SWITCH          */
#define GPIO_AEVEN1SWITCH_AEVEN1SWITCH_DEFAULT                        (_GPIO_AEVEN1SWITCH_AEVEN1SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_AEVEN1SWITCH  */

/* Bit fields for GPIO BODD0SWITCH */
#define _GPIO_BODD0SWITCH_RESETVALUE                                  0x00000000UL                                 /**< Default value for GPIO_BODD0SWITCH          */
#define _GPIO_BODD0SWITCH_MASK                                        0x00000007UL                                 /**< Mask for GPIO_BODD0SWITCH                   */
#define _GPIO_BODD0SWITCH_BODD0SWITCH_SHIFT                           0                                            /**< Shift value for GPIO_BODD0SWITCH            */
#define _GPIO_BODD0SWITCH_BODD0SWITCH_MASK                            0x7UL                                        /**< Bit mask for GPIO_BODD0SWITCH               */
#define _GPIO_BODD0SWITCH_BODD0SWITCH_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_BODD0SWITCH           */
#define GPIO_BODD0SWITCH_BODD0SWITCH_DEFAULT                          (_GPIO_BODD0SWITCH_BODD0SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_BODD0SWITCH   */

/* Bit fields for GPIO BODD1SWITCH */
#define _GPIO_BODD1SWITCH_RESETVALUE                                  0x00000000UL                                 /**< Default value for GPIO_BODD1SWITCH          */
#define _GPIO_BODD1SWITCH_MASK                                        0x00000007UL                                 /**< Mask for GPIO_BODD1SWITCH                   */
#define _GPIO_BODD1SWITCH_BODD1SWITCH_SHIFT                           0                                            /**< Shift value for GPIO_BODD1SWITCH            */
#define _GPIO_BODD1SWITCH_BODD1SWITCH_MASK                            0x7UL                                        /**< Bit mask for GPIO_BODD1SWITCH               */
#define _GPIO_BODD1SWITCH_BODD1SWITCH_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_BODD1SWITCH           */
#define GPIO_BODD1SWITCH_BODD1SWITCH_DEFAULT                          (_GPIO_BODD1SWITCH_BODD1SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_BODD1SWITCH   */

/* Bit fields for GPIO BEVEN0SWITCH */
#define _GPIO_BEVEN0SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_BEVEN0SWITCH         */
#define _GPIO_BEVEN0SWITCH_MASK                                       0x00000007UL                                   /**< Mask for GPIO_BEVEN0SWITCH                  */
#define _GPIO_BEVEN0SWITCH_BEVEN0SWITCH_SHIFT                         0                                              /**< Shift value for GPIO_BEVEN0SWITCH           */
#define _GPIO_BEVEN0SWITCH_BEVEN0SWITCH_MASK                          0x7UL                                          /**< Bit mask for GPIO_BEVEN0SWITCH              */
#define _GPIO_BEVEN0SWITCH_BEVEN0SWITCH_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_BEVEN0SWITCH          */
#define GPIO_BEVEN0SWITCH_BEVEN0SWITCH_DEFAULT                        (_GPIO_BEVEN0SWITCH_BEVEN0SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_BEVEN0SWITCH  */

/* Bit fields for GPIO BEVEN1SWITCH */
#define _GPIO_BEVEN1SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_BEVEN1SWITCH         */
#define _GPIO_BEVEN1SWITCH_MASK                                       0x00000007UL                                   /**< Mask for GPIO_BEVEN1SWITCH                  */
#define _GPIO_BEVEN1SWITCH_BEVEN1SWITCH_SHIFT                         0                                              /**< Shift value for GPIO_BEVEN1SWITCH           */
#define _GPIO_BEVEN1SWITCH_BEVEN1SWITCH_MASK                          0x7UL                                          /**< Bit mask for GPIO_BEVEN1SWITCH              */
#define _GPIO_BEVEN1SWITCH_BEVEN1SWITCH_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_BEVEN1SWITCH          */
#define GPIO_BEVEN1SWITCH_BEVEN1SWITCH_DEFAULT                        (_GPIO_BEVEN1SWITCH_BEVEN1SWITCH_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_BEVEN1SWITCH  */

/* Bit fields for GPIO CDODD0SWITCH */
#define _GPIO_CDODD0SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_CDODD0SWITCH         */
#define _GPIO_CDODD0SWITCH_MASK                                       0x0007001FUL                                   /**< Mask for GPIO_CDODD0SWITCH                  */
#define _GPIO_CDODD0SWITCH_CODD0SWITCH_SHIFT                          0                                              /**< Shift value for GPIO_CODD0SWITCH            */
#define _GPIO_CDODD0SWITCH_CODD0SWITCH_MASK                           0x1FUL                                         /**< Bit mask for GPIO_CODD0SWITCH               */
#define _GPIO_CDODD0SWITCH_CODD0SWITCH_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_CDODD0SWITCH          */
#define GPIO_CDODD0SWITCH_CODD0SWITCH_DEFAULT                         (_GPIO_CDODD0SWITCH_CODD0SWITCH_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_CDODD0SWITCH  */
#define _GPIO_CDODD0SWITCH_DODD0SWITCH_SHIFT                          16                                             /**< Shift value for GPIO_DODD0SWITCH            */
#define _GPIO_CDODD0SWITCH_DODD0SWITCH_MASK                           0x70000UL                                      /**< Bit mask for GPIO_DODD0SWITCH               */
#define _GPIO_CDODD0SWITCH_DODD0SWITCH_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_CDODD0SWITCH          */
#define GPIO_CDODD0SWITCH_DODD0SWITCH_DEFAULT                         (_GPIO_CDODD0SWITCH_DODD0SWITCH_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CDODD0SWITCH  */

/* Bit fields for GPIO CDODD1SWITCH */
#define _GPIO_CDODD1SWITCH_RESETVALUE                                 0x00000000UL                                   /**< Default value for GPIO_CDODD1SWITCH         */
#define _GPIO_CDODD1SWITCH_MASK                                       0x0007001FUL                                   /**< Mask for GPIO_CDODD1SWITCH                  */
#define _GPIO_CDODD1SWITCH_CODD1SWITCH_SHIFT                          0                                              /**< Shift value for GPIO_CODD1SWITCH            */
#define _GPIO_CDODD1SWITCH_CODD1SWITCH_MASK                           0x1FUL                                         /**< Bit mask for GPIO_CODD1SWITCH               */
#define _GPIO_CDODD1SWITCH_CODD1SWITCH_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_CDODD1SWITCH          */
#define GPIO_CDODD1SWITCH_CODD1SWITCH_DEFAULT                         (_GPIO_CDODD1SWITCH_CODD1SWITCH_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_CDODD1SWITCH  */
#define _GPIO_CDODD1SWITCH_DODD1SWITCH_SHIFT                          16                                             /**< Shift value for GPIO_DODD1SWITCH            */
#define _GPIO_CDODD1SWITCH_DODD1SWITCH_MASK                           0x70000UL                                      /**< Bit mask for GPIO_DODD1SWITCH               */
#define _GPIO_CDODD1SWITCH_DODD1SWITCH_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_CDODD1SWITCH          */
#define GPIO_CDODD1SWITCH_DODD1SWITCH_DEFAULT                         (_GPIO_CDODD1SWITCH_DODD1SWITCH_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CDODD1SWITCH  */

/* Bit fields for GPIO CDEVEN0SWITCH */
#define _GPIO_CDEVEN0SWITCH_RESETVALUE                                0x00000000UL                                     /**< Default value for GPIO_CDEVEN0SWITCH        */
#define _GPIO_CDEVEN0SWITCH_MASK                                      0x0007001FUL                                     /**< Mask for GPIO_CDEVEN0SWITCH                 */
#define _GPIO_CDEVEN0SWITCH_CEVEN0SWITCH_SHIFT                        0                                                /**< Shift value for GPIO_CEVEN0SWITCH           */
#define _GPIO_CDEVEN0SWITCH_CEVEN0SWITCH_MASK                         0x1FUL                                           /**< Bit mask for GPIO_CEVEN0SWITCH              */
#define _GPIO_CDEVEN0SWITCH_CEVEN0SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_CDEVEN0SWITCH         */
#define GPIO_CDEVEN0SWITCH_CEVEN0SWITCH_DEFAULT                       (_GPIO_CDEVEN0SWITCH_CEVEN0SWITCH_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_CDEVEN0SWITCH */
#define _GPIO_CDEVEN0SWITCH_DEVEN0SWITCH_SHIFT                        16                                               /**< Shift value for GPIO_DEVEN0SWITCH           */
#define _GPIO_CDEVEN0SWITCH_DEVEN0SWITCH_MASK                         0x70000UL                                        /**< Bit mask for GPIO_DEVEN0SWITCH              */
#define _GPIO_CDEVEN0SWITCH_DEVEN0SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_CDEVEN0SWITCH         */
#define GPIO_CDEVEN0SWITCH_DEVEN0SWITCH_DEFAULT                       (_GPIO_CDEVEN0SWITCH_DEVEN0SWITCH_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CDEVEN0SWITCH */

/* Bit fields for GPIO CDEVEN1SWITCH */
#define _GPIO_CDEVEN1SWITCH_RESETVALUE                                0x00000000UL                                     /**< Default value for GPIO_CDEVEN1SWITCH        */
#define _GPIO_CDEVEN1SWITCH_MASK                                      0x0007001FUL                                     /**< Mask for GPIO_CDEVEN1SWITCH                 */
#define _GPIO_CDEVEN1SWITCH_CEVEN1SWITCH_SHIFT                        0                                                /**< Shift value for GPIO_CEVEN1SWITCH           */
#define _GPIO_CDEVEN1SWITCH_CEVEN1SWITCH_MASK                         0x1FUL                                           /**< Bit mask for GPIO_CEVEN1SWITCH              */
#define _GPIO_CDEVEN1SWITCH_CEVEN1SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_CDEVEN1SWITCH         */
#define GPIO_CDEVEN1SWITCH_CEVEN1SWITCH_DEFAULT                       (_GPIO_CDEVEN1SWITCH_CEVEN1SWITCH_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_CDEVEN1SWITCH */
#define _GPIO_CDEVEN1SWITCH_DEVEN1SWITCH_SHIFT                        16                                               /**< Shift value for GPIO_DEVEN1SWITCH           */
#define _GPIO_CDEVEN1SWITCH_DEVEN1SWITCH_MASK                         0x70000UL                                        /**< Bit mask for GPIO_DEVEN1SWITCH              */
#define _GPIO_CDEVEN1SWITCH_DEVEN1SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_CDEVEN1SWITCH         */
#define GPIO_CDEVEN1SWITCH_DEVEN1SWITCH_DEFAULT                       (_GPIO_CDEVEN1SWITCH_DEVEN1SWITCH_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CDEVEN1SWITCH */

/* Bit fields for GPIO EXTIPSELL */
#define _GPIO_EXTIPSELL_RESETVALUE                                    0x00000000UL                              /**< Default value for GPIO_EXTIPSELL            */
#define _GPIO_EXTIPSELL_MASK                                          0x33333333UL                              /**< Mask for GPIO_EXTIPSELL                     */
#define _GPIO_EXTIPSELL_EXTIPSEL0_SHIFT                               0                                         /**< Shift value for GPIO_EXTIPSEL0              */
#define _GPIO_EXTIPSELL_EXTIPSEL0_MASK                                0x3UL                                     /**< Bit mask for GPIO_EXTIPSEL0                 */
#define _GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL0_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL0_PORTA << 0)    /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL0_PORTB << 0)    /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL0_PORTC << 0)    /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL0_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL0_PORTD << 0)    /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL1_SHIFT                               4                                         /**< Shift value for GPIO_EXTIPSEL1              */
#define _GPIO_EXTIPSELL_EXTIPSEL1_MASK                                0x30UL                                    /**< Bit mask for GPIO_EXTIPSEL1                 */
#define _GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL1_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL1_PORTA << 4)    /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL1_PORTB << 4)    /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL1_PORTC << 4)    /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL1_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL1_PORTD << 4)    /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL2_SHIFT                               8                                         /**< Shift value for GPIO_EXTIPSEL2              */
#define _GPIO_EXTIPSELL_EXTIPSEL2_MASK                                0x300UL                                   /**< Bit mask for GPIO_EXTIPSEL2                 */
#define _GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL2_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL2_PORTA << 8)    /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL2_PORTB << 8)    /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL2_PORTC << 8)    /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL2_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL2_PORTD << 8)    /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL3_SHIFT                               12                                        /**< Shift value for GPIO_EXTIPSEL3              */
#define _GPIO_EXTIPSELL_EXTIPSEL3_MASK                                0x3000UL                                  /**< Bit mask for GPIO_EXTIPSEL3                 */
#define _GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL3_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL3_PORTA << 12)   /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL3_PORTB << 12)   /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL3_PORTC << 12)   /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL3_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL3_PORTD << 12)   /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL4_SHIFT                               16                                        /**< Shift value for GPIO_EXTIPSEL4              */
#define _GPIO_EXTIPSELL_EXTIPSEL4_MASK                                0x30000UL                                 /**< Bit mask for GPIO_EXTIPSEL4                 */
#define _GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL4_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL4_PORTA << 16)   /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL4_PORTB << 16)   /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL4_PORTC << 16)   /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL4_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL4_PORTD << 16)   /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL5_SHIFT                               20                                        /**< Shift value for GPIO_EXTIPSEL5              */
#define _GPIO_EXTIPSELL_EXTIPSEL5_MASK                                0x300000UL                                /**< Bit mask for GPIO_EXTIPSEL5                 */
#define _GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL5_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL5_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL5_PORTA << 20)   /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL5_PORTB << 20)   /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL5_PORTC << 20)   /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL5_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL5_PORTD << 20)   /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL6_SHIFT                               24                                        /**< Shift value for GPIO_EXTIPSEL6              */
#define _GPIO_EXTIPSELL_EXTIPSEL6_MASK                                0x3000000UL                               /**< Bit mask for GPIO_EXTIPSEL6                 */
#define _GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL6_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL6_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL6_PORTA << 24)   /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL6_PORTB << 24)   /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL6_PORTC << 24)   /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL6_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL6_PORTD << 24)   /**< Shifted mode PORTD for GPIO_EXTIPSELL       */
#define _GPIO_EXTIPSELL_EXTIPSEL7_SHIFT                               28                                        /**< Shift value for GPIO_EXTIPSEL7              */
#define _GPIO_EXTIPSELL_EXTIPSEL7_MASK                                0x30000000UL                              /**< Bit mask for GPIO_EXTIPSEL7                 */
#define _GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELL             */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELL               */
#define _GPIO_EXTIPSELL_EXTIPSEL7_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELL               */
#define GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT                              (_GPIO_EXTIPSELL_EXTIPSEL7_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPSELL     */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTA                                (_GPIO_EXTIPSELL_EXTIPSEL7_PORTA << 28)   /**< Shifted mode PORTA for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTB                                (_GPIO_EXTIPSELL_EXTIPSEL7_PORTB << 28)   /**< Shifted mode PORTB for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTC                                (_GPIO_EXTIPSELL_EXTIPSEL7_PORTC << 28)   /**< Shifted mode PORTC for GPIO_EXTIPSELL       */
#define GPIO_EXTIPSELL_EXTIPSEL7_PORTD                                (_GPIO_EXTIPSELL_EXTIPSEL7_PORTD << 28)   /**< Shifted mode PORTD for GPIO_EXTIPSELL       */

/* Bit fields for GPIO EXTIPSELH */
#define _GPIO_EXTIPSELH_RESETVALUE                                    0x00000000UL                              /**< Default value for GPIO_EXTIPSELH            */
#define _GPIO_EXTIPSELH_MASK                                          0x00003333UL                              /**< Mask for GPIO_EXTIPSELH                     */
#define _GPIO_EXTIPSELH_EXTIPSEL0_SHIFT                               0                                         /**< Shift value for GPIO_EXTIPSEL0              */
#define _GPIO_EXTIPSELH_EXTIPSEL0_MASK                                0x3UL                                     /**< Bit mask for GPIO_EXTIPSEL0                 */
#define _GPIO_EXTIPSELH_EXTIPSEL0_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELH             */
#define _GPIO_EXTIPSELH_EXTIPSEL0_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL0_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL0_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL0_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELH               */
#define GPIO_EXTIPSELH_EXTIPSEL0_DEFAULT                              (_GPIO_EXTIPSELH_EXTIPSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELH     */
#define GPIO_EXTIPSELH_EXTIPSEL0_PORTA                                (_GPIO_EXTIPSELH_EXTIPSEL0_PORTA << 0)    /**< Shifted mode PORTA for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL0_PORTB                                (_GPIO_EXTIPSELH_EXTIPSEL0_PORTB << 0)    /**< Shifted mode PORTB for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL0_PORTC                                (_GPIO_EXTIPSELH_EXTIPSEL0_PORTC << 0)    /**< Shifted mode PORTC for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL0_PORTD                                (_GPIO_EXTIPSELH_EXTIPSEL0_PORTD << 0)    /**< Shifted mode PORTD for GPIO_EXTIPSELH       */
#define _GPIO_EXTIPSELH_EXTIPSEL1_SHIFT                               4                                         /**< Shift value for GPIO_EXTIPSEL1              */
#define _GPIO_EXTIPSELH_EXTIPSEL1_MASK                                0x30UL                                    /**< Bit mask for GPIO_EXTIPSEL1                 */
#define _GPIO_EXTIPSELH_EXTIPSEL1_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELH             */
#define _GPIO_EXTIPSELH_EXTIPSEL1_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL1_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL1_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL1_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELH               */
#define GPIO_EXTIPSELH_EXTIPSEL1_DEFAULT                              (_GPIO_EXTIPSELH_EXTIPSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELH     */
#define GPIO_EXTIPSELH_EXTIPSEL1_PORTA                                (_GPIO_EXTIPSELH_EXTIPSEL1_PORTA << 4)    /**< Shifted mode PORTA for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL1_PORTB                                (_GPIO_EXTIPSELH_EXTIPSEL1_PORTB << 4)    /**< Shifted mode PORTB for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL1_PORTC                                (_GPIO_EXTIPSELH_EXTIPSEL1_PORTC << 4)    /**< Shifted mode PORTC for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL1_PORTD                                (_GPIO_EXTIPSELH_EXTIPSEL1_PORTD << 4)    /**< Shifted mode PORTD for GPIO_EXTIPSELH       */
#define _GPIO_EXTIPSELH_EXTIPSEL2_SHIFT                               8                                         /**< Shift value for GPIO_EXTIPSEL2              */
#define _GPIO_EXTIPSELH_EXTIPSEL2_MASK                                0x300UL                                   /**< Bit mask for GPIO_EXTIPSEL2                 */
#define _GPIO_EXTIPSELH_EXTIPSEL2_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELH             */
#define _GPIO_EXTIPSELH_EXTIPSEL2_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL2_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL2_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL2_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELH               */
#define GPIO_EXTIPSELH_EXTIPSEL2_DEFAULT                              (_GPIO_EXTIPSELH_EXTIPSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPSELH     */
#define GPIO_EXTIPSELH_EXTIPSEL2_PORTA                                (_GPIO_EXTIPSELH_EXTIPSEL2_PORTA << 8)    /**< Shifted mode PORTA for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL2_PORTB                                (_GPIO_EXTIPSELH_EXTIPSEL2_PORTB << 8)    /**< Shifted mode PORTB for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL2_PORTC                                (_GPIO_EXTIPSELH_EXTIPSEL2_PORTC << 8)    /**< Shifted mode PORTC for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL2_PORTD                                (_GPIO_EXTIPSELH_EXTIPSEL2_PORTD << 8)    /**< Shifted mode PORTD for GPIO_EXTIPSELH       */
#define _GPIO_EXTIPSELH_EXTIPSEL3_SHIFT                               12                                        /**< Shift value for GPIO_EXTIPSEL3              */
#define _GPIO_EXTIPSELH_EXTIPSEL3_MASK                                0x3000UL                                  /**< Bit mask for GPIO_EXTIPSEL3                 */
#define _GPIO_EXTIPSELH_EXTIPSEL3_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EXTIPSELH             */
#define _GPIO_EXTIPSELH_EXTIPSEL3_PORTA                               0x00000000UL                              /**< Mode PORTA for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL3_PORTB                               0x00000001UL                              /**< Mode PORTB for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL3_PORTC                               0x00000002UL                              /**< Mode PORTC for GPIO_EXTIPSELH               */
#define _GPIO_EXTIPSELH_EXTIPSEL3_PORTD                               0x00000003UL                              /**< Mode PORTD for GPIO_EXTIPSELH               */
#define GPIO_EXTIPSELH_EXTIPSEL3_DEFAULT                              (_GPIO_EXTIPSELH_EXTIPSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPSELH     */
#define GPIO_EXTIPSELH_EXTIPSEL3_PORTA                                (_GPIO_EXTIPSELH_EXTIPSEL3_PORTA << 12)   /**< Shifted mode PORTA for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL3_PORTB                                (_GPIO_EXTIPSELH_EXTIPSEL3_PORTB << 12)   /**< Shifted mode PORTB for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL3_PORTC                                (_GPIO_EXTIPSELH_EXTIPSEL3_PORTC << 12)   /**< Shifted mode PORTC for GPIO_EXTIPSELH       */
#define GPIO_EXTIPSELH_EXTIPSEL3_PORTD                                (_GPIO_EXTIPSELH_EXTIPSEL3_PORTD << 12)   /**< Shifted mode PORTD for GPIO_EXTIPSELH       */

/* Bit fields for GPIO EXTIPINSELL */
#define _GPIO_EXTIPINSELL_RESETVALUE                                  0x00000000UL                                  /**< Default value for GPIO_EXTIPINSELL          */
#define _GPIO_EXTIPINSELL_MASK                                        0x33333333UL                                  /**< Mask for GPIO_EXTIPINSELL                   */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_SHIFT                           0                                             /**< Shift value for GPIO_EXTIPINSEL0            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_MASK                            0x3UL                                         /**< Bit mask for GPIO_EXTIPINSEL0               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN0 << 0)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN1 << 0)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN2 << 0)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL0_PIN3 << 0)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_SHIFT                           4                                             /**< Shift value for GPIO_EXTIPINSEL1            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_MASK                            0x30UL                                        /**< Bit mask for GPIO_EXTIPINSEL1               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN0 << 4)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN1 << 4)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN2 << 4)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL1_PIN3 << 4)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_SHIFT                           8                                             /**< Shift value for GPIO_EXTIPINSEL2            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_MASK                            0x300UL                                       /**< Bit mask for GPIO_EXTIPINSEL2               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN0 << 8)     /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN1 << 8)     /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN2 << 8)     /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL2_PIN3 << 8)     /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_SHIFT                           12                                            /**< Shift value for GPIO_EXTIPINSEL3            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_MASK                            0x3000UL                                      /**< Bit mask for GPIO_EXTIPINSEL3               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN0 << 12)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN1 << 12)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN2 << 12)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL3_PIN3 << 12)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_SHIFT                           16                                            /**< Shift value for GPIO_EXTIPINSEL4            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_MASK                            0x30000UL                                     /**< Bit mask for GPIO_EXTIPINSEL4               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL4_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL4_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN0 << 16)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN1 << 16)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN2 << 16)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL4_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL4_PIN3 << 16)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_SHIFT                           20                                            /**< Shift value for GPIO_EXTIPINSEL5            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_MASK                            0x300000UL                                    /**< Bit mask for GPIO_EXTIPINSEL5               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL5_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL5_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN0 << 20)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN1 << 20)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN2 << 20)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL5_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL5_PIN3 << 20)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_SHIFT                           24                                            /**< Shift value for GPIO_EXTIPINSEL6            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_MASK                            0x3000000UL                                   /**< Bit mask for GPIO_EXTIPINSEL6               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL6_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL6_DEFAULT << 24) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN0 << 24)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN1 << 24)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN2 << 24)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL6_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL6_PIN3 << 24)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_SHIFT                           28                                            /**< Shift value for GPIO_EXTIPINSEL7            */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_MASK                            0x30000000UL                                  /**< Bit mask for GPIO_EXTIPINSEL7               */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELL           */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN0                            0x00000000UL                                  /**< Mode PIN0 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN1                            0x00000001UL                                  /**< Mode PIN1 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN2                            0x00000002UL                                  /**< Mode PIN2 for GPIO_EXTIPINSELL              */
#define _GPIO_EXTIPINSELL_EXTIPINSEL7_PIN3                            0x00000003UL                                  /**< Mode PIN3 for GPIO_EXTIPINSELL              */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT                          (_GPIO_EXTIPINSELL_EXTIPINSEL7_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELL   */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN0                             (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN0 << 28)    /**< Shifted mode PIN0 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN1                             (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN1 << 28)    /**< Shifted mode PIN1 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN2                             (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN2 << 28)    /**< Shifted mode PIN2 for GPIO_EXTIPINSELL      */
#define GPIO_EXTIPINSELL_EXTIPINSEL7_PIN3                             (_GPIO_EXTIPINSELL_EXTIPINSEL7_PIN3 << 28)    /**< Shifted mode PIN3 for GPIO_EXTIPINSELL      */

/* Bit fields for GPIO EXTIPINSELH */
#define _GPIO_EXTIPINSELH_RESETVALUE                                  0x00000000UL                                  /**< Default value for GPIO_EXTIPINSELH          */
#define _GPIO_EXTIPINSELH_MASK                                        0x00003333UL                                  /**< Mask for GPIO_EXTIPINSELH                   */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_SHIFT                           0                                             /**< Shift value for GPIO_EXTIPINSEL0            */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_MASK                            0x3UL                                         /**< Bit mask for GPIO_EXTIPINSEL0               */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELH           */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_PIN8                            0x00000000UL                                  /**< Mode PIN8 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_PIN9                            0x00000001UL                                  /**< Mode PIN9 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_PIN10                           0x00000002UL                                  /**< Mode PIN10 for GPIO_EXTIPINSELH             */
#define _GPIO_EXTIPINSELH_EXTIPINSEL0_PIN11                           0x00000003UL                                  /**< Mode PIN11 for GPIO_EXTIPINSELH             */
#define GPIO_EXTIPINSELH_EXTIPINSEL0_DEFAULT                          (_GPIO_EXTIPINSELH_EXTIPINSEL0_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH   */
#define GPIO_EXTIPINSELH_EXTIPINSEL0_PIN8                             (_GPIO_EXTIPINSELH_EXTIPINSEL0_PIN8 << 0)     /**< Shifted mode PIN8 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL0_PIN9                             (_GPIO_EXTIPINSELH_EXTIPINSEL0_PIN9 << 0)     /**< Shifted mode PIN9 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL0_PIN10                            (_GPIO_EXTIPINSELH_EXTIPINSEL0_PIN10 << 0)    /**< Shifted mode PIN10 for GPIO_EXTIPINSELH     */
#define GPIO_EXTIPINSELH_EXTIPINSEL0_PIN11                            (_GPIO_EXTIPINSELH_EXTIPINSEL0_PIN11 << 0)    /**< Shifted mode PIN11 for GPIO_EXTIPINSELH     */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_SHIFT                           4                                             /**< Shift value for GPIO_EXTIPINSEL1            */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_MASK                            0x30UL                                        /**< Bit mask for GPIO_EXTIPINSEL1               */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELH           */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_PIN8                            0x00000000UL                                  /**< Mode PIN8 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_PIN9                            0x00000001UL                                  /**< Mode PIN9 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_PIN10                           0x00000002UL                                  /**< Mode PIN10 for GPIO_EXTIPINSELH             */
#define _GPIO_EXTIPINSELH_EXTIPINSEL1_PIN11                           0x00000003UL                                  /**< Mode PIN11 for GPIO_EXTIPINSELH             */
#define GPIO_EXTIPINSELH_EXTIPINSEL1_DEFAULT                          (_GPIO_EXTIPINSELH_EXTIPINSEL1_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH   */
#define GPIO_EXTIPINSELH_EXTIPINSEL1_PIN8                             (_GPIO_EXTIPINSELH_EXTIPINSEL1_PIN8 << 4)     /**< Shifted mode PIN8 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL1_PIN9                             (_GPIO_EXTIPINSELH_EXTIPINSEL1_PIN9 << 4)     /**< Shifted mode PIN9 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL1_PIN10                            (_GPIO_EXTIPINSELH_EXTIPINSEL1_PIN10 << 4)    /**< Shifted mode PIN10 for GPIO_EXTIPINSELH     */
#define GPIO_EXTIPINSELH_EXTIPINSEL1_PIN11                            (_GPIO_EXTIPINSELH_EXTIPINSEL1_PIN11 << 4)    /**< Shifted mode PIN11 for GPIO_EXTIPINSELH     */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_SHIFT                           8                                             /**< Shift value for GPIO_EXTIPINSEL2            */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_MASK                            0x300UL                                       /**< Bit mask for GPIO_EXTIPINSEL2               */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELH           */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_PIN8                            0x00000000UL                                  /**< Mode PIN8 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_PIN9                            0x00000001UL                                  /**< Mode PIN9 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_PIN10                           0x00000002UL                                  /**< Mode PIN10 for GPIO_EXTIPINSELH             */
#define _GPIO_EXTIPINSELH_EXTIPINSEL2_PIN11                           0x00000003UL                                  /**< Mode PIN11 for GPIO_EXTIPINSELH             */
#define GPIO_EXTIPINSELH_EXTIPINSEL2_DEFAULT                          (_GPIO_EXTIPINSELH_EXTIPINSEL2_DEFAULT << 8)  /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH   */
#define GPIO_EXTIPINSELH_EXTIPINSEL2_PIN8                             (_GPIO_EXTIPINSELH_EXTIPINSEL2_PIN8 << 8)     /**< Shifted mode PIN8 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL2_PIN9                             (_GPIO_EXTIPINSELH_EXTIPINSEL2_PIN9 << 8)     /**< Shifted mode PIN9 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL2_PIN10                            (_GPIO_EXTIPINSELH_EXTIPINSEL2_PIN10 << 8)    /**< Shifted mode PIN10 for GPIO_EXTIPINSELH     */
#define GPIO_EXTIPINSELH_EXTIPINSEL2_PIN11                            (_GPIO_EXTIPINSELH_EXTIPINSEL2_PIN11 << 8)    /**< Shifted mode PIN11 for GPIO_EXTIPINSELH     */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_SHIFT                           12                                            /**< Shift value for GPIO_EXTIPINSEL3            */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_MASK                            0x3000UL                                      /**< Bit mask for GPIO_EXTIPINSEL3               */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_EXTIPINSELH           */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_PIN8                            0x00000000UL                                  /**< Mode PIN8 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_PIN9                            0x00000001UL                                  /**< Mode PIN9 for GPIO_EXTIPINSELH              */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_PIN10                           0x00000002UL                                  /**< Mode PIN10 for GPIO_EXTIPINSELH             */
#define _GPIO_EXTIPINSELH_EXTIPINSEL3_PIN11                           0x00000003UL                                  /**< Mode PIN11 for GPIO_EXTIPINSELH             */
#define GPIO_EXTIPINSELH_EXTIPINSEL3_DEFAULT                          (_GPIO_EXTIPINSELH_EXTIPINSEL3_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_EXTIPINSELH   */
#define GPIO_EXTIPINSELH_EXTIPINSEL3_PIN8                             (_GPIO_EXTIPINSELH_EXTIPINSEL3_PIN8 << 12)    /**< Shifted mode PIN8 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL3_PIN9                             (_GPIO_EXTIPINSELH_EXTIPINSEL3_PIN9 << 12)    /**< Shifted mode PIN9 for GPIO_EXTIPINSELH      */
#define GPIO_EXTIPINSELH_EXTIPINSEL3_PIN10                            (_GPIO_EXTIPINSELH_EXTIPINSEL3_PIN10 << 12)   /**< Shifted mode PIN10 for GPIO_EXTIPINSELH     */
#define GPIO_EXTIPINSELH_EXTIPINSEL3_PIN11                            (_GPIO_EXTIPINSELH_EXTIPINSEL3_PIN11 << 12)   /**< Shifted mode PIN11 for GPIO_EXTIPINSELH     */

/* Bit fields for GPIO EXTIRISE */
#define _GPIO_EXTIRISE_RESETVALUE                                     0x00000000UL                           /**< Default value for GPIO_EXTIRISE             */
#define _GPIO_EXTIRISE_MASK                                           0x00000FFFUL                           /**< Mask for GPIO_EXTIRISE                      */
#define _GPIO_EXTIRISE_EXTIRISE_SHIFT                                 0                                      /**< Shift value for GPIO_EXTIRISE               */
#define _GPIO_EXTIRISE_EXTIRISE_MASK                                  0xFFFUL                                /**< Bit mask for GPIO_EXTIRISE                  */
#define _GPIO_EXTIRISE_EXTIRISE_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for GPIO_EXTIRISE              */
#define GPIO_EXTIRISE_EXTIRISE_DEFAULT                                (_GPIO_EXTIRISE_EXTIRISE_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EXTIRISE      */

/* Bit fields for GPIO EXTIFALL */
#define _GPIO_EXTIFALL_RESETVALUE                                     0x00000000UL                           /**< Default value for GPIO_EXTIFALL             */
#define _GPIO_EXTIFALL_MASK                                           0x00000FFFUL                           /**< Mask for GPIO_EXTIFALL                      */
#define _GPIO_EXTIFALL_EXTIFALL_SHIFT                                 0                                      /**< Shift value for GPIO_EXTIFALL               */
#define _GPIO_EXTIFALL_EXTIFALL_MASK                                  0xFFFUL                                /**< Bit mask for GPIO_EXTIFALL                  */
#define _GPIO_EXTIFALL_EXTIFALL_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for GPIO_EXTIFALL              */
#define GPIO_EXTIFALL_EXTIFALL_DEFAULT                                (_GPIO_EXTIFALL_EXTIFALL_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EXTIFALL      */

/* Bit fields for GPIO IF */
#define _GPIO_IF_RESETVALUE                                           0x00000000UL                     /**< Default value for GPIO_IF                   */
#define _GPIO_IF_MASK                                                 0x0FFF0FFFUL                     /**< Mask for GPIO_IF                            */
#define GPIO_IF_EXTIF0                                                (0x1UL << 0)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF0_SHIFT                                         0                                /**< Shift value for GPIO_EXTIF0                 */
#define _GPIO_IF_EXTIF0_MASK                                          0x1UL                            /**< Bit mask for GPIO_EXTIF0                    */
#define _GPIO_IF_EXTIF0_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF0_DEFAULT                                        (_GPIO_IF_EXTIF0_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF1                                                (0x1UL << 1)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF1_SHIFT                                         1                                /**< Shift value for GPIO_EXTIF1                 */
#define _GPIO_IF_EXTIF1_MASK                                          0x2UL                            /**< Bit mask for GPIO_EXTIF1                    */
#define _GPIO_IF_EXTIF1_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF1_DEFAULT                                        (_GPIO_IF_EXTIF1_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF2                                                (0x1UL << 2)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF2_SHIFT                                         2                                /**< Shift value for GPIO_EXTIF2                 */
#define _GPIO_IF_EXTIF2_MASK                                          0x4UL                            /**< Bit mask for GPIO_EXTIF2                    */
#define _GPIO_IF_EXTIF2_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF2_DEFAULT                                        (_GPIO_IF_EXTIF2_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF3                                                (0x1UL << 3)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF3_SHIFT                                         3                                /**< Shift value for GPIO_EXTIF3                 */
#define _GPIO_IF_EXTIF3_MASK                                          0x8UL                            /**< Bit mask for GPIO_EXTIF3                    */
#define _GPIO_IF_EXTIF3_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF3_DEFAULT                                        (_GPIO_IF_EXTIF3_DEFAULT << 3)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF4                                                (0x1UL << 4)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF4_SHIFT                                         4                                /**< Shift value for GPIO_EXTIF4                 */
#define _GPIO_IF_EXTIF4_MASK                                          0x10UL                           /**< Bit mask for GPIO_EXTIF4                    */
#define _GPIO_IF_EXTIF4_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF4_DEFAULT                                        (_GPIO_IF_EXTIF4_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF5                                                (0x1UL << 5)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF5_SHIFT                                         5                                /**< Shift value for GPIO_EXTIF5                 */
#define _GPIO_IF_EXTIF5_MASK                                          0x20UL                           /**< Bit mask for GPIO_EXTIF5                    */
#define _GPIO_IF_EXTIF5_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF5_DEFAULT                                        (_GPIO_IF_EXTIF5_DEFAULT << 5)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF6                                                (0x1UL << 6)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF6_SHIFT                                         6                                /**< Shift value for GPIO_EXTIF6                 */
#define _GPIO_IF_EXTIF6_MASK                                          0x40UL                           /**< Bit mask for GPIO_EXTIF6                    */
#define _GPIO_IF_EXTIF6_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF6_DEFAULT                                        (_GPIO_IF_EXTIF6_DEFAULT << 6)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF7                                                (0x1UL << 7)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF7_SHIFT                                         7                                /**< Shift value for GPIO_EXTIF7                 */
#define _GPIO_IF_EXTIF7_MASK                                          0x80UL                           /**< Bit mask for GPIO_EXTIF7                    */
#define _GPIO_IF_EXTIF7_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF7_DEFAULT                                        (_GPIO_IF_EXTIF7_DEFAULT << 7)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF8                                                (0x1UL << 8)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF8_SHIFT                                         8                                /**< Shift value for GPIO_EXTIF8                 */
#define _GPIO_IF_EXTIF8_MASK                                          0x100UL                          /**< Bit mask for GPIO_EXTIF8                    */
#define _GPIO_IF_EXTIF8_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF8_DEFAULT                                        (_GPIO_IF_EXTIF8_DEFAULT << 8)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF9                                                (0x1UL << 9)                     /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF9_SHIFT                                         9                                /**< Shift value for GPIO_EXTIF9                 */
#define _GPIO_IF_EXTIF9_MASK                                          0x200UL                          /**< Bit mask for GPIO_EXTIF9                    */
#define _GPIO_IF_EXTIF9_DEFAULT                                       0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF9_DEFAULT                                        (_GPIO_IF_EXTIF9_DEFAULT << 9)   /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF10                                               (0x1UL << 10)                    /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF10_SHIFT                                        10                               /**< Shift value for GPIO_EXTIF10                */
#define _GPIO_IF_EXTIF10_MASK                                         0x400UL                          /**< Bit mask for GPIO_EXTIF10                   */
#define _GPIO_IF_EXTIF10_DEFAULT                                      0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF10_DEFAULT                                       (_GPIO_IF_EXTIF10_DEFAULT << 10) /**< Shifted mode DEFAULT for GPIO_IF            */
#define GPIO_IF_EXTIF11                                               (0x1UL << 11)                    /**< External Pin Flag                           */
#define _GPIO_IF_EXTIF11_SHIFT                                        11                               /**< Shift value for GPIO_EXTIF11                */
#define _GPIO_IF_EXTIF11_MASK                                         0x800UL                          /**< Bit mask for GPIO_EXTIF11                   */
#define _GPIO_IF_EXTIF11_DEFAULT                                      0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EXTIF11_DEFAULT                                       (_GPIO_IF_EXTIF11_DEFAULT << 11) /**< Shifted mode DEFAULT for GPIO_IF            */
#define _GPIO_IF_EM4WU_SHIFT                                          16                               /**< Shift value for GPIO_EM4WU                  */
#define _GPIO_IF_EM4WU_MASK                                           0xFFF0000UL                      /**< Bit mask for GPIO_EM4WU                     */
#define _GPIO_IF_EM4WU_DEFAULT                                        0x00000000UL                     /**< Mode DEFAULT for GPIO_IF                    */
#define GPIO_IF_EM4WU_DEFAULT                                         (_GPIO_IF_EM4WU_DEFAULT << 16)   /**< Shifted mode DEFAULT for GPIO_IF            */

/* Bit fields for GPIO IEN */
#define _GPIO_IEN_RESETVALUE                                          0x00000000UL                         /**< Default value for GPIO_IEN                  */
#define _GPIO_IEN_MASK                                                0x0FFF0FFFUL                         /**< Mask for GPIO_IEN                           */
#define GPIO_IEN_EXTIEN0                                              (0x1UL << 0)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN0_SHIFT                                       0                                    /**< Shift value for GPIO_EXTIEN0                */
#define _GPIO_IEN_EXTIEN0_MASK                                        0x1UL                                /**< Bit mask for GPIO_EXTIEN0                   */
#define _GPIO_IEN_EXTIEN0_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN0_DEFAULT                                      (_GPIO_IEN_EXTIEN0_DEFAULT << 0)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN1                                              (0x1UL << 1)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN1_SHIFT                                       1                                    /**< Shift value for GPIO_EXTIEN1                */
#define _GPIO_IEN_EXTIEN1_MASK                                        0x2UL                                /**< Bit mask for GPIO_EXTIEN1                   */
#define _GPIO_IEN_EXTIEN1_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN1_DEFAULT                                      (_GPIO_IEN_EXTIEN1_DEFAULT << 1)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN2                                              (0x1UL << 2)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN2_SHIFT                                       2                                    /**< Shift value for GPIO_EXTIEN2                */
#define _GPIO_IEN_EXTIEN2_MASK                                        0x4UL                                /**< Bit mask for GPIO_EXTIEN2                   */
#define _GPIO_IEN_EXTIEN2_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN2_DEFAULT                                      (_GPIO_IEN_EXTIEN2_DEFAULT << 2)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN3                                              (0x1UL << 3)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN3_SHIFT                                       3                                    /**< Shift value for GPIO_EXTIEN3                */
#define _GPIO_IEN_EXTIEN3_MASK                                        0x8UL                                /**< Bit mask for GPIO_EXTIEN3                   */
#define _GPIO_IEN_EXTIEN3_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN3_DEFAULT                                      (_GPIO_IEN_EXTIEN3_DEFAULT << 3)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN4                                              (0x1UL << 4)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN4_SHIFT                                       4                                    /**< Shift value for GPIO_EXTIEN4                */
#define _GPIO_IEN_EXTIEN4_MASK                                        0x10UL                               /**< Bit mask for GPIO_EXTIEN4                   */
#define _GPIO_IEN_EXTIEN4_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN4_DEFAULT                                      (_GPIO_IEN_EXTIEN4_DEFAULT << 4)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN5                                              (0x1UL << 5)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN5_SHIFT                                       5                                    /**< Shift value for GPIO_EXTIEN5                */
#define _GPIO_IEN_EXTIEN5_MASK                                        0x20UL                               /**< Bit mask for GPIO_EXTIEN5                   */
#define _GPIO_IEN_EXTIEN5_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN5_DEFAULT                                      (_GPIO_IEN_EXTIEN5_DEFAULT << 5)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN6                                              (0x1UL << 6)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN6_SHIFT                                       6                                    /**< Shift value for GPIO_EXTIEN6                */
#define _GPIO_IEN_EXTIEN6_MASK                                        0x40UL                               /**< Bit mask for GPIO_EXTIEN6                   */
#define _GPIO_IEN_EXTIEN6_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN6_DEFAULT                                      (_GPIO_IEN_EXTIEN6_DEFAULT << 6)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN7                                              (0x1UL << 7)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN7_SHIFT                                       7                                    /**< Shift value for GPIO_EXTIEN7                */
#define _GPIO_IEN_EXTIEN7_MASK                                        0x80UL                               /**< Bit mask for GPIO_EXTIEN7                   */
#define _GPIO_IEN_EXTIEN7_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN7_DEFAULT                                      (_GPIO_IEN_EXTIEN7_DEFAULT << 7)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN8                                              (0x1UL << 8)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN8_SHIFT                                       8                                    /**< Shift value for GPIO_EXTIEN8                */
#define _GPIO_IEN_EXTIEN8_MASK                                        0x100UL                              /**< Bit mask for GPIO_EXTIEN8                   */
#define _GPIO_IEN_EXTIEN8_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN8_DEFAULT                                      (_GPIO_IEN_EXTIEN8_DEFAULT << 8)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN9                                              (0x1UL << 9)                         /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN9_SHIFT                                       9                                    /**< Shift value for GPIO_EXTIEN9                */
#define _GPIO_IEN_EXTIEN9_MASK                                        0x200UL                              /**< Bit mask for GPIO_EXTIEN9                   */
#define _GPIO_IEN_EXTIEN9_DEFAULT                                     0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN9_DEFAULT                                      (_GPIO_IEN_EXTIEN9_DEFAULT << 9)     /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN10                                             (0x1UL << 10)                        /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN10_SHIFT                                      10                                   /**< Shift value for GPIO_EXTIEN10               */
#define _GPIO_IEN_EXTIEN10_MASK                                       0x400UL                              /**< Bit mask for GPIO_EXTIEN10                  */
#define _GPIO_IEN_EXTIEN10_DEFAULT                                    0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN10_DEFAULT                                     (_GPIO_IEN_EXTIEN10_DEFAULT << 10)   /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EXTIEN11                                             (0x1UL << 11)                        /**< External Pin Enable                         */
#define _GPIO_IEN_EXTIEN11_SHIFT                                      11                                   /**< Shift value for GPIO_EXTIEN11               */
#define _GPIO_IEN_EXTIEN11_MASK                                       0x800UL                              /**< Bit mask for GPIO_EXTIEN11                  */
#define _GPIO_IEN_EXTIEN11_DEFAULT                                    0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EXTIEN11_DEFAULT                                     (_GPIO_IEN_EXTIEN11_DEFAULT << 11)   /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN0                                            (0x1UL << 16)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN0_SHIFT                                     16                                   /**< Shift value for GPIO_EM4WUIEN0              */
#define _GPIO_IEN_EM4WUIEN0_MASK                                      0x10000UL                            /**< Bit mask for GPIO_EM4WUIEN0                 */
#define _GPIO_IEN_EM4WUIEN0_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN0_DEFAULT                                    (_GPIO_IEN_EM4WUIEN0_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN1                                            (0x1UL << 17)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN1_SHIFT                                     17                                   /**< Shift value for GPIO_EM4WUIEN1              */
#define _GPIO_IEN_EM4WUIEN1_MASK                                      0x20000UL                            /**< Bit mask for GPIO_EM4WUIEN1                 */
#define _GPIO_IEN_EM4WUIEN1_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN1_DEFAULT                                    (_GPIO_IEN_EM4WUIEN1_DEFAULT << 17)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN2                                            (0x1UL << 18)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN2_SHIFT                                     18                                   /**< Shift value for GPIO_EM4WUIEN2              */
#define _GPIO_IEN_EM4WUIEN2_MASK                                      0x40000UL                            /**< Bit mask for GPIO_EM4WUIEN2                 */
#define _GPIO_IEN_EM4WUIEN2_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN2_DEFAULT                                    (_GPIO_IEN_EM4WUIEN2_DEFAULT << 18)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN3                                            (0x1UL << 19)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN3_SHIFT                                     19                                   /**< Shift value for GPIO_EM4WUIEN3              */
#define _GPIO_IEN_EM4WUIEN3_MASK                                      0x80000UL                            /**< Bit mask for GPIO_EM4WUIEN3                 */
#define _GPIO_IEN_EM4WUIEN3_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN3_DEFAULT                                    (_GPIO_IEN_EM4WUIEN3_DEFAULT << 19)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN4                                            (0x1UL << 20)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN4_SHIFT                                     20                                   /**< Shift value for GPIO_EM4WUIEN4              */
#define _GPIO_IEN_EM4WUIEN4_MASK                                      0x100000UL                           /**< Bit mask for GPIO_EM4WUIEN4                 */
#define _GPIO_IEN_EM4WUIEN4_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN4_DEFAULT                                    (_GPIO_IEN_EM4WUIEN4_DEFAULT << 20)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN5                                            (0x1UL << 21)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN5_SHIFT                                     21                                   /**< Shift value for GPIO_EM4WUIEN5              */
#define _GPIO_IEN_EM4WUIEN5_MASK                                      0x200000UL                           /**< Bit mask for GPIO_EM4WUIEN5                 */
#define _GPIO_IEN_EM4WUIEN5_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN5_DEFAULT                                    (_GPIO_IEN_EM4WUIEN5_DEFAULT << 21)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN6                                            (0x1UL << 22)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN6_SHIFT                                     22                                   /**< Shift value for GPIO_EM4WUIEN6              */
#define _GPIO_IEN_EM4WUIEN6_MASK                                      0x400000UL                           /**< Bit mask for GPIO_EM4WUIEN6                 */
#define _GPIO_IEN_EM4WUIEN6_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN6_DEFAULT                                    (_GPIO_IEN_EM4WUIEN6_DEFAULT << 22)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN7                                            (0x1UL << 23)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN7_SHIFT                                     23                                   /**< Shift value for GPIO_EM4WUIEN7              */
#define _GPIO_IEN_EM4WUIEN7_MASK                                      0x800000UL                           /**< Bit mask for GPIO_EM4WUIEN7                 */
#define _GPIO_IEN_EM4WUIEN7_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN7_DEFAULT                                    (_GPIO_IEN_EM4WUIEN7_DEFAULT << 23)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN8                                            (0x1UL << 24)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN8_SHIFT                                     24                                   /**< Shift value for GPIO_EM4WUIEN8              */
#define _GPIO_IEN_EM4WUIEN8_MASK                                      0x1000000UL                          /**< Bit mask for GPIO_EM4WUIEN8                 */
#define _GPIO_IEN_EM4WUIEN8_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN8_DEFAULT                                    (_GPIO_IEN_EM4WUIEN8_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN9                                            (0x1UL << 25)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN9_SHIFT                                     25                                   /**< Shift value for GPIO_EM4WUIEN9              */
#define _GPIO_IEN_EM4WUIEN9_MASK                                      0x2000000UL                          /**< Bit mask for GPIO_EM4WUIEN9                 */
#define _GPIO_IEN_EM4WUIEN9_DEFAULT                                   0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN9_DEFAULT                                    (_GPIO_IEN_EM4WUIEN9_DEFAULT << 25)  /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN10                                           (0x1UL << 26)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN10_SHIFT                                    26                                   /**< Shift value for GPIO_EM4WUIEN10             */
#define _GPIO_IEN_EM4WUIEN10_MASK                                     0x4000000UL                          /**< Bit mask for GPIO_EM4WUIEN10                */
#define _GPIO_IEN_EM4WUIEN10_DEFAULT                                  0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN10_DEFAULT                                   (_GPIO_IEN_EM4WUIEN10_DEFAULT << 26) /**< Shifted mode DEFAULT for GPIO_IEN           */
#define GPIO_IEN_EM4WUIEN11                                           (0x1UL << 27)                        /**< EM4 Wake Up Interrupt En                    */
#define _GPIO_IEN_EM4WUIEN11_SHIFT                                    27                                   /**< Shift value for GPIO_EM4WUIEN11             */
#define _GPIO_IEN_EM4WUIEN11_MASK                                     0x8000000UL                          /**< Bit mask for GPIO_EM4WUIEN11                */
#define _GPIO_IEN_EM4WUIEN11_DEFAULT                                  0x00000000UL                         /**< Mode DEFAULT for GPIO_IEN                   */
#define GPIO_IEN_EM4WUIEN11_DEFAULT                                   (_GPIO_IEN_EM4WUIEN11_DEFAULT << 27) /**< Shifted mode DEFAULT for GPIO_IEN           */

/* Bit fields for GPIO EM4WUEN */
#define _GPIO_EM4WUEN_RESETVALUE                                      0x00000000UL                          /**< Default value for GPIO_EM4WUEN              */
#define _GPIO_EM4WUEN_MASK                                            0x0FFF0000UL                          /**< Mask for GPIO_EM4WUEN                       */
#define _GPIO_EM4WUEN_EM4WUEN_SHIFT                                   16                                    /**< Shift value for GPIO_EM4WUEN                */
#define _GPIO_EM4WUEN_EM4WUEN_MASK                                    0xFFF0000UL                           /**< Bit mask for GPIO_EM4WUEN                   */
#define _GPIO_EM4WUEN_EM4WUEN_DEFAULT                                 0x00000000UL                          /**< Mode DEFAULT for GPIO_EM4WUEN               */
#define GPIO_EM4WUEN_EM4WUEN_DEFAULT                                  (_GPIO_EM4WUEN_EM4WUEN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EM4WUEN       */

/* Bit fields for GPIO EM4WUPOL */
#define _GPIO_EM4WUPOL_RESETVALUE                                     0x00000000UL                            /**< Default value for GPIO_EM4WUPOL             */
#define _GPIO_EM4WUPOL_MASK                                           0x0FFF0000UL                            /**< Mask for GPIO_EM4WUPOL                      */
#define _GPIO_EM4WUPOL_EM4WUPOL_SHIFT                                 16                                      /**< Shift value for GPIO_EM4WUPOL               */
#define _GPIO_EM4WUPOL_EM4WUPOL_MASK                                  0xFFF0000UL                             /**< Bit mask for GPIO_EM4WUPOL                  */
#define _GPIO_EM4WUPOL_EM4WUPOL_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_EM4WUPOL              */
#define GPIO_EM4WUPOL_EM4WUPOL_DEFAULT                                (_GPIO_EM4WUPOL_EM4WUPOL_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EM4WUPOL      */

/* Bit fields for GPIO DBGROUTEPEN */
#define _GPIO_DBGROUTEPEN_RESETVALUE                                  0x0000000FUL                                 /**< Default value for GPIO_DBGROUTEPEN          */
#define _GPIO_DBGROUTEPEN_MASK                                        0x0000000FUL                                 /**< Mask for GPIO_DBGROUTEPEN                   */
#define GPIO_DBGROUTEPEN_SWCLKTCKPEN                                  (0x1UL << 0)                                 /**< Route Pin Enable                            */
#define _GPIO_DBGROUTEPEN_SWCLKTCKPEN_SHIFT                           0                                            /**< Shift value for GPIO_SWCLKTCKPEN            */
#define _GPIO_DBGROUTEPEN_SWCLKTCKPEN_MASK                            0x1UL                                        /**< Bit mask for GPIO_SWCLKTCKPEN               */
#define _GPIO_DBGROUTEPEN_SWCLKTCKPEN_DEFAULT                         0x00000001UL                                 /**< Mode DEFAULT for GPIO_DBGROUTEPEN           */
#define GPIO_DBGROUTEPEN_SWCLKTCKPEN_DEFAULT                          (_GPIO_DBGROUTEPEN_SWCLKTCKPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBGROUTEPEN   */
#define GPIO_DBGROUTEPEN_SWDIOTMSPEN                                  (0x1UL << 1)                                 /**< Route Location 0                            */
#define _GPIO_DBGROUTEPEN_SWDIOTMSPEN_SHIFT                           1                                            /**< Shift value for GPIO_SWDIOTMSPEN            */
#define _GPIO_DBGROUTEPEN_SWDIOTMSPEN_MASK                            0x2UL                                        /**< Bit mask for GPIO_SWDIOTMSPEN               */
#define _GPIO_DBGROUTEPEN_SWDIOTMSPEN_DEFAULT                         0x00000001UL                                 /**< Mode DEFAULT for GPIO_DBGROUTEPEN           */
#define GPIO_DBGROUTEPEN_SWDIOTMSPEN_DEFAULT                          (_GPIO_DBGROUTEPEN_SWDIOTMSPEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_DBGROUTEPEN   */
#define GPIO_DBGROUTEPEN_TDOPEN                                       (0x1UL << 2)                                 /**< JTAG Test Debug Output Pin Enable           */
#define _GPIO_DBGROUTEPEN_TDOPEN_SHIFT                                2                                            /**< Shift value for GPIO_TDOPEN                 */
#define _GPIO_DBGROUTEPEN_TDOPEN_MASK                                 0x4UL                                        /**< Bit mask for GPIO_TDOPEN                    */
#define _GPIO_DBGROUTEPEN_TDOPEN_DEFAULT                              0x00000001UL                                 /**< Mode DEFAULT for GPIO_DBGROUTEPEN           */
#define GPIO_DBGROUTEPEN_TDOPEN_DEFAULT                               (_GPIO_DBGROUTEPEN_TDOPEN_DEFAULT << 2)      /**< Shifted mode DEFAULT for GPIO_DBGROUTEPEN   */
#define GPIO_DBGROUTEPEN_TDIPEN                                       (0x1UL << 3)                                 /**< JTAG Test Debug Input Pin Enable            */
#define _GPIO_DBGROUTEPEN_TDIPEN_SHIFT                                3                                            /**< Shift value for GPIO_TDIPEN                 */
#define _GPIO_DBGROUTEPEN_TDIPEN_MASK                                 0x8UL                                        /**< Bit mask for GPIO_TDIPEN                    */
#define _GPIO_DBGROUTEPEN_TDIPEN_DEFAULT                              0x00000001UL                                 /**< Mode DEFAULT for GPIO_DBGROUTEPEN           */
#define GPIO_DBGROUTEPEN_TDIPEN_DEFAULT                               (_GPIO_DBGROUTEPEN_TDIPEN_DEFAULT << 3)      /**< Shifted mode DEFAULT for GPIO_DBGROUTEPEN   */

/* Bit fields for GPIO TRACEROUTEPEN */
#define _GPIO_TRACEROUTEPEN_RESETVALUE                                0x00000000UL                                     /**< Default value for GPIO_TRACEROUTEPEN        */
#define _GPIO_TRACEROUTEPEN_MASK                                      0x0000003FUL                                     /**< Mask for GPIO_TRACEROUTEPEN                 */
#define GPIO_TRACEROUTEPEN_SWVPEN                                     (0x1UL << 0)                                     /**< Serial Wire Viewer Output Pin Enable        */
#define _GPIO_TRACEROUTEPEN_SWVPEN_SHIFT                              0                                                /**< Shift value for GPIO_SWVPEN                 */
#define _GPIO_TRACEROUTEPEN_SWVPEN_MASK                               0x1UL                                            /**< Bit mask for GPIO_SWVPEN                    */
#define _GPIO_TRACEROUTEPEN_SWVPEN_DEFAULT                            0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_SWVPEN_DEFAULT                             (_GPIO_TRACEROUTEPEN_SWVPEN_DEFAULT << 0)        /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */
#define GPIO_TRACEROUTEPEN_TRACECLKPEN                                (0x1UL << 1)                                     /**< Trace Clk Pin Enable                        */
#define _GPIO_TRACEROUTEPEN_TRACECLKPEN_SHIFT                         1                                                /**< Shift value for GPIO_TRACECLKPEN            */
#define _GPIO_TRACEROUTEPEN_TRACECLKPEN_MASK                          0x2UL                                            /**< Bit mask for GPIO_TRACECLKPEN               */
#define _GPIO_TRACEROUTEPEN_TRACECLKPEN_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_TRACECLKPEN_DEFAULT                        (_GPIO_TRACEROUTEPEN_TRACECLKPEN_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */
#define GPIO_TRACEROUTEPEN_TRACEDATA0PEN                              (0x1UL << 2)                                     /**< Trace Data0 Pin Enable                      */
#define _GPIO_TRACEROUTEPEN_TRACEDATA0PEN_SHIFT                       2                                                /**< Shift value for GPIO_TRACEDATA0PEN          */
#define _GPIO_TRACEROUTEPEN_TRACEDATA0PEN_MASK                        0x4UL                                            /**< Bit mask for GPIO_TRACEDATA0PEN             */
#define _GPIO_TRACEROUTEPEN_TRACEDATA0PEN_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_TRACEDATA0PEN_DEFAULT                      (_GPIO_TRACEROUTEPEN_TRACEDATA0PEN_DEFAULT << 2) /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */
#define GPIO_TRACEROUTEPEN_TRACEDATA1PEN                              (0x1UL << 3)                                     /**< Trace Data1 Pin Enable                      */
#define _GPIO_TRACEROUTEPEN_TRACEDATA1PEN_SHIFT                       3                                                /**< Shift value for GPIO_TRACEDATA1PEN          */
#define _GPIO_TRACEROUTEPEN_TRACEDATA1PEN_MASK                        0x8UL                                            /**< Bit mask for GPIO_TRACEDATA1PEN             */
#define _GPIO_TRACEROUTEPEN_TRACEDATA1PEN_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_TRACEDATA1PEN_DEFAULT                      (_GPIO_TRACEROUTEPEN_TRACEDATA1PEN_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */
#define GPIO_TRACEROUTEPEN_TRACEDATA2PEN                              (0x1UL << 4)                                     /**< Trace Data2 Pin Enable                      */
#define _GPIO_TRACEROUTEPEN_TRACEDATA2PEN_SHIFT                       4                                                /**< Shift value for GPIO_TRACEDATA2PEN          */
#define _GPIO_TRACEROUTEPEN_TRACEDATA2PEN_MASK                        0x10UL                                           /**< Bit mask for GPIO_TRACEDATA2PEN             */
#define _GPIO_TRACEROUTEPEN_TRACEDATA2PEN_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_TRACEDATA2PEN_DEFAULT                      (_GPIO_TRACEROUTEPEN_TRACEDATA2PEN_DEFAULT << 4) /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */
#define GPIO_TRACEROUTEPEN_TRACEDATA3PEN                              (0x1UL << 5)                                     /**< Trace Data3 Pin Enable                      */
#define _GPIO_TRACEROUTEPEN_TRACEDATA3PEN_SHIFT                       5                                                /**< Shift value for GPIO_TRACEDATA3PEN          */
#define _GPIO_TRACEROUTEPEN_TRACEDATA3PEN_MASK                        0x20UL                                           /**< Bit mask for GPIO_TRACEDATA3PEN             */
#define _GPIO_TRACEROUTEPEN_TRACEDATA3PEN_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_TRACEROUTEPEN         */
#define GPIO_TRACEROUTEPEN_TRACEDATA3PEN_DEFAULT                      (_GPIO_TRACEROUTEPEN_TRACEDATA3PEN_DEFAULT << 5) /**< Shifted mode DEFAULT for GPIO_TRACEROUTEPEN */

/* Bit fields for GPIO_ACMP ROUTEEN */
#define _GPIO_ACMP_ROUTEEN_RESETVALUE                                 0x00000000UL                                 /**< Default value for GPIO_ACMP_ROUTEEN         */
#define _GPIO_ACMP_ROUTEEN_MASK                                       0x00000001UL                                 /**< Mask for GPIO_ACMP_ROUTEEN                  */
#define GPIO_ACMP_ROUTEEN_ACMPOUTPEN                                  (0x1UL << 0)                                 /**< ACMPOUT pin enable control bit              */
#define _GPIO_ACMP_ROUTEEN_ACMPOUTPEN_SHIFT                           0                                            /**< Shift value for GPIO_ACMPOUTPEN             */
#define _GPIO_ACMP_ROUTEEN_ACMPOUTPEN_MASK                            0x1UL                                        /**< Bit mask for GPIO_ACMPOUTPEN                */
#define _GPIO_ACMP_ROUTEEN_ACMPOUTPEN_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_ACMP_ROUTEEN          */
#define GPIO_ACMP_ROUTEEN_ACMPOUTPEN_DEFAULT                          (_GPIO_ACMP_ROUTEEN_ACMPOUTPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_ACMP_ROUTEEN  */

/* Bit fields for GPIO_ACMP ACMPOUTROUTE */
#define _GPIO_ACMP_ACMPOUTROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_ACMP_ACMPOUTROUTE    */
#define _GPIO_ACMP_ACMPOUTROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_ACMP_ACMPOUTROUTE             */
#define _GPIO_ACMP_ACMPOUTROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_ACMP_ACMPOUTROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_ACMP_ACMPOUTROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_ACMP_ACMPOUTROUTE     */
#define GPIO_ACMP_ACMPOUTROUTE_PORT_DEFAULT                           (_GPIO_ACMP_ACMPOUTROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_ACMP_ACMPOUTROUTE*/
#define _GPIO_ACMP_ACMPOUTROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_ACMP_ACMPOUTROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_ACMP_ACMPOUTROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_ACMP_ACMPOUTROUTE     */
#define GPIO_ACMP_ACMPOUTROUTE_PIN_DEFAULT                            (_GPIO_ACMP_ACMPOUTROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_ACMP_ACMPOUTROUTE*/

/* Bit fields for GPIO_CMU ROUTEEN */
#define _GPIO_CMU_ROUTEEN_RESETVALUE                                  0x00000000UL                                /**< Default value for GPIO_CMU_ROUTEEN          */
#define _GPIO_CMU_ROUTEEN_MASK                                        0x0000000FUL                                /**< Mask for GPIO_CMU_ROUTEEN                   */
#define GPIO_CMU_ROUTEEN_CLKOUT0PEN                                   (0x1UL << 0)                                /**< CLKOUT0 pin enable control bit              */
#define _GPIO_CMU_ROUTEEN_CLKOUT0PEN_SHIFT                            0                                           /**< Shift value for GPIO_CLKOUT0PEN             */
#define _GPIO_CMU_ROUTEEN_CLKOUT0PEN_MASK                             0x1UL                                       /**< Bit mask for GPIO_CLKOUT0PEN                */
#define _GPIO_CMU_ROUTEEN_CLKOUT0PEN_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_CMU_ROUTEEN           */
#define GPIO_CMU_ROUTEEN_CLKOUT0PEN_DEFAULT                           (_GPIO_CMU_ROUTEEN_CLKOUT0PEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_CMU_ROUTEEN   */
#define GPIO_CMU_ROUTEEN_CLKOUT1PEN                                   (0x1UL << 1)                                /**< CLKOUT1 pin enable control bit              */
#define _GPIO_CMU_ROUTEEN_CLKOUT1PEN_SHIFT                            1                                           /**< Shift value for GPIO_CLKOUT1PEN             */
#define _GPIO_CMU_ROUTEEN_CLKOUT1PEN_MASK                             0x2UL                                       /**< Bit mask for GPIO_CLKOUT1PEN                */
#define _GPIO_CMU_ROUTEEN_CLKOUT1PEN_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_CMU_ROUTEEN           */
#define GPIO_CMU_ROUTEEN_CLKOUT1PEN_DEFAULT                           (_GPIO_CMU_ROUTEEN_CLKOUT1PEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_CMU_ROUTEEN   */
#define GPIO_CMU_ROUTEEN_CLKOUT2PEN                                   (0x1UL << 2)                                /**< CLKOUT2 pin enable control bit              */
#define _GPIO_CMU_ROUTEEN_CLKOUT2PEN_SHIFT                            2                                           /**< Shift value for GPIO_CLKOUT2PEN             */
#define _GPIO_CMU_ROUTEEN_CLKOUT2PEN_MASK                             0x4UL                                       /**< Bit mask for GPIO_CLKOUT2PEN                */
#define _GPIO_CMU_ROUTEEN_CLKOUT2PEN_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_CMU_ROUTEEN           */
#define GPIO_CMU_ROUTEEN_CLKOUT2PEN_DEFAULT                           (_GPIO_CMU_ROUTEEN_CLKOUT2PEN_DEFAULT << 2) /**< Shifted mode DEFAULT for GPIO_CMU_ROUTEEN   */

/* Bit fields for GPIO_CMU CLKIN0ROUTE */
#define _GPIO_CMU_CLKIN0ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_CMU_CLKIN0ROUTE      */
#define _GPIO_CMU_CLKIN0ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_CMU_CLKIN0ROUTE               */
#define _GPIO_CMU_CLKIN0ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_CMU_CLKIN0ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_CMU_CLKIN0ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_CMU_CLKIN0ROUTE       */
#define GPIO_CMU_CLKIN0ROUTE_PORT_DEFAULT                             (_GPIO_CMU_CLKIN0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_CMU_CLKIN0ROUTE*/
#define _GPIO_CMU_CLKIN0ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_CMU_CLKIN0ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_CMU_CLKIN0ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_CMU_CLKIN0ROUTE       */
#define GPIO_CMU_CLKIN0ROUTE_PIN_DEFAULT                              (_GPIO_CMU_CLKIN0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CMU_CLKIN0ROUTE*/

/* Bit fields for GPIO_CMU CLKOUT0ROUTE */
#define _GPIO_CMU_CLKOUT0ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_CMU_CLKOUT0ROUTE     */
#define _GPIO_CMU_CLKOUT0ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_CMU_CLKOUT0ROUTE              */
#define _GPIO_CMU_CLKOUT0ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_CMU_CLKOUT0ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_CMU_CLKOUT0ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT0ROUTE      */
#define GPIO_CMU_CLKOUT0ROUTE_PORT_DEFAULT                            (_GPIO_CMU_CLKOUT0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT0ROUTE*/
#define _GPIO_CMU_CLKOUT0ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_CMU_CLKOUT0ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_CMU_CLKOUT0ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT0ROUTE      */
#define GPIO_CMU_CLKOUT0ROUTE_PIN_DEFAULT                             (_GPIO_CMU_CLKOUT0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT0ROUTE*/

/* Bit fields for GPIO_CMU CLKOUT1ROUTE */
#define _GPIO_CMU_CLKOUT1ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_CMU_CLKOUT1ROUTE     */
#define _GPIO_CMU_CLKOUT1ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_CMU_CLKOUT1ROUTE              */
#define _GPIO_CMU_CLKOUT1ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_CMU_CLKOUT1ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_CMU_CLKOUT1ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT1ROUTE      */
#define GPIO_CMU_CLKOUT1ROUTE_PORT_DEFAULT                            (_GPIO_CMU_CLKOUT1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT1ROUTE*/
#define _GPIO_CMU_CLKOUT1ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_CMU_CLKOUT1ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_CMU_CLKOUT1ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT1ROUTE      */
#define GPIO_CMU_CLKOUT1ROUTE_PIN_DEFAULT                             (_GPIO_CMU_CLKOUT1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT1ROUTE*/

/* Bit fields for GPIO_CMU CLKOUT2ROUTE */
#define _GPIO_CMU_CLKOUT2ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_CMU_CLKOUT2ROUTE     */
#define _GPIO_CMU_CLKOUT2ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_CMU_CLKOUT2ROUTE              */
#define _GPIO_CMU_CLKOUT2ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_CMU_CLKOUT2ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_CMU_CLKOUT2ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT2ROUTE      */
#define GPIO_CMU_CLKOUT2ROUTE_PORT_DEFAULT                            (_GPIO_CMU_CLKOUT2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT2ROUTE*/
#define _GPIO_CMU_CLKOUT2ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_CMU_CLKOUT2ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_CMU_CLKOUT2ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_CMU_CLKOUT2ROUTE      */
#define GPIO_CMU_CLKOUT2ROUTE_PIN_DEFAULT                             (_GPIO_CMU_CLKOUT2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_CMU_CLKOUT2ROUTE*/

/* Bit fields for GPIO_DCDC ROUTEEN */
#define _GPIO_DCDC_ROUTEEN_RESETVALUE                                 0x00000000UL                                        /**< Default value for GPIO_DCDC_ROUTEEN         */
#define _GPIO_DCDC_ROUTEEN_MASK                                       0x00000003UL                                        /**< Mask for GPIO_DCDC_ROUTEEN                  */
#define GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN                           (0x1UL << 0)                                        /**< DCDCCOREHIDDEN pin enable control bit       */
#define _GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN_SHIFT                    0                                                   /**< Shift value for GPIO_DCDCCOREHIDDENPEN      */
#define _GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN_MASK                     0x1UL                                               /**< Bit mask for GPIO_DCDCCOREHIDDENPEN         */
#define _GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN_DEFAULT                  0x00000000UL                                        /**< Mode DEFAULT for GPIO_DCDC_ROUTEEN          */
#define GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN_DEFAULT                   (_GPIO_DCDC_ROUTEEN_DCDCCOREHIDDENPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DCDC_ROUTEEN  */

/* Bit fields for GPIO_DCDC DCDCCOREHIDDENROUTE */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DCDC_DCDCCOREHIDDENROUTE*/
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DCDC_DCDCCOREHIDDENROUTE      */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DCDC_DCDCCOREHIDDENROUTE*/
#define GPIO_DCDC_DCDCCOREHIDDENROUTE_PORT_DEFAULT                    (_GPIO_DCDC_DCDCCOREHIDDENROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DCDC_DCDCCOREHIDDENROUTE*/
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DCDC_DCDCCOREHIDDENROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DCDC_DCDCCOREHIDDENROUTE*/
#define GPIO_DCDC_DCDCCOREHIDDENROUTE_PIN_DEFAULT                     (_GPIO_DCDC_DCDCCOREHIDDENROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DCDC_DCDCCOREHIDDENROUTE*/

/* Bit fields for GPIO_EUSART ROUTEEN */
#define _GPIO_EUSART_ROUTEEN_RESETVALUE                               0x00000000UL                                /**< Default value for GPIO_EUSART_ROUTEEN       */
#define _GPIO_EUSART_ROUTEEN_MASK                                     0x0000001FUL                                /**< Mask for GPIO_EUSART_ROUTEEN                */
#define GPIO_EUSART_ROUTEEN_CSPEN                                     (0x1UL << 0)                                /**< CS pin enable control bit                   */
#define _GPIO_EUSART_ROUTEEN_CSPEN_SHIFT                              0                                           /**< Shift value for GPIO_CSPEN                  */
#define _GPIO_EUSART_ROUTEEN_CSPEN_MASK                               0x1UL                                       /**< Bit mask for GPIO_CSPEN                     */
#define _GPIO_EUSART_ROUTEEN_CSPEN_DEFAULT                            0x00000000UL                                /**< Mode DEFAULT for GPIO_EUSART_ROUTEEN        */
#define GPIO_EUSART_ROUTEEN_CSPEN_DEFAULT                             (_GPIO_EUSART_ROUTEEN_CSPEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_EUSART_ROUTEEN*/
#define GPIO_EUSART_ROUTEEN_RTSPEN                                    (0x1UL << 1)                                /**< RTS pin enable control bit                  */
#define _GPIO_EUSART_ROUTEEN_RTSPEN_SHIFT                             1                                           /**< Shift value for GPIO_RTSPEN                 */
#define _GPIO_EUSART_ROUTEEN_RTSPEN_MASK                              0x2UL                                       /**< Bit mask for GPIO_RTSPEN                    */
#define _GPIO_EUSART_ROUTEEN_RTSPEN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_EUSART_ROUTEEN        */
#define GPIO_EUSART_ROUTEEN_RTSPEN_DEFAULT                            (_GPIO_EUSART_ROUTEEN_RTSPEN_DEFAULT << 1)  /**< Shifted mode DEFAULT for GPIO_EUSART_ROUTEEN*/
#define GPIO_EUSART_ROUTEEN_RXPEN                                     (0x1UL << 2)                                /**< RX pin enable control bit                   */
#define _GPIO_EUSART_ROUTEEN_RXPEN_SHIFT                              2                                           /**< Shift value for GPIO_RXPEN                  */
#define _GPIO_EUSART_ROUTEEN_RXPEN_MASK                               0x4UL                                       /**< Bit mask for GPIO_RXPEN                     */
#define _GPIO_EUSART_ROUTEEN_RXPEN_DEFAULT                            0x00000000UL                                /**< Mode DEFAULT for GPIO_EUSART_ROUTEEN        */
#define GPIO_EUSART_ROUTEEN_RXPEN_DEFAULT                             (_GPIO_EUSART_ROUTEEN_RXPEN_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_EUSART_ROUTEEN*/
#define GPIO_EUSART_ROUTEEN_SCLKPEN                                   (0x1UL << 3)                                /**< SCLK pin enable control bit                 */
#define _GPIO_EUSART_ROUTEEN_SCLKPEN_SHIFT                            3                                           /**< Shift value for GPIO_SCLKPEN                */
#define _GPIO_EUSART_ROUTEEN_SCLKPEN_MASK                             0x8UL                                       /**< Bit mask for GPIO_SCLKPEN                   */
#define _GPIO_EUSART_ROUTEEN_SCLKPEN_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_EUSART_ROUTEEN        */
#define GPIO_EUSART_ROUTEEN_SCLKPEN_DEFAULT                           (_GPIO_EUSART_ROUTEEN_SCLKPEN_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_EUSART_ROUTEEN*/
#define GPIO_EUSART_ROUTEEN_TXPEN                                     (0x1UL << 4)                                /**< TX pin enable control bit                   */
#define _GPIO_EUSART_ROUTEEN_TXPEN_SHIFT                              4                                           /**< Shift value for GPIO_TXPEN                  */
#define _GPIO_EUSART_ROUTEEN_TXPEN_MASK                               0x10UL                                      /**< Bit mask for GPIO_TXPEN                     */
#define _GPIO_EUSART_ROUTEEN_TXPEN_DEFAULT                            0x00000000UL                                /**< Mode DEFAULT for GPIO_EUSART_ROUTEEN        */
#define GPIO_EUSART_ROUTEEN_TXPEN_DEFAULT                             (_GPIO_EUSART_ROUTEEN_TXPEN_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_EUSART_ROUTEEN*/

/* Bit fields for GPIO_EUSART CSROUTE */
#define _GPIO_EUSART_CSROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_EUSART_CSROUTE       */
#define _GPIO_EUSART_CSROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_EUSART_CSROUTE                */
#define _GPIO_EUSART_CSROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_CSROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_CSROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_CSROUTE        */
#define GPIO_EUSART_CSROUTE_PORT_DEFAULT                              (_GPIO_EUSART_CSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_CSROUTE*/
#define _GPIO_EUSART_CSROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_CSROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_CSROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_CSROUTE        */
#define GPIO_EUSART_CSROUTE_PIN_DEFAULT                               (_GPIO_EUSART_CSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_CSROUTE*/

/* Bit fields for GPIO_EUSART CTSROUTE */
#define _GPIO_EUSART_CTSROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_EUSART_CTSROUTE      */
#define _GPIO_EUSART_CTSROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_EUSART_CTSROUTE               */
#define _GPIO_EUSART_CTSROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_CTSROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_CTSROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_EUSART_CTSROUTE       */
#define GPIO_EUSART_CTSROUTE_PORT_DEFAULT                             (_GPIO_EUSART_CTSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_CTSROUTE*/
#define _GPIO_EUSART_CTSROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_CTSROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_CTSROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EUSART_CTSROUTE       */
#define GPIO_EUSART_CTSROUTE_PIN_DEFAULT                              (_GPIO_EUSART_CTSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_CTSROUTE*/

/* Bit fields for GPIO_EUSART RTSROUTE */
#define _GPIO_EUSART_RTSROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_EUSART_RTSROUTE      */
#define _GPIO_EUSART_RTSROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_EUSART_RTSROUTE               */
#define _GPIO_EUSART_RTSROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_RTSROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_RTSROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_EUSART_RTSROUTE       */
#define GPIO_EUSART_RTSROUTE_PORT_DEFAULT                             (_GPIO_EUSART_RTSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_RTSROUTE*/
#define _GPIO_EUSART_RTSROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_RTSROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_RTSROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_EUSART_RTSROUTE       */
#define GPIO_EUSART_RTSROUTE_PIN_DEFAULT                              (_GPIO_EUSART_RTSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_RTSROUTE*/

/* Bit fields for GPIO_EUSART RXROUTE */
#define _GPIO_EUSART_RXROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_EUSART_RXROUTE       */
#define _GPIO_EUSART_RXROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_EUSART_RXROUTE                */
#define _GPIO_EUSART_RXROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_RXROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_RXROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_RXROUTE        */
#define GPIO_EUSART_RXROUTE_PORT_DEFAULT                              (_GPIO_EUSART_RXROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_RXROUTE*/
#define _GPIO_EUSART_RXROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_RXROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_RXROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_RXROUTE        */
#define GPIO_EUSART_RXROUTE_PIN_DEFAULT                               (_GPIO_EUSART_RXROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_RXROUTE*/

/* Bit fields for GPIO_EUSART SCLKROUTE */
#define _GPIO_EUSART_SCLKROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_EUSART_SCLKROUTE     */
#define _GPIO_EUSART_SCLKROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_EUSART_SCLKROUTE              */
#define _GPIO_EUSART_SCLKROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_SCLKROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_SCLKROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_EUSART_SCLKROUTE      */
#define GPIO_EUSART_SCLKROUTE_PORT_DEFAULT                            (_GPIO_EUSART_SCLKROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_SCLKROUTE*/
#define _GPIO_EUSART_SCLKROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_SCLKROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_SCLKROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_EUSART_SCLKROUTE      */
#define GPIO_EUSART_SCLKROUTE_PIN_DEFAULT                             (_GPIO_EUSART_SCLKROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_SCLKROUTE*/

/* Bit fields for GPIO_EUSART TXROUTE */
#define _GPIO_EUSART_TXROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_EUSART_TXROUTE       */
#define _GPIO_EUSART_TXROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_EUSART_TXROUTE                */
#define _GPIO_EUSART_TXROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_EUSART_TXROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_EUSART_TXROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_TXROUTE        */
#define GPIO_EUSART_TXROUTE_PORT_DEFAULT                              (_GPIO_EUSART_TXROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_EUSART_TXROUTE*/
#define _GPIO_EUSART_TXROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_EUSART_TXROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_EUSART_TXROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_EUSART_TXROUTE        */
#define GPIO_EUSART_TXROUTE_PIN_DEFAULT                               (_GPIO_EUSART_TXROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_EUSART_TXROUTE*/

/* Bit fields for GPIO_FRC ROUTEEN */
#define _GPIO_FRC_ROUTEEN_RESETVALUE                                  0x00000000UL                               /**< Default value for GPIO_FRC_ROUTEEN          */
#define _GPIO_FRC_ROUTEEN_MASK                                        0x00000007UL                               /**< Mask for GPIO_FRC_ROUTEEN                   */
#define GPIO_FRC_ROUTEEN_DCLKPEN                                      (0x1UL << 0)                               /**< DCLK pin enable control bit                 */
#define _GPIO_FRC_ROUTEEN_DCLKPEN_SHIFT                               0                                          /**< Shift value for GPIO_DCLKPEN                */
#define _GPIO_FRC_ROUTEEN_DCLKPEN_MASK                                0x1UL                                      /**< Bit mask for GPIO_DCLKPEN                   */
#define _GPIO_FRC_ROUTEEN_DCLKPEN_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for GPIO_FRC_ROUTEEN           */
#define GPIO_FRC_ROUTEEN_DCLKPEN_DEFAULT                              (_GPIO_FRC_ROUTEEN_DCLKPEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_FRC_ROUTEEN   */
#define GPIO_FRC_ROUTEEN_DFRAMEPEN                                    (0x1UL << 1)                               /**< DFRAME pin enable control bit               */
#define _GPIO_FRC_ROUTEEN_DFRAMEPEN_SHIFT                             1                                          /**< Shift value for GPIO_DFRAMEPEN              */
#define _GPIO_FRC_ROUTEEN_DFRAMEPEN_MASK                              0x2UL                                      /**< Bit mask for GPIO_DFRAMEPEN                 */
#define _GPIO_FRC_ROUTEEN_DFRAMEPEN_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_FRC_ROUTEEN           */
#define GPIO_FRC_ROUTEEN_DFRAMEPEN_DEFAULT                            (_GPIO_FRC_ROUTEEN_DFRAMEPEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_FRC_ROUTEEN   */
#define GPIO_FRC_ROUTEEN_DOUTPEN                                      (0x1UL << 2)                               /**< DOUT pin enable control bit                 */
#define _GPIO_FRC_ROUTEEN_DOUTPEN_SHIFT                               2                                          /**< Shift value for GPIO_DOUTPEN                */
#define _GPIO_FRC_ROUTEEN_DOUTPEN_MASK                                0x4UL                                      /**< Bit mask for GPIO_DOUTPEN                   */
#define _GPIO_FRC_ROUTEEN_DOUTPEN_DEFAULT                             0x00000000UL                               /**< Mode DEFAULT for GPIO_FRC_ROUTEEN           */
#define GPIO_FRC_ROUTEEN_DOUTPEN_DEFAULT                              (_GPIO_FRC_ROUTEEN_DOUTPEN_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_FRC_ROUTEEN   */

/* Bit fields for GPIO_FRC DCLKROUTE */
#define _GPIO_FRC_DCLKROUTE_RESETVALUE                                0x00000000UL                            /**< Default value for GPIO_FRC_DCLKROUTE        */
#define _GPIO_FRC_DCLKROUTE_MASK                                      0x000F0003UL                            /**< Mask for GPIO_FRC_DCLKROUTE                 */
#define _GPIO_FRC_DCLKROUTE_PORT_SHIFT                                0                                       /**< Shift value for GPIO_PORT                   */
#define _GPIO_FRC_DCLKROUTE_PORT_MASK                                 0x3UL                                   /**< Bit mask for GPIO_PORT                      */
#define _GPIO_FRC_DCLKROUTE_PORT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_FRC_DCLKROUTE         */
#define GPIO_FRC_DCLKROUTE_PORT_DEFAULT                               (_GPIO_FRC_DCLKROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_FRC_DCLKROUTE */
#define _GPIO_FRC_DCLKROUTE_PIN_SHIFT                                 16                                      /**< Shift value for GPIO_PIN                    */
#define _GPIO_FRC_DCLKROUTE_PIN_MASK                                  0xF0000UL                               /**< Bit mask for GPIO_PIN                       */
#define _GPIO_FRC_DCLKROUTE_PIN_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_FRC_DCLKROUTE         */
#define GPIO_FRC_DCLKROUTE_PIN_DEFAULT                                (_GPIO_FRC_DCLKROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_FRC_DCLKROUTE */

/* Bit fields for GPIO_FRC DFRAMEROUTE */
#define _GPIO_FRC_DFRAMEROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_FRC_DFRAMEROUTE      */
#define _GPIO_FRC_DFRAMEROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_FRC_DFRAMEROUTE               */
#define _GPIO_FRC_DFRAMEROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_FRC_DFRAMEROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_FRC_DFRAMEROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_FRC_DFRAMEROUTE       */
#define GPIO_FRC_DFRAMEROUTE_PORT_DEFAULT                             (_GPIO_FRC_DFRAMEROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_FRC_DFRAMEROUTE*/
#define _GPIO_FRC_DFRAMEROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_FRC_DFRAMEROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_FRC_DFRAMEROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_FRC_DFRAMEROUTE       */
#define GPIO_FRC_DFRAMEROUTE_PIN_DEFAULT                              (_GPIO_FRC_DFRAMEROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_FRC_DFRAMEROUTE*/

/* Bit fields for GPIO_FRC DOUTROUTE */
#define _GPIO_FRC_DOUTROUTE_RESETVALUE                                0x00000000UL                            /**< Default value for GPIO_FRC_DOUTROUTE        */
#define _GPIO_FRC_DOUTROUTE_MASK                                      0x000F0003UL                            /**< Mask for GPIO_FRC_DOUTROUTE                 */
#define _GPIO_FRC_DOUTROUTE_PORT_SHIFT                                0                                       /**< Shift value for GPIO_PORT                   */
#define _GPIO_FRC_DOUTROUTE_PORT_MASK                                 0x3UL                                   /**< Bit mask for GPIO_PORT                      */
#define _GPIO_FRC_DOUTROUTE_PORT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_FRC_DOUTROUTE         */
#define GPIO_FRC_DOUTROUTE_PORT_DEFAULT                               (_GPIO_FRC_DOUTROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_FRC_DOUTROUTE */
#define _GPIO_FRC_DOUTROUTE_PIN_SHIFT                                 16                                      /**< Shift value for GPIO_PIN                    */
#define _GPIO_FRC_DOUTROUTE_PIN_MASK                                  0xF0000UL                               /**< Bit mask for GPIO_PIN                       */
#define _GPIO_FRC_DOUTROUTE_PIN_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_FRC_DOUTROUTE         */
#define GPIO_FRC_DOUTROUTE_PIN_DEFAULT                                (_GPIO_FRC_DOUTROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_FRC_DOUTROUTE */

/* Bit fields for GPIO_I2C ROUTEEN */
#define _GPIO_I2C_ROUTEEN_RESETVALUE                                  0x00000000UL                            /**< Default value for GPIO_I2C_ROUTEEN          */
#define _GPIO_I2C_ROUTEEN_MASK                                        0x00000003UL                            /**< Mask for GPIO_I2C_ROUTEEN                   */
#define GPIO_I2C_ROUTEEN_SCLPEN                                       (0x1UL << 0)                            /**< SCL pin enable control bit                  */
#define _GPIO_I2C_ROUTEEN_SCLPEN_SHIFT                                0                                       /**< Shift value for GPIO_SCLPEN                 */
#define _GPIO_I2C_ROUTEEN_SCLPEN_MASK                                 0x1UL                                   /**< Bit mask for GPIO_SCLPEN                    */
#define _GPIO_I2C_ROUTEEN_SCLPEN_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_I2C_ROUTEEN           */
#define GPIO_I2C_ROUTEEN_SCLPEN_DEFAULT                               (_GPIO_I2C_ROUTEEN_SCLPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_I2C_ROUTEEN   */
#define GPIO_I2C_ROUTEEN_SDAPEN                                       (0x1UL << 1)                            /**< SDA pin enable control bit                  */
#define _GPIO_I2C_ROUTEEN_SDAPEN_SHIFT                                1                                       /**< Shift value for GPIO_SDAPEN                 */
#define _GPIO_I2C_ROUTEEN_SDAPEN_MASK                                 0x2UL                                   /**< Bit mask for GPIO_SDAPEN                    */
#define _GPIO_I2C_ROUTEEN_SDAPEN_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_I2C_ROUTEEN           */
#define GPIO_I2C_ROUTEEN_SDAPEN_DEFAULT                               (_GPIO_I2C_ROUTEEN_SDAPEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_I2C_ROUTEEN   */

/* Bit fields for GPIO_I2C SCLROUTE */
#define _GPIO_I2C_SCLROUTE_RESETVALUE                                 0x00000000UL                           /**< Default value for GPIO_I2C_SCLROUTE         */
#define _GPIO_I2C_SCLROUTE_MASK                                       0x000F0003UL                           /**< Mask for GPIO_I2C_SCLROUTE                  */
#define _GPIO_I2C_SCLROUTE_PORT_SHIFT                                 0                                      /**< Shift value for GPIO_PORT                   */
#define _GPIO_I2C_SCLROUTE_PORT_MASK                                  0x3UL                                  /**< Bit mask for GPIO_PORT                      */
#define _GPIO_I2C_SCLROUTE_PORT_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for GPIO_I2C_SCLROUTE          */
#define GPIO_I2C_SCLROUTE_PORT_DEFAULT                                (_GPIO_I2C_SCLROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_I2C_SCLROUTE  */
#define _GPIO_I2C_SCLROUTE_PIN_SHIFT                                  16                                     /**< Shift value for GPIO_PIN                    */
#define _GPIO_I2C_SCLROUTE_PIN_MASK                                   0xF0000UL                              /**< Bit mask for GPIO_PIN                       */
#define _GPIO_I2C_SCLROUTE_PIN_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_I2C_SCLROUTE          */
#define GPIO_I2C_SCLROUTE_PIN_DEFAULT                                 (_GPIO_I2C_SCLROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_I2C_SCLROUTE  */

/* Bit fields for GPIO_I2C SDAROUTE */
#define _GPIO_I2C_SDAROUTE_RESETVALUE                                 0x00000000UL                           /**< Default value for GPIO_I2C_SDAROUTE         */
#define _GPIO_I2C_SDAROUTE_MASK                                       0x000F0003UL                           /**< Mask for GPIO_I2C_SDAROUTE                  */
#define _GPIO_I2C_SDAROUTE_PORT_SHIFT                                 0                                      /**< Shift value for GPIO_PORT                   */
#define _GPIO_I2C_SDAROUTE_PORT_MASK                                  0x3UL                                  /**< Bit mask for GPIO_PORT                      */
#define _GPIO_I2C_SDAROUTE_PORT_DEFAULT                               0x00000000UL                           /**< Mode DEFAULT for GPIO_I2C_SDAROUTE          */
#define GPIO_I2C_SDAROUTE_PORT_DEFAULT                                (_GPIO_I2C_SDAROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_I2C_SDAROUTE  */
#define _GPIO_I2C_SDAROUTE_PIN_SHIFT                                  16                                     /**< Shift value for GPIO_PIN                    */
#define _GPIO_I2C_SDAROUTE_PIN_MASK                                   0xF0000UL                              /**< Bit mask for GPIO_PIN                       */
#define _GPIO_I2C_SDAROUTE_PIN_DEFAULT                                0x00000000UL                           /**< Mode DEFAULT for GPIO_I2C_SDAROUTE          */
#define GPIO_I2C_SDAROUTE_PIN_DEFAULT                                 (_GPIO_I2C_SDAROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_I2C_SDAROUTE  */

/* Bit fields for GPIO_KEYSCAN ROUTEEN */
#define _GPIO_KEYSCAN_ROUTEEN_RESETVALUE                              0x00000000UL                                    /**< Default value for GPIO_KEYSCAN_ROUTEEN      */
#define _GPIO_KEYSCAN_ROUTEEN_MASK                                    0x000000FFUL                                    /**< Mask for GPIO_KEYSCAN_ROUTEEN               */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN                               (0x1UL << 0)                                    /**< COLOUT0 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN_SHIFT                        0                                               /**< Shift value for GPIO_COLOUT0PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN_MASK                         0x1UL                                           /**< Bit mask for GPIO_COLOUT0PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT0PEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN                               (0x1UL << 1)                                    /**< COLOUT1 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN_SHIFT                        1                                               /**< Shift value for GPIO_COLOUT1PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN_MASK                         0x2UL                                           /**< Bit mask for GPIO_COLOUT1PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT1PEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN                               (0x1UL << 2)                                    /**< COLOUT2 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN_SHIFT                        2                                               /**< Shift value for GPIO_COLOUT2PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN_MASK                         0x4UL                                           /**< Bit mask for GPIO_COLOUT2PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT2PEN_DEFAULT << 2) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN                               (0x1UL << 3)                                    /**< COLOUT3 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN_SHIFT                        3                                               /**< Shift value for GPIO_COLOUT3PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN_MASK                         0x8UL                                           /**< Bit mask for GPIO_COLOUT3PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT3PEN_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN                               (0x1UL << 4)                                    /**< COLOUT4 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN_SHIFT                        4                                               /**< Shift value for GPIO_COLOUT4PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN_MASK                         0x10UL                                          /**< Bit mask for GPIO_COLOUT4PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT4PEN_DEFAULT << 4) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN                               (0x1UL << 5)                                    /**< COLOUT5 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN_SHIFT                        5                                               /**< Shift value for GPIO_COLOUT5PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN_MASK                         0x20UL                                          /**< Bit mask for GPIO_COLOUT5PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT5PEN_DEFAULT << 5) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN                               (0x1UL << 6)                                    /**< COLOUT6 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN_SHIFT                        6                                               /**< Shift value for GPIO_COLOUT6PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN_MASK                         0x40UL                                          /**< Bit mask for GPIO_COLOUT6PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT6PEN_DEFAULT << 6) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/
#define GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN                               (0x1UL << 7)                                    /**< COLOUT7 pin enable control bit              */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN_SHIFT                        7                                               /**< Shift value for GPIO_COLOUT7PEN             */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN_MASK                         0x80UL                                          /**< Bit mask for GPIO_COLOUT7PEN                */
#define _GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN_DEFAULT                      0x00000000UL                                    /**< Mode DEFAULT for GPIO_KEYSCAN_ROUTEEN       */
#define GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN_DEFAULT                       (_GPIO_KEYSCAN_ROUTEEN_COLOUT7PEN_DEFAULT << 7) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROUTEEN*/

/* Bit fields for GPIO_KEYSCAN COLOUT0ROUTE */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT0ROUTE */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT0ROUTE          */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT0ROUTE  */
#define GPIO_KEYSCAN_COLOUT0ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT0ROUTE*/
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT0ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT0ROUTE  */
#define GPIO_KEYSCAN_COLOUT0ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT0ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT1ROUTE */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT1ROUTE */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT1ROUTE          */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT1ROUTE  */
#define GPIO_KEYSCAN_COLOUT1ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT1ROUTE*/
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT1ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT1ROUTE  */
#define GPIO_KEYSCAN_COLOUT1ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT1ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT2ROUTE */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT2ROUTE */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT2ROUTE          */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT2ROUTE  */
#define GPIO_KEYSCAN_COLOUT2ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT2ROUTE*/
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT2ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT2ROUTE  */
#define GPIO_KEYSCAN_COLOUT2ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT2ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT3ROUTE */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT3ROUTE */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT3ROUTE          */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT3ROUTE  */
#define GPIO_KEYSCAN_COLOUT3ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT3ROUTE*/
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT3ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT3ROUTE  */
#define GPIO_KEYSCAN_COLOUT3ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT3ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT4ROUTE */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT4ROUTE */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT4ROUTE          */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT4ROUTE  */
#define GPIO_KEYSCAN_COLOUT4ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT4ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT4ROUTE*/
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT4ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT4ROUTE  */
#define GPIO_KEYSCAN_COLOUT4ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT4ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT4ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT5ROUTE */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT5ROUTE */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT5ROUTE          */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT5ROUTE  */
#define GPIO_KEYSCAN_COLOUT5ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT5ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT5ROUTE*/
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT5ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT5ROUTE  */
#define GPIO_KEYSCAN_COLOUT5ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT5ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT5ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT6ROUTE */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT6ROUTE */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT6ROUTE          */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT6ROUTE  */
#define GPIO_KEYSCAN_COLOUT6ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT6ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT6ROUTE*/
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT6ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT6ROUTE  */
#define GPIO_KEYSCAN_COLOUT6ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT6ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT6ROUTE*/

/* Bit fields for GPIO_KEYSCAN COLOUT7ROUTE */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_RESETVALUE                         0x00000000UL                                   /**< Default value for GPIO_KEYSCAN_COLOUT7ROUTE */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_MASK                               0x000F0003UL                                   /**< Mask for GPIO_KEYSCAN_COLOUT7ROUTE          */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PORT_SHIFT                         0                                              /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PORT_MASK                          0x3UL                                          /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PORT_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT7ROUTE  */
#define GPIO_KEYSCAN_COLOUT7ROUTE_PORT_DEFAULT                        (_GPIO_KEYSCAN_COLOUT7ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT7ROUTE*/
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PIN_SHIFT                          16                                             /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PIN_MASK                           0xF0000UL                                      /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_COLOUT7ROUTE_PIN_DEFAULT                        0x00000000UL                                   /**< Mode DEFAULT for GPIO_KEYSCAN_COLOUT7ROUTE  */
#define GPIO_KEYSCAN_COLOUT7ROUTE_PIN_DEFAULT                         (_GPIO_KEYSCAN_COLOUT7ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_COLOUT7ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE0ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE0ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE0ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE0ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE0ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE0ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE0ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE1ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE1ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE1ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE1ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE1ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE1ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE1ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE2ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE2ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE2ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE2ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE2ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE2ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE2ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE3ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE3ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE3ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE3ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE3ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE3ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE3ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE4ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE4ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE4ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE4ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE4ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE4ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE4ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE4ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE4ROUTE*/

/* Bit fields for GPIO_KEYSCAN ROWSENSE5ROUTE */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_KEYSCAN_ROWSENSE5ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_KEYSCAN_ROWSENSE5ROUTE        */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE5ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_DEFAULT                      (_GPIO_KEYSCAN_ROWSENSE5ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE5ROUTE*/
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_KEYSCAN_ROWSENSE5ROUTE*/
#define GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_DEFAULT                       (_GPIO_KEYSCAN_ROWSENSE5ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_KEYSCAN_ROWSENSE5ROUTE*/

/* Bit fields for GPIO_LETIMER ROUTEEN */
#define _GPIO_LETIMER_ROUTEEN_RESETVALUE                              0x00000000UL                                 /**< Default value for GPIO_LETIMER_ROUTEEN      */
#define _GPIO_LETIMER_ROUTEEN_MASK                                    0x00000003UL                                 /**< Mask for GPIO_LETIMER_ROUTEEN               */
#define GPIO_LETIMER_ROUTEEN_OUT0PEN                                  (0x1UL << 0)                                 /**< OUT0 pin enable control bit                 */
#define _GPIO_LETIMER_ROUTEEN_OUT0PEN_SHIFT                           0                                            /**< Shift value for GPIO_OUT0PEN                */
#define _GPIO_LETIMER_ROUTEEN_OUT0PEN_MASK                            0x1UL                                        /**< Bit mask for GPIO_OUT0PEN                   */
#define _GPIO_LETIMER_ROUTEEN_OUT0PEN_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_LETIMER_ROUTEEN       */
#define GPIO_LETIMER_ROUTEEN_OUT0PEN_DEFAULT                          (_GPIO_LETIMER_ROUTEEN_OUT0PEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_LETIMER_ROUTEEN*/
#define GPIO_LETIMER_ROUTEEN_OUT1PEN                                  (0x1UL << 1)                                 /**< OUT1 pin enable control bit                 */
#define _GPIO_LETIMER_ROUTEEN_OUT1PEN_SHIFT                           1                                            /**< Shift value for GPIO_OUT1PEN                */
#define _GPIO_LETIMER_ROUTEEN_OUT1PEN_MASK                            0x2UL                                        /**< Bit mask for GPIO_OUT1PEN                   */
#define _GPIO_LETIMER_ROUTEEN_OUT1PEN_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_LETIMER_ROUTEEN       */
#define GPIO_LETIMER_ROUTEEN_OUT1PEN_DEFAULT                          (_GPIO_LETIMER_ROUTEEN_OUT1PEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_LETIMER_ROUTEEN*/

/* Bit fields for GPIO_LETIMER OUT0ROUTE */
#define _GPIO_LETIMER_OUT0ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_LETIMER_OUT0ROUTE    */
#define _GPIO_LETIMER_OUT0ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_LETIMER_OUT0ROUTE             */
#define _GPIO_LETIMER_OUT0ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_LETIMER_OUT0ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_LETIMER_OUT0ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_LETIMER_OUT0ROUTE     */
#define GPIO_LETIMER_OUT0ROUTE_PORT_DEFAULT                           (_GPIO_LETIMER_OUT0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_LETIMER_OUT0ROUTE*/
#define _GPIO_LETIMER_OUT0ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_LETIMER_OUT0ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_LETIMER_OUT0ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_LETIMER_OUT0ROUTE     */
#define GPIO_LETIMER_OUT0ROUTE_PIN_DEFAULT                            (_GPIO_LETIMER_OUT0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_LETIMER_OUT0ROUTE*/

/* Bit fields for GPIO_LETIMER OUT1ROUTE */
#define _GPIO_LETIMER_OUT1ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_LETIMER_OUT1ROUTE    */
#define _GPIO_LETIMER_OUT1ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_LETIMER_OUT1ROUTE             */
#define _GPIO_LETIMER_OUT1ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_LETIMER_OUT1ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_LETIMER_OUT1ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_LETIMER_OUT1ROUTE     */
#define GPIO_LETIMER_OUT1ROUTE_PORT_DEFAULT                           (_GPIO_LETIMER_OUT1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_LETIMER_OUT1ROUTE*/
#define _GPIO_LETIMER_OUT1ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_LETIMER_OUT1ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_LETIMER_OUT1ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_LETIMER_OUT1ROUTE     */
#define GPIO_LETIMER_OUT1ROUTE_PIN_DEFAULT                            (_GPIO_LETIMER_OUT1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_LETIMER_OUT1ROUTE*/

/* Bit fields for GPIO_MODEM ROUTEEN */
#define _GPIO_MODEM_ROUTEEN_RESETVALUE                                0x00000000UL                                       /**< Default value for GPIO_MODEM_ROUTEEN        */
#define _GPIO_MODEM_ROUTEEN_MASK                                      0x00007FFFUL                                       /**< Mask for GPIO_MODEM_ROUTEEN                 */
#define GPIO_MODEM_ROUTEEN_ANT0PEN                                    (0x1UL << 0)                                       /**< ANT0 pin enable control bit                 */
#define _GPIO_MODEM_ROUTEEN_ANT0PEN_SHIFT                             0                                                  /**< Shift value for GPIO_ANT0PEN                */
#define _GPIO_MODEM_ROUTEEN_ANT0PEN_MASK                              0x1UL                                              /**< Bit mask for GPIO_ANT0PEN                   */
#define _GPIO_MODEM_ROUTEEN_ANT0PEN_DEFAULT                           0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANT0PEN_DEFAULT                            (_GPIO_MODEM_ROUTEEN_ANT0PEN_DEFAULT << 0)         /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANT1PEN                                    (0x1UL << 1)                                       /**< ANT1 pin enable control bit                 */
#define _GPIO_MODEM_ROUTEEN_ANT1PEN_SHIFT                             1                                                  /**< Shift value for GPIO_ANT1PEN                */
#define _GPIO_MODEM_ROUTEEN_ANT1PEN_MASK                              0x2UL                                              /**< Bit mask for GPIO_ANT1PEN                   */
#define _GPIO_MODEM_ROUTEEN_ANT1PEN_DEFAULT                           0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANT1PEN_DEFAULT                            (_GPIO_MODEM_ROUTEEN_ANT1PEN_DEFAULT << 1)         /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN                             (0x1UL << 2)                                       /**< ANTROLLOVER pin enable control bit          */
#define _GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN_SHIFT                      2                                                  /**< Shift value for GPIO_ANTROLLOVERPEN         */
#define _GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN_MASK                       0x4UL                                              /**< Bit mask for GPIO_ANTROLLOVERPEN            */
#define _GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN_DEFAULT                     (_GPIO_MODEM_ROUTEEN_ANTROLLOVERPEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR0PEN                                  (0x1UL << 3)                                       /**< ANTRR0 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR0PEN_SHIFT                           3                                                  /**< Shift value for GPIO_ANTRR0PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR0PEN_MASK                            0x8UL                                              /**< Bit mask for GPIO_ANTRR0PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR0PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR0PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR0PEN_DEFAULT << 3)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR1PEN                                  (0x1UL << 4)                                       /**< ANTRR1 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR1PEN_SHIFT                           4                                                  /**< Shift value for GPIO_ANTRR1PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR1PEN_MASK                            0x10UL                                             /**< Bit mask for GPIO_ANTRR1PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR1PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR1PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR1PEN_DEFAULT << 4)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR2PEN                                  (0x1UL << 5)                                       /**< ANTRR2 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR2PEN_SHIFT                           5                                                  /**< Shift value for GPIO_ANTRR2PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR2PEN_MASK                            0x20UL                                             /**< Bit mask for GPIO_ANTRR2PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR2PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR2PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR2PEN_DEFAULT << 5)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR3PEN                                  (0x1UL << 6)                                       /**< ANTRR3 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR3PEN_SHIFT                           6                                                  /**< Shift value for GPIO_ANTRR3PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR3PEN_MASK                            0x40UL                                             /**< Bit mask for GPIO_ANTRR3PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR3PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR3PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR3PEN_DEFAULT << 6)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR4PEN                                  (0x1UL << 7)                                       /**< ANTRR4 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR4PEN_SHIFT                           7                                                  /**< Shift value for GPIO_ANTRR4PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR4PEN_MASK                            0x80UL                                             /**< Bit mask for GPIO_ANTRR4PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR4PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR4PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR4PEN_DEFAULT << 7)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTRR5PEN                                  (0x1UL << 8)                                       /**< ANTRR5 pin enable control bit               */
#define _GPIO_MODEM_ROUTEEN_ANTRR5PEN_SHIFT                           8                                                  /**< Shift value for GPIO_ANTRR5PEN              */
#define _GPIO_MODEM_ROUTEEN_ANTRR5PEN_MASK                            0x100UL                                            /**< Bit mask for GPIO_ANTRR5PEN                 */
#define _GPIO_MODEM_ROUTEEN_ANTRR5PEN_DEFAULT                         0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTRR5PEN_DEFAULT                          (_GPIO_MODEM_ROUTEEN_ANTRR5PEN_DEFAULT << 8)       /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTSWENPEN                                 (0x1UL << 9)                                       /**< ANTSWEN pin enable control bit              */
#define _GPIO_MODEM_ROUTEEN_ANTSWENPEN_SHIFT                          9                                                  /**< Shift value for GPIO_ANTSWENPEN             */
#define _GPIO_MODEM_ROUTEEN_ANTSWENPEN_MASK                           0x200UL                                            /**< Bit mask for GPIO_ANTSWENPEN                */
#define _GPIO_MODEM_ROUTEEN_ANTSWENPEN_DEFAULT                        0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTSWENPEN_DEFAULT                         (_GPIO_MODEM_ROUTEEN_ANTSWENPEN_DEFAULT << 9)      /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTSWUSPEN                                 (0x1UL << 10)                                      /**< ANTSWUS pin enable control bit              */
#define _GPIO_MODEM_ROUTEEN_ANTSWUSPEN_SHIFT                          10                                                 /**< Shift value for GPIO_ANTSWUSPEN             */
#define _GPIO_MODEM_ROUTEEN_ANTSWUSPEN_MASK                           0x400UL                                            /**< Bit mask for GPIO_ANTSWUSPEN                */
#define _GPIO_MODEM_ROUTEEN_ANTSWUSPEN_DEFAULT                        0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTSWUSPEN_DEFAULT                         (_GPIO_MODEM_ROUTEEN_ANTSWUSPEN_DEFAULT << 10)     /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTTRIGPEN                                 (0x1UL << 11)                                      /**< ANTTRIG pin enable control bit              */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGPEN_SHIFT                          11                                                 /**< Shift value for GPIO_ANTTRIGPEN             */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGPEN_MASK                           0x800UL                                            /**< Bit mask for GPIO_ANTTRIGPEN                */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGPEN_DEFAULT                        0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTTRIGPEN_DEFAULT                         (_GPIO_MODEM_ROUTEEN_ANTTRIGPEN_DEFAULT << 11)     /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN                             (0x1UL << 12)                                      /**< ANTTRIGSTOP pin enable control bit          */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN_SHIFT                      12                                                 /**< Shift value for GPIO_ANTTRIGSTOPPEN         */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN_MASK                       0x1000UL                                           /**< Bit mask for GPIO_ANTTRIGSTOPPEN            */
#define _GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN_DEFAULT                     (_GPIO_MODEM_ROUTEEN_ANTTRIGSTOPPEN_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_DCLKPEN                                    (0x1UL << 13)                                      /**< DCLK pin enable control bit                 */
#define _GPIO_MODEM_ROUTEEN_DCLKPEN_SHIFT                             13                                                 /**< Shift value for GPIO_DCLKPEN                */
#define _GPIO_MODEM_ROUTEEN_DCLKPEN_MASK                              0x2000UL                                           /**< Bit mask for GPIO_DCLKPEN                   */
#define _GPIO_MODEM_ROUTEEN_DCLKPEN_DEFAULT                           0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_DCLKPEN_DEFAULT                            (_GPIO_MODEM_ROUTEEN_DCLKPEN_DEFAULT << 13)        /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */
#define GPIO_MODEM_ROUTEEN_DOUTPEN                                    (0x1UL << 14)                                      /**< DOUT pin enable control bit                 */
#define _GPIO_MODEM_ROUTEEN_DOUTPEN_SHIFT                             14                                                 /**< Shift value for GPIO_DOUTPEN                */
#define _GPIO_MODEM_ROUTEEN_DOUTPEN_MASK                              0x4000UL                                           /**< Bit mask for GPIO_DOUTPEN                   */
#define _GPIO_MODEM_ROUTEEN_DOUTPEN_DEFAULT                           0x00000000UL                                       /**< Mode DEFAULT for GPIO_MODEM_ROUTEEN         */
#define GPIO_MODEM_ROUTEEN_DOUTPEN_DEFAULT                            (_GPIO_MODEM_ROUTEEN_DOUTPEN_DEFAULT << 14)        /**< Shifted mode DEFAULT for GPIO_MODEM_ROUTEEN */

/* Bit fields for GPIO_MODEM ANT0ROUTE */
#define _GPIO_MODEM_ANT0ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_MODEM_ANT0ROUTE      */
#define _GPIO_MODEM_ANT0ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_MODEM_ANT0ROUTE               */
#define _GPIO_MODEM_ANT0ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANT0ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANT0ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_ANT0ROUTE       */
#define GPIO_MODEM_ANT0ROUTE_PORT_DEFAULT                             (_GPIO_MODEM_ANT0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANT0ROUTE*/
#define _GPIO_MODEM_ANT0ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANT0ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANT0ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_ANT0ROUTE       */
#define GPIO_MODEM_ANT0ROUTE_PIN_DEFAULT                              (_GPIO_MODEM_ANT0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANT0ROUTE*/

/* Bit fields for GPIO_MODEM ANT1ROUTE */
#define _GPIO_MODEM_ANT1ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_MODEM_ANT1ROUTE      */
#define _GPIO_MODEM_ANT1ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_MODEM_ANT1ROUTE               */
#define _GPIO_MODEM_ANT1ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANT1ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANT1ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_ANT1ROUTE       */
#define GPIO_MODEM_ANT1ROUTE_PORT_DEFAULT                             (_GPIO_MODEM_ANT1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANT1ROUTE*/
#define _GPIO_MODEM_ANT1ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANT1ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANT1ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_ANT1ROUTE       */
#define GPIO_MODEM_ANT1ROUTE_PIN_DEFAULT                              (_GPIO_MODEM_ANT1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANT1ROUTE*/

/* Bit fields for GPIO_MODEM ANTROLLOVERROUTE */
#define _GPIO_MODEM_ANTROLLOVERROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_MODEM_ANTROLLOVERROUTE*/
#define _GPIO_MODEM_ANTROLLOVERROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_MODEM_ANTROLLOVERROUTE        */
#define _GPIO_MODEM_ANTROLLOVERROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTROLLOVERROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTROLLOVERROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_MODEM_ANTROLLOVERROUTE*/
#define GPIO_MODEM_ANTROLLOVERROUTE_PORT_DEFAULT                      (_GPIO_MODEM_ANTROLLOVERROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTROLLOVERROUTE*/
#define _GPIO_MODEM_ANTROLLOVERROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTROLLOVERROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTROLLOVERROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_MODEM_ANTROLLOVERROUTE*/
#define GPIO_MODEM_ANTROLLOVERROUTE_PIN_DEFAULT                       (_GPIO_MODEM_ANTROLLOVERROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTROLLOVERROUTE*/

/* Bit fields for GPIO_MODEM ANTRR0ROUTE */
#define _GPIO_MODEM_ANTRR0ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR0ROUTE    */
#define _GPIO_MODEM_ANTRR0ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR0ROUTE             */
#define _GPIO_MODEM_ANTRR0ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR0ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR0ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR0ROUTE     */
#define GPIO_MODEM_ANTRR0ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR0ROUTE*/
#define _GPIO_MODEM_ANTRR0ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR0ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR0ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR0ROUTE     */
#define GPIO_MODEM_ANTRR0ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR0ROUTE*/

/* Bit fields for GPIO_MODEM ANTRR1ROUTE */
#define _GPIO_MODEM_ANTRR1ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR1ROUTE    */
#define _GPIO_MODEM_ANTRR1ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR1ROUTE             */
#define _GPIO_MODEM_ANTRR1ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR1ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR1ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR1ROUTE     */
#define GPIO_MODEM_ANTRR1ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR1ROUTE*/
#define _GPIO_MODEM_ANTRR1ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR1ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR1ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR1ROUTE     */
#define GPIO_MODEM_ANTRR1ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR1ROUTE*/

/* Bit fields for GPIO_MODEM ANTRR2ROUTE */
#define _GPIO_MODEM_ANTRR2ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR2ROUTE    */
#define _GPIO_MODEM_ANTRR2ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR2ROUTE             */
#define _GPIO_MODEM_ANTRR2ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR2ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR2ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR2ROUTE     */
#define GPIO_MODEM_ANTRR2ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR2ROUTE*/
#define _GPIO_MODEM_ANTRR2ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR2ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR2ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR2ROUTE     */
#define GPIO_MODEM_ANTRR2ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR2ROUTE*/

/* Bit fields for GPIO_MODEM ANTRR3ROUTE */
#define _GPIO_MODEM_ANTRR3ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR3ROUTE    */
#define _GPIO_MODEM_ANTRR3ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR3ROUTE             */
#define _GPIO_MODEM_ANTRR3ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR3ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR3ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR3ROUTE     */
#define GPIO_MODEM_ANTRR3ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR3ROUTE*/
#define _GPIO_MODEM_ANTRR3ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR3ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR3ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR3ROUTE     */
#define GPIO_MODEM_ANTRR3ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR3ROUTE*/

/* Bit fields for GPIO_MODEM ANTRR4ROUTE */
#define _GPIO_MODEM_ANTRR4ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR4ROUTE    */
#define _GPIO_MODEM_ANTRR4ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR4ROUTE             */
#define _GPIO_MODEM_ANTRR4ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR4ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR4ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR4ROUTE     */
#define GPIO_MODEM_ANTRR4ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR4ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR4ROUTE*/
#define _GPIO_MODEM_ANTRR4ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR4ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR4ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR4ROUTE     */
#define GPIO_MODEM_ANTRR4ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR4ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR4ROUTE*/

/* Bit fields for GPIO_MODEM ANTRR5ROUTE */
#define _GPIO_MODEM_ANTRR5ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_MODEM_ANTRR5ROUTE    */
#define _GPIO_MODEM_ANTRR5ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_MODEM_ANTRR5ROUTE             */
#define _GPIO_MODEM_ANTRR5ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTRR5ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTRR5ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR5ROUTE     */
#define GPIO_MODEM_ANTRR5ROUTE_PORT_DEFAULT                           (_GPIO_MODEM_ANTRR5ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR5ROUTE*/
#define _GPIO_MODEM_ANTRR5ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTRR5ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTRR5ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_MODEM_ANTRR5ROUTE     */
#define GPIO_MODEM_ANTRR5ROUTE_PIN_DEFAULT                            (_GPIO_MODEM_ANTRR5ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTRR5ROUTE*/

/* Bit fields for GPIO_MODEM ANTSWENROUTE */
#define _GPIO_MODEM_ANTSWENROUTE_RESETVALUE                           0x00000000UL                                 /**< Default value for GPIO_MODEM_ANTSWENROUTE   */
#define _GPIO_MODEM_ANTSWENROUTE_MASK                                 0x000F0003UL                                 /**< Mask for GPIO_MODEM_ANTSWENROUTE            */
#define _GPIO_MODEM_ANTSWENROUTE_PORT_SHIFT                           0                                            /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTSWENROUTE_PORT_MASK                            0x3UL                                        /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTSWENROUTE_PORT_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTSWENROUTE    */
#define GPIO_MODEM_ANTSWENROUTE_PORT_DEFAULT                          (_GPIO_MODEM_ANTSWENROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTSWENROUTE*/
#define _GPIO_MODEM_ANTSWENROUTE_PIN_SHIFT                            16                                           /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTSWENROUTE_PIN_MASK                             0xF0000UL                                    /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTSWENROUTE_PIN_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTSWENROUTE    */
#define GPIO_MODEM_ANTSWENROUTE_PIN_DEFAULT                           (_GPIO_MODEM_ANTSWENROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTSWENROUTE*/

/* Bit fields for GPIO_MODEM ANTSWUSROUTE */
#define _GPIO_MODEM_ANTSWUSROUTE_RESETVALUE                           0x00000000UL                                 /**< Default value for GPIO_MODEM_ANTSWUSROUTE   */
#define _GPIO_MODEM_ANTSWUSROUTE_MASK                                 0x000F0003UL                                 /**< Mask for GPIO_MODEM_ANTSWUSROUTE            */
#define _GPIO_MODEM_ANTSWUSROUTE_PORT_SHIFT                           0                                            /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTSWUSROUTE_PORT_MASK                            0x3UL                                        /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTSWUSROUTE_PORT_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTSWUSROUTE    */
#define GPIO_MODEM_ANTSWUSROUTE_PORT_DEFAULT                          (_GPIO_MODEM_ANTSWUSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTSWUSROUTE*/
#define _GPIO_MODEM_ANTSWUSROUTE_PIN_SHIFT                            16                                           /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTSWUSROUTE_PIN_MASK                             0xF0000UL                                    /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTSWUSROUTE_PIN_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTSWUSROUTE    */
#define GPIO_MODEM_ANTSWUSROUTE_PIN_DEFAULT                           (_GPIO_MODEM_ANTSWUSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTSWUSROUTE*/

/* Bit fields for GPIO_MODEM ANTTRIGROUTE */
#define _GPIO_MODEM_ANTTRIGROUTE_RESETVALUE                           0x00000000UL                                 /**< Default value for GPIO_MODEM_ANTTRIGROUTE   */
#define _GPIO_MODEM_ANTTRIGROUTE_MASK                                 0x000F0003UL                                 /**< Mask for GPIO_MODEM_ANTTRIGROUTE            */
#define _GPIO_MODEM_ANTTRIGROUTE_PORT_SHIFT                           0                                            /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTTRIGROUTE_PORT_MASK                            0x3UL                                        /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTTRIGROUTE_PORT_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTTRIGROUTE    */
#define GPIO_MODEM_ANTTRIGROUTE_PORT_DEFAULT                          (_GPIO_MODEM_ANTTRIGROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTTRIGROUTE*/
#define _GPIO_MODEM_ANTTRIGROUTE_PIN_SHIFT                            16                                           /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTTRIGROUTE_PIN_MASK                             0xF0000UL                                    /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTTRIGROUTE_PIN_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for GPIO_MODEM_ANTTRIGROUTE    */
#define GPIO_MODEM_ANTTRIGROUTE_PIN_DEFAULT                           (_GPIO_MODEM_ANTTRIGROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTTRIGROUTE*/

/* Bit fields for GPIO_MODEM ANTTRIGSTOPROUTE */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_RESETVALUE                       0x00000000UL                                     /**< Default value for GPIO_MODEM_ANTTRIGSTOPROUTE*/
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_MASK                             0x000F0003UL                                     /**< Mask for GPIO_MODEM_ANTTRIGSTOPROUTE        */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PORT_SHIFT                       0                                                /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PORT_MASK                        0x3UL                                            /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PORT_DEFAULT                     0x00000000UL                                     /**< Mode DEFAULT for GPIO_MODEM_ANTTRIGSTOPROUTE*/
#define GPIO_MODEM_ANTTRIGSTOPROUTE_PORT_DEFAULT                      (_GPIO_MODEM_ANTTRIGSTOPROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTTRIGSTOPROUTE*/
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PIN_SHIFT                        16                                               /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PIN_MASK                         0xF0000UL                                        /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_ANTTRIGSTOPROUTE_PIN_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_MODEM_ANTTRIGSTOPROUTE*/
#define GPIO_MODEM_ANTTRIGSTOPROUTE_PIN_DEFAULT                       (_GPIO_MODEM_ANTTRIGSTOPROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_ANTTRIGSTOPROUTE*/

/* Bit fields for GPIO_MODEM DCLKROUTE */
#define _GPIO_MODEM_DCLKROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_MODEM_DCLKROUTE      */
#define _GPIO_MODEM_DCLKROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_MODEM_DCLKROUTE               */
#define _GPIO_MODEM_DCLKROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_DCLKROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_DCLKROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_DCLKROUTE       */
#define GPIO_MODEM_DCLKROUTE_PORT_DEFAULT                             (_GPIO_MODEM_DCLKROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_DCLKROUTE*/
#define _GPIO_MODEM_DCLKROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_DCLKROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_DCLKROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_DCLKROUTE       */
#define GPIO_MODEM_DCLKROUTE_PIN_DEFAULT                              (_GPIO_MODEM_DCLKROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_DCLKROUTE*/

/* Bit fields for GPIO_MODEM DINROUTE */
#define _GPIO_MODEM_DINROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_MODEM_DINROUTE       */
#define _GPIO_MODEM_DINROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_MODEM_DINROUTE                */
#define _GPIO_MODEM_DINROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_DINROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_DINROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_MODEM_DINROUTE        */
#define GPIO_MODEM_DINROUTE_PORT_DEFAULT                              (_GPIO_MODEM_DINROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_DINROUTE*/
#define _GPIO_MODEM_DINROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_DINROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_DINROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_MODEM_DINROUTE        */
#define GPIO_MODEM_DINROUTE_PIN_DEFAULT                               (_GPIO_MODEM_DINROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_DINROUTE*/

/* Bit fields for GPIO_MODEM DOUTROUTE */
#define _GPIO_MODEM_DOUTROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_MODEM_DOUTROUTE      */
#define _GPIO_MODEM_DOUTROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_MODEM_DOUTROUTE               */
#define _GPIO_MODEM_DOUTROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_MODEM_DOUTROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_MODEM_DOUTROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_DOUTROUTE       */
#define GPIO_MODEM_DOUTROUTE_PORT_DEFAULT                             (_GPIO_MODEM_DOUTROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_MODEM_DOUTROUTE*/
#define _GPIO_MODEM_DOUTROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_MODEM_DOUTROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_MODEM_DOUTROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_MODEM_DOUTROUTE       */
#define GPIO_MODEM_DOUTROUTE_PIN_DEFAULT                              (_GPIO_MODEM_DOUTROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_MODEM_DOUTROUTE*/

/* Bit fields for GPIO_PCNT S0INROUTE */
#define _GPIO_PCNT_S0INROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_PCNT_S0INROUTE       */
#define _GPIO_PCNT_S0INROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_PCNT_S0INROUTE                */
#define _GPIO_PCNT_S0INROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_PCNT_S0INROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PCNT_S0INROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_PCNT_S0INROUTE        */
#define GPIO_PCNT_S0INROUTE_PORT_DEFAULT                              (_GPIO_PCNT_S0INROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PCNT_S0INROUTE*/
#define _GPIO_PCNT_S0INROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_PCNT_S0INROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PCNT_S0INROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_PCNT_S0INROUTE        */
#define GPIO_PCNT_S0INROUTE_PIN_DEFAULT                               (_GPIO_PCNT_S0INROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PCNT_S0INROUTE*/

/* Bit fields for GPIO_PCNT S1INROUTE */
#define _GPIO_PCNT_S1INROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_PCNT_S1INROUTE       */
#define _GPIO_PCNT_S1INROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_PCNT_S1INROUTE                */
#define _GPIO_PCNT_S1INROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_PCNT_S1INROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PCNT_S1INROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_PCNT_S1INROUTE        */
#define GPIO_PCNT_S1INROUTE_PORT_DEFAULT                              (_GPIO_PCNT_S1INROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PCNT_S1INROUTE*/
#define _GPIO_PCNT_S1INROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_PCNT_S1INROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PCNT_S1INROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_PCNT_S1INROUTE        */
#define GPIO_PCNT_S1INROUTE_PIN_DEFAULT                               (_GPIO_PCNT_S1INROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PCNT_S1INROUTE*/

/* Bit fields for GPIO_PRS ROUTEEN */
#define _GPIO_PRS_ROUTEEN_RESETVALUE                                  0x00000000UL                                  /**< Default value for GPIO_PRS_ROUTEEN          */
#define _GPIO_PRS_ROUTEEN_MASK                                        0x000FFFFFUL                                  /**< Mask for GPIO_PRS_ROUTEEN                   */
#define GPIO_PRS_ROUTEEN_ASYNCH0PEN                                   (0x1UL << 0)                                  /**< ASYNCH0 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH0PEN_SHIFT                            0                                             /**< Shift value for GPIO_ASYNCH0PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH0PEN_MASK                             0x1UL                                         /**< Bit mask for GPIO_ASYNCH0PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH0PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH0PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH0PEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH1PEN                                   (0x1UL << 1)                                  /**< ASYNCH1 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH1PEN_SHIFT                            1                                             /**< Shift value for GPIO_ASYNCH1PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH1PEN_MASK                             0x2UL                                         /**< Bit mask for GPIO_ASYNCH1PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH1PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH1PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH1PEN_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH2PEN                                   (0x1UL << 2)                                  /**< ASYNCH2 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH2PEN_SHIFT                            2                                             /**< Shift value for GPIO_ASYNCH2PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH2PEN_MASK                             0x4UL                                         /**< Bit mask for GPIO_ASYNCH2PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH2PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH2PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH2PEN_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH3PEN                                   (0x1UL << 3)                                  /**< ASYNCH3 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH3PEN_SHIFT                            3                                             /**< Shift value for GPIO_ASYNCH3PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH3PEN_MASK                             0x8UL                                         /**< Bit mask for GPIO_ASYNCH3PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH3PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH3PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH3PEN_DEFAULT << 3)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH4PEN                                   (0x1UL << 4)                                  /**< ASYNCH4 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH4PEN_SHIFT                            4                                             /**< Shift value for GPIO_ASYNCH4PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH4PEN_MASK                             0x10UL                                        /**< Bit mask for GPIO_ASYNCH4PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH4PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH4PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH4PEN_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH5PEN                                   (0x1UL << 5)                                  /**< ASYNCH5 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH5PEN_SHIFT                            5                                             /**< Shift value for GPIO_ASYNCH5PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH5PEN_MASK                             0x20UL                                        /**< Bit mask for GPIO_ASYNCH5PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH5PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH5PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH5PEN_DEFAULT << 5)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH6PEN                                   (0x1UL << 6)                                  /**< ASYNCH6 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH6PEN_SHIFT                            6                                             /**< Shift value for GPIO_ASYNCH6PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH6PEN_MASK                             0x40UL                                        /**< Bit mask for GPIO_ASYNCH6PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH6PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH6PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH6PEN_DEFAULT << 6)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH7PEN                                   (0x1UL << 7)                                  /**< ASYNCH7 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH7PEN_SHIFT                            7                                             /**< Shift value for GPIO_ASYNCH7PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH7PEN_MASK                             0x80UL                                        /**< Bit mask for GPIO_ASYNCH7PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH7PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH7PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH7PEN_DEFAULT << 7)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH8PEN                                   (0x1UL << 8)                                  /**< ASYNCH8 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH8PEN_SHIFT                            8                                             /**< Shift value for GPIO_ASYNCH8PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH8PEN_MASK                             0x100UL                                       /**< Bit mask for GPIO_ASYNCH8PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH8PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH8PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH8PEN_DEFAULT << 8)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH9PEN                                   (0x1UL << 9)                                  /**< ASYNCH9 pin enable control bit              */
#define _GPIO_PRS_ROUTEEN_ASYNCH9PEN_SHIFT                            9                                             /**< Shift value for GPIO_ASYNCH9PEN             */
#define _GPIO_PRS_ROUTEEN_ASYNCH9PEN_MASK                             0x200UL                                       /**< Bit mask for GPIO_ASYNCH9PEN                */
#define _GPIO_PRS_ROUTEEN_ASYNCH9PEN_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH9PEN_DEFAULT                           (_GPIO_PRS_ROUTEEN_ASYNCH9PEN_DEFAULT << 9)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH10PEN                                  (0x1UL << 10)                                 /**< ASYNCH10 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH10PEN_SHIFT                           10                                            /**< Shift value for GPIO_ASYNCH10PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH10PEN_MASK                            0x400UL                                       /**< Bit mask for GPIO_ASYNCH10PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH10PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH10PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH10PEN_DEFAULT << 10) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH11PEN                                  (0x1UL << 11)                                 /**< ASYNCH11 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH11PEN_SHIFT                           11                                            /**< Shift value for GPIO_ASYNCH11PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH11PEN_MASK                            0x800UL                                       /**< Bit mask for GPIO_ASYNCH11PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH11PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH11PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH11PEN_DEFAULT << 11) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH12PEN                                  (0x1UL << 12)                                 /**< ASYNCH12 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH12PEN_SHIFT                           12                                            /**< Shift value for GPIO_ASYNCH12PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH12PEN_MASK                            0x1000UL                                      /**< Bit mask for GPIO_ASYNCH12PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH12PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH12PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH12PEN_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH13PEN                                  (0x1UL << 13)                                 /**< ASYNCH13 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH13PEN_SHIFT                           13                                            /**< Shift value for GPIO_ASYNCH13PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH13PEN_MASK                            0x2000UL                                      /**< Bit mask for GPIO_ASYNCH13PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH13PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH13PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH13PEN_DEFAULT << 13) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH14PEN                                  (0x1UL << 14)                                 /**< ASYNCH14 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH14PEN_SHIFT                           14                                            /**< Shift value for GPIO_ASYNCH14PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH14PEN_MASK                            0x4000UL                                      /**< Bit mask for GPIO_ASYNCH14PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH14PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH14PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH14PEN_DEFAULT << 14) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_ASYNCH15PEN                                  (0x1UL << 15)                                 /**< ASYNCH15 pin enable control bit             */
#define _GPIO_PRS_ROUTEEN_ASYNCH15PEN_SHIFT                           15                                            /**< Shift value for GPIO_ASYNCH15PEN            */
#define _GPIO_PRS_ROUTEEN_ASYNCH15PEN_MASK                            0x8000UL                                      /**< Bit mask for GPIO_ASYNCH15PEN               */
#define _GPIO_PRS_ROUTEEN_ASYNCH15PEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_ASYNCH15PEN_DEFAULT                          (_GPIO_PRS_ROUTEEN_ASYNCH15PEN_DEFAULT << 15) /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_SYNCH0PEN                                    (0x1UL << 16)                                 /**< SYNCH0 pin enable control bit               */
#define _GPIO_PRS_ROUTEEN_SYNCH0PEN_SHIFT                             16                                            /**< Shift value for GPIO_SYNCH0PEN              */
#define _GPIO_PRS_ROUTEEN_SYNCH0PEN_MASK                              0x10000UL                                     /**< Bit mask for GPIO_SYNCH0PEN                 */
#define _GPIO_PRS_ROUTEEN_SYNCH0PEN_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_SYNCH0PEN_DEFAULT                            (_GPIO_PRS_ROUTEEN_SYNCH0PEN_DEFAULT << 16)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_SYNCH1PEN                                    (0x1UL << 17)                                 /**< SYNCH1 pin enable control bit               */
#define _GPIO_PRS_ROUTEEN_SYNCH1PEN_SHIFT                             17                                            /**< Shift value for GPIO_SYNCH1PEN              */
#define _GPIO_PRS_ROUTEEN_SYNCH1PEN_MASK                              0x20000UL                                     /**< Bit mask for GPIO_SYNCH1PEN                 */
#define _GPIO_PRS_ROUTEEN_SYNCH1PEN_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_SYNCH1PEN_DEFAULT                            (_GPIO_PRS_ROUTEEN_SYNCH1PEN_DEFAULT << 17)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_SYNCH2PEN                                    (0x1UL << 18)                                 /**< SYNCH2 pin enable control bit               */
#define _GPIO_PRS_ROUTEEN_SYNCH2PEN_SHIFT                             18                                            /**< Shift value for GPIO_SYNCH2PEN              */
#define _GPIO_PRS_ROUTEEN_SYNCH2PEN_MASK                              0x40000UL                                     /**< Bit mask for GPIO_SYNCH2PEN                 */
#define _GPIO_PRS_ROUTEEN_SYNCH2PEN_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_SYNCH2PEN_DEFAULT                            (_GPIO_PRS_ROUTEEN_SYNCH2PEN_DEFAULT << 18)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */
#define GPIO_PRS_ROUTEEN_SYNCH3PEN                                    (0x1UL << 19)                                 /**< SYNCH3 pin enable control bit               */
#define _GPIO_PRS_ROUTEEN_SYNCH3PEN_SHIFT                             19                                            /**< Shift value for GPIO_SYNCH3PEN              */
#define _GPIO_PRS_ROUTEEN_SYNCH3PEN_MASK                              0x80000UL                                     /**< Bit mask for GPIO_SYNCH3PEN                 */
#define _GPIO_PRS_ROUTEEN_SYNCH3PEN_DEFAULT                           0x00000000UL                                  /**< Mode DEFAULT for GPIO_PRS_ROUTEEN           */
#define GPIO_PRS_ROUTEEN_SYNCH3PEN_DEFAULT                            (_GPIO_PRS_ROUTEEN_SYNCH3PEN_DEFAULT << 19)   /**< Shifted mode DEFAULT for GPIO_PRS_ROUTEEN   */

/* Bit fields for GPIO_PRS ASYNCH0ROUTE */
#define _GPIO_PRS_ASYNCH0ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH0ROUTE     */
#define _GPIO_PRS_ASYNCH0ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH0ROUTE              */
#define _GPIO_PRS_ASYNCH0ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH0ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH0ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH0ROUTE      */
#define GPIO_PRS_ASYNCH0ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH0ROUTE*/
#define _GPIO_PRS_ASYNCH0ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH0ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH0ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH0ROUTE      */
#define GPIO_PRS_ASYNCH0ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH0ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH1ROUTE */
#define _GPIO_PRS_ASYNCH1ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH1ROUTE     */
#define _GPIO_PRS_ASYNCH1ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH1ROUTE              */
#define _GPIO_PRS_ASYNCH1ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH1ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH1ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH1ROUTE      */
#define GPIO_PRS_ASYNCH1ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH1ROUTE*/
#define _GPIO_PRS_ASYNCH1ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH1ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH1ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH1ROUTE      */
#define GPIO_PRS_ASYNCH1ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH1ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH2ROUTE */
#define _GPIO_PRS_ASYNCH2ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH2ROUTE     */
#define _GPIO_PRS_ASYNCH2ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH2ROUTE              */
#define _GPIO_PRS_ASYNCH2ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH2ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH2ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH2ROUTE      */
#define GPIO_PRS_ASYNCH2ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH2ROUTE*/
#define _GPIO_PRS_ASYNCH2ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH2ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH2ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH2ROUTE      */
#define GPIO_PRS_ASYNCH2ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH2ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH3ROUTE */
#define _GPIO_PRS_ASYNCH3ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH3ROUTE     */
#define _GPIO_PRS_ASYNCH3ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH3ROUTE              */
#define _GPIO_PRS_ASYNCH3ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH3ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH3ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH3ROUTE      */
#define GPIO_PRS_ASYNCH3ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH3ROUTE*/
#define _GPIO_PRS_ASYNCH3ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH3ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH3ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH3ROUTE      */
#define GPIO_PRS_ASYNCH3ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH3ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH4ROUTE */
#define _GPIO_PRS_ASYNCH4ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH4ROUTE     */
#define _GPIO_PRS_ASYNCH4ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH4ROUTE              */
#define _GPIO_PRS_ASYNCH4ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH4ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH4ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH4ROUTE      */
#define GPIO_PRS_ASYNCH4ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH4ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH4ROUTE*/
#define _GPIO_PRS_ASYNCH4ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH4ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH4ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH4ROUTE      */
#define GPIO_PRS_ASYNCH4ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH4ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH4ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH5ROUTE */
#define _GPIO_PRS_ASYNCH5ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH5ROUTE     */
#define _GPIO_PRS_ASYNCH5ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH5ROUTE              */
#define _GPIO_PRS_ASYNCH5ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH5ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH5ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH5ROUTE      */
#define GPIO_PRS_ASYNCH5ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH5ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH5ROUTE*/
#define _GPIO_PRS_ASYNCH5ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH5ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH5ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH5ROUTE      */
#define GPIO_PRS_ASYNCH5ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH5ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH5ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH6ROUTE */
#define _GPIO_PRS_ASYNCH6ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH6ROUTE     */
#define _GPIO_PRS_ASYNCH6ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH6ROUTE              */
#define _GPIO_PRS_ASYNCH6ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH6ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH6ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH6ROUTE      */
#define GPIO_PRS_ASYNCH6ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH6ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH6ROUTE*/
#define _GPIO_PRS_ASYNCH6ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH6ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH6ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH6ROUTE      */
#define GPIO_PRS_ASYNCH6ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH6ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH6ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH7ROUTE */
#define _GPIO_PRS_ASYNCH7ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH7ROUTE     */
#define _GPIO_PRS_ASYNCH7ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH7ROUTE              */
#define _GPIO_PRS_ASYNCH7ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH7ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH7ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH7ROUTE      */
#define GPIO_PRS_ASYNCH7ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH7ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH7ROUTE*/
#define _GPIO_PRS_ASYNCH7ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH7ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH7ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH7ROUTE      */
#define GPIO_PRS_ASYNCH7ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH7ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH7ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH8ROUTE */
#define _GPIO_PRS_ASYNCH8ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH8ROUTE     */
#define _GPIO_PRS_ASYNCH8ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH8ROUTE              */
#define _GPIO_PRS_ASYNCH8ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH8ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH8ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH8ROUTE      */
#define GPIO_PRS_ASYNCH8ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH8ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH8ROUTE*/
#define _GPIO_PRS_ASYNCH8ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH8ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH8ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH8ROUTE      */
#define GPIO_PRS_ASYNCH8ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH8ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH8ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH9ROUTE */
#define _GPIO_PRS_ASYNCH9ROUTE_RESETVALUE                             0x00000000UL                               /**< Default value for GPIO_PRS_ASYNCH9ROUTE     */
#define _GPIO_PRS_ASYNCH9ROUTE_MASK                                   0x000F0003UL                               /**< Mask for GPIO_PRS_ASYNCH9ROUTE              */
#define _GPIO_PRS_ASYNCH9ROUTE_PORT_SHIFT                             0                                          /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH9ROUTE_PORT_MASK                              0x3UL                                      /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH9ROUTE_PORT_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH9ROUTE      */
#define GPIO_PRS_ASYNCH9ROUTE_PORT_DEFAULT                            (_GPIO_PRS_ASYNCH9ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH9ROUTE*/
#define _GPIO_PRS_ASYNCH9ROUTE_PIN_SHIFT                              16                                         /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH9ROUTE_PIN_MASK                               0xF0000UL                                  /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH9ROUTE_PIN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_PRS_ASYNCH9ROUTE      */
#define GPIO_PRS_ASYNCH9ROUTE_PIN_DEFAULT                             (_GPIO_PRS_ASYNCH9ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH9ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH10ROUTE */
#define _GPIO_PRS_ASYNCH10ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH10ROUTE    */
#define _GPIO_PRS_ASYNCH10ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH10ROUTE             */
#define _GPIO_PRS_ASYNCH10ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH10ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH10ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH10ROUTE     */
#define GPIO_PRS_ASYNCH10ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH10ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH10ROUTE*/
#define _GPIO_PRS_ASYNCH10ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH10ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH10ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH10ROUTE     */
#define GPIO_PRS_ASYNCH10ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH10ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH10ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH11ROUTE */
#define _GPIO_PRS_ASYNCH11ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH11ROUTE    */
#define _GPIO_PRS_ASYNCH11ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH11ROUTE             */
#define _GPIO_PRS_ASYNCH11ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH11ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH11ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH11ROUTE     */
#define GPIO_PRS_ASYNCH11ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH11ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH11ROUTE*/
#define _GPIO_PRS_ASYNCH11ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH11ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH11ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH11ROUTE     */
#define GPIO_PRS_ASYNCH11ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH11ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH11ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH12ROUTE */
#define _GPIO_PRS_ASYNCH12ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH12ROUTE    */
#define _GPIO_PRS_ASYNCH12ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH12ROUTE             */
#define _GPIO_PRS_ASYNCH12ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH12ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH12ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH12ROUTE     */
#define GPIO_PRS_ASYNCH12ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH12ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH12ROUTE*/
#define _GPIO_PRS_ASYNCH12ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH12ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH12ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH12ROUTE     */
#define GPIO_PRS_ASYNCH12ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH12ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH12ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH13ROUTE */
#define _GPIO_PRS_ASYNCH13ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH13ROUTE    */
#define _GPIO_PRS_ASYNCH13ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH13ROUTE             */
#define _GPIO_PRS_ASYNCH13ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH13ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH13ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH13ROUTE     */
#define GPIO_PRS_ASYNCH13ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH13ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH13ROUTE*/
#define _GPIO_PRS_ASYNCH13ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH13ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH13ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH13ROUTE     */
#define GPIO_PRS_ASYNCH13ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH13ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH13ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH14ROUTE */
#define _GPIO_PRS_ASYNCH14ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH14ROUTE    */
#define _GPIO_PRS_ASYNCH14ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH14ROUTE             */
#define _GPIO_PRS_ASYNCH14ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH14ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH14ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH14ROUTE     */
#define GPIO_PRS_ASYNCH14ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH14ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH14ROUTE*/
#define _GPIO_PRS_ASYNCH14ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH14ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH14ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH14ROUTE     */
#define GPIO_PRS_ASYNCH14ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH14ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH14ROUTE*/

/* Bit fields for GPIO_PRS ASYNCH15ROUTE */
#define _GPIO_PRS_ASYNCH15ROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_PRS_ASYNCH15ROUTE    */
#define _GPIO_PRS_ASYNCH15ROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_PRS_ASYNCH15ROUTE             */
#define _GPIO_PRS_ASYNCH15ROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_ASYNCH15ROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_ASYNCH15ROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH15ROUTE     */
#define GPIO_PRS_ASYNCH15ROUTE_PORT_DEFAULT                           (_GPIO_PRS_ASYNCH15ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH15ROUTE*/
#define _GPIO_PRS_ASYNCH15ROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_ASYNCH15ROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_ASYNCH15ROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_PRS_ASYNCH15ROUTE     */
#define GPIO_PRS_ASYNCH15ROUTE_PIN_DEFAULT                            (_GPIO_PRS_ASYNCH15ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_ASYNCH15ROUTE*/

/* Bit fields for GPIO_PRS SYNCH0ROUTE */
#define _GPIO_PRS_SYNCH0ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_PRS_SYNCH0ROUTE      */
#define _GPIO_PRS_SYNCH0ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_PRS_SYNCH0ROUTE               */
#define _GPIO_PRS_SYNCH0ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_SYNCH0ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_SYNCH0ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH0ROUTE       */
#define GPIO_PRS_SYNCH0ROUTE_PORT_DEFAULT                             (_GPIO_PRS_SYNCH0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH0ROUTE*/
#define _GPIO_PRS_SYNCH0ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_SYNCH0ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_SYNCH0ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH0ROUTE       */
#define GPIO_PRS_SYNCH0ROUTE_PIN_DEFAULT                              (_GPIO_PRS_SYNCH0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH0ROUTE*/

/* Bit fields for GPIO_PRS SYNCH1ROUTE */
#define _GPIO_PRS_SYNCH1ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_PRS_SYNCH1ROUTE      */
#define _GPIO_PRS_SYNCH1ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_PRS_SYNCH1ROUTE               */
#define _GPIO_PRS_SYNCH1ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_SYNCH1ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_SYNCH1ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH1ROUTE       */
#define GPIO_PRS_SYNCH1ROUTE_PORT_DEFAULT                             (_GPIO_PRS_SYNCH1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH1ROUTE*/
#define _GPIO_PRS_SYNCH1ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_SYNCH1ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_SYNCH1ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH1ROUTE       */
#define GPIO_PRS_SYNCH1ROUTE_PIN_DEFAULT                              (_GPIO_PRS_SYNCH1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH1ROUTE*/

/* Bit fields for GPIO_PRS SYNCH2ROUTE */
#define _GPIO_PRS_SYNCH2ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_PRS_SYNCH2ROUTE      */
#define _GPIO_PRS_SYNCH2ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_PRS_SYNCH2ROUTE               */
#define _GPIO_PRS_SYNCH2ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_SYNCH2ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_SYNCH2ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH2ROUTE       */
#define GPIO_PRS_SYNCH2ROUTE_PORT_DEFAULT                             (_GPIO_PRS_SYNCH2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH2ROUTE*/
#define _GPIO_PRS_SYNCH2ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_SYNCH2ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_SYNCH2ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH2ROUTE       */
#define GPIO_PRS_SYNCH2ROUTE_PIN_DEFAULT                              (_GPIO_PRS_SYNCH2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH2ROUTE*/

/* Bit fields for GPIO_PRS SYNCH3ROUTE */
#define _GPIO_PRS_SYNCH3ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_PRS_SYNCH3ROUTE      */
#define _GPIO_PRS_SYNCH3ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_PRS_SYNCH3ROUTE               */
#define _GPIO_PRS_SYNCH3ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_PRS_SYNCH3ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_PRS_SYNCH3ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH3ROUTE       */
#define GPIO_PRS_SYNCH3ROUTE_PORT_DEFAULT                             (_GPIO_PRS_SYNCH3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH3ROUTE*/
#define _GPIO_PRS_SYNCH3ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_PRS_SYNCH3ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_PRS_SYNCH3ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_PRS_SYNCH3ROUTE       */
#define GPIO_PRS_SYNCH3ROUTE_PIN_DEFAULT                              (_GPIO_PRS_SYNCH3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_PRS_SYNCH3ROUTE*/

/* Bit fields for GPIO_DBUSRAC ROUTEEN */
#define _GPIO_DBUSRAC_ROUTEEN_RESETVALUE                              0x00000000UL                                  /**< Default value for GPIO_DBUSRAC_ROUTEEN      */
#define _GPIO_DBUSRAC_ROUTEEN_MASK                                    0x00000003UL                                  /**< Mask for GPIO_DBUSRAC_ROUTEEN               */
#define GPIO_DBUSRAC_ROUTEEN_LNAENPEN                                 (0x1UL << 0)                                  /**< LNAEN pin enable control bit                */
#define _GPIO_DBUSRAC_ROUTEEN_LNAENPEN_SHIFT                          0                                             /**< Shift value for GPIO_LNAENPEN               */
#define _GPIO_DBUSRAC_ROUTEEN_LNAENPEN_MASK                           0x1UL                                         /**< Bit mask for GPIO_LNAENPEN                  */
#define _GPIO_DBUSRAC_ROUTEEN_LNAENPEN_DEFAULT                        0x00000000UL                                  /**< Mode DEFAULT for GPIO_DBUSRAC_ROUTEEN       */
#define GPIO_DBUSRAC_ROUTEEN_LNAENPEN_DEFAULT                         (_GPIO_DBUSRAC_ROUTEEN_LNAENPEN_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRAC_ROUTEEN*/
#define GPIO_DBUSRAC_ROUTEEN_PAENPEN                                  (0x1UL << 1)                                  /**< PAEN pin enable control bit                 */
#define _GPIO_DBUSRAC_ROUTEEN_PAENPEN_SHIFT                           1                                             /**< Shift value for GPIO_PAENPEN                */
#define _GPIO_DBUSRAC_ROUTEEN_PAENPEN_MASK                            0x2UL                                         /**< Bit mask for GPIO_PAENPEN                   */
#define _GPIO_DBUSRAC_ROUTEEN_PAENPEN_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_DBUSRAC_ROUTEEN       */
#define GPIO_DBUSRAC_ROUTEEN_PAENPEN_DEFAULT                          (_GPIO_DBUSRAC_ROUTEEN_PAENPEN_DEFAULT << 1)  /**< Shifted mode DEFAULT for GPIO_DBUSRAC_ROUTEEN*/

/* Bit fields for GPIO_DBUSRAC LNAENROUTE */
#define _GPIO_DBUSRAC_LNAENROUTE_RESETVALUE                           0x00000000UL                                 /**< Default value for GPIO_DBUSRAC_LNAENROUTE   */
#define _GPIO_DBUSRAC_LNAENROUTE_MASK                                 0x000F0003UL                                 /**< Mask for GPIO_DBUSRAC_LNAENROUTE            */
#define _GPIO_DBUSRAC_LNAENROUTE_PORT_SHIFT                           0                                            /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRAC_LNAENROUTE_PORT_MASK                            0x3UL                                        /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRAC_LNAENROUTE_PORT_DEFAULT                         0x00000000UL                                 /**< Mode DEFAULT for GPIO_DBUSRAC_LNAENROUTE    */
#define GPIO_DBUSRAC_LNAENROUTE_PORT_DEFAULT                          (_GPIO_DBUSRAC_LNAENROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRAC_LNAENROUTE*/
#define _GPIO_DBUSRAC_LNAENROUTE_PIN_SHIFT                            16                                           /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRAC_LNAENROUTE_PIN_MASK                             0xF0000UL                                    /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRAC_LNAENROUTE_PIN_DEFAULT                          0x00000000UL                                 /**< Mode DEFAULT for GPIO_DBUSRAC_LNAENROUTE    */
#define GPIO_DBUSRAC_LNAENROUTE_PIN_DEFAULT                           (_GPIO_DBUSRAC_LNAENROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRAC_LNAENROUTE*/

/* Bit fields for GPIO_DBUSRAC PAENROUTE */
#define _GPIO_DBUSRAC_PAENROUTE_RESETVALUE                            0x00000000UL                                /**< Default value for GPIO_DBUSRAC_PAENROUTE    */
#define _GPIO_DBUSRAC_PAENROUTE_MASK                                  0x000F0003UL                                /**< Mask for GPIO_DBUSRAC_PAENROUTE             */
#define _GPIO_DBUSRAC_PAENROUTE_PORT_SHIFT                            0                                           /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRAC_PAENROUTE_PORT_MASK                             0x3UL                                       /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRAC_PAENROUTE_PORT_DEFAULT                          0x00000000UL                                /**< Mode DEFAULT for GPIO_DBUSRAC_PAENROUTE     */
#define GPIO_DBUSRAC_PAENROUTE_PORT_DEFAULT                           (_GPIO_DBUSRAC_PAENROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRAC_PAENROUTE*/
#define _GPIO_DBUSRAC_PAENROUTE_PIN_SHIFT                             16                                          /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRAC_PAENROUTE_PIN_MASK                              0xF0000UL                                   /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRAC_PAENROUTE_PIN_DEFAULT                           0x00000000UL                                /**< Mode DEFAULT for GPIO_DBUSRAC_PAENROUTE     */
#define GPIO_DBUSRAC_PAENROUTE_PIN_DEFAULT                            (_GPIO_DBUSRAC_PAENROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRAC_PAENROUTE*/

/* Bit fields for GPIO_DBUSRFECA ROUTEEN */
#define _GPIO_DBUSRFECA_ROUTEEN_RESETVALUE                            0x00000000UL                                         /**< Default value for GPIO_DBUSRFECA_ROUTEEN    */
#define _GPIO_DBUSRFECA_ROUTEEN_MASK                                  0x000FFFFFUL                                         /**< Mask for GPIO_DBUSRFECA_ROUTEEN             */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN                            (0x1UL << 0)                                         /**< DATAOUT0 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN_SHIFT                     0                                                    /**< Shift value for GPIO_DATAOUT0PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN_MASK                      0x1UL                                                /**< Bit mask for GPIO_DATAOUT0PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT0PEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN                            (0x1UL << 1)                                         /**< DATAOUT1 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN_SHIFT                     1                                                    /**< Shift value for GPIO_DATAOUT1PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN_MASK                      0x2UL                                                /**< Bit mask for GPIO_DATAOUT1PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT1PEN_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN                            (0x1UL << 2)                                         /**< DATAOUT2 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN_SHIFT                     2                                                    /**< Shift value for GPIO_DATAOUT2PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN_MASK                      0x4UL                                                /**< Bit mask for GPIO_DATAOUT2PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT2PEN_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN                            (0x1UL << 3)                                         /**< DATAOUT3 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN_SHIFT                     3                                                    /**< Shift value for GPIO_DATAOUT3PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN_MASK                      0x8UL                                                /**< Bit mask for GPIO_DATAOUT3PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT3PEN_DEFAULT << 3)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN                            (0x1UL << 4)                                         /**< DATAOUT4 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN_SHIFT                     4                                                    /**< Shift value for GPIO_DATAOUT4PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN_MASK                      0x10UL                                               /**< Bit mask for GPIO_DATAOUT4PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT4PEN_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN                            (0x1UL << 5)                                         /**< DATAOUT5 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN_SHIFT                     5                                                    /**< Shift value for GPIO_DATAOUT5PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN_MASK                      0x20UL                                               /**< Bit mask for GPIO_DATAOUT5PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT5PEN_DEFAULT << 5)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN                            (0x1UL << 6)                                         /**< DATAOUT6 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN_SHIFT                     6                                                    /**< Shift value for GPIO_DATAOUT6PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN_MASK                      0x40UL                                               /**< Bit mask for GPIO_DATAOUT6PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT6PEN_DEFAULT << 6)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN                            (0x1UL << 7)                                         /**< DATAOUT7 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN_SHIFT                     7                                                    /**< Shift value for GPIO_DATAOUT7PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN_MASK                      0x80UL                                               /**< Bit mask for GPIO_DATAOUT7PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT7PEN_DEFAULT << 7)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN                            (0x1UL << 8)                                         /**< DATAOUT8 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN_SHIFT                     8                                                    /**< Shift value for GPIO_DATAOUT8PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN_MASK                      0x100UL                                              /**< Bit mask for GPIO_DATAOUT8PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT8PEN_DEFAULT << 8)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN                            (0x1UL << 9)                                         /**< DATAOUT9 pin enable control bit             */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN_SHIFT                     9                                                    /**< Shift value for GPIO_DATAOUT9PEN            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN_MASK                      0x200UL                                              /**< Bit mask for GPIO_DATAOUT9PEN               */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN_DEFAULT                   0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN_DEFAULT                    (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT9PEN_DEFAULT << 9)   /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN                           (0x1UL << 10)                                        /**< DATAOUT10 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN_SHIFT                    10                                                   /**< Shift value for GPIO_DATAOUT10PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN_MASK                     0x400UL                                              /**< Bit mask for GPIO_DATAOUT10PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT10PEN_DEFAULT << 10) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN                           (0x1UL << 11)                                        /**< DATAOUT11 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN_SHIFT                    11                                                   /**< Shift value for GPIO_DATAOUT11PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN_MASK                     0x800UL                                              /**< Bit mask for GPIO_DATAOUT11PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT11PEN_DEFAULT << 11) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN                           (0x1UL << 12)                                        /**< DATAOUT12 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN_SHIFT                    12                                                   /**< Shift value for GPIO_DATAOUT12PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN_MASK                     0x1000UL                                             /**< Bit mask for GPIO_DATAOUT12PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT12PEN_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN                           (0x1UL << 13)                                        /**< DATAOUT13 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN_SHIFT                    13                                                   /**< Shift value for GPIO_DATAOUT13PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN_MASK                     0x2000UL                                             /**< Bit mask for GPIO_DATAOUT13PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT13PEN_DEFAULT << 13) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN                           (0x1UL << 14)                                        /**< DATAOUT14 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN_SHIFT                    14                                                   /**< Shift value for GPIO_DATAOUT14PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN_MASK                     0x4000UL                                             /**< Bit mask for GPIO_DATAOUT14PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT14PEN_DEFAULT << 14) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN                           (0x1UL << 15)                                        /**< DATAOUT15 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN_SHIFT                    15                                                   /**< Shift value for GPIO_DATAOUT15PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN_MASK                     0x8000UL                                             /**< Bit mask for GPIO_DATAOUT15PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT15PEN_DEFAULT << 15) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN                           (0x1UL << 16)                                        /**< DATAOUT16 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN_SHIFT                    16                                                   /**< Shift value for GPIO_DATAOUT16PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN_MASK                     0x10000UL                                            /**< Bit mask for GPIO_DATAOUT16PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT16PEN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN                           (0x1UL << 17)                                        /**< DATAOUT17 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN_SHIFT                    17                                                   /**< Shift value for GPIO_DATAOUT17PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN_MASK                     0x20000UL                                            /**< Bit mask for GPIO_DATAOUT17PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT17PEN_DEFAULT << 17) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN                           (0x1UL << 18)                                        /**< DATAOUT18 pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN_SHIFT                    18                                                   /**< Shift value for GPIO_DATAOUT18PEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN_MASK                     0x40000UL                                            /**< Bit mask for GPIO_DATAOUT18PEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAOUT18PEN_DEFAULT << 18) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/
#define GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN                           (0x1UL << 19)                                        /**< DATAVALID pin enable control bit            */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN_SHIFT                    19                                                   /**< Shift value for GPIO_DATAVALIDPEN           */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN_MASK                     0x80000UL                                            /**< Bit mask for GPIO_DATAVALIDPEN              */
#define _GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN_DEFAULT                  0x00000000UL                                         /**< Mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN     */
#define GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN_DEFAULT                   (_GPIO_DBUSRFECA_ROUTEEN_DATAVALIDPEN_DEFAULT << 19) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_ROUTEEN*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT0ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT0ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT0ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT0ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT0ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT0ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT0ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT0ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT0ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT0ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT1ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT1ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT1ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT1ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT1ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT1ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT1ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT1ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT1ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT1ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT2ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT2ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT2ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT2ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT2ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT2ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT2ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT2ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT2ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT2ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT3ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT3ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT3ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT3ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT3ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT3ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT3ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT3ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT3ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT3ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT3ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT3ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT4ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT4ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT4ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT4ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT4ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT4ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT4ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT4ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT4ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT4ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT4ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT4ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT5ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT5ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT5ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT5ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT5ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT5ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT5ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT5ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT5ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT5ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT5ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT5ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT6ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT6ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT6ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT6ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT6ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT6ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT6ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT6ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT6ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT6ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT6ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT6ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT7ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT7ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT7ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT7ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT7ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT7ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT7ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT7ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT7ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT7ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT7ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT7ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT8ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT8ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT8ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT8ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT8ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT8ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT8ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT8ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT8ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT8ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT8ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT8ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT9ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_RESETVALUE                      0x00000000UL                                      /**< Default value for GPIO_DBUSRFECA_DATAOUT9ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_MASK                            0x000F0003UL                                      /**< Mask for GPIO_DBUSRFECA_DATAOUT9ROUTE       */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PORT_SHIFT                      0                                                 /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PORT_MASK                       0x3UL                                             /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PORT_DEFAULT                    0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT9ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT9ROUTE_PORT_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT9ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT9ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PIN_SHIFT                       16                                                /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PIN_MASK                        0xF0000UL                                         /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT9ROUTE_PIN_DEFAULT                     0x00000000UL                                      /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT9ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT9ROUTE_PIN_DEFAULT                      (_GPIO_DBUSRFECA_DATAOUT9ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT9ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT10ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT10ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT10ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT10ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT10ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT10ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT10ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT10ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT10ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT10ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT10ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT10ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT11ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT11ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT11ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT11ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT11ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT11ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT11ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT11ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT11ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT11ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT11ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT11ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT12ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT12ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT12ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT12ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT12ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT12ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT12ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT12ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT12ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT12ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT12ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT12ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT13ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT13ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT13ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT13ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT13ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT13ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT13ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT13ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT13ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT13ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT13ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT13ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT14ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT14ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT14ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT14ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT14ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT14ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT14ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT14ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT14ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT14ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT14ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT14ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT15ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT15ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT15ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT15ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT15ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT15ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT15ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT15ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT15ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT15ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT15ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT15ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT16ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT16ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT16ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT16ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT16ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT16ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT16ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT16ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT16ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT16ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT16ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT16ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT17ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT17ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT17ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT17ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT17ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT17ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT17ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT17ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT17ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT17ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT17ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT17ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAOUT18ROUTE */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAOUT18ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAOUT18ROUTE      */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT18ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT18ROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAOUT18ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT18ROUTE*/
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAOUT18ROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAOUT18ROUTE*/
#define GPIO_DBUSRFECA_DATAOUT18ROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAOUT18ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAOUT18ROUTE*/

/* Bit fields for GPIO_DBUSRFECA DATAVALIDROUTE */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_DATAVALIDROUTE*/
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_DATAVALIDROUTE      */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAVALIDROUTE*/
#define GPIO_DBUSRFECA_DATAVALIDROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_DATAVALIDROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAVALIDROUTE*/
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_DATAVALIDROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_DATAVALIDROUTE*/
#define GPIO_DBUSRFECA_DATAVALIDROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_DATAVALIDROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_DATAVALIDROUTE*/

/* Bit fields for GPIO_DBUSRFECA TRIGGERINROUTE */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_RESETVALUE                     0x00000000UL                                       /**< Default value for GPIO_DBUSRFECA_TRIGGERINROUTE*/
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_MASK                           0x000F0003UL                                       /**< Mask for GPIO_DBUSRFECA_TRIGGERINROUTE      */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PORT_SHIFT                     0                                                  /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PORT_MASK                      0x3UL                                              /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PORT_DEFAULT                   0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_TRIGGERINROUTE*/
#define GPIO_DBUSRFECA_TRIGGERINROUTE_PORT_DEFAULT                    (_GPIO_DBUSRFECA_TRIGGERINROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_TRIGGERINROUTE*/
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PIN_SHIFT                      16                                                 /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PIN_MASK                       0xF0000UL                                          /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSRFECA_TRIGGERINROUTE_PIN_DEFAULT                    0x00000000UL                                       /**< Mode DEFAULT for GPIO_DBUSRFECA_TRIGGERINROUTE*/
#define GPIO_DBUSRFECA_TRIGGERINROUTE_PIN_DEFAULT                     (_GPIO_DBUSRFECA_TRIGGERINROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSRFECA_TRIGGERINROUTE*/

/* Bit fields for GPIO_DBUSSYXO BUFOUTREQINASYNCROUTE */
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_RESETVALUE               0x00000000UL                                             /**< Default value for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_MASK                     0x000F0003UL                                             /**< Mask for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PORT_SHIFT               0                                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PORT_MASK                0x3UL                                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PORT_DEFAULT             0x00000000UL                                             /**< Mode DEFAULT for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/
#define GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PORT_DEFAULT              (_GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PIN_SHIFT                16                                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PIN_MASK                 0xF0000UL                                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PIN_DEFAULT              0x00000000UL                                             /**< Mode DEFAULT for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/
#define GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PIN_DEFAULT               (_GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_DBUSSYXO_BUFOUTREQINASYNCROUTE*/

/* Bit fields for GPIO_TIMER ROUTEEN */
#define _GPIO_TIMER_ROUTEEN_RESETVALUE                                0x00000000UL                               /**< Default value for GPIO_TIMER_ROUTEEN        */
#define _GPIO_TIMER_ROUTEEN_MASK                                      0x0000003FUL                               /**< Mask for GPIO_TIMER_ROUTEEN                 */
#define GPIO_TIMER_ROUTEEN_CC0PEN                                     (0x1UL << 0)                               /**< CC0 pin enable control bit                  */
#define _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT                              0                                          /**< Shift value for GPIO_CC0PEN                 */
#define _GPIO_TIMER_ROUTEEN_CC0PEN_MASK                               0x1UL                                      /**< Bit mask for GPIO_CC0PEN                    */
#define _GPIO_TIMER_ROUTEEN_CC0PEN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CC0PEN_DEFAULT                             (_GPIO_TIMER_ROUTEEN_CC0PEN_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */
#define GPIO_TIMER_ROUTEEN_CC1PEN                                     (0x1UL << 1)                               /**< CC1 pin enable control bit                  */
#define _GPIO_TIMER_ROUTEEN_CC1PEN_SHIFT                              1                                          /**< Shift value for GPIO_CC1PEN                 */
#define _GPIO_TIMER_ROUTEEN_CC1PEN_MASK                               0x2UL                                      /**< Bit mask for GPIO_CC1PEN                    */
#define _GPIO_TIMER_ROUTEEN_CC1PEN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CC1PEN_DEFAULT                             (_GPIO_TIMER_ROUTEEN_CC1PEN_DEFAULT << 1)  /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */
#define GPIO_TIMER_ROUTEEN_CC2PEN                                     (0x1UL << 2)                               /**< CC2 pin enable control bit                  */
#define _GPIO_TIMER_ROUTEEN_CC2PEN_SHIFT                              2                                          /**< Shift value for GPIO_CC2PEN                 */
#define _GPIO_TIMER_ROUTEEN_CC2PEN_MASK                               0x4UL                                      /**< Bit mask for GPIO_CC2PEN                    */
#define _GPIO_TIMER_ROUTEEN_CC2PEN_DEFAULT                            0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CC2PEN_DEFAULT                             (_GPIO_TIMER_ROUTEEN_CC2PEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */
#define GPIO_TIMER_ROUTEEN_CCC0PEN                                    (0x1UL << 3)                               /**< CCC0 pin enable control bit                 */
#define _GPIO_TIMER_ROUTEEN_CCC0PEN_SHIFT                             3                                          /**< Shift value for GPIO_CCC0PEN                */
#define _GPIO_TIMER_ROUTEEN_CCC0PEN_MASK                              0x8UL                                      /**< Bit mask for GPIO_CCC0PEN                   */
#define _GPIO_TIMER_ROUTEEN_CCC0PEN_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CCC0PEN_DEFAULT                            (_GPIO_TIMER_ROUTEEN_CCC0PEN_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */
#define GPIO_TIMER_ROUTEEN_CCC1PEN                                    (0x1UL << 4)                               /**< CCC1 pin enable control bit                 */
#define _GPIO_TIMER_ROUTEEN_CCC1PEN_SHIFT                             4                                          /**< Shift value for GPIO_CCC1PEN                */
#define _GPIO_TIMER_ROUTEEN_CCC1PEN_MASK                              0x10UL                                     /**< Bit mask for GPIO_CCC1PEN                   */
#define _GPIO_TIMER_ROUTEEN_CCC1PEN_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CCC1PEN_DEFAULT                            (_GPIO_TIMER_ROUTEEN_CCC1PEN_DEFAULT << 4) /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */
#define GPIO_TIMER_ROUTEEN_CCC2PEN                                    (0x1UL << 5)                               /**< CCC2 pin enable control bit                 */
#define _GPIO_TIMER_ROUTEEN_CCC2PEN_SHIFT                             5                                          /**< Shift value for GPIO_CCC2PEN                */
#define _GPIO_TIMER_ROUTEEN_CCC2PEN_MASK                              0x20UL                                     /**< Bit mask for GPIO_CCC2PEN                   */
#define _GPIO_TIMER_ROUTEEN_CCC2PEN_DEFAULT                           0x00000000UL                               /**< Mode DEFAULT for GPIO_TIMER_ROUTEEN         */
#define GPIO_TIMER_ROUTEEN_CCC2PEN_DEFAULT                            (_GPIO_TIMER_ROUTEEN_CCC2PEN_DEFAULT << 5) /**< Shifted mode DEFAULT for GPIO_TIMER_ROUTEEN */

/* Bit fields for GPIO_TIMER CC0ROUTE */
#define _GPIO_TIMER_CC0ROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_TIMER_CC0ROUTE       */
#define _GPIO_TIMER_CC0ROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_TIMER_CC0ROUTE                */
#define _GPIO_TIMER_CC0ROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CC0ROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CC0ROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC0ROUTE        */
#define GPIO_TIMER_CC0ROUTE_PORT_DEFAULT                              (_GPIO_TIMER_CC0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CC0ROUTE*/
#define _GPIO_TIMER_CC0ROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CC0ROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CC0ROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC0ROUTE        */
#define GPIO_TIMER_CC0ROUTE_PIN_DEFAULT                               (_GPIO_TIMER_CC0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CC0ROUTE*/

/* Bit fields for GPIO_TIMER CC1ROUTE */
#define _GPIO_TIMER_CC1ROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_TIMER_CC1ROUTE       */
#define _GPIO_TIMER_CC1ROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_TIMER_CC1ROUTE                */
#define _GPIO_TIMER_CC1ROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CC1ROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CC1ROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC1ROUTE        */
#define GPIO_TIMER_CC1ROUTE_PORT_DEFAULT                              (_GPIO_TIMER_CC1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CC1ROUTE*/
#define _GPIO_TIMER_CC1ROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CC1ROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CC1ROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC1ROUTE        */
#define GPIO_TIMER_CC1ROUTE_PIN_DEFAULT                               (_GPIO_TIMER_CC1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CC1ROUTE*/

/* Bit fields for GPIO_TIMER CC2ROUTE */
#define _GPIO_TIMER_CC2ROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_TIMER_CC2ROUTE       */
#define _GPIO_TIMER_CC2ROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_TIMER_CC2ROUTE                */
#define _GPIO_TIMER_CC2ROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CC2ROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CC2ROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC2ROUTE        */
#define GPIO_TIMER_CC2ROUTE_PORT_DEFAULT                              (_GPIO_TIMER_CC2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CC2ROUTE*/
#define _GPIO_TIMER_CC2ROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CC2ROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CC2ROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_TIMER_CC2ROUTE        */
#define GPIO_TIMER_CC2ROUTE_PIN_DEFAULT                               (_GPIO_TIMER_CC2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CC2ROUTE*/

/* Bit fields for GPIO_TIMER CCC0ROUTE */
#define _GPIO_TIMER_CCC0ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_TIMER_CCC0ROUTE      */
#define _GPIO_TIMER_CCC0ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_TIMER_CCC0ROUTE               */
#define _GPIO_TIMER_CCC0ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CCC0ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CCC0ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC0ROUTE       */
#define GPIO_TIMER_CCC0ROUTE_PORT_DEFAULT                             (_GPIO_TIMER_CCC0ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC0ROUTE*/
#define _GPIO_TIMER_CCC0ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CCC0ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CCC0ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC0ROUTE       */
#define GPIO_TIMER_CCC0ROUTE_PIN_DEFAULT                              (_GPIO_TIMER_CCC0ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC0ROUTE*/

/* Bit fields for GPIO_TIMER CCC1ROUTE */
#define _GPIO_TIMER_CCC1ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_TIMER_CCC1ROUTE      */
#define _GPIO_TIMER_CCC1ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_TIMER_CCC1ROUTE               */
#define _GPIO_TIMER_CCC1ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CCC1ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CCC1ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC1ROUTE       */
#define GPIO_TIMER_CCC1ROUTE_PORT_DEFAULT                             (_GPIO_TIMER_CCC1ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC1ROUTE*/
#define _GPIO_TIMER_CCC1ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CCC1ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CCC1ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC1ROUTE       */
#define GPIO_TIMER_CCC1ROUTE_PIN_DEFAULT                              (_GPIO_TIMER_CCC1ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC1ROUTE*/

/* Bit fields for GPIO_TIMER CCC2ROUTE */
#define _GPIO_TIMER_CCC2ROUTE_RESETVALUE                              0x00000000UL                              /**< Default value for GPIO_TIMER_CCC2ROUTE      */
#define _GPIO_TIMER_CCC2ROUTE_MASK                                    0x000F0003UL                              /**< Mask for GPIO_TIMER_CCC2ROUTE               */
#define _GPIO_TIMER_CCC2ROUTE_PORT_SHIFT                              0                                         /**< Shift value for GPIO_PORT                   */
#define _GPIO_TIMER_CCC2ROUTE_PORT_MASK                               0x3UL                                     /**< Bit mask for GPIO_PORT                      */
#define _GPIO_TIMER_CCC2ROUTE_PORT_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC2ROUTE       */
#define GPIO_TIMER_CCC2ROUTE_PORT_DEFAULT                             (_GPIO_TIMER_CCC2ROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC2ROUTE*/
#define _GPIO_TIMER_CCC2ROUTE_PIN_SHIFT                               16                                        /**< Shift value for GPIO_PIN                    */
#define _GPIO_TIMER_CCC2ROUTE_PIN_MASK                                0xF0000UL                                 /**< Bit mask for GPIO_PIN                       */
#define _GPIO_TIMER_CCC2ROUTE_PIN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_TIMER_CCC2ROUTE       */
#define GPIO_TIMER_CCC2ROUTE_PIN_DEFAULT                              (_GPIO_TIMER_CCC2ROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_TIMER_CCC2ROUTE*/

/* Bit fields for GPIO_USART ROUTEEN */
#define _GPIO_USART_ROUTEEN_RESETVALUE                                0x00000000UL                              /**< Default value for GPIO_USART_ROUTEEN        */
#define _GPIO_USART_ROUTEEN_MASK                                      0x0000001FUL                              /**< Mask for GPIO_USART_ROUTEEN                 */
#define GPIO_USART_ROUTEEN_CSPEN                                      (0x1UL << 0)                              /**< CS pin enable control bit                   */
#define _GPIO_USART_ROUTEEN_CSPEN_SHIFT                               0                                         /**< Shift value for GPIO_CSPEN                  */
#define _GPIO_USART_ROUTEEN_CSPEN_MASK                                0x1UL                                     /**< Bit mask for GPIO_CSPEN                     */
#define _GPIO_USART_ROUTEEN_CSPEN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_USART_ROUTEEN         */
#define GPIO_USART_ROUTEEN_CSPEN_DEFAULT                              (_GPIO_USART_ROUTEEN_CSPEN_DEFAULT << 0)  /**< Shifted mode DEFAULT for GPIO_USART_ROUTEEN */
#define GPIO_USART_ROUTEEN_RTSPEN                                     (0x1UL << 1)                              /**< RTS pin enable control bit                  */
#define _GPIO_USART_ROUTEEN_RTSPEN_SHIFT                              1                                         /**< Shift value for GPIO_RTSPEN                 */
#define _GPIO_USART_ROUTEEN_RTSPEN_MASK                               0x2UL                                     /**< Bit mask for GPIO_RTSPEN                    */
#define _GPIO_USART_ROUTEEN_RTSPEN_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_USART_ROUTEEN         */
#define GPIO_USART_ROUTEEN_RTSPEN_DEFAULT                             (_GPIO_USART_ROUTEEN_RTSPEN_DEFAULT << 1) /**< Shifted mode DEFAULT for GPIO_USART_ROUTEEN */
#define GPIO_USART_ROUTEEN_RXPEN                                      (0x1UL << 2)                              /**< RX pin enable control bit                   */
#define _GPIO_USART_ROUTEEN_RXPEN_SHIFT                               2                                         /**< Shift value for GPIO_RXPEN                  */
#define _GPIO_USART_ROUTEEN_RXPEN_MASK                                0x4UL                                     /**< Bit mask for GPIO_RXPEN                     */
#define _GPIO_USART_ROUTEEN_RXPEN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_USART_ROUTEEN         */
#define GPIO_USART_ROUTEEN_RXPEN_DEFAULT                              (_GPIO_USART_ROUTEEN_RXPEN_DEFAULT << 2)  /**< Shifted mode DEFAULT for GPIO_USART_ROUTEEN */
#define GPIO_USART_ROUTEEN_CLKPEN                                     (0x1UL << 3)                              /**< SCLK pin enable control bit                 */
#define _GPIO_USART_ROUTEEN_CLKPEN_SHIFT                              3                                         /**< Shift value for GPIO_CLKPEN                 */
#define _GPIO_USART_ROUTEEN_CLKPEN_MASK                               0x8UL                                     /**< Bit mask for GPIO_CLKPEN                    */
#define _GPIO_USART_ROUTEEN_CLKPEN_DEFAULT                            0x00000000UL                              /**< Mode DEFAULT for GPIO_USART_ROUTEEN         */
#define GPIO_USART_ROUTEEN_CLKPEN_DEFAULT                             (_GPIO_USART_ROUTEEN_CLKPEN_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_USART_ROUTEEN */
#define GPIO_USART_ROUTEEN_TXPEN                                      (0x1UL << 4)                              /**< TX pin enable control bit                   */
#define _GPIO_USART_ROUTEEN_TXPEN_SHIFT                               4                                         /**< Shift value for GPIO_TXPEN                  */
#define _GPIO_USART_ROUTEEN_TXPEN_MASK                                0x10UL                                    /**< Bit mask for GPIO_TXPEN                     */
#define _GPIO_USART_ROUTEEN_TXPEN_DEFAULT                             0x00000000UL                              /**< Mode DEFAULT for GPIO_USART_ROUTEEN         */
#define GPIO_USART_ROUTEEN_TXPEN_DEFAULT                              (_GPIO_USART_ROUTEEN_TXPEN_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_USART_ROUTEEN */

/* Bit fields for GPIO_USART CSROUTE */
#define _GPIO_USART_CSROUTE_RESETVALUE                                0x00000000UL                            /**< Default value for GPIO_USART_CSROUTE        */
#define _GPIO_USART_CSROUTE_MASK                                      0x000F0003UL                            /**< Mask for GPIO_USART_CSROUTE                 */
#define _GPIO_USART_CSROUTE_PORT_SHIFT                                0                                       /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_CSROUTE_PORT_MASK                                 0x3UL                                   /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_CSROUTE_PORT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_CSROUTE         */
#define GPIO_USART_CSROUTE_PORT_DEFAULT                               (_GPIO_USART_CSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_CSROUTE */
#define _GPIO_USART_CSROUTE_PIN_SHIFT                                 16                                      /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_CSROUTE_PIN_MASK                                  0xF0000UL                               /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_CSROUTE_PIN_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_CSROUTE         */
#define GPIO_USART_CSROUTE_PIN_DEFAULT                                (_GPIO_USART_CSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_CSROUTE */

/* Bit fields for GPIO_USART CTSROUTE */
#define _GPIO_USART_CTSROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_USART_CTSROUTE       */
#define _GPIO_USART_CTSROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_USART_CTSROUTE                */
#define _GPIO_USART_CTSROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_CTSROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_CTSROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_CTSROUTE        */
#define GPIO_USART_CTSROUTE_PORT_DEFAULT                              (_GPIO_USART_CTSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_CTSROUTE*/
#define _GPIO_USART_CTSROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_CTSROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_CTSROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_CTSROUTE        */
#define GPIO_USART_CTSROUTE_PIN_DEFAULT                               (_GPIO_USART_CTSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_CTSROUTE*/

/* Bit fields for GPIO_USART RTSROUTE */
#define _GPIO_USART_RTSROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_USART_RTSROUTE       */
#define _GPIO_USART_RTSROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_USART_RTSROUTE                */
#define _GPIO_USART_RTSROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_RTSROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_RTSROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_RTSROUTE        */
#define GPIO_USART_RTSROUTE_PORT_DEFAULT                              (_GPIO_USART_RTSROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_RTSROUTE*/
#define _GPIO_USART_RTSROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_RTSROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_RTSROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_RTSROUTE        */
#define GPIO_USART_RTSROUTE_PIN_DEFAULT                               (_GPIO_USART_RTSROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_RTSROUTE*/

/* Bit fields for GPIO_USART RXROUTE */
#define _GPIO_USART_RXROUTE_RESETVALUE                                0x00000000UL                            /**< Default value for GPIO_USART_RXROUTE        */
#define _GPIO_USART_RXROUTE_MASK                                      0x000F0003UL                            /**< Mask for GPIO_USART_RXROUTE                 */
#define _GPIO_USART_RXROUTE_PORT_SHIFT                                0                                       /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_RXROUTE_PORT_MASK                                 0x3UL                                   /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_RXROUTE_PORT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_RXROUTE         */
#define GPIO_USART_RXROUTE_PORT_DEFAULT                               (_GPIO_USART_RXROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_RXROUTE */
#define _GPIO_USART_RXROUTE_PIN_SHIFT                                 16                                      /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_RXROUTE_PIN_MASK                                  0xF0000UL                               /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_RXROUTE_PIN_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_RXROUTE         */
#define GPIO_USART_RXROUTE_PIN_DEFAULT                                (_GPIO_USART_RXROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_RXROUTE */

/* Bit fields for GPIO_USART CLKROUTE */
#define _GPIO_USART_CLKROUTE_RESETVALUE                               0x00000000UL                             /**< Default value for GPIO_USART_CLKROUTE       */
#define _GPIO_USART_CLKROUTE_MASK                                     0x000F0003UL                             /**< Mask for GPIO_USART_CLKROUTE                */
#define _GPIO_USART_CLKROUTE_PORT_SHIFT                               0                                        /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_CLKROUTE_PORT_MASK                                0x3UL                                    /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_CLKROUTE_PORT_DEFAULT                             0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_CLKROUTE        */
#define GPIO_USART_CLKROUTE_PORT_DEFAULT                              (_GPIO_USART_CLKROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_CLKROUTE*/
#define _GPIO_USART_CLKROUTE_PIN_SHIFT                                16                                       /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_CLKROUTE_PIN_MASK                                 0xF0000UL                                /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_CLKROUTE_PIN_DEFAULT                              0x00000000UL                             /**< Mode DEFAULT for GPIO_USART_CLKROUTE        */
#define GPIO_USART_CLKROUTE_PIN_DEFAULT                               (_GPIO_USART_CLKROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_CLKROUTE*/

/* Bit fields for GPIO_USART TXROUTE */
#define _GPIO_USART_TXROUTE_RESETVALUE                                0x00000000UL                            /**< Default value for GPIO_USART_TXROUTE        */
#define _GPIO_USART_TXROUTE_MASK                                      0x000F0003UL                            /**< Mask for GPIO_USART_TXROUTE                 */
#define _GPIO_USART_TXROUTE_PORT_SHIFT                                0                                       /**< Shift value for GPIO_PORT                   */
#define _GPIO_USART_TXROUTE_PORT_MASK                                 0x3UL                                   /**< Bit mask for GPIO_PORT                      */
#define _GPIO_USART_TXROUTE_PORT_DEFAULT                              0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_TXROUTE         */
#define GPIO_USART_TXROUTE_PORT_DEFAULT                               (_GPIO_USART_TXROUTE_PORT_DEFAULT << 0) /**< Shifted mode DEFAULT for GPIO_USART_TXROUTE */
#define _GPIO_USART_TXROUTE_PIN_SHIFT                                 16                                      /**< Shift value for GPIO_PIN                    */
#define _GPIO_USART_TXROUTE_PIN_MASK                                  0xF0000UL                               /**< Bit mask for GPIO_PIN                       */
#define _GPIO_USART_TXROUTE_PIN_DEFAULT                               0x00000000UL                            /**< Mode DEFAULT for GPIO_USART_TXROUTE         */
#define GPIO_USART_TXROUTE_PIN_DEFAULT                                (_GPIO_USART_TXROUTE_PIN_DEFAULT << 16) /**< Shifted mode DEFAULT for GPIO_USART_TXROUTE */

/* Bit fields for GPIO RPURATD0 */
#define _GPIO_RPURATD0_RESETVALUE                                     0x00000000UL                                  /**< Default value for GPIO_RPURATD0             */
#define _GPIO_RPURATD0_MASK                                           0x1B01B000UL                                  /**< Mask for GPIO_RPURATD0                      */
#define GPIO_RPURATD0_RATDPORTACTRL                                   (0x1UL << 12)                                 /**< CTRL Protection Bit                         */
#define _GPIO_RPURATD0_RATDPORTACTRL_SHIFT                            12                                            /**< Shift value for GPIO_RATDPORTACTRL          */
#define _GPIO_RPURATD0_RATDPORTACTRL_MASK                             0x1000UL                                      /**< Bit mask for GPIO_RATDPORTACTRL             */
#define _GPIO_RPURATD0_RATDPORTACTRL_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTACTRL_DEFAULT                           (_GPIO_RPURATD0_RATDPORTACTRL_DEFAULT << 12)  /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTAMODEL                                  (0x1UL << 13)                                 /**< MODEL Protection Bit                        */
#define _GPIO_RPURATD0_RATDPORTAMODEL_SHIFT                           13                                            /**< Shift value for GPIO_RATDPORTAMODEL         */
#define _GPIO_RPURATD0_RATDPORTAMODEL_MASK                            0x2000UL                                      /**< Bit mask for GPIO_RATDPORTAMODEL            */
#define _GPIO_RPURATD0_RATDPORTAMODEL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTAMODEL_DEFAULT                          (_GPIO_RPURATD0_RATDPORTAMODEL_DEFAULT << 13) /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTAMODEH                                  (0x1UL << 15)                                 /**< MODEH Protection Bit                        */
#define _GPIO_RPURATD0_RATDPORTAMODEH_SHIFT                           15                                            /**< Shift value for GPIO_RATDPORTAMODEH         */
#define _GPIO_RPURATD0_RATDPORTAMODEH_MASK                            0x8000UL                                      /**< Bit mask for GPIO_RATDPORTAMODEH            */
#define _GPIO_RPURATD0_RATDPORTAMODEH_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTAMODEH_DEFAULT                          (_GPIO_RPURATD0_RATDPORTAMODEH_DEFAULT << 15) /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTADOUT                                   (0x1UL << 16)                                 /**< DOUT Protection Bit                         */
#define _GPIO_RPURATD0_RATDPORTADOUT_SHIFT                            16                                            /**< Shift value for GPIO_RATDPORTADOUT          */
#define _GPIO_RPURATD0_RATDPORTADOUT_MASK                             0x10000UL                                     /**< Bit mask for GPIO_RATDPORTADOUT             */
#define _GPIO_RPURATD0_RATDPORTADOUT_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTADOUT_DEFAULT                           (_GPIO_RPURATD0_RATDPORTADOUT_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTBCTRL                                   (0x1UL << 24)                                 /**< CTRL Protection Bit                         */
#define _GPIO_RPURATD0_RATDPORTBCTRL_SHIFT                            24                                            /**< Shift value for GPIO_RATDPORTBCTRL          */
#define _GPIO_RPURATD0_RATDPORTBCTRL_MASK                             0x1000000UL                                   /**< Bit mask for GPIO_RATDPORTBCTRL             */
#define _GPIO_RPURATD0_RATDPORTBCTRL_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTBCTRL_DEFAULT                           (_GPIO_RPURATD0_RATDPORTBCTRL_DEFAULT << 24)  /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTBMODEL                                  (0x1UL << 25)                                 /**< MODEL Protection Bit                        */
#define _GPIO_RPURATD0_RATDPORTBMODEL_SHIFT                           25                                            /**< Shift value for GPIO_RATDPORTBMODEL         */
#define _GPIO_RPURATD0_RATDPORTBMODEL_MASK                            0x2000000UL                                   /**< Bit mask for GPIO_RATDPORTBMODEL            */
#define _GPIO_RPURATD0_RATDPORTBMODEL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTBMODEL_DEFAULT                          (_GPIO_RPURATD0_RATDPORTBMODEL_DEFAULT << 25) /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTBMODEH                                  (0x1UL << 27)                                 /**< MODEH Protection Bit                        */
#define _GPIO_RPURATD0_RATDPORTBMODEH_SHIFT                           27                                            /**< Shift value for GPIO_RATDPORTBMODEH         */
#define _GPIO_RPURATD0_RATDPORTBMODEH_MASK                            0x8000000UL                                   /**< Bit mask for GPIO_RATDPORTBMODEH            */
#define _GPIO_RPURATD0_RATDPORTBMODEH_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTBMODEH_DEFAULT                          (_GPIO_RPURATD0_RATDPORTBMODEH_DEFAULT << 27) /**< Shifted mode DEFAULT for GPIO_RPURATD0      */
#define GPIO_RPURATD0_RATDPORTBDOUT                                   (0x1UL << 28)                                 /**< DOUT Protection Bit                         */
#define _GPIO_RPURATD0_RATDPORTBDOUT_SHIFT                            28                                            /**< Shift value for GPIO_RATDPORTBDOUT          */
#define _GPIO_RPURATD0_RATDPORTBDOUT_MASK                             0x10000000UL                                  /**< Bit mask for GPIO_RATDPORTBDOUT             */
#define _GPIO_RPURATD0_RATDPORTBDOUT_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD0              */
#define GPIO_RPURATD0_RATDPORTBDOUT_DEFAULT                           (_GPIO_RPURATD0_RATDPORTBDOUT_DEFAULT << 28)  /**< Shifted mode DEFAULT for GPIO_RPURATD0      */

/* Bit fields for GPIO RPURATD1 */
#define _GPIO_RPURATD1_RESETVALUE                                     0x00000000UL                                  /**< Default value for GPIO_RPURATD1             */
#define _GPIO_RPURATD1_MASK                                           0x001B01B0UL                                  /**< Mask for GPIO_RPURATD1                      */
#define GPIO_RPURATD1_RATDPORTCCTRL                                   (0x1UL << 4)                                  /**< CTRL Protection Bit                         */
#define _GPIO_RPURATD1_RATDPORTCCTRL_SHIFT                            4                                             /**< Shift value for GPIO_RATDPORTCCTRL          */
#define _GPIO_RPURATD1_RATDPORTCCTRL_MASK                             0x10UL                                        /**< Bit mask for GPIO_RATDPORTCCTRL             */
#define _GPIO_RPURATD1_RATDPORTCCTRL_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTCCTRL_DEFAULT                           (_GPIO_RPURATD1_RATDPORTCCTRL_DEFAULT << 4)   /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTCMODEL                                  (0x1UL << 5)                                  /**< MODEL Protection Bit                        */
#define _GPIO_RPURATD1_RATDPORTCMODEL_SHIFT                           5                                             /**< Shift value for GPIO_RATDPORTCMODEL         */
#define _GPIO_RPURATD1_RATDPORTCMODEL_MASK                            0x20UL                                        /**< Bit mask for GPIO_RATDPORTCMODEL            */
#define _GPIO_RPURATD1_RATDPORTCMODEL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTCMODEL_DEFAULT                          (_GPIO_RPURATD1_RATDPORTCMODEL_DEFAULT << 5)  /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTCMODEH                                  (0x1UL << 7)                                  /**< MODEH Protection Bit                        */
#define _GPIO_RPURATD1_RATDPORTCMODEH_SHIFT                           7                                             /**< Shift value for GPIO_RATDPORTCMODEH         */
#define _GPIO_RPURATD1_RATDPORTCMODEH_MASK                            0x80UL                                        /**< Bit mask for GPIO_RATDPORTCMODEH            */
#define _GPIO_RPURATD1_RATDPORTCMODEH_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTCMODEH_DEFAULT                          (_GPIO_RPURATD1_RATDPORTCMODEH_DEFAULT << 7)  /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTCDOUT                                   (0x1UL << 8)                                  /**< DOUT Protection Bit                         */
#define _GPIO_RPURATD1_RATDPORTCDOUT_SHIFT                            8                                             /**< Shift value for GPIO_RATDPORTCDOUT          */
#define _GPIO_RPURATD1_RATDPORTCDOUT_MASK                             0x100UL                                       /**< Bit mask for GPIO_RATDPORTCDOUT             */
#define _GPIO_RPURATD1_RATDPORTCDOUT_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTCDOUT_DEFAULT                           (_GPIO_RPURATD1_RATDPORTCDOUT_DEFAULT << 8)   /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTDCTRL                                   (0x1UL << 16)                                 /**< CTRL Protection Bit                         */
#define _GPIO_RPURATD1_RATDPORTDCTRL_SHIFT                            16                                            /**< Shift value for GPIO_RATDPORTDCTRL          */
#define _GPIO_RPURATD1_RATDPORTDCTRL_MASK                             0x10000UL                                     /**< Bit mask for GPIO_RATDPORTDCTRL             */
#define _GPIO_RPURATD1_RATDPORTDCTRL_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTDCTRL_DEFAULT                           (_GPIO_RPURATD1_RATDPORTDCTRL_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTDMODEL                                  (0x1UL << 17)                                 /**< MODEL Protection Bit                        */
#define _GPIO_RPURATD1_RATDPORTDMODEL_SHIFT                           17                                            /**< Shift value for GPIO_RATDPORTDMODEL         */
#define _GPIO_RPURATD1_RATDPORTDMODEL_MASK                            0x20000UL                                     /**< Bit mask for GPIO_RATDPORTDMODEL            */
#define _GPIO_RPURATD1_RATDPORTDMODEL_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTDMODEL_DEFAULT                          (_GPIO_RPURATD1_RATDPORTDMODEL_DEFAULT << 17) /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTDMODEH                                  (0x1UL << 19)                                 /**< MODEH Protection Bit                        */
#define _GPIO_RPURATD1_RATDPORTDMODEH_SHIFT                           19                                            /**< Shift value for GPIO_RATDPORTDMODEH         */
#define _GPIO_RPURATD1_RATDPORTDMODEH_MASK                            0x80000UL                                     /**< Bit mask for GPIO_RATDPORTDMODEH            */
#define _GPIO_RPURATD1_RATDPORTDMODEH_DEFAULT                         0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTDMODEH_DEFAULT                          (_GPIO_RPURATD1_RATDPORTDMODEH_DEFAULT << 19) /**< Shifted mode DEFAULT for GPIO_RPURATD1      */
#define GPIO_RPURATD1_RATDPORTDDOUT                                   (0x1UL << 20)                                 /**< DOUT Protection Bit                         */
#define _GPIO_RPURATD1_RATDPORTDDOUT_SHIFT                            20                                            /**< Shift value for GPIO_RATDPORTDDOUT          */
#define _GPIO_RPURATD1_RATDPORTDDOUT_MASK                             0x100000UL                                    /**< Bit mask for GPIO_RATDPORTDDOUT             */
#define _GPIO_RPURATD1_RATDPORTDDOUT_DEFAULT                          0x00000000UL                                  /**< Mode DEFAULT for GPIO_RPURATD1              */
#define GPIO_RPURATD1_RATDPORTDDOUT_DEFAULT                           (_GPIO_RPURATD1_RATDPORTDDOUT_DEFAULT << 20)  /**< Shifted mode DEFAULT for GPIO_RPURATD1      */

/* Bit fields for GPIO RPURATD6 */
#define _GPIO_RPURATD6_RESETVALUE                                     0x00000000UL                                     /**< Default value for GPIO_RPURATD6             */
#define _GPIO_RPURATD6_MASK                                           0x00FFF701UL                                     /**< Mask for GPIO_RPURATD6                      */
#define GPIO_RPURATD6_RATDLOCK                                        (0x1UL << 0)                                     /**< LOCK Protection Bit                         */
#define _GPIO_RPURATD6_RATDLOCK_SHIFT                                 0                                                /**< Shift value for GPIO_RATDLOCK               */
#define _GPIO_RPURATD6_RATDLOCK_MASK                                  0x1UL                                            /**< Bit mask for GPIO_RATDLOCK                  */
#define _GPIO_RPURATD6_RATDLOCK_DEFAULT                               0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDLOCK_DEFAULT                                (_GPIO_RPURATD6_RATDLOCK_DEFAULT << 0)           /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDABUSALLOC                                   (0x1UL << 8)                                     /**< ABUSALLOC Protection Bit                    */
#define _GPIO_RPURATD6_RATDABUSALLOC_SHIFT                            8                                                /**< Shift value for GPIO_RATDABUSALLOC          */
#define _GPIO_RPURATD6_RATDABUSALLOC_MASK                             0x100UL                                          /**< Bit mask for GPIO_RATDABUSALLOC             */
#define _GPIO_RPURATD6_RATDABUSALLOC_DEFAULT                          0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDABUSALLOC_DEFAULT                           (_GPIO_RPURATD6_RATDABUSALLOC_DEFAULT << 8)      /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDBBUSALLOC                                   (0x1UL << 9)                                     /**< BBUSALLOC Protection Bit                    */
#define _GPIO_RPURATD6_RATDBBUSALLOC_SHIFT                            9                                                /**< Shift value for GPIO_RATDBBUSALLOC          */
#define _GPIO_RPURATD6_RATDBBUSALLOC_MASK                             0x200UL                                          /**< Bit mask for GPIO_RATDBBUSALLOC             */
#define _GPIO_RPURATD6_RATDBBUSALLOC_DEFAULT                          0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDBBUSALLOC_DEFAULT                           (_GPIO_RPURATD6_RATDBBUSALLOC_DEFAULT << 9)      /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDCDBUSALLOC                                  (0x1UL << 10)                                    /**< CDBUSALLOC Protection Bit                   */
#define _GPIO_RPURATD6_RATDCDBUSALLOC_SHIFT                           10                                               /**< Shift value for GPIO_RATDCDBUSALLOC         */
#define _GPIO_RPURATD6_RATDCDBUSALLOC_MASK                            0x400UL                                          /**< Bit mask for GPIO_RATDCDBUSALLOC            */
#define _GPIO_RPURATD6_RATDCDBUSALLOC_DEFAULT                         0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDCDBUSALLOC_DEFAULT                          (_GPIO_RPURATD6_RATDCDBUSALLOC_DEFAULT << 10)    /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDAODD0SWITCH                                 (0x1UL << 12)                                    /**< AODD0SWITCH Protection Bit                  */
#define _GPIO_RPURATD6_RATDAODD0SWITCH_SHIFT                          12                                               /**< Shift value for GPIO_RATDAODD0SWITCH        */
#define _GPIO_RPURATD6_RATDAODD0SWITCH_MASK                           0x1000UL                                         /**< Bit mask for GPIO_RATDAODD0SWITCH           */
#define _GPIO_RPURATD6_RATDAODD0SWITCH_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDAODD0SWITCH_DEFAULT                         (_GPIO_RPURATD6_RATDAODD0SWITCH_DEFAULT << 12)   /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDAODD1SWITCH                                 (0x1UL << 13)                                    /**< AODD1SWITCH Protection Bit                  */
#define _GPIO_RPURATD6_RATDAODD1SWITCH_SHIFT                          13                                               /**< Shift value for GPIO_RATDAODD1SWITCH        */
#define _GPIO_RPURATD6_RATDAODD1SWITCH_MASK                           0x2000UL                                         /**< Bit mask for GPIO_RATDAODD1SWITCH           */
#define _GPIO_RPURATD6_RATDAODD1SWITCH_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDAODD1SWITCH_DEFAULT                         (_GPIO_RPURATD6_RATDAODD1SWITCH_DEFAULT << 13)   /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDAEVEN0SWITCH                                (0x1UL << 14)                                    /**< AEVEN0SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDAEVEN0SWITCH_SHIFT                         14                                               /**< Shift value for GPIO_RATDAEVEN0SWITCH       */
#define _GPIO_RPURATD6_RATDAEVEN0SWITCH_MASK                          0x4000UL                                         /**< Bit mask for GPIO_RATDAEVEN0SWITCH          */
#define _GPIO_RPURATD6_RATDAEVEN0SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDAEVEN0SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDAEVEN0SWITCH_DEFAULT << 14)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDAEVEN1SWITCH                                (0x1UL << 15)                                    /**< AEVEN1SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDAEVEN1SWITCH_SHIFT                         15                                               /**< Shift value for GPIO_RATDAEVEN1SWITCH       */
#define _GPIO_RPURATD6_RATDAEVEN1SWITCH_MASK                          0x8000UL                                         /**< Bit mask for GPIO_RATDAEVEN1SWITCH          */
#define _GPIO_RPURATD6_RATDAEVEN1SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDAEVEN1SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDAEVEN1SWITCH_DEFAULT << 15)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDBODD0SWITCH                                 (0x1UL << 16)                                    /**< BODD0SWITCH Protection Bit                  */
#define _GPIO_RPURATD6_RATDBODD0SWITCH_SHIFT                          16                                               /**< Shift value for GPIO_RATDBODD0SWITCH        */
#define _GPIO_RPURATD6_RATDBODD0SWITCH_MASK                           0x10000UL                                        /**< Bit mask for GPIO_RATDBODD0SWITCH           */
#define _GPIO_RPURATD6_RATDBODD0SWITCH_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDBODD0SWITCH_DEFAULT                         (_GPIO_RPURATD6_RATDBODD0SWITCH_DEFAULT << 16)   /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDBODD1SWITCH                                 (0x1UL << 17)                                    /**< BODD1SWITCH Protection Bit                  */
#define _GPIO_RPURATD6_RATDBODD1SWITCH_SHIFT                          17                                               /**< Shift value for GPIO_RATDBODD1SWITCH        */
#define _GPIO_RPURATD6_RATDBODD1SWITCH_MASK                           0x20000UL                                        /**< Bit mask for GPIO_RATDBODD1SWITCH           */
#define _GPIO_RPURATD6_RATDBODD1SWITCH_DEFAULT                        0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDBODD1SWITCH_DEFAULT                         (_GPIO_RPURATD6_RATDBODD1SWITCH_DEFAULT << 17)   /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDBEVEN0SWITCH                                (0x1UL << 18)                                    /**< BEVEN0SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDBEVEN0SWITCH_SHIFT                         18                                               /**< Shift value for GPIO_RATDBEVEN0SWITCH       */
#define _GPIO_RPURATD6_RATDBEVEN0SWITCH_MASK                          0x40000UL                                        /**< Bit mask for GPIO_RATDBEVEN0SWITCH          */
#define _GPIO_RPURATD6_RATDBEVEN0SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDBEVEN0SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDBEVEN0SWITCH_DEFAULT << 18)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDBEVEN1SWITCH                                (0x1UL << 19)                                    /**< BEVEN1SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDBEVEN1SWITCH_SHIFT                         19                                               /**< Shift value for GPIO_RATDBEVEN1SWITCH       */
#define _GPIO_RPURATD6_RATDBEVEN1SWITCH_MASK                          0x80000UL                                        /**< Bit mask for GPIO_RATDBEVEN1SWITCH          */
#define _GPIO_RPURATD6_RATDBEVEN1SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDBEVEN1SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDBEVEN1SWITCH_DEFAULT << 19)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDCDODD0SWITCH                                (0x1UL << 20)                                    /**< CDODD0SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDCDODD0SWITCH_SHIFT                         20                                               /**< Shift value for GPIO_RATDCDODD0SWITCH       */
#define _GPIO_RPURATD6_RATDCDODD0SWITCH_MASK                          0x100000UL                                       /**< Bit mask for GPIO_RATDCDODD0SWITCH          */
#define _GPIO_RPURATD6_RATDCDODD0SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDCDODD0SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDCDODD0SWITCH_DEFAULT << 20)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDCDODD1SWITCH                                (0x1UL << 21)                                    /**< CDODD1SWITCH Protection Bit                 */
#define _GPIO_RPURATD6_RATDCDODD1SWITCH_SHIFT                         21                                               /**< Shift value for GPIO_RATDCDODD1SWITCH       */
#define _GPIO_RPURATD6_RATDCDODD1SWITCH_MASK                          0x200000UL                                       /**< Bit mask for GPIO_RATDCDODD1SWITCH          */
#define _GPIO_RPURATD6_RATDCDODD1SWITCH_DEFAULT                       0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDCDODD1SWITCH_DEFAULT                        (_GPIO_RPURATD6_RATDCDODD1SWITCH_DEFAULT << 21)  /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDCDEVEN0SWITCH                               (0x1UL << 22)                                    /**< CDEVEN0SWITCH Protection Bit                */
#define _GPIO_RPURATD6_RATDCDEVEN0SWITCH_SHIFT                        22                                               /**< Shift value for GPIO_RATDCDEVEN0SWITCH      */
#define _GPIO_RPURATD6_RATDCDEVEN0SWITCH_MASK                         0x400000UL                                       /**< Bit mask for GPIO_RATDCDEVEN0SWITCH         */
#define _GPIO_RPURATD6_RATDCDEVEN0SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDCDEVEN0SWITCH_DEFAULT                       (_GPIO_RPURATD6_RATDCDEVEN0SWITCH_DEFAULT << 22) /**< Shifted mode DEFAULT for GPIO_RPURATD6      */
#define GPIO_RPURATD6_RATDCDEVEN1SWITCH                               (0x1UL << 23)                                    /**< CDEVEN1SWITCH Protection Bit                */
#define _GPIO_RPURATD6_RATDCDEVEN1SWITCH_SHIFT                        23                                               /**< Shift value for GPIO_RATDCDEVEN1SWITCH      */
#define _GPIO_RPURATD6_RATDCDEVEN1SWITCH_MASK                         0x800000UL                                       /**< Bit mask for GPIO_RATDCDEVEN1SWITCH         */
#define _GPIO_RPURATD6_RATDCDEVEN1SWITCH_DEFAULT                      0x00000000UL                                     /**< Mode DEFAULT for GPIO_RPURATD6              */
#define GPIO_RPURATD6_RATDCDEVEN1SWITCH_DEFAULT                       (_GPIO_RPURATD6_RATDCDEVEN1SWITCH_DEFAULT << 23) /**< Shifted mode DEFAULT for GPIO_RPURATD6      */

/* Bit fields for GPIO RPURATD8 */
#define _GPIO_RPURATD8_RESETVALUE                                     0x00000000UL                                                /**< Default value for GPIO_RPURATD8             */
#define _GPIO_RPURATD8_MASK                                           0xFDB31B3FUL                                                /**< Mask for GPIO_RPURATD8                      */
#define GPIO_RPURATD8_RATDEXTIPSELL                                   (0x1UL << 0)                                                /**< EXTIPSELL Protection Bit                    */
#define _GPIO_RPURATD8_RATDEXTIPSELL_SHIFT                            0                                                           /**< Shift value for GPIO_RATDEXTIPSELL          */
#define _GPIO_RPURATD8_RATDEXTIPSELL_MASK                             0x1UL                                                       /**< Bit mask for GPIO_RATDEXTIPSELL             */
#define _GPIO_RPURATD8_RATDEXTIPSELL_DEFAULT                          0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIPSELL_DEFAULT                           (_GPIO_RPURATD8_RATDEXTIPSELL_DEFAULT << 0)                 /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEXTIPSELH                                   (0x1UL << 1)                                                /**< EXTIPSELH Protection Bit                    */
#define _GPIO_RPURATD8_RATDEXTIPSELH_SHIFT                            1                                                           /**< Shift value for GPIO_RATDEXTIPSELH          */
#define _GPIO_RPURATD8_RATDEXTIPSELH_MASK                             0x2UL                                                       /**< Bit mask for GPIO_RATDEXTIPSELH             */
#define _GPIO_RPURATD8_RATDEXTIPSELH_DEFAULT                          0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIPSELH_DEFAULT                           (_GPIO_RPURATD8_RATDEXTIPSELH_DEFAULT << 1)                 /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEXTIPINSELL                                 (0x1UL << 2)                                                /**< EXTIPINSELL Protection Bit                  */
#define _GPIO_RPURATD8_RATDEXTIPINSELL_SHIFT                          2                                                           /**< Shift value for GPIO_RATDEXTIPINSELL        */
#define _GPIO_RPURATD8_RATDEXTIPINSELL_MASK                           0x4UL                                                       /**< Bit mask for GPIO_RATDEXTIPINSELL           */
#define _GPIO_RPURATD8_RATDEXTIPINSELL_DEFAULT                        0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIPINSELL_DEFAULT                         (_GPIO_RPURATD8_RATDEXTIPINSELL_DEFAULT << 2)               /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEXTIPINSELH                                 (0x1UL << 3)                                                /**< EXTIPINSELH Protection Bit                  */
#define _GPIO_RPURATD8_RATDEXTIPINSELH_SHIFT                          3                                                           /**< Shift value for GPIO_RATDEXTIPINSELH        */
#define _GPIO_RPURATD8_RATDEXTIPINSELH_MASK                           0x8UL                                                       /**< Bit mask for GPIO_RATDEXTIPINSELH           */
#define _GPIO_RPURATD8_RATDEXTIPINSELH_DEFAULT                        0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIPINSELH_DEFAULT                         (_GPIO_RPURATD8_RATDEXTIPINSELH_DEFAULT << 3)               /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEXTIRISE                                    (0x1UL << 4)                                                /**< EXTIRISE Protection Bit                     */
#define _GPIO_RPURATD8_RATDEXTIRISE_SHIFT                             4                                                           /**< Shift value for GPIO_RATDEXTIRISE           */
#define _GPIO_RPURATD8_RATDEXTIRISE_MASK                              0x10UL                                                      /**< Bit mask for GPIO_RATDEXTIRISE              */
#define _GPIO_RPURATD8_RATDEXTIRISE_DEFAULT                           0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIRISE_DEFAULT                            (_GPIO_RPURATD8_RATDEXTIRISE_DEFAULT << 4)                  /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEXTIFALL                                    (0x1UL << 5)                                                /**< EXTIFALL Protection Bit                     */
#define _GPIO_RPURATD8_RATDEXTIFALL_SHIFT                             5                                                           /**< Shift value for GPIO_RATDEXTIFALL           */
#define _GPIO_RPURATD8_RATDEXTIFALL_MASK                              0x20UL                                                      /**< Bit mask for GPIO_RATDEXTIFALL              */
#define _GPIO_RPURATD8_RATDEXTIFALL_DEFAULT                           0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEXTIFALL_DEFAULT                            (_GPIO_RPURATD8_RATDEXTIFALL_DEFAULT << 5)                  /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDIF                                          (0x1UL << 8)                                                /**< IF Protection Bit                           */
#define _GPIO_RPURATD8_RATDIF_SHIFT                                   8                                                           /**< Shift value for GPIO_RATDIF                 */
#define _GPIO_RPURATD8_RATDIF_MASK                                    0x100UL                                                     /**< Bit mask for GPIO_RATDIF                    */
#define _GPIO_RPURATD8_RATDIF_DEFAULT                                 0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDIF_DEFAULT                                  (_GPIO_RPURATD8_RATDIF_DEFAULT << 8)                        /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDIEN                                         (0x1UL << 9)                                                /**< IEN Protection Bit                          */
#define _GPIO_RPURATD8_RATDIEN_SHIFT                                  9                                                           /**< Shift value for GPIO_RATDIEN                */
#define _GPIO_RPURATD8_RATDIEN_MASK                                   0x200UL                                                     /**< Bit mask for GPIO_RATDIEN                   */
#define _GPIO_RPURATD8_RATDIEN_DEFAULT                                0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDIEN_DEFAULT                                 (_GPIO_RPURATD8_RATDIEN_DEFAULT << 9)                       /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEM4WUEN                                     (0x1UL << 11)                                               /**< EM4WUEN Protection Bit                      */
#define _GPIO_RPURATD8_RATDEM4WUEN_SHIFT                              11                                                          /**< Shift value for GPIO_RATDEM4WUEN            */
#define _GPIO_RPURATD8_RATDEM4WUEN_MASK                               0x800UL                                                     /**< Bit mask for GPIO_RATDEM4WUEN               */
#define _GPIO_RPURATD8_RATDEM4WUEN_DEFAULT                            0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEM4WUEN_DEFAULT                             (_GPIO_RPURATD8_RATDEM4WUEN_DEFAULT << 11)                  /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDEM4WUPOL                                    (0x1UL << 12)                                               /**< EM4WUPOL Protection Bit                     */
#define _GPIO_RPURATD8_RATDEM4WUPOL_SHIFT                             12                                                          /**< Shift value for GPIO_RATDEM4WUPOL           */
#define _GPIO_RPURATD8_RATDEM4WUPOL_MASK                              0x1000UL                                                    /**< Bit mask for GPIO_RATDEM4WUPOL              */
#define _GPIO_RPURATD8_RATDEM4WUPOL_DEFAULT                           0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDEM4WUPOL_DEFAULT                            (_GPIO_RPURATD8_RATDEM4WUPOL_DEFAULT << 12)                 /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBGROUTEPEN                                 (0x1UL << 16)                                               /**< DBGROUTEPEN Protection Bit                  */
#define _GPIO_RPURATD8_RATDDBGROUTEPEN_SHIFT                          16                                                          /**< Shift value for GPIO_RATDDBGROUTEPEN        */
#define _GPIO_RPURATD8_RATDDBGROUTEPEN_MASK                           0x10000UL                                                   /**< Bit mask for GPIO_RATDDBGROUTEPEN           */
#define _GPIO_RPURATD8_RATDDBGROUTEPEN_DEFAULT                        0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBGROUTEPEN_DEFAULT                         (_GPIO_RPURATD8_RATDDBGROUTEPEN_DEFAULT << 16)              /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDTRACEROUTEPEN                               (0x1UL << 17)                                               /**< TRACEROUTEPEN Protection Bit                */
#define _GPIO_RPURATD8_RATDTRACEROUTEPEN_SHIFT                        17                                                          /**< Shift value for GPIO_RATDTRACEROUTEPEN      */
#define _GPIO_RPURATD8_RATDTRACEROUTEPEN_MASK                         0x20000UL                                                   /**< Bit mask for GPIO_RATDTRACEROUTEPEN         */
#define _GPIO_RPURATD8_RATDTRACEROUTEPEN_DEFAULT                      0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDTRACEROUTEPEN_DEFAULT                       (_GPIO_RPURATD8_RATDTRACEROUTEPEN_DEFAULT << 17)            /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN                            (0x1UL << 20)                                               /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN_SHIFT                     20                                                          /**< Shift value for GPIO_RATDDBUSACMP0ROUTEEN   */
#define _GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN_MASK                      0x100000UL                                                  /**< Bit mask for GPIO_RATDDBUSACMP0ROUTEEN      */
#define _GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN_DEFAULT                   0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN_DEFAULT                    (_GPIO_RPURATD8_RATDDBUSACMP0ROUTEEN_DEFAULT << 20)         /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE                       (0x1UL << 21)                                               /**< ACMPOUTROUTE Protection Bit                 */
#define _GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE_SHIFT                21                                                          /**< Shift value for GPIO_RATDDBUSACMP0ACMPOUTROUTE*/
#define _GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE_MASK                 0x200000UL                                                  /**< Bit mask for GPIO_RATDDBUSACMP0ACMPOUTROUTE */
#define _GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE_DEFAULT              0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE_DEFAULT               (_GPIO_RPURATD8_RATDDBUSACMP0ACMPOUTROUTE_DEFAULT << 21)    /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN                            (0x1UL << 23)                                               /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN_SHIFT                     23                                                          /**< Shift value for GPIO_RATDDBUSACMP1ROUTEEN   */
#define _GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN_MASK                      0x800000UL                                                  /**< Bit mask for GPIO_RATDDBUSACMP1ROUTEEN      */
#define _GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN_DEFAULT                   0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN_DEFAULT                    (_GPIO_RPURATD8_RATDDBUSACMP1ROUTEEN_DEFAULT << 23)         /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE                       (0x1UL << 24)                                               /**< ACMPOUTROUTE Protection Bit                 */
#define _GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE_SHIFT                24                                                          /**< Shift value for GPIO_RATDDBUSACMP1ACMPOUTROUTE*/
#define _GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE_MASK                 0x1000000UL                                                 /**< Bit mask for GPIO_RATDDBUSACMP1ACMPOUTROUTE */
#define _GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE_DEFAULT              0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE_DEFAULT               (_GPIO_RPURATD8_RATDDBUSACMP1ACMPOUTROUTE_DEFAULT << 24)    /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUROUTEEN                              (0x1UL << 26)                                               /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD8_RATDDBUSCMUROUTEEN_SHIFT                       26                                                          /**< Shift value for GPIO_RATDDBUSCMUROUTEEN     */
#define _GPIO_RPURATD8_RATDDBUSCMUROUTEEN_MASK                        0x4000000UL                                                 /**< Bit mask for GPIO_RATDDBUSCMUROUTEEN        */
#define _GPIO_RPURATD8_RATDDBUSCMUROUTEEN_DEFAULT                     0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUROUTEEN_DEFAULT                      (_GPIO_RPURATD8_RATDDBUSCMUROUTEEN_DEFAULT << 26)           /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE                          (0x1UL << 27)                                               /**< CLKIN0ROUTE Protection Bit                  */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE_SHIFT                   27                                                          /**< Shift value for GPIO_RATDDBUSCMUCLKIN0ROUTE */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE_MASK                    0x8000000UL                                                 /**< Bit mask for GPIO_RATDDBUSCMUCLKIN0ROUTE    */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE_DEFAULT                 0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE_DEFAULT                  (_GPIO_RPURATD8_RATDDBUSCMUCLKIN0ROUTE_DEFAULT << 27)       /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE                         (0x1UL << 28)                                               /**< CLKOUT0ROUTE Protection Bit                 */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE_SHIFT                  28                                                          /**< Shift value for GPIO_RATDDBUSCMUCLKOUT0ROUTE*/
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE_MASK                   0x10000000UL                                                /**< Bit mask for GPIO_RATDDBUSCMUCLKOUT0ROUTE   */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE_DEFAULT                0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE_DEFAULT                 (_GPIO_RPURATD8_RATDDBUSCMUCLKOUT0ROUTE_DEFAULT << 28)      /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE                         (0x1UL << 29)                                               /**< CLKOUT1ROUTE Protection Bit                 */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE_SHIFT                  29                                                          /**< Shift value for GPIO_RATDDBUSCMUCLKOUT1ROUTE*/
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE_MASK                   0x20000000UL                                                /**< Bit mask for GPIO_RATDDBUSCMUCLKOUT1ROUTE   */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE_DEFAULT                0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE_DEFAULT                 (_GPIO_RPURATD8_RATDDBUSCMUCLKOUT1ROUTE_DEFAULT << 29)      /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE                         (0x1UL << 30)                                               /**< CLKOUT2ROUTE Protection Bit                 */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE_SHIFT                  30                                                          /**< Shift value for GPIO_RATDDBUSCMUCLKOUT2ROUTE*/
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE_MASK                   0x40000000UL                                                /**< Bit mask for GPIO_RATDDBUSCMUCLKOUT2ROUTE   */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE_DEFAULT                0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE_DEFAULT                 (_GPIO_RPURATD8_RATDDBUSCMUCLKOUT2ROUTE_DEFAULT << 30)      /**< Shifted mode DEFAULT for GPIO_RPURATD8      */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE                    (0x1UL << 31)                                               /**< CLKOUTHIDDENROUTE Protection Bit            */
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE_SHIFT             31                                                          /**< Shift value for GPIO_RATDDBUSCMUCLKOUTHIDDENROUTE*/
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE_MASK              0x80000000UL                                                /**< Bit mask for GPIO_RATDDBUSCMUCLKOUTHIDDENROUTE*/
#define _GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE_DEFAULT           0x00000000UL                                                /**< Mode DEFAULT for GPIO_RPURATD8              */
#define GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE_DEFAULT            (_GPIO_RPURATD8_RATDDBUSCMUCLKOUTHIDDENROUTE_DEFAULT << 31) /**< Shifted mode DEFAULT for GPIO_RPURATD8      */

/* Bit fields for GPIO RPURATD9 */
#define _GPIO_RPURATD9_RESETVALUE                                     0x00000000UL                                                  /**< Default value for GPIO_RPURATD9             */
#define _GPIO_RPURATD9_MASK                                           0xDDEFEFEEUL                                                  /**< Mask for GPIO_RPURATD9                      */
#define GPIO_RPURATD9_RATDDBUSDCDCROUTEEN                             (0x1UL << 1)                                                  /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSDCDCROUTEEN_SHIFT                      1                                                             /**< Shift value for GPIO_RATDDBUSDCDCROUTEEN    */
#define _GPIO_RPURATD9_RATDDBUSDCDCROUTEEN_MASK                       0x2UL                                                         /**< Bit mask for GPIO_RATDDBUSDCDCROUTEEN       */
#define _GPIO_RPURATD9_RATDDBUSDCDCROUTEEN_DEFAULT                    0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSDCDCROUTEEN_DEFAULT                     (_GPIO_RPURATD9_RATDDBUSDCDCROUTEEN_DEFAULT << 1)             /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE                 (0x1UL << 2)                                                  /**< DCDCCOREHIDDENROUTE Protection Bit          */
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE_SHIFT          2                                                             /**< Shift value for GPIO_RATDDBUSDCDCDCDCCOREHIDDENROUTE*/
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE_MASK           0x4UL                                                         /**< Bit mask for GPIO_RATDDBUSDCDCDCDCCOREHIDDENROUTE*/
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE_DEFAULT        0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE_DEFAULT         (_GPIO_RPURATD9_RATDDBUSDCDCDCDCCOREHIDDENROUTE_DEFAULT << 2) /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE                 (0x1UL << 3)                                                  /**< DCDCVCMPHIDDENROUTE Protection Bit          */
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE_SHIFT          3                                                             /**< Shift value for GPIO_RATDDBUSDCDCDCDCVCMPHIDDENROUTE*/
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE_MASK           0x8UL                                                         /**< Bit mask for GPIO_RATDDBUSDCDCDCDCVCMPHIDDENROUTE*/
#define _GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE_DEFAULT        0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE_DEFAULT         (_GPIO_RPURATD9_RATDDBUSDCDCDCDCVCMPHIDDENROUTE_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN                          (0x1UL << 5)                                                  /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN_SHIFT                   5                                                             /**< Shift value for GPIO_RATDDBUSEUSART0ROUTEEN */
#define _GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN_MASK                    0x20UL                                                        /**< Bit mask for GPIO_RATDDBUSEUSART0ROUTEEN    */
#define _GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART0ROUTEEN_DEFAULT << 5)          /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE                          (0x1UL << 6)                                                  /**< CSROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE_SHIFT                   6                                                             /**< Shift value for GPIO_RATDDBUSEUSART0CSROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE_MASK                    0x40UL                                                        /**< Bit mask for GPIO_RATDDBUSEUSART0CSROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART0CSROUTE_DEFAULT << 6)          /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE                         (0x1UL << 7)                                                  /**< CTSROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE_SHIFT                  7                                                             /**< Shift value for GPIO_RATDDBUSEUSART0CTSROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE_MASK                   0x80UL                                                        /**< Bit mask for GPIO_RATDDBUSEUSART0CTSROUTE   */
#define _GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE_DEFAULT                 (_GPIO_RPURATD9_RATDDBUSEUSART0CTSROUTE_DEFAULT << 7)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE                         (0x1UL << 8)                                                  /**< RTSROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE_SHIFT                  8                                                             /**< Shift value for GPIO_RATDDBUSEUSART0RTSROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE_MASK                   0x100UL                                                       /**< Bit mask for GPIO_RATDDBUSEUSART0RTSROUTE   */
#define _GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE_DEFAULT                 (_GPIO_RPURATD9_RATDDBUSEUSART0RTSROUTE_DEFAULT << 8)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE                          (0x1UL << 9)                                                  /**< RXROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE_SHIFT                   9                                                             /**< Shift value for GPIO_RATDDBUSEUSART0RXROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE_MASK                    0x200UL                                                       /**< Bit mask for GPIO_RATDDBUSEUSART0RXROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART0RXROUTE_DEFAULT << 9)          /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE                        (0x1UL << 10)                                                 /**< SCLKROUTE Protection Bit                    */
#define _GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE_SHIFT                 10                                                            /**< Shift value for GPIO_RATDDBUSEUSART0SCLKROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE_MASK                  0x400UL                                                       /**< Bit mask for GPIO_RATDDBUSEUSART0SCLKROUTE  */
#define _GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE_DEFAULT               0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE_DEFAULT                (_GPIO_RPURATD9_RATDDBUSEUSART0SCLKROUTE_DEFAULT << 10)       /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE                          (0x1UL << 11)                                                 /**< TXROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE_SHIFT                   11                                                            /**< Shift value for GPIO_RATDDBUSEUSART0TXROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE_MASK                    0x800UL                                                       /**< Bit mask for GPIO_RATDDBUSEUSART0TXROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART0TXROUTE_DEFAULT << 11)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN                          (0x1UL << 13)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN_SHIFT                   13                                                            /**< Shift value for GPIO_RATDDBUSEUSART1ROUTEEN */
#define _GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN_MASK                    0x2000UL                                                      /**< Bit mask for GPIO_RATDDBUSEUSART1ROUTEEN    */
#define _GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART1ROUTEEN_DEFAULT << 13)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE                          (0x1UL << 14)                                                 /**< CSROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE_SHIFT                   14                                                            /**< Shift value for GPIO_RATDDBUSEUSART1CSROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE_MASK                    0x4000UL                                                      /**< Bit mask for GPIO_RATDDBUSEUSART1CSROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART1CSROUTE_DEFAULT << 14)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE                         (0x1UL << 15)                                                 /**< CTSROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE_SHIFT                  15                                                            /**< Shift value for GPIO_RATDDBUSEUSART1CTSROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE_MASK                   0x8000UL                                                      /**< Bit mask for GPIO_RATDDBUSEUSART1CTSROUTE   */
#define _GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE_DEFAULT                 (_GPIO_RPURATD9_RATDDBUSEUSART1CTSROUTE_DEFAULT << 15)        /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE                         (0x1UL << 16)                                                 /**< RTSROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE_SHIFT                  16                                                            /**< Shift value for GPIO_RATDDBUSEUSART1RTSROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE_MASK                   0x10000UL                                                     /**< Bit mask for GPIO_RATDDBUSEUSART1RTSROUTE   */
#define _GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE_DEFAULT                 (_GPIO_RPURATD9_RATDDBUSEUSART1RTSROUTE_DEFAULT << 16)        /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE                          (0x1UL << 17)                                                 /**< RXROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE_SHIFT                   17                                                            /**< Shift value for GPIO_RATDDBUSEUSART1RXROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE_MASK                    0x20000UL                                                     /**< Bit mask for GPIO_RATDDBUSEUSART1RXROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART1RXROUTE_DEFAULT << 17)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE                        (0x1UL << 18)                                                 /**< SCLKROUTE Protection Bit                    */
#define _GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE_SHIFT                 18                                                            /**< Shift value for GPIO_RATDDBUSEUSART1SCLKROUTE*/
#define _GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE_MASK                  0x40000UL                                                     /**< Bit mask for GPIO_RATDDBUSEUSART1SCLKROUTE  */
#define _GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE_DEFAULT               0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE_DEFAULT                (_GPIO_RPURATD9_RATDDBUSEUSART1SCLKROUTE_DEFAULT << 18)       /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE                          (0x1UL << 19)                                                 /**< TXROUTE Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE_SHIFT                   19                                                            /**< Shift value for GPIO_RATDDBUSEUSART1TXROUTE */
#define _GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE_MASK                    0x80000UL                                                     /**< Bit mask for GPIO_RATDDBUSEUSART1TXROUTE    */
#define _GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSEUSART1TXROUTE_DEFAULT << 19)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSFRCROUTEEN                              (0x1UL << 21)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSFRCROUTEEN_SHIFT                       21                                                            /**< Shift value for GPIO_RATDDBUSFRCROUTEEN     */
#define _GPIO_RPURATD9_RATDDBUSFRCROUTEEN_MASK                        0x200000UL                                                    /**< Bit mask for GPIO_RATDDBUSFRCROUTEEN        */
#define _GPIO_RPURATD9_RATDDBUSFRCROUTEEN_DEFAULT                     0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSFRCROUTEEN_DEFAULT                      (_GPIO_RPURATD9_RATDDBUSFRCROUTEEN_DEFAULT << 21)             /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE                            (0x1UL << 22)                                                 /**< DCLKROUTE Protection Bit                    */
#define _GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE_SHIFT                     22                                                            /**< Shift value for GPIO_RATDDBUSFRCDCLKROUTE   */
#define _GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE_MASK                      0x400000UL                                                    /**< Bit mask for GPIO_RATDDBUSFRCDCLKROUTE      */
#define _GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE_DEFAULT                    (_GPIO_RPURATD9_RATDDBUSFRCDCLKROUTE_DEFAULT << 22)           /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE                          (0x1UL << 23)                                                 /**< DFRAMEROUTE Protection Bit                  */
#define _GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE_SHIFT                   23                                                            /**< Shift value for GPIO_RATDDBUSFRCDFRAMEROUTE */
#define _GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE_MASK                    0x800000UL                                                    /**< Bit mask for GPIO_RATDDBUSFRCDFRAMEROUTE    */
#define _GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE_DEFAULT                  (_GPIO_RPURATD9_RATDDBUSFRCDFRAMEROUTE_DEFAULT << 23)         /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE                            (0x1UL << 24)                                                 /**< DOUTROUTE Protection Bit                    */
#define _GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE_SHIFT                     24                                                            /**< Shift value for GPIO_RATDDBUSFRCDOUTROUTE   */
#define _GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE_MASK                      0x1000000UL                                                   /**< Bit mask for GPIO_RATDDBUSFRCDOUTROUTE      */
#define _GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE_DEFAULT                    (_GPIO_RPURATD9_RATDDBUSFRCDOUTROUTE_DEFAULT << 24)           /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN                             (0x1UL << 26)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN_SHIFT                      26                                                            /**< Shift value for GPIO_RATDDBUSI2C0ROUTEEN    */
#define _GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN_MASK                       0x4000000UL                                                   /**< Bit mask for GPIO_RATDDBUSI2C0ROUTEEN       */
#define _GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN_DEFAULT                    0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN_DEFAULT                     (_GPIO_RPURATD9_RATDDBUSI2C0ROUTEEN_DEFAULT << 26)            /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE                            (0x1UL << 27)                                                 /**< SCLROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE_SHIFT                     27                                                            /**< Shift value for GPIO_RATDDBUSI2C0SCLROUTE   */
#define _GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE_MASK                      0x8000000UL                                                   /**< Bit mask for GPIO_RATDDBUSI2C0SCLROUTE      */
#define _GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE_DEFAULT                    (_GPIO_RPURATD9_RATDDBUSI2C0SCLROUTE_DEFAULT << 27)           /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE                            (0x1UL << 28)                                                 /**< SDAROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE_SHIFT                     28                                                            /**< Shift value for GPIO_RATDDBUSI2C0SDAROUTE   */
#define _GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE_MASK                      0x10000000UL                                                  /**< Bit mask for GPIO_RATDDBUSI2C0SDAROUTE      */
#define _GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE_DEFAULT                    (_GPIO_RPURATD9_RATDDBUSI2C0SDAROUTE_DEFAULT << 28)           /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN                             (0x1UL << 30)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN_SHIFT                      30                                                            /**< Shift value for GPIO_RATDDBUSI2C1ROUTEEN    */
#define _GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN_MASK                       0x40000000UL                                                  /**< Bit mask for GPIO_RATDDBUSI2C1ROUTEEN       */
#define _GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN_DEFAULT                    0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN_DEFAULT                     (_GPIO_RPURATD9_RATDDBUSI2C1ROUTEEN_DEFAULT << 30)            /**< Shifted mode DEFAULT for GPIO_RPURATD9      */
#define GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE                            (0x1UL << 31)                                                 /**< SCLROUTE Protection Bit                     */
#define _GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE_SHIFT                     31                                                            /**< Shift value for GPIO_RATDDBUSI2C1SCLROUTE   */
#define _GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE_MASK                      0x80000000UL                                                  /**< Bit mask for GPIO_RATDDBUSI2C1SCLROUTE      */
#define _GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE_DEFAULT                   0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD9              */
#define GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE_DEFAULT                    (_GPIO_RPURATD9_RATDDBUSI2C1SCLROUTE_DEFAULT << 31)           /**< Shifted mode DEFAULT for GPIO_RPURATD9      */

/* Bit fields for GPIO RPURATD10 */
#define _GPIO_RPURATD10_RESETVALUE                                    0x00000000UL                                                  /**< Default value for GPIO_RPURATD10            */
#define _GPIO_RPURATD10_MASK                                          0xFFDDFFFDUL                                                  /**< Mask for GPIO_RPURATD10                     */
#define GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE                           (0x1UL << 0)                                                  /**< SDAROUTE Protection Bit                     */
#define _GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE_SHIFT                    0                                                             /**< Shift value for GPIO_RATDDBUSI2C1SDAROUTE   */
#define _GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE_MASK                     0x1UL                                                         /**< Bit mask for GPIO_RATDDBUSI2C1SDAROUTE      */
#define _GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE_DEFAULT                  0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE_DEFAULT                   (_GPIO_RPURATD10_RATDDBUSI2C1SDAROUTE_DEFAULT << 0)           /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN                          (0x1UL << 2)                                                  /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN_SHIFT                   2                                                             /**< Shift value for GPIO_RATDDBUSKEYPADROUTEEN  */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN_MASK                    0x4UL                                                         /**< Bit mask for GPIO_RATDDBUSKEYPADROUTEEN     */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN_DEFAULT                 0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN_DEFAULT                  (_GPIO_RPURATD10_RATDDBUSKEYPADROUTEEN_DEFAULT << 2)          /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE                     (0x1UL << 3)                                                  /**< COLOUT0ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE_SHIFT              3                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE_MASK               0x8UL                                                         /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT0ROUTE_DEFAULT << 3)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE                     (0x1UL << 4)                                                  /**< COLOUT1ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE_SHIFT              4                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE_MASK               0x10UL                                                        /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT1ROUTE_DEFAULT << 4)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE                     (0x1UL << 5)                                                  /**< COLOUT2ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE_SHIFT              5                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT2ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE_MASK               0x20UL                                                        /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT2ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT2ROUTE_DEFAULT << 5)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE                     (0x1UL << 6)                                                  /**< COLOUT3ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE_SHIFT              6                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT3ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE_MASK               0x40UL                                                        /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT3ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT3ROUTE_DEFAULT << 6)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE                     (0x1UL << 7)                                                  /**< COLOUT4ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE_SHIFT              7                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT4ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE_MASK               0x80UL                                                        /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT4ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT4ROUTE_DEFAULT << 7)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE                     (0x1UL << 8)                                                  /**< COLOUT5ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE_SHIFT              8                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT5ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE_MASK               0x100UL                                                       /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT5ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT5ROUTE_DEFAULT << 8)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE                     (0x1UL << 9)                                                  /**< COLOUT6ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE_SHIFT              9                                                             /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT6ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE_MASK               0x200UL                                                       /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT6ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT6ROUTE_DEFAULT << 9)     /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE                     (0x1UL << 10)                                                 /**< COLOUT7ROUTE Protection Bit                 */
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE_SHIFT              10                                                            /**< Shift value for GPIO_RATDDBUSKEYPADCOLOUT7ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE_MASK               0x400UL                                                       /**< Bit mask for GPIO_RATDDBUSKEYPADCOLOUT7ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE_DEFAULT            0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE_DEFAULT             (_GPIO_RPURATD10_RATDDBUSKEYPADCOLOUT7ROUTE_DEFAULT << 10)    /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE                   (0x1UL << 11)                                                 /**< ROWSENSE0ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE_SHIFT            11                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE_MASK             0x800UL                                                       /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE0ROUTE_DEFAULT << 11)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE                   (0x1UL << 12)                                                 /**< ROWSENSE1ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE_SHIFT            12                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE_MASK             0x1000UL                                                      /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE1ROUTE_DEFAULT << 12)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE                   (0x1UL << 13)                                                 /**< ROWSENSE2ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE_SHIFT            13                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE2ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE_MASK             0x2000UL                                                      /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE2ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE2ROUTE_DEFAULT << 13)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE                   (0x1UL << 14)                                                 /**< ROWSENSE3ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE_SHIFT            14                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE3ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE_MASK             0x4000UL                                                      /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE3ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE3ROUTE_DEFAULT << 14)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE                   (0x1UL << 15)                                                 /**< ROWSENSE4ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE_SHIFT            15                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE4ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE_MASK             0x8000UL                                                      /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE4ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE4ROUTE_DEFAULT << 15)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE                   (0x1UL << 16)                                                 /**< ROWSENSE5ROUTE Protection Bit               */
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE_SHIFT            16                                                            /**< Shift value for GPIO_RATDDBUSKEYPADROWSENSE5ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE_MASK             0x10000UL                                                     /**< Bit mask for GPIO_RATDDBUSKEYPADROWSENSE5ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE_DEFAULT          0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE_DEFAULT           (_GPIO_RPURATD10_RATDDBUSKEYPADROWSENSE5ROUTE_DEFAULT << 16)  /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN                         (0x1UL << 18)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN_SHIFT                  18                                                            /**< Shift value for GPIO_RATDDBUSLETIMERROUTEEN */
#define _GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN_MASK                   0x40000UL                                                     /**< Bit mask for GPIO_RATDDBUSLETIMERROUTEEN    */
#define _GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN_DEFAULT                 (_GPIO_RPURATD10_RATDDBUSLETIMERROUTEEN_DEFAULT << 18)        /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE                       (0x1UL << 19)                                                 /**< OUT0ROUTE Protection Bit                    */
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE_SHIFT                19                                                            /**< Shift value for GPIO_RATDDBUSLETIMEROUT0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE_MASK                 0x80000UL                                                     /**< Bit mask for GPIO_RATDDBUSLETIMEROUT0ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSLETIMEROUT0ROUTE_DEFAULT << 19)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE                       (0x1UL << 20)                                                 /**< OUT1ROUTE Protection Bit                    */
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE_SHIFT                20                                                            /**< Shift value for GPIO_RATDDBUSLETIMEROUT1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE_MASK                 0x100000UL                                                    /**< Bit mask for GPIO_RATDDBUSLETIMEROUT1ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSLETIMEROUT1ROUTE_DEFAULT << 20)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMROUTEEN                           (0x1UL << 22)                                                 /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD10_RATDDBUSMODEMROUTEEN_SHIFT                    22                                                            /**< Shift value for GPIO_RATDDBUSMODEMROUTEEN   */
#define _GPIO_RPURATD10_RATDDBUSMODEMROUTEEN_MASK                     0x400000UL                                                    /**< Bit mask for GPIO_RATDDBUSMODEMROUTEEN      */
#define _GPIO_RPURATD10_RATDDBUSMODEMROUTEEN_DEFAULT                  0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMROUTEEN_DEFAULT                   (_GPIO_RPURATD10_RATDDBUSMODEMROUTEEN_DEFAULT << 22)          /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE                         (0x1UL << 23)                                                 /**< ANT0ROUTE Protection Bit                    */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE_SHIFT                  23                                                            /**< Shift value for GPIO_RATDDBUSMODEMANT0ROUTE */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE_MASK                   0x800000UL                                                    /**< Bit mask for GPIO_RATDDBUSMODEMANT0ROUTE    */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE_DEFAULT                 (_GPIO_RPURATD10_RATDDBUSMODEMANT0ROUTE_DEFAULT << 23)        /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE                         (0x1UL << 24)                                                 /**< ANT1ROUTE Protection Bit                    */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE_SHIFT                  24                                                            /**< Shift value for GPIO_RATDDBUSMODEMANT1ROUTE */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE_MASK                   0x1000000UL                                                   /**< Bit mask for GPIO_RATDDBUSMODEMANT1ROUTE    */
#define _GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE_DEFAULT                0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE_DEFAULT                 (_GPIO_RPURATD10_RATDDBUSMODEMANT1ROUTE_DEFAULT << 24)        /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE                  (0x1UL << 25)                                                 /**< ANTROLLOVERROUTE Protection Bit             */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE_SHIFT           25                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTROLLOVERROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE_MASK            0x2000000UL                                                   /**< Bit mask for GPIO_RATDDBUSMODEMANTROLLOVERROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE_DEFAULT         0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE_DEFAULT          (_GPIO_RPURATD10_RATDDBUSMODEMANTROLLOVERROUTE_DEFAULT << 25) /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE                       (0x1UL << 26)                                                 /**< ANTRR0ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE_SHIFT                26                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR0ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE_MASK                 0x4000000UL                                                   /**< Bit mask for GPIO_RATDDBUSMODEMANTRR0ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR0ROUTE_DEFAULT << 26)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE                       (0x1UL << 27)                                                 /**< ANTRR1ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE_SHIFT                27                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR1ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE_MASK                 0x8000000UL                                                   /**< Bit mask for GPIO_RATDDBUSMODEMANTRR1ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR1ROUTE_DEFAULT << 27)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE                       (0x1UL << 28)                                                 /**< ANTRR2ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE_SHIFT                28                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR2ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE_MASK                 0x10000000UL                                                  /**< Bit mask for GPIO_RATDDBUSMODEMANTRR2ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR2ROUTE_DEFAULT << 28)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE                       (0x1UL << 29)                                                 /**< ANTRR3ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE_SHIFT                29                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR3ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE_MASK                 0x20000000UL                                                  /**< Bit mask for GPIO_RATDDBUSMODEMANTRR3ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR3ROUTE_DEFAULT << 29)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE                       (0x1UL << 30)                                                 /**< ANTRR4ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE_SHIFT                30                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR4ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE_MASK                 0x40000000UL                                                  /**< Bit mask for GPIO_RATDDBUSMODEMANTRR4ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR4ROUTE_DEFAULT << 30)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE                       (0x1UL << 31)                                                 /**< ANTRR5ROUTE Protection Bit                  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE_SHIFT                31                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTRR5ROUTE*/
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE_MASK                 0x80000000UL                                                  /**< Bit mask for GPIO_RATDDBUSMODEMANTRR5ROUTE  */
#define _GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE_DEFAULT              0x00000000UL                                                  /**< Mode DEFAULT for GPIO_RPURATD10             */
#define GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE_DEFAULT               (_GPIO_RPURATD10_RATDDBUSMODEMANTRR5ROUTE_DEFAULT << 31)      /**< Shifted mode DEFAULT for GPIO_RPURATD10     */

/* Bit fields for GPIO RPURATD11 */
#define _GPIO_RPURATD11_RESETVALUE                                    0x00000000UL                                                 /**< Default value for GPIO_RPURATD11            */
#define _GPIO_RPURATD11_MASK                                          0xFFFFF67FUL                                                 /**< Mask for GPIO_RPURATD11                     */
#define GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE                      (0x1UL << 0)                                                 /**< ANTSWENROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE_SHIFT               0                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTSWENROUTE*/
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE_MASK                0x1UL                                                        /**< Bit mask for GPIO_RATDDBUSMODEMANTSWENROUTE */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSMODEMANTSWENROUTE_DEFAULT << 0)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE                      (0x1UL << 1)                                                 /**< ANTSWUSROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE_SHIFT               1                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTSWUSROUTE*/
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE_MASK                0x2UL                                                        /**< Bit mask for GPIO_RATDDBUSMODEMANTSWUSROUTE */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSMODEMANTSWUSROUTE_DEFAULT << 1)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE                      (0x1UL << 2)                                                 /**< ANTTRIGROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE_SHIFT               2                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTTRIGROUTE*/
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE_MASK                0x4UL                                                        /**< Bit mask for GPIO_RATDDBUSMODEMANTTRIGROUTE */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSMODEMANTTRIGROUTE_DEFAULT << 2)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE                  (0x1UL << 3)                                                 /**< ANTTRIGSTOPROUTE Protection Bit             */
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE_SHIFT           3                                                            /**< Shift value for GPIO_RATDDBUSMODEMANTTRIGSTOPROUTE*/
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE_MASK            0x8UL                                                        /**< Bit mask for GPIO_RATDDBUSMODEMANTTRIGSTOPROUTE*/
#define _GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE_DEFAULT         0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE_DEFAULT          (_GPIO_RPURATD11_RATDDBUSMODEMANTTRIGSTOPROUTE_DEFAULT << 3) /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE                         (0x1UL << 4)                                                 /**< DCLKROUTE Protection Bit                    */
#define _GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE_SHIFT                  4                                                            /**< Shift value for GPIO_RATDDBUSMODEMDCLKROUTE */
#define _GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE_MASK                   0x10UL                                                       /**< Bit mask for GPIO_RATDDBUSMODEMDCLKROUTE    */
#define _GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE_DEFAULT                0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE_DEFAULT                 (_GPIO_RPURATD11_RATDDBUSMODEMDCLKROUTE_DEFAULT << 4)        /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMDINROUTE                          (0x1UL << 5)                                                 /**< DINROUTE Protection Bit                     */
#define _GPIO_RPURATD11_RATDDBUSMODEMDINROUTE_SHIFT                   5                                                            /**< Shift value for GPIO_RATDDBUSMODEMDINROUTE  */
#define _GPIO_RPURATD11_RATDDBUSMODEMDINROUTE_MASK                    0x20UL                                                       /**< Bit mask for GPIO_RATDDBUSMODEMDINROUTE     */
#define _GPIO_RPURATD11_RATDDBUSMODEMDINROUTE_DEFAULT                 0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMDINROUTE_DEFAULT                  (_GPIO_RPURATD11_RATDDBUSMODEMDINROUTE_DEFAULT << 5)         /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE                         (0x1UL << 6)                                                 /**< DOUTROUTE Protection Bit                    */
#define _GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE_SHIFT                  6                                                            /**< Shift value for GPIO_RATDDBUSMODEMDOUTROUTE */
#define _GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE_MASK                   0x40UL                                                       /**< Bit mask for GPIO_RATDDBUSMODEMDOUTROUTE    */
#define _GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE_DEFAULT                0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE_DEFAULT                 (_GPIO_RPURATD11_RATDDBUSMODEMDOUTROUTE_DEFAULT << 6)        /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE                         (0x1UL << 9)                                                 /**< S0INROUTE Protection Bit                    */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE_SHIFT                  9                                                            /**< Shift value for GPIO_RATDDBUSPCNT0S0INROUTE */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE_MASK                   0x200UL                                                      /**< Bit mask for GPIO_RATDDBUSPCNT0S0INROUTE    */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE_DEFAULT                0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE_DEFAULT                 (_GPIO_RPURATD11_RATDDBUSPCNT0S0INROUTE_DEFAULT << 9)        /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE                         (0x1UL << 10)                                                /**< S1INROUTE Protection Bit                    */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE_SHIFT                  10                                                           /**< Shift value for GPIO_RATDDBUSPCNT0S1INROUTE */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE_MASK                   0x400UL                                                      /**< Bit mask for GPIO_RATDDBUSPCNT0S1INROUTE    */
#define _GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE_DEFAULT                0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE_DEFAULT                 (_GPIO_RPURATD11_RATDDBUSPCNT0S1INROUTE_DEFAULT << 10)       /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN                            (0x1UL << 12)                                                /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN_SHIFT                     12                                                           /**< Shift value for GPIO_RATDDBUSPRS0ROUTEEN    */
#define _GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN_MASK                      0x1000UL                                                     /**< Bit mask for GPIO_RATDDBUSPRS0ROUTEEN       */
#define _GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN_DEFAULT                   0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN_DEFAULT                    (_GPIO_RPURATD11_RATDDBUSPRS0ROUTEEN_DEFAULT << 12)          /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE                       (0x1UL << 13)                                                /**< ASYNCH0ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE_SHIFT                13                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH0ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE_MASK                 0x2000UL                                                     /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH0ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH0ROUTE_DEFAULT << 13)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE                       (0x1UL << 14)                                                /**< ASYNCH1ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE_SHIFT                14                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH1ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE_MASK                 0x4000UL                                                     /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH1ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH1ROUTE_DEFAULT << 14)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE                       (0x1UL << 15)                                                /**< ASYNCH2ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE_SHIFT                15                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH2ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE_MASK                 0x8000UL                                                     /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH2ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH2ROUTE_DEFAULT << 15)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE                       (0x1UL << 16)                                                /**< ASYNCH3ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE_SHIFT                16                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH3ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE_MASK                 0x10000UL                                                    /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH3ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH3ROUTE_DEFAULT << 16)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE                       (0x1UL << 17)                                                /**< ASYNCH4ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE_SHIFT                17                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH4ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE_MASK                 0x20000UL                                                    /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH4ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH4ROUTE_DEFAULT << 17)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE                       (0x1UL << 18)                                                /**< ASYNCH5ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE_SHIFT                18                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH5ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE_MASK                 0x40000UL                                                    /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH5ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH5ROUTE_DEFAULT << 18)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE                       (0x1UL << 19)                                                /**< ASYNCH6ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE_SHIFT                19                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH6ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE_MASK                 0x80000UL                                                    /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH6ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH6ROUTE_DEFAULT << 19)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE                       (0x1UL << 20)                                                /**< ASYNCH7ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE_SHIFT                20                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH7ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE_MASK                 0x100000UL                                                   /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH7ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH7ROUTE_DEFAULT << 20)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE                       (0x1UL << 21)                                                /**< ASYNCH8ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE_SHIFT                21                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH8ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE_MASK                 0x200000UL                                                   /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH8ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH8ROUTE_DEFAULT << 21)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE                       (0x1UL << 22)                                                /**< ASYNCH9ROUTE Protection Bit                 */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE_SHIFT                22                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH9ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE_MASK                 0x400000UL                                                   /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH9ROUTE  */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE_DEFAULT              0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE_DEFAULT               (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH9ROUTE_DEFAULT << 22)     /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE                      (0x1UL << 23)                                                /**< ASYNCH10ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE_SHIFT               23                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH10ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE_MASK                0x800000UL                                                   /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH10ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH10ROUTE_DEFAULT << 23)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE                      (0x1UL << 24)                                                /**< ASYNCH11ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE_SHIFT               24                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH11ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE_MASK                0x1000000UL                                                  /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH11ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH11ROUTE_DEFAULT << 24)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE                      (0x1UL << 25)                                                /**< ASYNCH12ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE_SHIFT               25                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH12ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE_MASK                0x2000000UL                                                  /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH12ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH12ROUTE_DEFAULT << 25)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE                      (0x1UL << 26)                                                /**< ASYNCH13ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE_SHIFT               26                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH13ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE_MASK                0x4000000UL                                                  /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH13ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH13ROUTE_DEFAULT << 26)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE                      (0x1UL << 27)                                                /**< ASYNCH14ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE_SHIFT               27                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH14ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE_MASK                0x8000000UL                                                  /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH14ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH14ROUTE_DEFAULT << 27)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE                      (0x1UL << 28)                                                /**< ASYNCH15ROUTE Protection Bit                */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE_SHIFT               28                                                           /**< Shift value for GPIO_RATDDBUSPRS0ASYNCH15ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE_MASK                0x10000000UL                                                 /**< Bit mask for GPIO_RATDDBUSPRS0ASYNCH15ROUTE */
#define _GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE_DEFAULT             0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE_DEFAULT              (_GPIO_RPURATD11_RATDDBUSPRS0ASYNCH15ROUTE_DEFAULT << 28)    /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE                        (0x1UL << 29)                                                /**< SYNCH0ROUTE Protection Bit                  */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE_SHIFT                 29                                                           /**< Shift value for GPIO_RATDDBUSPRS0SYNCH0ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE_MASK                  0x20000000UL                                                 /**< Bit mask for GPIO_RATDDBUSPRS0SYNCH0ROUTE   */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE_DEFAULT               0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE_DEFAULT                (_GPIO_RPURATD11_RATDDBUSPRS0SYNCH0ROUTE_DEFAULT << 29)      /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE                        (0x1UL << 30)                                                /**< SYNCH1ROUTE Protection Bit                  */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE_SHIFT                 30                                                           /**< Shift value for GPIO_RATDDBUSPRS0SYNCH1ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE_MASK                  0x40000000UL                                                 /**< Bit mask for GPIO_RATDDBUSPRS0SYNCH1ROUTE   */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE_DEFAULT               0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE_DEFAULT                (_GPIO_RPURATD11_RATDDBUSPRS0SYNCH1ROUTE_DEFAULT << 30)      /**< Shifted mode DEFAULT for GPIO_RPURATD11     */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE                        (0x1UL << 31)                                                /**< SYNCH2ROUTE Protection Bit                  */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE_SHIFT                 31                                                           /**< Shift value for GPIO_RATDDBUSPRS0SYNCH2ROUTE*/
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE_MASK                  0x80000000UL                                                 /**< Bit mask for GPIO_RATDDBUSPRS0SYNCH2ROUTE   */
#define _GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE_DEFAULT               0x00000000UL                                                 /**< Mode DEFAULT for GPIO_RPURATD11             */
#define GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE_DEFAULT                (_GPIO_RPURATD11_RATDDBUSPRS0SYNCH2ROUTE_DEFAULT << 31)      /**< Shifted mode DEFAULT for GPIO_RPURATD11     */

/* Bit fields for GPIO RPURATD12 */
#define _GPIO_RPURATD12_RESETVALUE                                    0x00000000UL                                                       /**< Default value for GPIO_RPURATD12            */
#define _GPIO_RPURATD12_MASK                                          0x4FFFFFDDUL                                                       /**< Mask for GPIO_RPURATD12                     */
#define GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE                        (0x1UL << 0)                                                       /**< SYNCH3ROUTE Protection Bit                  */
#define _GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE_SHIFT                 0                                                                  /**< Shift value for GPIO_RATDDBUSPRS0SYNCH3ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE_MASK                  0x1UL                                                              /**< Bit mask for GPIO_RATDDBUSPRS0SYNCH3ROUTE   */
#define _GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE_DEFAULT               0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE_DEFAULT                (_GPIO_RPURATD12_RATDDBUSPRS0SYNCH3ROUTE_DEFAULT << 0)             /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRACROUTEEN                             (0x1UL << 2)                                                       /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD12_RATDDBUSRACROUTEEN_SHIFT                      2                                                                  /**< Shift value for GPIO_RATDDBUSRACROUTEEN     */
#define _GPIO_RPURATD12_RATDDBUSRACROUTEEN_MASK                       0x4UL                                                              /**< Bit mask for GPIO_RATDDBUSRACROUTEEN        */
#define _GPIO_RPURATD12_RATDDBUSRACROUTEEN_DEFAULT                    0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRACROUTEEN_DEFAULT                     (_GPIO_RPURATD12_RATDDBUSRACROUTEEN_DEFAULT << 2)                  /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRACLNAENROUTE                          (0x1UL << 3)                                                       /**< LNAENROUTE Protection Bit                   */
#define _GPIO_RPURATD12_RATDDBUSRACLNAENROUTE_SHIFT                   3                                                                  /**< Shift value for GPIO_RATDDBUSRACLNAENROUTE  */
#define _GPIO_RPURATD12_RATDDBUSRACLNAENROUTE_MASK                    0x8UL                                                              /**< Bit mask for GPIO_RATDDBUSRACLNAENROUTE     */
#define _GPIO_RPURATD12_RATDDBUSRACLNAENROUTE_DEFAULT                 0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRACLNAENROUTE_DEFAULT                  (_GPIO_RPURATD12_RATDDBUSRACLNAENROUTE_DEFAULT << 3)               /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRACPAENROUTE                           (0x1UL << 4)                                                       /**< PAENROUTE Protection Bit                    */
#define _GPIO_RPURATD12_RATDDBUSRACPAENROUTE_SHIFT                    4                                                                  /**< Shift value for GPIO_RATDDBUSRACPAENROUTE   */
#define _GPIO_RPURATD12_RATDDBUSRACPAENROUTE_MASK                     0x10UL                                                             /**< Bit mask for GPIO_RATDDBUSRACPAENROUTE      */
#define _GPIO_RPURATD12_RATDDBUSRACPAENROUTE_DEFAULT                  0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRACPAENROUTE_DEFAULT                   (_GPIO_RPURATD12_RATDDBUSRACPAENROUTE_DEFAULT << 4)                /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN                          (0x1UL << 6)                                                       /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN_SHIFT                   6                                                                  /**< Shift value for GPIO_RATDDBUSRFECA0ROUTEEN  */
#define _GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN_MASK                    0x40UL                                                             /**< Bit mask for GPIO_RATDDBUSRFECA0ROUTEEN     */
#define _GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN_DEFAULT                 0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN_DEFAULT                  (_GPIO_RPURATD12_RATDDBUSRFECA0ROUTEEN_DEFAULT << 6)               /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE                    (0x1UL << 7)                                                       /**< DATAOUT0ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE_SHIFT             7                                                                  /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT0ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE_MASK              0x80UL                                                             /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT0ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT0ROUTE_DEFAULT << 7)         /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE                    (0x1UL << 8)                                                       /**< DATAOUT1ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE_SHIFT             8                                                                  /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT1ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE_MASK              0x100UL                                                            /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT1ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT1ROUTE_DEFAULT << 8)         /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE                    (0x1UL << 9)                                                       /**< DATAOUT2ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE_SHIFT             9                                                                  /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT2ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE_MASK              0x200UL                                                            /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT2ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT2ROUTE_DEFAULT << 9)         /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE                    (0x1UL << 10)                                                      /**< DATAOUT3ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE_SHIFT             10                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT3ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE_MASK              0x400UL                                                            /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT3ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT3ROUTE_DEFAULT << 10)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE                    (0x1UL << 11)                                                      /**< DATAOUT4ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE_SHIFT             11                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT4ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE_MASK              0x800UL                                                            /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT4ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT4ROUTE_DEFAULT << 11)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE                    (0x1UL << 12)                                                      /**< DATAOUT5ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE_SHIFT             12                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT5ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE_MASK              0x1000UL                                                           /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT5ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT5ROUTE_DEFAULT << 12)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE                    (0x1UL << 13)                                                      /**< DATAOUT6ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE_SHIFT             13                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT6ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE_MASK              0x2000UL                                                           /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT6ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT6ROUTE_DEFAULT << 13)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE                    (0x1UL << 14)                                                      /**< DATAOUT7ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE_SHIFT             14                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT7ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE_MASK              0x4000UL                                                           /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT7ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT7ROUTE_DEFAULT << 14)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE                    (0x1UL << 15)                                                      /**< DATAOUT8ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE_SHIFT             15                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT8ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE_MASK              0x8000UL                                                           /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT8ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT8ROUTE_DEFAULT << 15)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE                    (0x1UL << 16)                                                      /**< DATAOUT9ROUTE Protection Bit                */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE_SHIFT             16                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT9ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE_MASK              0x10000UL                                                          /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT9ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE_DEFAULT           0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE_DEFAULT            (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT9ROUTE_DEFAULT << 16)        /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE                   (0x1UL << 17)                                                      /**< DATAOUT10ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE_SHIFT            17                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT10ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE_MASK             0x20000UL                                                          /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT10ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT10ROUTE_DEFAULT << 17)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE                   (0x1UL << 18)                                                      /**< DATAOUT11ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE_SHIFT            18                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT11ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE_MASK             0x40000UL                                                          /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT11ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT11ROUTE_DEFAULT << 18)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE                   (0x1UL << 19)                                                      /**< DATAOUT12ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE_SHIFT            19                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT12ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE_MASK             0x80000UL                                                          /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT12ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT12ROUTE_DEFAULT << 19)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE                   (0x1UL << 20)                                                      /**< DATAOUT13ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE_SHIFT            20                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT13ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE_MASK             0x100000UL                                                         /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT13ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT13ROUTE_DEFAULT << 20)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE                   (0x1UL << 21)                                                      /**< DATAOUT14ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE_SHIFT            21                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT14ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE_MASK             0x200000UL                                                         /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT14ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT14ROUTE_DEFAULT << 21)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE                   (0x1UL << 22)                                                      /**< DATAOUT15ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE_SHIFT            22                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT15ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE_MASK             0x400000UL                                                         /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT15ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT15ROUTE_DEFAULT << 22)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE                   (0x1UL << 23)                                                      /**< DATAOUT16ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE_SHIFT            23                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT16ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE_MASK             0x800000UL                                                         /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT16ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT16ROUTE_DEFAULT << 23)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE                   (0x1UL << 24)                                                      /**< DATAOUT17ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE_SHIFT            24                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT17ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE_MASK             0x1000000UL                                                        /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT17ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT17ROUTE_DEFAULT << 24)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE                   (0x1UL << 25)                                                      /**< DATAOUT18ROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE_SHIFT            25                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAOUT18ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE_MASK             0x2000000UL                                                        /**< Bit mask for GPIO_RATDDBUSRFECA0DATAOUT18ROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAOUT18ROUTE_DEFAULT << 25)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE                   (0x1UL << 26)                                                      /**< DATAVALIDROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE_SHIFT            26                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0DATAVALIDROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE_MASK             0x4000000UL                                                        /**< Bit mask for GPIO_RATDDBUSRFECA0DATAVALIDROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0DATAVALIDROUTE_DEFAULT << 26)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE                   (0x1UL << 27)                                                      /**< TRIGGERINROUTE Protection Bit               */
#define _GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE_SHIFT            27                                                                 /**< Shift value for GPIO_RATDDBUSRFECA0TRIGGERINROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE_MASK             0x8000000UL                                                        /**< Bit mask for GPIO_RATDDBUSRFECA0TRIGGERINROUTE*/
#define _GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE_DEFAULT          0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE_DEFAULT           (_GPIO_RPURATD12_RATDDBUSRFECA0TRIGGERINROUTE_DEFAULT << 27)       /**< Shifted mode DEFAULT for GPIO_RPURATD12     */
#define GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE             (0x1UL << 30)                                                      /**< BUFOUTREQINASYNCROUTE Protection Bit        */
#define _GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE_SHIFT      30                                                                 /**< Shift value for GPIO_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE*/
#define _GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE_MASK       0x40000000UL                                                       /**< Bit mask for GPIO_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE*/
#define _GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE_DEFAULT    0x00000000UL                                                       /**< Mode DEFAULT for GPIO_RPURATD12             */
#define GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE_DEFAULT     (_GPIO_RPURATD12_RATDDBUSSYXO0BUFOUTREQINASYNCROUTE_DEFAULT << 30) /**< Shifted mode DEFAULT for GPIO_RPURATD12     */

/* Bit fields for GPIO RPURATD13 */
#define _GPIO_RPURATD13_RESETVALUE                                    0x00000000UL                                            /**< Default value for GPIO_RPURATD13            */
#define _GPIO_RPURATD13_MASK                                          0x7F7F7F7FUL                                            /**< Mask for GPIO_RPURATD13                     */
#define GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN                          (0x1UL << 0)                                            /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN_SHIFT                   0                                                       /**< Shift value for GPIO_RATDDBUSTIMER0ROUTEEN  */
#define _GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN_MASK                    0x1UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER0ROUTEEN     */
#define _GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN_DEFAULT                  (_GPIO_RPURATD13_RATDDBUSTIMER0ROUTEEN_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE                         (0x1UL << 1)                                            /**< CC0ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE_SHIFT                  1                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CC0ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE_MASK                   0x2UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER0CC0ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER0CC0ROUTE_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE                         (0x1UL << 2)                                            /**< CC1ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE_SHIFT                  2                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CC1ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE_MASK                   0x4UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER0CC1ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER0CC1ROUTE_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE                         (0x1UL << 3)                                            /**< CC2ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE_SHIFT                  3                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CC2ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE_MASK                   0x8UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER0CC2ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER0CC2ROUTE_DEFAULT << 3)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE                        (0x1UL << 4)                                            /**< CCC0ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE_SHIFT                 4                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CCC0ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE_MASK                  0x10UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER0CCC0ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER0CCC0ROUTE_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE                        (0x1UL << 5)                                            /**< CCC1ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE_SHIFT                 5                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CCC1ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE_MASK                  0x20UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER0CCC1ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER0CCC1ROUTE_DEFAULT << 5)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE                        (0x1UL << 6)                                            /**< CCC2ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE_SHIFT                 6                                                       /**< Shift value for GPIO_RATDDBUSTIMER0CCC2ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE_MASK                  0x40UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER0CCC2ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER0CCC2ROUTE_DEFAULT << 6)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN                          (0x1UL << 8)                                            /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN_SHIFT                   8                                                       /**< Shift value for GPIO_RATDDBUSTIMER1ROUTEEN  */
#define _GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN_MASK                    0x100UL                                                 /**< Bit mask for GPIO_RATDDBUSTIMER1ROUTEEN     */
#define _GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN_DEFAULT                  (_GPIO_RPURATD13_RATDDBUSTIMER1ROUTEEN_DEFAULT << 8)    /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE                         (0x1UL << 9)                                            /**< CC0ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE_SHIFT                  9                                                       /**< Shift value for GPIO_RATDDBUSTIMER1CC0ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE_MASK                   0x200UL                                                 /**< Bit mask for GPIO_RATDDBUSTIMER1CC0ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER1CC0ROUTE_DEFAULT << 9)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE                         (0x1UL << 10)                                           /**< CC1ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE_SHIFT                  10                                                      /**< Shift value for GPIO_RATDDBUSTIMER1CC1ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE_MASK                   0x400UL                                                 /**< Bit mask for GPIO_RATDDBUSTIMER1CC1ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER1CC1ROUTE_DEFAULT << 10)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE                         (0x1UL << 11)                                           /**< CC2ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE_SHIFT                  11                                                      /**< Shift value for GPIO_RATDDBUSTIMER1CC2ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE_MASK                   0x800UL                                                 /**< Bit mask for GPIO_RATDDBUSTIMER1CC2ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER1CC2ROUTE_DEFAULT << 11)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE                        (0x1UL << 12)                                           /**< CCC0ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE_SHIFT                 12                                                      /**< Shift value for GPIO_RATDDBUSTIMER1CCC0ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE_MASK                  0x1000UL                                                /**< Bit mask for GPIO_RATDDBUSTIMER1CCC0ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER1CCC0ROUTE_DEFAULT << 12) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE                        (0x1UL << 13)                                           /**< CCC1ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE_SHIFT                 13                                                      /**< Shift value for GPIO_RATDDBUSTIMER1CCC1ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE_MASK                  0x2000UL                                                /**< Bit mask for GPIO_RATDDBUSTIMER1CCC1ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER1CCC1ROUTE_DEFAULT << 13) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE                        (0x1UL << 14)                                           /**< CCC2ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE_SHIFT                 14                                                      /**< Shift value for GPIO_RATDDBUSTIMER1CCC2ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE_MASK                  0x4000UL                                                /**< Bit mask for GPIO_RATDDBUSTIMER1CCC2ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER1CCC2ROUTE_DEFAULT << 14) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN                          (0x1UL << 16)                                           /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN_SHIFT                   16                                                      /**< Shift value for GPIO_RATDDBUSTIMER2ROUTEEN  */
#define _GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN_MASK                    0x10000UL                                               /**< Bit mask for GPIO_RATDDBUSTIMER2ROUTEEN     */
#define _GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN_DEFAULT                  (_GPIO_RPURATD13_RATDDBUSTIMER2ROUTEEN_DEFAULT << 16)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE                         (0x1UL << 17)                                           /**< CC0ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE_SHIFT                  17                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CC0ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE_MASK                   0x20000UL                                               /**< Bit mask for GPIO_RATDDBUSTIMER2CC0ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER2CC0ROUTE_DEFAULT << 17)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE                         (0x1UL << 18)                                           /**< CC1ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE_SHIFT                  18                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CC1ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE_MASK                   0x40000UL                                               /**< Bit mask for GPIO_RATDDBUSTIMER2CC1ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER2CC1ROUTE_DEFAULT << 18)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE                         (0x1UL << 19)                                           /**< CC2ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE_SHIFT                  19                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CC2ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE_MASK                   0x80000UL                                               /**< Bit mask for GPIO_RATDDBUSTIMER2CC2ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER2CC2ROUTE_DEFAULT << 19)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE                        (0x1UL << 20)                                           /**< CCC0ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE_SHIFT                 20                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CCC0ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE_MASK                  0x100000UL                                              /**< Bit mask for GPIO_RATDDBUSTIMER2CCC0ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER2CCC0ROUTE_DEFAULT << 20) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE                        (0x1UL << 21)                                           /**< CCC1ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE_SHIFT                 21                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CCC1ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE_MASK                  0x200000UL                                              /**< Bit mask for GPIO_RATDDBUSTIMER2CCC1ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER2CCC1ROUTE_DEFAULT << 21) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE                        (0x1UL << 22)                                           /**< CCC2ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE_SHIFT                 22                                                      /**< Shift value for GPIO_RATDDBUSTIMER2CCC2ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE_MASK                  0x400000UL                                              /**< Bit mask for GPIO_RATDDBUSTIMER2CCC2ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER2CCC2ROUTE_DEFAULT << 22) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN                          (0x1UL << 24)                                           /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN_SHIFT                   24                                                      /**< Shift value for GPIO_RATDDBUSTIMER3ROUTEEN  */
#define _GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN_MASK                    0x1000000UL                                             /**< Bit mask for GPIO_RATDDBUSTIMER3ROUTEEN     */
#define _GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN_DEFAULT                  (_GPIO_RPURATD13_RATDDBUSTIMER3ROUTEEN_DEFAULT << 24)   /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE                         (0x1UL << 25)                                           /**< CC0ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE_SHIFT                  25                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CC0ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE_MASK                   0x2000000UL                                             /**< Bit mask for GPIO_RATDDBUSTIMER3CC0ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER3CC0ROUTE_DEFAULT << 25)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE                         (0x1UL << 26)                                           /**< CC1ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE_SHIFT                  26                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CC1ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE_MASK                   0x4000000UL                                             /**< Bit mask for GPIO_RATDDBUSTIMER3CC1ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER3CC1ROUTE_DEFAULT << 26)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE                         (0x1UL << 27)                                           /**< CC2ROUTE Protection Bit                     */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE_SHIFT                  27                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CC2ROUTE */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE_MASK                   0x8000000UL                                             /**< Bit mask for GPIO_RATDDBUSTIMER3CC2ROUTE    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE_DEFAULT                 (_GPIO_RPURATD13_RATDDBUSTIMER3CC2ROUTE_DEFAULT << 27)  /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE                        (0x1UL << 28)                                           /**< CCC0ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE_SHIFT                 28                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CCC0ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE_MASK                  0x10000000UL                                            /**< Bit mask for GPIO_RATDDBUSTIMER3CCC0ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER3CCC0ROUTE_DEFAULT << 28) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE                        (0x1UL << 29)                                           /**< CCC1ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE_SHIFT                 29                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CCC1ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE_MASK                  0x20000000UL                                            /**< Bit mask for GPIO_RATDDBUSTIMER3CCC1ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER3CCC1ROUTE_DEFAULT << 29) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE                        (0x1UL << 30)                                           /**< CCC2ROUTE Protection Bit                    */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE_SHIFT                 30                                                      /**< Shift value for GPIO_RATDDBUSTIMER3CCC2ROUTE*/
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE_MASK                  0x40000000UL                                            /**< Bit mask for GPIO_RATDDBUSTIMER3CCC2ROUTE   */
#define _GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD13             */
#define GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE_DEFAULT                (_GPIO_RPURATD13_RATDDBUSTIMER3CCC2ROUTE_DEFAULT << 30) /**< Shifted mode DEFAULT for GPIO_RPURATD13     */

/* Bit fields for GPIO RPURATD14 */
#define _GPIO_RPURATD14_RESETVALUE                                    0x00000000UL                                            /**< Default value for GPIO_RPURATD14            */
#define _GPIO_RPURATD14_MASK                                          0x00007F7FUL                                            /**< Mask for GPIO_RPURATD14                     */
#define GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN                          (0x1UL << 0)                                            /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN_SHIFT                   0                                                       /**< Shift value for GPIO_RATDDBUSTIMER4ROUTEEN  */
#define _GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN_MASK                    0x1UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER4ROUTEEN     */
#define _GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN_DEFAULT                  (_GPIO_RPURATD14_RATDDBUSTIMER4ROUTEEN_DEFAULT << 0)    /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE                         (0x1UL << 1)                                            /**< CC0ROUTE Protection Bit                     */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE_SHIFT                  1                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CC0ROUTE */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE_MASK                   0x2UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER4CC0ROUTE    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE_DEFAULT                 (_GPIO_RPURATD14_RATDDBUSTIMER4CC0ROUTE_DEFAULT << 1)   /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE                         (0x1UL << 2)                                            /**< CC1ROUTE Protection Bit                     */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE_SHIFT                  2                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CC1ROUTE */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE_MASK                   0x4UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER4CC1ROUTE    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE_DEFAULT                 (_GPIO_RPURATD14_RATDDBUSTIMER4CC1ROUTE_DEFAULT << 2)   /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE                         (0x1UL << 3)                                            /**< CC2ROUTE Protection Bit                     */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE_SHIFT                  3                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CC2ROUTE */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE_MASK                   0x8UL                                                   /**< Bit mask for GPIO_RATDDBUSTIMER4CC2ROUTE    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE_DEFAULT                 (_GPIO_RPURATD14_RATDDBUSTIMER4CC2ROUTE_DEFAULT << 3)   /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE                        (0x1UL << 4)                                            /**< CCC0ROUTE Protection Bit                    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE_SHIFT                 4                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CCC0ROUTE*/
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE_MASK                  0x10UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER4CCC0ROUTE   */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE_DEFAULT                (_GPIO_RPURATD14_RATDDBUSTIMER4CCC0ROUTE_DEFAULT << 4)  /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE                        (0x1UL << 5)                                            /**< CCC1ROUTE Protection Bit                    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE_SHIFT                 5                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CCC1ROUTE*/
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE_MASK                  0x20UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER4CCC1ROUTE   */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE_DEFAULT                (_GPIO_RPURATD14_RATDDBUSTIMER4CCC1ROUTE_DEFAULT << 5)  /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE                        (0x1UL << 6)                                            /**< CCC2ROUTE Protection Bit                    */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE_SHIFT                 6                                                       /**< Shift value for GPIO_RATDDBUSTIMER4CCC2ROUTE*/
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE_MASK                  0x40UL                                                  /**< Bit mask for GPIO_RATDDBUSTIMER4CCC2ROUTE   */
#define _GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE_DEFAULT                (_GPIO_RPURATD14_RATDDBUSTIMER4CCC2ROUTE_DEFAULT << 6)  /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN                          (0x1UL << 8)                                            /**< ROUTEEN Protection Bit                      */
#define _GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN_SHIFT                   8                                                       /**< Shift value for GPIO_RATDDBUSUSART0ROUTEEN  */
#define _GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN_MASK                    0x100UL                                                 /**< Bit mask for GPIO_RATDDBUSUSART0ROUTEEN     */
#define _GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN_DEFAULT                  (_GPIO_RPURATD14_RATDDBUSUSART0ROUTEEN_DEFAULT << 8)    /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0CSROUTE                          (0x1UL << 9)                                            /**< CSROUTE Protection Bit                      */
#define _GPIO_RPURATD14_RATDDBUSUSART0CSROUTE_SHIFT                   9                                                       /**< Shift value for GPIO_RATDDBUSUSART0CSROUTE  */
#define _GPIO_RPURATD14_RATDDBUSUSART0CSROUTE_MASK                    0x200UL                                                 /**< Bit mask for GPIO_RATDDBUSUSART0CSROUTE     */
#define _GPIO_RPURATD14_RATDDBUSUSART0CSROUTE_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0CSROUTE_DEFAULT                  (_GPIO_RPURATD14_RATDDBUSUSART0CSROUTE_DEFAULT << 9)    /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE                         (0x1UL << 10)                                           /**< CTSROUTE Protection Bit                     */
#define _GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE_SHIFT                  10                                                      /**< Shift value for GPIO_RATDDBUSUSART0CTSROUTE */
#define _GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE_MASK                   0x400UL                                                 /**< Bit mask for GPIO_RATDDBUSUSART0CTSROUTE    */
#define _GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE_DEFAULT                 (_GPIO_RPURATD14_RATDDBUSUSART0CTSROUTE_DEFAULT << 10)  /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE                         (0x1UL << 11)                                           /**< RTSROUTE Protection Bit                     */
#define _GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE_SHIFT                  11                                                      /**< Shift value for GPIO_RATDDBUSUSART0RTSROUTE */
#define _GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE_MASK                   0x800UL                                                 /**< Bit mask for GPIO_RATDDBUSUSART0RTSROUTE    */
#define _GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE_DEFAULT                0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE_DEFAULT                 (_GPIO_RPURATD14_RATDDBUSUSART0RTSROUTE_DEFAULT << 11)  /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0RXROUTE                          (0x1UL << 12)                                           /**< RXROUTE Protection Bit                      */
#define _GPIO_RPURATD14_RATDDBUSUSART0RXROUTE_SHIFT                   12                                                      /**< Shift value for GPIO_RATDDBUSUSART0RXROUTE  */
#define _GPIO_RPURATD14_RATDDBUSUSART0RXROUTE_MASK                    0x1000UL                                                /**< Bit mask for GPIO_RATDDBUSUSART0RXROUTE     */
#define _GPIO_RPURATD14_RATDDBUSUSART0RXROUTE_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0RXROUTE_DEFAULT                  (_GPIO_RPURATD14_RATDDBUSUSART0RXROUTE_DEFAULT << 12)   /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE                        (0x1UL << 13)                                           /**< SCLKROUTE Protection Bit                    */
#define _GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE_SHIFT                 13                                                      /**< Shift value for GPIO_RATDDBUSUSART0SCLKROUTE*/
#define _GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE_MASK                  0x2000UL                                                /**< Bit mask for GPIO_RATDDBUSUSART0SCLKROUTE   */
#define _GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE_DEFAULT               0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE_DEFAULT                (_GPIO_RPURATD14_RATDDBUSUSART0SCLKROUTE_DEFAULT << 13) /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
#define GPIO_RPURATD14_RATDDBUSUSART0TXROUTE                          (0x1UL << 14)                                           /**< TXROUTE Protection Bit                      */
#define _GPIO_RPURATD14_RATDDBUSUSART0TXROUTE_SHIFT                   14                                                      /**< Shift value for GPIO_RATDDBUSUSART0TXROUTE  */
#define _GPIO_RPURATD14_RATDDBUSUSART0TXROUTE_MASK                    0x4000UL                                                /**< Bit mask for GPIO_RATDDBUSUSART0TXROUTE     */
#define _GPIO_RPURATD14_RATDDBUSUSART0TXROUTE_DEFAULT                 0x00000000UL                                            /**< Mode DEFAULT for GPIO_RPURATD14             */
#define GPIO_RPURATD14_RATDDBUSUSART0TXROUTE_DEFAULT                  (_GPIO_RPURATD14_RATDDBUSUSART0TXROUTE_DEFAULT << 14)   /**< Shifted mode DEFAULT for GPIO_RPURATD14     */
/** @} End of group Parts */

#endif /* MGM24_GPIO_H */
