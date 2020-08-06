from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "PDM"
description = "Pulse-Density Modulation"
compatibility = dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2))
peripheral = 'PDM'
options = {
    "BSP_PDM_CLK": {
        "type": types.Pin(signal="CLK"),
        "description": "CLK pin",
        "longdescription": "Select pin for the CLK signal",
    },
    "BSP_PDM_DAT0": {
        "type": types.Pin(signal="DAT0"),
        "description": "DAT0 pin",
        "longdescription": "Select pin for the DAT0 signal",
    },
    "BSP_PDM_DAT1": {
        "type": types.Pin(signal="DAT1"),
        "description": "DAT1 pin",
        "longdescription": "Select pin for the DAT1 signal",
    },
}
