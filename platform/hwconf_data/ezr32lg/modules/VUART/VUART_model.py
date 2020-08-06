from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "VUART"
displayname = "Virtual UART"
description = "Serial communication over debug interface (SWO/RTT)"
compatibility = dep.Dependency(mcu_type=dep.McuType.RADIO)  # all
category = " Serial"
enable = {
    "define": "HAL_SERIAL_VUART_ENABLE",
    "description": "Enable VUART/Semihosting",
}
options = {
    "HAL_VUART_TYPE": {
        "type": "enum",
        "values": [types.EnumValue('HAL_VUART_TYPE_NONE', 'No VUART'),
                   types.EnumValue('HAL_VUART_TYPE_SWO', 'VUART via SWO')],
        "description": "VUART type",
        "longdescription": "Select the transport for VUART. SWO: Dedicated Serial Wire Output pin, input through shared memory with debug host (RTT). RTT: Bidirectional shared memory [not implemented in (W)STK].",
    },
}
