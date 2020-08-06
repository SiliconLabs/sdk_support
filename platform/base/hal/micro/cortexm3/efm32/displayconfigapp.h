/***************************************************************************//**
 * @file
 * @brief Display application specific configuration file.
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
#ifndef _DISPLAY_CONFIG_APP_H_
#define _DISPLAY_CONFIG_APP_H_

/* Include pixel matrix allocation support. */
#define PIXEL_MATRIX_ALLOC_SUPPORT

/* Enable allocation of pixel matrices from the static pixel matrix pool.
 *    NOTE:
 *    The allocator does not support free'ing pixel matrices. It allocates
 *    continuosly from the static pool without keeping track of the sizes of
 *    old allocations. I.e. this is a one-shot allocator, and the  user should
 *    allocate buffers once at the beginning of the program.
 */
#define USE_STATIC_PIXEL_MATRIX_POOL

/* Specify the size of the static pixel matrix pool. For the weatherstation demo
 *    we need one pixel matrix (framebuffer) covering the whole display.
 */
#define PIXEL_MATRIX_POOL_SIZE   (DISPLAY0_HEIGHT * DISPLAY0_WIDTH / 8)

#endif /* _DISPLAY_CONFIG_APP_H_ */
