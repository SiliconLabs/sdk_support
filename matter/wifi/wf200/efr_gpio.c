#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "em_bus.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_usart.h"
#include "gpiointerrupt.h"

#include "AppConfig.h"
#include "sl_wfx_board.h"
#include "sl_wfx_host.h"
#include "sl_wfx_task.h"
#include "wfx_host_events.h"

extern uint8_t wirq_irq_nb;
/*
 * IRQ for SPI callback
 * Clear the Interrupt and wake up the task that
 * handles the actions of the interrupt (typically - wfx_bus_task ())
 */
static void sl_wfx_spi_wakeup_irq_callback(uint8_t irqNumber)
{
  BaseType_t bus_task_woken;
  uint32_t interrupt_mask;

  if (irqNumber != wirq_irq_nb)
    return;
  // Get and clear all pending GPIO interrupts
  interrupt_mask = GPIO_IntGet();
  GPIO_IntClear(interrupt_mask);
  bus_task_woken = pdFALSE;
  xSemaphoreGiveFromISR(wfx_wakeup_sem, &bus_task_woken);
  vTaskNotifyGiveFromISR(wfx_bus_task_handle, &bus_task_woken);
  portYIELD_FROM_ISR(bus_task_woken);
}

/****************************************************************************
 * Init some actions pins to the WF-200 expansion board
 *****************************************************************************/
void sl_wfx_host_gpio_init(void)
{
  EFR32_LOG("WIFI: GPIO Init:IRQ=%d", wirq_irq_nb);
  // Enable GPIO clock.
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure WF200 reset pin.
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_RESET_PORT, SL_WFX_HOST_PINOUT_RESET_PIN, gpioModePushPull, 0);
  // Configure WF200 WUP pin.
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_WUP_PORT, SL_WFX_HOST_PINOUT_WUP_PIN, gpioModePushPull, 0);

  // GPIO used as IRQ.
  GPIO_PinModeSet(SL_WFX_HOST_PINOUT_SPI_WIRQ_PORT, SL_WFX_HOST_PINOUT_SPI_WIRQ_PIN, gpioModeInputPull, 0);
  CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

  // Set up interrupt based callback function - trigger on both edges.
  GPIOINT_Init();
  GPIO_ExtIntConfig(SL_WFX_HOST_PINOUT_SPI_WIRQ_PORT,
                    SL_WFX_HOST_PINOUT_SPI_WIRQ_PIN,
                    wirq_irq_nb,
                    true,
                    false,
                    false); /* Don't enable it */

  GPIOINT_CallbackRegister(wirq_irq_nb, sl_wfx_spi_wakeup_irq_callback);

  // Change GPIO interrupt priority (FreeRTOS asserts unless this is done here!)
  NVIC_ClearPendingIRQ(1 << wirq_irq_nb);
  NVIC_SetPriority(GPIO_EVEN_IRQn, 5);
  NVIC_SetPriority(GPIO_ODD_IRQn, 5);
}
