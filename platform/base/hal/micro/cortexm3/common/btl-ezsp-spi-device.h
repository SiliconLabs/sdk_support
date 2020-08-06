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
#ifndef __BTL_EZSP_SPI_DEVICE_H__
#define __BTL_EZSP_SPI_DEVICE_H__

void ezspSetupSpiAndDma(void);

void ezspSpiInitSpiAndDma(void);

void configureSpiGpio(void);

void ezspSpiConfigureInterrupts(void);

void ezspSpiDisableReceptionInterrupts(void);

void ezspSpiDisableReception(void);

void ezspSpiAckUnload(void);

void ezspSpiEnableReception(void);

void ezspSpiStartTxTransfer(uint8_t responseLength);

bool ezspSpiRxActive(void);

void ezspSpiFlushRxFifo(void);

bool ezspSpiValidStartOfData(void);

bool ezspSpiHaveTwoBytes(void);

bool ezspSpiHaveAllData(void);

bool ezspSpiPollForMosi(uint8_t responseLength);

bool ezspSpiPollForNWAKE(void);

bool ezspSpiPollForNSSEL(void);

bool ezspSpiTransactionValid(uint8_t responseLength);

#endif //__BTL_EZSP_SPI_DEVICE_H__
