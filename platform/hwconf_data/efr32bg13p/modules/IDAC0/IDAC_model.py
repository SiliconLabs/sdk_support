from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "IDAC"
compatibility = dep.Dependency(dep.Platform.SERIES1)  # all
peripheral = 'IDAC'
options = {
    "BSP_IDAC_OUTPUT": {
        "type": types.AportSingleChannel(
            "BSP_IDAC_OUTPUT",
            signal='OUT',
            define_name_prefix='BSP_IDAC_OUT',
            define_value_prefix='_IDAC_CTRL_APORTOUTSEL_',
        ),
        "description": "Output selection",
        "subcategory":"Output"
    },
}