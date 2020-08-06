/***************************************************************************//**
 * @brief IEC60335 Class B c based WDT test
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
 /*! @addtogroup IEC60335_WDOG_TEST
 * @{
 */

#include "iec60335_class_b_wdt_test.h"


#ifdef TESSY
/*! @cond TESSY */
uint32_t TS_TessyDummyWDOGCTRL(void);
uint32_t TS_TessyDummyWDOGCMD(void);
#define SyncWDOGCTRL()   (TS_TessyDummyWDOGCTRL())
#define SyncWDOGCMD()    (TS_TessyDummyWDOGCMD())
/*! @endcond */
#else
#define SyncWDOGCTRL()   (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CTRL)
#define SyncWDOGCMD()    (WDOG->SYNCBUSY & WDOG_SYNCBUSY_CMD)
#endif


/*! @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#if defined (__ICCARM__)
    #pragma section="IEC60335_code"
#else
__attribute__((section(".IEC60335_code")))
#endif
/*! @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */
testResult_t IEC60335_ClassB_initWDT(void)
{
  testResult_t result = IEC60335_testFailed;
  uint32_t     resetcause;
  /* check for core locked condition */
  resetcause = RMU->RSTCAUSE;
  if (!(RMU->CTRL & (1 << _RMU_CTRL_LOCKUPRDIS_SHIFT)))
  {
    /* check POR or Ext-reset reset as last reset event */
    if ((resetcause == RMU_RSTCAUSE_PORST)
        || ((resetcause & RMU_RSTCAUSE_EXTRST) && ((~resetcause) & 0x3)))
    {
      /* enable LE clock */
      CMU->HFCORECLKEN0 |= CMU_HFCORECLKEN0_LE;
      /* clear flag */
      RMU->CMD     = RMU_CMD_RCCLR;
      EMU->AUXCTRL = EMU_AUXCTRL_HRCCLR;
      EMU->AUXCTRL = 0;
      /* init WDOG and start */
      while (SyncWDOGCTRL()) ;
      WDOG->CTRL = 0x80D;
      /* optional WDOG_CTRL_DEBUGRUN */
      result = IEC60335_testInProgress;
    }
    /* WDOG reset detected (second entry) */
    else if ((resetcause & RMU_RSTCAUSE_WDOGRST) && (~resetcause & 0x03))
    {
      /* test has been successful */
      result = IEC60335_testPassed;
      /* optional clear flag */
/*    RMU->CMD = RMU_CMD_RCCLR; */
    }
  }

  return result;
}

/*! @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#if defined (__ICCARM__)
    #pragma section="IEC60335_code"
#else
__attribute__((section(".IEC60335_code")))
#endif
/*! @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */
void IEC60335_ClassB_Refresh_WDT(void)
{
  /* If a previous clearing is being synchronized to LF domain, then there
   * is no point in waiting for it to complete before clearing over again.
   * This avoids stalling the core in the typical use case where some idle loop
   * keeps clearing the watchdog. */
  if (SyncWDOGCMD())
  {
    return;
  }

  WDOG->CMD = WDOG_CMD_CLEAR;
}

/*! @cond DO_NOT_INCLUDE_WITH_DOXYGEN */
#if defined (__ICCARM__)
    #pragma section="IEC60335_code"
#else
__attribute__((section(".IEC60335_code")))
#endif
/*! @endcond (DO_NOT_INCLUDE_WITH_DOXYGEN) */
testResult_t IEC60335_ClassB_Force_WDT_Reset(void)
{
  testResult_t result = IEC60335_testFailed;
  /* no debugger allowed here */
  result = IEC60335_ClassB_initWDT();

  return result;
}

/*!
 * @}
 */

/************************************** EOF *********************************/
