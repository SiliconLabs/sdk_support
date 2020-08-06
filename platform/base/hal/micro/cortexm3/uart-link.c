/***************************************************************************//**
 * @file
 * @brief low-level driver for sending typed blocks of data on 35x
 * or in simulation.
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
#include "stack/core/ember-stack.h"
#include "hal/hal.h"
#include "hal/micro/uart-link.h"
#include "hal/micro/generic/ash-v3.h"

#ifdef EMBER_SCRIPTED_TEST
  #define DEBUG_PRINTF(...) emLogLine(UNIT_TEST, " > " __VA_ARGS__)
#else
  #define DEBUG_PRINTF(...) emberDebugPrintf(__VA_ARGS__)
#endif

#ifdef EMBER_TEST
  #include "../../../../Device/SiliconLabs/simulation/Include/em_device.h"
  #include "uart-sim.h"
  #define SET_DMACTRL(v) simSetDmaCtrl(v)
  #define TX_STOPPED() (false)
#else  // EMBER_TEST not defined
  #define simTick(x)
  #define SET_DMACTRL(v) (SC1->DMACTRL) = (v)
  #define TX_STOPPED() ((GPIO->P[1].IN) & GPIO_P_IN_Px3) // nCTS deasserted (high)
#endif // #ifdef EMBER_TEST

#define SET_TXD_GPIO(gpioCfg, state) do {                        \
    (state) ? (GPIO->P[1].SET = GPIO_P_SET_Px1)                  \
    : (GPIO->P[1].CLR = GPIO_P_CLR_Px1);                         \
    GPIO->P[1].CFGL = (GPIO->P[1].CFGL & ~_GPIO_P_CFGL_Px1_MASK) \
                      | ((gpioCfg) << _GPIO_P_CFGL_Px1_SHIFT);   \
} while (0)

#define BUFFER_SIZE 100
#define XON_RESEND_COUNT 5
#define XON_XOFF_DELAY_MS 100

static uint8_t rxDmaBufferA[BUFFER_SIZE];
static uint8_t rxDmaBufferB[BUFFER_SIZE];
static uint8_t rxConsumedA;
static uint8_t rxConsumedB;

#ifdef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
typedef enum {
  NO_XOFF_STATE = 0,
  SEND_XOFF     = 1,
  XOFF_SENT     = 2
} XOffState_e;

typedef uint8_t XOffState;

static uint8_t xOnDmaBuffer[1];
static uint8_t xOffDmaBuffer[1];
static uint16_t nextXOnTime = 0;
static uint8_t xOnCount;
static XOffState xOffState;

static bool maybeSendXOn(void)
{
  if (xOffState == XOFF_SENT) {
    xOffState = NO_XOFF_STATE;
    xOnCount = XON_RESEND_COUNT;
  }

  if (xOnCount > 0
      && halHostUartTxIdle()
      && (xOnCount == XON_RESEND_COUNT
          || timeGTorEqualInt16u(halCommonGetInt16uMillisecondTick(),
                                 nextXOnTime))) {
    halHostUartLinkTx(xOnDmaBuffer, sizeof(xOnDmaBuffer));
    xOnCount--;
    nextXOnTime = halCommonGetInt16uMillisecondTick() + XON_XOFF_DELAY_MS;
    return true;
  }

  return false;
}

static void sendXOn(void)
{
  xOnCount = XON_RESEND_COUNT;
  maybeSendXOn();
}

static bool maybeSendXOff(void)
{
  if (halHostUartTxIdle()
      && xOffState == SEND_XOFF) {
    halHostUartLinkTx(xOffDmaBuffer, sizeof(xOffDmaBuffer));
    xOffState = XOFF_SENT;
    return true;
  }

  return false;
}

#else // EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
static bool maybeSendXOn(void)
{
  return false;
}

static bool maybeSendXOff(void)
{
  return false;
}

#endif

enum {
  FLAG_NONE     = 0,
  FLAG_INITED   = (1 << 0),  // Driver was inited by a user
};

static uint8_t driverFlags = FLAG_NONE;
static volatile bool rxError = false;

#define TX_BUSY() ((SC1->UARTSTAT & (SC_UARTSTAT_UARTTXIDLE     \
                                     | SC_UARTSTAT_UARTTXFREE)) \
                   != (SC_UARTSTAT_UARTTXIDLE | SC_UARTSTAT_UARTTXFREE))
#if 0 //NOTYET - maybe needed for pathological situations?
static uint16_t txLastCnt = 0;
#define TX_STUCK() ((txLastCnt == SC1->TXCNT) \
                    ? true : ((txLastCnt = SC1->TXCNT), false))
#else//!
#define TX_STUCK() true
#endif//
static uint32_t txLastProbe = 0;
#define HOST_IS_AWAKE() do {                           \
    txLastProbe = halCommonGetInt32uMillisecondTick(); \
} while (0)

#define INT_RX_ERRORS  (EVENT_SC12_FLAG_RXOVF    \
                        | EVENT_SC12_FLAG_FRMERR \
                        | EVENT_SC12_FLAG_PARERR)
#define STAT_RX_ERRORS (SC_UARTSTAT_UARTRXOVF    \
                        | SC_UARTSTAT_UARTFRMERR \
                        | SC_UARTSTAT_UARTPARERR)

#define HOST_WAKEUP_RETRY_TIMEOUT_MS 250 // Retry host wakeup after this many ms
#define HOST_WAKEUP_TXD_LO_TIME_US   121 // Time to hold TxD low for 'break'
// The value 121 us comes from (1000000 us/sec / 115200 bits/sec) = 8.68 us/bit
// * (1 start + 8 data + 2 stop + 3 safety bits) = 121.52.

void halHostSerialInit(void)
{
#if     (defined(UNIX_HOST) || defined(UNIX_HOST_SIM) || defined(EMBER_TEST))
  SC1->UARTPER = 104; // 115200 baud
  SC1->UARTFRAC = 0; // 115200 baud
#else//!(defined(UNIX_HOST) || defined(UNIX_HOST_SIM))
  halInternalUartSetBaudRate(1, 115200);
#endif//(defined(UNIX_HOST) || defined(UNIX_HOST_SIM))
  SC1->UARTCFG = (SC_UARTCFG_UART8BIT | SC_UARTCFG_UARTAUTO); // 8-n-1

#ifndef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
  SC1->UARTCFG |= SC_UARTCFG_UARTFLOW; // RTS+CTS
#endif

  SET_DMACTRL(SC_DMACTRL_TXDMARST | SC_DMACTRL_RXDMARST);
  SC1->RXBEGA = (uint32_t)rxDmaBufferA;
  SC1->RXENDA = (uint32_t)(rxDmaBufferA + sizeof(rxDmaBufferA) - 1);
  SC1->RXBEGB = (uint32_t)rxDmaBufferB;
  SC1->RXENDB = (uint32_t)(rxDmaBufferB + sizeof(rxDmaBufferB) - 1);
  SET_DMACTRL(SC_DMACTRL_RXLODA | SC_DMACTRL_RXLODB);
  rxConsumedA = 0;
  rxConsumedB = 0;
  SC1->MODE = SC_MODE_MODE_UART; // Do this before clearing 'stale' ints
  EVENT_SC1->CFG = INT_RX_ERRORS;

#ifdef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
  // EVENT_SC12_CFG_RXULDA = DMA receive buffer A unloaded interrupt enable
  // EVENT_SC12_CFG_RXULDB = DMA receive buffer B unloaded interrupt enable
  // EVENT_SC12_CFG_TXULDA = DMA transmit buffer A unloaded interrupt enable
  // EVENT_SC12_CFG_TXULDB = DMA transmit buffer B unloaded interrupt enable
  EVENT_SC1->CFG |= EVENT_SC12_CFG_RXULDA
                    | EVENT_SC12_CFG_RXULDB
                    | EVENT_SC12_CFG_TXULDA
                    | EVENT_SC12_CFG_TXULDB;
#endif

  EVENT_SC1->FLAG = 0xFFFF;
  NVIC_ClearPendingIRQ(SC1_IRQn); // Clear a stale top-level interrupt
  // Now enable OUT_ALT on TxD, avoiding any glitches while SC1->MODE was off
  SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT_ALT, 1);
  rxError = false;
  driverFlags |= FLAG_INITED;
  NVIC_EnableIRQ(SC1_IRQn);

#ifdef EMBER_TEST
  emInitializeUartSim();
#endif

#ifdef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
  xOnDmaBuffer[0] = ASH_XON;
  xOffDmaBuffer[0] = ASH_XOFF;
  sendXOn();
#endif
}

static uint32_t scTxBegA; // For proper TX completion notification across sleep

void halInternalPowerDownUart(void)
{
  //This is called with interrupts off
  //wait for any output in progress to complete
  if ((driverFlags & FLAG_INITED) && (SC1->MODE == SC_MODE_MODE_UART)) {
   #ifndef EMBER_TEST // Not simulated yet
    halResetWatchdog();
    // Spin to let current Tx DMA finish
    while (TX_BUSY()) {
      // If Host deasserts nCTS, punt and abort the pending Tx; don't wait
      if (TX_STOPPED()) {
        break;
      }
    }
    halResetWatchdog();
   #endif//EMBER_TEST // Not simulated yet
    scTxBegA = SC1->TXBEGA; // Save TX state, potentially incomplete
    // Disable OUT_ALT on TxD, avoiding any glitches while SC1->MODE is off
    SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT, 1);
    // Use "big hammer" to shut down UART
    SC1->MODE = SC_MODE_MODE_DISABLED;
    EVENT_SC1->CFG = 0;          // Disable all SC1 ints
    EVENT_SC1->FLAG = 0xFFFF;    // Clear out any pending SC1 interrupts
    NVIC_ClearPendingIRQ(SC1_IRQn); // safety so this doesn't fire after waking
  }
}

void halInternalPowerUpUart(void)
{
  // Called upon waking -- restart UART
  if ((driverFlags & FLAG_INITED) != 0
      && (SC1->MODE == SC_MODE_MODE_DISABLED)) {
    halHostSerialInit();
    SC1->TXBEGA = scTxBegA; // Restore TX state, which should have completed
    (void) TX_STUCK(); // Update notion of progress for host wake
    txLastProbe = (uint32_t) -HOST_WAKEUP_RETRY_TIMEOUT_MS; // Allow for quick host wake
  }
}

void halHostFlushBuffers(void)
{
  // This routine being called indicates upper layers have gotten out of sync
  // or lost track of host, and are trying to get things back in order.
  // Stop Rx until reinited
  SET_DMACTRL(SC_DMACTRL_TXDMARST | SC_DMACTRL_RXDMARST);
  (void) TX_STUCK(); // Update notion of progress for host wake
  // Disable OUT_ALT on TxD, avoiding any glitches while SC1->MODE is off
  SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT, 1);
  SC1->MODE = SC_MODE_MODE_DISABLED; // Needed to clear out the Tx FIFO too
  EVENT_SC1->CFG = 0;
  EVENT_SC1->FLAG = 0xFFFF;
  SC1->MODE = SC_MODE_MODE_UART; // reactivate UART afresh
  SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT_ALT, 1);  // Return to normal UART operation
  //FIXME: Would like to just do halHostSerialInit() here but uppers not ready
  SC1->TXBEGA = _SC_TXBEGA_RESETVALUE;
}

static void hostWakeProbe(void)
{
  // Check if host seems asleep and needs a wake probe
  // Basically, if we:
  // - have something queued to send
  // - nCTS is deasserted (we're flow controlled so can't send it)
  // - we look stuck (TX DMA isn't progressing) -- optional
  // and we've been in this situation for at least HOST_WAKEUP_RETRY_TIMEOUT_MS
  // then issue a probe consisting of an out-of-band BREAK to trigger not just
  // a transition on TxD signal but one that should result in a framing error
  // (not something misinterpreted as valid data) if the host is actually awake
  // and just being snooty with nCTS.
  // N.B. It's important to have TX_STUCK() first in below condition because
  //      it might need to update state on every call to monitor progress;
  //      That shouldn't be conditionalized on TX_BUSY() or TX_STOPPED().
  if (TX_STUCK() && TX_BUSY() && TX_STOPPED()) {
    if (elapsedTimeInt32u(txLastProbe, halCommonGetInt32uMillisecondTick())
        >= HOST_WAKEUP_RETRY_TIMEOUT_MS) {
      HOST_IS_AWAKE(); // or so we hope it will be soon
      SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT, 0);      // Trigger a break on TxD
      halCommonDelayMicroseconds(HOST_WAKEUP_TXD_LO_TIME_US);
      SET_TXD_GPIO(_GPIO_P_CFGz_Pxy_OUT_ALT, 1);  // Return to normal UART operation
      // TxD should stay high until host asserts nCTS
    }
  } else { // No TX, or TX is allowed to flow or flowing - deem host awake
    HOST_IS_AWAKE();
  }
}

static void checkRx(uint32_t dmaCtrl,
                    uint32_t mask,
                    uint32_t value,
                    uint32_t begin,
                    uint8_t *consumed,
                    uint16_t bufferSize)
{
  if ((dmaCtrl & mask) == value && *consumed < bufferSize) {
    //
    // eat ASH input
    //

    uint16_t length = bufferSize - *consumed;
    if (length > 0) {
      HOST_IS_AWAKE(); // Host speaketh!  Deem it awake
    }

    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t ashInput[BUFFER_SIZE] = { 0 };

    // strip out XON and XOFF bytes before handing the input to ASH
    for (i = *consumed; i < *consumed + length; i++) {
      uint8_t byte = *((uint8_t *)(begin + i));
      bool useByte = true;

      // if we use software flow control, strip out XON and XOFF bytes before
      // handing the input to ASH
#ifdef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
      if (byte == ASH_XON || byte == ASH_XOFF) {
        useByte = false;
      }
#endif

      if (useByte) {
        ashInput[j] = byte;
        j++;
      }
    }

    *consumed += emProcessAshRxInput(ashInput, j);

    if (value == 0 && *consumed == bufferSize) {
      SET_DMACTRL(mask);
      *consumed = 0;
    }
  }
}

bool halHostUartTxIdle(void)
{
  return (!TX_BUSY());
}

void halHostUartLinkTx(const uint8_t *data, uint16_t length)
{
  SC1->TXBEGA = (uint32_t)data;
  SC1->TXENDA = (uint32_t)(data + length - 1);
  SET_DMACTRL(SC_DMACTRL_TXLODA);
  (void) TX_STUCK(); // Update notion of progress for host wake
}

void halHostSerialTick(void)
{
  uint32_t dmaControl;
  uint16_t rxCountA;
  uint16_t rxCountB;
  emLogLine(UNIT_TEST, "uartLinkTick (%X)", SC1->DMACTRL);
  simTick(true);
  hostWakeProbe(); // Tickle host if we've been stuck for too long

  // rxError is set by halSc1Isr and cleared by halHostSerialInit.
  if (rxError) {
    DEBUG_PRINTF("rx error");

#if !defined(EMBER_STACK_CONNECT)
    emberCounterHandler(EMBER_COUNTER_UART_IN_FAIL, 1);
#endif // EMBER_STACK_CONNECT

    rxError = false;
    return;
  }

  do {
    /* this do-while should guard against buffer A unloading in between the
     * reading of RXCNTA and RXCNTB, which would result in dropping some bytes
     * and possibly reenabling DMA in the wrong order
     */
    dmaControl = SC1->DMACTRL;
    rxCountA = SC1->RXCNTA;
    rxCountB = SC1->RXCNTB;
  } while (dmaControl != SC1->DMACTRL);

  if ((dmaControl & SC_DMACTRL_TXLODA) == 0
      && SC1->TXBEGA != _SC_TXBEGA_RESETVALUE) {
    // TX is complete
    SC1->TXBEGA = _SC_TXBEGA_RESETVALUE;
    emAshNotifyTxComplete();
  }

  maybeSendXOn();
  maybeSendXOff();

  /* TODO rdm 5/16/2013 I'd really like to clean this up by "inlining" checkRx,
   * which allows it to be simplified for each of these four cases.  There is
   * probably some common code that can still be in a "process buffer" helper
   * function, but the logic should be here.
   */
  checkRx(dmaControl, SC_DMACTRL_RXLODA, 0,
          SC1->RXBEGA, &rxConsumedA, sizeof(rxDmaBufferA));
  checkRx(dmaControl, SC_DMACTRL_RXLODB, 0,
          SC1->RXBEGB, &rxConsumedB, sizeof(rxDmaBufferB));
  checkRx(dmaControl, SC_DMACTRL_RXLODA, SC_DMACTRL_RXLODA,
          SC1->RXBEGA, &rxConsumedA, rxCountA);
  checkRx(dmaControl, SC_DMACTRL_RXLODB, SC_DMACTRL_RXLODB,
          SC1->RXBEGB, &rxConsumedB, rxCountB);
}

void halSc1Isr(void)
{
  if ((EVENT_SC1->FLAG & INT_RX_ERRORS) != 0) {
    EVENT_SC1->FLAG = INT_RX_ERRORS; // clear interrupt flag
    // Ignore serial errors when in FRAMING mode waiting for frame sync byte
    // e.g. right after a wakeup when UART might restart in midst of Rx data.
    if (isAshActive()) {
      rxError = true;
    }
  }

#ifdef EMBER_APPLICATION_USES_SOFTWARE_FLOW_CONTROL
  // if RX buffer A or RX buffer B are full, then we send an XOFF
  if ((EVENT_SC1->FLAG & EVENT_SC12_FLAG_RXULDA) != 0) {
    // RX buffer A is full, ack
    EVENT_SC1->FLAG = EVENT_SC12_FLAG_RXULDA;
    xOffState = SEND_XOFF;
  }

  if ((EVENT_SC1->FLAG & EVENT_SC12_FLAG_RXULDB) != 0) {
    // RX buffer B is full, ack
    EVENT_SC1->FLAG = EVENT_SC12_FLAG_RXULDB;
    xOffState = SEND_XOFF;
  }

  if ((EVENT_SC1->FLAG & EVENT_SC12_FLAG_TXULDA) != 0) {
    // we're done TXing buffer A, ack
    EVENT_SC1->FLAG = EVENT_SC12_FLAG_TXULDA;
  }

  if ((EVENT_SC1->FLAG & EVENT_SC12_FLAG_TXULDB) != 0) {
    // we're done TXing buffer B, ack
    EVENT_SC1->FLAG = EVENT_SC12_FLAG_TXULDB;
  }

  maybeSendXOff();
  maybeSendXOn();
#endif
}

uint16_t halInternalSc1Isr(uint16_t interrupt, uint16_t pcbContext)
{
  return interrupt;
}
