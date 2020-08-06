/***************************************************************************//**
 * @file
 * @brief Utility and convenience functions for EM35x microcontroller.
 * See @ref micro for documentation.
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
/** @addtogroup micro
 * See also hal/micro/cortexm3/micro.h for source code.
 *@{
 */

#ifndef __EM3XX_MICRO_H__
#define __EM3XX_MICRO_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS

#ifndef __MICRO_H__
#error do not include this file directly - include micro/micro.h
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifndef __EMBERSTATUS_TYPE__
#define __EMBERSTATUS_TYPE__
//This is necessary here because halSetRadioHoldOff returns an
//EmberStatus and not adding this typedef to this file breaks a
//whole lot of builds due to include mis-ordering
typedef uint8_t EmberStatus;
#endif //__EMBERSTATUS_TYPE__
#endif // DOXYGEN_SHOULD_SKIP_THIS

// Micro specific serial defines
#define EM_NUM_SERIAL_PORTS 4
#define EMBER_SPI_MASTER 4
#define EMBER_SPI_SLAVE 5
#define EMBER_I2C 6

// Define the priority registers of system handlers and interrupts.
// This example shows how to save the current ADC interrupt priority and
// then set it to 24:
//    uint8_t oldAdcPriority = INTERRUPT_PRIORITY_REGISTER(ADC);
//    INTERRUPT_PRIORITY_REGISTER(ADC) = 24;

// For Cortex-M3 faults and exceptions
#define HANDLER_PRIORITY_REGISTER(handler) \
  (*(((uint8_t *)SCS_SHPR_7to4_ADDR) + handler##_VECTOR_INDEX - 4))

// For EM3XX-specific interrupts
#define INTERRUPT_PRIORITY_REGISTER(interrupt) \
  (*(((uint8_t *)NVIC_IPR_3to0_ADDR) + interrupt##_VECTOR_INDEX - 16))

// The reset types of the EM300 series have both a base type and an
//  extended type.  The extended type is a 16-bit value which has the base
//  type in the upper 8-bits, and the extended classification in the
//  lower 8-bits
// For backwards compatibility with other platforms, only the base type is
//  returned by the halGetResetInfo() API.  For the full extended type, the
//  halGetExtendedResetInfo() API should be called.

#define RESET_BASE_TYPE(extendedType)   ((uint8_t)(((extendedType) >> 8) & 0xFF))
#define RESET_EXTENDED_FIELD(extendedType) ((uint8_t)((extendedType) & 0xFF))
#define RESET_VALID_SIGNATURE           (0xF00F)
#define RESET_INVALID_SIGNATURE         (0xC33C)

// Define the base reset cause types
#define RESET_BASE_DEF(basename, value, string)  RESET_##basename = value,
#define RESET_EXT_DEF(basename, extname, extvalue, string)     /*nothing*/
enum {
  #include "reset-def.h"
  NUM_RESET_BASE_TYPES
};

#undef RESET_BASE_DEF
#undef RESET_EXT_DEF

// Define the extended reset cause types
#define RESET_EXT_VALUE(basename, extvalue) \
  (((RESET_##basename) << 8) + extvalue)
#define RESET_BASE_DEF(basename, value, string)    /*nothing*/
#define RESET_EXT_DEF(basename, extname, extvalue, string) \
  RESET_##basename##_##extname = RESET_EXT_VALUE(basename, extvalue),
enum {
  #include "reset-def.h"
};

#undef RESET_EXT_VALUE
#undef RESET_BASE_DEF
#undef RESET_EXT_DEF

// These define the size of the GUARD region configured in the MPU that
// sits between the heap and the stack
#define HEAP_GUARD_REGION_SIZE       (SIZE_32B)
#define HEAP_GUARD_REGION_SIZE_BYTES (1 << (HEAP_GUARD_REGION_SIZE + 1))

// Define a value to fill the guard region between the heap and stack.
#define HEAP_GUARD_FILL_VALUE (0xE2E2E2E2U)

// Resize the CSTACK to add space to the 'heap' that exists below it
uint32_t halStackModifyCStackSize(int32_t stackSizeDeltaWords);

// Initialize the CSTACK/Heap region and the guard page in between them
void halInternalInitCStackRegion(void);

// Helper functions to get the location of the stack/heap
uint32_t halInternalGetCStackBottom(void);
uint32_t halInternalGetHeapTop(void);
uint32_t halInternalGetHeapBottom(void);

// Determines reset cause
void halInternalClassifyReset(void);

#endif // DOXYGEN_SHOULD_SKIP_THIS

/** @name Vector Table Index Definitions
 * These are numerical definitions for vector table. Indices 0 through 15 are
 * Cortex-M3 standard exception vectors and indices 16 through 35 are EM3XX
 * specific interrupt vectors.
 *
 *@{
 */

/**
 * @brief A numerical definition for a vector.
 */
#define STACK_VECTOR_INDEX          0U // special case: stack pointer at reset
#define RESET_VECTOR_INDEX          1U
#define NMI_VECTOR_INDEX            2U
#define HARD_FAULT_VECTOR_INDEX     3U
#define MEMORY_FAULT_VECTOR_INDEX   4U
#define BUS_FAULT_VECTOR_INDEX      5U
#define USAGE_FAULT_VECTOR_INDEX    6U
#define RESERVED07_VECTOR_INDEX     7U
#define RESERVED08_VECTOR_INDEX     8U
#define RESERVED09_VECTOR_INDEX     9U
#define RESERVED10_VECTOR_INDEX     10U
#define SVCALL_VECTOR_INDEX         11U
#define DEBUG_MONITOR_VECTOR_INDEX  12U
#define RESERVED13_VECTOR_INDEX     13U
#define PENDSV_VECTOR_INDEX         14U
#define SYSTICK_VECTOR_INDEX        15U
#define TIMER1_VECTOR_INDEX         16U
#define TIMER2_VECTOR_INDEX         17U
#define MANAGEMENT_VECTOR_INDEX     18U
#define BASEBAND_VECTOR_INDEX       19U
#define SLEEP_TIMER_VECTOR_INDEX    20U
#define SC1_VECTOR_INDEX            21U
#define SC2_VECTOR_INDEX            22U
#define SECURITY_VECTOR_INDEX       23U
#define MAC_TIMER_VECTOR_INDEX      24U
#define MAC_TX_VECTOR_INDEX         25U
#define MAC_RX_VECTOR_INDEX         26U
#define ADC_VECTOR_INDEX            27U
#define IRQA_VECTOR_INDEX           28U
#define IRQB_VECTOR_INDEX           29U
#define IRQC_VECTOR_INDEX           30U
#define IRQD_VECTOR_INDEX           31U
#define DEBUG_VECTOR_INDEX          32U
#define SC3_VECTOR_INDEX            33U
#define SC4_VECTOR_INDEX            34U
#define USB_VECTOR_INDEX            35U

/**
 * @brief Number of vectors.
 */
#define VECTOR_TABLE_LENGTH         36U

/** @}  Vector Table Index Definitions */

/**
 * @brief Records the specified reset cause then forces a reboot.
 */
void halInternalSysReset(uint16_t extendedCause);

/**
 * @brief Returns the Extended Reset Cause information
 *
 * @return A 16-bit code identifying the base and extended cause of the reset
 */
uint16_t halGetExtendedResetInfo(void);

/** @brief Calls ::halGetExtendedResetInfo() and supplies a string describing
 *  the extended cause of the reset.  halGetResetString() should also be called
 *  to get the string for the base reset cause
 *
 * @appusage Useful for diagnostic printing of text just after program
 * initialization.
 *
 * @return A pointer to a program space string.
 */
PGM_P halGetExtendedResetString(void);








































/** @brief Enables or disables Radio HoldOff support
 *
 * @param enable  When true, configures ::RHO_GPIO in BOARD_HEADER
 * as an input which, when asserted, will prevent the radio from
 * transmitting.  When false, configures ::RHO_GPIO for its original
 * default purpose.
 *
 * @return EMBER_SUCCESS if Radio HoldOff was configured as desired
 * or EMBER_BAD_ARGUMENT if requesting it be enabled but RHO has not
 * been configured by the BOARD_HEADER.
 */
EmberStatus halSetRadioHoldOff(bool enable);

/** @brief Returns whether Radio HoldOff has been enabled or not.
 *
 * @return true if Radio HoldOff has been enabled, false otherwise.
 */
bool halGetRadioHoldOff(void);

/** @brief To assist with saving power when the radio automatically powers
 * down, this function allows the stack to tell the HAL to put pins
 * specific to radio functionality in their powerdown state.  The pin
 * state used is the state used by halInternalPowerDownBoard, but applied
 * only to the pins identified in the global variable gpioRadioPowerBoardMask.
 * The stack will automatically call this function as needed, but it
 * will only change GPIO state based on gpioRadioPowerBoardMask.  Most
 * commonly, the bits set in gpioRadioPowerBoardMask petain to using a
 * Front End Module.  This function is often called from interrupt context.
 */
void halStackRadioPowerDownBoard(void);

/** @brief To assist with saving power when radio2 automatically powers
 * down, this function allows the stack to tell the HAL to put pins
 * specific to radio functionality in their powerdown state.  The pin
 * state used is the state used by halInternalPowerDownBoard, but applied
 * only to the pins identified in the global variable gpioRadioPowerBoardMask.
 * The stack will automatically call this function as needed, but it
 * will only change GPIO state based on gpioRadioPowerBoardMask.  Most
 * commonly, the bits set in gpioRadioPowerBoardMask petain to using a
 * Front End Module.  This function is often called from interrupt context.
 */
void halStackRadio2PowerDownBoard(void);

/** @brief To assist with saving power when the radio automatically powers
 * up, this function allows the stack to tell the HAL to put pins
 * specific to radio functionality in their powerup state.  The pin
 * state used is the state used by halInternalPowerUpBoard, but applied
 * only to the pins identified in the global variable gpioRadioPowerBoardMask.
 * The stack will automatically call this function as needed, but it
 * will only change GPIO state based on gpioRadioPowerBoardMask.  Most
 * commonly, the bits set in gpioRadioPowerBoardMask petain to using a
 * Front End Module.  This function can be called from interrupt context.
 */
void halStackRadioPowerUpBoard(void);

/** @brief To assist with saving power when radio2 automatically powers
 * up, this function allows the stack to tell the HAL to put pins
 * specific to radio functionality in their powerup state.  The pin
 * state used is the state used by halInternalPowerUpBoard, but applied
 * only to the pins identified in the global variable gpioRadioPowerBoardMask.
 * The stack will automatically call this function as needed, but it
 * will only change GPIO state based on gpioRadioPowerBoardMask.  Most
 * commonly, the bits set in gpioRadioPowerBoardMask petain to using a
 * Front End Module.  This function can be called from interrupt context.
 */
void halStackRadio2PowerUpBoard(void);

/** @brief This function is called automatically by the stack prior to Radio
 * power-up and after Radio power-down.  It can be used to prepare for the
 * radio being powered on and to clean up after it's been powered off.  Unlike
 * halStackRadioPowerUpBoard() and halStackRadioPowerDownBoard(), which can
 * be called from interrupt context, this function is only called from
 * main-line context.
 */
void halStackRadioPowerMainControl(bool powerUp);

/**
 * @brief Handler called in main context prior to radio being powered on
 */
void halRadioPowerUpHandler(void);

/**
 * @brief Handler called in main context after radio has been powered off
 */
void halRadioPowerDownHandler(void);

#include "micro-common.h"

#endif //__EM3XX_MICRO_H__

/**@} END micro group
 */
