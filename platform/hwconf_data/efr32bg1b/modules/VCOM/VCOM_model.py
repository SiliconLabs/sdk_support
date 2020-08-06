from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "VCOM"
displayname = "Virtual COM Port"
description = "UART over USB/Ethernet through Starter Kit Board Controller"
compatibility = dep.Dependency()  # all
category = " Serial"
enable = {
    "define": "HAL_VCOM_ENABLE",
    "description": "Enable VCOM",
}
options = {
    "BSP_VCOM_ENABLE": {
        "type": types.Pin(),
        "description": "VCOM enable pin",
        "longdescription": "Select pin which drives the VCOM enable switch on (W)STK."
    }
}
