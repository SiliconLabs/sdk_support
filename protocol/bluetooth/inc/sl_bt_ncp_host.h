/***************************************************************************//**
 * @brief Adaptation layer between host application and SL_BT_API protocol
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

#ifndef SL_BT_NCP_HOST_H
#define SL_BT_NCP_HOST_H

/*****************************************************************************
 *
 *  This is an adaptation layer between host application and SL_BT_API protocol.
 *  It provides synchronization mechanism for SL_BT_API-protocol that allows
 *  using same application architecture between application in mcu and external
 *  host.
 *
 *  Synchronization is done by waiting for response after each command. If
 *  any events are received during response waiting, they are queued and
 *  delivered next time sl_bt_wait_event is called.
 *
 *  Queue length is controlled by defining macro "SL_BT_API_QUEUE_LEN", default is 30.
 *  Queue length depends on use cases and allowed host memory usage.
 *
 *  SL_BT_API usage:
 *      Define library, it must be defined globally:
 *          SL_BT_API_DEFINE();
 *
 *      Declare and define output function, prototype is:
 *          void my_output(uint16_t len,uint8_t* data);
 *          Function sends "len" amount of data from pointer "data" to device.
 *
 *      Declare and define input function, prototype is:
 *          void my_input(uint16_t len,uint8_t* data);
 *          Function reads "len" amount of data to pointer "data" from device.
 *          Function return nonzero if it failed.
 *
 *      Initialize library,and provide output and input function:
 *          SL_BT_API_INITIALIZE(my_output,my_input);
 *
 *
 *  Receiving event:
 *   Events are received by sl_bt_wait_event-function.
 *
 *   prototype:
 *       sl_bt_msg_t* sl_bt_wait_event(void)
 *
 *   Event ID can be read from header of event by SL_BT_API_MSG_ID-macro.
 *
 *   Event data can be accessed thru returned pointer.
 *
 *   Example:
 *       sl_bt_msg_t *p;
 *
 *       p=sl_bt_wait_event()
 *
 *       if(SL_BT_API_MSG_ID(p->header)==sl_bt_evt_gatt_server_characteristic_status_id)
 *       {
 *           c=evt->evt_gatt_server_characteristic_status.connection;//accesses connection field of event data
 *       }
 *
 *  Sending commands:
 *   SL_BT_API-commands can be sent by calling helper functions, that then build SL_BT_API-message and call output-function.
 *   Function then waits for response and return pointer to that message.
 *
 *   Example:
 *       //Test that connection to the device is working
 *       if(sl_bt_system_hello() == SL_STATUS_OK)
 *       {//function call was successful
 *
 *       }
 *
 *
 ****************************************************************************/

#if _MSC_VER  //msvc
#define inline __inline
#endif

#include "sl_bt_api.h"

#ifndef SL_BT_QUEUE_LEN
#define SL_BT_API_QUEUE_LEN 30
#endif

#define SL_BT_API_DEFINE()                                   \
  sl_bt_msg_t _sl_bt_cmd_msg;                                \
  sl_bt_msg_t _sl_bt_rsp_msg;                                \
  sl_bt_msg_t *sl_bt_cmd_msg = &_sl_bt_cmd_msg;              \
  sl_bt_msg_t *sl_bt_rsp_msg = &_sl_bt_rsp_msg;              \
  void (*sl_bt_api_output)(uint32_t len1, uint8_t* data1);   \
  int32_t (*sl_bt_api_input)(uint32_t len1, uint8_t* data1); \
  int32_t (*sl_bt_api_peek)(void);                           \
  sl_bt_msg_t sl_bt_queue[SL_BT_API_QUEUE_LEN];              \
  int    sl_bt_queue_w = 0;                                  \
  int    sl_bt_queue_r = 0;

extern sl_bt_msg_t sl_bt_queue[SL_BT_API_QUEUE_LEN];
extern int    sl_bt_queue_w;
extern int    sl_bt_queue_r;

/**
 * Initialize SL_BT_API
 * @param OFUNC
 * @param IFUNC
 */
#define SL_BT_API_INITIALIZE(OFUNC, IFUNC) sl_bt_api_output = OFUNC; sl_bt_api_input = IFUNC; sl_bt_api_peek = NULL;

/**
 * Initialize SL_BT_API to support nonblocking mode
 * @param OFUNC
 * @param IFUNC
 * @param PFUNC peek function to check if there is data to be read from UART
 */
#define SL_BT_API_INITIALIZE_NONBLOCK(OFUNC, IFUNC, PFUNC) sl_bt_api_output = OFUNC; sl_bt_api_input = IFUNC; sl_bt_api_peek = PFUNC;

extern void(*sl_bt_api_output)(uint32_t len1, uint8_t* data1);
extern int32_t (*sl_bt_api_input)(uint32_t len1, uint8_t* data1);
extern int32_t(*sl_bt_api_peek)(void);
void sl_bt_host_handle_command();
void sl_bt_host_handle_command_noresponse();
sl_status_t sl_bt_wait_event(sl_bt_msg_t *p);

#endif
