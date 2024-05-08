/*
 *
 *    Copyright (c) 2022 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "rsi_pll.h"
#include "rsi_rom_clks.h"
#include "silabs_utils.h"
#include "sl_si91x_button_pin_config.h"
#include "sli_siwx917_soc.h"
#include "rsi_debug.h"
#include "rsi_rom_egpio.h"

#define SOC_PLL_REF_FREQUENCY 40000000 // /* PLL input REFERENCE clock 40MHZ */

// Note: Change this macro to required PLL frequency in hertz
#define PS4_SOC_FREQ 180000000 /* PLL out clock 180MHz */
#define SWITCH_QSPI_TO_SOC_PLL
#define ICACHE_DISABLE
#define DEBUG_DISABLE

/* QSPI clock config params */
#define INTF_PLL_500_CTRL_VALUE 0xD900
#define INTF_PLL_CLK            80000000 /* PLL out clock 80 MHz */

#define PMU_GOOD_TIME  31 /*Duration in us*/
#define XTAL_GOOD_TIME 31 /*Duration in us*/

/*Pre-fetch and regestring */
#define ICACHE2_ADDR_TRANSLATE_1_REG  *(volatile uint32_t *)(0x20280000 + 0x24)
#define MISC_CFG_SRAM_REDUNDANCY_CTRL *(volatile uint32_t *)(0x46008000 + 0x18)
#define MISC_CONFIG_MISC_CTRL1        *(volatile uint32_t *)(0x46008000 + 0x44)
#define MISC_QUASI_SYNC_MODE          *(volatile uint32_t *)(0x46008000 + 0x84)

void sl_button_on_change(uint8_t btn, uint8_t btnAction);

int soc_pll_config(void)
{
  int32_t status = RSI_OK;

  RSI_CLK_M4SocClkConfig(M4CLK, M4_ULPREFCLK, 0);
  // Configures the required registers for 180 Mhz clock in PS4
  RSI_PS_PS4SetRegisters();
  // Configure the PLL frequency
  // Configure the SOC PLL to 180MHz
  RSI_CLK_SetSocPllFreq(M4CLK, PS4_SOC_FREQ, SOC_PLL_REF_FREQUENCY);
  // Switch M4 clock to PLL clock for speed operations
  RSI_CLK_M4SocClkConfig(M4CLK, M4_SOCPLLCLK, 0);

  SysTick_Config(SystemCoreClock / 1000);
  DEBUGINIT();

#ifdef SWITCH_QSPI_TO_SOC_PLL
  /* program intf pll to 160Mhz */
  SPI_MEM_MAP_PLL(INTF_PLL_500_CTRL_REG9) = INTF_PLL_500_CTRL_VALUE;
  status                                  = RSI_CLK_SetIntfPllFreq(M4CLK, INTF_PLL_CLK, SOC_PLL_REF_FREQUENCY);
  if (status != RSI_OK) {
    SILABS_LOG("Failed to Config Interface PLL Clock, status:%d", status);
  } else {
    SILABS_LOG("Configured Interface PLL Clock to %d", INTF_PLL_CLK);
  }

  RSI_CLK_QspiClkConfig(M4CLK, QSPI_INTFPLLCLK, 0, 0, 1);
#endif /* SWITCH_QSPI_TO_SOC_PLL */
  return 0;
}

void sl_si91x_button_isr(uint8_t pin, uint8_t state)
{
  (pin == SL_BUTTON_BTN0_PIN) ? sl_button_on_change(SL_BUTTON_BTN0_NUMBER, !state)
                              : sl_button_on_change(SL_BUTTON_BTN1_NUMBER, !state);
}
