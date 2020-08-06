/***************************************************************************//**
 * @file
 * @brief Debug plugin for Silicon Labs Bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef BTL_DEBUG_H
#define BTL_DEBUG_H

#include "config/btl_config.h"
#include "stdint.h"
#include "core/btl_util.h"

MISRAC_DISABLE
#include "em_common.h"
MISRAC_ENABLE

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup Debug
 * @{
 * @brief Debug Plugin
 * @details
 *   This plugin provides the bootloader with support for debugging functions.
 *   The plugin implements two types of debugging functionality:
 *   * Defining BTL_PLUGIN_DEBUG_ASSERT enables assertions on compile-time
 *     configurable parameters in the bootloader
 *   * Defining BTL_PLUGIN_DEBUG_PRINT enables debug prints at strategic
 *     points in the code.
 ******************************************************************************/

#if defined(BTL_PLUGIN_DEBUG_ASSERT)
#if defined(BTL_PLUGIN_DEBUG_ASSERT_VERBOSE)
SL_NORETURN void btl_assert(const char* file, int line);

#define BTL_ASSERT(exp)  ((exp) ? ((void)0) : btl_assert(__FILE__, __LINE__))
#else
SL_NORETURN void btl_assert(void);

#define BTL_ASSERT(exp)  ((exp) ? ((void)0) : btl_assert())
#endif
#else
/// Assertion in bootloader
#define BTL_ASSERT(exp)  ((void)(exp))
#endif

// Print debug information throughout the bootloader
#if defined(BTL_PLUGIN_DEBUG_PRINT)

#ifndef BTL_DEBUG_NEWLINE
#define BTL_DEBUG_NEWLINE "\n"
#endif

void btl_debugInit(void);
void btl_debugWriteChar(char c);
void btl_debugWriteString(const char * s);
void btl_debugWriteLine(const char * s);

void btl_debugWriteCharHex(uint8_t number);
void btl_debugWriteShortHex(uint16_t number);
void btl_debugWriteWordHex(uint32_t number);
void btl_debugWriteInt(int number);
void btl_debugWriteNewline(void);

#define BTL_DEBUG_INIT()                  (btl_debugInit())
#define BTL_DEBUG_PRINT(str)              (btl_debugWriteString(str))
#define BTL_DEBUG_PRINTLN(str)            (btl_debugWriteLine(str))
#define BTL_DEBUG_PRINTC(chr)             (btl_debugWriteChar(chr))

#define BTL_DEBUG_PRINT_CHAR_HEX(number)  (btl_debugWriteCharHex(number))
#define BTL_DEBUG_PRINT_SHORT_HEX(number) (btl_debugWriteShortHex(number))
#define BTL_DEBUG_PRINT_WORD_HEX(number)  (btl_debugWriteWordHex(number))
#define BTL_DEBUG_PRINT_LF()              (btl_debugWriteNewline())

#else // No debug prints

/// Initialize debug output
#define BTL_DEBUG_INIT()                  do {} while (0)
/// Print a string to debug out
#define BTL_DEBUG_PRINT(str)              do {} while (0)
/// Print a string followed by a newline to debug out
#define BTL_DEBUG_PRINTLN(str)            do {} while (0)
/// Print a character to debut out
#define BTL_DEBUG_PRINTC(chr)             do {} while (0)
/// Print a single hex byte
#define BTL_DEBUG_PRINT_CHAR_HEX(number)  do {} while (0)
/// Print two hex bytes
#define BTL_DEBUG_PRINT_SHORT_HEX(number) do {} while (0)
/// Print a hex word
#define BTL_DEBUG_PRINT_WORD_HEX(number)  do {} while (0)
/// Print a newline
#define BTL_DEBUG_PRINT_LF()              do {} while (0)

#endif

/**
 * @} (end addtogroup Debug)
 * @} (end addtogroup Plugin)
 */

#endif // BTL_DEBUG_H
