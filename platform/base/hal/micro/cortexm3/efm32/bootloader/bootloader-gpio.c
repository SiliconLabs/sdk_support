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







#if defined(USE_BUTTON_RECOVERY) || HAL_BTL_BUTTON_ENABLE
#ifndef BSP_BTL_BUTTON_PORT
// Default to using BUTTON0 or PF6 for the bootloader recovery GPIO.
// This can be overridden in the BOARD_HEADER.
  #if (BSP_BUTTON_COUNT > 0)
  #define BSP_BTL_BUTTON_PORT  BSP_BUTTON0_PORT
  #define BSP_BTL_BUTTON_PIN   BSP_BUTTON0_PIN
  #else
  #define BSP_BTL_BUTTON_PORT  gpioPortF
  #define BSP_BTL_BUTTON_PIN   6
  #endif
#endif//BSP_BTL_BUTTON_PORT
#endif//USE_BUTTON_RECOVERY

#define BUTTON_RECOVERY_SET()     GPIO_PinOutSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN)
#define BUTTON_RECOVERY_PRESSED() ((GPIO_PinInGet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN) ? false : true))

// Function Name: bootloadForceActivation
// Description:   Decides whether to continue launching the bootloader or vector
//                to the application instead. This decision is usually based on
//                some sort of GPIO logic.
//                (ie. a hardware trigger).
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
  #if defined(USE_BUTTON_RECOVERY) || HAL_BTL_BUTTON_ENABLE
  uint32_t i;
  bool pressed;
  // this provides an example of an alternative recovery mode activation
  //  method by utilizing one of the breakout board buttons
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Since the button may have decoupling caps, they may not be charged
  //  after a power-on and could give a false positive result.  To avoid
  //  this issue, drive the output as an output for a short time to charge
  //  them up as quickly as possible
  GPIO_PinModeSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN, gpioModePushPull, 1);
  BUTTON_RECOVERY_SET();
  for (i = 0; i < 100; i++) {
    NO_OPERATION();
  }

  // Reconfigure as an input with pullup to read the button state
  GPIO_PinModeSet(BSP_BTL_BUTTON_PORT, BSP_BTL_BUTTON_PIN, gpioModeInputPull, 1);
  // (IO was already set to enable the pullup above)
  // We have to delay again here so that if the button is depressed the
  //  cap has time to discharge again after being charged up
  //  by the above delay
  for (i = 0; i < 500; i++) {
    NO_OPERATION();
  }
  pressed = BUTTON_RECOVERY_PRESSED();

  return pressed;
  #else
  return false;
  #endif
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
