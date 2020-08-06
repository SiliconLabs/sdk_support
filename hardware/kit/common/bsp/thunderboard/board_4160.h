/***************************************************************************//**
 * @file
 * @brief BOARD module header file
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef BOARD_4160_H
#define BOARD_4160_H

#include <stdint.h>
#include <stdbool.h>

/**************************************************************************//**
* @addtogroup TBSense_BSP
* @{
******************************************************************************/

/***************************************************************************//**
 * @addtogroup BOARD_4160
 * @{
 ******************************************************************************/

uint32_t BOARD_picIntGet           (uint8_t *flags);
uint32_t BOARD_picIntClear         (uint8_t flags);
uint32_t BOARD_picWriteReg         (uint8_t addr, uint8_t value);
uint32_t BOARD_picReadReg          (uint8_t addr, uint8_t *result);
uint32_t BOARD_picRegBitsSet       (uint8_t addr, bool set, uint8_t bitMask);
uint32_t BOARD_picGetDeviceId      (void);
uint32_t BOARD_picGetFwRevision    (uint8_t *major, uint8_t *minor, uint8_t *patch);
uint8_t  BOARD_picGetHwRevision    (void);
bool     BOARD_picIsLegacyIntCtrl  (void);

uint32_t BOARD_gasSensorEnable     (bool enable);
uint32_t BOARD_gasSensorEnableIRQ  (bool enable);
void     BOARD_gasSensorClearIRQ   (void);
uint32_t BOARD_gasSensorWake       (bool wake);
void     BOARD_gasSensorSetIRQCallback(BOARD_IrqCallback cb);

uint32_t BOARD_bapEnable           (bool enable);

void     BOARD_pushButton0SetIRQCallback (BOARD_IrqCallback cb);
void     BOARD_pushButton0ClearIRQ       (void);
void     BOARD_pushButton1SetIRQCallback (BOARD_IrqCallback cb);
void     BOARD_pushButton1ClearIRQ       (void);

void     BOARD_rgbledEnable        (bool enable, uint8_t mask);
void     BOARD_rgbledSetColor      (uint8_t red, uint8_t green, uint8_t blue);
void     BOARD_rgbledSetRawColor   (uint16_t red, uint16_t green, uint16_t blue);
void     BOARD_rgbledPowerEnable   (bool enable);

/** @} */
/** @} */

#endif // BOARD_4160_H
