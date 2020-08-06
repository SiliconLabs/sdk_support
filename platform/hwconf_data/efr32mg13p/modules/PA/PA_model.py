from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "PA"
description = "Power Amplifier"
compatibility = dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2), mcu_type=dep.McuType.RADIO)  # EFR32
enable = {
    "define": "HAL_PA_ENABLE",
    "description": "Enable PA",
}
options = {
    "HAL_PA_CURVE_HEADER": {
        "type": "string",
        "description": "Custom PA curve header file",
        "defaultValue": '"pa_curves_efr32.h"',
        "longdescription": "Specify PA curve header file for power level look up table. Used to convert raw power level to dBm.",
    },
    "HAL_PA_POWER": {
        "type": "uint8_t",
        "description": "Output power (raw units)",
        "min": "0",
        "max": "252",
        "defaultValue": "252",
        "longdescription": "Set output power in raw units",
    },
    "HAL_PA_RAMP": {
        "type": "uint16_t",
        "description": "Ramp time (us)",
        "min": "1",
        "max": "65535",
        "defaultValue": "10",
        "longdescription": "Select the PA ramp time in microseconds",
    },
    "BSP_PA_VOLTAGE": {
        "type": "uint16_t",
        "description": "PA voltage (mV)",
        "min": "0",
        "max": "3800",
        "defaultValue": "3300",
        "longdescription": "Set the PA supply voltage. Should be 1800 if powered from DCDC, and typically 3300 if powered from a coin-cell battery.",
        "generate_if_hidden": False,
    },
    "HAL_PA_2P4_LOWPOWER": {
        "type": "boolean",
        "description": "Use low power PA on 2.4 GHz",
        "defaultValue": "False",
        "dependency": dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO),
        "longdescription": "Use low power PA on 2.4 GHz",
    },
    "HAL_PA_SELECTION": {
        "type": "enum",
        "description": "PA Selection",
        "values": [
                types.EnumValue('HAL_PA_SELECTION_2P4_HP', 'High Power'),
                types.EnumValue('HAL_PA_SELECTION_2P4_MP', 'Medium Power'),
                types.EnumValue('HAL_PA_SELECTION_2P4_LP', 'Low Power'),
                types.EnumValue('HAL_PA_SELECTION_HIGHEST', 'Highest Power Available')
        ],
        "defaultValue": "High Power",
        "dependency": dep.Dependency(platform=dep.Platform.SERIES2, mcu_type=dep.McuType.RADIO),
        "longdescription": "Select Low, Medium or High power PA on 2.4 GHz; Highest Power Available option will automatically select the highest power PA available where PA will be selected at runtime to take into account all restrictions on the current OPN.",
    }
}
