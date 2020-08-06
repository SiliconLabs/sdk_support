from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "VDAC"
compatibility = dep.Dependency(dep.Platform.SERIES1)  # all
peripheral = 'VDAC'
options = {
    "BSP_VDAC_OPA0_POS": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA0_POS_INPUT",
            signal='OPA0POS',
            define_name_prefix='BSP_VDAC_OPA0_POS',
            define_value_prefix='_VDAC_OPA_MUX_POSSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('DAC', 'DAC'),
                types.EnumValue('POSPAD', 'POSPAD'),
                types.EnumValue('OPANEXT', 'OPANEXT'),
                types.EnumValue('OPATAP', 'OPATAP'),
            ],
        ),
        "description": "Positive input selection",
        "category": "OPA0",
        "subcategory":"Positive Input"
    },
    "BSP_VDAC_OPA0_NEG": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA0_NEG_INPUT",
            signal='OPA0NEG',
            define_name_prefix='BSP_VDAC_OPA0_NEG',
            define_value_prefix='_VDAC_OPA_MUX_NEGSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('UG', 'UG'),
                types.EnumValue('OPATAP', 'OPATAP'),
                types.EnumValue('NEGPAD', 'NEGPAD'),
            ],
        ),
        "description": "Negative input selection",
        "category": "OPA0",
        "subcategory":"Negative Input"
    },
    "BSP_VDAC_OPA0_OUT": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA0_OUTPUT",
            signal='OPA0OUT',
            define_name_prefix='BSP_VDAC_OPA0_OUT',
            define_value_prefix='_VDAC_OPA_OUT_APORTOUTSEL_'
        ),
        "description": "Output selection",
        "category": "OPA0",
        "subcategory": "Output"
    },
    "BSP_VDAC_OPA1_POS": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA1_POS_INPUT",
            signal='OPA1POS',
            define_name_prefix='BSP_VDAC_OPA1_POS',
            define_value_prefix='_VDAC_OPA_MUX_POSSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('DAC', 'DAC'),
                types.EnumValue('POSPAD', 'POSPAD'),
                types.EnumValue('OPANEXT', 'OPANEXT'),
                types.EnumValue('OPATAP', 'OPATAP'),
            ],
        ),
        "description": "Positive input selection",
        "category": "OPA1",
        "subcategory": "Positive Input"
    },
    "BSP_VDAC_OPA1_NEG": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA1_NEG_INPUT",
            signal='OPA1NEG',
            define_name_prefix='BSP_VDAC_OPA1_NEG',
            define_value_prefix='_VDAC_OPA_MUX_NEGSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('UG', 'UG'),
                types.EnumValue('OPATAP', 'OPATAP'),
                types.EnumValue('NEGPAD', 'NEGPAD'),
            ],
        ),
        "description": "Negative input selection",
        "category": "OPA1",
        "subcategory": "Negative Input"
    },
    "BSP_VDAC_OPA1_OUT": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA1_OUTPUT",
            signal='OPA1OUT',
            define_name_prefix='BSP_VDAC_OPA1_OUT',
            define_value_prefix='_VDAC_OPA_OUT_APORTOUTSEL_'
        ),
        "description": "Output selection",
        "category": "OPA1",
        "subcategory": "Output"
    },
    "BSP_VDAC_OPA2_POS": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA2_POS_INPUT",
            signal='OPA2POS',
            define_name_prefix='BSP_VDAC_OPA2_POS',
            define_value_prefix='_VDAC_OPA_MUX_POSSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('DAC', 'DAC'),
                types.EnumValue('POSPAD', 'POSPAD'),
                types.EnumValue('OPANEXT', 'OPANEXT'),
                types.EnumValue('OPATAP', 'OPATAP'),
            ],
        ),
        "description": "Positive input selection",
        "category": "OPA2",
        "subcategory": "Positive Input",
        "dependency": dep.Dependency(not_sdid=[95])
    },
    "BSP_VDAC_OPA2_NEG": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA2_NEG_INPUT",
            signal='OPA2NEG',
            define_name_prefix='BSP_VDAC_OPA2_NEG',
            define_value_prefix='_VDAC_OPA_MUX_NEGSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('UG', 'UG'),
                types.EnumValue('OPATAP', 'OPATAP'),
                types.EnumValue('NEGPAD', 'NEGPAD'),
            ],
        ),
        "description": "Negative input selection",
        "category": "OPA2",
        "subcategory": "Negative Input",
        "dependency": dep.Dependency(not_sdid=[95])
    },
    "BSP_VDAC_OPA2_OUT": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA2_OUTPUT",
            signal='OPA2OUT',
            define_name_prefix='BSP_VDAC_OPA2_OUT',
            define_value_prefix='_VDAC_OPA_OUT_APORTOUTSEL_'
        ),
        "description": "Output selection",
        "category": "OPA2",
        "subcategory": "Output",
        "dependency": dep.Dependency(not_sdid=[95])
    },
    "BSP_VDAC_OPA3_POS": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA3_POS_INPUT",
            signal='OPA3POS',
            define_name_prefix='BSP_VDAC_OPA3_POS',
            define_value_prefix='_VDAC_OPA_MUX_POSSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('DAC', 'DAC'),
                types.EnumValue('POSPAD', 'POSPAD'),
                types.EnumValue('OPANEXT', 'OPANEXT'),
                types.EnumValue('OPATAP', 'OPATAP'),
            ],
        ),
        "description": "Positive input selection",
        "category": "OPA3",
        "subcategory": "Positive Input",
        "dependency": dep.Dependency(sdid=[100, 103, 106])
    },
    "BSP_VDAC_OPA3_NEG": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA3_NEG_INPUT",
            signal='OPA3NEG',
            define_name_prefix='BSP_VDAC_OPA3_NEG',
            define_value_prefix='_VDAC_OPA_MUX_NEGSEL_',
            extra_values=[
                types.EnumValue('DISABLE', 'DISABLE'),
                types.EnumValue('UG', 'UG'),
                types.EnumValue('OPATAP', 'OPATAP'),
                types.EnumValue('NEGPAD', 'NEGPAD'),
            ],
        ),
        "description": "Negative input selection",
        "category": "OPA3",
        "subcategory": "Negative Input",
        "dependency": dep.Dependency(sdid=[100, 103, 106])
    },
    "BSP_VDAC_OPA3_OUT": {
        "type": types.AportSingleChannel(
            "BSP_VDAC_OPA3_OUTPUT",
            signal='OPA3OUT',
            define_name_prefix='BSP_VDAC_OPA3_OUT',
            define_value_prefix='_VDAC_OPA_OUT_APORTOUTSEL_'
        ),
        "description": "Output selection",
        "category": "OPA3",
        "subcategory": "Output",
        "dependency": dep.Dependency(sdid=[100, 103, 106])
    },
}