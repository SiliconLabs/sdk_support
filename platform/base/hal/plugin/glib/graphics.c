/***************************************************************************//**
 * @file
 * @brief Draws the graphics on the display
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
#include "hal/plugin/glib/graphics.h"
#include "em_types.h"
#include "glib.h"
#include "dmd.h"
#include "display.h"
#include "textdisplay.h"
#include "retargettextdisplay.h"
#include <string.h>
#include <stdio.h>
#include "sl_sleeptimer.h"

GLIB_Context_t glibContext;          /* Global glib context */

static sl_sleeptimer_timer_handle_t timerId;
static void (*rtcCallback)(void*) = NULL;
static void * rtcCallbackArg = 0;
volatile uint32_t rtcCallbacks = 0;

/**************************************************************************//**
 * @brief Initializes the graphics stack.
 * @note This function will /hang/ if errors occur (usually
 *       caused by faulty displays.
 *****************************************************************************/
void GRAPHICS_Init(void)
{
  EMSTATUS status;

  /* Initialize the display module. */
  status = DISPLAY_Init();
  if (DISPLAY_EMSTATUS_OK != status) {
    while (1)
      ;
  }

  /* Initialize the DMD module for the DISPLAY device driver. */
  status = DMD_init(0);
  if (DMD_OK != status) {
    while (1)
      ;
  }

  status = GLIB_contextInit(&glibContext);
  if (GLIB_OK != status) {
    while (1)
      ;
  }

  glibContext.backgroundColor = White;
  glibContext.foregroundColor = Black;

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *)&GLIB_FontNarrow6x8);
}

/**************************************************************************//**
 * @brief This function draws the initial display screen
 *****************************************************************************/
void GRAPHICS_ShowStatus(void)
{
  GLIB_clear(&glibContext);
  GLIB_drawString(&glibContext, "EFR32 Sample App", 17, 5, 5, 0);
  DMD_updateDisplay();
}

/**************************************************************************//**
 * @brief Helper function for printing numbers. Consumes less space than
 *        snprintf. Limited to two digits and one decimal.
 * @param string
 *        The string to print32_t to
 * @param value
 *        The value to print
 *****************************************************************************/
void GRAPHICS_CreateString(char *string, int32_t value)
{
  if (value < 0) {
    value = -value;
    string[0] = '-';
  } else {
    string[0] = ' ';
  }
  string[5] = 0;
  string[4] = '0' + (value % 1000) / 100;
  string[3] = '.';
  string[2] = '0' + (value % 10000) / 1000;
  string[1] = '0' + (value % 100000) / 10000;

  if (string[1] == '0') {
    string[1] = ' ';
  }
}

/**************************************************************************//**
 * @brief   The actual callback for Memory LCD toggling
 * @param[in] id
 *   The id of the RTC timer (not used)
 *****************************************************************************/
static void memLcdCallback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void) handle;
  (void) data;
  rtcCallback(rtcCallbackArg);

  rtcCallbacks++;
}

/**************************************************************************//**
 * @brief   Register a callback function at the given frequency.
 *
 * @param[in] pFunction  Pointer to function that should be called at the
 *                       given frequency.
 * @param[in] argument   Argument to be given to the function.
 * @param[in] frequency  Frequency at which to call function at.
 *
 * @return  0 for successful or
 *         -1 if the requested frequency does not match the RTC frequency.
 *****************************************************************************/
int rtcIntCallbackRegister(void (*pFunction)(void*),
                           void* argument,
                           unsigned int frequency)
{
  rtcCallback    = pFunction;
  rtcCallbackArg = argument;

  sl_sleeptimer_start_periodic_timer_ms(&timerId,
                                        1000 / frequency,
                                        memLcdCallback,
                                        NULL,
                                        10u,
                                        0u);

  return 0;
}
