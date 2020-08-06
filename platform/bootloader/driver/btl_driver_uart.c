/***************************************************************************//**
 * @file
 * @brief Universal UART driver for the Silicon Labs Bootloader.
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
#include "config/btl_config.h"

#if (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART0)  \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART1) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART2) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART3) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART4) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART5) \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_UART0)  \
  || (BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_UART1)

#include "btl_driver_uart.h"
#include "btl_driver_delay.h"
#include "api/btl_interface.h"
#include "btl_driver_util.h"

#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_bus.h"

#include "plugin/debug/btl_debug.h"

#if BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART0
#define BTL_DRIVER_UART                     USART0
#define BTL_DRIVER_USART_NUM                0
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART0
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART0_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART0_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART1
#define BTL_DRIVER_UART                     USART1
#define BTL_DRIVER_USART_NUM                1
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART1
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART1_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART1_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART2
#define BTL_DRIVER_UART                     USART2
#define BTL_DRIVER_USART_NUM                2
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART2
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART2_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART2_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART3
#define BTL_DRIVER_UART                     USART3
#define BTL_DRIVER_USART_NUM                3
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART3
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART3_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART3_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART4
#define BTL_DRIVER_UART                     USART4
#define BTL_DRIVER_USART_NUM                4
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART4
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART4_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART4_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART5
#define BTL_DRIVER_UART                     USART5
#define BTL_DRIVER_USART_NUM                5
#define BTL_DRIVER_UART_CLOCK               cmuClock_USART5
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_USART5_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_USART5_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_UART0
#define BTL_DRIVER_UART                     UART0
#define BTL_DRIVER_UART_NUM                 0
#define BTL_DRIVER_UART_CLOCK               cmuClock_UART0
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_UART0_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_UART0_RXDATAV)
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_UART1
#define BTL_DRIVER_UART                     UART1
#define BTL_DRIVER_UART_NUM                 1
#define BTL_DRIVER_UART_CLOCK               cmuClock_UART1
#define BTL_DRIVER_UART_LDMA_TXBL_SIGNAL    (ldmaPeripheralSignal_UART1_TXBL)
#define BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL (ldmaPeripheralSignal_UART1_RXDATAV)
#endif

#define BTL_DRIVER_UART_LDMA_RX_CHANNEL     0
#define BTL_DRIVER_UART_LDMA_TX_CHANNEL     1

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
  BTL_DRIVER_UART_LDMA_TXBL_SIGNAL
  );
/// LDMA channel configuration triggering on available byte in UART receive FIFO
static const LDMA_TransferCfg_t ldmaRxTransfer = LDMA_TRANSFER_CFG_PERIPHERAL(
  BTL_DRIVER_UART_LDMA_RXDATAV_SIGNAL
  );

/// LDMA transfer for copying transmit buffer to UART TX FIFO
static LDMA_Descriptor_t ldmaTxDesc = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(
  txBuffer,
  &(BTL_DRIVER_UART->TXDATA),
  0
  );

static const LDMA_Descriptor_t ldmaRxDesc[4] = {
  /// First half of receive pingpong configuration
  LDMA_DESCRIPTOR_LINKREL_P2M_BYTE(
    &(BTL_DRIVER_UART->RXDATA),
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
    &(BTL_DRIVER_UART->RXDATA),
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
 * Initialize the configured USART peripheral for UART operation. Also sets up
 *  GPIO settings for TX, RX, and, if configured, flow control.
 */
void uart_init(void)
{
  uint32_t refFreq, clkdiv;

  // Clock peripherals
#if defined(_SILICON_LABS_32B_SERIES_1)
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_LDMA, true);
  CMU_ClockEnable(BTL_DRIVER_UART_CLOCK, true);
#endif

#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_SET = CMU_CLKEN0_GPIO;
#if BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART0
  CMU->CLKEN0_SET = CMU_CLKEN0_USART0;
#elif BSP_SERIAL_APP_PORT == HAL_SERIAL_PORT_USART1
  CMU->CLKEN0_SET = CMU_CLKEN0_USART1;
#else
#error "Invalid BSP_EXTFLASH_USART"
#endif
#endif

#if defined(USART_EN_EN)
  BTL_DRIVER_UART->EN_SET = USART_EN_EN;
#endif

  // Set up USART
  BTL_DRIVER_UART->CMD = USART_CMD_RXDIS
                         | USART_CMD_TXDIS
                         | USART_CMD_MASTERDIS
                         | USART_CMD_RXBLOCKDIS
                         | USART_CMD_TXTRIDIS
                         | USART_CMD_CLEARTX
                         | USART_CMD_CLEARRX;
  BTL_DRIVER_UART->CTRL = _USART_CTRL_RESETVALUE;
  BTL_DRIVER_UART->CTRLX = _USART_CTRLX_RESETVALUE;
  BTL_DRIVER_UART->FRAME = _USART_FRAME_RESETVALUE;
  BTL_DRIVER_UART->TRIGCTRL = _USART_TRIGCTRL_RESETVALUE;
  BTL_DRIVER_UART->CLKDIV = _USART_CLKDIV_RESETVALUE;
  BTL_DRIVER_UART->IEN = _USART_IEN_RESETVALUE;
#if defined(_USART_IFC_MASK)
  BTL_DRIVER_UART->IFC = _USART_IFC_MASK;
#else
  BTL_DRIVER_UART->IF_CLR = _USART_IF_MASK;
#endif

#if defined(_USART_ROUTEPEN_RESETVALUE)
  BTL_DRIVER_UART->ROUTEPEN = _USART_ROUTEPEN_RESETVALUE;
  BTL_DRIVER_UART->ROUTELOC0 = _USART_ROUTELOC0_RESETVALUE;
  BTL_DRIVER_UART->ROUTELOC1 = _USART_ROUTELOC1_RESETVALUE;
#else
#if defined(BTL_DRIVER_USART_NUM)
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].ROUTEEN = _GPIO_USART_ROUTEEN_RESETVALUE;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].TXROUTE = _GPIO_USART_TXROUTE_RESETVALUE;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].RXROUTE = _GPIO_USART_RXROUTE_RESETVALUE;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].CTSROUTE = _GPIO_USART_CTSROUTE_RESETVALUE;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].RTSROUTE = _GPIO_USART_RTSROUTE_RESETVALUE;
#else
#error "No USART number given"
#endif // BTL_DRIVER_USART_NUM
#endif

  // Configure databits, stopbits and parity
  BTL_DRIVER_UART->FRAME = USART_FRAME_DATABITS_EIGHT
                           | USART_FRAME_STOPBITS_ONE
                           | USART_FRAME_PARITY_NONE;

  // Configure oversampling and baudrate
  BTL_DRIVER_UART->CTRL |= USART_CTRL_OVS_X16;
  refFreq = util_getClockFreq();
#if defined(_SILICON_LABS_32B_SERIES_2)
  refFreq = refFreq / (1U + ((CMU->SYSCLKCTRL & _CMU_SYSCLKCTRL_PCLKPRESC_MASK)
                             >> _CMU_SYSCLKCTRL_PCLKPRESC_SHIFT));
#endif
  clkdiv = 32 * refFreq + (16 * HAL_SERIAL_APP_BAUD_RATE) / 2;
  clkdiv /= (16 * HAL_SERIAL_APP_BAUD_RATE);
  clkdiv -= 32;
  clkdiv *= 8;

  // Verify that resulting clock divider is within limits
  BTL_ASSERT(clkdiv <= _USART_CLKDIV_DIV_MASK);

  // If asserts are not enabled, make sure we don't write to reserved bits
  clkdiv &= _USART_CLKDIV_DIV_MASK;

  BTL_DRIVER_UART->CLKDIV = clkdiv;

  GPIO_PinModeSet(BSP_SERIAL_APP_TX_PORT,
                  BSP_SERIAL_APP_TX_PIN,
                  gpioModePushPull,
                  1);
  GPIO_PinModeSet(BSP_SERIAL_APP_RX_PORT,
                  BSP_SERIAL_APP_RX_PIN,
                  gpioModeInput,
                  1);

  // Configure route
#if defined(_USART_ROUTEPEN_RESETVALUE)
  BTL_DRIVER_UART->ROUTELOC0 = (BSP_SERIAL_APP_TX_LOC
                                << _USART_ROUTELOC0_TXLOC_SHIFT)
                               | (BSP_SERIAL_APP_RX_LOC
                                  << _USART_ROUTELOC0_RXLOC_SHIFT);
  BTL_DRIVER_UART->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN;
#else
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN
                                                   | GPIO_USART_ROUTEEN_RXPEN;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].TXROUTE = 0
                                                   | (BSP_SERIAL_APP_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT)
                                                   | (BSP_SERIAL_APP_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].RXROUTE = 0
                                                   | (BSP_SERIAL_APP_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT)
                                                   | (BSP_SERIAL_APP_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
#endif

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

  // Configure CTS/RTS route
#if defined(_USART_ROUTEPEN_RESETVALUE)
  BTL_DRIVER_UART->ROUTELOC1 = (BSP_SERIAL_APP_RTS_LOC
                                << _USART_ROUTELOC1_RTSLOC_SHIFT)
                               | (BSP_SERIAL_APP_CTS_LOC
                                  << _USART_ROUTELOC1_CTSLOC_SHIFT);
  BTL_DRIVER_UART->ROUTEPEN |= USART_ROUTEPEN_RTSPEN | USART_ROUTEPEN_CTSPEN;
#else
  GPIO->USARTROUTE_SET[BTL_DRIVER_USART_NUM].ROUTEEN = GPIO_USART_ROUTEEN_RTSPEN;
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].CTSROUTE =
    (BSP_SERIAL_APP_CTS_PORT << _GPIO_USART_CTSROUTE_PORT_SHIFT)
    | (BSP_SERIAL_APP_CTS_PIN << _GPIO_USART_CTSROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[BTL_DRIVER_USART_NUM].RTSROUTE =
    (BSP_SERIAL_APP_RTS_PORT << _GPIO_USART_RTSROUTE_PORT_SHIFT)
    | (BSP_SERIAL_APP_RTS_PIN << _GPIO_USART_RTSROUTE_PIN_SHIFT);

#endif

  // Configure USART for flow control
  BTL_DRIVER_UART->CTRLX |= USART_CTRLX_CTSEN;
#endif

#if (HAL_VCOM_ENABLE == 1) && defined(BSP_VCOM_ENABLE_PORT)
  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT,
                  BSP_VCOM_ENABLE_PIN,
                  gpioModePushPull,
                  1);
#endif

  // Enable TX/RX
  BTL_DRIVER_UART->CMD = USART_CMD_RXEN
                         | USART_CMD_TXEN;

#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_SET = (CMU_CLKEN0_LDMA | CMU_CLKEN0_LDMAXBAR);
#endif

#if defined(LDMA_EN_EN)
  LDMA->EN = LDMA_EN_EN;
#endif

  // Reset LDMA
  LDMA->CTRL = _LDMA_CTRL_RESETVALUE;
  LDMA->CHEN = _LDMA_CHEN_RESETVALUE;
  LDMA->DBGHALT = _LDMA_DBGHALT_RESETVALUE;
  LDMA->REQDIS = _LDMA_REQDIS_RESETVALUE;
  LDMA->IEN = _LDMA_IEN_RESETVALUE;

  // Set up channel 0 as RX transfer
#if defined(LDMAXBAR)
  LDMAXBAR->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].REQSEL = ldmaRxTransfer.ldmaReqSel;
#else
  LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].REQSEL = ldmaRxTransfer.ldmaReqSel;
#endif
  LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].LOOP
    = (ldmaRxTransfer.ldmaLoopCnt << _LDMA_CH_LOOP_LOOPCNT_SHIFT);
  LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].CFG
    = (ldmaRxTransfer.ldmaCfgArbSlots << _LDMA_CH_CFG_ARBSLOTS_SHIFT)
      | (ldmaRxTransfer.ldmaCfgSrcIncSign << _LDMA_CH_CFG_SRCINCSIGN_SHIFT)
      | (ldmaRxTransfer.ldmaCfgDstIncSign << _LDMA_CH_CFG_DSTINCSIGN_SHIFT);

  LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].LINK
    = (uint32_t)(&ldmaRxDesc[0]) & _LDMA_CH_LINK_LINKADDR_MASK;

  // Set up channel 1 as TX transfer
#if defined(LDMAXBAR)
  LDMAXBAR->CH[BTL_DRIVER_UART_LDMA_TX_CHANNEL].REQSEL = ldmaTxTransfer.ldmaReqSel;
#else
  LDMA->CH[BTL_DRIVER_UART_LDMA_TX_CHANNEL].REQSEL = ldmaTxTransfer.ldmaReqSel;
#endif
  LDMA->CH[BTL_DRIVER_UART_LDMA_TX_CHANNEL].LOOP
    = (ldmaTxTransfer.ldmaLoopCnt << _LDMA_CH_LOOP_LOOPCNT_SHIFT);
  LDMA->CH[BTL_DRIVER_UART_LDMA_TX_CHANNEL].CFG
    = (ldmaTxTransfer.ldmaCfgArbSlots << _LDMA_CH_CFG_ARBSLOTS_SHIFT)
      | (ldmaTxTransfer.ldmaCfgSrcIncSign << _LDMA_CH_CFG_SRCINCSIGN_SHIFT)
      | (ldmaTxTransfer.ldmaCfgDstIncSign << _LDMA_CH_CFG_DSTINCSIGN_SHIFT);

  // Clear DONE flag on both RX and TX channels
  BUS_RegMaskedClear(&LDMA->CHDONE,
                     ((1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL)
                      | (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL)));

  // Kick off background RX
  LDMA->LINKLOAD = (1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL);

  // Mark second half of RX buffer as ready
#if defined(_LDMA_SYNCSWSET_MASK)
  LDMA->SYNCSWSET_SET = 1 << 1;
#else
  BUS_RegMaskedSet(&LDMA->SYNC, 1 << 1);
#endif

  initialized = true;
}

/**
 * Disable the configured USART peripheral for UART operation.
 */
void uart_deinit(void)
{
#if !defined(BTL_DRIVER_UART_NUM)
  util_deinitUsart(BTL_DRIVER_UART, BTL_DRIVER_USART_NUM, BTL_DRIVER_UART_CLOCK);
#endif
#if defined(_CMU_CLKEN0_MASK)
  CMU->CLKEN0_CLR = (CMU_CLKEN0_LDMA | CMU_CLKEN0_LDMAXBAR | CMU_CLKEN0_GPIO);
#endif
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
  LDMA->CH[BTL_DRIVER_UART_LDMA_TX_CHANNEL].LINK
    = (uint32_t)(&ldmaTxDesc) & _LDMA_CH_LINK_LINKADDR_MASK;
  LDMA->LINKLOAD = 1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL;

  // Optional wait for completion
  if (blocking) {
    while (uart_isTxIdle() == false) {
      // Do nothing
    }
    while (!(BTL_DRIVER_UART->STATUS & USART_STATUS_TXC)) {
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
  while (!(BTL_DRIVER_UART->STATUS & USART_STATUS_TXBL)) {
    // Do nothing
  }

  // Send byte
  BTL_DRIVER_UART->TXDATA = byte;

  // Wait until byte has been fully sent out
  while (!(BTL_DRIVER_UART->STATUS & USART_STATUS_TXC)) {
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
  if (LDMA->CHDONE & (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL)) {
#if defined(_LDMA_CHDIS_MASK)
    LDMA->CHDIS = (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
#else
    BUS_RegMaskedClear(&LDMA->CHEN, 1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
#endif
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
    txLength = 0;
    return true;
#if defined(_LDMA_CHSTATUS_MASK)
  } else if ((LDMA->CHSTATUS & (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL)) == 0) {
#else
  } else if ((LDMA->CHEN & (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL)) == 0) {
#endif
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
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
  dst = LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].DST;

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
#if defined(_LDMA_SYNCSWSET_MASK)
      LDMA->SYNCSWSET_SET = 1 << 1;
#else
      BUS_RegMaskedSet(&LDMA->SYNC, 1 << 1);
#endif
    } else if (rxHead == BTL_DRIVER_UART_RX_BUFFER_SIZE / 2) {
      // Completed processing of first half of the buffer, mark it as available
      // for LDMA again by setting SYNC[0]
#if defined(_LDMA_SYNCSWSET_MASK)
      LDMA->SYNCSWSET_SET = 1 << 0;
#else
      BUS_RegMaskedSet(&LDMA->SYNC, 1 << 0);
#endif
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
#if defined(_LDMA_CHDIS_MASK)
    LDMA->CHDIS = (1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
#else
    BUS_RegMaskedClear(&LDMA->CHEN, 1 << BTL_DRIVER_UART_LDMA_TX_CHANNEL);
#endif
    txLength = 0;
  }

  if (flushRx) {
#if defined(_LDMA_CHDIS_MASK)
    LDMA->CHDIS = (1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL);
#else
    BUS_RegMaskedClear(&LDMA->CHEN, 1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL);
#endif
    BUS_RegMaskedClear(&LDMA->CHDONE, 1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL);
    LDMA->CH[BTL_DRIVER_UART_LDMA_RX_CHANNEL].LINK
      = (uint32_t)(&ldmaRxDesc[0]) & _LDMA_CH_LINK_LINKADDR_MASK;
    rxHead = 0;
    LDMA->LINKLOAD = (1 << BTL_DRIVER_UART_LDMA_RX_CHANNEL);

    // Mark second half of RX buffer as ready
#if defined(_LDMA_SYNCSWSET_MASK)
    BUS_RegMaskedSet(&LDMA->SYNCSWSET, 1 << 1);
#else
    BUS_RegMaskedSet(&LDMA->SYNC, 1 << 1);
#endif
  }

  return BOOTLOADER_OK;
}

#endif
