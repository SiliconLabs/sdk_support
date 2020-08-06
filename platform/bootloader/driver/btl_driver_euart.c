/***************************************************************************//**
 * @file
 * @brief Universal asynchronous receiver/transmitter (EUSART)
 *        driver for the Silicon Labs Bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "config/btl_config.h"

#if (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_EUART0)

#include "btl_driver_uart.h"
#include "btl_driver_delay.h"
#include "api/btl_interface.h"
#include "btl_driver_util.h"

#include "em_cmu.h"
#include "em_eusart.h"
#include "em_gpio.h"
#include "em_ldma.h"

#include "plugin/debug/btl_debug.h"

#if BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_EUART0
#define BTL_DRIVER_EUSART                      EUART0
#define BTL_DRIVER_EUSART_CLOCK                cmuClock_EUART0
#define BTL_DRIVER_EUSART_LDMA_TXFL_SIGNAL     (LDMAXBAR_CH_REQSEL_SIGSEL_EUART0TXFL | LDMAXBAR_CH_REQSEL_SOURCESEL_EUART0)
#define BTL_DRIVER_EUSART_LDMA_RXFL_SIGNAL     (LDMAXBAR_CH_REQSEL_SIGSEL_EUART0RXFL | LDMAXBAR_CH_REQSEL_SOURCESEL_EUART0)
#endif

#define BTL_DRIVER_EUSART_LDMA_RX_CHANNEL     0
#define BTL_DRIVER_EUSART_LDMA_TX_CHANNEL     1

// ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Configuration validation
#if HAL_SERIAL_APP_BAUD_RATE < 100
#warning "UART baud rate is very low, consider increasing speed"
#endif
#if BTL_DRIVER_UART_RX_BUFFER_SIZE < 8
#error "UART RX buffer too small"
#endif
#if BTL_DRIVER_UART_TX_BUFFER_SIZE < 8
#error "UART TX buffer too small"
#endif
#if (BTL_DRIVER_UART_RX_BUFFER_SIZE % 2) != 0
#error "UART RX buffer size is not even"
#endif

// ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Static variables

/// Flag to indicate hardware is up and running
static bool    initialized = false;
/// Receive buffer (forced to even size).
/// LDMA will pingpong between two halves of this buffer.
static uint8_t rxBuffer[BTL_DRIVER_UART_RX_BUFFER_SIZE];
/// Transmit buffer for LDMA use.
static uint8_t txBuffer[BTL_DRIVER_UART_TX_BUFFER_SIZE];
/// Amount of bytes in the current transmit operation
static size_t  txLength;

/// Index into the receive buffer indicating which byte is due to be read next.
static size_t  rxHead;

/// LDMA channel configuration triggering on free space in UART transmit FIFO
static const LDMA_TransferCfg_t ldmaTxTransfer = LDMA_TRANSFER_CFG_PERIPHERAL(
  BTL_DRIVER_EUSART_LDMA_TXFL_SIGNAL
  );
/// LDMA channel configuration triggering on available byte in UART receive FIFO
static const LDMA_TransferCfg_t ldmaRxTransfer = LDMA_TRANSFER_CFG_PERIPHERAL(
  BTL_DRIVER_EUSART_LDMA_RXFL_SIGNAL
  );

/// LDMA transfer for copying transmit buffer to UART TX FIFO
static LDMA_Descriptor_t ldmaTxDesc = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(
  txBuffer,
  &(BTL_DRIVER_EUSART->TXDATA),
  0
  );

static const LDMA_Descriptor_t ldmaRxDesc[4] = {
  /// First half of receive pingpong configuration
  LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(
    &(BTL_DRIVER_EUSART->RXDATA),
    &(rxBuffer[0]),
    BTL_DRIVER_UART_RX_BUFFER_SIZE / 2,
    1
    ),
  // Sync structure waiting for SYNC[1], clearing SYNC[0]
  LDMA_DESCRIPTOR_LINKREL_SYNC(
    0,
    (1 << 0),
    (1 << 1),
    (1 << 1),
    1
    ),
  /// Second half of receive pingpong configuration
  LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(
    &(BTL_DRIVER_EUSART->RXDATA),
    &(rxBuffer[BTL_DRIVER_UART_RX_BUFFER_SIZE / 2]),
    BTL_DRIVER_UART_RX_BUFFER_SIZE / 2,
    1
    ),
  /// Sync structure waiting for SYNC[0], clearing SYNC[1]
  LDMA_DESCRIPTOR_LINKREL_SYNC(
    0,
    (1 << 1),
    (1 << 0),
    (1 << 0),
    -3
    )
};
//  ‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐‐
// Functions

/**
 * Initialize the configured EUART peripheral for UART operation. Also sets up
 *  GPIO settings for TX, RX, and, if configured, flow control.
 */
void uart_init(void)
{
  CMU_ClockEnable(cmuClock_EM01GRPACLK, true);
  CMU_ClockEnable(BTL_DRIVER_EUSART_CLOCK, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockSelectSet(BTL_DRIVER_EUSART_CLOCK, cmuSelect_EM01GRPACLK); // Select HF clock for euart.

  EUSART_UartInit_TypeDef init = EUSART_UART_INIT_DEFAULT_HF;
  init.enable = eusartDisable;

  // Configure CTS/RTS in case of flow control
#if (HAL_SERIAL_APP_FLOW_CONTROL == HAL_USART_FLOW_CONTROL_HW)      \
  || (HAL_SERIAL_APP_FLOW_CONTROL == HAL_USART_FLOW_CONTROL_HWUART) \
  || (HAL_SERIAL_APP_FLOW_CONTROL == HAL_UART_FLOW_CONTROL_HW)      \
  || (HAL_SERIAL_APP_FLOW_CONTROL == HAL_UART_FLOW_CONTROL_HWUART)
  GPIO_PinModeSet(BSP_SERIAL_APP_RTS_PORT,
                  BSP_SERIAL_APP_RTS_PIN,
                  gpioModePushPull,
                  1);
  GPIO_PinModeSet(BSP_SERIAL_APP_CTS_PORT,
                  BSP_SERIAL_APP_CTS_PIN,
                  gpioModeInput,
                  1);

  // Advansed init to configure CTS and RTS
  EUSART_AdvancedInit_TypeDef advancedInit = EUSART_ADVANCED_INIT_DEFAULT;
  advancedInit.hwFlowControl = eusartHwFlowControlCtsAndRts;
  init.advancedSettings = &advancedInit;

  GPIO->EUARTROUTE->CTSROUTE =
    (BSP_SERIAL_APP_CTS_PORT << _GPIO_EUART_CTSROUTE_PORT_SHIFT)
    | (BSP_SERIAL_APP_CTS_PIN << _GPIO_EUART_CTSROUTE_PIN_SHIFT);
  GPIO->EUARTROUTE->RTSROUTE =
    (BSP_SERIAL_APP_RTS_PORT << _GPIO_EUART_RTSROUTE_PORT_SHIFT)
    | (BSP_SERIAL_APP_RTS_PIN << _GPIO_EUART_RTSROUTE_PIN_SHIFT);
#endif
  init.refFreq = util_getClockFreq() / (1U + ((CMU->SYSCLKCTRL & _CMU_SYSCLKCTRL_PCLKPRESC_MASK)
                                              >> _CMU_SYSCLKCTRL_PCLKPRESC_SHIFT));
  init.baudrate = HAL_SERIAL_APP_BAUD_RATE;
  EUSART_UartInitHf(BTL_DRIVER_EUSART, &init);

  GPIO_PinModeSet(BSP_SERIAL_APP_TX_PORT,
                  BSP_SERIAL_APP_TX_PIN,
                  gpioModePushPull,
                  1);
  GPIO_PinModeSet(BSP_SERIAL_APP_RX_PORT,
                  BSP_SERIAL_APP_RX_PIN,
                  gpioModeInput,
                  1);
  GPIO->EUARTROUTE->ROUTEEN = GPIO_EUART_ROUTEEN_TXPEN;
  GPIO->EUARTROUTE->TXROUTE = 0
                              | (BSP_SERIAL_APP_TX_PORT << _GPIO_EUART_TXROUTE_PORT_SHIFT)
                              | (BSP_SERIAL_APP_TX_PIN << _GPIO_EUART_TXROUTE_PIN_SHIFT);
  GPIO->EUARTROUTE->RXROUTE = 0
                              | (BSP_SERIAL_APP_RX_PORT << _GPIO_EUART_RXROUTE_PORT_SHIFT)
                              | (BSP_SERIAL_APP_RX_PIN << _GPIO_EUART_RXROUTE_PIN_SHIFT);

#if (HAL_VCOM_ENABLE == 1) && defined(BSP_VCOM_ENABLE_PORT)
  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT,
                  BSP_VCOM_ENABLE_PIN,
                  gpioModePushPull,
                  1);
#endif
  EUSART_Enable(BTL_DRIVER_EUSART, eusartEnable);

  // Configure LDMA
  CMU->CLKEN0_SET = (CMU_CLKEN0_LDMA | CMU_CLKEN0_LDMAXBAR);
  LDMA->EN = LDMA_EN_EN;
  // Reset LDMA
  LDMA->CTRL = _LDMA_CTRL_RESETVALUE;
  LDMA->CHEN = _LDMA_CHEN_RESETVALUE;
  LDMA->DBGHALT = _LDMA_DBGHALT_RESETVALUE;
  LDMA->REQDIS = _LDMA_REQDIS_RESETVALUE;
  LDMA->IEN = _LDMA_IEN_RESETVALUE;

  // Set up channel 0 as RX transfer
  LDMAXBAR->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].REQSEL = ldmaRxTransfer.ldmaReqSel;
  LDMA->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].LOOP
    = (ldmaRxTransfer.ldmaLoopCnt << _LDMA_CH_LOOP_LOOPCNT_SHIFT);
  LDMA->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].CFG
    = (ldmaRxTransfer.ldmaCfgArbSlots << _LDMA_CH_CFG_ARBSLOTS_SHIFT)
      | (ldmaRxTransfer.ldmaCfgSrcIncSign << _LDMA_CH_CFG_SRCINCSIGN_SHIFT)
      | (ldmaRxTransfer.ldmaCfgDstIncSign << _LDMA_CH_CFG_DSTINCSIGN_SHIFT);

  LDMA->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].LINK
    = (uint32_t)(&ldmaRxDesc[0]) & _LDMA_CH_LINK_LINKADDR_MASK;

  // Set up channel 1 as TX transfer
  LDMAXBAR->CH[BTL_DRIVER_EUSART_LDMA_TX_CHANNEL].REQSEL = ldmaTxTransfer.ldmaReqSel;
  LDMA->CH[BTL_DRIVER_EUSART_LDMA_TX_CHANNEL].LOOP
    = (ldmaTxTransfer.ldmaLoopCnt << _LDMA_CH_LOOP_LOOPCNT_SHIFT);
  LDMA->CH[BTL_DRIVER_EUSART_LDMA_TX_CHANNEL].CFG
    = (ldmaTxTransfer.ldmaCfgArbSlots << _LDMA_CH_CFG_ARBSLOTS_SHIFT)
      | (ldmaTxTransfer.ldmaCfgSrcIncSign << _LDMA_CH_CFG_SRCINCSIGN_SHIFT)
      | (ldmaTxTransfer.ldmaCfgDstIncSign << _LDMA_CH_CFG_DSTINCSIGN_SHIFT);

  // Clear DONE flag on both RX and TX channels
  BUS_RegMaskedClear(&LDMA->CHDONE,
                     ((1 << BTL_DRIVER_EUSART_LDMA_RX_CHANNEL)
                      | (1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL)));

  // Kick off background RX
  LDMA->LINKLOAD = (1 << BTL_DRIVER_EUSART_LDMA_RX_CHANNEL);

  // Mark second half of RX buffer as ready
  LDMA->SYNCSWSET_SET = (1UL << 1);

  initialized = true;
}

/**
 * Disable the configured EUART peripheral for UART operation.
 */
void uart_deinit(void)
{
  CMU->CLKEN0_CLR = (CMU_CLKEN0_LDMA | CMU_CLKEN0_LDMAXBAR | CMU_CLKEN0_EUART0);

  initialized = false;
}

/**
 * Write a data buffer to the UART.
 *
 * @param[in] buffer The data buffer to send
 * @param[in] length Amount of bytes in the buffer to send
 * @param[in] blocking Indicates whether this transfer can be offloaded to LDMA
 *  and return, or whether it should wait on completion before returning.
 *
 * @return BOOTLOADER_OK if successful, error code otherwise
 */
int32_t uart_sendBuffer(uint8_t* buffer, size_t length, bool blocking)
{
  BTL_ASSERT(initialized == true);
  BTL_ASSERT(length > 0);

  if (length >= BTL_DRIVER_UART_TX_BUFFER_SIZE) {
    return BOOTLOADER_ERROR_SPISLAVE_ARGUMENT;
  }

  if (!uart_isTxIdle()) {
    return BOOTLOADER_ERROR_UART_BUSY;
  }

  // Copy buffer
  txLength = length;
  length = 0;
  for (; length < txLength; length++) {
    txBuffer[length] = buffer[length];
  }

  // Populate descriptor
  ldmaTxDesc.xfer.xferCnt = txLength - 1;

  // Kick off transfer
  LDMA->CH[BTL_DRIVER_EUSART_LDMA_TX_CHANNEL].LINK
    = (uint32_t)(&ldmaTxDesc) & _LDMA_CH_LINK_LINKADDR_MASK;
  LDMA->LINKLOAD = (1UL << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL);

  // Optional wait for completion
  if (blocking) {
    while (uart_isTxIdle() == false) {
      // Do nothing
    }
    while (!(BTL_DRIVER_EUSART->STATUS & EUSART_STATUS_TXC)) {
      // Do nothing
    }
  }

  return BOOTLOADER_OK;
}

/**
 * Write one byte to the UART in a blocking fashion.
 *
 * @param[in] byte The byte to send
 *
 * @return BOOTLOADER_OK if successful, error code otherwise
 */
int32_t uart_sendByte(uint8_t byte)
{
  BTL_ASSERT(initialized == true);

  // Wait until previous LDMA transfer is done
  while (!uart_isTxIdle()) {
    // Do nothing
  }

  // Wait until there is room for one more byte
  while (!(BTL_DRIVER_EUSART->STATUS & EUSART_STATUS_TXFL)) {
    // Do nothing
  }

  // Send byte
  BTL_DRIVER_EUSART->TXDATA = byte;

  // Wait until byte has been fully sent out
  while (!(BTL_DRIVER_EUSART->STATUS & EUSART_STATUS_TXC)) {
    // Do nothing
  }
  return BOOTLOADER_OK;
}

/**
 * Find out whether the UART can accept more data to send.
 *
 * @return true if the UART is not currently transmitting
 */
bool uart_isTxIdle(void)
{
  BTL_ASSERT(initialized == true);
  if (LDMA->CHDONE & (1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL)) {
    LDMA->CHDIS = (1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL);
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL);
    txLength = 0;
    return true;
  } else if ((LDMA->CHSTATUS & (1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL)) == 0) {
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL);
    txLength = 0;
    return true;
  }

  return false;
}

/**
 * Gets the amount of bytes ready for reading.
 *
 * @return Amount of bytes in the receive buffer available for reading with
 *   @ref protocol_uart_recv
 */
size_t  uart_getRxAvailableBytes(void)
{
  size_t ldmaHead;
  size_t dst;

  BTL_ASSERT(initialized == true);

  // Get destination address for next transfer
  dst = LDMA->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].DST;

  if (dst == 0x0101) {
    // SYNC descriptor with bit 0 of MATCHEN and MATCHVAL set
    ldmaHead = 0;
  } else if (dst == 0x0202) {
    // SYNC descriptor with bit 1 of MATCHEN and MATCHVAL set
    ldmaHead = BTL_DRIVER_UART_RX_BUFFER_SIZE / 2;
  } else {
    // XFER descriptor with absolute address in buffer
    ldmaHead = dst - (uint32_t)(rxBuffer);
  }

  // Return difference between received head and LDMA head
  if (rxHead == ldmaHead) {
    return 0;
  } else if (rxHead < ldmaHead) {
    return ldmaHead - rxHead;
  } else {
    return BTL_DRIVER_UART_RX_BUFFER_SIZE - (rxHead - ldmaHead);
  }
}

/**
 * Read from the UART into a data buffer.
 *
 * @param[out] buffer The data buffer to receive into
 * @param[in] requestedLength Amount of bytes we'd like to read
 * @param[out] receivedLength Amount of bytes read
 * @param[in] blocking Indicates whether we to wait for requestedLength
 *   bytes to be available and read before returning, whether to read out
 *   data currently in the buffer and return.
 * @param[in] timeout Number of milliseconds to wait for data in blocking mode
 *
 * @return BOOTLOADER_OK if successful, error code otherwise
 */
int32_t uart_receiveBuffer(uint8_t  * buffer,
                           size_t   requestedLength,
                           size_t   * receivedLength,
                           bool     blocking,
                           uint32_t timeout)
{
  size_t copyBytes = 0;
  size_t copiedBytes = 0;

  BTL_ASSERT(initialized == true);
  BTL_ASSERT(requestedLength < BTL_DRIVER_UART_RX_BUFFER_SIZE);

  // Check whether we have enough data
  // Optional spin for timeout cycles
  if (blocking) {
    if (timeout != 0) {
      delay_init();
      delay_milliseconds(timeout, false);
    }

    while (uart_getRxAvailableBytes() < requestedLength) {
      if ((timeout != 0) && delay_expired()) {
        break;
      }
    }
  }

  copyBytes = uart_getRxAvailableBytes();
  if (requestedLength < copyBytes) {
    copyBytes = requestedLength;
  }

  // Copy up to requested bytes to given buffer
  while (copiedBytes < copyBytes) {
    buffer[copiedBytes] = rxBuffer[rxHead];
    copiedBytes++;
    rxHead++;

    if (rxHead == BTL_DRIVER_UART_RX_BUFFER_SIZE) {
      rxHead = 0;
      // Completed processing of second half of the buffer, mark it as available
      // for LDMA again by setting SYNC[1]
      LDMA->SYNCSWSET_SET = 1 << 1;
    } else if (rxHead == BTL_DRIVER_UART_RX_BUFFER_SIZE / 2) {
      // Completed processing of first half of the buffer, mark it as available
      // for LDMA again by setting SYNC[0]
      LDMA->SYNCSWSET_SET = 1 << 0;
    }

    // TODO: Check overflow by checking both SYNC[0] and SYNC[1]
  }

  if ((uint32_t)receivedLength != 0UL) {
    *receivedLength = copiedBytes;
  }

  if (copiedBytes < requestedLength) {
    return BOOTLOADER_ERROR_UART_TIMEOUT;
  } else {
    return BOOTLOADER_OK;
  }
}

/**
 * Get one byte from the UART in a blocking fashion.
 *
 * @param[out] byte The byte to send
 *
 * @return BOOTLOADER_OK if successful, error code otherwise
 */
int32_t uart_receiveByte(uint8_t* byte)
{
  return uart_receiveBuffer(byte, 1, (size_t*)0UL, true, 0);
}

/**
 * Get one byte from the UART in a blocking fashion.
 *
 * @param[out] byte The byte to send
 * @param[in]  timeout Maximum timeout before aborting transfer
 *
 * @return BOOTLOADER_OK if successful, error code otherwise
 */
int32_t uart_receiveByteTimeout(uint8_t* byte, uint32_t timeout)
{
  return uart_receiveBuffer(byte, 1, (size_t *)0UL, true, timeout);
}

/**
 * Flushes one or both UART buffers.
 *
 * @param[in] flushTx Flushes the transmit buffer when true
 * @param[in] flushRx Flushes the receive buffer when true
 *
 * @return BOOTLOADER_OK
 */
int32_t uart_flush(bool flushTx, bool flushRx)
{
  BTL_ASSERT(initialized == true);

  if (flushTx) {
    LDMA->CHDIS = (1 << BTL_DRIVER_EUSART_LDMA_TX_CHANNEL);
    txLength = 0;
  }

  if (flushRx) {
    LDMA->CHDIS = (1 << BTL_DRIVER_EUSART_LDMA_RX_CHANNEL);
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_EUSART_LDMA_RX_CHANNEL);
    LDMA->CH[BTL_DRIVER_EUSART_LDMA_RX_CHANNEL].LINK
      = (uint32_t)(&ldmaRxDesc[0]) & _LDMA_CH_LINK_LINKADDR_MASK;
    rxHead = 0;
    LDMA->LINKLOAD = (1 << BTL_DRIVER_EUSART_LDMA_RX_CHANNEL);

    // Mark second half of RX buffer as ready
    BUS_RegMaskedSet(&LDMA->SYNCSWSET, 1 << 1);
  }

  return BOOTLOADER_OK;
}

#endif
