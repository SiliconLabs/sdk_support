from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "BUTTON"
displayname = "Button"
compatibility = dep.Dependency()  # = all
enable = {
    "define": "BSP_BUTTON_PRESENT",
    "description": "Buttons present on board",
}
options = {
    "BSP_BUTTON": {
        "type": types.PinArray(
            "BSP_BUTTON",
            min=0,
            max=8,
            default=2,
            item_description="Button %n"
        ),
        "description": "Number of buttons available on board",
        "allowedconflicts": ["BSP_LED", "BSP_BTL_BUTTON"],
        "longdescription": "Number of buttons physically present in hardware [0-8]"
    },
    "BSP_BUTTON_GPIO_DOUT": {
        "type": "enum",
        "description": "DOUT register value of button pins",
        "values": [
            types.EnumValue("HAL_GPIO_DOUT_LOW", "Low"),
            types.EnumValue("HAL_GPIO_DOUT_HIGH", "High")
        ],
        "longdescription": "Set to high/low to enable pullup or pulldown respectively when in input mode with pull. Set to high to enable filter in input only mode.",
    },
    "BSP_BUTTON_GPIO_MODE": {
        "type": "enum",
        "description": "MODE register value of button pins",
        "values": [
            types.EnumValue("HAL_GPIO_MODE_INPUT", "Input"),
            types.EnumValue("HAL_GPIO_MODE_INPUT_PULL", "Input with pullup/down"),
            types.EnumValue("HAL_GPIO_MODE_INPUT_PULL_FILTER", "Input with pullup/down and filter")
        ],
        "longdescription": "Set the GPIO mode for the pins used for buttons.",
    },
    "HAL_BUTTON_COUNT": {
        "type": "uint8_t",
        "description": "Number of buttons to enable",
        "min": "0",
        "max": "255",
        "advanced": True,
        "longdescription": "Cannot exceed number of buttons configured as available above.",
    },
    "HAL_BUTTON_ENABLE": {
        "type": "array",
        "description": "List of button indices to enable",
        "defaultValue": "0, 1",
        "advanced": True,
        "longdescription": "Comma separated list of the buttons that should be enabled for this application. Example: Board has 4 buttons, but application only uses button 0 and 2. Configure the list of buttons to enable as \"0, 2\".",
    },
}
