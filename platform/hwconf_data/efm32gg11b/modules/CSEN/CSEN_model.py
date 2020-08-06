from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "CSEN"
compatibility = dep.Dependency(dep.Platform.SERIES1)  # all
peripheral = 'CSEN'
modes = {
    'define': 'hal_csen_mode',
    'description': 'Mode',
    'hide_properties': False,
    'values': [
        types.EnumValue('single', 'Single Channel Mode'),
        types.EnumValue('scan', 'Scan Mode'),
        types.EnumValue('bonded', 'Bonded Mode'),
    ]
}
options = {
    "BSP_CSEN_SINGLE_INPUT": {
        "type": types.AportSingleChannel(
            "BSP_CSEN_SINGLE_INPUT",
            signal='CEXT',
            define_name_prefix='BSP_CSEN_SINGLE',
            define_value_prefix='_CSEN_SINGLECTRL_SINGLESEL_',
        ),
        "description": "Single input selection",
        "subcategory":"Single Channel Input",
        "mode": "single",
    },
    "BSP_CSEN_SCAN_MASK0": {
        "type": types.AportScanMode(
            define_value_prefix="_CSEN_SCANINPUTSEL0_INPUT%nSEL_",
        ),
        "description": "Scan input mask (0-31)",
        "category": "Scan Mode",
        "allowedconflicts": ["BSP_CSEN_BONDED_INPUT", "BSP_CSEN_SCAN_INPUT"],
        "mode": "scan",
    },
    "BSP_CSEN_SCAN_MASK1": {
        "type": types.AportScanMode(
            define_value_prefix="_CSEN_SCANINPUTSEL1_INPUT%nSEL_",
            channel_start=32
        ),
        "description": "Scan input mask (32-63)",
        "category": "Scan Mode",
        "allowedconflicts": ["BSP_CSEN_BONDED_INPUT", "BSP_CSEN_SCAN_INPUT"],
        "mode": "scan",
    },
    "BSP_CSEN_BONDED_MASK0": {
        "type": types.AportBondedMode(
            channel_start=0,
            aport="1"
        ),
        "description": "Bonded input mask (0-31)",
        "category": "Bonded Mode",
        "subcategory": "Input 0-31 (APORT1)",
        "allowedconflicts": ["BSP_CSEN_BONDED_INPUT", "BSP_CSEN_SCAN_INPUT"],
        "mode": "bonded",
    },
    "BSP_CSEN_BONDED_MASK1": {
        "type": types.AportBondedMode(
            channel_start=32,
            aport="3"
        ),
        "description": "Bonded input mask (32-63)",
        "category": "Bonded Mode",
        "subcategory": "Input 32-63 (APORT3)",
        "allowedconflicts": ["BSP_CSEN_BONDED_INPUT", "BSP_CSEN_SCAN_INPUT"],
        "mode": "bonded",
    }
}