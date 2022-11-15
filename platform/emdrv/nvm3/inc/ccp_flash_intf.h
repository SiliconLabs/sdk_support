/*******************************************************************************
 * @file  Flash_Intf.h
 * @brief
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

/**
 * Includes
 */
#ifndef __FLASH_INTF_H__
#define __FLASH_INTF_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rsi_qspi.h"
#include "rsi_rom_egpio.h"
#define M4SS_CLK_PWR_CTRL_BASE_ADDR 0x46000000
#define M4SS_CLK_ENABLE_SET_REG1                                               \
  *(volatile uint32_t *)(M4SS_CLK_PWR_CTRL_BASE_ADDR + 0x00)
#define M4SS_CLK_ENABLE_CLEAR_REG1                                             \
  *(volatile uint32_t *)(M4SS_CLK_PWR_CTRL_BASE_ADDR + 0x04)
#define M4SS_STATIC_CLK_SWITCH BIT(19)

#define CLK_ENABLE_SET_2_REG_QSPI                                              \
  (*((volatile uint32_t *)(M4SS_CLK_PWR_CTRL_BASE_ADDR + 0x08)))
/*Disable the flash based retention sleep */
#define FLASH_BASED_RET_SLEEP 1 /*<! Enable flash based execution       >*/
#define INTERMEDIATE_SP 0x1F800 /*<! Stack pointer on retention wake up >*/
#define QSPI_PINS_PORT 0
#define TA_RESET_ADDR 0x22000004
#define INIT_FLASH_OFFSET 0x12000
#define FLASH_SECTOR_OFFSET 0x400000
#define SIZE_1K 1024
#define CRC_LEN_VAL 236
#define FLASH_VERIFY_ADDR 0x00FFFFFF
#define FLASH_PAGE_SIZE 256
#define DWORD_ADDR_COMP 0xffffffff
#define VAL_12 12
#define VAL_11 11
#define VAL_15 15
#define VAL_6 6

#ifdef SECONDARY_FLASH
#define PadSelectionEnable_CLK 16
#define PadSelectionEnable_D0 17
#define PadSelectionEnable_D1 18
#define PadSelectionEnable_CSN0 19
#define PadSelectionEnable_D2 20
#define PadSelectionEnable_D3 21

#define QSPI_MODE 9

/*M4 QSPI  pin set */
#define M4SS_QSPI_CLK 52
#define M4SS_QSPI_D0 53
#define M4SS_QSPI_D1 54
#define M4SS_QSPI_CSN0 55
#define M4SS_QSPI_D2 56
#define M4SS_QSPI_D3 57
#endif

#ifdef PRIMARY_FLASH
#define PadSelectionEnable 0
#define QSPI_MODE 1
/*M4 QSPI  pin set */
#define M4SS_QSPI_CLK 0
#define M4SS_QSPI_CSN0 1
#define M4SS_QSPI_D0 2
#define M4SS_QSPI_D1 3
#define M4SS_QSPI_D2 4
#define M4SS_QSPI_D3 5
#endif
#ifdef EXTERNAL_FLASH
#define PadSelectionEnable_1 11
#define PadSelectionEnable_2 12
#define QSPI_MODE 10
/*M4 QSPI  pin set */
#define M4SS_QSPI_CLK 46
#define M4SS_QSPI_CSN0 49
#define M4SS_QSPI_D0 47
#define M4SS_QSPI_D1 48
#define M4SS_QSPI_D2 50
#define M4SS_QSPI_D3 51
#endif

/******************************************
 *              FLASH CMDS
 ******************************************/
//! Write enable cmd
#define WREN 0x06
#define WREN2 0xF9
//! Write disable cmd
#define WRDI 0x04
#define WRDI2 0xFB
//! Read status reg cmd
#define RDSR 0x05
#define RDSR2 0xFA
//! chip erase cmd
#define CHIP_ERASE 0xC7
//! block erase cmd
#define BLOCK_ERASE 0xD8
//! sector erase cmd
#define SECTOR_ERASE 0x20
//! high speed rd cmd
#define HISPEED_READ 0x0B
//! rd cmd
#define READ 0x03
//! write config2
#define WCFG2 0x72

#define _1BYTE 0
#define _2BYTE 1
#define _4BYTE 3

/* GPIO register bit position related defines */
#define GPIO_0_TO_5 0
#define GPIO_6_TO_11 1
#define GPIO_46_TO_51 2
#define GPIO_52_TO_57 3
#define GPIO_58_TO_63 4
//! TA OCTA/DUAL combinations
#define GPIO_0_AND_58 5
#define GPIO_6_AND_58 6
#define GPIO_46_AND_58 7
//! M4 OCTA/DUAL combinations
#define GPIO_0_AND_52 8
#define GPIO_6_AND_52 9
#define GPIO_46_AND_52 10
#define NOT_USING 11 //! Not applicable
#define GPIO_58_AND_52 12
#define GPIO_DDR_PADS 13

uint32_t RSI_FLASH_Initialize(void);

uint32_t RSI_FLASH_EraseSector(uint32_t sector_address);

uint32_t RSI_FLASH_Erasechip(void);

uint32_t checksum_addition(uint8_t *buf, uint32_t size, uint32_t prev_sum);

uint32_t RSI_FLASH_ProgramPage(uint32_t address, unsigned char *data,
                               uint32_t length);

uint32_t RSI_FLASH_Verify(uint32_t address, unsigned char *data,
                          uint32_t length);

uint32_t RSI_FLASH_Read(uint32_t address, unsigned char *data, uint32_t length,
                        uint8_t auto_mode);

uint32_t RSI_FLASH_UnInitialize(void);

void qspi_gpio_revert_m4(void);

void GetQspiConfig(spi_config_t *spi_config);

#ifdef __cplusplus
}
#endif

#endif /* __RSI_EGPIO_H__*/
