/***************************************************************************/ 
/**
 * @file sl_si91x_rgb_led_instances.c.jinja
 * @brief RGB LED Instances
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#include "sl_si91x_rgb_led.h"
#include "sl_si91x_rgb_led_config.h"

#ifdef SI917_RGB_DRIVER_OLD
sl_led_t led_red = {
  .port = SL_LED_RED_PORT,
  .pin = SL_LED_RED_PIN,
  .led_number = SL_LED_RED_NUMBER,
  .pad = SL_LED_RED_PAD,
};

sl_led_t led_green = {
  .port = SL_LED_GREEN_PORT,
  .pin = SL_LED_GREEN_PIN,
  .led_number = SL_LED_GREEN_NUMBER,
  .pad = SL_LED_GREEN_PAD,
};

sl_led_t led_blue = {
  .port = SL_LED_BLUE_PORT,
  .pin = SL_LED_BLUE_PIN,
  .led_number = SL_LED_BLUE_NUMBER,
  .pad = SL_LED_BLUE_PAD,
};
#else
  sl_led_t led_led0_red = {
    .port = SL_LED_LED0_RED_PORT,
    .pin = SL_LED_LED0_RED_PIN,
    .led_number = SL_LED_LED0_RED_NUMBER,
    .pad = SL_LED_LED0_RED_PAD,
  };

  sl_led_t led_led0_green = {
    .port = SL_LED_LED0_GREEN_PORT,
    .pin = SL_LED_LED0_GREEN_PIN,
    .led_number = SL_LED_LED0_GREEN_NUMBER,
    .pad = SL_LED_LED0_GREEN_PAD,
  };

  sl_led_t led_led0_blue = {
    .port = SL_LED_LED0_BLUE_PORT,
    .pin = SL_LED_LED0_BLUE_PIN,
    .led_number = SL_LED_LED0_BLUE_NUMBER,
    .pad = SL_LED_LED0_BLUE_PAD,
  };

  const sl_rgb_led_t led_led0 = {
    .red = &led_led0_red,
    .green = &led_led0_green,
    .blue = &led_led0_blue,
  };
#endif

void rgb_led_init_instances(void)
{
#ifdef SI917_RGB_DRIVER_OLD
sl_si91x_rgb_led_init(&led_red);
sl_si91x_rgb_led_init(&led_green);
sl_si91x_rgb_led_init(&led_blue);
#else
sl_si91x_simple_rgb_led_init(&led_led0);
#endif
}
