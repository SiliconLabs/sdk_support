/***************************************************************************//**
 * @file
 * @brief HAL config initialization
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
#include "hal/hal.h"
#include "em_device.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "ecode.h"
#include "plugin/antenna/antenna.h"
#include "plugin/serial/com.h"
#include "plugin/serial/com_config.h"
#if (PHY_RAIL || PHY_DUALRAIL)
#include "rail.h"
#include "rail_ieee802154.h"
#elif defined (_EFR_DEVICE)
#include "rfhal_pti.h"
#endif
#if HAL_IOEXP_VCOM_ENABLE
#include "bsp.h"
#include "retargetserial.h"
#endif
#if HAL_FEM_ENABLE
#include "util/plugin/plugin-common/fem-control/fem-control.h"
#endif
#if HAL_COEX_ENABLE
#include "coexistence/protocol/ieee802154/coexistence-802154.h"
#endif

// Use a default LFXO precision of 500 so that it's not undefined
#ifndef HAL_LFXO_PRECISION
#define HAL_LFXO_PRECISION 500
#endif

static void halConfigClockInit(void)
{
// Initialize HFXO if used
#if ((HAL_CLK_HFCLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFXO)             \
  || ((HAL_CLK_HFCLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFRCODPLL)       \
  && ((HAL_CLK_PLL_CONFIGURATION == HAL_CLK_PLL_CONFIGURATION_80MHZ) \
  || (HAL_CLK_PLL_CONFIGURATION == HAL_CLK_PLL_CONFIGURATION_76_8MHZ))))
  #if !BSP_CLK_HFXO_PRESENT
    #error Cannot select HFXO when HFXO is not present
  #endif

  CMU_HFXOInit_TypeDef hfxoInit = BSP_CLK_HFXO_INIT;

  #if defined(BSP_CLK_HFXO_CTUNE) && (BSP_CLK_HFXO_CTUNE >= 0)
  #if defined(_SILICON_LABS_32B_SERIES_2)
  hfxoInit.ctuneXiAna = BSP_CLK_HFXO_CTUNE;
  hfxoInit.ctuneXoAna = BSP_CLK_HFXO_CTUNE;
  #else
  hfxoInit.ctuneSteadyState = BSP_CLK_HFXO_CTUNE;
  #endif // series 2
  #endif // BSP_CLK_HFXO_CTUNE

  #if !defined(FPGA)
  #if defined(_SILICON_LABS_32B_SERIES_2)
  uint8_t customSteadyCtuneXi;
  uint8_t customSteadyCtuneXo;
  uint16_t customSteadyCtuneToken;

  // check factory calibrated ctune value
  if (halInternalGetModuleCtuneXiXo(&customSteadyCtuneXi, &customSteadyCtuneXo)) {
    hfxoInit.ctuneXiAna = customSteadyCtuneXi;
    hfxoInit.ctuneXoAna = customSteadyCtuneXo;
  }
  // otherwise check for ctune in mfg token
  else if (halInternalGetCtuneToken(&customSteadyCtuneToken, &customSteadyCtuneToken)) {
    hfxoInit.ctuneXiAna = (uint8_t)customSteadyCtuneToken;
    hfxoInit.ctuneXoAna = (uint8_t)customSteadyCtuneToken;
  }
  #else
  uint16_t customSteadyCtuneModule;
  uint16_t customSteadyCtuneToken;
  // check factory calibrated ctune value
  if (halInternalGetModuleCtune(&customSteadyCtuneModule)) {
    hfxoInit.ctuneSteadyState = customSteadyCtuneModule;
  }
  // otherwise check for ctune in mfg token
  else if (halInternalGetCtuneToken(&customSteadyCtuneToken, &customSteadyCtuneToken)) {
    hfxoInit.ctuneSteadyState = customSteadyCtuneToken;
  } else {
    // satisfy MISRA 15.7
  }
  #endif // series 2

  CMU_HFXOInit(&hfxoInit);
  #endif // FPGA
#endif // hfxo or hfrco with hfxo

#if (HAL_CLK_HFCLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFXO)
  // Setting system HFXO frequency
  SystemHFXOClockSet(BSP_CLK_HFXO_FREQ);

  // Select the HFXO and, if supported, manually turn off HFRCO
  // If requested and supported, turn on autostart/select for series 1 devices
  #if defined(_SILICON_LABS_32B_SERIES_1)
    #if defined(HAL_CLK_HFXO_AUTOSTART) && HAL_CLK_HFXO_AUTOSTART == HAL_CLK_HFXO_AUTOSTART_SELECT
  // Automatically start and select HFXO
  CMU_HFXOAutostartEnable(0, true, true);
    #else
      #if defined(HAL_CLK_HFXO_AUTOSTART) && HAL_CLK_HFXO_AUTOSTART == HAL_CLK_HFXO_AUTOSTART_START
  // Automatically start HFXO
  CMU_HFXOAutostartEnable(0, true, false);
      #endif // HAL_CLK_HFXO_AUTOSTART
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO);
    #endif // HAL_CLK_HFXO_AUTOSTART
  /* HFRCO not needed when using HFXO */
  CMU_OscillatorEnable(cmuOsc_HFRCO, false, false);

  #elif defined(_SILICON_LABS_32B_SERIES_2) // defined(_SILICON_LABS_32B_SERIES_1)
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFXO);
  #else // defined(_SILICON_LABS_32B_SERIES_2)
    #error Unknown device series
  #endif // defined(_SILICON_LABS_32B_SERIES_2)

#elif (HAL_CLK_HFCLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFRCO)
  #if defined(_SILICON_LABS_32B_SERIES_1)
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFRCO);
  #elif defined(_SILICON_LABS_32B_SERIES_2)
  CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_HFRCODPLL);
  #endif

// HFRCODPLL for using DPLL to get higher frequencies, series 2 and up
#elif (HAL_CLK_HFCLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFRCODPLL)
  #if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
  // Use LFXO at 40MHz
  #if (HAL_CLK_PLL_CONFIGURATION == HAL_CLK_PLL_CONFIGURATION_40MHZ)
  CMU_LFXOInit_TypeDef lfxoInit = CMU_LFXOINIT_DEFAULT;
    #if defined(BSP_CLK_LFXO_CTUNE) && BSP_CLK_LFXO_CTUNE > 0
  lfxoInit.ctune = BSP_CLK_LFXO_CTUNE;
    #endif
  CMU_LFXOInit(&lfxoInit);
  CMU_LFXOPrecisionSet(HAL_LFXO_PRECISION);
  CMU_DPLLInit_TypeDef dpllInit = CMU_DPLL_LFXO_TO_40MHZ;
  #endif

  // Use HFXO at 80MHz
  #if (HAL_CLK_PLL_CONFIGURATION == HAL_CLK_PLL_CONFIGURATION_80MHZ)
  CMU_DPLLInit_TypeDef dpllInit = CMU_DPLL_HFXO_TO_80MHZ;
  #endif

  #elif defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  // Use HFXO at 76.8MHz
  #if (HAL_CLK_PLL_CONFIGURATION == HAL_CLK_PLL_CONFIGURATION_76_8MHZ)
  CMU_DPLLInit_TypeDef dpllInit = CMU_DPLL_HFXO_TO_76_8MHZ;
  #endif
  #endif // CONFIG 2

  CMU_Select_TypeDef selected_sysclk = CMU_ClockSelectGet(cmuClock_SYSCLK);

  if (selected_sysclk == cmuSelect_HFRCODPLL) {
    // From Reference Manual:
    // The CMU should not be running from the HFRCO. If necessary, the CMU
    // should switch to the FSRCO until after the DPLL has locked to avoid
    // over-clocking due to overshoot.
    CMU_ClockSelectSet(cmuClock_SYSCLK, cmuSelect_FSRCO);
  }

  #if defined (_SILICON_LABS_32B_SERIES_2_CONFIG_2) || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_3)
  CMU_ClockEnable(cmuClock_DPLL0, true);
  #endif

  CMU_DPLLLock(&dpllInit);

  if (selected_sysclk == cmuSelect_HFRCODPLL) {
    CMU_ClockSelectSet(cmuClock_SYSCLK, selected_sysclk);
  }
#else
  #error Must define HAL_CLK_HFCLK_SOURCE
#endif // HAL_CLK_HFCLK_SOURCE

/* LFCLK */
#if (HAL_CLK_LFACLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)   \
  || (HAL_CLK_LFBCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)  \
  || (HAL_CLK_LFCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)  \
  || (HAL_CLK_LFECLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)  \
  || (HAL_CLK_EM23CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO) \
  || (HAL_CLK_EM4CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)  \
  || (HAL_CLK_RTCCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  #if !BSP_CLK_LFXO_PRESENT
    #error "Cannot select LFXO when LFXO is not present"
  #endif
  uint8_t lfxoTuneModule;
  uint8_t lfxoTuneToken;
  uint8_t lfxoTempTune;
  CMU_LFXOInit_TypeDef lfxoInit = BSP_CLK_LFXO_INIT;

  // if halconfig specifies lfxo ctune
  #if defined(BSP_CLK_LFXO_CTUNE) && BSP_CLK_LFXO_CTUNE > 0
  lfxoTempTune = BSP_CLK_LFXO_CTUNE;
  #endif // BSP_CLK_HFXO_CTUNE

  // check factory calibrated ctune value
  if (halInternalGetModuleLfxoTune(&lfxoTuneModule)) {
    lfxoTempTune = lfxoTuneModule;
  }
  // otherwise check for lfxo tune in mfg token
  else if (halInternalGetLfxoTuneToken(&lfxoTuneToken)) {
    lfxoTempTune = lfxoTuneToken;
  } else {
    // satisfy MISRA 15.7
  }

  #if defined(_SILICON_LABS_32B_SERIES_1)
  lfxoInit.ctune = lfxoTempTune;
  #elif defined(_SILICON_LABS_32B_SERIES_2)
  lfxoInit.capTune = lfxoTempTune;
  #else
  #error Unknown device type
  #endif

  CMU_LFXOInit(&lfxoInit);
  CMU_LFXOPrecisionSet(HAL_LFXO_PRECISION);

  // Set system LFXO frequency
  SystemLFXOClockSet(BSP_CLK_LFXO_FREQ);
#endif // LFCLK

#if defined(_SILICON_LABS_32B_SERIES_1)
  // LFA
#if (HAL_CLK_LFACLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFXO);
#elif (HAL_CLK_LFACLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_LFRCO);
#elif (HAL_CLK_LFACLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_ULFRCO);
#elif (HAL_CLK_LFACLK_SOURCE == HAL_CLK_LFCLK_SOURCE_HFLE)
  CMU_ClockSelectSet(cmuClock_LFA, cmuSelect_HFCLKLE);
#endif

  // LFB
#if (HAL_CLK_LFBCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO);
#elif (HAL_CLK_LFBCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFRCO);
#elif (HAL_CLK_LFBCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_ULFRCO);
#elif (HAL_CLK_LFBCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_HFLE)
  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_HFCLKLE);
#endif

  // LFC
#if (HAL_CLK_LFCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_LFC, cmuSelect_LFXO);
#elif (HAL_CLK_LFCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_LFC, cmuSelect_LFRCO);
#endif

  // LFE
#if (HAL_CLK_LFECLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);
#elif (HAL_CLK_LFECLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFRCO);
#elif (HAL_CLK_LFECLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_ULFRCO);
#endif

#elif defined(_SILICON_LABS_32B_SERIES_2)
  // EM01
#if (HAL_CLK_EM01CLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFXO)
  CMU_ClockSelectSet(cmuClock_EM01GRPACLK, cmuSelect_HFXO);
#elif (HAL_CLK_EM01CLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFRCO)
  CMU_ClockSelectSet(cmuClock_EM01GRPACLK, cmuSelect_HFRCO);
#elif (HAL_CLK_EM01CLK_SOURCE == HAL_CLK_HFCLK_SOURCE_HFRCODPLL)
  CMU_ClockSelectSet(cmuClock_EM01GRPACLK, cmuSelect_HFRCODPLL);
#endif
  // EM23
#if (HAL_CLK_EM23CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_EM23GRPACLK, cmuSelect_LFXO);
#elif (HAL_CLK_EM23CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_EM23GRPACLK, cmuSelect_LFRCO);
#elif (HAL_CLK_EM23CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_EM23GRPACLK, cmuSelect_ULFRCO);
#endif

  // EM4
#if (HAL_CLK_EM4CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_EM4GRPACLK, cmuSelect_LFXO);
#elif (HAL_CLK_EM4CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_EM4GRPACLK, cmuSelect_LFRCO);
#elif (HAL_CLK_EM4CLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_EM4GRPACLK, cmuSelect_ULFRCO);
#endif

  // RTCC
#if defined(RTCC_PRESENT)
#if (HAL_CLK_RTCCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFXO)
  CMU_ClockSelectSet(cmuClock_RTCCCLK, cmuSelect_LFXO);
#elif (HAL_CLK_RTCCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_LFRCO)
  CMU_ClockSelectSet(cmuClock_RTCCCLK, cmuSelect_LFRCO);
#elif (HAL_CLK_RTCCCLK_SOURCE == HAL_CLK_LFCLK_SOURCE_ULFRCO)
  CMU_ClockSelectSet(cmuClock_RTCCCLK, cmuSelect_ULFRCO);
#endif
#endif // RTCC_PRESENT
#endif // _SILICON_LABS_32B_SERIES_1
}

Ecode_t halConfigInit(void)
{
  Ecode_t status = ECODE_OK;

  INTERRUPTS_ON();   //enables using USB and the proper emberSerialReadByte
#if defined(_EMU_DCDCCTRL_MASK) || defined(_DCDC_CTRL_MASK)
#if BSP_DCDC_PRESENT
  EMU_DCDCInit_TypeDef dcdcInit = BSP_DCDC_INIT;
  #if HAL_DCDC_BYPASS
  dcdcInit.dcdcMode = emuDcdcMode_Bypass;
  #endif
  EMU_DCDCInit(&dcdcInit);
#else
  EMU_DCDCPowerOff();
#endif
#endif //_EMU_DCDCCTRL_MASK

#if HAL_EMU_ENABLE
  EMU_EM23Init_TypeDef em23init = EMU_EM23INIT_DEFAULT;
  #if HAL_EMU_EM23_VREG
  em23init.em23VregFullEn = true;
  #endif
  #if HAL_EMU_EM23_VSCALE == HAL_EMU_EM23_VSCALE_FASTWAKEUP
  em23init.vScaleEM23Voltage = emuVScaleEM23_FastWakeup;
  #elif HAL_EMU_EM23_VSCALE == HAL_EMU_EM23_VSCALE_LOWPOWER
  em23init.vScaleEM23Voltage = emuVScaleEM23_LowPower;
  #endif
  EMU_EM23Init(&em23init);
#endif //HAL_EMU_ENABLE

// EMHAL-2448 workaround until zigbee on UC is available.
#if defined(SL_RAIL_UTIL_RSSI_OFFSET) && (PHY_RAIL || PHY_DUALRAIL)
  (void)RAIL_SetRssiOffset(RAIL_EFR32_HANDLE, (int8_t)SL_RAIL_UTIL_RSSI_OFFSET);
#endif

  halConfigClockInit();

#if (HAL_BUTTON_COUNT > 0)
#if (defined(BSP_BUTTON0_PIN) && defined(BSP_LED0_PIN) && (((BSP_BUTTON0_PIN) == (BSP_LED0_PIN)) && ((BSP_BUTTON0_PORT) == (BSP_LED0_PORT))))  \
  || (defined(BSP_BUTTON0_PIN) && defined(BSP_LED1_PIN) && (((BSP_BUTTON0_PIN) == (BSP_LED1_PIN)) && ((BSP_BUTTON0_PORT) == (BSP_LED1_PORT)))) \
  || (defined(BSP_BUTTON1_PIN) && defined(BSP_LED1_PIN) && (((BSP_BUTTON1_PIN) == (BSP_LED1_PIN)) && ((BSP_BUTTON1_PORT) == (BSP_LED1_PORT)))) \
  || (defined(BSP_BUTTON1_PIN) && defined(BSP_LED0_PIN) && (((BSP_BUTTON1_PIN) == (BSP_LED0_PIN)) && ((BSP_BUTTON1_PORT) == (BSP_LED0_PORT))))
  // Skip Button initialization due to button and LED conflict
  #warning "Buttons and LEDs share pins. Skipping Button initialization."
#else
  halInternalInitButton();
#endif
#endif

#if (HAL_LED_COUNT > 0)
  halInternalInitLed();
#endif

#if (HAL_GPIO_MAX > 0)
  halConfigInitGpio();
#endif

#if defined (_EFR_DEVICE)
#if (HAL_PTI_ENABLE)
  #if HAL_PTI_MODE == HAL_PTI_MODE_SPI
  // SPI Mode
    #define PTI_MODE RAIL_PTI_MODE_SPI
  #elif HAL_PTI_MODE == HAL_PTI_MODE_UART
  // UART Mode
    #define PTI_MODE RAIL_PTI_MODE_UART
  // DCLK unused in UART mode
    #undef BSP_PTI_DCLK_LOC
    #undef BSP_PTI_DCLK_PORT
    #undef BSP_PTI_DCLK_PIN
    #define BSP_PTI_DCLK_LOC  0
    #define BSP_PTI_DCLK_PORT 0
    #define BSP_PTI_DCLK_PIN  0
  #elif HAL_PTI_MODE == HAL_PTI_MODE_UART_ONEWIRE
  // Onewire UART Mode
    #define PTI_MODE RAIL_PTI_MODE_UART_ONEWIRE
  // DCLK unused in onewire mode
    #undef BSP_PTI_DCLK_LOC
    #undef BSP_PTI_DCLK_PORT
    #undef BSP_PTI_DCLK_PIN
    #define BSP_PTI_DCLK_LOC    0
    #define BSP_PTI_DCLK_PORT   0
    #define BSP_PTI_DCLK_PIN    0
  // DFRAME unused in onewire mode
    #undef BSP_PTI_DFRAME_LOC
    #undef BSP_PTI_DFRAME_PORT
    #undef BSP_PTI_DFRAME_PIN
    #define BSP_PTI_DFRAME_LOC  0
    #define BSP_PTI_DFRAME_PORT 0
    #define BSP_PTI_DFRAME_PIN  0
  #else
    #error HAL_PTI_MODE not recognized
  #endif //HAL_PTI_MODE

  // Newer chips use a different scheme for alternate function routing. For
  // those chips, the _LOC defines aren't used but still need definitions to
  // satisfy the compiler.
  #if !defined(_SILICON_LABS_32B_SERIES_1)
    #define BSP_PTI_DFRAME_LOC 0
    #define BSP_PTI_DOUT_LOC 0
    #define BSP_PTI_DCLK_LOC 0
  #endif

  RAIL_PtiConfig_t ptiInit = { PTI_MODE,
                               HAL_PTI_BAUD_RATE,             /* 1.6 MHz baud */
                               BSP_PTI_DOUT_LOC,              /* DOUT location */
                               (uint8_t) BSP_PTI_DOUT_PORT,   /* DOUT port */
                               BSP_PTI_DOUT_PIN,              /* DOUT pin */
                               BSP_PTI_DCLK_LOC,              /* DCLK location */
                               (uint8_t) BSP_PTI_DCLK_PORT,   /* DCLK port */
                               BSP_PTI_DCLK_PIN,              /* DCLK pin */
                               BSP_PTI_DFRAME_LOC,            /* DFRAME location */
                               (uint8_t) BSP_PTI_DFRAME_PORT, /* DFRAME port */
                               BSP_PTI_DFRAME_PIN };          /* DFRAME pin */
#if (PHY_RAIL || PHY_DUALRAIL)
  RAIL_ConfigPti(NULL, &ptiInit);
#else
  PTI_Config(&ptiInit);
#endif
#endif // HAL_PTI_ENABLE
#endif // defined (_EFR_DEVICE)

#if (HAL_COEX_ENABLE)
#if     (PHY_RAIL || PHY_DUALRAIL)
  (void) RAIL_ConfigMultiTimer(true);
#endif//(PHY_RAIL || PHY_DUALRAIL)
  HalPtaOptions ptaOptions = halPtaGetOptions();
  halPtaSetOptions(ptaOptions);
  halInternalInitPta();
#endif

#if (HAL_ANTDIV_ENABLE || defined(_SILICON_LABS_32B_SERIES_2))
  (void) halInitAntenna();
#endif

#if (HAL_SERIAL_USART0_ENABLE)
  COM_Init_t initDataUsart0 = COM_USART0_DEFAULT;
  status = COM_Init(comPortUsart0, &initDataUsart0);
  if (status != ECODE_OK) {
    return status;
  }
#endif
#if (HAL_SERIAL_USART1_ENABLE)
  COM_Init_t initDataUsart1 = (COM_Init_t) COM_USART1_DEFAULT;
  status = COM_Init(comPortUsart1, &initDataUsart1);
  if (status != ECODE_OK) {
    return status;
  }
#endif
#if (HAL_SERIAL_USART2_ENABLE)
  COM_Init_t initDataUsart2 = (COM_Init_t) COM_USART2_DEFAULT;
  status = COM_Init(comPortUsart2, &initDataUsart2);
  if (status != ECODE_OK) {
    return status;
  }
#endif
#if (HAL_SERIAL_USART3_ENABLE)
  COM_Init_t initDataUsart3 = (COM_Init_t) COM_USART3_DEFAULT;
  status = COM_Init(comPortUsart3, &initDataUsart3);
  if (status != ECODE_OK) {
    return status;
  }
#endif
#if (HAL_SERIAL_LEUART0_ENABLE)
  COM_Init_t initDataLeuart0 = (COM_Init_t) COM_LEUART0_DEFAULT;
  status = COM_Init(comPortLeuart0, &initDataLeuart0);
  if (status != ECODE_OK) {
    return status;
  }
#endif
#if (HAL_SERIAL_LEUART1_ENABLE)
  COM_Init_t initDataLeuart1 = (COM_Init_t) COM_LEUART1_DEFAULT;
  status = COM_Init(comPortLeuart1, &initDataLeuart1);
  if (status != ECODE_OK) {
    return status;
  }
#endif

#if (HAL_VCOM_ENABLE)
  #if HAL_IOEXP_VCOM_ENABLE
  BSP_Init(BSP_INIT_IOEXP);
  BSP_PeripheralAccess(BSP_IOEXP_VCOM, true);
  #elif defined (BSP_VCOM_ENABLE_PORT)
  GPIO_PinModeSet(BSP_VCOM_ENABLE_PORT, BSP_VCOM_ENABLE_PIN, gpioModePushPull, 1);
  #else
  #warning VCOM enabled without configuring enable pin or IOEXP
  #endif
#endif // (HAL_SERIAL_VCOM_ENABLE)

#if (HAL_SERIAL_RXWAKE_ENABLE)
  COM_RxGpioWakeInit();
#endif

#if (HAL_FEM_ENABLE)
  initFem();
#endif

#if (HAL_WDOG_ENABLE)
  halInternalEnableWatchDog();
#endif
  return status;
}

#define ANTDIV_PHY_DEFAULT_ENABLED (ANTENNA_RX_DEFAULT_MODE != HAL_ANTENNA_MODE_DISABLED)
#define HAL_RADIO_CONFIG_154_2P4_DEFAULT_SUPPORTED                   \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || !ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || !HAL_COEX_PHY_ENABLED)         \
   && (HAL_FEM_RUNTIME_PHY_SELECT || !HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_ANT_DIV_SUPPORTED                  \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || !HAL_COEX_PHY_ENABLED)        \
   && (HAL_FEM_RUNTIME_PHY_SELECT || !HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_COEX_SUPPORTED                      \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || !ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || HAL_COEX_PHY_ENABLED)          \
   && (HAL_FEM_RUNTIME_PHY_SELECT || !HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_SUPPORTED             \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || HAL_COEX_PHY_ENABLED)         \
   && (HAL_FEM_RUNTIME_PHY_SELECT || !HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_FEM_SUPPORTED                       \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || !ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || !HAL_COEX_PHY_ENABLED)         \
   && (HAL_FEM_RUNTIME_PHY_SELECT || HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_ANT_DIV_FEM_SUPPORTED              \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || !HAL_COEX_PHY_ENABLED)        \
   && (HAL_FEM_RUNTIME_PHY_SELECT || HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_COEX_FEM_SUPPORTED                  \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || !ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || HAL_COEX_PHY_ENABLED)          \
   && (HAL_FEM_RUNTIME_PHY_SELECT || HAL_FEM_OPTIMIZED_PHY_ENABLE))
#define HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_FEM_SUPPORTED         \
  ((HAL_ANTDIV_RX_RUNTIME_PHY_SELECT || ANTDIV_PHY_DEFAULT_ENABLED) \
   && (HAL_COEX_RUNTIME_PHY_SELECT || HAL_COEX_PHY_ENABLED)         \
   && (HAL_FEM_RUNTIME_PHY_SELECT || HAL_FEM_OPTIMIZED_PHY_ENABLE))

#if ANTDIV_PHY_DEFAULT_ENABLED
#define DEFAULT_ANTDIV_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_ANT_DIV
#else //!ANTDIV_PHY_DEFAULT_ENABLED
#define DEFAULT_ANTDIV_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_DEFAULT
#endif //ANTDIV_PHY_DEFAULT_ENABLED

#if HAL_COEX_PHY_ENABLED
#define DEFAULT_COEX_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_COEX
#else //!HAL_COEX_PHY_ENABLED
#define DEFAULT_COEX_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_DEFAULT
#endif //HAL_COEX_PHY_ENABLED

#if HAL_FEM_OPTIMIZED_PHY_ENABLE
#define DEFAULT_FEM_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_FEM
#else //!HAL_FEM_OPTIMIZED_PHY_ENABLE
#define DEFAULT_FEM_RADIO_CONFIG HAL_RADIO_CONFIG_154_2P4_ANT_DIV
#endif //HAL_FEM_OPTIMIZED_PHY_ENABLE

#define DEFAULT_RADIO_CONFIG (HAL_RADIO_CONFIG_154_2P4_DEFAULT \
                              | DEFAULT_ANTDIV_RADIO_CONFIG    \
                              | DEFAULT_COEX_RADIO_CONFIG      \
                              | DEFAULT_FEM_RADIO_CONFIG)

#if     HAL_COEX_RUNTIME_PHY_SELECT
#if     HAL_COEX_PHY_ENABLED
bool halCoexPhySelectedCoex = true;
#else//!HAL_COEX_PHY_ENABLED
bool halCoexPhySelectedCoex = false;
#endif//HAL_COEX_PHY_ENABLED
#elif   HAL_COEX_PHY_ENABLED
#define halCoexPhySelectedCoex (true)
#else //!HAL_COEX_PHY_ENABLED
#define halCoexPhySelectedCoex (false)
#endif//HAL_COEX_RUNTIME_PHY_SELECT

static volatile HalRadioConfig_t desiredRadioConfig = DEFAULT_RADIO_CONFIG;
static volatile HalRadioConfig_t activeRadioConfig = DEFAULT_RADIO_CONFIG;

#if HAL_ANTDIV_RX_RUNTIME_PHY_SELECT
bool halAntDivRxPhyChanged(void)
{
  return ((desiredRadioConfig & HAL_RADIO_CONFIG_154_2P4_ANT_DIV)
          != (activeRadioConfig & HAL_RADIO_CONFIG_154_2P4_ANT_DIV));
}
#define halAntDivRxPhySelected() (halGetAntennaRxMode() == HAL_ANTENNA_MODE_DIVERSITY)
#else //!HAL_ANTDIV_RX_RUNTIME_PHY_SELECT
#define halAntDivRxPhySelected() (ANTENNA_RX_DEFAULT_MODE != HAL_ANTENNA_MODE_DISABLED)
#endif //HAL_ANTDIV_RX_RUNTIME_PHY_SELECT

#if HAL_FEM_RUNTIME_PHY_SELECT
static bool halFemPhySelected = (HAL_FEM_OPTIMIZED_PHY_ENABLE != 0U);

bool halFemPhyIsEnabled(void)
{
  return halFemPhySelected;
}

void halFemPhySetEnable(bool enable)
{
  halFemPhySelected = enable;
}
#else //!HAL_FEM_RUNTIME_PHY_SELECT

#if HAL_FEM_OPTIMIZED_PHY_ENABLE
#define halFemPhySelected (true)
#else //!HAL_FEM_OPTIMIZED_PHY_ENABLE
#define halFemPhySelected (false)
#endif //HAL_FEM_OPTIMIZED_PHY_ENABLE

bool halFemPhyIsEnabled(void)
{
  return halFemPhySelected;
}

void halFemPhySetEnable(bool enable)
{
  (void)enable;
}
#endif //HAL_FEM_RUNTIME_PHY_SELECT

HalRadioConfig_t halGetDesiredRadioConfig(void)
{
  return ((halAntDivRxPhySelected() ? HAL_RADIO_CONFIG_154_2P4_ANT_DIV : HAL_RADIO_CONFIG_154_2P4_DEFAULT)
          | (halCoexPhySelectedCoex ? HAL_RADIO_CONFIG_154_2P4_COEX : HAL_RADIO_CONFIG_154_2P4_DEFAULT)
          | (halFemPhySelected ? HAL_RADIO_CONFIG_154_2P4_FEM : HAL_RADIO_CONFIG_154_2P4_DEFAULT));
}

RAIL_Status_t halPluginConfig2p4GHzRadio(RAIL_Handle_t railHandle)
{
  // Establish the proper radio config supporting antenna diversity
  RAIL_Status_t status = RAIL_STATUS_INVALID_STATE;

  desiredRadioConfig = halGetDesiredRadioConfig();
  switch (desiredRadioConfig) {
#if HAL_RADIO_CONFIG_154_2P4_DEFAULT_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_DEFAULT:
      status = RAIL_IEEE802154_Config2p4GHzRadio(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_DEFAULT_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_ANT_DIV_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_ANT_DIV:
      status = RAIL_IEEE802154_Config2p4GHzRadioAntDiv(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_ANT_DIV_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_COEX_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_COEX:
      status = RAIL_IEEE802154_Config2p4GHzRadioCoex(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_COEX_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX:
      status = RAIL_IEEE802154_Config2p4GHzRadioAntDivCoex(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_FEM_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_FEM:
      status = RAIL_IEEE802154_Config2p4GHzRadioFem(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_FEM_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_ANT_DIV_FEM_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_ANT_DIV_FEM:
      status = RAIL_IEEE802154_Config2p4GHzRadioAntDivFem(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_ANT_DIV_FEM_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_COEX_FEM_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_COEX_FEM:
      status = RAIL_IEEE802154_Config2p4GHzRadioCoexFem(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_COEX_FEM_SUPPORTED
#if HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_FEM_SUPPORTED
    case HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_FEM:
      status = RAIL_IEEE802154_Config2p4GHzRadioAntDivCoexFem(railHandle);
      break;
#endif //HAL_RADIO_CONFIG_154_2P4_ANT_DIV_COEX_FEM_SUPPORTED
    default:
      break;
  }
  assert(status == RAIL_STATUS_NO_ERROR);
  activeRadioConfig = desiredRadioConfig;

 #if ANTENNA_USE_RAIL_SCHEME && (ANTENNA_RX_DEFAULT_MODE != HAL_ANTENNA_MODE_DISABLED)
  // Tell RAIL what Rx antenna mode to use
  extern EmberStatus emRadioConfigRxAntenna(HalAntennaMode mode);
  assert(emRadioConfigRxAntenna(halGetAntennaRxMode()) == EMBER_SUCCESS);
 #endif

  return status;
}

HalRadioConfig_t halGetActiveRadioConfig(void)
{
  return activeRadioConfig;
}
