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

#include "sl_bt_ncp_host.h"
#include "sl_status.h"

extern sl_bt_msg_t*  sl_bt_cmd_msg;
extern sl_bt_msg_t*  sl_bt_rsp_msg;

sl_bt_msg_t* sl_bt_wait_message(void)//wait for event from system
{
  uint32_t msg_length;
  uint32_t header;
  uint8_t  *payload;
  sl_bt_msg_t *pck, *retVal = NULL;
  int      ret;
  //sync to header byte
  ret = sl_bt_api_input(1, (uint8_t*)&header);
  if (ret < 0 || (header & 0x78) != sl_bgapi_dev_type_bt) {
    return 0;
  }
  ret = sl_bt_api_input(SL_BGAPI_MSG_HEADER_LEN - 1, &((uint8_t*)&header)[1]);
  if (ret < 0) {
    return 0;
  }

  msg_length = SL_BT_MSG_LEN(header);

  if (msg_length > SL_BGAPI_MAX_PAYLOAD_SIZE) {
    return 0;
  }

  if ((header & 0xf8) == (sl_bgapi_dev_type_bt | sl_bgapi_msg_type_evt)) {
    //received event
    if ((sl_bt_queue_w + 1) % SL_BT_API_QUEUE_LEN == sl_bt_queue_r) {
      //drop packet
      if (msg_length) {
        uint8_t tmp_payload[SL_BGAPI_MAX_PAYLOAD_SIZE];
        sl_bt_api_input(msg_length, tmp_payload);
      }
      return 0;      //NO ROOM IN QUEUE
    }
    pck = &sl_bt_queue[sl_bt_queue_w];
    sl_bt_queue_w = (sl_bt_queue_w + 1) % SL_BT_API_QUEUE_LEN;
  } else if ((header & 0xf8) == sl_bgapi_dev_type_bt) {//response
    retVal = pck = sl_bt_rsp_msg;
  } else {
    //fail
    return 0;
  }
  pck->header = header;
  payload = (uint8_t*)&pck->data.payload;
  /**
   * Read the payload data if required and store it after the header.
   */
  if (msg_length) {
    ret = sl_bt_api_input(msg_length, payload);
    if (ret < 0) {
      return 0;
    }
  }

  // Using retVal avoid double handling of event msg types in outer function
  return retVal;
}

bool sl_bt_event_pending(void)
{
  if (sl_bt_queue_w != sl_bt_queue_r) {//event is waiting in queue
    return true;
  }

  //something in uart waiting to be read
  if (sl_bt_api_peek && sl_bt_api_peek()) {
    return true;
  }

  return false;
}

sl_status_t sl_bt_get_event(int block, sl_bt_msg_t* event)
{
  sl_bt_msg_t* p;
  while (1) {
    if (sl_bt_queue_w != sl_bt_queue_r) {
      memcpy(event, &sl_bt_queue[sl_bt_queue_r], sizeof(sl_bt_msg_t));
      sl_bt_queue_r = (sl_bt_queue_r + 1) % SL_BT_API_QUEUE_LEN;
      return SL_STATUS_OK;
    }
    //if not blocking and nothing in uart -> out
    if (!block && sl_bt_api_peek && sl_bt_api_peek() == 0) {
      return SL_STATUS_WOULD_BLOCK;
    }

    //read more messages from device
    if ( (p = sl_bt_wait_message()) ) {
      memcpy(event, p, sizeof(sl_bt_msg_t));
      return SL_STATUS_OK;
    }
  }
}

sl_status_t sl_bt_wait_event(sl_bt_msg_t* event)
{
  return sl_bt_get_event(1, event);
}

sl_status_t sl_bt_pop_event(sl_bt_msg_t* event)
{
  return sl_bt_get_event(0, event);
}

sl_bt_msg_t* sl_bt_wait_response(void)
{
  sl_bt_msg_t* p;
  while (1) {
    p = sl_bt_wait_message();
    if (p && !(p->header & sl_bgapi_msg_type_evt)) {
      return p;
    }
  }
}

void sl_bt_host_handle_command()
{
  //packet in sl_bt_cmd_msg is waiting for output
  sl_bt_api_output(SL_BGAPI_MSG_HEADER_LEN + SL_BT_MSG_LEN(sl_bt_cmd_msg->header), (uint8_t*)sl_bt_cmd_msg);
  sl_bt_wait_response();
}

void sl_bt_host_handle_command_noresponse()
{
  //packet in sl_bt_cmd_msg is waiting for output
  sl_bt_api_output(SL_BGAPI_MSG_HEADER_LEN + SL_BT_MSG_LEN(sl_bt_cmd_msg->header), (uint8_t*)sl_bt_cmd_msg);
}
