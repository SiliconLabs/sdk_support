/***************************************************************************//**
 * @file
 * @brief USB descriptor prototypes for CDC serial example project.
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

#ifndef DESCRIPTORS_H
#define DESCRIPTORS_H

#include "hal/micro/cortexm3/usb/em_usb.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  uint8_t len;
  uint8_t type;
  uint16_t name[17];
} __attribute__ ((packed)) tUSBCDC_iSerialNumber;

extern const USBD_Init_TypeDef USBCDC_initStruct;
extern tUSBCDC_iSerialNumber USBCDC_iSerialNumber;
int  USBCDC_SetupCmd(const USB_Setup_TypeDef *setup);
void USBCDC_stateChange(USBD_State_TypeDef oldState, USBD_State_TypeDef newState);

#ifdef __cplusplus
}
#endif

#endif /* DESCRIPTORS_H */
