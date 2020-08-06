from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "WDOG"
description = "Watchdog"
compatibility = dep.Dependency()  # = all
#peripheral = 'WDOG' # Don't attach to WDOG physical peripheral, since it has no I/O
enable = {
    "define": "HAL_WDOG_ENABLE",
    "description": "Enable watchdog",
}
options = {
}
