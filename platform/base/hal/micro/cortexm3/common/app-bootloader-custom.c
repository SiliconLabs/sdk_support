/***************************************************************************//**
 * @file
 * @brief Application bootloader
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
#include "bootloader-common.h"
#include "bootloader-serial.h"
#include "bootloader-gpio.h"
#include "app-bootloader.h"
#include "hal/micro/micro.h"
#include "hal.h"

void bootloaderAction(bool runRecovery)
{
  BL_Status status;

  BL_STATE_UP();   // indicate bootloader is up
  BLDEBUG_PRINT("in app bootloader\r\n");

  if (runRecovery) {
    while (1) {
      status = recoveryMode();
      if (status == BL_SUCCESS) {
        // complete image downloaded
        serPutStr("\r\nOk\r\n");
        serPutFlush();
        // reset to reactivate app bootloader to flash image.
        halInternalSysReset(RESET_BOOTLOADER_BOOTLOAD);  // never returns
      } else {
        serPutStr("\r\nERR ");
        serPutHex(status);
        serPutStr("\r\n");
      }
    }
  } else {
    // We were either reset with the BOOTLOAD_BOOTLOAD type, or no valid
    //  image was detected but recovery mode was not activated, so
    // Attempt to install an image from the external eeprom

    // first verify the remote image is valid before we disturb flash
    if ((status = processImage(false)) == BL_SUCCESS ) {
      BLDEBUG_PRINT("image CRC ok\r\n");

      // now actually program the new image to main flash
      if ((status = processImage(true)) == BL_SUCCESS ) {
        BLDEBUG_PRINT("image flashed ok\r\n");
        BL_STATE_DOWNLOAD_SUCCESS();

        // reset and run the new image
        halInternalSysReset(RESET_BOOTLOADER_GO);
      } else {
        // flashing failed
        BLDEBUG_PRINT("process image failed ");
      }
    } else {
      // new image verification failed
      BLDEBUG_PRINT("image CRC failed ");
    }

    BL_STATE_DOWNLOAD_FAILURE();   // indicate download failure
    (void)status;  // avoid warning about unused status in non BL_DEBUG builds
    BLDEBUG(serPutHex(status));
    BLDEBUG_PRINT("\r\n");
    BLDEBUG_PRINT("reboot to app\r\n");
    BLDEBUG(serPutFlush());
    // reset with badimage type.  If there is no valid app image anymore,
    //   the bootloader cstartup will detect it and we'll end up back in the
    //   app bootloader and recovery mode will be activated.
    BL_STATE_DOWN();   // going down
    halInternalSysReset(RESET_BOOTLOADER_BADIMAGE);
  }
}
