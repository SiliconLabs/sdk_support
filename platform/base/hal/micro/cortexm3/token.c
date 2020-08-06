/***************************************************************************//**
 * @file
 * @brief Token implementation for the Cortex-M3/EM3XX chip.
 * See token.h for details.
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
#include "stack/include/error.h"
#include "hal/hal.h"
#include "serial/serial.h"
#include "hal/plugin/sim-eeprom/sim-eeprom.h"

#ifndef SER232
  #define SER232 0
#endif

//prints debug data from the token access functions
#define TOKENDBG(x)
//#define TOKENDBG(x) x

bool tokensActive = false;










EmberStatus halStackInitTokens(void)
{
  #if !defined(BOOTLOADER) && !defined(EMBER_TEST)
  tokTypeMfgFibVersion tokMfg;
  EmberStatus status = EMBER_ERR_FATAL;
  tokTypeStackNvdataVersion tokStack;
  bool mfgTokenVersionValid = false;
  tokTypeMfgFibVersion validMfgTokens[] = VALID_MFG_TOKEN_VERSIONS;
  #endif
  tokensActive = true;



























  if (halInternalSimEeInit() != EMBER_SUCCESS) {
    TOKENDBG(emberSerialPrintf(SER232, "halInternalSimEeInit Attempt 1 fail\r\n"); )
    if (halInternalSimEeInit() != EMBER_SUCCESS) {
      TOKENDBG(emberSerialPrintf(SER232, "halInternalSimEeInit Attempt 2 fail\r\n"); )
      tokensActive = false;
      return EMBER_SIM_EEPROM_INIT_2_FAILED;
    }
  }

  TOKENDBG(emberSerialPrintf(SER232, "halInternalSimEeInit Successful\r\n"); )

  // TODO: remove emulator reference.
  #if !defined(BOOTLOADER) && !defined(EMBER_TEST) && !defined(EMBER_EMU_TEST)
  halCommonGetToken(&tokMfg, TOKEN_MFG_FIB_VERSION);
  halCommonGetToken(&tokStack, TOKEN_STACK_NVDATA_VERSION);

  // See if this manufacturing token version matches any known valid version
  {
    uint32_t i;
    for (i = 0; i < (sizeof(validMfgTokens) / sizeof(*validMfgTokens)); i++) {
      if (validMfgTokens[i] == tokMfg) {
        mfgTokenVersionValid = true;
      }
    }
  }

  if (!mfgTokenVersionValid || CURRENT_STACK_TOKEN_VERSION != tokStack) {
    if (!mfgTokenVersionValid && (CURRENT_STACK_TOKEN_VERSION != tokStack)) {
      status = EMBER_EEPROM_MFG_STACK_VERSION_MISMATCH;
    } else if (!mfgTokenVersionValid) {
      status = EMBER_EEPROM_MFG_VERSION_MISMATCH;
    } else if (CURRENT_STACK_TOKEN_VERSION != tokStack) {
      status = EMBER_EEPROM_STACK_VERSION_MISMATCH;
    } else {
      // MISRA requires ..else if.. to have terminating else.
    }
      #if defined(DEBUG)
    if (!mfgTokenVersionValid) {
      //Even is we're a debug image, a bad manufacturing token version
      //is a fatal error, so return the error status.
      tokensActive = false;
      return status;
    }
    if (CURRENT_STACK_TOKEN_VERSION != tokStack) {
      //Debug images with a bad stack token version should attempt to
      //fix the SimEE before continuing on.
      TOKENDBG(emberSerialPrintf(SER232, "Stack Version mismatch, reloading\r\n"); )
      halInternalSimEeRepair(true);
      if (halInternalSimEeInit() != EMBER_SUCCESS) {
        TOKENDBG(emberSerialPrintf(SER232, "halInternalSimEeInit Attempt 3 fail\r\n"); )
        tokensActive = false;
        return EMBER_SIM_EEPROM_INIT_3_FAILED;
      }
    }
      #else //  node release image
    TOKENDBG(emberSerialPrintf(SER232, "EEPROM_x_VERSION_MISMATCH (%d)\r\n", status); )
    tokensActive = false;
        #if defined(PLATFORMTEST) || defined(LEVEL_ONE_TEST)
    tokensActive = true;        //Keep tokens active for test code.
        #endif //defined(PLATFORMTEST)
    return status;
      #endif
  }
  #endif //!defined(BOOTLOADER) && !defined(EMBER_TEST) && !defined(EMBER_EMU_TEST)

  TOKENDBG(emberSerialPrintf(SER232, "TOKENS ACTIVE\r\n"); )
  return EMBER_SUCCESS;
}

void halInternalGetTokenData(void *data, uint16_t token, uint8_t index, uint8_t len)
{
  if (token < 256) {
    //the token ID is within the SimEEPROM's range, route to the SimEEPROM
    if (tokensActive) {
      halInternalSimEeGetData(data, token, index, len);
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "getIdxToken supressed.\r\n"); )
    }
  } else {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    halInternalGetMfgTokenData(data, token, index, len);
    #endif //EMBER_TEST
  }
}

void halInternalGetIdxTokenPtrOrData(void *ptr, uint16_t ID, uint8_t index, uint8_t len)
{
  if (ID < 256) {
    //the ID is within the SimEEPROM's range, route to the SimEEPROM
    if (tokensActive) {
      halInternalSimEeGetPtr(ptr, ID, index, len);
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "getIdxToken supressed.\r\n"); )
    }
  } else {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    uint32_t *ptrOut = (uint32_t *)ptr;
    uint32_t realAddress;

    //0x7F is a non-indexed token.  Remap to 0 for the address calculation
    index = (index == 0x7F) ? 0 : index;

    realAddress = (FIB_BOTTOM | ID) + (len * index);

    *ptrOut = realAddress;
    #endif //EMBER_TEST
  }
}

bool simEeSetDataActiveSemaphore = false;
void halInternalSetTokenData(uint16_t token, uint8_t index, void *data, uint8_t len)
{
  if (token < 256) {
    //the token ID is within the SimEEPROM's range, route to the SimEEPROM
    if (tokensActive) {
      //You cannot interrupt SetData with another SetData!
      assert(!simEeSetDataActiveSemaphore);
      simEeSetDataActiveSemaphore = true;
      halInternalSimEeSetData(token, data, index, len);
      simEeSetDataActiveSemaphore = false;
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "setIdxToken supressed.\r\n"); )
    }
  } else {
    //The Information Blocks can only be written by an external tool!
    //Something is making a set token call on a manufacturing token, and that
    //is not allowed!
    assert(0);
  }
}

void halInternalIncrementCounterToken(uint8_t token)
{
  if (tokensActive) {
    halInternalSimEeIncrementCounter(token);
  } else {
    TOKENDBG(emberSerialPrintf(SER232, "IncrementCounter supressed.\r\n"); )
  }
}

#ifndef EMBER_TEST

// The following interfaces are admittedly code space hogs but serve
// as glue interfaces to link creator codes to tokens for test code.

uint16_t getTokenAddress(uint16_t creator)
{
  uint16_t tokenAddress;

  #define DEFINETOKENS
  switch (creator) {
    #define TOKEN_MFG TOKEN_DEF
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case creator:                                                          \
    tokenAddress = TOKEN_##name;                                         \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "hal/micro/cortexm3/token-manufacturing.h"
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_MFG
    #undef TOKEN_DEF
    default:
      tokenAddress = INVALID_EE_ADDRESS;
      break;
  }
  #undef DEFINETOKENS
  return tokenAddress;
}

uint8_t getTokenSize(uint16_t creator)
{
  uint8_t tokenSize;

  #define DEFINETOKENS
  switch (creator) {
    #define TOKEN_MFG TOKEN_DEF
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case creator:                                                          \
    tokenSize = sizeof(type);                                            \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "hal/micro/cortexm3/token-manufacturing.h"
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_MFG
    #undef TOKEN_DEF
    default:
      tokenSize = 0U;
      break;
  }
  #undef DEFINETOKENS
  return tokenSize;
}

uint8_t getTokenArraySize(uint16_t creator)
{
  uint8_t tokenArraySize;

  #define DEFINETOKENS
  switch (creator) {
    #define TOKEN_MFG TOKEN_DEF
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case creator:                                                          \
    tokenArraySize = arraysize;                                          \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "hal/micro/cortexm3/token-manufacturing.h"
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_MFG
    #undef TOKEN_DEF
    default:
      tokenArraySize = 0U;
      break;
  }
  #undef DEFINETOKENS
  return tokenArraySize;
}

#endif //EMBER_TEST
