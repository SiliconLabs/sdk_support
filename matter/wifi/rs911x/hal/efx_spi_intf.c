/*************************************************************************
 *
 * Copyright (c) 2019 Redpine Signals Incorporated. All Rights Reserved.
 *
 * NOTICE:  All  information  contained  herein is, and  remains  the  property of
 * Redpine Signals Incorporated. The intellectual and technical concepts contained
 * herein  are  proprietary to  Redpine Signals Incorporated and may be covered by
 * U.S. and Foreign Patents, patents in process, and are protected by trade secret
 * or copyright law. Dissemination  of this  information or reproduction  of  this
 * material is strictly forbidden unless prior written permission is obtained from
 * Redpine Signals Incorporated.
 */
/**
 * Includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmadrv.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_core.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_ldma.h"
#if defined(EFR32MG12)
#include "em_usart.h"
#elif defined(EFR32MG24)
#include "em_eusart.h"
#endif
#include "gpiointerrupt.h"
#include "sl_device_init_clocks.h"
#include "sl_status.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

#include "wfx_host_events.h"
#include "wfx_rsi.h"

#include "rsi_board_configuration.h"
#include "rsi_driver.h"
#include "sl_device_init_dpll.h"
#include "sl_device_init_hfxo.h"

StaticSemaphore_t xEfxSpiIntfSemaBuffer;
static SemaphoreHandle_t spi_sem;
static unsigned int tx_dma_chan, rx_dma_chan;
/*TODO -  FIX This - It belongs somewhere else depending on which USART is used */
static uint32_t dummy_data; /* Used for DMA - when results don't matter */
extern void rsi_gpio_irq_cb(uint8_t irqnum);

/****************************************************************************
 * @fn    static void dma_init(void)
 * @brief  
 *        Initialize DMA
 * @return 
 *        None
 *****************************************************************************/
static void dma_init(void)
{
  /* Note LDMA is init'd by DMADRV_Init */
  DMADRV_Init();
  DMADRV_AllocateChannel(&tx_dma_chan, NULL);
  DMADRV_AllocateChannel(&rx_dma_chan, NULL);
}

/****************************************************************************
 * @fn   sl_wfx_host_init_bus(void)
 * @brief  
 *       Initialize SPI peripheral
 * @return
 *       None
 *****************************************************************************/
void sl_wfx_host_init_bus(void)
{
  // Initialize and enable the USART
#if defined(EFR32MG12)
  USART_InitSync_TypeDef config = USART_INITSYNC_DEFAULT;

  dummy_data          = 0;
  config.master       = true;            // master mode
  config.baudrate     = 10000000u;       // CLK freq is 1 MHz
  config.autoCsEnable = true;            // CS pin controlled by hardware, not firmware
  config.clockMode    = usartClockMode0; // clock idle low, sample on rising/first edge
  config.msbf         = true;            // send MSB first
  config.enable       = usartDisable;    // Make sure to keep USART disabled until it's all set up
  CMU_ClockEnable(cmuClock_HFPER, true);
#elif defined(EFR32MG21) || defined(EFR32MG24)
  CMU_ClockEnable(cmuClock_EUSART1, true);
  // Configure MOSI (TX) pin as an output
  GPIO_PinModeSet(EUS1MOSI_PORT, EUS1MOSI_PIN, gpioModePushPull, 0);

  // Configure MISO (RX) pin as an input
  GPIO_PinModeSet(EUS1MISO_PORT, EUS1MISO_PIN, gpioModeInput, 0);

  // Configure SCLK pin as an output low (CPOL = 0)
  GPIO_PinModeSet(EUS1SCLK_PORT, EUS1SCLK_PIN, gpioModePushPull, 0);

  // Configure CS pin as an output initially high
  // GPIO_PinModeSet(EUS1CS_PORT, EUS1CS_PIN, gpioModePushPull, 0);
  // SPI advanced configuration (part of the initializer)
  EUSART_SpiAdvancedInit_TypeDef adv = EUSART_SPI_ADVANCED_INIT_DEFAULT;

  adv.msbFirst = true;        // SPI standard MSB first
  adv.autoInterFrameTime = 7; // 7 bit times of delay between frames
                              // to accommodate non-DMA secondaries

  // Default asynchronous initializer (main/master mode and 8-bit data)
  EUSART_SpiInit_TypeDef init = EUSART_SPI_MASTER_INIT_DEFAULT_HF;

  init.bitRate = 12000000;         // 12 MHz shift clock
  init.advancedSettings = &adv;   // Advanced settings structure
#endif
#if defined(EFR32MG12)
  CMU_ClockEnable(MY_USART_CLOCK, true);
  USART_InitSync(MY_USART, &config);
#endif
#if defined(EFR32MG12)
  MY_USART->CTRL |= (1u << _USART_CTRL_SMSDELAY_SHIFT);
  MY_USART->ROUTELOC0 =
    (USART_ROUTELOC0_CLKLOC_LOC1) | // US2_CLK n location 1 = PA8 per datasheet section 6.4 = EXP Header pin 8
    (USART_ROUTELOC0_CSLOC_LOC1) |  // US2_CS on location 1 = PA9 per datasheet section 6.4 = EXP Header pin 10
    (USART_ROUTELOC0_TXLOC_LOC1) |  // US2_TX (MOSI) on location 1 = PA6 per datasheet section 6.4 = EXP Header pin 4
    (USART_ROUTELOC0_RXLOC_LOC1);   // US2_RX (MISO) on location 1 = PA7 per datasheet section 6.4 = EXP Header pin 6

  MY_USART->ROUTEPEN = USART_ROUTEPEN_TXPEN | USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_CLKPEN | USART_ROUTEPEN_CSPEN;
  MY_USART->CMD      = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
  USART_Enable(MY_USART, usartEnable);
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_SPI_TX_PORT, SL_WFX_HOST_PINOUT_SPI_TX_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_SPI_RX_PORT, SL_WFX_HOST_PINOUT_SPI_RX_PIN, gpioModeInput, 1);
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_SPI_CLK_PORT, SL_WFX_HOST_PINOUT_SPI_CLK_PIN, gpioModePushPull, 0);

#elif defined(EFR32MG21) || defined(EFR32MG24)
  /**********************************************************************
   * Route EUSART1 MOSI, MISO, and SCLK to the specified pins.  CS is
   * not controlled by EUSART1 so there is no write to the corresponding
   * EUSARTROUTE register to do this.
   ****************************************************************************/
  GPIO->EUSARTROUTE[1].TXROUTE = (EUS1MOSI_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
      | (EUS1MOSI_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[1].RXROUTE = (EUS1MISO_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT)
      | (EUS1MISO_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[1].SCLKROUTE = (EUS1SCLK_PORT << _GPIO_EUSART_SCLKROUTE_PORT_SHIFT)
      | (EUS1SCLK_PIN << _GPIO_EUSART_SCLKROUTE_PIN_SHIFT);

  // Enable EUSART interface pins
  GPIO->EUSARTROUTE[1].ROUTEEN = GPIO_EUSART_ROUTEEN_RXPEN |    // MISO
                                 GPIO_EUSART_ROUTEEN_TXPEN |    // MOSI
                                 GPIO_EUSART_ROUTEEN_SCLKPEN;

  // Configure and enable EUSART1
  EUSART_SpiInit(EUSART1, &init);

#else
#error "EFRxx - No UART/HAL"
#endif
}

/********************************************************
 * @fn   sl_wfx_host_gpio_init(void)
 * @brief
 *        Deal with the PINS that are not associated with SPI -
 *        Ie. RESET, Wakeup
 * @return 
 *        None
 **********************************************************/
void sl_wfx_host_gpio_init(void)
{
#if defined(EFR32MG24)
  sl_device_init_hfxo();
  sl_device_init_dpll();
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
#endif
    // Enable GPIO clock.
    CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(WFX_RESET_PIN.port, WFX_RESET_PIN.pin, gpioModePushPull, 1);
  GPIO_PinModeSet(WFX_SLEEP_CONFIRM_PIN.port, WFX_SLEEP_CONFIRM_PIN.pin, gpioModePushPull, 0);

  CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

  // Set up interrupt based callback function - trigger on both edges.
  GPIOINT_Init();
  GPIO_PinModeSet(WFX_INTERRUPT_PIN.port, WFX_INTERRUPT_PIN.pin, gpioModeInputPull, 0);
  GPIO_ExtIntConfig(WFX_INTERRUPT_PIN.port, WFX_INTERRUPT_PIN.pin, SL_WFX_HOST_PINOUT_SPI_IRQ, true, false, true);
  GPIOINT_CallbackRegister(SL_WFX_HOST_PINOUT_SPI_IRQ, rsi_gpio_irq_cb);
  GPIO_IntDisable(1 << SL_WFX_HOST_PINOUT_SPI_IRQ); /* Will be enabled by RSI */

  // Change GPIO interrupt priority (FreeRTOS asserts unless this is done here!)
  NVIC_SetPriority(GPIO_EVEN_IRQn, 5);
  NVIC_SetPriority(GPIO_ODD_IRQn, 5);
}

/*****************************************************************
 * @fn  void sl_wfx_host_reset_chip(void)
 * @brief
 *      To reset the WiFi CHIP
 * @return 
 *      None
 ****************************************************************/
void sl_wfx_host_reset_chip(void)
{
  // Pull it low for at least 1 ms to issue a reset sequence
  GPIO_PinOutClear(WFX_RESET_PIN.port, WFX_RESET_PIN.pin);

  // Delay for 10ms
  vTaskDelay(pdMS_TO_TICKS(10));

  // Hold pin high to get chip out of reset
  GPIO_PinOutSet(WFX_RESET_PIN.port, WFX_RESET_PIN.pin);

  // Delay for 3ms
  vTaskDelay(pdMS_TO_TICKS(3));
}

/*****************************************************************
 * @fn   void rsi_hal_board_init(void)
 * @brief
 *       Initialize the board
 * @return 
 *       None
 ****************************************************************/
void rsi_hal_board_init(void)
{
  spi_sem = xSemaphoreCreateBinaryStatic(&xEfxSpiIntfSemaBuffer);
  xSemaphoreGive(spi_sem);
  WFX_RSI_LOG("RSI_HAL: init GPIO");
  sl_wfx_host_gpio_init();
  WFX_RSI_LOG("RSI_HAL: init SPI");
  sl_wfx_host_init_bus();
  dma_init();
  WFX_RSI_LOG("RSI_HAL: Reset Wifi");
  sl_wfx_host_reset_chip ();
  WFX_RSI_LOG("RSI_HAL: Init done");
}

/*****************************************************************************
*@fn static bool rx_dma_complete(unsigned int channel, unsigned int sequenceNo, void *userParam)
*
*@brief
*    complete dma
*
* @param[in] channel:
* @param[in] sequenceNO: sequence number
* @param[in] userParam :user parameter
*
* @return
*    None
******************************************************************************/
static bool rx_dma_complete(unsigned int channel, unsigned int sequenceNo, void *userParam)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  // WFX_RSI_LOG ("SPI: DMA done [%x,%x,%x,%x]", buf [0], buf [1], buf [2], buf [3]);
  xSemaphoreGiveFromISR(spi_sem, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

  return true;
}

#ifdef RS911X_USE_LDMA
/*****************************************************************************
*@fn static void do_ldma_usart(void *rx_buf, void *tx_buf, uint8_t xlen)
*
*@brief
*    ldma usart
*
* @param[in] rx_buf:
* @param[in] tx_buf:
* @param[in] xlen:
*
* @return
*    None
******************************************************************************/
static void do_ldma_usart(void *rx_buf, void *tx_buf, uint8_t xlen)
{
  LDMA_Descriptor_t ldmaTXDescriptor;
  LDMA_TransferCfg_t ldmaTXConfig;
  LDMA_Descriptor_t ldmaRXDescriptor;
  LDMA_TransferCfg_t ldmaRXConfig;

  WFX_RSI_LOG("SPI: LDMA len=%d", xlen)

  ldmaTXDescriptor = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_M2P_BYTE(tx_buf, &(MY_USART->TXDATA), xlen);
  ldmaTXConfig     = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(MY_USART_TX_SIGNAL);

  ldmaRXDescriptor = (LDMA_Descriptor_t)LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&(MY_USART->RXDATA), rx_buf, xlen);
  ldmaRXConfig     = (LDMA_TransferCfg_t)LDMA_TRANSFER_CFG_PERIPHERAL(MY_USART_RX_SIGNAL);

  // Start both channels
  DMADRV_LdmaStartTransfer(rx_dma_chan, &ldmaRXConfig, &ldmaRXDescriptor, rx_dma_complete, (void *)0);
  DMADRV_LdmaStartTransfer(tx_dma_chan, &ldmaTXConfig, &ldmaTXDescriptor, (DMADRV_Callback_t)0, (void *)0);
}
#endif /*  RS911X_USE_LDMA */

/*************************************************************
 * @fn   static void rx_do_dma(uint8_t *rx_buf, uint16_t xlen)
 * @brief
 *       RX buf was specified
 *       TX buf was not specified by caller - so we
 *       transmit dummy data (typically 0)
 * @param[in] rx_buf:
 * @param[in] xlen:
 * @return
 *        None
 *******************************************************************/
static void rx_do_dma(uint8_t *rx_buf, uint16_t xlen)
{
#ifdef RS911X_USE_LDMA
  do_ldma_usart(rx_buf, (void *)&dummy_data, xlen);
#else
  /*
     * The caller wants to receive data -
     * The xmit can be dummy data (no src increment for tx)
     */
  dummy_data = 0;
  DMADRV_PeripheralMemory(rx_dma_chan,
                          MY_USART_RX_SIGNAL,
                          (void *)rx_buf,
                          (void *)&(MY_USART->RXDATA),
                          true,
                          xlen,
                          dmadrvDataSize1,
                          rx_dma_complete,
                          NULL);

  // Start transmit DMA.
  DMADRV_MemoryPeripheral(tx_dma_chan,
                          MY_USART_TX_SIGNAL,
                          (void *)&(MY_USART->TXDATA),
                          (void *)&(dummy_data),
                          false,
                          xlen,
                          dmadrvDataSize1,
                          NULL,
                          NULL);
#endif
}

/*****************************************************************************
*@fn static void do_ldma_usart(void *rx_buf, void *tx_buf, uint8_t xlen)
*@brief
*    we have a tx_buf. There are some instances where
*    a rx_buf is not specifed. If one is specified then
*    the caller wants results (auto increment src)
* @param[in] rx_buf: 
* @param[in] tx_buf:
* @param[in] xlen:
* @return
*     None
******************************************************************************/
static void tx_do_dma(uint8_t *rx_buf, uint8_t *tx_buf, uint16_t xlen)
{
#ifdef RS911X_USE_LDMA
  do_ldma_usart(rx_buf, tx_buf, xlen);
#else
  void *buf;
  bool srcinc;
  /*
     * TODO - the caller specified 8/32 bit - we should use this
     * instead of dmadrvDataSize1 always
     */
  if (rx_buf == (uint8_t *)0) {
    buf    = &dummy_data;
    srcinc = false;
  } else {
    buf                   = rx_buf;
    srcinc                = true;
    /* DEBUG */ rx_buf[0] = 0xAA;
    rx_buf[1]             = 0x55;
  }
  DMADRV_PeripheralMemory(rx_dma_chan,
                          MY_USART_RX_SIGNAL,
                          buf,
                          (void *)&(MY_USART->RXDATA),
                          srcinc,
                          xlen,
                          dmadrvDataSize1,
                          rx_dma_complete,
                          buf);
  // Start transmit DMA.
  DMADRV_MemoryPeripheral(tx_dma_chan,
                          MY_USART_TX_SIGNAL,
                          (void *)&(MY_USART->TXDATA),
                          (void *)tx_buf,
                          true,
                          xlen,
                          dmadrvDataSize1,
                          NULL,
                          NULL);
#endif /* USE_LDMA */
}

/*********************************************************************
 * @fn   int16_t rsi_spi_transfer(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t xlen, uint8_t mode)
 * @brief
 *       Do a SPI transfer - Mode is 8/16 bit - But every 8 bit is aligned
 * @param[in] tx_buf:
 * @param[in] rx_buf:
 * @param[in] xlen:
 * @param[in] mode:
 * @return
 *        None
 **************************************************************************/
int16_t rsi_spi_transfer(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t xlen, uint8_t mode)
{
  // WFX_RSI_LOG ("SPI: Xfer: tx=%x,rx=%x,len=%d",(uint32_t)tx_buf, (uint32_t)rx_buf, xlen);
#ifdef not_yet_tested_programmed_io
  while (!(MY_USART->STATUS & USART_STATUS_TXBL)) {
  }
  MY_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;

  /*
     * Short stuff should be done via programmed I/O
     */
  if (xlen < 16 && tx_buf && !rx_buf) {
    for (; xlen > 0; --xlen, ++tx_buf) {
      MY_USART->TXDATA = (uint32_t)(*txbuf);

      while (!(MY_USART->STATUS & USART_STATUS_TXC)) {
      }
    }
    while (!(MY_USART->STATUS & USART_STATUS_TXBL)) {
    }
  }
#endif /* not_yet_tested_programmed_io */
  if (xlen > 0) {
    MY_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    if (xSemaphoreTake(spi_sem, portMAX_DELAY) != pdTRUE) {
      return RSI_FALSE;
    }
    if (tx_buf == (void *)0) {
      rx_do_dma(rx_buf, xlen);
    } else {
      tx_do_dma(rx_buf, tx_buf, xlen);
    }
    /*
         * Wait for the call-back to complete
         */
    if (xSemaphoreTake(spi_sem, portMAX_DELAY) == pdTRUE) {
      xSemaphoreGive(spi_sem);
    }
  }

  return RSI_ERROR_NONE;
}
