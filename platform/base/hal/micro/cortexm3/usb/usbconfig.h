/***************************************************************************//**
 * @file
 * @brief USB protocol stack library, application supplied configuration options.
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

#ifndef __USBCONFIG_H
#define __USBCONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Compile stack for device mode. */
// #define USB_DEVICE

/* Specify number of endpoints used (in addition to EP0) */
#ifndef NUM_EP_USED
  #if EM_SERIAL3_ENABLED
    #define NUM_EP_USED 3
  #else
    #define NUM_EP_USED 2
  #endif
#endif

/* Select TIMER0 to be used by the USB stack. This timer
 * must not be used by the application. */
// #define USB_TIMER USB_TIMER0

/**********************************************************
* Define the endpoint addresses. Bits [3:0] define
* endpoint number. Bit 7 defines direction (1 = IN).
**********************************************************/

/* Endpoint for USB data IN  (device to host).    */
#define EP_IN             0x81

/* Endpoint for USB data OUT (host to device).    */
#define EP_OUT            0x01

/**********************************************************
* Debug Configuration. Enable the stack to output
* debug messages to a console. This example is
* configured to output messages over UART.
**********************************************************/

/* Enable debug output from the stack */
// #define DEBUG_USB_API

/* Enable printf calls in stack */
// #define USB_USE_PRINTF

/* Function declaration for the low-level printing of a
 * character. This function must be implemented by the
 * application. */
// int RETARGET_WriteChar(char c);
// #define USER_PUTCHAR  RETARGET_WriteChar

/**********************************************************
* Power saving configuration. Select low frequency
* clock and power saving mode.
**********************************************************/

/* Select the clock used when USB is in low power mode */
// #define USB_USBC_32kHz_CLK   USB_USBC_32kHz_CLK_LFXO

/* Select the power saving mode. Enter power save on Suspend and
 * when losing power on VBUS. Let the application handle when to
 * enter EM2 */
// #define USB_PWRSAVE_MODE (USB_PWRSAVE_MODE_ONSUSPEND | USB_PWRSAVE_MODE_ONVBUSOFF)

#ifdef __cplusplus
}
#endif

#endif /* __USBCONFIG_H */
