/***************************************************************************//**
 * @brief header code for spi applications based on Cortex M3
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
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DVK_SPI_H__
#define __DVK_SPI_H__

/*! @addtogroup IEC60335_TOOLS
* @{
*/
/*! public function to enable LED communication, set LED0, set LED0 and 1
 * use this function to show that the WDOG reset occurred and changed the system.
 * a complete check will enable the LED0 until the WDOG reset occurred and
 * than change the LEDs to LED0 and LED1.
 * @param mode  available options are : 0 = init interface and reset all LEDs\n
 *                                      1 = set LED0\n
 *                                  other = set LED0 and LED1
 */
void DVK_SPI(uint8_t mode);
/*!
 * @}
*/
#endif /* __DVK_SPI_H__ */

/************************************** EOF *********************************/
