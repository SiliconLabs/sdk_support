from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "MODEM"
compatibility = dep.Dependency()  # all
peripheral = 'MODEM'
enable = {
    'define': 'HAL_MODEM_ENABLE',
    'description': 'Enable Antenna Modem',
}
options = {
    "BSP_MODEM_SEL": {
        "type": types.Pin(signal="ANT0"),
        "description": "Antenna select",
        "longdescription": "Pin used to control external antenna switch",
    },
    "BSP_MODEM_NSEL": {
        "type": types.Pin(signal="ANT1"),
        "description": "Complementary antenna select",
        "longdescription": "Pin for inverted external antenna signal",
    },
}