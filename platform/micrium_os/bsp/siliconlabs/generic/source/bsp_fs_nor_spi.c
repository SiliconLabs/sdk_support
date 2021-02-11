/***************************************************************************//**
 * @file
 * @brief NOR SPI Controller BSP
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

/********************************************************************************************************
 ********************************************************************************************************
 *                                     DEPENDENCIES & AVAIL CHECK(S)
 ********************************************************************************************************
 *******************************************************************************************************/

#include  <rtos_description.h>
#include  <em_chip.h>

#if (defined(RTOS_MODULE_FS_AVAIL) && defined(RTOS_MODULE_FS_STORAGE_NOR_AVAIL) \
  && defined(_EFR32_MIGHTY_FAMILY))

/********************************************************************************************************
 ********************************************************************************************************
 *                                            INCLUDE FILES
 ********************************************************************************************************
 *******************************************************************************************************/

#include  <cpu/include/cpu.h>
#include  <common/include/lib_def.h>
#include  <common/include/lib_mem.h>

#include  <drivers/fs/include/fs_nor_quad_spi_drv.h>
#include  <fs/include/fs_nor_quad_spi.h>
#include  <fs/include/fs_nor.h>
#include  <fs/include/fs_nor_phy_drv.h>

#include  <em_cmu.h>
#include  <em_gpio.h>

/********************************************************************************************************
 ********************************************************************************************************
 *                                             LOCAL DEFINES
 ********************************************************************************************************
 *******************************************************************************************************/

#define  MX25R_PIN_SCLK                    8u
#define  MX25R_PIN_MOSI                    6u
#define  MX25R_PIN_MISO                    7u
#define  MX25R_PIN_CS                      4u

/********************************************************************************************************
 ********************************************************************************************************
 *                                        LOCAL FUNCTION PROTOTYPES
 ********************************************************************************************************
 *******************************************************************************************************/

static CPU_BOOLEAN BSP_FS_NOR_SPI_Init(FS_NOR_QUAD_SPI_ISR_HANDLE_FNCT isr_fnct,
                                       void                            *p_drv_data);

static CPU_BOOLEAN BSP_FS_NOR_SPI_ClkCfg(void);

static CPU_BOOLEAN BSP_FS_NOR_SPI_IO_Cfg(void);

static CPU_BOOLEAN BSP_FS_NOR_SPI_ChipSelEn(CPU_INT16U part_slave_id);

static CPU_BOOLEAN BSP_FS_NOR_SPI_ChipSelDis(CPU_INT16U part_slave_id);

static CPU_INT32U BSP_FS_NOR_SPI_ClkFreqGet(void);

/********************************************************************************************************
 ********************************************************************************************************
 *                                          LOCAL GLOBAL VARIABLES
 ********************************************************************************************************
 *******************************************************************************************************/

static const FS_NOR_QUAD_SPI_BSP_API SPI_Ctrlr_BSP_API = {
  .Init = BSP_FS_NOR_SPI_Init,
  .ClkCfg = BSP_FS_NOR_SPI_ClkCfg,
  .IO_Cfg = BSP_FS_NOR_SPI_IO_Cfg,
  .IntCfg = DEF_NULL,
  .ChipSelEn = BSP_FS_NOR_SPI_ChipSelEn,
  .ChipSelDis = BSP_FS_NOR_SPI_ChipSelDis,
  .ClkFreqGet = BSP_FS_NOR_SPI_ClkFreqGet
};

/********************************************************************************************************
 ********************************************************************************************************
 *                                           GLOBAL VARIABLES
 ********************************************************************************************************
 *******************************************************************************************************/

const FS_NOR_QUAD_SPI_CTRLR_INFO BSP_FS_NOR_SPICtrl_HwInfo = {
  .DrvApiPtr = (FS_NOR_QUAD_SPI_DRV_API *)&FS_NOR_SpiDrvAPI_Silabs_EFM32,
  .BspApiPtr = (FS_NOR_QUAD_SPI_BSP_API *)&SPI_Ctrlr_BSP_API,
  .BaseAddr = USART1_BASE,
  .AlignReq = sizeof(CPU_ALIGN),
  .FlashMemMapStartAddr = FS_NOR_PHY_FLASH_MEM_MAP_NONE,
  .BusWidth = FS_NOR_SERIAL_BUS_WIDTH_SINGLE_IO,
};

const FS_NOR_QUAD_SPI_HW_INFO BSP_FS_NOR_MX25R_SPI_HwInfo = {
  .PartHwInfo.PhyApiPtr = (CPU_INT32U)(&FS_NOR_PHY_MX25R_API),
  .PartHwInfo.ChipSelID = 0u,
  .CtrlrHwInfoPtr = &BSP_FS_NOR_SPICtrl_HwInfo
};

const FS_NOR_QUAD_SPI_HW_INFO BSP_FS_NOR_W25Q_SPI_HwInfo = {
  .PartHwInfo.PhyApiPtr = (CPU_INT32U)(&FS_NOR_PHY_W25Q_API),
  .PartHwInfo.ChipSelID = 0u,
  .CtrlrHwInfoPtr = &BSP_FS_NOR_SPICtrl_HwInfo
};

/********************************************************************************************************
 ********************************************************************************************************
 *                                             LOCAL FUNCTIONS
 ********************************************************************************************************
 *******************************************************************************************************/

/****************************************************************************************************//**
 *                                        BSP_FS_NOR_SPI_Init()
 *
 * @brief   Initializes internal resources needed by the NOR SPI BSP.
 *
 * @param   isr_fnct    Interrupt service routine to call when an interruption from the QSPI
 *                      controller occurs.
 *
 * @param   p_drv_data  Pointer to SPI controller driver private data. This must be passed to the
 *                      interrupt service routine 'isr_fnct'.
 *
 * @return  DEF_OK,   if successful.
 *          DEF_FAIL, otherwise.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_NOR_SPI_Init(FS_NOR_QUAD_SPI_ISR_HANDLE_FNCT isr_fnct,
                                       void                            *p_drv_data)
{
  PP_UNUSED_PARAM(isr_fnct);                                    // SPI driver does not use interrupt for NOR xfers.
  PP_UNUSED_PARAM(p_drv_data);

  return (DEF_OK);
}

/****************************************************************************************************//**
 *                                       BSP_FS_NOR_SPI_ClkCfg()
 *
 * @brief   Initializes clock(s) needed by the SPI controller.
 *
 * @return  DEF_OK,   if successful.
 *          DEF_FAIL, otherwise.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_NOR_SPI_ClkCfg(void)
{
  CMU_ClockEnable(cmuClock_USART1, true);                       // Enable the USART1 clock Peripheral.
  CMU_ClockEnable(cmuClock_GPIO, true);                         // Enable GPIO clock signals (used for LEDs)

  return (DEF_OK);
}

/****************************************************************************************************//**
 *                                       BSP_FS_NOR_SPI_IO_Cfg()
 *
 * @brief   Initializes Input/Output needed by the SPI controller.
 *
 * @return  DEF_OK,   if successful.
 *          DEF_FAIL, otherwise.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_NOR_SPI_IO_Cfg(void)
{
  GPIO_PinModeSet(gpioPortC,
                  MX25R_PIN_SCLK,                               // MX25R SPI_SCLK (USART1): pin 8.
                  gpioModePushPull,
                  DEF_OFF);                                     // Initial setting: line is low.

  GPIO_PinModeSet(gpioPortC,
                  MX25R_PIN_MOSI,                               // MX25R SPI_MOSI (USART1): pin 6.
                  gpioModePushPull,
                  DEF_OFF);                                     // Initial setting: line is low.

  GPIO_PinModeSet(gpioPortC,
                  MX25R_PIN_MISO,                               // MX25R SPI_MISO (USART1): pin 7.
                  gpioModeInput,
                  DEF_OFF);                                     // Initial setting: line is Low.

  GPIO_PinModeSet(gpioPortA,
                  MX25R_PIN_CS,                                 // MX25R SPI_CS (GPIO): pin 4.
                  gpioModePushPull,
                  DEF_ON);                                      // Initial setting: line is HIGH = chip NOT selected.

  //                                                               Cfg I/O Routing Location and Pin in USART1 controller.
  //                                                               Location 11 used on Thunderboard Sense.
  USART1->ROUTELOC0 = (USART_ROUTELOC0_RXLOC_LOC11
                       | USART_ROUTELOC0_TXLOC_LOC11
                       | USART_ROUTELOC0_CLKLOC_LOC11);
  //                                                               Enable all required pins.
  USART1->ROUTEPEN = (USART_ROUTEPEN_RXPEN
                      | USART_ROUTEPEN_TXPEN
                      | USART_ROUTEPEN_CLKPEN);

  return (DEF_OK);
}

/****************************************************************************************************//**
 *                                     BSP_FS_NOR_SPI_ChipSelEn()
 *
 * @brief   Enable SPI chip select.
 *
 * @param   part_slave_id    Slave ID to enable CS.
 *
 * @return  DEF_OK,   if successful.
 *          DEF_FAIL, otherwise.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_NOR_SPI_ChipSelEn(CPU_INT16U part_slave_id)
{
  CPU_BOOLEAN success;

  success = DEF_FAIL;
  switch (part_slave_id) {
    case 0:
      GPIO_PinOutClear(gpioPortA, MX25R_PIN_CS);
      success = DEF_OK;
      break;

    case 1:
    case 2:
    default:
      break;
  }

  return (success);
}

/****************************************************************************************************//**
 *                                     BSP_FS_NOR_SPI_ChipSelDis()
 *
 * @brief   Disable SPI chip select.
 *
 * @param   part_slave_id    Slave ID to Disable CS.
 *
 * @return  DEF_OK,   if successful.
 *          DEF_FAIL, otherwise.
 *******************************************************************************************************/
static CPU_BOOLEAN BSP_FS_NOR_SPI_ChipSelDis(CPU_INT16U part_slave_id)
{
  CPU_BOOLEAN success;

  success = DEF_FAIL;
  switch (part_slave_id) {
    case 0:
      GPIO_PinOutSet(gpioPortA, MX25R_PIN_CS);
      success = DEF_OK;
      break;

    case 1:
    case 2:
    default:
      break;
  }

  return (success);
}

/****************************************************************************************************//**
 *                                      BSP_FS_NOR_SPI_ClkFreqGet()
 *
 * @brief   Get input clock frequency of SPI controller.
 *
 * @return  Input clock frequency, in hertz.
 *******************************************************************************************************/
static CPU_INT32U BSP_FS_NOR_SPI_ClkFreqGet(void)
{
  CPU_INT32U clk_freq;

  clk_freq = CMU_ClockFreqGet(cmuClock_USART1);                 // Get input clock of USART controller.

  return (clk_freq);
}

/********************************************************************************************************
 ********************************************************************************************************
 *                                   DEPENDENCIES & AVAIL CHECK(S) END
 ********************************************************************************************************
 *******************************************************************************************************/

#endif // RTOS_MODULE_FS_AVAIL && RTOS_MODULE_FS_STORAGE_NOR_AVAIL
