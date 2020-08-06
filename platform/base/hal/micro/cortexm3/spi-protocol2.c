/***************************************************************************//**
 * @file
 * @brief SPI protocol implementation for ZIP NCPs (ip-modem-app-spi et al)
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
#include "serial/serial.h"
#include "hal/micro/cortexm3/spi-protocol2.h"

// TODO find a better home for this too.  it should probably live in some
// hal-wide header and then the other random projects that define their own
// should be modified to use the global one
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Pin assignments - uses SC2, IRQB, IRQC
// PA0 - MOSI
// PA1 - MISO
// PA2 - SCLK
// PA3 - nSSEL (IRQC)
// PB2 - nHOST_INT  (EZSP-SPI compatibility)
// PB4 - nHOST_ALT  (alternative nHOST_INT)
// PB6 - nWAKE (IRQB)
// PB0 - nSIMRST (IRQA replaces nRESET for debugging only)

// Convenience defines to make the GPIO code easier to read.
#define GPIOOUT_PULLUP                       (0x1u)
#define GPIOOUT_PULLDOWN                     (0x0u)
#define GPIOINTMOD_DISABLED                  (0)
#define GPIOINTMOD_RISING_EDGE               (1)
#define GPIOINTMOD_FALLING_EDGE              (2)
#define GPIOINTMOD_BOTH_EDGES                (3)
#define GPIOINTMOD_HIGH_LEVEL                (4)
#define GPIOINTMOD_LOW_LEVEL                 (5)

#define SPI_INITED (SC2->MODE == SC_MODE_MODE_SPI) // SPI has been activated

// SC2MOSI: PA0, configured as a floating input
#define MOSI_BIT            0

// SC2MISO: PA1, configured as an alternate function push-pull output
#define MISO_BIT            1

// SC2SCLK: PA2, configured as a floating input
#define SCLK_BIT            2

// SC2nSSEL:  PA3, configured as a input with pullup
// nSSEL interrupt: IRQC (assigned to pin PA3, rising edge with no filtering)
#define nSSEL_BIT           3
#define PULLUP_nSSEL()      (GPIO->P[0].SET = (1 << nSSEL_BIT))
#define nSSEL_IS_HIGH       ((GPIO->P[0].IN & (1 << nSSEL_BIT)) != 0)
#define nSSEL_IS_LOW        ((GPIO->P[0].IN & (1 << nSSEL_BIT)) == 0)
#define nSSEL_IRQSEL        (GPIO->IRQCSEL)
#define nSSEL_IRQSEL_MASK   3
#define nSSEL_INTCFG        (EVENT_GPIO->CFGC)
#define nSSEL_INT           BIT32(IRQC_IRQn)
#define nSSEL_GPIOFLAG      (EVENT_GPIO_FLAG_IRQC)

// nHOST_INT: PB2, configured as a push-pull output
// nHOST_ALT: PB4, configured as a push-pull output
#define nHOST_INT_BIT       2
#define nHOST_ALT_BIT       4
#define CFG_nHOST_INT(cfg)  do { uint32_t temp;                                   \
                                 temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px2_MASK; \
                                 temp |= (cfg) << _GPIO_P_CFGL_Px2_SHIFT;         \
                                 GPIO->P[1].CFGL = temp;                          \
                                 temp = GPIO->P[1].CFGH & ~_GPIO_P_CFGH_Px4_MASK; \
                                 temp |= (cfg) << _GPIO_P_CFGH_Px4_SHIFT;         \
                                 GPIO->P[1].CFGH = temp; } while (0)
#define SET_nHOST_INT()     do { GPIO->P[1].SET = (1 << nHOST_INT_BIT) \
                                                  | (1 << nHOST_ALT_BIT); } while (0)
#define CLR_nHOST_INT()     do { GPIO->P[1].CLR = (1 << nHOST_INT_BIT) \
                                                  | (1 << nHOST_ALT_BIT); } while (0)

// nSSEL_INT: PB3, configured as a floating input
// For EM260 compatibility, can be connected to nSSEL; it is unused on the 35x
#define nSSEL_INT_BIT       3
#define CFG_nSSEL_INT(cfg)  do { uint32_t temp;                                   \
                                 temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px3_MASK; \
                                 temp |= (cfg) << _GPIO_P_CFGL_Px3_SHIFT;         \
                                 GPIO->P[1].CFGL = temp; } while (0)

// nWAKE: PB6, configured as input with a pull-up
// nWAKE interrupt: IRQB (fixed at pin PB6, falling edge with no filtering)
#define nWAKE_BIT           6
#define CFG_nWAKE(cfg)      do { uint32_t temp;                                   \
                                 temp = GPIO->P[1].CFGH & ~_GPIO_P_CFGH_Px6_MASK; \
                                 temp |= (cfg) << _GPIO_P_CFGH_Px6_SHIFT;         \
                                 GPIO->P[1].CFGH = temp; } while (0)
#define PULLUP_nWAKE()      (GPIO->P[1].SET = (1 << nWAKE_BIT))
#define nWAKE_IS_HIGH       ((GPIO->P[1].IN & (1 << nWAKE_BIT)) != 0)
#define nWAKE_IS_LOW        ((GPIO->P[1].IN & (1 << nWAKE_BIT)) == 0)
#define nWAKE_INTCFG        (EVENT_GPIO->CFGB)
#define nWAKE_INT           BIT32(IRQB_IRQn)
#define nWAKE_GPIOFLAG      (EVENT_GPIO_FLAG_IRQB)

// For debugging, use PB0/IRQA in place of nRESET.  Use the the board file
// dev0680spi-test.h to enable this functionality (the board file configures
// the gpio and defines ENABLE_NSIMRST).
#ifdef ENABLE_NSIMRST
// nSIMRST: PB0, configured as input with a pull-up
// nSIMRST interrupt: IRQA (fixed at pin PB0, falling edge with no filtering)
#define nSIMRST_BIT         0
#define CFG_nSIMRST(cfg)    do { uint32_t temp;                                   \
                                 temp = GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px0_MASK; \
                                 temp |= (cfg) << _GPIO_P_CFGL_Px0_SHIFT;         \
                                 GPIO->P[1].CFGL = temp; } while (0)
#define PULLUP_nSIMRST()    (GPIO->P[1].SET = (1 << nSIMRST_BIT))
#define nSIMRST_IS_HIGH     ((GPIO->P[1].IN & (1 << nSIMRST_BIT)) != 0)
#define nSIMRST_IS_LOW      ((GPIO->P[1].IN & (1 << nSIMRST_BIT)) == 0)
#define nSIMRST_INTCFG      (EVENT_GPIO->CFGA)
#define nSIMRST_INT         BIT32(IRQA_IRQn)
#define nSIMRST_GPIOFLAG    (EVENT_GPIO_FLAG_IRQA)
#endif

#define NUM_RX_BUFFERS            1

typedef struct NcpSpiRxBuffer {
  // TODO does this need to be volatile?
  uint8_t buffer[NCP_SPI_BUFSIZE];
  uint8_t * packet; // start address of the packet within the buffer (may not be
                    // 0 due to padding)
  uint8_t * payload; // start address of the payload within the buffer (will be
                     // NCP_SPI_PKT_HEADER_LEN bytes after 'packet'
} NcpSpiRxBuffer;

typedef struct NcpSpiTxBuffer {
  uint8_t buffer[NCP_SPI_BUFSIZE];
  uint16_t head; // index of first byte in the circular buffer
  uint16_t tail; // index after the last byte in the buffer, i.e. the index at
                 // which the next byte enqueued will be placed
  uint16_t length; // number of bytes in the buffer -- if we're currently copying
                   // data into the buffer, this may not be the same as the
                   // number of bytes indicated by head and tail
} NcpSpiTxBuffer;

static NcpSpiTxBuffer txBuffer; // NCP to host
static NcpSpiRxBuffer rxBuffers[NUM_RX_BUFFERS]; // host to NCP
static NcpSpiRxBuffer* activeRxBuffer = rxBuffers;

bool spipFlagWakeFallingEdge;    // flag for detecting a falling edge on nWAKE
bool spipFlagIdleHostInt;        // flag for idling nHOST_INT at proper time
bool spipFlagNcpReset = true;    // flag for indicating the SPIP has just booted
bool spipFlagRxComplete;         // flag for indicating a complete but
                                 // unprocessed transaction
bool spipFlagIgnoreRx;           // flag for when you want to ignore RX,
                                 // such as during error recovery
uint16_t spipBytesReceived;           // number of bytes we received in this transaction

static uint16_t halHostTxBytesUsed(void)
{
  return (txBuffer.tail + NCP_SPI_BUFSIZE - txBuffer.head) % NCP_SPI_BUFSIZE;
}

uint16_t halHostTxSpaceAvailable(void)
{
  return NCP_SPI_BUFSIZE - halHostTxBytesUsed() - 1;
}

bool halHostTxIsIdle(void)
{
  return halHostTxBytesUsed() == NCP_SPI_PKT_HEADER_LEN;
}

void halHostFlushBuffers(void)
{
  DECLARE_INTERRUPT_STATE;
  DISABLE_INTERRUPTS();
  // flush TX
  txBuffer.head = 0;
  txBuffer.tail = NCP_SPI_PKT_HEADER_LEN;
  txBuffer.length = NCP_SPI_PKT_HEADER_LEN;

  // flush RX
  spipFlagIgnoreRx = true; // prevents NAKing in future transactions while
                           // also preventing setting spipFlagRxComplete
  spipFlagRxComplete = false; // prevents processing of current data, if any
  RESTORE_INTERRUPTS();
}

/** @brief shift bytes off the TX buffer.  the packet header is included in
 * these bytes, and this function guarantees that the first bytes of the buffer
 * are reserved for the packet header, so if you attempt to shift fewer bytes
 * than the size of the packet header, no change will occur.
 * @param length  the number of bytes to shift off the buffer.  if this is
 * greater than the length of the packet, the packet length will be made zero.
 */
static void dequeueTx(int32_t length)
{
  assert(length <= txBuffer.length);

  // keep enough bytes for the packet header reserved that don't have actual
  // data in them
  if (length < NCP_SPI_PKT_HEADER_LEN) {
    return;
  }

  length -= NCP_SPI_PKT_HEADER_LEN;

  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    txBuffer.length -= length;
    txBuffer.head = (txBuffer.head + length) % NCP_SPI_BUFSIZE;
    RESTORE_INTERRUPTS();
  }
}

/** @brief sets the packet header fields for a TX packet based on global state.
 * @note this should only be called immediately before loading the DMA, from the ISR
 */
static uint16_t setTxHeader(void)
{
  // set command byte constant fields
  txBuffer.buffer[txBuffer.head] = NCP_SPI_PKT_CMD_PAT
                                   | NCP_SPI_PKT_CMD_PAY
                                   | NCP_SPI_PKT_CMD_RSP;

  // did we reset?
  if (spipFlagNcpReset) {
    txBuffer.buffer[txBuffer.head] |= NCP_SPI_PKT_CMD_RST;
  }

  // if RX DMA isn't loaded, tell host we're not receiving, unless we're
  // intentionally ignoring RX
  if (!(SC2->DMASTAT & (SC_DMASTAT_RXACTA | SC_DMASTAT_RXACTB)) && !spipFlagIgnoreRx) {
    txBuffer.buffer[txBuffer.head] |= NCP_SPI_PKT_CMD_NAK;
  }

  // set length byte
  uint16_t len = txBuffer.length - NCP_SPI_PKT_HEADER_LEN;
  if (len > NCP_SPI_MAX_PAYLOAD) {
    len = NCP_SPI_MAX_PAYLOAD;
  }

  txBuffer.buffer[(txBuffer.head + 1) % NCP_SPI_BUFSIZE] = len;

  return len;
}

/** @brief searches through the first few bytes of the received packet to find
 * the start, ignoring any padding bytes it finds on the way.  This function
 * relies on state inside the buffer object to avoid repetitive searching; that
 * state must be reset before the next RX operation.
 * @param bytesReceived  the number of bytes received so far of the packet,
 * needed for when the full packet hasn't been received yet
 */
static bool findRxPacketStart(NcpSpiRxBuffer* buf, uint16_t bytesReceived)
{
  // TODO unwind loop for speed?
  for (int i = buf->packet - buf->buffer;
       i < NCP_SPI_RX_SLOP && i < bytesReceived;
       ++i) {
    if (*buf->packet == 0xFF || *buf->packet == 0x00) { // padding
      ++buf->packet;
      continue;
    } else if ((*buf->packet & NCP_SPI_PKT_CMD_PAT_MASK)
               == NCP_SPI_PKT_CMD_PAT
               && (*buf->packet & NCP_SPI_PKT_CMD_RSP)
               == DIRECTION_HOST_TO_NCP) {
      // assert the payload bit is set; it might not always be, but
      // we don't know how to deal with it if it's not.  TODO ideally,
      // replace this with some code that can handle it
      assert(*buf->packet & NCP_SPI_PKT_CMD_PAY);
      buf->payload = buf->packet + NCP_SPI_PKT_HEADER_LEN;
      return true;
    } else {
      return false;
    }
  }

  return false;
}

static bool rxPacketHasHeader(NcpSpiRxBuffer* buf, uint16_t bytesReceived)
{
  if (!findRxPacketStart(buf, bytesReceived)) {
    return false;
  }

  return bytesReceived >= (buf->payload - buf->buffer);
}

/** @brief shut down and restart the SPI peripheral.  this is necessary because
 * there may be bytes in the TX or RX FIFOs that we can't clear without
 * restarting the peripheral.  This is especially problematic in the TX case.
 */
static void wipeSpi(void)
{
  // Make SPI peripheral clean and start a-new
  EVENT_SC2->CFG = 0; // disable all interrupts
  SC2->DMACTRL = SC_DMACTRL_RXDMARST;    //reset DMA just in case
  SC2->DMACTRL = SC_DMACTRL_TXDMARST;    //reset DMA just in case
  SC2->MODE = SC_MODE_MODE_DISABLED; //be safe, make sure we start from disabled
  SC2->RATELIN =  0; //no effect in slave mode
  SC2->RATEEXP =  0; //no effect in slave mode
  SC2->SPICFG  = (0 << _SC_SPICFG_SPIMST_SHIFT)    //slave mode
                 | (0 << _SC_SPICFG_SPIPHA_SHIFT) //SPI Mode 0 - sample leading edge
                 | (0 << _SC_SPICFG_SPIPOL_SHIFT) //SPI Mode 0 - rising leading edge
                 | (0 << _SC_SPICFG_SPIORD_SHIFT) //MSB first
                 | (0 << _SC_SPICFG_SPIRXDRV_SHIFT) //no effect in slave mode
                 | (0 << _SC_SPICFG_SPIRPT_SHIFT); //transmit 0xFF when no data to send
  SC2->MODE   =  SC_MODE_MODE_SPI; //activate SPI mode
  EVENT_SC2->FLAG = 0xFFFF;     //clear any stale interrupts
  NVIC_ClearPendingIRQ(SC2_IRQn); //clear stale interrupt
  EVENT_SC2->CFG |= EVENT_SC12_CFG_RXVAL; //enable byte received interrupt
  NVIC_EnableIRQ(SC2_IRQn);     //enable top-level interrupt
}

/** @brief clear stale state from the previous SPI transaction
 */
static void restartSpiRx(void)
{
  spipFlagRxComplete = false;
  spipBytesReceived = 0;

  activeRxBuffer->packet = activeRxBuffer->buffer; // this isn't actually the start of the
  // packet due to possible padding, but it
  // is used as the point where we begin
  // searching for the start of the packet
  // don't set activeRxBuffer->payload because we don't know where it is in the buffer

  SC2->RXBEGA = (uint32_t) activeRxBuffer->buffer;
  SC2->RXENDA = (uint32_t) activeRxBuffer->buffer + NCP_SPI_BUFSIZE - 1;

  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    if (!(SC2->SPISTAT & (SC_SPISTAT_SPIRXVAL | SC_SPISTAT_SPIRXOVF))) {
      /* load DMA only if a transaction hasn't begun (otherwise we might have
       * already missed some bytes).  the assumption here is that if the FIFO
       * is empty in the IF statement above, it can't have filled all 4 bytes
       * worth before we load the DMA, thus there is no race.  I *think* that's
       * a sound assumption, but at high baud rates, who knows
       */
      SC2->DMACTRL = SC_DMACTRL_RXLODA; // load DMA
    }
    RESTORE_INTERRUPTS();
  }
}

/** @brief load TX and RX DMA
 */
static void stageSpiTransaction(void)
{
  // set TX packet header values
  uint16_t payloadLen = setTxHeader();

  //Configure DMA TX channel
  SC2->DMACTRL = SC_DMACTRL_TXDMARST;
  SC2->TXBEGA = (uint32_t) txBuffer.buffer + txBuffer.head;

  /* include tail padding.  this means that the padded bytes will be whatever
   * comes next in the buffer, possibly useful data, possibly garbage.  we're
   * relying on the host respecting the length byte of the header to not
   * process these
   */
  int packetLen = NCP_SPI_PKT_HEADER_LEN + payloadLen + NCP_SPI_PKT_TAIL_LEN;

  SC2->DATA = 0xFF; // emlipari-183: Prepend sacrificial Tx pad byte
  if (txBuffer.head + packetLen <= NCP_SPI_BUFSIZE) {
    SC2->TXENDA = (uint32_t) txBuffer.buffer + txBuffer.head + packetLen - 1;

    // load DMA
    SC2->DMACTRL = SC_DMACTRL_TXLODA;
  } else {
    SC2->TXENDA = (uint32_t) txBuffer.buffer + NCP_SPI_BUFSIZE - 1;

    // handle other half of the ring
    SC2->TXBEGB = (uint32_t) txBuffer.buffer;
    SC2->TXENDB = (uint32_t) txBuffer.buffer
                  + packetLen
                  - (NCP_SPI_BUFSIZE - txBuffer.head)
                  - 1;

    // load DMA
    SC2->DMACTRL = SC_DMACTRL_TXLODA | SC_DMACTRL_TXLODB;
  }
}

void wipeAndRestartSpi(void)
{
  wipeSpi();
  restartSpiRx();
}

/** add some data to the TX queue
 * @param data  the data to send
 * @param length  the number of bytes in \cdata
 * @return the number of bytes actually enqueued (might be less than requested
 * depending on available buffer space.  buffer space can be checked with
 * halHostTxSpaceAvailable())
 * @note this function is non-reentrant
 */
uint16_t halHostEnqueueTx(const uint8_t* data, uint16_t length)
{
  // if we ever want to support datagram-style use of this protocol, we would
  // want to return 0 here if there is already a packet in the pipe instead of
  // growing said packet

  uint16_t chunkStart;

  // figure out how much space we have, and reserve it
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    length = MIN(length, halHostTxSpaceAvailable());
    chunkStart = txBuffer.tail;
    txBuffer.tail = (txBuffer.tail + length) % NCP_SPI_BUFSIZE;
    RESTORE_INTERRUPTS();
  }

  if (length == 0) {
    return 0;
  }

  uint16_t chunkLength = length;
  uint16_t dataOffset = 0;

  if (chunkStart + chunkLength >= NCP_SPI_BUFSIZE) { // it's going to wrap
    MEMMOVE(txBuffer.buffer + chunkStart, data, NCP_SPI_BUFSIZE - chunkStart);
    chunkLength -= NCP_SPI_BUFSIZE - chunkStart;
    dataOffset = NCP_SPI_BUFSIZE - chunkStart;
    chunkStart = 0;
  }

  MEMMOVE(txBuffer.buffer + chunkStart, data + dataOffset, chunkLength);

  // store the length, which is the signal to the consumer that the data is
  // really available
  {
    DECLARE_INTERRUPT_STATE;
    DISABLE_INTERRUPTS();
    txBuffer.length += length;
    RESTORE_INTERRUPTS();
  }

  halHostCallback(true);

  return length;
}

static void halHostSerialPowerupForReal(void)
{
  //block until an active transfer is complete in order not to confuse
  //Host by starting to receive/send in the middle of a transfer.
  //N.B. Here we rely on BOARD_HEADER's nSSEL GPIO configuration
  halResetWatchdog();
  while (nSSEL_IS_LOW) {
  }
  halResetWatchdog();

  ////---- Configure SPI ----////
  wipeAndRestartSpi();

  ////---- Configure basic SPI Pins: MOSI, MISO, SCLK and nSSEL ----////
  // To avoid glitches, refresh configuration for all 4 pins in PACFGL at once.
  GPIO->P[0].CFGL = ((_GPIO_P_CFGL_Px0_IN      << (4 * (MOSI_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_OUT_ALT << (4 * (MISO_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_IN      << (4 * (SCLK_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_IN_PUD  << (4 * (nSSEL_BIT & 3))));
  PULLUP_nSSEL();

  ////---- Configure nWAKE interrupt (PB6/IRQB) ----////
  //start from a fresh state just in case
  NVIC->ICER[0] = nWAKE_INT;                 //disable triggering
  nWAKE_INTCFG = (GPIOINTMOD_DISABLED << _EVENT_GPIO_CFGA_MOD_SHIFT);
  //Configure nWAKE pin
  CFG_nWAKE(_GPIO_P_CFGL_Px0_IN_PUD);              //input with pullup
  PULLUP_nWAKE();
  //Enable Interrupts
  EVENT_GPIO->FLAG = nWAKE_GPIOFLAG;          //clear stale interrupts
  NVIC->ICPR[0] = nWAKE_INT;
  NVIC->ISER[0] = nWAKE_INT;
  nWAKE_INTCFG =  (0 << _EVENT_GPIO_CFGB_FILT_SHIFT)       //no filter
                 | (GPIOINTMOD_FALLING_EDGE << _EVENT_GPIO_CFGA_MOD_SHIFT);

  ////---- Configure nSSEL interrupt (PA3/IRQC) ----////
  NVIC->ICER[0] = nSSEL_INT;                 //disable triggering
  nSSEL_INTCFG = (GPIOINTMOD_DISABLED << _EVENT_GPIO_CFGA_MOD_SHIFT);
  nSSEL_IRQSEL = nSSEL_IRQSEL_MASK;       //assign PA3 pin, nSSEL, to IRQC
  //Enable Interrupts
  EVENT_GPIO->FLAG = nSSEL_GPIOFLAG;          //clear stale interrupts
  NVIC->ICPR[0] = nSSEL_INT;
  NVIC->ISER[0] = nSSEL_INT;
  nSSEL_INTCFG = (0 << _EVENT_GPIO_CFGB_FILT_SHIFT)      //no filter
                 | (GPIOINTMOD_BOTH_EDGES << _EVENT_GPIO_CFGA_MOD_SHIFT);

  ////---- Configure nHOST_INT output (PB4) ----////
  SET_nHOST_INT();
  CFG_nHOST_INT(_GPIO_P_CFGL_Px0_OUT);

#ifdef ENABLE_NSIMRST
  // For debugging, configure nSIMRST (PB0/IRQA) //
  NVIC->ICER[0] = nSIMRST_INT;               //disable triggering
  nSIMRST_INTCFG = (GPIOINTMOD_DISABLED << _EVENT_GPIO_CFGA_MOD_SHIFT);
  CFG_nSIMRST(_GPIO_P_CFGL_Px0_IN_PUD);            //input with pull-up
  PULLUP_nSIMRST();
  EVENT_GPIO->FLAG = nSIMRST_GPIOFLAG;        //clear stale interrupts
  NVIC->ICPR[0] = nSIMRST_INT;
  NVIC->ISER[0] = nSIMRST_INT;               //enable interrupt
  nSIMRST_INTCFG = (0 << _EVENT_GPIO_CFGB_FILT_SHIFT)      //no filter
                   | (GPIOINTMOD_FALLING_EDGE << _EVENT_GPIO_CFGA_MOD_SHIFT);
#endif
}

void halHostSerialPowerup(void)
{
  // Called from BOARD_HEADER's halInternalPowerUpBoard()
  // Do nothing - SPI initialization is deferred to Tick time
}

void halHostSerialInit(void)
{
  // hack to get around not being able to init structs with array members at
  // static initialization time in a portable way using our version of C
  txBuffer.tail = NCP_SPI_PKT_HEADER_LEN;
  txBuffer.length = NCP_SPI_PKT_HEADER_LEN;

  spipFlagWakeFallingEdge = false; //start with no edge on nWAKE
  spipFlagRxComplete = false;
  spipFlagIgnoreRx = false;

  halHostSerialPowerupForReal();
}

#ifdef ENABLE_NSIMRST
// nSIMRST falling edge interrupt replaces nRESET
void halIrqAIsr(void)
{
  halReboot();
}

#endif

void halHostSerialPowerdown(void)
{
  //This is called with interrupts off
  //wait for any transfer in progress is complete
  //and ensure its pending ints get handled before sleeping
  halResetWatchdog();
  do {
    if ( (NVIC->ISPR[0] & BIT32(SC2_IRQn)) == BIT32(SC2_IRQn) ) {
      halSc2Isr();
    }
  } while (nSSEL_IS_LOW);
  halResetWatchdog();
  // Force MISO high so if host starts a new transaction
  // they get 0xFF bupkis
  // But don't shut down SC2 yet as we need its pending ints
  // to process any just-received transaction
  GPIO->P[0].SET  = (GPIOOUT_PULLUP << (MISO_BIT & 7));
  GPIO->P[0].CFGL = ((_GPIO_P_CFGL_Px0_IN      << (4 * (MOSI_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_IN_PUD  << (4 * (MISO_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_IN      << (4 * (SCLK_BIT  & 3)))
                     | (_GPIO_P_CFGL_Px0_IN_PUD  << (4 * (nSSEL_BIT & 3))));
  if (NVIC->ISPR[0] & nSSEL_INT) {
    halIrqCIsr();
  }
  // Disable SC2 and nSSEL interrupts -- only want nWAKE firing on wakeup
  NVIC->ICER[0]  = (BIT32(SC2_IRQn) | nSSEL_INT);
  // Use "big hammer" to shut down SPI (deasserting SPI_INITED)
  SC2->MODE = SC_MODE_MODE_DISABLED;
  NVIC->ICPR[0] = (BIT32(SC2_IRQn) | nSSEL_INT); // safety
}

/**
 * When the upper application has a callback it needs to deliver to the Host, it
 * calls halHostCallback() at will with haveData set to true. The HAL will
 * indicate to the Host through the nHOST_INT singal that there is a callback
 * pending. The EZSP application must make another call with haveData set to
 * false when there are no more callbacks pending.  The SPIP is responsible
 * for latching this call, timing actual nHOST_INT manipulation, and
 * multiplexing it in with SPIP generated assertions.
 *
 * @param haveData: true indicates there is a callback and the SPIP should
 * schedule nHOST_INT assertion.  false says the SPIP and deassert nHOST_INT.
 */
void halHostCallback(bool haveData)
{
  if (haveData) {
    //only assert nHOST_INT if we are outside a wake handshake (wake==1)
    //and outside of a current transaction (nSSEL=1)
    //if inside a wake handshake or transaction, delay asserting nHOST_INT
    //until the SerialTick
    if ( nWAKE_IS_HIGH && nSSEL_IS_HIGH ) {
      CLR_nHOST_INT();
    }
    spipFlagIdleHostInt = false;
  } else {
    spipFlagIdleHostInt = true;
  }
}

void halHostSerialTickFullDuplex()
{
  uint8_t bytesToProcess = 0;
  static uint8_t consumed = 0;

  if (spipFlagIgnoreRx) {
    restartSpiRx();
  }

  if (spipFlagRxComplete) {
    if (rxPacketHasHeader(activeRxBuffer, spipBytesReceived)) {
      bytesToProcess = MIN(spipBytesReceived
                           - (activeRxBuffer->payload - activeRxBuffer->buffer),
                           activeRxBuffer->packet[NCP_SPI_LENGTH_INDEX]);
      consumed += serialCopyFromRx(activeRxBuffer->payload + consumed,
                                   bytesToProcess - consumed);
    } else {
      // Can't find any payload data to process -- this is probably bad
      // because we might have ACKed what the host sent, but best we can
      // do is throw it away and hope higher layers realize something is
      // missing and initiate appropriate recovery.
      consumed = bytesToProcess;
    }

    if (consumed < bytesToProcess) {
    } else {
      // free the buffer we were processing
      consumed = 0;
      bytesToProcess = 0;
      restartSpiRx();
    }
  }
}

void halHostSerialTick(void)
{
  if (!SPI_INITED) {
    // SPI port (re)initialization is deferred to Tick time
    // so app can choose to sleep/wake without bringing up SPI
    // host communications until it needs to
    halHostSerialPowerupForReal();
    assert(SPI_INITED);
  }

  if (spipFlagWakeFallingEdge) { //detected falling edge on nWAKE, handshake
    CLR_nHOST_INT();
    while ( nWAKE_IS_LOW ) {
      halResetWatchdog();                        /*EMHAL-1074*/
    }
    SET_nHOST_INT();
    spipFlagWakeFallingEdge = false;
    //The wake handshake is complete, but spipFlagIdleHostInt is saying
    //that there is a callback pending.
    if (!spipFlagIdleHostInt) {
      spipFlagIdleHostInt = true;
      halCommonDelayMicroseconds(50); //delay 50us so Host can get ready
      CLR_nHOST_INT();  //indicate the pending callback
    }
  } else {
    // perform processing specific to one mode or the other
    halHostSerialTickFullDuplex();
  }

  emLoadSerialTx();
}

//All SPI operation interrupts come in here
void halSc2Isr(void)
{
  if (EVENT_SC2->FLAG & EVENT_SC12_FLAG_RXVAL) {
    EVENT_SC2->FLAG = EVENT_SC12_FLAG_RXVAL;   //clear byte received interrupt
    SET_nHOST_INT();  //by clocking a byte, the Host ack'ed nHOST_INT
    //spipFlagIdleHostInt = true;
    EVENT_SC2->CFG &= ~EVENT_SC12_FLAG_RXVAL;   //disable byte received interrupt
  }
  // TODO error on interrupts that shouldn't be happening?
}

// Defined in stack/mac/802.15.4/wakeup.c for ZIP.
// TODO: currently used by the hal to wakeup the ip-modem via SPI.
extern void emWakeupStopSleeping(void);

// stub for when we don't have a wakeup function to call in the IrqB ISR
WEAK(void emWakeupStopSleeping(void))
{
}

//nWAKE signal comes in on PB6/IRQB (falling edge-triggered)
void halIrqBIsr(void)
{
  // ack int before read to avoid potential of missing interrupt
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQB;

  // Only trigger wake handshake if we were truly asleep
  if (!SPI_INITED) {
    //A wakeup handshake should be performed in response to a falling edge on
    //the WAKE line. The handshake should only be performed on a SerialTick.
    spipFlagWakeFallingEdge = true;

    // notify the stack that we should wake up
    emWakeupStopSleeping();
  }
}

//nSSEL signal comes in on PA3/IRQC (triggered on both edges)
//May be jumpered to PB3 for compatibility with the EM260, but the input
//at PB3 is not used by the spi protocol.
void halIrqCIsr(void)
{
  EVENT_GPIO->FLAG = EVENT_GPIO_FLAG_IRQC;

  if (nSSEL_IS_HIGH) { // probably rising edge
    uint16_t rxCnt = SC2->RXCNTA;
    int32_t txCnt;

    if (SC2->DMASTAT & SC_DMASTAT_TXACTA) {
      // if buffer A is still active, the length is TXCNT, adjusted for the
      // size of the FIFO
      txCnt = SC2->TXCNT - NCP_SPI_PKT_TAIL_LEN;
    } else if (EVENT_SC2->FLAG & EVENT_SC12_FLAG_TXULDA) {
      uint32_t txBegA = SC2->TXBEGA; // Locals avoid compiler volatile warnings
      uint32_t txEndA = SC2->TXENDA; // These regs aren't really volatile here
      if (EVENT_SC2->FLAG & EVENT_SC12_FLAG_TXULDB) {
        // if buffer A and B are both unloaded, the length is len(A) + len(B),
        // adjusted for FIFO
        uint32_t txBegB = SC2->TXBEGB; // Locals avoid compiler volatile warnings
        uint32_t txEndB = SC2->TXENDB; // These regs aren't really volatile here
        txCnt = (txEndA - txBegA) + 1
                + (txEndB - txBegB) + 1
                - NCP_SPI_PKT_TAIL_LEN;
      } else if (SC2->DMASTAT & SC_DMASTAT_TXACTB) {
        // if buffer A is unloaded and buffer B is active, the length is len(A)
        // + TXCNT, adjusted for the size of the FIFO
        txCnt = (txEndA - txBegA) + 1 + SC2->TXCNT - NCP_SPI_PKT_TAIL_LEN;
      } else {
        // if buffer A is unloaded and buffer B was never loaded, length is
        // len(A) adjusted for FIFO
        txCnt = (txEndA - txBegA) + 1 - NCP_SPI_PKT_TAIL_LEN;
      }
    } else {
      // TX was never loaded??
      txCnt = 0;
    }

    wipeSpi(); // clear out any leftover junk from this transaction

    /* normally nHOST_INT is idled in the RXVALID Isr, but if we never loaded
     * the RX buffer, the RXVALID interrupt will never fire.  a very short
     * response could also cause us to handle this interrupt before RXVALID
     */
    SET_nHOST_INT();

    if (spipFlagNcpReset && txCnt >= 1) { // we sent the byte indicating a reset
      spipFlagNcpReset = false;
    }

    if (!spipFlagRxComplete && !spipFlagIgnoreRx) { // we're trying to receive
      if ((txBuffer.buffer[txBuffer.head] & NCP_SPI_PKT_CMD_NAK) || txCnt < 1) {
        /* we get here for one of two reasons: we told the host we were NAKing,
         * or the host assumes we were NAKing because we never sent anything to
         * tell it otherwise.  In the former case, this will only happen if the
         * RX buffer was loaded during the transaction.  Either way, we need to
         * discard whatever we received, since the host is going to send it
         * again.
         */
        restartSpiRx();
      } else {
        spipFlagRxComplete = true;
        spipBytesReceived = rxCnt; // record how many bytes we received
      }
    }

    // dequeue the data we just sent
    dequeueTx(txCnt);

    // if there's still data to send, indicate that to the host
    halHostCallback(txBuffer.length > NCP_SPI_PKT_HEADER_LEN);
  } else { // probably falling edge
    stageSpiTransaction();
  }
}
