from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "GPIO"
description = "GPIO configuration of debug signals"
compatibility = dep.Dependency()  # all
peripheral = 'GPIO'
options = {
    "BSP_TRACE_SWO": [
        {
            # SWO pin is called "SWV" on Series 1
            "type": types.Pin(signal='SWV'),
            "description": "Serial Wire Output pin",
            "dependency": dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2)),
            "longdescription": "Select pin for SWO",
        },
        {
            # SWO pin is called "SWO" on Series 0
            "type": types.Pin(signal='SWO'),
            "description": "Serial Wire Output",
            "dependency": dep.Dependency(platform=dep.Platform.SERIES0, not_sdid=[76,77]),
            "longdescription": "Select pin for SWO",
        },
        # Documentation options
        {
            "type": types.Pin(),
            "description": "Serial Wire Output pin",
            "dependency": dep.Dependency(),
            "documentation": "True",
        },
        {
            "define": "BSP_TRACE_SWO_LOC",
            "type": "enum",
            "values": "_GPIO_ROUTELOC0_SWVLOC_LOC0",
            "description": "Serial Wire Output location (Series 1 and 2)",
            "dependency": dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2)),
            "documentation": "True",
        },
        {
            "define": "BSP_TRACE_DBGROUTE_LOC",
            "type": "enum",
            "values": "_GPIO_ROUTE_SWLOCATION_LOC0",
            "description": "Serial Wire Output location (Series 0)",
            "dependency": dep.Dependency(platform=dep.Platform.SERIES0, not_sdid=[76,77]),
            "documentation": "True",
        }
    ],
}
