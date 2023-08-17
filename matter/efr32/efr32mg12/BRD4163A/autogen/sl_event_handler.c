#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_device_init_nvic.h"
#include "sl_board_init.h"
#include "sl_device_init_dcdc.h"
#include "sl_device_init_hfxo.h"
#include "sl_device_init_lfxo.h"
#include "sl_device_init_clocks.h"
#include "sl_device_init_emu.h"
#include "pa_conversions_efr32.h"
#include "sl_mbedtls.h"
#include "sl_rail_util_pti.h"
#include "sl_board_control.h"
#include "sl_bt_rtos_adaptation.h"
#include "nvm3_default.h"
#include "sl_sleeptimer.h"
#include "gpiointerrupt.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#if defined(CONFIG_ENABLE_UART)
#include "sl_uartdrv_instances.h"
#endif // CONFIG_ENABLE_UART
#include "psa/crypto.h"
#include "cmsis_os2.h"
#include "sl_bluetooth.h"
#include "sl_power_manager.h"

#ifdef SL_WIFI
#include "sl_spidrv_instances.h"
#endif

#ifdef USE_TEMP_SENSOR
#include "sl_i2cspm_instances.h"
#endif

void sl_platform_init(void)
{
    CHIP_Init();
    sl_device_init_nvic();
    sl_board_preinit();
    sl_device_init_dcdc();
    sl_device_init_hfxo();
    sl_device_init_lfxo();
    sl_device_init_clocks();
    sl_device_init_emu();
    sl_board_init();
    nvm3_initDefault();
    osKernelInitialize();
    sl_power_manager_init();
}

void sl_kernel_start(void)
{
    osKernelStart();
}

void sl_driver_init(void)
{
    GPIOINT_Init();
#ifdef SL_WIFI
    sl_spidrv_init_instances();
#endif
#ifdef USE_TEMP_SENSOR
    sl_i2cspm_init_instances();
#endif
    sl_simple_button_init_instances();
    sl_simple_led_init_instances();
#if defined(CONFIG_ENABLE_UART)
    sl_uartdrv_init_instances();
#endif // CONFIG_ENABLE_UART
}

void sl_service_init(void)
{
    sl_sleeptimer_init();
    sl_mbedtls_init();
    psa_crypto_init();
}

void sl_stack_init(void)
{
    sl_rail_util_pa_init();
    sl_rail_util_pti_init();
#if !RSI_BLE_ENABLE
    sl_bt_rtos_init();
#endif
}

void sl_internal_app_init(void)
{
}
