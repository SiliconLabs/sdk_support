/***************************************************************************//**
 * @file
 * @brief Definition of the interface between the core bootloader and the
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
#ifndef BTL_IMAGE_PARSER_H
#define BTL_IMAGE_PARSER_H

#include "api/application_properties.h"
#include "api/btl_interface_parser.h"

// The EBL parser is the only parser, so include it unconditionally
#include "ebl/btl_ebl_parser.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/***************************************************************************//**
 * @addtogroup Plugin
 * @{
 * @addtogroup ImageParser Image Parser
 * @{
 * @brief Image parser plugin
 * @details
 *   Generic image parser interface for Silicon Labs bootloader.
 ******************************************************************************/

/// Structure containing state of the image file processed
typedef struct {
  /// Image contents
  uint8_t                     contents;
  /// Parser instructions
  uint8_t                     instructions;
  /// Flag to indicate parsing has completed
  bool                        imageCompleted;
  /// Flag to indicate the image file has been validated
  bool                        imageVerified;
  /// Version number of main bootloader extracted from image file
  uint32_t                    bootloaderVersion;
  /// Information about the application
  ApplicationData_t           application;
  /// Size of the bootloader upgrade contained in the image file
  uint32_t                    bootloaderUpgradeSize;
#if defined(SEMAILBOX_PRESENT) || defined(CRYPTOACC_PRESENT)
  /// Version number of SE upgrade extracted from image file
  uint32_t                    seUpgradeVersion;
#endif
} ImageProperties_t;

/// Upgrade image contains application upgrade
#define BTL_IMAGE_CONTENT_APPLICATION       0x01U
/// Upgrade image contains bootloader upgrade
#define BTL_IMAGE_CONTENT_BOOTLOADER        0x02U
/// Upgrade image contains SE upgrade
#define BTL_IMAGE_CONTENT_SE                0x04U

/// Application upgrade should be applied from upgrade image
#define BTL_IMAGE_INSTRUCTION_APPLICATION   0x01U
/// Bootloader upgrade should be applied from upgrade image
#define BTL_IMAGE_INSTRUCTION_BOOTLOADER    0x02U
/// SE upgrade should be applied from upgrade image
#define BTL_IMAGE_INSTRUCTION_SE            0x04U

/***************************************************************************//**
 * Initialize the parser's context.
 *
 * @param context         Pointer to context for the parser implementation
 * @param decryptContext  Pointer to context for decryption of parsed file
 * @param authContext     Pointer to context for authentication of parsed file
 * @param flags           Flags for parser support
 *
 * @return @ref BOOTLOADER_OK if OK, error code otherwise.
 ******************************************************************************/
int32_t parser_init(void *context,
                    void *decryptContext,
                    void *authContext,
                    uint8_t flags);

/***************************************************************************//**
 * Parse an image file to extract the binary and some metadata.
 *
 * Pushes data into the image file parser to be parsed.
 *
 * @param context Pointer to the specific parser's context variable
 * @param imageProperties Pointer to the image file state variable
 * @param buffer Pointer to byte array containing data to parse
 * @param length Size in bytes of the data in buffer
 * @param callbacks Struct containing function pointers to be called by the
 *   parser to pass the extracted binary data back to BTL.
 *
 * @return @ref BOOTLOADER_OK if OK, error code otherwise.
 ******************************************************************************/
int32_t parser_parse(void                              *context,
                     ImageProperties_t                 *imageProperties,
                     uint8_t                           buffer[],
                     size_t                            length,
                     const BootloaderParserCallbacks_t *callbacks);

/***************************************************************************//**
 * Check whether the parser requires images to be signed.
 *
 * @return True if authenticity is required, else false
 ******************************************************************************/
bool parser_requireAuthenticity(void);

/***************************************************************************//**
 * Check whether the parser requires images to be encrypted.
 *
 * @return True if confidentiality is required, else false
 ******************************************************************************/
bool parser_requireConfidentiality(void);

/***************************************************************************//**
 * Check whether the parser requires images to be authenticated by the
 * bootloader certificate.
 *
 * @return True if certificate based authenticity is required, else false
 ******************************************************************************/
bool parser_requireCertificateAuthenticity(void);

/***************************************************************************//**
 * Check whether the parser requires images to be signed by a certificate.
 *
 * @return True if certificate signed image is required, else false
 ******************************************************************************/
bool parser_requireCertificateSignedImage(void);

/***************************************************************************//**
 * Return the start address of the application.
 *
 * @return start address of the application
 ******************************************************************************/
uint32_t parser_getApplicationAddress(void);

/***************************************************************************//**
 * Return the address of the first stage bootloader table.
 *
 * @return address of the first stage bootloader table.
 ******************************************************************************/
uint32_t parser_getFirstStageBootloaderTable(void);

/***************************************************************************//**
 * Return the address of the main bootloader table.
 *
 * @return address of the main bootloader table.
 ******************************************************************************/
uint32_t parser_getMainBootloaderTable(void);

/***************************************************************************//**
 * Return the start address of the bootloader upgrade location.
 *
 * @return start address of the bootloader upgrade location if upgrading is
 *         supported, otherwise 0.
 ******************************************************************************/
uint32_t parser_getBootloaderUpgradeAddress(void);

/***************************************************************************//**
 * Callback to tell the parser whether to accept the application upgrade
 * present in the upgrade image.
 *
 * @param[in] app Pointer to the application data structure contained in the
 *                upgrade image.
 *
 * @return True if the application is accepted, and the parser should continue.
 *         False if the application is rejected. If rejected, the parser will
 *         abort parsing the image file and return
 *         ::BOOTLOADER_ERROR_PARSER_REJECTED.
 ******************************************************************************/
bool parser_applicationUpgradeValidCallback(ApplicationData_t *app);

/** @} (end addtogroup ImageParser) */
/** @} (end addtogroup Plugin) */

#endif // BTL_IMAGE_PARSER_H
