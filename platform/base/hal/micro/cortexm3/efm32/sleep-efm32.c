/***************************************************************************//**
 * @file
 * @brief EFM32/EFR32 specific sleep functions.
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
#include "sleep-efm32.h"
#include "hal/micro/micro.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "serial/com.h"
#include "watchdog.h"
#include "em_wdog.h"

#if defined(RTCC_PRESENT) && (RTCC_COUNT == 1)
#define SYSTIMER_IRQ_N   RTCC_IRQn
#else
#define SYSTIMER_IRQ_N   RTC_IRQn
#endif

static WakeEvents wakeInfo;
static Em4WakeupCause_t em4WakeupCause;

WakeEvents halGetWakeInfo(void)
{
  return wakeInfo;
}

const Em4WakeupCause_t * halInternalEm4WakeupCause(void)
{
  return &em4WakeupCause;
}

void halInternalEm4Wakeup(void)
{
  uint32_t gpioEm4Flags = 0;

#if defined(_GPIO_IF_EM4WU_MASK)
  gpioEm4Flags = GPIO_IntGet() & _GPIO_IF_EM4WU_MASK;
  GPIO_IntClear(gpioEm4Flags);
#elif defined(_GPIO_EM4WUCAUSE_MASK)
  gpioEm4Flags = GPIO->EM4WUCAUSE & _GPIO_EM4WUCAUSE_MASK;
#endif

  em4WakeupCause.gpioFlags = gpioEm4Flags;
}

/**
 * @brief Check if an interrupt is triggered
 *
 * @details This function checks if an interrupt is enabled and pending
 *
 * @param  [in] IRQn Interrupt number
 *
 * @return true   Interrupt is triggered
 *         false  Interrupt is not triggered
 */
static bool irqTriggered(IRQn_Type IRQn)
{
  return NVIC_GetPendingIRQ(IRQn) && NVIC_GetEnableIRQ(IRQn);
}

static void halInternalSleepHelper(SleepModes sleepMode, bool preserveIntState)
{
  bool watchdogDisableInSleep;

  // SLEEPMODE_POWERDOWN and SLEEPMODE_POWERSAVE are deprecated.  Remap them
  // to their appropriate, new mode name.
  if (sleepMode == SLEEPMODE_POWERDOWN) {
    sleepMode = SLEEPMODE_MAINTAINTIMER;
  } else if (sleepMode == SLEEPMODE_POWERSAVE) {
    sleepMode = SLEEPMODE_WAKETIMER;
  }

  halSleepCallback(true, sleepMode);
  // Disable and restore watchdog if already on and going for EM1 sleep,
  // since we can't clear it asleep in EM1. The watchdog is frozen in
  // EM2 and 3 and disabling it while in EM2 and 3 sleep is not needed.
  watchdogDisableInSleep = halInternalWatchDogEnabled()
                           && (sleepMode == SLEEPMODE_IDLE);

  if (watchdogDisableInSleep) {
    halInternalDisableWatchDog(MICRO_DISABLE_WATCH_DOG_KEY);
  } else if (halInternalWatchDogEnabled()) {
    halInternalWatchDogSleep();
  }

  // BASEPRI is set to 0 in order to allow interrupts to wakeup the MCU
  // PRIMASK is set to 1 in order to block interrupt handler when MCU wakes up.
  uint32_t primask = __get_PRIMASK();
  __set_PRIMASK(1);
#if (__CORTEX_M >= 3)
  uint32_t basepri = __get_BASEPRI();
  __set_BASEPRI(0);
#endif

#if !(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))
  // For DMP NCP applications UART interrupt switching (on/off)
  // happens before/after zigbee task yields/resumes respectively.
  COM_InternalPowerDown(sleepMode == SLEEPMODE_IDLE);
#endif //!(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))
  wakeInfo = 0;

#ifdef BOOTLOADER_OPEN
  #error no bootloader support yet
#endif

  switch (sleepMode) {
    case SLEEPMODE_IDLE:
      EMU_EnterEM1();
      break;
    // there is no difference between wake/maintain timer
    case SLEEPMODE_WAKETIMER:
    case SLEEPMODE_MAINTAINTIMER:
      EMU_EnterEM2(true);
      break;
    case SLEEPMODE_NOTIMER:
      EMU_EnterEM3(true);
      break;
    case SLEEPMODE_HIBERNATE:
      EMU_EnterEM4();
      break;
    default:
      //Oops!  Invalid sleepMode parameter.
      assert(0);
      break;
  }

#if defined (_SILICON_LABS_32B_SERIES_2_CONFIG_2) && !defined (_GPIO_IF_EXT_MASK)
  // Series 2, config 2 devices use multiple masks for
  // all the IF EXT sources.  Earlier devices use a single IF EXT mask.
  #define _GPIO_IF_EXT_MASK (_GPIO_IF_EXTIF0_MASK    \
                             | _GPIO_IF_EXTIF1_MASK  \
                             | _GPIO_IF_EXTIF2_MASK  \
                             | _GPIO_IF_EXTIF3_MASK  \
                             | _GPIO_IF_EXTIF4_MASK  \
                             | _GPIO_IF_EXTIF5_MASK  \
                             | _GPIO_IF_EXTIF6_MASK  \
                             | _GPIO_IF_EXTIF7_MASK  \
                             | _GPIO_IF_EXTIF8_MASK  \
                             | _GPIO_IF_EXTIF9_MASK  \
                             | _GPIO_IF_EXTIF10_MASK \
                             | _GPIO_IF_EXTIF11_MASK)
#endif // _GPIO_IF_EXT_MASK
  wakeInfo = GPIO_IntGetEnabled() & _GPIO_IF_EXT_MASK;
  if (irqTriggered(GPIO_EVEN_IRQn) || irqTriggered(GPIO_ODD_IRQn)) {
    wakeInfo |= WAKE_IRQ_GPIO;
  }
  if (irqTriggered(SYSTIMER_IRQ_N)) {
    wakeInfo |= WAKE_IRQ_SYSTIMER;
  }
#if defined(RFSENSE_PRESENT) && (RFSENSE_COUNT == 1)
  if (irqTriggered(RFSENSE_IRQn)) {
    wakeInfo |= WAKE_IRQ_RFSENSE;
  }
#endif

  // restart watchdog if it was running when we entered sleep
  // do this before dispatching interrupts while we still have tight
  // control of code execution
  if (watchdogDisableInSleep) {
    WDOGn_Enable(DEFAULT_WDOG, true);
  }

#if !(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))
  // For DMP NCP applications UART interrupt switching (on/off)
  // happens before/after zigbee task yields/resumes respectively.
  COM_InternalPowerUp(sleepMode == SLEEPMODE_IDLE);
#endif  //!(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))

  if (preserveIntState) { // RTOS-friendly scheme to preserve interrupt state
    // Restore BASEPRI and PRIMASK to previous levels.
  #if (__CORTEX_M >= 3)
    __set_BASEPRI(basepri);
  #endif
    __set_PRIMASK(primask);
  } else { // emberHAL-compatible scheme enabling interrupts per API expectation
    // Clear PRIMASK to enable all interrupts. Note that after this
    // point BASEPRI=0 and PRIMASK=0 which means that all interrupts
    // are enabled. The interrupt state is not saved/restored due to
    // historical API restrictions.
    __set_PRIMASK(0);
  }
  halSleepCallback(false, sleepMode);
}

void halInternalSleep(SleepModes sleepMode)
{
  halInternalSleepHelper(sleepMode, false);
}

#if defined (_SILICON_LABS_32B_SERIES_2_CONFIG_2) && !defined (_GPIO_IEN_EXT_MASK)
// Series 2, config 2 devices use multiple masks for
// all IEN EXT sources.  Earlier devices use a single IEN EXT mask.
#define _GPIO_IEN_EXT_MASK (_GPIO_IEN_EXTIEN0_MASK    \
                            | _GPIO_IEN_EXTIEN1_MASK  \
                            | _GPIO_IEN_EXTIEN2_MASK  \
                            | _GPIO_IEN_EXTIEN3_MASK  \
                            | _GPIO_IEN_EXTIEN4_MASK  \
                            | _GPIO_IEN_EXTIEN5_MASK  \
                            | _GPIO_IEN_EXTIEN6_MASK  \
                            | _GPIO_IEN_EXTIEN7_MASK  \
                            | _GPIO_IEN_EXTIEN8_MASK  \
                            | _GPIO_IEN_EXTIEN9_MASK  \
                            | _GPIO_IEN_EXTIEN10_MASK \
                            | _GPIO_IEN_EXTIEN11_MASK)
// Series 1 devices use _GPIO_IEN_EXT_MASK and series 2, config 1 devices use
// an identical mask renamed to _GPIO_IEN_EXTIEN_MASK.
#elif defined (_SILICON_LABS_32B_SERIES_2) && !defined (_GPIO_IEN_EXT_MASK)
#define _GPIO_IEN_EXT_MASK _GPIO_IEN_EXTIEN_MASK
#endif

void halSleepWithOptions(SleepModes sleepMode, WakeMask wakeMask)
{
  uint32_t gpioIen = GPIO->IEN & _GPIO_IEN_EXT_MASK;
  GPIO->IEN = (GPIO->IEN & ~(_GPIO_IEN_EXT_MASK))
              | (wakeMask & _GPIO_IEN_EXT_MASK);
  halInternalSleep(sleepMode);
  GPIO->IEN = (GPIO->IEN & ~(_GPIO_IEN_EXT_MASK))
              | (gpioIen & _GPIO_IEN_EXT_MASK);
}

void halSleep(SleepModes sleepMode)
{
  halInternalSleep(sleepMode);
}

// RTOS-friendly APIs that restore interrupt state upon waking
void halSleepWithOptionsPreserveInts(SleepModes sleepMode, WakeMask wakeMask)
{
  uint32_t gpioIen = GPIO->IEN & _GPIO_IEN_EXT_MASK;
  GPIO->IEN = (GPIO->IEN & ~(_GPIO_IEN_EXT_MASK))
              | (wakeMask & _GPIO_IEN_EXT_MASK);
  halInternalSleepHelper(sleepMode, true);
  GPIO->IEN = (GPIO->IEN & ~(_GPIO_IEN_EXT_MASK))
              | (gpioIen & _GPIO_IEN_EXT_MASK);
  // N.B. If interrupts were disabled upon entry, any GPIOs in wakeMask
  // that were newly enabled (not in gpioIen) and caused the wakeup
  // will *not* trigger their ISR handler because interrupts remain
  // disabled here and those wakeMask GPIOs were just disabled by the
  // GPIO IEN restoration above.  They will, however, be represented
  // by WAKE_IRQ_GPIO in halGetWakeInfo().
}

void halSleepPreserveInts(SleepModes sleepMode)
{
  halInternalSleepHelper(sleepMode, true);
}
