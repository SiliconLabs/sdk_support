/***************************************************************************//**
 * @file
 * @brief Token implementation.
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

#ifndef SER232
  #define SER232 1
#endif

//prints debug data from the token access functions
#define TOKENDBG(x)
//#define TOKENDBG(x) x

#ifdef USE_NVM3
#include "hal/plugin/nvm3/nvm3-token.h"

#if defined(NVM3_EXTFLASH)
bool emRadioGetRandomNumbers(uint16_t *rn, uint8_t count);
#define NVM3_CRYPTO_KEY_BYTES 16

#if !defined(NVM3_TEST)
#include "em_wdog.h"
#define NVM3_CRYPTO_KEY_ADDRESS (LOCKBITS_BASE + (TOKEN_MFG_NVM3_CRYPTO_KEY & 0x0FFFU));
#endif // NVM3_TEST

// Function passed ot NVM3 to provide random numbers
static uint32_t getRandomNumber(void)
{
  uint32_t res;

  emRadioGetRandomNumbers((uint16_t *) &res, sizeof(res) / sizeof(uint16_t));

  return res;
}

#endif // NVM3_EXFLASH

// Global variable used by library code to know number of tokens
#ifdef SIMEE2_TO_NVM3_UPGRADE
uint8_t tokenCount = TOKEN_COUNT;
#endif

EmberStatus halSimEeToNvm3Upgrade(void);

static bool tokensActive = false;

EmberStatus halStackInitTokens(void)
{
  uint8_t i;
  uint8_t arrayIndex;
  size_t size;
  uint32_t objectType;
  Ecode_t ecode, status;
  EmberStatus ret;
  nvm3_HalInfo_t halInfo;

#if defined (NVM3_EXTFLASH)
  // Disable watchdog and reconfigure it to a longer timout period to allow
  // nvm3_open to finish as this takes a long time with external flash
#if !defined (NVM3_TEST) && defined(HAL_WDOG_ENABLE)
  halInternalDisableWatchDog(MICRO_DISABLE_WATCH_DOG_KEY);
  WDOG_Init_TypeDef wdogInit = WDOG_INIT_DEFAULT;
  wdogInit.enable = true;
  wdogInit.perSel = wdogPeriod_128k;
  wdogInit.warnSel = wdogWarnTime75pct;

  WDOGn_Init(DEFAULT_WDOG, &wdogInit);
#endif

  bool cryptoKeyExists = false;
  uint16_t nvm3CryptoKey[NVM3_CRYPTO_KEY_BYTES / 2];

  // Read existing crypto key from manufacturing token
  halInternalGetMfgTokenData((uint8_t *) nvm3CryptoKey,
                             TOKEN_MFG_NVM3_CRYPTO_KEY,
                             0,
                             NVM3_CRYPTO_KEY_BYTES);

  // If the existing crypto key is all FFs we assume it
  // has not been written yet
  for (i = 0; i < NVM3_CRYPTO_KEY_BYTES / 2; i++) {
    cryptoKeyExists |= (nvm3CryptoKey[i] != 0xFFFFU);
  }

  // If no NVM3 crypto key exists we generate a new one and
  // write it as a manufacturing token
  if (!cryptoKeyExists) {
    emRadioGetRandomNumbers(nvm3CryptoKey, NVM3_CRYPTO_KEY_BYTES / sizeof(nvm3CryptoKey[0]));
    halInternalSetMfgTokenData(TOKEN_MFG_NVM3_CRYPTO_KEY,
                               (uint8_t *) nvm3CryptoKey,
                               NVM3_CRYPTO_KEY_BYTES);
  }

  nvm3_defaultInit->getRndNumber = getRandomNumber;
  nvm3_defaultInit->cryptoKey = (uint8_t *) NVM3_CRYPTO_KEY_ADDRESS;

#else // defined (NVM3_EXTFLASH)
  // Updrade is only supported when using NVM3 in internal flash
  if (halSimEeToNvm3Upgrade()) {
    return (EmberStatus) EMBER_NVM3_ERR_UPGRADE;
  }
#endif

  ecode = nvm3_open(nvm3_defaultHandle, nvm3_defaultInit);
  TOKENDBG(emberSerialPrintf(SER232,
                             "halStackInitTokens nvm3_open status: 0x%x\r\n",
                             ecode); )
  if (ecode != ECODE_NVM3_OK) {
    nvm3_halOpen(nvm3_defaultInit->halHandle, nvm3_defaultInit->nvmAdr, nvm3_defaultInit->nvmSize);
    nvm3_halGetInfo(nvm3_defaultInit->halHandle, &halInfo);
    nvm3_halNvmAccess(nvm3_defaultInit->halHandle, NVM3_HAL_NVM_ACCESS_RDWR);
    for (i = 0; i < nvm3_defaultInit->nvmSize / halInfo.pageSize; i++) {
      ecode = nvm3_halPageErase(nvm3_defaultInit->halHandle,
                                (nvm3_HalPtr_t)((size_t) nvm3_defaultInit->nvmAdr + i * halInfo.pageSize));
      TOKENDBG(emberSerialPrintf(SER232,
                                 "nvm3_halPageErase %d status: 0x%x\r\n",
                                 i,
                                 ecode); )
    }
    nvm3_halNvmAccess(nvm3_defaultInit->halHandle, NVM3_HAL_NVM_ACCESS_NONE);
    nvm3_halClose(nvm3_defaultInit->halHandle);

    ecode = nvm3_open(nvm3_defaultHandle, nvm3_defaultInit);
    TOKENDBG(emberSerialPrintf(SER232,
                               "halStackInitTokens second nvm3_open status: 0x%x\r\n",
                               ecode); )
  }

  for (i = 0; i < (uint8_t) TOKEN_COUNT; i++) {
    if (ecode == ECODE_NVM3_OK) {
      TOKENDBG(emberSerialPrintf(SER232,
                                 "Token[%d]: Key=0x%4x Array size =%d \r\n",
                                 i,
                                 tokenNvm3Keys[i],
                                 tokenArraySize[i]); )

      if (tokenIsCnt[i]) { // Counter token
        status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                    tokenNvm3Keys[i],
                                    &objectType,
                                    &size);

        // Create NVM3 objects for tokens if they don't exist already
        // or if type or size doesn't match
        if ((status == ECODE_NVM3_ERR_KEY_NOT_FOUND)
            || ((status == ECODE_NVM3_OK)
                && (objectType != NVM3_OBJECTTYPE_COUNTER))) {
          TOKENDBG(emberSerialPrintf(SER232, "Creating counter token from default value\r\n"); )

          // If object type is wrong we need to delete it before creating the
          // new one with the correct type.
          if (status == ECODE_NVM3_OK) {
            (void) nvm3_deleteObject(nvm3_defaultHandle, tokenNvm3Keys[i]);
            TOKENDBG(emberSerialPrintf(SER232, "Deleting object of wrong type\r\n"); )
          }

          ecode = nvm3_writeCounter(nvm3_defaultHandle,
                                    tokenNvm3Keys[i],
                                    *(const uint32_t *) tokenDefaults[i]);
          TOKENDBG(emberSerialPrintf(SER232,
                                     "halStackInitTokens nvm3_writeCounter value: 0x%4x status: 0x%x\r\n",
                                     *(uint32_t *) tokenDefaults[i],
                                     ecode); )
        }
      } else { // Basic or indexed token
        // For indexed tokens we need to create every index in the indexed
        // token key domain if it doesn't exist already or if size or type doesn't match
        for (arrayIndex = 0; arrayIndex < tokenArraySize[i]; arrayIndex++) {
          status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                      tokenNvm3Keys[i] + arrayIndex,
                                      &objectType,
                                      &size);

          if ((status == ECODE_NVM3_ERR_KEY_NOT_FOUND)
              || ((status == ECODE_NVM3_OK)
                  && ((objectType != NVM3_OBJECTTYPE_DATA)
                      || (size != tokenSize[i])))) {
            TOKENDBG(emberSerialPrintf(SER232, "Creating basic/index token (index: %x) from default value\r\n", arrayIndex); )

            // If the object type is wrong we need to delete it before creating the
            // new one with the correct type.
            // Wrong size will be corrected by the data write itself
            if (((status == ECODE_NVM3_OK)
                 && ((objectType != NVM3_OBJECTTYPE_DATA)))) {
              (void) nvm3_deleteObject(nvm3_defaultHandle, tokenNvm3Keys[i] + arrayIndex);
              TOKENDBG(emberSerialPrintf(SER232, "Deleting object of wrong type\r\n"); )
            }

            ecode = nvm3_writeData(nvm3_defaultHandle,
                                   tokenNvm3Keys[i] + arrayIndex,
                                   (const void *) tokenDefaults[i],
                                   tokenSize[i]);
            TOKENDBG(emberSerialPrintf(SER232,
                                       "halStackInitTokens nvm3_writeData length: %d  status: 0x%x\r\n",
                                       tokenSize[i],
                                       ecode); )
            if (ecode != ECODE_NVM3_OK) {
              break;
            }
          }
        }

        if (tokenIsIdx[i]) {
          // We need to delete objects for any indexes that are no longer used.
          for (arrayIndex = tokenArraySize[i]; arrayIndex < 0x7FU; arrayIndex++) {
            status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                        tokenNvm3Keys[i] + arrayIndex,
                                        &objectType,
                                        &size);

            if (status == ECODE_NVM3_ERR_KEY_NOT_FOUND) {
              // If we don't find an object we assume there are no objects at higher indexes
              // and stop looking.
              break;
            } else {
              ecode = nvm3_deleteObject(nvm3_defaultHandle, tokenNvm3Keys[i] + arrayIndex);
              TOKENDBG(emberSerialPrintf(SER232,
                                         "halStackInitTokens Erased unused index %d of token with key 0x%4x\r\n",
                                         arrayIndex,
                                         tokenNvm3Keys[i]); )
              if (ecode != ECODE_NVM3_OK) {
                break;
              }
            }
          }
        }
      }
    }
  }

  tokensActive = ecode == ECODE_NVM3_OK;

// Map NVM3 error codes to EmberStatus codes
  switch (ecode) {
    case ECODE_NVM3_ERR_OPENED_WITH_OTHER_PARAMETERS:
      ret = (EmberStatus) EMBER_NVM3_ERR_OPENED_WITH_OTHER_PARAMETERS;
      break;
    case ECODE_NVM3_ERR_ALIGNMENT_INVALID:
      ret = (EmberStatus) EMBER_NVM3_ERR_ALIGNMENT_INVALID;
      break;
    case ECODE_NVM3_ERR_SIZE_TOO_SMALL:
      ret = (EmberStatus) EMBER_NVM3_ERR_SIZE_TOO_SMALL;
      break;
    case ECODE_NVM3_ERR_PAGE_SIZE_NOT_SUPPORTED:
      ret = (EmberStatus) EMBER_NVM3_ERR_PAGE_SIZE_NOT_SUPPORTED;
      break;
    case ECODE_NVM3_OK:
      ret = (EmberStatus) EMBER_SUCCESS;
      break;
    default:
      ret = (EmberStatus) EMBER_NVM3_ERR_TOKEN_INIT;
      break;
  }

  // If the NVM3 cache overflows it is too small to index all live and deleted NVM3 objects
  assert(!nvm3_defaultHandle->cache.overflow);

  // Disable watchdog and reconfigure it to restore original watchdog period.
#if defined (NVM3_EXTFLASH) && defined(HAL_WDOG_ENABLE)
  halInternalDisableWatchDog(MICRO_DISABLE_WATCH_DOG_KEY);
  halInternalEnableWatchDog();
#endif
  return ret;
}

void halInternalGetTokenData(void *data, uint16_t token, uint8_t index, uint8_t len)
{
  uint8_t offset;
  Ecode_t ecode = ECODE_NVM3_OK;

  if (token < TOKEN_COUNT) {
    if (tokensActive) {
      TOKENDBG(emberSerialPrintf(SER232,
                                 "Get token[%d]: Key=0x%4x Index= 0x%d\r\n",
                                 token,
                                 tokenNvm3Keys[token],
                                 index); )
      if (tokenIsCnt[token]) {
        ecode = nvm3_readCounter(nvm3_defaultHandle,
                                 tokenNvm3Keys[token],
                                 data);
        TOKENDBG(emberSerialPrintf(SER232,
                                   "halInternalGetTokenData nvm3_readCounter value: 0x%4x status: 0x%x\r\n",
                                   *(uint32_t *) data,
                                   ecode); )
      } else { // Basic/indexed token
        offset = index == 0x7FU ? 0U : index;
        ecode = nvm3_readData(nvm3_defaultHandle,
                              tokenNvm3Keys[token] + offset,
                              data,
                              len);
        TOKENDBG(emberSerialPrintf(SER232,
                                   "halInternalGetTokenData nvm3_readData length: %d status: 0x%x\r\n",
                                   len,
                                   ecode); )
      }
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "halInternalGetTokenData supressed\r\n"); )
    }
  } else if (token >= 256U) {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    halInternalGetMfgTokenData(data, token, index, len);
    #endif // EMBER_TEST
  } else {
    assert(false);
  }

  if (ecode != ECODE_NVM3_OK) {
    halNvm3Callback(ecode);
  }
}

void halInternalSetTokenData(uint16_t token, uint8_t index, void *data, uint8_t len)
{
  uint8_t offset;
  Ecode_t ecode = ECODE_NVM3_OK;

  if (token < TOKEN_COUNT) {
    if (tokensActive) {
      TOKENDBG(emberSerialPrintf(SER232,
                                 "Set token[%d]: Key=0x%4x Index= 0x%d\r\n",
                                 token,
                                 tokenNvm3Keys[token],
                                 index); )

      if (tokenIsCnt[token]) {
        ecode = nvm3_writeCounter(nvm3_defaultHandle,
                                  tokenNvm3Keys[token],
                                  *(uint32_t *) data);
        TOKENDBG(emberSerialPrintf(SER232,
                                   "halInternalSetTokenData nvm3_writeCounter value: 0x%4x status: 0x%x\r\n",
                                   *(uint32_t *) data,
                                   ecode); )
      } else { //Basic/indexed token
        offset = index == 0x7FU ? 0U : index;
        ecode = nvm3_writeData(nvm3_defaultHandle,
                               tokenNvm3Keys[token] + offset,
                               data,
                               len);
        TOKENDBG(emberSerialPrintf(SER232,
                                   "halInternalSetTokenData nvm3_writeData length: %d status: 0x%x\r\n",
                                   len,
                                   ecode); )
      }
    } else {
      TOKENDBG(emberSerialPrintf(SER232,
                                 "halInternalSetTokenData supressed\r\n"); )
    }
  } else if (token >= 256U) {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    halInternalSetMfgTokenData(token, data, len);
    #endif //EMBER_TEST
  } else {
    assert(false);
  }
  if (ecode != ECODE_NVM3_OK) {
    halNvm3Callback(ecode);
  }
}

void halInternalIncrementCounterToken(uint8_t token)
{
  Ecode_t ecode = ECODE_NVM3_OK;
  if (tokensActive) {
    TOKENDBG(emberSerialPrintf(SER232,
                               "Increment token[%d]: Key=0x%4x\r\n",
                               token,
                               tokenNvm3Keys[token]); )
    ecode = nvm3_incrementCounter(nvm3_defaultHandle, tokenNvm3Keys[token], NULL);
    TOKENDBG(emberSerialPrintf(SER232,
                               "halInternalIncrementCounterToken nvm3_incrementCounter status: 0x%x\r\n",
                               ecode); )
  } else {
    TOKENDBG(emberSerialPrintf(SER232,
                               "halInternalIncrementCounterToken supressed\r\n"); )
  }
  if (ecode != ECODE_NVM3_OK) {
    halNvm3Callback(ecode);
  }
}

#else //USE_NVM3

#include "hal/plugin/sim-eeprom/sim-eeprom.h"

bool tokensActive = false;

EmberStatus halStackInitTokens(void)
{
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

  #if !defined(BOOTLOADER) && !defined(EMBER_TEST)
  {
    tokTypeStackNvdataVersion tokStack;
    halCommonGetToken(&tokStack, TOKEN_STACK_NVDATA_VERSION);

    if (CURRENT_STACK_TOKEN_VERSION != tokStack) {
      #if defined(DEBUG)
      //Debug images with a bad stack token version should attempt to
      //fix the SimEE before continuing on.
      TOKENDBG(emberSerialPrintf(SER232, "Stack Version mismatch, reloading\r\n"); )
      halInternalSimEeRepair(true);
      if (halInternalSimEeInit() != EMBER_SUCCESS) {
        TOKENDBG(emberSerialPrintf(SER232, "halInternalSimEeInit Attempt 3 fail\r\n"); )
        tokensActive = false;
        return EMBER_SIM_EEPROM_INIT_3_FAILED;
      }
      #else //  node release image
      TOKENDBG(emberSerialPrintf(SER232, "EEPROM_x_VERSION_MISMATCH (%d)\r\n",
                                 EMBER_EEPROM_STACK_VERSION_MISMATCH); )
      tokensActive = false;
        #if defined(PLATFORMTEST) || defined(LEVEL_ONE_TEST)
      tokensActive = true;      //Keep tokens active for test code.
        #endif //defined(PLATFORMTEST)
      return EMBER_EEPROM_STACK_VERSION_MISMATCH;
      #endif
    }
  }
  #endif //!defined(BOOTLOADER) && !defined(EMBER_TEST)

  TOKENDBG(emberSerialPrintf(SER232, "TOKENS ACTIVE\r\n"); )
  return EMBER_SUCCESS;
}

void halInternalGetTokenData(void *data, uint16_t token, uint8_t index, uint8_t len)
{
  if (token < TOKEN_COUNT) {
    //the token ID is within the SimEEPROM's range, route to the SimEEPROM
    if (tokensActive) {
      halInternalSimEeGetData(data, token, index, len);
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "getIdxToken supressed.\r\n"); )
    }
  } else if (token >= 256U) {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    halInternalGetMfgTokenData(data, token, index, len);
    #endif //EMBER_TEST
  } else {
    assert(false);
  }
}

bool simEeSetDataActiveSemaphore = false;
void halInternalSetTokenData(uint16_t token, uint8_t index, void *data, uint8_t len)
{
  if (token < TOKEN_COUNT) {
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
  } else if (token >= 256) {
    //Something is making a set token call on a manufacturing token,
    //on efm32 we permit this if the token is otherwise unprogrammed
    halInternalSetMfgTokenData(token, data, len);
  } else {
    assert(false);
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

#endif //USE_NVM3

void halInternalGetIdxTokenPtrOrData(void *ptr, uint16_t token, uint8_t index, uint8_t len)
{
  if (token < TOKEN_COUNT) {
    // The token is within the SimEEPROM/NVM3's range, route to the SimEEPROM/NVM3
    if (tokensActive) {
#ifdef USE_NVM3
      // NVM3 doesn't support pointers to data in the NVM storage so we instead copy the data
      // to the location provided through the pointer.
      halInternalGetTokenData(*(void **) ptr, token, index, len);
#else
      halInternalSimEeGetPtr(ptr, token, index, len);
#endif
    } else {
      TOKENDBG(emberSerialPrintf(SER232, "getIdxToken supressed.\r\n"); )
    }
  } else if (token >= 256) {
    #ifdef EMBER_TEST
    assert(false);
    #else //EMBER_TEST
    uint32_t *ptrOut = (uint32_t *)ptr;
    uint32_t realAddress = 0;

    //0x7F is a non-indexed token.  Remap to 0 for the address calculation
    index = (index == 0x7F) ? 0 : index;

    if ((token & 0xF000) == (USERDATA_TOKENS & 0xF000)) {
      realAddress = ((USERDATA_BASE | (token & 0x0FFF)) + (len * index));
    } else if ((token & 0xF000) == (LOCKBITSDATA_TOKENS & 0xF000)) {
      realAddress = ((LOCKBITS_BASE | (token & 0x0FFF)) + (len * index));
    } else {
      //This function must only ever be called from token code that passes
      //a proper "token" parameter.  A valid 16bit token must pass the
      //above check to find the 32bit realAddress.
      assert(0);
    }

    *ptrOut = realAddress;
    #endif //EMBER_TEST
  } else {
    assert(false);
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
    #include "hal/micro/cortexm3/efm32/token-manufacturing.h"
    // Creator codes are only guaranteed to be defined for tokens when SimEE plugins are included
#if !defined (USE_NVM3) || defined (SIMEE2_TO_NVM3_UPGRADE)
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
#endif
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
    #include "hal/micro/cortexm3/efm32/token-manufacturing.h"
    // Creator codes are only guaranteed to be defined for tokens when SimEE plugins are included
#if !defined (USE_NVM3) || defined (SIMEE2_TO_NVM3_UPGRADE)
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
#endif
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
    #include "hal/micro/cortexm3/efm32/token-manufacturing.h"
    // Creator codes are only guaranteed to be defined for tokens when SimEE plugins are included
#if !defined (USE_NVM3) || defined (SIMEE2_TO_NVM3_UPGRADE)
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
#endif
    #undef TOKEN_MFG
    #undef TOKEN_DEF
    default:
      tokenArraySize = 0U;
      break;
  }
  #undef DEFINETOKENS
  return tokenArraySize;
}

#if defined (USE_NVM3)
uint16_t getNvm3TokenAddress(uint32_t nvm3Key)
{
  uint16_t tokenAddress;

  #define DEFINETOKENS
  switch (nvm3Key) {
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case NVM3KEY_##name:                                                   \
    tokenAddress = TOKEN_##name;                                         \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_DEF
    default:
      tokenAddress = INVALID_EE_ADDRESS;
      break;
  }
  #undef DEFINETOKENS
  return tokenAddress;
}

uint8_t getNvm3TokenSize(uint32_t nvm3Key)
{
  uint8_t tokenSize;

  #define DEFINETOKENS
  switch (nvm3Key) {
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case NVM3KEY_##name:                                                   \
    tokenSize = sizeof(type);                                            \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_DEF
    default:
      tokenSize = 0U;
      break;
  }
  #undef DEFINETOKENS
  return tokenSize;
}

uint8_t getNvm3TokenArraySize(uint32_t nvm3Key)
{
  uint8_t tokenArraySize;

  #define DEFINETOKENS
  switch (nvm3Key) {
    #define TOKEN_DEF(name, creator, iscnt, isidx, type, arraysize, ...) \
  case NVM3KEY_##name:                                                   \
    tokenArraySize = arraysize;                                          \
    break;
    // Multiple inclusion of unguarded token-related header files is by design; suppress violation.
    //cstat !MISRAC2012-Dir-4.10
    #include "stack/config/token-stack.h"
    #undef TOKEN_DEF
    default:
      tokenArraySize = 0U;
      break;
  }
  #undef DEFINETOKENS
  return tokenArraySize;
}
#endif //defined (USE_NVM3)

#endif //EMBER_TEST
