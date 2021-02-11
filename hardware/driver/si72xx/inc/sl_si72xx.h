/***************************************************************************//**
 * @file
 * @brief Driver for the Si72xx Hall Effect Sensor
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_SI72XX_H
#define SL_SI72XX_H

#include "em_device.h"
#include <stddef.h>
#include <stdbool.h>

/***************************************************************************//**
 * @addtogroup si72xx Si72xx - Magnetic Hall Effect Sensor
 * @{
 ******************************************************************************/

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

/** I2C device address for Si72xx */
#define SI7200_ADDR_0      (0x30 << 1)
#define SI7200_ADDR_1      (0x31 << 1)
#define SI7200_ADDR_2      (0x32 << 1)
#define SI7200_ADDR_3      (0x33 << 1)

/** I2C registers for Si72xx */
#define SI72XX_HREVID             0xC0
#define SI72XX_DSPSIGM            0xC1
#define SI72XX_DSPSIGL            0xC2
#define SI72XX_DSPSIGSEL          0xC3
#define SI72XX_POWER_CTRL         0xC4
#define SI72XX_ARAUTOINC          0xC5
#define SI72XX_CTRL1              0xC6
#define SI72XX_CTRL2              0xC7
#define SI72XX_SLTIME             0xC8
#define SI72XX_CTRL3              0xC9
#define SI72XX_A0                 0xCA
#define SI72XX_A1                 0xCB
#define SI72XX_A2                 0xCC
#define SI72XX_CTRL4              0xCD
#define SI72XX_A3                 0xCE
#define SI72XX_A4                 0xCF
#define SI72XX_A5                 0xD0
#define SI72XX_OTP_ADDR           0xE1
#define SI72XX_OTP_DATA           0xE2
#define SI72XX_OTP_CTRL           0xE3
#define SI72XX_TM_FG              0xE4

#define SI72XX_OTP_20MT_ADDR      0x21
#define SI72XX_OTP_200MT_ADDR     0x27

#define SI72XX_ERROR_BUSY         0xfe
#define SI72XX_ERROR_NODATA       0xfd

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/
/** Si72xx magnetic field full-scales */
typedef enum {
  SI7210_20MT,
  SI7210_200MT
} Si72xxFieldScale_t;

/** Si72xx sleep modes */
typedef enum {
  SI72XX_SLEEP_MODE,
  SI72XX_SLTIMEENA_MODE
} Si72xxSleepMode_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/
uint32_t sl_si72xx_read_register(I2C_TypeDef *i2c,
                                 uint8_t addr,
                                 uint8_t reg,
                                 uint8_t *data);
uint32_t sl_si72xx_write_register(I2C_TypeDef *i2c,
                                  uint8_t addr,
                                  uint8_t reg,
                                  uint8_t data);

uint32_t sl_si72xx_wake_up_and_idle(I2C_TypeDef *i2c, uint8_t addr);
uint32_t sl_si72xx_read_magfield_data(I2C_TypeDef *i2c,
                                      uint8_t addr,
                                      int16_t *magData);
uint32_t sl_si72xx_from_idle_go_to_sleep(I2C_TypeDef *i2c, uint8_t addr);
uint32_t sl_si72xx_from_idle_go_to_sltimeena(I2C_TypeDef *i2c, uint8_t addr);

uint32_t sl_si72xx_read_magfield_data_and_sleep(I2C_TypeDef *i2c,
                                                uint8_t addr,
                                                Si72xxFieldScale_t mTScale,
                                                Si72xxSleepMode_t sleepMode,
                                                int16_t *magFieldData);
int32_t sl_si72xx_convert_data_codes_to_magnetic_field(Si72xxFieldScale_t fieldScale,
                                                       int16_t dataCode);
uint32_t sl_si72xx_enter_sleep_mode(I2C_TypeDef *i2c,
                                    uint8_t addr,
                                    Si72xxSleepMode_t sleepMode);
uint32_t sl_si72xx_enter_latch_mode (I2C_TypeDef *i2c, uint8_t addr);
uint32_t sl_si72xx_read_temperature_and_sleep(I2C_TypeDef *i2c,
                                              uint8_t addr,
                                              int32_t *rawTemp);
uint32_t sl_si72xx_read_corrected_temp_and_sleep(I2C_TypeDef *i2c,
                                                 uint8_t addr,
                                                 int16_t offsetData,
                                                 int16_t gainData,
                                                 int32_t *correctedTemp);
uint32_t sl_si72xx_read_temp_correction_data_and_sleep(I2C_TypeDef *i2c,
                                                       uint8_t addr,
                                                       int16_t *offsetValue,
                                                       int16_t *gainValue);

uint32_t sl_si72xx_identify_and_sleep(I2C_TypeDef *i2c,
                                      uint8_t addr,
                                      uint8_t *partId,
                                      uint8_t *partRev);
uint32_t sl_si72xx_read_variant_and_sleep(I2C_TypeDef *i2c,
                                          uint8_t addr,
                                          uint8_t *basePn,
                                          uint8_t *pnVariant);

/** @} (end group si72xx) */

#endif /* SL_SI72xx_H */
