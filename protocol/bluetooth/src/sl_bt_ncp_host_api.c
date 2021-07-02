/***************************************************************************//**
 * @brief SL_BT_API commands for NCP host
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

#include "sl_bt_api.h"
#include "sli_bt_api.h"

void sl_bt_host_handle_command();
void sl_bt_host_handle_command_noresponse();
extern sl_bt_msg_t *sl_bt_cmd_msg;
extern sl_bt_msg_t *sl_bt_rsp_msg;

void sl_bt_dfu_reset(uint8_t dfu) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    cmd->data.cmd_dfu_reset.dfu=dfu;

    cmd->header=sl_bt_cmd_dfu_reset_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command_noresponse();
}

sl_status_t sl_bt_dfu_flash_set_address(uint32_t address) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_dfu_flash_set_address.address=address;

    cmd->header=sl_bt_cmd_dfu_flash_set_address_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_set_address.result;

}

sl_status_t sl_bt_dfu_flash_upload(size_t data_len, const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_dfu_flash_upload.data.len=data_len;
    memcpy(cmd->data.cmd_dfu_flash_upload.data.data,data,data_len);

    cmd->header=sl_bt_cmd_dfu_flash_upload_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_upload.result;

}

sl_status_t sl_bt_dfu_flash_upload_finish() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_dfu_flash_upload_finish_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_dfu_flash_upload_finish.result;

}

sl_status_t sl_bt_system_hello() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_hello_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_hello.result;

}

sl_status_t sl_bt_system_start_bluetooth() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_start_bluetooth_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_start_bluetooth.result;

}

sl_status_t sl_bt_system_stop_bluetooth() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_stop_bluetooth_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_stop_bluetooth.result;

}

sl_status_t sl_bt_system_get_version(uint16_t *major,
                                     uint16_t *minor,
                                     uint16_t *patch,
                                     uint16_t *build,
                                     uint32_t *bootloader,
                                     uint32_t *hash) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_version_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    *major = rsp->data.rsp_system_get_version.major;
    *minor = rsp->data.rsp_system_get_version.minor;
    *patch = rsp->data.rsp_system_get_version.patch;
    *build = rsp->data.rsp_system_get_version.build;
    *bootloader = rsp->data.rsp_system_get_version.bootloader;
    *hash = rsp->data.rsp_system_get_version.hash;
    return rsp->data.rsp_system_get_version.result;

}

void sl_bt_system_reset(uint8_t dfu) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    cmd->data.cmd_system_reset.dfu=dfu;

    cmd->header=sl_bt_cmd_system_reset_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command_noresponse();
}

sl_status_t sl_bt_system_halt(uint8_t halt) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_halt.halt=halt;

    cmd->header=sl_bt_cmd_system_halt_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_halt.result;

}

sl_status_t sl_bt_system_linklayer_configure(uint8_t key,
                                             size_t data_len,
                                             const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_linklayer_configure.key=key;
    cmd->data.cmd_system_linklayer_configure.data.len=data_len;
    memcpy(cmd->data.cmd_system_linklayer_configure.data.data,data,data_len);

    cmd->header=sl_bt_cmd_system_linklayer_configure_id+(((2+data_len)&0xff)<<8)+(((2+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_linklayer_configure.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_system_set_max_tx_power(int16_t power, int16_t *set_power) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_max_tx_power.power=power;

    cmd->header=sl_bt_cmd_system_set_max_tx_power_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *set_power = rsp->data.rsp_system_set_max_tx_power.set_power;
    return rsp->data.rsp_system_set_max_tx_power.result;

}

sl_status_t sl_bt_system_set_tx_power(int16_t min_power,
                                      int16_t max_power,
                                      int16_t *set_min,
                                      int16_t *set_max) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_tx_power.min_power=min_power;
    cmd->data.cmd_system_set_tx_power.max_power=max_power;

    cmd->header=sl_bt_cmd_system_set_tx_power_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    *set_min = rsp->data.rsp_system_set_tx_power.set_min;
    *set_max = rsp->data.rsp_system_set_tx_power.set_max;
    return rsp->data.rsp_system_set_tx_power.result;

}

sl_status_t sl_bt_system_get_tx_power_setting(int16_t *support_min,
                                              int16_t *support_max,
                                              int16_t *set_min,
                                              int16_t *set_max,
                                              int16_t *rf_path_gain) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_tx_power_setting_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    *support_min = rsp->data.rsp_system_get_tx_power_setting.support_min;
    *support_max = rsp->data.rsp_system_get_tx_power_setting.support_max;
    *set_min = rsp->data.rsp_system_get_tx_power_setting.set_min;
    *set_max = rsp->data.rsp_system_get_tx_power_setting.set_max;
    *rf_path_gain = rsp->data.rsp_system_get_tx_power_setting.rf_path_gain;
    return rsp->data.rsp_system_get_tx_power_setting.result;

}

sl_status_t sl_bt_system_set_identity_address(bd_addr address, uint8_t type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_system_set_identity_address.address,&address,sizeof(bd_addr));
    cmd->data.cmd_system_set_identity_address.type=type;

    cmd->header=sl_bt_cmd_system_set_identity_address_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_set_identity_address.result;

}

sl_status_t sl_bt_system_get_identity_address(bd_addr *address, uint8_t *type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_get_identity_address_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    memcpy(address,&rsp->data.rsp_system_get_identity_address.address,sizeof(bd_addr));
    *type = rsp->data.rsp_system_get_identity_address.type;
    return rsp->data.rsp_system_get_identity_address.result;

}

sl_status_t sl_bt_system_get_random_data(uint8_t length,
                                         size_t max_data_size,
                                         size_t *data_len,
                                         uint8_t *data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_get_random_data.length=length;

    cmd->header=sl_bt_cmd_system_get_random_data_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *data_len = rsp->data.rsp_system_get_random_data.data.len;
    if (rsp->data.rsp_system_get_random_data.data.len <= max_data_size) {
        memcpy(data,rsp->data.rsp_system_get_random_data.data.data,rsp->data.rsp_system_get_random_data.data.len);
    }
    return rsp->data.rsp_system_get_random_data.result;

}

sl_status_t sl_bt_system_data_buffer_write(size_t data_len,
                                           const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_data_buffer_write.data.len=data_len;
    memcpy(cmd->data.cmd_system_data_buffer_write.data.data,data,data_len);

    cmd->header=sl_bt_cmd_system_data_buffer_write_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_data_buffer_write.result;

}

sl_status_t sl_bt_system_data_buffer_clear() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_system_data_buffer_clear_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_data_buffer_clear.result;

}

sl_status_t sl_bt_system_get_counters(uint8_t reset,
                                      uint16_t *tx_packets,
                                      uint16_t *rx_packets,
                                      uint16_t *crc_errors,
                                      uint16_t *failures) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_get_counters.reset=reset;

    cmd->header=sl_bt_cmd_system_get_counters_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *tx_packets = rsp->data.rsp_system_get_counters.tx_packets;
    *rx_packets = rsp->data.rsp_system_get_counters.rx_packets;
    *crc_errors = rsp->data.rsp_system_get_counters.crc_errors;
    *failures = rsp->data.rsp_system_get_counters.failures;
    return rsp->data.rsp_system_get_counters.result;

}

sl_status_t sl_bt_system_set_soft_timer(uint32_t time,
                                        uint8_t handle,
                                        uint8_t single_shot) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_soft_timer.time=time;
    cmd->data.cmd_system_set_soft_timer.handle=handle;
    cmd->data.cmd_system_set_soft_timer.single_shot=single_shot;

    cmd->header=sl_bt_cmd_system_set_soft_timer_id+(((6)&0xff)<<8)+(((6)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_set_soft_timer.result;

}

sl_status_t sl_bt_system_set_lazy_soft_timer(uint32_t time,
                                             uint32_t slack,
                                             uint8_t handle,
                                             uint8_t single_shot) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_system_set_lazy_soft_timer.time=time;
    cmd->data.cmd_system_set_lazy_soft_timer.slack=slack;
    cmd->data.cmd_system_set_lazy_soft_timer.handle=handle;
    cmd->data.cmd_system_set_lazy_soft_timer.single_shot=single_shot;

    cmd->header=sl_bt_cmd_system_set_lazy_soft_timer_id+(((10)&0xff)<<8)+(((10)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_system_set_lazy_soft_timer.result;

}

sl_status_t sl_bt_gap_set_privacy_mode(uint8_t privacy, uint8_t interval) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gap_set_privacy_mode.privacy=privacy;
    cmd->data.cmd_gap_set_privacy_mode.interval=interval;

    cmd->header=sl_bt_cmd_gap_set_privacy_mode_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_set_privacy_mode.result;

}

sl_status_t sl_bt_gap_set_data_channel_classification(size_t channel_map_len,
                                                      const uint8_t* channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gap_set_data_channel_classification.channel_map.len=channel_map_len;
    memcpy(cmd->data.cmd_gap_set_data_channel_classification.channel_map.data,channel_map,channel_map_len);

    cmd->header=sl_bt_cmd_gap_set_data_channel_classification_id+(((1+channel_map_len)&0xff)<<8)+(((1+channel_map_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_set_data_channel_classification.result;

}

sl_status_t sl_bt_gap_enable_whitelisting(uint8_t enable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gap_enable_whitelisting.enable=enable;

    cmd->header=sl_bt_cmd_gap_enable_whitelisting_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gap_enable_whitelisting.result;

}

sl_status_t sl_bt_advertiser_create_set(uint8_t *handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_advertiser_create_set_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    *handle = rsp->data.rsp_advertiser_create_set.handle;
    return rsp->data.rsp_advertiser_create_set.result;

}

sl_status_t sl_bt_advertiser_set_timing(uint8_t handle,
                                        uint32_t interval_min,
                                        uint32_t interval_max,
                                        uint16_t duration,
                                        uint8_t maxevents) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_timing.handle=handle;
    cmd->data.cmd_advertiser_set_timing.interval_min=interval_min;
    cmd->data.cmd_advertiser_set_timing.interval_max=interval_max;
    cmd->data.cmd_advertiser_set_timing.duration=duration;
    cmd->data.cmd_advertiser_set_timing.maxevents=maxevents;

    cmd->header=sl_bt_cmd_advertiser_set_timing_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_timing.result;

}

sl_status_t sl_bt_advertiser_set_phy(uint8_t handle,
                                     uint8_t primary_phy,
                                     uint8_t secondary_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_phy.handle=handle;
    cmd->data.cmd_advertiser_set_phy.primary_phy=primary_phy;
    cmd->data.cmd_advertiser_set_phy.secondary_phy=secondary_phy;

    cmd->header=sl_bt_cmd_advertiser_set_phy_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_phy.result;

}

sl_status_t sl_bt_advertiser_set_channel_map(uint8_t handle,
                                             uint8_t channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_channel_map.handle=handle;
    cmd->data.cmd_advertiser_set_channel_map.channel_map=channel_map;

    cmd->header=sl_bt_cmd_advertiser_set_channel_map_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_channel_map.result;

}

sl_status_t sl_bt_advertiser_set_tx_power(uint8_t handle,
                                          int16_t power,
                                          int16_t *set_power) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_tx_power.handle=handle;
    cmd->data.cmd_advertiser_set_tx_power.power=power;

    cmd->header=sl_bt_cmd_advertiser_set_tx_power_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    *set_power = rsp->data.rsp_advertiser_set_tx_power.set_power;
    return rsp->data.rsp_advertiser_set_tx_power.result;

}

sl_status_t sl_bt_advertiser_set_report_scan_request(uint8_t handle,
                                                     uint8_t report_scan_req) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_report_scan_request.handle=handle;
    cmd->data.cmd_advertiser_set_report_scan_request.report_scan_req=report_scan_req;

    cmd->header=sl_bt_cmd_advertiser_set_report_scan_request_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_report_scan_request.result;

}

sl_status_t sl_bt_advertiser_set_random_address(uint8_t handle,
                                                uint8_t addr_type,
                                                bd_addr address,
                                                bd_addr *address_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_random_address.handle=handle;
    cmd->data.cmd_advertiser_set_random_address.addr_type=addr_type;
    memcpy(&cmd->data.cmd_advertiser_set_random_address.address,&address,sizeof(bd_addr));

    cmd->header=sl_bt_cmd_advertiser_set_random_address_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    memcpy(address_out,&rsp->data.rsp_advertiser_set_random_address.address_out,sizeof(bd_addr));
    return rsp->data.rsp_advertiser_set_random_address.result;

}

sl_status_t sl_bt_advertiser_clear_random_address(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_clear_random_address.handle=handle;

    cmd->header=sl_bt_cmd_advertiser_clear_random_address_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_clear_random_address.result;

}

sl_status_t sl_bt_advertiser_set_configuration(uint8_t handle,
                                               uint32_t configurations) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_configuration.handle=handle;
    cmd->data.cmd_advertiser_set_configuration.configurations=configurations;

    cmd->header=sl_bt_cmd_advertiser_set_configuration_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_configuration.result;

}

sl_status_t sl_bt_advertiser_clear_configuration(uint8_t handle,
                                                 uint32_t configurations) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_clear_configuration.handle=handle;
    cmd->data.cmd_advertiser_clear_configuration.configurations=configurations;

    cmd->header=sl_bt_cmd_advertiser_clear_configuration_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_clear_configuration.result;

}

sl_status_t sl_bt_advertiser_set_data(uint8_t handle,
                                      uint8_t packet_type,
                                      size_t adv_data_len,
                                      const uint8_t* adv_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_data.handle=handle;
    cmd->data.cmd_advertiser_set_data.packet_type=packet_type;
    cmd->data.cmd_advertiser_set_data.adv_data.len=adv_data_len;
    memcpy(cmd->data.cmd_advertiser_set_data.adv_data.data,adv_data,adv_data_len);

    cmd->header=sl_bt_cmd_advertiser_set_data_id+(((3+adv_data_len)&0xff)<<8)+(((3+adv_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_data.result;

}

sl_status_t sl_bt_advertiser_set_long_data(uint8_t handle, uint8_t packet_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_set_long_data.handle=handle;
    cmd->data.cmd_advertiser_set_long_data.packet_type=packet_type;

    cmd->header=sl_bt_cmd_advertiser_set_long_data_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_set_long_data.result;

}

sl_status_t sl_bt_advertiser_start(uint8_t handle,
                                   uint8_t discover,
                                   uint8_t connect) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_start.handle=handle;
    cmd->data.cmd_advertiser_start.discover=discover;
    cmd->data.cmd_advertiser_start.connect=connect;

    cmd->header=sl_bt_cmd_advertiser_start_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_start.result;

}

sl_status_t sl_bt_advertiser_stop(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_stop.handle=handle;

    cmd->header=sl_bt_cmd_advertiser_stop_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_stop.result;

}

sl_status_t sl_bt_advertiser_start_periodic_advertising(uint8_t handle,
                                                        uint16_t interval_min,
                                                        uint16_t interval_max,
                                                        uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_start_periodic_advertising.handle=handle;
    cmd->data.cmd_advertiser_start_periodic_advertising.interval_min=interval_min;
    cmd->data.cmd_advertiser_start_periodic_advertising.interval_max=interval_max;
    cmd->data.cmd_advertiser_start_periodic_advertising.flags=flags;

    cmd->header=sl_bt_cmd_advertiser_start_periodic_advertising_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_start_periodic_advertising.result;

}

sl_status_t sl_bt_advertiser_stop_periodic_advertising(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_stop_periodic_advertising.handle=handle;

    cmd->header=sl_bt_cmd_advertiser_stop_periodic_advertising_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_stop_periodic_advertising.result;

}

sl_status_t sl_bt_advertiser_delete_set(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_advertiser_delete_set.handle=handle;

    cmd->header=sl_bt_cmd_advertiser_delete_set_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_advertiser_delete_set.result;

}

sl_status_t sl_bt_scanner_set_timing(uint8_t phys,
                                     uint16_t scan_interval,
                                     uint16_t scan_window) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_timing.phys=phys;
    cmd->data.cmd_scanner_set_timing.scan_interval=scan_interval;
    cmd->data.cmd_scanner_set_timing.scan_window=scan_window;

    cmd->header=sl_bt_cmd_scanner_set_timing_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_timing.result;

}

sl_status_t sl_bt_scanner_set_mode(uint8_t phys, uint8_t scan_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_set_mode.phys=phys;
    cmd->data.cmd_scanner_set_mode.scan_mode=scan_mode;

    cmd->header=sl_bt_cmd_scanner_set_mode_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_set_mode.result;

}

sl_status_t sl_bt_scanner_start(uint8_t scanning_phy, uint8_t discover_mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_scanner_start.scanning_phy=scanning_phy;
    cmd->data.cmd_scanner_start.discover_mode=discover_mode;

    cmd->header=sl_bt_cmd_scanner_start_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_start.result;

}

sl_status_t sl_bt_scanner_stop() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_scanner_stop_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_scanner_stop.result;

}

sl_status_t sl_bt_sync_set_parameters(uint16_t skip,
                                      uint16_t timeout,
                                      uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_set_parameters.skip=skip;
    cmd->data.cmd_sync_set_parameters.timeout=timeout;
    cmd->data.cmd_sync_set_parameters.flags=flags;

    cmd->header=sl_bt_cmd_sync_set_parameters_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_set_parameters.result;

}

sl_status_t sl_bt_sync_open(bd_addr address,
                            uint8_t address_type,
                            uint8_t adv_sid,
                            uint16_t *sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sync_open.address,&address,sizeof(bd_addr));
    cmd->data.cmd_sync_open.address_type=address_type;
    cmd->data.cmd_sync_open.adv_sid=adv_sid;

    cmd->header=sl_bt_cmd_sync_open_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    *sync = rsp->data.rsp_sync_open.sync;
    return rsp->data.rsp_sync_open.result;

}

sl_status_t sl_bt_sync_close(uint16_t sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sync_close.sync=sync;

    cmd->header=sl_bt_cmd_sync_close_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sync_close.result;

}

sl_status_t sl_bt_connection_set_default_parameters(uint16_t min_interval,
                                                    uint16_t max_interval,
                                                    uint16_t latency,
                                                    uint16_t timeout,
                                                    uint16_t min_ce_length,
                                                    uint16_t max_ce_length) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_default_parameters.min_interval=min_interval;
    cmd->data.cmd_connection_set_default_parameters.max_interval=max_interval;
    cmd->data.cmd_connection_set_default_parameters.latency=latency;
    cmd->data.cmd_connection_set_default_parameters.timeout=timeout;
    cmd->data.cmd_connection_set_default_parameters.min_ce_length=min_ce_length;
    cmd->data.cmd_connection_set_default_parameters.max_ce_length=max_ce_length;

    cmd->header=sl_bt_cmd_connection_set_default_parameters_id+(((12)&0xff)<<8)+(((12)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_default_parameters.result;

}

sl_status_t sl_bt_connection_set_default_preferred_phy(uint8_t preferred_phy,
                                                       uint8_t accepted_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_default_preferred_phy.preferred_phy=preferred_phy;
    cmd->data.cmd_connection_set_default_preferred_phy.accepted_phy=accepted_phy;

    cmd->header=sl_bt_cmd_connection_set_default_preferred_phy_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_default_preferred_phy.result;

}

sl_status_t sl_bt_connection_open(bd_addr address,
                                  uint8_t address_type,
                                  uint8_t initiating_phy,
                                  uint8_t *connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_connection_open.address,&address,sizeof(bd_addr));
    cmd->data.cmd_connection_open.address_type=address_type;
    cmd->data.cmd_connection_open.initiating_phy=initiating_phy;

    cmd->header=sl_bt_cmd_connection_open_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    *connection = rsp->data.rsp_connection_open.connection;
    return rsp->data.rsp_connection_open.result;

}

sl_status_t sl_bt_connection_set_parameters(uint8_t connection,
                                            uint16_t min_interval,
                                            uint16_t max_interval,
                                            uint16_t latency,
                                            uint16_t timeout,
                                            uint16_t min_ce_length,
                                            uint16_t max_ce_length) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_parameters.connection=connection;
    cmd->data.cmd_connection_set_parameters.min_interval=min_interval;
    cmd->data.cmd_connection_set_parameters.max_interval=max_interval;
    cmd->data.cmd_connection_set_parameters.latency=latency;
    cmd->data.cmd_connection_set_parameters.timeout=timeout;
    cmd->data.cmd_connection_set_parameters.min_ce_length=min_ce_length;
    cmd->data.cmd_connection_set_parameters.max_ce_length=max_ce_length;

    cmd->header=sl_bt_cmd_connection_set_parameters_id+(((13)&0xff)<<8)+(((13)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_parameters.result;

}

sl_status_t sl_bt_connection_set_preferred_phy(uint8_t connection,
                                               uint8_t preferred_phy,
                                               uint8_t accepted_phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_preferred_phy.connection=connection;
    cmd->data.cmd_connection_set_preferred_phy.preferred_phy=preferred_phy;
    cmd->data.cmd_connection_set_preferred_phy.accepted_phy=accepted_phy;

    cmd->header=sl_bt_cmd_connection_set_preferred_phy_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_preferred_phy.result;

}

sl_status_t sl_bt_connection_disable_slave_latency(uint8_t connection,
                                                   uint8_t disable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_disable_slave_latency.connection=connection;
    cmd->data.cmd_connection_disable_slave_latency.disable=disable;

    cmd->header=sl_bt_cmd_connection_disable_slave_latency_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_disable_slave_latency.result;

}

sl_status_t sl_bt_connection_get_rssi(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_rssi.connection=connection;

    cmd->header=sl_bt_cmd_connection_get_rssi_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_get_rssi.result;

}

sl_status_t sl_bt_connection_read_channel_map(uint8_t connection,
                                              size_t max_channel_map_size,
                                              size_t *channel_map_len,
                                              uint8_t *channel_map) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_read_channel_map.connection=connection;

    cmd->header=sl_bt_cmd_connection_read_channel_map_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *channel_map_len = rsp->data.rsp_connection_read_channel_map.channel_map.len;
    if (rsp->data.rsp_connection_read_channel_map.channel_map.len <= max_channel_map_size) {
        memcpy(channel_map,rsp->data.rsp_connection_read_channel_map.channel_map.data,rsp->data.rsp_connection_read_channel_map.channel_map.len);
    }
    return rsp->data.rsp_connection_read_channel_map.result;

}

sl_status_t sl_bt_connection_set_power_reporting(uint8_t connection,
                                                 uint8_t mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_power_reporting.connection=connection;
    cmd->data.cmd_connection_set_power_reporting.mode=mode;

    cmd->header=sl_bt_cmd_connection_set_power_reporting_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_power_reporting.result;

}

sl_status_t sl_bt_connection_set_remote_power_reporting(uint8_t connection,
                                                        uint8_t mode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_set_remote_power_reporting.connection=connection;
    cmd->data.cmd_connection_set_remote_power_reporting.mode=mode;

    cmd->header=sl_bt_cmd_connection_set_remote_power_reporting_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_set_remote_power_reporting.result;

}

sl_status_t sl_bt_connection_get_tx_power(uint8_t connection,
                                          uint8_t phy,
                                          int8_t *current_level,
                                          int8_t *max_level) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_tx_power.connection=connection;
    cmd->data.cmd_connection_get_tx_power.phy=phy;

    cmd->header=sl_bt_cmd_connection_get_tx_power_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *current_level = rsp->data.rsp_connection_get_tx_power.current_level;
    *max_level = rsp->data.rsp_connection_get_tx_power.max_level;
    return rsp->data.rsp_connection_get_tx_power.result;

}

sl_status_t sl_bt_connection_get_remote_tx_power(uint8_t connection,
                                                 uint8_t phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_get_remote_tx_power.connection=connection;
    cmd->data.cmd_connection_get_remote_tx_power.phy=phy;

    cmd->header=sl_bt_cmd_connection_get_remote_tx_power_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_get_remote_tx_power.result;

}

sl_status_t sl_bt_connection_close(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_connection_close.connection=connection;

    cmd->header=sl_bt_cmd_connection_close_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_connection_close.result;

}

sl_status_t sl_bt_gatt_set_max_mtu(uint16_t max_mtu, uint16_t *max_mtu_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_set_max_mtu.max_mtu=max_mtu;

    cmd->header=sl_bt_cmd_gatt_set_max_mtu_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *max_mtu_out = rsp->data.rsp_gatt_set_max_mtu.max_mtu_out;
    return rsp->data.rsp_gatt_set_max_mtu.result;

}

sl_status_t sl_bt_gatt_discover_primary_services(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_primary_services.connection=connection;

    cmd->header=sl_bt_cmd_gatt_discover_primary_services_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_primary_services.result;

}

sl_status_t sl_bt_gatt_discover_primary_services_by_uuid(uint8_t connection,
                                                         size_t uuid_len,
                                                         const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_primary_services_by_uuid.connection=connection;
    cmd->data.cmd_gatt_discover_primary_services_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_discover_primary_services_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_discover_primary_services_by_uuid_id+(((2+uuid_len)&0xff)<<8)+(((2+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_primary_services_by_uuid.result;

}

sl_status_t sl_bt_gatt_find_included_services(uint8_t connection,
                                              uint32_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_find_included_services.connection=connection;
    cmd->data.cmd_gatt_find_included_services.service=service;

    cmd->header=sl_bt_cmd_gatt_find_included_services_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_find_included_services.result;

}

sl_status_t sl_bt_gatt_discover_characteristics(uint8_t connection,
                                                uint32_t service) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_characteristics.connection=connection;
    cmd->data.cmd_gatt_discover_characteristics.service=service;

    cmd->header=sl_bt_cmd_gatt_discover_characteristics_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_characteristics.result;

}

sl_status_t sl_bt_gatt_discover_characteristics_by_uuid(uint8_t connection,
                                                        uint32_t service,
                                                        size_t uuid_len,
                                                        const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_characteristics_by_uuid.connection=connection;
    cmd->data.cmd_gatt_discover_characteristics_by_uuid.service=service;
    cmd->data.cmd_gatt_discover_characteristics_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_discover_characteristics_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_discover_characteristics_by_uuid_id+(((6+uuid_len)&0xff)<<8)+(((6+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_characteristics_by_uuid.result;

}

sl_status_t sl_bt_gatt_discover_descriptors(uint8_t connection,
                                            uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_discover_descriptors.connection=connection;
    cmd->data.cmd_gatt_discover_descriptors.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_discover_descriptors_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_discover_descriptors.result;

}

sl_status_t sl_bt_gatt_set_characteristic_notification(uint8_t connection,
                                                       uint16_t characteristic,
                                                       uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_set_characteristic_notification.connection=connection;
    cmd->data.cmd_gatt_set_characteristic_notification.characteristic=characteristic;
    cmd->data.cmd_gatt_set_characteristic_notification.flags=flags;

    cmd->header=sl_bt_cmd_gatt_set_characteristic_notification_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_set_characteristic_notification.result;

}

sl_status_t sl_bt_gatt_send_characteristic_confirmation(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_send_characteristic_confirmation.connection=connection;

    cmd->header=sl_bt_cmd_gatt_send_characteristic_confirmation_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_send_characteristic_confirmation.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value(uint8_t connection,
                                                 uint16_t characteristic) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value_from_offset(uint8_t connection,
                                                             uint16_t characteristic,
                                                             uint16_t offset,
                                                             uint16_t maxlen) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value_from_offset.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.characteristic=characteristic;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.offset=offset;
    cmd->data.cmd_gatt_read_characteristic_value_from_offset.maxlen=maxlen;

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_from_offset_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value_from_offset.result;

}

sl_status_t sl_bt_gatt_read_multiple_characteristic_values(uint8_t connection,
                                                           size_t characteristic_list_len,
                                                           const uint8_t* characteristic_list) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_multiple_characteristic_values.connection=connection;
    cmd->data.cmd_gatt_read_multiple_characteristic_values.characteristic_list.len=characteristic_list_len;
    memcpy(cmd->data.cmd_gatt_read_multiple_characteristic_values.characteristic_list.data,characteristic_list,characteristic_list_len);

    cmd->header=sl_bt_cmd_gatt_read_multiple_characteristic_values_id+(((2+characteristic_list_len)&0xff)<<8)+(((2+characteristic_list_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_multiple_characteristic_values.result;

}

sl_status_t sl_bt_gatt_read_characteristic_value_by_uuid(uint8_t connection,
                                                         uint32_t service,
                                                         size_t uuid_len,
                                                         const uint8_t* uuid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.connection=connection;
    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.service=service;
    cmd->data.cmd_gatt_read_characteristic_value_by_uuid.uuid.len=uuid_len;
    memcpy(cmd->data.cmd_gatt_read_characteristic_value_by_uuid.uuid.data,uuid,uuid_len);

    cmd->header=sl_bt_cmd_gatt_read_characteristic_value_by_uuid_id+(((6+uuid_len)&0xff)<<8)+(((6+uuid_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_characteristic_value_by_uuid.result;

}

sl_status_t sl_bt_gatt_write_characteristic_value(uint8_t connection,
                                                  uint16_t characteristic,
                                                  size_t value_len,
                                                  const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_characteristic_value.connection=connection;
    cmd->data.cmd_gatt_write_characteristic_value.characteristic=characteristic;
    cmd->data.cmd_gatt_write_characteristic_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_characteristic_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_characteristic_value_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_write_characteristic_value.result;

}

sl_status_t sl_bt_gatt_write_characteristic_value_without_response(uint8_t connection,
                                                                   uint16_t characteristic,
                                                                   size_t value_len,
                                                                   const uint8_t* value,
                                                                   uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_characteristic_value_without_response.connection=connection;
    cmd->data.cmd_gatt_write_characteristic_value_without_response.characteristic=characteristic;
    cmd->data.cmd_gatt_write_characteristic_value_without_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_characteristic_value_without_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_characteristic_value_without_response_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *sent_len = rsp->data.rsp_gatt_write_characteristic_value_without_response.sent_len;
    return rsp->data.rsp_gatt_write_characteristic_value_without_response.result;

}

sl_status_t sl_bt_gatt_prepare_characteristic_value_write(uint8_t connection,
                                                          uint16_t characteristic,
                                                          uint16_t offset,
                                                          size_t value_len,
                                                          const uint8_t* value,
                                                          uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_prepare_characteristic_value_write.connection=connection;
    cmd->data.cmd_gatt_prepare_characteristic_value_write.characteristic=characteristic;
    cmd->data.cmd_gatt_prepare_characteristic_value_write.offset=offset;
    cmd->data.cmd_gatt_prepare_characteristic_value_write.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_prepare_characteristic_value_write.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_prepare_characteristic_value_write_id+(((6+value_len)&0xff)<<8)+(((6+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *sent_len = rsp->data.rsp_gatt_prepare_characteristic_value_write.sent_len;
    return rsp->data.rsp_gatt_prepare_characteristic_value_write.result;

}

sl_status_t sl_bt_gatt_prepare_characteristic_value_reliable_write(uint8_t connection,
                                                                   uint16_t characteristic,
                                                                   uint16_t offset,
                                                                   size_t value_len,
                                                                   const uint8_t* value,
                                                                   uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.connection=connection;
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.characteristic=characteristic;
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.offset=offset;
    cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_prepare_characteristic_value_reliable_write.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_prepare_characteristic_value_reliable_write_id+(((6+value_len)&0xff)<<8)+(((6+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *sent_len = rsp->data.rsp_gatt_prepare_characteristic_value_reliable_write.sent_len;
    return rsp->data.rsp_gatt_prepare_characteristic_value_reliable_write.result;

}

sl_status_t sl_bt_gatt_execute_characteristic_value_write(uint8_t connection,
                                                          uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_execute_characteristic_value_write.connection=connection;
    cmd->data.cmd_gatt_execute_characteristic_value_write.flags=flags;

    cmd->header=sl_bt_cmd_gatt_execute_characteristic_value_write_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_execute_characteristic_value_write.result;

}

sl_status_t sl_bt_gatt_read_descriptor_value(uint8_t connection,
                                             uint16_t descriptor) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_read_descriptor_value.connection=connection;
    cmd->data.cmd_gatt_read_descriptor_value.descriptor=descriptor;

    cmd->header=sl_bt_cmd_gatt_read_descriptor_value_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_read_descriptor_value.result;

}

sl_status_t sl_bt_gatt_write_descriptor_value(uint8_t connection,
                                              uint16_t descriptor,
                                              size_t value_len,
                                              const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_write_descriptor_value.connection=connection;
    cmd->data.cmd_gatt_write_descriptor_value.descriptor=descriptor;
    cmd->data.cmd_gatt_write_descriptor_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_write_descriptor_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_write_descriptor_value_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_write_descriptor_value.result;

}

sl_status_t sl_bt_gatt_server_set_capabilities(uint32_t caps,
                                               uint32_t reserved) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_set_capabilities.caps=caps;
    cmd->data.cmd_gatt_server_set_capabilities.reserved=reserved;

    cmd->header=sl_bt_cmd_gatt_server_set_capabilities_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_set_capabilities.result;

}

sl_status_t sl_bt_gatt_server_enable_capabilities(uint32_t caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_enable_capabilities.caps=caps;

    cmd->header=sl_bt_cmd_gatt_server_enable_capabilities_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_enable_capabilities.result;

}

sl_status_t sl_bt_gatt_server_disable_capabilities(uint32_t caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_disable_capabilities.caps=caps;

    cmd->header=sl_bt_cmd_gatt_server_disable_capabilities_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_disable_capabilities.result;

}

sl_status_t sl_bt_gatt_server_get_enabled_capabilities(uint32_t *caps) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_gatt_server_get_enabled_capabilities_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    *caps = rsp->data.rsp_gatt_server_get_enabled_capabilities.caps;
    return rsp->data.rsp_gatt_server_get_enabled_capabilities.result;

}

sl_status_t sl_bt_gatt_server_set_max_mtu(uint16_t max_mtu,
                                          uint16_t *max_mtu_out) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_set_max_mtu.max_mtu=max_mtu;

    cmd->header=sl_bt_cmd_gatt_server_set_max_mtu_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *max_mtu_out = rsp->data.rsp_gatt_server_set_max_mtu.max_mtu_out;
    return rsp->data.rsp_gatt_server_set_max_mtu.result;

}

sl_status_t sl_bt_gatt_server_get_mtu(uint8_t connection, uint16_t *mtu) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_get_mtu.connection=connection;

    cmd->header=sl_bt_cmd_gatt_server_get_mtu_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *mtu = rsp->data.rsp_gatt_server_get_mtu.mtu;
    return rsp->data.rsp_gatt_server_get_mtu.result;

}

sl_status_t sl_bt_gatt_server_find_attribute(uint16_t start,
                                             size_t type_len,
                                             const uint8_t* type,
                                             uint16_t *attribute) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_find_attribute.start=start;
    cmd->data.cmd_gatt_server_find_attribute.type.len=type_len;
    memcpy(cmd->data.cmd_gatt_server_find_attribute.type.data,type,type_len);

    cmd->header=sl_bt_cmd_gatt_server_find_attribute_id+(((3+type_len)&0xff)<<8)+(((3+type_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *attribute = rsp->data.rsp_gatt_server_find_attribute.attribute;
    return rsp->data.rsp_gatt_server_find_attribute.result;

}

sl_status_t sl_bt_gatt_server_read_attribute_value(uint16_t attribute,
                                                   uint16_t offset,
                                                   size_t max_value_size,
                                                   size_t *value_len,
                                                   uint8_t *value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_attribute_value.attribute=attribute;
    cmd->data.cmd_gatt_server_read_attribute_value.offset=offset;

    cmd->header=sl_bt_cmd_gatt_server_read_attribute_value_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    *value_len = rsp->data.rsp_gatt_server_read_attribute_value.value.len;
    if (rsp->data.rsp_gatt_server_read_attribute_value.value.len <= max_value_size) {
        memcpy(value,rsp->data.rsp_gatt_server_read_attribute_value.value.data,rsp->data.rsp_gatt_server_read_attribute_value.value.len);
    }
    return rsp->data.rsp_gatt_server_read_attribute_value.result;

}

sl_status_t sl_bt_gatt_server_read_attribute_type(uint16_t attribute,
                                                  size_t max_type_size,
                                                  size_t *type_len,
                                                  uint8_t *type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_attribute_type.attribute=attribute;

    cmd->header=sl_bt_cmd_gatt_server_read_attribute_type_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *type_len = rsp->data.rsp_gatt_server_read_attribute_type.type.len;
    if (rsp->data.rsp_gatt_server_read_attribute_type.type.len <= max_type_size) {
        memcpy(type,rsp->data.rsp_gatt_server_read_attribute_type.type.data,rsp->data.rsp_gatt_server_read_attribute_type.type.len);
    }
    return rsp->data.rsp_gatt_server_read_attribute_type.result;

}

sl_status_t sl_bt_gatt_server_write_attribute_value(uint16_t attribute,
                                                    uint16_t offset,
                                                    size_t value_len,
                                                    const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_write_attribute_value.attribute=attribute;
    cmd->data.cmd_gatt_server_write_attribute_value.offset=offset;
    cmd->data.cmd_gatt_server_write_attribute_value.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_write_attribute_value.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_write_attribute_value_id+(((5+value_len)&0xff)<<8)+(((5+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_write_attribute_value.result;

}

sl_status_t sl_bt_gatt_server_send_user_read_response(uint8_t connection,
                                                      uint16_t characteristic,
                                                      uint8_t att_errorcode,
                                                      size_t value_len,
                                                      const uint8_t* value,
                                                      uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_read_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_read_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_read_response.att_errorcode=att_errorcode;
    cmd->data.cmd_gatt_server_send_user_read_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_user_read_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_user_read_response_id+(((5+value_len)&0xff)<<8)+(((5+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *sent_len = rsp->data.rsp_gatt_server_send_user_read_response.sent_len;
    return rsp->data.rsp_gatt_server_send_user_read_response.result;

}

sl_status_t sl_bt_gatt_server_send_user_write_response(uint8_t connection,
                                                       uint16_t characteristic,
                                                       uint8_t att_errorcode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_write_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_write_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_write_response.att_errorcode=att_errorcode;

    cmd->header=sl_bt_cmd_gatt_server_send_user_write_response_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_user_write_response.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_gatt_server_send_characteristic_notification(uint8_t connection,
                                                               uint16_t characteristic,
                                                               size_t value_len,
                                                               const uint8_t* value,
                                                               uint16_t *sent_len) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_characteristic_notification.connection=connection;
    cmd->data.cmd_gatt_server_send_characteristic_notification.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_characteristic_notification.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_characteristic_notification.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_characteristic_notification_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *sent_len = rsp->data.rsp_gatt_server_send_characteristic_notification.sent_len;
    return rsp->data.rsp_gatt_server_send_characteristic_notification.result;

}

sl_status_t sl_bt_gatt_server_send_notification(uint8_t connection,
                                                uint16_t characteristic,
                                                size_t value_len,
                                                const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_notification.connection=connection;
    cmd->data.cmd_gatt_server_send_notification.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_notification.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_notification.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_notification_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_notification.result;

}

sl_status_t sl_bt_gatt_server_send_indication(uint8_t connection,
                                              uint16_t characteristic,
                                              size_t value_len,
                                              const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_indication.connection=connection;
    cmd->data.cmd_gatt_server_send_indication.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_indication.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_indication.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_indication_id+(((4+value_len)&0xff)<<8)+(((4+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_indication.result;

}

sl_status_t sl_bt_gatt_server_notify_all(uint16_t characteristic,
                                         size_t value_len,
                                         const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_notify_all.characteristic=characteristic;
    cmd->data.cmd_gatt_server_notify_all.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_notify_all.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_notify_all_id+(((3+value_len)&0xff)<<8)+(((3+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_notify_all.result;

}

sl_status_t sl_bt_gatt_server_read_client_configuration(uint8_t connection,
                                                        uint16_t characteristic,
                                                        uint16_t *client_config_flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_read_client_configuration.connection=connection;
    cmd->data.cmd_gatt_server_read_client_configuration.characteristic=characteristic;

    cmd->header=sl_bt_cmd_gatt_server_read_client_configuration_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    *client_config_flags = rsp->data.rsp_gatt_server_read_client_configuration.client_config_flags;
    return rsp->data.rsp_gatt_server_read_client_configuration.result;

}

sl_status_t sl_bt_gatt_server_send_user_prepare_write_response(uint8_t connection,
                                                               uint16_t characteristic,
                                                               uint8_t att_errorcode,
                                                               uint16_t offset,
                                                               size_t value_len,
                                                               const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_gatt_server_send_user_prepare_write_response.connection=connection;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.characteristic=characteristic;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.att_errorcode=att_errorcode;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.offset=offset;
    cmd->data.cmd_gatt_server_send_user_prepare_write_response.value.len=value_len;
    memcpy(cmd->data.cmd_gatt_server_send_user_prepare_write_response.value.data,value,value_len);

    cmd->header=sl_bt_cmd_gatt_server_send_user_prepare_write_response_id+(((7+value_len)&0xff)<<8)+(((7+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_gatt_server_send_user_prepare_write_response.result;

}

sl_status_t sl_bt_nvm_save(uint16_t key,
                           size_t value_len,
                           const uint8_t* value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_save.key=key;
    cmd->data.cmd_nvm_save.value.len=value_len;
    memcpy(cmd->data.cmd_nvm_save.value.data,value,value_len);

    cmd->header=sl_bt_cmd_nvm_save_id+(((3+value_len)&0xff)<<8)+(((3+value_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_save.result;

}

sl_status_t sl_bt_nvm_load(uint16_t key,
                           size_t max_value_size,
                           size_t *value_len,
                           uint8_t *value) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_load.key=key;

    cmd->header=sl_bt_cmd_nvm_load_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    *value_len = rsp->data.rsp_nvm_load.value.len;
    if (rsp->data.rsp_nvm_load.value.len <= max_value_size) {
        memcpy(value,rsp->data.rsp_nvm_load.value.data,rsp->data.rsp_nvm_load.value.len);
    }
    return rsp->data.rsp_nvm_load.result;

}

sl_status_t sl_bt_nvm_erase(uint16_t key) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_nvm_erase.key=key;

    cmd->header=sl_bt_cmd_nvm_erase_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_erase.result;

}

sl_status_t sl_bt_nvm_erase_all() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_nvm_erase_all_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_nvm_erase_all.result;

}

SL_BGAPI_DEPRECATED sl_status_t sl_bt_test_dtm_tx(uint8_t packet_type,
                              uint8_t length,
                              uint8_t channel,
                              uint8_t phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_tx.packet_type=packet_type;
    cmd->data.cmd_test_dtm_tx.length=length;
    cmd->data.cmd_test_dtm_tx.channel=channel;
    cmd->data.cmd_test_dtm_tx.phy=phy;

    cmd->header=sl_bt_cmd_test_dtm_tx_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_tx.result;

}

sl_status_t sl_bt_test_dtm_tx_v4(uint8_t packet_type,
                                 uint8_t length,
                                 uint8_t channel,
                                 uint8_t phy,
                                 int8_t power_level) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_tx_v4.packet_type=packet_type;
    cmd->data.cmd_test_dtm_tx_v4.length=length;
    cmd->data.cmd_test_dtm_tx_v4.channel=channel;
    cmd->data.cmd_test_dtm_tx_v4.phy=phy;
    cmd->data.cmd_test_dtm_tx_v4.power_level=power_level;

    cmd->header=sl_bt_cmd_test_dtm_tx_v4_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_tx_v4.result;

}

sl_status_t sl_bt_test_dtm_rx(uint8_t channel, uint8_t phy) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_test_dtm_rx.channel=channel;
    cmd->data.cmd_test_dtm_rx.phy=phy;

    cmd->header=sl_bt_cmd_test_dtm_rx_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_rx.result;

}

sl_status_t sl_bt_test_dtm_end() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_test_dtm_end_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_test_dtm_end.result;

}

sl_status_t sl_bt_sm_configure(uint8_t flags, uint8_t io_capabilities) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_configure.flags=flags;
    cmd->data.cmd_sm_configure.io_capabilities=io_capabilities;

    cmd->header=sl_bt_cmd_sm_configure_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_configure.result;

}

sl_status_t sl_bt_sm_set_minimum_key_size(uint8_t minimum_key_size) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_minimum_key_size.minimum_key_size=minimum_key_size;

    cmd->header=sl_bt_cmd_sm_set_minimum_key_size_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_minimum_key_size.result;

}

sl_status_t sl_bt_sm_set_debug_mode() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_sm_set_debug_mode_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_debug_mode.result;

}

sl_status_t sl_bt_sm_add_to_whitelist(bd_addr address, uint8_t address_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    memcpy(&cmd->data.cmd_sm_add_to_whitelist.address,&address,sizeof(bd_addr));
    cmd->data.cmd_sm_add_to_whitelist.address_type=address_type;

    cmd->header=sl_bt_cmd_sm_add_to_whitelist_id+(((7)&0xff)<<8)+(((7)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_add_to_whitelist.result;

}

sl_status_t sl_bt_sm_store_bonding_configuration(uint8_t max_bonding_count,
                                                 uint8_t policy_flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_store_bonding_configuration.max_bonding_count=max_bonding_count;
    cmd->data.cmd_sm_store_bonding_configuration.policy_flags=policy_flags;

    cmd->header=sl_bt_cmd_sm_store_bonding_configuration_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_store_bonding_configuration.result;

}

sl_status_t sl_bt_sm_set_bondable_mode(uint8_t bondable) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_bondable_mode.bondable=bondable;

    cmd->header=sl_bt_cmd_sm_set_bondable_mode_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_bondable_mode.result;

}

sl_status_t sl_bt_sm_set_passkey(int32_t passkey) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_passkey.passkey=passkey;

    cmd->header=sl_bt_cmd_sm_set_passkey_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_passkey.result;

}

sl_status_t sl_bt_sm_set_oob_data(size_t oob_data_len, const uint8_t* oob_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_oob_data.oob_data.len=oob_data_len;
    memcpy(cmd->data.cmd_sm_set_oob_data.oob_data.data,oob_data,oob_data_len);

    cmd->header=sl_bt_cmd_sm_set_oob_data_id+(((1+oob_data_len)&0xff)<<8)+(((1+oob_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_oob_data.result;

}

sl_status_t sl_bt_sm_use_sc_oob(uint8_t enable,
                                size_t max_oob_data_size,
                                size_t *oob_data_len,
                                uint8_t *oob_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_use_sc_oob.enable=enable;

    cmd->header=sl_bt_cmd_sm_use_sc_oob_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *oob_data_len = rsp->data.rsp_sm_use_sc_oob.oob_data.len;
    if (rsp->data.rsp_sm_use_sc_oob.oob_data.len <= max_oob_data_size) {
        memcpy(oob_data,rsp->data.rsp_sm_use_sc_oob.oob_data.data,rsp->data.rsp_sm_use_sc_oob.oob_data.len);
    }
    return rsp->data.rsp_sm_use_sc_oob.result;

}

sl_status_t sl_bt_sm_set_sc_remote_oob_data(size_t oob_data_len,
                                            const uint8_t* oob_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_set_sc_remote_oob_data.oob_data.len=oob_data_len;
    memcpy(cmd->data.cmd_sm_set_sc_remote_oob_data.oob_data.data,oob_data,oob_data_len);

    cmd->header=sl_bt_cmd_sm_set_sc_remote_oob_data_id+(((1+oob_data_len)&0xff)<<8)+(((1+oob_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_set_sc_remote_oob_data.result;

}

sl_status_t sl_bt_sm_increase_security(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_increase_security.connection=connection;

    cmd->header=sl_bt_cmd_sm_increase_security_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_increase_security.result;

}

sl_status_t sl_bt_sm_enter_passkey(uint8_t connection, int32_t passkey) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_enter_passkey.connection=connection;
    cmd->data.cmd_sm_enter_passkey.passkey=passkey;

    cmd->header=sl_bt_cmd_sm_enter_passkey_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_enter_passkey.result;

}

sl_status_t sl_bt_sm_passkey_confirm(uint8_t connection, uint8_t confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_passkey_confirm.connection=connection;
    cmd->data.cmd_sm_passkey_confirm.confirm=confirm;

    cmd->header=sl_bt_cmd_sm_passkey_confirm_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_passkey_confirm.result;

}

sl_status_t sl_bt_sm_bonding_confirm(uint8_t connection, uint8_t confirm) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_bonding_confirm.connection=connection;
    cmd->data.cmd_sm_bonding_confirm.confirm=confirm;

    cmd->header=sl_bt_cmd_sm_bonding_confirm_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_bonding_confirm.result;

}

sl_status_t sl_bt_sm_list_all_bondings() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_sm_list_all_bondings_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_list_all_bondings.result;

}

sl_status_t sl_bt_sm_delete_bonding(uint8_t bonding) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_sm_delete_bonding.bonding=bonding;

    cmd->header=sl_bt_cmd_sm_delete_bonding_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_delete_bonding.result;

}

sl_status_t sl_bt_sm_delete_bondings() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_sm_delete_bondings_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_sm_delete_bondings.result;

}

sl_status_t sl_bt_ota_set_device_name(size_t name_len, const uint8_t* name) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_device_name.name.len=name_len;
    memcpy(cmd->data.cmd_ota_set_device_name.name.data,name,name_len);

    cmd->header=sl_bt_cmd_ota_set_device_name_id+(((1+name_len)&0xff)<<8)+(((1+name_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_device_name.result;

}

sl_status_t sl_bt_ota_set_advertising_data(uint8_t packet_type,
                                           size_t adv_data_len,
                                           const uint8_t* adv_data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_advertising_data.packet_type=packet_type;
    cmd->data.cmd_ota_set_advertising_data.adv_data.len=adv_data_len;
    memcpy(cmd->data.cmd_ota_set_advertising_data.adv_data.data,adv_data,adv_data_len);

    cmd->header=sl_bt_cmd_ota_set_advertising_data_id+(((2+adv_data_len)&0xff)<<8)+(((2+adv_data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_advertising_data.result;

}

sl_status_t sl_bt_ota_set_configuration(uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_configuration.flags=flags;

    cmd->header=sl_bt_cmd_ota_set_configuration_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_configuration.result;

}

sl_status_t sl_bt_ota_set_rf_path(uint8_t enable, uint8_t antenna) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_ota_set_rf_path.enable=enable;
    cmd->data.cmd_ota_set_rf_path.antenna=antenna;

    cmd->header=sl_bt_cmd_ota_set_rf_path_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_ota_set_rf_path.result;

}

sl_status_t sl_bt_coex_set_options(uint32_t mask, uint32_t options) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_options.mask=mask;
    cmd->data.cmd_coex_set_options.options=options;

    cmd->header=sl_bt_cmd_coex_set_options_id+(((8)&0xff)<<8)+(((8)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_options.result;

}

sl_status_t sl_bt_coex_set_parameters(uint8_t priority,
                                      uint8_t request,
                                      uint8_t pwm_period,
                                      uint8_t pwm_dutycycle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_parameters.priority=priority;
    cmd->data.cmd_coex_set_parameters.request=request;
    cmd->data.cmd_coex_set_parameters.pwm_period=pwm_period;
    cmd->data.cmd_coex_set_parameters.pwm_dutycycle=pwm_dutycycle;

    cmd->header=sl_bt_cmd_coex_set_parameters_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_parameters.result;

}

sl_status_t sl_bt_coex_set_directional_priority_pulse(uint8_t pulse) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_set_directional_priority_pulse.pulse=pulse;

    cmd->header=sl_bt_cmd_coex_set_directional_priority_pulse_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_coex_set_directional_priority_pulse.result;

}

sl_status_t sl_bt_coex_get_counters(uint8_t reset,
                                    size_t max_counters_size,
                                    size_t *counters_len,
                                    uint8_t *counters) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_coex_get_counters.reset=reset;

    cmd->header=sl_bt_cmd_coex_get_counters_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    *counters_len = rsp->data.rsp_coex_get_counters.counters.len;
    if (rsp->data.rsp_coex_get_counters.counters.len <= max_counters_size) {
        memcpy(counters,rsp->data.rsp_coex_get_counters.counters.data,rsp->data.rsp_coex_get_counters.counters.len);
    }
    return rsp->data.rsp_coex_get_counters.result;

}

sl_status_t sl_bt_l2cap_coc_send_connection_request(uint8_t connection,
                                                    uint16_t le_psm,
                                                    uint16_t mtu,
                                                    uint16_t mps,
                                                    uint16_t initial_credit) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_coc_send_connection_request.connection=connection;
    cmd->data.cmd_l2cap_coc_send_connection_request.le_psm=le_psm;
    cmd->data.cmd_l2cap_coc_send_connection_request.mtu=mtu;
    cmd->data.cmd_l2cap_coc_send_connection_request.mps=mps;
    cmd->data.cmd_l2cap_coc_send_connection_request.initial_credit=initial_credit;

    cmd->header=sl_bt_cmd_l2cap_coc_send_connection_request_id+(((9)&0xff)<<8)+(((9)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_coc_send_connection_request.result;

}

sl_status_t sl_bt_l2cap_coc_send_connection_response(uint8_t connection,
                                                     uint16_t cid,
                                                     uint16_t mtu,
                                                     uint16_t mps,
                                                     uint16_t initial_credit,
                                                     uint16_t l2cap_errorcode) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_coc_send_connection_response.connection=connection;
    cmd->data.cmd_l2cap_coc_send_connection_response.cid=cid;
    cmd->data.cmd_l2cap_coc_send_connection_response.mtu=mtu;
    cmd->data.cmd_l2cap_coc_send_connection_response.mps=mps;
    cmd->data.cmd_l2cap_coc_send_connection_response.initial_credit=initial_credit;
    cmd->data.cmd_l2cap_coc_send_connection_response.l2cap_errorcode=l2cap_errorcode;

    cmd->header=sl_bt_cmd_l2cap_coc_send_connection_response_id+(((11)&0xff)<<8)+(((11)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_coc_send_connection_response.result;

}

sl_status_t sl_bt_l2cap_coc_send_le_flow_control_credit(uint8_t connection,
                                                        uint16_t cid,
                                                        uint16_t credits) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_coc_send_le_flow_control_credit.connection=connection;
    cmd->data.cmd_l2cap_coc_send_le_flow_control_credit.cid=cid;
    cmd->data.cmd_l2cap_coc_send_le_flow_control_credit.credits=credits;

    cmd->header=sl_bt_cmd_l2cap_coc_send_le_flow_control_credit_id+(((5)&0xff)<<8)+(((5)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_coc_send_le_flow_control_credit.result;

}

sl_status_t sl_bt_l2cap_coc_send_disconnection_request(uint8_t connection,
                                                       uint16_t cid) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_coc_send_disconnection_request.connection=connection;
    cmd->data.cmd_l2cap_coc_send_disconnection_request.cid=cid;

    cmd->header=sl_bt_cmd_l2cap_coc_send_disconnection_request_id+(((3)&0xff)<<8)+(((3)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_coc_send_disconnection_request.result;

}

sl_status_t sl_bt_l2cap_coc_send_data(uint8_t connection,
                                      uint16_t cid,
                                      size_t data_len,
                                      const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_l2cap_coc_send_data.connection=connection;
    cmd->data.cmd_l2cap_coc_send_data.cid=cid;
    cmd->data.cmd_l2cap_coc_send_data.data.len=data_len;
    memcpy(cmd->data.cmd_l2cap_coc_send_data.data.data,data,data_len);

    cmd->header=sl_bt_cmd_l2cap_coc_send_data_id+(((4+data_len)&0xff)<<8)+(((4+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_l2cap_coc_send_data.result;

}

sl_status_t sl_bt_cte_transmitter_set_dtm_parameters(uint8_t cte_length,
                                                     uint8_t cte_type,
                                                     size_t switching_pattern_len,
                                                     const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_set_dtm_parameters.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_set_dtm_parameters.cte_type=cte_type;
    cmd->data.cmd_cte_transmitter_set_dtm_parameters.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_set_dtm_parameters.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_set_dtm_parameters_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_set_dtm_parameters.result;

}

sl_status_t sl_bt_cte_transmitter_clear_dtm_parameters() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_transmitter_clear_dtm_parameters_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_clear_dtm_parameters.result;

}

sl_status_t sl_bt_cte_transmitter_enable_connection_cte(uint8_t connection,
                                                        uint8_t cte_types,
                                                        size_t switching_pattern_len,
                                                        const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_connection_cte.connection=connection;
    cmd->data.cmd_cte_transmitter_enable_connection_cte.cte_types=cte_types;
    cmd->data.cmd_cte_transmitter_enable_connection_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_connection_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_connection_cte_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_connection_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_connection_cte(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_connection_cte.connection=connection;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_connection_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_connection_cte.result;

}

sl_status_t sl_bt_cte_transmitter_enable_connectionless_cte(uint8_t handle,
                                                            uint8_t cte_length,
                                                            uint8_t cte_type,
                                                            uint8_t cte_count,
                                                            size_t switching_pattern_len,
                                                            const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.handle=handle;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_type=cte_type;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.cte_count=cte_count;
    cmd->data.cmd_cte_transmitter_enable_connectionless_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_connectionless_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_connectionless_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_connectionless_cte(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_connectionless_cte.handle=handle;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_connectionless_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_transmitter_enable_silabs_cte(uint8_t handle,
                                                    uint8_t cte_length,
                                                    uint8_t cte_type,
                                                    uint8_t cte_count,
                                                    size_t switching_pattern_len,
                                                    const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_enable_silabs_cte.handle=handle;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_length=cte_length;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_type=cte_type;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.cte_count=cte_count;
    cmd->data.cmd_cte_transmitter_enable_silabs_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_transmitter_enable_silabs_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_transmitter_enable_silabs_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_enable_silabs_cte.result;

}

sl_status_t sl_bt_cte_transmitter_disable_silabs_cte(uint8_t handle) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_transmitter_disable_silabs_cte.handle=handle;

    cmd->header=sl_bt_cmd_cte_transmitter_disable_silabs_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_transmitter_disable_silabs_cte.result;

}

sl_status_t sl_bt_cte_receiver_set_dtm_parameters(uint8_t cte_length,
                                                  uint8_t cte_type,
                                                  uint8_t slot_durations,
                                                  size_t switching_pattern_len,
                                                  const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_dtm_parameters.cte_length=cte_length;
    cmd->data.cmd_cte_receiver_set_dtm_parameters.cte_type=cte_type;
    cmd->data.cmd_cte_receiver_set_dtm_parameters.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_set_dtm_parameters.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_set_dtm_parameters.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_set_dtm_parameters_id+(((4+switching_pattern_len)&0xff)<<8)+(((4+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_dtm_parameters.result;

}

sl_status_t sl_bt_cte_receiver_clear_dtm_parameters() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_receiver_clear_dtm_parameters_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_clear_dtm_parameters.result;

}

sl_status_t sl_bt_cte_receiver_set_sync_cte_type(uint8_t sync_cte_type) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_set_sync_cte_type.sync_cte_type=sync_cte_type;

    cmd->header=sl_bt_cmd_cte_receiver_set_sync_cte_type_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_set_sync_cte_type.result;

}

sl_status_t sl_bt_cte_receiver_configure(uint8_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_configure.flags=flags;

    cmd->header=sl_bt_cmd_cte_receiver_configure_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_configure.result;

}

sl_status_t sl_bt_cte_receiver_enable_connection_cte(uint8_t connection,
                                                     uint16_t interval,
                                                     uint8_t cte_length,
                                                     uint8_t cte_type,
                                                     uint8_t slot_durations,
                                                     size_t switching_pattern_len,
                                                     const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_connection_cte.connection=connection;
    cmd->data.cmd_cte_receiver_enable_connection_cte.interval=interval;
    cmd->data.cmd_cte_receiver_enable_connection_cte.cte_length=cte_length;
    cmd->data.cmd_cte_receiver_enable_connection_cte.cte_type=cte_type;
    cmd->data.cmd_cte_receiver_enable_connection_cte.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_enable_connection_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_connection_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_connection_cte_id+(((7+switching_pattern_len)&0xff)<<8)+(((7+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_connection_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_connection_cte(uint8_t connection) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_disable_connection_cte.connection=connection;

    cmd->header=sl_bt_cmd_cte_receiver_disable_connection_cte_id+(((1)&0xff)<<8)+(((1)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_connection_cte.result;

}

sl_status_t sl_bt_cte_receiver_enable_connectionless_cte(uint16_t sync,
                                                         uint8_t slot_durations,
                                                         uint8_t cte_count,
                                                         size_t switching_pattern_len,
                                                         const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_connectionless_cte.sync=sync;
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.cte_count=cte_count;
    cmd->data.cmd_cte_receiver_enable_connectionless_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_connectionless_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_connectionless_cte_id+(((5+switching_pattern_len)&0xff)<<8)+(((5+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_connectionless_cte(uint16_t sync) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_disable_connectionless_cte.sync=sync;

    cmd->header=sl_bt_cmd_cte_receiver_disable_connectionless_cte_id+(((2)&0xff)<<8)+(((2)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_connectionless_cte.result;

}

sl_status_t sl_bt_cte_receiver_enable_silabs_cte(uint8_t slot_durations,
                                                 uint8_t cte_count,
                                                 size_t switching_pattern_len,
                                                 const uint8_t* switching_pattern) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_cte_receiver_enable_silabs_cte.slot_durations=slot_durations;
    cmd->data.cmd_cte_receiver_enable_silabs_cte.cte_count=cte_count;
    cmd->data.cmd_cte_receiver_enable_silabs_cte.switching_pattern.len=switching_pattern_len;
    memcpy(cmd->data.cmd_cte_receiver_enable_silabs_cte.switching_pattern.data,switching_pattern,switching_pattern_len);

    cmd->header=sl_bt_cmd_cte_receiver_enable_silabs_cte_id+(((3+switching_pattern_len)&0xff)<<8)+(((3+switching_pattern_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_enable_silabs_cte.result;

}

sl_status_t sl_bt_cte_receiver_disable_silabs_cte() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_cte_receiver_disable_silabs_cte_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_cte_receiver_disable_silabs_cte.result;

}

sl_status_t sl_bt_memory_profiler_get_status(uint32_t *num_memory_trackers,
                                             uint32_t *num_live_allocations,
                                             uint32_t *peak_live_allocations,
                                             uint32_t *num_heap_bytes_used,
                                             uint32_t *peak_heap_bytes_used,
                                             uint32_t *peak_stack_bytes_used,
                                             uint32_t *errors) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_memory_profiler_get_status_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    *num_memory_trackers = rsp->data.rsp_memory_profiler_get_status.num_memory_trackers;
    *num_live_allocations = rsp->data.rsp_memory_profiler_get_status.num_live_allocations;
    *peak_live_allocations = rsp->data.rsp_memory_profiler_get_status.peak_live_allocations;
    *num_heap_bytes_used = rsp->data.rsp_memory_profiler_get_status.num_heap_bytes_used;
    *peak_heap_bytes_used = rsp->data.rsp_memory_profiler_get_status.peak_heap_bytes_used;
    *peak_stack_bytes_used = rsp->data.rsp_memory_profiler_get_status.peak_stack_bytes_used;
    *errors = rsp->data.rsp_memory_profiler_get_status.errors;
    return rsp->data.rsp_memory_profiler_get_status.result;

}

sl_status_t sl_bt_memory_profiler_reset(uint32_t flags) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_memory_profiler_reset.flags=flags;

    cmd->header=sl_bt_cmd_memory_profiler_reset_id+(((4)&0xff)<<8)+(((4)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_memory_profiler_reset.result;

}

sl_status_t sl_bt_memory_profiler_list_ram_usage() {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;


    cmd->header=sl_bt_cmd_memory_profiler_list_ram_usage_id+(((0)&0xff)<<8)+(((0)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_memory_profiler_list_ram_usage.result;

}

sl_status_t sl_bt_user_message_to_target(size_t data_len,
                                         const uint8_t* data,
                                         size_t max_response_size,
                                         size_t *response_len,
                                         uint8_t *response) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_user_message_to_target.data.len=data_len;
    memcpy(cmd->data.cmd_user_message_to_target.data.data,data,data_len);

    cmd->header=sl_bt_cmd_user_message_to_target_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    *response_len = rsp->data.rsp_user_message_to_target.response.len;
    if (rsp->data.rsp_user_message_to_target.response.len <= max_response_size) {
        memcpy(response,rsp->data.rsp_user_message_to_target.response.data,rsp->data.rsp_user_message_to_target.response.len);
    }
    return rsp->data.rsp_user_message_to_target.result;

}

sl_status_t sl_bt_user_manage_event_filter(size_t data_len,
                                           const uint8_t* data) {
    struct sl_bt_packet *cmd = (struct sl_bt_packet *)sl_bt_cmd_msg;

    struct sl_bt_packet *rsp = (struct sl_bt_packet *)sl_bt_rsp_msg;

    cmd->data.cmd_user_manage_event_filter.data.len=data_len;
    memcpy(cmd->data.cmd_user_manage_event_filter.data.data,data,data_len);

    cmd->header=sl_bt_cmd_user_manage_event_filter_id+(((1+data_len)&0xff)<<8)+(((1+data_len)&0x700)>>8);


    sl_bt_host_handle_command();
    return rsp->data.rsp_user_manage_event_filter.result;

}
