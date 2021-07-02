/***************************************************************************//**
 * @file
 * @brief Configuration header for bootloader Spi Slave Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef BTL_SPI_MASTER_DRIVER_CONFIG_H
#define BTL_SPI_MASTER_DRIVER_CONFIG_H

// <o SL_EXTFLASH_FREQUENCY> Frequency 
// <i> Default: 6400000
#define SL_EXTFLASH_FREQUENCY           6400000

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX,CLK,(CS)> SL_EXTFLASH
// $[USART_SL_EXTFLASH]
#define SL_EXTFLASH_PERIPHERAL                   USART0
#define SL_EXTFLASH_PERIPHERAL_NO                0

// USART0 TX on PB11
#define SL_EXTFLASH_TX_PORT                      gpioPortB
#define SL_EXTFLASH_TX_PIN                       11
#define SL_EXTFLASH_TX_LOC                       6

// USART0 RX on PB12
#define SL_EXTFLASH_RX_PORT                      gpioPortB
#define SL_EXTFLASH_RX_PIN                       12
#define SL_EXTFLASH_RX_LOC                       6

// USART0 CLK on PB13
#define SL_EXTFLASH_CLK_PORT                     gpioPortB
#define SL_EXTFLASH_CLK_PIN                      13
#define SL_EXTFLASH_CLK_LOC                      6

// USART0 CS on PD13
#define SL_EXTFLASH_CS_PORT                      gpioPortD
#define SL_EXTFLASH_CS_PIN                       13
#define SL_EXTFLASH_CS_LOC                       18

// [USART_SL_EXTFLASH]$

// <gpio> SL_EXTFLASH_WP
// $[GPIO_SL_EXTFLASH_WP]

// [GPIO_SL_EXTFLASH_WP]$

// <gpio> SL_EXTFLASH_HOLD
// $[GPIO_SL_EXTFLASH_HOLD]

// [GPIO_SL_EXTFLASH_HOLD]$

// <<< sl:end pin_tool >>>

#endif // BTL_SPI_MASTER_DRIVER_CONFIG_H
