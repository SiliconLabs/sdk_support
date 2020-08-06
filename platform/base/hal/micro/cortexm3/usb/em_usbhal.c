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
#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "hal/hal.h"

#if defined(CORTEXM3_EM35X_USB)
#include "em_usb.h"
#include "em_usbtypes.h"
#include "em_usbhal.h"

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

bool usbVbusPresent;
extern USBD_Device_TypeDef *dev;

ALIGNMENT(8)
EndPointUnion usbBufferA = { 0, };
uint8_t *EPOUTBUF[7] = { usbBufferA.eps.ep0OUT,
                         usbBufferA.eps.ep1OUT,
                         usbBufferA.eps.ep2OUT,
                         usbBufferA.eps.ep3OUT,
                         usbBufferA.eps.ep4OUT,
                         usbBufferA.eps.ep5OUT,
                         usbBufferA.eps.ep6OUT };
uint8_t *EPINBUF[7]  = { usbBufferA.eps.ep0IN,
                         usbBufferA.eps.ep1IN,
                         usbBufferA.eps.ep2IN,
                         usbBufferA.eps.ep3IN,
                         usbBufferA.eps.ep4IN,
                         usbBufferA.eps.ep5IN,
                         usbBufferA.eps.ep6IN };
void USBDHAL_Connect(void)
{
  #if USB_SELFPWRD_STATE == 1 && defined(VBUSMON)

  //For self-powered devices, The USB specification requires that the pull-up
  //resistor is disconnected if VBUS is not connected.
  vbusMonCfg();
  if (usbVbusPresent) {
    //Set ENUMCTRL ouput-high to enumerate.
    ENUMCTRL_SETCFG(_GPIO_P_CFGL_Px0_OUT);
    ENUMCTRL_SET();
  }
  #else // USB_SELFPWRD_STATE==1 && defined(VBUSMON)
  //Set ENUMCTRL ouput-high to enumerate.
  ENUMCTRL_SETCFG(_GPIO_P_CFGL_Px0_OUT);
  ENUMCTRL_SET();
  #endif // USB_SELFPWRD_STATE==1 && defined(VBUSMON)
}

void USBDHAL_Disconnect(void)
{
  ENUMCTRL_SETCFG(_GPIO_P_CFGL_Px0_IN);
  ENUMCTRL_CLR();
}

USB_Status_TypeDef USBDHAL_CoreInit(uint32_t totalRxFifoSize,
                                    uint32_t totalTxFifoSize)
{
  //Configure PA0 and PA1 in analog mode for USB
  GPIO->P[0].CFGL = ((GPIO->P[0].CFGL & (~_GPIO_P_CFGL_Px0_MASK))
                     & GPIO_P_CFGL_Px0_ANALOG);
  GPIO->P[0].CFGL = ((GPIO->P[0].CFGL & (~_GPIO_P_CFGL_Px1_MASK))
                     & GPIO_P_CFGL_Px1_ANALOG);

  USB->BUFBASEA = (uint32_t)usbBufferA.allEps;
  MEMSET(usbBufferA.allEps, 0, USB_BUFFER_SIZE);

  // Double buffering currently not supported
  // #ifdef USB_DOUBLE_BUFFER
  //   USB->BUFBASEB = (uint32_t)usbBufferB.allEps;
  //   MEMSET(usbBufferB.allEps, 0, USB_BUFFER_SIZE);
  //   //Refer to "handle buffer B" in the driveEp3Tx() function above
  //   //to learn why double buffering is not enabled by default.
  //
  //   //Enable double buffering bulk EP3.
  //   USB->CTRL |= (USB_CTRL_ENBUFOUTEP3B | USB_CTRL_ENBUFINEP3B);
  // #endif // USB_DOUBLE_BUFFER

  //Use the SELFPWDRD and REMOTEWKUPEN state defines to set the appropriate
  //bits in USB->CTRL
  USB->CTRL = (USB->CTRL & (~(USB_CTRL_SELFPWRD | USB_CTRL_REMOTEWKUPEN)))
              | ((USB_SELFPWRD_STATE << _USB_CTRL_SELFPWRD_SHIFT)
                 | (USB_REMOTEWKUPEN_STATE << _USB_CTRL_REMOTEWKUPEN_SHIFT));

#ifdef  EMBER_EMU_TEST
  //Select which GPIO output is used for connect/disconnect. Any
  //value > 47, selects disconnected state.
  EMU_USB_DISCONNECT = PORTA_PIN(2);
#endif //EMBER_EMU_TEST

  return USB_STATUS_OK;
}

void USBDHAL_AbortAllTransfers(USB_Status_TypeDef reason)
{
  int i;
  USBD_Ep_TypeDef *ep;
  USB_XferCompleteCb_TypeDef callback;

  if ( reason != USB_STATUS_DEVICE_RESET ) {
    // unsupported
    // USBDHAL_AbortAllEps();
  }

  for ( i = 1; i <= NUM_EP_USED; i++ ) {
    ep = &(dev->ep[i]);
    if ( ep->state != D_EP_IDLE ) {
      ep->state = D_EP_IDLE;
      if ( ep->xferCompleteCb != 0U ) {
        callback = ep->xferCompleteCb;
        ep->xferCompleteCb = NULL;

        if ((dev->lastState == USBD_STATE_CONFIGURED)
            && (dev->state     == USBD_STATE_ADDRESSED)) {
          USBDHAL_DeactivateEp(ep);
        }
        callback(reason, ep->xferred, ep->remaining);
      }
    }
  }
}

#ifdef VBUSMON
//Use a selectable IRQ for monitoring VBUS on VBUSMON.
void vbusMonCfg(void)
{
  //VBUSMON just needs to be a simple input.
  VBUSMON_SETCFG();

  //start from a fresh state, just in case
  VBUSMON_INTCFG = _EVENT_GPIO_CFGD_RESETVALUE;              //disable triggering
  NVIC->ICER[0] = VBUSMON_INT_EN_BIT; //clear top level int enable
  EVENT_GPIO->FLAG = VBUSMON_FLAG_BIT; //clear stale interrupt
  EVENT_MISS->MISS = VBUSMON_MISS_BIT;     //clear stale missed interrupt
  //configure
  VBUSMON_SEL();             //point IRQ at the desired pin
  VBUSMON_INTCFG  = ((0 << _EVENT_GPIO_CFGD_FILT_SHIFT)   //no filter
                     | (3 << _EVENT_GPIO_CFGD_MOD_SHIFT)); //3 = both edges

  usbVbusPresent = ((VBUSMON_IN & VBUSMON) == VBUSMON);

  NVIC->ISER[0] = VBUSMON_INT_EN_BIT; //set top level interrupt enable
}

#endif //VBUSMON

#ifndef EMBER_APPLICATION_HAS_CUSTOM_SUSPEND_CALLBACK
uint32_t savedPeripheralReg;
void halSuspendCallback(void)
{
  halSuspend();
  savedPeripheralReg = CMLV->PERIPHERALDISABLE;
  CMLV->PERIPHERALDISABLE |= (CMLV_PERIPHERALDISABLE_ADC    \
                              | CMLV_PERIPHERALDISABLE_TIM2 \
                              | CMLV_PERIPHERALDISABLE_TIM1 \
                              | CMLV_PERIPHERALDISABLE_SC1  \
                              | CMLV_PERIPHERALDISABLE_SC2);
}

void halResumeCallback(void)
{
  CMLV->PERIPHERALDISABLE = savedPeripheralReg;
  halResume();
}

#endif // EMBER_APPLICATION_HAS_CUSTOM_SUSPEND_CALLBACK

/** @endcond */
#endif //CORTEXM3_EM35X_USB
