/***************************************************************************//**
 * @file hal.h
 * @brief Header file for the Legacy HAL
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

#ifndef HAL_H
#define HAL_H

#ifdef TOKEN_MANAGER_TEST
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#else // TOKEN_MANAGER_TEST
#include "ember.h"
#endif // TOKEN_MANAGER_TEST
#include "error-def.h"
#include "micro.h"
#include "serial.h"
#include "led.h"
#include "button.h"
#include "crc.h"

#if defined(SL_CATALOG_LEGACY_BOOTLOADER_INTERFACE_PRESENT)
#include "bootloader-common.h"
#include "bootloader-interface.h"
#include "bootloader-interface-app.h"
#include "bootloader-interface-standalone.h"
#endif

#include "random.h"
#include "sl_token_api.h"
#include "cortexm3/diagnostic.h"

#define SECURITY_BLOCK_SIZE   16 // in bytes

/***************************************************************************//**
 * @addtogroup legacyhal Legacy HAL
 * @brief Legacy HAL API
 * @{
 ******************************************************************************/

uint16_t halCommonGetInt16uMillisecondTick(void);
uint32_t halCommonGetInt32uMillisecondTick(void);
uint64_t halCommonGetInt64uMillisecondTick(void);
uint16_t halCommonGetInt16uQuarterSecondTick(void);
uint16_t halInternalStartSystemTimer(void);
void halCommonDelayMicroseconds(uint16_t us);
void halCommonDelayMilliseconds(uint16_t ms);
void halStackSymbolDelayAIsr(void);
#define simulatedTimePasses()

void halStackRadioPowerMainControl(bool powerUp);
void halStackRadioPowerUpBoard(void);
void halStackRadioPowerDownBoard(void);
void halStackProcessBootCount(void);
EmberStatus emDebugInit(void);
void emRadioSeedRandom(void);

/** @} (end addtogroup legacyhal) */

#endif // HAL_H
