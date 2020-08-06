from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "WTIMER"
description = "Wide Timer"
compatibility = dep.Dependency()  # all
peripheral = 'WTIMER'
options = {
    "BSP_WTIMER_CC0": {
        "type": types.Pin(signal='CC0'),
        "description": "WTIMER Compare/Capture Channel 0 pin",
        "longdescription": "Select pin for CC channel 0",
    },
    "BSP_WTIMER_CC1": {
        "type": types.Pin(signal='CC1'),
        "description": "WTIMER Compare/Capture Channel 1 pin",
        "longdescription": "Select pin for CC channel 1",
    },
    "BSP_WTIMER_CC2": {
        "type": types.Pin(signal='CC2'),
        "description": "WTIMER Compare/Capture Channel 2 pin",
        "longdescription": "Select pin for CC channel 2",
    },
    "BSP_WTIMER_CC3": {
        "type": types.Pin(signal='CC3'),
        "description": "WTIMER Compare/Capture Channel 3 pin",
        "dependency": dep.Dependency(is_peripheral=['WTIMER1'], platform=dep.Platform.SERIES1),
        "longdescription": "Select pin for CC channel 3",
    },
}
