/***************************************************************************//**
 * @file
 * @brief External Device GPIO driver
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
#include "stack/include/ember-types.h"
#include "stack/include/error.h"
#include "hal/hal.h"

#include "ext-device.h"         // Implement this API

#ifdef  ENABLE_EXT_DEVICE       // Driver is enabled

//== DRIVER CONFIGURATION ==

/** @brief API to access External Device GPIOs configured by BOARD_HEADER:
 *  - EXT_DEVICE_PWR  Power signal
 *  - EXT_DEVICE_RDY  Ready signal
 *  - EXT_DEVICE_SEL  Select signal
 *  - EXT_DEVICE_INT  Interrupt signal
 *  It is not necessary to provide any which don't apply to the design.
 *  Each one requires 4 definitions: itself, two helpers (_PORT and _BIT
 *  which make for efficient code), and its true-asserted value (polarity).
 *  E.g.:
 *      #define EXT_DEVICE_INT          PORTB_PIN(6)
 *      #define EXT_DEVICE_INT_PORT     1
 *      #define EXT_DEVICE_INT_BIT      6
 *      #define EXT_DEVICE_INT_TRUE     0 // 0=low true, 1=high true
 *  For EXT_DEVICE_INT, and optionally EXT_DEVICE_RDY if want a distinct
 *  ready interrupt, must additionally provide the IRQx selection and
 *  the settings for its EVENT_GPIO_CFGx register (EVENT_GPIO_CFGx_FILT and
 *  EVENT_GPIO_CFGx_MOD fields):
 *      #define EXT_DEVICE_INT_IRQ    B   // A,B,C,D are the valid IRQs
 *      #define EXT_DEVICE_INT_IRQCFG (EVENT_GPIO_CFGx_MOD_LOW_LEVEL)
 *  Finally, for EXT_DEVICE_INT/EXT_DEVICE_RDY, IRQ priority can be provided.
 *  NVIC_ATOMIC achieves interrupt disabled since this file used the
 *  NVIC_SetPriority and NVIC_EncodePriority which shifts the value and
 *  sets the correct register.
 *      #define EXT_DEVICE_INT_IRQPRI   NVIC_ATOMIC
 */

//== DEFINITIONS ==

// Some handy-dandy preprocessor magic
#define PASTE(a, b, c)       a##b##c
#define EVAL3(a, b, c)       PASTE(a, b, c)

//-- GPIO access for signals
#define GPIO_P_IN(port, bit)  (!!(GPIO->P[port].IN  & EVAL3(_GPIO_P_IN_Px, bit, _MASK)))
#define GPIO_P_CLR(port, bit)  (GPIO->P[port].CLR = EVAL3(_GPIO_P_CLR_Px, bit, _MASK))
#define GPIO_P_SET(port, bit)  (GPIO->P[port].SET = EVAL3(_GPIO_P_SET_Px, bit, _MASK))

//-- Access for interrupts.  'gpioPort' parameter is A, B, C, or D.
// GPIO IRQ interrupt handler function (halIrqxIsr).
#define GPIO_IRQx_ISR(gpioPort)         (EVAL3(halIrq, gpioPort, Isr))
// EVENT_GPIO->CFGx register
#define EVENT_GPIO_CFGx(gpioPort)       (EVAL3(EVENT_GPIO->CFG, gpioPort, ))
// IRQx_IRQn top level NVIC interrupt number, for NVIC_DisableIRQ/NVIC_EnableIRQ
#define IRQx_IRQn(gpioPort)             (EVAL3(IRQ, gpioPort, _IRQn))
// EVENT_GPIO_FLAG_IRQx bit for EVENT_GPIO->FLAG register
#define EVENT_GPIO_FLAG_IRQx(gpioPort)  (EVAL3(EVENT_GPIO_FLAG_IRQ, gpioPort, ))
// EVENT_MISS_MISS_IRQx bit for EVENT_MISS->MISS register
#define EVENT_MISS_IRQx(gpioPort)       (EVAL3(EVENT_MISS_MISS_IRQ, gpioPort, ))
// Set interrupt priority register
#define SET_IRQx_IRQn_PRIORITY(gpioPort, priority) \
  NVIC_SetPriority(IRQx_IRQn(gpioPort), NVIC_EncodePriority(PRIGROUP_POSITION, priority, 0))

// Handy for explicit cases in "switch (EXT_DEVICE_RDY_IRQ)"
enum { A, B, C, D, MAXIRQ };

//== LOCAL STATE ==

static HalExtDeviceIrqCB halExtDeviceIntCB = NULL;
static HalExtDeviceIrqCB halExtDeviceRdyCB = NULL;
static bool halExtDevicePowered = false;
static bool halExtDeviceSelected = false;
static uint8_t halExtDeviceIntLevel = EXT_DEVICE_INT_UNCONFIGURED;

//== HELPER FUNCTIONS ==

/** @brief Configure and enable/disable the device ready IRQ
 */
static void halExtDeviceRdyCfgIrq(void)
{
  #ifdef  EXT_DEVICE_RDY_IRQ
  // The logic here is basically:
  // - If device isn't powered (e.g. at boot), just disable and configure IRQ.
  // - If device is powered then clear out anything stale and enable or
  //   disable IRQ as indicated by its callback.
  if (!halExtDevicePowered) {
    // Start from a fresh state just in case
    EVENT_GPIO_CFGx(EXT_DEVICE_RDY_IRQ) = 0;  // Disable GPIO IRQx
    NVIC_DisableIRQ(IRQx_IRQn(EXT_DEVICE_RDY_IRQ));  // Disable top level
    // Configure interrupt mode
    EVENT_GPIO_CFGx(EXT_DEVICE_RDY_IRQ) = EXT_DEVICE_RDY_IRQCFG;
    // Point IRQC/D at the right pin -- a bit kludgy but avoids warnings
    switch (EXT_DEVICE_RDY_IRQ) {
      case C:
        GPIO->IRQCSEL = EXT_DEVICE_RDY;
        break;
      case D:
        GPIO->IRQDSEL = EXT_DEVICE_RDY;
        break;
      default:
        break;
    }
    #ifdef  EXT_DEVICE_RDY_IRQPRI
    // Need to change the interrupt's priority in the NVIC
    SET_IRQx_IRQn_PRIORITY(EXT_DEVICE_RDY_IRQ, EXT_DEVICE_RDY_IRQPRI);
    #endif//EXT_DEVICE_RDY_IRQPRI
  } else {
    // Clear out any stale state
    NVIC_DisableIRQ(IRQx_IRQn(EXT_DEVICE_RDY_IRQ));  // Disable top level
    EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear 2nd level
    EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear any missed
    NVIC_ClearPendingIRQ(IRQx_IRQn(EXT_DEVICE_RDY_IRQ));  // Clear any pended
    if (halExtDeviceRdyCB != NULL) {
      NVIC_EnableIRQ(IRQx_IRQn(EXT_DEVICE_RDY_IRQ));  // Enable top level
    }
  }
  #endif//EXT_DEVICE_RDY_IRQ
}

/** @brief Configure and enable/disable the device interrupt IRQ
 */
static void halExtDeviceIntCfgIrq(void)
{
  #ifdef  EXT_DEVICE_INT_IRQ
  // The logic here is basically:
  // - If device isn't powered (e.g. at boot), just disable and configure IRQ.
  // - If device is powered then clear out anything stale and enable or
  //   disable IRQ as indicated by its callback.
  if (!halExtDevicePowered) {
    // Start from a fresh state just in case
    EVENT_GPIO_CFGx(EXT_DEVICE_INT_IRQ) = 0;  // Disable GPIO IRQx
    NVIC_DisableIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Disable top level
    // Configure interrupt mode
    EVENT_GPIO_CFGx(EXT_DEVICE_INT_IRQ) = EXT_DEVICE_INT_IRQCFG;
    // Point IRQC/D at the right pin -- a bit kludgy but avoids warnings
    switch (EXT_DEVICE_INT_IRQ) {
      case C:
        GPIO->IRQCSEL = EXT_DEVICE_INT;
        break;
      case D:
        GPIO->IRQDSEL = EXT_DEVICE_INT;
        break;
      default:
        break;
    }
     #ifdef  EXT_DEVICE_INT_IRQPRI
    // Need to change the interrupt's priority in the NVIC
    SET_IRQx_IRQn_PRIORITY(EXT_DEVICE_INT_IRQ, EXT_DEVICE_INT_IRQPRI);
     #endif//EXT_DEVICE_INT_IRQPRI
  } else {
    // Clear out any stale state
    NVIC_DisableIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Disable top level
    EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_INT_IRQ);  // Clear 2nd level
    EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_INT_IRQ);  // Clear any missed
    NVIC_ClearPendingIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Clear any pended
    if (halExtDeviceIntCB == NULL) {
      halExtDeviceIntLevel = EXT_DEVICE_INT_UNCONFIGURED;
    } else {
      halExtDeviceIntLevel = EXT_DEVICE_INT_LEVEL_OFF;
      // Callers need to use halExtDeviceIntEnable() to enable top level
    }
  }
  #endif//EXT_DEVICE_INT_IRQ
}

//== INTERNAL ISRS ==

#ifdef EXT_DEVICE_RDY_IRQ
void GPIO_IRQx_ISR(EXT_DEVICE_RDY_IRQ)(void)
{
  #if (EXT_DEVICE_RDY_IRQCFG < (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Acknowledge edge-triggered interrupt before callback, so don't miss edge
  EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear any missed
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear 2nd level
  #endif //(EXT_DEVICE_RDY_IRQCFG < (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Issue callback -- in ISR context
  if (halExtDeviceRdyCB != NULL) {
    (*halExtDeviceRdyCB)();
  }
  #if (EXT_DEVICE_RDY_IRQCFG >= (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Acknowledge level-triggered interrupt after callback
  EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear any missed
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_RDY_IRQ);  // Clear 2nd level
  #endif //(EXT_DEVICE_RDY_IRQCFG >= (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
}
#endif //EXT_DEVICE_RDY_IRQ

#ifdef EXT_DEVICE_INT_IRQ
void GPIO_IRQx_ISR(EXT_DEVICE_INT_IRQ)(void)
{
  #if (EXT_DEVICE_INT_IRQCFG < (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Acknowledge edge-triggered interrupt before callback, so don't miss edge
  EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_INT_IRQ);  // Clear any missed
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_INT_IRQ);  // Clear 2nd level
  #endif //(EXT_DEVICE_INT_IRQCFG < (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Issue callback -- in ISR context
  if (halExtDeviceIntCB != NULL) {
    (*halExtDeviceIntCB)();
  }
  #if (EXT_DEVICE_INT_IRQCFG >= (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
  // Acknowledge level-triggered interrupt after callback
  EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_INT_IRQ);  // Clear any missed
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_INT_IRQ);  // Clear 2nd level
  #endif //(EXT_DEVICE_INT_IRQCFG >= (EVENT_GPIO_CFGx_MOD_HIGH_LEVEL))
}
#endif //EXT_DEVICE_INT_IRQ

//== API FUNCTIONS ==

//-- External Device Initialization --

/** @brief Initialize External Device GPIOs
 * @param  deviceIntCB The callback routine for device general interrupt
 *                     (NULL to disable)
 * @param  deviceRdyCB The callback routine for device ready interrupt
 *                     (NULL to disable)
 * @return bitmask of configured features for this device
 * @note First initialization after bootup leaves the device powered down
 *       and unselected.  Subsequent inits don't touch the device powered
 *       or selected states and can be used to reconfigure callback(s),
 *       which always clears any stale/pending events.  For deviceRdyCB,
 *       its interrupt is enabled upon configuration; for deviceIntCB,
 *       halExtDeviceIntEnable() must subsequently be called to enable it.
 */
HalExtDeviceConfig halExtDeviceInit(HalExtDeviceIrqCB deviceIntCB,
                                    HalExtDeviceIrqCB deviceRdyCB)
{
  // BOARD_HEADER should already have specified proper GPIO configuration

  // Record (new) ISR information
  UNUSED_VAR(halExtDeviceRdyCB); // Work around potential compiler warnings
  UNUSED_VAR(halExtDeviceIntCB); // Work around potential compiler warnings
  halExtDeviceRdyCB = deviceRdyCB;
  halExtDeviceIntCB = deviceIntCB;
  // Inits while not powered simply ensure device is indeed not powered and
  // not selected.
  // Inits while powered just update the IRQ callbacks.
  if (!halExtDevicePowered) {
    halExtDeviceDeselect();
    halExtDevicePowerDown();
  } else {
    halExtDeviceRdyCfgIrq();
    halExtDeviceIntCfgIrq();
  }

  return (0
        #ifdef  EXT_DEVICE_PWR
          | EXT_DEVICE_HAS_PWR
        #endif//EXT_DEVICE_PWR
        #ifdef  EXT_DEVICE_RDY
          | EXT_DEVICE_HAS_RDY
        #ifdef  EXT_DEVICE_RDY_IRQ
          | EXT_DEVICE_HAS_RDY_IRQ
        #endif//EXT_DEVICE_RDY_IRQ
        #endif//EXT_DEVICE_RDY
        #ifdef  EXT_DEVICE_SEL
          | EXT_DEVICE_HAS_SEL
        #endif//EXT_DEVICE_SEL
        #ifdef  EXT_DEVICE_INT
          | EXT_DEVICE_HAS_INT
        #ifdef  EXT_DEVICE_INT_IRQ
          | EXT_DEVICE_HAS_INT_IRQ
        #endif//EXT_DEVICE_INT_IRQ
        #endif//EXT_DEVICE_INT
          );
}

//-- External Device Power --

/** @brief Power down the external device per GPIO
 */
void halExtDevicePowerDown(void)
{
  // Shut off ISRs before removing power, in case of glitches
  halExtDevicePowered = false;
  halExtDeviceRdyCfgIrq();
  halExtDeviceIntCfgIrq();

  #ifdef EXT_DEVICE_PWR
  // Deassert Power
    #if (EXT_DEVICE_PWR_TRUE)
  GPIO_P_CLR(EXT_DEVICE_PWR_PORT, EXT_DEVICE_PWR_BIT);
    #else //!(EXT_DEVICE_PWR_TRUE)
  GPIO_P_SET(EXT_DEVICE_PWR_PORT, EXT_DEVICE_PWR_BIT);
    #endif //(EXT_DEVICE_PWR_TRUE)
  #endif //EXT_DEVICE_PWR
}

/** @brief Power up the external device per GPIO
 */
void halExtDevicePowerUp(void)
{
  // Enable ISRs before powering so they can notify when device is ready
  halExtDevicePowered = true;
  halExtDeviceRdyCfgIrq();
  halExtDeviceIntCfgIrq();

  #ifdef EXT_DEVICE_PWR
  // Assert power
    #if (EXT_DEVICE_PWR_TRUE)
  GPIO_P_SET(EXT_DEVICE_PWR_PORT, EXT_DEVICE_PWR_BIT);
    #else //!(EXT_DEVICE_PWR_TRUE)
  GPIO_P_CLR(EXT_DEVICE_PWR_PORT, EXT_DEVICE_PWR_BIT);
    #endif //(EXT_DEVICE_PWR_TRUE)
  #endif //EXT_DEVICE_PWR
}

//-- External Device Ready --

/** @brief Indicate if the device is ready per GPIO
 * @return true if device is ready, false otherwise
 */
bool halExtDeviceIsReady(void)
{
  #ifdef EXT_DEVICE_RDY
  return (halExtDevicePowered
          && GPIO_P_IN(EXT_DEVICE_RDY_PORT, EXT_DEVICE_RDY_BIT)
          == EXT_DEVICE_RDY_TRUE);
  #else //!EXT_DEVICE_RDY
  return halExtDevicePowered;   // Assume ready only when powered
  #endif //EXT_DEVICE_RDY
}

/** @brief Wait for the device to become ready per GPIO
 */
void halExtDeviceWaitReady(void)
{
  halResetWatchdog();
  while (!halExtDeviceIsReady()) {
    // spin
  }
  halResetWatchdog();
}

//-- External Device Selection --

/** @brief Select the external device
 */
void halExtDeviceSelect(void)
{
  halExtDeviceSelected = true;
  #ifdef EXT_DEVICE_SEL
  // Assert select
    #if (EXT_DEVICE_SEL_TRUE)
  GPIO_P_SET(EXT_DEVICE_SEL_PORT, EXT_DEVICE_SEL_BIT);
    #else //!(EXT_DEVICE_SEL_TRUE)
  GPIO_P_CLR(EXT_DEVICE_SEL_PORT, EXT_DEVICE_SEL_BIT);
    #endif //(EXT_DEVICE_SEL_TRUE)
  #endif //EXT_DEVICE_SEL
}

/** @brief Unselect the external device
 */
void halExtDeviceDeselect(void)
{
  halExtDeviceSelected = false;
  #ifdef EXT_DEVICE_SEL
  // Deassert select
    #if (EXT_DEVICE_SEL_TRUE)
  GPIO_P_CLR(EXT_DEVICE_SEL_PORT, EXT_DEVICE_SEL_BIT);
    #else //!(EXT_DEVICE_SEL_TRUE)
  GPIO_P_SET(EXT_DEVICE_SEL_PORT, EXT_DEVICE_SEL_BIT);
    #endif //(EXT_DEVICE_SEL_TRUE)
  #endif //EXT_DEVICE_SEL
}

/** @brief Indicate if the device is selected
 */
bool halExtDeviceIsSelected(void)
{
  return halExtDeviceSelected;
}

//-- External Device Interrupts --

/** @brief Indicate if device interrupt GPIO is pending
 * @return true if device interrupt is pending, false otherwise
 */
bool halExtDeviceIntPending(void)
{
  #ifdef  EXT_DEVICE_INT
  //FIXME: This is pure GPIO level -- should it check INT_PENDING instead?
  return (halExtDevicePowered
          && GPIO_P_IN(EXT_DEVICE_INT_PORT, EXT_DEVICE_INT_BIT)
          == EXT_DEVICE_INT_TRUE);
  #else  //!EXT_DEVICE_INT
  return false;  // Assume never pending
  #endif  //EXT_DEVICE_INT
}

/** @brief Disable device interrupt and increment interrupt nesting level.
 * @return interrupt level prior to disabling (0=interrupts were enabled)
 */
HalExtDeviceIntLevel halExtDeviceIntDisable(void)
{
  #ifdef  EXT_DEVICE_INT
  uint8_t origLevel;
  NVIC_DisableIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Disable top level
  // We don't bother with 2nd-level here
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS(); // disable interrupts because these routines might be called from other ISRs
    origLevel = halExtDeviceIntLevel;
    if (origLevel != EXT_DEVICE_INT_UNCONFIGURED) {
      halExtDeviceIntLevel += 1;
    }
    RESTORE_INTERRUPTS();
  }
  return origLevel;
  #else  //!EXT_DEVICE_INT
  return EXT_DEVICE_INT_UNCONFIGURED;
  #endif  //EXT_DEVICE_INT
}

/** @brief Decrement interrupt nesting level and, if 0, enable device
 * interrupt.
 * @param  clearPending if true clears any "stale" pending interrupt just
 *         prior to enabling device interrupt.
 * @return interrupt level prior to enabling (0=interrupts were enabled)
 */
HalExtDeviceIntLevel halExtDeviceIntEnable(bool clearPending)
{
  #ifdef  EXT_DEVICE_INT
  uint8_t origLevel;
  bool justEnabled = false;
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS(); // disable interrupts because these routines might be called from other ISRs
    origLevel = halExtDeviceIntLevel;
    if (origLevel != EXT_DEVICE_INT_UNCONFIGURED) {
      if (origLevel > EXT_DEVICE_INT_LEVEL_ON) {   // Peg at LEVEL_ON
        halExtDeviceIntLevel -= 1;
        justEnabled = (halExtDeviceIntLevel == EXT_DEVICE_INT_LEVEL_ON);
      }
    }
    RESTORE_INTERRUPTS();
  }
  if (clearPending) {
    // Clear out any stale state
    EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQx(EXT_DEVICE_INT_IRQ);  // Clear 2nd level
    EVENT_MISS->MISS = EVENT_MISS_IRQx(EXT_DEVICE_INT_IRQ);  // Clear any missed
    NVIC_ClearPendingIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Clear any pended
  }
  if (justEnabled) {
    NVIC_EnableIRQ(IRQx_IRQn(EXT_DEVICE_INT_IRQ));  // Enable top level
  }
  return origLevel;
  #else  //!EXT_DEVICE_INT
  UNUSED_VAR(clearPending);
  return EXT_DEVICE_INT_UNCONFIGURED;
  #endif  //EXT_DEVICE_INT
}

#endif//ENABLE_EXT_DEVICE       // Driver is enabled
