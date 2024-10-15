/***************************************************************************/ /**
 * @file sl_si91x_led_instances.h.jinja
 * @brief Button Driver Instances
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

#ifndef SL_SI91x_LED_INSTANCES_H
#define SL_SI91x_LED_INSTANCES_H

#include <stdint.h>
#include "sl_si91x_led_init_led0_config.h"
#include "sl_si91x_led_init_led1_config.h"

typedef struct {
  uint8_t pin;        ///< Pin number of the LED.
  uint8_t port;       ///< Port number of the LED.
  uint8_t led_number; ///< LED number for identification.
} sl_led_t;

extern const sl_led_t led_led0;
extern const sl_led_t led_led1;


void led_init_instances(void);

#endif // SL_SI91x_LED_INSTANCES_H