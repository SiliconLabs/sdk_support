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

#include "dhcp_client.h"
#include "rsi_hal.h"
#include "wfx_host_events.h"
#include "wfx_rsi.h"

static uint8_t wfx_rsi_drv_buf[WFX_RSI_BUF_SZ];

int32_t rsi_wifi_ble_init()
{
    int32_t status;
    uint8_t buf[128];
    extern void rsi_hal_board_init(void);

    /* Get the GPIOs/PINs set-up
     */

    WFX_RSI_LOG("WFX:RSI:Starting(HEAP_SZ=%d)..", SL_HEAP_SIZE);
    //! Driver initialization
    status = rsi_driver_init(wfx_rsi_drv_buf, WFX_RSI_BUF_SZ);
    if ((status < 0) || (status > WFX_RSI_BUF_SZ))
    {
        WFX_RSI_LOG("ERR: RSI drv init");
        return status;
    }

    WFX_RSI_LOG("WFX:RSI:Dev init..");

    //! Redpine module intialisation
    if ((status = rsi_device_init(LOAD_NWP_FW)) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("ERR: RSI dev init");
        return status;
    }

    WFX_RSI_LOG("WFX:Start wireless drv task");
    /*
     * Create the driver task
     */
    if (xTaskCreate((TaskFunction_t) rsi_wireless_driver_task, "rsi_drv", WFX_RSI_WLAN_TASK_SZ, NULL, 3, &wfx_rsi.drv_task) !=
        pdPASS)
    {
        WFX_RSI_LOG("ERR: RSI task creat");
        return RSI_ERROR_INVALID_PARAM;
    }

    WFX_RSI_LOG("RSI: Wireless init");
    if ((status = rsi_wireless_init(0, 13)) != RSI_SUCCESS)
    {

        WFX_RSI_LOG("ERR: RSI wireless init");
        return status;
    }

    WFX_RSI_LOG("RSI: Get FW Ver");
    /*
     * Get the MAC and other info to let the user know about it.
     */
    if (rsi_wlan_get(RSI_FW_VERSION, buf, sizeof(buf)) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("ERR: RSI FW-Ver");
        return status;
    }
    buf[sizeof(buf) - 1] = 0;
    WFX_RSI_LOG("RSI-FW: Ver=%s", buf);

    //! Send feature frame
    if ((status = rsi_send_feature_frame()) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("ERR: RSI feat frame");
        return status;
    }
    WFX_RSI_LOG("WFX: Sent RSI Feature frame");
    (void) rsi_wlan_radio_init(); /* Required so we can get MAC address */
    if ((status = rsi_wlan_get(RSI_MAC_ADDRESS, &wfx_rsi.sta_mac.octet[0], 6)) != RSI_SUCCESS)
    {
        WFX_RSI_LOG("ERR: RSI MAC-Addr");
        return status;
    }
    WFX_RSI_LOG("WLAN: MAC %02x:%02x:%02x %02x:%02x:%02x", wfx_rsi.sta_mac.octet[0], wfx_rsi.sta_mac.octet[1],
                wfx_rsi.sta_mac.octet[2], wfx_rsi.sta_mac.octet[3], wfx_rsi.sta_mac.octet[4], wfx_rsi.sta_mac.octet[5]);
    wfx_rsi.events = xEventGroupCreate();
    /*
     * Register callbacks - We are only interested in the connectivity CBs
     */

    return status;
}

void init_rsiPlatform()
{
    /*BLE task - RS911x*/
    WFX_RSI_LOG("WFX:Start ble task");
    if (xTaskCreate((TaskFunction_t) rsi_ble_task, "rsi_ble", WFX_RSI_TASK_SZ, NULL, 2, &wfx_rsi.ble_task) != pdPASS)
    {
        WFX_RSI_LOG("ERR: RSI ble task create");
    }
}