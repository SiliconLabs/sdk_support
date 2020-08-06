from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "DCDC"
description = "DC-to-DC Converter"
compatibility = dep.Dependency(platform=(dep.Platform.SERIES1, dep.Platform.SERIES2), not_sdid=(200))
enable = {
    "define": "BSP_DCDC_PRESENT",
    "description": "Power circuit configured for DCDC",
}
options = {
    "BSP_DCDC_INIT": {
        "type": "string",
        "description": "DCDC initialization options struct",
        "defaultValue": "EMU_DCDCINIT_DEFAULT",
        "longdescription": "Settings to initialize the DCDC. The value given here will typically be assigned to a EMU_DCDCInit_TypeDef structure from EMLIB. One way of setting non-default settings for this property, is to set it to the value of a macro that is defined elsewhere. For instance, this property can be set to MY_CUSTOM_DCDC_INIT, and that macro can be #define-ed in the hal-config.h file before the EMU section (taking care to define it outside of the $[...]$ sections that get overwritten when generating).",
        "generate_if_hidden": False,
    },
    "HAL_DCDC_BYPASS": {
        "type": "boolean",
        "description": "Bypass DCDC",
        "longdescription": "The PCB is wired for DCDC, but the DCDC should be bypassed.",
        "generate_if_hidden": False,
    },
}
