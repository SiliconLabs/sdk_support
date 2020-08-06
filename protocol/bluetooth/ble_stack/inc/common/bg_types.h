/***************************************************************************//**
 * @brief Basic types used in Bluetooth stack
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

#ifndef BG_TYPES_H
#define BG_TYPES_H

#include <stdint.h>
#include <stddef.h>

#ifndef SL_BT_TYPE_UINT8ARRARY
#define SL_BT_TYPE_UINT8ARRARY
typedef struct {
  uint8_t len;
  uint8_t  data[];
}uint8array;
#endif

#ifndef SL_BT_TYPE_BYTE_ARRARY
#define SL_BT_TYPE_BYTE_ARRARY
typedef struct {
  uint16_t len;
  uint8_t  data[];
}byte_array;
#endif

#ifndef SL_BT_TYPE_STRING
#define SL_BT_TYPE_STRING
typedef struct {
  uint8_t len;
  int8_t  data[];
} string;
#endif

#ifndef SL_BT_TYPE_BDADDR
#define SL_BT_TYPE_BDADDR
typedef struct {
  uint8_t addr[6];
} bd_addr;
#endif

#ifndef SL_BT_TYPE_SERNAME
#define SL_BT_TYPE_SERNAME
typedef struct {
  uint8_t name[16];
} ser_name;
#endif

#ifndef SL_BT_TYPE_UUID128
#define SL_BT_TYPE_UUID128
typedef struct {
  uint8_t data[16];
} uuid_128;
#endif

#ifndef SL_BT_TYPE_AES_KEY128
#define SL_BT_TYPE_AES_KEY128
typedef struct {
  uint8_t data[16];
} aes_key_128;
#endif

#ifndef SL_BT_TYPE_UUID64
#define SL_BT_TYPE_UUID64
typedef struct {
  uint8_t data[8];
} sl_bt_uuid_64_t;
#endif

#define MAX_UUID_LEN 16

#ifndef SL_BT_TYPE_UUID
#define SL_BT_TYPE_UUID
typedef struct {
  uint8_t uuid[MAX_UUID_LEN];
  uint32_t len;
} sl_bt_uuid_t;
#endif

#if !defined _MSC_VER && !defined __APPLE__
/* Don't define under MSVC and OSX */

#ifndef memcpy
void * memcpy(void *OUT, const void *IN, size_t N);
#endif
#ifndef memcmp
int  memcmp(const void *S1, const void *S2, size_t N);
#endif
#ifndef memset
void * memset(void *DST, int c, size_t LENGTH);
#endif
#ifndef memmove
void * memmove(void *DST, const void *src, size_t LENGTH);
#endif
#endif

#endif
