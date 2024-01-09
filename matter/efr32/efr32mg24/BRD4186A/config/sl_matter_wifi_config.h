#ifndef SL_MATTER_WIFI_CONFIG
#define SL_MATTER_WIFI_CONFIG

// <<< Use Configuration Wizard in Context Menu >>>
// <o WIFI_ENABLE_SECURITY_WPA3_TRANSITION> CHANGE WIFI SECURITY
// <i> Default: 0
// <WIFI_ENABLE_SECURITY_WPA3_TRANSITION=> 1
// <d> WIFI_ENABLE_SECURITY_WPA3_TRANSITION
// <q WIFI_ENABLE_SECURITY_WPA3_TRANSITION > WIFI SECURITY MODE
#define WIFI_ENABLE_SECURITY_WPA3_TRANSITION 0

// <o CHIP_DEVICE_CONFIG_ENABLE_IPV4> IP MODES
// <i> Default: 0
// <CHIP_DEVICE_CONFIG_ENABLE_IPV4=> 1
// <d> CHIP_DEVICE_CONFIG_ENABLE_IPV4
// <q CHIP_DEVICE_CONFIG_ENABLE_IPV4 > IP MODES
#ifndef CHIP_DEVICE_CONFIG_ENABLE_IPV4
#define CHIP_DEVICE_CONFIG_ENABLE_IPV4 0
#endif

// <<< end of configuration section >>>
#endif // SL_MATTER_WIFI_CONFIG
