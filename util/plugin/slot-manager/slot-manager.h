/**************************************************************************//**
 * Copyright 2017 Silicon Laboratories, Inc.
 *
 *****************************************************************************/

#ifndef __SLOT_MANAGER_H__
#define __SLOT_MANAGER_H__

#include "api/btl_interface.h"
#include "api/btl_interface_storage.h"

#if defined (EMBER_STACK_ZIGBEE)
#include "app/framework/include/af.h"
#define slotManagerPrint(...)   emberAfAppPrint(__VA_ARGS__)
#define slotManagerPrintln(...) emberAfAppPrintln(__VA_ARGS__)
#define pokeStackOrWatchDog()   halInternalResetWatchDog()

#elif defined (EMBER_STACK_BLE)
#define slotManagerPrint(...)   printf(__VA_ARGS__)
#define slotManagerPrintln(...) do { printf(__VA_ARGS__); printf("\n"); \
} while (0)
#define pokeStackOrWatchDog()   (void)0

#else
#error "Slot Manager plugin: Stack is either not defined or not supported!"
#endif // EMBER_STACK_ZIGBEE

// Return values
#define   SLOT_MANAGER_SUCCESS                    0
#define   SLOT_MANAGER_ERROR                      1
#define   SLOT_MANAGER_INVALID_CALL               2
#define   SLOT_MANAGER_BAD_ARG                    3
#define   SLOT_MANAGER_CONTINUE                   4

#define   SLOT_MANAGER_INVALID_SLOT               (uint32_t)-1
#define   SLOT_MANAGER_VERIFICATION_CONTEXT_SIZE  384

// Defines
typedef struct {
  BootloaderStorageSlot_t slotStorageInfo;
  ApplicationData_t       slotAppInfo;
} SlotManagerSlotInfo_t;

// Prototypes
void      emberAfPluginSlotManagerInitCallback(void);

/***************************************************************************//**
 * Print information about the external flash, if applicable.
 ******************************************************************************/
void      emberAfPluginSlotManagerPrintExternalFlashInfo(void);

/***************************************************************************//**
 * Read data from the external flash.
 *
 * @param[in] address The address to begin reading from
 * @param[out] data The buffer to fill in
 * @param[in] length The number of bytes to read
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerReadExtFlash(uint32_t address,
                                               uint8_t  *data,
                                               uint8_t  length);

/***************************************************************************//**
 * Verify image in slot and bootload it if valid.
 *
 * @param[in] slotId The slot to verify and potentially bootload
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 *
 * @note This function is for demonstrative purposes only. It holds off other
 *       tasks until image validation is complete. Users should call
 *       emberAfPluginSlotManagerImageIsValidReset and
 *       emberAfPluginSlotManagerImageIsValid instead of this function in
 *       production code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerVerifyAndBootloadSlot(uint32_t slotId);

/***************************************************************************//**
 * Retrieve address, length, and image information about a slot.
 *
 * @param[in] slotId The slot to retrieve the information for
 * @param[out] slotInfo The SlotManagerInfo_t struct to fill in
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerGetSlotInfo(uint32_t              slotId,
                                              SlotManagerSlotInfo_t *slotInfo);

/***************************************************************************//**
 * Write data to slot.
 *
 * @param[in] slotId The slot ID to write to
 * @param[in] offset The address offset within the slot to write to
 * @param[in] buffer The data to write
 * @param[in] length The number of bytes to write
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerWriteToSlot(uint32_t slotId,
                                              uint32_t offset,
                                              uint8_t  *buffer,
                                              size_t   length);

/***************************************************************************//**
 * Erase slot contents.
 *
 * @param[in] slotId The slot ID to erase
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 *
 * @note This function is for demonstrative purposes only. It holds off other
 *       tasks until slot erasure is complete. It should not be used in
 *       production code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerEraseSlot(uint32_t slotId);

/***************************************************************************//**
 * Fetch the number of slots in storage.
 *
 * @param[out] numSlots A buffer to fill in with the number of slots in storage
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerGetNumberOfSlots(uint32_t *numSlots);

/***************************************************************************//**
 * Begin image validation in slot.
 *
 * @param[in] slotId The slot ID to validate the image
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 *
 * @note Upon calling this function, if SLOT_MANAGER_SUCCESS is returned, users
 *       should continuously call emberAfPluginSlotManagerImageIsValid until
 *       either SLOT_MANAGER_SUCCESS or a Slot Manager error code is returned.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerImageIsValidReset(uint32_t slotId);

/***************************************************************************//**
 * Continue image validation in a slot.
 *
 * @return SLOT_MANAGER_SUCCESS if successful, SLOT_MANAGER_CONTINUE if image is
 *         still being validated, else a Slot Manager error code.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerImageIsValid();

/***************************************************************************//**
 * Boot the image in a slot.
 *
 * @param[in] slotId The slot ID to boot
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 *
 * @note Though programmatically this function returns a good status code
 *       if successful, this function will actually not return control to the
 *       caller if so. The bootloader code will begin to boot the image.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerBootSlot(uint32_t slotId);

/***************************************************************************//**
 * Fetch the metadata tags in a GBL image in a slot.
 *
 * @param[in] slotId The slot ID to fetch the metadata tags
 * @param[in] callbackFunction A callback to call when a metadata tag is found
 *
 * @return SLOT_MANAGER_SUCCESS if successful, else a Slot Manager error code.
 *
 * @note One metadata tag can cause callbackFunction to be called multiple times
 *       if its data length is longer than a code block used to inspect the
 *       image. The callbackFunction prototype offers an address variable to
 *       indicate that the same metadata tag is being processed.
 ******************************************************************************/
uint8_t   emberAfPluginSlotManagerGetMetadataTagsFromGbl(
  uint32_t slotId,
  BootloaderParserCallback_t callbackFunction);

#endif  // __SLOT_MANAGER_H__
