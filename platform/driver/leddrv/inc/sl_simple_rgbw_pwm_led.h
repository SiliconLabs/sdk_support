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

#ifndef SL_SIMPLE_RGBW_PWM_LED_H
#define SL_SIMPLE_RGBW_PWM_LED_H

#include "sl_led.h"
#include "em_gpio.h"
#include <stdint.h>

/***************************************************************************//**
 * @addtogroup led
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup simple_rgbw_pwm_led Simple RGBW PWM LED Driver
 * @brief Simple Red/Green/Blue/White PWM LED Driver
 * @{
 ******************************************************************************/

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

#define SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH 0U  ///< LED Active polarity High
#define SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW  1U  ///< LED Active polarity Low

#define SL_SIMPLE_RGBW_PWM_LED_COLOR_R              0U  ///< LED Red
#define SL_SIMPLE_RGBW_PWM_LED_COLOR_G              1U  ///< LED Green
#define SL_SIMPLE_RGBW_PWM_LED_COLOR_B              2U  ///< LED Blue
#define SL_SIMPLE_RGBW_PWM_LED_COLOR_W              3U  ///< LED White

#define SL_SIMPLE_RGBW_PWM_LED_VALUE_OFF            0U  ///< LED off value

#define SL_SIMPLE_RGBW_PWM_LED_NUM_CC_REQUIRED      4U  ///< Number of Timer Capture Channels required (1 for each RGBW color)

/*******************************************************************************
 *****************************   DATA TYPES   **********************************
 ******************************************************************************/

typedef uint8_t sl_simple_rgbw_pwm_led_polarity_t;    ///< LED GPIO polarities (active high/low)

/// A Simple RGBW LED context
typedef struct {
  /* Config parameters */
  GPIO_Port_TypeDef                 port[4];      ///< Red, Green, Blue and White GPIO ports
  uint8_t                           pin[4];       ///< Red, Green, Blue and White GPIO pins
  sl_simple_rgbw_pwm_led_polarity_t polarity[4];  ///< Red, Green, Blue and White GPIO polarities (active high/low)
  uint8_t                           channel[4];   ///< Red, Green, Blue and White PWM timer channels
  uint8_t                           location[4];  ///< Red, Green, Blue and White PWM timer location
  TIMER_TypeDef                     *timer;       ///< PWM timer (common instance for all four RGBW LEDs)
  uint32_t                          frequency;    ///< PWM frequency
  uint32_t                          resolution;   ///< PWM resolution (dimming steps)
  /* Settings */
  uint16_t                          level[4];     ///< Red, Green, Blue and White levels (PWM duty cycle [0-65535])
  sl_led_state_t                    state;        ///< Current state (ON/OFF)
} sl_simple_rgbw_pwm_led_context_t;

/// A Simple RGBW LED PWM instance
typedef struct {
  sl_led_t       led_common;                      ///< Inherit from the Common LED Driver
  void           (*set_rgbw_color)(void *context, uint16_t red, uint16_t green, uint16_t blue, uint16_t white);     ///< member function to set RGBW
  void           (*get_rgbw_color)(void *context, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white); ///< member function to get RGBW
} sl_led_rgbw_pwm_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize the RGBW PWM LED driver.
 *
 * @param[in] led_handle         Pointer to rgbw-pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 *
 * @return    Status Code:
 *              - SL_STATUS_OK   Success
 *              - SL_STATUS_FAIL Init error
 ******************************************************************************/
sl_status_t sl_simple_rgbw_pwm_led_init(void *led_handle);

/***************************************************************************//**
 * Turn on an RBGW LED.
 *   Turns on at previously set color levels
 *   If no previous levels set, turns on at max level for all four RGBW LEDs
 *
 * @param[in] led_handle         Pointer to rgbw_pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 *
 ******************************************************************************/
void sl_simple_rgbw_pwm_led_turn_on(void *led_handle);

/***************************************************************************//**
 * Turn off an RGBW LED.
 *
 * @param[in] led_handle         Pointer to rgbw-pwm-led specific data:
 *                                 - sl_rgbw_pwm_led_context_t
 *
 ******************************************************************************/
void sl_simple_rgbw_pwm_led_turn_off(void *led_handle);

/***************************************************************************//**
 * Toggle an RGBW LED.
 *  The toggle "ON" behavior is as defined for sl_simple_rgbw_pwm_led_turn_on()

 * @param[in] led_handle         Pointer to rgbw-pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 *
 ******************************************************************************/
void sl_simple_rgbw_pwm_led_toggle(void *led_handle);

/***************************************************************************//**
 * Get status of an RGBW LED.
 *
 * @param[in] led_handle         Pointer to rgbw-pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 *
 * @return    sl_led_state_t     Current state of RGBW LED.
 *                               0 for Red, Green, Blue and White LEDs are all OFF
 *                               1 for Red, Green, Blue or White LED is ON
 ******************************************************************************/
sl_led_state_t sl_simple_rgbw_pwm_led_get_state(void *led_handle);

/***************************************************************************//**
 * Set color mixing and dimming level of an RGBW LED.
 *
 * @param[in] led_handle         Pointer to rgbw-pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 * @param[in] red                Red color level (PWM duty-cycle [0-65535])
 * @param[in] green              Green color level (PWM duty-cycle [0-65535])
 * @param[in] blue               Blue color level (PWM duty-cycle [0-65535])
 * @param[in] white              White color level (PWM duty-cycle [0-65535])
 *
 ******************************************************************************/
void sl_simple_rgbw_pwm_led_set_color(void *led_handle, uint16_t red, uint16_t green, uint16_t blue, uint16_t white);

/***************************************************************************//**
 * Get current color mixing and dimming level of an RGBW LED.
 *
 * @note Will return the last stored levels regardless of the current ON/OFF
 * state. Call sl_simple_rgbw_pwm_led_get_state() to determine if the RGBW LED
 * is actually ON or OFF.
 *
 * @param[in]  led_handle        Pointer to rgbw-pwm-led specific data:
 *                                 - sl_simple_rgbw_pwm_led_context_t
 * @param[out] red               Red color level (PWM duty-cycle [0-65535])
 * @param[out] green             Green color level (PWM duty-cycle [0-65535])
 * @param[out] blue              Blue color level (PWM duty-cycle [0-65535])
 * @param[out] white             White color level (PWM duty-cycle [0-65535])
 *
 ******************************************************************************/
void sl_simple_rgbw_pwm_led_get_color(void *led_handle, uint16_t *red, uint16_t *green, uint16_t *blue, uint16_t *white);

/*******************************************************************************
 ****************   API extensions to the Common LED Driver   ******************
 ******************************************************************************/

void sl_led_set_rgbw_color(const sl_led_rgbw_pwm_t *led_handle,   ///< LED Instance handle
                           uint16_t red,                          ///< LED red intensity
                           uint16_t green,                        ///< LED green intensity
                           uint16_t blue,                         ///< LED blue intensity
                           uint16_t white                         ///< LED white intensity
                           ); ///< LED set RGBW color

void sl_led_get_rgbw_color(const sl_led_rgbw_pwm_t * led_handle,    ///< LED Instance handle
                           uint16_t * red,                          ///< LED red intensity
                           uint16_t * green,                        ///< LED green intensity
                           uint16_t * blue,                         ///< LED blue intensity
                           uint16_t * white                         ///< LED white intensity
                           ); ///< LED get RGBW setting

/** @} (end group simple_rgbw_pwm_led) */
/** @} (end group led) */

// ******** THE REST OF THE FILE IS DOCUMENTATION ONLY !***********************
/// @addtogroup simple_rgbw_pwm_led Simple RGBW PWM LED Driver
/// @{
///
///   @details
///
///   @n @section rgbw_led_intro Introduction
///
///   The Simple RGBW PWM LED Driver is a module for the LED driver that provides functionality
///   for controlling Red/Green/Blue/White LEDs that are driven by PWM.
///
///   @n @section rgbw_led_config RGBW PWM LED Configuration
///
///   RGBW PWM LEDs use the @ref sl_led_t struct, and their own structs
///   @ref sl_simple_rgbw_pwm_led_context_t and @ref sl_led_rgbw_pwm_t. These are automatically
///   generated into the following files, as well as instance specific headers with macro
///   definitions in them. The samples below are for a single instance called "inst0".
///
///   @code{.c}
///// sl_simple_rgbw_pwm_led_instances.c
///
///#include "sl_simple_rgbw_pwm_led.h"
///#include "em_gpio.h"
///#include "sl_simple_rgbw_pwm_led_inst0_config.h"
///
///sl_simple_rgbw_pwm_led_context_t simple_rgbw_pwm_inst0_context = {
///  .port[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_INST0_RED_PORT,
///  .pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_INST0_RED_PIN,
///  .polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_INST0_RED_POLARITY,
///  .channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_INST0_RED_CHANNEL,
///#if defined(SL_SIMPLE_RGBW_PWM_LED_INST0_RED_LOC)
///  .location[SL_SIMPLE_RGBW_PWM_LED_COLOR_R] = SL_SIMPLE_RGBW_PWM_LED_INST0_RED_LOC,
///#endif
///  .port[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_PORT,
///  .pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_PIN,
///  .polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_POLARITY,
///  .channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_CHANNEL,
///#if defined(SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_LOC)
///  .location[SL_SIMPLE_RGBW_PWM_LED_COLOR_G] = SL_SIMPLE_RGBW_PWM_LED_INST0_GREEN_LOC,
///#endif
///  .port[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_PORT,
///  .pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_PIN,
///  .polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_POLARITY,
///  .channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_CHANNEL,
///#if defined(SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_LOC)
///  .location[SL_SIMPLE_RGBW_PWM_LED_COLOR_B] = SL_SIMPLE_RGBW_PWM_LED_INST0_BLUE_LOC,
///#endif
///  .port[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_PORT,
///  .pin[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_PIN,
///  .polarity[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_POLARITY,
///  .channel[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_CHANNEL,
///#if defined(SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_LOC)
///  .location[SL_SIMPLE_RGBW_PWM_LED_COLOR_W] = SL_SIMPLE_RGBW_PWM_LED_INST0_WHITE_LOC,
///#endif
///  .timer = SL_SIMPLE_RGBW_PWM_LED_INST0_PERIPHERAL,
///  .frequency = SL_SIMPLE_RGBW_PWM_LED_INST0_FREQUENCY,
///  .resolution = SL_SIMPLE_RGBW_PWM_LED_INST0_RESOLUTION,
///};
///
///const sl_led_rgbw_pwm_t sl_inst0 = {
///  .led_common.context = &simple_rgbw_pwm_inst0_context,
///  .led_common.init = sl_simple_rgbw_pwm_led_init,
///  .led_common.turn_on = sl_simple_rgbw_pwm_led_turn_on,
///  .led_common.turn_off = sl_simple_rgbw_pwm_led_turn_off,
///  .led_common.toggle = sl_simple_rgbw_pwm_led_toggle,
///  .led_common.get_state = sl_simple_rgbw_pwm_led_get_state,
///  .set_rgbw_color = sl_simple_rgbw_pwm_led_set_color,
///  .get_rgbw_color = sl_simple_rgbw_pwm_led_get_color,
///};
///
///void sl_simple_rgbw_pwm_led_init_instances(void)
///{
///  sl_led_init((sl_led_t *)&sl_inst0);
///}
///   @endcode
///
///   @note The sl_simple_rgbw_pwm_led_instances.c file is shown with only one instance, but if more
///         were in use they would all appear in this .c file.
///
///   @code{.c}
///// sl_simple_rgbw_pwm_led_instances.h
///
///#ifndef SL_SIMPLE_RGBW_PWM_LED_INSTANCES_H
///#define SL_SIMPLE_RGBW_PWM_LED_INSTANCES_H
///
///#include "sl_simple_rgbw_pwm_led.h"
///
///extern const sl_led_rgbw_pwm_t sl_inst0;
///
///void sl_simple_rgbw_pwm_led_init_instances(void);
///
///#endif // SL_SIMPLE_RGBW_PWM_LED_INIT_H
///   @endcode
///
///   @note The sl_simple_rgbw_pwm_led_instances.h file is shown with only one instance, but if more
///         were in use they would all appear in this .h file.
///
///   @n @section rgbw_led_usage RGBW PWM LED Usage
///
///   The RGBW PWM Led driver provides functionality for controlling Red/Green/Blue/White
///   LEDs that are driven by PWM. The LEDs can be turned on and off and toggled, and remember
///   their color and brightness state when being turned back on. The color and brightness can be
///   set using values of 0-65535 for red, green, blue, and white. Retrieving the state gives the
///   on/off value, while retrieving the color gives the rgbw values. The following
///   code shows how to control these LEDs. An LED should always be initialized before
///   calling any other functions with it.
///
///   @code{.c}
///// initialize rgbw LED
///sl_led_init(&rgbw_led_inst0);
///
///// turn on LED, set color to purple, turn off, toggle (would maintain purple color)
///sl_led_turn_on(&rgbw_led_inst0);
///uint16_t white = 65535; // max brightness
///uint16_t red = 65535; // max red
///uint16_t green = 0; // no green
///uint16_t blue = 65535; // max blue
///sl_led_set_rgbw_color(&rgbw_led_inst0, red, green, blue, white);
///sl_led_turn_off(&rgbw_led_inst0);
///sl_led_toggle(&rgbw_led_inst0);
///
///// get the state of the led
///sl_led_state_t state = sl_led_get_state(&rgbw_led_instance0);
///   @endcode
///
/// @} end group led ********************************************************/

#endif // SL_SIMPLE_RGBW_PWM_LED_H
