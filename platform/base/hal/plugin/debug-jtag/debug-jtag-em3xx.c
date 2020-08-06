/***************************************************************************//**
 * @file
 * @brief EM3XX Debug Transport Mechanism (JTAG)
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
#include "hal/hal.h"
#include "hal/plugin/debug-jtag/debug-channel.h"

#if DEBUG_LEVEL >= BASIC_DEBUG

#define RAM_VERSION_INDEX           0
#define RAM_IN_LENGTH_INDEX         1
#define RAM_IN_BLOCK_SIZE_INDEX     2
#define RAM_IN_BLOCK_POINTER_INDEX  4  // uint32_t pointer must be aligned
#define RAM_OUT_BLOCK_POINTER_INDEX 8  // uint32_t pointer must be aligned
#define RAM_OUT_STATUS_INDEX        12
#define RAM_OUT_LENGTH_INDEX        13
#define RAM_OUT_BLOCK_SIZE_INDEX    14
#define RAM_SIZE                    16
#define RAM_OUT_STATUS_GO   1
#define RAM_OUT_STATUS_STOP 2
#ifdef RAM_DEBUG_OUTPUT
  #define RAM_VERSION 0xB5
#else
  #define RAM_VERSION 0xA5
#endif

#define ramInBlockPointer \
  ((uint32_t *)(debugChannel + RAM_IN_BLOCK_POINTER_INDEX))
#define ramOutBlockPointer \
  ((uint32_t *)(debugChannel + RAM_OUT_BLOCK_POINTER_INDEX))

#define OUT_VERSION_INDEX   0U
#define OUT_TYPE_INDEX      1U
#define OUT_SEQUENCE_INDEX  3U
#define OUT_DATA_INDEX      4U
#define OUT_VERSION 0xD1

#define TIMEOUT_MS 500U

// This is the division factor used to generate the correct baud rate:
// NOTE:  If the prescaler is changed, then the delay in emDebugPowerDown
//        must be adjusted to be 50 bit times at the new baud rate.
#define SPEED_HZ 500000
// This is the amount of time needed to allow a VUART transmission to complete
// before halStackDebugPutBuffer can return.
// 20 byte fifo (four 4 byte transmissions plus their header byte)
// 10 bits per byte
// 500000 baud rate
// (1/500000) * (20*10) = 400 us
#define TX_COMPLETE_DELAY 400

#define MIN(a, b) ((a) < (b) ? (a) : (b))

VAR_AT_SEGMENT(static uint8_t volatile debugChannel[RAM_SIZE], __DEBUG_CHANNEL__);

#if defined(EMBER_STACK_IP) || defined(EMBER_STACK_CONNECT)
#include "stack/include/byte-utilities.h"

#define DEBUG_OFF           0
#define DEBUG_INITIALIZED   1
#define DEBUG_ENABLED       2
#define DEBUG_POWERING_DOWN 3

static uint8_t debugChannelState = DEBUG_OFF;
static uint8_t sequenceNumber = 0;

EmberStatus emDebugInit(void)
{
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();
  // Only initialize the debug channel if we're currently in the OFF state
  if (debugChannelState == DEBUG_OFF) {
    #ifdef RAM_DEBUG_OUTPUT
    *ramOutBlockPointer                    = 0;
    // RAM_OUT_STATUS_INDEX is not modified.
    debugChannel[RAM_OUT_LENGTH_INDEX]     = 0;
    debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = 0;
    #endif //RAM_DEBUG_OUTPUT

    *ramInBlockPointer                    = 0;
    debugChannel[RAM_IN_LENGTH_INDEX]     = 0;
    debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = 0;
    debugChannel[RAM_VERSION_INDEX]       = RAM_VERSION;
    #if DEBUG_LEVEL == FULL_DEBUG
    emberDebugReportRestore(true);
    emDebugClearStats();
    #endif
    debugChannelState = DEBUG_INITIALIZED;
  }
  RESTORE_INTERRUPTS();

  emDebugPowerUp();

  return EMBER_SUCCESS;
}

//NOTE:  If emDebugPowerDown is ever called, emDebugPowerUp must be called
//       in order to restore configuration.
void emDebugPowerDown(void)
{
  uint8_t done = false;

  // Only begin the power down process if we're in the enabled state
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    if (debugChannelState != DEBUG_ENABLED) {
      done = true;
    } else {
      // Set the debug state back down to initialized
      debugChannelState = DEBUG_POWERING_DOWN;
    }
    RESTORE_INTERRUPTS();
  }
  // Now that we're out of the disabled interrupts block return if we are done
  if (done) {
    return;
  }

  #ifndef RAM_DEBUG_OUTPUT
  if ((ITM->TCR & ITM_TCR_ITMENA_Msk)) {
    //Set DWT Sync Tap to 0, disabling sync counting and preventing any
    //new sync packets from being generated:
    DWT->CTRL = (DWT->CTRL & (~DWT_CTRL_SYNCTAP_Msk));

    //Disable ITM, preventing any new activity from being accepted.  Activity
    //already in the hardware FIFO (such as stimulus output or sync output)
    //will not be disrupted.
    ITM->TCR &= ~ITM_TCR_ITMENA_Msk;

    //Wait for the ITM to indicate that is has gone idle
    while (ITM->TCR & ITM_TCR_BUSY_Msk) {
    }

    //Don't bother delaying during shutdown if CDBGPWRUPREQ is not set since
    //this indicates that the debugger is not connected so we do not need
    //to worry about cutting off some data.
    if (CMHV->CPWRUPREQSTATUS) {
      //ARM suggests waiting long enough for 5 bytes of data to be output
      //(50 bit times) which should ensure that any old data has been cleanly
      //output.  50 bit times at 500kbps is 100us.  This matches with testing
      //which has shown that the ITM TCR Busy flag will clear about 78us
      //before the TPIU has finished transmitting.  Since the TPIU provides
      //no means of knowing when it is empty/idle, we must manually delay.
      halCommonDelayMicroseconds(100);
    }

    //NOTE: At this point, all DWT/ITM/TPIU functionality must be idle
    //      and remain idle until emDebugPowerUp is called.

    //When performing an emulated deep sleep the TPIU will go through a
    //partial reset that causes the FIFO pointers to become out of sync.
    //When the chip powers back up, the out of sync pointers will cause
    //the TPIU to resend an unknown amount of data (unknown since we cannot
    //predict how far the pointers will become out of sync).  Since there
    //is no means of stopping or altering this transmission, our only
    //option is to change the TPIU protocol to transmit (flush) these bytes
    //as quickly as possible.  Since the GPIO will be powerup/reenabled
    //before the TPIU is reconfigured, we need to maintain the same
    //protocol used during normal operation (this means we can't switch
    //from NRZ to 4bit synchronous and back again without generating extra
    //edges on the GPIO).  The fastest method, therefore, is to reduce the
    //prescalar and increase baud rate to maximum.  Given a maximum of 8
    //bytes (80 NRZ bits) at 6Mhz, the transmission should complete in
    //13.4us. Since cstartup normally takes ~50us of time, the garbage
    //should be flushed long before LV_FREEZE is cleared and the GPIO are
    //reconfigured for TPIU output.
    TPI->ACPR = 0;    //fastest possible NRZ transmission
  }
  #endif //RAM_DEBUG_OUTPUT

  debugChannelState = DEBUG_INITIALIZED;
}

void emDebugPowerUp(void)
{
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();
  // Only enable the debug channel if it's in the initialized state
  if (debugChannelState == DEBUG_INITIALIZED) {
    #ifndef RAM_DEBUG_OUTPUT
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;          // Trace enable.
    TPI->CSPSR = 1;                             // Port size.
    halInternalTpiuSetSpeedHz(SPEED_HZ);      // Speed divisor.
    TPI->SPPR = 2;                             // Pin protocol (2 = NRZ).
    TPI->FFCR = 0;                             // Disable formatter.
    ITM->LAR = 0xC5ACCE55;                      // Unlock ITM.
    ITM->TER = 1;                              // Enable stimulus port 0.
    ITM->TCR = ((0x01 << ITM_TCR_TraceBusID_Pos)    // Must be value between 0x01-0x6F
                | ITM_TCR_DWTENA_Msk              // Enable DWT.
                | ITM_TCR_SYNCENA_Msk             // Enable synchronization.
                | ITM_TCR_ITMENA_Msk);             // Enable ITM.
    DWT->CTRL = ((1 << DWT_CTRL_SYNCTAP_Pos)   // Synchronisation pulse rate.
                 | DWT_CTRL_CYCCNTENA_Msk);       // Enable CYCCNT.
    #endif //RAM_DEBUG_OUTPUT

    // Enable halDebugIsr().
    NVIC_EnableIRQ(DEBUG_IRQn);
    debugChannelState = DEBUG_ENABLED;
  }
  RESTORE_INTERRUPTS();
}

bool halStackDebugActive(void)
{
  #ifdef RAM_DEBUG_OUTPUT
  return (debugChannel[RAM_OUT_STATUS_INDEX] == RAM_OUT_STATUS_GO);
  #else//!RAM_DEBUG_OUTPUT
  // To be active, debug needs to be enabled, debugger needs to be connected,
  // and trace needs to be enabled.
  return ((debugChannelState == DEBUG_ENABLED)
          && CMHV->CPWRUPREQSTATUS
          && (CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) != 0);
  #endif//RAM_DEBUG_OUTPUT
}

uint8_t emDebugAddInitialFraming(uint8_t *buff, uint16_t debugType)
{
  buff[OUT_VERSION_INDEX]  = OUT_VERSION;
  buff[OUT_TYPE_INDEX]     = LOW_BYTE(debugType);
  buff[OUT_TYPE_INDEX + 1] = HIGH_BYTE(debugType);
  buff[OUT_SEQUENCE_INDEX] = sequenceNumber++;
  return OUT_DATA_INDEX;
}

#ifdef RAM_DEBUG_OUTPUT

static EmberStatus sendOutput(uint8_t *data, uint8_t length)
{
  uint8_t blockSize;
  uint16_t startTime = halCommonGetInt16uMillisecondTick();
  if (debugChannel[RAM_OUT_STATUS_INDEX] != RAM_OUT_STATUS_GO
      || debugChannel[RAM_OUT_LENGTH_INDEX] != 0
      || length < OUT_DATA_INDEX) {
    return EMBER_ERR_FATAL;
  }
  debugChannel[RAM_OUT_LENGTH_INDEX] = length;
  *ramOutBlockPointer = (uint32_t)data;
  blockSize = MIN(length, MAX_BLOCK_SIZE);
  debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = blockSize;
  while (length > 0) {
    uint16_t now = halCommonGetInt16uMillisecondTick();
    if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
      break;
    }
    if (debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] == 0) {
      length -= blockSize;
      if (length > 0) {
        *ramOutBlockPointer += blockSize;
        blockSize = MIN(length, MAX_BLOCK_SIZE);
        debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = blockSize;
      }
    }
  }
  debugChannel[RAM_OUT_LENGTH_INDEX] = 0;
  debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = 0;
  if (length == 0) {
    return EMBER_SUCCESS;
  } else {
    debugChannel[RAM_OUT_STATUS_INDEX] = RAM_OUT_STATUS_STOP;
    return EMBER_ERR_FATAL;
  }
}

#else // RAM_DEBUG_OUTPUT

static EmberStatus sendOutput(uint8_t *data, uint8_t dataLength)
{
  uint8_t length = dataLength + 5;
  uint8_t index = 0;
  uint16_t startTime = halCommonGetInt16uMillisecondTick();
  uint16_t crc = 0xFFFF;

  while ((halStackDebugActive()) && (index < length)) {
    uint16_t now = halCommonGetInt16uMillisecondTick();
    if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
      break;
    }
    if (ITM->PORT[0].u32 == 1 /*ITM_SP0_FIFOREADY*/) {
      uint32_t output = 0;
      uint8_t i;
      for (i = 0; i < 4; i++) {
        uint8_t outputByte;
        if (index == 0) {
          outputByte = '[';
          index++;
        } else if (index == 1) {
          outputByte = dataLength;
          index++;
        } else if (index == length - 3) {
          outputByte = LOW_BYTE(crc);
          index++;
        } else if (index == length - 2) {
          outputByte = HIGH_BYTE(crc);
          index++;
        } else if (index == length - 1) {
          outputByte = ']';
          index++;
        } else if (index == length) {
          outputByte = 0;
        } else {
          outputByte = data[index - 2];
          crc = halCommonCrc16(outputByte, crc);
          index++;
        }
        output |= (uint32_t) (((uint32_t) outputByte) << (i * 8));
      }
      ITM->PORT[0].u32 = output;
    }
  }

  //By design, emberSerialPrintf of the VUART must complete before returning.
  //But, the hardware has a very deep FIFO that means it's possible to return
  //before the transmission has completed.  The hardware does not provide
  //any means of knowing when transmission has completed, so the simplest,
  //safest, and cleanest method is to simply wait based upon our baud rate.
  //Because of the framing used on the bytes, performing a printf of even
  //just a single byte will result in enough data that this delay will only
  //add a small amount (factor of safety) beyond the time necessary (10-40us).
  halCommonDelayMicroseconds(TX_COMPLETE_DELAY);

  if (index == length) {
    return EMBER_SUCCESS;
  } else {
    return EMBER_ERR_FATAL;
  }
}

#endif // RAM_DEBUG_OUTPUT

EmberStatus emDebugSend(uint8_t *data, uint8_t *length)
{
  EmberStatus status = EMBER_SUCCESS;
  if (*length > OUT_DATA_INDEX) {
    status = sendOutput(data, *length);
  }
  *length = OUT_DATA_INDEX;
  return status;
}

// 255 bytes is the maximum input that the ISA will send us. There is no way to
// tell the ISA we have a smaller buffer. We have to receive the whole message
// before processing it because the message type is the last two bytes. If this
// buffer were small enough to go on the stack, it could be moved inside
// halDebugIsr().
static uint8_t rxBuffer[255];

void halDebugIsr(void)
{
  uint8_t length = debugChannel[RAM_IN_LENGTH_INDEX];
  if (length > 0) {
    uint16_t startTime = halCommonGetInt16uMillisecondTick();
//    if (length > sizeof(rxBuffer)) {
//      debugChannel[RAM_IN_LENGTH_INDEX] = 0;
//      return;
//    }
    uint8_t remainingLength = length;
    uint8_t blockSize = MIN(remainingLength, MAX_BLOCK_SIZE);
    *ramInBlockPointer = (uint32_t)rxBuffer;
    debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = blockSize;
    while (debugChannel[RAM_IN_LENGTH_INDEX] > 0) {
      uint16_t now = halCommonGetInt16uMillisecondTick();
      if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
        break;
      }
      if (debugChannel[RAM_IN_BLOCK_SIZE_INDEX] == 0) {
        remainingLength -= blockSize;
        debugChannel[RAM_IN_LENGTH_INDEX] = remainingLength;
        if (remainingLength > 0) {
          *ramInBlockPointer += blockSize;
          blockSize = MIN(remainingLength, MAX_BLOCK_SIZE);
          debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = blockSize;
        }
      }
    }
    if (remainingLength == 0
        && debugChannel[RAM_IN_LENGTH_INDEX] == 0
        && debugChannel[RAM_IN_BLOCK_SIZE_INDEX] == 0) {
      uint16_t type = emberFetchLowHighInt16u(rxBuffer + length - 2);
      emDebugProcessIncoming(type, rxBuffer, length - 2);
    } else {
      debugChannel[RAM_IN_LENGTH_INDEX] = 0;
      debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = 0;
    }
  }
}

void emDebugReceiveData(void)
{
}

#else //defined(EMBER_STACK_IP) || defined(EMBER_STACK_CONNECT))
#include "stack/include/packet-buffer.h"

static uint8_t sequenceNumber = 0;

EmberStatus emDebugInit(void)
{
  #ifdef RAM_DEBUG_OUTPUT
  *ramOutBlockPointer                    = 0;
  // RAM_OUT_STATUS_INDEX is not modified.
  debugChannel[RAM_OUT_LENGTH_INDEX]     = 0;
  debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = 0;
  #endif //RAM_DEBUG_OUTPUT

  *ramInBlockPointer                    = 0;
  debugChannel[RAM_IN_LENGTH_INDEX]     = 0;
  debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = 0;
  debugChannel[RAM_VERSION_INDEX]       = RAM_VERSION;
  emberDebugReportRestore(true);
  emDebugClearStats();

  emDebugPowerUp();

  return (EmberStatus) EMBER_SUCCESS;
}

//NOTE:  If emDebugPowerDown is ever called, emDebugPowerUp must be called
//       in order to restore configuration.
void emDebugPowerDown(void)
{
  #ifndef RAM_DEBUG_OUTPUT
  if ((ITM->TCR & ITM_TCR_ITMENA_Msk) != 0U) {
    //Set DWT Sync Tap to 0, disabling sync counting and preventing any
    //new sync packets from being generated:
    DWT->CTRL = (DWT->CTRL & (~DWT_CTRL_SYNCTAP_Msk));

    //Disable ITM, preventing any new activity from being accepted.  Activity
    //already in the hardware FIFO (such as stimulus output or sync output)
    //will not be disrupted.
    ITM->TCR &= ~ITM_TCR_ITMENA_Msk;

    //Wait for the ITM to indicate that is has gone idle
    while ((ITM->TCR & ITM_TCR_BUSY_Msk) != 0U) {
    }

    //Don't bother delaying during shutdown if CDBGPWRUPREQ is not set since
    //this indicates that the debugger is not connected so we do not need
    //to worry about cutting off some data.
    if ((CMHV->CPWRUPREQSTATUS) != 0U) {
      //ARM suggests waiting long enough for 5 bytes of data to be output
      //(50 bit times) which should ensure that any old data has been cleanly
      //output.  50 bit times at 500kbps is 100us.  This matches with testing
      //which has shown that the ITM TCR Busy flag will clear about 78us
      //before the TPIU has finished transmitting.  Since the TPIU provides
      //no means of knowing when it is empty/idle, we must manually delay.
      halCommonDelayMicroseconds(100);
    }

    //NOTE: At this point, all DWT/ITM/TPIU functionality must be idle
    //      and remain idle until emDebugPowerUp is called.

    //When performing an emulated deep sleep the TPIU will go through a
    //partial reset that causes the FIFO pointers to become out of sync.
    //When the chip powers back up, the out of sync pointers will cause
    //the TPIU to resend an unknown amount of data (unknown since we cannot
    //predict how far the pointers will become out of sync).  Since there
    //is no means of stopping or altering this transmission, our only
    //option is to change the TPIU protocol to transmit (flush) these bytes
    //as quickly as possible.  Since the GPIO will be powerup/reenabled
    //before the TPIU is reconfigured, we need to maintain the same
    //protocol used during normal operation (this means we can't switch
    //from NRZ to 4bit synchronous and back again without generating extra
    //edges on the GPIO).  The fastest method, therefore, is to reduce the
    //prescalar and increase baud rate to maximum.  Given a maximum of 8
    //bytes (80 NRZ bits) at 6Mhz, the transmission should complete in
    //13.4us. Since cstartup normally takes ~50us of time, the garbage
    //should be flushed long before LV_FREEZE is cleared and the GPIO are
    //reconfigured for TPIU output.
    TPI->ACPR = 0;    //fastest possible NRZ transmission
  }
  #endif //RAM_DEBUG_OUTPUT
}

void emDebugPowerUp(void)
{
  #ifndef RAM_DEBUG_OUTPUT
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;          // Trace enable.
  TPI->CSPSR = 1;                             // Port size.
  (void) halInternalTpiuSetSpeedHz(SPEED_HZ);      // Speed divisor.
  TPI->SPPR = 2;                             // Pin protocol (2 = NRZ).
  TPI->FFCR = 0;                             // Disable formatter.
  ITM->LAR = 0xC5ACCE55U;                      // Unlock ITM.
  ITM->TER = 1;                              // Enable stimulus port 0.
  ITM->TCR = ((0x01U << ITM_TCR_TraceBusID_Pos)    // Must be value between 0x01-0x6F
              | ITM_TCR_DWTENA_Msk              // Enable DWT.
              | ITM_TCR_SYNCENA_Msk             // Enable synchronization.
              | ITM_TCR_ITMENA_Msk);             // Enable ITM.
  DWT->CTRL = ((1U << DWT_CTRL_SYNCTAP_Pos)   // Synchronisation pulse rate.
               | DWT_CTRL_CYCCNTENA_Msk);       // Enable CYCCNT.
  #endif //RAM_DEBUG_OUTPUT

  // Enable halDebugIsr().
  NVIC_EnableIRQ(DEBUG_IRQn);
}

bool halStackDebugActive(void)
{
  #ifdef RAM_DEBUG_OUTPUT
  return (debugChannel[RAM_OUT_STATUS_INDEX] == RAM_OUT_STATUS_GO);
  #else//!RAM_DEBUG_OUTPUT
  return ((TPI->ACPR != 0U)
          && ((CMHV->CPWRUPREQSTATUS) != 0U)
          && ((CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk) != 0U));
  #endif//RAM_DEBUG_OUTPUT
}

uint8_t emDebugAddInitialFraming(uint8_t *buff, uint16_t debugType)
{
  buff[OUT_VERSION_INDEX]  = OUT_VERSION;
  buff[OUT_TYPE_INDEX]     = LOW_BYTE(debugType);
  buff[OUT_TYPE_INDEX + 1] = HIGH_BYTE(debugType);
  buff[OUT_SEQUENCE_INDEX] = sequenceNumber++;
  return OUT_DATA_INDEX;
}

#ifdef RAM_DEBUG_OUTPUT

static EmberStatus ramOutput(EmberMessageBuffer buffer)
{
  uint8_t length = emberMessageBufferLength(buffer);
  uint8_t blockSize;
  uint16_t startTime = halCommonGetInt16uMillisecondTick();
  if (debugChannel[RAM_OUT_STATUS_INDEX] != RAM_OUT_STATUS_GO
      || debugChannel[RAM_OUT_LENGTH_INDEX] != 0
      || length < OUT_DATA_INDEX) {
    return EMBER_ERR_FATAL;
  }
  debugChannel[RAM_OUT_LENGTH_INDEX] = length;
  *ramOutBlockPointer = (uint32_t)emberMessageBufferContents(buffer);
  blockSize = MIN(length, PACKET_BUFFER_SIZE);
  debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = blockSize;
  while (length > 0) {
    uint16_t now = halCommonGetInt16uMillisecondTick();
    if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
      break;
    }
    if (debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] == 0) {
      length -= blockSize;
      if (length > 0) {
        buffer = emberStackBufferLink(buffer);
        *ramOutBlockPointer = (uint32_t)emberMessageBufferContents(buffer);
        blockSize = MIN(length, PACKET_BUFFER_SIZE);
        debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = blockSize;
      }
    }
  }
  debugChannel[RAM_OUT_LENGTH_INDEX] = 0;
  debugChannel[RAM_OUT_BLOCK_SIZE_INDEX] = 0;
  if (length == 0) {
    return EMBER_SUCCESS;
  } else {
    debugChannel[RAM_OUT_STATUS_INDEX] = RAM_OUT_STATUS_STOP;
    return EMBER_ERR_FATAL;
  }
}

#else // RAM_DEBUG_OUTPUT

static EmberStatus swoOutput(EmberMessageBuffer buffer)
{
  uint8_t swoOutputLength = emberMessageBufferLength(buffer) + 5U;
  uint8_t index = 0U;
  uint16_t startTime = halCommonGetInt16uMillisecondTick();
  uint16_t crc = 0xFFFFU;
  while ((halStackDebugActive()) && (index < swoOutputLength)) {
    uint16_t now = halCommonGetInt16uMillisecondTick();
    if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
      break;
    }
    if (ITM->PORT[0].u32 == 1U /*ITM_SP0_FIFOREADY*/) {
      uint32_t output = 0U;
      uint8_t i;
      for (i = 0; i < 4U; i++) {
        uint8_t outputByte;
        if (index == 0) {
          outputByte = (uint8_t)'[';
          index++;
        } else if (index == 1U) {
          outputByte = emberMessageBufferLength(buffer);
          index++;
        } else if (index == swoOutputLength - 3U) {
          outputByte = LOW_BYTE(crc);
          index++;
        } else if (index == swoOutputLength - 2U) {
          outputByte = HIGH_BYTE(crc);
          index++;
        } else if (index == swoOutputLength - 1U) {
          outputByte = (uint8_t) ']';
          index++;
        } else if (index == swoOutputLength) {
          outputByte = 0U;
        } else {
          outputByte = emberGetLinkedBuffersByte(buffer, index - 2U);
          crc = halCommonCrc16(outputByte, crc);
          index++;
        }
        output |= (uint32_t) (((uint32_t) outputByte) << (i * 8U));
      }
      ITM->PORT[0].u32 = output;
    }
  }

  //By design, emberSerialPrintf of the VUART must complete before returning.
  //But, the hardware has a very deep FIFO that means it's possible to return
  //before the transmission has completed.  The hardware does not provide
  //any means of knowing when transmission has completed, so the simplest,
  //safest, and cleanest method is to simply wait based upon our baud rate.
  //Because of the framing used on the bytes, performing a printf of even
  //just a single byte will result in enough data that this delay will only
  //add a small amount (factor of safety) beyond the time necessary (10-40us).
  halCommonDelayMicroseconds(TX_COMPLETE_DELAY);

  if (index == swoOutputLength) {
    return (EmberStatus) EMBER_SUCCESS;
  } else {
    return (EmberStatus) EMBER_ERR_FATAL;
  }
}

#endif // RAM_DEBUG_OUTPUT

EmberStatus halStackDebugPutBuffer(EmberMessageBuffer buffer)
{
  if (emberMessageBufferLength(buffer) < OUT_DATA_INDEX) {
    return (EmberStatus) EMBER_ERR_FATAL;
  }
  #ifdef RAM_DEBUG_OUTPUT
  return ramOutput(buffer);
  #else
  return swoOutput(buffer);
  #endif
}

void halDebugIsr(void)
{
  uint8_t remainingLength = debugChannel[RAM_IN_LENGTH_INDEX];
  if (remainingLength > 0U) {
    uint16_t startTime = halCommonGetInt16uMillisecondTick();
    EmberMessageBuffer buffer = emberFillLinkedBuffers(NULL, remainingLength);
    EmberMessageBuffer currentBlock = buffer;
    if (buffer == (EmberMessageBuffer)EMBER_NULL_MESSAGE_BUFFER) {
      debugChannel[RAM_IN_LENGTH_INDEX] = 0U;
      return;
    }
    uint8_t blockSize = MIN(remainingLength, PACKET_BUFFER_SIZE);
    *ramInBlockPointer = (uint32_t)emberMessageBufferContents(currentBlock);
    debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = blockSize;
    while (debugChannel[RAM_IN_LENGTH_INDEX] > 0U) {
      uint16_t now = halCommonGetInt16uMillisecondTick();
      if (elapsedTimeInt16u(startTime, now) > TIMEOUT_MS) {
        break;
      }
      if (debugChannel[RAM_IN_BLOCK_SIZE_INDEX] == 0U) {
        remainingLength -= blockSize;
        debugChannel[RAM_IN_LENGTH_INDEX] = remainingLength;
        if (remainingLength > 0U) {
          currentBlock = emberStackBufferLink(currentBlock);
          blockSize = MIN(remainingLength, PACKET_BUFFER_SIZE);
          *ramInBlockPointer = (uint32_t)emberMessageBufferContents(currentBlock);
          debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = blockSize;
        }
      }
    }
    if (remainingLength == 0U
        && debugChannel[RAM_IN_LENGTH_INDEX] == 0U
        && debugChannel[RAM_IN_BLOCK_SIZE_INDEX] == 0U) {
      uint8_t bufferLength = emberMessageBufferLength(buffer);
      uint16_t type = emberGetLinkedBuffersLowHighInt16u(buffer,
                                                         bufferLength - 2U);
      // Virtual UART input is handled immediately (in interrupt context). All
      // other input is put on a queue so it can be handled by
      // emDebugReceiveTick(). This is so that applications can receive virtual
      // UART input without having to call emDebugReceiveTick().
      if (type == EM_DEBUG_VIRTUAL_UART_RX) {
        emberSetLinkedBuffersLength(buffer, bufferLength - 2U);
        emDebugProcessIncoming(type, buffer);
      } else {
        emDebugQueueAdd(buffer);
      }
    } else {
      debugChannel[RAM_IN_LENGTH_INDEX] = 0U;
      debugChannel[RAM_IN_BLOCK_SIZE_INDEX] = 0U;
    }
    emberReleaseMessageBuffer(buffer);
  }
}

void emDebugReceiveData(void)
{
}

#endif //defined(EMBER_STACK_IP) || defined(EMBER_STACK_CONNECT))

#endif // DEBUG_LEVEL >= BASIC_DEBUG
