from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "PTI"
description = "Packet Trace Interface"
compatibility = dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2), mcu_type=dep.McuType.RADIO)  # EFR32
peripheral = 'PTI'
modes = {
    "define": "HAL_PTI_MODE",
    "description": "mode",
    "values": [types.EnumValue('HAL_PTI_MODE_UART', 'Asynchronous (UART)'),
               types.EnumValue('HAL_PTI_MODE_SPI', 'Synchronous (SPI)'),
               types.EnumValue('HAL_PTI_MODE_UART_ONEWIRE', 'Asynchronous (UART) one wire')],
}
enable = {
    "define": "HAL_PTI_ENABLE",
    "description": "Enable PTI peripheral",
}
options = {
    "HAL_PTI_BAUD_RATE": {
        "type": "uint32_t",
        "description": "PTI baud rate",
        "min": "0",
        "max": "4294967295",
        "defaultValue": "1600000",
        "longdescription": "",
    },
    "BSP_PTI_DCLK": {
        "type": types.Pin(signal="DCLK"),
        "description": "DCLK pin",
        "mode": "HAL_PTI_MODE_SPI",
        "longdescription": "Select pin for the DCLK signal",
    },
    "BSP_PTI_DFRAME": {
        "type": types.Pin(signal="DFRAME"),
        "description": "DFRAME pin",
        "mode": ["HAL_PTI_MODE_SPI", "HAL_PTI_MODE_UART"],
        "longdescription": "Select pin for the DFRAME signal",
    },
    "BSP_PTI_DOUT": {
        "type": types.Pin(signal="DOUT"),
        "description": "DOUT pin",
        "mode": ["HAL_PTI_MODE_SPI", "HAL_PTI_MODE_UART", "HAL_PTI_MODE_UART_ONEWIRE"],
        "longdescription": "Select pin for the DOUT signal",
    },

}
