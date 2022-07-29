/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/***************************************************************************
 * @file
 * @brief WFX FMAC driver main bus communication task
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc.
 *www.silabs.com</b>
 *******************************************************************************
 *
 * Licensed under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in
 *compliance with the License. You may obtain a copy
 *of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in
 *writing, software distributed under the License is
 *distributed on an "AS IS" BASIS, WITHOUT WARRANTIES
 *OR CONDITIONS OF ANY KIND, either express or
 *implied. See the License for the specific language
 *governing permissions and limitations under the
 *License.
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "em_bus.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_ldma.h"
#include "em_usart.h"
#include "gpiointerrupt.h"

#include "wifi_config.h"

#include "AppConfig.h"
#include "sl_wfx_host.h"
#include "wfx_host_events.h"
#include "sl_wfx_board.h"
#include "sl_wfx_task.h"

#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"

#include "dhcp_client.h"
#include "ethernetif.h"
#include <platform/CHIPDeviceLayer.h>

using namespace ::chip;
using namespace ::chip::DeviceLayer;

EventGroupHandle_t sl_wfx_event_group;
TaskHandle_t wfx_events_task_handle;
static sl_wfx_mac_address_t ap_mac;
static uint32_t sta_ip;

// wfx_fmac_driver context
sl_wfx_context_t wifiContext;
static uint8_t wifi_extra;
#define WE_ST_STARTED    1
#define WE_ST_STA_CONN   2
#define WE_ST_HW_STARTED 4

#ifdef SL_WFX_CONFIG_SOFTAP
// Connection parameters
char softap_ssid[32]                   = SOFTAP_SSID_DEFAULT;
char softap_passkey[64]                = SOFTAP_PASSKEY_DEFAULT;
sl_wfx_security_mode_t softap_security = SOFTAP_SECURITY_DEFAULT;
uint8_t softap_channel                 = SOFTAP_CHANNEL_DEFAULT;
#endif

/* station network interface structures */
struct netif *sta_netif;
wfx_wifi_provision_t wifi_provision;

bool hasNotifiedIPV6 = false;
bool hasNotifiedIPV4 = false;
bool hasNotifiedWifiConnectivity = false;
static uint8_t retryJoin = 0;
bool retryInProgress = false;

#ifdef SL_WFX_CONFIG_SCAN
static struct scan_result_holder {
  struct scan_result_holder *next;
  wfx_wifi_scan_result scan;
} * scan_save;
static uint8_t scan_count = 0;
static void (*scan_cb)(wfx_wifi_scan_result_t *); /* user-callback - when scan is done */
static char *scan_ssid;                           /* Which one are we scanning for */
static void sl_wfx_scan_result_callback(sl_wfx_scan_result_ind_body_t *scan_result);
static void sl_wfx_scan_complete_callback(uint32_t status);
#endif /* SL_WFX_CONFIG_SCAN */

static void wfx_events_task(void *p_arg);

/* WF200 host callbacks */
static void sl_wfx_connect_callback(uint8_t *mac, uint32_t status);
static void sl_wfx_disconnect_callback(uint8_t *mac, uint16_t reason);
static void sl_wfx_generic_status_callback(sl_wfx_generic_ind_t *frame);

#ifdef SL_WFX_CONFIG_SOFTAP
static void sl_wfx_start_ap_callback(uint32_t status);
static void sl_wfx_stop_ap_callback(void);
static void sl_wfx_client_connected_callback(uint8_t *mac);
static void sl_wfx_ap_client_disconnected_callback(uint32_t status, uint8_t *mac);
static void sl_wfx_ap_client_rejected_callback(uint32_t status, uint8_t *mac);
#endif

/***************************************************************************
 * Creates WFX events processing task.
 ******************************************************************************/
static void wfx_events_task_start()
{
  /* create an event group to track Wi-Fi events */
  sl_wfx_event_group = xEventGroupCreate();

  if (xTaskCreate(wfx_events_task, "wfx_events", 1024, NULL, 1, &wfx_events_task_handle) != pdPASS) {
    EFR32_LOG("Failed to create WFX wfx_events");
  }
}

/****************************************************************************
 * Called when the driver needs to post an event
 *
 * @returns Returns SL_STATUS_OK if successful,
 *SL_STATUS_FAIL otherwise
 *****************************************************************************/
sl_status_t sl_wfx_host_process_event(sl_wfx_generic_message_t *event_payload)
{
  switch (event_payload->header.id) {
    /******** INDICATION ********/
    case SL_WFX_STARTUP_IND_ID: {
      EFR32_LOG("WFX Startup Completed\r\n");
      PlatformMgrImpl().HandleWFXSystemEvent(WIFI_EVENT, event_payload);
      break;
    }
    case SL_WFX_CONNECT_IND_ID: {
      sl_wfx_connect_ind_t *connect_indication = (sl_wfx_connect_ind_t *)event_payload;
      sl_wfx_connect_callback(connect_indication->body.mac, connect_indication->body.status);
      break;
    }
    case SL_WFX_DISCONNECT_IND_ID: {
      sl_wfx_disconnect_ind_t *disconnect_indication = (sl_wfx_disconnect_ind_t *)event_payload;
      sl_wfx_disconnect_callback(disconnect_indication->body.mac, disconnect_indication->body.reason);
      break;
    }
    case SL_WFX_RECEIVED_IND_ID: {
      sl_wfx_received_ind_t *ethernet_frame = (sl_wfx_received_ind_t *)event_payload;
      if (ethernet_frame->body.frame_type == 0) {
        sl_wfx_host_received_frame_callback(ethernet_frame);
      }
      break;
    }
#ifdef SL_WFX_CONFIG_SCAN
    case SL_WFX_SCAN_RESULT_IND_ID: {
      sl_wfx_scan_result_ind_t *scan_result = (sl_wfx_scan_result_ind_t *)event_payload;
      sl_wfx_scan_result_callback(&scan_result->body);
      break;
    }
    case SL_WFX_SCAN_COMPLETE_IND_ID: {
      sl_wfx_scan_complete_ind_t *scan_complete = (sl_wfx_scan_complete_ind_t *)event_payload;
      sl_wfx_scan_complete_callback(scan_complete->body.status);
      break;
    }
#endif /* SL_WFX_CONFIG_SCAN */
#ifdef SL_WFX_CONFIG_SOFTAP
    case SL_WFX_START_AP_IND_ID: {
      sl_wfx_start_ap_ind_t *start_ap_indication = (sl_wfx_start_ap_ind_t *)event_payload;
      sl_wfx_start_ap_callback(start_ap_indication->body.status);
      break;
    }
    case SL_WFX_STOP_AP_IND_ID: {
      sl_wfx_stop_ap_callback();
      break;
    }
    case SL_WFX_AP_CLIENT_CONNECTED_IND_ID: {
      sl_wfx_ap_client_connected_ind_t *client_connected_indication = (sl_wfx_ap_client_connected_ind_t *)event_payload;
      sl_wfx_client_connected_callback(client_connected_indication->body.mac);
      break;
    }
    case SL_WFX_AP_CLIENT_REJECTED_IND_ID: {
      sl_wfx_ap_client_rejected_ind_t *ap_client_rejected_indication = (sl_wfx_ap_client_rejected_ind_t *)event_payload;
      sl_wfx_ap_client_rejected_callback(ap_client_rejected_indication->body.reason,
                                         ap_client_rejected_indication->body.mac);
      break;
    }
    case SL_WFX_AP_CLIENT_DISCONNECTED_IND_ID: {
      sl_wfx_ap_client_disconnected_ind_t *ap_client_disconnected_indication =
        (sl_wfx_ap_client_disconnected_ind_t *)event_payload;
      sl_wfx_ap_client_disconnected_callback(ap_client_disconnected_indication->body.reason,
                                             ap_client_disconnected_indication->body.mac);
      break;
    }
#endif /* SL_WFX_CONFIG_SOFTAP */
#ifdef SL_WFX_USE_SECURE_LINK
    case SL_WFX_SECURELINK_EXCHANGE_PUB_KEYS_IND_ID: {
      if (host_context.waited_event_id != SL_WFX_SECURELINK_EXCHANGE_PUB_KEYS_IND_ID) {
        memcpy((void *)&sl_wfx_context->secure_link_exchange_ind, (void *)event_payload, event_payload->header.length);
      }
      break;
    }
#endif
    case SL_WFX_GENERIC_IND_ID: {
      sl_wfx_generic_ind_t *generic_status = (sl_wfx_generic_ind_t *)event_payload;
      sl_wfx_generic_status_callback(generic_status);
      break;
    }
    case SL_WFX_EXCEPTION_IND_ID: {
      sl_wfx_exception_ind_t *firmware_exception = (sl_wfx_exception_ind_t *)event_payload;
      uint8_t *exception_tmp                     = (uint8_t *)firmware_exception;
      EFR32_LOG("firmware exception\r\n");
      for (uint16_t i = 0; i < firmware_exception->header.length; i += 16) {
        EFR32_LOG("hif: %.8x:", i);
        for (uint8_t j = 0; (j < 16) && ((i + j) < firmware_exception->header.length); j++) {
          EFR32_LOG(" %.2x", *exception_tmp);
          exception_tmp++;
        }
        EFR32_LOG("\r\n");
      }
      break;
    }
    case SL_WFX_ERROR_IND_ID: {
      sl_wfx_error_ind_t *firmware_error = (sl_wfx_error_ind_t *)event_payload;
      uint8_t *error_tmp                 = (uint8_t *)firmware_error;
      EFR32_LOG("firmware error %lu\r\n", firmware_error->body.type);
      for (uint16_t i = 0; i < firmware_error->header.length; i += 16) {
        EFR32_LOG("hif: %.8x:", i);
        for (uint8_t j = 0; (j < 16) && ((i + j) < firmware_error->header.length); j++) {
          EFR32_LOG(" %.2x", *error_tmp);
          error_tmp++;
        }
        EFR32_LOG("\r\n");
      }
      break;
    }
  }

  return SL_STATUS_OK;
}

#ifdef SL_WFX_CONFIG_SCAN
/****************************************************************************
 * Callback for individual scan result
 *****************************************************************************/
static void sl_wfx_scan_result_callback(sl_wfx_scan_result_ind_body_t *scan_result)
{
  struct scan_result_holder *ap;

  EFR32_LOG("# %2d %2d  %03d %02X:%02X:%02X:%02X:%02X:%02X  %s",
            scan_count,
            scan_result->channel,
            ((int16_t)(scan_result->rcpi - 220) / 2),
            scan_result->mac[0],
            scan_result->mac[1],
            scan_result->mac[2],
            scan_result->mac[3],
            scan_result->mac[4],
            scan_result->mac[5],
            scan_result->ssid_def.ssid);
  /*Report one AP information*/
  EFR32_LOG("\r\n");
  /* don't save if filter only wants specific ssid */
  if (scan_ssid != (char *)0) {
    if (strcmp(scan_ssid, (char *)&scan_result->ssid_def.ssid[0]) != 0)
      return;
  }
  if ((ap = (struct scan_result_holder *)pvPortMalloc(sizeof(*ap))) == (struct scan_result_holder *)0) {
    EFR32_LOG("*ERR*Scan: No Mem");
  } else {
    ap->next  = scan_save;
    scan_save = ap;
    /* Not checking if scan_result->ssid_length is < 33 */
    memcpy(ap->scan.ssid, scan_result->ssid_def.ssid, scan_result->ssid_def.ssid_length);
    ap->scan.ssid[scan_result->ssid_def.ssid_length] = 0; /* make sure about null terminate */
    /* We do it in this order WPA3 first */
    /* No EAP supported - Is this required */
    if (scan_result->security_mode.wpa3) {
      ap->scan.security = WFX_SEC_WPA3;
    } else if (scan_result->security_mode.wpa2) {
      ap->scan.security = WFX_SEC_WPA2;
    } else if (scan_result->security_mode.wpa) {
      ap->scan.security = WFX_SEC_WPA;
    } else if (scan_result->security_mode.wep) {
      ap->scan.security = WFX_SEC_WEP;
    } else {
      ap->scan.security = WFX_SEC_NONE;
    }
    ap->scan.chan = scan_result->channel;
    ap->scan.rssi = scan_result->rcpi;
    memcpy(&ap->scan.bssid[0], &scan_result->mac[0], 6);
    scan_count++;
  }
}

/****************************************************************************
 * Callback for scan complete
 *****************************************************************************/
/* ARGSUSED */
static void sl_wfx_scan_complete_callback(uint32_t status)
{
  (void)(status);
  /* Use scan_count value and reset it */
  xEventGroupSetBits(sl_wfx_event_group, SL_WFX_SCAN_COMPLETE);
}
#endif /* SL_WFX_CONFIG_SCAN */

/****************************************************************************
 * Callback when station connects
 *****************************************************************************/
static void sl_wfx_connect_callback(uint8_t *mac, uint32_t status)
{
  (void)(mac);
  switch (status) {
    case WFM_STATUS_SUCCESS: {
      EFR32_LOG("STA-Connected\r\n");
      memcpy(&ap_mac.octet[0], mac, 6);
      sl_wfx_context->state = static_cast<sl_wfx_state_t>(static_cast<int>(sl_wfx_context->state)
                                                          | static_cast<int>(SL_WFX_STA_INTERFACE_CONNECTED));
      xEventGroupSetBits(sl_wfx_event_group, SL_WFX_CONNECT);
      break;
    }
    case WFM_STATUS_NO_MATCHING_AP: {
      EFR32_LOG("WFX Connection failed, access point not found\r\n");
      break;
    }
    case WFM_STATUS_CONNECTION_ABORTED: {
      EFR32_LOG("WFX Connection aborted\r\n");
      break;
    }
    case WFM_STATUS_CONNECTION_TIMEOUT: {
      EFR32_LOG("WFX Connection timeout\r\n");
      break;
    }
    case WFM_STATUS_CONNECTION_REJECTED_BY_AP: {
      EFR32_LOG("WFX Connection rejected by the access point\r\n");
      break;
    }
    case WFM_STATUS_CONNECTION_AUTH_FAILURE: {
      EFR32_LOG("WFX Connection authentication failure\r\n");
      break;
    }
    default: {
      EFR32_LOG("WF Connection attempt error\r\n");
    }
  }

      if ( (status != WFM_STATUS_SUCCESS) && retryJoin < 5) {
        retryJoin += 1;
        retryInProgress = false;
        EFR32_LOG("WFX Retry to connect to network count: %d",retryJoin);
        sl_wfx_context->state = static_cast<sl_wfx_state_t>(static_cast<int>(sl_wfx_context->state)
                                                      & ~static_cast<int>(SL_WFX_STARTED));
        xEventGroupSetBits(sl_wfx_event_group, SL_WFX_RETRY_CONNECT);
    }
}

/****************************************************************************
 * Callback for station disconnect
 *****************************************************************************/
static void sl_wfx_disconnect_callback(uint8_t *mac, uint16_t reason)
{
  (void)(mac);
  EFR32_LOG("WFX Disconnected %d\r\n", reason);
  sl_wfx_context->state = static_cast<sl_wfx_state_t>(static_cast<int>(sl_wfx_context->state)
                                                      & ~static_cast<int>(SL_WFX_STA_INTERFACE_CONNECTED));
  xEventGroupSetBits(sl_wfx_event_group, SL_WFX_DISCONNECT);
}

#ifdef SL_WFX_CONFIG_SOFTAP
/****************************************************************************
 * Callback for AP started
 *****************************************************************************/
static void sl_wfx_start_ap_callback(uint32_t status)
{
  if (status == 0) {
    EFR32_LOG("AP started\r\n");
    sl_wfx_context->state =
      static_cast<sl_wfx_state_t>(static_cast<int>(sl_wfx_context->state) | static_cast<int>(SL_WFX_AP_INTERFACE_UP));
    xEventGroupSetBits(sl_wfx_event_group, SL_WFX_START_AP);
  } else {
    EFR32_LOG("AP start failed\r\n");
    strcpy(event_log, "AP start failed");
  }
}

/****************************************************************************
 * Callback for AP stopped
 *****************************************************************************/
static void sl_wfx_stop_ap_callback(void)
{
  // TODO
  // dhcpserver_clear_stored_mac();
  EFR32_LOG("SoftAP stopped\r\n");
  sl_wfx_context->state =
    static_cast<sl_wfx_state_t>(static_cast<int>(sl_wfx_context->state) & ~static_cast<int>(SL_WFX_AP_INTERFACE_UP));
  xEventGroupSetBits(sl_wfx_event_group, SL_WFX_STOP_AP);
}

/****************************************************************************
 * Callback for client connect to AP
 *****************************************************************************/
static void sl_wfx_client_connected_callback(uint8_t *mac)
{
  EFR32_LOG("Client connected, MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  // TODO
  // EFR32_LOG("Open a web browser and go to http://%d.%d.%d.%d\r\n", ap_ip_addr0, ap_ip_addr1, ap_ip_addr2, ap_ip_addr3);
}

/****************************************************************************
 * Callback for client rejected from AP
 *****************************************************************************/
static void sl_wfx_ap_client_rejected_callback(uint32_t status, uint8_t *mac)
{
  // struct eth_addr mac_addr;
  // memcpy(&mac_addr, mac, SL_WFX_BSSID_SIZE);
  // TODO
  // dhcpserver_remove_mac(&mac_addr);
  EFR32_LOG("Client rejected, reason: %d, MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
            (int)status,
            mac[0],
            mac[1],
            mac[2],
            mac[3],
            mac[4],
            mac[5]);
}

/****************************************************************************
 * Callback for AP client disconnect
 *****************************************************************************/
static void sl_wfx_ap_client_disconnected_callback(uint32_t status, uint8_t *mac)
{
  // TODO
  // struct eth_addr mac_addr;
  // memcpy(&mac_addr, mac, SL_WFX_BSSID_SIZE);
  // dhcpserver_remove_mac(&mac_addr);
  EFR32_LOG("Client disconnected, reason: %d, MAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
            (int)status,
            mac[0],
            mac[1],
            mac[2],
            mac[3],
            mac[4],
            mac[5]);
}
#endif /* SL_WFX_CONFIG_SOFTAP */

/****************************************************************************
 * Callback for generic status received
 *****************************************************************************/
static void sl_wfx_generic_status_callback(sl_wfx_generic_ind_t *frame)
{
  (void)(frame);
  EFR32_LOG("WFX Generic status received\r\n");
}

/***************************************************************************
 * WFX events processing task.
 ******************************************************************************/
static void wfx_events_task(void *p_arg)
{
  TickType_t last_dhcp_poll, now;
  EventBits_t flags;
  (void)p_arg;
  
  sta_netif            = wfx_get_netif(SL_WFX_STA_INTERFACE);
  last_dhcp_poll = xTaskGetTickCount();
  while (1) {
    flags = xEventGroupWaitBits(sl_wfx_event_group,
                                SL_WFX_CONNECT | SL_WFX_DISCONNECT
#ifdef SL_WFX_CONFIG_SOFTAP
                                  | SL_WFX_START_AP | SL_WFX_STOP_AP
#endif /* SL_WFX_CONFIG_SOFTAP */
#ifdef SL_WFX_CONFIG_SCAN
                                  | SL_WFX_SCAN_START | SL_WFX_SCAN_COMPLETE
#endif /* SL_WFX_CONFIG_SCAN */
                                  | 0,
                                pdTRUE,
                                pdFALSE,
                                pdMS_TO_TICKS(250));
    if (flags & SL_WFX_RETRY_CONNECT) {
        if (!retryInProgress) {
            EFR32_LOG("WFX sending the connect command");
            wfx_connect_to_ap();
            retryInProgress = true;
        }
    }

    if (wifi_extra & WE_ST_STA_CONN) {
      if ((now = xTaskGetTickCount()) > (last_dhcp_poll + pdMS_TO_TICKS(250))) {
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
         uint8_t dhcp_state = dhcpclient_poll(&sta_netif);

         if ((dhcp_state == DHCP_ADDRESS_ASSIGNED) && !hasNotifiedIPV4) {
            wfx_dhcp_got_ipv4 ((uint32_t)sta_netif->ip_addr.u_addr.ip4.addr);
            hasNotifiedIPV4 = true;
            if (!hasNotifiedWifiConnectivity) {
              EFR32_LOG ("WIFI: Has Notified Wifi Connectivity");
              wfx_connected_notify(0, &ap_mac);
              hasNotifiedWifiConnectivity = true;
            }
         } else if (dhcp_state == DHCP_OFF) {
            wfx_ip_changed_notify (0);
            hasNotifiedIPV4 = false;
         }
#endif // CHIP_DEVICE_CONFIG_ENABLE_IPV4
        if ((ip6_addr_ispreferred(netif_ip6_addr_state(sta_netif, 0))) && !hasNotifiedIPV6) {
          wfx_ipv6_notify(1);
          hasNotifiedIPV6 = true;
          if (!hasNotifiedWifiConnectivity) {
            wfx_connected_notify(0, &ap_mac);
            hasNotifiedWifiConnectivity = true;
          }
        }
        last_dhcp_poll = now;
      }
    }


    if (flags & SL_WFX_CONNECT) {
#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
      wfx_ip_changed_notify (0);
      hasNotifiedIPV4 = false;
#endif // CHIP_DEVICE_CONFIG_ENABLE_IPV4
      wfx_ipv6_notify (0);
      hasNotifiedIPV6 = false;
      hasNotifiedWifiConnectivity = false;
      EFR32_LOG("WIFI: Connected to AP");
      wifi_extra |= WE_ST_STA_CONN;
      wfx_lwip_set_sta_link_up();
#ifdef SLEEP_ENABLED
      if (!(wfx_get_wifi_state() & SL_WFX_AP_INTERFACE_UP)) {
        // Enable the power save
        sl_wfx_set_power_mode(WFM_PM_MODE_PS, WFM_PM_POLL_UAPSD, 1);
        sl_wfx_enable_device_power_save();
      }
#endif //SLEEP_ENABLED

    }

    if (flags & SL_WFX_DISCONNECT) {

#if (CHIP_DEVICE_CONFIG_ENABLE_IPV4)
      wfx_ip_changed_notify (0);
      hasNotifiedIPV4 = false;
#endif // CHIP_DEVICE_CONFIG_ENABLE_IPV4
      wfx_ipv6_notify(0);
      hasNotifiedIPV6 = false;
      hasNotifiedWifiConnectivity = false;
      wifi_extra &= ~WE_ST_STA_CONN;
      wfx_lwip_set_sta_link_down();
    }

#ifdef SL_WFX_CONFIG_SCAN
    if (flags & SL_WFX_SCAN_START) {
      /*
             * Start the Scan
             */
      sl_wfx_ssid_def_t ssid, *sp;
      uint16_t num_ssid, slen;
      if (scan_ssid) {
        memset(&ssid, 0, sizeof(ssid));
        slen = strlen(scan_ssid);
        memcpy(&ssid.ssid[0], scan_ssid, slen);
        ssid.ssid_length = slen;
        num_ssid         = 1;
        sp               = &ssid;
      } else {
        num_ssid = 0;
        sp       = (sl_wfx_ssid_def_t *)0;
      }
      (void)sl_wfx_send_scan_command(WFM_SCAN_MODE_ACTIVE,
                                     (const uint8_t *)0, /* Channel list */
                                     0,                  /* Scan all chans */
                                     sp,
                                     num_ssid,
                                     (const uint8_t *)0, /* IE we're looking for */
                                     0,
                                     (const uint8_t *)0);
    }
    if (flags & SL_WFX_SCAN_COMPLETE) {
      struct scan_result_holder *hp, *next;

      EFR32_LOG("WIFI: Return %d scan results", scan_count);
      for (hp = scan_save; hp; hp = next) {
        next = hp->next;
        (*scan_cb)(&hp->scan);
        vPortFree(hp);
      }
      (*scan_cb)((wfx_wifi_scan_result *)0);
      scan_save  = (struct scan_result_holder *)0;
      scan_count = 0;
      if (scan_ssid) {
        vPortFree(scan_ssid);
        scan_ssid = (char *)0;
      }
      /* Terminate scan */
      scan_cb = 0;
    }
#endif /* SL_WFX_CONFIG_SCAN */
  }
}

static sl_status_t wfx_init(void)
{
  /* Initialize the WF200 used by the two interfaces */
  wfx_events_task_start();
  sl_status_t status = sl_wfx_init(&wifiContext);
  EFR32_LOG("FMAC Driver version    %s", FMAC_DRIVER_VERSION_STRING);
  switch (status) {
    case SL_STATUS_OK:
      EFR32_LOG("WF200 FW ver:%d.%d.%d [MAC %02x:%02x:%02x-%02x:%02x:%02x]",
                wifiContext.firmware_major,
                wifiContext.firmware_minor,
                wifiContext.firmware_build,
                wifiContext.mac_addr_0.octet[0],
                wifiContext.mac_addr_0.octet[1],
                wifiContext.mac_addr_0.octet[2],
                wifiContext.mac_addr_0.octet[3],
                wifiContext.mac_addr_0.octet[4],
                wifiContext.mac_addr_0.octet[5]);
      EFR32_LOG("WF200 Init OK");

      if (wifiContext.state == SL_WFX_STA_INTERFACE_CONNECTED) {
        sl_wfx_send_disconnect_command();
      }

      break;
    case SL_STATUS_WIFI_INVALID_KEY:
      EFR32_LOG("*ERR*WF200: F/W keyset invalid");
      break;
    case SL_STATUS_WIFI_FIRMWARE_DOWNLOAD_TIMEOUT:
      EFR32_LOG("*ERR*WF200: F/W download timo");
      break;
    case SL_STATUS_TIMEOUT:
      EFR32_LOG("*ERR*WF200: Poll for value timo");
      break;
    case SL_STATUS_FAIL:
      EFR32_LOG("*ERR*WF200: Error");
      break;
    default:
      EFR32_LOG("*ERR*WF200: Unknown");
  }

  return status;
}

/*****************************************************************************
 * @brief
 *   tcp ip, wfx and lwip stack and start dhcp client.
 *
 * @param[in]
 *    not used
 *
 * @return
 *    sl_status_t Shows init succes or error.
 ******************************************************************************/
static void wfx_wifi_hw_start(void)
{
  sl_status_t status;

  if (wifi_extra & WE_ST_HW_STARTED)
    return;
  EFR32_LOG("STARTING WF200\n");
  wifi_extra |= WE_ST_HW_STARTED;

  sl_wfx_host_gpio_init();
  if ((status = wfx_init()) == SL_STATUS_OK) {
    /* Initialize the LwIP stack */
    EFR32_LOG("WF200:Start LWIP");
    wfx_lwip_start();
    wifiContext.state = SL_WFX_STARTED; /* Really this is a bit mask */
    EFR32_LOG("WF200:ready..");
  } else {
    EFR32_LOG("*ERR*WF200:init failed");
  }
}
/*
 * Get AP info
 */
int32_t wfx_get_ap_info(wfx_wifi_scan_result_t *ap){
  /* TODO */
  return -1;
}
int32_t wfx_get_ap_ext(wfx_wifi_scan_ext_t *extra_info){
  /* TODO */
  return -1;
}
int32_t wfx_reset_counts(){
  /* TODO */
  return -1;
}
/*
 * I think that this is getting called before FreeRTOS threads are ready
 */
sl_status_t wfx_wifi_start(void)
{
  if (wifi_extra & WE_ST_STARTED) {
    EFR32_LOG("WIFI: Already started");
    return SL_STATUS_OK;
  }
  wifi_extra |= WE_ST_STARTED;
  wfx_soft_init();
  wfx_wifi_hw_start();

  return SL_STATUS_OK;
}

sl_wfx_state_t wfx_get_wifi_state(void)
{
  return wifiContext.state;
}

struct netif *wfx_GetNetif(sl_wfx_interface_t interface)
{
  struct netif *SelectedNetif = NULL;
  if (interface == SL_WFX_STA_INTERFACE) {
    SelectedNetif = sta_netif;
  }
#ifdef SL_WFX_CONFIG_SOFTAP
  else if (interface == SL_WFX_SOFTAP_INTERFACE) {
    // no ap currently
  }
#endif
  return SelectedNetif;
}

sl_wfx_mac_address_t wfx_get_wifi_mac_addr(sl_wfx_interface_t interface)
{
  // return Mac address used by WFX SL_WFX_STA_INTERFACE or SL_WFX_SOFTAP_INTERFACE,
  return (interface == SL_WFX_STA_INTERFACE) ? wifiContext.mac_addr_0 : wifiContext.mac_addr_1;
}

void wfx_set_wifi_provision(wfx_wifi_provision_t *wifiConfig)
{
  memcpy(wifi_provision.ssid, wifiConfig->ssid, sizeof(wifiConfig->ssid));
  memcpy(wifi_provision.passkey, wifiConfig->passkey, sizeof(wifiConfig->passkey));
  EFR32_LOG("WIFI: Provision SSID=%s", &wifi_provision.ssid[0]);

  /* Not very good - To be improved */
  switch (wifiConfig->security) {
    case WFX_SEC_WPA:
      wifi_provision.security = static_cast<uint8_t>(sl_wfx_security_mode_e::WFM_SECURITY_MODE_WPA2_WPA1_PSK);
      break;
    case WFX_SEC_WPA3:
      wifi_provision.security = WFM_SECURITY_MODE_WPA3_SAE;
      break;
    case WFX_SEC_WPA2:
      wifi_provision.security = static_cast<uint8_t>(sl_wfx_security_mode_e::WFM_SECURITY_MODE_WPA2_WPA1_PSK);
      break;
    case WFX_SEC_WPA_WPA2_MIXED:
      wifi_provision.security = static_cast<uint8_t>(sl_wfx_security_mode_e::WFM_SECURITY_MODE_WPA2_WPA1_PSK);
      break;
    default:
      wifi_provision.security = WFM_SECURITY_MODE_WPA2_PSK;
      break;
  }
}

bool wfx_get_wifi_provision(wfx_wifi_provision_t *wifiConfig)
{
  if (wifiConfig == NULL) {
    return false;
  }
  memcpy(wifiConfig, &wifi_provision, sizeof(wfx_wifi_provision_t));

  return true;
}

void wfx_clear_wifi_provision(void)
{
  memset(&wifi_provision, 0, sizeof(wifi_provision));
}
bool wfx_is_sta_provisioned(void)
{
  return (wifi_provision.ssid[0]) ? true : false;
}
sl_status_t wfx_connect_to_ap(void)
{
  sl_status_t result;

  if (wifi_provision.ssid[0] == 0) {
    return SL_STATUS_NOT_AVAILABLE;
  }
  EFR32_LOG("WIFI:JOIN to %s", &wifi_provision.ssid[0]);
  result = sl_wfx_send_join_command((uint8_t *)wifi_provision.ssid,
                                    strlen(wifi_provision.ssid),
                                    NULL,
                                    0,
                                    static_cast<sl_wfx_security_mode_t>(wifi_provision.security),
                                    1,
                                    0,
                                    (uint8_t *)wifi_provision.passkey,
                                    strlen(wifi_provision.passkey),
                                    NULL,
                                    0);

  return result;
}
void wfx_get_wifi_mac_addr(sl_wfx_interface_t interface, sl_wfx_mac_address_t *addr)
{
  sl_wfx_mac_address_t *mac;

#ifdef SL_WFX_CONFIG_SOFTAP
  mac = (interface == SL_WFX_SOFTAP_INTERFACE) ? &wifiContext.mac_addr_1 : &wifiContext.mac_addr_0;
#else
  mac = &wifiContext.mac_addr_0;
#endif
  *addr = *mac;
  EFR32_LOG("WLAN:Get WiFi Mac addr %02x:%02x:%02x:%02x:%02x:%02x",
            mac->octet[0],
            mac->octet[1],
            mac->octet[2],
            mac->octet[3],
            mac->octet[4],
            mac->octet[5]);
}

bool wfx_have_ipv4_addr(sl_wfx_interface_t which_if)
{
  if (which_if == SL_WFX_STA_INTERFACE) {
    return (sta_ip == 0) ? false : true;
  } else {
    return false; /* TODO */
  }
}

bool
wfx_have_ipv6_addr (sl_wfx_interface_t which_if)
{
    EFR32_LOG ("%s: started.", __func__);
    bool status = false;
    if (which_if == SL_WFX_STA_INTERFACE) {
        status = wfx_is_sta_connected();
    } else {
        status = false; /* TODO */
    }
    EFR32_LOG ("%s: status: %d", __func__, status);
    return status;
}

sl_status_t wfx_sta_discon(void)
{
  EFR32_LOG("STA-Discon: TODO");
  /* TODO - Disconnect station mode from connected AP */

  return SL_STATUS_OK;
}
bool wfx_is_sta_mode_enabled(void)
{
  return true; /* It always is */
}
bool wfx_is_sta_connected(void)
{
  bool val;

  val = (wifi_extra & WE_ST_STA_CONN) ? true : false;

  EFR32_LOG("WLAN: STA %s connected", (val ? "IS" : "NOT"));

  return val;
}
void wfx_setup_ip6_link_local(sl_wfx_interface_t whichif)
{
  EFR32_LOG("Setup-IP6: TODO"); /* It is automatically done when lwip link up */
}

void wfx_enable_sta_mode(void)
{
  /* Nothing to do - default is that it is */
}
wifi_mode_t wfx_get_wifi_mode()
{
  if (wifiContext.state & SL_WFX_STARTED)
    return WIFI_MODE_STA;
  return WIFI_MODE_NULL;
}

/*
 * This is called from the context of AppTask
 * For WF200 - Start WIFI here
 */
bool wfx_hw_ready(void)
{
  return (wifiContext.state & SL_WFX_STARTED) ? true : false;
}
void wfx_dhcp_got_ipv4(uint32_t ip)
{
  /* Acquire the new IP address
         */
  sta_ip = ip;
  wfx_ip_changed_notify(1);
}

#ifdef SL_WFX_CONFIG_SCAN
bool wfx_start_scan(char *ssid, void (*callback)(wfx_wifi_scan_result_t *))
{
  int sz;

  if (scan_cb)
    return false; /* Already in progress */
  if (ssid) {
    sz = strlen(ssid);
    if ((scan_ssid = (char *)pvPortMalloc(sz + 1)) == (char *)0) {
      return false;
    }
    strcpy(scan_ssid, ssid);
  }
  scan_cb = callback;
  xEventGroupSetBits(sl_wfx_event_group, SL_WFX_SCAN_START);

  return true;
}
void wfx_cancel_scan(void)
{
  struct scan_result_holder *hp, *next;
  /* Not possible */
  if (!scan_cb) {
    return;
  }
  sl_wfx_send_stop_scan_command();
  for (hp = scan_save; hp; hp = next) {
    next = hp->next;
    vPortFree(hp);
  }
  scan_save  = (struct scan_result_holder *)0;
  scan_count = 0;
  if (scan_ssid) {
    vPortFree(scan_ssid);
    scan_ssid = (char *)0;
  }
  scan_cb = 0;
}
#endif /* SL_WFX_CONFIG_SCAN */
