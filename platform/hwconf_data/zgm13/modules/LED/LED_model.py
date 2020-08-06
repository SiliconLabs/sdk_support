from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "LED"
compatibility = dep.Dependency()  # = all
studio_module = {
    "basename" : "SDK.HAL.LED",
    "modules" : [types.StudioFrameworkModule("BLE", types.Framework.BLE)],
    }
enable = {
    "define": "BSP_LED_PRESENT",
    "description": "LEDs present on board",
}
options = {
    "BSP_LED": {
        "type": types.PinArray(
            "BSP_LED",
            min=0,
            max=8,
            default=2,
            item_description="LED %n"
        ),
        "description": "Number of LEDs available on board",
        "allowedconflicts": ["BSP_BUTTON", "BSP_BTL_BUTTON"],
        "longdescription": "Number of LEDs physically present in hardware [0-8]",
    },
    "HAL_LED_COUNT": {
        "type": "uint8_t",
        "description": "Number of LEDs to initialize",
        "min": "0",
        "max": "8",
        "advanced": True,
        "longdescription": "Cannot exceed number of LEDs configured as available above.",
    },
    "HAL_LED_ENABLE": {
        "type": "array",
        "description": "List of LED indices to initialize",
        "defaultValue": "0, 1",
        "advanced": True,
        "longdescription": "Comma separated list of the LEDs that should be enabled for this application. Example: Board has 4 LEDs, but application only uses LEDs 0 and 2. Configure the list of LEDs to enable as \"0, 2\", and the number of LEDs to initialize as 2.",
    },
    "BSP_LED_POLARITY": {
        "type": "enum",
        "description": "Polarity",
        "values": [
            types.EnumValue("0", "Active low"),
            types.EnumValue("1", "Active high")
        ],
        "defaultValue": "Active high",
        "longdescription": "LED polarity",
    },
}
