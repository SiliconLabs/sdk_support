from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "BULBPWM_COLOR"
displayname = "Color PWM Lightbulb"
description = "Configuration of pulse-width modulation for controlling a color lightbulb"
category = "PWM"
compatibility = dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO)  # EFR32
peripheral = 'TIMER'
enable = {
    "define": "HAL_BULBPWM_COLOR_ENABLE",
    "description": "Enable BULBPWM_COLOR",
}
options = {
    "HAL_BULBPWM_COLOR_FREQUENCY": {
        "description": "PWM frequency select",
        "type": "uint16_t",
        "min": 500,
        "max": 2000,
        "defaultValue": 1000,
        "longdescription": "Base frequency of the PWM",
    },
    "BSP_BULBPWM_COLOR_TIMER": {
        "type": types.Peripheral(filter=["TIMER"], inherit_options=True),
        "description": "BULBPWM_COLOR Timer module",
        "defaultValue": "TIMER1",
        "readonly": True,
        "longdescription": "Timer to be used by the PWM",
    },
    "HAL_BULBPWM_RED_ENABLE": {
        "description": "Enable red PWM channel (CC0)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for red LED",
    },
    "HAL_BULBPWM_GREEN_ENABLE": {
        "description": "Enable green PWM channel (CC1)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for green LED",
    },
    "HAL_BULBPWM_BLUE_ENABLE": {
        "description": "Enable blue PWM channel (CC2)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for blue LED",
    },
    "HAL_BULBPWM_AMBER_ENABLE": {
        "description": "Enable amber PWM channel (CC3)",
        "type": "boolean",
        "longdescription": "Enable Compare/Capture channel for amber LED",
    },
}
