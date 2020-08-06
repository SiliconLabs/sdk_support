/***************************************************************************//**
 * @file
 * @brief USB protocol stack library, low level USB peripheral access.
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
#ifndef __EM_USBHAL_H
#define __EM_USBHAL_H

#include "em_usbtypes.h"

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef VBUSMON
void vbusMonCfg(void);

#endif //VBUSMON
void halSuspendCallback(void);
void halResumeCallback(void);

#define INT_USBTXACTIVE (EVENT_USB_CFG_TXACTIVEEP0   \
                         | EVENT_USB_CFG_TXACTIVEEP1 \
                         | EVENT_USB_CFG_TXACTIVEEP2 \
                         | EVENT_USB_CFG_TXACTIVEEP3 \
                         | EVENT_USB_CFG_TXACTIVEEP4 \
                         | EVENT_USB_CFG_TXACTIVEEP5 \
                         | EVENT_USB_CFG_TXACTIVEEP6)

#define INT_USBRXVALID (EVENT_USB_CFG_RXVALIDEP0   \
                        | EVENT_USB_CFG_RXVALIDEP1 \
                        | EVENT_USB_CFG_RXVALIDEP2 \
                        | EVENT_USB_CFG_RXVALIDEP3 \
                        | EVENT_USB_CFG_RXVALIDEP4 \
                        | EVENT_USB_CFG_RXVALIDEP5 \
                        | EVENT_USB_CFG_RXVALIDEP6)

//Define the size of all the endpoints.
#define EP0_SIZE (8)   //CTRL endpoint
#define EP1_SIZE (8)   //BULK\INTERRUPT
#define EP2_SIZE (8)   //BULK\INTERRUPT
#define EP3_SIZE (64)  //BULK\INTERRUPT
#define EP4_SIZE (32)  //BULK\INTERRUPT
#define EP5_SIZE (64)  //BULK\INTERRUPT
#define EP6_SIZE (512) //ISOCHRONOUS endpoint
//The USB core in the chip does not distinguish between INTERRUPT and BULK.
//The BULK/INTERRUPT endpoints can be morphed between each other's type by
//simply updating the endpoint descriptor.

//All physical endpoints are packed together and accessed through
//a contiguous block of RAM.  Therefore, define the overall size of the
//buffer by adding all the endpoints together.  The multiply by 2 is
//because each endpoint is bidirection with IN and OUT.
#define USB_BUFFER_SIZE ((EP0_SIZE * 2)   \
                         + (EP1_SIZE * 2) \
                         + (EP2_SIZE * 2) \
                         + (EP3_SIZE * 2) \
                         + (EP4_SIZE * 2) \
                         + (EP5_SIZE * 2) \
                         + (EP6_SIZE * 2))

//Define all of the endpoints as byte arrays.
typedef struct {
  uint8_t ep0IN[EP0_SIZE];
  uint8_t ep0OUT[EP0_SIZE];

  uint8_t ep1IN[EP1_SIZE];
  uint8_t ep1OUT[EP1_SIZE];

  uint8_t ep2IN[EP2_SIZE];
  uint8_t ep2OUT[EP2_SIZE];

  uint8_t ep3IN[EP3_SIZE];
  uint8_t ep3OUT[EP3_SIZE];

  uint8_t ep4IN[EP4_SIZE];
  uint8_t ep4OUT[EP4_SIZE];

  uint8_t ep5IN[EP5_SIZE];
  uint8_t ep5OUT[EP5_SIZE];

  uint8_t ep6IN[EP6_SIZE];
  uint8_t ep6OUT[EP6_SIZE];
} EndPointStruct;

//Overlay the endpoint structure on top of a flat byte array of the entire
//memory block that USB will be accessing.  This way an enpoint can be
//accessed specifically by name or the entire block can be accessed.
typedef union {
  uint8_t allEps[USB_BUFFER_SIZE];
  EndPointStruct eps;
} EndPointUnion;

extern EndPointUnion usbBufferA;
extern EndPointUnion usbBufferB;

extern uint8_t *EPOUTBUF[7];
extern uint8_t *EPINBUF[7];

extern bool usbVbusPresent;

static inline void USBHAL_DisableGlobalInt(void)
{
  NVIC_DisableIRQ(USB_IRQn);

  /* Disable all interrupts. */
  EVENT_USB->CFG = 0;

  /* Clear pending interrupts */
  EVENT_USB->FLAG = 0xFFFFFFFFU;
}

static inline void USBHAL_EnableGlobalInt(void)
{
  NVIC_EnableIRQ(USB_IRQn);
}

static inline void USBDHAL_EnableUsbResetInt(void)
{
  /* Disable all interrupts. */
  EVENT_USB->CFG = 0;

  /* Clear pending interrupts */
  EVENT_USB->FLAG = 0xFFFFFFFFU;

  #ifndef BOOTLOADER
  EVENT_USB->CFG = (EVENT_USB_CFG_RESET
                    | EVENT_USB_CFG_RXVALIDEP0
                    | EVENT_USB_CFG_TXACTIVEEP0
                    | EVENT_USB_CFG_RESUME
                    | EVENT_USB_CFG_WAKEUP
                    | EVENT_USB_CFG_SUSPEND);
  #else
  EVENT_USB->CFG = (EVENT_USB_CFG_RESET
                    | EVENT_USB_CFG_RXVALIDEP0
                    | EVENT_USB_CFG_TXACTIVEEP0);

  #endif
}

static inline void USBDHAL_StartEp0Setup(USBD_Device_TypeDef *pDev)
{
  pDev->ep[0].in = false;
  pDev->setup = pDev->setupPkt;
}

static inline void USBDHAL_ReenableEp0Setup(USBD_Device_TypeDef *pDev)
{
  pDev->setup = pDev->setupPkt;
}

static inline void USBDHAL_DeactivateEp(USBD_Ep_TypeDef *ep)
{
  #ifdef USB_DEBUG_EP
  DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "Deactivating EP%d", ep->num);
  #endif
  if (ep->in) {
    #ifdef USB_DEBUG_EP
      #ifdef USB_DEBUG_VERBOSE
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "in-->\r\n");
      #else
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "in\r\n");
      #endif
    #endif
    USB->ENABLEIN  &= ~(USB_ENABLEIN_ENABLEINEP0 << ep->num);
    USB->CTRL      &= ~(USB_CTRL_ENBUFINEP0B << ep->num);
    EVENT_USB->CFG &= ~(EVENT_USB_CFG_TXACTIVEEP0 << ep->num);
  } else {
    #ifdef USB_DEBUG_EP
      #ifdef USB_DEBUG_VERBOSE
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "out-->\r\n");
      #else
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "out\r\n");
      #endif
    #endif
    USB->ENABLEOUT &= ~(USB_ENABLEOUT_ENABLEOUTEP0  << ep->num);
    USB->CTRL      &= ~(USB_CTRL_ENBUFOUTEP0B << ep->num);
    EVENT_USB->CFG &= ~(EVENT_USB_CFG_RXVALIDEP0 << ep->num);
  }

  #ifdef USB_DEBUG_EP
    #ifdef USB_DEBUG_VERBOSE
  DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "USB->ENABLEIN\tUSB->ENABLEOUT\tUSB->CTRL\tEVENT_USB->CFG\r\n");
  DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "%X           \t%X            \t%X       \t%X\r\n", USB->ENABLEIN, USB->ENABLEOUT, USB->CTRL, EVENT_USB->CFG);
    #endif
  #endif
}

static inline USB_Status_TypeDef USBDHAL_StallEp(USBD_Ep_TypeDef *ep)
{
  USB_Status_TypeDef retVal = USB_STATUS_REQ_ERR;

  if ( ep->in == true ) {
    USB->STALLIN |= USB_STALLIN_STALLINEP0 << ep->num;
    retVal = USB_STATUS_OK;
  } else {
    USB->STALLOUT |= USB_STALLOUT_STALLOUTEP0 << ep->num;
    retVal = USB_STATUS_OK;
  }

  return retVal;
}

static inline USB_Status_TypeDef USBDHAL_UnStallEp(USBD_Ep_TypeDef *ep)
{
  USB_Status_TypeDef retVal = USB_STATUS_REQ_ERR;

  if ( ep->in == true ) {
    USB->STALLIN &= ~(USB_STALLIN_STALLINEP0 << ep->num);
    retVal = USB_STATUS_OK;
  } else {
    USB->STALLOUT &= ~(USB_STALLOUT_STALLOUTEP0 << ep->num);
    retVal = USB_STATUS_OK;
  }

  return retVal;
}

static inline USB_Status_TypeDef USBDHAL_GetStallStatusEp(
  USBD_Ep_TypeDef *ep, uint16_t *halt)
{
  USB_Status_TypeDef retVal = USB_STATUS_REQ_ERR;

  if ( ep->in == true ) {
    *halt = USB->STALLIN & (USB_STALLIN_STALLINEP0 << ep->num) ? 1 : 0;
    retVal = USB_STATUS_OK;
  } else {
    *halt = USB->STALLOUT & (USB_STALLOUT_STALLOUTEP0 << ep->num) ? 1 : 0;
    retVal = USB_STATUS_OK;
  }

  return retVal;
}

static inline bool USBDHAL_EpIsStalled(USBD_Ep_TypeDef *ep)
{
  bool retVal = false;
  uint16_t stallStatus;

  if ( USBDHAL_GetStallStatusEp(ep, &stallStatus) == USB_STATUS_OK ) {
    retVal = stallStatus & 1 ? true : false;
  }
  return retVal;
}

static inline void USBDHAL_StartEpIn(USBD_Ep_TypeDef *ep)
{
  uint8_t txSize = (ep->remaining > ep->packetSize) ? ep->packetSize : ep->remaining;

  if (txSize > 0) {
    if (ep->buf != NULL) {
      MEMMOVE(EPINBUF[ep->num], ep->buf, txSize);
    }
  }
  ep->buf += txSize;

  #if (defined (USB_DEBUG_WRITE) && defined(USB_DEBUG_VERBOSE))
  uint8_t i;
  for (i = 0; i < txSize; i++) {
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "%02X ", EPINBUF[ep->num][i]);
  }
  DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "\r\n");
  #endif

  USB->TXBUFSIZEEPA[ep->num] = txSize;

  USB->TXLOAD = USB_TXLOAD_TXLOADEP0A << ep->num;
}

static void USBDHAL_StartEpOut(USBD_Ep_TypeDef *ep)
{
  #if defined(USB_DEBUG_EP) && defined(USB_DEBUG_VERBOSE)
  uint8_t i;
  for (i = 0; i < 8; i++) {
    DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "%c", EPOUTBUF[ep->num][i]);
  }
  DEBUG_BUFFER += sprintf(DEBUG_BUFFER, "\r\n");
  #endif

  USB->RXVALID |= ( (USB_RXVALID_RXVALIDEP0A << ep->num)
                    | (USB_RXVALID_RXVALIDEP0B << ep->num) );
}

static inline void USBDHAL_SetRemoteWakeup(void)
{
  USB->RESUME = 1;
}

// not supported
void USBDHAL_AbortAllEps(void);

void USBDHAL_Connect(void);
void USBDHAL_Disconnect(void);
USB_Status_TypeDef USBDHAL_CoreInit(uint32_t totalRxFifoSize,
                                    uint32_t totalTxFifoSize);
void USBDHAL_AbortAllTransfers(USB_Status_TypeDef reason);

#ifdef __cplusplus
}
#endif

/** @endcond */
#endif /* __EM_USBHAL_H */
