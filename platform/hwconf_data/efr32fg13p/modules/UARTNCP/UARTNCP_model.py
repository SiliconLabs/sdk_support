from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "UARTNCP"
displayname = "UART NCP"
compatibility = dep.Dependency()  # all
category = " NCP"
studio_module = {
    "basename": "SDK.HAL.UARTNCP",
    "modules": [types.StudioFrameworkModule("ZIGBEE", types.Framework.ZNET),
                types.StudioFrameworkModule("THREAD", types.Framework.THREAD),
                types.StudioFrameworkModule("BLE", types.Framework.BLE)],
    }
options = {
    "BSP_UARTNCP_USART_PORT": {
        "type": types.Peripheral(filter=["USART", "UART", "LEUART"],
                                 inherit_options=True,
                                 define_value_prefix="HAL_SERIAL_PORT_",
                                 mode="uart"),
        "description": "UART port",
        "longdescription": "Select UART port for NCP communication",
    },
}
