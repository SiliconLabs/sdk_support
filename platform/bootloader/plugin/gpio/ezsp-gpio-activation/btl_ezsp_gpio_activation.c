/***************************************************************************//**
 * @file
 * @brief EZSP GPIO Activation plugin for Silicon Labs bootloader.
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

#include "config/btl_config.h"

#include "em_device.h"
#include "em_gpio.h"
#include "btl_ezsp_gpio_activation.h"

// Map GPIO activation polarity settings to GPIO pin states
#define HIGH 0
#define LOW  1

bool ezsp_gpio_enterBootloader(void)
{
  bool pressed;

#if defined(CMU_HFBUSCLKEN0_GPIO)
  // Enable GPIO clock
  CMU->HFBUSCLKEN0 |= CMU_HFBUSCLKEN0_GPIO;
#endif
#if defined(_CMU_CLKEN0_MASK)
  // Enable GPIO clock
  CMU->CLKEN0_SET = CMU_CLKEN0_GPIO;
#endif

  // Reconfigure as an input with pull(up|down) to read the nWake state
  GPIO_PinModeSet(BSP_SPINCP_NWAKE_PORT,
                  BSP_SPINCP_NWAKE_PIN,
                  gpioModeInputPull,
                  BTL_EZSP_GPIO_ACTIVATION_POLARITY);

  pressed = GPIO_PinInGet(BSP_SPINCP_NWAKE_PORT, BSP_SPINCP_NWAKE_PIN)
            != BTL_EZSP_GPIO_ACTIVATION_POLARITY;

  // Disable GPIO pin
  GPIO_PinModeSet(BSP_SPINCP_NWAKE_PORT,
                  BSP_SPINCP_NWAKE_PIN,
                  gpioModeDisabled,
                  BTL_EZSP_GPIO_ACTIVATION_POLARITY);

#if defined(CMU_HFBUSCLKEN0_GPIO)
  // Disable GPIO clock
  CMU->HFBUSCLKEN0 &= ~CMU_HFBUSCLKEN0_GPIO;
#endif

  return pressed;
}
