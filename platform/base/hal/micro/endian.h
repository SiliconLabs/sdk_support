/***************************************************************************//**
 * @file
 * @brief See @ref endian for detailed documentation.
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
#ifndef __ENDIAN_H__
#define __ENDIAN_H__

/** @addtogroup endian
 * Functions that provide conversions from network to host byte
 * order.  Network byte order is big endian, so these APIs are only necessary
 * on platforms which have a natural little endian byte order.  On big-endian
 * platforms, the APIs are macro'd away to nothing.  See endian.h for source
 * code.
 *@{
 */

// If this is being compiled on a Mac then we need to disable the defines
// from its own internal _endian.h file since they conflict with our
// defines. This allows us to compile the 3xx tools for Mac.
#ifdef __APPLE__
  #undef NTOHL
  #undef NTOHS
  #undef HTONL
  #undef HTONS
#endif

#if BIGENDIAN_CPU == false

/** @brief Converts a short (16-bit) value from network to host byte order
 *
 */
  #ifndef NTOHS  // some platforms already define this
uint16_t NTOHS(uint16_t val);

  #endif

/** @brief Converts a long (32-bit) value from network to host byte order
 *
 */
  #ifndef NTOHL  // some platforms already define this
uint32_t NTOHL(uint32_t val);

  #endif

#else // BIGENDIAN_CPU == true

  #ifndef NTOHS  // some platforms already define this
    #define NTOHS(val)  (val)
  #endif
  #ifndef NTOHL  // some platforms already define this
    #define NTOHL(val)  (val)
  #endif

#endif

// The HTON and NTOH operations are the same for sane architectures (eg. big
// and little endian) so define the inverse functions if they don't exist
#ifndef HTONL
  #define HTONL NTOHL
#endif
#ifndef HTONS
  #define HTONS NTOHS
#endif

/* Swap byte order, e.g. LE to BE or BE to LE.
 * This function is used when working with 802.15.4 frames on 8051 MCUs. */
uint32_t SwapEndiannessInt32u(uint32_t val);

/**@} end of Endian Functions
 */

#endif //__ENDIAN_H__
