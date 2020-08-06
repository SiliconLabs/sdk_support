from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "TIMER"
description = "Timer"
compatibility = dep.Dependency()  # all
peripheral = 'TIMER'
options = {
    "BSP_TIMER_CC0": {
        "type": types.Pin(signal='CC0'),
        "description": "TIMER Compare/Capture Channel 0 pin",
        "longdescription": "Select pin for CC channel 0",
    },
    "BSP_TIMER_CC1": {
        "type": types.Pin(signal='CC1'),
        "description": "TIMER Compare/Capture Channel 1 pin",
        "longdescription": "Select pin for CC channel 1",
    },
    "BSP_TIMER_CC2": {
        "type": types.Pin(signal='CC2'),
        "description": "TIMER Compare/Capture Channel 2 pin",
        "longdescription": "Select pin for CC channel 2",
    },
    "BSP_TIMER_CC3": {
        "type": types.Pin(signal='CC3'),
        "description": "TIMER Compare/Capture Channel 3 pin",
        "dependency": dep.Dependency(is_peripheral=['TIMER1'], platform=dep.Platform.SERIES1),
        "longdescription": "Select pin for CC channel 3",
    },
}
