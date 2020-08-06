from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "SPINCP"
displayname = "SPI NCP"
compatibility = dep.Dependency()  # = all
category = " NCP"
studio_module = {
    "basename": "SDK.HAL.SPINCP",
    "modules": [types.StudioFrameworkModule("ZIGBEE", types.Framework.ZNET),
                types.StudioFrameworkModule("THREAD", types.Framework.THREAD)],
    }
options = {
    "BSP_SPINCP_USART_PORT": {
        "type": types.Peripheral(filter=["USART"],
                                 inherit_options=True,
                                 define_value_prefix='HAL_SPI_PORT_',
                                 mode="spi"),
        "description": "USART port",
        "longdescription": "Select USART port for NCP communication",
    },
    "BSP_SPINCP_CS": {
        "type": types.Pin(disabled_label="Inherited from USART"),
        "description": "Chip Select pin",
        "longdescription": "Select pin for CS signal of NCP",
    },
    "BSP_SPINCP_NHOSTINT": {
        "type": types.Pin(),
        "description": "nHOST_INT pin",
        "longdescription": "Select pin for nHOST_INT signal of NCP",
    },
    "BSP_SPINCP_NWAKE": {
        "type": types.Pin(),
        "description": "nWAKE pin",
        "longdescription": "Select pin for nWAKE signal of NCP",
    },
}
