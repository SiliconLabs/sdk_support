/***************************************************************************//**
 * @file
 * @brief Simple Button Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_simple_button.h"
#include "sl_simple_button_config.h"

#include "gpiointerrupt.h"
#include "em_cmu.h"

#if (SL_SIMPLE_BUTTON_DEBOUNCE_BITS < 1U)
#undef SL_SIMPLE_BUTTON_DEBOUNCE_BITS
#define SL_SIMPLE_BUTTON_DEBOUNCE_BITS  1U
#endif
#if (SL_SIMPLE_BUTTON_DEBOUNCE_BITS > 15U)
#undef SL_SIMPLE_BUTTON_DEBOUNCE_BITS
#define SL_SIMPLE_BUTTON_DEBOUNCE_BITS  15U
#endif

static const uint16_t check_press = (uint16_t)(0xffff << SL_SIMPLE_BUTTON_DEBOUNCE_BITS);
static const uint16_t check_release = (uint16_t)(~(0x1 << SL_SIMPLE_BUTTON_DEBOUNCE_BITS));
static const uint16_t debounce_window = (uint16_t)(0xffff << (SL_SIMPLE_BUTTON_DEBOUNCE_BITS + 1));

extern const sl_button_t *sl_simple_button_array[];
extern const uint8_t simple_button_count;

/***************************************************************************//**
 * An internal callback called in interrupt context whenever a button changes
 * its state. (mode - SL_SIMPLE_BUTTON_MODE_INTERRUPT)
 *
 * @note The button state is updated by this function. The application callback
 * should not update it again.
 *
 * @param[in] interrupt_no      Interrupt number (pin number)
 ******************************************************************************/
static void sli_simple_button_on_change(uint8_t interrupt_no)
{
  for (uint8_t i = 0; i < simple_button_count; i++) {
    sl_simple_button_context_t *ctxt = ((sl_simple_button_context_t *)sl_simple_button_array[i]->context);
    if ( (ctxt->pin == interrupt_no) && (ctxt->state != SL_SIMPLE_BUTTON_DISABLED) ) {
      ctxt->state = ((bool)GPIO_PinInGet(ctxt->port, ctxt->pin) == SL_SIMPLE_BUTTON_POLARITY);
      sl_button_on_change(sl_simple_button_array[i]);
      break;
    }
  }
}

sl_status_t sl_simple_button_init(void *context)
{
  sl_simple_button_context_t *button = context;

  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(button->port,
                  button->pin,
                  SL_SIMPLE_BUTTON_GPIO_MODE,
                  SL_SIMPLE_BUTTON_GPIO_DOUT);

  button->state = ((bool)GPIO_PinInGet(button->port, button->pin) == SL_SIMPLE_BUTTON_POLARITY);

  if (button->mode == SL_SIMPLE_BUTTON_MODE_INTERRUPT) {
    GPIOINT_Init();
    GPIOINT_CallbackRegister(button->pin,
                             (GPIOINT_IrqCallbackPtr_t)sli_simple_button_on_change);
    GPIO_ExtIntConfig(button->port,
                      button->pin,
                      button->pin,
                      true,
                      true,
                      true);
  }

  return SL_STATUS_OK;
}

sl_button_state_t sl_simple_button_get_state(void *context)
{
  sl_simple_button_context_t *button = context;
  return button->state;
}

void sl_simple_button_poll_step(void *context)
{
  sl_simple_button_context_t *button = context;

  if (button->state == SL_SIMPLE_BUTTON_DISABLED) {
    return;
  }

  bool button_press = (bool)GPIO_PinInGet(button->port, button->pin);

  if (button->mode == SL_SIMPLE_BUTTON_MODE_POLL_AND_DEBOUNCE) {
    uint16_t history = button->history;
    history = (history << 1) | (button_press ^ SL_SIMPLE_BUTTON_POLARITY) | (debounce_window);

    if (history == check_press) {
      button->state = SL_SIMPLE_BUTTON_PRESSED;
    }
    if (history == check_release) {
      button->state = SL_SIMPLE_BUTTON_RELEASED;
    }

    button->history = history;
  } else if (button->mode == SL_SIMPLE_BUTTON_MODE_POLL) {
    button->state = (button_press == SL_SIMPLE_BUTTON_POLARITY);
  }
}

void sl_simple_button_enable(void *context)
{
  sl_simple_button_context_t *button = context;

  // Return if the button is not disabled
  if (button->state != SL_SIMPLE_BUTTON_DISABLED) {
    return;
  }

  // Clear history
  button->history = 0;
  // Reinit button
  sl_simple_button_init(button);
}

void sl_simple_button_disable(void *context)
{
  sl_simple_button_context_t *button = context;
  // Return if the button is disabled
  if (button->state == SL_SIMPLE_BUTTON_DISABLED) {
    return;
  }
  if (button->mode == SL_SIMPLE_BUTTON_MODE_INTERRUPT) {
    GPIOINT_CallbackUnRegister(button->pin);
    // Disable interrupts
    GPIO_ExtIntConfig(button->port,
                      button->pin,
                      button->pin,
                      false,
                      false,
                      false);
  }
  // Disable the button
  button->state = SL_SIMPLE_BUTTON_DISABLED;
}
