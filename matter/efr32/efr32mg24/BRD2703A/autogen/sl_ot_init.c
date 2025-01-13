
#include "sl_ot_init.h"
// TODO: Remove the Power Manager include when OT does not add an EM1 req at init
#define CURRENT_MODULE_NAME "OPENTHREAD"
#include "sl_power_manager.h"

void sl_ot_init(void)
{
    sl_ot_create_instance();
    sl_ot_sleep_init();

    // TODO: Remove the Power Manager remove req when OT does not add an EM1 req at init
    sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);

    sl_ot_cli_init();
    sl_ot_custom_cli_init();
}