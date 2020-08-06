/***************************************************************************//**
 * @file
 * @brief  Sample API functions for operating buttons (external interrupts).
 *  Please see the board header file for the definition of the BUTTON*
 *  instances used below.  The BUTTON* defines used here are designed to make
 *  this library generic such that only the board header needs to be modified
 *  to change which GPIO the buttons are on.
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
#include "stack/include/ember.h"
#include "hal/hal.h"
#include "serial/serial.h"

#include "em_cmu.h"
#include "em_gpio.h"
#include "gpiointerrupt.h"

// This state is kept track of so the IRQ ISRs knows when to notify buttonIsrs.
#if (HAL_BUTTON_COUNT > 0)
static uint8_t buttonState[BSP_BUTTON_COUNT];
void halInternalButtonIsr(uint8_t pin);
typedef struct {
  GPIO_Port_TypeDef   port;
  unsigned int        pin;
} tButtonArray;
static const tButtonArray buttonArray[BSP_BUTTON_COUNT] = BSP_BUTTON_INIT;
#endif

#define HAL_BUTTON_INVALID_INDEX BSP_BUTTON_COUNT
#if (HAL_BUTTON_COUNT > 0)
static uint8_t halInternalButtonIndex(uint8_t pin)
{
  uint8_t i;
  for ( i = 0; i < BSP_BUTTON_COUNT; i++ ) {
    if (buttonArray[i].pin == pin) {
      break;
    }
  }
  return i;
}
#endif

void halInternalInitButton(void)
{
#if (HAL_BUTTON_COUNT > 0)
  uint8_t enableButtons[HAL_BUTTON_COUNT] = HAL_BUTTON_ENABLE;
  /* Initialize GPIO interrupt dispatcher */
  GPIOINT_Init();

  /* Enable GPIO in CMU */
#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif
  CMU_ClockEnable(cmuClock_GPIO, true);

  uint8_t i;
  for ( i = 0; i < HAL_BUTTON_COUNT; i++ ) {
    /* Configure pin as input */
    GPIO_PinModeSet(buttonArray[enableButtons[i]].port,
                    buttonArray[enableButtons[i]].pin,
                    BSP_BUTTON_GPIO_MODE,
                    BSP_BUTTON_GPIO_DOUT);
    /* Register callbacks before setting up and enabling pin interrupt. */
    GPIOINT_CallbackRegister(buttonArray[enableButtons[i]].pin,
                             halInternalButtonIsr);
    /* Set rising and falling edge interrupts */
    GPIO_ExtIntConfig(buttonArray[enableButtons[i]].port,
                      buttonArray[enableButtons[i]].pin,
                      buttonArray[enableButtons[i]].pin,
                      true,
                      true,
                      true);
  }
#endif
}

uint8_t halButtonState(uint8_t button)
{
  // Note: this returns the "soft" state rather than reading the port
  //  so it jives with the interrupts and their callbacks
#if (HAL_BUTTON_COUNT > 0)
  uint8_t index = halInternalButtonIndex(button);
  if ( index != HAL_BUTTON_INVALID_INDEX ) {
    return buttonState[index];
  }
#endif
  // return BUTTON_RELEASED if no matching button was found
  return BUTTON_RELEASED;
}

void halInternalButtonStateSet(uint8_t button, uint8_t state)
{
  // Note: this sets the "soft" state
  //  so it jives with the interrupts and their callbacks
#if (HAL_BUTTON_COUNT > 0)
  uint8_t index = halInternalButtonIndex(button);
  if ( index != HAL_BUTTON_INVALID_INDEX ) {
    buttonState[index] = state;
  }
#endif
}

void halInternalButtonToggleState(uint8_t button)
{
  // Note: this toggles the "soft" state
  //  so it jives with the interrupts and their callbacks
#if (HAL_BUTTON_COUNT > 0)
  uint8_t index = halInternalButtonIndex(button);
  if ( index != HAL_BUTTON_INVALID_INDEX ) {
    buttonState[index] = !buttonState[index];
  }
#endif
}

uint8_t halButtonPinState(uint8_t button)
{
#if (HAL_BUTTON_COUNT > 0)
  uint8_t index = halInternalButtonIndex(button);
  if ( index != HAL_BUTTON_INVALID_INDEX ) {
    return (GPIO_PinInGet(buttonArray[index].port, buttonArray[index].pin)) ? BUTTON_RELEASED : BUTTON_PRESSED;
  }
#endif
  return BUTTON_RELEASED;
}

//DEBOUNCE operation is based upon the theory that when multiple reads in a row
//return the same value, we have passed any debounce created by the mechanical
//action of a button.  The define "DEBOUNCE" says how many reads in a row
//should return the same value.  The value '5', below, is the recommended value
//since this should require the signal to have stabalized for approximately
//100us which should be much longer than any debounce action.
//Uncomment the following line to enable software debounce operation:
//#define DEBOUNCE 5

//Typically, software debounce is disabled by defaulting to a value of '0'
//which will cause the preprocessor to strip out the debounce code and save
//flash space.
#ifndef DEBOUNCE
#define DEBOUNCE 5
#endif//DEBOUNCE

#if (HAL_BUTTON_COUNT > 0)
void halInternalButtonIsr(uint8_t pin)
{
  uint8_t buttonStateNow;
  #if (DEBOUNCE > 0)
  uint8_t buttonStatePrev;
  uint32_t debounce;
  #endif //(DEBOUNCE > 0)

  buttonStateNow = halButtonPinState(pin);
  #if (DEBOUNCE > 0)
  //read button until get "DEBOUNCE" number of consistent readings
  for ( debounce = 0;
        debounce < DEBOUNCE;
        debounce = (buttonStateNow == buttonStatePrev) ? debounce + 1 : 0 ) {
    buttonStatePrev = buttonStateNow;
    buttonStateNow = halButtonPinState(pin);
  }
  #endif //(DEBOUNCE > 0)

  if (halButtonState(pin) != buttonStateNow) { //state changed, notify app
    halInternalButtonStateSet(pin, buttonStateNow);
    halButtonIsr(pin, halButtonState(pin));
  } else {  //state unchanged, then notify app of a double-transition
    halInternalButtonToggleState(pin); //invert temporarily for calling Isr
    halButtonIsr(pin, halButtonState(pin));
    halInternalButtonToggleState(pin); //and put it back to current state
    halButtonIsr(pin, halButtonState(pin));
  }
}

WEAK(void halButtonIsr(uint8_t button, uint8_t state)
{
})
#endif
