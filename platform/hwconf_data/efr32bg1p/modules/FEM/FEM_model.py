from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "FEM"
displayname = "External FEM"
compatibility = dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2), mcu_type=dep.McuType.RADIO)  # EFR32
category = " Radio"
studio_module = {
    "basename" : "SDK.HAL.FEM",
    "modules" : [types.StudioFrameworkModule("BASE", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT]),
                 types.StudioFrameworkModule("FLEX", [types.Framework.FLEX])],
    }
enable = {
    "define": "HAL_FEM_ENABLE",
    "description": "Enable FEM",
}
options = {
    "BSP_FEM_RX": {
        "type": types.PRSChannelLocation("BSP_FEM_RX", custom_name="FEM_RX"),
        "description": "RX PRS channel",
        "longdescription": "PRS channel for RX control (FEM pin CRX). If no TX defined, it is dual use pin.",
    },
    "BSP_FEM_SLEEP": {
        "type": types.PRSChannelLocation("BSP_FEM_SLEEP", custom_name="FEM_SLEEP"),
        "description": "Sleep PRS channel",
        "longdescription": "PRS channel for sleep control (FEM pin CSD). Optional: If used, must be channel immediately following RX PRS channel.",
    },
    "BSP_FEM_TX": {
        "type": types.PRSChannelLocation("BSP_FEM_TX", custom_name="FEM_TX"),
        "description": "TX PRS channel",
        "longdescription": "PRS channel for TX control (FEM pin CTX). Optional: If not used, assumes CRX is dual use pin.",
    },
    "HAL_FEM_RX_ACTIVE": {
        "type": "boolean",
        "description": "Enable RX mode",
        "defaultValue": "False",
        "longdescription": "Enable RX mode",
        "generate_if_hidden": False,
    },
    "HAL_FEM_TX_ACTIVE": {
        "type": "boolean",
        "description": "Enable TX mode",
        "defaultValue": "False",
        "longdescription": "Enable TX mode",
        "generate_if_hidden": False,
    },
    "BSP_FEM_BYPASS": {
        "type": types.Pin(),
        "description": "Bypass pin",
        "longdescription": "Select pin for the bypass (FEM pin CPS) signal (optional)",
        "subcategory": "Bypass",
    },
    "BSP_FEM_TXPOWER": {
        "type": types.Pin(),
        "description": "TX power pin",
        "longdescription": "Select pin for the tx power mode (FEM pin CHL) signal (optional)",
        "subcategory": "Power",
    },
    "HAL_FEM_BYPASS_ENABLE": {
        "type": "boolean",
        "description": "Enable bypass mode",
        "defaultValue": "False",
        "longdescription": "Enable bypass mode",
        "subcategory": "Bypass",
        "generate_if_hidden": False,
    },
    "HAL_FEM_TX_HIGH_POWER": {
        "type": "boolean",
        "description": "Enable high power tx",
        "defaultValue": "False",
        "longdescription": "Enable high power tx on true, low power on false",
        "subcategory": "Power",
        "generate_if_hidden": False,
    },
}
