import sys
from enum import Enum


class Platform(Enum):
    """ Enum class describing architectural size """
    SERIES0 = 0
    SERIES1 = 1
    SERIES2 = 2


class McuType(Enum):
    """ Enum class differentiation MCU and RADIO parts """
    MCU = 0
    RADIO = 1


class FlashType(Enum):
    """ Enum class describing internal flash type """
    INTERNAL_ONLY = 0
    STACKED_FLASH = 1


# List of family names mapped to sdid
# Important: List _must_ be ordered from longest to shortest name
PREFIX_TO_SDID_AND_PLAT = [
    # Series 2
    ("rm21z", 200, Platform.SERIES2),
    ("efr32bg21", 200, Platform.SERIES2),
    ("efr32mg21", 200, Platform.SERIES2),
    ("efr32mg22", 205, Platform.SERIES2),
    ("efr32bg22", 205, Platform.SERIES2),
    ("efr32fg22", 205, Platform.SERIES2),

    # Series 1 MCU
    ("efm32gg11b", 100, Platform.SERIES1),
    ("efm32tg11b", 103, Platform.SERIES1),
    ("efm32gg12b", 106, Platform.SERIES1),

    # Series 1 radio-capable
    ("efm32pg12b", 84, Platform.SERIES1),
    ("efm32jg12b", 84, Platform.SERIES1),
    ("efr32mg12", 84, Platform.SERIES1),
    ("efr32bg12", 84, Platform.SERIES1),
    ("efr32fg12", 84, Platform.SERIES1),
    ("efr32mg2p", 84, Platform.SERIES1), # BC

    ("efm32pg13b", 89, Platform.SERIES1),
    ("efm32jg13b", 89, Platform.SERIES1),
    ("efr32mg13", 89, Platform.SERIES1),
    ("efr32bg13", 89, Platform.SERIES1),
    ("efr32fg13", 89, Platform.SERIES1),
    ("efr32zg13", 89, Platform.SERIES1),
    ("efr32mg3p", 89, Platform.SERIES1),  # BC

    ("efm32pg14b", 95, Platform.SERIES1),
    ("efm32jg14b", 95, Platform.SERIES1),
    ("efr32mg14", 95, Platform.SERIES1),
    ("efr32bg14", 95, Platform.SERIES1),
    ("efr32fg14", 95, Platform.SERIES1),
    ("efr32zg14", 95, Platform.SERIES1),

    ("efm32pg1b", 80, Platform.SERIES1),
    ("efm32jg1b", 80, Platform.SERIES1),
    ("efr32mg1", 80, Platform.SERIES1),
    ("efr32bg1", 80, Platform.SERIES1),
    ("efr32fg1", 80, Platform.SERIES1),

    # Series 2 module
    ("bgm21", 200, Platform.SERIES2),
    ("mgm21", 200, Platform.SERIES2),
    ("bgm22", 205, Platform.SERIES2),
    ("mgm22", 205, Platform.SERIES2),

    # Series 1 module
    ("artik", 80, Platform.SERIES1),
    ("bgm11", 80, Platform.SERIES1),
    ("bgm12", 80, Platform.SERIES1), # BC
    ("mgm11", 80, Platform.SERIES1),
    ("mgm12", 84, Platform.SERIES1),
    ("bgm13", 89, Platform.SERIES1),
    ("mgm13", 89, Platform.SERIES1),
    ("zgm13", 89, Platform.SERIES1),

    # Series 0 MCU
    ("efm32gg", 72, Platform.SERIES0),
    ("efm32tg", 73, Platform.SERIES0),
    ("efm32lg", 74, Platform.SERIES0),
    ("efm32wg", 74, Platform.SERIES0),
    ("efm32zg", 76, Platform.SERIES0),
    ("efm32hg", 77, Platform.SERIES0),
    ("efm32g", 71, Platform.SERIES0),

    # Series 0 radio
    ("ezr32lg", 74, Platform.SERIES0),
    ("ezr32wg", 74, Platform.SERIES0),
    ("ezr32hg", 77, Platform.SERIES0),
]


class Dependency(object):
    """ Class describing for which families this property/module exists.
        A value of i.e. self.platform = None means that all platforms have this property/module """

    def __init__(self, platform=(), mcu_type=None, sdid=(), not_sdid=(), is_peripheral=(), has_peripheral=(), flash_type=None):
        # Converting input tu tuples, if needed
        if platform and not isinstance(platform, (tuple, list)):
            platform = (platform,)
        if sdid and not isinstance(sdid, (tuple, list)):
            sdid = (sdid,)
        if not_sdid and not isinstance(not_sdid, (tuple, list)):
            not_sdid = (not_sdid,)
        if is_peripheral and not isinstance(is_peripheral, (tuple, list)):
            is_peripheral = (is_peripheral,)
        if has_peripheral and not isinstance(has_peripheral, (tuple, list)):
            has_peripheral = (has_peripheral,)

        self.platform = platform
        self.mcu_type = mcu_type
        self.sdid = sdid
        self.not_sdid = not_sdid
        self.is_peripheral = is_peripheral
        self.has_peripheral = has_peripheral
        self.flash_type = flash_type

        # Handling the case where you want to input only the sdids that are not allowed. not_sdid overrides sdid
        if not_sdid:
            if self.platform:
                self.sdid = tuple(id for (prefix, id, plat) in PREFIX_TO_SDID_AND_PLAT if (id not in not_sdid and plat in self.platform))
            else:
                self.sdid = tuple(id for (prefix, id, plat) in PREFIX_TO_SDID_AND_PLAT if id not in not_sdid)

    def __add__(self, other):
        if (self.platform != () and other.platform  == ()):
            platform = self.platform
        elif (self.platform == () and other.platform  != ()):
            platform = other.platform
        elif (self.platform == other.platform):
            platform = self.platform
        else:
            raise Exception("Can't sum two conflicting dependencies")

        if (self.mcu_type and other.mcu_type is None):
            mcu_type = self.mcu_type
        elif (self.mcu_type is None and other.mcu_type):
            mcu_type = other.mcu_type
        elif (self.mcu_type == other.mcu_type):
            mcu_type = self.mcu_type
        else:
            print ("mcu_type: %s + %s" %(self.mcu_type,other.mcu_type))
            raise Exception("Can't sum two conflicting dependencies")

        if (self.sdid != () and other.sdid  == ()):
            sdid = self.sdid
        elif (self.sdid == () and other.sdid  != ()):
            sdid = other.sdid
        elif (self.sdid == other.sdid):
            sdid = self.sdid
        else:
            raise Exception("Can't sum two conflicting dependencies")
        
        if (self.not_sdid != () and other.not_sdid  == ()):
            not_sdid = self.not_sdid
        elif (self.not_sdid == () and other.not_sdid  != ()):
            not_sdid = other.not_sdid
        elif (self.not_sdid == other.not_sdid):
            not_sdid = self.not_sdid
        else:
            raise Exception("Can't sum two conflicting dependencies")
        
        if (self.is_peripheral != () and other.is_peripheral  == ()):
            is_peripheral = self.is_peripheral
        elif (self.is_peripheral == () and other.is_peripheral  != ()):
            is_peripheral = other.is_peripheral
        elif (self.is_peripheral == other.is_peripheral):
            is_peripheral = self.is_peripheral
        else:
            raise Exception("Can't sum two conflicting dependencies")
        
        if (self.has_peripheral != () and other.has_peripheral  == ()):
            has_peripheral = self.has_peripheral
        elif (self.has_peripheral == () and other.has_peripheral  != ()):
            has_peripheral = other.has_peripheral
        elif (self.has_peripheral == other.has_peripheral):
            has_peripheral = self.has_peripheral
        else:
            raise Exception("Can't sum two conflicting dependencies")
        
        if (self.flash_type and other.flash_type is None):
            flash_type = self.flash_type
        elif (self.flash_type is None and other.flash_type):
            flash_type = other.flash_type
        elif (self.flash_type == other.flash_type):
            flash_type = self.flash_type
        else:
            raise Exception("Can't sum two conflicting dependencies")

        return Dependency(platform=platform,
                          mcu_type=mcu_type,
                          sdid=sdid,
                          not_sdid=not_sdid,
                          is_peripheral=is_peripheral,
                          has_peripheral=has_peripheral,
                          flash_type=flash_type)

    def __str__(self):
        dependencies = []
        if self.platform:
            dependencies.append(str(self.platform[0].name))
        if self.mcu_type:
            dependencies.append(str(self.mcu_type.name))
        if self.sdid:
            if self.not_sdid:
                sdid_deps = [prefix for (prefix, id, plat) in PREFIX_TO_SDID_AND_PLAT if id in self.not_sdid]
                if len(sdid_deps)==1:
                    sdid_deps = sdid_deps[0]
                dependencies.append("not " + str(sdid_deps))
            else:
                sdid_deps = [prefix for (prefix, id, plat) in PREFIX_TO_SDID_AND_PLAT if id in self.sdid]
                dependencies.append(str(sdid_deps))
        if self.is_peripheral:
            dependencies.append(str(self.is_peripheral[0]))
        if self.has_peripheral:
            dependencies.append(str(self.has_peripheral))
        if self.flash_type:
            dependencies.append(str(self.flash_type))

        if len(dependencies)==0:
            return "None"
        elif len(dependencies) == 1:
            return str(dependencies[0])
        elif len(dependencies) > 1:
            returnstring = ""
            for d in dependencies[0:-1]:
                returnstring += str(d) + ", "
            returnstring += dependencies[-1]
            return returnstring
        return str(dependencies)

    def applies_to_family(self, family="", available_mods=[]):
        """ Returns true if the family fits the dependency """
        # If string, convert to family object
        if isinstance(family, str):
            family = Family(family_str=family, available_mods=available_mods)

        # Verify if prop/mod is applicable to family.
        if self.platform:
            if not any(plat == family.platform for plat in self.platform):
                return False
        if self.mcu_type:
            if self.mcu_type != family.mcu_type:
                return False
        if self.sdid:
            if not any(id == family.sdid for id in self.sdid):
                return False
        if self.has_peripheral:
            if not family.available_mods:
                raise ValueError("Family has no available mods list")
            if not any(mod in family.available_mods for mod in self.has_peripheral):
                return False
        if self.flash_type:
            if family.flash_type != self.flash_type:
                return False
        return True

    def applies_to_module(self, module_name):
        """ Returns true if the module fits the dependency """
        if self.is_peripheral:
            return module_name in self.is_peripheral
        return True


class Family(object):
    """ Class describing a family of parts """

    def __init__(self, family_str, available_mods=[]):
        # If platform or type as string input, convert to enums
        self.platform = None
        self.mcu_type = None
        self.sdid = None
        self.flash_type = None
        self.empty = True
        self.family_str = family_str
        self.available_mods = available_mods
        self.set_family_from_string(family_str)

    def set_family_from_string(self, family_str):
        """
        Configures the family object from a string representation of the family name
        :param family_str: string containing family name or part name
        :return: None
        """

        family_str = family_str.lower()

        # Setting mcu_type
        if family_str.startswith('efm'):
            self.mcu_type = McuType.MCU
        elif family_str.startswith(('ezr', 'efr', 'bgm', 'mgm', 'zgm', 'rm')):
            self.mcu_type = McuType.RADIO
        else:
            pass

        # Setting sdid and platform
        for prefix, sdid, platform in PREFIX_TO_SDID_AND_PLAT:
            if family_str.lower().startswith(prefix):
                self.sdid = sdid
                self.platform = platform
                self.empty = False
                if len(self.family_str) > 10:
                    # String is likely a full OPN
                    self.family_str = prefix
                break

        # Raising exception if no valid sdid is found, and family_str is not empty
        if not self.sdid and family_str:
            raise ValueError("No match found for family/part: " + family_str)

        # Trying to decode parts with stacked flash
        if self.sdid == 80:
            # Series 1 Config 1 stacked flash = xG1x6/xG1x7
            try:
                if family_str[9] == '6' or family_str[9] == '7':
                    self.flash_type = FlashType.STACKED_FLASH
            except:
                # Didn't get enough info, assume regular
                self.flash_type = FlashType.INTERNAL_ONLY
        elif self.sdid == 89:
            # Series 1 Config 3 stacked flash: xG13x8/xG13x9
            try:
                if family_str[10] == '8' or family_str[10] == '9':
                    self.flash_type = FlashType.STACKED_FLASH
            except:
                # Didn't get enough info, assume regular
                self.flash_type = FlashType.INTERNAL_ONLY

        if self.flash_type is None:
            self.flash_type = FlashType.INTERNAL_ONLY

    def get_name(self):
        """ Returns the family name """
        return self.family_str
