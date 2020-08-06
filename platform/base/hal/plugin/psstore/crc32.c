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
#include <stdint.h>
#include "em_device.h"

uint32_t bg_crc_calc(uint32_t inCrc32, int size, const uint8_t*data)

{
#if defined (_SILICON_LABS_32B_SERIES_2)
  GPCRC->EN = GPCRC_EN_EN;
  GPCRC->CTRL = GPCRC_CTRL_BYTEMODE;
#else // defined (_SILICON_LABS_32B_SERIES_2)
  GPCRC->CTRL = GPCRC_CTRL_BYTEMODE | GPCRC_CTRL_EN;
#endif //  defined (_SILICON_LABS_32B_SERIES_2)
  GPCRC->INIT = inCrc32;
  GPCRC->CMD = GPCRC_CMD_INIT;

  while (size--) {
    GPCRC->INPUTDATABYTE = *data++;
  }
  return GPCRC->DATA ^ 0xffffffff;
}
