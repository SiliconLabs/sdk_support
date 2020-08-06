/***************************************************************************//**
 * @file
 * @brief This header file contains the prototypes for functions
 * needed in all spiflash-class1.c files in order for
 * them to work with spiflash-common.c
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
#ifndef __SPIFLASH_CLASS1_COMMON_H__
#define __SPIFLASH_CLASS1_COMMON_H__

void halSpiPush8(uint8_t txData);

uint8_t halSpiPop8(void);

void setFlashCSActive(void);

void setFlashCSInactive(void);

uint8_t halEepromInit(void);

void configureEepromPowerPin(void);

void setEepromPowerPin(void);

void clearEepromPowerPin(void);

void halEepromConfigureGPIO(void);

void halEepromConfigureFlashController(void);

void halEepromDelayMicroseconds(uint32_t timeToDelay);

#endif // __SPIFLASH_CLASS1_COMMON_H__
