/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef __IEEE802154MAC_H__
#define __IEEE802154MAC_H__

//------------------------------------------------------------------------
// 802.15.4 Frame Control Field definitions for Beacon, Ack, Data, Command

#define MAC_FRAME_TYPE_MASK                    ((uint16_t)0x0007U) // Bits 0..2
#define MAC_FRAME_TYPE_BEACON                  ((uint16_t)0x0000U) // Beacon
#define MAC_FRAME_TYPE_DATA                    ((uint16_t)0x0001U) // Data
#define MAC_FRAME_TYPE_ACK                     ((uint16_t)0x0002U) // ACK
#define MAC_FRAME_TYPE_COMMAND                 ((uint16_t)0x0003U) // Command
#define MAC_FRAME_TYPE_CONTROL                 MAC_FRAME_TYPE_COMMAND // (synonym)
#define MAC_FRAME_TYPE_RESERVED_MASK           ((uint16_t)0x0004U) // Versions 0/1
// 802.15.4E-2012 introduced MultiPurpose with different Frame Control Field
// layout described in the MultiPurpose section below.
#define MAC_FRAME_TYPE_MULTIPURPOSE            ((uint16_t)0x0005U) // MultiPurpose

#define MAC_FRAME_FLAG_SECURITY_ENABLED        ((uint16_t)0x0008U) // Bit 3
#define MAC_FRAME_FLAG_FRAME_PENDING           ((uint16_t)0x0010U) // Bit 4
#define MAC_FRAME_FLAG_ACK_REQUIRED            ((uint16_t)0x0020U) // Bit 5
#define MAC_FRAME_FLAG_INTRA_PAN               ((uint16_t)0x0040U) // Bit 6
// 802.15.4-2006 renamed the Intra-Pan flag PanId-Compression
#define MAC_FRAME_FLAG_PANID_COMPRESSION       MAC_FRAME_FLAG_INTRA_PAN
#define MAC_FRAME_FLAG_RESERVED                ((uint16_t)0x0080U) // Bit 7 reserved
// Use the reserved flag internally for CCA inhibit
#define MAC_INHIBIT_CCA                        MAC_FRAME_FLAG_RESERVED
// 802.15.4E-2012 introduced these flags for Frame Version 2 frames
// which are reserved bit positions in earlier Frame Version frames:
#define MAC_FRAME_FLAG_SEQ_SUPPRESSION         ((uint16_t)0x0100U) // Bit 8
#define MAC_FRAME_FLAG_IE_LIST_PRESENT         ((uint16_t)0x0200U) // Bit 9

#define MAC_FRAME_DESTINATION_MODE_MASK        ((uint16_t)0x0C00U) // Bits 10..11
#define MAC_FRAME_DESTINATION_MODE_NONE        ((uint16_t)0x0000U) // Mode 0
#define MAC_FRAME_DESTINATION_MODE_RESERVED    ((uint16_t)0x0400U) // Mode 1
#define MAC_FRAME_DESTINATION_MODE_SHORT       ((uint16_t)0x0800U) // Mode 2
#define MAC_FRAME_DESTINATION_MODE_LONG        ((uint16_t)0x0C00U) // Mode 3
// 802.15.4e-2012 only (not adopted into 802.15.4-2015)
#define MAC_FRAME_DESTINATION_MODE_BYTE        MAC_FRAME_DESTINATION_MODE_RESERVED

#define MAC_FRAME_VERSION_MASK                 ((uint16_t)0x3000U) // Bits 12..13
#define MAC_FRAME_VERSION_2003                 ((uint16_t)0x0000U) // Version 0
#define MAC_FRAME_VERSION_2006                 ((uint16_t)0x1000U) // Version 1
// In 802.15.4-2015, Version 2 is just called "IEEE STD 802.15.4"
// which can be rather confusing. It was introduced in 802.15.4E-2012.
#define MAC_FRAME_VERSION_2012                 ((uint16_t)0x2000U) // Version 2
#define MAC_FRAME_VERSION_RESERVED             ((uint16_t)0x3000U) // Version 3

#define MAC_FRAME_SOURCE_MODE_MASK             ((uint16_t)0xC000U) // Bits 14..15
#define MAC_FRAME_SOURCE_MODE_NONE             ((uint16_t)0x0000U) // Mode 0
#define MAC_FRAME_SOURCE_MODE_RESERVED         ((uint16_t)0x4000U) // Mode 1
#define MAC_FRAME_SOURCE_MODE_SHORT            ((uint16_t)0x8000U) // Mode 2
#define MAC_FRAME_SOURCE_MODE_LONG             ((uint16_t)0xC000U) // Mode 3
// 802.15.4e-2012 only (not adopted into 802.15.4-2015)
#define MAC_FRAME_SOURCE_MODE_BYTE             MAC_FRAME_SOURCE_MODE_RESERVED

//------------------------------------------------------------------------
// 802.15.4E-2012 Frame Control Field definitions for MultiPurpose

#define MAC_MP_FRAME_TYPE_MASK                 MAC_FRAME_TYPE_MASK // Bits 0..2
#define MAC_MP_FRAME_TYPE_MULTIPURPOSE         MAC_FRAME_TYPE_MULTIPURPOSE

#define MAC_MP_FRAME_FLAG_LONG_FCF             ((uint16_t)0x0008U) // Bit 3

#define MAC_MP_FRAME_DESTINATION_MODE_MASK     ((uint16_t)0x0030U) // Bits 4..5
#define MAC_MP_FRAME_DESTINATION_MODE_NONE     ((uint16_t)0x0000U) // Mode 0
#define MAC_MP_FRAME_DESTINATION_MODE_RESERVED ((uint16_t)0x0010U) // Mode 1
#define MAC_MP_FRAME_DESTINATION_MODE_SHORT    ((uint16_t)0x0020U) // Mode 2
#define MAC_MP_FRAME_DESTINATION_MODE_LONG     ((uint16_t)0x0030U) // Mode 3
// 802.15.4e-2012 only (not adopted into 802.15.4-2015)
#define MAC_MP_FRAME_DESTINATION_MODE_BYTE     MAC_MP_FRAME_DESTINATION_MODE_RESERVED

#define MAC_MP_FRAME_SOURCE_MODE_MASK          ((uint16_t)0x00C0U) // Bits 6..7
#define MAC_MP_FRAME_SOURCE_MODE_NONE          ((uint16_t)0x0000U) // Mode 0
#define MAC_MP_FRAME_SOURCE_MODE_RESERVED      ((uint16_t)0x0040U) // Mode 1
#define MAC_MP_FRAME_SOURCE_MODE_SHORT         ((uint16_t)0x0080U) // Mode 2
#define MAC_MP_FRAME_SOURCE_MODE_LONG          ((uint16_t)0x00C0U) // Mode 3
// 802.15.4e-2012 only (not adopted into 802.15.4-2015)
#define MAC_MP_FRAME_SOURCE_MODE_BYTE          MAC_MP_FRAME_SOURCE_MODE_RESERVED

#define MAC_MP_FRAME_FLAG_PANID_PRESENT        ((uint16_t)0x0100U) // Bit 8
#define MAC_MP_FRAME_FLAG_SECURITY_ENABLED     ((uint16_t)0x0200U) // Bit 9
#define MAC_MP_FRAME_FLAG_SEQ_SUPPRESSION      ((uint16_t)0x0400U) // Bit 10
#define MAC_MP_FRAME_FLAG_FRAME_PENDING        ((uint16_t)0x0800U) // Bit 11

#define MAC_MP_FRAME_VERSION_MASK              MAC_FRAME_VERSION_MASK // Bits 12..13
#define MAC_MP_FRAME_VERSION_2012              ((uint16_t)0x0000U) // Version 0
// All other MultiPurpose Frame Versions are reserved

#define MAC_MP_FRAME_FLAG_ACK_REQUIRED         ((uint16_t)0x4000U) // Bit 14
#define MAC_MP_FRAME_FLAG_IE_LIST_PRESENT      ((uint16_t)0x8000U) // Bit 15

//------------------------------------------------------------------------
// Information Elements fields

// There are Header IEs and Payload IEs.  Header IEs are authenticated
// if MAC Security is enabled.  Payload IEs are both authenticated and
// encrypted if MAC security is enabled.

// Header and Payload IEs have slightly different formats and different
// contents based on the 802.15.4 spec.

// Both are actually a list of IEs that continues until a termination
// IE is seen.

#define MAC_FRAME_HEADER_INFO_ELEMENT_LENGTH_MASK 0x007F // bits 0-6
#define MAC_FRAME_HEADER_INFO_ELEMENT_ID_MASK     0x7F80 // bits 7-14
#define MAC_FRAME_HEADER_INFO_ELEMENT_TYPE_MASK   0x8000 // bit  15

#define MAC_FRAME_HEADER_INFO_ELEMENT_ID_SHIFT 7

#define MAC_FRAME_PAYLOAD_INFO_ELEMENT_LENGTH_MASK   0x07FF  // bits 0 -10
#define MAC_FRAME_PAYLOAD_INFO_ELEMENT_GROUP_ID_MASK 0x7800  // bits 11-14
#define MAC_FRAME_PAYLOAD_INFO_ELEMENT_TYPE_MASK     0x8000  // bit  15

#define MAC_FRAME_PAYLOAD_INFO_ELEMENT_ID_SHIFT      11

// This "type" field indicates header vs. payload IE.  However there is
// also a Header IE List terminator which would imply the IE list
// that follows is only payload IEs.
#define MAC_FRAME_INFO_ELEMENT_TYPE_MASK             0x8000

// Header Termination ID 1 is used when there are Payload IEs that follow.
// Header Termination ID 2 is used when there are no Payload IEs and the
//   next field is the MAC payload.
#define MAC_FRAME_HEADER_TERMINATION_ID_1 0x7E
#define MAC_FRAME_HEADER_TERMINATION_ID_2 0x7F
#define MAC_FRAME_PAYLOAD_TERMINATION_ID 0x0F

#endif //__IEEE802154MAC_H__
