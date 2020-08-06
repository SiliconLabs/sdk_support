from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "SPIDISPLAY"
displayname = "SPI Display"
compatibility = dep.Dependency(not_sdid=[71])  # = all
studio_module = {
    "basename": "SDK.HAL.SPIDISPLAY",
    "modules": [types.StudioFrameworkModule("COMMON", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.FLEX]),
                types.StudioFrameworkModule("BLE", types.Framework.BLE)],
    }
enable = {
    "define": "HAL_SPIDISPLAY_ENABLE",
    "description": "Enable SPI display",
}
options = {
    "BSP_SPIDISPLAY_DISPLAY": {
        "type": "enum",
        "description": "Display type",
        "values": [
            types.EnumValue('HAL_DISPLAY_SHARP_LS013B7DH03', 'Sharp LS013B7DH03'),
            types.EnumValue('HAL_DISPLAY_SHARP_LS013B7DH06', 'Sharp LS013B7DH06'),
        ],
        "longdescription": "Select the part number of the used display",
    },
    "BSP_SPIDISPLAY_USART": {
        "type": types.Peripheral(filter=["USART"],
                                 inherit_options=True,
                                 mode="spi",
                                 define_value_prefix='HAL_SPI_PORT_'),
        "description": "USART port",
        "longdescription": "Select the USART to use with the display",
    },
    "BSP_SPIDISPLAY_CS": {
        "type": types.Pin(disabled_label="Inherited from USART"),
        "description": "Chip Select pin",
        "longdescription": "Select pin to connect to the CS signal of the display",
    },
    "BSP_SPIDISPLAY_ENABLE": {
        "type": types.Pin(),
        "description": "Display enable pin",
        "longdescription": "Select pin which drives the display enable switch on (W)STK",
    },
    "BSP_SPIDISPLAY_EXTMODE": {
        "type": types.Pin(),
        "description": "EXTMODE pin",
        "longdescription": "External COM inversion mode pin. If present, this pin tells the display whether to expect COM inversion on GPIO pin or as SPI command. Most designs tie this pin high or low in hardware, rather than retaining software control.",
    },
    "HAL_SPIDISPLAY_EXTMODE_EXTCOMIN": {
        "type": "boolean",
        "description": "Use EXTCOMIN pin for polarity inversion",
        "defaultValue": "True",
        "longdescription": "Handle COM inversion by toggling a GPIO pin",
    },
    "HAL_SPIDISPLAY_EXTMODE_SPI": {
        "type": "boolean",
        "description": "Use SPI command for polarity inversion",
        "longdescription": "Handle COM inversion by sending a SPI command",
    },
    "HAL_SPIDISPLAY_EXTCOMIN_USE_CALLBACK": {
        "type": "boolean",
        "description": "Toggle EXTCOMIN from software callback",
        "longdescription": "Use a software callback to toggle the COM inversion pin",
    },
    "HAL_SPIDISPLAY_EXTCOMIN_CALLBACK": {
        "type": "string",
        "description": "EXTCOMIN callback registration function",
        "longdescription": "Specify function the display driver should call in order to register the periodic software callback used to toggle the COM inversion signal",
    },
    "HAL_SPIDISPLAY_EXTCOMIN_USE_PRS": {
        "type": "boolean",
        "description": "Autonomously toggle EXTCOMIN using PRS",
        "longdescription": "Toggle COM inversion signal autonomously using PRS",
    },
    "BSP_SPIDISPLAY_EXTCOMIN": {
        "type": types.Pin(),
        "description": "EXTCOMIN pin",
        "allowedconflicts": ["PRS_CH"],
        "longdescription": "Select GPIO pin for COM inversion signal",
    },
    "BSP_SPIDISPLAY_EXTCOMIN_PRS": {
        "type": types.PRSChannelLocation("BSP_SPIDISPLAY_EXTCOMIN", custom_name="SPIDISPLAY_EXTCOMIN"),
        "description": "EXTCOMIN PRS channel",
        "longdescription": "Select PRS channel for COM inversion signal",
    },
}
