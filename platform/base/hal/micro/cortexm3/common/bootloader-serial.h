/***************************************************************************//**
 * @file
 * @brief Common bootloader serial definitions.
 * See @ref cbhc_serial for detailed documentation.
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
/** @addtogroup cbhc_serial
 * @brief Common bootloader serial definitions.
 *
 * See bootloader-serial.h for source code.
 *@{
 */

#ifndef __BOOTLOADER_SERIAL_H__
#define __BOOTLOADER_SERIAL_H__

#ifndef MSD_BOOTLOADER

/** @brief Initialize serial port.
 */
void serInit(void);

/** @brief Flush the transmiter.
 */
void serPutFlush(void);

/** @brief Transmit a character.
 * @param ch A character.
 */
void serPutChar(uint8_t ch);

/** @brief  Transmit a string.
 * @param str A string.
 */
void serPutStr(const char *str);

/** @brief Transmit a buffer.
 * @param buf A buffer.
 * @param size Length of buffer.
 */
void serPutBuf(const uint8_t buf[], uint8_t size);

/** @brief Transmit a 16bit value in decimal.
 * @param val The data to print.
 */
void serPutDecimal(uint16_t val);

/** @brief Transmit a byte as hex.
 * @param byte A byte.
 */
void serPutHex(uint8_t byte);

/** @brief  Transmit a 16bit integer as hex.
 * @param word A 16bit integer.
 */
void serPutHexInt(uint16_t word);

/** @brief Determine if a character is available.
 * @return true if a character is available, false otherwise.
 */
bool serCharAvailable(void);

/** @brief Get a character if available, otherwise return an error.
 * @param ch Pointer to a location where the received byte will be placed.
 * @return ::BL_SUCCESS if a character was obtained, ::BL_ERR otherwise.
 */
uint8_t   serGetChar(uint8_t* ch);

/** @brief Flush the receiver.
 */
void    serGetFlush(void);

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#ifdef BTL_HAS_EZSP_SPI
extern uint8_t preSpiComBufIndex;
#define serResetCharInput() preSpiComBufIndex = 0;
#endif
#endif

#else //MSD_BOOTLOADER

// clear serial calls
#define serInit(x) {}
#define serPutFlush(x)
#define serPutChar(x)
#define serPutStr(x)
#define serPutBuf(x)
#define serPutDecimal(x)
#define serPutHex(x) x
#define serPutHexInt(x)
#define serCharAvailable(x)
#define serGetChar(x)
#define serGetFlush(x)

#endif //MSD_BOOTLOADER

#endif //__BOOTLOADER_SERIAL_H__

/**@} end of group*/
