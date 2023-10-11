#include "sl_event_handler.h"

#include "cmsis_os2.h"
#include "rsi_board.h"
#include "rsi_chip.h"
#include "rsi_nvic_priorities_config.h"
#include "rsi_wisemcu_hardware_setup.h"
#include "sl_device_init_nvic.h"
#include "sl_iostream_init_instances.h"
#include "sl_iostream_rtt.h"
#include "sl_si91x_button_instances.h"
#include "sli_siwx917_soc.h"

void sl_platform_init(void) {
  SystemCoreClockUpdate();
  sl_si91x_device_init_nvic();
  sl_device_init_nvic();
  sli_si91x_platform_init();
  RSI_Board_Init();
  osKernelInitialize();
}

void sl_kernel_start(void) { osKernelStart(); }

void sl_driver_init(void) { button_init_instances(); }

void sl_service_init(void) { sl_iostream_init_instances(); }

void sl_stack_init(void) {}

void sl_internal_app_init(void) {}

void sl_iostream_init_instances(void) { sl_iostream_rtt_init(); }
