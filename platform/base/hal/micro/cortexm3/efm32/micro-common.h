/***************************************************************************//**
 * @file
 * @brief Utility and convenience functions for EFM32/EFR32 microcontroller,
 *        common to both the full and minimal hal.
 * See @ref micro for documentation.
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
/** @addtogroup micro
 * See also hal/micro/cortexm3/efm32/micro.h for source code.
 *@{
 */

#ifndef __EFM32_MICRO_COMMON_H__
#define __EFM32_MICRO_COMMON_H__

#include "em_gpio.h" // For GPIO_ TypeDefs
#include "ecode.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifndef __EMBERSTATUS_TYPE__
#define __EMBERSTATUS_TYPE__
//This is necessary here because halSleepForQsWithOptions returns an
//EmberStatus and not adding this typedef to this file breaks a
//whole lot of builds.
typedef uint8_t EmberStatus;
#endif //__EMBERSTATUS_TYPE__
#endif // DOXYGEN_SHOULD_SKIP_THIS

// Forward declarations of the handlers used in the vector table
// These declarations are extracted from the NVIC configuration file.
#define EXCEPTION(vectorNumber, functionName, deviceIrqn, deviceIrqHandler, priorityLevel, subpriority) \
  void functionName(void);
  #include NVIC_CONFIG
#undef  EXCEPTION

/** @brief Initializes HAL config defined peripherals.
 */
Ecode_t halConfigInit(void);

/**
 * @brief Resets the watchdog timer.  This function is pointed
 * to by the macro ::halResetWatchdog().
 * @warning Be very careful when using this as you can easily get into an
 * infinite loop.
 */
void halInternalResetWatchDog(void);

/** @brief Blocks the current thread of execution for the specified
 * amount of time, in milliseconds.
 *
 * The function is implemented with cycle-counted busy loops
 * and is intended to create the short delays required when interfacing with
 * hardware peripherals.  This function works by simply adding another
 * layer on top of halCommonDelayMicroseconds().
 *
 * @param ms  The specified time, in milliseconds.
 */
void halCommonDelayMilliseconds(uint16_t ms);

/**
 * @brief Puts the microcontroller to sleep in a specified mode.
 *
 * @param sleepMode  A microcontroller sleep mode.
 *
 * @param wakeMask  A bit mask of the GPIO that are allowed to wake
 * the chip from sleep. A high bit in the mask will enable waking
 * the chip. The meaning of each bit is as follows:
 *
 * - [31:16] = Unused
 * - [15:0] = GPIO External Interrupt Pin [15:0]
 *
 * @sa ::SleepModes
 */
void halSleepWithOptions(SleepModes sleepMode, WakeMask wakeMask);

/**
 * @brief Uses the system timer to enter ::SLEEPMODE_WAKETIMER for
 * approximately the specified amount of time (provided in quarter seconds).
 *
 * This function returns ::EMBER_SUCCESS and the duration parameter is
 * decremented to 0 after sleeping for the specified amount of time.  If an
 * interrupt occurs that brings the chip out of sleep, the function returns
 * ::EMBER_SLEEP_INTERRUPTED and the duration parameter reports the amount of
 * time remaining out of the original request.
 *
 * @note This routine always enables interrupts.
 *
 * @nostackusage
 *
 * @param duration The amount of time, expressed in quarter seconds, that the
 * micro should be placed into ::SLEEPMODE_WAKETIMER.  When the function returns,
 * this parameter provides the amount of time remaining out of the original
 * sleep time request (normally the return value will be 0).
 *
 * @param wakeMask  A bit mask of the GPIO that are allowed to wake
 * the chip from sleep. A high bit in the mask will enable waking
 * the chip. The meaning of each bit is as follows:
 *
 * - [31:16] = Unused
 * - [15:0] = GPIO External Interrupt Pin [15:0]
 *
 * @return An EmberStatus value indicating the success or
 *  failure of the command.
 */
EmberStatus halSleepForQsWithOptions(uint32_t *duration, WakeMask wakeMask);

/**
 * @brief Puts the microcontroller to sleep in a specified mode. This
 *  internal function performs the actual sleep operation.
 *
 * @param sleepMode  A microcontroller sleep mode
 */
void halInternalSleep(SleepModes sleepMode);

/**
 * @brief Called whenever the microcontroller enters/exits a idle/sleep mode
 *
 * @param enter        True if entering idle/sleep, False if exiting
 * @param sleepMode    Idle/sleep mode
 */
void halSleepCallback(boolean enter, SleepModes sleepMode);

/**
 * @brief Obtains the events that caused the last wake from sleep. The
 * meaning of each bit is as follows:
 * - [31:19] = Unused
 * - [18] = RFSENSE IRQ
 * - [17] = System Timer IRQ
 * - [16] = GPIO IRQ
 * - [15:0] = GPIO External Interrup Pin [15:0]
 *
 * @return Indication of what events that caused the last wake from sleep.
 */
WakeEvents halGetWakeInfo(void);

/**
 * IO pin config type
 */
typedef GPIO_Mode_TypeDef HalGpioCfg_t;

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port A pins into a single number.
 */
#define PORTA_PIN(y) ((0u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port B pins into a single number.
 */
#define PORTB_PIN(y) ((1u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port C pins into a single number.
 */
#define PORTC_PIN(y) ((2u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port D pins into a single number.
 */
#define PORTD_PIN(y) ((3u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port E pins into a single number.
 */
#define PORTE_PIN(y) ((4u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port F pins into a single number.
 */
#define PORTF_PIN(y) ((5u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port G pins into a single number.
 */
#define PORTG_PIN(y) ((6u << 4) | (y))

/**
 * @brief Some registers and variables require identifying GPIO by
 * a single number instead of the port and pin. This macro converts
 * Port H pins into a single number.
 */
#define PORTH_PIN(y) ((7u << 4) | (y))

// Some convenience macros for converting above into PORT,PIN,FLAG
#define GPIO_PORT(x) ((GPIO_Port_TypeDef)((x) >> 4))
#define GPIO_PIN(x)  ((x) & 0x0f)
#define GPIO_FLAG(x) (1ul << GPIO_PIN(x))

/***************************************************************************//**
 * @brief
 *   Register GPIO for powerup/powerdown configuration. If GPIO is already
 *   registered, current configuration will be overwritten
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number in the port.
 *
 * @param[in] pUpMode
 *   The desired pin mode when powering up.
 *
 * @param[in] pUpOut
 *   Value to set for pin in DOUT register on power down. The DOUT setting is
 *   important for even some input mode configurations, determining
 *   pull-up/down direction.
 *
 * @param[in] pDownMode
 *   The desired pin mode when powering down
 *
 * @param[in] pDownOut
 *   Value to set for pin in DOUT register on power down. The DOUT setting is
 *   important for even some input mode configurations, determining
 *   pull-up/down direction.
 *
 * @return
 *  True on success, false on failure (ran out of space)
 ******************************************************************************/
bool halConfigRegisterGpio(GPIO_Port_TypeDef port,
                           uint8_t pin,
                           GPIO_Mode_TypeDef pUpMode,
                           uint8_t pUpOut,
                           GPIO_Mode_TypeDef pDownMode,
                           uint8_t pDownOut);

/***************************************************************************//**
 * @brief
 *   Unregister GPIO. Will disable automatic powerup/powerdown configuration.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number in the port.
 *
 * @return
 *  True on success, false on failure (could not find GPIO)
 ******************************************************************************/
bool halConfigUnregisterGpio(GPIO_Port_TypeDef port, uint8_t pin);

/**
 * @brief Configure the operating mode of an IO pin
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 * @param config   The IO mode to use.
 *
 */
void halGpioSetConfig(uint32_t gpio, HalGpioCfg_t config);

/**
 * @brief Get the operating mode of an IO pin
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 * @return The current configuration mode.
 *
 */
HalGpioCfg_t halGpioGetConfig(uint32_t gpio);

/**
 * @brief Set an output pin high
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 *
 */
void halGpioSet(uint32_t gpio);

/**
 * @brief Set an output pin low
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 *
 */
void halGpioClear(uint32_t gpio);

/**
 * @brief Read the input value of an IO pin
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 * @return 1 if the pin reads high, 0 otherwise.
 *
 */
uint32_t halGpioRead(uint32_t gpio);

/**
 * @brief Read the output value of an IO pin
 *
 * @param gpio   The IO pin to use, can be specified with the convenience macros
 *               PORTA_PIN(), PORTB_PIN(), PORTC_PIN(), etc.
 * @return 1 if the pin reads high, 0 otherwise.
 *
 */
uint32_t halGpioReadOutput(uint32_t gpio);

/**
 * @brief Change the CTUNE value. Involves switching to HFRCO and turning off
 * the HFXO temporarily.
 *
 * @param tune   Value to set CTUNE to.
 *
 */
void halInternalSetCtune(uint16_t tune);

/**
 * @brief Get the CTUNE value.
 *
 * @return Current CTUNE value.
 *
 */
uint16_t halInternalGetCtune(void);

/**
 * @brief Get the factory calibrated CTUNE value on a series 1 module.
 *
 * @param ctuneVal  pointer to write ctune value
 *
 * @return True if factory calibrated value present, False if not present.
 *
 */
bool halInternalGetModuleCtune(uint16_t *ctuneVal);

/**
 * @brief Get the factory calibrated CTUNE Xi and Xo values on a series 2 module.
 *
 * @param ctuneXiVal  pointer to write ctune Xi value
 *
 * @param ctuneXoVal   pointer to write ctune Xo value
 *
 * @return True if factory calibrated values present, False if not present.
 *
 */
bool halInternalGetModuleCtuneXiXo(uint8_t *ctuneXiVal, uint8_t *ctuneXoVal);

/**
 * @brief Get the CTUNE token value.
 *
 * @param startupCtune  Unused
 *
 * @param steadyCtune   pointer to write steady state ctune value
 *
 * @return True if ctune token valid, False if ctune token not present.
 *
 */
bool halInternalGetCtuneToken(uint16_t *startupCtune, uint16_t *steadyCtune);

/**
 * @brief Change the LFXO TUNE value. Involves switching to LFRCO and turning off
 * the LFXO temporarily.
 *
 * @param tune   Value to set LFXO TUNE to.
 *
 */
void halInternalSetLfxoTune(uint8_t tune);

/**
 * @brief Get the LFXO TUNE value.
 *
 * @return Current LFXO TUNE value.
 *
 */
uint16_t halInternalGetLfxoTune(void);

/**
 * @brief Get the factory calibrated LFXO TUNE value.
 *
 * @param lfxoTuneVal  pointer to write lfxo tune value
 *
 * @return True if factory calibrated value present, False if not present.
 *
 */
bool halInternalGetModuleLfxoTune(uint8_t *lfxoTuneVal);

/**
 * @brief Get the LFXO TUNE token value.
 *
 * @param lfxoTune   pointer to write steady state ctune value
 *
 * @return True if lfxo tune token valid, False if lfxo tune token not present.
 *
 */
bool halInternalGetLfxoTuneToken(uint8_t *lfxoTune);
#endif //__EFM32_MICRO_COMMON_H__

/**@} END micro group
 */
