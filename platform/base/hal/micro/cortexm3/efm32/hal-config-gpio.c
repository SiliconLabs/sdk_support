/***************************************************************************//**
 * @file
 * @brief HAL config gpio initialization
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
//
#include PLATFORM_HEADER
#include "hal/hal.h"
#include "em_device.h"

#if (HAL_GPIO_MAX > 32)
uint64_t halConfigGpioActive;
#define GPIOBIT(x) ((uint64_t)1 << (x))
#else
uint32_t halConfigGpioActive;
#define GPIOBIT(x) ((uint32_t)1 << (x))
#endif
#define GPIOCLEARBIT(reg, bit)    reg &= ~(GPIOBIT(bit))
#define GPIOREADBIT(reg, bit)     (reg & (GPIOBIT(bit)))
#define GPIOSETBIT(reg, bit)      reg |= GPIOBIT(bit)

#if (HAL_GPIO_MAX == 0)
void halConfigInitGpio(void)
{
}
void halConfigPowerDownGpio(void)
{
}
void halConfigPowerUpGpio(void)
{
}
bool halConfigRegisterGpio(GPIO_Port_TypeDef port,
                           uint8_t pin,
                           GPIO_Mode_TypeDef pUpMode,
                           uint8_t pUpOut,
                           GPIO_Mode_TypeDef pDownMode,
                           uint8_t pDownOut)
{
  return false;
}
bool halConfigUnregisterGpio(GPIO_Port_TypeDef port, uint8_t pin)
{
  return false;
}
#else

typedef struct {
  GPIO_Port_TypeDef   port;
  uint8_t             pin;
  GPIO_Mode_TypeDef   pUpMode;
  uint8_t             pUpOut;
  GPIO_Mode_TypeDef   pDownMode;
  uint8_t             pDownOut;
} tGpioArray;

static tGpioArray halConfigGpio[HAL_GPIO_MAX];

/******************************************************************************/
/**
 * @brief
 *   Locate index of an active GPIO
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number in the port.
 *
 * @param[in] index
 *   Pointer to contain index
 *   * On success (found GPIO) - Store index of matching gpio
 *   * On failure (free space) - Store a free (non-active) index
 *   * On failure (no space) - Store -1
 *
 * @return
 *  True on success, False on failure
 ******************************************************************************/
static bool halConfigFindGpio(GPIO_Port_TypeDef port, uint8_t pin, int8_t *index)
{
  *index = -1;
  int8_t i;
  for ( i = 0; i < HAL_GPIO_MAX; i++ ) {
    // Return immediately if GPIO is found
    if ((halConfigGpio[i].port == port)
        && (halConfigGpio[i].pin == pin)
        && (GPIOREADBIT(halConfigGpioActive, i))) {
      *index = i;
      return true;
    }
    // Store free index in case GPIO is not found
    if (!GPIOREADBIT(halConfigGpioActive, i)) {
      *index = i;
    }
  }
  return false;
}
/******************************************************************************/
/**
 * @brief
 *   Initialize HAL_GPIO state
 ******************************************************************************/
void halConfigInitGpio(void)
{
  // Clear GPIO state
  halConfigGpioActive = 0;
  MEMSET(halConfigGpio, 0, sizeof(halConfigGpio));
  // Initialize preset GPIO registration
#ifdef HAL_GPIO_INIT
  tGpioArray fixedGpioArray[] = HAL_GPIO_INIT;
  MEMCOPY(halConfigGpio, fixedGpioArray, sizeof(fixedGpioArray));
  int8_t i;
  for ( i = 0; i < (sizeof(fixedGpioArray) / sizeof(tGpioArray)); i++ ) {
    GPIOSETBIT(halConfigGpioActive, i);
  }
#endif
}

/******************************************************************************/
/**
 * @brief
 *   Power down GPIO. Sets all registered GPIO to disabled mode
 ******************************************************************************/
void halConfigPowerDownGpio()
{
  uint8_t i;
  for ( i = 0; i < HAL_GPIO_MAX; i++ ) {
    if (GPIOREADBIT(halConfigGpioActive, i)) {
      GPIO_PinModeSet(halConfigGpio[i].port,
                      halConfigGpio[i].pin,
                      halConfigGpio[i].pDownMode,
                      halConfigGpio[i].pDownOut);
    }
  }
}

/******************************************************************************/
/**
 * @brief
 *   Power up GPIO. Sets all registered GPIO to assigned mode/output
 ******************************************************************************/
void halConfigPowerUpGpio()
{
  uint8_t i;
  for ( i = 0; i < HAL_GPIO_MAX; i++ ) {
    if (GPIOREADBIT(halConfigGpioActive, i)) {
      GPIO_PinModeSet(halConfigGpio[i].port,
                      halConfigGpio[i].pin,
                      halConfigGpio[i].pUpMode,
                      halConfigGpio[i].pUpOut);
    }
  }
}

/******************************************************************************/
/**
 * @brief
 *   Register GPIO for powerup/powerdown configuration. If GPIO is already
 *   registered, current configuration will be overwritten
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number in the port.
 *
 * @param[in] pUpMode
 *   The desired pin mode when powering up.
 *
 * @param[in] pUpOut
 *   Value to set for pin in DOUT register on power down. The DOUT setting is
 *   important for even some input mode configurations, determining
 *   pull-up/down direction.
 *
 * @param[in] pDownMode
 *   The desired pin mode when powering down
 *
 * @param[in] pDownOut
 *   Value to set for pin in DOUT register on power down. The DOUT setting is
 *   important for even some input mode configurations, determining
 *   pull-up/down direction.
 *
 * @return
 *  True on success, false on failure (ran out of space)
 ******************************************************************************/
bool halConfigRegisterGpio(GPIO_Port_TypeDef port,
                           uint8_t pin,
                           GPIO_Mode_TypeDef pUpMode,
                           uint8_t pUpOut,
                           GPIO_Mode_TypeDef pDownMode,
                           uint8_t pDownOut)
{
  int8_t index;
  tGpioArray gpio = { port, pin, pUpMode, pUpOut, pDownMode, pDownOut };
  // Found active GPIO, overwrite current settings
  if (halConfigFindGpio(port, pin, &index)) {
    halConfigGpio[index] = gpio;
    return true;
  }
  // Register new GPIO
  else if (index >= 0) {
    GPIOSETBIT(halConfigGpioActive, index);
    halConfigGpio[index] = gpio;
    return true;
  }
  // No space remaining
  return false;
}

/******************************************************************************/
/**
 * @brief
 *   Unregister GPIO. Will diable automatic powerup/powerdown configuration.
 *
 * @param[in] port
 *   The GPIO port to access.
 *
 * @param[in] pin
 *   The pin number in the port.
 *
 * @return
 *  True on success, false on failure (could not find GPIO)
 ******************************************************************************/
bool halConfigUnregisterGpio(GPIO_Port_TypeDef port, uint8_t pin)
{
  int8_t index;
  if (!halConfigFindGpio(port, pin, &index)) {
    return false;
  }
  GPIOCLEARBIT(halConfigGpioActive, index);
  return true;
}
#endif //(HAL_GPIO_MAX==0)
