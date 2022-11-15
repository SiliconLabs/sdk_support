/*******************************************************************************
* @file  Flash_Intf.c
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
#include "RS1xxxx_9117.h"
#include "ccp_flash_intf.h"
#include "rsi_board.h"
#include "rsi_chip.h"
#include "system_RS1xxxx.h"

uint32_t  RSI_FLASH_UnInitialize(void)
{
	/* This function not supported so always returns zero */
	return 0;
}

void qspi_gpio_revert_m4(void)
{
  uint32_t gpio_pin_no = 0;
  uint32_t gpio_mode = VAL_15;
  uint32_t i;

  //! Enable QSPI  clock and hclock
  CLK_ENABLE_SET_2_REG_QSPI = ((1 << VAL_12)|(1 << VAL_11));
  RSI_EGPIO_PadSelectionDisable(0);
  for(i = 0; i < VAL_6; i++) {
     RSI_EGPIO_SetPinMux(EGPIO, QSPI_PINS_PORT, (gpio_pin_no + i), gpio_mode);
   }
 }

#ifdef CHIP_9117
#define PadSelectionEnable_CLK  16
#define PadSelectionEnable_D0   17
#define PadSelectionEnable_D1   18
#define PadSelectionEnable_CSN0 19
#define PadSelectionEnable_D2   20
#define PadSelectionEnable_D3   21

#define QSPI_MODE 9

/*M4 QSPI  pin set */
#define M4SS_QSPI_CLK  52
#define M4SS_QSPI_D0   53
#define M4SS_QSPI_D1   54
#define M4SS_QSPI_CSN0 55
#define M4SS_QSPI_D2   56
#define M4SS_QSPI_D3   57
#endif

void RSI_QSPI_PinMuxInit(void)
{
#ifdef CHIP_9118
  /*Pad selection enable */
  RSI_EGPIO_PadSelectionEnable(15);
#endif

#ifdef CHIP_9117
  /*Pad selection enable */
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_CLK);
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_D0);
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_D1);
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_CSN0);
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_D2);
  RSI_EGPIO_PadSelectionEnable(PadSelectionEnable_D3);
#endif

  /*Receive enable for QSPI GPIO*/
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_CLK);
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_CSN0);
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_D0);
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_D1);
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_D2);
  RSI_EGPIO_PadReceiverEnable(M4SS_QSPI_D3);

  /*Set GPIO pin MUX for QSPI*/
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_CLK, QSPI_MODE);
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_CSN0, QSPI_MODE);
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_D0, QSPI_MODE);
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_D1, QSPI_MODE);
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_D2, QSPI_MODE);
  RSI_EGPIO_SetPinMux(EGPIO, 0, M4SS_QSPI_D3, QSPI_MODE);
}


/* QSPI HAL wrapper for NVM3 */
uint32_t RSI_FLASH_Initialize(void)
{
  /*Init the QSPI configurations structure */
  spi_config_t spi_configs_init;

  /*Get QSPI  structures configuration     */
  GetQspiConfig(&spi_configs_init);

  /* Configures the pin MUX for QSPI  pins*/
  RSI_QSPI_PinMuxInit();

  /* initializes QSPI  */
  RSI_QSPI_SpiInit((qspi_reg_t *)QSPI_BASE, &spi_configs_init, 1, 0, 0);

  return 0;
}

uint32_t RSI_FLASH_EraseSector(uint32_t sector_address)
{
	spi_config_t spi_configs_erase;
	GetQspiConfig(&spi_configs_erase);
	//ROMAPI_QSPI_API->qspi_spi_erase((qspi_reg_t *)(M4_QSPI_BASE_ADDRESS),&spi_configs_erase,SECTOR_ERASE, sector_address, 1, 0);
	/* The erase function does the erase and takes care of any missing configurations to successfully erase the sector*/
	//return 0;

  /* Erases the SECTOR   */
  DEBUGOUT("\r\n Erase Sector \r\n");
  RSI_QSPI_SpiErase((qspi_reg_t *)QSPI_BASE, &spi_configs_erase, SECTOR_ERASE, sector_address, 1, 0);

	/* The erase function does the erase and takes care of any missing configurations to successfully erase the sector*/
	return 0;
}

uint32_t RSI_FLASH_Write(uint32_t address, unsigned char *data, uint32_t length)
{
	spi_config_t spi_configs_program;
	uint32_t check_sum = 0;
	GetQspiConfig(&spi_configs_program);

  /* writes the data to required address using qspi */
  DEBUGOUT("\r\n Write Data to Flash Memory \r\n");
  RSI_QSPI_SpiWrite((qspi_reg_t *)QSPI_BASE,
                    &spi_configs_program,
                    0x2,
                    address,
                    (uint8_t *)&data[0],
                    length,
                    256, //256
                    _1BYTE,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0);

	return 0;
}

uint32_t RSI_FLASH_Read(uint32_t address, unsigned char *data, uint32_t length, uint8_t auto_mode)
{
	spi_config_t spi_configs_program;
	uint32_t check_sum = 0;
	GetQspiConfig(&spi_configs_program);

  /* IO_READ - Manual Mode */
	if (0 == auto_mode) {
    /* IO Read config */
  /* Reads from the address in manual mode */
  DEBUGOUT("\r\n Read Data From Flash Memory Using Manual Mode\r\n");
  RSI_QSPI_ManualRead((qspi_reg_t *)(QSPI_BASE),
                      &spi_configs_program,
                      address,
                      (uint8_t *)data,
                      0 /*_32BIT*/,
                      length,
                      0,
                      0,
                      0);
	} else { /* DMA_READ - Auto mode */
  /* Read the data by using UDMA */
#if 0 //Need to Implement
  DEBUGOUT("\r\n Read Data From Flash Memory Using DMA \r\n");
  UDMA_Read();
  /* Wait till dma done */
  while (!done)
    ;
#endif
	}

	return 0;
}

uint32_t RSI_FLASH_Erasechip()
{
	volatile int sector_off_set_addr = 0;

	spi_config_t spi_configs_erase_chip;
	GetQspiConfig(&spi_configs_erase_chip);

  /*Note : This function will not erase the MBR content of the flash but erases the rest of the flash from 72K*/
	//! Initial offset of the flash to be erased.
	sector_off_set_addr = INIT_FLASH_OFFSET;

	do{
	  ROMAPI_QSPI_API->qspi_spi_erase((qspi_reg_t *)(M4_QSPI_BASE_ADDRESS),&spi_configs_erase_chip,SECTOR_ERASE, sector_off_set_addr, 1, 0);
		//! Increment the sector address by 4K
		sector_off_set_addr = (sector_off_set_addr + (4*SIZE_1K));
		//! This loop will be terminated once it reaches to the 1Mb range of memory
	//! Compare with 4Mb flash size
	}while(sector_off_set_addr < FLASH_SECTOR_OFFSET);
	// The erase function does the erase and takes care of any missing configurations to successfully erase the sector of the flash
	return 0;
}

uint32_t checksum_addition(uint8_t *buf, uint32_t size, uint32_t prev_sum)
{
	uint32_t sum = prev_sum;
	uint32_t cnt;
	uint32_t cnt_limit;
	uint32_t dword;

	if (size == 0)
	{
 		return sum;
	}

	cnt_limit = (size & (~0x3));
	/* Accumulate checksum */
	for (cnt = 0; cnt < cnt_limit; cnt += 4)
	{
		dword = *(uint32_t *) &buf[cnt];
		sum += dword;
		if(sum < dword)
		{
			/* In addition operation, if result is lesser than any one of the operand
			 * it means carry is generated.
			 * Incrementing the sum to get ones compliment addition */

			sum++;
		}
	}

	/* Handle non dword-sized case */
  if(size & 0x3) {
		dword = DWORD_ADDR_COMP;
		dword = ~(dword << (8 * (size & 0x3)));
		/* Keeping only valid bytes and making upper bytes zeroes. */
		dword = (*(uint32_t *) &buf[cnt]) & dword;
		sum += dword;
		if(sum < dword)
		{
			sum++;
		}
	}

	return ~sum;
}


uint32_t RSI_FLASH_ProgramPage(uint32_t address, unsigned char *data, uint32_t length)
{
	spi_config_t spi_configs_program;
	uint32_t check_sum = 0;
	GetQspiConfig(&spi_configs_program);
	if(address == INIT_FLASH_OFFSET)
	{
		check_sum  = checksum_addition(data , CRC_LEN_VAL , 1);
		memcpy(&data[CRC_LEN_VAL] ,(uint8_t*)&check_sum,4);
	}
 	if (ROMAPI_QSPI_API->qspi_spi_write((qspi_reg_t *)(M4_QSPI_BASE_ADDRESS),
								&spi_configs_program,0x2 ,
									address,(uint8_t *) data,
											length, FLASH_PAGE_SIZE, _1BYTE, 1,0,1,0,0,0) == RSI_OK){
		return 0; // Success
	}
	else {
		return 1; // Failed
	}
}


uint32_t RSI_FLASH_Verify(uint32_t address, unsigned char *data, uint32_t length)
{
	uint32_t check_sum = 0, i;
	uint8_t *buffer = (uint8_t *)address;

	if((address & FLASH_VERIFY_ADDR)== INIT_FLASH_OFFSET)	{
		check_sum  = checksum_addition(data , CRC_LEN_VAL , 1);
		memcpy(&data[CRC_LEN_VAL] ,(uint8_t*)&check_sum,4);
		for(i=0;i<length;i++)
			if(buffer[i] != data[i])
				break;
	} else {
		for(i=0;i<length;i++)
			if(buffer[i] != data[i])
				break;
	}
	return (address+i);
}

void GetQspiConfig(spi_config_t *spi_config)
{
	memset(spi_config, 0, sizeof(spi_config_t));
	spi_config->spi_config_1.inst_mode         = SINGLE_MODE;
	spi_config->spi_config_1.addr_mode         = SINGLE_MODE;
	spi_config->spi_config_1.data_mode         = SINGLE_MODE;
	spi_config->spi_config_1.dummy_mode        = SINGLE_MODE;
	spi_config->spi_config_1.extra_byte_mode   = SINGLE_MODE;
	spi_config->spi_config_1.prefetch_en       = DIS_PREFETCH;
	spi_config->spi_config_1.dummy_W_or_R      = DUMMY_READS;
	spi_config->spi_config_1.extra_byte_en     = 0;
	spi_config->spi_config_1.d3d2_data         = 3;
	spi_config->spi_config_1.continuous        = DIS_CONTINUOUS;
	spi_config->spi_config_1.read_cmd          = READ;
	spi_config->spi_config_1.flash_type        = SST_SPI_FLASH;
	spi_config->spi_config_1.no_of_dummy_bytes = 0;


	spi_config->spi_config_2.auto_mode         = EN_AUTO_MODE;
	spi_config->spi_config_2.cs_no             = CHIP_ZERO;
	spi_config->spi_config_2.neg_edge_sampling = NEG_EDGE_SAMPLING;
	spi_config->spi_config_2.qspi_clk_en       = QSPI_FULL_TIME_CLK;
	spi_config->spi_config_2.protection        = DNT_REM_WR_PROT;
	spi_config->spi_config_2.dma_mode          = NO_DMA;
	spi_config->spi_config_2.swap_en           = SWAP;
	spi_config->spi_config_2.full_duplex       = IGNORE_FULL_DUPLEX;
	spi_config->spi_config_2.wrap_len_in_bytes = NO_WRAP;
	spi_config->spi_config_2.addr_width_valid  = 0;
	spi_config->spi_config_2.addr_width        = _24BIT_ADDR;
	spi_config->spi_config_2.pinset_valid      = 0;
	spi_config->spi_config_2.flash_pinset      = GPIO_58_TO_63;
	spi_config->spi_config_2.dummy_cycles_for_controller = 0;

	spi_config->spi_config_3.xip_mode                = 0;
	spi_config->spi_config_3._16bit_cmd_valid        = 0;
	spi_config->spi_config_3._16bit_rd_cmd_msb       = 0;
	#ifdef CHIP_9118
	spi_config->spi_config_3.ddr_mode_en             = 0;
	#endif
	spi_config->spi_config_3.wr_cmd                  = 0x2;
	spi_config->spi_config_3.wr_inst_mode            = SINGLE_MODE;
	spi_config->spi_config_3.wr_addr_mode            = SINGLE_MODE;
	spi_config->spi_config_3.wr_data_mode            = SINGLE_MODE;
	spi_config->spi_config_3.dummys_4_jump           = 1;

	spi_config->spi_config_4._16bit_wr_cmd_msb       = 0;
	#ifdef CHIP_9118
	spi_config->spi_config_4.qspi_manual_ddr_phasse  = 0;
	spi_config->spi_config_4.ddr_data_mode           = 0;
	spi_config->spi_config_4.ddr_addr_mode           = 0;
	spi_config->spi_config_4.ddr_inst_mode           = 0;
	spi_config->spi_config_4.ddr_dummy_mode          = 0;
	spi_config->spi_config_4.ddr_extra_byte          = 0;
	#endif
	spi_config->spi_config_4.dual_flash_mode         = 0;
	spi_config->spi_config_4.secondary_csn           = 1;
	spi_config->spi_config_4.polarity_mode           = 0;
	spi_config->spi_config_4.valid_prot_bits         = 4;
	spi_config->spi_config_4.no_of_ms_dummy_bytes    = 0;
	#ifdef CHIP_9118
	spi_config->spi_config_4.ddr_dll_en              = 0;
	#endif
	spi_config->spi_config_4.continue_fetch_en       = 0;


	spi_config->spi_config_5.block_erase_cmd           = BLOCK_ERASE;
	spi_config->spi_config_5.busy_bit_pos              = 0;
	spi_config->spi_config_5.d7_d4_data                = 0xf;
	spi_config->spi_config_5.dummy_bytes_for_rdsr      = 0x0;
	spi_config->spi_config_5.reset_type                = 0x0;

	spi_config->spi_config_6.chip_erase_cmd        = CHIP_ERASE;
	spi_config->spi_config_6.sector_erase_cmd      = SECTOR_ERASE;

	spi_config->spi_config_7.status_reg_write_cmd  = 0x1;
	spi_config->spi_config_7.status_reg_read_cmd   = 0x5;
}
