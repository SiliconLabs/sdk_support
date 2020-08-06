/***************************************************************************//**
 * @file
 * @brief LED manipulation routines; stack and example APIs
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
#if !defined(MINIMAL_HAL) && defined(BOARD_HEADER)
// full hal needs the board header to get pulled in
  #include "hal/micro/micro.h"
  #include BOARD_HEADER
  #ifdef HAL_CONFIG
    #include "hal-config.h"
  #endif
#endif
#include "hal/micro/led.h"
#include "em_cmu.h"

// Stub out LED functions when there aren't any LEDs
#if HAL_LED_COUNT == 0
void halInternalInitLed(void)
{
  /* no-op */
}
void halSetLed(HalBoardLed led)
{
  /* no-op */
}
void halClearLed(HalBoardLed led)
{
  /* no-op */
}
void halToggleLed(HalBoardLed led)
{
  /* no-op */
}
#else
typedef struct {
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} tLedArray;
static const tLedArray ledArray[BSP_LED_COUNT] = BSP_LED_INIT;

// HWCONF will intialize LED GPIOs
#ifndef EMBER_AF_USE_HW_CONF
void halInternalInitLed(void)
{
  int i;
  uint8_t enableLeds[HAL_LED_COUNT] = HAL_LED_ENABLE;

#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif //!defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_GPIO, true);
  for ( i = 0; i < HAL_LED_COUNT; i++ ) {
  #if defined (BSP_LED_POLARITY) && (BSP_LED_POLARITY == 0)
    GPIO_PinModeSet(ledArray[enableLeds[i]].port,
                    ledArray[enableLeds[i]].pin,
                    gpioModePushPull,
                    1);
  #else
    GPIO_PinModeSet(ledArray[enableLeds[i]].port,
                    ledArray[enableLeds[i]].pin,
                    gpioModePushPull,
                    0);
  #endif
  }
}
#endif

void halSetLed(HalBoardLed led)
{
#if defined (BSP_LED_POLARITY) && (BSP_LED_POLARITY == 0)
  GPIO_PinOutClear(ledArray[led].port, ledArray[led].pin);
#else
  GPIO_PinOutSet(ledArray[led].port, ledArray[led].pin);
#endif
}

void halClearLed(HalBoardLed led)
{
#if defined (BSP_LED_POLARITY) && (BSP_LED_POLARITY == 0)
  GPIO_PinOutSet(ledArray[led].port, ledArray[led].pin);
#else
  GPIO_PinOutClear(ledArray[led].port, ledArray[led].pin);
#endif
}

void halToggleLed(HalBoardLed led)
{
  GPIO_PinOutToggle(ledArray[led].port, ledArray[led].pin);
}
#endif

#ifndef MINIMAL_HAL
void halStackIndicateActivity(bool turnOn)
{
 #if     NO_LED
  // Don't touch LEDs when built with NO_LED
 #else//!NO_LED
  if (turnOn) {
    halSetLed(BOARD_ACTIVITY_LED);
  } else {
    halClearLed(BOARD_ACTIVITY_LED);
  }
 #endif//NO_LED
}

#endif //MINIMAL_HAL
