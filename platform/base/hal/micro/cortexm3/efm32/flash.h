/***************************************************************************//**
 * @file
 * @brief See @ref flash for documentation.
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
/** @addtogroup flash
 * @brief Definition and description of public flash manipulation routines.
 *
 * @note
 * During an erase or a write the flash is not available,
 * which means code will not be executable from flash. These routines still
 * execute from flash, though, since the bus architecture can support doing so.
 * <b>Additonally, this also means all interrupts will be disabled.</b>
 *
 * <b>Hardware documentation indicates 40us for a write and 21ms for an erase.</b>
 *
 * See flash.h for source code.
 *@{
 */

#ifndef __FLASH_H__
#define __FLASH_H__

#include "hal/micro/cortexm3/memmap.h"

/** @brief Tells the calling code if a Flash Erase operation is active.
 *
 * This state is import to know because Flash Erasing is ATOMIC for 21ms
 * and could disrupt interrupt latency.  But if an ISR can know that it wasn't
 * serviced immediately due to Flash Erasing, then the ISR has the opportunity
 * to correct in whatever manner it needs to.
 *
 * @return A bool flag: true if Flash Erase is active, false otherwise.
 */
bool halFlashEraseIsActive(void);

#ifndef DOXYGEN_SHOULD_SKIP_THIS



/**
 * @brief Assign numerical value to the type of erasure requested.
 */
#define MFB_MASS_ERASE 0x01
#define MFB_PAGE_ERASE 0x02
#define CIB_ERASE      0x03

/** @brief Erases a section of flash back to all 0xFFFF.
 *
 * @param eraseType Choose one of the three types of erasures to perform.
 *  - MFB_MASS_ERASE (0x01) Erase the entire main flash block.
 *  - MFB_PAGE_ERASE (0x02) Erase one hardware page in the main flash block
 *  chosen by the \c address parameter.
 *  - CIB_ERASE      (0x03) Erase the entire customer information block.
 *
 * @param address This parameter is only effectual when a MFB_PAGE_ERASE is
 * being performed.  The hardware page encapsulating the address given in this
 * parameter will be erased.  A hardware page size depends on the chip
 *
 * @return An ::EmberStatus value indicating the success or failure of the
 * command:
 *  - EMBER_ERR_FATAL if the \c eraseType is not valid
 *  - EMBER_ERR_FLASH_ERASE_FAIL if erasing failed due to write protection
 *  - EMBER_ERR_FLASH_VERIFY_FAILED if erase verification failed
 *  - EMBER_SUCCESS if erasure completed and verified properly
 */
EmberStatus halInternalFlashErase(uint8_t eraseType, uint32_t address);

/** @brief Writes a block of 16 bit words to flash.  A page is erased
 * to 0xFFFF at every address.  Only two writes can be performed to the same
 * address between erasures and this is enforced by the flash interface
 * controller.  If the value already in the address being written to is 0xFFFF,
 * any value can be written.

 * \b NOTE: The following is deprecated and should only be used internally: If
 * the value is not 0xFFFF and not 0x0000, only 0x0000 can be written.  If the
 * value is 0x0000, nothing can be written.
 *
 * \b NOTE: This function can NOT write the option bytes and will throw an
 * error if that is attempted.
 *
 * \b NOTE: This function can only write on series 2 devices if provided a 4 byte
 * aligned address and an even number of 16bit half-words.
 *
 * @param address The starting address of where the programming will occur.
 * This parameter MUST be half-word aligned since all programming operations
 * are half-words.  Also, the address parameter is NOT a pointer.  This
 * routines will cast the address to a pointer for the actual hardware access.
 *
 * @param data A pointer to a buffer containing the 16bit (half-words) to
 * be written.
 *
 * @param length The number of 16bit (half-words) contained in the data buffer
 * to be written to flash.
 *
 * @return An ::EmberStatus value indicating the success or failure of the
 * command:
 *  - EMBER_ERR_FLASH_PROG_FAIL if the address is not half-word aligned, the
 *    address is inside the option bytes, write protection is enabled, or the
 *    address is being written to more than twice between erasures.
 *  - EMBER_ERR_FLASH_VERIFY_FAILED if write verification failed
 *  - EMBER_SUCCESS if writing completed and verified properly
 */
EmberStatus halInternalFlashWrite(uint32_t address, uint16_t * data, uint32_t length);

/** @brief Writes a block of 32 bit words to flash.  A page is erased
 * to 0xFFFFFFFF at every address. If the value already in the address being written
 * to is 0xFFFFFFFF, any value can be written. Otherwise nothing can be written.
 *
 * \b NOTE: This function can NOT write the option bytes and will throw an
 * error if that is attempted.
 *
 * @param address The starting address of where the programming will occur.
 * This parameter MUST be word (four byte) aligned since all programming operations
 * are words.  Also, the address parameter is NOT a pointer.  This
 * routine will cast the address to a pointer for the actual hardware access.
 *
 * @param data A pointer to a buffer containing the 32bit words to be written.
 *
 * @param length The number of 32bit words contained in the data buffer
 * to be written to flash.
 *
 * @return An ::EmberStatus value indicating the success or failure of the
 * command:
 *  - EMBER_ERR_FLASH_PROG_FAIL if the address is not 32 bit aligned, the
 *    address is inside the option bytes, write protection is enabled, or the
 *    address is being written to more than twice between erasures.
 *  - EMBER_ERR_FLASH_VERIFY_FAILED if write verification failed
 *  - EMBER_SUCCESS if writing completed and verified properly
 */
EmberStatus halInternalFlashWriteSeries2(uint32_t address, uint32_t * data, uint32_t length);

/** @brief Writes a block of 32 bit words to flash.
 * @param address The starting address of where the programming will occur.
 * This parameter MUST be half-word aligned since all programming operations
 * are half-words.  Also, the address parameter is NOT a pointer.  This
 * routine will cast the address to a pointer for the actual hardware access.
 *
 * @param data A pointer to a buffer containing the 32bit words to
 * be written.
 *
 * @param length The number of 32bit words contained in the data buffer
 * to be written to flash.
 */
EmberStatus halInternalFlashWriteWord(uint32_t address, uint32_t * data, uint32_t length);

/** @brief Writes an option byte to the customer information block.  Only
 * two writes can be performed to the same address between erasures and this
 * is enforced by the flash interface controller.
 *
 * @param byte The option byte number, 0 though 7, to be programmed.
 *
 * @param data The 8 bit value to be programmed into the option byte.  The
 * hardware is responsible for calculating the compliment and programming
 * the full 16bit option byte space.
 *
 * @return An ::EmberStatus value indicating the success or failure of the
 * command:
 *  - EMBER_ERR_FLASH_PROG_FAIL if the byte chosen is greater than 7, write
 *    protection is enabled, or the byte is being written to more than twice
 *    between erasures.
 *  - EMBER_ERR_FLASH_VERIFY_FAILED if write verification failed
 *  - EMBER_SUCCESS if writing completed and verified properly
 */
EmberStatus halInternalCibOptionByteWrite(uint8_t byte, uint8_t data);

#endif //DOXYGEN_SHOULD_SKIP_THIS

#endif //__FLASH_H__

/** @} END addtogroup */
