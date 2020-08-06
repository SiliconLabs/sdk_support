/***************************************************************************//**
 * @file
 * @brief Generic set of HAL includes for all platforms.
 *
 * See also @ref hal for more documentation.
 *
 * Some HAL includes are not used or present in builds intended for the Host
 * processor connected to the Ember Network Coprocessor.
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
/** @addtogroup hal
 *  @if EM35x
 *    EM35x Microprocessors
 *  @endif
 *  @if STM32F103RET
 *    STM32F103RET Host Microcontroller
 *  @endif
 *  @if PC_Host
 *    PC Host
 *  @endif
 *
 * HAL function names have the following prefix conventions:
 *
 *  <b>halCommon:</b>   API that is used by the EmberZNet stack and can also be called
 *                 from an application. This API must be implemented. Custom
 *                 applications can change the implementation of the API but
 *                 its functionality must remain the same.
 *
 *  <b>hal:</b>    API that is used by sample applications. Custom
 *                 applications can remove this API or change its
 *                 implementation as they see fit.
 *
 *
 *  <b>halStack:</b>   API used only by the EmberZNet stack. This API must be implemented
 *                 and should not be directly called from any application.
 *                 Custom applications can change the implementation of the
 *                 API, but its functionality must remain the same.
 *
 *  <b>halInternal:</b>   API that is internal to the HAL. The EmberZNet stack
 *                and applications must never call this API directly.
 *                Custom applications can change this API as they see
 *                fit. However, be careful not to impact the functionalty of
 *                any halStack or halCommon APIs.
 * <br><br>
 *
 * See also hal.h.
 */

#ifndef __HAL_H__
#define __HAL_H__

#ifdef HAL_HOST

#include "host/button-common.h"
#include "host/crc.h"
#include "host/led-common.h"
#include "host/micro-common.h"
#include "host/serial.h"
#include "host/system-timer.h"
#include "host/bootloader-eeprom.h"
//Pull in the micro specific ADC, buzzer, and clocks headers.  The
//specific header is chosen by the build include path pointing at
//the appropriate directory.
#include "plugin/adc/adc-stm32f103ret.h"

#ifdef STM32F10X_HD
#include "plugin/buzzer/buzzer-stm32f103ret.h"
#else
#include "plugin/buzzer/buzzer.h"
#endif

#else //HAL_MICRO

// Keep micro and board first for specifics used by other headers
#include "micro/micro.h"
#if !defined(STACK)
#ifdef BOARD_HEADER
  #include BOARD_HEADER
#endif
#ifdef HAL_CONFIG
  #include "hal-config.h"
  #include "ember-hal-config.h"
  #ifndef HAL_GPIO_MAX
  #define HAL_GPIO_MAX 0
  #endif
// if no serial port defined or vuart is used, define dummy value for HAL_SERIAL_APP_PORT
  #if !defined(HAL_SERIAL_APP_BAUD_RATE) || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_VUART)
  #define HAL_SERIAL_APP_BAUD_RATE 0
  #ifndef APP_SERIAL
  #define APP_SERIAL 0
  #endif
  #endif
  #ifdef RF_USARTRF_CS_PORT
  #define BSP_EXTDEV_CS_PORT  RF_USARTRF_CS_PORT
  #define BSP_EXTDEV_CS_PIN   RF_USARTRF_CS_PIN
  #define BSP_EXTDEV_INT_PORT RF_INT_PORT
  #define BSP_EXTDEV_INT_PIN  RF_INT_PIN
  #define BSP_EXTDEV_SDN_PORT RF_SDN_PORT
  #define BSP_EXTDEV_SDN_PIN  RF_SDN_PIN
  #endif
void halConfigPowerDownGpio(void);
void halConfigPowerUpGpio(void);
#elif defined(BOARD_HEADER) //HAL_CONFIG
#define BSP_SERIAL_APP_PORT APP_SERIAL
#ifdef COM_RETARGET_SERIAL
  #define BSP_BUTTON0_PIN   BUTTON0
  #define BSP_BUTTON0_PORT  BUTTON0_PORT
  #define BSP_BUTTON1_PIN   BUTTON1
  #define BSP_BUTTON1_PORT  BUTTON1_PORT
  #include "retargetserialconfig.h"
  #ifdef _USART_ROUTELOC0_MASK
    #define BSP_USART0_TX_LOC RETARGET_TX_LOCATION
    #define BSP_USART0_RX_LOC RETARGET_RX_LOCATION
  #else
    #define BSP_USART0_ROUTE_LOC RETARGET_LOCATION
  #endif

  #define BSP_USART0_TX_PORT RETARGET_TXPORT
  #define BSP_USART0_TX_PIN  RETARGET_TXPIN
  #define BSP_USART0_RX_PORT RETARGET_RXPORT
  #define BSP_USART0_RX_PIN  RETARGET_RXPIN

  #define halConfigInit()
  #define halConfigPowerDownGpio()
  #define halConfigPowerUpGpio()
#endif /*COM_RETARGET_SERIAL*/
#endif
#endif
#include "plugin/antenna/antenna.h"

#if defined(EMBER_STACK_CONNECT)
  #if defined(UNIX_HOST) && !defined(EMBER_TEST)
    #include "plugin/adc/adc.h"
    #include "micro/button.h"
    #include "plugin/buzzer/buzzer.h"
    #include "micro/crc.h"
    #include "micro/endian.h"
    #include "micro/led.h"
    #include "micro/random.h"
    #include "micro/serial.h"
    #include "micro/spi.h"
    #include "micro/system-timer.h"
  #else
// TODO: here we include only the functionalities that we will have on mustang
    #if defined(CORTEXM3)
      #include "plugin/adc/adc.h"
      #include "micro/bootloader-eeprom.h"
      #if defined (_EFR_DEVICE) || defined(CORTEXM3_EMBER_MICRO)
      #include "micro/bootloader-interface.h"
      #endif
      #include "micro/button.h"
      #include "micro/led.h"
      #include "plugin/buzzer/buzzer.h"
      #include "micro/crc.h"
      #include "micro/diagnostic.h"
      #include "micro/endian.h"
    #endif //CORTEXM3
    #include "plugin/sim-eeprom/sim-eeprom.h"
    #include "micro/system-timer.h"
    #include "micro/symbol-timer.h"
    #include "micro/spi.h"
    #if defined(CORTEXM3) || defined(EMBER_TEST)
      #include "micro/serial.h"
    #else
      #include "micro/serial-minimal.h"
    #endif
    #include "micro/random.h"
    #include "micro/token.h"
    #ifdef EMBER_TEST
      #include "plugin/adc/adc.h"
      #include "micro/bootloader-interface.h"
      #include "micro/button.h"
      #include "micro/led.h"
    #endif
  #endif // UNIX_HOST && !EMBER_TEST
#elif defined(EMBER_STACK_OWL_RX)
// TODO: here we include only the functionalities that we will have on OWL-RX
  #include "micro/button.h"
  #include "micro/flash.h"
  #include "micro/led.h"
  #include "micro/dog_glcd.h"
  #include "micro/system-timer.h"
  #include "micro/symbol-timer.h"
  #include "micro/spi.h"
  #include "micro/serial-minimal.h"
  #include "micro/endian.h"
//  #include "micro/random.h"
//  #include "micro/token.h"
//  #ifdef EMBER_TEST
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-interface.h"
//    #include "micro/button.h"
//    #include "micro/led.h"
//  #endif
#elif defined(EMBER_STACK_OWL_TX)
// TODO: here we include only the functionalities that we will have on OWL-TX
//  #include "micro/button.h"
//  #include "micro/flash.h"
//  #include "micro/led.h"
//  #include "micro/dog_glcd.h"
//  #include "micro/system-timer.h"
//  #include "micro/symbol-timer.h"
//  #include "micro/spi.h"
//  #include "micro/serial-minimal.h"
//  #include "micro/random.h"
//  #include "micro/token.h"
//  #ifdef EMBER_TEST
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-interface.h"
//    #include "micro/button.h"
//    #include "micro/led.h"
//  #endif
#elif defined(EMBER_STACK_WASP)
// TODO: here we include only the functionalities that we will have on mustang
  #if defined(CORTEXM3)
//    #include "plugin/adc/adc.h"
//    #include "micro/bootloader-eeprom.h"
    #include "micro/button.h"
    #include "plugin/buzzer/buzzer.h"
    #include "micro/led.h"
    #include "micro/diagnostic.h"
  #endif //CORTEXM3
  #include "micro/flash.h"
  #include "micro/system-timer.h"
  #include "micro/symbol-timer.h"
  #include "micro/spi.h"
  #if defined(CORTEXM3)
    #include "micro/serial.h"
  #else
    #include "micro/serial-minimal.h"
  #endif
  #include "micro/random.h"
  #include "micro/token.h"
  #ifdef EMBER_TEST
    #include "plugin/adc/adc.h"
    #include "micro/bootloader-interface.h"
    #include "micro/button.h"
    #include "micro/led.h"
  #endif
#elif !defined(EMBER_STACK_IP)
// Pro Stack
  #include "plugin/adc/adc.h"
  #include "micro/button.h"
  #include "plugin/buzzer/buzzer.h"
  #include "micro/crc.h"
  #include "micro/endian.h"
  #include "micro/led.h"
  #include "micro/random.h"
  #include "micro/serial.h"
  #include "micro/spi.h"
  #include "micro/system-timer.h"
  #include "micro/bootloader-eeprom.h"

//Host processors sometimes use the token module.
  #if !defined(EZSP_HOST) || defined(EMBER_AF_API_TOKEN)
    #include "micro/token.h"
  #endif

//Host processors do not use the following modules, therefore the header
//files should be ignored.
  #ifndef EZSP_HOST
    #include "micro/bootloader-interface.h"
    #include "micro/diagnostic.h"
//No public HAL code in release 4.0 uses the symbol timer,
//therefore it should not be in doxygen.
    #ifndef DOXYGEN_SHOULD_SKIP_THIS
      #include "micro/symbol-timer.h"
    #endif // DOXYGEN_SHOULD_SKIP_THIS
  #endif //EZSP_HOST

#else
// IP Stack
  #include "plugin/adc/adc.h"
  #include "micro/button.h"
  #include "plugin/buzzer/buzzer.h"
  #include "micro/crc.h"
  #include "micro/endian.h"
  #include "micro/led.h"
  #include "micro/random.h"
  #include "micro/serial.h"
  #include "micro/spi.h"
  #include "micro/system-timer.h"

//Host processors sometimes use the token module.
  #if !defined(UNIX_HOST) || defined(EMBER_AF_API_TOKEN)
    #include "micro/token.h"
  #endif

//Host processors do not use the following modules, therefore the header
//files should be ignored.
  #ifndef UNIX_HOST
    #include "micro/bootloader-interface.h"
    #include "micro/diagnostic.h"
//No public HAL code in release 4.0 uses the symbol timer,
//therefore it should not be in doxygen.
    #ifndef DOXYGEN_SHOULD_SKIP_THIS
      #include "micro/symbol-timer.h"
    #endif // DOXYGEN_SHOULD_SKIP_THIS
  #endif //UNIX_HOST

#endif // !EMBER_STACK_IP

#endif // !HAL_HOST

#if ((defined(RTOS) && !defined(IP_MODEM_LIBRARY)) \
  || (defined(UNIX_HOST)                           \
  || defined(UNIX_HOST_SIM)))
  #define EMBER_HOST
  #define emAmHost() true
#else
  #define emAmHost() false
#endif

#endif //__HAL_H__
