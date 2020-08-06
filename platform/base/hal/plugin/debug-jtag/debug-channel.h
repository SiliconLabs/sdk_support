/***************************************************************************//**
 * @file
 * @brief Functions that provide access to the debug channel.
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
#ifndef __DEBUG_CHANNEL_H__
#define __DEBUG_CHANNEL_H__

#include "stack/include/ember-types.h" // for EmberStatus and EmberMessageBuffer
#include "stack/include/ember-debug.h" // for emberDebugReportRestore
#include "stack/framework/debug.h"     // for emDebugClearStats

/** @name Debug Channel Functions */

//@{

// The ISA checks that the block size for RAM input and output is always <= 32
// due to the linked buffers of yore.
#define MAX_BLOCK_SIZE 32

EmberStatus halStackDebugPutBuffer(EmberMessageBuffer buffer);
uint8_t emDebugAddInitialFraming(uint8_t *buff, uint16_t debugType);
EmberStatus emDebugSend(uint8_t *data, uint8_t *length);
EmberStatus emDebugInit(void);

#if DEBUG_LEVEL >= BASIC_DEBUG

void emDebugPowerDown(void);
void emDebugPowerUp(void);
bool halStackDebugActive(void);

void emDebugReceiveData(void);

#else // DEBUG_LEVEL >= BASIC_DEBUG

#if defined(EMBER_STACK_IP) || defined(EMBER_STACK_CONNECT)
#define emDebugInit() do {} while (0)
#endif // defined(EMBER_STACK_IP) || defined(EMBER_STACK_CONNECT)

#define emDebugPowerDown()
#define emDebugPowerUp()

#if !defined(EMBER_STACK_IP) && !defined(EMBER_STACK_CONNECT)
#define emDebugReceiveData()
#endif // !defined(EMBER_STACK_IP) && !defined(EMBER_STACK_CONNECT)

#endif // DEBUG_LEVEL >= BASIC_DEBUG

//@}  // end of Debug Channel Functions

#endif //__DEBUG_CHANNEL_H__
