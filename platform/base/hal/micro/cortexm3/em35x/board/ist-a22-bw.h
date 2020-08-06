/***************************************************************************//**
 * @file
 * @brief See @ref board for detailed documentation.
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
/** @addtogroup board
 *  @brief Functions and definitions specific to the breakout board.
 *
 * @note The file ist-a22-bw.h is intended to be used with the lighting module
 * for HA certified, dimmable LED light bulbs.  It is used with the ist-a22
 * module (with the EM3585) or with the ist-a20 mdoule (with the EM357).
 *
 * The file ist-a22-bw.h is the default BOARD_HEADER file used with the
 * LED lighting module.
 *
 * The EM35x on a IST-a22 module has the following example GPIO configuration.
 * This board file and the default HAL setup reflects this configuration.
 * - PA0 - SC2MOSI  // to connect to external EEPROM for the EM357 use case.
 * - PA1 - SC2MISO
 * - PA2 - SC2SCLK
 * - PA3 - SC2nSSEL
 * - PA4 - PTI_EN
 * - PA5 - PTI_DATA
 * - PA6 - NC
 * - PA7 - NC
 * - PB0 - NC
 * - PB1 - PWM1, White by default
 * - PB2 - PWM2, unused by default
 * - PB3 - PWM3, unused by default
 * - PB4 - PWM4, unused by default.
 * - PB5 - NC
 * - PB6 - NC
 * - PB7 - NC
 * - PC0 - NC (JTAG (JRST))
 * - PC1 - NC
 * - PC2 - JTAG (JTDO) / SWO
 * - PC3 - NC (JTAG (JTDI))
 * - PC4 - JTAG (JTMS)
 * - PC5 - FEM TX_ACTIVE
 * - PC6 - FEM CPS_CSD
 * - PC7 - NC
 *
 *@{
 */

#ifndef __BOARD_H__
#define __BOARD_H__

/** @name PWM control LED definition.
 *
 * The following code is used to define the default values for driving the PWM
 * signals in an LED bulb.  It is also used to set up which PWM will be driven
 * based on the board configuration.
 */
//@{

/**
 * @brief The frequency, in Hz, at which we will drive the PWM ouptut hardware
 * by default.  The extreme range is from about 24kHz (6E6 / 255) to about 91
 * Hz(6E6 / 65535), although most bulbs typically drive in the 500 Hz to 1.5
 * kHz range.
 */
  #define PWM_DEFAULT_FREQUENCY 1000 // 1 kHz.

/**
 * @brief For the reference design, we drive PB1-4, which are accessed through
 * the alternate drive outputs of timer 2.
 */
  #define TIM2_CHAN1_ALT 1 // PA0 = 0, PB1 = 1
  #define TIM2_CHAN2_ALT 1 // PA1 = 0, PB2 = 1
  #define TIM2_CHAN3_ALT 1 // PA2 = 0, PB3 = 1
  #define TIM2_CHAN4_ALT 1 // PA3 = 0, PB4 = 1

/**
 * @brief For the reference design, we do not enable timer 1 output channels.
 */
  #define TIM1_CHAN1_ENABLE 0  // PB6
  #define TIM1_CHAN2_ENABLE 0  // PB7
  #define TIM1_CHAN3_ENABLE 0  // PA6
  #define TIM1_CHAN4_ENABLE 0  // PA7

/**
 * @brief For the reference design, we enable the timer 2 otuput channels.
 * This is to allow configuration, through manufacturer tokens, of which PWM
 * to drive.
 */
  #define TIM2_CHAN1_ENABLE 1  // PA0 = 0, PB1 = 1
  #define TIM2_CHAN2_ENABLE 1  // PA3 = 0, PB2 = 1
  #define TIM2_CHAN3_ENABLE 1  // PA3 = 0, PB3 = 1
  #define TIM2_CHAN4_ENABLE 1  // PA3 = 0, PB4 = 1

/**
 * @brief Default value of the WHITE counter compare register, which sets the
 * width of the pulse.
 */
  #define PWM_WHITE TIM2_CCR1

/**
 * @brief Frequency at which the PWM counter will increment.
 */
  #define CLOCK_FREQUENCY     6000000

/**
 * @brief Default value of the minimum on time, in microseconds.  Most bulb
 *    & power supplies have a minimum current below which the supply could be
 * damaged or may start to blink.  This threshold is set to be above this
 * minimum threshold for safe power supply operation.  It translates to the
 * PWM pulse width when the level contorl level attribute is set to 1.
 */
  #define MINIMUM_ON_TIME_US 15
//@} //END OF BULB PWM DEFINITIONS

/** @name Custom Baud Rate Definitions
 *
 * The following define is used with defining a custom baud rate for the UART.
 * This define provides a simple hook into the definition of
 * the baud rates used with the UART.  The baudSettings[] array in uart.c
 * links the BAUD_* defines with the actual register values needed for
 * operating the UART.  The array baudSettings[] can be edited directly for a
 * custom baud rate or another entry (the register settings) can be provided
 * here with this define.
 */
//@{

/**
 * @brief This define is the register setting for generating a baud of
 * 921600.  Refer to the EM35x datasheet's discussion on UART baud rates for
 * the equation used to derive this value.
 */
#define EMBER_SERIAL_BAUD_CUSTOM  13
//@} //END OF CUSTOM BAUD DEFINITIONS

/** @name Framework Noop definitions
 *
 * The framework assumes we have a few macros defined even if we have no
 * intention of ever using this functionality.
 *
 */
//@{
#define NO_LED 1

enum HalBoardLedPins {
  BOARDLED0 = 0
};

#define halInternalInitRadioHoldOff()

/** @name Packet Trace
 *
 * When ::PACKET_TRACE is defined, ::GPIO->P[0].CFGH will automatically be setup by
 * halInit() to enable Packet Trace support on PA4 and PA5,
 * in addition to the configuration specified below.
 *
 * @note This define will override any settings for PA4 and PA5.
 */
//@{

/**
 * @brief This define does not equate to anything.  It is used as a
 * trigger to enable Packet Trace support on the breakout board (dev0680).
 */
#define PACKET_TRACE  // We do have PACKET_TRACE support
//@} //END OF PACKET TRACE DEFINITIONS

/** @name Packet Trace Configuration Defines
 *
 * Provide the proper set of pin configuration for when the Packet
 * Trace is enabled (look above for the define which enables it).  When Packet
 * Trace is not enabled, leave the two PTI pins in their default configuration.
 * If Packet Trace is not being used, feel free to set the pin configurations
 * as desired.  The config shown here is simply the Power On Reset defaults.
 *@{
 */

/**
 * @brief Give the packet trace configuration a friendly name.
 */
#ifdef  PACKET_TRACE
  #define PWRUP_CFG_PTI_EN    _GPIO_P_CFGL_Px0_OUT_ALT
  #define PWRUP_OUT_PTI_EN    0
  #define PWRDN_CFG_PTI_EN    _GPIO_P_CFGL_Px0_IN_PUD
  #define PWRDN_OUT_PTI_EN    GPIOOUT_PULLDOWN
  #define PWRUP_CFG_PTI_DATA  _GPIO_P_CFGL_Px0_OUT_ALT
  #define PWRUP_OUT_PTI_DATA  1
  #define PWRDN_CFG_PTI_DATA  _GPIO_P_CFGL_Px0_IN_PUD
  #define PWRDN_OUT_PTI_DATA  GPIOOUT_PULLUP
#else//!PACKET_TRACE
  #define PWRUP_CFG_PTI_EN    _GPIO_P_CFGL_Px0_IN
  #define PWRUP_OUT_PTI_EN    0
  #define PWRDN_CFG_PTI_EN    _GPIO_P_CFGL_Px0_IN
  #define PWRDN_OUT_PTI_EN    0
  #define PWRUP_CFG_PTI_DATA  _GPIO_P_CFGL_Px0_IN
  #define PWRUP_OUT_PTI_DATA  0
  #define PWRDN_CFG_PTI_DATA  _GPIO_P_CFGL_Px0_IN
  #define PWRDN_OUT_PTI_DATA  0
#endif//PACKET_TRACE
//@} END OF Packet Trace Configuration Defines

/** @name GPIO Configuration Macros
 *
 * These macros define the GPIO configuration and initial state of the output
 * registers for all the GPIO in the powerup and powerdown modes.
 *@{
 */

//Each pin has 4 cfg bits.  There are 3 ports with 2 cfg registers per
//port since the cfg register only holds 2 pins (16bits).  Therefore,
//the cfg arrays need to be 6 entries of 16bits.
extern uint16_t gpioCfgPowerUp[6];
extern uint16_t gpioCfgPowerDown[6];
//Each pin has 1 out bit.  There are 3 ports with 1 out register per
//port (8bits).  Therefore, the out arrays need to be 3 entries of 8bits.
extern uint8_t gpioOutPowerUp[3];
extern uint8_t gpioOutPowerDown[3];
//A single mask variable covers all 24 GPIO.
extern uint32_t gpioRadioPowerBoardMask;

/**
 * @brief Define the mask for GPIO relevant to the radio in the context
 * of power state.  Each bit in the mask indicates the corresponding GPIO
 * which should be affected when invoking halStackRadioPowerUpBoard() or
 * halStackRadioPowerDownBoard().
 */
#define DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE() \
  uint32_t gpioRadioPowerBoardMask = 0

/**
 * @brief Initialize GPIO powerup configuration variables.
 */
#define DEFINE_POWERUP_GPIO_CFG_VARIABLES()                       \
  uint16_t gpioCfgPowerUp[6] = {                                  \
    ((_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_IN          << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGH_Px4_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGH_Px5_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGH_Px7_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGH_Px4_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGH_Px5_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD      << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGH_Px7_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN          << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_IN          << _GPIO_P_CFGH_Px4_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT_ALT     << _GPIO_P_CFGH_Px5_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT         << _GPIO_P_CFGH_Px7_SHIFT))  \
  }

/**
 * @brief Initialize GPIO powerup output variables.
 */
#define DEFINE_POWERUP_GPIO_OUTPUT_DATA_VARIABLES()          \
  uint8_t gpioOutPowerUp[3] = {                              \
    ((0                  << _GPIO_P_OUT_Px0_SHIFT)           \
     | (0                  << _GPIO_P_OUT_Px1_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px2_SHIFT)         \
     |                      /* nSSEL is default idle high */ \
     (1                  << _GPIO_P_OUT_Px3_SHIFT)           \
     | (PWRUP_OUT_PTI_EN   << _GPIO_P_OUT_Px4_SHIFT)         \
     | (PWRUP_OUT_PTI_DATA << _GPIO_P_OUT_Px5_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px6_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)),       \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)           \
     | (1                  << _GPIO_P_OUT_Px1_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px2_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px3_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px4_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px5_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px6_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px7_SHIFT)),       \
    ((1                  << _GPIO_P_OUT_Px0_SHIFT)           \
     | (0                  << _GPIO_P_OUT_Px1_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px3_SHIFT)         \
     | (0                  << _GPIO_P_OUT_Px4_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px5_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px6_SHIFT)         \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT))        \
  }

/**
 * @brief Initialize powerdown GPIO configuration variables.
 */
#define DEFINE_POWERDOWN_GPIO_CFG_VARIABLES()                    \
  uint16_t gpioCfgPowerDown[6] = {                               \
    ((_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((PWRDN_CFG_PTI_EN   << _GPIO_P_CFGH_Px4_SHIFT)              \
     | (PWRDN_CFG_PTI_DATA << _GPIO_P_CFGH_Px5_SHIFT)            \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px7_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px4_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGH_Px5_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGH_Px7_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px0_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGL_Px1_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGL_Px2_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGL_Px3_SHIFT)), \
    ((_GPIO_P_CFGL_Px0_IN_PUD     << _GPIO_P_CFGH_Px4_SHIFT)     \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px5_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px6_SHIFT)   \
     | (_GPIO_P_CFGL_Px0_OUT        << _GPIO_P_CFGH_Px7_SHIFT))  \
  }

/**
 * @brief Initialize powerdown GPIO output variables.
 */
#define DEFINE_POWERDOWN_GPIO_OUTPUT_DATA_VARIABLES()  \
  uint8_t gpioOutPowerDown[3] = {                      \
    ((GPIOOUT_PULLUP     << _GPIO_P_OUT_Px0_SHIFT)     \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px1_SHIFT)   \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px2_SHIFT)   \
     | (1                  << _GPIO_P_OUT_Px3_SHIFT)   \
     | (PWRDN_OUT_PTI_EN   << _GPIO_P_OUT_Px4_SHIFT)   \
     | (PWRDN_OUT_PTI_DATA << _GPIO_P_OUT_Px5_SHIFT)   \
     | (1                  << _GPIO_P_OUT_Px6_SHIFT)   \
     | (1                  << _GPIO_P_OUT_Px7_SHIFT)), \
    ((0                  << _GPIO_P_OUT_Px0_SHIFT)     \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px1_SHIFT)   \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px2_SHIFT)   \
     | (GPIOOUT_PULLDOWN   << _GPIO_P_OUT_Px3_SHIFT)   \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px4_SHIFT)   \
     | (GPIOOUT_PULLDOWN   << _GPIO_P_OUT_Px5_SHIFT)   \
     | (GPIOOUT_PULLUP     << _GPIO_P_OUT_Px6_SHIFT)   \
     | (GPIOOUT_PULLDOWN   << _GPIO_P_OUT_Px7_SHIFT)), \
    ((GPIOOUT_PULLUP     << _GPIO_P_OUT_Px0_SHIFT)     \
     | (0                  << _GPIO_P_OUT_Px1_SHIFT)   \
     | (1                  << _GPIO_P_OUT_Px2_SHIFT)   \
     | (GPIOOUT_PULLDOWN   << _GPIO_P_OUT_Px3_SHIFT)   \
     | (GPIOOUT_PULLDOWN   << _GPIO_P_OUT_Px4_SHIFT)   \
     | (1                  << _GPIO_P_OUT_Px5_SHIFT)   \
     | (0                  << _GPIO_P_OUT_Px6_SHIFT)   \
     | (0                  << _GPIO_P_OUT_Px7_SHIFT))  \
  }

/**
 * @brief Set powerup GPIO configuration registers.
 */
#define SET_POWERUP_GPIO_CFG_REGISTERS() \
  GPIO->P[0].CFGL = gpioCfgPowerUp[0];   \
  GPIO->P[0].CFGH = gpioCfgPowerUp[1];   \
  GPIO->P[1].CFGL = gpioCfgPowerUp[2];   \
  GPIO->P[1].CFGH = gpioCfgPowerUp[3];   \
  GPIO->P[2].CFGL = gpioCfgPowerUp[4];   \
  GPIO->P[2].CFGH = gpioCfgPowerUp[5];

/**
 * @brief Set powerup GPIO output registers.
 */
#define SET_POWERUP_GPIO_OUTPUT_DATA_REGISTERS() \
  GPIO->P[0].OUT = gpioOutPowerUp[0];            \
  GPIO->P[1].OUT = gpioOutPowerUp[1];            \
  GPIO->P[2].OUT = gpioOutPowerUp[2];

/**
 * @brief Set powerdown GPIO configuration registers.
 */
#define SET_POWERDOWN_GPIO_CFG_REGISTERS() \
  GPIO->P[0].CFGL = gpioCfgPowerDown[0];   \
  GPIO->P[0].CFGH = gpioCfgPowerDown[1];   \
  GPIO->P[1].CFGL = gpioCfgPowerDown[2];   \
  GPIO->P[1].CFGH = gpioCfgPowerDown[3];   \
  GPIO->P[2].CFGL = gpioCfgPowerDown[4];   \
  GPIO->P[2].CFGH = gpioCfgPowerDown[5];

/**
 * @brief Set powerdown GPIO output registers.
 */
#define SET_POWERDOWN_GPIO_OUTPUT_DATA_REGISTERS() \
  GPIO->P[0].OUT = gpioOutPowerDown[0];            \
  GPIO->P[1].OUT = gpioOutPowerDown[1];            \
  GPIO->P[2].OUT = gpioOutPowerDown[2];

/**
 * @brief External regulator enable/disable macro.
 */
#ifdef ENABLE_ALT_FUNCTION_REG_EN
  #define CONFIGURE_EXTERNAL_REGULATOR_ENABLE()  GPIO->DBGCFG |= GPIO_DBGCFG_EXTREGEN;
#else
  #define CONFIGURE_EXTERNAL_REGULATOR_ENABLE()  GPIO->DBGCFG &= ~GPIO_DBGCFG_EXTREGEN;
#endif
//@} END OF GPIO Configuration Macros

/** @name GPIO Wake Source Definitions
 *
 * A convenient define that chooses if this external signal can
 * be used as source to wake from deep sleep.  Any change in the state of the
 * signal will wake up the CPU.
 */
//@{

/**
 * @brief true if this GPIO can wake the chip from deep sleep, false if not.
 */
#define WAKE_ON_PA0   false
#define WAKE_ON_PA1   false
#define WAKE_ON_PA2   false
#define WAKE_ON_PA3   false
#define WAKE_ON_PA4   false
#define WAKE_ON_PA5   false
#define WAKE_ON_PA6   false
#define WAKE_ON_PA7   false
#define WAKE_ON_PB0   false
#define WAKE_ON_PB1   false
#ifdef SLEEPY_EZSP_UART  // SC1RXD
  #define WAKE_ON_PB2   true
#else
  #define WAKE_ON_PB2   false
#endif
#define WAKE_ON_PB3   false
#define WAKE_ON_PB4   false
#define WAKE_ON_PB5   false
#define WAKE_ON_PB6   false
#define WAKE_ON_PB7   false
#define WAKE_ON_PC0   false
#define WAKE_ON_PC1   false
#define WAKE_ON_PC2   false
#define WAKE_ON_PC3   false
#define WAKE_ON_PC4   false
#define WAKE_ON_PC5   false
#define WAKE_ON_PC6   false
#define WAKE_ON_PC7   false
//@} //END OF GPIO Wake Source Definitions

//@} //END OF GPIO Configuration Definitions

/** @name Board Specific Functions
 *
 * The following macros exist to aid in the initialization, power up from sleep,
 * and power down to sleep operations.  These macros are responsible for
 * either initializing directly, or calling initialization functions for any
 * peripherals that are specific to this board implementation.  These
 * macros are called from halInit, halPowerDown, and halPowerUp respectively.
 */
//@{

/**
 * @brief Initialize the board.  This function is called from ::halInit().
 */
#ifndef EZSP_UART
  #define halInternalInitBoard()   \
  do {                             \
    halInternalPowerUpBoard();     \
    halInternalInitRadioHoldOff(); \
    halInternalInitButton();       \
  } while (0)
#else
  #define halInternalInitBoard()   \
  do {                             \
    halInternalPowerUpBoard();     \
    halInternalInitRadioHoldOff(); \
  } while (0)
#endif

/**
 * @brief Power down the board.  This function is called from
 * ::halPowerDown().
 */
#define halInternalPowerDownBoard()            \
  do {                                         \
    /* Board peripheral deactivation */        \
    /* halInternalSleepAdc(); */               \
    SET_POWERDOWN_GPIO_OUTPUT_DATA_REGISTERS() \
    SET_POWERDOWN_GPIO_CFG_REGISTERS()         \
  } while (0)

/**
 * @brief Power up the board.  This function is called from
 * ::halPowerUp().
 */
#define halInternalPowerUpBoard()                            \
  do {                                                       \
    SET_POWERUP_GPIO_OUTPUT_DATA_REGISTERS()                 \
    SET_POWERUP_GPIO_CFG_REGISTERS()                         \
    /*The radio GPIO should remain in the powerdown state */ \
    /*until the stack specifically powers them up. */        \
    halStackRadioPowerDownBoard();                           \
    CONFIGURE_EXTERNAL_REGULATOR_ENABLE()                    \
    /* Board peripheral reactivation */                      \
    halInternalInitAdc();                                    \
  } while (0)
//@} //END OF BOARD SPECIFIC FUNCTIONS

#endif //__BOARD_H__

/** @} END Board Specific Functions */

/** @} END addtogroup */
