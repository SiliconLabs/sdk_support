from enum import Enum

class Peripheral(object):
    def __init__(self, filter=[], inherit_options=False, define_value_prefix="", mode=None, define_name_postfix=""):
        self.filter = filter
        self.inherit_options = inherit_options
        self.define_value_prefix = define_value_prefix
        self.mode = mode
        self.define_name_postfix = define_name_postfix

    def __str__(self):
        return "Peripheral:%s" % self.filter


class Pin(object):
    def __init__(self, signal=None, em4=False, disabled_label=None):
        self.signal = signal
        self.em4 = em4
        self.disabled_label = disabled_label

    def __str__(self):
        if self.signal:
            return "Pin/%s" % self.signal
        else:
            return "Pin"


class PinArray(object):
    def __init__(self, name, min=0, max=0, default=0, item_description=None):
        self.name = name
        self.count_define = name + "_COUNT"
        self.init_define = name + "_INIT"
        self.item_define = name + "%n"
        self.item_port_define = name + "%n_PORT"
        self.item_pin_define = name + "%n_PIN"
        self.min = min
        self.max = max
        self.default = default

        self.item_description = item_description

    def __str__(self):
        return "Array of pins"


class PRSChannelLocation(object):
    def __init__(self, name, channel=0, custom_name=None, gpio=True):
        self.name = name
        self.channel = channel
        self.custom_name = custom_name
        self.define = name + "_CHANNEL"
        self.output_description = "PRS channel %n output pin"
        # Channel count is handled in ExporterModel
        self.default = 0
        self.signal = "OUTPUT"
        self.gpio = gpio

    def __str__(self):
        return "PRS Channel: " + str(self.channel)


class EnumValue(object):
    def __init__(self, define_value="", display_name="", dependency=None):
        self.define_value = define_value
        self.display_name = display_name
        self.dependency = dependency

    def __str__(self):
        return "EnumValue:%s" % self.display_name


class AportSingleChannel(object):
    def __init__(self, define, signal, define_name_prefix='', define_value_prefix='', extra_values=None):
        self.define = define
        self.signal = signal
        self.define_name_prefix = define_name_prefix
        self.define_value_prefix = define_value_prefix
        if extra_values:
            self.extra_values = extra_values
        else:
            self.extra_values = []


class AportScanMode(object):
    def __init__(self, define_value_prefix='', channel_start=0):
        self.channel_start = channel_start
        self.define_value_prefix = define_value_prefix


class AportBondedMode(object):
    def __init__(self, channel_start=0, aport="1"):
        self.channel_start = channel_start
        self.aport = aport


class Framework(Enum):
    """ Enum class describing framework """
    ZNET = "znet"
    THREAD = "thread"
    CONNECT = "connect"
    RAIL = "rail"
    FLEX = "flex"
    BLE = "BLE"
    BOOTLOADER = "BOOTLOADER"
    NONE = "NONE"

class StudioFrameworkModule(object):
    """docstring for StudioFrameworkModule"""
    def __init__(self, name, frameworks=None):
        super(StudioFrameworkModule, self).__init__()
        self.name = name
        self.frameworks = frameworks