/***************************************************************************//**
 * @file
 * @brief
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
#include "app/framework/include/af.h"
#include "hal/hal.h"
#include "serial/serial.h"
#include "store.h"

#define NUM_DBS                 2
#define MAX_ENTRY_VALUE_BYTES   255
#define BITS_PER_BYTE           8

void emAfPluginPsStoreInit(void);
void emAfPluginPsStoreDump(void);
void emAfPluginPsStorePrintTags(void);
void emAfPluginPsStoreWriteTag(void);
void emAfPluginPsStoreDeleteTag(void);

extern db_store_t *volatile db_store[];

void emAfPluginPsStoreInit(void)
{
  store_init();
}

void emAfPluginPsStoreDump(void)
{
  uint8_t currentDb;
  uint32_t i;
  uint8_t *bytePtr;

  for (currentDb = 0; currentDb < NUM_DBS; currentDb++) {
    bytePtr = (uint8_t *)db_store[currentDb];
    emberSerialPrintfLine(APP_SERIAL,
                          "\r\nPrinting a HW page for db_store[%d] starting @ "
                          "0x%4X", currentDb, bytePtr);

    for (i = 0; i < FLASH_PAGE_SIZE; i++) {
      if ((i % 16) == 0) {
        emberSerialPrintfLine(APP_SERIAL, "");
      }
      emberSerialPrintf(APP_SERIAL, "%X ", bytePtr[i]);
    }
    emberSerialPrintfLine(APP_SERIAL, "");
  }
}

void emAfPluginPsStorePrintTags(void)
{
  uint8_t index = 0;
  uint16_t key;
  uint8_t flags;
  uint8_t len;      // bytes
  uint32_t* value;  // words
  uint8_t* byteValues;
  uint32_t byte;

  errorcode_t errorCode = store_read_index(index, &key, &flags, &len, &value);
  if (bg_err_success != errorCode) {
    emberSerialPrintfLine(APP_SERIAL, "No tags currently present in PS Store");
  }

  while (bg_err_success == errorCode) {
    emberSerialPrintfLine(APP_SERIAL, "Tag:   0x%2X", key);
    emberSerialPrintfLine(APP_SERIAL, "Flags: 0x%X", flags);
    emberSerialPrintfLine(APP_SERIAL, "Len:   %d (bytes)", len);
    emberSerialPrintf(APP_SERIAL, "Data:  ");

    byteValues = (uint8_t*)value;

    for (byte = 0; byte < len; byte++) {
      if ((byte > 0) && !(byte % 16)) {
        emberSerialPrintf(APP_SERIAL, "\r\n       ");
      }
      emberSerialPrintf(APP_SERIAL, "%X ", byteValues[byte]);
    }
    emberSerialPrintfLine(APP_SERIAL, "\r\n");
    index++;
    errorCode = store_read_index(index, &key, &flags, &len, &value);
  }
}

void emAfPluginPsStoreWriteTag(void)
{
  uint16_t tag = (uint16_t)emberUnsignedCommandArgument(0);
  uint8_t flags = (uint8_t)emberUnsignedCommandArgument(1);
  uint8_t len = (uint8_t)emberUnsignedCommandArgument(2);
  uint8_t val[MAX_ENTRY_VALUE_BYTES];
  emberCopyStringArgument(3, val, MAX_ENTRY_VALUE_BYTES, false);

  errorcode_t errorCode = store_write(tag, flags, len, (void *)val);
  if (bg_err_success == errorCode) {
    emberSerialPrintfLine(APP_SERIAL, "Successfully wrote tag into PS Store");
  } else {
    emberSerialPrintfLine(APP_SERIAL,
                          "Failed to write tag into PS Store (error %d)",
                          errorCode);
  }
}

void emAfPluginPsStoreDeleteTag(void)
{
  uint16_t tag = (uint16_t)emberUnsignedCommandArgument(0);
  uint16_t mask = (uint16_t)emberUnsignedCommandArgument(1);
  errorcode_t errorCode = store_delete(tag, mask);
  if (bg_err_success == errorCode) {
    emberSerialPrintfLine(APP_SERIAL,
                          "Successfully deleted tag(s) in PS Store");
  } else {
    emberSerialPrintfLine(APP_SERIAL,
                          "Failed to delete tag(s) in PS Store (error %d)",
                          errorCode);
  }
}
