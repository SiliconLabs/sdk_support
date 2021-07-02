/***************************************************************************//**
 * @file
 * @brief Memory LCD interface
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_memlcd.h"
#include "sl_memlcd_display.h"
#include "sl_sleeptimer.h"
#include "sl_udelay.h"
#include "em_gpio.h"
#include <string.h>

#define CMD_UPDATE        0x01
#define CMD_ALL_CLEAR     0x04

/* Concatenate preprocessor tokens A and B. */
#define SL_CONCAT(A, B) A ## B

/* Generate the cmu clock symbol based on instance. */
#if defined(SL_MEMLCD_USE_USART)
#define SL_MEMLCD_SPI_CLOCK(N) SL_CONCAT(cmuClock_USART, N)
#elif defined(SL_MEMLCD_USE_EUSART)
#define SL_MEMLCD_SPI_CLOCK(N) SL_CONCAT(cmuClock_EUSART, N)
#endif

#if defined(SL_MEMLCD_EXTCOMIN_PORT)
/** Timer used for periodic maintenance of the display. */
static sl_sleeptimer_timer_handle_t extcomin_timer;

static void extcomin_toggle(sl_sleeptimer_timer_handle_t *handle, void *data);
#endif

#if defined(SL_MEMLCD_LPM013M126A)
/** Utility function to reverse bits for the LPM013M126A. */
static uint8_t reverse_bits(uint8_t data);
#endif

/** Memory lcd instance. This variable will be initialized in the
 *  @ref sl_memlcd_configure() function. */
static sl_memlcd_t memlcd_instance;

/** Flag to monitor is this driver has been initialized. The memlcd_instance
 *  is only valid after initialized=true. */
static bool initialized = false;

/** SPI handle to use for SPI communication to the memory lcd. */
#if defined(SL_MEMLCD_USE_EUSART)
static sli_memlcd_spi_handle_t spi_handle = {
  .eusart     = SL_MEMLCD_SPI_PERIPHERAL,
  .clock      = SL_MEMLCD_SPI_CLOCK(SL_MEMLCD_SPI_PERIPHERAL_NO),
  .mosi_port  = SL_MEMLCD_SPI_TX_PORT,
  .mosi_pin   = SL_MEMLCD_SPI_TX_PIN,
  .miso_port  = SL_MEMLCD_SPI_VALUE_NONE,
  .miso_pin   = SL_MEMLCD_SPI_VALUE_NONE,
  .sclk_port  = SL_MEMLCD_SPI_SCLK_PORT,
  .sclk_pin   = SL_MEMLCD_SPI_SCLK_PIN,
};
#elif defined(SL_MEMLCD_USE_USART)
static sli_memlcd_spi_handle_t spi_handle = {
  .usart     = SL_MEMLCD_SPI_PERIPHERAL,
  .clock     = SL_MEMLCD_SPI_CLOCK(SL_MEMLCD_SPI_PERIPHERAL_NO),
  .mosi_port = SL_MEMLCD_SPI_TX_PORT,
  .mosi_pin  = SL_MEMLCD_SPI_TX_PIN,
  .miso_port = SL_MEMLCD_SPI_VALUE_NONE,
  .miso_pin  = SL_MEMLCD_SPI_VALUE_NONE,
  .clk_port  = SL_MEMLCD_SPI_CLK_PORT,
  .clk_pin   = SL_MEMLCD_SPI_CLK_PIN,
#if defined(_SILICON_LABS_32B_SERIES_0)
  .loc       = SL_MEMLCD_SPI_ROUTE_LOC,
#elif defined(_SILICON_LABS_32B_SERIES_1)
  .mosi_loc  = SL_MEMLCD_SPI_TX_LOC,
  .miso_loc  = SL_MEMLCD_SPI_VALUE_NONE,
  .clk_loc   = SL_MEMLCD_SPI_CLK_LOC,
#endif
};
#endif

sl_status_t sl_memlcd_configure(struct sl_memlcd_t *device)
{
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Initialize the SPI bus. */
#if defined(SL_MEMLCD_USE_EUSART)
  sli_memlcd_spi_init(&spi_handle, device->spi_freq, eusartClockMode0);
#elif defined(SL_MEMLCD_USE_USART)
  sli_memlcd_spi_init(&spi_handle, device->spi_freq, usartClockMode0);
#endif

  /* Setup GPIOs */
  GPIO_PinModeSet(SL_MEMLCD_SPI_CS_PORT, SL_MEMLCD_SPI_CS_PIN, gpioModePushPull, 0);
#if defined(SL_MEMLCD_EXTCOMIN_PORT)
  GPIO_PinModeSet(SL_MEMLCD_EXTCOMIN_PORT, SL_MEMLCD_EXTCOMIN_PIN, gpioModePushPull, 0);
#endif

  memlcd_instance = *device;
  initialized = true;
  sl_memlcd_power_on(device, true);
  sl_memlcd_clear(device);

  return SL_STATUS_OK;
}

sl_status_t sl_memlcd_refresh(const struct sl_memlcd_t *device)
{
  #if defined(SL_MEMLCD_USE_EUSART)
  sli_memlcd_spi_init(&spi_handle, device->spi_freq, eusartClockMode0);
  #elif defined(SL_MEMLCD_USE_USART)
  sli_memlcd_spi_init(&spi_handle, device->spi_freq, usartClockMode0);
  #endif

  return SL_STATUS_OK;
}

sl_status_t sl_memlcd_power_on(const struct sl_memlcd_t *device, bool on)
{
  (void) device;
  (void) on;
  sl_status_t status = SL_STATUS_OK;

#if defined(SL_MEMLCD_EXTCOMIN_PORT)
  if (on) {
    uint32_t freq = sl_sleeptimer_get_timer_frequency();
    status = sl_sleeptimer_restart_periodic_timer(&extcomin_timer,
                                                  freq / (device->extcomin_freq * 2),
                                                  extcomin_toggle,
                                                  NULL,
                                                  0,
                                                  SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
  } else {
    status = sl_sleeptimer_stop_timer(&extcomin_timer);
  }
#endif

  return status;
}

sl_status_t sl_memlcd_clear(const struct sl_memlcd_t *device)
{
  uint16_t cmd;

  /* Set SCS */
  GPIO_PinOutSet(SL_MEMLCD_SPI_CS_PORT, SL_MEMLCD_SPI_CS_PIN);

  /* SCS setup time */
  sl_udelay_wait(device->setup_us);

  /* Send command */
  cmd = CMD_ALL_CLEAR;
  sli_memlcd_spi_tx(&spi_handle, &cmd, 2);
  sli_memlcd_spi_wait(&spi_handle);

  /* SCS hold time */
  sl_udelay_wait(device->hold_us);

  /* Clear SCS */
  GPIO_PinOutClear(SL_MEMLCD_SPI_CS_PORT, SL_MEMLCD_SPI_CS_PIN);

  return SL_STATUS_OK;
}

sl_status_t sl_memlcd_draw(const struct sl_memlcd_t *device, const void *data, unsigned int row_start, unsigned int row_count)
{
  unsigned int i;
  const uint8_t *p = data;
  uint16_t cmd;
  int row_len;
#if defined(SL_MEMLCD_LPM013M126A)
  uint8_t reversed_row;
#endif

  row_len = (device->width * device->bpp) / 8;
  row_start++;

  /* Assert SCS */
  GPIO_PinOutSet(SL_MEMLCD_SPI_CS_PORT, SL_MEMLCD_SPI_CS_PIN);

  /* SCS setup time */
  sl_udelay_wait(device->setup_us);

#if defined(SL_MEMLCD_LPM013M126A)
  /* LPM013M126A uses MSB first for the row */
  reversed_row = reverse_bits((uint8_t)row_start);

  /* Send update command and first line address */
  /* CMD_UPDATE is only 6 bits and the address line is 10 bits
     but the first two bits of address are always 00 so this works */
  cmd = CMD_UPDATE | (reversed_row << 8);
#else
  /* Send update command and first line address */
  cmd = CMD_UPDATE | (row_start << 8);
#endif

  sli_memlcd_spi_tx(&spi_handle, &cmd, 2);

  /* Get start address to draw from */
  for ( i = 0; i < row_count; i++ ) {
    /* Send pixels for this line */
    sli_memlcd_spi_tx(&spi_handle, p, row_len);
    p += row_len;

    if (i == row_count - 1) {
      cmd = 0xffff;
    } else {
#if defined(SL_MEMLCD_LPM013M126A)
  /* LPM013M126A uses MSB first for the row */
  reversed_row = reverse_bits((uint8_t)row_start + i + 1);

  /* Send update command and line address */
  /* CMD_UPDATE is only 6 bits and the address line is 10 bits
     but the first two bits of address are always 00 so this works */
      cmd = 0x3f | (reversed_row << 8);
#else
      cmd = 0xff | ((row_start + i + 1) << 8);
#endif
    }
    sli_memlcd_spi_tx(&spi_handle, &cmd, 2);
  }

  sli_memlcd_spi_wait(&spi_handle);

  /* SCS hold time */
  sl_udelay_wait(device->hold_us);

  /* De-assert SCS */
  GPIO_PinOutClear(SL_MEMLCD_SPI_CS_PORT, SL_MEMLCD_SPI_CS_PIN);

  return SL_STATUS_OK;
}

const sl_memlcd_t *sl_memlcd_get(void)
{
  if (initialized) {
    return &memlcd_instance; 
  } else {
    return NULL;
  }
}

#if defined (SL_MEMLCD_EXTCOMIN_PORT)
/**************************************************************************//**
 * @brief
 *   Inverse polarity across the Liquid Crystal cells in the display.
 *
 * @detail
 *   This function inverses the polarity across the Liquid Crystal cells
 *   in the LCD. Must be called at least every second.
 *****************************************************************************/
static void extcomin_toggle(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void) handle;
  (void) data;

  GPIO_PinOutToggle(SL_MEMLCD_EXTCOMIN_PORT, SL_MEMLCD_EXTCOMIN_PIN);
}

#if defined(SL_MEMLCD_LPM013M126A)
/**************************************************************************//**
 * @brief
 *   Reverse the bits of a unit8_t to make the transform from LSB to MSB and
 *   vice-versa.
 *****************************************************************************/
static uint8_t reverse_bits(uint8_t data)
{
    // Ex: data = 0b01101100 ==> data = 0b11000110
    data = ((data & 0xF0) >> 4) | ((data & 0x0F) << 4);

    // Ex: data = 0b11000110 ==> data = 0b00111001
    data = ((data & 0xCC) >> 2) | ((data & 0x33) << 2);

    // Ex: data = 0b00111001 ==> data = 0b00110110
    data = ((data & 0xAA) >> 1) | ((data & 0x55) << 1);

    return data;
}
#endif // SL_MEMLCD_LPM013M126A
#endif
