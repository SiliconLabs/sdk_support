from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "USART"
description = "USART. Asynchronous and synchronous serial communication interface"
peripheral = 'USART'
compatibility = dep.Dependency()  # = all
modes = {
    "define": "hal_usart_mode",
    "description": "mode",
    "values": [types.EnumValue('uart', "Asynchronous (UART)"),
               types.EnumValue("spi", "Synchronous (SPI)")]
}
enable = {
    "define": "HAL_USART_ENABLE",
    "description": "Enable USART",
}
options = {
    "HAL_USART_BAUD_RATE": {
        "type": "uint32_t",
        "description": "Baud rate",
        "min": "1",
        "max": "4294967295",
        "defaultValue": "115200",
        "mode": "uart",
        "longdescription": "Specify the baud rate of the USART. Must be less than refFreq/oversampling as described in the reference manual",
    },
    "HAL_USART_FREQUENCY": {
        "type": "uint32_t",
        "description": "Frequency",
        "min": "1",
        "max": "4294967295",
        "defaultValue": "1000000",
        "mode": "spi",
        "longdescription": "Specify the baud rate of the USART.",
    },
    "HAL_USART_FLOW_CONTROL": {
        "type": "enum",
        "description": "Flow control mode",
        "values": [types.EnumValue('HAL_USART_FLOW_CONTROL_NONE', 'No flow control', dependency=compatibility),
                   types.EnumValue('HAL_USART_FLOW_CONTROL_SW', 'Xon-Xoff', dependency=compatibility),
                   types.EnumValue('HAL_USART_FLOW_CONTROL_HW', 'GPIO-based CTS/RTS', dependency=compatibility),
                   types.EnumValue('HAL_USART_FLOW_CONTROL_HWUART', 'USART-based CTS/RTS', dependency=dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2)))],
        "mode": "uart",
        "longdescription": "Configure flow control for the USART",
    },
    "HAL_USART_RXSTOP": {
        "type": "uint16_t",
        "description": "Flow control threshold",
        "min": "0",
        "max": "65535",
        "mode": "uart",
        "advanced": True,
        "longdescription": "Flow control assert threshold (flow control is asserted once less than the specified amount of bytes are available in the RX buffer)",
    },
    "HAL_USART_RXSTART": {
        "type": "uint16_t",
        "description": "Release flow control threshold",
        "min": "0",
        "max": "65535",
        "mode": "uart",
        "advanced": True,
        "longdescription": "Flow control release threshold (flow control is released once more than the specified amount of bytes are available in the RX buffer). Must be a multiple of the assert flow control threshold",
    },
    "HAL_USART_TX_QUEUE_SIZE": {
        "type": "uint16_t",
        "description": "TX buffer size",
        "min": "0",
        "max": "65535",
        "mode": "uart",
        "advanced": True,
        "longdescription": "Transmit buffer size.",
    },
    "HAL_USART_RX_QUEUE_SIZE": {
        "type": "uint16_t",
        "description": "RX buffer size",
        "mode": "uart",
        "min": "0",
        "max": "65535",
        "advanced": True,
        "longdescription": "Receive buffer size. Must be a multiple of the assert flow control threshold",
    },
    "BSP_USART_MOSI": {
        "type": types.Pin(signal="TX"),
        "description": "USART MOSI pin",
        "mode": "spi",
        "longdescription": "Select pin for the MOSI signal",
    },
    "BSP_USART_MISO": {
        "type": types.Pin(signal="RX"),
        "description": "USART MISO pin",
        "mode": "spi",
        "longdescription": "Select pin for the MISO signal",
    },
    "BSP_USART_CLK": {
        "type": types.Pin(signal="CLK"),
        "description": "USART CLK pin",
        "mode": "spi",
        "longdescription": "Select pin for the CLK signal",
    },
    "BSP_USART_CS": {
        "type": types.Pin(signal="CS"),
        "description": "USART CS pin",
        "mode": "spi",
        "longdescription": "Select pin for the CS signal",
    },
    "BSP_USART_TX": {
        "type": types.Pin(signal="TX"),
        "description": "USART TX pin",
        "mode": "uart",
        "longdescription": "Select pin for the TX signal",
    },
    "BSP_USART_RX": {
        "type": types.Pin(signal="RX"),
        "description": "USART RX pin",
        "mode": "uart",
        "longdescription": "Select pin for the RX signal",
    },
    "BSP_USART_CTS": {
        "type": types.Pin(signal="CTS"),
        "description": "USART CTS pin",
        "dependency": dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2)),
        "mode": "uart",
        "longdescription": "Select pin for the CTS signal",
    },
    "BSP_USART_RTS": {
        "type": types.Pin(signal="RTS"),
        "description": "USART RTS pin",
        "dependency": dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2)),
        "mode": "uart",
        "longdescription": "Select pin for the RTS signal",
    },
}
