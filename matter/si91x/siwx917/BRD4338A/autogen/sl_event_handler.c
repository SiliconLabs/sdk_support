#include "sl_event_handler.h"

#include "rsi_board.h"
#include "rsi_debug.h"
#include "rsi_nvic_priorities_config.h"
#include "sli_siwx917_soc.h"
#include "system_si91x.h"
#if SL_ICD_ENABLED
#include "rsi_wisemcu_hardware_setup.h"
#include "sl_si91x_power_manager.h"
#include "sl_si91x_power_manager_init.h"
#endif // SL_ICD_ENABLED
#include "SEGGER_RTT.h"
#include "cmsis_os2.h"
#include "sl_iostream_init_instances.h"
#include "sl_iostream_rtt.h"
#include "sl_si91x_button_instances.h"
#include "sl_si91x_led_instances.h"
#include "sl_sleeptimer.h"
#include "sl_ulp_timer_instances.h"

void sl_platform_init(void) {
  SystemCoreClockUpdate();
  sl_si91x_device_init_nvic();
  sli_si91x_platform_init();
  RSI_Board_Init();
  DEBUGINIT();
#if SL_ICD_ENABLED
  sl_si91x_hardware_setup();
#endif // SL_ICD_ENABLED
  osKernelInitialize();
}

void sl_kernel_start(void) { osKernelStart(); }

void sl_driver_init(void) {
  button_init_instances();
  led_init_instances();
}

void sl_service_init(void) {
#if SL_ICD_ENABLED
  sl_si91x_power_manager_init();
  sli_si91x_power_manager_configure_ram_and_peripheral();
#endif // SL_ICD_ENABLED
#ifdef DISPLAY_ENABLED || SL_ICD_ENABLED
  sl_sleeptimer_init();
#endif // DISPLAY_ENABLED || SL_ICD_ENABLED
  sl_iostream_init_instances();
}

void sl_stack_init(void) {}

void sl_internal_app_init(void) {}

void sl_iostream_init_instances(void) { sl_iostream_rtt_init(); }
