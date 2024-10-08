#include "sl_event_handler.h"

#include "em_chip.h"
#include "sl_interrupt_manager.h"
#include "sl_board_init.h"
#include "sl_clock_manager_init.h"
#include "sl_device_init_dcdc.h"
#include "sl_clock_manager.h"
#include "sl_hfxo_manager.h"
#include "SEGGER_RTT.h"
#include "sl_fem_util.h"
#include "pa_conversions_efr32.h"
#include "sl_rail_util_power_manager_init.h"
#include "sl_rail_util_pti.h"
#include "sl_rail_util_rssi.h"
#include "sl_board_control.h"
#include "sl_bt_rtos_adaptation.h"
#include "platform-efr32.h"
#include "sl_sleeptimer.h"
#include "sl_mpu.h"
#include "gpiointerrupt.h"
#ifdef USE_TEMP_SENSOR
#include "sl_i2cspm_instances.h"
#endif
#include "sl_iostream_rtt.h"
#include "sl_mbedtls.h"
#include "nvm3_default.h"
#include "sl_ot_rtos_adaptation.h"
#include "sl_simple_button_instances.h"
#if defined(CONFIG_ENABLE_UART)
#include "sl_uartdrv_instances.h"
#endif
#include "psa/crypto.h"
#include "sli_protocol_crypto.h"
#include "cmsis_os2.h"
#include "sl_iostream_init_instances.h"
#include "sl_bluetooth.h"
#include "sl_power_manager.h"

void sl_platform_init(void)
{
  CHIP_Init();
  sl_interrupt_manager_init();
  sl_board_preinit();
  sl_clock_manager_init();
  sl_device_init_dcdc();
  sl_clock_manager_runtime_init();
  sl_hfxo_manager_init_hardware();
  SEGGER_RTT_Init();
  sl_board_init();
  nvm3_initDefault();
  osKernelInitialize();
  sl_power_manager_init();
}

void sl_kernel_start(void)
{
  sli_bt_rtos_adaptation_kernel_start();
  osKernelStart();
}

void sl_driver_init(void)
{
  GPIOINT_Init();
#if defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
  sl_i2cspm_init_instances();
#endif // defined(SL_MATTER_USE_SI70XX_SENSOR) && SL_MATTER_USE_SI70XX_SENSOR
  sl_simple_button_init_instances();
#if defined(CONFIG_ENABLE_UART)
  sl_uartdrv_init_instances();
#endif // CONFIG_ENABLE_UART
}

void sl_service_init(void)
{
  sl_board_configure_vcom();
  sl_sleeptimer_init();
  sl_hfxo_manager_init();
  sl_mpu_disable_execute_from_ram();
  sl_mbedtls_init();
  psa_crypto_init();
  sli_aes_seed_mask();
  sl_iostream_init_instances();
}

void sl_stack_init(void)
{
  sl_fem_util_init();
  sl_rail_util_pa_init();
  sl_rail_util_power_manager_init();
  sl_rail_util_pti_init();
  sl_rail_util_rssi_init();
  sl_bt_rtos_init();
  sl_ot_sys_init();
}

void sl_internal_app_init(void)
{
  sl_ot_rtos_stack_init();
  sl_ot_rtos_app_init();
}

void sl_iostream_init_instances(void)
{
  sl_iostream_rtt_init();
}
