/***************************************************************************//**
 * @file
 * @brief LED Driver Instances
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

#include "sl_simple_led.h"
#include "em_gpio.h"
#include "sl_simple_led_led0_config.h"
#include "sl_simple_led_led1_config.h"

/*****************************************************************************
* Device LED 0 configuration
******************************************************************************/
sl_simple_led_context_t simple_led0_context = {
  .port = SL_SIMPLE_LED_LED0_PORT,
  .pin = SL_SIMPLE_LED_LED0_PIN,
  .polarity = SL_SIMPLE_LED_LED0_POLARITY,
};

/*****************************************************************************
* Device LED 0 initialization with callback function and inturrpt
* type for LED 0
******************************************************************************/
const sl_led_t sl_led_led0 = {
  .context = &simple_led0_context,
  .init = sl_simple_led_init,
  .turn_on = sl_simple_led_turn_on,
  .turn_off = sl_simple_led_turn_off,
  .toggle = sl_simple_led_toggle,
  .get_state = sl_simple_led_get_state,
};

/*****************************************************************************
* Device LED 1 configuration
******************************************************************************/
sl_simple_led_context_t simple_led1_context = {
  .port = SL_SIMPLE_LED_LED1_PORT,
  .pin = SL_SIMPLE_LED_LED1_PIN,
  .polarity = SL_SIMPLE_LED_LED1_POLARITY,
};

/*****************************************************************************
* Device LED 1 initialization with callback function and inturrpt
* type for LED 1
******************************************************************************/
const sl_led_t sl_led_led1 = {
  .context = &simple_led1_context,
  .init = sl_simple_led_init,
  .turn_on = sl_simple_led_turn_on,
  .turn_off = sl_simple_led_turn_off,
  .toggle = sl_simple_led_toggle,
  .get_state = sl_simple_led_get_state,
};

/*****************************************************************************
*  Notify Device LED related handlers
******************************************************************************/
const sl_led_t *sl_simple_led_array[] = {
  &sl_led_led0,
  &sl_led_led1
};

/*****************************************************************************
*  Notify Device LED 0 and 1 initialization
*
* @param void
******************************************************************************/
void sl_simple_led_init_instances(void)
{
  sl_led_init(&sl_led_led0);
  sl_led_init(&sl_led_led1);
}
