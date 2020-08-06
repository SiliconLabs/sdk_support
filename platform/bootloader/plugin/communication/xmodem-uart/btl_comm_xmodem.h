/***************************************************************************//**
 * @file
 * @brief Communication plugin implementing XMODEM
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

#ifndef BTL_COMM_XMODEM_H
#define BTL_COMM_XMODEM_H

#include "core/btl_util.h"

MISRAC_DISABLE
#include "em_common.h"
MISRAC_ENABLE
#include "plugin/communication/xmodem-parser/btl_xmodem.h"

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup Communication
 * @{
 * @page communication_xmodem UART XMODEM
 *   By enabling the UART XMODEM communication plugin, the bootloader
 *   communication interface implements the XMODEM-CRC protocol over UART. This
 *   plugin makes the bootloader compatible with the legacy
 *   `serial-uart-bootloader` that was previously released with the EmberZnet
 *   and SL-Thread wireless stacks.
 ******************************************************************************/

/** @cond DO_NOT_INCLUDE_WITH_DOXYGEN */

SL_PACK_START(1)
typedef struct {
  uint8_t padding;
  XmodemPacket_t packet;
} SL_ATTRIBUTE_PACKED XmodemReceiveBuffer_t;
SL_PACK_END()

typedef enum {
  MENU,
  IDLE,
  INIT_TRANSFER,
  WAIT_FOR_DATA,
  RECEIVE_DATA,
  BOOT,
  COMPLETE,
} XmodemState_t;

/** @endcond */

/** @} addtogroup Communication */
/** @} addtogroup Plugin */

#endif // BTL_COMM_XMODEM_H
