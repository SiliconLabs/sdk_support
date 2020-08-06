from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "EZRADIOPRO"
displayname = "EZRadioPro"
description = "EZRadioPro external transceiver configuration"
compatibility = dep.Dependency(mcu_type=dep.McuType.RADIO)  # = all
category = " Radio"
studio_module = {
    "basename": "SDK.HAL.EZRADIOPRO",
    "modules": [types.StudioFrameworkModule("BASE", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT])],
    }
enable = {
    "define": "HAL_EZRADIOPRO_ENABLE",
    "description": "Enable EZRadio Pro",
}
options = {
    "BSP_EZRADIOPRO_USART": {
        "type": types.Peripheral(filter=["USART"],
                                 inherit_options=True,
                                 mode="spi",
                                 define_value_prefix="HAL_SPI_PORT_"),
        "description": "USART port",
        "longdescription": "USART port to communicate with PRO2+ tranceiver",
    },
    "BSP_EZRADIOPRO_CS": {
        "type": types.Pin(disabled_label="Inherited from USART"),
        "description": "nSEL/CS pin",
        "longdescription": "Pin for PRO2+ tranceiver CS signal",
    },
    "BSP_EZRADIOPRO_INT": {
        "type": types.Pin(),
        "description": "EZRadio Pro Interrupt pin",
        "longdescription": "Pin for PRO2+ tranceiver interrupt signal",
    },
    "BSP_EZRADIOPRO_SDN": {
        "type": types.Pin(),
        "description": "EZRadio Pro Shutdown pin",
        "longdescription": "Pin for PRO2+ tranceiver shutdown signal",
    },
    "HAL_EZRADIOPRO_SHUTDOWN_SLEEP": {
        "type": "boolean",
        "description": "Shutdown radio when MCU is sleeping",
        "longdescription": "Shut down radio when MCU is sleeping",
    },
}
