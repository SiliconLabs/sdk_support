#ifndef SL_COMPONENT_CATALOG_H
#define SL_COMPONENT_CATALOG_H

// APIs present in project
#define SL_CATALOG_BLUETOOTH_CONFIGURATION_PRESENT

#define SL_CATALOG_BLUETOOTH_FEATURE_ADVERTISER_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_CONNECTION_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_GAP_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_GATT_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_GATT_SERVER_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_LEGACY_ADVERTISER_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_NVM_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_SCANNER_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_SM_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_SYSTEM_PRESENT
#define SL_CATALOG_BLUETOOTH_PRESENT
#define SL_CATALOG_BLUETOOTH_FEATURE_MULTIPROTOCOL_PRESENT
#define SL_CATALOG_GECKO_BOOTLOADER_INTERFACE_PRESENT
#define SL_CATALOG_DEVICE_INIT_NVIC_PRESENT
#define SL_CATALOG_EMLIB_CORE_DEBUG_CONFIG_PRESENT
#define SL_CATALOG_FREERTOS_KERNEL_PRESENT
#define SL_CATALOG_KERNEL_PRESENT
#define SL_CATALOG_GATT_CONFIGURATION_PRESENT

/*
    This devices does not support LCD
    Removing all the LCD components
*/
#define SL_CATALOG_NVM3_PRESENT
#define SL_CATALOG_PSA_CRYPTO_PRESENT
#define SL_CATALOG_RAIL_LIB_PRESENT
#define SL_CATALOG_RAIL_UTIL_PTI_PRESENT
#define SL_CATALOG_BTN0_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN0_PRESENT
#define SL_CATALOG_BTN1_PRESENT
#define SL_CATALOG_SIMPLE_BUTTON_BTN1_PRESENT

/*
    This devices does not support LEDs and Buttons at the same time.
    Removing all the LED components
*/


#if CHIP_DEVICE_CONFIG_ENABLE_SED
#define SL_CATALOG_POWER_MANAGER_PRESENT
#define SL_CATALOG_SLEEPTIMER_PRESENT
#endif // CHIP_DEVICE_CONFIG_ENABLE_SED
#define SL_CATALOG_SLI_PROTOCOL_CRYPTO_PRESENT
/*
	This device does not support an external flash.
	Removing Defines relating to MX25 Flash components
*/

#define SL_CATALOG_UARTDRV_EUSART_PRESENT

#endif // SL_COMPONENT_CATALOG_H
