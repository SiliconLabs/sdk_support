/***************************************************************************//**
 * @file
 * @brief See @ref cbh_app for detailed documentation.
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

#ifndef __BOOTLOADER_EEPROM_H__
#define __BOOTLOADER_EEPROM_H__
#include <stdint.h>

/** @brief Definition of an EEPROM page size, in bytes.  This definition is
 *  deprecated, and should no longer be used.
 */
#define EEPROM_PAGE_SIZE      (128ul)

/** @brief Define the location of the first page in EEPROM.  This definition is
 *  deprecated, and should no longer be used.
 */
#define EEPROM_FIRST_PAGE   (0)

/** @brief Define the location of the image start in EEPROM as a function of
 * the ::EEPROM_FIRST_PAGE and ::EEPROM_PAGE_SIZE.  This definition is
 * deprecated, and should no longer be used.
 */
#define EEPROM_IMAGE_START  (EEPROM_FIRST_PAGE * EEPROM_PAGE_SIZE)

/** @brief Define EEPROM success status.
 */
#define EEPROM_SUCCESS 0U

/** @brief Define EEPROM error status.
 */
#define EEPROM_ERR 1U

/** @brief Define EEPROM chip initialization error.
 */
#define EEPROM_ERR_INVALID_CHIP 0x86U

/** @brief This structure defines a variety of information about the attached
 *          external EEPROM device.
 */
typedef struct {
  /** The version of this data structure */
  uint16_t version;

  /** A bitmask describing the capabilites of this particular external EEPROM */
  uint16_t capabilitiesMask;

  /** Maximum time it takes to erase a page. (in 1024Hz Milliseconds) */
  uint16_t pageEraseMs;

  /** Maximum time it takes to erase the entire part. (in 1024Hz Milliseconds).
      Can be changed to be in seconds using EEPROM_CAPABILITIES_PART_ERASE_SECONDS */
  uint16_t partEraseTime;

  /** The size of a single erasable page in bytes */
  uint32_t pageSize;

  /** The total size of the external EEPROM in bytes */
  uint32_t partSize;

  /** Pointer to a string describing the attached external EEPROM */
  const char * const partDescription;

  /** The number of bytes in a word for the external EEPROM **/
  uint8_t wordSizeBytes;
} HalEepromInformationType;

/** @brief Eeprom capabilities mask that indicateds that the partEraseTime
 *          field of HalEepromInformationType is in seconds instead of
 *          the usual millisecondss.
 */
#define EEPROM_CAPABILITIES_PART_ERASE_SECONDS (0x0010U)

/** @brief Call this function to get information about the external EEPROM
 *          and its capabilities.
 *
 *         The format of this call must not be altered. However, the content
 *          can be changed to work with a different device.
 *
 *  @return A pointer to a HalEepromInformationType data structure, or NULL
 *           if the driver does not support this API
 */
const HalEepromInformationType *halEepromInfo(void);

// This structure holds information about where we left off when last accessing
// the eeprom.
typedef struct {
  uint32_t address;
  uint16_t pages;
  uint16_t pageBufFinger;
  uint16_t pageBufLen;
  uint8_t pageBuf[EEPROM_PAGE_SIZE];
} EepromStateType;

#endif //__BOOTLOADER_EEPROM_H__
