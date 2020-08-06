/***************************************************************************//**
 * @file
 * @brief em35x standalone bootloader public definitions
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
#ifndef __BTL_EZSP_SPI_PROTOCOL_H__
#define __BTL_EZSP_SPI_PROTOCOL_H__
#ifdef BTL_HAS_EZSP_SPI

#define SPIP_RESET               0x00
#define SPIP_OVERSIZED_EZSP      0x01
#define SPIP_ABORTED_TRANSACTION 0x02
#define SPIP_MISSING_FT          0x03
#define SPIP_UNSUPPORTED_COMMAND 0x04
#define SPIP_VERSION             0x82
#define SPIP_ALIVE               0xC1

#define FRAME_TERMINATOR 0xA7

void halHostSerialInit(void);
bool halHostSerialTick(bool responseReady);
void halHostCallback(bool haveData);
void spiImmediateResponse(uint8_t status);

extern uint8_t halHostResponseBuffer[];
extern uint8_t halHostCommandBuffer[];

void flushSpiResponse(void);

extern bool spipFramePending;      // halHostBuffer[] contains a frame
extern bool spipResponsePending;   // have data to send in next spi session

#define XMODEM_FRAME_START_INDEX 2

#define SPI_FRAME_ID_INDEX 0
#define SPI_FRAME_LENGTH_INDEX 1

// Note these lengths only apply directly to radio messages
// For ezsp spi the length is decreased by RSP_MSG_ACK_NAK_ERR_OFFSET + 1
#define QUERY_RESPONSE_MESSAGE_LENGTH 53

// The EM260 added an extra byte with error information to ACK, NAK and CAN
// messages. To add a zero byte so that the message length remain the same,
// define THREE_BYTE_ACK_NAK_CAN_MESSAGES.
//#define THREE_BYTE_ACK_NAK_CAN_MESSAGES
#ifdef THREE_BYTE_ACK_NAK_CAN_MESSAGES
  #define QUERY_ACK_NAK_MESSAGE_LENGTH  30
#else
  #define QUERY_ACK_NAK_MESSAGE_LENGTH  29
#endif

#endif // BTL_HAS_EZSP_SPI
#endif //__BTL_EZSP_SPI_PROTOCOL_H__
