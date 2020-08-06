"""
Generated from a template
"""

from PythonSnippet.PropertyMap import PropertyMap

class PORT_PINS(PropertyMap):
    S = 'PORT_PINS'

    ports = 'ports'
    ports_settings = 'Settings'

    class ports_settings_pinmode:
        ## Pin mode
        S = 'ports.settings.pinmode'
        T = 1
        gpioModeDisabled = 0
        gpioModeInput = 1
        gpioModeInputPull = 2
        gpioModeInputPullFilter = 3
        gpioModePushPull = 4
        gpioModePushPullAlternate = 5
        gpioModeWiredOr = 6
        gpioModeWiredOrPullDown = 7
        gpioModeWiredAnd = 8
        gpioModeWiredAndFilter = 9
        gpioModeWiredAndPullUp = 10
        gpioModeWiredAndPullUpFilter = 11
        gpioModeWiredAndAlternate = 12
        gpioModeWiredAndAlternateFilter = 13
        gpioModeWiredAndAlternatePullUp = 14
        gpioModeWiredAndAlternatePullUpFilter = 15
        ATOI = {
            'DISABLED': 0,
            'INPUT': 1,
            'INPUT_PULL': 2,
            'INPUT_PULL_FILTER': 3,
            'PUSH_PULL': 4,
            'PUSH_PULL_ALT': 5,
            'WIRED_OR': 6,
            'WIRED_OR_PULL_DOWN': 7,
            'WIRED_AND': 8,
            'WIRED_AND_FILTER': 9,
            'WIRED_AND_PULLUP': 10,
            'WIRED_AND_PULLUP_FILTER': 11,
            'WIRED_AND_ALT': 12,
            'WIRED_AND_ALT_FILTER': 13,
            'WIRED_AND_ALT_PULLUP': 14,
            'WIRED_AND_ALT_PULLUP_FILTER': 15
        }
        ITOA = {v: k for k, v in ATOI.items()}



    class ports_settings_custompinname:
        ## Custom Pin Name
        S = 'ports.settings.custompinname'

    class ports_settings_halpinname:
        ## Custom Pin Name
        S = 'ports.settings.halpinname'

    class ports_settings_dummy:
        ## Dummy property
        S = 'ports.settings.dummy'

    class ports_settings_reserve:
        ## Reserve
        S = 'ports.settings.reserve'
        T = 1
        NOT_RESERVED = 0
        RESERVED = 1