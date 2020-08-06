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
#include "btl-ezsp-spi-protocol.h"
#include "hal/micro/cortexm3/ezsp-spi-serial-controller-autoselect.h"
#include "btl-ezsp-spi-device.h"

void ezspSetupSpiAndDma(void)
{
  // Make SPI peripheral clean and start a-new
  INT_SCxCFG &= ~EVENT_SC12_CFG_RXVAL;   //disable byte received interrupt
  INT_SCxCFG &= ~EVENT_SC12_CFG_RXULDA;  //disable buffer A unload interrupt
  SCx_REG(DMACTRL) = SC_DMACTRL_RXDMARST;    //reset DMA just in case
  SCx_REG(DMACTRL) = SC_DMACTRL_TXDMARST;    //reset DMA just in case
  SCx_REG(MODE) = SCx_MODE(DISABLED); //be safe, make sure we start from disabled
  SCx_REG(RATELIN) =  0; //no effect in slave mode
  SCx_REG(RATEEXP) =  0; //no effect in slave mode
  SCx_REG(SPICFG)  =  (0 << _SC_SPICFG_SPIMST_SHIFT)    //slave mode
                     | (0 << _SC_SPICFG_SPIPHA_SHIFT)   //SPI Mode 0 - sample leading edge
                     | (0 << _SC_SPICFG_SPIPOL_SHIFT)   //SPI Mode 0 - rising leading edge
                     | (0 << _SC_SPICFG_SPIORD_SHIFT)   //MSB first
                     | (0 << _SC_SPICFG_SPIRXDRV_SHIFT) //no effect in slave mode
                     | (0 << _SC_SPICFG_SPIRPT_SHIFT);  //transmit 0xFF when no data to send
  SCx_REG(MODE)   =  SCx_MODE(SPI); //activate SPI mode
  //Configure DMA RX channel to point to the command buffer
  SCx_REG(RXBEGA) = (uint32_t) halHostCommandBuffer;
  SCx_REG(RXENDA) = (uint32_t) halHostCommandBuffer + SPIP_BUFFER_SIZE - 1;
  //Configure DMA TX channel to point to the response buffer
  SCx_REG(TXBEGA) = (uint32_t) halHostResponseBuffer;
  SCx_REG(TXENDA) = (uint32_t) halHostResponseBuffer + SPIP_BUFFER_SIZE - 1;
  if (nSSEL_IS_NEGATED()) { //only activate DMA if nSSEL is idle
    //since bootloader is polling driven, do not enable ISRs!
    INT_SCxCFG |= EVENT_SC12_CFG_RXVAL; //enable byte received interrupt
    INT_SCxCFG |= EVENT_SC12_CFG_RXULDA;//enable RX buffer A unload interrupt
    SCx_REG(DMACTRL) = SC_DMACTRL_RXLODA;  //activate RX DMA for first command
  }
  INT_SCxFLAG = 0xFFFF;     //clear any stale interrupts
  //since bootloader is polling driven, do not enable top-level SCx interrupts!
  //  NVIC_EnableIRQ(INT_SCx);     // no interrupts in bootloader!
}

void ezspSpiInitSpiAndDma(void)
{
  // do nothing, no additional code needed for em3xx
}

void configureSpiGpio(void)
{
  ////---- Configure basic SPI Pins: MOSI, MISO, SCLK and nSSEL ----////
  CFG_SPI_GPIO();
  PULLUP_nSSEL();
}

void ezspSpiConfigureInterrupts(void)
{
  ////---- Configure nWAKE interrupt ----////
  //start from a fresh state just in case
  NVIC_DisableIRQ(nWAKE_INT);               //disable triggering
  nWAKE_INTCFG = (EVENT_GPIO_CFGx_MOD_DISABLED);
  //Configure nWAKE pin
  CFG_nWAKE(_GPIO_P_CFGL_Px0_IN_PUD);              //input with pullup
  PULLUP_nWAKE();
  //Enable Interrupts
  EVENT_GPIO->FLAG = nWAKE_GPIOFLAG;        //clear stale interrupts
  NVIC_ClearPendingIRQ(nWAKE_INT);
  //  NVIC_EnableIRQ(nWAKE_INT);             // no interrupts in bootloader!
  nWAKE_INTCFG =  (0 << _EVENT_GPIO_CFGA_FILT_SHIFT)       //no filter
                 | (EVENT_GPIO_CFGx_MOD_FALLING_EDGE);

  ////---- Configure nSSEL_INT for compatibility with EM260 ----////
  CFG_nSSEL_INT(_GPIO_P_CFGL_Px0_IN);              //input floating - not used

  ////---- Configure nSSEL interrupt (IRQC) ----////
  NVIC_DisableIRQ(nSSEL_INT);                 //disable triggering
  nSSEL_INTCFG = (EVENT_GPIO_CFGx_MOD_DISABLED);
  nSSEL_IRQSEL = nSSEL_IRQSEL_MASK;     //assign nSSEL pin to IRQC
  //Enable Interrupts
  EVENT_GPIO->FLAG = nSSEL_GPIOFLAG;        //clear stale interrupts
  NVIC_ClearPendingIRQ(nSSEL_INT);
  //  NVIC_EnableIRQ(nSSEL_INT);             // no interrupts in bootloader!
  nSSEL_INTCFG = (0 << _EVENT_GPIO_CFGA_FILT_SHIFT)      //no filter
                 | (EVENT_GPIO_CFGx_MOD_RISING_EDGE);

  ////---- Configure nHOST_INT output ----////
  SET_nHOST_INT();
  CFG_nHOST_INT(_GPIO_P_CFGL_Px0_OUT);
}

void ezspSpiDisableReceptionInterrupts(void)
{
  INT_SCxCFG &= ~EVENT_SC12_CFG_RXVAL;   //disable byte received interrupt
  INT_SCxCFG &= ~EVENT_SC12_CFG_RXULDA;  //disable buffer A unload interrupt
}

void ezspSpiDisableReception(void)
{
  SCx_REG(DMACTRL) = SC_DMACTRL_RXDMARST; //disable reception while processing
}

void ezspSpiAckUnload(void)
{
  //ack command unload --BugzId:14622
  INT_SCxFLAG = EVENT_SC12_FLAG_RXULDA;
}

void ezspSpiEnableReception(void)
{
  INT_SCxFLAG = EVENT_SC12_FLAG_RXVAL; //clear byte received interrupt
  INT_SCxFLAG = EVENT_SC12_FLAG_RXULDA;//clear buffer A unload interrupt
  INT_SCxCFG |= EVENT_SC12_CFG_RXVAL; //enable byte received interrupt
  INT_SCxCFG |= EVENT_SC12_CFG_RXULDA;//enable buffer A unload interrupt
  SCx_REG(DMACTRL) = SC_DMACTRL_RXLODA; //we are inter-command, activate RX DMA for next
}

void ezspSpiStartTxTransfer(uint8_t responseLength)
{
  SCx_REG(TXENDA) = (uint32_t)halHostResponseBuffer + responseLength - 1;
  SCx_REG(DATA) = 0xFF; // emlipari-183: Prepend sacrificial Tx pad byte
  INT_SCxFLAG = EVENT_SC12_FLAG_RXVAL; //clear byte received interrupt
  SCx_REG(DMACTRL) = SC_DMACTRL_TXLODA;   //enable response for TX
  INT_SCxCFG |= EVENT_SC12_CFG_RXVAL; //enable byte received interrupt
}

bool ezspSpiRxActive(void)
{
  if (((SCx_REG(DMASTAT) & SC_DMASTAT_RXACTA) != SC_DMASTAT_RXACTA)) {
    return false;
  } else {
    return true;
  }
}

void ezspSpiFlushRxFifo(void)
{
  volatile uint8_t dummy;
  // em3xx buffer is 4 so read 4 dummy bytes
  dummy = SCx_REG(DATA);
  dummy = SCx_REG(DATA);
  dummy = SCx_REG(DATA);
  dummy = SCx_REG(DATA);
}

bool ezspSpiValidStartOfData(void)
{
  //check for valid start of data (counter!=0)
  //check for unloaded buffer
  if ((SCx_REG(RXCNTA) != 0) || (INT_SCxFLAG & EVENT_SC12_FLAG_RXULDA)) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiCheckIfUnloaded(void)
{
  //if we have unloaded, know command arrived so jump directly there
  //bypassing RXCNT checks.  On em2xx this is needed because unload
  //clears RXCNT; on em3xx it is simply a convenience.
  if (INT_SCxFLAG & EVENT_SC12_FLAG_RXULDA) {
    //While em2xx could get away with ACKing unload interrupt here,
    //because unload clears RXCNT, em3xx *must* do it below otherwise
    //a just-missed unload leaving RXCNT intact could mistakenly come
    //back to haunt us as a ghost command. -- BugzId:14622.
    return true;
  } else {
    return false;
  }
}

bool ezspSpiHaveTwoBytes(void)
{
  if (SCx_REG(RXCNTA) > 1) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiHaveAllData(void)
{
  if (SCx_REG(RXCNTA) >= halHostCommandBuffer[1] + 3) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiPollForMosi(uint8_t responseLength)
{
  //this fakes out SCx_ISR() in the normal SPI Protocol
  if (INT_SCxFLAG & EVENT_SC12_FLAG_RXVAL) {
    return true;
  } else {
    return false;
  }
}

bool ezspSpiPollForNWAKE(void)
{
  if (EVENT_GPIO->FLAG & nWAKE_GPIOFLAG) {
    // ack int before read to avoid potential of missing interrupt
    EVENT_GPIO->FLAG = nWAKE_GPIOFLAG;
    return true;
  } else {
    // falling edge not detected
    return false;
  }
}

bool ezspSpiPollForNSSEL(void)
{
  //nSSEL signal comes in on IRQC
  if (EVENT_GPIO->FLAG & nSSEL_GPIOFLAG) {
    // ack int before read to avoid potential of missing interrupt
    EVENT_GPIO->FLAG = nSSEL_GPIOFLAG;
    return true;
  } else {
    // rising edge not detected
    return false;
  }
}

bool ezspSpiTransactionValid(uint8_t responseLength)
{
  if ((SCx_REG(TXCNT) != responseLength)) {
    return false;
  } else {
    return true;
  }
}
