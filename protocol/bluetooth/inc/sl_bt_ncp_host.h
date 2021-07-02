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

#ifndef SL_BT_API_QUEUE_LEN
#define SL_BT_API_QUEUE_LEN 30
#endif

#define SL_BT_API_DEFINE()

/**
 * Structure defining a device type and the event queue where events of that
 * type should be stored.
 */
typedef struct {
  enum sl_bgapi_dev_types device_type; /*< Protocol/device type */
  uint32_t write_offset; /*< Pointer to the protocol consumer's write offset counter */
  uint32_t read_offset; /*< Pointer to the protocol consumer's write offset counter */
  sl_bt_msg_t *buffer; /*< Pointer to the protocol consumer's event queue buffer */
  uint32_t len; /*< Number of events possible to store in the queue */
} bgapi_device_type_queue_t;

extern bgapi_device_type_queue_t sl_bt_api_queue;

void sli_bgapi_register_device(bgapi_device_type_queue_t *queue);
bool sli_bgapi_device_queue_has_events(bgapi_device_type_queue_t *device_queue);
bool sli_bgapi_other_events_in_queue(enum sl_bgapi_dev_types my_device_type);
sl_status_t sli_bgapi_get_event(int block, sl_bt_msg_t *event, bgapi_device_type_queue_t *device_queue);

/**
 * Initialize SL_BT_API
 * @param OFUNC
 * @param IFUNC
 */
#define SL_BT_API_INITIALIZE(OFUNC, IFUNC)          \
  do { sl_bt_api_output = OFUNC;                    \
       sl_bt_api_input = IFUNC;                     \
       sl_bt_api_peek = NULL;                       \
       sli_bgapi_register_device(&sl_bt_api_queue); \
  } while (0)

/**
 * Initialize SL_BT_API to support nonblocking mode
 * @param OFUNC
 * @param IFUNC
 * @param PFUNC peek function to check if there is data to be read from UART
 */
#define SL_BT_API_INITIALIZE_NONBLOCK(OFUNC, IFUNC, PFUNC) \
  do { sl_bt_api_output = OFUNC;                           \
       sl_bt_api_input = IFUNC;                            \
       sl_bt_api_peek = PFUNC;                             \
       sli_bgapi_register_device(&sl_bt_api_queue);        \
  } while (0)

extern void(*sl_bt_api_output)(uint32_t len1, uint8_t* data1);
extern int32_t (*sl_bt_api_input)(uint32_t len1, uint8_t* data1);
extern int32_t(*sl_bt_api_peek)(void);
void sl_bt_host_handle_command();
void sl_bt_host_handle_command_noresponse();
sl_status_t sl_bt_wait_event(sl_bt_msg_t *p);

sl_bt_msg_t* sli_wait_for_bgapi_message(sl_bt_msg_t *response_buf);

#endif
