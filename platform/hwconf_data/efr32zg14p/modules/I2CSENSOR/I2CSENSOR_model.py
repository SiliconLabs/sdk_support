from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "I2CSENSOR"
displayname = "I2C Sensor"
description = "I2C sensor configuration. Can be used with I2C sensors on starter kits."
compatibility = dep.Dependency()  # = all
studio_module = {
    "basename": "SDK.HAL.I2CSENSOR",
    "modules": [types.StudioFrameworkModule("COMMON", [types.Framework.ZNET, types.Framework.THREAD, types.Framework.CONNECT]),
                types.StudioFrameworkModule("BLE", types.Framework.BLE)],
    }
enable = {
    "define": "HAL_I2CSENSOR_ENABLE",
    "description": "Enable I2C sensor",
}
options = {
    "BSP_I2CSENSOR_ENABLE": {
        "type": types.Pin(),
        "description": "Sensor enable pin",
        "longdescription": "Pin for I2C sensor enable signal (typically used on Starter Kit)",
    },
    "BSP_I2CSENSOR_PERIPHERAL": {
        "type": types.Peripheral(filter=["I2C"], inherit_options=True, define_value_prefix='HAL_I2C_PORT_'),
        "description": "I2C peripheral",
        "longdescription": "Select I2C peripheral",
    },
}
