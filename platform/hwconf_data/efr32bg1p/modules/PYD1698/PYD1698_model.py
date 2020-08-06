from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "PYD1698"
displayname = "PYD1698 IR Sensor"
description = "Configuration for PIR sensor used on reference designs"
compatibility = dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO)  # = "EFR32"
category = "Third Party"
enable = {
    "define": "HAL_PYD1698_ENABLE",
    "description": "Enable PYD1698 IR Sensor",
}
options = {
    "BSP_PYD1698_SERIN": {
        "description": "PYD1698 serial in",
        "type": types.Pin(),
        "longdescription": "Select pin to connect to the serial in signal of the occupancy sensor",
    },
    "BSP_PYD1698_DLINK": {
        "description": "PYD1698 DLINK port",
        "type": types.Pin(em4=True),
        "longdescription": "Select pin to connect to the DLINK signal of the occupancy sensor",
    },
    "BSP_PYD1698_INSTALLATION_JP": {
        "description": "PYD1698 calibration mode",
        "type": types.Pin(),
        "longdescription": "Input signal to identify if the occupancy sensor is currently in calbration mode",
    },
}
