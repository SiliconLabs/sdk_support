from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "BTL_BUTTON"
displayname = "Bootloader Entry"
description = "GPIO used by bootloader upon reset. It is not necessary to configure this in the application, only the bootloader."
compatibility = dep.Dependency() # = all
enable = {
    "define": "HAL_BTL_BUTTON_ENABLE",
    "description": "Enable bootloader entry via button press",
}
options = {
    "BSP_BTL_BUTTON": {
        "type": types.Pin(),
        "description": "Bootloader entry pin",
        "allowedconflicts": ["BSP_LED", "BSP_BUTTON"],
        "longdescription": "Device is forced to stay in bootloader when signal is high/low as configured in bootloader"
    },
}
