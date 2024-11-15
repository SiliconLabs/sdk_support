/*
 * EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND
 * CONDITIONS OF THE CONTROLLING LICENSE AGREEMENT FOUND AT LICENSE.md
 * IN THIS SDK. IF YOU DO NOT AGREE TO THE LICENSE TERMS AND CONDITIONS,
 * PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.
 * (c) Copyright 2018, Silicon Laboratories Inc.  All rights reserved.
 */
#include "sl_net_for_lwip.h"
#include "sl_status.h"
#include "lwip/tcpip.h"
#include "lwip/etharp.h"
#include "lwip/dhcp.h"
#include "lwip/netif.h"
#include "lwip/netifapi.h"
#include "lwip/ethip6.h"
#include "lwip/ip6_addr.h"
#include "lwip/timeouts.h"
#include "cmsis_os2.h"
#include "sl_si91x_host_interface.h"
#include "sl_wifi.h"
#include "sl_utility.h"
#include "sl_wifi_callback_framework.h"
#include "sl_net_wifi_types.h"
#include "sl_net.h"
#include <string.h>
#include "sl_rsi_utility.h"

#define NETIF_IPV4_ADDRESS(X, Y) (uint8_t)(((X) >> (8 * Y)) & 0xFF)
#define MAC_48_BIT_SET           (1)
#define LWIP_FRAME_ALIGNMENT     60
#define STRUCT_PBUF              ((struct pbuf *)0)
#define INTERFACE_NAME_0         'w' ///< Network interface name 0
#define INTERFACE_NAME_1         'l' ///< Network interface name 1
#define MAX_TRANSFER_UNIT        1500
#define get_netif(i)             ((i & SL_WIFI_CLIENT_INTERFACE) ? &wifi_client_context->netif : &wifi_ap_context->netif)

sl_net_wifi_lwip_context_t *wifi_client_context = NULL;
sl_net_wifi_lwip_context_t *wifi_ap_context     = NULL;
uint32_t gOverrunCount                          = 0;

/******************************************************************************
                                Static Functions
******************************************************************************/
static void low_level_init(struct netif *netif)
{
  uint32_t status = 0;
  sl_mac_address_t mac_addr;

  // set netif MAC hardware address length
  netif->hwaddr_len = ETH_HWADDR_LEN;

  // Request MAC address
  status = sl_wifi_get_mac_address(SL_WIFI_CLIENT_INTERFACE, &mac_addr);
  if (status != SL_STATUS_OK) {
    SL_DEBUG_LOG("\r\n MAC address failed \r\n");
    return;
  }

  // set netif MAC hardware address
  netif->hwaddr[0] = mac_addr.octet[0];
  netif->hwaddr[1] = mac_addr.octet[1];
  netif->hwaddr[2] = mac_addr.octet[2];
  netif->hwaddr[3] = mac_addr.octet[3];
  netif->hwaddr[4] = mac_addr.octet[4];
  netif->hwaddr[5] = mac_addr.octet[5];

  // set netif maximum transfer unit
  netif->mtu = MAX_TRANSFER_UNIT;

  // Accept broadcast address and ARP traffic
  netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_IGMP;

  // Set netif link flag
  // netif->flags |= NETIF_FLAG_LINK_UP;

#if LWIP_IPV6_MLD
  netif->flags |= NETIF_FLAG_MLD6;
#endif /* LWIP_IPV6_MLD */
}

static void low_level_input(struct netif *netif, uint8_t *b, uint16_t len)
{
  struct pbuf *p, *q;
  uint32_t bufferoffset;

  if (len <= 0) {
    return;
  }

  if (len < LWIP_FRAME_ALIGNMENT) { /* 60 : LWIP frame alignment */
    len = LWIP_FRAME_ALIGNMENT;
  }

  // Drop packets originated from the same interface and is not destined for the said interface
  const uint8_t *src_mac = b + netif->hwaddr_len;
  const uint8_t *dst_mac = b;

#if LWIP_IPV6
  if (!(ip6_addr_ispreferred(netif_ip6_addr_state(netif, 0)))
      && (memcmp(netif->hwaddr, src_mac, netif->hwaddr_len) == 0)
      && (memcmp(netif->hwaddr, dst_mac, netif->hwaddr_len) != 0)) {
    SL_DEBUG_LOG("%s: DROP, [%02x:%02x:%02x:%02x:%02x:%02x]<-[%02x:%02x:%02x:%02x:%02x:%02x] type=%02x%02x",
                 __func__,
                 dst_mac[0],
                 dst_mac[1],
                 dst_mac[2],
                 dst_mac[3],
                 dst_mac[4],
                 dst_mac[5],
                 src_mac[0],
                 src_mac[1],
                 src_mac[2],
                 src_mac[3],
                 src_mac[4],
                 src_mac[5],
                 b[12],
                 b[13]);
    return;
  }
#endif

  /* We allocate a pbuf chain of pbufs from the Lwip buffer pool
   * and copy the data to the pbuf chain
   */
  if ((p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL)) != STRUCT_PBUF) {
    for (q = p, bufferoffset = 0; q != NULL; q = q->next) {
      memcpy((uint8_t *)q->payload, (uint8_t *)b + bufferoffset, q->len);
      bufferoffset += q->len;
    }

    SL_DEBUG_LOG("%s: ACCEPT %d, [%02x:%02x:%02x:%02x:%02x:%02x]<-[%02x:%02x:%02x:%02x:%02x:%02x] type=%02x%02x",
                 __func__,
                 bufferoffset,
                 dst_mac[0],
                 dst_mac[1],
                 dst_mac[2],
                 dst_mac[3],
                 dst_mac[4],
                 dst_mac[5],
                 src_mac[0],
                 src_mac[1],
                 src_mac[2],
                 src_mac[3],
                 src_mac[4],
                 src_mac[5],
                 b[12],
                 b[13]);

    if (netif->input(p, netif) != ERR_OK) {
      gOverrunCount++;
      pbuf_free(p);
    }
  } else {
    gOverrunCount++;
  }

  return;
}

static err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  UNUSED_PARAMETER(netif);
  sl_status_t status;

  status = sl_wifi_send_raw_data_frame(SL_WIFI_CLIENT_INTERFACE, (uint8_t *)p->payload, p->len);
  if (status != SL_STATUS_OK) {
    return ERR_IF;
  }
  return ERR_OK;
}

static err_t sta_ethernetif_init(struct netif *netif)
{
  LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip_sta";
#endif /* LWIP_NETIF_HOSTNAME */
  //! Set the netif name to identify the interface
  netif->name[0] = INTERFACE_NAME_0;
  netif->name[1] = INTERFACE_NAME_1;

  //! Assign handler/function for the interface
  // netif->input      = tcpip_input;
#if LWIP_IPV4 && LWIP_ARP
  netif->output = etharp_output;
#endif /* #if LWIP_IPV4 && LWIP_ARP */
#if LWIP_IPV6 && LWIP_ETHERNET
  netif->output_ip6 = ethip6_output;
#endif /* LWIP_IPV6 && LWIP_ETHERNET */
  netif->linkoutput = low_level_output;

  //! initialize the hardware
  low_level_init(netif);
  //  sta_netif = *netif;

  return ERR_OK;
}

static void sta_netif_config(void)
{
#if LWIP_IPV4
  ip_addr_t sta_ipaddr;
  ip_addr_t sta_netmask;
  ip_addr_t sta_gw;

  /* Initialize the Station information */
  ip_addr_set_zero_ip4(&sta_ipaddr);
  ip_addr_set_zero_ip4(&sta_netmask);
  ip_addr_set_zero_ip4(&sta_gw);
#endif /* LWIP_IPV4 */

  /* Add station interfaces */
  netif_add(&(wifi_client_context->netif),
#if LWIP_IPV4
            (const ip4_addr_t *)&sta_ipaddr,
            (const ip4_addr_t *)&sta_netmask,
            (const ip4_addr_t *)&sta_gw,
#endif /* LWIP_IPV4 */
            NULL,
            &sta_ethernetif_init,
            &tcpip_input);

  /* Registers the default network interface */
  netif_set_default(&(wifi_client_context->netif));
}

static void set_sta_link_up(sl_net_wifi_client_profile_t *profile)
{
#if LWIP_IPV4
  if (SL_IP_MANAGEMENT_STATIC_IP == profile->ip.mode) {
    ip4_addr_t ipaddr  = { 0 };
    ip4_addr_t gateway = { 0 };
    ip4_addr_t netmask = { 0 };
    uint8_t *address   = &(profile->ip.ip.v4.ip_address.bytes[0]);

    IP4_ADDR(&ipaddr, address[0], address[1], address[2], address[3]);
    address = &(profile->ip.ip.v4.gateway.bytes[0]);
    IP4_ADDR(&gateway, address[0], address[1], address[2], address[3]);
    address = &(profile->ip.ip.v4.netmask.bytes[0]);
    IP4_ADDR(&netmask, address[0], address[1], address[2], address[3]);

    netifapi_netif_set_addr(&(wifi_client_context->netif), &ipaddr, &netmask, &gateway);
  }
#endif

  netifapi_netif_set_up(&(wifi_client_context->netif));
  netifapi_netif_set_link_up(&(wifi_client_context->netif));

  if (SL_IP_MANAGEMENT_DHCP == profile->ip.mode) {
#if LWIP_IPV4 && LWIP_DHCP
    ip_addr_set_zero_ip4(&(wifi_client_context->netif.ip_addr));
    ip_addr_set_zero_ip4(&(wifi_client_context->netif.netmask));
    ip_addr_set_zero_ip4(&(wifi_client_context->netif.gw));
    dhcp_start(&(wifi_client_context->netif));

    //! Wait for DHCP to acquire IP Address
    while (!dhcp_supplied_address(&(wifi_client_context->netif))) {
      osDelay(100);
    }
#endif /* LWIP_IPV4 && LWIP_DHCP */
    /*
       * Enable IPV6
       */
  }

#if LWIP_IPV4
  uint64_t addr = wifi_client_context->netif.ip_addr.addr;
#endif
#if LWIP_IPV6
  // uint64_t addr = wifi_client_context->netif.ip_addr.u_addr.ip4.addr;
#endif
#if LWIP_IPV4
  SL_DEBUG_LOG("DHCP IP: %u.%u.%u.%u\n",
               NETIF_IPV4_ADDRESS(addr, 0),
               NETIF_IPV4_ADDRESS(addr, 1),
               NETIF_IPV4_ADDRESS(addr, 2),
               NETIF_IPV4_ADDRESS(addr, 3));
#endif

#if LWIP_IPV6
#if LWIP_IPV6_AUTOCONFIG
  wifi_client_context->netif.ip6_autoconfig_enabled = 1;
#endif /* LWIP_IPV6_AUTOCONFIG */
  netif_create_ip6_linklocal_address(&(wifi_client_context->netif), MAC_48_BIT_SET);
#endif
  return;
}

static void set_sta_link_down(void)
{
#if LWIP_IPV4 && LWIP_DHCP
  SL_DEBUG_LOG("DHCP Link down\n");
  dhcp_stop(&(wifi_client_context->netif));
#endif /* LWIP_IPV4 && LWIP_DHCP */
  netifapi_netif_set_link_down(&(wifi_client_context->netif));
  netifapi_netif_set_down(&(wifi_client_context->netif));
}

/******************************************************************************
                                Public Functions
******************************************************************************/
sl_status_t sl_net_wifi_ap_init(sl_net_interface_t interface,
                                const void *configuration,
                                const void *workspace,
                                sl_net_event_handler_t event_handler)
{
  UNUSED_PARAMETER(interface);
  UNUSED_PARAMETER(configuration);
  UNUSED_PARAMETER(workspace);
  UNUSED_PARAMETER(event_handler);
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t sl_net_wifi_ap_deinit(sl_net_interface_t interface)
{
  UNUSED_PARAMETER(interface);
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t sl_net_wifi_ap_up(sl_net_interface_t interface, sl_net_profile_id_t profile_id)
{
  UNUSED_PARAMETER(interface);
  UNUSED_PARAMETER(profile_id);
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t sl_net_wifi_ap_down(sl_net_interface_t interface)
{
  UNUSED_PARAMETER(interface);
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t sl_net_wifi_client_init(sl_net_interface_t interface,
                                    const void *configuration,
                                    void *context,
                                    sl_net_event_handler_t event_handler)
{
  UNUSED_PARAMETER(interface);
  UNUSED_PARAMETER(event_handler);
  sl_status_t status = sl_wifi_init(configuration, NULL, sl_wifi_default_event_handler);
  if (status != SL_STATUS_OK) {
    return status;
  }
  wifi_client_context = context;
  tcpip_init(NULL, NULL);
  sta_netif_config();
  return SL_STATUS_OK;
}

sl_status_t sl_net_wifi_client_deinit(sl_net_interface_t interface)
{
  UNUSED_PARAMETER(interface);

  // if (lwip_thread.thread_handle != NULL) {
  //   osStatus_t thread_status = osThreadTerminate(lwip_thread.thread_handle);
  //   if (thread_status != osOK) {
  //     SL_DEBUG_LOG("\n\r TCP-IP thread terminate status : %d \r\n", thread_status);
  //     return SL_STATUS_FAIL;
  //   }
  // }

  //! Free all timers
  // struct sys_timeo **list_head = NULL;
  // for (int i = 0; i < lwip_num_cyclic_timers; i++) {
  //   list_head = sys_timeouts_get_next_timeout();
  //   if (*list_head != NULL)
  //     sys_untimeout((*list_head)->h, (*list_head)->arg);
  // }

  return sl_wifi_deinit();
}

sl_status_t sl_net_wifi_client_up(sl_net_interface_t interface, sl_net_profile_id_t profile_id)
{
  UNUSED_PARAMETER(interface);
  uint32_t status = 0;

  // Load profile and connect here
  sl_net_wifi_client_profile_t profile = { 0 };

  status = sl_net_get_profile(SL_NET_WIFI_CLIENT_INTERFACE, profile_id, &profile);
  VERIFY_STATUS_AND_RETURN(status);

  status = sl_wifi_connect(SL_WIFI_CLIENT_INTERFACE, &profile.config, 5000);
  VERIFY_STATUS_AND_RETURN(status);

  set_sta_link_up(&profile);
#if LWIP_IPV4 && LWIP_DHCP
  uint64_t addr                        = wifi_client_context->netif.ip_addr.addr;
  profile.ip.ip.v4.ip_address.bytes[0] = NETIF_IPV4_ADDRESS(addr, 0);
  profile.ip.ip.v4.ip_address.bytes[1] = NETIF_IPV4_ADDRESS(addr, 1);
  profile.ip.ip.v4.ip_address.bytes[2] = NETIF_IPV4_ADDRESS(addr, 2);
  profile.ip.ip.v4.ip_address.bytes[3] = NETIF_IPV4_ADDRESS(addr, 3);

  addr                              = wifi_client_context->netif.gw.addr;
  profile.ip.ip.v4.gateway.bytes[0] = NETIF_IPV4_ADDRESS(addr, 0);
  profile.ip.ip.v4.gateway.bytes[1] = NETIF_IPV4_ADDRESS(addr, 1);
  profile.ip.ip.v4.gateway.bytes[2] = NETIF_IPV4_ADDRESS(addr, 2);
  profile.ip.ip.v4.gateway.bytes[3] = NETIF_IPV4_ADDRESS(addr, 3);

  addr                              = wifi_client_context->netif.netmask.addr;
  profile.ip.ip.v4.netmask.bytes[0] = NETIF_IPV4_ADDRESS(addr, 0);
  profile.ip.ip.v4.netmask.bytes[1] = NETIF_IPV4_ADDRESS(addr, 1);
  profile.ip.ip.v4.netmask.bytes[2] = NETIF_IPV4_ADDRESS(addr, 2);
  profile.ip.ip.v4.netmask.bytes[3] = NETIF_IPV4_ADDRESS(addr, 3);
#endif

#if LWIP_IPV6
  memcpy(&profile.ip.ip.v6.link_local_address, wifi_client_context->netif.ip6_addr, sizeof(sl_ipv6_address_t));
#endif

  // Set the client profile
  status = sl_net_set_profile(SL_NET_WIFI_CLIENT_INTERFACE, profile_id, &profile);

  return SL_STATUS_OK;
}

sl_status_t sl_net_wifi_client_down(sl_net_interface_t interface)
{
  UNUSED_PARAMETER(interface);
  set_sta_link_down();

  return sl_wifi_disconnect(SL_WIFI_CLIENT_INTERFACE);
}

sl_status_t sl_si91x_host_process_data_frame(sl_wifi_interface_t interface, sl_wifi_buffer_t *buffer)
{
  void *packet;
  struct netif *ifp;
  sl_si91x_packet_t *rsi_pkt;
  packet  = sl_si91x_host_get_buffer_data(buffer, 0, NULL);
  rsi_pkt = (sl_si91x_packet_t *)packet;
  SL_DEBUG_LOG("\nRX len : %d\n", rsi_pkt->length);

  /* get the network interface for STATION interface,
   * and forward the received frame buffer to LWIP
   */
  if ((ifp = get_netif(interface)) != NULL) {
    low_level_input(ifp, rsi_pkt->data, rsi_pkt->length);
  }

  return SL_STATUS_OK;
}

sl_status_t sl_net_configure_ip(sl_net_interface_t interface,
                                const sl_net_ip_configuration_t *ip_config,
                                uint32_t timeout)
{
  UNUSED_PARAMETER(interface);
  UNUSED_PARAMETER(ip_config);
  UNUSED_PARAMETER(timeout);
  return SL_STATUS_WIFI_UNSUPPORTED;
}

sl_status_t sl_net_get_ip_address(sl_net_interface_t interface, sl_net_ip_address_t *ip_address, uint32_t timeout)
{
  UNUSED_PARAMETER(interface);
  UNUSED_PARAMETER(ip_address);
  UNUSED_PARAMETER(timeout);
  return SL_STATUS_WIFI_UNSUPPORTED;
}
