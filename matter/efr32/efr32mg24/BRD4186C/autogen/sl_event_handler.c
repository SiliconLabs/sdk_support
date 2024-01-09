#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_device_init_nvic.h"
#include "sl_board_init.h"
#include "sl_device_init_dcdc.h"
#include "sl_device_init_lfxo.h"
#include "sl_device_init_hfxo.h"
#include "sl_device_init_dpll.h"
#include "sl_device_init_clocks.h"
#include "sl_device_init_emu.h"
#include "sl_rail_util_pti.h"
#include "btl_interface.h"
#include "sl_board_control.h"
#include "sl_sleeptimer.h"
#include "gpiointerrupt.h"
#include "sl_iostream_rtt.h"
#include "sl_mbedtls.h"
#include "sl_mpu.h"
#include "nvm3_default.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "psa/crypto.h"
#include "sli_protocol_crypto.h"
#include "cmsis_os2.h"
#include "sl_iostream_init_instances.h"
#include "sl_bluetooth.h"
#include "sl_power_manager.h"
#if !RSI_BLE_ENABLE
#include "sl_rail_util_power_manager_init.h"
#endif // !RSI_BLE_ENABLE

void sl_platform_init(void)
{
  CHIP_Init();
  sl_device_init_nvic();
  sl_board_preinit();
  sl_device_init_dcdc();
  sl_device_init_lfxo();
  sl_device_init_hfxo();
  sl_device_init_dpll();
  sl_device_init_clocks();
  sl_device_init_emu();
  sl_board_init();
  bootloader_init();
  nvm3_initDefault();
  osKernelInitialize();
}

void sl_kernel_start(void)
{
#if !RSI_BLE_ENABLE
 // sli_bt_rtos_adaptation_kernel_start();
#endif // !RSI_BLE_ENABLE
  osKernelStart();
}

void sl_driver_init(void)
{
  GPIOINT_Init();
  sl_simple_button_init_instances();
  sl_simple_led_init_instances();
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_sleeptimer_init();
  sl_mbedtls_init();
  sl_mpu_disable_execute_from_ram();
  psa_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances();
}

void sl_stack_init(void)
{
#if !RSI_BLE_ENABLE
  sl_rail_util_pti_init();
 // sl_bt_rtos_init();
  sl_rail_util_power_manager_init();
#endif

}

void sl_internal_app_init(void)
{
}

void sl_iostream_init_instances(void)
{
  sl_iostream_rtt_init();
}

