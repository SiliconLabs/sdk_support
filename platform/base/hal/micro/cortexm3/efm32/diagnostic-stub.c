/***************************************************************************//**
 * @file
 * @brief stubs for HAL diagnostic functions.
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

void halPrintCrashData(uint8_t port)
{
}

void halPrintCrashDetails(uint8_t port)
{
}

void halPrintCrashSummary(uint8_t port)
{
}

void halStartPCDiagnostics(void)
{
}

void halStopPCDiagnostics(void)
{
}

uint16_t halGetPCDiagnostics(void)
{
  return 0;
}

void halInternalAssertFailed(PGM_P filename, int linenumber)
{
}

uint16_t halInternalCrashHandler(void)
{
  return 0;
}

// Stub for the EnergyMicro assert handler
void assertEFM(const char *file, int line)
{
}
