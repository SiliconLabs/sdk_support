from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "ANTDIV"
displayname = "Antenna Diversity"
description = "Antenna Diversity"
compatibility = dep.Dependency(mcu_type=dep.McuType.RADIO, has_peripheral=['MODEM'])  # = all
category = " Radio"
studio_module = {
    "basename" : "SDK.HAL.ANTDIV",
    "modules" : [types.StudioFrameworkModule("BASE", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT])],
    }
enable = {
    "define": "HAL_ANTDIV_ENABLE",
    "description": "Enable antenna diversity. At least one of SEL and NSEL signal must be defined.",
}
options = {
    "HAL_ANTDIV_TX_MODE": {
        "type": "enum",
        "description": "Antenna Diversity TX Mode",
        "values": [types.EnumValue('HAL_ANTENNA_MODE_DISABLED', 'Disabled'),
                   types.EnumValue('HAL_ANTENNA_MODE_ENABLE1', 'Enable 1'),
                   types.EnumValue('HAL_ANTENNA_MODE_ENABLE2', 'Enable 2'),
                   types.EnumValue('HAL_ANTENNA_MODE_DIVERSITY', 'Diversity')],
        "defaultValue": "Diversity",
        "longdescription": "Choose mode for antenna diversity TX",
    },
    "HAL_ANTDIV_RX_MODE": {
        "type": "enum",
        "description": "Antenna Diversity RX Mode",
        "values": [types.EnumValue('HAL_ANTENNA_MODE_DISABLED', 'Disabled'),
                   types.EnumValue('HAL_ANTENNA_MODE_ENABLE1', 'Enable 1'),
                   types.EnumValue('HAL_ANTENNA_MODE_ENABLE2', 'Enable 2'),
                   types.EnumValue('HAL_ANTENNA_MODE_DIVERSITY', 'Diversity')],
        "defaultValue": "Disabled",
        "longdescription": "Choose mode for antenna diversity RX",
    },
    "BSP_ANTDIV": {
        "type": types.Peripheral(filter=["MODEM"],
                                 inherit_options=True),
        "description": "Inherit antenna select from MODEM",
        "defaultValue": "MODEM",
        "visible": False,
        "generate_if_hidden": False,
        "longdescription": "Pins used to control external antenna switch and external antenna signal are defined in MODEM module",
    },
    "BSP_ANTDIV_SEL": {
        "type": types.Pin(disabled_label="Inherited from MODEM"),
        "description": "Antenna select",
        "longdescription": "Pin used to control external antenna switch",
    },
    "BSP_ANTDIV_NSEL": {
        "type": types.Pin(disabled_label="Inherited from MODEM"),
        "description": "Complementary antenna select",
        "longdescription": "Pin for inverted external antenna signal",
    },
    "HAL_ANTDIV_RX_RUNTIME_PHY_SELECT": {
        "type": "boolean",
        "description": "Enable selecting the RX antenna diversity PHY at runtime",
        "defaultValue": "False",
        "longdescription": "Allow toggling between standard and RX antenna diversity radio configuration",
    },
}
