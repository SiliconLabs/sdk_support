#include "sl_iostream.h"
#include "sl_iostream_handles.h"
#include "string.h"

const sl_iostream_instance_info_t *sl_iostream_instances_info[] = {

    &sl_iostream_instance_rtt_info,
  
};

const uint32_t sl_iostream_instances_count = sizeof(sl_iostream_instances_info) / sizeof(sl_iostream_instances_info[0]);
sl_iostream_t *sl_iostream_recommended_console_stream = NULL;


/***************************************************************************//**
 * Get iostream instance handle for a given name
 *
 * @return  Instance handle if it exist, NULL otherwise.
 ******************************************************************************/
sl_iostream_t *sl_iostream_get_handle(char *name)
{
  for (uint32_t i = 0; i < sl_iostream_instances_count; i++) {
    if (strcmp(sl_iostream_instances_info[i]->name, name) == 0) {
      return sl_iostream_instances_info[i]->handle;
    }
  }

  return NULL;
}

/***************************************************************************//**
 * Set iostream recommended instance for a console
 ******************************************************************************/
void sl_iostream_set_console_instance(void)
{
  sl_iostream_type_t console = SL_IOSTREAM_TYPE_UNDEFINED;

  for (uint32_t i = 0; i < sl_iostream_instances_count; i++) {
    switch (sl_iostream_instances_info[i]->type) {
      case SL_IOSTREAM_TYPE_UART:
      case SL_IOSTREAM_TYPE_RTT:
        if (console != SL_IOSTREAM_TYPE_UART) {
          console = sl_iostream_instances_info[i]->type;
          sl_iostream_recommended_console_stream = sl_iostream_instances_info[i]->handle;
        }
        break;

      case SL_IOSTREAM_TYPE_VUART:
        if (console != SL_IOSTREAM_TYPE_UART && console != SL_IOSTREAM_TYPE_RTT) {
          console = sl_iostream_instances_info[i]->type;
          sl_iostream_recommended_console_stream = sl_iostream_instances_info[i]->handle;
        }
        break;

      case SL_IOSTREAM_TYPE_LOOPBACK:
      default:
        // Ignore loopback interface
        break;
    }
  }
}