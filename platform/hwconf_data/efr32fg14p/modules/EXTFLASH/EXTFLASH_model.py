from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "EXTFLASH"
displayname = "SPI Flash"
compatibility = dep.Dependency()  # = all
options = {
    "BSP_EXTFLASH_INTERNAL": {
        "type": "enum",
        "description": "SPI Flash type",
        "values": [types.EnumValue('0', 'External SPI flash'),
                   types.EnumValue('1', 'Internal SPI flash')],
        "longdescription": "Connection type of SPI flash. Select Internal SPI flash to auto-configure SPI flash in SiP package (e.g. EFR32MG1P632F256GM32). Non-SiP devices can only select External SPI flash.",
    },
    "BSP_EXTFLASH_USART": {
        "type": types.Peripheral(filter=["USART"],
                                 inherit_options=True,
                                 define_value_prefix='HAL_SPI_PORT_',
                                 mode="spi"),
        "description": "USART connected to SPI Flash",
        "longdescription": "USART port to communicate with external flash",
    },
    "BSP_EXTFLASH_CS": {
        "type": types.Pin(disabled_label="Inherited from USART"),
        "description": "Chip Select pin",
        "longdescription": "Pin for external flash CS signal",
    },
    "BSP_EXTFLASH_HOLD": {
        "type": types.Pin(),
        "description": "Hold pin",
        "longdescription": "Pin for external flash hold signal",
    },
    "BSP_EXTFLASH_WP": {
        "type": types.Pin(),
        "description": "Write Protect pin",
        "longdescription": "Pin for external flash write protect signal",
    },
}
