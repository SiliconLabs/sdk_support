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
// Define module name for Power Manager debuging feature.
#define CURRENT_MODULE_NAME    "BASE"

#include PLATFORM_HEADER
#include "sleep-efm32.h"
#include "sl_power_manager.h"
#include "hal/micro/micro.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "serial/com.h"
#include "watchdog.h"
#include "em_wdog.h"

#ifdef BOOTLOADER_OPEN
#error no bootloader support yet
#endif

#if defined(RTCC_PRESENT) && (RTCC_COUNT == 1)
#define SYSTIMER_IRQ_N   RTCC_IRQn
#elif defined(SYSRTC_PRESENT)
#warning ToDo: Figure out how to use SYSRTC for bobcat
#define SYSTIMER_IRQ_N   SYSRTC_APP_IRQn
#else
#define SYSTIMER_IRQ_N   RTC_IRQn
#endif

#if defined (_SILICON_LABS_32B_SERIES_2_CONFIG_2) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)
// On series 2, config 2 parts, the device headers define separate masks for
// each pin interrupt. Device headers for earlier parts define a single
// combined mask.
  #define _GPIO_IF_EXT_MASK   (_GPIO_IF_EXTIF0_MASK    \
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

  #define _GPIO_IEN_EXT_MASK  (_GPIO_IEN_EXTIEN0_MASK    \
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

#elif (defined (_SILICON_LABS_32B_SERIES_2) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_4)) && !defined (_GPIO_IEN_EXT_MASK)
// On series 2, config 1 devices, the pin interrupt mask was renamed (relative
// to series 1).
  #define _GPIO_IEN_EXT_MASK  _GPIO_IEN_EXTIEN_MASK
#endif

// EM Events
#define SLEEP_EM_EVENT_MASK      (SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM0   \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM0  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM1 \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM1  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM2 \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2  \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_ENTERING_EM3 \
                                  | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3)

static void events_handler(sl_power_manager_em_t from,
                           sl_power_manager_em_t to);

static sl_power_manager_em_transition_event_info_t events_info =
{
  .event_mask = SLEEP_EM_EVENT_MASK,
  .on_event = events_handler,
};

static sl_power_manager_em_transition_event_handle_t events_handle;
static WakeEvents wakeInfo;
static Em4WakeupCause_t em4WakeupCause;
static bool watchdogDisableInSleep;

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

void halEnergyModeNotificationInit(void)
{
  sl_status_t result = sl_power_manager_init();

  assert(result == SL_STATUS_OK);

  sl_power_manager_subscribe_em_transition_event(&events_handle,
                                                 &events_info);
}

/**
 * @brief On All Events callback
 *
 * @param from EM level from where we start from
 *
 * @param to   EM level where we are going
 */
static void events_handler(sl_power_manager_em_t from,
                           sl_power_manager_em_t to)
{
  if (from == SL_POWER_MANAGER_EM0) {
    wakeInfo = 0;

#if !(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))
    // For DMP NCP applications UART interrupt switching (on/off)
    // happens before/after zigbee task yields/resumes respectively.
    COM_InternalPowerDown(to == SLEEPMODE_IDLE);
#endif //!(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))

    switch (to) {
      case SL_POWER_MANAGER_EM1:
        halSleepCallback(true, SLEEPMODE_IDLE);
        watchdogDisableInSleep = halInternalWatchDogEnabled();
        if (watchdogDisableInSleep) {
          halInternalDisableWatchDog(MICRO_DISABLE_WATCH_DOG_KEY);
        }

        COM_InternalPowerDown(true);
        break;

      case SL_POWER_MANAGER_EM0:
        break;

      case SL_POWER_MANAGER_EM2:
        halSleepCallback(true, SLEEPMODE_WAKETIMER);
        if (halInternalWatchDogEnabled()) {
          halInternalWatchDogSleep();
        }
        break;

      case SL_POWER_MANAGER_EM3:
        halSleepCallback(true, SLEEPMODE_NOTIMER);
        if (halInternalWatchDogEnabled()) {
          halInternalWatchDogSleep();
        }
        break;

      case SL_POWER_MANAGER_EM4:
        halSleepCallback(true, SLEEPMODE_HIBERNATE);
        break;

      default:
        break;
    }
  } else {
    // restart watchdog if it was running when we entered sleep
    // do this before dispatching interrupts while we still have tight
    // control of code execution
    if (watchdogDisableInSleep) {
      WDOGn_Enable(DEFAULT_WDOG, true);
    }

#if !(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))
    // For DMP NCP applications UART interrupt switching (on/off)
    // happens before/after zigbee task yields/resumes respectively.
    COM_InternalPowerUp(from == SLEEPMODE_IDLE);
#endif  //!(defined(EMBER_AF_NCP) && defined(EMBER_STACK_ZIGBEE) && defined(MICRIUMOS))

    switch (from) {
      case SL_POWER_MANAGER_EM1:
        COM_InternalPowerUp(true);
        halSleepCallback(false, SLEEPMODE_IDLE);
        break;

      case SL_POWER_MANAGER_EM0:
        break;

      case SL_POWER_MANAGER_EM2:
        halSleepCallback(false, SLEEPMODE_WAKETIMER);
        break;

      case SL_POWER_MANAGER_EM3:
        halSleepCallback(false, SLEEPMODE_NOTIMER);
        break;

      case SL_POWER_MANAGER_EM4:
        halSleepCallback(false, SLEEPMODE_HIBERNATE);
        break;

      default:
        break;
    }
  }
}

void sli_power_manager_on_wakeup(void)
{
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
}

#if defined(SL_KERNEL_PRESENT)
bool OSCanReturnToSleep(void)
{
  return false;
}
#endif

void halInternalSleep(SleepModes sleepMode)
{
  sl_power_manager_em_t em_power = SL_POWER_MANAGER_EM0;

  if (sleepMode == SLEEPMODE_IDLE) {
    em_power = SL_POWER_MANAGER_EM1;
  } else if (sleepMode == SLEEPMODE_WAKETIMER
             || sleepMode == SLEEPMODE_MAINTAINTIMER) {
    em_power = SL_POWER_MANAGER_EM2;
  } else if (sleepMode == SLEEPMODE_NOTIMER) {
    em_power = SL_POWER_MANAGER_EM3;
  } else if (sleepMode == SLEEPMODE_HIBERNATE) {
    // Only a power on reset or external reset pin can wake the device from EM4.
    EMU_EnterEM4();
  }

  //Add a requirement
  sl_power_manager_add_em_requirement(em_power);

  // The sleep functions will often be entered with interrupts turned off (via
  // BASEPRI). Our API documentation states that these functions will exit with
  // interupts on. Furthermore, Cortex-M processors will not wake up from an IRQ
  // if it's blocked by the current BASEPRI. However, we still want to run some
  // ode (including capturing the wake reasons) after waking but before
  // interrupts run. We therefore will enter sleep with PRIMASK set and BASEPRI
  // cleared.
  CORE_CriticalDisableIrq();
  INTERRUPTS_ON();

  //Go to sleep
  sl_power_manager_sleep();

  // Renable interrupts.
  CORE_CriticalEnableIrq();

  //Remove the previous requirement
  sl_power_manager_remove_em_requirement(em_power);
}

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
  halInternalSleep(sleepMode);
  GPIO->IEN = (GPIO->IEN & ~(_GPIO_IEN_EXT_MASK))
              | (gpioIen & _GPIO_IEN_EXT_MASK);
  // N.B. If interrupts were disabled upon entry, any GPIOs in wakeMask
  // that were newly enabled (not in gpioIen) and caused the wakeup
  // will *not* trigger their ISR handler because interrupts remain
  // disabled here and those wakeMask GPIOs were just disabled by the
  // GPIO IEN restoration above.
}

void halSleepPreserveInts(SleepModes sleepMode)
{
  halInternalSleep(sleepMode);
}
