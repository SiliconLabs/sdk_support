/***************************************************************************//**
 * @file
 * @brief NCP side of the Host<->NCP serial link.
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
bool halHostUartTxIdle(void);
void halHostUartLinkTx(const uint8_t *data, uint16_t length);
void halHostSerialInit(void);
void halHostSerialTick(void);
bool halHostUartTxEmpty(void);
void halHostUartForceRTS(void);
bool halHostCtsWaitOrTimeout(bool reset);
