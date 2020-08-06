from . import halconfig_types as types
from . import halconfig_dependency as dep

name = "ACMP"
compatibility = dep.Dependency((dep.Platform.SERIES1, dep.Platform.SERIES2))  # all
peripheral = 'ACMP'
options = {
    # "BSP_ACMP_VA": {
    #     "type": types.AportSingleChannel(
    #         "BSP_ACMP_VA_INPUT",
    #         signal='VA',
    #         define_name_prefix='BSP_ACMP_VA',
    #         define_value_prefix='_ACMP_INPUTSEL_VASEL_',
    #         extra_values=[
    #             types.EnumValue('VDD', 'VDD'),
    #         ],
    #     ),
    #     "description": "VA input selection",
    #     "subcategory":"VA Input"
    # },
    "BSP_ACMP_NEG": [
        {
            "type": types.AportSingleChannel(
                "BSP_ACMP_NEG_INPUT",
                signal='NEG',
                define_name_prefix='BSP_ACMP_NEG',
                define_value_prefix='_ACMP_INPUTSEL_NEGSEL_',
                extra_values=[
                    types.EnumValue('VLP', 'VLP'),
                    types.EnumValue('VBDIV', 'VBDIV'),
                    types.EnumValue('VADIV', 'VADIV'),
                    types.EnumValue('VDD', 'VDD'),
                    types.EnumValue('VSS', 'VSS'),
                ]
            ),
            "description": "Negative input selection",
            "subcategory":"Negative Input",
            "dependency": dep.Dependency(dep.Platform.SERIES1),
        },
        {
            "type": types.Pin(signal='NEG'),
            "description": "Negative input selection",
            "subcategory": "Negative Input",
            "dependency": dep.Dependency(dep.Platform.SERIES2),
        },
    ],
    "BSP_ACMP_POS": [
        {
            "type": types.AportSingleChannel(
                "BSP_ACMP_POS_INPUT",
                signal='POS',
                define_name_prefix='BSP_ACMP_POS',
                define_value_prefix='_ACMP_INPUTSEL_POSSEL_',
                extra_values=[
                    types.EnumValue('VLP', 'VLP'),
                    types.EnumValue('VBDIV', 'VBDIV'),
                    types.EnumValue('VADIV', 'VADIV'),
                    types.EnumValue('VDD', 'VDD'),
                    types.EnumValue('VSS', 'VSS'),
                ]
            ),
            "description": "Positive input selection",
            "subcategory": "Positive Input",
            "dependency": dep.Dependency(dep.Platform.SERIES1),
        },
        {
            "type": types.Pin(signal='POS'),
            "description": "Positive input selection",
            "subcategory": "Positive Input",
            "dependency": dep.Dependency(dep.Platform.SERIES2),
        },
    ],
}