/***************************************************************************//**
 * @file
 * @brief
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
#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "hal/hal.h"
#include "hal/plugin/key-matrix/key-matrix-driver.h"

#ifndef KEY_MATRIX_COLUMNS_AS_OUTPUTS
#define KEY_MATRIX_COLUMNS_AS_OUTPUTS 0
#endif

#ifndef KEY_MATRIX_PINS_ACTIVE_HIGH
#define KEY_MATRIX_PINS_ACTIVE_HIGH 1
#endif

#if (KEY_MATRIX_COLUMNS_AS_OUTPUTS == 1)
#define KEY_OUTPUT_PIN_NUM        KEY_MATRIX_NUM_COLUMNS
#define KEY_INPUT_PIN_NUM         KEY_MATRIX_NUM_ROWS
#define KEY_OUTPUT_PIN_MASK       KEY_COLUMN_PINS_MASK
#define KEY_INPUT_PIN_MASK        KEY_ROW_PINS_MASK
#define KEY_OUTPUT_DEBUG_PIN_MASK KEY_COLUMN_DEBUG_PINS
#define KEY_INPUT_DEBUG_PIN_MASK  KEY_ROW_DEBUG_PINS
#define KEY_OUTPUT_PINS           KEY_COLUMN_PINS
#define KEY_INPUT_PINS            KEY_ROW_PINS
#else
#define KEY_OUTPUT_PIN_NUM        KEY_MATRIX_NUM_ROWS
#define KEY_INPUT_PIN_NUM         KEY_MATRIX_NUM_COLUMNS
#define KEY_OUTPUT_PIN_MASK       KEY_ROW_PINS_MASK
#define KEY_INPUT_PIN_MASK        KEY_COLUMN_PINS_MASK
#define KEY_OUTPUT_DEBUG_PIN_MASK KEY_ROW_DEBUG_PINS
#define KEY_INPUT_DEBUG_PIN_MASK  KEY_COLUMN_DEBUG_PINS
#define KEY_OUTPUT_PINS           KEY_ROW_PINS
#define KEY_INPUT_PINS            KEY_COLUMN_PINS
#endif

// Key outputs and inputs GPIO pins
static const uint32_t keyOutputPins[KEY_OUTPUT_PIN_NUM] = KEY_OUTPUT_PINS;
static const uint32_t keyInputPins[KEY_INPUT_PIN_NUM]   = KEY_INPUT_PINS;

// Key value memory ( initialized to 0s)
// 1 means a pressed key, 0 means a released key
static bool keyValueMemory[KEY_OUTPUT_PIN_NUM][KEY_INPUT_PIN_NUM];

// Dynamic key inputs and key outputs scanning
static uint8_t keyInputMask, keyOutputMask;

// GPIO power up/down settings defined in board header file.
extern uint16_t gpioCfgPowerUp[], gpioCfgPowerDown[];
extern uint8_t gpioOutPowerUp[], gpioOutPowerDown[];

static void gpioOut(uint32_t gpio, uint8_t out)
{
  uint32_t port = gpio / 8;
  uint32_t pin = gpio & 0x7;
  GPIO->P[port].OUT = ((GPIO->P[port].OUT & ~(1 << pin))
                       | (out << pin));
}

static uint32_t gpioIn(uint32_t gpio)
{
  uint32_t port = gpio / 8;
  uint32_t pin = gpio & 0x7;
  return (GPIO->P[port].IN & BIT(pin)) >> pin;
}

static void gpioConfigToVar(uint16_t *gpioCfg, uint8_t gpio, uint8_t config)
{
  uint16_t *port = (uint16_t*)(gpioCfg + (gpio >> 2));
  uint16_t cfg_bit = (gpio & 0x3) << 2;

  // Replace orignal GPIO config with new one
  *port &= ~(0xf << cfg_bit);
  *port |= ((config & 0xf) << cfg_bit);
}

static void gpioOutToVar(uint8_t *gpioSet, uint8_t gpio, uint8_t out)
{
  uint8_t *port = (uint8_t*)(gpioSet + (gpio >> 3));
  uint8_t set_bit = gpio & 0x7;

  // Replace orignal GPIO set value with new one
  *port &= ~(0x1 << set_bit);
  *port |=  ((out & 0x1) << set_bit);
}

void halKeyMatrixInitialize(void)
{
  uint8_t outputPin;
  uint8_t inputPin;

  // Check GPIO_DBGSTAT_FORCEDBG bit in GPIO->DBGSTAT register to figure out if we
  // are in a debug session or not. If we are debugging we have to use the key
  // masks to avoid the pins that are used for debug.
  if (GPIO->DBGSTAT & GPIO_DBGSTAT_FORCEDBG) {
    keyInputMask  = KEY_INPUT_PIN_MASK  & ~KEY_INPUT_DEBUG_PIN_MASK;
    keyOutputMask = KEY_OUTPUT_PIN_MASK & ~KEY_OUTPUT_DEBUG_PIN_MASK;
  } else {
    keyInputMask  = KEY_INPUT_PIN_MASK;
    keyOutputMask = KEY_OUTPUT_PIN_MASK;
    GPIO->DBGCFG |= GPIO_DBGCFG_DEBUGDIS; //Disable debug
  }

  // Set outputs to drive active level
  for (outputPin = 0; outputPin < KEY_OUTPUT_PIN_NUM; outputPin++) {
    if (READBIT(keyOutputMask, outputPin)) {
      gpioOut(keyOutputPins[outputPin], KEY_MATRIX_PINS_ACTIVE_HIGH);
      halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_OUT);

      // Modify system power up/down output pin gpio config and out settings
      gpioOutToVar(gpioOutPowerUp, keyOutputPins[outputPin], KEY_MATRIX_PINS_ACTIVE_HIGH);
      gpioOutToVar(gpioOutPowerDown, keyOutputPins[outputPin], KEY_MATRIX_PINS_ACTIVE_HIGH);
      gpioConfigToVar(gpioCfgPowerUp, keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_OUT);
      gpioConfigToVar(gpioCfgPowerDown, keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_OUT);
    }
  }

  // Set inputs to weak pull to inactive level
  for (inputPin = 0; inputPin < KEY_INPUT_PIN_NUM; inputPin++) {
    if (READBIT(keyInputMask, inputPin)) {
      gpioOut(keyInputPins[inputPin], !KEY_MATRIX_PINS_ACTIVE_HIGH);
      halGpioSetConfig(keyInputPins[inputPin], GPIO_P_CFGz_Pxy_IN_PUD);

      // Modify system power up/down input gpio config and pull up/down settings
      gpioOutToVar(gpioOutPowerUp, keyInputPins[inputPin], !KEY_MATRIX_PINS_ACTIVE_HIGH);
      gpioOutToVar(gpioOutPowerDown, keyInputPins[inputPin], !KEY_MATRIX_PINS_ACTIVE_HIGH);
      gpioConfigToVar(gpioCfgPowerUp, keyInputPins[inputPin], GPIO_P_CFGz_Pxy_IN_PUD);
      gpioConfigToVar(gpioCfgPowerDown, keyInputPins[inputPin], GPIO_P_CFGz_Pxy_IN_PUD);
    }
  }
}

bool halKeyMatrixAnyKeyDown(void)
{
  uint8_t inputPin;

  for (inputPin = 0; inputPin < KEY_INPUT_PIN_NUM; inputPin++) {
    if (READBIT(keyInputMask, inputPin)
        && (gpioIn(keyInputPins[inputPin]) == KEY_MATRIX_PINS_ACTIVE_HIGH)) {
      return true;
    }
  }
  return false;
}

// Scan the entire key matrix. The results of the last scan for an individual
// key can be read with halMatrixGetValue()
void halKeyMatrixScan(void)
{
  uint8_t outputPin;
  uint8_t inputPin;

  for (outputPin = 0; outputPin < KEY_OUTPUT_PIN_NUM; outputPin++) {
    if (READBIT(keyOutputMask, outputPin)) {
      gpioOut(keyOutputPins[outputPin], KEY_MATRIX_PINS_ACTIVE_HIGH);
      halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_OUT);

      // Wait until key output pin is stable to read key input pins
      halCommonDelayMicroseconds(KEY_MATRIX_IO_WAIT_TIME_US);

      for (inputPin = 0; inputPin < KEY_INPUT_PIN_NUM; inputPin++) {
        keyValueMemory[outputPin][inputPin] = READBIT(keyInputMask, inputPin)
                                              && (gpioIn(keyInputPins[inputPin])
                                                  == KEY_MATRIX_PINS_ACTIVE_HIGH);
      }

      halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_IN_PUD);
      gpioOut(keyOutputPins[outputPin], !KEY_MATRIX_PINS_ACTIVE_HIGH);
    }
  }
}

// Scan only one key. The results for all other keys are unaltered from the
// previous time they were scanned. The results of the last scan for an
// individual key can be read with halMatrixGetValue()
void halKeyMatrixScanSingle(uint8_t key)
{
  uint8_t outputPin;
  uint8_t inputPin;

  outputPin = key / KEY_INPUT_PIN_NUM;
  inputPin = key % KEY_INPUT_PIN_NUM;

  gpioOut(keyOutputPins[outputPin], KEY_MATRIX_PINS_ACTIVE_HIGH);
  halGpioSetConfig(keyOutputPins[key / KEY_INPUT_PIN_NUM], GPIO_P_CFGz_Pxy_OUT);

  // Wait key output pin is stable to read key input pins
  halCommonDelayMicroseconds(KEY_MATRIX_IO_WAIT_TIME_US);

  keyValueMemory[outputPin][inputPin] = (gpioIn(keyInputPins[inputPin])
                                         == KEY_MATRIX_PINS_ACTIVE_HIGH);

  halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_IN_PUD);
  gpioOut(keyOutputPins[outputPin], !KEY_MATRIX_PINS_ACTIVE_HIGH);
}

// Read back value for a key. 0 means released and 1 means pressed
bool halKeyMatrixGetValue(uint8_t key)
{
  return keyValueMemory[key / KEY_INPUT_PIN_NUM][key % KEY_INPUT_PIN_NUM];
}

// Set all outputs as high output before going to sleep so that any
// key press will wake up the device through a wake-up enabled output pin
// Drive direction is already configured by gpioOutPowerDown
void halKeyMatrixPrepareForSleep(void)
{
  uint8_t outputPin;

  for (outputPin = 0; outputPin < KEY_OUTPUT_PIN_NUM; outputPin++) {
    if (READBIT(keyOutputMask, outputPin)) {
      halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_OUT);
    }
  }
}

// Set all input pins as inputs when exiting sleep to allow individual pins to
// be measured.
// Pull direction is already configured by gpioOutPowerUp
void halKeyMatrixRestoreFromSleep(void)
{
  uint8_t outputPin;

  for (outputPin = 0; outputPin < KEY_OUTPUT_PIN_NUM; outputPin++) {
    if (READBIT(keyOutputMask, outputPin)) {
      halGpioSetConfig(keyOutputPins[outputPin], GPIO_P_CFGz_Pxy_IN);
    }
  }
}
