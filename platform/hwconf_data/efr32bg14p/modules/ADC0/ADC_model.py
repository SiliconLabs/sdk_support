from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "ADC"
compatibility = dep.Dependency(dep.Platform.SERIES1)  # all
peripheral = 'ADC'
modes = {
    'define': 'hal_adc_mode',
    'description': 'Mode',
    'hide_properties': False,
    'values': [
        types.EnumValue('single', 'Single Channel Mode'),
        types.EnumValue('scan', 'Scan Mode'),
    ]
}
enable = {
    'define': 'HAL_ADC_ENABLE',
    'description': 'Enable ADC',
}
options = {
    "BSP_ADC_POS": {
        "type": types.AportSingleChannel(
            "BSP_ADC_POS_INPUT",
            signal='POS',
            define_name_prefix='BSP_ADC_POS',
            define_value_prefix='_ADC_SINGLECTRL_POSSEL_',
            extra_values=[
                types.EnumValue('AVDD', 'AVDD'),
                types.EnumValue('BU', 'BUVDD', dependency=dep.Dependency(sdid=[100,103])),
                types.EnumValue('AREG', 'DVDD'),
                types.EnumValue('PDBU', 'DECOUPLE'),
                types.EnumValue('IO0', 'IOVDD0'),
                types.EnumValue('IO1', 'IOVDD1', dependency=dep.Dependency(sdid=[100,106])),
                types.EnumValue('TEMP', 'TEMP'),
                types.EnumValue('VSS', 'VSS'),
            ],
        ),
        "description": "Positive input selection",
        "subcategory": "Single Channel Positive Input",
        "mode": "single",
    },
    "BSP_ADC_NEG": {
        "type": types.AportSingleChannel(
            "BSP_ADC_NEG_INPUT",
            signal='NEG',
            define_name_prefix='BSP_ADC_NEG',
            define_value_prefix='_ADC_SINGLECTRL_NEGSEL_',
            extra_values=[
                types.EnumValue('VSS', 'VSS')
            ]
        ),
        "description": "Negative input selection",
        "subcategory": "Single Channel Negative Input",
        "mode": "single",
    },
    "BSP_ADC_SCAN_MASK": {
        "type": types.AportScanMode(
            define_value_prefix="_ADC_SCANINPUTSEL_INPUT%nSEL_",
        ),
        "description": "Scan input mask",
        "category": "Scan Mode",
        "mode": "scan",
    }
}