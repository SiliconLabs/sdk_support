from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "BULBPWM"
displayname = "PWM Lightbulb"
description = "Configuration of pulse-width modulation for controlling a lightbulb"
category = "PWM"
compatibility = dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO)  # EFR32
peripheral = 'TIMER'
enable = {
    "define": "HAL_BULBPWM_ENABLE",
    "description": "Enable BULBPWM",
}
options = {
    "HAL_BULBPWM_FREQUENCY": {
        "description": "PWM frequency select",
        "type": "uint16_t",
        "min": 500,
        "max": 2000,
        "defaultValue": 1000,
        "longdescription": "Base frequency of the PWM",
    },
    "BSP_BULBPWM_TIMER": {
        "type": types.Peripheral(filter=["TIMER"], inherit_options=True),
        "description": "BULBPWM Timer module",
        "defaultValue": "TIMER0",
        "readonly": True,
        "longdescription": "Timer to be used by the PWM",
    },
    "HAL_BULBPWM_WHITE_ENABLE": {
        "description": "Enable white PWM channel (CC0)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for white LED",
    },
    "HAL_BULBPWM_LOWTEMP_ENABLE": {
        "description": "Enable lowtemp PWM channel (CC1)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for low temperature LED",
    },
    "HAL_BULBPWM_STATUS_ENABLE": {
        "description": "Enable status PWM channel (CC2)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for status LED",
    },
}
