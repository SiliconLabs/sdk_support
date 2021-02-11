/***************************************************************************//**
 * @file
 * @brief Common coexistence configuration header file
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_RAIL_UTIL_COEX_COMMON_CONFIG_H
#define SL_RAIL_UTIL_COEX_COMMON_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> Coexistence Configuration

// <q SL_RAIL_UTIL_COEX_TX_ABORT> Abort transmission mid-packet if Grant  when GRANT deasserted, RHO asserted, or REQUEST not secured (shared REQUEST only)
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_TX_ABORT 1

// <h> IEEE802.15.4 Only Configuration
// <q SL_RAIL_UTIL_COEX_ACKHOLDOFF> Disable ACKing when GRANT deasserted, RHO asserted, or REQUEST deasserted
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_ACKHOLDOFF 1

// <q SL_RAIL_UTIL_COEX_PHY_ENABLED> Optimize for Wi-Fi Blocker
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PHY_ENABLED 1
// </h>

// <e>  REQUEST
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_REQ_ENABLED 0

// <q SL_RAIL_UTIL_COEX_REQ_ASSERT_LEVEL> REQUEST assert signal level
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_REQ_ASSERT_LEVEL 1

// <q SL_RAIL_UTIL_COEX_REQ_SHARED> Enable REQUEST shared mode
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_REQ_SHARED 1

// <o SL_RAIL_UTIL_COEX_REQ_BACKOFF> Max REQUEST backoff mask [0-255]
// <0-255:1>
// <i> Default: 15
#define SL_RAIL_UTIL_COEX_REQ_BACKOFF 15

// <h> BLE Only Request Configuration
// <o SL_RAIL_UTIL_COEX_REQ_WINDOW> Specify the number of microseconds between asserting Request and starting RX/TX
// <0-255:1>
// <i> Default: 500
#define SL_RAIL_UTIL_COEX_REQ_WINDOW 500
// </h>

// <h> IEEE802.15.4 Only Request Configuration
// <e> Enable REQUEST receive retry
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_RETRYRX_ENABLE 0

// <o SL_RAIL_UTIL_COEX_RETRYRX_TIMEOUT> REQUEST receive retry timeout(ms)
// <0-255:1>
// <i> Default: 16
#define SL_RAIL_UTIL_COEX_RETRYRX_TIMEOUT 16

// <q SL_RAIL_UTIL_COEX_RETRYRX_HIPRI> REQUEST receive retry assert PRIORITY
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_RETRYRX_HIPRI 0
// </e>
// </h>
// </e>

// <e> GRANT
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_GNT_ENABLED 0

// <q SL_RAIL_UTIL_COEX_GNT_ASSERT_LEVEL> GRANT assert signal level
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_GNT_ASSERT_LEVEL 1
// </e>

// <e> PRIORITY
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_PRI_ENABLED 0

// <q SL_RAIL_UTIL_COEX_PRI_ASSERT_LEVEL> PRIORITY assert signal level
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PRI_ASSERT_LEVEL 1

// <q SL_RAIL_UTIL_COEX_PRI_SHARED> Enable PRIORITY shared mode
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PRI_SHARED 1

// <h> BLE Only Priority Configuration
// <q SL_RAIL_UTIL_COEX_PRIORITY_DEFAULT> Default Enabled/Disabled
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PRIORITY_DEFAULT 1
// </h>

// <h> IEEE802.15.4 Only Priority Configuration
// <q SL_RAIL_UTIL_COEX_TX_HIPRI> Assert PRIORITY when transmitting packet
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_TX_HIPRI 1

// <q SL_RAIL_UTIL_COEX_RX_HIPRI> Assert PRIORITY when receiving packet
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_RX_HIPRI 1

// <q SL_RAIL_UTIL_COEX_PRIORITY_ESCALATION_ENABLE> Include TX PRIORITY escalation
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PRIORITY_ESCALATION_ENABLE 1

// <o SL_RAIL_UTIL_COEX_CCA_THRESHOLD> CCA/GRANT TX PRIORITY Escalation Threshold
// <0-255:1>
// <i> Default: 4
#define SL_RAIL_UTIL_COEX_CCA_THRESHOLD 4

// <q SL_RAIL_UTIL_COEX_MAC_FAIL_THRESHOLD> MAC Fail TX PRIORITY Escalation threshold
// <0-3:1>
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_MAC_FAIL_THRESHOLD 0
// </h>
// </e>

// <e> PWM REQUEST
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_PWM_REQ_ENABLED 0

// <q SL_RAIL_UTIL_COEX_PWM_REQ_ASSERT_LEVEL> PWM REQUEST signal level (shared REQUEST only)
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PWM_REQ_ASSERT_LEVEL 1

// <q SL_RAIL_UTIL_COEX_PWM_DEFAULT_ENABLED> Enable PWM REQUEST at startup
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PWM_DEFAULT_ENABLED 1
// <o SL_RAIL_UTIL_COEX_PWM_REQ_PERIOD> PWM Request Period (0.5ms steps)
// <5-109>
// <i> Default: 78
#define SL_RAIL_UTIL_COEX_PWM_REQ_PERIOD 78

// <o SL_RAIL_UTIL_COEX_PWM_REQ_DUTYCYCLE> PWM Request Duty-Cycle (%)
// <1-95:1>
// <i> Default: 20
#define SL_RAIL_UTIL_COEX_PWM_REQ_DUTYCYCLE 20

// <q SL_RAIL_UTIL_COEX_PWM_PRIORITY> Assert priority when PWM REQUEST asserted
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_PWM_PRIORITY 1

// <h> BLE Only PWM Configuration
// <q SL_RAIL_UTIL_COEX_SCANPWM_DEFAULT_ENABLED> Enable PWM only when local device is scanning
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_SCANPWM_DEFAULT_ENABLED 0
// </h>
// </e>

// <e> Radio Hold-off
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_RHO_ENABLED 0
// <q SL_RAIL_UTIL_COEX_RHO_ASSERT_LEVEL> RHO assert signal level
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_RHO_ASSERT_LEVEL 1
// </e>

// <e> Directional PRIORITY
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_DP_ENABLED 0
// <o SL_RAIL_UTIL_COEX_DP_PULSE_WIDTH_US> Directional PRIORITY pulse width
// <0-255:1>
// <i> Default: 20
#define SL_RAIL_UTIL_COEX_DP_PULSE_WIDTH_US 20
// </e>

// <e> RX active
// <i> Default: 0
#define SL_RAIL_UTIL_COEX_RX_ACTIVE_ENABLED 0

// <q SL_RAIL_UTIL_COEX_RX_ACTIVE_ASSERT_LEVEL> RX active assert signal level
// <i> Default: 1
#define SL_RAIL_UTIL_COEX_RX_ACTIVE_ASSERT_LEVEL 1
// </e>

// </h>
// <<< end of configuration section >>>

#endif // SL_RAIL_UTIL_COEX_COMMON_CONFIG_H
