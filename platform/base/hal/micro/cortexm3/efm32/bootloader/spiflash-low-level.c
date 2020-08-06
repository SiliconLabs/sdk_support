/***************************************************************************//**
 * @file
 * @brief This is the efm specific spiflash-class1.c that provides
 *              device specific implementation of the spiflash that
 *              changes between parts.
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
/*
 * When SPI_FLASH_SC1 is defined, serial controller one will be used to
 * communicate with the external flash.
 * - This must be enabled in the case of app bootloading over USB, since USB
 *   uses SC2. Also ensure that the board jumpers are in the right place and
 *   the debugger is not connected to any SC1 pins.
 * - This must be enabled in the case of PRO2+-connected devices since SC2
 *   is used to interact with the PRO2+ radio.
 */

#include PLATFORM_HEADER
#include "hal/micro/micro.h"
#include "hal/micro/cortexm3/memmap.h"
#include "hal-config.h"

#include "spiflash-low-level.h"

//// abstract away which pins and serial controller are being used
//#include "external-flash-gpio-select.h"

#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"

#if BSP_EXTFLASH_USART == HAL_SPI_PORT_USART0
#define SPIFLASH_USART          USART0
#define SPIFLASH_USART_CLOCK    cmuClock_USART0
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART1
#define SPIFLASH_USART          USART1
#define SPIFLASH_USART_CLOCK    cmuClock_USART1
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART2
#define SPIFLASH_USART          USART2
#define SPIFLASH_USART_CLOCK    cmuClock_USART2
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART3
#define SPIFLASH_USART          USART3
#define SPIFLASH_USART_CLOCK    cmuClock_USART3
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART4
#define SPIFLASH_USART          USART4
#define SPIFLASH_USART_CLOCK    cmuClock_USART4
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART5
#define SPIFLASH_USART          USART5
#define SPIFLASH_USART_CLOCK    cmuClock_USART5
#elif BSP_EXTFLASH_USART == HAL_SPI_PORT_USART6
#define SPIFLASH_USART          USART6
#define SPIFLASH_USART_CLOCK    cmuClock_USART6
#else
#error "Invalid BSP_EXTFLASH_USART"
#endif

//
// ~~~~~~~~~~~~~~ Device Specific SPI Routines ~~~~~~~~~~~~~~
//

// WARNING! hardware FIFO is only 2 bytes plus the shift register, so don't push
// more than 3 before popping!

void halSpiPush8(uint8_t txData)
{
  USART_Tx(SPIFLASH_USART, txData);
}

uint8_t halSpiPop8(void)
{
  // WARNING!  spiPop8 must be matched 1:1 with spiPush8 calls made first
  //  or else this could spin forever!!
  return USART_Rx(SPIFLASH_USART);
}

#ifndef BSP_EXTFLASH_CS_ACTIVE
#define BSP_EXTFLASH_CS_ACTIVE()              GPIO_PinOutClear(BSP_EXTFLASH_CS_PORT, BSP_EXTFLASH_CS_PIN)
#endif
#ifndef BSP_EXTFLASH_CS_INACTIVE
#define BSP_EXTFLASH_CS_INACTIVE()            GPIO_PinOutSet(BSP_EXTFLASH_CS_PORT, BSP_EXTFLASH_CS_PIN)
#endif

#ifndef HAL_EXTFLASH_USART_BAUDRATE
  #define HAL_EXTFLASH_USART_BAUDRATE          6400000U
#else
  #if (HAL_EXTFLASH_USART_BAUDRATE          > 9000000)
    #warning Baudrate over 9000000 can have issues on some chips due to MISO setup time
  #elif (HAL_EXTFLASH_USART_BAUDRATE          <= 0)
    #error Can't have baudrate of 0 or below
  #endif
#endif

// default PA4 for power pin

#if defined(EEPROM_USES_SHUTDOWN_CONTROL)

// Default to PA4 when board header doesn't fully define alternative
  #if    !defined(EEPROM_POWER_PORT) \
  || !defined(EEPROM_POWER_PIN)

// Issue warning for partial definitions
    #if    defined(EEPROM_POWER_PORT) \
  || defined(EEPROM_POWER_PIN)

      #error Partial EEPROM enable pin definition. Please define all of \
  CONFIGURE_EEPROM_POWER_PIN, SET_EEPROM_POWER_PIN, and                 \
  CLR_EEPROM_POWER_PIN as funciton-like macros when specifying an       \
  alternate pin.

    #endif

    #define EEPROM_POWER_PORT gpioPortA
    #define EEPROM_POWER_PIN  4

  #endif

  #define CONFIGURE_EEPROM_POWER_PIN()  GPIO_PinModeSet(EEPROM_POWER_PORT, EEPROM_POWER_PIN, gpioModePushPull, 0)
  #define SET_EEPROM_POWER_PIN()        GPIO_PinOutSet(EEPROM_POWER_PORT, EEPROM_POWER_PIN)
  #define CLR_EEPROM_POWER_PIN()        GPIO_PinOutClear(EEPROM_POWER_PORT, EEPROM_POWER_PIN)

#else

// Define empty macros when shutdown control is not used
  #define CONFIGURE_EEPROM_POWER_PIN()            (void)0
  #define SET_EEPROM_POWER_PIN()                  (void)0
  #define CLR_EEPROM_POWER_PIN()                  (void)0

#endif

#if defined(SPIFLASH_CLASS1_DEBUG) && SPIFLASH_CLASS1_DEBUG
  #define SPIFLASH_CLASS1_DEBUG_SETUP()   GPIO_PinModeSet(gpioPortF, 4, gpioModePushPull, 0)
  #define SPIFLASH_CLASS1_DEBUG_TOGGLE()  GPIO_PinToggle(gpioPortF, 4)
  #define SPIFLASH_CLASS1_DEBUG_SET()     GPIO_PinOutSet(gpioPortF, 4)
  #define SPIFLASH_CLASS1_DEBUG_CLEAR()   GPIO_PinOutClear(gpioPortF, 4)
#else
  #define SPIFLASH_CLASS1_DEBUG_SETUP()   (void)0
  #define SPIFLASH_CLASS1_DEBUG_TOGGLE()  (void)0
  #define SPIFLASH_CLASS1_DEBUG_SET()     (void)0
  #define SPIFLASH_CLASS1_DEBUG_CLEAR()   (void)0
#endif

//
//  ~~~~~~~~~~~ Device Specific Eeprom Functions ~~~~~~~~~~~
//

void setFlashCSActive(void)
{
  BSP_EXTFLASH_CS_ACTIVE();
}

void setFlashCSInactive(void)
{
  BSP_EXTFLASH_CS_INACTIVE();
}

/** Synchronous mode init structure. */
static const USART_InitSync_TypeDef usartInit =
{
  /** Specifies whether TX and/or RX shall be enabled when init completed. */
  //USART_Enable_TypeDef    enable;
  usartEnable,

  /**
   * USART/UART reference clock assumed when configuring baudrate setup. Set
   * it to 0 if currently configurated reference clock shall be used.
   */
  //uint32_t                refFreq;
  38400000U,

  /** Desired baudrate. */
  //uint32_t                baudrate;
  HAL_EXTFLASH_USART_BAUDRATE,

  /** Number of databits in frame. */
  //USART_Databits_TypeDef  databits;
  usartDatabits8,

  /** Select if to operate in master or slave mode. */
  //bool                    master;
  true,

  /** Select if to send most or least significant bit first. */
  //bool                    msbf;
  true,

  /** Clock polarity/phase mode. */
  //USART_ClockMode_TypeDef clockMode;
  usartClockMode0,

  /** Enable USART Rx via PRS. */
  //bool                    prsRxEnable;
  false,

  /** Select PRS channel for USART Rx. (Only valid if prsRxEnable is true). */
  //USART_PrsRxCh_TypeDef   prsRxCh;
  usartPrsRxCh0,

  /** Enable AUTOTX mode. Transmits as long as RX is not full.
   *  If TX is empty, underflows are generated. */
  //bool                    autoTx;
  false,

  /** Auto CS enabling */
  //bool autoCsEnable;
  false,

  /** Auto CS hold time in baud cycles */
  //uint8_t autoCsHold;
  0,

  /** Auto CS setup time in baud cycles */
  //uint8_t autoCsSetup;
  0,
};

static const uint32_t iterations_per_microsecond = 3;

void usecDelay(uint32_t usecs)
{
  volatile uint64_t iterations = iterations_per_microsecond * usecs;

  while (iterations--) ;
}

void halEepromConfigureGPIO(void)
{
  // MOSI
  GPIO_PinModeSet(BSP_EXTFLASH_MOSI_PORT, BSP_EXTFLASH_MOSI_PIN, gpioModePushPull, 0);
  // MISO
  GPIO_PinModeSet(BSP_EXTFLASH_MISO_PORT, BSP_EXTFLASH_MISO_PIN, gpioModeInputPull, 0);
  // CLK
  GPIO_PinModeSet(BSP_EXTFLASH_CLK_PORT, BSP_EXTFLASH_CLK_PIN, gpioModePushPull, 0);
  // CS#
  GPIO_PinModeSet(BSP_EXTFLASH_CS_PORT, BSP_EXTFLASH_CS_PIN, gpioModePushPull, 1);

#if defined(REDUCED_SLEWRATE)
  // ----- Account for Noise and Crosstalk ------ //
  // on some hardware configurations there is a lot of noise and bootloading can fail
  // due to crosstalk. to avoid this, the slewrate is lowered here from 6 to 5
  // if noise related errors still occur, the slewrate can be lowered further
  GPIO->P[BSP_EXTFLASH_MOSI_PORT].CTRL = 0x00000000;
  GPIO->P[BSP_EXTFLASH_MOSI_PORT].CTRL = (0x5 << _GPIO_P_CTRL_SLEWRATE_SHIFT);
  GPIO->P[BSP_EXTFLASH_MOSI_PORT].CTRL |= (0x5 << _GPIO_P_CTRL_SLEWRATEALT_SHIFT);

  GPIO->P[BSP_EXTFLASH_MISO_PORT].CTRL = 0x00000000;
  GPIO->P[BSP_EXTFLASH_MISO_PORT].CTRL = (0x5 << _GPIO_P_CTRL_SLEWRATE_SHIFT);
  GPIO->P[BSP_EXTFLASH_MISO_PORT].CTRL |= (0x5 << _GPIO_P_CTRL_SLEWRATEALT_SHIFT);

  GPIO->P[BSP_EXTFLASH_CLK_PORT].CTRL = 0x00000000;
  GPIO->P[BSP_EXTFLASH_CLK_PORT].CTRL = (0x5 << _GPIO_P_CTRL_SLEWRATE_SHIFT);
  GPIO->P[BSP_EXTFLASH_CLK_PORT].CTRL |= (0x5 << _GPIO_P_CTRL_SLEWRATEALT_SHIFT);

  GPIO->P[BSP_EXTFLASH_CS_PORT].CTRL = 0x00000000;
  GPIO->P[BSP_EXTFLASH_CS_PORT].CTRL = (0x5 << _GPIO_P_CTRL_SLEWRATE_SHIFT);
  GPIO->P[BSP_EXTFLASH_CS_PORT].CTRL |= (0x5 << _GPIO_P_CTRL_SLEWRATEALT_SHIFT);
#endif

#if defined(BSP_EXTFLASH_HOLD_PORT)
  GPIO_PinModeSet(BSP_EXTFLASH_HOLD_PORT, BSP_EXTFLASH_HOLD_PIN, gpioModePushPull, 1);
#endif
#if defined(BSP_EXTFLASH_WP_PORT)
  GPIO_PinModeSet(BSP_EXTFLASH_WP_PORT, BSP_EXTFLASH_WP_PIN, gpioModePushPull, 1);
#endif
}

void halEepromConfigureFlashController(void)
{
  SPIFLASH_CLASS1_DEBUG_SETUP();
  SPIFLASH_CLASS1_DEBUG_CLEAR();

  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(SPIFLASH_USART_CLOCK, true);

  USART_InitSync(SPIFLASH_USART, &usartInit);

  // :TODO: abstract away pin selection for route location and GPIO mode setting

  SPIFLASH_USART->ROUTEPEN  =   USART_ROUTEPEN_TXPEN
                              | USART_ROUTEPEN_RXPEN
                              | USART_ROUTEPEN_CLKPEN;

  SPIFLASH_USART->ROUTELOC0 = (BSP_EXTFLASH_MOSI_LOC
                               << _USART_ROUTELOC0_TXLOC_SHIFT)
                              | (BSP_EXTFLASH_MISO_LOC
                                 << _USART_ROUTELOC0_RXLOC_SHIFT)
                              | (BSP_EXTFLASH_CLK_LOC
                                 << _USART_ROUTELOC0_CLKLOC_SHIFT);
}

void halEepromDelayMicroseconds(uint32_t timeToDelay)
{
  SPIFLASH_CLASS1_DEBUG_SET();
  usecDelay(timeToDelay);
  SPIFLASH_CLASS1_DEBUG_CLEAR();
}

void configureEepromPowerPin(void)
{
  CONFIGURE_EEPROM_POWER_PIN();
}

void setEepromPowerPin(void)
{
  SET_EEPROM_POWER_PIN();
}

void clearEepromPowerPin(void)
{
  CLR_EEPROM_POWER_PIN();
}
