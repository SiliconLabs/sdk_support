#ifndef SL_RAIL_TEST_CONFIG_H
#define SL_RAIL_TEST_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> RAILtest Configuration

// <q SL_RAIL_TEST_RADIO_CONFIG_EXTERNAL_SUPPORT_ENABLED> Enable this if providing an external radio configuration (i.e. rail_config.c/h).
// <i> Default: 1
#define SL_RAIL_TEST_RADIO_CONFIG_EXTERNAL_SUPPORT_ENABLED 1

// <o SL_RAIL_TEST_RADIO_CONFIG_DEFAULT> Default Radio Configuration
// <RADIO_CONFIG_EXTERNAL=> External Radio Config (rail_config.c/h)
// <RADIO_CONFIG_EXTERNAL_RMR=> Dynamic Radio Config
// <RADIO_CONFIG_INTERNAL_IEEE802154_GB868_915MHZ=> IEEE 802.15.4 GB868 915MHz
// <RADIO_CONFIG_INTERNAL_IEEE802154_GB868_863MHZ=> IEEE 802.15.4 GB868 863MHz
// <RADIO_CONFIG_INTERNAL_ZWAVE_EU=> Z-Wave Europe
// <RADIO_CONFIG_INTERNAL_ZWAVE_US=> Z-Wave United States
// <RADIO_CONFIG_INTERNAL_ZWAVE_ANZ=> Z-Wave Australia
// <RADIO_CONFIG_INTERNAL_ZWAVE_HK=> Z-Wave Hong Kong
// <RADIO_CONFIG_INTERNAL_ZWAVE_MY=> Z-Wave Malaysia
// <RADIO_CONFIG_INTERNAL_ZWAVE_IN=> Z-Wave India
// <RADIO_CONFIG_INTERNAL_ZWAVE_JP=> Z-Wave Japan
// <RADIO_CONFIG_INTERNAL_ZWAVE_RU=> Z-Wave Russia
// <RADIO_CONFIG_INTERNAL_ZWAVE_IL=> Z-Wave Israel
// <RADIO_CONFIG_INTERNAL_ZWAVE_KR=> Z-Wave Korea
// <RADIO_CONFIG_INTERNAL_ZWAVE_CN=> Z-Wave China
// <i> Default: RADIO_CONFIG_EXTERNAL
#define SL_RAIL_TEST_RADIO_CONFIG_DEFAULT  RADIO_CONFIG_EXTERNAL

// <s.50 SL_RAIL_TEST_APP_NAME> Application name displayed by CLI on boot
// <i> Default: "RAILtest"
#define SL_RAIL_TEST_APP_NAME  "RAILtest"

// <o SL_RAIL_TEST_MAX_PACKET_LENGTH> Maximum packet length
// <i> Default: 1024
#define SL_RAIL_TEST_MAX_PACKET_LENGTH  1024

// <o SL_RAIL_TEST_CONTINUOUS_TRANSFER_PERIOD> Continuous transfer period
// <i> Default: 250
#define SL_RAIL_TEST_CONTINUOUS_TRANSFER_PERIOD  250

// <o SL_RAIL_TEST_TX_BUFFER_SIZE> Transmit buffer size
// <i> Default: 512
#define SL_RAIL_TEST_TX_BUFFER_SIZE  512

// <o SL_RAIL_TEST_RX_BUFFER_SIZE> Receive buffer size
// <i> Default: 512
#define SL_RAIL_TEST_RX_BUFFER_SIZE  512

// <o SL_RAIL_TEST_BUTTON_LONG_HOLD_DURATION_MS> Button Long Press Duration (milliseconds)
// <i> Default: 1000
#define SL_RAIL_TEST_BUTTON_LONG_HOLD_DURATION_MS  1000

// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_RAIL_TEST_PER
// $[GPIO_SL_RAIL_TEST_PER]
#define SL_RAIL_TEST_PER_PORT                    gpioPortC
#define SL_RAIL_TEST_PER_PIN                     2
// [GPIO_SL_RAIL_TEST_PER]$
// <<< sl:end pin_tool >>>

#endif // SL_RAIL_TEST_CONFIG_H
