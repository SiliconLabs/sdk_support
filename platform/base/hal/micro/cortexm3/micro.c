/***************************************************************************//**
 * @file
 * @brief EM3XX micro specific full HAL functions
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
#include "stack/include/ember.h"
#include "include/error.h"

#include "hal/hal.h"
#include "serial/serial.h"
#include "hal/micro/cortexm3/diagnostic.h"
#include "hal/micro/cortexm3/memmap.h"
#include "hal/micro/cortexm3/flash.h"
#include "hal/plugin/debug-jtag/debug-channel.h"
#include "coexistence/protocol/ieee802154/coexistence-802154.h"

#ifdef RTOS
  #include "rtos/rtos.h"
#endif

extern void halStackRadioHoldOffPowerDown(void); // fwd ref
extern void halStackRadioHoldOffPowerUp(void);   // fwd ref

// halInit is called on first initial boot, not on wakeup from sleep.
void halInit(void)
{










  // Determine and record the reason for the reset.  Because this code uses
  // static variables in RAM, it must be performed after RAM segements are
  // initialized, but the RESETINFO segment is left uninitialized.
  halInternalClassifyReset();

  //Fill the unused portion of the memory reserved for the stack.
  //memset() is not being used to do this in case it uses the stack
  //to store the return address.
  volatile uint32_t *dataDestination;
  //This code assumes that the __get_MSP() return value and
  //_CSTACK_SEGMENT_BEGIN are both 32-bit aligned values.
  dataDestination = (uint32_t*) (__get_MSP() - 4U);
  //Start at current stack ptr fill up until CSTACK_SEGMENT_BEGIN
  while (dataDestination >= _CSTACK_SEGMENT_BEGIN) {
    //Fill with magic value interpreted by C-SPY's Stack View
    *dataDestination-- = STACK_FILL_VALUE;
  }

  // Zero out the EMHEAP segment.
  {
    // IAR warns about "integer conversion resulted in truncation" if
    // _EMHEAP_SEGMENT_SIZE is used directly in MEMSET().  This segment
    // should always be smaller than a 16bit size.
    MEMSET(_EMHEAP_SEGMENT_BEGIN, 0, (_EMHEAP_SEGMENT_SIZE & 0xFFFFu));
  }

  (void)halCommonStartXtal();

  halInternalSetRegTrim(false);

  GPIO->DBGCFG |= GPIO_DBGCFG_DBGCFGRSVD;

  #ifndef DISABLE_WATCHDOG
  halInternalEnableWatchDog();
  #endif

  halCommonCalibratePads();

  #ifdef DISABLE_INTERNAL_1V8_REGULATOR
  //Out of reset, VREG 1V8 is enabled.  Update the helper variable
  //to keep the state in agreement with what the disable API is expecting.
  halCommonVreg1v8EnableCount = 1;
  halCommonDisableVreg1v8();
  #endif

  halInternalInitBoard();

  halCommonSwitchToXtal();

  #ifndef DISABLE_RC_CALIBRATION
  halInternalCalibrateFastRc();
  #endif//DISABLE_RC_CALIBRATION

  (void) halInternalStartSystemTimer();

  #ifdef INTERRUPT_DEBUGGING
  //When debugging interrupts/ATOMIC, ensure that our
  //debug pin is properly enabled and idle low.
  I_OUT(I_PORT, I_PIN, I_CFG_HL);
  I_CLR(I_PORT, I_PIN);
  #endif //INTERRUPT_DEBUGGING

  #ifdef USB_CERT_TESTING
  halInternalPowerDownBoard();
  #endif
}

void halReboot(void)
{
  halInternalSysReset(RESET_SOFTWARE_REBOOT);
}

void halPowerDown(void)
{
  emDebugPowerDown();

  halInternalPowerDownUart();

  halInternalPowerDownBoard();
}

// halPowerUp is called from sleep state, not from first initial boot.
void halPowerUp(void)
{










  halInternalPowerUpKickXtal();

  halCommonCalibratePads();

  //NOTE: The register VREG is a high voltage register that holds its
  //      state across deep sleep.  While halInit() must be sensitive
  //      to the define DISABLE_INTERNAL_1V8_REGULATOR, halPowerUp()
  //      trusts that VREG hasn't been modified and therefore doesn't
  //      need to take further action with respect to VREG.

  halInternalPowerUpBoard();

  halInternalBlockUntilXtal();

  halInternalPowerUpUart();

  emDebugPowerUp();
}

// halSuspend suspends all board activity except for USB
void halSuspend(void)
{
  halInternalPowerDownUart();

  #ifdef CORTEXM3_EM35X_USB
  halInternalSuspendBoard();
  #endif
}

// halResume restores all board activity from a previous USB suspend
void halResume(void)
{










  halInternalPowerUpKickXtal();

  halCommonCalibratePads();

  #ifdef CORTEXM3_EM35X_USB
  halInternalResumeBoard();
  #endif

  halInternalBlockUntilXtal();

  halInternalPowerUpUart();
}

#ifndef EMBER_APPLICATION_HAS_CUSTOM_SLEEP_CALLBACK
WEAK(void halSleepCallback(boolean enter, SleepModes sleepMode))
{
}

#endif // EMBER_APPLICATION_HAS_CUSTOM_SLEEP_CALLBACK

//If the board file defines runtime powerup/powerdown GPIO configuration,
//instantiate the variables and implement halStackRadioPowerDownBoard/
//halStackRadioPowerUpBoard which the stack will use to control the
//power state of radio specific GPIO.  If the board file does not define
//runtime GPIO configuration, the compile time configuration will work as
//it always has.
#if defined(DEFINE_POWERUP_GPIO_CFG_VARIABLES)          \
  && defined(DEFINE_POWERUP_GPIO_OUTPUT_DATA_VARIABLES) \
  && defined(DEFINE_POWERDOWN_GPIO_CFG_VARIABLES)       \
  && defined(DEFINE_POWERDOWN_GPIO_OUTPUT_DATA_VARIABLES)

DEFINE_POWERUP_GPIO_CFG_VARIABLES();
DEFINE_POWERUP_GPIO_OUTPUT_DATA_VARIABLES();
DEFINE_POWERDOWN_GPIO_CFG_VARIABLES();
DEFINE_POWERDOWN_GPIO_OUTPUT_DATA_VARIABLES();

#if defined(DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE)
DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE();
#endif
#if defined(DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE)
DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE();
#endif

static void rmwRadioPowerCfgReg(uint32_t radioPowerBoardGpioMask,
                                uint16_t radioPowerCfg[],
                                uint32_t volatile * cfgReg,
                                uint8_t cfgVar)
{
  uint32_t temp = *cfgReg;
  uint8_t i;

  //don't waste time with a register that doesn't have anything to be done
  if ((radioPowerBoardGpioMask & (((GpioMaskType)0xF) << (4U * cfgVar))) != 0U) {
    //loop over the 4 pins of the cfgReg
    for (i = 0U; i < 4U; i++) {
      if (((radioPowerBoardGpioMask >> ((4U * cfgVar) + i)) & 1U) != 0U) {
        //read-modify-write the pin's cfg if the mask says it pertains
        //to the radio's power state
        temp &= ~(0xFU << (4U * i));
        temp |= (radioPowerCfg[cfgVar] & (0xFU << (4U * i)));
      }
    }
  }

  *cfgReg = temp;
}

static void rmwRadioPowerOutReg(uint32_t radioPowerBoardGpioMask,
                                uint8_t radioPowerOut[],
                                uint32_t volatile * outReg,
                                uint8_t outVar)
{
  uint32_t temp = *outReg;
  uint8_t i;

  //don't waste time with a register that doesn't have anything to be done
  if ((radioPowerBoardGpioMask & (((GpioMaskType)0xFFU) << (8U * outVar))) != 0U) {
    //loop over the 8 pins of the outReg
    for (i = 0U; i < 8U; i++) {
      if (((radioPowerBoardGpioMask >> ((8U * outVar) + i)) & 1U) != 0U) {
        //read-modify-write the pin's out if the mask says it pertains
        //to the radio's power state
        temp &= ~(0x1U << (1U * i));
        temp |= (radioPowerOut[outVar] & (0x1U << (1U * i)));
      }
    }
  }

  *outReg = temp;
}

void halStackRadioPowerDownBoard(void)
{
  uint8_t i, j;
  (void) halPtaStackEvent(PTA_STACK_EVENT_RX_IDLED, 0U);
  // Don't touch PTA Tx Request here
  halStackRadioHoldOffPowerDown();

 #if     defined(DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE)
  if (gpioRadioPowerBoardMask == 0U) {
    //If the mask indicates there are no special GPIOs for the
    //radio that need their power state to be conrolled by the stack,
    //don't bother attempting to do anything.
    return;
  }

  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerOutReg(gpioRadioPowerBoardMask, gpioOutPowerDown, &GPIO->P[i].OUT, i);
  }

  j = 0;
  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerCfgReg(gpioRadioPowerBoardMask, gpioCfgPowerDown, &GPIO->P[i].CFGL, j++);
    rmwRadioPowerCfgReg(gpioRadioPowerBoardMask, gpioCfgPowerDown, &GPIO->P[i].CFGH, j++);
  }
 #endif//defined(DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE)
}

void halStackRadio2PowerDownBoard(void)
{
  // Neither PTA nor RHO are supported on Radio2
 #if     defined(DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE)
  uint8_t i, j;
  if (gpioRadio2PowerBoardMask == 0U) {
    //If the mask indicates there are no special GPIOs for the
    //radio that need their power state to be conrolled by the stack,
    //don't bother attempting to do anything.
    return;
  }

  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerOutReg(gpioRadio2PowerBoardMask, gpioOutPowerDown, &GPIO->P[i].OUT, i);
  }

  j = 0;
  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerCfgReg(gpioRadio2PowerBoardMask, gpioCfgPowerDown, &GPIO->P[i].CFGL, j++);
    rmwRadioPowerCfgReg(gpioRadio2PowerBoardMask, gpioCfgPowerDown, &GPIO->P[i].CFGH, j++);
  }
 #endif//defined(DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE)
}

void halStackRadioPowerUpBoard(void)
{
  uint8_t i, j;
  (void) halPtaStackEvent(PTA_STACK_EVENT_RX_LISTEN, 0U);
  halStackRadioHoldOffPowerUp();

 #if     defined(DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE)
  if (gpioRadioPowerBoardMask == 0U) {
    //If the mask indicates there are no special GPIOs for the
    //radio that need their power state to be conrolled by the stack,
    //don't bother attempting to do anything.
    return;
  }

  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerOutReg(gpioRadioPowerBoardMask, gpioOutPowerUp, &GPIO->P[i].OUT, i);
  }

  j = 0;
  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerCfgReg(gpioRadioPowerBoardMask, gpioCfgPowerUp, &GPIO->P[i].CFGL, j++);
    rmwRadioPowerCfgReg(gpioRadioPowerBoardMask, gpioCfgPowerUp, &GPIO->P[i].CFGH, j++);
  }
 #endif//defined(DEFINE_GPIO_RADIO_POWER_BOARD_MASK_VARIABLE)
}

void halStackRadio2PowerUpBoard(void)
{
  // Neither PTA nor RHO are supported on Radio2
 #if     defined(DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE)
  uint8_t i, j;
  if (gpioRadio2PowerBoardMask == 0U) {
    //If the mask indicates there are no special GPIOs for the
    //radio that need their power state to be conrolled by the stack,
    //don't bother attempting to do anything.
    return;
  }

  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerOutReg(gpioRadio2PowerBoardMask, gpioOutPowerUp, &GPIO->P[i].OUT, i);
  }

  j = 0;
  for (i = 0U; i < 3U; i++) {
    rmwRadioPowerCfgReg(gpioRadio2PowerBoardMask, gpioCfgPowerUp, &GPIO->P[i].CFGL, j++);
    rmwRadioPowerCfgReg(gpioRadio2PowerBoardMask, gpioCfgPowerUp, &GPIO->P[i].CFGH, j++);
  }
 #endif//defined(DEFINE_GPIO_RADIO2_POWER_BOARD_MASK_VARIABLE)
}

#else

//If the board file uses traditional compile time powerup/powerdown GPIO
//configuration, stub halStackRadioPowerDownBoard/halStackRadioPowerUpBoard
//which the stack would have used to control the power state of radio
//relevant GPIO.  With compile time configuration, only the traditional
//halInternalPowerDownBoard and halInternalPowerUpBoard funtions configure
//the GPIO.  RHO powerdown/up still needs to be managed however.

void halStackRadioPowerDownBoard(void)
{
  (void) halPtaStackEvent(PTA_STACK_EVENT_RX_IDLED, 0U);
  // Don't touch PTA Tx Request here
  halStackRadioHoldOffPowerDown();
}

void halStackRadio2PowerDownBoard(void)
{
  // Neither PTA nor RHO are supported on Radio2
}

void halStackRadioPowerUpBoard(void)
{
  (void) halPtaStackEvent(PTA_STACK_EVENT_RX_LISTEN, 0U);
  halStackRadioHoldOffPowerUp();
}

void halStackRadio2PowerUpBoard(void)
{
  // Neither PTA nor RHO are supported on Radio2
}

#endif

void halStackRadioPowerMainControl(bool powerUp)
{
  if (powerUp) {
    halRadioPowerUpHandler();
  } else {
    halRadioPowerDownHandler();
  }
}

void halStackProcessBootCount(void)
{
  //Note: Because this always counts up at every boot (called from emberInit),
  //and non-volatile storage has a finite number of write cycles, this will
  //eventually stop working.  Disable this token call if non-volatile write
  //cycles need to be used sparingly.
  halCommonIncrementCounterToken(TOKEN_STACK_BOOT_COUNTER);
}

PGM_P halGetResetString(void)
{
  // Table used to convert from reset types to reset strings.
  #define RESET_BASE_DEF(basename, value, string)  string,
  #define RESET_EXT_DEF(basename, extname, extvalue, string)     /*nothing*/
  static PGM char resetStringTable[][4] = {
    #include "reset-def.h"
  };
  #undef RESET_BASE_DEF
  #undef RESET_EXT_DEF

  uint8_t resetInfo = halGetResetInfo();
  if (resetInfo >= (sizeof(resetStringTable) / sizeof(resetStringTable[0]))) {
    return resetStringTable[0x00];   // return unknown
  } else {
    return resetStringTable[resetInfo];
  }
}

// Note that this API should be used in conjunction with halGetResetString
//  to get the full information, as this API does not provide a string for
//  the base reset type
PGM_P halGetExtendedResetString(void)
{
  // Create a table of reset strings for each extended reset type
  typedef PGM char ResetStringTableType[][4];
  #define RESET_BASE_DEF(basename, value, string) \
  }; static ResetStringTableType basename##ResetStringTable = {
  #define RESET_EXT_DEF(basename, extname, extvalue, string)  string,
  {
    #include "reset-def.h"
  };
  #undef RESET_BASE_DEF
  #undef RESET_EXT_DEF

  // Create a table of pointers to each of the above tables
  #define RESET_BASE_DEF(basename, value, string)  (ResetStringTableType *)basename##ResetStringTable,
  #define RESET_EXT_DEF(basename, extname, extvalue, string)     /*nothing*/
  static ResetStringTableType * PGM extendedResetStringTablePtrs[] = {
    #include "reset-def.h"
  };
  #undef RESET_BASE_DEF
  #undef RESET_EXT_DEF

  // Create a table of the size of each of the above tables
  #define RESET_BASE_DEF(basename, value, string)  COUNTOF(basename##ResetStringTable),
  #define RESET_EXT_DEF(basename, extname, extvalue, string)     /*nothing*/
  static uint8_t PGM countOfPerBasetypeExtendedResetStrings[] = {
    #include "reset-def.h"
  };
  #undef RESET_BASE_DEF
  #undef RESET_EXT_DEF

  uint16_t fullResetInfo = halGetExtendedResetInfo();
  uint8_t baseResetType = RESET_BASE_TYPE(fullResetInfo);
  uint8_t extResetField = RESET_EXTENDED_FIELD(fullResetInfo);

  // ensure that we won't be trying to access any array out of bounds
  if (baseResetType < COUNTOF(extendedResetStringTablePtrs)
      && extResetField < countOfPerBasetypeExtendedResetStrings[baseResetType]) {
    return (*extendedResetStringTablePtrs[baseResetType])[extResetField];
  } else {
    // The reset info is not valid, return the first one (should be "UNK")
    return (*extendedResetStringTablePtrs[0x00u])[0x00u];
  }
}

// Translate EM3xx reset codes to the codes previously used by the EM2xx.
// If there is no corresponding code, return the EM3xx base code with bit 7 set.
uint8_t halGetEm2xxResetInfo(void)
{
  uint8_t reset = halGetResetInfo();

  // Any reset with an extended value field of zero is considered an unknown
  // reset, except for FIB resets.
  if ((RESET_EXTENDED_FIELD(halGetExtendedResetInfo()) == 0U)
      && (reset != RESET_FIB)) {
    return EM2XX_RESET_UNKNOWN;
  }

  switch (reset) {
    case RESET_UNKNOWN:
      return EM2XX_RESET_UNKNOWN;
    case RESET_BOOTLOADER:
      return EM2XX_RESET_BOOTLOADER;
    case RESET_EXTERNAL:    // map pin resets to poweron for EM2xx compatibility
//    return EM2XX_RESET_EXTERNAL;
    case RESET_POWERON:
      return EM2XX_RESET_POWERON;
    case RESET_WATCHDOG:
      return EM2XX_RESET_WATCHDOG;
    case RESET_SOFTWARE:
      return EM2XX_RESET_SOFTWARE;
    case RESET_CRASH:
      return EM2XX_RESET_ASSERT;
    default:
      return (reset | 0x80);    // set B7 for all other reset codes
  }
}
