from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "IADC"
compatibility = dep.Dependency(dep.Platform.SERIES2)  # all
peripheral = 'IADC'
enable = {
    'define': 'HAL_ADC_ENABLE',
    'description': 'Enable ADC',
}
options = {
    "BSP_IADC_POS": {
        "type": types.Pin(signal='POS'),
        "description": "Positive input selection",
        "subcategory": "Single Channel Positive Input",
    },
    "BSP_IADC_NEG": {
        "type": types.Pin(signal='NEG'),
        "description": "Negative input selection",
        "subcategory": "Single Channel Negative Input",
    },
}