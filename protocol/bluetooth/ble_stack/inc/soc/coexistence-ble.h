/***************************************************************************//**
 * @brief Co-existence support for Bluetooth
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef COEX_H
#define COEX_H

#ifdef HAL_CONFIG
#include "hal-config.h"
#endif

#include <em_gpio.h>

/**
 * Coexistence interface
 */

struct gecko_coexInit {
  uint32_t options;
  uint16_t requestWindow;
  uint16_t requestWindowCalibration;
};

#ifndef HAL_COEX_REQ_WINDOW
// Request window defines how many micro seconds earlier request signal
// is set before actual radio operation. Default value is defined here.
#define HAL_COEX_REQ_WINDOW 500
#endif

#ifndef HAL_COEX_REQ_BACKOFF
// Maximum backoff time in micro seconds after request signal is deasserted.
// This value needs to be smaller than request window.
#define HAL_COEX_REQ_BACKOFF 100
#endif

#ifndef HAL_COEX_PWM_REQ_PERIOD
//Default pwm period is disabled
#define HAL_COEX_PWM_REQ_PERIOD 0
#endif

#ifndef HAL_COEX_PWM_REQ_DUTYCYCLE
//Default pwm dutycycle is disabled
#define HAL_COEX_PWM_REQ_DUTYCYCLE 0
#endif

//Compatibility defines if Tx and Rx defined separately
#ifndef HAL_COEX_PRIORITY_DEFAULT
#if defined(HAL_COEX_TX_HIPRI) && defined(HAL_COEX_RX_HIPRI)
#define HAL_COEX_PRIORITY_DEFAULT (HAL_COEX_TX_HIPRI | HAL_COEX_RX_HIPRI)
#endif
#endif

// Request window calibration value takes into account the hardware and
// software delayes which may delay the request signal
#ifndef GECKO_COEX_REQ_WINDOW_CALIBRATION
#if (HAL_COEX_REQ_SHARED)
#define GECKO_COEX_REQ_WINDOW_CALIBRATION   89
#else
#define GECKO_COEX_REQ_WINDOW_CALIBRATION   87
#endif
#endif

#define GECKO_COEXINIT_DEFAULT {               \
    0, /* configuration options */             \
    HAL_COEX_REQ_WINDOW,  /* request window */ \
    GECKO_COEX_REQ_WINDOW_CALIBRATION,         \
}

#define GECKO_COEX_OPTION_REQUEST_BACKOFF_SHIFT 0
#define GECKO_COEX_OPTION_REQUEST_BACKOFF_MASK  0xff
#define GECKO_COEX_OPTION_REQUEST_BACKOFF_DEFAULT \
  HAL_COEX_REQ_BACKOFF
#define GECKO_COEX_OPTION_ENABLE_SHIFT          8
#define GECKO_COEX_OPTION_TX_ABORT_SHIFT        10
#define GECKO_COEX_OPTION_PRIORITY_ENABLE_SHIFT 11
#define GECKO_COEX_OPTION_PWM_PRIORITY_SHIFT    12
#define GECKO_COEX_OPTION_PWM_ENABLE_SHIFT      13

/* Coex is enabled*/
#define GECKO_COEX_OPTION_ENABLE                (1 << GECKO_COEX_OPTION_ENABLE_SHIFT)
/* Abort transmission if grant is lost*/
#define GECKO_COEX_OPTION_TX_ABORT              (1 << GECKO_COEX_OPTION_TX_ABORT_SHIFT)
/* Priority signal toggling is enabled */
#define GECKO_COEX_OPTION_PRIORITY_ENABLE       (1 << GECKO_COEX_OPTION_PRIORITY_ENABLE_SHIFT)
/* Priority signal is toggled with pwm */
#define GECKO_COEX_OPTION_PWM_PRIORITY          (1 << GECKO_COEX_OPTION_PWM_PRIORITY_SHIFT)
/* PWM toggling is enabled */
#define GECKO_COEX_OPTION_PWM_ENABLE            (1 << GECKO_COEX_OPTION_PWM_ENABLE_SHIFT)

#define GECKO_COEX_OPTION_MASK                  0x0000ff00
#define GECKO_COEX_OPTION_REQUEST_WINDOW_SHIFT  16
#define GECKO_COEX_OPTION_REQUEST_WINDOW_MASK   0xffff0000

void gecko_initCoex(const struct gecko_coexInit *coexInit);
#if !defined(NCP_GECKO_H)
void gecko_bgapi_class_coex_init();
#endif
static inline void gecko_initCoexHAL()
{
#ifdef HAL_CONFIG
#if (HAL_COEX_ENABLE)
  // Initialise coexistence interface
  struct gecko_coexInit coexInit = {
    .options = GECKO_COEX_OPTION_ENABLE | GECKO_COEX_OPTION_REQUEST_BACKOFF_DEFAULT,
    .requestWindow = HAL_COEX_REQ_WINDOW,
    .requestWindowCalibration = GECKO_COEX_REQ_WINDOW_CALIBRATION,
  };

  // COEX options
#if (HAL_COEX_TX_ABORT)
  coexInit.options |= GECKO_COEX_OPTION_TX_ABORT;
#endif
#ifdef HAL_COEX_PRIORITY_DEFAULT
  coexInit.options |= HAL_COEX_PRIORITY_DEFAULT ? GECKO_COEX_OPTION_PRIORITY_ENABLE : 0;
#endif
#ifdef HAL_COEX_PWM_PRIORITY
  coexInit.options |= HAL_COEX_PWM_PRIORITY ? GECKO_COEX_OPTION_PWM_PRIORITY : 0;
#endif
#ifdef HAL_COEX_PWM_DEFAULT_ENABLED
  coexInit.options |= HAL_COEX_PWM_DEFAULT_ENABLED ? GECKO_COEX_OPTION_PWM_ENABLE : 0;
#endif

  gecko_initCoex(&coexInit);

#ifdef NCP_GECKO_H
  ncp_gecko_bgapi_class_coex_init();
#endif
#ifdef NATIVE_GECKO_H
  gecko_bgapi_class_coex_init();
#endif

#endif // HAL_COEX_ENABLE
#endif // HAL_CONFIG
}

/**
 * Set coexistence options
 *
 * @param mask options to configure
 * @param options enable/disable features
 *
 * @return true Parameters was set
 * @return false Operation failed, this can happen if command is used through BGAPI and coex is not linked in
 */
bool gecko_setCoexOptions(uint32_t mask, uint32_t options);

struct ll_coexConfig{
  uint8_t threshold_coex_pri; /** Priority line is toggled if priority is below this*/
  uint8_t threshold_coex_req; /** Coex request is toggled if priority is below this*/
  uint8_t coex_pwm_period;    /** PWM Period in ms, if 0 pwm is disabled*/
  uint8_t coex_pwm_dutycycle; /** PWM dutycycle percentage, if 0 pwm is disabled, if >= 100 pwm line is always enabled*/
};
#define GECKO_COEX_DEFAULT_CONFIG { 175, 255, HAL_COEX_PWM_REQ_PERIOD, HAL_COEX_PWM_REQ_DUTYCYCLE }
/**
 * Update coex configuration
 *
 */
void gecko_coexSetConfig(struct ll_coexConfig * config);

// Interval functions for debugging purposes
void gecko_enableCoexPullResistor(bool enable);

/* Coex counters interface */
/**
 * Get coex counter data structure
 *
 * @param ptr returns pointer to coex structure
 * @param size returns size of coex structure
 * if either ptr or size is NULL, coex data structure is cleared
 *
 * @return true Parameters was set
 * @return false Operation failed, this can happen if command is used through BGAPI and coex is not linked in
 */

bool gecko_getCoexCounters(const void **ptr, uint8_t *size);

/**
 * Called internally by coex to update data structure
 *
 */
void coex_counterRequest(bool request, bool priority);
void coex_counterGrantUpdate(bool state);
void coex_counterIncrementDenied(void);

#endif
