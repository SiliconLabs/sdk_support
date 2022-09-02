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
#include "spidrv.h"

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

static SemaphoreHandle_t spi_sem;

#if defined(EFR32MG12)
extern SPIDRV_Handle_t sl_spidrv_exp_handle;
#elif defined(EFR32MG24)
extern SPIDRV_Handle_t sl_spidrv_eusart_exp_handle;
#endif

static unsigned int tx_dma_channel;
static unsigned int rx_dma_channel;

/*TODO -  FIX This - It belongs somewhere else depending on which USART is used */
static uint32_t dummy_data; /* Used for DMA - when results don't matter */
extern void rsi_gpio_irq_cb(uint8_t irqnum);
//#define RS911X_USE_LDMA

/*
 * Deal with the PINS that are not associated with SPI -
 * Ie. RESET, Wakeup
 */
void sl_wfx_host_gpio_init(void)
{
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
/*
 * To reset the WiFi CHIP
 */
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
void rsi_hal_board_init(void)
{
  spi_sem = xSemaphoreCreateBinary();
  xSemaphoreGive(spi_sem);

  /* Assign DMA channel from Handle*/
#if defined(EFR32MG12)
  tx_dma_channel= sl_spidrv_exp_handle->txDMACh;
  rx_dma_channel= sl_spidrv_exp_handle->rxDMACh;

#elif defined(EFR32MG24)
  tx_dma_channel= sl_spidrv_eusart_exp_handle->txDMACh;
  rx_dma_channel= sl_spidrv_eusart_exp_handle->rxDMACh;
#endif

  WFX_RSI_LOG("RSI_HAL: init GPIO");
  sl_wfx_host_gpio_init();
  WFX_RSI_LOG("RSI_HAL: Reset Wifi");
  sl_wfx_host_reset_chip ();
  WFX_RSI_LOG("RSI_HAL: Init done");
}

static bool rx_dma_complete(unsigned int channel, unsigned int sequenceNo, void *userParam)
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  // uint8_t *buf = (void *)userParam;

  (void)channel;
  (void)sequenceNo;
  (void)userParam;

  // WFX_RSI_LOG ("SPI: DMA done [%x,%x,%x,%x]", buf [0], buf [1], buf [2], buf [3]);
  xSemaphoreGiveFromISR(spi_sem, &xHigherPriorityTaskWoken);
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

  return true;
}

/*
 * RX buf was specified
 * TX buf was not specified by caller - so we
 * transmit dummy data (typically 0
 */
static void receiveDMA(uint8_t *rx_buf, uint16_t xlen)
{
  /*
     * The caller wants to receive data -
     * The xmit can be dummy data (no src increment for tx)
     */
  dummy_data = 0;
  DMADRV_PeripheralMemory(rx_dma_channel,
                          MY_USART_RX_SIGNAL,
                          (void *)rx_buf,
                          (void *)&(MY_USART->RXDATA),
                          true,
                          xlen,
                          dmadrvDataSize1,
                          rx_dma_complete,
                          NULL);

  // Start transmit DMA.
  DMADRV_MemoryPeripheral(tx_dma_channel,
                          MY_USART_TX_SIGNAL,
                          (void *)&(MY_USART->TXDATA),
                          (void *)&(dummy_data),
                          false,
                          xlen,
                          dmadrvDataSize1,
                          NULL,
                          NULL);
}
static void transmitDMA(uint8_t *rx_buf, uint8_t *tx_buf, uint16_t xlen)
{
  void *buf;
  bool srcinc;
  /*
     * we have a tx_buf. There are some instances where
     * a rx_buf is not specifed. If one is specified then
     * the caller wants results (auto increment src)
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
  DMADRV_PeripheralMemory(rx_dma_channel,
                          MY_USART_RX_SIGNAL,
                          buf,
                          (void *)&(MY_USART->RXDATA),
                          srcinc,
                          xlen,
                          dmadrvDataSize1,
                          rx_dma_complete,
                          buf);
  // Start transmit DMA.
  DMADRV_MemoryPeripheral(tx_dma_channel,
                          MY_USART_TX_SIGNAL,
                          (void *)&(MY_USART->TXDATA),
                          (void *)tx_buf,
                          true,
                          xlen,
                          dmadrvDataSize1,
                          NULL,
                          NULL);
}
/*
 * Do a SPI transfer - Mode is 8/16 bit - But every 8 bit is aligned
 */
int16_t rsi_spi_transfer(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t xlen, uint8_t mode)
{
  // WFX_RSI_LOG ("SPI: Xfer: tx=%x,rx=%x,len=%d",(uint32_t)tx_buf, (uint32_t)rx_buf, xlen);
  if (xlen > 0) {
    MY_USART->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
    if (xSemaphoreTake(spi_sem, portMAX_DELAY) != pdTRUE) {
      return RSI_FALSE;
    }
    if (tx_buf == (void *)0) {
      receiveDMA(rx_buf, xlen);
    } else {
      transmitDMA(rx_buf, tx_buf, xlen);
    }
    // vTaskDelay(pdMS_TO_TICKS(10));
    /*
         * Wait for the call-back to complete
         */
    if (xSemaphoreTake(spi_sem, portMAX_DELAY) == pdTRUE) {
      xSemaphoreGive(spi_sem);
    }
  }

  return RSI_ERROR_NONE;
}
