/***************************************************************************//**
 * @file
 * @brief Functions to use the parser plugin to parse an image
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
#ifndef BTL_PARSE_H
#define BTL_PARSE_H

#include "plugin/parser/btl_image_parser.h"
#include "plugin/security/btl_security_types.h"

/// Context used by bootloader image parser to store parser state
struct BootloaderParserContext {
  /// Properties of the image being parsed
  ImageProperties_t     imageProperties;
  /// Context information for the image parser
  ParserContext_t       parserContext;
  /// Decryption context information for the image parser
  DecryptContext_t      decryptContext;
  /// Authentication context information for the image parser
  AuthContext_t         authContext;
  /// Slot ID to try and parse an image from
  uint32_t              slotId;
  /// Size of storage slot
  uint32_t              slotSize;
  /// Offset into storage slot
  uint32_t              slotOffset;
  /// Error code returned by the image parser
  int32_t               errorCode;
};

/***************************************************************************//**
 * Initialize the image parser.
 *
 * @param[in] context     Pointer to the parser context struct
 * @param[in] contextSize Size of the context struct
 *
 * @return BOOTLOADER_OK if success, BOOTLOADER_ERROR_PARSE_CONTEXT if context
 *         struct is too small.
 ******************************************************************************/
int32_t core_initParser(BootloaderParserContext_t *context,
                        size_t                    contextSize);

/***************************************************************************//**
 * Parse a buffer.
 * @param     context     Pointer to the parser context struct
 * @param[in] callbacks   Pointer to the struct of callbacks for different types
 *                        of data
 * @param[in] data        Data to be parsed
 * @param[in] numBytes    Size of the data buffer
 *
 * @return BOOTLOADER_ERROR_PARSE_CONTINUE if the chunk was parsed correctly,
 *         and a new chunk is expected. BOOTLOADER_ERROR_PARSER_* if something
 *         went wrong during parsing. BOOTLOADER_ERROR_PARSE_SUCCESS if the
 *         entire file was successfully parsed.
 ******************************************************************************/
int32_t core_parseBuffer(BootloaderParserContext_t         *context,
                         const BootloaderParserCallbacks_t *callbacks,
                         uint8_t                           data[],
                         size_t                            numBytes);

#endif // BTL_PARSE_H
