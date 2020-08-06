/***************************************************************************//**
 * @file
 * @brief  Serial controller abstraction for EM3XX interface to external flash
 *
 * This layer of abstraction allows the board header to specify which serial
 * controller to use when talking to the Flash IC. If EXTERNAL_FLASH_PORT is left
 * undefined, the old behavior is used (SC2 unless SPI_FLASH_SC1 is defined).
 *
 * When EEPROM_USES_SHUTDOWN_CONTROL is defined in the board header, logic is
 * enabled in the EEPROM driver which drives a line high upon initialization.
 * In Ember reference designs, an enable pin must be driven high in order to use
 * the EEPROM. This option is intended to be enabled when running app-bootloader
 * on designs based on current Ember reference designs. PB7 is chosen as this
 * pin unless overridden.
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
// Default to old behavior
#ifndef EXTERNAL_FLASH_SERIAL_CONTROLLER
  #ifdef SPI_FLASH_SC1
    #define EXTERNAL_FLASH_SERIAL_CONTROLLER  1
  #else
    #define EXTERNAL_FLASH_SERIAL_CONTROLLER  2
  #endif
#endif

// only serial controllers 1 through 4 are valid
#if !(EXTERNAL_FLASH_SERIAL_CONTROLLER >= 1 \
      && EXTERNAL_FLASH_SERIAL_CONTROLLER <= 4)
  #error "EXTERNAL_FLASH_SERIAL_CONTROLLER out of range (1-4)."
#endif

// only serial controllers actually present on the micro are valid
#if (EMBER_MICRO_SERIAL_CONTROLLERS_MASK & (1 << (EXTERNAL_FLASH_SERIAL_CONTROLLER - 1))) == 0

  #error EXTERNAL_FLASH_SERIAL_CONTROLLER specifies an invalid serial \
  controller for this micro.

#endif

// Abstract away registers to make access serial controller agnostic
#if EXTERNAL_FLASH_SERIAL_CONTROLLER == 1

// GPIO assignments (SC1)
// PB1: SC1MOSI / SC1SDA
// PB2: SC1MISO / SC1SCL
// PB3: SC1SCLK
// PB4: SC1 chip select

  #if    !(EMBER_MICRO_PORT_B_GPIO & GPIO_P_IN_Px1) \
  || !(EMBER_MICRO_PORT_B_GPIO & GPIO_P_IN_Px2)     \
  || !(EMBER_MICRO_PORT_B_GPIO & GPIO_P_IN_Px3)     \
  || !(EMBER_MICRO_PORT_B_GPIO & GPIO_P_IN_Px4)

    #error EXTERNAL_FLASH_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EXTERNAL_FLASH_SCx_DATA        (SC1->DATA)
  #define EXTERNAL_FLASH_SCx_MODE        (SC1->MODE)
  #define EXTERNAL_FLASH_SCx_RATELIN     (SC1->RATELIN)
  #define EXTERNAL_FLASH_SCx_RATEEXP     (SC1->RATEEXP)

  #define EXTERNAL_FLASH_MOSI_PIN        PORTB_PIN(1) // PB1
  #define EXTERNAL_FLASH_MISO_PIN        PORTB_PIN(2) // PB2
  #define EXTERNAL_FLASH_SCLK_PIN        PORTB_PIN(3) // PB3

  #if !defined(EXTERNAL_FLASH_CS_ACTIVE)
// default to PB4 if it is not already defined
    #define EXTERNAL_FLASH_CS_ACTIVE()     do { (GPIO->P[1].CLR) = BIT(4); } while (0)
    #define EXTERNAL_FLASH_CS_INACTIVE()   do { (GPIO->P[1].SET) = BIT(4); } while (0)
    #define EXTERNAL_FLASH_nCS_PIN         PORTB_PIN(4) // PB4
  #endif

  #define EXTERNAL_FLASH_SCx_MODE_SPI    SC_MODE_MODE_SPI
  #define EXTERNAL_FLASH_SCx_SPISTAT     (SC1->SPISTAT)
  #define EXTERNAL_FLASH_SCx_SPICFG      (SC1->SPICFG)

  #define EXTERNAL_FLASH_SDA_PIN         PORTB_PIN(1) // PB1
  #define EXTERNAL_FLASH_SCL_PIN         PORTB_PIN(2) // PB2

  #define EXTERNAL_FLASH_SCx_MODE_I2C    SC_MODE_MODE_I2C
  #define EXTERNAL_FLASH_SCx_TWISTAT     (SC1->TWISTAT)
  #define EXTERNAL_FLASH_SCx_TWICTRL1    (SC1->TWICTRL1)
  #define EXTERNAL_FLASH_SCx_TWICTRL2    (SC1->TWICTRL2)

#elif EXTERNAL_FLASH_SERIAL_CONTROLLER == 2

// GPIO assignments (SC2)
// PA0: SC2MOSI
// PA1: SC2MISO / SC2SDA
// PA2: SC2SCLK / SC2SCL
// PA3: SC2 chip select

  #if    !(EMBER_MICRO_PORT_A_GPIO & GPIO_P_IN_Px0) \
  || !(EMBER_MICRO_PORT_A_GPIO & GPIO_P_IN_Px1)     \
  || !(EMBER_MICRO_PORT_A_GPIO & GPIO_P_IN_Px2)     \
  || !(EMBER_MICRO_PORT_A_GPIO & GPIO_P_IN_Px3)

    #error EXTERNAL_FLASH_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EXTERNAL_FLASH_SCx_DATA        (SC2->DATA)
  #define EXTERNAL_FLASH_SCx_MODE        (SC2->MODE)
  #define EXTERNAL_FLASH_SCx_RATELIN     (SC2->RATELIN)
  #define EXTERNAL_FLASH_SCx_RATEEXP     (SC2->RATEEXP)

  #define EXTERNAL_FLASH_MOSI_PIN        PORTA_PIN(0) // PA0
  #define EXTERNAL_FLASH_MISO_PIN        PORTA_PIN(1) // PA1
  #define EXTERNAL_FLASH_SCLK_PIN        PORTA_PIN(2) // PA2

  #if !defined(EXTERNAL_FLASH_CS_ACTIVE)
// default to PA3 if it is not already defined
    #define EXTERNAL_FLASH_CS_ACTIVE()     do { (GPIO->P[0].CLR) = BIT(3); } while (0)
    #define EXTERNAL_FLASH_CS_INACTIVE()   do { (GPIO->P[0].SET) = BIT(3); } while (0)
    #define EXTERNAL_FLASH_nCS_PIN         PORTA_PIN(3) // PA3
  #endif

  #define EXTERNAL_FLASH_SCx_MODE_SPI    SC_MODE_MODE_SPI
  #define EXTERNAL_FLASH_SCx_SPICFG      (SC2->SPICFG)
  #define EXTERNAL_FLASH_SCx_SPISTAT     (SC2->SPISTAT)

  #define EXTERNAL_FLASH_SDA_PIN         PORTA_PIN(1) // PA1
  #define EXTERNAL_FLASH_SCL_PIN         PORTA_PIN(2) // PA2

  #define EXTERNAL_FLASH_SCx_MODE_I2C    SC_MODE_MODE_I2C
  #define EXTERNAL_FLASH_SCx_TWISTAT     (SC2->TWISTAT)
  #define EXTERNAL_FLASH_SCx_TWICTRL1    (SC2->TWICTRL1)
  #define EXTERNAL_FLASH_SCx_TWICTRL2    (SC2->TWICTRL2)

#elif EXTERNAL_FLASH_SERIAL_CONTROLLER == 3

// GPIO assignments (SC3)
// PD1: SC3MOSI / SC3SDA
// PD2: SC3MISO / SC3SCL
// PD3: SC3SCLK
// PD4: SC3 chip select unless overwritten elsewhere

  #if    !(EMBER_MICRO_PORT_D_GPIO & GPIO_P_IN_Px1) \
  || !(EMBER_MICRO_PORT_D_GPIO & GPIO_P_IN_Px2)     \
  || !(EMBER_MICRO_PORT_D_GPIO & GPIO_P_IN_Px3)     \
  || !(EMBER_MICRO_PORT_D_GPIO & GPIO_P_IN_Px4)

    #error EXTERNAL_FLASH_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EXTERNAL_FLASH_SCx_DATA        (SC->DATA)
  #define EXTERNAL_FLASH_SCx_MODE        (SC->MODE)
  #define EXTERNAL_FLASH_SCx_RATELIN     (SC->RATELIN)
  #define EXTERNAL_FLASH_SCx_RATEEXP     (SC->RATEEXP)

  #define EXTERNAL_FLASH_MOSI_PIN        PORTD_PIN(1) // PD1
  #define EXTERNAL_FLASH_MISO_PIN        PORTD_PIN(2) // PD2
  #define EXTERNAL_FLASH_SCLK_PIN        PORTD_PIN(3) // PD3

  #if !defined(EXTERNAL_FLASH_CS_ACTIVE)
// default to PD4 if it is not already defined
    #define EXTERNAL_FLASH_CS_ACTIVE()   do { (GPIO->P[3].CLR) = BIT(4); } while (0)
    #define EXTERNAL_FLASH_CS_INACTIVE() do { (GPIO->P[3].SET) = BIT(4); } while (0)
    #define EXTERNAL_FLASH_nCS_PIN         PORTD_PIN(4) // PD4
  #endif

  #define EXTERNAL_FLASH_SCx_MODE_SPI    SC_MODE_MODE_SPI
  #define EXTERNAL_FLASH_SCx_SPISTAT     (SC3->SPISTAT)
  #define EXTERNAL_FLASH_SCx_SPICFG      (SC3->SPICFG)

  #define EXTERNAL_FLASH_SDA_PIN         PORTD_PIN(1) // PD1
  #define EXTERNAL_FLASH_SCL_PIN         PORTD_PIN(2) // PD2

  #define EXTERNAL_FLASH_SCx_MODE_I2C    SC_MODE_MODE_I2C
  #define EXTERNAL_FLASH_SCx_TWISTAT     (SC3->TWISTAT)
  #define EXTERNAL_FLASH_SCx_TWICTRL1    (SC3->TWICTRL1)
  #define EXTERNAL_FLASH_SCx_TWICTRL2    (SC3->TWICTRL2)

#elif EXTERNAL_FLASH_SERIAL_CONTROLLER == 4

// GPIO assignments (SC4)
// PE0: SC4MOSI
// PE1: SC4MISO / SC4SDA
// PE2: SC4SCLK / SC4SCL
// PE3: SC4 chip select

  #if    !(EMBER_MICRO_PORT_E_GPIO & GPIO_P_IN_Px0) \
  || !(EMBER_MICRO_PORT_E_GPIO & GPIO_P_IN_Px1)     \
  || !(EMBER_MICRO_PORT_E_GPIO & GPIO_P_IN_Px2)     \
  || !(EMBER_MICRO_PORT_E_GPIO & GPIO_P_IN_Px3)

    #error EXTERNAL_FLASH_SERIAL_CONTROLLER requires invalid GPIO for this micro.

  #endif

  #define EXTERNAL_FLASH_SCx_DATA        (SC4->DATA)
  #define EXTERNAL_FLASH_SCx_MODE        (SC4->MODE)
  #define EXTERNAL_FLASH_SCx_RATELIN     (SC4->RATELIN)
  #define EXTERNAL_FLASH_SCx_RATEEXP     (SC4->RATEEXP)

  #define EXTERNAL_FLASH_MOSI_PIN        PORTE_PIN(0) // PE0
  #define EXTERNAL_FLASH_MISO_PIN        PORTE_PIN(1) // PE1
  #define EXTERNAL_FLASH_SCLK_PIN        PORTE_PIN(2) // PE2

  #if !defined(EXTERNAL_FLASH_CS_ACTIVE)
// default to PE3 if it is not already defined
    #define EXTERNAL_FLASH_CS_ACTIVE()     do { (GPIO->P[4].CLR) = BIT(3); } while (0)
    #define EXTERNAL_FLASH_CS_INACTIVE()   do { (GPIO->P[4].SET) = BIT(3); } while (0)
    #define EXTERNAL_FLASH_nCS_PIN         PORTE_PIN(3) // PE3
  #endif

  #define EXTERNAL_FLASH_SCx_MODE_SPI    SC_MODE_MODE_SPI
  #define EXTERNAL_FLASH_SCx_SPISTAT     (SC4->SPISTAT)
  #define EXTERNAL_FLASH_SCx_SPICFG      (SC4->SPICFG)

  #define EXTERNAL_FLASH_SDA_PIN         PORTE_PIN(1) // PE1
  #define EXTERNAL_FLASH_SCL_PIN         PORTE_PIN(2) // PE2

  #define EXTERNAL_FLASH_SCx_MODE_I2C    SC_MODE_MODE_I2C
  #define EXTERNAL_FLASH_SCx_TWISTAT     (SC4->TWISTAT)
  #define EXTERNAL_FLASH_SCx_TWICTRL1    (SC4->TWICTRL1)
  #define EXTERNAL_FLASH_SCx_TWICTRL2    (SC4->TWICTRL2)

#else

  #error EXTERNAL_FLASH_SERIAL_CONTROLLER must be 1, 2, 3, or 4

#endif

#if defined(EEPROM_USES_SHUTDOWN_CONTROL)

  #if !defined(EEPROM_POWER_PORT_PIN)
// Some micros don't have PB7, issue error when alternate wasn't specified
    #if !(EMBER_MICRO_PORT_B_GPIO & GPIO_P_IN_Px7)

      #error Default EEPROM enable pin (PB7) is invalid for this micro. \
  Please define EEPROM_USES_SHUTDOWN_CONTROL.
    #endif

    #define EEPROM_POWER_PORT_PIN PORTB_PIN(7)

  #endif

  #define CONFIGURE_EEPROM_POWER_PIN()  do { halGpioSetConfig(EEPROM_POWER_PORT_PIN, _GPIO_P_CFGz_Pxy_OUT); } while (0)
  #define SET_EEPROM_POWER_PIN()        do { halGpioSet(EEPROM_POWER_PORT_PIN); } while (0)
  #define CLR_EEPROM_POWER_PIN()        do { halGpioClear(EEPROM_POWER_PORT_PIN); } while (0)

#else

// Define empty macros when shutdown control is not used
  #define CONFIGURE_EEPROM_POWER_PIN()    (void)0
  #define SET_EEPROM_POWER_PIN()          (void)0
  #define CLR_EEPROM_POWER_PIN()          (void)0

#endif
