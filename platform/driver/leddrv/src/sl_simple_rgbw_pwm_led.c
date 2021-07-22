/***************************************************************************//**
 * @file
 * @brief Simple RGBW PWM LED Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_simple_rgbw_pwm_led.h"

#include "em_timer.h"
#include "em_cmu.h"

/*
 *  Private functions
 */
static void sl_simple_rgbw_pwm_led_set_current_state(sl_simple_rgbw_pwm_led_context_t *led, sl_led_state_t state)
{
  led->state = state;
}

static sl_led_state_t sl_simple_rgbw_pwm_led_get_current_state(sl_simple_rgbw_pwm_led_context_t *led)
{
  return led->state;
}

static CMU_Clock_TypeDef sl_simple_rgbw_pwm_led_get_timer_clock(TIMER_TypeDef *timer)
{
#if defined(_CMU_HFCLKSEL_MASK) || defined(_CMU_CMD_HFCLKSEL_MASK)
  CMU_Clock_TypeDef timer_clock = cmuClock_HF;
#elif defined(_CMU_SYSCLKCTRL_MASK)
  CMU_Clock_TypeDef timer_clock = cmuClock_SYSCLK;
#else
#error "Unknown root of clock tree"
#endif

  switch ((uint32_t)timer) {
#if defined(TIMER0_BASE)
    case TIMER0_BASE:
      timer_clock = cmuClock_TIMER0;
      break;
#endif
#if defined(TIMER1_BASE)
    case TIMER1_BASE:
      timer_clock = cmuClock_TIMER1;
      break;
#endif
#if defined(TIMER2_BASE)
    case TIMER2_BASE:
      timer_clock = cmuClock_TIMER2;
      break;
#endif
#if defined(TIMER3_BASE)
    case TIMER3_BASE:
      timer_clock = cmuClock_TIMER3;
      break;
#endif
#if defined(TIMER4_BASE)
    case TIMER4_BASE:
      timer_clock = cmuClock_TIMER4;
      break;
#endif
#if defined(TIMER5_BASE)
    case TIMER5_BASE:
      timer_clock = cmuClock_TIMER5;
      break;
#endif
#if defined(TIMER6_BASE)
    case TIMER6_BASE:
      timer_clock = cmuClock_TIMER6;
      break;
#endif
#if defined(WTIMER0_BASE)
    case WTIMER0_BASE:
      timer_clock = cmuClock_WTIMER0;
      break;
#endif
#if defined(WTIMER1_BASE)
    case WTIMER1_BASE:
      timer_clock = cmuClock_WTIMER1;
      break;
#endif
#if defined(WTIMER2_BASE)
    case WTIMER2_BASE:
      timer_clock = cmuClock_WTIMER2;
      break;
#endif
#if defined(WTIMER3_BASE)
    case WTIMER3_BASE:
      timer_clock = cmuClock_WTIMER3;
      break;
#endif
    default:
      EFM_ASSERT(0);
      break;
  }
  return timer_clock;
}

static void sl_simple_rgbw_pwm_led_start(sl_simple_rgbw_pwm_led_context_t *led)
{
  // Enable PWM output
#if defined(_TIMER_ROUTE_MASK)
  BUS_RegMaskedSet(&led->timer->ROUTE,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTE,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTE,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTE,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] + _TIMER_ROUTE_CC0PEN_SHIFT));
#elif defined(_TIMER_ROUTELOC0_MASK)
  BUS_RegMaskedSet(&led->timer->ROUTEPEN,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTEPEN,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTEPEN,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedSet(&led->timer->ROUTEPEN,
                   1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
#elif defined(_GPIO_TIMER_ROUTEEN_MASK)
  GPIO->TIMERROUTE_SET[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_SET[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_SET[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_SET[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
#else
#error "Unknown route setting"
#endif
}

static void sl_simple_rgbw_pwm_led_stop(sl_simple_rgbw_pwm_led_context_t *led)
{
  // Disable PWM output
#if defined(_TIMER_ROUTE_MASK)
  BUS_RegMaskedClear(&led->timer->ROUTE,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTE,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTE,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _TIMER_ROUTE_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTE,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] + _TIMER_ROUTE_CC0PEN_SHIFT));
#elif defined(_TIMER_ROUTELOC0_MASK)
  BUS_RegMaskedClear(&led->timer->ROUTEPEN,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTEPEN,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTEPEN,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
  BUS_RegMaskedClear(&led->timer->ROUTEPEN,
                     1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _TIMER_ROUTEPEN_CC0PEN_SHIFT));
#elif defined(_GPIO_TIMER_ROUTEEN_MASK)
  GPIO->TIMERROUTE_CLR[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_CLR[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_CLR[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
  GPIO->TIMERROUTE_CLR[TIMER_NUM(led->timer)].ROUTEEN = 1 << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] + _GPIO_TIMER_ROUTEEN_CC0PEN_SHIFT);
#else
#error "Unknown route setting"
#endif

  // Keep timer running in case other channels are in use
}

/*
 *  Public functions
 */
sl_status_t sl_simple_rgbw_pwm_led_init(void *context)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

#if !defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif
  CMU_Clock_TypeDef timer_clock = sl_simple_rgbw_pwm_led_get_timer_clock(led->timer);
  CMU_ClockEnable(timer_clock, true);

  TIMER_InitCC_TypeDef channel_init = TIMER_INITCC_DEFAULT;
  channel_init.mode = timerCCModePWM;
  channel_init.cmoa = timerOutputActionToggle;
  channel_init.edge = timerEdgeBoth;

  // Sanity check the user configuration values

  // Validate that the selected timer has the required number of Capture/Compare channels.
  // We do this by writing and reading back a "magic" value (1234) to the channel with the highest number.
  // If the channel exists, then the read-back value will match the written value. Otherwise not.
  TIMER_CompareSet(led->timer, SL_SIMPLE_RGBW_PWM_LED_NUM_CC_REQUIRED - 1, 1234U);
  uint32_t capture_value = TIMER_CaptureGet(led->timer, SL_SIMPLE_RGBW_PWM_LED_NUM_CC_REQUIRED - 1);
  if (capture_value != 1234U) {
    // The timer the user has selected doesn't have the required number of CC channels
#if !defined(_SILICON_LABS_32B_SERIES_2)
    CMU_ClockEnable(cmuClock_HFPER, false);
#endif
    CMU_ClockEnable(timer_clock, false);

    return SL_STATUS_FAIL;
  }

  // The configured resolution configuration has to be at least 2. And not bigger than the timer max count + 1
  uint32_t max_count = TIMER_MaxCount(led->timer);
  if ((led->resolution < 2U) || (led->resolution > (max_count + 1))) {
    // The user configured max level value is invalid
#if !defined(_SILICON_LABS_32B_SERIES_2)
    CMU_ClockEnable(cmuClock_HFPER, false);
#endif
    CMU_ClockEnable(timer_clock, false);

    return SL_STATUS_FAIL;
  }

  // User configuration values are OK. Continue with the initialization...

  // Set CC channel parameters
  channel_init.outInvert = (led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] == SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW);
  TIMER_InitCC(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R], &channel_init);
  channel_init.outInvert = (led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] == SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW);
  TIMER_InitCC(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G], &channel_init);
  channel_init.outInvert = (led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] == SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW);
  TIMER_InitCC(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B], &channel_init);
  channel_init.outInvert = (led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] == SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW);
  TIMER_InitCC(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W], &channel_init);

  // Set PWM pin as output
  CMU_ClockEnable(cmuClock_GPIO, true);
  GPIO_PinModeSet((GPIO_Port_TypeDef)led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_R],
                  led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_R],
                  gpioModePushPull,
                  led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_R]);
  GPIO_PinModeSet((GPIO_Port_TypeDef)led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_G],
                  led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_G],
                  gpioModePushPull,
                  led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_G]);
  GPIO_PinModeSet((GPIO_Port_TypeDef)led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_B],
                  led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_B],
                  gpioModePushPull,
                  led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_B]);
  GPIO_PinModeSet((GPIO_Port_TypeDef)led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_W],
                  led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_W],
                  gpioModePushPull,
                  led->polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_W]);

  // Configure CC channel pinout
#if defined(_TIMER_ROUTE_MASK)
  BUS_RegMaskedWrite(&led->timer->ROUTE,
                     _TIMER_ROUTE_LOCATION_MASK,
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] << _TIMER_ROUTE_LOCATION_SHIFT);
  BUS_RegMaskedWrite(&led->timer->ROUTE,
                     _TIMER_ROUTE_LOCATION_MASK,
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] << _TIMER_ROUTE_LOCATION_SHIFT);
  BUS_RegMaskedWrite(&led->timer->ROUTE,
                     _TIMER_ROUTE_LOCATION_MASK,
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] << _TIMER_ROUTE_LOCATION_SHIFT);
  BUS_RegMaskedWrite(&led->timer->ROUTE,
                     _TIMER_ROUTE_LOCATION_MASK,
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] << _TIMER_ROUTE_LOCATION_SHIFT);
#elif defined(_TIMER_ROUTELOC0_MASK)
  BUS_RegMaskedWrite(&led->timer->ROUTELOC0,
                     _TIMER_ROUTELOC0_CC0LOC_MASK << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] * 8U),
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] * 8U));
  BUS_RegMaskedWrite(&led->timer->ROUTELOC0,
                     _TIMER_ROUTELOC0_CC0LOC_MASK << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] * 8U),
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] * 8U));
  BUS_RegMaskedWrite(&led->timer->ROUTELOC0,
                     _TIMER_ROUTELOC0_CC0LOC_MASK << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] * 8U),
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] * 8U));
  BUS_RegMaskedWrite(&led->timer->ROUTELOC0,
                     _TIMER_ROUTELOC0_CC0LOC_MASK << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] * 8U),
                     led->location[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] << (led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] * 8U));
#elif defined(_GPIO_TIMER_ROUTEEN_MASK)
  volatile uint32_t * route_register = &GPIO->TIMERROUTE[TIMER_NUM(led->timer)].CC0ROUTE;
  *(route_register + led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R]) = (led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT)
                                                                     | (led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
  *(route_register + led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G]) = (led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT)
                                                                     | (led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
  *(route_register + led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B]) = (led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] << _GPIO_TIMER_CC2ROUTE_PORT_SHIFT)
                                                                     | (led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] << _GPIO_TIMER_CC2ROUTE_PIN_SHIFT);
  *(route_register + led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W]) = (led->port[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] << _GPIO_TIMER_CC3ROUTE_PORT_SHIFT)
                                                                     | (led->pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] << _GPIO_TIMER_CC3ROUTE_PIN_SHIFT);
#else
#error "Unknown route setting"
#endif

  // Configure the Timer TOP value on basis of the application PWM frequency and resolution config values
  uint32_t top = 0;
  // First find the TOP value that satisfies the PWM frequency config (if not set to 0 = "don't care")
  if (led->frequency > 0U) {
    top = (CMU_ClockFreqGet(timer_clock) / (led->frequency)) - 1U;
  }

  // Then adjust it to make it an even multiplier of the PWM resolution config
  top = (top / (led->resolution - 1)) * (led->resolution - 1);

  if (top < (led->resolution - 1)) {
    // The PWM resolution config demands a higher TOP value than what the frequency config sets.
    // In this case the resolution config takes precedence over frequency.
    // So simply set the TOP value equal to the max input value (resolution value - 1).
    top = led->resolution - 1;
  }
  TIMER_TopSet(led->timer, top);

  // Set the initial duty cycles and LED state to OFF
  TIMER_CompareSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);

  sl_simple_rgbw_pwm_led_set_current_state(led, SL_LED_CURRENT_STATE_OFF);

  // Initialize TIMER
  TIMER_Init_TypeDef timer_init = TIMER_INIT_DEFAULT;
  TIMER_Init(led->timer, &timer_init);

  // Initialize the level settings values
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF;

  // Enable output
  sl_simple_rgbw_pwm_led_start(led);

  return SL_STATUS_OK;
}

void sl_simple_rgbw_pwm_led_turn_on(void *context)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;
  uint32_t level_increments = TIMER_TopGet(led->timer) / (led->resolution - 1); // Get the counter increments per intensity level step

  if ((led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)
      && (led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)
      && (led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)
      && (led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)) {
    // No previous level set. Turn on with max level
    led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = (uint16_t)(led->resolution - 1);
    led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = (uint16_t)(led->resolution - 1);
    led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = (uint16_t)(led->resolution - 1);
    led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = (uint16_t)(led->resolution - 1);
  }

  sl_simple_rgbw_pwm_led_stop(led);

  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R], led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] * level_increments);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G], led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] * level_increments);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B], led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] * level_increments);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W], led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] * level_increments);

  sl_simple_rgbw_pwm_led_start(led);

  sl_simple_rgbw_pwm_led_set_current_state(led, SL_LED_CURRENT_STATE_ON);
}

void sl_simple_rgbw_pwm_led_turn_off(void *context)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

  sl_simple_rgbw_pwm_led_stop(led);

  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);
  TIMER_CompareBufSet(led->timer, led->channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W], SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF);

  sl_simple_rgbw_pwm_led_start(led);

  sl_simple_rgbw_pwm_led_set_current_state(led, SL_LED_CURRENT_STATE_OFF);
}

void sl_simple_rgbw_pwm_led_toggle(void *context)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

  if (sl_simple_rgbw_pwm_led_get_current_state(led) == SL_LED_CURRENT_STATE_OFF) {
    sl_simple_rgbw_pwm_led_turn_on(led);
  } else {
    sl_simple_rgbw_pwm_led_turn_off(led);
  }
}

sl_led_state_t sl_simple_rgbw_pwm_led_get_state(void *context)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

  return sl_simple_rgbw_pwm_led_get_current_state(led);
}

void sl_simple_rgbw_pwm_led_set_color(void *context, uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = red;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = green;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = blue;
  led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = white;

  if ((red == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF) && (green == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)
      && (blue == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF) && (white == SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF)) {
    // All colors set to OFF. I.e. the same as if the user issued a turn off command
    sl_simple_rgbw_pwm_led_turn_off(led);
  } else {
    sl_simple_rgbw_pwm_led_turn_on(led);
  }
}

void sl_simple_rgbw_pwm_led_get_color(void *context, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white)
{
  sl_simple_rgbw_pwm_led_context_t *led = context;

  *red   = led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_R];
  *green = led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_G];
  *blue  = led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_B];
  *white = led->level[SL_SIMPLE_RGBW_PWM_LED_COLOR_W];
}

/*
 *  API functions (extentions to the Common LED Driver API)
 */
void sl_led_set_rgbw_color(const sl_led_rgbw_pwm_t *led_handle, uint16_t red, uint16_t green, uint16_t blue, uint16_t white)
{
  led_handle->set_rgbw_color(led_handle->led_common.context, red, green, blue, white);
}

void sl_led_get_rgbw_color(const sl_led_rgbw_pwm_t *led_handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white)
{
  led_handle->get_rgbw_color(led_handle->led_common.context, red, green, blue, white);
}
