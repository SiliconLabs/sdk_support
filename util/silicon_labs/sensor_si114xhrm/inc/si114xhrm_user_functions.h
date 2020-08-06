/***************************************************************************//**
 * @file
 * @brief si114x functions to be provided by developer specific to
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
 #ifndef SI114XHRM_USER_FUNC_H
#define SI114xHRM_USER_FUNC_H

#include <stdint.h>
#include "si114x_types.h"

int si114xFindEvb(char *port_description, char *last_port, int num_ports_found);
int si114xSetupDebug(HANDLE si114x_handle, void *si114x_debug);
int si114xOutputDebugMessage(HANDLE si114x_handle, char *message);
s16 Si114xWriteToRegister(HANDLE si114x_handle, u8 address, u8 data);
s16 Si114xReadFromRegister(HANDLE si114x_handle, u8 address);
int16_t Si114xBlockWrite(HANDLE si114x_handle,
                         uint8_t address, uint8_t length, uint8_t *values);
s16 Si114xBlockRead(HANDLE si114x_handle,
                    u8 address, u8 length, u8 *values);
s16 Si114xProcessIrq(HANDLE si114x_handle, u16 timestamp);
s16 Si114xIrqQueueNumentries(HANDLE si114x_handle);
s16 Si114xIrqQueue_Get(HANDLE si114x_handle, SI114X_IRQ_SAMPLE *samples);
s16 Si114xIrqQueue_Clear(HANDLE si114x_handle);
s16 Si114xInit(void *port, int options, HANDLE *si114x_handle);
s16 Si114xClose(HANDLE si114x_handle);

#endif
