from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "BATTERYMON"
displayname = "Battery Monitor"
description = "External battery monitor used on reference designs."
compatibility = dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO)  # EFR32
category = "Third Party"
enable = {
    "define": "HAL_BATTERYMON_ENABLE",
    "description": "Enable battery monitor",
}
options = {
    "BSP_BATTERYMON_TX_ACTIVE": {
        "type": types.PRSChannelLocation("BSP_BATTERYMON_TX_ACTIVE", custom_name="BATTERYMON_TX_ACTIVE"),
        "description": "Battery monitor TX active PRS channel",
        "longdescription": "Signal to trigger reading the supply voltage when TX is active (current consumption is highest)"
    },
}