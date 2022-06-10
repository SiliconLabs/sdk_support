/*
 * The interface in this file is used by WFXutils (and by ConnectivityManagerImpl.cpp)
 */
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
#include "wfx_rsi.h"

/*
 * Called from ConnectivityManagerImpl.cpp - to enable the device
 * Create the RSI task and let it deal with life.
 */
sl_status_t wfx_wifi_start(void)
{
  if (wfx_rsi.dev_state & WFX_RSI_ST_STARTED) {
    WFX_RSI_LOG("%s: already started.", __func__);
    return SL_STATUS_OK;
  }
  wfx_rsi.dev_state |= WFX_RSI_ST_STARTED;
  WFX_RSI_LOG("%s: starting..", __func__);
  /*
     * Create the driver task
     */
  if (xTaskCreate(wfx_rsi_task, "wfx_rsi", WFX_RSI_TASK_SZ, NULL, 1, &wfx_rsi.wlan_task) != pdPASS) {
    WFX_RSI_LOG("%s: error: failed to create task.", __func__);
    return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}
void wfx_enable_sta_mode(void)
{
  wfx_rsi.dev_state |= WFX_RSI_ST_STA_MODE;
}
bool wfx_is_sta_mode_enabled(void)
{
  bool mode;
  mode = !!(wfx_rsi.dev_state & WFX_RSI_ST_STA_MODE);

  // WFX_RSI_LOG("%s: %d", __func__, (mode ? "yes" : "no"));
  return mode;
}

sl_wfx_state_t wfx_get_wifi_state(void)
{
  if (wfx_rsi.dev_state & WFX_RSI_ST_STA_DHCP_DONE) {
    return SL_WFX_STA_INTERFACE_CONNECTED;
  }
  if (wfx_rsi.dev_state & WFX_RSI_ST_DEV_READY) {
    return SL_WFX_STARTED;
  }
  return SL_WFX_NOT_INIT;
}
void wfx_get_wifi_mac_addr(sl_wfx_interface_t interface, sl_wfx_mac_address_t *addr)
{
  sl_wfx_mac_address_t *mac;

#ifdef SL_WFX_CONFIG_SOFTAP
  mac = (interface == SL_WFX_SOFTAP_INTERFACE) ? &wfx_rsi.softap_mac : &wfx_rsi.sta_mac;
#else
  mac = &wfx_rsi.sta_mac;
#endif
  *addr = *mac;
  WFX_RSI_LOG("%s: %02x:%02x:%02x:%02x:%02x:%02x",
              __func__,
              mac->octet[0],
              mac->octet[1],
              mac->octet[2],
              mac->octet[3],
              mac->octet[4],
              mac->octet[5]);
}
void wfx_set_wifi_provision(wfx_wifi_provision_t *cfg)
{
  WFX_RSI_LOG("%s: SSID: %s", __func__, &wfx_rsi.sec.ssid[0]);

  wfx_rsi.sec = *cfg;
  wfx_rsi.dev_state |= WFX_RSI_ST_STA_PROVISIONED;
}
bool wfx_get_wifi_provision(wfx_wifi_provision_t *wifiConfig)
{
  if (wifiConfig != NULL) {
    if (wfx_rsi.dev_state & WFX_RSI_ST_STA_PROVISIONED) {
      *wifiConfig = wfx_rsi.sec;
      return true;
    }
  }
  return false;
}
bool wfx_is_sta_provisioned(void)
{
  bool status = (wfx_rsi.dev_state & WFX_RSI_ST_STA_PROVISIONED) ? true : false;
  WFX_RSI_LOG("%s: status: SSID -> %s: %s",
              __func__,
              &wfx_rsi.sec.ssid[0],
              (status ? "provisioned" : "not provisioned"));
  return status;
}
void wfx_clear_wifi_provision(void)
{
  memset(&wfx_rsi.sec, 0, sizeof(wfx_rsi.sec));
  wfx_rsi.dev_state &= ~WFX_RSI_ST_STA_PROVISIONED;
  WFX_RSI_LOG("%s: completed.", __func__);
}
/*
 * Start a JOIN command to the AP - Done by the wfx_rsi task
 */
sl_status_t wfx_connect_to_ap(void)
{
  if (wfx_rsi.dev_state & WFX_RSI_ST_STA_PROVISIONED) {
    WFX_RSI_LOG("%s: connecting to access point -> SSID: %s, PSK:%s",
                __func__,
                &wfx_rsi.sec.ssid[0],
                &wfx_rsi.sec.passkey[0]);
    xEventGroupSetBits(wfx_rsi.events, WFX_EVT_STA_START_JOIN);
  } else {
    WFX_RSI_LOG("%s: error: access point not provisioned", __func__);
    return SL_STATUS_INVALID_CONFIGURATION;
  }
  return SL_STATUS_OK;
}
void wfx_setup_ip6_link_local(sl_wfx_interface_t whichif)
{
  /*
   * TODO: Implement IPV6 setup, currently in wfx_rsi_task()
   * This is hooked with MATTER code.
   */
  WFX_RSI_LOG("%s: warning: not implemented.", __func__);
}

bool wfx_is_sta_connected(void)
{
  bool status;
  status = (wfx_rsi.dev_state & WFX_RSI_ST_STA_CONNECTED) ? true : false;
  WFX_RSI_LOG("%s: status: %s", __func__, (status ? "connected" : "not connected"));
  return status;
}

wifi_mode_t wfx_get_wifi_mode()
{
  if (wfx_rsi.dev_state & WFX_RSI_ST_DEV_READY)
    return WIFI_MODE_STA;
  return WIFI_MODE_NULL;
}
sl_status_t wfx_sta_discon(void)
{
  WFX_RSI_LOG("%s: started.", __func__);
  /* TODO - Disconnect station mode from connected AP */
  WFX_RSI_LOG("%s: completed.", __func__);
  return SL_STATUS_OK;
}
bool wfx_have_ipv4_addr(sl_wfx_interface_t which_if)
{
  bool status = false;
  if (which_if == SL_WFX_STA_INTERFACE) {
    status = (wfx_rsi.dev_state & WFX_RSI_ST_STA_DHCP_DONE) ? true : false;
  } else {
    status = false; /* TODO */
  }
  WFX_RSI_LOG("%s: status: %d", __func__, status);
  return status;
}
bool wfx_have_ipv6_addr(sl_wfx_interface_t which_if)
{
  bool status = false;
  if (which_if == SL_WFX_STA_INTERFACE) {
    status = (wfx_rsi.dev_state & WFX_RSI_ST_STA_CONNECTED) ? true : false;
  } else {
    status = false; /* TODO */
  }
  WFX_RSI_LOG("%s: status: %d", __func__, status);
  return status;
}
bool wfx_hw_ready(void)
{
  return (wfx_rsi.dev_state & WFX_RSI_ST_DEV_READY) ? true : false;
}

#ifdef SL_WFX_CONFIG_SCAN
bool wfx_start_scan(char *ssid, void (*callback)(wfx_wifi_scan_result_t *))
{
  int sz;

  if (wfx_rsi.scan_cb)
    return false; /* Already in progress */
  if (ssid) {
    sz = strlen(ssid);
    if ((wfx_rsi.scan_ssid = (char *)pvPortMalloc(sz + 1)) == (char *)0) {
      return false;
    }
    strcpy(wfx_rsi.scan_ssid, ssid);
  }
  wfx_rsi.scan_cb = callback;
  xEventGroupSetBits(wfx_rsi.events, WFX_EVT_SCAN);

  return true;
}
void wfx_cancel_scan(void)
{
  /* Not possible */
  WFX_RSI_LOG("%s: cannot cancel scan", __func__);
}
#endif /* SL_WFX_CONFIG_SCAN */
