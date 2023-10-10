#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "em_device.h"
#include "sl_assert.h"
#include "sl_iostream.h"
#include "sl_iostream_init_si91x_uart.h"
#include "sl_iostream_uart_si91x.h"
#include "sl_iostream_usart_si91x.h"

// Include instance config
#include "sl_iostream_usart_vcom_config.h"

sl_status_t sl_iostream_uart_91x_init_vcom(void);

// Instance(s) handle and context variable

static sl_iostream_uart_t sl_iostream_vcom;
sl_iostream_t *sl_iostream_vcom_handle = &sl_iostream_vcom.stream;
sl_iostream_uart_t *sl_iostream_uart_vcom_handle = &sl_iostream_vcom;
static sl_iostream_usart_context_t context_vcom;
static uint8_t rx_buffer_vcom[SL_IOSTREAM_USART_VCOM_RX_BUFFER_SIZE];
sl_iostream_instance_info_t sl_iostream_instance_vcom_info = {
    .handle = &sl_iostream_vcom.stream,
    .name = "vcom",
    .type = SL_IOSTREAM_TYPE_91X_UART,
    .init = sl_iostream_uart_91x_init_vcom,
};

sl_status_t sl_iostream_uart_91x_init_vcom(void) {
  sl_status_t status;
  USART_InitAsync_TypeDef init_vcom = usart_config;
  init_vcom.baudrate = SL_IOSTREAM_USART_VCOM_BAUDRATE;
  init_vcom.parity = SL_IOSTREAM_USART_VCOM_PARITY;
  init_vcom.stopbits = SL_IOSTREAM_USART_VCOM_STOP_BITS;
  init_vcom.mode = SL_IOSTREAM_USART_VCOM_MODE;
  init_vcom.hwflowcontrol = SL_IOSTREAM_USART_VCOM_FLOW_CONTROL_TYPE;
  init_vcom.databits = SL_IOSTREAM_USART_VCOM_DATA_BITS;
  init_vcom.usart_module = SL_USART_MODULE;

  sl_iostream_uart_config_t uart_config_vcom = {
      .rx_buffer = rx_buffer_vcom,
      .rx_buffer_length = SL_IOSTREAM_USART_VCOM_RX_BUFFER_SIZE,
      .lf_to_crlf = SL_IOSTREAM_USART_VCOM_CONVERT_BY_DEFAULT_LF_TO_CRLF,
  };
  // Instantiate usart instance
  status = sl_iostream_usart_init(&sl_iostream_vcom, &uart_config_vcom,
                                  &init_vcom, NULL, &context_vcom);
  EFM_ASSERT(status == SL_STATUS_OK);

  return status;
}

void sl_iostream_usart_init_instances(void) {
  sl_status_t status;

  // Instantiate usart instance(s)

  status = sl_iostream_uart_91x_init_vcom();
  EFM_ASSERT(status == SL_STATUS_OK);
}