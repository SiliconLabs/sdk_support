/***************************************************************************//**
 * @file
 * @brief Versioning of Silicon Labs base repo
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
// The 4 digit version: A.B.C.D
#define SL_BASE_MAJOR_VERSION     6
#define SL_BASE_MINOR_VERSION     9
#define SL_BASE_PATCH_VERSION     0
#define SL_BASE_SPECIAL_VERSION   0

// Version represented in 2 bytes as hexadecimal <Major><minor><patch><special>
#define SL_BASE_BUILD_NUMBER      0
#define SL_BASE_FULL_VERSION      ((SL_BASE_MAJOR_VERSION << 12)   \
                                   | (SL_BASE_MINOR_VERSION <<  8) \
                                   | (SL_BASE_PATCH_VERSION <<  4) \
                                   | (SL_BASE_SPECIAL_VERSION))

//#define SL_BASE_VERSION_TYPE  SL_VERSION_TYPE_GA
