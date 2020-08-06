"""
Generated from a template
"""
import efm32gg11b.PythonSnippet.RuntimeModel as RuntimeModel
import efm32gg11b.PythonSnippet.Metadata as Metadata
from efm32gg11b.modules.PIN.PIN_Defs import PORT_PINS

class Route:
    '''
    A class representing a pin route
    '''

    def __init__(self, selector=None, route=None, location=None):
        '''
        :type selector: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ISelectorAccessor
        :type route: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IRouteAccessor
        :type location: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ILocationAccessor
        '''
        self.selector = selector
        self.route = route
        self.location = location

    def getLabel(self):
        '''
        :rtype: str
        :return: A route label consisting of the selector name and route name
        '''
        return '{0}_{1}'.format(self.selector.module.name, self.route.name)

    def getModuleName(self):
        return self.selector.module.name

    def getPin(self):
        """
        :rtype Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPinAccessor
        """
        return self.location.pin

    def getPinId(self):
        return self.location.pin.id

    def getPinName(self):
        '''
        :rtype: str
        '''
        return str(self.location.pin).split('::')[1]

    def getPropRef(self):
        """
        :rtype Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_IPropertyReference
        """
        return self.route.enablePropertyReference

    def getAportName(self):
        '''
        :rtype: str
        :return: the name of the APORT bus this route is connected to. None if not defined (i.e. route is not an APORT connection).
        '''
        return self.route.aportName

    def getName(self):
        """
        :rtype: str
        """
        return self.route.name

class PinRoutes:
    '''
    A class representing a pin object and all Route objects associated with the pin
    '''

    def __init__(self, pin=None, routes=[]):
        '''
        :type pin: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPinAccessor
        :param pin: A pin accessor object
        :type routes: [ Route ]
        :param routes: A list of Route objects for the pin
        '''
        self.pin = pin
        self.routes = routes

    def __getNumAssignments(self):
        '''
        :return: The number of routes assigned to the pin (including routes and GPIO)
        '''
        aports = 0
        others = 0

        for assignment in self.__getAssignmentList():
            if 'APORT' in assignment:
                if aports == 0:
                    aports = 1
            else:
                others += 1

        return (aports + others)

    def __getNumHalAssignments(self):
        '''
        :return: The number of HAL functions assigned to the pin
        '''
        assignments = 0

        for assignment in self.__getHalAssignmentList():
            assignments += 1

        return assignments

    def getPin(self):
        """
        :rtype Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPinAccessor
        :return: The pin accessor
        """
        return self.pin

    def __getAssignmentList(self):
        '''
        :rtype: [ str ]
        :return: A list of routes/GPIO labels assigned to the pin
        '''
        labels = []
        for route in self.routes:
            labels.append(route.getLabel())

        if self.__isReserved():
            labels.append(self.__getReservedLabel())

        return labels

    def __getHalAssignmentList(self):
        '''
        :rtype: [ str ]
        :return: A list of routes/GPIO labels assigned to the pin
        '''
        labels = []

        hal_label = self.__getHalLabel()
        if hal_label:
            if ',' in hal_label:
                for hallabel in hal_label.split(','):
                    labels.append(hallabel)
            else:
                labels.append(hal_label)

        return labels

    def __isReserved(self):
        '''
        :return: True if the pin is reserved for GPIO
        '''
        return self.getPin().ref(PORT_PINS.ports_settings_reserve.S).enumIndex != 0

    def __getReservedLabel(self):
        '''
        :rtype: str
        :return: The reserved label for GPIO
        '''
        if self.__isReserved():
            return 'GPIO_{0}'.format(self.getPin().name)
        else:
            return ''

    def __getOverrideLabel(self):
        '''
        :rtype: str
        :return: The custom label string (user-assigned)
        '''
        return self.pin.ref(PORT_PINS.ports_settings_custompinname.S).get()

    def __setOverrideLabel(self, label):
        '''
        Sets the given label as custom label on the pin.
        :param label: Label to assign to the pin
        :return: void
        '''
        RuntimeModel.set_property_value(self.pin.ref(PORT_PINS.ports_settings_custompinname.S), label, module=self.pin)

    def __getHalLabel(self):
        '''
        :rtype: str
        :return: The HAL label string (module-assigned)
        '''
        return self.pin.ref(PORT_PINS.ports_settings_halpinname.S).get()

    def getLabel(self):
        '''
        :rtype: str
        :return: The pin label with all pin assignments (separated by forward slash '/')
        '''
        labels = ' / '.join(self.__getAssignmentList() + self.__getHalAssignmentList())

        if self.__getOverrideLabel():
            if labels:
                return '{0} : ({1})'.format(labels, self.__getOverrideLabel())
            else:
                return '({0})'.format(self.__getOverrideLabel())
        else:
            return labels

    def getColor(self):
        '''
        :rtype: str
        :return: Pin color ('None', 'routed' (blue), or 'conflict' (red))
        '''
        if self.__getNumAssignments() + self.__getNumHalAssignments() == 0:
            # No route or hal assignment => pin not used
            return None
        elif self.__getNumAssignments() > 1:
            # 2 or more route assignments => conflict
            return 'conflict'
        elif (self.__getNumAssignments() + self.__getNumHalAssignments()) > 1:
            # 2 or more hal+route assignments => warning
            # TODO: return soft-conflict when Studio supports it
            return 'routed'
        else:
            return 'routed'

    def getRoutes(self):
        """
        :rtype: [Route]
        :return: A list of Route objects
        """
        return self.routes

    def isAportConnected(self):
        """
        Returns True if one ore more of the assigned routes are boolean, and False if not
        :rtype: boolean
        """
        for route in self.routes:
            if route.getAportName():
                return True
        return False

    def errors(self):
        '''
        :rtype: (Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_IPropertyReference, str)
        :return: A list of property/error message tuples
        '''
        if self.__getNumAssignments() > 1:
            for route in self.routes:
                conflictinglabels = self.__getAssignmentList()
                conflictinglabels.remove(route.getLabel())
                yield (route.getPropRef(),
                       '{0} pin assignment conflicts with {1}'.format(route.getLabel(), ', '.join(conflictinglabels)))
            if self.__isReserved():
                conflictinglabels = self.__getAssignmentList()
                conflictinglabels.remove(self.__getReservedLabel())
                yield (self.getPin().ref(PORT_PINS.ports_settings_reserve.S),
                       '{0} pin assignment conflicts with {1}'.format(self.__getReservedLabel(),
                                                                      ', '.join(conflictinglabels)))
        if self.__getNumHalAssignments() + self.__getNumAssignments() > 1:
            for label in self.__getHalAssignmentList():
                conflictinglabels = self.__getHalAssignmentList() + self.__getAssignmentList()
                # We don't conflict with ourselves
                conflictinglabels.remove(label)
                for conflicting in Metadata.allowed_route_conflicts(label):
                    conflictinglabels = [l for l in conflictinglabels if not l.startswith(conflicting)]
                # We don't conflict with HAL labels with the same prefix (only difference in ending digits)
                nonconflictinglabels = [l for l in conflictinglabels if l.rstrip("0123456789") == label.rstrip("0123456789")]
                for nlabel in nonconflictinglabels:
                    conflictinglabels.remove(nlabel)
                # Yield a warning if we still conflict
                if conflictinglabels:
                    yield (self.getPin().ref(PORT_PINS.ports_settings_halpinname.S),
                           '{0} pin assignment conflicts with {1}'.format(label,
                                                                          ', '.join(conflictinglabels)))


def activePinRoutes(portio):
    '''
    Return all enabled pin routes in a RouteLocation object
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    :rtype Route
    '''
    for selector in portio.selectors:
        if False: assert isinstance(selector,
                                    Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ISelectorAccessor)

        # Not all selectors have a location property
        if selector.locationPropertyReference:
            selectorLocation = selector.locationPropertyReference.get()
        else:
            selectorLocation = None

        for route in selector.routes:
            if False: assert isinstance(route,
                                        Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IRouteAccessor)
            # Route is enabled, so get the pin location
            if route.enablePropertyReference.enumIndex == 1:
                for location in route.locations:
                    if False: assert isinstance(location,
                                                Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ILocationAccessor)

                    # If selector doesn't have a location property, then use the first location,
                    # otherwise find matching location number by string comparison
                    if (not selectorLocation) or (str(location.locationNumber) == selectorLocation):
                        yield Route(selector, route, location)
                        break


def aportWarnings(aportPinAssignments):
    """
    Yields tuples (prop, msg) to be sent as warnings if multiple APORT routes are assigned to same input/output
    :type aportPinAssignments: { pin ID : PinRoutes }
    :param aportPinAssignments: A dictionary of all active APORT pin routes from each pin with at least one APORT module enabled
    :rtype: (Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_IPropertyReference, str)
    :return: A list of property/error message tuples
    """

    ## Finding modules used
    moduleToRouteMap = {}
    for pinRoute in aportPinAssignments.values():
        for route in pinRoute.getRoutes():

            # Adding modules
            if route.getModuleName() in moduleToRouteMap.keys():
                moduleToRouteMap[route.getModuleName()].append(route)
            else:
                moduleToRouteMap[route.getModuleName()] = [route]

    ## For each module, look for multiple input/output of same type
    msgTemplate = "{0} assignment conflicts with {1}. Multiple {2} input/output on same APORT module"
    for routeList in moduleToRouteMap.values():
        if len(routeList) > 1:

            # Defining list to search through and counter dictionary, and counting appearance of iotype
            iotypeCountMap = {}
            for route in routeList:
                iotype = None
                nameParts = route.getName().split("_")
                if len(nameParts) > 1:
                    iotype = "_".join(nameParts[:-1])
                if iotype:
                    if iotype not in iotypeCountMap:
                        iotypeCountMap[iotype] = 1
                    else:
                        iotypeCountMap[iotype] += 1

            # Yielding tuples if conflict is found
            for iotype in iotypeCountMap.keys():
                for route in routeList:
                    if iotype in route.getLabel() and iotypeCountMap[iotype] > 1:
                        labelList = [iotypeRoute.getLabel() for iotypeRoute in routeList if
                                         iotype in iotypeRoute.getLabel()]
                        labelList.remove(route.getLabel())
                        yield (route.getPin().ref(PORT_PINS.ports_settings_dummy.S),
                               msgTemplate.format(route.getLabel(), ", ".join(labelList), iotype))


def aportInfos(aportPinAssignments):
    """
    Generates info prop/msg to be sent by newInfo
    :param aportPinAssignments: A dictionary of all active APORT pin routes from each pin with at least one APORT module enabled
    :return: A list of property/message tuples
    """
    ## Finding buses used
    busesInUse = {}
    for pinRoute in aportPinAssignments.values():
        for route in pinRoute.getRoutes():

            # Adding buses
            if route.getAportName() not in busesInUse.keys():
                busesInUse[route.getAportName()] = [route]
            else:
                busesInUse[route.getAportName()].append(route)

    ##  Looking at each bus to look for multiple usage
    for busUse in busesInUse.values():
        if len(busUse) > 1:
            msgTemplate = "{0} bus assignment conflicts with {1}. Disable master for "
            if len(busUse) == 2:
                msgTemplate += "one of them"
            else:
                msgTemplate += "all but one"

            # Making a list of routeLabels for the routes assigned to this bus and yielding warnings
            for route in busUse:
                labelList = [busRoute.getLabel() for busRoute in busUse]
                labelList.remove(route.getLabel())
                yield (route.getPin().ref(PORT_PINS.ports_settings_dummy.S),
                       msgTemplate.format(route.getLabel(), ", ".join(labelList)))