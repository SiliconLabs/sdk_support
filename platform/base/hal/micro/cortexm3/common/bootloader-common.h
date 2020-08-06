/***************************************************************************//**
 * @file
 * @brief Common bootloader definitions
 * See @ref cbh_common for detailed documentation.
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
/** @addtogroup cbh_common
 * @brief Common bootloader definitions.
 *
 * See bootloader-common.h for source code.
 *@{
 */

#ifndef __BOOTLOADER_COMMON_H__
#define __BOOTLOADER_COMMON_H__

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//#define BL_DEBUG

#ifdef BL_DEBUG
#define BLDEBUG(x) (x)   // turn debug output on
#define BLDEBUG_PRINT(str) serPutStr(str)
#else
#define BLDEBUG(x)       // turn debug output off
#define BLDEBUG_PRINT(str)
#endif

#endif //DOXYGEN_SHOULD_SKIP_THIS

/** @brief Define the bootloader status type.
 */
typedef uint8_t BL_Status;

/** @name Bootloader Status Definitions
 * These are numerical definitions for the possible bootloader status codes.
 *@{
 */

/** @brief Numerical definition for a bootloader status code: Success.
 */
#define BL_SUCCESS 0U

/** @brief Numerical definition for a bootloader status code: CRC match.
 */
#define BL_CRC_MATCH 2U

/** @brief Numerical definition for a bootloader status code: Image flashed.
 */
#define BL_IMG_FLASHED 3U

/** @brief Numerical definition for a bootloader status code: serial error.
 */
#define BL_ERR 1U

/** @brief Numerical definition for a bootloader status code: Error mask.
 */
#define BL_ERR_MASK 0x40U

/** @brief Numerical definition for a bootloader status code: Failed in header
 * state.  Header expected.
 */
#define BL_ERR_HEADER_EXP 0x41U

/** @brief Numerical definition for a bootloader status code: Failed write/CRC
 * of header.
 */
#define BL_ERR_HEADER_WRITE_CRC 0x42U

/** @brief Numerical definition for a bootloader status code: Failed file CRC.
 */
#define BL_ERR_CRC 0x43U

/** @brief Numerical definition for a bootloader status code: Unknown tag.
 */
#define BL_ERR_UNKNOWN_TAG 0x44U

/** @brief Numerical definition for a bootloader status code: EBL header error.
 */
#define BL_ERR_SIG 0x45U

/** @brief Numerical definition for a bootloader status code: Trying to flash
 * odd length bytes.
 */
#define BL_ERR_ODD_LEN 0x46U

/** @brief Numerical definition for a bootloader status code: Indexed past end
 * of block buffer.
 */
#define BL_ERR_BLOCK_INDEX 0x47U

/** @brief Numerical definition for a bootloader status code: Attempt to
 * overwrite bootloader flash.
 */
#define BL_ERR_OVWR_BL 0x48U

/** @brief Numerical definition for a bootloader status code: Attempt to
 * overwrite Simulated EEPROM flash.
 */
#define BL_ERR_OVWR_SIMEE 0x49U

/** @brief Numerical definition for a bootloader status code: Flash erase
 * failed.
 */
#define BL_ERR_ERASE_FAIL 0x4AU

/** @brief Numerical definition for a bootloader status code: Flash write
 * failed.
 */
#define BL_ERR_WRITE_FAIL 0x4BU

/** @brief Numerical definition for a bootloader status code: END tag CRC
 * wrong length.
 */
#define BL_ERR_CRC_LEN 0x4CU

/** @brief Numerical definition for a bootloader status code: Received data
 * before query request/response.
 */
#define BL_ERR_NO_QUERY 0X4DU

/** @brief Numerical definition for a bootloader status code: Invalid length
 * detected.
 */
#define BL_ERR_BAD_LEN 0x4EU

/** @brief Numerical definition for a bootloader status code: Problem with
 * tagBuf detected.
 */
#define BL_ERR_TAGBUF 0x4FU

/** @brief Numerical definition for a bootloader status code: processEbl
 * deferred, call again to continue.
 */
#define BL_EBL_CONTINUE 0x50U

/** @brief Numerical definition for a bootloader status code: A known tag was
 * found in an unexpected location (eg. header tag found after data)
 */
#define BL_ERR_UNEXPECTED_TAG 0x51U

/** @brief Numerical definition for a bootloader status code: The specified
 * encryption type is unknown to this bootloader.
 */
#define BL_ERR_UNK_ENC 0x52U

/** @brief Numerical definition for a bootloader status code: No valid
 * encryption key found on the device (ie. It's all 0xFF's). Bootloader will
 * not function until this key is set.
 */
#define BL_ERR_INV_KEY 0x53U

/** @brief Numerical definition for a bootloader status code: Generic error
 * indicating that there was a problem with the encrypted file when decrypting.
 */
#define BL_ERR_ENC 0x54U

/** @brief Numerical definition for a bootloader status code: Failed IBR crc
 */
#define BL_IBR_ERR_CRC 0x55U

/** @brief Numerical definition for a bootloader status code: Incorrect IBR
 * version
 */
#define BL_IBR_ERR_VERS 0x56U

/** @brief Numerical definition for a bootloader status code: Invalid ebl
 * address in IBR
 */
#define BL_IBR_ERR_ADDR 0x57U

/** @brief Numerical definition for a bootloader status code: Incorrect IBR
 * header
 */
#define BL_IBR_ERR_HDR 0x58U

/**@} */

/** @name Bootloader State Flags
 * These are numerical flags for the possible bootloader states.  These
 * values are used in the bootloader code for making the current state
 * more verbose.
 * @note The flags do not start at 0 so that they can be output via the
 * serial port during debug and easily screened out of normal xmodem traffic
 * which depends only on ACK (0x06) and NAK (0x15).
 *@{
 */

/** @brief Bootloader state flag.
 */
#define TIMEOUT             0x16
#define FILEDONE            0x17
#define FILEABORT           0x18
#define BLOCKOK             0x19
#define QUERYFOUND          0x1A
#define START_TIMEOUT       0x1B
#define BLOCK_TIMEOUT       0x1C
#define BLOCKERR_MASK       0x20

/** @brief Bootloader state flag: Start Of Header not received.
 */
#define BLOCKERR_SOH        0x21

/** @brief Bootloader state flag: Sequence of bytes don't match.
 */
#define BLOCKERR_CHK        0x22

/** @brief Bootloader state flag: CRC High byte failure.
 */
#define BLOCKERR_CRCH       0x23

/** @brief Bootloader state flag: CRC Low byte failure.
 */
#define BLOCKERR_CRCL       0x24

/** @brief Bootloader state flag: Block received out of sequence.
 */
#define BLOCKERR_SEQUENCE   0x25

/** @brief Bootloader state flag: Partial block received.
 */
#define BLOCKERR_PARTIAL    0x26

/** @brief Bootloader state flag: Duplicate of previous block.
 */
#define BLOCKERR_DUPLICATE 0x27

/**@} */

// two possible communication modes: serial mode, or radio/ota mode.
enum {
  COMM_SERIAL  = 0x01,  // in serial mode (uart or ezsp spi)
  COMM_RADIO   = 0x02,  // in radio mode
};

#endif //__BOOTLOADER_COMMON_H__

/**@} end of group*/
