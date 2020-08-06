/***************************************************************************//**
 * @file
 * @brief Non-Volatile Memory Wear-Leveling driver HAL
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

#ifndef __NVMHAL_H
#define __NVMHAL_H

#include "em_device.h"
#include <stdbool.h>
#include "nvm.h"
#include "ecode.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

void NVMHAL_Init(void);
void NVMHAL_DeInit(void);
void NVMHAL_Read(uint8_t *pAddress, void *pObject, uint16_t len);
Ecode_t NVMHAL_Write(uint8_t *pAddress, void const *pObject, uint16_t len);
Ecode_t NVMHAL_PageErase(uint8_t *pAddress);
void NVMHAL_Checksum(uint16_t *checksum, void *pMemory, uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* __NVMHAL_H */
