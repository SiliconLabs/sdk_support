#ifndef SL_MATTER_CONFIG_H
#define SL_MATTER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_MATTER_STACK_LOCK_TRACKING_MODE> Stack Lock Tracking Mode
// <SL_MATTER_STACK_LOCK_TRACKING_NONE=> None
// <SL_MATTER_STACK_LOCK_TRACKING_LOG=> Log
// <SL_MATTER_STACK_LOCK_TRACKING_FATAL=> Fatal
// <d> SL_MATTER_STACK_LOCK_TRACKING_FATAL
#define SL_MATTER_STACK_LOCK_TRACKING_MODE  SL_MATTER_STACK_LOCK_TRACKING_FATAL

// <o SL_MATTER_LOG_LEVEL> Log Level
// <SL_MATTER_LOG_NONE=> None
// <SL_MATTER_LOG_ERROR=> Error
// <SL_MATTER_LOG_PROGRESS=> Progress
// <SL_MATTER_LOG_DETAIL=> Detailed log (debug)
// <SL_MATTER_LOG_AUTOMATION=> Automation
// <d> SL_MATTER_LOG_ERROR
#ifndef SL_MATTER_LOG_LEVEL
#define SL_MATTER_LOG_LEVEL SL_MATTER_LOG_DETAIL
#endif

// <q SILABS_LOG_ENABLED> Enable Silabs specific log used in matter
#ifndef SILABS_LOG_ENABLED
#define SILABS_LOG_ENABLED 1
#endif

// <q HARD_FAULT_LOG_ENABLE> Enable hard fault logging
#ifndef HARD_FAULT_LOG_ENABLE
#define HARD_FAULT_LOG_ENABLE 1
#endif

// <o CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION> Device software version
#define CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION 1

// <s CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION_STRING> Device software version string
#define CHIP_DEVICE_CONFIG_DEVICE_SOFTWARE_VERSION_STRING "1"

// <o CHIP_DEVICE_CONFIG_DEFAULT_DEVICE_HARDWARE_VERSION> Device hardware version
#define CHIP_DEVICE_CONFIG_DEFAULT_DEVICE_HARDWARE_VERSION 1

// <q SL_MATTER_CLI_ARG_PARSER> Enable CLI Argument Parser
#ifndef SL_MATTER_CLI_ARG_PARSER
#define SL_MATTER_CLI_ARG_PARSER 1
#endif

// <o CHIP_DEVICE_CONFIG_MAX_DISCOVERED_IP_ADDRESSES> Define the default number of ip addresses to discover
#define CHIP_DEVICE_CONFIG_MAX_DISCOVERED_IP_ADDRESSES 5

// <o KVS_MAX_ENTRIES> Maximum amount of KVS Entries
#define KVS_MAX_ENTRIES 255

// GN flag that needs to be defined for Matter 1.2 to build
// See: https://github.com/project-chip/connectedhomeip/pull/28149 add chip_enable_read_client in common_flags.gni
#define CHIP_CONFIG_ENABLE_READ_CLIENT 1

// <o ICD_MAX_NOTIFICATION_SUBSCRIBERS> Maximum amount of ICD notification subscribers
#define ICD_MAX_NOTIFICATION_SUBSCRIBERS 1

// <<< end of configuration section >>>

#endif // SL_MATTER_CONFIG_H
