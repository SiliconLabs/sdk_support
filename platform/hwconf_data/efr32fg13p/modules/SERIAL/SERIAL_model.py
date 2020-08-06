from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "SERIAL"
displayname = "Serial"
compatibility = dep.Dependency()  # = all
category = " Serial"
studio_module = {
    "basename" : "SDK.HAL.SERIAL",
    "modules" : [types.StudioFrameworkModule("BASE", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT]),
                 types.StudioFrameworkModule("BLE", types.Framework.BLE)],
    }
options = {
    "BSP_SERIAL_APP_PORT": {
        "type": types.Peripheral(filter=["USART", "UART", "LEUART", "EUART", "EUSART", "VUART"],
                                 inherit_options=True,
                                 define_value_prefix="HAL_SERIAL_PORT_",
                                 define_name_postfix="_APP",
                                 mode="uart"),
        "description": "Port for application serial communication",
        "longdescription": "Select the port on which application prints are communicated (such as printf())",
    },
    "BSP_SERIAL_ASSERT_PORT": {
        "type": types.Peripheral(filter=["USART", "UART", "LEUART", "VUART"],
                                 inherit_options=True,
                                 define_value_prefix="HAL_SERIAL_PORT_",
                                 define_name_postfix="_ASSERT",
                                 mode="uart"),
        "description": "Port for assert serial communication",
        "dependency": dep.Dependency(mcu_type=dep.McuType.RADIO),
        "advanced": True,
        "longdescription": "Select the port on which asserts are communicated",
    },
    "HAL_SERIAL_RXWAKE_ENABLE": {
        "type": "boolean",
        "description": "Enable wake from activity on RX GPIO of application port",
        "dependency": dep.Dependency(mcu_type=dep.McuType.RADIO),
        "advanced": True,
        "longdescription": "Enable wake up on Serial Activity",
    },
    "HAL_SERIAL_IDLE_WAKE_ENABLE": {
        "type": "boolean",
        "description": "Enable wake from idle",
        "dependency": dep.Dependency(mcu_type=dep.McuType.RADIO),
        "defaultValue": "True",
        "advanced": True,
        "longdescription": "Enable wake from idle",
    },
    "HAL_SERIAL_LEUART0_ENABLE": {
        "type": "boolean",
        "description": "Use LEUART0 for serial",
        "dependency": dep.Dependency(has_peripheral=['LEUART0'], platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_LEUART1_ENABLE": {
        "type": "boolean",
        "description": "Use LEUART1 for serial",
        "dependency": dep.Dependency(has_peripheral=['LEUART1'], platform=dep.Platform.SERIES1, mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_UART0_ENABLE": {
        "type": "boolean",
        "description": "Use UART0 for serial",
        "dependency": dep.Dependency(has_peripheral=['UART0'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_UART1_ENABLE": {
        "type": "boolean",
        "description": "Use UART1 for serial",
        "dependency": dep.Dependency(has_peripheral=['UART1'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_USART0_ENABLE": {
        "type": "boolean",
        "description": "Use USART0 for serial",
        "dependency": dep.Dependency(has_peripheral=['USART0'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_USART1_ENABLE": {
        "type": "boolean",
        "description": "Use USART1 for serial",
        "dependency": dep.Dependency(has_peripheral=['USART1'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_USART2_ENABLE": {
        "type": "boolean",
        "description": "Use USART2 for serial",
        "dependency": dep.Dependency(has_peripheral=['USART2'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
    "HAL_SERIAL_USART3_ENABLE": {
        "type": "boolean",
        "description": "Use USART3 for serial",
        "dependency": dep.Dependency(has_peripheral=['USART3'], mcu_type=dep.McuType.RADIO),
        "advanced": True,
    },
}
