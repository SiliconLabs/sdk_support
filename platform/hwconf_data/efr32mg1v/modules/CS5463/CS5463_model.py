from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "CS5463"
displayname = "CS5463 Power Meter"
description = "Power meter used on reference designs"
compatibility = dep.Dependency(platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO)  # = all
category = "Third Party"
studio_module = {
    "basename": "SDK.HAL.CS5463",
    "modules" : [types.StudioFrameworkModule("BASE", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT])],
    }
options = {
    "BSP_CS5463_CS": {
        "type": types.Pin(disabled_label="Inherited from USART"),
        "description": "CS5463 CS pin",
        "longdescription": "Pin used for CS signal of the CS5463",
    },
    "BSP_CS5463_USART_PORT": {
        "type": types.Peripheral(filter=["USART"],
                                 inherit_options=True,
                                 define_value_prefix='HAL_SPI_PORT_',
                                 mode="spi"),
        "description": "CS5463 USART port",
        "longdescription": "USART port to communicate with the CS5463",
    },
}
