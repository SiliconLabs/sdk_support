/***************************************************************************//**
 * @file
 * @brief
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

#ifndef SL_RAIL_UTIL_IEEE802154_PHY_SELECT_H
#define SL_RAIL_UTIL_IEEE802154_PHY_SELECT_H

#include "sl_rail_util_ieee802154_stack_event.h"

#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_DEFAULT         0
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_ANTDIV          1
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_COEX            2
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_ANTDIV_COEX     3
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_FEM             4
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_ANTDIV_FEM      5
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_COEX_FEM        6
#define SL_RAIL_UTIL_RADIO_CONFIG_154_2P4_ANTDIV_COEX_FEM 7
typedef uint8_t sl_rail_util_radio_config_t;

sl_rail_util_ieee802154_stack_status_t sl_rail_util_ieee802154_phy_select_on_event(
  sl_rail_util_ieee802154_stack_event_t stack_event,
  uint32_t supplement);
sl_rail_util_radio_config_t sl_rail_util_get_active_radio_config(void);
RAIL_Status_t sl_rail_util_plugin_config_2p4ghz_radio(RAIL_Handle_t railHandle);

sl_rail_util_radio_config_t sl_rail_util_get_active_radio_config(void);
#endif // SL_RAIL_UTIL_IEEE802154_PHY_SELECT_H
