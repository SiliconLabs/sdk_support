/***************************************************************************//**
 * @file
 * @brief Test helper to acquire and release SE manager lock
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
/*
 * This file includes an alternative implementation of ECDH using the secure
 * element incorporated in MCU devices from Silicon Laboratories.
 */

#include "em_device.h"

#if defined(SEMAILBOX_PRESENT)
#include "sl_se_manager.h"
#include "sli_se_manager_internal.h"

int se_management_acquire()
{
  // Get SE manager context
  sl_status_t ret;

  // Initialize the SE manager.
  ret = sl_se_init();
  if (ret != SL_STATUS_OK) {
    return -1;
  }

  // Acquire SE manager lock
  ret = sli_se_lock_acquire();
  if (ret != 0) {
    return -1;
  }

  return 0;
}

int se_management_release()
{
  // Release SE manager lock
  return sli_se_lock_release();
}

#endif /* #if defined(SEMAILBOX_PRESENT) */
