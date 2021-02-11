/***************************************************************************//**
 * @file base-replacement.c
 * @brief Legacy HAL
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories, Inc, www.silabs.com</b>
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

#include <stdio.h>
#include "hal.h"
#include "em_chip.h"
#include "tempdrv.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "pa_conversions_efr32.h"
#include "sl_iostream.h"
#include "ustimer.h"
#include "sl_sleeptimer.h"
#include "em_wdog.h"
#include "em_rmu.h"
#include "sl_iostream_handles.h"
#include "sl_power_manager.h"
#include "rail.h"
#include "sl_status.h"
#include "sl_component_catalog.h"
#include "sl_token_api.h"

#if defined(SL_CATALOG_IOSTREAM_VUART_PRESENT)
#include "sl_iostream_vuart.h"
#endif

#if defined(SL_CATALOG_LED_PRESENT)
#include "sl_led.h"
#endif

#define EMBER_SUCCESS             (0x00u)
#define EMBER_ERR_FATAL           (0x01u)
#define EMBER_SLEEP_INTERRUPTED   (0x85u)

// System timer / sleeptimer
uint16_t halCommonGetInt16uMillisecondTick(void)
{
  return (uint16_t)halCommonGetInt64uMillisecondTick();
}

uint32_t halCommonGetInt32uMillisecondTick(void)
{
  return (uint32_t)halCommonGetInt64uMillisecondTick();
}

uint64_t halCommonGetInt64uMillisecondTick(void)
{
  uint64_t ms;

  assert(sl_sleeptimer_tick64_to_ms(sl_sleeptimer_get_tick_count64(),
                                    &ms) == SL_STATUS_OK);
  return ms;
}

uint16_t halCommonGetInt16uQuarterSecondTick(void)
{
  uint32_t ticks = halCommonGetInt32uMillisecondTick();
  ticks /= MILLISECOND_TICKS_PER_QUARTERSECOND;
  return (uint16_t)ticks;
}

bool sl_legacy_hal_is_ok_to_sleep(void)
{
  return true;
}

sl_power_manager_on_isr_exit_t sl_legacy_hal_sleep_on_isr_exit(void)
{
  return SL_POWER_MANAGER_WAKEUP;
}

void halCommonDelayMicroseconds(uint16_t us)
{
  USTIMER_DelayIntSafe(us);
}

void halCommonDelayMilliseconds(uint16_t ms)
{
  while (ms-- != 0U) {
    halCommonDelayMicroseconds(1000u);
  }
}

uint16_t halInternalStartSystemTimer(void)
{
  USTIMER_Init();
  if (sl_sleeptimer_init() != SL_STATUS_OK) {
    assert(0);
  }
  return 0;
}

void halInit(void)
{
  halInternalClassifyReset();

  //Fill the unused portion of the memory reserved for the stack.
  //memset() is not being used to do this in case it uses the stack
  //to store the return address.
  volatile uint32_t *dataDestination;
  //This code assumes that the __get_MSP() return value and
  //_CSTACK_SEGMENT_BEGIN are both 32-bit aligned values.
  dataDestination = (uint32_t*) (__get_MSP() - 4U);
  //Start at current stack ptr fill up until CSTACK_SEGMENT_BEGIN
  while (dataDestination >= _CSTACK_SEGMENT_BEGIN) {
    //Fill with magic value interpreted by C-SPY's Stack View
    *dataDestination-- = STACK_FILL_VALUE;
  }

  TEMPDRV_Init();
  EMU_UnlatchPinRetention();

  halInternalStartSystemTimer();

  RAIL_InitTxPowerCurvesAlt(&RAIL_TxPowerCurvesVbat);
}

// Watchdog functions

void halInternalEnableWatchDog(void)
{
  // Enable LE interface
#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFLE, true);
  CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);
#endif

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  CMU_ClockEnable(cmuClock_WDOG0, true);
#endif

  // Make sure FULL reset is used on WDOG timeout
#if defined(_RMU_CTRL_WDOGRMODE_MASK)
  RMU_ResetControl(rmuResetWdog, rmuResetModeFull);
#endif

  WDOG_Init_TypeDef init = WDOG_INIT_DEFAULT;

#if defined(_WDOG_CTRL_CLKSEL_MASK)
  init.clkSel = wdogClkSelLFRCO;
#else
  // Series 2 devices select watchdog oscillator with the CMU.
  CMU_ClockSelectSet(cmuClock_WDOG0, cmuSelect_LFRCO);
#endif

  WDOGn_Init(DEFAULT_WDOG, &init);
}

void halResetWatchdog(void)
{
#if defined(_CMU_HFBUSCLKEN0_LE_MASK)
  if ((CMU->HFBUSCLKEN0 & _CMU_HFBUSCLKEN0_LE_MASK) != 0) {
    WDOGn_Feed(DEFAULT_WDOG);
  }
#elif defined(_CMU_CLKEN0_WDOG0_MASK)
  if ((CMU->CLKEN0 & _CMU_CLKEN0_WDOG0_MASK) != 0) {
    WDOGn_Feed(DEFAULT_WDOG);
  }
#else
  WDOGn_Feed(DEFAULT_WDOG);
#endif
}

void halInternalDisableWatchDog(uint8_t magicKey)
{
#if defined(_CMU_HFBUSCLKEN0_LE_MASK)
  if ((CMU->HFBUSCLKEN0 & _CMU_HFBUSCLKEN0_LE_MASK) != 0) {
    if ( magicKey == MICRO_DISABLE_WATCH_DOG_KEY ) {
      WDOGn_Enable(DEFAULT_WDOG, false);
    }
  }
#elif defined(_CMU_CLKEN0_WDOG0_MASK)
  if ((CMU->CLKEN0 & _CMU_CLKEN0_WDOG0_MASK) != 0) {
    if ( magicKey == MICRO_DISABLE_WATCH_DOG_KEY ) {
      WDOGn_Enable(DEFAULT_WDOG, false);
    }
  }
#else
  if ( magicKey == MICRO_DISABLE_WATCH_DOG_KEY ) {
    WDOGn_Enable(DEFAULT_WDOG, false);
  }
#endif
}

bool halInternalWatchDogEnabled(void)
{
#if defined(_CMU_HFBUSCLKEN0_LE_MASK)
  if ((CMU->HFBUSCLKEN0 & _CMU_HFBUSCLKEN0_LE_MASK) != 0) {
    return WDOGn_IsEnabled(DEFAULT_WDOG);
  } else {
    return 0;
  }
#elif defined(_CMU_CLKEN0_WDOG0_MASK)
  if ((CMU->CLKEN0 & _CMU_CLKEN0_WDOG0_MASK) != 0) {
    return WDOGn_IsEnabled(DEFAULT_WDOG);
  } else {
    return 0;
  }
#else
  return WDOGn_IsEnabled(DEFAULT_WDOG);
#endif
}

void halReboot(void)
{
  halInternalSysReset(RESET_SOFTWARE_REBOOT);
}

// Memory functions

void halCommonMemMove(void *dest, const void *src, uint16_t bytes)
{
  uint8_t *d = (uint8_t *)dest;
  uint8_t *s = (uint8_t *)src;

  if (d > s) {
    d += bytes - 1;
    s += bytes - 1;
    #ifndef _HAL_SMALL_MEMUTILS_
    while (bytes >= 4) {
      bytes -= 4;
      *d-- = *s--;
      *d-- = *s--;
      *d-- = *s--;
      *d-- = *s--;
    }
    #endif // _HAL_SMALL_MEMUTILS_
    for (; bytes != 0U; bytes--) {
      *d-- = *s--;
    }
  } else {
    #ifndef _HAL_SMALL_MEMUTILS_
    while (bytes >= 4) {
      bytes -= 4;
      *d++ = *s++;
      *d++ = *s++;
      *d++ = *s++;
      *d++ = *s++;
    }
    #endif // _HAL_SMALL_MEMUTILS_
    for (; bytes != 0U; bytes--) {
      *d++ = *s++;
    }
  }
}

int16_t halCommonMemCompare(const void *source0, const void *source1, uint16_t bytes)
{
  uint8_t *s0 = (uint8_t *)source0;
  uint8_t *s1 = (uint8_t *)source1;

  while (0 < bytes) {
    uint8_t b0 = *s0;
    uint8_t b1 = *s1;
    if (b0 != b1) {
      return b0 - b1;
    }
    bytes--;
    s0++;
    s1++;
  }
  return 0;
}

void halCommonMemSet(void *dest, uint8_t val, uint16_t bytes)
{
  uint8_t *d = (uint8_t *)dest;

  for (; bytes != 0U; bytes--) {
    *d++ = val;
  }
}

int8_t halCommonMemPGMCompare(const void *source0, const void PGM_NO_CONST *source1, uint16_t bytes)
{
  return halCommonMemCompare(source0, source1, bytes);
}

void halCommonMemPGMCopy(void* dest, const void PGM_NO_CONST *source, uint16_t bytes)
{
  halCommonMemMove(dest, source, bytes);
}

uint32_t halInternalGetCStackBottom(void)
{
  return (uint32_t)(uint8_t *)_CSTACK_SEGMENT_BEGIN;
}

// These variables are defined by the stack in ember-configuration.c
extern uint16_t heapMemory[];
extern const uint32_t heapMemorySize;

uint32_t halInternalGetHeapTop(void)
{
  return (uint32_t)((uint8_t *)heapMemory) + heapMemorySize;
}

uint32_t halInternalGetHeapBottom(void)
{
  return (uint32_t)(uint8_t *)heapMemory;
}

WEAK(void halRadioPowerUpHandler(void))
{
  // Intentionally empty.
  // This function is implemented here weakly as a fallback when it is not
  // overridden. It is called below by halStackRadioPowerMainControl.
}

WEAK(void halRadioPowerDownHandler(void))
{
  // Intentionally empty.
  // This function is implemented here weakly as a fallback when it is not
  // overridden. It is called below by halStackRadioPowerMainControl.
}

void halStackRadioPowerMainControl(bool powerUp)
{
  if (powerUp) {
    halRadioPowerUpHandler();
  } else {
    halRadioPowerDownHandler();
  }
}

void halStackRadioPowerUpBoard(void)
{
  // Intentionally empty.
  // This function is defined here only to provide compatibility for code that
  // may also link against legacy RF coexistence implementations.
}

void halStackRadioPowerDownBoard(void)
{
  // Intentionally empty.
  // This function is defined here only to provide compatibility for code that
  // may also link against legacy RF coexistence implementations.
}

#if !defined(BOARD_ACTIVITY_LED)
  #if defined(SL_CATALOG_BOARD_ACTIVITY_PRESENT)
    #define BOARD_ACTIVITY_LED  sl_led_board_activity
  #elif defined(SL_CATALOG_LED0_PRESENT)
    #define BOARD_ACTIVITY_LED  sl_led_led0
  #endif
#endif

void halStackIndicateActivity(bool turnOn)
{
  (void)turnOn;

#if defined(SL_CATALOG_LED_PRESENT) && defined(BOARD_ACTIVITY_LED)
  if (turnOn) {
    sl_led_turn_on(&BOARD_ACTIVITY_LED);
  } else {
    sl_led_turn_off(&BOARD_ACTIVITY_LED);
  }
#endif
}

void halSetLed(HalBoardLed led)
{
  (void)led;
}

void halClearLed(HalBoardLed led)
{
  (void)led;
}

void halToggleLed(HalBoardLed led)
{
  (void)led;
}

void halStackProcessBootCount(void)
{
#if defined(CREATOR_STACK_BOOT_COUNTER)
  halCommonIncrementCounterToken(TOKEN_STACK_BOOT_COUNTER);
#endif
}

EmberStatus halCommonIdleForMilliseconds(uint32_t *duration)
{
  (void)duration;

  // Sleeping is now handled by the Power Manager. Closest we can get to the old
  // behavior is to tell the caller that sleep was interrupted.
  return EMBER_SLEEP_INTERRUPTED;
}

void halStackSymbolDelayAIsr(void)
{
  // Intentionally empty.
  // This function is defined here only to provide compatibility for code that
  // may also be built for legacy parts.
}

EmberStatus emDebugInit(void)
{
#if defined(SL_CATALOG_IOSTREAM_VUART_PRESENT)
  sl_status_t status = sl_iostream_vuart_init();

  if (status == SL_STATUS_OK) {
    return EMBER_SUCCESS;
  }
#endif

  return EMBER_ERR_FATAL;
}

void emRadioSeedRandom(void)
{
  uint32_t seed;
  uint16_t bytes = RAIL_GetRadioEntropy(NULL, (uint8_t *)(&seed), sizeof(seed));
  assert(bytes == sizeof(seed));
  halStackSeedRandom(seed);
}

//------------------------------------------------------------------------------

// emberSerial

typedef enum COM_Port {
  // Legacy COM port defines
  COM_VCP = 0,
  COM_USART0 = 1,
  COM_USART1 = 2,
  COM_USART2 = 3,
  COM_USB = 4,
  COM_LEUART0 = 5,
  COM_LEUART1 = 6,

  // VCP
  comPortVcp = 0x10,

  // USARTs
  comPortUsart0 = 0x20,
  comPortUsart1 = 0x21,
  comPortUsart2 = 0x22,
  comPortUsart3 = 0x23,

  // LEUARTs
  comPortLeuart0 = 0x40,
  comPortLeuart1 = 0x41,

  // USB
  comPortUsb = 0x50,
} COM_Port_t;

EmberStatus emberSerialInit(uint8_t port,
                            SerialBaudRate rate,
                            SerialParity parity,
                            uint8_t stopBits)
{
  (void) port;
  (void) rate;
  (void) parity;
  (void) stopBits;
  return EMBER_SUCCESS;
}

EmberStatus emberSerialWaitSend(uint8_t port)
{
  (void) port;
  return EMBER_SUCCESS;
}

EmberStatus emberSerialReadByte(uint8_t port, uint8_t *dataByte)
{
  for (uint8_t i = 0; i < sl_iostream_instances_count; i++) {
    switch (port) {
      case COM_VCP:
      case comPortVcp:
        if (sl_iostream_instances_info[i]->type == SL_IOSTREAM_TYPE_SWO) {
          if (sl_iostream_getchar(sl_iostream_instances_info[i]->handle, (char *)dataByte) == SL_STATUS_OK) {
            return EMBER_SUCCESS;
          } else {
            return EMBER_SERIAL_RX_EMPTY;
          }
        }
        break;
      case COM_USART0:
      case comPortUsart0:
        if (sl_iostream_instances_info[i]->type == SL_IOSTREAM_TYPE_UART && sl_iostream_instances_info[i]->periph_id == 0) {
          if (sl_iostream_getchar(sl_iostream_instances_info[i]->handle, (char *)dataByte) == SL_STATUS_OK) {
            return EMBER_SUCCESS;
          } else {
            return EMBER_SERIAL_RX_EMPTY;
          }
        }
        break;
      case COM_USART1:
      case comPortUsart1:
        if (sl_iostream_instances_info[i]->type == SL_IOSTREAM_TYPE_UART && sl_iostream_instances_info[i]->periph_id == 1) {
          if (sl_iostream_getchar(sl_iostream_instances_info[i]->handle, (char *)dataByte) == SL_STATUS_OK) {
            return EMBER_SUCCESS;
          } else {
            return EMBER_SERIAL_RX_EMPTY;
          }
        }
        break;
      case COM_USART2:
      case comPortUsart2:
        if (sl_iostream_instances_info[i]->type == SL_IOSTREAM_TYPE_UART && sl_iostream_instances_info[i]->periph_id == 2) {
          if (sl_iostream_getchar(sl_iostream_instances_info[i]->handle, (char *)dataByte) == SL_STATUS_OK) {
            return EMBER_SUCCESS;
          } else {
            return EMBER_SERIAL_RX_EMPTY;
          }
        }
        break;
      case comPortUsart3:
        if (sl_iostream_instances_info[i]->type == SL_IOSTREAM_TYPE_UART && sl_iostream_instances_info[i]->periph_id == 3) {
          if (sl_iostream_getchar(sl_iostream_instances_info[i]->handle, (char *)dataByte) == SL_STATUS_OK) {
            return EMBER_SUCCESS;
          } else {
            return EMBER_SERIAL_RX_EMPTY;
          }
        }
        break;
      default:
        return EMBER_SERIAL_INVALID_PORT;
        break;
    }
  }
  return EMBER_ERR_FATAL;
}

EmberStatus emberSerialReadData(uint8_t port, uint8_t *data, uint16_t length, uint16_t *bytesRead)
{
  uint16_t bytesReadInternal = 0;
  EmberStatus status;

  while (bytesReadInternal < length) {
    status = emberSerialReadByte(port, data);
    switch (status) {
      case EMBER_SUCCESS:
        ++data;
        ++bytesReadInternal;
        break;

      case EMBER_SERIAL_RX_EMPTY:
        // empty queue is not an error for us, we just want to keep waiting
        break;

      default:
        // only store number of bytes read if the caller provided a non-NULL pointer
        if (bytesRead) {
          *bytesRead = bytesReadInternal;
        }
        return status;
    }
  }

  // only store number of bytes read if the caller provided a non-NULL pointer
  if (bytesRead) {
    *bytesRead = bytesReadInternal;
  }
  return EMBER_SUCCESS;
}

EmberStatus emberSerialGuaranteedPrintf(uint8_t port, const char * formatString, ...)
{
  EmberStatus status;
  va_list ap;
  va_start(ap, formatString);
  status = emberSerialPrintfVarArg(port, formatString, ap);
  va_end(ap);
  printf("\n");
  return status;
}
