#include "sl_ot_init.h"

void sl_ot_init(void)
{
  sl_ot_create_instance();
  sl_ot_sleep_init();
  sl_ot_cli_init();
  sl_ot_custom_cli_init();
}