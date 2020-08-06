/***************************************************************************//**
 * @file
 * @brief EFM32 bootloader gpio interface
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
#include "hal.h"
#include "bootloader-common.h"
// #include "standalone-bootloader.h"
#include "bootloader-gpio.h"

#include "em_gpio.h"
#include "em_cmu.h"
#include "spi-protocol-device.h"

///////////////////////////////////////////////////////////////////
// If you edit this file, be sure to also edit bootloader-gpio.c //
///////////////////////////////////////////////////////////////////

#if !defined(BSP_BTL_BUTTON_PORT) || !defined(BSP_BTL_BUTTON_PIN)
// Default to using nWake for the bootloader recovery GPIO.
// This can be overridden in the BOARD_HEADER.
  #if defined(DISABLE_NWAKE) || (defined(HAL_CONFIG) && !defined(BSP_SPINCP_NWAKE_PIN))
    #error Please define BSP_BTL_BUTTON_PORT and BSP_BTL_BUTTON_PIN when disabling nWake
  #endif

  #if defined(BSP_BTL_BUTTON_PORT) || defined(BSP_BTL_BUTTON_PIN)
    #error Please define both BSP_BTL_BUTTON_PORT and BSP_BTL_BUTTON_PIN when overriding
  #endif

  #define BSP_BTL_BUTTON_PORT      BSP_SPINCP_NWAKE_PORT
  #define BSP_BTL_BUTTON_PIN       BSP_SPINCP_NWAKE_PIN
#endif//!defined(BSP_BTL_BUTTON_PORT) || !defined(BSP_BTL_BUTTON_PIN)

#define BUTTON_RECOVERY_SET()     GPIO_PinOutSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN)
#define BUTTON_RECOVERY_PRESSED() (GPIO_PinInGet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN) == 0)

// Function Name: bootloadForceActivation
// Description:   Decides whether to continue launching the bootloader or vector
//                to the application instead. The nWAKE pin used by the ezsp-spi
//                protocol is read and if it is low, this function returns true.
// NOTE!!!        This function is called extremely early in the boot process
//                prior to the chip being fully configured and before memory
//                is initialized, so limited functionality is available.
//                If this function returns false any state altered should
//                be returned to its reset state.
// Parameters:    none
// Returns:       false (0) if bootloader should not be launched.
//                (This will try to execute the application if possible.)
//                true (1) if bootloader should be launched.
//
bool bootloadForceActivation(void)
{
  uint32_t i;

  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  bool pressed = false;

  GPIO_PinModeSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN, gpioModeInputPull, 1);
  BUTTON_RECOVERY_SET();
  for (i = 0; i < 10; i++) {
    NO_OPERATION();
  }
  for (i = 0; i < 200; i++) {
    if (BUTTON_RECOVERY_PRESSED()) {
      pressed = true;
      break;
    }
  }

  //restore IO to its reset state
  GPIO_PinModeSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN, gpioModeDisabled, 0);
  CMU_ClockEnable(cmuClock_GPIO, false);
  return pressed;
}

//
// Function Name: bootloadGpioInit
// Description:   This function selects the chip's GPIO configuration. These
//                settings are the minimum base configuration needed to
//                support the bootloader functionality. These settings can
//                be modified for custom applications as long as the base
//                settings are preserved.
// Parameters:    none
// Returns:       none
//
void bootloadGpioInit(void)
{
  halInternalEnableWatchDog();

  #ifndef NO_LED
  halInternalInitLed();
  #endif
}

// bootloadStateIndicator
//
// Called by the bootloader state macros (in bootloader-gpio.h). Used to blink
// the LED's or otherwise signal bootloader activity.
//
// Current settings:
// Enabled: Turn on yellow activity LED on bootloader up and successful bootload
//          Turn off yellow activity LED on bootload failure
// Disabled: Blink red heartbeat LED during idle polling.
void bootloadStateIndicator(enum blState_e state)
{
  // sample state indication using LEDs
  #ifndef NO_LED
  static uint16_t pollCntr = 0;

  switch (state) {
    case BL_ST_UP:                        // bootloader up
      halSetLed(BOARD_ACTIVITY_LED);
      break;

    case BL_ST_DOWN:                      // bootloader going down
      break;

    case BL_ST_POLLING_LOOP:              // Polling for serial or radio input in
                                          // standalone bootloader.
      if (0 == pollCntr--) {
        halToggleLed(BOARD_HEARTBEAT_LED);
        pollCntr = 10000;
      }
      break;

    case BL_ST_DOWNLOAD_LOOP:             // processing download image
      halClearLed(BOARD_HEARTBEAT_LED);
      halToggleLed(BOARD_ACTIVITY_LED);
      break;

    case BL_ST_DOWNLOAD_SUCCESS:
      halSetLed(BOARD_ACTIVITY_LED);
      break;

    case BL_ST_DOWNLOAD_FAILURE:
      halClearLed(BOARD_ACTIVITY_LED);
      break;

    default:
      break;
  }
  #endif
}
