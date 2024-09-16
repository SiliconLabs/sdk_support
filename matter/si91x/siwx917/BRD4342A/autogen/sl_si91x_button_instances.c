/***************************************************************************/ /**
 * @file sl_si91x_button_instances.c.jinja
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

#include "sl_si91x_button_pin_config.h"
#include "sl_si91x_button_instances.h"
#include "sl_si91x_button_btn0_config.h"
#include "sl_si91x_button_btn1_config.h"

sl_button_t const button_btn0 = {
  .port = SL_BUTTON_BTN0_PORT,
  .pin = SL_BUTTON_BTN0_PIN,
  .button_number = SL_BUTTON_BTN0_NUMBER,
  #ifdef SL_BUTTON_BTN0_PAD
  .pad = SL_BUTTON_BTN0_PAD,
  #endif
  .interrupt_config = SL_BUTTON_CONFIG_BTN0_INTR
};
sl_button_t const button_btn1 = {
  .port = SL_BUTTON_BTN1_PORT,
  .pin = SL_BUTTON_BTN1_PIN,
  .button_number = SL_BUTTON_BTN1_NUMBER,
  #ifdef SL_BUTTON_BTN1_PAD
  .pad = SL_BUTTON_BTN1_PAD,
  #endif
  .interrupt_config = SL_BUTTON_CONFIG_BTN1_INTR
};

void button_init_instances(void)
{
  sl_si91x_button_init(&button_btn0);
  sl_si91x_button_init(&button_btn1);
}