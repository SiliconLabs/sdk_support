/***************************************************************************//**
 * @file
 * @brief EFM32 internal SPI protocol implementation for use with the
 *   standalone ezsp spi bootloader.
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
#include "em_gpio.h"
#include "em_usart.h"
#include "em_ldma.h"
#include "em_cmu.h"
#include "em_bus.h"
#include "em_core.h"
#include "em_chip.h"
#include "em_emu.h"
#include "spidrv.h"
#include "gpiointerrupt.h"
#include "spi-protocol-device.h"
#include "btl-ezsp-spi-protocol.h"
#include "btl-ezsp-spi-device.h"

static const USART_InitSync_TypeDef initUsartData = SPI_BTL_USART_INIT;

SPIDRV_Init_t btlEzspSpi = SPI_NCP_USART_INIT;

// LDMA Assignments

// LDMA Rx and Tx Configurations
LDMA_TransferCfg_t periTransferRx = LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART1_RXDATAV);
LDMA_TransferCfg_t periTransferTx = LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_USART1_TXEMPTY);

// LDMA Rx and Tx Descriptors
LDMA_Descriptor_t rxDescriptor = LDMA_DESCRIPTOR_SINGLE_P2M_BYTE(&USART1->RXDATA,
                                                                 (uint32_t)halHostCommandBuffer,
                                                                 SPIP_BUFFER_SIZE);

LDMA_Descriptor_t txDescriptor = LDMA_DESCRIPTOR_SINGLE_M2P_BYTE((uint32_t)halHostResponseBuffer,
                                                                 &USART1->TXDATA,
                                                                 SPIP_BUFFER_SIZE);

const uint8_t rxChannel = 0;                // LDMA channel 0 for rx
const uint8_t txChannel = 1;                // LDMA channel 1 for tx

LDMA_Init_t initLdmaData = LDMA_INIT_DEFAULT;   // use default initialization

void ezspSetupSpiAndDma(void)
{
  uint32_t resetRouteloc = 0x00000000;
  // USART SPI initialization
  USART_InitSync(SPI_NCP_USART, &initUsartData);    // initialize the uart in spi mode

  SPI_NCP_USART->ROUTELOC0 = resetRouteloc;
  SPI_NCP_USART->ROUTELOC0 |= (btlEzspSpi.portLocationRx << _USART_ROUTELOC0_RXLOC_SHIFT);
  SPI_NCP_USART->ROUTELOC0 |= (btlEzspSpi.portLocationTx << _USART_ROUTELOC0_TXLOC_SHIFT);
  SPI_NCP_USART->ROUTELOC0 |= (btlEzspSpi.portLocationClk << _USART_ROUTELOC0_CLKLOC_SHIFT);
  SPI_NCP_USART->ROUTELOC0 |= (btlEzspSpi.portLocationCs << _USART_ROUTELOC0_CSLOC_SHIFT);

  SPI_NCP_USART->ROUTEPEN |= USART_ROUTEPEN_RXPEN;
  SPI_NCP_USART->ROUTEPEN |= USART_ROUTEPEN_TXPEN;
  SPI_NCP_USART->ROUTEPEN |= USART_ROUTEPEN_CSPEN;
  SPI_NCP_USART->ROUTEPEN |= USART_ROUTEPEN_CLKPEN;

  LDMA->CH[0].DST = (uint32_t)halHostCommandBuffer;
  LDMA->CH[1].DST = (uint32_t)halHostResponseBuffer;

  SPI_NCP_USART->IEN |= USART_IEN_RXDATAV;    // enable rxdatav interrupt

  LDMA_IntClear(0xFFFFFFFF);           // clear channel done interrupts

  LDMA->CHEN    = 0;    // disable all channels
  LDMA->REQDIS  = 0;    // enable all peripheral requests

  NVIC_ClearPendingIRQ(LDMA_IRQn);

  // disable rx and tx in usart just in case so LDMA transfer won't start prematurely
  USART_Enable(SPI_NCP_USART, usartDisable);

  LDMA_StartTransfer(rxChannel, &periTransferRx, &rxDescriptor);

  BUS_RegMaskedClear(&LDMA->CHEN, 1 << rxChannel);

  USART_Enable(SPI_NCP_USART, usartEnable);  // enable the rx and tx in uart

  if (nSSEL_IS_NEGATED()) {
    LDMA_IntEnable((uint32_t)1 << rxChannel);    // enable transfer complete interrupt for rxChannel
    BUS_RegMaskedSet(&LDMA->CHEN, 1 << rxChannel);  //Enable receive channel.
  }
}

void ezspSpiInitSpiAndDma(void)
{
  CMU_HFXOInit_TypeDef hfxoInit = BSP_CLK_HFXO_INIT;
  CMU_HFXOInit(&hfxoInit);
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(SPI_NCP_USART_CLOCK, true);

  LDMA_Init(&initLdmaData);

  // LDMA_Init always enables the IRQ, explicitly disable as bootloaders don't
  // handle interrupts
  NVIC_DisableIRQ(LDMA_IRQn);
}

void configureSpiGpio(void)
{
  GPIO_PinModeSet(SPI_NCP_MOSI_PORT, SPI_NCP_MOSI_PIN, gpioModeInputPull, 1);
  GPIO_PinModeSet(SPI_NCP_MISO_PORT, SPI_NCP_MISO_PIN, gpioModePushPull, 0);
  GPIO_PinModeSet(SPI_NCP_CLK_PORT, SPI_NCP_CLK_PIN, gpioModeInputPull, 1);
  GPIO_PinModeSet(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN, gpioModeInputPullFilter, 1);
}

void ezspSpiConfigureInterrupts(void)
{
  ////---- Configure nWAKE interrupt ----////
  //start from a fresh state just in case
#if (!defined(DISABLE_NWAKE)) && (!defined(HAL_CONFIG) || defined(BSP_SPINCP_NWAKE_PIN))
  GPIO->EXTIFALL = 0 << BSP_SPINCP_NWAKE_PIN; // disable triggering
  // configure nwake pin
  GPIO_IntConfig(BSP_SPINCP_NWAKE_PORT,
                 BSP_SPINCP_NWAKE_PIN,
                 false,
                 true,  // falling edge
                 false);
  GPIO_PinModeSet(BSP_SPINCP_NWAKE_PORT,
                  BSP_SPINCP_NWAKE_PIN,
                  gpioModeInputPullFilter,  // input with pullup
                  1);
#endif

  ////---- Configure nSSEL interrupt ----////
  GPIO->EXTIRISE = 0 << SPI_NCP_CS_PIN; // disable triggering
  GPIO_IntConfig(SPI_NCP_CS_PORT, SPI_NCP_CS_PIN, true, false, false);

  ////---- Configure nHOST_INT output ----////
  GPIO_PinModeSet(BSP_SPINCP_NHOSTINT_PORT,
                  BSP_SPINCP_NHOSTINT_PIN,
                  gpioModePushPull,
                  1);

  // ----- Account for Noise and Crosstalk ------ //
  // on some hardware configurations there is a lot of noise and bootloading can fail
  // due to crosstalk. to avoid this, the slewrate is lowered here from 5 to 4, and the
  // drivestrength is lowered from 10mA to 1mA. if noise related errors still occur,
  // the slewrate can be lowered further
  GPIO_SlewrateSet(BSP_SPINCP_NHOSTINT_PORT, 4, 4);
  // the drivestrength is lowered from 10mA to 1mA by setting DRIVESTRENGTH to 1
#if defined (_GPIO_P_CTRL_DRIVEMODE_MASK)
  GPIO_DriveStrengthSet(BSP_SPINCP_NHOSTINT_PORT, 1);
#endif
}

void ezspSpiDisableReceptionInterrupts(void)
{
  // do nothing, not needed on efr32
}

void ezspSpiDisableReception(void)
{
  BUS_RegMaskedClear(&LDMA->CHEN, 1 << rxChannel);
}

void ezspSpiAckUnload(void)
{
  // do nothing, not needed on efr32
}

void ezspSpiEnableReception(void)
{
  LDMA_IntEnable(1 << rxChannel);    // enable transfer complete int for rxChannel
  BUS_RegMaskedSet(&LDMA->CHEN, 1 << rxChannel);   //Enable receive channel.
}

void ezspSpiStartTxTransfer(uint8_t responseLength)
{
  LDMA_StartTransfer(txChannel, &periTransferTx, &txDescriptor);
}

bool ezspSpiRxActive(void)
{
  if (BUS_RegMaskedRead(&LDMA->CHEN, 1 << rxChannel) == 0) {
    return false;
  } else {
    return true;
  }
}

void ezspSpiFlushRxFifo(void)
{
  volatile uint8_t dummy;
  // efr32 buffer is 3 so read 3 dummy bytes
  dummy = (uint8_t)SPI_NCP_USART->RXDATA;
  dummy = (uint8_t)SPI_NCP_USART->RXDATA;
  dummy = (uint8_t)SPI_NCP_USART->RXDATA;
}

bool ezspSpiValidStartOfData(void)
{
  // check for valid start of data (CH[0].DST has moved from start)
  // check for unloaded buffer
  if (BUS_RegMaskedRead(&LDMA->CH[0].DST, 0xFFFFFFFF) > (uint32_t)&halHostCommandBuffer
      || BUS_RegMaskedRead(&LDMA->CHDONE, 1 << rxChannel)) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiCheckIfUnloaded(void)
{
  // efr32 doesn't need to do this
  return false;
}

bool ezspSpiHaveTwoBytes(void)
{
  // check that DST has moved at least 2 places
  if (BUS_RegMaskedRead(&LDMA->CH[0].DST, 0xFFFFFFFF)
      >= ((uint32_t)&halHostCommandBuffer + 0x2)) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiHaveAllData(void)
{
  if (BUS_RegMaskedRead(&LDMA->CH[0].DST, 0xFFFFFFFF)
      >= ((uint32_t)&halHostCommandBuffer + halHostCommandBuffer[1] + 0x3)) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiPollForMosi(uint8_t responseLength)
{
  if ((BUS_RegMaskedRead(&LDMA->CH[0].DST, 0xFFFFFFFF) > (uint32_t)&halHostCommandBuffer)
      && (responseLength <= 0)) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiPollForNWAKE(void)
{
  #if (!defined(DISABLE_NWAKE)) && (!defined(HAL_CONFIG) || defined(BSP_SPINCP_NWAKE_PIN))
  if ((GPIO_IntGet() & ((uint32_t)1 << BSP_SPINCP_NWAKE_PIN)) == ((uint32_t)1 << BSP_SPINCP_NWAKE_PIN)) {
    // ack int before read to avoid potential of missing interrupt
    GPIO_IntClear((uint32_t)1 << BSP_SPINCP_NWAKE_PIN);  // clears the nWAKE interrupt flag
    return true;
  } else {
    return false;
  }
  #else
  return false;
  #endif
}

bool ezspSpiPollForNSSEL(void)
{
  if ((GPIO_IntGet() & ((uint32_t)1 << SPI_NCP_CS_PIN)) == ((uint32_t)1 << SPI_NCP_CS_PIN)) {
    // ack int before read to avoid potential of missing interrupt
    GPIO_IntClear((uint32_t)1 << SPI_NCP_CS_PIN);  // clears the nSSEL interrupt flag
    return true;
  } else {
    return false;
  }
}

bool ezspSpiTransactionValid(uint8_t responseLength)
{
  // not implemented
  return true;
}
