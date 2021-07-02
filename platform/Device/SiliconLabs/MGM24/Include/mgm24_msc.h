/**************************************************************************//**
 * @file
 * @brief MGM24 MSC register and bit field definitions
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
#ifndef MGM24_MSC_H
#define MGM24_MSC_H
#define MSC_HAS_SET_CLEAR

/**************************************************************************//**
* @addtogroup Parts
* @{
******************************************************************************/
/**************************************************************************//**
 * @defgroup MGM24_MSC MSC
 * @{
 * @brief MGM24 MSC Register Declaration.
 *****************************************************************************/

/** MSC Register Declaration. */
typedef struct {
  __IM uint32_t  IPVERSION;                     /**< IP version ID                                      */
  __IOM uint32_t READCTRL;                      /**< Read Control Register                              */
  __IOM uint32_t RDATACTRL;                     /**< Read Data Control Register                         */
  __IOM uint32_t WRITECTRL;                     /**< Host Write Control Register                        */
  __IOM uint32_t WRITECMD;                      /**< Host Write Command Register                        */
  __IOM uint32_t ADDRB;                         /**< Host Page Erase/Write Address Buffer               */
  __IOM uint32_t WDATA;                         /**< Host Write Data Register                           */
  __IM uint32_t  STATUS;                        /**< Host Status Register                               */
  __IOM uint32_t IF;                            /**< Host Interrupt Flag Register                       */
  __IOM uint32_t IEN;                           /**< Host Interrupt Enable Register                     */
  uint32_t       RESERVED0[3U];                 /**< Reserved for future use                            */
  __IM uint32_t  USERDATASIZE;                  /**< user data regsion size                             */
  __IOM uint32_t CMD;                           /**< Command Register                                   */
  __IOM uint32_t LOCK;                          /**< Configuration Lock Register                        */
  __IOM uint32_t MISCLOCKWORD;                  /**< Mass erase and User data page lock word            */
  uint32_t       RESERVED1[3U];                 /**< Reserved for future use                            */
  __IOM uint32_t PWRCTRL;                       /**< Power control register                             */
  uint32_t       RESERVED2[11U];                /**< Reserved for future use                            */
  __IOM uint32_t SEWRITECTRL;                   /**< SE Write Control Register (SE)                     */
  __IOM uint32_t SEWRITECMD;                    /**< SE Write Command Register (SE)                     */
  __IOM uint32_t SEADDRB;                       /**< SE Page Erase/Write Address Buffer (SE)            */
  __IOM uint32_t SEWDATA;                       /**< SE Write Data Register (SE)                        */
  __IM uint32_t  SESTATUS;                      /**< SE Status Register (SE)                            */
  __IOM uint32_t SEIF;                          /**< SE Interrupt Flag Register (SE)                    */
  __IOM uint32_t SEIEN;                         /**< SE Interrupt Enable Register (SE)                  */
  uint32_t       RESERVED3[1U];                 /**< Reserved for future use                            */
  __IOM uint32_t STARTUP;                       /**< Startup Control (SE)                               */
  __IOM uint32_t SERDATACTRL;                   /**< SE Read Data Control Register                      */
  uint32_t       RESERVED4[6U];                 /**< Reserved for future use                            */
  __IOM uint32_t FLASHERASETIME;                /**< flash  erase timing counter (SE)                   */
  __IOM uint32_t FLASHPROGTIME;                 /**< flash programming timing counter (SE)              */
  __IOM uint32_t SELOCK;                        /**< SE Configuration Lock Register                     */
  uint32_t       RESERVED5[21U];                /**< Reserved for future use                            */
  __IOM uint32_t PAGELOCKWORD0;                 /**< Main space page 0-31 lock word                     */
  __IOM uint32_t PAGELOCKWORD1;                 /**< Main space page 32-63 lock word                    */
  __IOM uint32_t PAGELOCKWORD2;                 /**< Main space page 64-95 lock word                    */
  __IOM uint32_t PAGELOCKWORD3;                 /**< Main space page 96-127 lock word                   */
  __IOM uint32_t PAGELOCKWORD4;                 /**< Main space page 128-159 lock word                  */
  __IOM uint32_t PAGELOCKWORD5;                 /**< Main space page 160-191 lock word                  */
  uint32_t       RESERVED6[2U];                 /**< Reserved for future use                            */
  __IOM uint32_t REPADDR0;                      /**< Flash INSTx Repair Address 0 (SE)                  */
  __IOM uint32_t REPADDR1;                      /**< Flash INSTx Repair Address 1 (SE)                  */
  uint32_t       RESERVED7[2U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED8[4U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED9[4U];                 /**< Reserved for future use                            */
  uint32_t       RESERVED10[12U];               /**< Reserved for future use                            */
  uint32_t       RESERVED11[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED12[8U];                /**< Reserved for future use                            */
  __IOM uint32_t RPURATD0;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD1;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD2;                      /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD3;                      /**< Root Access Type Descriptor Register               */
  uint32_t       RESERVED13[907U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_SET;                 /**< IP version ID                                      */
  __IOM uint32_t READCTRL_SET;                  /**< Read Control Register                              */
  __IOM uint32_t RDATACTRL_SET;                 /**< Read Data Control Register                         */
  __IOM uint32_t WRITECTRL_SET;                 /**< Host Write Control Register                        */
  __IOM uint32_t WRITECMD_SET;                  /**< Host Write Command Register                        */
  __IOM uint32_t ADDRB_SET;                     /**< Host Page Erase/Write Address Buffer               */
  __IOM uint32_t WDATA_SET;                     /**< Host Write Data Register                           */
  __IM uint32_t  STATUS_SET;                    /**< Host Status Register                               */
  __IOM uint32_t IF_SET;                        /**< Host Interrupt Flag Register                       */
  __IOM uint32_t IEN_SET;                       /**< Host Interrupt Enable Register                     */
  uint32_t       RESERVED14[3U];                /**< Reserved for future use                            */
  __IM uint32_t  USERDATASIZE_SET;              /**< user data regsion size                             */
  __IOM uint32_t CMD_SET;                       /**< Command Register                                   */
  __IOM uint32_t LOCK_SET;                      /**< Configuration Lock Register                        */
  __IOM uint32_t MISCLOCKWORD_SET;              /**< Mass erase and User data page lock word            */
  uint32_t       RESERVED15[3U];                /**< Reserved for future use                            */
  __IOM uint32_t PWRCTRL_SET;                   /**< Power control register                             */
  uint32_t       RESERVED16[11U];               /**< Reserved for future use                            */
  __IOM uint32_t SEWRITECTRL_SET;               /**< SE Write Control Register (SE)                     */
  __IOM uint32_t SEWRITECMD_SET;                /**< SE Write Command Register (SE)                     */
  __IOM uint32_t SEADDRB_SET;                   /**< SE Page Erase/Write Address Buffer (SE)            */
  __IOM uint32_t SEWDATA_SET;                   /**< SE Write Data Register (SE)                        */
  __IM uint32_t  SESTATUS_SET;                  /**< SE Status Register (SE)                            */
  __IOM uint32_t SEIF_SET;                      /**< SE Interrupt Flag Register (SE)                    */
  __IOM uint32_t SEIEN_SET;                     /**< SE Interrupt Enable Register (SE)                  */
  uint32_t       RESERVED17[1U];                /**< Reserved for future use                            */
  __IOM uint32_t STARTUP_SET;                   /**< Startup Control (SE)                               */
  __IOM uint32_t SERDATACTRL_SET;               /**< SE Read Data Control Register                      */
  uint32_t       RESERVED18[6U];                /**< Reserved for future use                            */
  __IOM uint32_t FLASHERASETIME_SET;            /**< flash  erase timing counter (SE)                   */
  __IOM uint32_t FLASHPROGTIME_SET;             /**< flash programming timing counter (SE)              */
  __IOM uint32_t SELOCK_SET;                    /**< SE Configuration Lock Register                     */
  uint32_t       RESERVED19[21U];               /**< Reserved for future use                            */
  __IOM uint32_t PAGELOCKWORD0_SET;             /**< Main space page 0-31 lock word                     */
  __IOM uint32_t PAGELOCKWORD1_SET;             /**< Main space page 32-63 lock word                    */
  __IOM uint32_t PAGELOCKWORD2_SET;             /**< Main space page 64-95 lock word                    */
  __IOM uint32_t PAGELOCKWORD3_SET;             /**< Main space page 96-127 lock word                   */
  __IOM uint32_t PAGELOCKWORD4_SET;             /**< Main space page 128-159 lock word                  */
  __IOM uint32_t PAGELOCKWORD5_SET;             /**< Main space page 160-191 lock word                  */
  uint32_t       RESERVED20[2U];                /**< Reserved for future use                            */
  __IOM uint32_t REPADDR0_SET;                  /**< Flash INSTx Repair Address 0 (SE)                  */
  __IOM uint32_t REPADDR1_SET;                  /**< Flash INSTx Repair Address 1 (SE)                  */
  uint32_t       RESERVED21[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED22[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED23[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED24[12U];               /**< Reserved for future use                            */
  uint32_t       RESERVED25[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED26[8U];                /**< Reserved for future use                            */
  __IOM uint32_t RPURATD0_SET;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD1_SET;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD2_SET;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD3_SET;                  /**< Root Access Type Descriptor Register               */
  uint32_t       RESERVED27[907U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_CLR;                 /**< IP version ID                                      */
  __IOM uint32_t READCTRL_CLR;                  /**< Read Control Register                              */
  __IOM uint32_t RDATACTRL_CLR;                 /**< Read Data Control Register                         */
  __IOM uint32_t WRITECTRL_CLR;                 /**< Host Write Control Register                        */
  __IOM uint32_t WRITECMD_CLR;                  /**< Host Write Command Register                        */
  __IOM uint32_t ADDRB_CLR;                     /**< Host Page Erase/Write Address Buffer               */
  __IOM uint32_t WDATA_CLR;                     /**< Host Write Data Register                           */
  __IM uint32_t  STATUS_CLR;                    /**< Host Status Register                               */
  __IOM uint32_t IF_CLR;                        /**< Host Interrupt Flag Register                       */
  __IOM uint32_t IEN_CLR;                       /**< Host Interrupt Enable Register                     */
  uint32_t       RESERVED28[3U];                /**< Reserved for future use                            */
  __IM uint32_t  USERDATASIZE_CLR;              /**< user data regsion size                             */
  __IOM uint32_t CMD_CLR;                       /**< Command Register                                   */
  __IOM uint32_t LOCK_CLR;                      /**< Configuration Lock Register                        */
  __IOM uint32_t MISCLOCKWORD_CLR;              /**< Mass erase and User data page lock word            */
  uint32_t       RESERVED29[3U];                /**< Reserved for future use                            */
  __IOM uint32_t PWRCTRL_CLR;                   /**< Power control register                             */
  uint32_t       RESERVED30[11U];               /**< Reserved for future use                            */
  __IOM uint32_t SEWRITECTRL_CLR;               /**< SE Write Control Register (SE)                     */
  __IOM uint32_t SEWRITECMD_CLR;                /**< SE Write Command Register (SE)                     */
  __IOM uint32_t SEADDRB_CLR;                   /**< SE Page Erase/Write Address Buffer (SE)            */
  __IOM uint32_t SEWDATA_CLR;                   /**< SE Write Data Register (SE)                        */
  __IM uint32_t  SESTATUS_CLR;                  /**< SE Status Register (SE)                            */
  __IOM uint32_t SEIF_CLR;                      /**< SE Interrupt Flag Register (SE)                    */
  __IOM uint32_t SEIEN_CLR;                     /**< SE Interrupt Enable Register (SE)                  */
  uint32_t       RESERVED31[1U];                /**< Reserved for future use                            */
  __IOM uint32_t STARTUP_CLR;                   /**< Startup Control (SE)                               */
  __IOM uint32_t SERDATACTRL_CLR;               /**< SE Read Data Control Register                      */
  uint32_t       RESERVED32[6U];                /**< Reserved for future use                            */
  __IOM uint32_t FLASHERASETIME_CLR;            /**< flash  erase timing counter (SE)                   */
  __IOM uint32_t FLASHPROGTIME_CLR;             /**< flash programming timing counter (SE)              */
  __IOM uint32_t SELOCK_CLR;                    /**< SE Configuration Lock Register                     */
  uint32_t       RESERVED33[21U];               /**< Reserved for future use                            */
  __IOM uint32_t PAGELOCKWORD0_CLR;             /**< Main space page 0-31 lock word                     */
  __IOM uint32_t PAGELOCKWORD1_CLR;             /**< Main space page 32-63 lock word                    */
  __IOM uint32_t PAGELOCKWORD2_CLR;             /**< Main space page 64-95 lock word                    */
  __IOM uint32_t PAGELOCKWORD3_CLR;             /**< Main space page 96-127 lock word                   */
  __IOM uint32_t PAGELOCKWORD4_CLR;             /**< Main space page 128-159 lock word                  */
  __IOM uint32_t PAGELOCKWORD5_CLR;             /**< Main space page 160-191 lock word                  */
  uint32_t       RESERVED34[2U];                /**< Reserved for future use                            */
  __IOM uint32_t REPADDR0_CLR;                  /**< Flash INSTx Repair Address 0 (SE)                  */
  __IOM uint32_t REPADDR1_CLR;                  /**< Flash INSTx Repair Address 1 (SE)                  */
  uint32_t       RESERVED35[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED36[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED37[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED38[12U];               /**< Reserved for future use                            */
  uint32_t       RESERVED39[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED40[8U];                /**< Reserved for future use                            */
  __IOM uint32_t RPURATD0_CLR;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD1_CLR;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD2_CLR;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD3_CLR;                  /**< Root Access Type Descriptor Register               */
  uint32_t       RESERVED41[907U];              /**< Reserved for future use                            */
  __IM uint32_t  IPVERSION_TGL;                 /**< IP version ID                                      */
  __IOM uint32_t READCTRL_TGL;                  /**< Read Control Register                              */
  __IOM uint32_t RDATACTRL_TGL;                 /**< Read Data Control Register                         */
  __IOM uint32_t WRITECTRL_TGL;                 /**< Host Write Control Register                        */
  __IOM uint32_t WRITECMD_TGL;                  /**< Host Write Command Register                        */
  __IOM uint32_t ADDRB_TGL;                     /**< Host Page Erase/Write Address Buffer               */
  __IOM uint32_t WDATA_TGL;                     /**< Host Write Data Register                           */
  __IM uint32_t  STATUS_TGL;                    /**< Host Status Register                               */
  __IOM uint32_t IF_TGL;                        /**< Host Interrupt Flag Register                       */
  __IOM uint32_t IEN_TGL;                       /**< Host Interrupt Enable Register                     */
  uint32_t       RESERVED42[3U];                /**< Reserved for future use                            */
  __IM uint32_t  USERDATASIZE_TGL;              /**< user data regsion size                             */
  __IOM uint32_t CMD_TGL;                       /**< Command Register                                   */
  __IOM uint32_t LOCK_TGL;                      /**< Configuration Lock Register                        */
  __IOM uint32_t MISCLOCKWORD_TGL;              /**< Mass erase and User data page lock word            */
  uint32_t       RESERVED43[3U];                /**< Reserved for future use                            */
  __IOM uint32_t PWRCTRL_TGL;                   /**< Power control register                             */
  uint32_t       RESERVED44[11U];               /**< Reserved for future use                            */
  __IOM uint32_t SEWRITECTRL_TGL;               /**< SE Write Control Register (SE)                     */
  __IOM uint32_t SEWRITECMD_TGL;                /**< SE Write Command Register (SE)                     */
  __IOM uint32_t SEADDRB_TGL;                   /**< SE Page Erase/Write Address Buffer (SE)            */
  __IOM uint32_t SEWDATA_TGL;                   /**< SE Write Data Register (SE)                        */
  __IM uint32_t  SESTATUS_TGL;                  /**< SE Status Register (SE)                            */
  __IOM uint32_t SEIF_TGL;                      /**< SE Interrupt Flag Register (SE)                    */
  __IOM uint32_t SEIEN_TGL;                     /**< SE Interrupt Enable Register (SE)                  */
  uint32_t       RESERVED45[1U];                /**< Reserved for future use                            */
  __IOM uint32_t STARTUP_TGL;                   /**< Startup Control (SE)                               */
  __IOM uint32_t SERDATACTRL_TGL;               /**< SE Read Data Control Register                      */
  uint32_t       RESERVED46[6U];                /**< Reserved for future use                            */
  __IOM uint32_t FLASHERASETIME_TGL;            /**< flash  erase timing counter (SE)                   */
  __IOM uint32_t FLASHPROGTIME_TGL;             /**< flash programming timing counter (SE)              */
  __IOM uint32_t SELOCK_TGL;                    /**< SE Configuration Lock Register                     */
  uint32_t       RESERVED47[21U];               /**< Reserved for future use                            */
  __IOM uint32_t PAGELOCKWORD0_TGL;             /**< Main space page 0-31 lock word                     */
  __IOM uint32_t PAGELOCKWORD1_TGL;             /**< Main space page 32-63 lock word                    */
  __IOM uint32_t PAGELOCKWORD2_TGL;             /**< Main space page 64-95 lock word                    */
  __IOM uint32_t PAGELOCKWORD3_TGL;             /**< Main space page 96-127 lock word                   */
  __IOM uint32_t PAGELOCKWORD4_TGL;             /**< Main space page 128-159 lock word                  */
  __IOM uint32_t PAGELOCKWORD5_TGL;             /**< Main space page 160-191 lock word                  */
  uint32_t       RESERVED48[2U];                /**< Reserved for future use                            */
  __IOM uint32_t REPADDR0_TGL;                  /**< Flash INSTx Repair Address 0 (SE)                  */
  __IOM uint32_t REPADDR1_TGL;                  /**< Flash INSTx Repair Address 1 (SE)                  */
  uint32_t       RESERVED49[2U];                /**< Reserved for future use                            */
  uint32_t       RESERVED50[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED51[4U];                /**< Reserved for future use                            */
  uint32_t       RESERVED52[12U];               /**< Reserved for future use                            */
  uint32_t       RESERVED53[1U];                /**< Reserved for future use                            */
  uint32_t       RESERVED54[8U];                /**< Reserved for future use                            */
  __IOM uint32_t RPURATD0_TGL;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD1_TGL;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD2_TGL;                  /**< Root Access Type Descriptor Register               */
  __IOM uint32_t RPURATD3_TGL;                  /**< Root Access Type Descriptor Register               */
} MSC_TypeDef;
/** @} End of group MGM24_MSC */

/**************************************************************************//**
 * @addtogroup MGM24_MSC
 * @{
 * @defgroup MGM24_MSC_BitFields MSC Bit Fields
 * @{
 *****************************************************************************/

/* Bit fields for MSC IPVERSION */
#define _MSC_IPVERSION_RESETVALUE                      0x00000003UL                            /**< Default value for MSC_IPVERSION             */
#define _MSC_IPVERSION_MASK                            0xFFFFFFFFUL                            /**< Mask for MSC_IPVERSION                      */
#define _MSC_IPVERSION_IPVERSION_SHIFT                 0                                       /**< Shift value for MSC_IPVERSION               */
#define _MSC_IPVERSION_IPVERSION_MASK                  0xFFFFFFFFUL                            /**< Bit mask for MSC_IPVERSION                  */
#define _MSC_IPVERSION_IPVERSION_DEFAULT               0x00000003UL                            /**< Mode DEFAULT for MSC_IPVERSION              */
#define MSC_IPVERSION_IPVERSION_DEFAULT                (_MSC_IPVERSION_IPVERSION_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_IPVERSION      */

/* Bit fields for MSC READCTRL */
#define _MSC_READCTRL_RESETVALUE                       0x00200000UL                       /**< Default value for MSC_READCTRL              */
#define _MSC_READCTRL_MASK                             0x00300000UL                       /**< Mask for MSC_READCTRL                       */
#define _MSC_READCTRL_MODE_SHIFT                       20                                 /**< Shift value for MSC_MODE                    */
#define _MSC_READCTRL_MODE_MASK                        0x300000UL                         /**< Bit mask for MSC_MODE                       */
#define _MSC_READCTRL_MODE_DEFAULT                     0x00000002UL                       /**< Mode DEFAULT for MSC_READCTRL               */
#define _MSC_READCTRL_MODE_WS0                         0x00000000UL                       /**< Mode WS0 for MSC_READCTRL                   */
#define _MSC_READCTRL_MODE_WS1                         0x00000001UL                       /**< Mode WS1 for MSC_READCTRL                   */
#define _MSC_READCTRL_MODE_WS2                         0x00000002UL                       /**< Mode WS2 for MSC_READCTRL                   */
#define _MSC_READCTRL_MODE_WS3                         0x00000003UL                       /**< Mode WS3 for MSC_READCTRL                   */
#define MSC_READCTRL_MODE_DEFAULT                      (_MSC_READCTRL_MODE_DEFAULT << 20) /**< Shifted mode DEFAULT for MSC_READCTRL       */
#define MSC_READCTRL_MODE_WS0                          (_MSC_READCTRL_MODE_WS0 << 20)     /**< Shifted mode WS0 for MSC_READCTRL           */
#define MSC_READCTRL_MODE_WS1                          (_MSC_READCTRL_MODE_WS1 << 20)     /**< Shifted mode WS1 for MSC_READCTRL           */
#define MSC_READCTRL_MODE_WS2                          (_MSC_READCTRL_MODE_WS2 << 20)     /**< Shifted mode WS2 for MSC_READCTRL           */
#define MSC_READCTRL_MODE_WS3                          (_MSC_READCTRL_MODE_WS3 << 20)     /**< Shifted mode WS3 for MSC_READCTRL           */

/* Bit fields for MSC RDATACTRL */
#define _MSC_RDATACTRL_RESETVALUE                      0x00001000UL                             /**< Default value for MSC_RDATACTRL             */
#define _MSC_RDATACTRL_MASK                            0x00001002UL                             /**< Mask for MSC_RDATACTRL                      */
#define MSC_RDATACTRL_AFDIS                            (0x1UL << 1)                             /**< Automatic Invalidate Disable                */
#define _MSC_RDATACTRL_AFDIS_SHIFT                     1                                        /**< Shift value for MSC_AFDIS                   */
#define _MSC_RDATACTRL_AFDIS_MASK                      0x2UL                                    /**< Bit mask for MSC_AFDIS                      */
#define _MSC_RDATACTRL_AFDIS_DEFAULT                   0x00000000UL                             /**< Mode DEFAULT for MSC_RDATACTRL              */
#define MSC_RDATACTRL_AFDIS_DEFAULT                    (_MSC_RDATACTRL_AFDIS_DEFAULT << 1)      /**< Shifted mode DEFAULT for MSC_RDATACTRL      */
#define MSC_RDATACTRL_DOUTBUFEN                        (0x1UL << 12)                            /**< Flash dout pipeline buffer enable           */
#define _MSC_RDATACTRL_DOUTBUFEN_SHIFT                 12                                       /**< Shift value for MSC_DOUTBUFEN               */
#define _MSC_RDATACTRL_DOUTBUFEN_MASK                  0x1000UL                                 /**< Bit mask for MSC_DOUTBUFEN                  */
#define _MSC_RDATACTRL_DOUTBUFEN_DEFAULT               0x00000001UL                             /**< Mode DEFAULT for MSC_RDATACTRL              */
#define MSC_RDATACTRL_DOUTBUFEN_DEFAULT                (_MSC_RDATACTRL_DOUTBUFEN_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_RDATACTRL      */

/* Bit fields for MSC WRITECTRL */
#define _MSC_WRITECTRL_RESETVALUE                      0x00000000UL                                /**< Default value for MSC_WRITECTRL             */
#define _MSC_WRITECTRL_MASK                            0x03FF000BUL                                /**< Mask for MSC_WRITECTRL                      */
#define MSC_WRITECTRL_WREN                             (0x1UL << 0)                                /**< Enable Write/Erase Controller               */
#define _MSC_WRITECTRL_WREN_SHIFT                      0                                           /**< Shift value for MSC_WREN                    */
#define _MSC_WRITECTRL_WREN_MASK                       0x1UL                                       /**< Bit mask for MSC_WREN                       */
#define _MSC_WRITECTRL_WREN_DEFAULT                    0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL              */
#define MSC_WRITECTRL_WREN_DEFAULT                     (_MSC_WRITECTRL_WREN_DEFAULT << 0)          /**< Shifted mode DEFAULT for MSC_WRITECTRL      */
#define MSC_WRITECTRL_IRQERASEABORT                    (0x1UL << 1)                                /**< Abort Page Erase on Interrupt               */
#define _MSC_WRITECTRL_IRQERASEABORT_SHIFT             1                                           /**< Shift value for MSC_IRQERASEABORT           */
#define _MSC_WRITECTRL_IRQERASEABORT_MASK              0x2UL                                       /**< Bit mask for MSC_IRQERASEABORT              */
#define _MSC_WRITECTRL_IRQERASEABORT_DEFAULT           0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL              */
#define MSC_WRITECTRL_IRQERASEABORT_DEFAULT            (_MSC_WRITECTRL_IRQERASEABORT_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_WRITECTRL      */
#define MSC_WRITECTRL_LPWRITE                          (0x1UL << 3)                                /**< Low-Power Erase                             */
#define _MSC_WRITECTRL_LPWRITE_SHIFT                   3                                           /**< Shift value for MSC_LPWRITE                 */
#define _MSC_WRITECTRL_LPWRITE_MASK                    0x8UL                                       /**< Bit mask for MSC_LPWRITE                    */
#define _MSC_WRITECTRL_LPWRITE_DEFAULT                 0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL              */
#define MSC_WRITECTRL_LPWRITE_DEFAULT                  (_MSC_WRITECTRL_LPWRITE_DEFAULT << 3)       /**< Shifted mode DEFAULT for MSC_WRITECTRL      */
#define _MSC_WRITECTRL_RANGECOUNT_SHIFT                16                                          /**< Shift value for MSC_RANGECOUNT              */
#define _MSC_WRITECTRL_RANGECOUNT_MASK                 0x3FF0000UL                                 /**< Bit mask for MSC_RANGECOUNT                 */
#define _MSC_WRITECTRL_RANGECOUNT_DEFAULT              0x00000000UL                                /**< Mode DEFAULT for MSC_WRITECTRL              */
#define MSC_WRITECTRL_RANGECOUNT_DEFAULT               (_MSC_WRITECTRL_RANGECOUNT_DEFAULT << 16)   /**< Shifted mode DEFAULT for MSC_WRITECTRL      */

/* Bit fields for MSC WRITECMD */
#define _MSC_WRITECMD_RESETVALUE                       0x00000000UL                             /**< Default value for MSC_WRITECMD              */
#define _MSC_WRITECMD_MASK                             0x00001136UL                             /**< Mask for MSC_WRITECMD                       */
#define MSC_WRITECMD_ERASEPAGE                         (0x1UL << 1)                             /**< Erase Page                                  */
#define _MSC_WRITECMD_ERASEPAGE_SHIFT                  1                                        /**< Shift value for MSC_ERASEPAGE               */
#define _MSC_WRITECMD_ERASEPAGE_MASK                   0x2UL                                    /**< Bit mask for MSC_ERASEPAGE                  */
#define _MSC_WRITECMD_ERASEPAGE_DEFAULT                0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_ERASEPAGE_DEFAULT                 (_MSC_WRITECMD_ERASEPAGE_DEFAULT << 1)   /**< Shifted mode DEFAULT for MSC_WRITECMD       */
#define MSC_WRITECMD_WRITEEND                          (0x1UL << 2)                             /**< End Write Mode                              */
#define _MSC_WRITECMD_WRITEEND_SHIFT                   2                                        /**< Shift value for MSC_WRITEEND                */
#define _MSC_WRITECMD_WRITEEND_MASK                    0x4UL                                    /**< Bit mask for MSC_WRITEEND                   */
#define _MSC_WRITECMD_WRITEEND_DEFAULT                 0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_WRITEEND_DEFAULT                  (_MSC_WRITECMD_WRITEEND_DEFAULT << 2)    /**< Shifted mode DEFAULT for MSC_WRITECMD       */
#define MSC_WRITECMD_ERASERANGE                        (0x1UL << 4)                             /**< Erase range of pages                        */
#define _MSC_WRITECMD_ERASERANGE_SHIFT                 4                                        /**< Shift value for MSC_ERASERANGE              */
#define _MSC_WRITECMD_ERASERANGE_MASK                  0x10UL                                   /**< Bit mask for MSC_ERASERANGE                 */
#define _MSC_WRITECMD_ERASERANGE_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_ERASERANGE_DEFAULT                (_MSC_WRITECMD_ERASERANGE_DEFAULT << 4)  /**< Shifted mode DEFAULT for MSC_WRITECMD       */
#define MSC_WRITECMD_ERASEABORT                        (0x1UL << 5)                             /**< Abort erase sequence                        */
#define _MSC_WRITECMD_ERASEABORT_SHIFT                 5                                        /**< Shift value for MSC_ERASEABORT              */
#define _MSC_WRITECMD_ERASEABORT_MASK                  0x20UL                                   /**< Bit mask for MSC_ERASEABORT                 */
#define _MSC_WRITECMD_ERASEABORT_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_ERASEABORT_DEFAULT                (_MSC_WRITECMD_ERASEABORT_DEFAULT << 5)  /**< Shifted mode DEFAULT for MSC_WRITECMD       */
#define MSC_WRITECMD_ERASEMAIN0                        (0x1UL << 8)                             /**< Mass erase region 0                         */
#define _MSC_WRITECMD_ERASEMAIN0_SHIFT                 8                                        /**< Shift value for MSC_ERASEMAIN0              */
#define _MSC_WRITECMD_ERASEMAIN0_MASK                  0x100UL                                  /**< Bit mask for MSC_ERASEMAIN0                 */
#define _MSC_WRITECMD_ERASEMAIN0_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_ERASEMAIN0_DEFAULT                (_MSC_WRITECMD_ERASEMAIN0_DEFAULT << 8)  /**< Shifted mode DEFAULT for MSC_WRITECMD       */
#define MSC_WRITECMD_CLEARWDATA                        (0x1UL << 12)                            /**< Clear WDATA state                           */
#define _MSC_WRITECMD_CLEARWDATA_SHIFT                 12                                       /**< Shift value for MSC_CLEARWDATA              */
#define _MSC_WRITECMD_CLEARWDATA_MASK                  0x1000UL                                 /**< Bit mask for MSC_CLEARWDATA                 */
#define _MSC_WRITECMD_CLEARWDATA_DEFAULT               0x00000000UL                             /**< Mode DEFAULT for MSC_WRITECMD               */
#define MSC_WRITECMD_CLEARWDATA_DEFAULT                (_MSC_WRITECMD_CLEARWDATA_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_WRITECMD       */

/* Bit fields for MSC ADDRB */
#define _MSC_ADDRB_RESETVALUE                          0x00000000UL                     /**< Default value for MSC_ADDRB                 */
#define _MSC_ADDRB_MASK                                0xFFFFFFFFUL                     /**< Mask for MSC_ADDRB                          */
#define _MSC_ADDRB_ADDRB_SHIFT                         0                                /**< Shift value for MSC_ADDRB                   */
#define _MSC_ADDRB_ADDRB_MASK                          0xFFFFFFFFUL                     /**< Bit mask for MSC_ADDRB                      */
#define _MSC_ADDRB_ADDRB_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_ADDRB                  */
#define MSC_ADDRB_ADDRB_DEFAULT                        (_MSC_ADDRB_ADDRB_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_ADDRB          */

/* Bit fields for MSC WDATA */
#define _MSC_WDATA_RESETVALUE                          0x00000000UL                     /**< Default value for MSC_WDATA                 */
#define _MSC_WDATA_MASK                                0xFFFFFFFFUL                     /**< Mask for MSC_WDATA                          */
#define _MSC_WDATA_DATAW_SHIFT                         0                                /**< Shift value for MSC_DATAW                   */
#define _MSC_WDATA_DATAW_MASK                          0xFFFFFFFFUL                     /**< Bit mask for MSC_DATAW                      */
#define _MSC_WDATA_DATAW_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_WDATA                  */
#define MSC_WDATA_DATAW_DEFAULT                        (_MSC_WDATA_DATAW_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_WDATA          */

/* Bit fields for MSC STATUS */
#define _MSC_STATUS_RESETVALUE                         0x08000008UL                                   /**< Default value for MSC_STATUS                */
#define _MSC_STATUS_MASK                               0xF90100FFUL                                   /**< Mask for MSC_STATUS                         */
#define MSC_STATUS_BUSY                                (0x1UL << 0)                                   /**< Erase/Write Busy                            */
#define _MSC_STATUS_BUSY_SHIFT                         0                                              /**< Shift value for MSC_BUSY                    */
#define _MSC_STATUS_BUSY_MASK                          0x1UL                                          /**< Bit mask for MSC_BUSY                       */
#define _MSC_STATUS_BUSY_DEFAULT                       0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_BUSY_DEFAULT                        (_MSC_STATUS_BUSY_DEFAULT << 0)                /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_LOCKED                              (0x1UL << 1)                                   /**< Access Locked                               */
#define _MSC_STATUS_LOCKED_SHIFT                       1                                              /**< Shift value for MSC_LOCKED                  */
#define _MSC_STATUS_LOCKED_MASK                        0x2UL                                          /**< Bit mask for MSC_LOCKED                     */
#define _MSC_STATUS_LOCKED_DEFAULT                     0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_LOCKED_DEFAULT                      (_MSC_STATUS_LOCKED_DEFAULT << 1)              /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_INVADDR                             (0x1UL << 2)                                   /**< Invalid Write Address or Erase Page         */
#define _MSC_STATUS_INVADDR_SHIFT                      2                                              /**< Shift value for MSC_INVADDR                 */
#define _MSC_STATUS_INVADDR_MASK                       0x4UL                                          /**< Bit mask for MSC_INVADDR                    */
#define _MSC_STATUS_INVADDR_DEFAULT                    0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_INVADDR_DEFAULT                     (_MSC_STATUS_INVADDR_DEFAULT << 2)             /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_WDATAREADY                          (0x1UL << 3)                                   /**< WDATA Write Ready                           */
#define _MSC_STATUS_WDATAREADY_SHIFT                   3                                              /**< Shift value for MSC_WDATAREADY              */
#define _MSC_STATUS_WDATAREADY_MASK                    0x8UL                                          /**< Bit mask for MSC_WDATAREADY                 */
#define _MSC_STATUS_WDATAREADY_DEFAULT                 0x00000001UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_WDATAREADY_DEFAULT                  (_MSC_STATUS_WDATAREADY_DEFAULT << 3)          /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_ERASEABORTED                        (0x1UL << 4)                                   /**< The Current Flash Erase Operation Aborte    */
#define _MSC_STATUS_ERASEABORTED_SHIFT                 4                                              /**< Shift value for MSC_ERASEABORTED            */
#define _MSC_STATUS_ERASEABORTED_MASK                  0x10UL                                         /**< Bit mask for MSC_ERASEABORTED               */
#define _MSC_STATUS_ERASEABORTED_DEFAULT               0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_ERASEABORTED_DEFAULT                (_MSC_STATUS_ERASEABORTED_DEFAULT << 4)        /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_PENDING                             (0x1UL << 5)                                   /**< Write command is in queue                   */
#define _MSC_STATUS_PENDING_SHIFT                      5                                              /**< Shift value for MSC_PENDING                 */
#define _MSC_STATUS_PENDING_MASK                       0x20UL                                         /**< Bit mask for MSC_PENDING                    */
#define _MSC_STATUS_PENDING_DEFAULT                    0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_PENDING_DEFAULT                     (_MSC_STATUS_PENDING_DEFAULT << 5)             /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_TIMEOUT                             (0x1UL << 6)                                   /**< Write command timeout flag                  */
#define _MSC_STATUS_TIMEOUT_SHIFT                      6                                              /**< Shift value for MSC_TIMEOUT                 */
#define _MSC_STATUS_TIMEOUT_MASK                       0x40UL                                         /**< Bit mask for MSC_TIMEOUT                    */
#define _MSC_STATUS_TIMEOUT_DEFAULT                    0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_TIMEOUT_DEFAULT                     (_MSC_STATUS_TIMEOUT_DEFAULT << 6)             /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_RANGEPARTIAL                        (0x1UL << 7)                                   /**< EraseRange with skipped locked pages        */
#define _MSC_STATUS_RANGEPARTIAL_SHIFT                 7                                              /**< Shift value for MSC_RANGEPARTIAL            */
#define _MSC_STATUS_RANGEPARTIAL_MASK                  0x80UL                                         /**< Bit mask for MSC_RANGEPARTIAL               */
#define _MSC_STATUS_RANGEPARTIAL_DEFAULT               0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_RANGEPARTIAL_DEFAULT                (_MSC_STATUS_RANGEPARTIAL_DEFAULT << 7)        /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_REGLOCK                             (0x1UL << 16)                                  /**< Register Lock Status                        */
#define _MSC_STATUS_REGLOCK_SHIFT                      16                                             /**< Shift value for MSC_REGLOCK                 */
#define _MSC_STATUS_REGLOCK_MASK                       0x10000UL                                      /**< Bit mask for MSC_REGLOCK                    */
#define _MSC_STATUS_REGLOCK_DEFAULT                    0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define _MSC_STATUS_REGLOCK_UNLOCKED                   0x00000000UL                                   /**< Mode UNLOCKED for MSC_STATUS                */
#define _MSC_STATUS_REGLOCK_LOCKED                     0x00000001UL                                   /**< Mode LOCKED for MSC_STATUS                  */
#define MSC_STATUS_REGLOCK_DEFAULT                     (_MSC_STATUS_REGLOCK_DEFAULT << 16)            /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_REGLOCK_UNLOCKED                    (_MSC_STATUS_REGLOCK_UNLOCKED << 16)           /**< Shifted mode UNLOCKED for MSC_STATUS        */
#define MSC_STATUS_REGLOCK_LOCKED                      (_MSC_STATUS_REGLOCK_LOCKED << 16)             /**< Shifted mode LOCKED for MSC_STATUS          */
#define MSC_STATUS_PWRON                               (0x1UL << 24)                                  /**< Flash power on status                       */
#define _MSC_STATUS_PWRON_SHIFT                        24                                             /**< Shift value for MSC_PWRON                   */
#define _MSC_STATUS_PWRON_MASK                         0x1000000UL                                    /**< Bit mask for MSC_PWRON                      */
#define _MSC_STATUS_PWRON_DEFAULT                      0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_PWRON_DEFAULT                       (_MSC_STATUS_PWRON_DEFAULT << 24)              /**< Shifted mode DEFAULT for MSC_STATUS         */
#define MSC_STATUS_WREADY                              (0x1UL << 27)                                  /**< Flash Write Ready                           */
#define _MSC_STATUS_WREADY_SHIFT                       27                                             /**< Shift value for MSC_WREADY                  */
#define _MSC_STATUS_WREADY_MASK                        0x8000000UL                                    /**< Bit mask for MSC_WREADY                     */
#define _MSC_STATUS_WREADY_DEFAULT                     0x00000001UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_WREADY_DEFAULT                      (_MSC_STATUS_WREADY_DEFAULT << 27)             /**< Shifted mode DEFAULT for MSC_STATUS         */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_SHIFT           28                                             /**< Shift value for MSC_PWRUPCKBDFAILCOUNT      */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_MASK            0xF0000000UL                                   /**< Bit mask for MSC_PWRUPCKBDFAILCOUNT         */
#define _MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT         0x00000000UL                                   /**< Mode DEFAULT for MSC_STATUS                 */
#define MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT          (_MSC_STATUS_PWRUPCKBDFAILCOUNT_DEFAULT << 28) /**< Shifted mode DEFAULT for MSC_STATUS         */

/* Bit fields for MSC IF */
#define _MSC_IF_RESETVALUE                             0x00000000UL                     /**< Default value for MSC_IF                    */
#define _MSC_IF_MASK                                   0x00000307UL                     /**< Mask for MSC_IF                             */
#define MSC_IF_ERASE                                   (0x1UL << 0)                     /**< Host Erase Done Interrupt Read Flag         */
#define _MSC_IF_ERASE_SHIFT                            0                                /**< Shift value for MSC_ERASE                   */
#define _MSC_IF_ERASE_MASK                             0x1UL                            /**< Bit mask for MSC_ERASE                      */
#define _MSC_IF_ERASE_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for MSC_IF                     */
#define MSC_IF_ERASE_DEFAULT                           (_MSC_IF_ERASE_DEFAULT << 0)     /**< Shifted mode DEFAULT for MSC_IF             */
#define MSC_IF_WRITE                                   (0x1UL << 1)                     /**< Host Write Done Interrupt Read Flag         */
#define _MSC_IF_WRITE_SHIFT                            1                                /**< Shift value for MSC_WRITE                   */
#define _MSC_IF_WRITE_MASK                             0x2UL                            /**< Bit mask for MSC_WRITE                      */
#define _MSC_IF_WRITE_DEFAULT                          0x00000000UL                     /**< Mode DEFAULT for MSC_IF                     */
#define MSC_IF_WRITE_DEFAULT                           (_MSC_IF_WRITE_DEFAULT << 1)     /**< Shifted mode DEFAULT for MSC_IF             */
#define MSC_IF_WDATAOV                                 (0x1UL << 2)                     /**< Host write buffer overflow                  */
#define _MSC_IF_WDATAOV_SHIFT                          2                                /**< Shift value for MSC_WDATAOV                 */
#define _MSC_IF_WDATAOV_MASK                           0x4UL                            /**< Bit mask for MSC_WDATAOV                    */
#define _MSC_IF_WDATAOV_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IF                     */
#define MSC_IF_WDATAOV_DEFAULT                         (_MSC_IF_WDATAOV_DEFAULT << 2)   /**< Shifted mode DEFAULT for MSC_IF             */
#define MSC_IF_PWRUPF                                  (0x1UL << 8)                     /**< Flash Power Up Sequence Complete Flag       */
#define _MSC_IF_PWRUPF_SHIFT                           8                                /**< Shift value for MSC_PWRUPF                  */
#define _MSC_IF_PWRUPF_MASK                            0x100UL                          /**< Bit mask for MSC_PWRUPF                     */
#define _MSC_IF_PWRUPF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IF                     */
#define MSC_IF_PWRUPF_DEFAULT                          (_MSC_IF_PWRUPF_DEFAULT << 8)    /**< Shifted mode DEFAULT for MSC_IF             */
#define MSC_IF_PWROFF                                  (0x1UL << 9)                     /**< Flash Power Off Sequence Complete Flag      */
#define _MSC_IF_PWROFF_SHIFT                           9                                /**< Shift value for MSC_PWROFF                  */
#define _MSC_IF_PWROFF_MASK                            0x200UL                          /**< Bit mask for MSC_PWROFF                     */
#define _MSC_IF_PWROFF_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IF                     */
#define MSC_IF_PWROFF_DEFAULT                          (_MSC_IF_PWROFF_DEFAULT << 9)    /**< Shifted mode DEFAULT for MSC_IF             */

/* Bit fields for MSC IEN */
#define _MSC_IEN_RESETVALUE                            0x00000000UL                     /**< Default value for MSC_IEN                   */
#define _MSC_IEN_MASK                                  0x00000307UL                     /**< Mask for MSC_IEN                            */
#define MSC_IEN_ERASE                                  (0x1UL << 0)                     /**< Erase Done Interrupt enable                 */
#define _MSC_IEN_ERASE_SHIFT                           0                                /**< Shift value for MSC_ERASE                   */
#define _MSC_IEN_ERASE_MASK                            0x1UL                            /**< Bit mask for MSC_ERASE                      */
#define _MSC_IEN_ERASE_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IEN                    */
#define MSC_IEN_ERASE_DEFAULT                          (_MSC_IEN_ERASE_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_IEN            */
#define MSC_IEN_WRITE                                  (0x1UL << 1)                     /**< Write Done Interrupt enable                 */
#define _MSC_IEN_WRITE_SHIFT                           1                                /**< Shift value for MSC_WRITE                   */
#define _MSC_IEN_WRITE_MASK                            0x2UL                            /**< Bit mask for MSC_WRITE                      */
#define _MSC_IEN_WRITE_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_IEN                    */
#define MSC_IEN_WRITE_DEFAULT                          (_MSC_IEN_WRITE_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_IEN            */
#define MSC_IEN_WDATAOV                                (0x1UL << 2)                     /**< write data buffer overflow irq enable       */
#define _MSC_IEN_WDATAOV_SHIFT                         2                                /**< Shift value for MSC_WDATAOV                 */
#define _MSC_IEN_WDATAOV_MASK                          0x4UL                            /**< Bit mask for MSC_WDATAOV                    */
#define _MSC_IEN_WDATAOV_DEFAULT                       0x00000000UL                     /**< Mode DEFAULT for MSC_IEN                    */
#define MSC_IEN_WDATAOV_DEFAULT                        (_MSC_IEN_WDATAOV_DEFAULT << 2)  /**< Shifted mode DEFAULT for MSC_IEN            */
#define MSC_IEN_PWRUPF                                 (0x1UL << 8)                     /**< Flash Power Up Seq done irq enable          */
#define _MSC_IEN_PWRUPF_SHIFT                          8                                /**< Shift value for MSC_PWRUPF                  */
#define _MSC_IEN_PWRUPF_MASK                           0x100UL                          /**< Bit mask for MSC_PWRUPF                     */
#define _MSC_IEN_PWRUPF_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IEN                    */
#define MSC_IEN_PWRUPF_DEFAULT                         (_MSC_IEN_PWRUPF_DEFAULT << 8)   /**< Shifted mode DEFAULT for MSC_IEN            */
#define MSC_IEN_PWROFF                                 (0x1UL << 9)                     /**< Flash Power Off Seq done irq enable         */
#define _MSC_IEN_PWROFF_SHIFT                          9                                /**< Shift value for MSC_PWROFF                  */
#define _MSC_IEN_PWROFF_MASK                           0x200UL                          /**< Bit mask for MSC_PWROFF                     */
#define _MSC_IEN_PWROFF_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_IEN                    */
#define MSC_IEN_PWROFF_DEFAULT                         (_MSC_IEN_PWROFF_DEFAULT << 9)   /**< Shifted mode DEFAULT for MSC_IEN            */

/* Bit fields for MSC USERDATASIZE */
#define _MSC_USERDATASIZE_RESETVALUE                   0x00000004UL                                  /**< Default value for MSC_USERDATASIZE          */
#define _MSC_USERDATASIZE_MASK                         0x0000003FUL                                  /**< Mask for MSC_USERDATASIZE                   */
#define _MSC_USERDATASIZE_USERDATASIZE_SHIFT           0                                             /**< Shift value for MSC_USERDATASIZE            */
#define _MSC_USERDATASIZE_USERDATASIZE_MASK            0x3FUL                                        /**< Bit mask for MSC_USERDATASIZE               */
#define _MSC_USERDATASIZE_USERDATASIZE_DEFAULT         0x00000004UL                                  /**< Mode DEFAULT for MSC_USERDATASIZE           */
#define MSC_USERDATASIZE_USERDATASIZE_DEFAULT          (_MSC_USERDATASIZE_USERDATASIZE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_USERDATASIZE   */

/* Bit fields for MSC CMD */
#define _MSC_CMD_RESETVALUE                            0x00000000UL                     /**< Default value for MSC_CMD                   */
#define _MSC_CMD_MASK                                  0x00000011UL                     /**< Mask for MSC_CMD                            */
#define MSC_CMD_PWRUP                                  (0x1UL << 0)                     /**< Flash Power Up Command                      */
#define _MSC_CMD_PWRUP_SHIFT                           0                                /**< Shift value for MSC_PWRUP                   */
#define _MSC_CMD_PWRUP_MASK                            0x1UL                            /**< Bit mask for MSC_PWRUP                      */
#define _MSC_CMD_PWRUP_DEFAULT                         0x00000000UL                     /**< Mode DEFAULT for MSC_CMD                    */
#define MSC_CMD_PWRUP_DEFAULT                          (_MSC_CMD_PWRUP_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_CMD            */
#define MSC_CMD_PWROFF                                 (0x1UL << 4)                     /**< Flash power off/sleep command               */
#define _MSC_CMD_PWROFF_SHIFT                          4                                /**< Shift value for MSC_PWROFF                  */
#define _MSC_CMD_PWROFF_MASK                           0x10UL                           /**< Bit mask for MSC_PWROFF                     */
#define _MSC_CMD_PWROFF_DEFAULT                        0x00000000UL                     /**< Mode DEFAULT for MSC_CMD                    */
#define MSC_CMD_PWROFF_DEFAULT                         (_MSC_CMD_PWROFF_DEFAULT << 4)   /**< Shifted mode DEFAULT for MSC_CMD            */

/* Bit fields for MSC LOCK */
#define _MSC_LOCK_RESETVALUE                           0x00000000UL                     /**< Default value for MSC_LOCK                  */
#define _MSC_LOCK_MASK                                 0x0000FFFFUL                     /**< Mask for MSC_LOCK                           */
#define _MSC_LOCK_LOCKKEY_SHIFT                        0                                /**< Shift value for MSC_LOCKKEY                 */
#define _MSC_LOCK_LOCKKEY_MASK                         0xFFFFUL                         /**< Bit mask for MSC_LOCKKEY                    */
#define _MSC_LOCK_LOCKKEY_DEFAULT                      0x00000000UL                     /**< Mode DEFAULT for MSC_LOCK                   */
#define _MSC_LOCK_LOCKKEY_LOCK                         0x00000000UL                     /**< Mode LOCK for MSC_LOCK                      */
#define _MSC_LOCK_LOCKKEY_UNLOCK                       0x00001B71UL                     /**< Mode UNLOCK for MSC_LOCK                    */
#define MSC_LOCK_LOCKKEY_DEFAULT                       (_MSC_LOCK_LOCKKEY_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_LOCK           */
#define MSC_LOCK_LOCKKEY_LOCK                          (_MSC_LOCK_LOCKKEY_LOCK << 0)    /**< Shifted mode LOCK for MSC_LOCK              */
#define MSC_LOCK_LOCKKEY_UNLOCK                        (_MSC_LOCK_LOCKKEY_UNLOCK << 0)  /**< Shifted mode UNLOCK for MSC_LOCK            */

/* Bit fields for MSC MISCLOCKWORD */
#define _MSC_MISCLOCKWORD_RESETVALUE                   0x00000011UL                               /**< Default value for MSC_MISCLOCKWORD          */
#define _MSC_MISCLOCKWORD_MASK                         0x00000011UL                               /**< Mask for MSC_MISCLOCKWORD                   */
#define MSC_MISCLOCKWORD_MELOCKBIT                     (0x1UL << 0)                               /**< Mass Erase Lock                             */
#define _MSC_MISCLOCKWORD_MELOCKBIT_SHIFT              0                                          /**< Shift value for MSC_MELOCKBIT               */
#define _MSC_MISCLOCKWORD_MELOCKBIT_MASK               0x1UL                                      /**< Bit mask for MSC_MELOCKBIT                  */
#define _MSC_MISCLOCKWORD_MELOCKBIT_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for MSC_MISCLOCKWORD           */
#define MSC_MISCLOCKWORD_MELOCKBIT_DEFAULT             (_MSC_MISCLOCKWORD_MELOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_MISCLOCKWORD   */
#define MSC_MISCLOCKWORD_UDLOCKBIT                     (0x1UL << 4)                               /**< User Data Lock                              */
#define _MSC_MISCLOCKWORD_UDLOCKBIT_SHIFT              4                                          /**< Shift value for MSC_UDLOCKBIT               */
#define _MSC_MISCLOCKWORD_UDLOCKBIT_MASK               0x10UL                                     /**< Bit mask for MSC_UDLOCKBIT                  */
#define _MSC_MISCLOCKWORD_UDLOCKBIT_DEFAULT            0x00000001UL                               /**< Mode DEFAULT for MSC_MISCLOCKWORD           */
#define MSC_MISCLOCKWORD_UDLOCKBIT_DEFAULT             (_MSC_MISCLOCKWORD_UDLOCKBIT_DEFAULT << 4) /**< Shifted mode DEFAULT for MSC_MISCLOCKWORD   */

/* Bit fields for MSC PWRCTRL */
#define _MSC_PWRCTRL_RESETVALUE                        0x00100002UL                                  /**< Default value for MSC_PWRCTRL               */
#define _MSC_PWRCTRL_MASK                              0x00FF0013UL                                  /**< Mask for MSC_PWRCTRL                        */
#define MSC_PWRCTRL_PWROFFONEM1ENTRY                   (0x1UL << 0)                                  /**< Power down Flash macro when enter EM1       */
#define _MSC_PWRCTRL_PWROFFONEM1ENTRY_SHIFT            0                                             /**< Shift value for MSC_PWROFFONEM1ENTRY        */
#define _MSC_PWRCTRL_PWROFFONEM1ENTRY_MASK             0x1UL                                         /**< Bit mask for MSC_PWROFFONEM1ENTRY           */
#define _MSC_PWRCTRL_PWROFFONEM1ENTRY_DEFAULT          0x00000000UL                                  /**< Mode DEFAULT for MSC_PWRCTRL                */
#define MSC_PWRCTRL_PWROFFONEM1ENTRY_DEFAULT           (_MSC_PWRCTRL_PWROFFONEM1ENTRY_DEFAULT << 0)  /**< Shifted mode DEFAULT for MSC_PWRCTRL        */
#define MSC_PWRCTRL_PWROFFONEM1PENTRY                  (0x1UL << 1)                                  /**< Power down Flash macro when enter EM1P      */
#define _MSC_PWRCTRL_PWROFFONEM1PENTRY_SHIFT           1                                             /**< Shift value for MSC_PWROFFONEM1PENTRY       */
#define _MSC_PWRCTRL_PWROFFONEM1PENTRY_MASK            0x2UL                                         /**< Bit mask for MSC_PWROFFONEM1PENTRY          */
#define _MSC_PWRCTRL_PWROFFONEM1PENTRY_DEFAULT         0x00000001UL                                  /**< Mode DEFAULT for MSC_PWRCTRL                */
#define MSC_PWRCTRL_PWROFFONEM1PENTRY_DEFAULT          (_MSC_PWRCTRL_PWROFFONEM1PENTRY_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_PWRCTRL        */
#define MSC_PWRCTRL_PWROFFENTRYAGAIN                   (0x1UL << 4)                                  /**< POWER down flash again in EM1/EM1p          */
#define _MSC_PWRCTRL_PWROFFENTRYAGAIN_SHIFT            4                                             /**< Shift value for MSC_PWROFFENTRYAGAIN        */
#define _MSC_PWRCTRL_PWROFFENTRYAGAIN_MASK             0x10UL                                        /**< Bit mask for MSC_PWROFFENTRYAGAIN           */
#define _MSC_PWRCTRL_PWROFFENTRYAGAIN_DEFAULT          0x00000000UL                                  /**< Mode DEFAULT for MSC_PWRCTRL                */
#define MSC_PWRCTRL_PWROFFENTRYAGAIN_DEFAULT           (_MSC_PWRCTRL_PWROFFENTRYAGAIN_DEFAULT << 4)  /**< Shifted mode DEFAULT for MSC_PWRCTRL        */
#define _MSC_PWRCTRL_PWROFFDLY_SHIFT                   16                                            /**< Shift value for MSC_PWROFFDLY               */
#define _MSC_PWRCTRL_PWROFFDLY_MASK                    0xFF0000UL                                    /**< Bit mask for MSC_PWROFFDLY                  */
#define _MSC_PWRCTRL_PWROFFDLY_DEFAULT                 0x00000010UL                                  /**< Mode DEFAULT for MSC_PWRCTRL                */
#define MSC_PWRCTRL_PWROFFDLY_DEFAULT                  (_MSC_PWRCTRL_PWROFFDLY_DEFAULT << 16)        /**< Shifted mode DEFAULT for MSC_PWRCTRL        */

/* Bit fields for MSC SEWRITECTRL */
#define _MSC_SEWRITECTRL_RESETVALUE                    0x00000000UL                                  /**< Default value for MSC_SEWRITECTRL           */
#define _MSC_SEWRITECTRL_MASK                          0x03FF000BUL                                  /**< Mask for MSC_SEWRITECTRL                    */
#define MSC_SEWRITECTRL_WREN                           (0x1UL << 0)                                  /**< Enable Write/Erase Controller               */
#define _MSC_SEWRITECTRL_WREN_SHIFT                    0                                             /**< Shift value for MSC_WREN                    */
#define _MSC_SEWRITECTRL_WREN_MASK                     0x1UL                                         /**< Bit mask for MSC_WREN                       */
#define _MSC_SEWRITECTRL_WREN_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for MSC_SEWRITECTRL            */
#define MSC_SEWRITECTRL_WREN_DEFAULT                   (_MSC_SEWRITECTRL_WREN_DEFAULT << 0)          /**< Shifted mode DEFAULT for MSC_SEWRITECTRL    */
#define MSC_SEWRITECTRL_IRQERASEABORT                  (0x1UL << 1)                                  /**< Abort Page Erase on Interrupt               */
#define _MSC_SEWRITECTRL_IRQERASEABORT_SHIFT           1                                             /**< Shift value for MSC_IRQERASEABORT           */
#define _MSC_SEWRITECTRL_IRQERASEABORT_MASK            0x2UL                                         /**< Bit mask for MSC_IRQERASEABORT              */
#define _MSC_SEWRITECTRL_IRQERASEABORT_DEFAULT         0x00000000UL                                  /**< Mode DEFAULT for MSC_SEWRITECTRL            */
#define MSC_SEWRITECTRL_IRQERASEABORT_DEFAULT          (_MSC_SEWRITECTRL_IRQERASEABORT_DEFAULT << 1) /**< Shifted mode DEFAULT for MSC_SEWRITECTRL    */
#define MSC_SEWRITECTRL_LPWRITE                        (0x1UL << 3)                                  /**< Low-Power Erase                             */
#define _MSC_SEWRITECTRL_LPWRITE_SHIFT                 3                                             /**< Shift value for MSC_LPWRITE                 */
#define _MSC_SEWRITECTRL_LPWRITE_MASK                  0x8UL                                         /**< Bit mask for MSC_LPWRITE                    */
#define _MSC_SEWRITECTRL_LPWRITE_DEFAULT               0x00000000UL                                  /**< Mode DEFAULT for MSC_SEWRITECTRL            */
#define MSC_SEWRITECTRL_LPWRITE_DEFAULT                (_MSC_SEWRITECTRL_LPWRITE_DEFAULT << 3)       /**< Shifted mode DEFAULT for MSC_SEWRITECTRL    */
#define _MSC_SEWRITECTRL_RANGECOUNT_SHIFT              16                                            /**< Shift value for MSC_RANGECOUNT              */
#define _MSC_SEWRITECTRL_RANGECOUNT_MASK               0x3FF0000UL                                   /**< Bit mask for MSC_RANGECOUNT                 */
#define _MSC_SEWRITECTRL_RANGECOUNT_DEFAULT            0x00000000UL                                  /**< Mode DEFAULT for MSC_SEWRITECTRL            */
#define MSC_SEWRITECTRL_RANGECOUNT_DEFAULT             (_MSC_SEWRITECTRL_RANGECOUNT_DEFAULT << 16)   /**< Shifted mode DEFAULT for MSC_SEWRITECTRL    */

/* Bit fields for MSC SEWRITECMD */
#define _MSC_SEWRITECMD_RESETVALUE                     0x00000000UL                               /**< Default value for MSC_SEWRITECMD            */
#define _MSC_SEWRITECMD_MASK                           0x00001736UL                               /**< Mask for MSC_SEWRITECMD                     */
#define MSC_SEWRITECMD_ERASEPAGE                       (0x1UL << 1)                               /**< Erase Page                                  */
#define _MSC_SEWRITECMD_ERASEPAGE_SHIFT                1                                          /**< Shift value for MSC_ERASEPAGE               */
#define _MSC_SEWRITECMD_ERASEPAGE_MASK                 0x2UL                                      /**< Bit mask for MSC_ERASEPAGE                  */
#define _MSC_SEWRITECMD_ERASEPAGE_DEFAULT              0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASEPAGE_DEFAULT               (_MSC_SEWRITECMD_ERASEPAGE_DEFAULT << 1)   /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_WRITEEND                        (0x1UL << 2)                               /**< End Write Mode                              */
#define _MSC_SEWRITECMD_WRITEEND_SHIFT                 2                                          /**< Shift value for MSC_WRITEEND                */
#define _MSC_SEWRITECMD_WRITEEND_MASK                  0x4UL                                      /**< Bit mask for MSC_WRITEEND                   */
#define _MSC_SEWRITECMD_WRITEEND_DEFAULT               0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_WRITEEND_DEFAULT                (_MSC_SEWRITECMD_WRITEEND_DEFAULT << 2)    /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_ERASERANGE                      (0x1UL << 4)                               /**< Erase range of pages                        */
#define _MSC_SEWRITECMD_ERASERANGE_SHIFT               4                                          /**< Shift value for MSC_ERASERANGE              */
#define _MSC_SEWRITECMD_ERASERANGE_MASK                0x10UL                                     /**< Bit mask for MSC_ERASERANGE                 */
#define _MSC_SEWRITECMD_ERASERANGE_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASERANGE_DEFAULT              (_MSC_SEWRITECMD_ERASERANGE_DEFAULT << 4)  /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_ERASEABORT                      (0x1UL << 5)                               /**< Abort erase sequence                        */
#define _MSC_SEWRITECMD_ERASEABORT_SHIFT               5                                          /**< Shift value for MSC_ERASEABORT              */
#define _MSC_SEWRITECMD_ERASEABORT_MASK                0x20UL                                     /**< Bit mask for MSC_ERASEABORT                 */
#define _MSC_SEWRITECMD_ERASEABORT_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASEABORT_DEFAULT              (_MSC_SEWRITECMD_ERASEABORT_DEFAULT << 5)  /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_ERASEMAIN0                      (0x1UL << 8)                               /**< Mass erase user area                        */
#define _MSC_SEWRITECMD_ERASEMAIN0_SHIFT               8                                          /**< Shift value for MSC_ERASEMAIN0              */
#define _MSC_SEWRITECMD_ERASEMAIN0_MASK                0x100UL                                    /**< Bit mask for MSC_ERASEMAIN0                 */
#define _MSC_SEWRITECMD_ERASEMAIN0_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASEMAIN0_DEFAULT              (_MSC_SEWRITECMD_ERASEMAIN0_DEFAULT << 8)  /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_ERASEMAIN1                      (0x1UL << 9)                               /**< Mass erase non-user area                    */
#define _MSC_SEWRITECMD_ERASEMAIN1_SHIFT               9                                          /**< Shift value for MSC_ERASEMAIN1              */
#define _MSC_SEWRITECMD_ERASEMAIN1_MASK                0x200UL                                    /**< Bit mask for MSC_ERASEMAIN1                 */
#define _MSC_SEWRITECMD_ERASEMAIN1_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASEMAIN1_DEFAULT              (_MSC_SEWRITECMD_ERASEMAIN1_DEFAULT << 9)  /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_ERASEMAINA                      (0x1UL << 10)                              /**< Mass erase all main                         */
#define _MSC_SEWRITECMD_ERASEMAINA_SHIFT               10                                         /**< Shift value for MSC_ERASEMAINA              */
#define _MSC_SEWRITECMD_ERASEMAINA_MASK                0x400UL                                    /**< Bit mask for MSC_ERASEMAINA                 */
#define _MSC_SEWRITECMD_ERASEMAINA_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_ERASEMAINA_DEFAULT              (_MSC_SEWRITECMD_ERASEMAINA_DEFAULT << 10) /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */
#define MSC_SEWRITECMD_CLEARWDATA                      (0x1UL << 12)                              /**< Clear WDATA state                           */
#define _MSC_SEWRITECMD_CLEARWDATA_SHIFT               12                                         /**< Shift value for MSC_CLEARWDATA              */
#define _MSC_SEWRITECMD_CLEARWDATA_MASK                0x1000UL                                   /**< Bit mask for MSC_CLEARWDATA                 */
#define _MSC_SEWRITECMD_CLEARWDATA_DEFAULT             0x00000000UL                               /**< Mode DEFAULT for MSC_SEWRITECMD             */
#define MSC_SEWRITECMD_CLEARWDATA_DEFAULT              (_MSC_SEWRITECMD_CLEARWDATA_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_SEWRITECMD     */

/* Bit fields for MSC SEADDRB */
#define _MSC_SEADDRB_RESETVALUE                        0x00000000UL                      /**< Default value for MSC_SEADDRB               */
#define _MSC_SEADDRB_MASK                              0xFFFFFFFFUL                      /**< Mask for MSC_SEADDRB                        */
#define _MSC_SEADDRB_ADDRB_SHIFT                       0                                 /**< Shift value for MSC_ADDRB                   */
#define _MSC_SEADDRB_ADDRB_MASK                        0xFFFFFFFFUL                      /**< Bit mask for MSC_ADDRB                      */
#define _MSC_SEADDRB_ADDRB_DEFAULT                     0x00000000UL                      /**< Mode DEFAULT for MSC_SEADDRB                */
#define MSC_SEADDRB_ADDRB_DEFAULT                      (_MSC_SEADDRB_ADDRB_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_SEADDRB        */

/* Bit fields for MSC SEWDATA */
#define _MSC_SEWDATA_RESETVALUE                        0x00000000UL                      /**< Default value for MSC_SEWDATA               */
#define _MSC_SEWDATA_MASK                              0xFFFFFFFFUL                      /**< Mask for MSC_SEWDATA                        */
#define _MSC_SEWDATA_DATAW_SHIFT                       0                                 /**< Shift value for MSC_DATAW                   */
#define _MSC_SEWDATA_DATAW_MASK                        0xFFFFFFFFUL                      /**< Bit mask for MSC_DATAW                      */
#define _MSC_SEWDATA_DATAW_DEFAULT                     0x00000000UL                      /**< Mode DEFAULT for MSC_SEWDATA                */
#define MSC_SEWDATA_DATAW_DEFAULT                      (_MSC_SEWDATA_DATAW_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_SEWDATA        */

/* Bit fields for MSC SESTATUS */
#define _MSC_SESTATUS_RESETVALUE                       0x00000008UL                                  /**< Default value for MSC_SESTATUS              */
#define _MSC_SESTATUS_MASK                             0xC00100FFUL                                  /**< Mask for MSC_SESTATUS                       */
#define MSC_SESTATUS_BUSY                              (0x1UL << 0)                                  /**< Erase/Write Busy                            */
#define _MSC_SESTATUS_BUSY_SHIFT                       0                                             /**< Shift value for MSC_BUSY                    */
#define _MSC_SESTATUS_BUSY_MASK                        0x1UL                                         /**< Bit mask for MSC_BUSY                       */
#define _MSC_SESTATUS_BUSY_DEFAULT                     0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_BUSY_DEFAULT                      (_MSC_SESTATUS_BUSY_DEFAULT << 0)             /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_LOCKED                            (0x1UL << 1)                                  /**< Access Locked                               */
#define _MSC_SESTATUS_LOCKED_SHIFT                     1                                             /**< Shift value for MSC_LOCKED                  */
#define _MSC_SESTATUS_LOCKED_MASK                      0x2UL                                         /**< Bit mask for MSC_LOCKED                     */
#define _MSC_SESTATUS_LOCKED_DEFAULT                   0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_LOCKED_DEFAULT                    (_MSC_SESTATUS_LOCKED_DEFAULT << 1)           /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_INVADDR                           (0x1UL << 2)                                  /**< Invalid Write Address or Erase Page         */
#define _MSC_SESTATUS_INVADDR_SHIFT                    2                                             /**< Shift value for MSC_INVADDR                 */
#define _MSC_SESTATUS_INVADDR_MASK                     0x4UL                                         /**< Bit mask for MSC_INVADDR                    */
#define _MSC_SESTATUS_INVADDR_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_INVADDR_DEFAULT                   (_MSC_SESTATUS_INVADDR_DEFAULT << 2)          /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_WDATAREADY                        (0x1UL << 3)                                  /**< WDATA Write Ready                           */
#define _MSC_SESTATUS_WDATAREADY_SHIFT                 3                                             /**< Shift value for MSC_WDATAREADY              */
#define _MSC_SESTATUS_WDATAREADY_MASK                  0x8UL                                         /**< Bit mask for MSC_WDATAREADY                 */
#define _MSC_SESTATUS_WDATAREADY_DEFAULT               0x00000001UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_WDATAREADY_DEFAULT                (_MSC_SESTATUS_WDATAREADY_DEFAULT << 3)       /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_ERASEABORTED                      (0x1UL << 4)                                  /**< The Current Flash Erase Operation Aborte    */
#define _MSC_SESTATUS_ERASEABORTED_SHIFT               4                                             /**< Shift value for MSC_ERASEABORTED            */
#define _MSC_SESTATUS_ERASEABORTED_MASK                0x10UL                                        /**< Bit mask for MSC_ERASEABORTED               */
#define _MSC_SESTATUS_ERASEABORTED_DEFAULT             0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_ERASEABORTED_DEFAULT              (_MSC_SESTATUS_ERASEABORTED_DEFAULT << 4)     /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_PENDING                           (0x1UL << 5)                                  /**< Write command is in queue                   */
#define _MSC_SESTATUS_PENDING_SHIFT                    5                                             /**< Shift value for MSC_PENDING                 */
#define _MSC_SESTATUS_PENDING_MASK                     0x20UL                                        /**< Bit mask for MSC_PENDING                    */
#define _MSC_SESTATUS_PENDING_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_PENDING_DEFAULT                   (_MSC_SESTATUS_PENDING_DEFAULT << 5)          /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_TIMEOUT                           (0x1UL << 6)                                  /**< Write command timeout flag                  */
#define _MSC_SESTATUS_TIMEOUT_SHIFT                    6                                             /**< Shift value for MSC_TIMEOUT                 */
#define _MSC_SESTATUS_TIMEOUT_MASK                     0x40UL                                        /**< Bit mask for MSC_TIMEOUT                    */
#define _MSC_SESTATUS_TIMEOUT_DEFAULT                  0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_TIMEOUT_DEFAULT                   (_MSC_SESTATUS_TIMEOUT_DEFAULT << 6)          /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_RANGEPARTIAL                      (0x1UL << 7)                                  /**< EraseRange with skipped locked pages        */
#define _MSC_SESTATUS_RANGEPARTIAL_SHIFT               7                                             /**< Shift value for MSC_RANGEPARTIAL            */
#define _MSC_SESTATUS_RANGEPARTIAL_MASK                0x80UL                                        /**< Bit mask for MSC_RANGEPARTIAL               */
#define _MSC_SESTATUS_RANGEPARTIAL_DEFAULT             0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_RANGEPARTIAL_DEFAULT              (_MSC_SESTATUS_RANGEPARTIAL_DEFAULT << 7)     /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_ROOTLOCK                          (0x1UL << 16)                                 /**< Register Lock Status                        */
#define _MSC_SESTATUS_ROOTLOCK_SHIFT                   16                                            /**< Shift value for MSC_ROOTLOCK                */
#define _MSC_SESTATUS_ROOTLOCK_MASK                    0x10000UL                                     /**< Bit mask for MSC_ROOTLOCK                   */
#define _MSC_SESTATUS_ROOTLOCK_DEFAULT                 0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define _MSC_SESTATUS_ROOTLOCK_UNLOCKED                0x00000000UL                                  /**< Mode UNLOCKED for MSC_SESTATUS              */
#define _MSC_SESTATUS_ROOTLOCK_LOCKED                  0x00000001UL                                  /**< Mode LOCKED for MSC_SESTATUS                */
#define MSC_SESTATUS_ROOTLOCK_DEFAULT                  (_MSC_SESTATUS_ROOTLOCK_DEFAULT << 16)        /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_ROOTLOCK_UNLOCKED                 (_MSC_SESTATUS_ROOTLOCK_UNLOCKED << 16)       /**< Shifted mode UNLOCKED for MSC_SESTATUS      */
#define MSC_SESTATUS_ROOTLOCK_LOCKED                   (_MSC_SESTATUS_ROOTLOCK_LOCKED << 16)         /**< Shifted mode LOCKED for MSC_SESTATUS        */
#define MSC_SESTATUS_PWRCKDONE                         (0x1UL << 30)                                 /**< Flash power up CKBD done flag               */
#define _MSC_SESTATUS_PWRCKDONE_SHIFT                  30                                            /**< Shift value for MSC_PWRCKDONE               */
#define _MSC_SESTATUS_PWRCKDONE_MASK                   0x40000000UL                                  /**< Bit mask for MSC_PWRCKDONE                  */
#define _MSC_SESTATUS_PWRCKDONE_DEFAULT                0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_PWRCKDONE_DEFAULT                 (_MSC_SESTATUS_PWRCKDONE_DEFAULT << 30)       /**< Shifted mode DEFAULT for MSC_SESTATUS       */
#define MSC_SESTATUS_PWRCKSKIPSTATUS                   (0x1UL << 31)                                 /**< Flash power up CKBD skip status             */
#define _MSC_SESTATUS_PWRCKSKIPSTATUS_SHIFT            31                                            /**< Shift value for MSC_PWRCKSKIPSTATUS         */
#define _MSC_SESTATUS_PWRCKSKIPSTATUS_MASK             0x80000000UL                                  /**< Bit mask for MSC_PWRCKSKIPSTATUS            */
#define _MSC_SESTATUS_PWRCKSKIPSTATUS_DEFAULT          0x00000000UL                                  /**< Mode DEFAULT for MSC_SESTATUS               */
#define MSC_SESTATUS_PWRCKSKIPSTATUS_DEFAULT           (_MSC_SESTATUS_PWRCKSKIPSTATUS_DEFAULT << 31) /**< Shifted mode DEFAULT for MSC_SESTATUS       */

/* Bit fields for MSC SEIF */
#define _MSC_SEIF_RESETVALUE                           0x00000000UL                       /**< Default value for MSC_SEIF                  */
#define _MSC_SEIF_MASK                                 0x00000007UL                       /**< Mask for MSC_SEIF                           */
#define MSC_SEIF_ERASEIF                               (0x1UL << 0)                       /**< SE Erase Done Interrupt Read Flag           */
#define _MSC_SEIF_ERASEIF_SHIFT                        0                                  /**< Shift value for MSC_ERASEIF                 */
#define _MSC_SEIF_ERASEIF_MASK                         0x1UL                              /**< Bit mask for MSC_ERASEIF                    */
#define _MSC_SEIF_ERASEIF_DEFAULT                      0x00000000UL                       /**< Mode DEFAULT for MSC_SEIF                   */
#define MSC_SEIF_ERASEIF_DEFAULT                       (_MSC_SEIF_ERASEIF_DEFAULT << 0)   /**< Shifted mode DEFAULT for MSC_SEIF           */
#define MSC_SEIF_WRITEIF                               (0x1UL << 1)                       /**< SE Write Done Interrupt Read Flag           */
#define _MSC_SEIF_WRITEIF_SHIFT                        1                                  /**< Shift value for MSC_WRITEIF                 */
#define _MSC_SEIF_WRITEIF_MASK                         0x2UL                              /**< Bit mask for MSC_WRITEIF                    */
#define _MSC_SEIF_WRITEIF_DEFAULT                      0x00000000UL                       /**< Mode DEFAULT for MSC_SEIF                   */
#define MSC_SEIF_WRITEIF_DEFAULT                       (_MSC_SEIF_WRITEIF_DEFAULT << 1)   /**< Shifted mode DEFAULT for MSC_SEIF           */
#define MSC_SEIF_WDATAOVIF                             (0x1UL << 2)                       /**< SE write buffer overflow                    */
#define _MSC_SEIF_WDATAOVIF_SHIFT                      2                                  /**< Shift value for MSC_WDATAOVIF               */
#define _MSC_SEIF_WDATAOVIF_MASK                       0x4UL                              /**< Bit mask for MSC_WDATAOVIF                  */
#define _MSC_SEIF_WDATAOVIF_DEFAULT                    0x00000000UL                       /**< Mode DEFAULT for MSC_SEIF                   */
#define MSC_SEIF_WDATAOVIF_DEFAULT                     (_MSC_SEIF_WDATAOVIF_DEFAULT << 2) /**< Shifted mode DEFAULT for MSC_SEIF           */

/* Bit fields for MSC SEIEN */
#define _MSC_SEIEN_RESETVALUE                          0x00000000UL                         /**< Default value for MSC_SEIEN                 */
#define _MSC_SEIEN_MASK                                0x00000007UL                         /**< Mask for MSC_SEIEN                          */
#define MSC_SEIEN_ERASEIEN                             (0x1UL << 0)                         /**< Erase Done Interrupt enable                 */
#define _MSC_SEIEN_ERASEIEN_SHIFT                      0                                    /**< Shift value for MSC_ERASEIEN                */
#define _MSC_SEIEN_ERASEIEN_MASK                       0x1UL                                /**< Bit mask for MSC_ERASEIEN                   */
#define _MSC_SEIEN_ERASEIEN_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for MSC_SEIEN                  */
#define MSC_SEIEN_ERASEIEN_DEFAULT                     (_MSC_SEIEN_ERASEIEN_DEFAULT << 0)   /**< Shifted mode DEFAULT for MSC_SEIEN          */
#define MSC_SEIEN_WRITEIEN                             (0x1UL << 1)                         /**< Write Done Interrupt enable                 */
#define _MSC_SEIEN_WRITEIEN_SHIFT                      1                                    /**< Shift value for MSC_WRITEIEN                */
#define _MSC_SEIEN_WRITEIEN_MASK                       0x2UL                                /**< Bit mask for MSC_WRITEIEN                   */
#define _MSC_SEIEN_WRITEIEN_DEFAULT                    0x00000000UL                         /**< Mode DEFAULT for MSC_SEIEN                  */
#define MSC_SEIEN_WRITEIEN_DEFAULT                     (_MSC_SEIEN_WRITEIEN_DEFAULT << 1)   /**< Shifted mode DEFAULT for MSC_SEIEN          */
#define MSC_SEIEN_WDATAOVIEN                           (0x1UL << 2)                         /**< write data buffer overflow irq enable       */
#define _MSC_SEIEN_WDATAOVIEN_SHIFT                    2                                    /**< Shift value for MSC_WDATAOVIEN              */
#define _MSC_SEIEN_WDATAOVIEN_MASK                     0x4UL                                /**< Bit mask for MSC_WDATAOVIEN                 */
#define _MSC_SEIEN_WDATAOVIEN_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for MSC_SEIEN                  */
#define MSC_SEIEN_WDATAOVIEN_DEFAULT                   (_MSC_SEIEN_WDATAOVIEN_DEFAULT << 2) /**< Shifted mode DEFAULT for MSC_SEIEN          */

/* Bit fields for MSC STARTUP */
#define _MSC_STARTUP_RESETVALUE                        0x23001078UL                         /**< Default value for MSC_STARTUP               */
#define _MSC_STARTUP_MASK                              0x773FF3FFUL                         /**< Mask for MSC_STARTUP                        */
#define _MSC_STARTUP_STDLY0_SHIFT                      0                                    /**< Shift value for MSC_STDLY0                  */
#define _MSC_STARTUP_STDLY0_MASK                       0x3FFUL                              /**< Bit mask for MSC_STDLY0                     */
#define _MSC_STARTUP_STDLY0_DEFAULT                    0x00000078UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_STDLY0_DEFAULT                     (_MSC_STARTUP_STDLY0_DEFAULT << 0)   /**< Shifted mode DEFAULT for MSC_STARTUP        */
#define _MSC_STARTUP_STDLY1_SHIFT                      12                                   /**< Shift value for MSC_STDLY1                  */
#define _MSC_STARTUP_STDLY1_MASK                       0x3FF000UL                           /**< Bit mask for MSC_STDLY1                     */
#define _MSC_STARTUP_STDLY1_DEFAULT                    0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_STDLY1_DEFAULT                     (_MSC_STARTUP_STDLY1_DEFAULT << 12)  /**< Shifted mode DEFAULT for MSC_STARTUP        */
#define MSC_STARTUP_ASTWAIT                            (0x1UL << 24)                        /**< Active Startup Wait                         */
#define _MSC_STARTUP_ASTWAIT_SHIFT                     24                                   /**< Shift value for MSC_ASTWAIT                 */
#define _MSC_STARTUP_ASTWAIT_MASK                      0x1000000UL                          /**< Bit mask for MSC_ASTWAIT                    */
#define _MSC_STARTUP_ASTWAIT_DEFAULT                   0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_ASTWAIT_DEFAULT                    (_MSC_STARTUP_ASTWAIT_DEFAULT << 24) /**< Shifted mode DEFAULT for MSC_STARTUP        */
#define MSC_STARTUP_STWSEN                             (0x1UL << 25)                        /**< Startup Waitstates Enable                   */
#define _MSC_STARTUP_STWSEN_SHIFT                      25                                   /**< Shift value for MSC_STWSEN                  */
#define _MSC_STARTUP_STWSEN_MASK                       0x2000000UL                          /**< Bit mask for MSC_STWSEN                     */
#define _MSC_STARTUP_STWSEN_DEFAULT                    0x00000001UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_STWSEN_DEFAULT                     (_MSC_STARTUP_STWSEN_DEFAULT << 25)  /**< Shifted mode DEFAULT for MSC_STARTUP        */
#define MSC_STARTUP_STWSAEN                            (0x1UL << 26)                        /**< Startup Waitstates Always Enable            */
#define _MSC_STARTUP_STWSAEN_SHIFT                     26                                   /**< Shift value for MSC_STWSAEN                 */
#define _MSC_STARTUP_STWSAEN_MASK                      0x4000000UL                          /**< Bit mask for MSC_STWSAEN                    */
#define _MSC_STARTUP_STWSAEN_DEFAULT                   0x00000000UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_STWSAEN_DEFAULT                    (_MSC_STARTUP_STWSAEN_DEFAULT << 26) /**< Shifted mode DEFAULT for MSC_STARTUP        */
#define _MSC_STARTUP_STWS_SHIFT                        28                                   /**< Shift value for MSC_STWS                    */
#define _MSC_STARTUP_STWS_MASK                         0x70000000UL                         /**< Bit mask for MSC_STWS                       */
#define _MSC_STARTUP_STWS_DEFAULT                      0x00000002UL                         /**< Mode DEFAULT for MSC_STARTUP                */
#define MSC_STARTUP_STWS_DEFAULT                       (_MSC_STARTUP_STWS_DEFAULT << 28)    /**< Shifted mode DEFAULT for MSC_STARTUP        */

/* Bit fields for MSC SERDATACTRL */
#define _MSC_SERDATACTRL_RESETVALUE                    0x00000000UL                                 /**< Default value for MSC_SERDATACTRL           */
#define _MSC_SERDATACTRL_MASK                          0x00001000UL                                 /**< Mask for MSC_SERDATACTRL                    */
#define MSC_SERDATACTRL_SEDOUTBUFEN                    (0x1UL << 12)                                /**< Flash dout pipeline buffer enable           */
#define _MSC_SERDATACTRL_SEDOUTBUFEN_SHIFT             12                                           /**< Shift value for MSC_SEDOUTBUFEN             */
#define _MSC_SERDATACTRL_SEDOUTBUFEN_MASK              0x1000UL                                     /**< Bit mask for MSC_SEDOUTBUFEN                */
#define _MSC_SERDATACTRL_SEDOUTBUFEN_DEFAULT           0x00000000UL                                 /**< Mode DEFAULT for MSC_SERDATACTRL            */
#define MSC_SERDATACTRL_SEDOUTBUFEN_DEFAULT            (_MSC_SERDATACTRL_SEDOUTBUFEN_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_SERDATACTRL    */

/* Bit fields for MSC FLASHERASETIME */
#define _MSC_FLASHERASETIME_RESETVALUE                 0x27102710UL                              /**< Default value for MSC_FLASHERASETIME        */
#define _MSC_FLASHERASETIME_MASK                       0x7FFF7FFFUL                              /**< Mask for MSC_FLASHERASETIME                 */
#define _MSC_FLASHERASETIME_TERASE_SHIFT               0                                         /**< Shift value for MSC_TERASE                  */
#define _MSC_FLASHERASETIME_TERASE_MASK                0x7FFFUL                                  /**< Bit mask for MSC_TERASE                     */
#define _MSC_FLASHERASETIME_TERASE_DEFAULT             0x00002710UL                              /**< Mode DEFAULT for MSC_FLASHERASETIME         */
#define MSC_FLASHERASETIME_TERASE_DEFAULT              (_MSC_FLASHERASETIME_TERASE_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_FLASHERASETIME */
#define _MSC_FLASHERASETIME_TME_SHIFT                  16                                        /**< Shift value for MSC_TME                     */
#define _MSC_FLASHERASETIME_TME_MASK                   0x7FFF0000UL                              /**< Bit mask for MSC_TME                        */
#define _MSC_FLASHERASETIME_TME_DEFAULT                0x00002710UL                              /**< Mode DEFAULT for MSC_FLASHERASETIME         */
#define MSC_FLASHERASETIME_TME_DEFAULT                 (_MSC_FLASHERASETIME_TME_DEFAULT << 16)   /**< Shifted mode DEFAULT for MSC_FLASHERASETIME */

/* Bit fields for MSC FLASHPROGTIME */
#define _MSC_FLASHPROGTIME_RESETVALUE                  0x12481878UL                               /**< Default value for MSC_FLASHPROGTIME         */
#define _MSC_FLASHPROGTIME_MASK                        0x7FFF1FFFUL                               /**< Mask for MSC_FLASHPROGTIME                  */
#define _MSC_FLASHPROGTIME_TPROG_SHIFT                 0                                          /**< Shift value for MSC_TPROG                   */
#define _MSC_FLASHPROGTIME_TPROG_MASK                  0xFUL                                      /**< Bit mask for MSC_TPROG                      */
#define _MSC_FLASHPROGTIME_TPROG_DEFAULT               0x00000008UL                               /**< Mode DEFAULT for MSC_FLASHPROGTIME          */
#define MSC_FLASHPROGTIME_TPROG_DEFAULT                (_MSC_FLASHPROGTIME_TPROG_DEFAULT << 0)    /**< Shifted mode DEFAULT for MSC_FLASHPROGTIME  */
#define _MSC_FLASHPROGTIME_TXLPW_SHIFT                 4                                          /**< Shift value for MSC_TXLPW                   */
#define _MSC_FLASHPROGTIME_TXLPW_MASK                  0xF0UL                                     /**< Bit mask for MSC_TXLPW                      */
#define _MSC_FLASHPROGTIME_TXLPW_DEFAULT               0x00000007UL                               /**< Mode DEFAULT for MSC_FLASHPROGTIME          */
#define MSC_FLASHPROGTIME_TXLPW_DEFAULT                (_MSC_FLASHPROGTIME_TXLPW_DEFAULT << 4)    /**< Shifted mode DEFAULT for MSC_FLASHPROGTIME  */
#define _MSC_FLASHPROGTIME_TIMEBASE_SHIFT              8                                          /**< Shift value for MSC_TIMEBASE                */
#define _MSC_FLASHPROGTIME_TIMEBASE_MASK               0x1F00UL                                   /**< Bit mask for MSC_TIMEBASE                   */
#define _MSC_FLASHPROGTIME_TIMEBASE_DEFAULT            0x00000018UL                               /**< Mode DEFAULT for MSC_FLASHPROGTIME          */
#define MSC_FLASHPROGTIME_TIMEBASE_DEFAULT             (_MSC_FLASHPROGTIME_TIMEBASE_DEFAULT << 8) /**< Shifted mode DEFAULT for MSC_FLASHPROGTIME  */
#define _MSC_FLASHPROGTIME_THV_SHIFT                   16                                         /**< Shift value for MSC_THV                     */
#define _MSC_FLASHPROGTIME_THV_MASK                    0x7FFF0000UL                               /**< Bit mask for MSC_THV                        */
#define _MSC_FLASHPROGTIME_THV_DEFAULT                 0x00001248UL                               /**< Mode DEFAULT for MSC_FLASHPROGTIME          */
#define MSC_FLASHPROGTIME_THV_DEFAULT                  (_MSC_FLASHPROGTIME_THV_DEFAULT << 16)     /**< Shifted mode DEFAULT for MSC_FLASHPROGTIME  */

/* Bit fields for MSC SELOCK */
#define _MSC_SELOCK_RESETVALUE                         0x00000000UL                         /**< Default value for MSC_SELOCK                */
#define _MSC_SELOCK_MASK                               0x0000FFFFUL                         /**< Mask for MSC_SELOCK                         */
#define _MSC_SELOCK_SELOCKKEY_SHIFT                    0                                    /**< Shift value for MSC_SELOCKKEY               */
#define _MSC_SELOCK_SELOCKKEY_MASK                     0xFFFFUL                             /**< Bit mask for MSC_SELOCKKEY                  */
#define _MSC_SELOCK_SELOCKKEY_DEFAULT                  0x00000000UL                         /**< Mode DEFAULT for MSC_SELOCK                 */
#define _MSC_SELOCK_SELOCKKEY_LOCK                     0x00000000UL                         /**< Mode LOCK for MSC_SELOCK                    */
#define _MSC_SELOCK_SELOCKKEY_UNLOCK                   0x0000A3DEUL                         /**< Mode UNLOCK for MSC_SELOCK                  */
#define MSC_SELOCK_SELOCKKEY_DEFAULT                   (_MSC_SELOCK_SELOCKKEY_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_SELOCK         */
#define MSC_SELOCK_SELOCKKEY_LOCK                      (_MSC_SELOCK_SELOCKKEY_LOCK << 0)    /**< Shifted mode LOCK for MSC_SELOCK            */
#define MSC_SELOCK_SELOCKKEY_UNLOCK                    (_MSC_SELOCK_SELOCKKEY_UNLOCK << 0)  /**< Shifted mode UNLOCK for MSC_SELOCK          */

/* Bit fields for MSC PAGELOCKWORD0 */
#define _MSC_PAGELOCKWORD0_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD0         */
#define _MSC_PAGELOCKWORD0_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD0                  */
#define _MSC_PAGELOCKWORD0_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD0_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD0_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD0          */
#define MSC_PAGELOCKWORD0_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD0_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD0  */

/* Bit fields for MSC PAGELOCKWORD1 */
#define _MSC_PAGELOCKWORD1_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD1         */
#define _MSC_PAGELOCKWORD1_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD1                  */
#define _MSC_PAGELOCKWORD1_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD1_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD1_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD1          */
#define MSC_PAGELOCKWORD1_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD1_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD1  */

/* Bit fields for MSC PAGELOCKWORD2 */
#define _MSC_PAGELOCKWORD2_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD2         */
#define _MSC_PAGELOCKWORD2_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD2                  */
#define _MSC_PAGELOCKWORD2_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD2_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD2_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD2          */
#define MSC_PAGELOCKWORD2_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD2_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD2  */

/* Bit fields for MSC PAGELOCKWORD3 */
#define _MSC_PAGELOCKWORD3_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD3         */
#define _MSC_PAGELOCKWORD3_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD3                  */
#define _MSC_PAGELOCKWORD3_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD3_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD3_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD3          */
#define MSC_PAGELOCKWORD3_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD3_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD3  */

/* Bit fields for MSC PAGELOCKWORD4 */
#define _MSC_PAGELOCKWORD4_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD4         */
#define _MSC_PAGELOCKWORD4_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD4                  */
#define _MSC_PAGELOCKWORD4_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD4_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD4_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD4          */
#define MSC_PAGELOCKWORD4_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD4_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD4  */

/* Bit fields for MSC PAGELOCKWORD5 */
#define _MSC_PAGELOCKWORD5_RESETVALUE                  0x00000000UL                              /**< Default value for MSC_PAGELOCKWORD5         */
#define _MSC_PAGELOCKWORD5_MASK                        0xFFFFFFFFUL                              /**< Mask for MSC_PAGELOCKWORD5                  */
#define _MSC_PAGELOCKWORD5_LOCKBIT_SHIFT               0                                         /**< Shift value for MSC_LOCKBIT                 */
#define _MSC_PAGELOCKWORD5_LOCKBIT_MASK                0xFFFFFFFFUL                              /**< Bit mask for MSC_LOCKBIT                    */
#define _MSC_PAGELOCKWORD5_LOCKBIT_DEFAULT             0x00000000UL                              /**< Mode DEFAULT for MSC_PAGELOCKWORD5          */
#define MSC_PAGELOCKWORD5_LOCKBIT_DEFAULT              (_MSC_PAGELOCKWORD5_LOCKBIT_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_PAGELOCKWORD5  */

/* Bit fields for MSC REPADDR0 */
#define _MSC_REPADDR0_RESETVALUE                       0x00000001UL                            /**< Default value for MSC_REPADDR0              */
#define _MSC_REPADDR0_MASK                             0x0000FFFFUL                            /**< Mask for MSC_REPADDR0                       */
#define MSC_REPADDR0_REPINVALID                        (0x1UL << 0)                            /**< Repair Addr Invalid Flag                    */
#define _MSC_REPADDR0_REPINVALID_SHIFT                 0                                       /**< Shift value for MSC_REPINVALID              */
#define _MSC_REPADDR0_REPINVALID_MASK                  0x1UL                                   /**< Bit mask for MSC_REPINVALID                 */
#define _MSC_REPADDR0_REPINVALID_DEFAULT               0x00000001UL                            /**< Mode DEFAULT for MSC_REPADDR0               */
#define MSC_REPADDR0_REPINVALID_DEFAULT                (_MSC_REPADDR0_REPINVALID_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_REPADDR0       */
#define _MSC_REPADDR0_REPADDR_SHIFT                    1                                       /**< Shift value for MSC_REPADDR                 */
#define _MSC_REPADDR0_REPADDR_MASK                     0xFFFEUL                                /**< Bit mask for MSC_REPADDR                    */
#define _MSC_REPADDR0_REPADDR_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for MSC_REPADDR0               */
#define MSC_REPADDR0_REPADDR_DEFAULT                   (_MSC_REPADDR0_REPADDR_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_REPADDR0       */

/* Bit fields for MSC REPADDR1 */
#define _MSC_REPADDR1_RESETVALUE                       0x00000001UL                            /**< Default value for MSC_REPADDR1              */
#define _MSC_REPADDR1_MASK                             0x0000FFFFUL                            /**< Mask for MSC_REPADDR1                       */
#define MSC_REPADDR1_REPINVALID                        (0x1UL << 0)                            /**< Repair Addr Invalid Flag                    */
#define _MSC_REPADDR1_REPINVALID_SHIFT                 0                                       /**< Shift value for MSC_REPINVALID              */
#define _MSC_REPADDR1_REPINVALID_MASK                  0x1UL                                   /**< Bit mask for MSC_REPINVALID                 */
#define _MSC_REPADDR1_REPINVALID_DEFAULT               0x00000001UL                            /**< Mode DEFAULT for MSC_REPADDR1               */
#define MSC_REPADDR1_REPINVALID_DEFAULT                (_MSC_REPADDR1_REPINVALID_DEFAULT << 0) /**< Shifted mode DEFAULT for MSC_REPADDR1       */
#define _MSC_REPADDR1_REPADDR_SHIFT                    1                                       /**< Shift value for MSC_REPADDR                 */
#define _MSC_REPADDR1_REPADDR_MASK                     0xFFFEUL                                /**< Bit mask for MSC_REPADDR                    */
#define _MSC_REPADDR1_REPADDR_DEFAULT                  0x00000000UL                            /**< Mode DEFAULT for MSC_REPADDR1               */
#define MSC_REPADDR1_REPADDR_DEFAULT                   (_MSC_REPADDR1_REPADDR_DEFAULT << 1)    /**< Shifted mode DEFAULT for MSC_REPADDR1       */

/* Bit fields for MSC RPURATD0 */
#define _MSC_RPURATD0_RESETVALUE                       0x00000000UL                                      /**< Default value for MSC_RPURATD0              */
#define _MSC_RPURATD0_MASK                             0x0011C37EUL                                      /**< Mask for MSC_RPURATD0                       */
#define MSC_RPURATD0_RATDMSCREADCTRL                   (0x1UL << 1)                                      /**< READCTRL Protection Bit                     */
#define _MSC_RPURATD0_RATDMSCREADCTRL_SHIFT            1                                                 /**< Shift value for MSC_RATDMSCREADCTRL         */
#define _MSC_RPURATD0_RATDMSCREADCTRL_MASK             0x2UL                                             /**< Bit mask for MSC_RATDMSCREADCTRL            */
#define _MSC_RPURATD0_RATDMSCREADCTRL_DEFAULT          0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCREADCTRL_DEFAULT           (_MSC_RPURATD0_RATDMSCREADCTRL_DEFAULT << 1)      /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCRDATACTRL                  (0x1UL << 2)                                      /**< RDATACTRL Protection Bit                    */
#define _MSC_RPURATD0_RATDMSCRDATACTRL_SHIFT           2                                                 /**< Shift value for MSC_RATDMSCRDATACTRL        */
#define _MSC_RPURATD0_RATDMSCRDATACTRL_MASK            0x4UL                                             /**< Bit mask for MSC_RATDMSCRDATACTRL           */
#define _MSC_RPURATD0_RATDMSCRDATACTRL_DEFAULT         0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCRDATACTRL_DEFAULT          (_MSC_RPURATD0_RATDMSCRDATACTRL_DEFAULT << 2)     /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCWRITECTRL                  (0x1UL << 3)                                      /**< WRITECTRL Protection Bit                    */
#define _MSC_RPURATD0_RATDMSCWRITECTRL_SHIFT           3                                                 /**< Shift value for MSC_RATDMSCWRITECTRL        */
#define _MSC_RPURATD0_RATDMSCWRITECTRL_MASK            0x8UL                                             /**< Bit mask for MSC_RATDMSCWRITECTRL           */
#define _MSC_RPURATD0_RATDMSCWRITECTRL_DEFAULT         0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCWRITECTRL_DEFAULT          (_MSC_RPURATD0_RATDMSCWRITECTRL_DEFAULT << 3)     /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCWRITECMD                   (0x1UL << 4)                                      /**< WRITECMD Protection Bit                     */
#define _MSC_RPURATD0_RATDMSCWRITECMD_SHIFT            4                                                 /**< Shift value for MSC_RATDMSCWRITECMD         */
#define _MSC_RPURATD0_RATDMSCWRITECMD_MASK             0x10UL                                            /**< Bit mask for MSC_RATDMSCWRITECMD            */
#define _MSC_RPURATD0_RATDMSCWRITECMD_DEFAULT          0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCWRITECMD_DEFAULT           (_MSC_RPURATD0_RATDMSCWRITECMD_DEFAULT << 4)      /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCADDRB                      (0x1UL << 5)                                      /**< ADDRB Protection Bit                        */
#define _MSC_RPURATD0_RATDMSCADDRB_SHIFT               5                                                 /**< Shift value for MSC_RATDMSCADDRB            */
#define _MSC_RPURATD0_RATDMSCADDRB_MASK                0x20UL                                            /**< Bit mask for MSC_RATDMSCADDRB               */
#define _MSC_RPURATD0_RATDMSCADDRB_DEFAULT             0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCADDRB_DEFAULT              (_MSC_RPURATD0_RATDMSCADDRB_DEFAULT << 5)         /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCWDATA                      (0x1UL << 6)                                      /**< WDATA Protection Bit                        */
#define _MSC_RPURATD0_RATDMSCWDATA_SHIFT               6                                                 /**< Shift value for MSC_RATDMSCWDATA            */
#define _MSC_RPURATD0_RATDMSCWDATA_MASK                0x40UL                                            /**< Bit mask for MSC_RATDMSCWDATA               */
#define _MSC_RPURATD0_RATDMSCWDATA_DEFAULT             0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCWDATA_DEFAULT              (_MSC_RPURATD0_RATDMSCWDATA_DEFAULT << 6)         /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCIF                         (0x1UL << 8)                                      /**< IF Protection Bit                           */
#define _MSC_RPURATD0_RATDMSCIF_SHIFT                  8                                                 /**< Shift value for MSC_RATDMSCIF               */
#define _MSC_RPURATD0_RATDMSCIF_MASK                   0x100UL                                           /**< Bit mask for MSC_RATDMSCIF                  */
#define _MSC_RPURATD0_RATDMSCIF_DEFAULT                0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCIF_DEFAULT                 (_MSC_RPURATD0_RATDMSCIF_DEFAULT << 8)            /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCIEN                        (0x1UL << 9)                                      /**< IEN Protection Bit                          */
#define _MSC_RPURATD0_RATDMSCIEN_SHIFT                 9                                                 /**< Shift value for MSC_RATDMSCIEN              */
#define _MSC_RPURATD0_RATDMSCIEN_MASK                  0x200UL                                           /**< Bit mask for MSC_RATDMSCIEN                 */
#define _MSC_RPURATD0_RATDMSCIEN_DEFAULT               0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCIEN_DEFAULT                (_MSC_RPURATD0_RATDMSCIEN_DEFAULT << 9)           /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCCMD                        (0x1UL << 14)                                     /**< CMD Protection Bit                          */
#define _MSC_RPURATD0_RATDMSCCMD_SHIFT                 14                                                /**< Shift value for MSC_RATDMSCCMD              */
#define _MSC_RPURATD0_RATDMSCCMD_MASK                  0x4000UL                                          /**< Bit mask for MSC_RATDMSCCMD                 */
#define _MSC_RPURATD0_RATDMSCCMD_DEFAULT               0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCCMD_DEFAULT                (_MSC_RPURATD0_RATDMSCCMD_DEFAULT << 14)          /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCLOCK                       (0x1UL << 15)                                     /**< LOCK Protection Bit                         */
#define _MSC_RPURATD0_RATDMSCLOCK_SHIFT                15                                                /**< Shift value for MSC_RATDMSCLOCK             */
#define _MSC_RPURATD0_RATDMSCLOCK_MASK                 0x8000UL                                          /**< Bit mask for MSC_RATDMSCLOCK                */
#define _MSC_RPURATD0_RATDMSCLOCK_DEFAULT              0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCLOCK_DEFAULT               (_MSC_RPURATD0_RATDMSCLOCK_DEFAULT << 15)         /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCMISCLOCKWORD               (0x1UL << 16)                                     /**< MISCLOCKWORD Protection Bit                 */
#define _MSC_RPURATD0_RATDMSCMISCLOCKWORD_SHIFT        16                                                /**< Shift value for MSC_RATDMSCMISCLOCKWORD     */
#define _MSC_RPURATD0_RATDMSCMISCLOCKWORD_MASK         0x10000UL                                         /**< Bit mask for MSC_RATDMSCMISCLOCKWORD        */
#define _MSC_RPURATD0_RATDMSCMISCLOCKWORD_DEFAULT      0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCMISCLOCKWORD_DEFAULT       (_MSC_RPURATD0_RATDMSCMISCLOCKWORD_DEFAULT << 16) /**< Shifted mode DEFAULT for MSC_RPURATD0       */
#define MSC_RPURATD0_RATDMSCPWRCTRL                    (0x1UL << 20)                                     /**< PWRCTRL Protection Bit                      */
#define _MSC_RPURATD0_RATDMSCPWRCTRL_SHIFT             20                                                /**< Shift value for MSC_RATDMSCPWRCTRL          */
#define _MSC_RPURATD0_RATDMSCPWRCTRL_MASK              0x100000UL                                        /**< Bit mask for MSC_RATDMSCPWRCTRL             */
#define _MSC_RPURATD0_RATDMSCPWRCTRL_DEFAULT           0x00000000UL                                      /**< Mode DEFAULT for MSC_RPURATD0               */
#define MSC_RPURATD0_RATDMSCPWRCTRL_DEFAULT            (_MSC_RPURATD0_RATDMSCPWRCTRL_DEFAULT << 20)      /**< Shifted mode DEFAULT for MSC_RPURATD0       */

/* Bit fields for MSC RPURATD1 */
#define _MSC_RPURATD1_RESETVALUE                       0x00000000UL                                        /**< Default value for MSC_RPURATD1              */
#define _MSC_RPURATD1_MASK                             0x00073FEFUL                                        /**< Mask for MSC_RPURATD1                       */
#define MSC_RPURATD1_RATDMSCSEWRITECTRL                (0x1UL << 0)                                        /**< SEWRITECTRL Protection Bit                  */
#define _MSC_RPURATD1_RATDMSCSEWRITECTRL_SHIFT         0                                                   /**< Shift value for MSC_RATDMSCSEWRITECTRL      */
#define _MSC_RPURATD1_RATDMSCSEWRITECTRL_MASK          0x1UL                                               /**< Bit mask for MSC_RATDMSCSEWRITECTRL         */
#define _MSC_RPURATD1_RATDMSCSEWRITECTRL_DEFAULT       0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEWRITECTRL_DEFAULT        (_MSC_RPURATD1_RATDMSCSEWRITECTRL_DEFAULT << 0)     /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEWRITECMD                 (0x1UL << 1)                                        /**< SEWRITECMD Protection Bit                   */
#define _MSC_RPURATD1_RATDMSCSEWRITECMD_SHIFT          1                                                   /**< Shift value for MSC_RATDMSCSEWRITECMD       */
#define _MSC_RPURATD1_RATDMSCSEWRITECMD_MASK           0x2UL                                               /**< Bit mask for MSC_RATDMSCSEWRITECMD          */
#define _MSC_RPURATD1_RATDMSCSEWRITECMD_DEFAULT        0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEWRITECMD_DEFAULT         (_MSC_RPURATD1_RATDMSCSEWRITECMD_DEFAULT << 1)      /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEADDRB                    (0x1UL << 2)                                        /**< SEADDRB Protection Bit                      */
#define _MSC_RPURATD1_RATDMSCSEADDRB_SHIFT             2                                                   /**< Shift value for MSC_RATDMSCSEADDRB          */
#define _MSC_RPURATD1_RATDMSCSEADDRB_MASK              0x4UL                                               /**< Bit mask for MSC_RATDMSCSEADDRB             */
#define _MSC_RPURATD1_RATDMSCSEADDRB_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEADDRB_DEFAULT            (_MSC_RPURATD1_RATDMSCSEADDRB_DEFAULT << 2)         /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEWDATA                    (0x1UL << 3)                                        /**< SEWDATA Protection Bit                      */
#define _MSC_RPURATD1_RATDMSCSEWDATA_SHIFT             3                                                   /**< Shift value for MSC_RATDMSCSEWDATA          */
#define _MSC_RPURATD1_RATDMSCSEWDATA_MASK              0x8UL                                               /**< Bit mask for MSC_RATDMSCSEWDATA             */
#define _MSC_RPURATD1_RATDMSCSEWDATA_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEWDATA_DEFAULT            (_MSC_RPURATD1_RATDMSCSEWDATA_DEFAULT << 3)         /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEIF                       (0x1UL << 5)                                        /**< SEIF Protection Bit                         */
#define _MSC_RPURATD1_RATDMSCSEIF_SHIFT                5                                                   /**< Shift value for MSC_RATDMSCSEIF             */
#define _MSC_RPURATD1_RATDMSCSEIF_MASK                 0x20UL                                              /**< Bit mask for MSC_RATDMSCSEIF                */
#define _MSC_RPURATD1_RATDMSCSEIF_DEFAULT              0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEIF_DEFAULT               (_MSC_RPURATD1_RATDMSCSEIF_DEFAULT << 5)            /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEIEN                      (0x1UL << 6)                                        /**< SEIEN Protection Bit                        */
#define _MSC_RPURATD1_RATDMSCSEIEN_SHIFT               6                                                   /**< Shift value for MSC_RATDMSCSEIEN            */
#define _MSC_RPURATD1_RATDMSCSEIEN_MASK                0x40UL                                              /**< Bit mask for MSC_RATDMSCSEIEN               */
#define _MSC_RPURATD1_RATDMSCSEIEN_DEFAULT             0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEIEN_DEFAULT              (_MSC_RPURATD1_RATDMSCSEIEN_DEFAULT << 6)           /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCMEMFEATURE                 (0x1UL << 7)                                        /**< MEMFEATURE Protection Bit                   */
#define _MSC_RPURATD1_RATDMSCMEMFEATURE_SHIFT          7                                                   /**< Shift value for MSC_RATDMSCMEMFEATURE       */
#define _MSC_RPURATD1_RATDMSCMEMFEATURE_MASK           0x80UL                                              /**< Bit mask for MSC_RATDMSCMEMFEATURE          */
#define _MSC_RPURATD1_RATDMSCMEMFEATURE_DEFAULT        0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCMEMFEATURE_DEFAULT         (_MSC_RPURATD1_RATDMSCMEMFEATURE_DEFAULT << 7)      /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSTARTUP                    (0x1UL << 8)                                        /**< STARTUP Protection Bit                      */
#define _MSC_RPURATD1_RATDMSCSTARTUP_SHIFT             8                                                   /**< Shift value for MSC_RATDMSCSTARTUP          */
#define _MSC_RPURATD1_RATDMSCSTARTUP_MASK              0x100UL                                             /**< Bit mask for MSC_RATDMSCSTARTUP             */
#define _MSC_RPURATD1_RATDMSCSTARTUP_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSTARTUP_DEFAULT            (_MSC_RPURATD1_RATDMSCSTARTUP_DEFAULT << 8)         /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSERDATACTRL                (0x1UL << 9)                                        /**< SERDATACTRL Protection Bit                  */
#define _MSC_RPURATD1_RATDMSCSERDATACTRL_SHIFT         9                                                   /**< Shift value for MSC_RATDMSCSERDATACTRL      */
#define _MSC_RPURATD1_RATDMSCSERDATACTRL_MASK          0x200UL                                             /**< Bit mask for MSC_RATDMSCSERDATACTRL         */
#define _MSC_RPURATD1_RATDMSCSERDATACTRL_DEFAULT       0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSERDATACTRL_DEFAULT        (_MSC_RPURATD1_RATDMSCSERDATACTRL_DEFAULT << 9)     /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSEPWRSKIP                  (0x1UL << 10)                                       /**< SEPWRSKIP Protection Bit                    */
#define _MSC_RPURATD1_RATDMSCSEPWRSKIP_SHIFT           10                                                  /**< Shift value for MSC_RATDMSCSEPWRSKIP        */
#define _MSC_RPURATD1_RATDMSCSEPWRSKIP_MASK            0x400UL                                             /**< Bit mask for MSC_RATDMSCSEPWRSKIP           */
#define _MSC_RPURATD1_RATDMSCSEPWRSKIP_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSEPWRSKIP_DEFAULT          (_MSC_RPURATD1_RATDMSCSEPWRSKIP_DEFAULT << 10)      /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCMTPCTRL                    (0x1UL << 11)                                       /**< MTPCTRL Protection Bit                      */
#define _MSC_RPURATD1_RATDMSCMTPCTRL_SHIFT             11                                                  /**< Shift value for MSC_RATDMSCMTPCTRL          */
#define _MSC_RPURATD1_RATDMSCMTPCTRL_MASK              0x800UL                                             /**< Bit mask for MSC_RATDMSCMTPCTRL             */
#define _MSC_RPURATD1_RATDMSCMTPCTRL_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCMTPCTRL_DEFAULT            (_MSC_RPURATD1_RATDMSCMTPCTRL_DEFAULT << 11)        /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCMTPSIZE                    (0x1UL << 12)                                       /**< MTPSIZE Protection Bit                      */
#define _MSC_RPURATD1_RATDMSCMTPSIZE_SHIFT             12                                                  /**< Shift value for MSC_RATDMSCMTPSIZE          */
#define _MSC_RPURATD1_RATDMSCMTPSIZE_MASK              0x1000UL                                            /**< Bit mask for MSC_RATDMSCMTPSIZE             */
#define _MSC_RPURATD1_RATDMSCMTPSIZE_DEFAULT           0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCMTPSIZE_DEFAULT            (_MSC_RPURATD1_RATDMSCMTPSIZE_DEFAULT << 12)        /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCOTPERASE                   (0x1UL << 13)                                       /**< OTPERASE Protection Bit                     */
#define _MSC_RPURATD1_RATDMSCOTPERASE_SHIFT            13                                                  /**< Shift value for MSC_RATDMSCOTPERASE         */
#define _MSC_RPURATD1_RATDMSCOTPERASE_MASK             0x2000UL                                            /**< Bit mask for MSC_RATDMSCOTPERASE            */
#define _MSC_RPURATD1_RATDMSCOTPERASE_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCOTPERASE_DEFAULT           (_MSC_RPURATD1_RATDMSCOTPERASE_DEFAULT << 13)       /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCFLASHERASETIME             (0x1UL << 16)                                       /**< FLASHERASETIME Protection Bit               */
#define _MSC_RPURATD1_RATDMSCFLASHERASETIME_SHIFT      16                                                  /**< Shift value for MSC_RATDMSCFLASHERASETIME   */
#define _MSC_RPURATD1_RATDMSCFLASHERASETIME_MASK       0x10000UL                                           /**< Bit mask for MSC_RATDMSCFLASHERASETIME      */
#define _MSC_RPURATD1_RATDMSCFLASHERASETIME_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCFLASHERASETIME_DEFAULT     (_MSC_RPURATD1_RATDMSCFLASHERASETIME_DEFAULT << 16) /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCFLASHPROGTIME              (0x1UL << 17)                                       /**< FLASHPROGTIME Protection Bit                */
#define _MSC_RPURATD1_RATDMSCFLASHPROGTIME_SHIFT       17                                                  /**< Shift value for MSC_RATDMSCFLASHPROGTIME    */
#define _MSC_RPURATD1_RATDMSCFLASHPROGTIME_MASK        0x20000UL                                           /**< Bit mask for MSC_RATDMSCFLASHPROGTIME       */
#define _MSC_RPURATD1_RATDMSCFLASHPROGTIME_DEFAULT     0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCFLASHPROGTIME_DEFAULT      (_MSC_RPURATD1_RATDMSCFLASHPROGTIME_DEFAULT << 17)  /**< Shifted mode DEFAULT for MSC_RPURATD1       */
#define MSC_RPURATD1_RATDMSCSELOCK                     (0x1UL << 18)                                       /**< SELOCK Protection Bit                       */
#define _MSC_RPURATD1_RATDMSCSELOCK_SHIFT              18                                                  /**< Shift value for MSC_RATDMSCSELOCK           */
#define _MSC_RPURATD1_RATDMSCSELOCK_MASK               0x40000UL                                           /**< Bit mask for MSC_RATDMSCSELOCK              */
#define _MSC_RPURATD1_RATDMSCSELOCK_DEFAULT            0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD1               */
#define MSC_RPURATD1_RATDMSCSELOCK_DEFAULT             (_MSC_RPURATD1_RATDMSCSELOCK_DEFAULT << 18)         /**< Shifted mode DEFAULT for MSC_RPURATD1       */

/* Bit fields for MSC RPURATD2 */
#define _MSC_RPURATD2_RESETVALUE                       0x00000000UL                                        /**< Default value for MSC_RPURATD2              */
#define _MSC_RPURATD2_MASK                             0x00033F00UL                                        /**< Mask for MSC_RPURATD2                       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD0             (0x1UL << 8)                                        /**< PAGELOCKWORD0 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD0_SHIFT      8                                                   /**< Shift value for MSC_RATDINSTPAGELOCKWORD0   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD0_MASK       0x100UL                                             /**< Bit mask for MSC_RATDINSTPAGELOCKWORD0      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD0_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD0_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD0_DEFAULT << 8)  /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD1             (0x1UL << 9)                                        /**< PAGELOCKWORD1 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD1_SHIFT      9                                                   /**< Shift value for MSC_RATDINSTPAGELOCKWORD1   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD1_MASK       0x200UL                                             /**< Bit mask for MSC_RATDINSTPAGELOCKWORD1      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD1_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD1_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD1_DEFAULT << 9)  /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD2             (0x1UL << 10)                                       /**< PAGELOCKWORD2 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD2_SHIFT      10                                                  /**< Shift value for MSC_RATDINSTPAGELOCKWORD2   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD2_MASK       0x400UL                                             /**< Bit mask for MSC_RATDINSTPAGELOCKWORD2      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD2_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD2_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD2_DEFAULT << 10) /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD3             (0x1UL << 11)                                       /**< PAGELOCKWORD3 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD3_SHIFT      11                                                  /**< Shift value for MSC_RATDINSTPAGELOCKWORD3   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD3_MASK       0x800UL                                             /**< Bit mask for MSC_RATDINSTPAGELOCKWORD3      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD3_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD3_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD3_DEFAULT << 11) /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD4             (0x1UL << 12)                                       /**< PAGELOCKWORD4 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD4_SHIFT      12                                                  /**< Shift value for MSC_RATDINSTPAGELOCKWORD4   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD4_MASK       0x1000UL                                            /**< Bit mask for MSC_RATDINSTPAGELOCKWORD4      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD4_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD4_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD4_DEFAULT << 12) /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD5             (0x1UL << 13)                                       /**< PAGELOCKWORD5 Protection Bit                */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD5_SHIFT      13                                                  /**< Shift value for MSC_RATDINSTPAGELOCKWORD5   */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD5_MASK       0x2000UL                                            /**< Bit mask for MSC_RATDINSTPAGELOCKWORD5      */
#define _MSC_RPURATD2_RATDINSTPAGELOCKWORD5_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTPAGELOCKWORD5_DEFAULT     (_MSC_RPURATD2_RATDINSTPAGELOCKWORD5_DEFAULT << 13) /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTREPADDR0                  (0x1UL << 16)                                       /**< REPADDR0 Protection Bit                     */
#define _MSC_RPURATD2_RATDINSTREPADDR0_SHIFT           16                                                  /**< Shift value for MSC_RATDINSTREPADDR0        */
#define _MSC_RPURATD2_RATDINSTREPADDR0_MASK            0x10000UL                                           /**< Bit mask for MSC_RATDINSTREPADDR0           */
#define _MSC_RPURATD2_RATDINSTREPADDR0_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTREPADDR0_DEFAULT          (_MSC_RPURATD2_RATDINSTREPADDR0_DEFAULT << 16)      /**< Shifted mode DEFAULT for MSC_RPURATD2       */
#define MSC_RPURATD2_RATDINSTREPADDR1                  (0x1UL << 17)                                       /**< REPADDR1 Protection Bit                     */
#define _MSC_RPURATD2_RATDINSTREPADDR1_SHIFT           17                                                  /**< Shift value for MSC_RATDINSTREPADDR1        */
#define _MSC_RPURATD2_RATDINSTREPADDR1_MASK            0x20000UL                                           /**< Bit mask for MSC_RATDINSTREPADDR1           */
#define _MSC_RPURATD2_RATDINSTREPADDR1_DEFAULT         0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD2               */
#define MSC_RPURATD2_RATDINSTREPADDR1_DEFAULT          (_MSC_RPURATD2_RATDINSTREPADDR1_DEFAULT << 17)      /**< Shifted mode DEFAULT for MSC_RPURATD2       */

/* Bit fields for MSC RPURATD3 */
#define _MSC_RPURATD3_RESETVALUE                       0x00000000UL                                        /**< Default value for MSC_RPURATD3              */
#define _MSC_RPURATD3_MASK                             0x00018B00UL                                        /**< Mask for MSC_RPURATD3                       */
#define MSC_RPURATD3_RATDMSCTESTCTRL                   (0x1UL << 8)                                        /**< TESTCTRL Protection Bit                     */
#define _MSC_RPURATD3_RATDMSCTESTCTRL_SHIFT            8                                                   /**< Shift value for MSC_RATDMSCTESTCTRL         */
#define _MSC_RPURATD3_RATDMSCTESTCTRL_MASK             0x100UL                                             /**< Bit mask for MSC_RATDMSCTESTCTRL            */
#define _MSC_RPURATD3_RATDMSCTESTCTRL_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD3               */
#define MSC_RPURATD3_RATDMSCTESTCTRL_DEFAULT           (_MSC_RPURATD3_RATDMSCTESTCTRL_DEFAULT << 8)        /**< Shifted mode DEFAULT for MSC_RPURATD3       */
#define MSC_RPURATD3_RATDMSCPATDIAGCTRL                (0x1UL << 9)                                        /**< PATDIAGCTRL Protection Bit                  */
#define _MSC_RPURATD3_RATDMSCPATDIAGCTRL_SHIFT         9                                                   /**< Shift value for MSC_RATDMSCPATDIAGCTRL      */
#define _MSC_RPURATD3_RATDMSCPATDIAGCTRL_MASK          0x200UL                                             /**< Bit mask for MSC_RATDMSCPATDIAGCTRL         */
#define _MSC_RPURATD3_RATDMSCPATDIAGCTRL_DEFAULT       0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD3               */
#define MSC_RPURATD3_RATDMSCPATDIAGCTRL_DEFAULT        (_MSC_RPURATD3_RATDMSCPATDIAGCTRL_DEFAULT << 9)     /**< Shifted mode DEFAULT for MSC_RPURATD3       */
#define MSC_RPURATD3_RATDMSCPATDONEADDR                (0x1UL << 11)                                       /**< PATDONEADDR Protection Bit                  */
#define _MSC_RPURATD3_RATDMSCPATDONEADDR_SHIFT         11                                                  /**< Shift value for MSC_RATDMSCPATDONEADDR      */
#define _MSC_RPURATD3_RATDMSCPATDONEADDR_MASK          0x800UL                                             /**< Bit mask for MSC_RATDMSCPATDONEADDR         */
#define _MSC_RPURATD3_RATDMSCPATDONEADDR_DEFAULT       0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD3               */
#define MSC_RPURATD3_RATDMSCPATDONEADDR_DEFAULT        (_MSC_RPURATD3_RATDMSCPATDONEADDR_DEFAULT << 11)    /**< Shifted mode DEFAULT for MSC_RPURATD3       */
#define MSC_RPURATD3_RATDMSCTESTREDUNDANCY             (0x1UL << 15)                                       /**< TESTREDUNDANCY Protection Bit               */
#define _MSC_RPURATD3_RATDMSCTESTREDUNDANCY_SHIFT      15                                                  /**< Shift value for MSC_RATDMSCTESTREDUNDANCY   */
#define _MSC_RPURATD3_RATDMSCTESTREDUNDANCY_MASK       0x8000UL                                            /**< Bit mask for MSC_RATDMSCTESTREDUNDANCY      */
#define _MSC_RPURATD3_RATDMSCTESTREDUNDANCY_DEFAULT    0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD3               */
#define MSC_RPURATD3_RATDMSCTESTREDUNDANCY_DEFAULT     (_MSC_RPURATD3_RATDMSCTESTREDUNDANCY_DEFAULT << 15) /**< Shifted mode DEFAULT for MSC_RPURATD3       */
#define MSC_RPURATD3_RATDMSCTESTLOCK                   (0x1UL << 16)                                       /**< TESTLOCK Protection Bit                     */
#define _MSC_RPURATD3_RATDMSCTESTLOCK_SHIFT            16                                                  /**< Shift value for MSC_RATDMSCTESTLOCK         */
#define _MSC_RPURATD3_RATDMSCTESTLOCK_MASK             0x10000UL                                           /**< Bit mask for MSC_RATDMSCTESTLOCK            */
#define _MSC_RPURATD3_RATDMSCTESTLOCK_DEFAULT          0x00000000UL                                        /**< Mode DEFAULT for MSC_RPURATD3               */
#define MSC_RPURATD3_RATDMSCTESTLOCK_DEFAULT           (_MSC_RPURATD3_RATDMSCTESTLOCK_DEFAULT << 16)       /**< Shifted mode DEFAULT for MSC_RPURATD3       */

/** @} End of group MGM24_MSC_BitFields */
/** @} End of group MGM24_MSC */
/** @} End of group Parts */

#endif /* MGM24_MSC_H */
