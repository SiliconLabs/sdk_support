/***************************************************************************//**
 * @file
 * @brief EFM32 bootloader serial interface functions for ezsp spi
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
#include PLATFORM_HEADER  // should be iar.h
#include "bootloader-common.h"
#include "bootloader-gpio.h"
#include "bootloader-serial.h"
#include "btl-ezsp-spi-protocol.h"
#include "stack/include/ember-types.h"
#include "hal.h"

bool spipFramePending;       // halHostCommandBuffer[] contains a frame
bool spipResponsePending;    // have data to send in next spi session
uint8_t preSpiComBufIndex;        // index for reading from halHostCommandBuffer[]

void serInit(void)
{
  halHostSerialInit();
}

void serPutFlush(void)
{
  //stub
}

void serPutChar(uint8_t ch)
{
  //stub
  (void)ch;
}

void serPutStr(const char *str)
{
  //stub
  (void)*str;
}

void serPutBuf(const uint8_t buf[], uint8_t size)
{
  //stub
  (void)*buf; (void)size;
}

void serPutHex(uint8_t byte)
{
  //stub
  (void)byte;
}

void serPutHexInt(uint16_t word)
{
  //stub
  (void)word;
}

// get char if available, else return error
BL_Status serGetChar(uint8_t* ch)
{
  if (serCharAvailable()) {
    *ch = halHostCommandBuffer[XMODEM_FRAME_START_INDEX + preSpiComBufIndex];
    preSpiComBufIndex++;
    return BL_SUCCESS;
  } else {
    return BL_ERR;
  }
}

bool serCharAvailable(void)
{
  if (spipFramePending) {           // already have frame?
    return true;
  }

  if (!halHostSerialTick(false)) {  // see if a frame was just received
    return false;
  }
  if (spipResponsePending) {        // need to send a response?
    halHostCallback(false);         // send it at once
    halHostSerialTick(true);
    spipResponsePending = false;
    return false;
  }
  spipFramePending = true;          // flag frame available
  preSpiComBufIndex = 0;            // and set read index to the frame start
  return true;
}

void serGetFlush(void)
{
  //stub
}
