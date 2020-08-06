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

#ifndef COEX_LL_H
#define COEX_LL_H

#include <stdbool.h>
#include <rail_types.h>

/**
 * Set request window
 * @param request window in us
 */
void ll_coexSetRequestWindow(uint16_t requestWindow);

/**
 * Inform COEX code that grant signal state is changed.
 */
void ll_coexUpdateGrant(bool allowAbort);

/**
 * Set COEX request and priority signals immediately.
 * @param request state of request signal
 * @param pwmEnable Enable pwm toggling of request line
 * @param priority priority level of request
 */
void ll_coexRequest(bool request, bool pwmEnable, uint8_t priority);

/**
 * Set COEX request and priority signals at given time. Signals are set
 * immediately if time is already past.
 * @param time setting time in RAIL time
 * @param request state of request signal
 * @param priority priority level of request
 */
void ll_coexRequestDelayed(uint32_t time, bool request, bool pwmEnable, uint8_t priority);

typedef void(* CBcoexAbortTx)(void);
typedef uint16_t(* CBcoexFastRandom)(void);
/**
 * Set RAIL handle and callbacks for coex to use
 *
 */
void ll_coexSetContext(RAIL_Handle_t railHandle, CBcoexAbortTx abortTx, CBcoexFastRandom fastRandom);

/**
 * Get random number quickly
 *
 */
uint16_t ll_coexFastRandom(void);

bool coex_txAllowed(void);

#endif
