from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "EMU"
description = "Energy Management Unit"
compatibility = dep.Dependency()
enable = {
    "define": "HAL_EMU_ENABLE",
    "description": "Initialize EMU settings",
}
options = {
    "HAL_EMU_EM23_VREG": {
        "type": "boolean",
        "description": "Enable full VREG drive strength in EM2/3",
        "defaultValue": False,
        "dependency": dep.Dependency(platform=dep.Platform.SERIES0),
        "longdescription": "Enable full drive strength for the voltage regulator in EM2 and EM3",
    },
    "HAL_EMU_EM01_VSCALE": {
        "type": "boolean",
        "description": "Enable voltage scaling in EM0/1",
        "defaultValue": False,
        "dependency": dep.Dependency(not_sdid=[80], platform=dep.Platform.SERIES1),
        "longdescription": "Enable automatic voltage scaling in EM0 and EM1. The voltage scale level will depend on the HF clock frequency at any given time. Should not be used in combination with radio.",
        "generate_if_hidden": False,
    },
    "HAL_EMU_EM23_VSCALE": {
        "type": "enum",
        "description": "EM2/3 voltage scaling level ",
        "defaultValue": "Fast wakeup",
        "values": [types.EnumValue('HAL_EMU_EM23_VSCALE_FASTWAKEUP', 'Fast wakeup'),
                   types.EnumValue('HAL_EMU_EM23_VSCALE_LOWPOWER', 'Low power')],
        "dependency": dep.Dependency(not_sdid=[80], platform=dep.Platform.SERIES1),
        "longdescription": "Set voltage scaling level in EM2 and EM3.",
        "generate_if_hidden": False,
    },
}
