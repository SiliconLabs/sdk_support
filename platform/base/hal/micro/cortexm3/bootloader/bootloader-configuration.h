/***************************************************************************//**
 * @file
 * @brief This file holds any customer accessible configuration options for the
 * Ember bootloaders.
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
// The CUSTOMER_BOOTLOADER_VERSION allows you to track the version of your
// bootloader independent of the Ember release version. This value will be
// stored at a fixed location in memory and be accessible by all Ember tools
// and through an API. The value can be any 32bit integer, however, the value of
// 0xFFFFFFFF is reserved to indicate an unset customer version number.
//
// #define CUSTOMER_BOOTLOADER_VERSION 1
