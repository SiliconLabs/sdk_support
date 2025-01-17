/*******************************************************************************
 * @file
 * @brief OpenThread initialization.
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_ot_init.h"
// TODO: Remove the Power Manager include when OT does not add an EM1 req at init
#define CURRENT_MODULE_NAME "OPENTHREAD"
#include "sl_power_manager.h"

void sl_ot_init(void)
{
  sl_ot_create_instance();
  sl_ot_sleep_init();
  
  // TODO: Remove the Power Manager remove req when OT does not add an EM1 req at init
  sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
  sl_ot_cli_init();
  sl_ot_custom_cli_init();
}