#ifndef SL_IOSTREAM_INIT_SI91X_USART_H
#define SL_IOSTREAM_INIT_SI91X_USART_H
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_iostream.h"
#include "sl_iostream_uart_si91x.h"
#ifdef __cplusplus
extern "C" {
#endif


extern sl_iostream_t *sl_iostream_vcom_handle;
extern sl_iostream_uart_t *sl_iostream_uart_vcom_handle;
extern sl_iostream_instance_info_t sl_iostream_instance_vcom_info;


// Initialize only iostream usart instance(s)
void sl_iostream_usart_init_instances(void);

#ifdef __cplusplus
}
#endif

#endif // SL_IOSTREAM_INIT_SI91X_USART_H