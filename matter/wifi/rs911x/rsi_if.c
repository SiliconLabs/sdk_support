#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "em_bus.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_usart.h"

#include "sl_status.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

#include "wfx_host_events.h"

#include "rsi_driver.h"
#include "rsi_wlan_non_rom.h"

#include "rsi_common_apis.h"
#include "rsi_data_types.h"
#include "rsi_nwk.h"
#include "rsi_socket.h"
#include "rsi_utils.h"
#include "rsi_wlan.h"
#include "rsi_wlan_apis.h"
#include "rsi_wlan_config.h"
//#include "rsi_wlan_non_rom.h"
#include "rsi_bootup_config.h"
#include "rsi_error.h"
#include "rsi_ble.h"
#include "rsi_ble_apis.h"
#include "rsi_ble_common_config.h"
#include "rsi_ble_config.h"
#include "rsi_bootup_config.h"
#include "rsi_bt_common.h"
#include "rsi_bt_common_apis.h"
#include "dhcp_client.h"
#include "wfx_rsi.h"

//! BLE attribute service types uuid values
#define RSI_BLE_CHAR_SERV_UUID 0x2803
#define RSI_BLE_CLIENT_CHAR_UUID 0x2902

//! BLE characteristic service uuid
#define RSI_BLE_HEART_RATE_SERVICE_UUID 0x180D
#define RSI_BLE_HEART_RATE_MEASUREMENT_UUID 0x2A37
#define RSI_BLE_SENSOR_LOCATION_UUID 0x2A38
#define RSI_BLE_HEART_RATE_CONTROL_POINT_UUID 0x2A39

#define CHIP_ADV_DATA_TYPE_UUID 0x03
#define CHIP_ADV_DATA_TYPE_NAME 0x09
#define CHIP_ADV_DATA_TYPE_SERVICE_DATA 0x16
#define CHIP_ADV_SHORT_UUID_LEN 2
#define CHIP_ADV_DATA_FLAGS 0x06
#define RSI_BLE_ATT_PROPERTY_READ 0x02
#define RSI_BLE_ATT_PROPERTY_WRITE 0x08
#define RSI_BLE_ATT_PROPERTY_NOTIFY 0x10

#define RSI_BLE_BODY_SENSOR_LOCATION_WRIST BIT(2)
volatile uint16_t rsi_ble_att3_val_hndl;
const uint8_t ShortUUID_CHIPoBLEService[] = { 0xF6, 0xFF };

bool hasNotifiedIPV6 = false;
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
bool hasNotifiedIPV4 = false;
#endif /* CHIP_DEVICE_CONFIG_ENABLE_IPV4 */
bool hasNotifiedWifiConnectivity = false;
/*
 * This file implements the interface to the RSI SAPIs
 */
wfx_wifi_scan_ext_t *temp_reset;
uint8_t security;

static uint32_t ble_app_event_map;
static uint32_t ble_app_event_mask;
rsi_semaphore_handle_t ble_main_task_sem;
static rsi_ble_event_conn_status_t resp_connect;
static rsi_ble_event_mtu_t * rsi_ble_mtu_exchange;
static rsi_ble_event_conn_status_t conn_event_to_app;
static rsi_ble_event_disconnect_t disconn_event_to_app;
// static rsi_ble_event_write_t app_ble_write_event;
static uint16_t rsi_ble_measurement_hndl;
int8_t notify_start = 0;
rsi_ble_t att_list;
uint8_t retry;
static int8_t ble_wifi_flag = 0;
uint8_t ble_conn_id = 0xFF;
uint8_t coex_ssid[50], dis_ssid[50], pwd[RSI_BLE_MAX_DATA_LEN], sec_type;



/*
 * Getting the AP details
 */
int32_t wfx_rsi_get_ap_info(wfx_wifi_scan_result_t *ap) {
  int32_t status;
  uint8_t rssi;
  ap->security = security;
  ap->chan = wfx_rsi.ap_chan;
  memcpy(&ap->bssid[0], &wfx_rsi.ap_mac.octet[0], 6);
  status = rsi_wlan_get(RSI_RSSI, &rssi, sizeof(rssi));
  if (status == RSI_SUCCESS) {
    ap->rssi = (-1) * rssi;
  }
  return status;
}
int32_t wfx_rsi_get_ap_ext(wfx_wifi_scan_ext_t *extra_info) {
  int32_t status;
  uint8_t buff[28] = {0};
  status = rsi_wlan_get(RSI_WLAN_EXT_STATS, buff, sizeof(buff));
  if (status != RSI_SUCCESS) {
    WFX_RSI_LOG("\r\n Failed, Error Code : 0x%lX\r\n", status);
  } else {
    rsi_wlan_ext_stats_t *test = (rsi_wlan_ext_stats_t *)buff;
    extra_info->beacon_lost_count =
        test->beacon_lost_count - temp_reset->beacon_lost_count;
    extra_info->beacon_rx_count =
        test->beacon_rx_count - temp_reset->beacon_rx_count;
    extra_info->mcast_rx_count =
        test->mcast_rx_count - temp_reset->mcast_rx_count;
    extra_info->mcast_tx_count =
        test->mcast_tx_count - temp_reset->mcast_tx_count;
    extra_info->ucast_rx_count =
        test->ucast_rx_count - temp_reset->ucast_rx_count;
    extra_info->ucast_tx_count =
        test->ucast_tx_count - temp_reset->ucast_tx_count;
    extra_info->overrun_count = test->overrun_count - temp_reset->overrun_count;
  }
  return status;
}
int32_t wfx_rsi_reset_count() {
  int32_t status;
  uint8_t buff[28] = {0};
  status = rsi_wlan_get(RSI_WLAN_EXT_STATS, buff, sizeof(buff));
  if (status != RSI_SUCCESS) {
    WFX_RSI_LOG("\r\n Failed, Error Code : 0x%lX\r\n", status);
  } else {
    rsi_wlan_ext_stats_t *test = (rsi_wlan_ext_stats_t *)buff;
    temp_reset->beacon_lost_count = test->beacon_lost_count;
    temp_reset->beacon_rx_count = test->beacon_rx_count;
    temp_reset->mcast_rx_count = test->mcast_rx_count;
    temp_reset->mcast_tx_count = test->mcast_tx_count;
    temp_reset->ucast_rx_count = test->ucast_rx_count;
    temp_reset->ucast_tx_count = test->ucast_tx_count;
    temp_reset->overrun_count = test->overrun_count;
  }
  return status;
}
int32_t wfx_rsi_disconnect() {
  int32_t status = rsi_wlan_disconnect();
  return status;
}
static void wfx_rsi_join_cb(uint16_t status, const uint8_t *buf,
                            const uint16_t len) {
  WFX_RSI_LOG("%s: status: %02x", __func__, status);
  wfx_rsi.dev_state &= ~WFX_RSI_ST_STA_CONNECTING;
  temp_reset = (wfx_wifi_scan_ext_t *)malloc(sizeof(wfx_wifi_scan_ext_t));
  memset(temp_reset, 0, sizeof(wfx_wifi_scan_ext_t));
  if (status != RSI_SUCCESS) {
    /*
     * We should enable retry.. (Need config variable for this)
     */
    WFX_RSI_LOG("%s: failed. retry: %d", __func__, wfx_rsi.join_retries);
#if (WFX_RSI_CONFIG_MAX_JOIN != 0)
    if (++wfx_rsi.join_retries < WFX_RSI_CONFIG_MAX_JOIN)
#endif
    {
      xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_START_JOIN);
    }
  } else {
    /*
     * Join was complete - Do the DHCP
     */
    WFX_RSI_LOG("%s: join completed.", __func__);
#ifdef RS911X_SOCKETS
    xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_DO_DHCP);
#else
    xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_CONN);
#endif
  }
}
static void wfx_rsi_join_fail_cb(uint16_t status, uint8_t *buf, uint32_t len) {
  WFX_RSI_LOG("%s: error: failed status: %02x on try %d", __func__, status,
              wfx_rsi.join_retries);
  wfx_rsi.join_retries += 1;
  wfx_rsi.dev_state &= ~WFX_RSI_ST_STA_CONNECTING;
  xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_START_JOIN);
}
#ifdef RS911X_SOCKETS
/*
 * DHCP should end up here.
 */
static void wfx_rsi_ipchange_cb(uint16_t status, uint8_t *buf, uint32_t len) {
  WFX_RSI_LOG("%s: status: %02x", __func__, status);
  if (status != RSI_SUCCESS) {
    /* Restart DHCP? */
    xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_DO_DHCP);
  } else {
    wfx_rsi.dev_state |= WFX_RSI_ST_STA_DHCP_DONE;
    xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_DHCP_DONE);
  }
}
#else
/*
 * Got RAW WLAN data pkt
 */
static void wfx_rsi_wlan_pkt_cb(uint16_t status, uint8_t *buf, uint32_t len) {
  // WFX_RSI_LOG("%s: status=%d, len=%d", __func__, status, len);
  if (status != RSI_SUCCESS) {
    return;
  }
  wfx_host_received_sta_frame_cb(buf, len);
}
#endif /* !Socket support */
static int32_t wfx_rsi_init(void)
{
    int32_t status;

    while (ble_wifi_flag != 1)
    {
        vTaskDelay(200);
    }

#if 0  /* missing in sapi library */
 	if ((status = rsi_wlan_register_callbacks (RSI_WLAN_JOIN_RESPONSE_HANDLER, wfx_rsi_join_cb)) != RSI_SUCCESS) {
                 WFX_RSI_LOG ("*ERR*RSI CB register join cb");
                 return status;
         }
#endif /* missing in sapi */
    if ((status = rsi_wlan_register_callbacks(RSI_JOIN_FAIL_CB, wfx_rsi_join_fail_cb)) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("*ERR*RSI CB register join fail");
        return status;
    }
#ifdef RS911X_SOCKETS
    (void) rsi_wlan_register_callbacks(RSI_IP_CHANGE_NOTIFY_CB, wfx_rsi_ipchange_cb);
#else
    if ((status = rsi_wlan_register_callbacks(RSI_WLAN_DATA_RECEIVE_NOTIFY_CB, wfx_rsi_wlan_pkt_cb)) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("*ERR*RSI CB register data-notify");
        return status;
    }
#endif
    wfx_rsi.dev_state |= WFX_RSI_ST_DEV_READY;
    WFX_RSI_LOG("WFX:RSI: OK");

    return RSI_SUCCESS;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_init_events
 * @brief      initializes the event parameter.
 * @param[in]  none.
 * @return     none.
 * @section description
 * This function is used during BLE initialization.
 */
static void rsi_ble_app_init_events()
{
    ble_app_event_map  = 0;
    ble_app_event_mask = 0xFFFFFFFF;
    ble_app_event_mask = ble_app_event_mask; // To suppress warning while compiling
    return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_app_set_event
 * @brief      set the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to set/raise the specific event.
 */
static void rsi_ble_app_set_event(uint32_t event_num)
{
    ble_app_event_map |= BIT(event_num);
    return;
}


/*==============================================*/
/**
 * @fn         rsi_ble_app_clear_event
 * @brief      clears the specific event.
 * @param[in]  event_num, specific event number.
 * @return     none.
 * @section description
 * This function is used to clear the specific event.
 */
static void rsi_ble_app_clear_event(uint32_t event_num)
{
    ble_app_event_map &= ~BIT(event_num);
    return;
}




/*==============================================*/
/**
 * @fn         rsi_ble_app_get_event
 * @brief      returns the first set event based on priority
 * @param[in]  none.
 * @return     int32_t
 *             > 0  = event number
 *             -1   = not received any event
 * @section description
 * This function returns the highest priority event among all the set events
 */
static int32_t rsi_ble_app_get_event(void)
{
    uint32_t ix;

    for (ix = 0; ix < 32; ix++)
    {
        if (ble_app_event_map & (1 << ix))
        {
            return ix;
        }
    }

    return (-1);
}



void rsi_ble_on_enhance_conn_status_event(rsi_ble_event_enhance_conn_status_t * resp_enh_conn)
{
    conn_event_to_app.dev_addr_type = resp_enh_conn->dev_addr_type;
    memcpy(conn_event_to_app.dev_addr, resp_enh_conn->dev_addr, RSI_DEV_ADDR_LEN);
    conn_event_to_app.status = resp_enh_conn->status;
    memcpy(&resp_connect, &conn_event_to_app, sizeof(rsi_ble_event_conn_status_t));

    //Ble_ConnectEvent_notify();
    rsi_ble_app_set_event(RSI_BLE_CONN_EVENT);
}
static void rsi_ble_on_connect_event(rsi_ble_event_conn_status_t * resp_conn)
{
    //  sl_bt_msg_t * evt;
    // Ble_ConnectEvent_notify(evt);
  //  memcpy(&conn_event_to_app, resp_conn, sizeof(rsi_ble_event_conn_status_t));

    rsi_ble_app_set_event(RSI_BLE_CONN_EVENT);
}
static void rsi_ble_on_disconnect_event(rsi_ble_event_disconnect_t * resp_disconnect, uint16_t reason)
{
    UNUSED_PARAMETER(reason); // This statement is added only to resolve compilation warning, value is unchanged
    memcpy(&disconn_event_to_app, resp_disconnect, sizeof(rsi_ble_event_disconnect_t));

    rsi_ble_app_set_event(RSI_BLE_DISCONN_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_gatt_write_event
 * @brief      its invoked when write/notify/indication events are received.
 * @param[in]  event_id, it indicates write/notification event id.
 * @param[in]  rsi_ble_write, write event parameters.
 * @return     none.
 * @section description
 * This callback function is invoked when write/notify/indication events are received
 */

void rsi_ble_on_gatt_write_event(uint16_t event_id, rsi_ble_event_write_t * rsi_ble_write)
{
    UNUSED_PARAMETER(event_id); // This statement is added only to resolve compilation warning, value is unchanged
   // uint8_t cmdid;
    // sl_bt_msg_t * evt;
    // evt =(void *)malloc(sizeof(sl_bt_msg_t));
    // memcpy(&(evt->data.evt_gatt_server_user_write_request.value.len),&rsi_ble_write->length,sizeof(rsi_ble_event_write_t));
    // memcpy(&(evt->data.handle),&rsi_ble_write->handle,sizeof(rsi_ble_event_write_t));

    int length = rsi_ble_write->length;
    for (int j=0; j < length; j++)
    {
    for (int i = j; i < length; i++)
    {
        WFX_RSI_LOG("value : %d", rsi_ble_write->att_value[i]);
    }
    WFX_RSI_LOG(" done \n");
    memset(rsi_ble_write, 0, sizeof(rsi_ble_event_write_t));
    }
   //Ble_write_Notify(evt);
       rsi_ble_app_set_event(RSI_BLE_GATT_WRITE_EVENT);

    return;
}
/*==============================================*/
/**
 * @fn         rsi_ble_on_mtu_event
 * @brief      its invoked when mtu exhange event is received.
 * @param[in]  rsi_ble_mtu, mtu event paramaters.
 * @return     none.
 * @section description
 * This callback function is invoked when  mtu exhange event is received
 */
static void rsi_ble_on_mtu_event(rsi_ble_event_mtu_t * rsi_ble_mtu)
{

    rsi_ble_mtu_exchange = rsi_ble_mtu;
    //set conn specific event
    rsi_ble_app_set_event(RSI_BLE_MTU_EVENT);
}

/*==============================================*/
/**
 * @fn         rsi_ble_on_event_indication_confirmation
 * @brief      this function will invoke when received indication confirmation event
 * @param[out] resp_id, response id
 * @param[out] status, status of the response
 * @return     none
 * @section description
 */
static void rsi_ble_on_event_indication_confirmation(uint16_t resp_status, rsi_ble_set_att_resp_t * rsi_ble_event_set_att_rsp)
{
UNUSED_PARAMETER(resp_status);
   // if(rsi_ble_event_set_att_rsp->dev_addr[RSI_DEV_ADDR_LEN]==)
    //! set conn specific event
    rsi_ble_app_set_event(RSI_BLE_GATT_INDICATION_CONFIRMATION);
}

/*
 * The main WLAN task - started by wfx_wifi_start () that interfaces with RSI.
 * The rest of RSI stuff come in call-backs.
 * The initialization has been already done.
 */
/* ARGSUSED */

#if 1
/*==============================================*/
/**
 * @fn         rsi_gatt_add_attribute_to_list
 * @brief      This function is used to store characteristic service attribute.
 * @param[in]  p_val, pointer to homekit structure
 * @param[in]  handle, characteristic service attribute handle.
 * @param[in]  data_len, characteristic value length
 * @param[in]  data, characteristic value pointer
 * @param[in]  uuid, characteristic value uuid
 * @return     none.
 * @section description
 * This function is used to store all attribute records
 */
void rsi_gatt_add_attribute_to_list(rsi_ble_t * p_val, uint16_t handle, uint16_t data_len, uint8_t * data, uuid_t uuid,
                                    uint8_t char_prop)
{
    if ((p_val->DATA_ix + data_len) >= BLE_ATT_REC_SIZE)
    { //! Check for max data length for the characteristic value
        LOG_PRINT("\r\n no data memory for att rec values \r\n");
        return;
    }

    p_val->att_rec_list[p_val->att_rec_list_count].char_uuid     = uuid;
    p_val->att_rec_list[p_val->att_rec_list_count].handle        = handle;
    p_val->att_rec_list[p_val->att_rec_list_count].value_len     = data_len;
    p_val->att_rec_list[p_val->att_rec_list_count].max_value_len = data_len;
    p_val->att_rec_list[p_val->att_rec_list_count].char_val_prop = char_prop;
    memcpy(p_val->DATA + p_val->DATA_ix, data, data_len);
    p_val->att_rec_list[p_val->att_rec_list_count].value = p_val->DATA + p_val->DATA_ix;
    p_val->att_rec_list_count++;
    p_val->DATA_ix += p_val->att_rec_list[p_val->att_rec_list_count].max_value_len;

    return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_add_char_serv_att
 * @brief      this function is used to add characteristic service attribute..
 * @param[in]  serv_handler, service handler.
 * @param[in]  handle, characteristic service attribute handle.
 * @param[in]  val_prop, characteristic value property.
 * @param[in]  att_val_handle, characteristic value handle
 * @param[in]  att_val_uuid, characteristic value uuid
 * @return     none.
 * @section description
 * This function is used at application to add characteristic attribute
 */
static void rsi_ble_add_char_serv_att(void * serv_handler, uint16_t handle, uint8_t val_prop, uint16_t att_val_handle,
                                      uuid_t att_val_uuid)
{
    rsi_ble_req_add_att_t new_att = { 0 };

    //! preparing the attribute service structure
    new_att.serv_handler       = serv_handler;
    new_att.handle             = handle;
    new_att.att_uuid.size      = 2;
    new_att.att_uuid.val.val16 = RSI_BLE_CHAR_SERV_UUID;
    new_att.property           = RSI_BLE_ATT_PROPERTY_READ;

    //! preparing the characteristic attribute value
    new_att.data_len = att_val_uuid.size + 4;
    new_att.data[0]  = val_prop;
    rsi_uint16_to_2bytes(&new_att.data[2], att_val_handle);
    if (new_att.data_len == 6)
    {
        rsi_uint16_to_2bytes(&new_att.data[4], att_val_uuid.val.val16);
    }
    else if (new_att.data_len == 8)
    {
        rsi_uint32_to_4bytes(&new_att.data[4], att_val_uuid.val.val32);
    }
    else if (new_att.data_len == 20)
    {
        memcpy(&new_att.data[4], &att_val_uuid.val.val128, att_val_uuid.size);
    }
    //! Add attribute to the service
    rsi_ble_add_attribute(&new_att);

    return;
}

/*==============================================*/
/**
 * @fn         rsi_ble_add_char_val_att
 * @brief      this function is used to add characteristic value attribute.
 * @param[in]  serv_handler, new service handler.
 * @param[in]  handle, characteristic value attribute handle.
 * @param[in]  att_type_uuid, attribute uuid value.
 * @param[in]  val_prop, characteristic value property.
 * @param[in]  data, characteristic value data pointer.
 * @param[in]  data_len, characteristic value length.
 * @return     none.
 * @section description
 * This function is used at application to create new service.
 */

static void rsi_ble_add_char_val_att(void * serv_handler, uint16_t handle, uuid_t att_type_uuid, uint8_t val_prop, uint8_t * data,
                                     uint8_t data_len, uint8_t auth_read)
{
    rsi_ble_req_add_att_t new_att = { 0 };

    memset(&new_att, 0, sizeof(rsi_ble_req_add_att_t));
    //! preparing the attributes
    new_att.serv_handler  = serv_handler;
    new_att.handle        = handle;
    new_att.config_bitmap = auth_read;
    memcpy(&new_att.att_uuid, &att_type_uuid, sizeof(uuid_t));
    new_att.property = val_prop;

    if (data != NULL)
        memcpy(new_att.data, data, RSI_MIN(sizeof(new_att.data), data_len));

    //! preparing the attribute value
    new_att.data_len = data_len;

    //! add attribute to the service
    rsi_ble_add_attribute(&new_att);

    if ((auth_read == ATT_REC_MAINTAIN_IN_HOST) || (data_len > 20))
    {
        if (data != NULL)
        {
            rsi_gatt_add_attribute_to_list(&att_list, handle, data_len, data, att_type_uuid, val_prop);
        }
    }

    //! check the attribute property with notification/Indication
    if ((val_prop & RSI_BLE_ATT_PROPERTY_NOTIFY) || (val_prop & RSI_BLE_ATT_PROPERTY_INDICATE))
    {
        //! if notification/indication property supports then we need to add client characteristic service.

        //! preparing the client characteristic attribute & values
        memset(&new_att, 0, sizeof(rsi_ble_req_add_att_t));
        new_att.serv_handler       = serv_handler;
        new_att.handle             = handle + 1;
        new_att.att_uuid.size      = 2;
        new_att.att_uuid.val.val16 = RSI_BLE_CLIENT_CHAR_UUID;
        new_att.property           = RSI_BLE_ATT_PROPERTY_READ | RSI_BLE_ATT_PROPERTY_WRITE;
        new_att.data_len           = 2;

        //! add attribute to the service
        rsi_ble_add_attribute(&new_att);
    }

    return;
}
#endif



static uint32_t rsi_ble_add_simple_chat_serv3(void)
{
    // volatile uint16_t rsi_ble_att2_val_hndl;
    // adding the custom service
    // 0x6A4E3300-667B-11E3-949A-0800200C9A66

    /*static const uuid_t custom_service = { .size             = 16,
                                           .reserved         = { 0x00, 0x00, 0x00 },
                                           .val.val128.data1 = 0x6A4E3300,
                                           .val.val128.data2 = 0x667B,
                                           .val.val128.data3 = 0x11E3,
                                           .val.val128.data4 = { 0x9A, 0x94, 0x00, 0x08, 0x66, 0x9A, 0x0C, 0x20 } };*/

    /*static const uuid_t custom_service = { .size             = 2,
                                           .val16            = 0xFFF6};*/
    uuid_t custom_service    = { 0 };
    custom_service.size      = 2;
    custom_service.val.val16 = 0xFFF6;
    uint8_t data1[254]       = {
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
              0x00,
    };
    // 6A4E3304-667B-11E3-949A-0800200C9A66
    // 18EE2EF5-263D-4559-959F-4F9C429F9D11
    static const uuid_t custom_characteristic_RX = { .size             = 16,
                                                     .reserved         = { 0x00, 0x00, 0x00 },
                                                     .val.val128.data1 = 0x18EE2EF5,
                                                     .val.val128.data2 = 0x263D,
                                                     .val.val128.data3 = 0x4559,
                                                     .val.val128.data4 = { 0x9F, 0x95, 0x9C, 0x4F, 0x11, 0x9D, 0x9F, 0x42 } };

    rsi_ble_resp_add_serv_t new_serv_resp = { 0 };
    rsi_ble_add_service(custom_service, &new_serv_resp);

    // adding custom characteristic declaration to the custom service
    rsi_ble_add_char_serv_att(new_serv_resp.serv_handler, new_serv_resp.start_handle + 1,
                              RSI_BLE_ATT_PROPERTY_WRITE | RSI_BLE_ATT_PROPERTY_READ, // Set read, write, write without response
                              new_serv_resp.start_handle + 2, custom_characteristic_RX);

    // adding characteristic value attribute to the service
    //  rsi_ble_att2_val_hndl = new_serv_resp.start_handle + 2;
    WFX_RSI_LOG("handle 1 : %c \n", new_serv_resp.start_handle + 2);
    rsi_ble_measurement_hndl = new_serv_resp.start_handle + 2;
    rsi_ble_add_char_val_att(new_serv_resp.serv_handler, new_serv_resp.start_handle + 2, custom_characteristic_RX,
                             RSI_BLE_ATT_PROPERTY_WRITE | RSI_BLE_ATT_PROPERTY_READ, // Set read, write, write without response
                             data1, sizeof(data1), 0);

    static const uuid_t custom_characteristic_TX = { .size             = 16,
                                                     .reserved         = { 0x00, 0x00, 0x00 },
                                                     .val.val128.data1 = 0x18EE2EF5,
                                                     .val.val128.data2 = 0x263D,
                                                     .val.val128.data3 = 0x4559,
                                                     .val.val128.data4 = { 0x9F, 0x95, 0x9C, 0x4F, 0x12, 0x9D, 0x9F, 0x42 } };

    // adding custom characteristic declaration to the custom service
    rsi_ble_add_char_serv_att(new_serv_resp.serv_handler, new_serv_resp.start_handle + 3,
                              RSI_BLE_ATT_PROPERTY_WRITE_NO_RESPONSE | RSI_BLE_ATT_PROPERTY_WRITE | RSI_BLE_ATT_PROPERTY_READ |
                                  RSI_BLE_ATT_PROPERTY_NOTIFY |
                                  RSI_BLE_ATT_PROPERTY_INDICATE, // Set read, write, write without response
                              new_serv_resp.start_handle + 4, custom_characteristic_TX);

    // adding characteristic value attribute to the service
    rsi_ble_measurement_hndl = new_serv_resp.start_handle + 4;
    WFX_RSI_LOG("handle 2 : %c \n", new_serv_resp.start_handle + 4);
    rsi_ble_add_char_val_att(new_serv_resp.serv_handler, new_serv_resp.start_handle + 4, custom_characteristic_TX,
                             RSI_BLE_ATT_PROPERTY_WRITE_NO_RESPONSE | RSI_BLE_ATT_PROPERTY_WRITE | RSI_BLE_ATT_PROPERTY_READ |
                                 RSI_BLE_ATT_PROPERTY_NOTIFY |
                                 RSI_BLE_ATT_PROPERTY_INDICATE, // Set read, write, write without response
                             data1, sizeof(data1), 0);

     memset(&data1, 0, sizeof(data1));
    return 0;
}



int32_t rsi_wifi_ble_init();

void rsi_ble_task(void * arg)
{
    int32_t status;
    int32_t event_id;
    uint8_t advData[31] = { 2, 1, 6 };
    uint32_t index      = 0;

    rsi_wifi_ble_init();
    ble_wifi_flag = 1;
    
    // rsi_ble_add_custom_service_serv();
    rsi_ble_add_simple_chat_serv3();

    // rsi_ble_device_info_add_new_serv();
    // registering the GAP callback functions
    rsi_ble_gap_register_callbacks(NULL, rsi_ble_on_connect_event, rsi_ble_on_disconnect_event, NULL, NULL, NULL,
                                   rsi_ble_on_enhance_conn_status_event, NULL, NULL, NULL);
    // registering the GATT call back functions
  rsi_ble_gatt_register_callbacks(NULL,
                                  NULL, /*rsi_ble_profile*/
                                  NULL, /*rsi_ble_char_services*/
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  rsi_ble_on_gatt_write_event,
                                  NULL,
                                  NULL,
                                  NULL,
                                  rsi_ble_on_mtu_event,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL,
                                  rsi_ble_on_event_indication_confirmation,
                                  NULL);
    //  initializing the application events map
    rsi_ble_app_init_events();
    // Set local name
    rsi_bt_set_local_name((uint8_t *) RSI_BLE_DEV_NAME);

    index            = 3;
    advData[index++] = 11;                           // AD length
    advData[index++] = 22;                           // AD type : Service Data
    advData[index++] = ShortUUID_CHIPoBLEService[0]; // AD value
    advData[index++] = ShortUUID_CHIPoBLEService[1];

    advData[index++] = 0;
    advData[index++] = 0;
    advData[index++] = 15;
    advData[index++] = 241;
    advData[index++] = 255;
    advData[index++] = 5;
    advData[index++] = 128;
    advData[index++] = 0;

    //! prepare advertise data //local/device name
    advData[index++] = strlen(RSI_BLE_DEV_NAME) + 1;
    advData[index++] = 9;

    memcpy(&advData[index], RSI_BLE_DEV_NAME, strlen(RSI_BLE_DEV_NAME)); // AD value
    index += strlen(RSI_BLE_DEV_NAME);

    // set advertise data
    rsi_ble_set_advertise_data(advData, index);

    // set device in advertising mode.
    WFX_RSI_LOG("WFX:RSI:BLE start advertising.........");

    status = rsi_ble_start_advertising();
    if (status != RSI_SUCCESS)
    {
        WFX_RSI_LOG("advertising failed = %d ", status);
    }
    WFX_RSI_LOG("advertising started =  index  %d ", index);
    for (uint32_t i = 0; i < index; i++)
    {

        WFX_RSI_LOG(" advData[ %" PRIu32 "] = %u", i, advData[i]);
    }

    // waiting for events from controller.
    while (1)
    {
        // checking for events list
        event_id = rsi_ble_app_get_event();
        if (event_id == -1)
        {
            continue;
        }
        switch (event_id)
        {
        case RSI_BLE_CONN_EVENT: {
            // uint8_t bondingHandle    = 1;
            //   uint8_t connectionHandle = 1;
            //  rsi_ble_on_connect_event(&resp_connect);
            // rsi_AddConnection(connectionHandle, bondingHandle);
            //      PlatformMgr().ScheduleWork(DriveBLEState, 0);
            rsi_ble_app_clear_event(RSI_BLE_CONN_EVENT);
            WFX_RSI_LOG(" RSI_BLE : Module got connected");
        }
        break;
        case RSI_BLE_DISCONN_EVENT: {
            // event invokes when disconnection was completed
            // clear the served event
            rsi_ble_app_clear_event(RSI_BLE_DISCONN_EVENT);

            WFX_RSI_LOG(" RSI_BLE : Module got Disconnected");
            status = rsi_ble_start_advertising();
        }
        break;
        case RSI_BLE_MTU_EVENT: {
            // event invokes when write/notification events received
            WFX_RSI_LOG("RSI_BLE::In  mtu evt");
            WFX_RSI_LOG("\n");
            // clear the served event
            rsi_ble_app_clear_event(RSI_BLE_MTU_EVENT);
        }
        break;
        case RSI_BLE_GATT_WRITE_EVENT: {
            // event invokes when write/notification events received
            WFX_RSI_LOG("RSI_BLE : Write event");
            // clear the served event
            rsi_ble_app_clear_event(RSI_BLE_GATT_WRITE_EVENT);
        }
        break;
        case RSI_BLE_GATT_INDICATION_CONFIRMATION: {
            WFX_RSI_LOG("RSI_BLE : indication confirmation");
        }
        break;

        case RSI_BLE_RESP_ATT_VALUE:
        {
            WFX_RSI_LOG("RSI_BLE : RESP_ATT confirmation");
        }
        default:
            break;
        }
    }
}


void wfx_show_err(char * msg)
{
    WFX_RSI_LOG("RSI ERR: %s", msg);
}
/*
 * Saving the details of the AP
 */
static void wfx_rsi_save_ap_info() {
  int32_t status;
  rsi_rsp_scan_t rsp;

  status = rsi_wlan_scan_with_bitmap_options((int8_t *)&wfx_rsi.sec.ssid[0], 0,
                                             &rsp, sizeof(rsp), 1);
  if (status) {
    /*
     * Scan is done - failed
     */
  } else {
    wfx_rsi.sec.security = rsp.scan_info->security_mode;
    wfx_rsi.ap_chan = rsp.scan_info->rf_channel;
    memcpy(&wfx_rsi.ap_mac.octet[0], &rsp.scan_info->bssid[0], 6);
  }
  if ((wfx_rsi.sec.security == RSI_WPA) || (wfx_rsi.sec.security == RSI_WPA2)) {
    // saving the security before changing into mixed mode
    security = wfx_rsi.sec.security;
    wfx_rsi.sec.security = RSI_WPA_WPA2_MIXED;
  }
  if (wfx_rsi.sec.security == SME_WPA3) {
    // returning 3 for WPA3 when DGWIFI read security-type is called
    security = WPA3_SECURITY;
    wfx_rsi.sec.security = RSI_WPA3;
  }
  WFX_RSI_LOG("%s: WLAN: connecting to %s==%s, sec=%d, status=%02x", __func__,
              &wfx_rsi.sec.ssid[0], &wfx_rsi.sec.passkey[0],
              wfx_rsi.sec.security, status);
}
/*
 * Start an async Join command
 */
static void wfx_rsi_do_join(void) {
  int32_t status;

  if (wfx_rsi.dev_state &
      (WFX_RSI_ST_STA_CONNECTING | WFX_RSI_ST_STA_CONNECTED)) {
    WFX_RSI_LOG("%s: not joining - already in progress", __func__);
  } else {
    WFX_RSI_LOG("%s: WLAN: connecting to %s==%s, sec=%d", __func__,
                &wfx_rsi.sec.ssid[0], &wfx_rsi.sec.passkey[0],
                wfx_rsi.sec.security);
    /*
     * Join the network
     */
    /* TODO - make the WFX_SECURITY_xxx - same as RSI_xxx
     * Right now it's done by hand - we need something better
     */
    wfx_rsi.dev_state |= WFX_RSI_ST_STA_CONNECTING;
    while (((status = rsi_wlan_connect_async(
                 (int8_t *)&wfx_rsi.sec.ssid[0],
                 (rsi_security_mode_t)wfx_rsi.sec.security,
                 &wfx_rsi.sec.passkey[0], wfx_rsi_join_cb)) != RSI_SUCCESS) &&
           (++wfx_rsi.join_retries < WFX_RSI_CONFIG_MAX_JOIN)) {
      wfx_rsi.dev_state &= ~WFX_RSI_ST_STA_CONNECTING;
      WFX_RSI_LOG(
          "%s: rsi_wlan_connect_async failed with status: %02x on try %d",
          __func__, status, wfx_rsi.join_retries);
      vTaskDelay(4000);
      /* TODO - Start a timer.. to retry */
    }
    if (wfx_rsi.join_retries == 5) {
      WFX_RSI_LOG("Connect failed after %d tries", wfx_rsi.join_retries);
    } else {
      WFX_RSI_LOG("%s: starting JOIN to %s after %d tries\n", __func__,
                  (char *)&wfx_rsi.sec.ssid[0], wfx_rsi.join_retries);
    }
  }
}
/*
 * The main WLAN task - started by wfx_wifi_start () that interfaces with RSI.
 * The rest of RSI stuff come in call-backs.
 * The initialization has been already done.
 */
/* ARGSUSED */
void wfx_rsi_task(void *arg) {
  EventBits_t flags;
#ifndef RS911X_SOCKETS
  TickType_t last_dhcp_poll, now;
  struct netif *sta_netif;
#endif
  (void)arg;
  uint32_t rsi_status = wfx_rsi_init();
  if (rsi_status != RSI_SUCCESS) {
    WFX_RSI_LOG("%s: error: wfx_rsi_init with status: %02x", __func__,
                rsi_status);
    return;
  }
#ifndef RS911X_SOCKETS
  wfx_lwip_start();
  last_dhcp_poll = xTaskGetTickCount();
  sta_netif = wfx_get_netif(SL_WFX_STA_INTERFACE);
#endif
  wfx_started_notify();

  WFX_RSI_LOG("%s: starting event wait", __func__);
  for (;;) {
    /*
     * This is the main job of this task.
     * Wait for commands from the ConnectivityManager
     * Make state changes (based on call backs)
     */
    flags = xEventGroupWaitBits(
        wfx_rsi.events,
        WFX_EVT_STA_CONN | WFX_EVT_STA_DISCONN | WFX_EVT_STA_START_JOIN
#ifdef RS911X_SOCKETS
            | WFX_EVT_STA_DO_DHCP | WFX_EVT_STA_DHCP_DONE
#endif /* RS911X_SOCKETS */
#ifdef SL_WFX_CONFIG_SOFTAP
            | WFX_EVT_AP_START | WFX_EVT_AP_STOP
#endif /* SL_WFX_CONFIG_SOFTAP */
#ifdef SL_WFX_CONFIG_SCAN
            | WFX_EVT_SCAN
#endif /* SL_WFX_CONFIG_SCAN */
            | 0,
        pdTRUE,  /* Clear the bits */
        pdFALSE, /* Wait for any bit */
        pdMS_TO_TICKS(250));

    if (flags) {
      WFX_RSI_LOG("%s: wait event encountered: %x", __func__, flags);
    }
#ifdef RS911X_SOCKETS
    if (flags & WFX_EVT_STA_DO_DHCP) {
      /*
       * Do DHCP -
       */
      if ((status = rsi_config_ipaddress(
               RSI_IP_VERSION_4, RSI_DHCP | RSI_DHCP_UNICAST_OFFER, NULL, NULL,
               NULL, &wfx_rsi.ip4_addr[0], 4, 0)) != RSI_SUCCESS) {
        /* We should try this again.. (perhaps sleep) */
        /* TODO - Figure out what to do here */
      }
    }
#else /* !RS911X_SOCKET - using LWIP */
    /*
     * Let's handle DHCP polling here
     */
    if (wfx_rsi.dev_state & WFX_RSI_ST_STA_CONNECTED) {
      if ((now = xTaskGetTickCount()) > (last_dhcp_poll + pdMS_TO_TICKS(250))) {
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
        uint8_t dhcp_state = dhcpclient_poll(sta_netif);
        if (dhcp_state == DHCP_ADDRESS_ASSIGNED && !hasNotifiedIPV4) {
          wfx_dhcp_got_ipv4((uint32_t)sta_netif->ip_addr.u_addr.ip4.addr);
          hasNotifiedIPV4 = true;
          if (!hasNotifiedWifiConnectivity) {
            wfx_connected_notify(0, &wfx_rsi.ap_mac);
            hasNotifiedWifiConnectivity = true;
          }
        } else if (dhcp_state == DHCP_OFF) {
          wfx_ip_changed_notify(0);
          hasNotifiedIPV4 = false;
        }
#endif /* CHIP_DEVICE_CONFIG_ENABLE_IPV4 */
        if ((ip6_addr_ispreferred(netif_ip6_addr_state(sta_netif, 0))) &&
            !hasNotifiedIPV6) {
          wfx_ipv6_notify(1);
          hasNotifiedIPV6 = true;
          if (!hasNotifiedWifiConnectivity) {
            wfx_connected_notify(0, &wfx_rsi.ap_mac);
            hasNotifiedWifiConnectivity = true;
          }
        }
        last_dhcp_poll = now;
      }
    }
#endif /* RS911X_SOCKETS */
    if (flags & WFX_EVT_STA_START_JOIN) {
      // saving the AP related info
      wfx_rsi_save_ap_info();
      // Joining to the network
      wfx_rsi_do_join();
    }
    if (flags & WFX_EVT_STA_CONN) {
      /*
       * Initiate the Join command (assuming we have been provisioned)
       */
      WFX_RSI_LOG("%s: starting LwIP STA", __func__);
      wfx_rsi.dev_state |= WFX_RSI_ST_STA_CONNECTED;
#ifndef RS911X_SOCKETS
      hasNotifiedWifiConnectivity = false;
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
      hasNotifiedIPV4 = false;
#endif // CHIP_DEVICE_CONFIG_ENABLE_IPV4
      hasNotifiedIPV6 = false;
      wfx_lwip_set_sta_link_up();
#endif /* !RS911X_SOCKETS */
      /* We need to get AP Mac - TODO */
      // Uncomment once the hook into MATTER is moved to IP connectivty instead
      // of AP connectivity. wfx_connected_notify(0, &wfx_rsi.ap_mac); // This
      // is independant of IP connectivity.
    }
    if (flags & WFX_EVT_STA_DISCONN) {
      wfx_rsi.dev_state &=
          ~(WFX_RSI_ST_STA_READY | WFX_RSI_ST_STA_CONNECTING |
            WFX_RSI_ST_STA_CONNECTED | WFX_RSI_ST_STA_DHCP_DONE);
      WFX_RSI_LOG("%s: disconnect notify", __func__);
      /* TODO: Implement disconnect notify */
#ifndef RS911X_SOCKETS
      wfx_lwip_set_sta_link_down(); // Internally dhcpclient_poll(netif) ->
                                    // wfx_ip_changed_notify(0) for IPV4
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
      wfx_ip_changed_notify(0);
      hasNotifiedIPV4 = false;
#endif /* CHIP_DEVICE_CONFIG_ENABLE_IPV4 */
      wfx_ipv6_notify(0);
      hasNotifiedIPV6 = false;
      hasNotifiedWifiConnectivity = false;
#endif /* !RS911X_SOCKETS */
    }
#ifdef SL_WFX_CONFIG_SCAN
    if (flags & WFX_EVT_SCAN) {
      if (!(wfx_rsi.dev_state & WFX_RSI_ST_SCANSTARTED)) {
        WFX_RSI_LOG("%s: start SSID scan", __func__);
        int x;
        wfx_wifi_scan_result_t ap;
        rsi_scan_info_t *scan;
        int32_t status;
        uint8_t bgscan_results[500] = {0};
        status =
            rsi_wlan_bgscan_profile(1, (rsi_rsp_scan_t *)bgscan_results, 500);

        WFX_RSI_LOG("%s: status: %02x size = %d", __func__, status, 500);
        rsi_rsp_scan_t *rsp = (rsi_rsp_scan_t *)bgscan_results;
        if (status) {
          /*
           * Scan is done - failed
           */
        } else
          for (x = 0; x < rsp->scan_count[0]; x++) {
            scan = &rsp->scan_info[x];
            strcpy(&ap.ssid[0], (char *)&scan->ssid[0]);
            if (wfx_rsi.scan_ssid) {
              WFX_RSI_LOG("Inside scan_ssid");
              WFX_RSI_LOG("SCAN SSID: %s , ap scan: %s", wfx_rsi.scan_ssid,
                          ap.ssid);
              if (strcmp(wfx_rsi.scan_ssid, ap.ssid) == 0) {
                WFX_RSI_LOG("Inside ap details");
                ap.security = scan->security_mode;
                ap.rssi = (-1) * scan->rssi_val;
                memcpy(&ap.bssid[0], &scan->bssid[0], 6);
                (*wfx_rsi.scan_cb)(&ap);
              }
            } else {
              WFX_RSI_LOG("Inside else");
              ap.security = scan->security_mode;
              ap.rssi = (-1) * scan->rssi_val;
              memcpy(&ap.bssid[0], &scan->bssid[0], 6);
              (*wfx_rsi.scan_cb)(&ap);
            }
          }
        wfx_rsi.dev_state &= ~WFX_RSI_ST_SCANSTARTED;
        /* Terminate with end of scan which is no ap sent back */
        (*wfx_rsi.scan_cb)((wfx_wifi_scan_result_t *)0);
        wfx_rsi.scan_cb = (void (*)(wfx_wifi_scan_result_t *))0;

        if (wfx_rsi.scan_ssid) {
          vPortFree(wfx_rsi.scan_ssid);
          wfx_rsi.scan_ssid = (char *)0;
        }
      }
    }
#endif /* SL_WFX_CONFIG_SCAN */
#ifdef SL_WFX_CONFIG_SOFTAP
    /* TODO */
    if (flags & WFX_EVT_AP_START) {
    }
    if (flags & WFX_EVT_AP_STOP) {
    }
#endif /* SL_WFX_CONFIG_SOFTAP */
  }
}
void wfx_dhcp_got_ipv4(uint32_t ip) {
  /*
   * Acquire the new IP address
   */
  wfx_rsi.ip4_addr[0] = (ip)&0xff;
  wfx_rsi.ip4_addr[1] = (ip >> 8) & 0xff;
  wfx_rsi.ip4_addr[2] = (ip >> 16) & 0xff;
  wfx_rsi.ip4_addr[3] = (ip >> 24) & 0xff;
  WFX_RSI_LOG("%s: DHCP OK: IP=%d.%d.%d.%d", __func__, wfx_rsi.ip4_addr[0],
              wfx_rsi.ip4_addr[1], wfx_rsi.ip4_addr[2], wfx_rsi.ip4_addr[3]);
  /* Notify the Connectivity Manager - via the app */
  wfx_ip_changed_notify(1);
  wfx_rsi.dev_state |= WFX_RSI_ST_STA_READY;
}
/*
 * WARNING - Taken from RSI and broken up
 * This is my own RSI stuff for not copying code and allocating an extra
 * level of indirection - when using LWIP buffers
 * see also: int32_t rsi_wlan_send_data_xx(uint8_t *buffer, uint32_t length)
 */
void *wfx_rsi_alloc_pkt() {
  rsi_pkt_t *pkt;
  // Allocate packet to send data
  if ((pkt = rsi_pkt_alloc(&rsi_driver_cb->wlan_cb->wlan_tx_pool)) == NULL) {
    return (void *)0;
  }

  return (void *)pkt;
}
void wfx_rsi_pkt_add_data(void *p, uint8_t *buf, uint16_t len, uint16_t off) {
  rsi_pkt_t *pkt;

  pkt = (rsi_pkt_t *)p;
  memcpy(((char *)pkt->data) + off, buf, len);
}
int32_t wfx_rsi_send_data(void *p, uint16_t len) {
  int32_t status;
  register uint8_t *host_desc;
  rsi_pkt_t *pkt;

  pkt = (rsi_pkt_t *)p;
  host_desc = pkt->desc;
  memset(host_desc, 0, RSI_HOST_DESC_LENGTH);
  rsi_uint16_to_2bytes(host_desc, (len & 0xFFF));

  // Fill packet type
  host_desc[1] |= (RSI_WLAN_DATA_Q << 4);
  host_desc[2] |= 0x01;

  rsi_enqueue_pkt(&rsi_driver_cb->wlan_tx_q, pkt);

#ifndef RSI_SEND_SEM_BITMAP
  rsi_driver_cb_non_rom->send_wait_bitmap |= BIT(0);
#endif
  // Set TX packet pending event
  rsi_set_event(RSI_TX_EVENT);

  if (rsi_wait_on_wlan_semaphore(&rsi_driver_cb_non_rom->send_data_sem,
                                 RSI_SEND_DATA_RESPONSE_WAIT_TIME) !=
      RSI_ERROR_NONE) {
    return RSI_ERROR_RESPONSE_TIMEOUT;
  }
  status = rsi_wlan_get_status();

  return status;
}
struct wfx_rsi wfx_rsi;
