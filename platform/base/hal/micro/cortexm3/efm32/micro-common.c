/***************************************************************************//**
 * @file
 * @brief EFM micro specific HAL functions common to full and minimal hal
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
#include "em_device.h"
#include "em_wdog.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_rmu.h"
#include "em_gpio.h"

#include "include/error.h"
#include "hal/micro/micro-common.h"
#include "hal/micro/cortexm3/efm32/micro-common.h"
#include "hal/plugin/adc/adc.h"
#include "ustimer.h"
#include "watchdog.h"

#if defined(BOARD_HEADER) && !defined(MINIMAL_HAL)
  #include BOARD_HEADER
#endif //defined(BOARD_HEADER)

// -----------------------------------------------------------------------------
// Watchdog Functions
#if defined(WDOG_IF_WARN) && !defined(BOOTLOADER)
void WDOG0_IRQHandler(void)
{
  NMI_Handler();
}

#endif

void halInternalEnableWatchDog(void)
{
  /* Enable LE interface */
#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_CORELE, true);
  CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  CMU_ClockEnable(cmuClock_WDOG0, true);
#endif

  /* Make sure FULL reset is used on WDOG timeout */
#if defined(_RMU_CTRL_WDOGRMODE_MASK)
  RMU_ResetControl(rmuResetWdog, rmuResetModeFull);
#endif

  /* Trigger watchdog reset after 2 seconds (64k / 32k)
   * warning interrupt is triggered after 1.5 seconds (75% of timeout). */
  WDOG_Init_TypeDef init = WDOG_INIT_DEFAULT;
  init.enable = true;
  init.perSel = wdogPeriod_64k;
  init.warnSel = wdogWarnTime75pct;

#if defined(_WDOG_CTRL_CLKSEL_MASK)
  init.clkSel = wdogClkSelLFRCO;
#else
  // Series 2 devices select watchdog oscillator with the CMU.
  CMU_ClockSelectSet(cmuClock_WDOG0, cmuSelect_LFRCO);
#endif

  WDOGn_Init(DEFAULT_WDOG, &init);

  /* Enable WARN interrupt. */
#if defined(WDOG_IF_WARN) && !defined(BOOTLOADER)
  NVIC_ClearPendingIRQ(WDOG0_IRQn);
  WDOGn_IntClear(DEFAULT_WDOG, WDOG_IF_WARN);
  NVIC_EnableIRQ(WDOG0_IRQn);
  WDOGn_IntEnable(DEFAULT_WDOG, WDOG_IEN_WARN);
#endif
}

void halInternalResetWatchDog(void)
{
  WDOGn_Feed(DEFAULT_WDOG);
}

void halInternalDisableWatchDog(uint8_t magicKey)
{
  if ( magicKey == MICRO_DISABLE_WATCH_DOG_KEY ) {
    WDOGn_Enable(DEFAULT_WDOG, false);
  }
}

bool halInternalWatchDogEnabled(void)
{
  return WDOGn_IsEnabled(DEFAULT_WDOG);
}

void halInternalWatchDogSleep(void)
{
  // Wait for potential watchdog reset commands to finish. Watchdog commands
  // in progress while entering EM2 will be aborted unless we wait for the
  // syncbusy flag to clear.
  while (DEFAULT_WDOG->SYNCBUSY != 0U) {
  }
}

//------------------------------------------------------------------------------
// GPIO Functions

void halGpioSetConfig(uint32_t gpio, HalGpioCfg_t config)
{
  GPIO_PinModeSet(GPIO_PORT(gpio), GPIO_PIN(gpio),
                  (GPIO_Mode_TypeDef)config, halGpioReadOutput(gpio));
}

HalGpioCfg_t halGpioGetConfig(uint32_t gpio)
{
  // Unfortunately, there is no emlib API for this
  uint8_t port = GPIO_PORT(gpio);
  uint8_t pin  = GPIO_PIN(gpio);
  assert(GPIO_PORT_PIN_VALID(port, pin));
  return (HalGpioCfg_t)
         ((BUS_RegMaskedRead((pin < 8) ? &GPIO->P[port].MODEL
                             : &GPIO->P[port].MODEH,
                             0xF << ((pin % 8) * 4))) >> ((pin % 8) * 4));
}

void halGpioClear(uint32_t gpio)
{
  GPIO_PinOutClear(GPIO_PORT(gpio), GPIO_PIN(gpio));
}

void halGpioSet(uint32_t gpio)
{
  GPIO_PinOutSet(GPIO_PORT(gpio), GPIO_PIN(gpio));
}

uint32_t halGpioRead(uint32_t gpio)
{
  return GPIO_PinInGet(GPIO_PORT(gpio), GPIO_PIN(gpio));
}

uint32_t halGpioReadOutput(uint32_t gpio)
{
  return GPIO_PinOutGet(GPIO_PORT(gpio), GPIO_PIN(gpio));
}
