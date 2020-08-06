"""
Generated from a template
"""

import Studio
import ezr32hg.PythonSnippet.RuntimeModel as RuntimeModel
from ezr32hg.modules.PIN.PIN_Class import *
#from modules32.APORT_EFR.APORT_EFR_Defs import APORT_EFR
import collections
import time

##Public control variables
SNIPPET_PROFILE = False


'''
A dictionary of modes to signal assignments for all pins
{ str : ( com_silabs_ide_halconf_core_client_ISignalReference, [str, str] ) }
{ mode name : ( pin assignment, [label, color] ) }
'''
LastSignalSettings = {}


def activate_runtime():
    RuntimeModel.set_change_handler_regex('PORTIO', 'portio\.[^.]*\.enable\..*' , onPortRoutePropertyChange)
    RuntimeModel.set_change_handler_regex('PORTIO', 'portio\.[^.]*\.location\..*', onPortRoutePropertyChange)

    RuntimeModel.set_change_handler_regex('P[A-Z][0-9][0-5]?', PORT_PINS.ports_settings_custompinname.S, onPortPinPropertyChange)
    RuntimeModel.set_change_handler_regex('P[A-Z][0-9][0-5]?', PORT_PINS.ports_settings_halpinname.S, onPortPinPropertyChange)
    RuntimeModel.set_change_handler_regex('P[A-Z][0-9][0-5]?', PORT_PINS.ports_settings_reserve.S, onPortPinPropertyChange)









def inLastSignalSettings(mode, signalSetting):
    '''
    :type mode: str
    :param mode: The mode name
    :type signalSetting: ( com_silabs_ide_halconf_core_client_ISignalReference, [str, str] )
    :return: True if the signal setting already exists in the list (setting has already
    been applied and can be ignored)
    '''
    global LastSignalSettings

    if mode in LastSignalSettings:
        for lastSignalSetting in LastSignalSettings[mode]:
            if lastSignalSetting[0].id == signalSetting[0].id and lastSignalSetting[1] == signalSetting[1]:
                return True

    return False


def validateRouting(portio, state):
    '''
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    '''

    if SNIPPET_PROFILE:
        start = time.time()

    # ensure that this is always in a known mapping group
    RuntimeModel.new_problem_group(None, portio, state, 'validateRouting')

    """
    A map that stores the pin assignment(s) for each physical pin:
    { pin ID : PinRoutes }
    """
    pinAssignments = collections.OrderedDict()

    """
    Generate a PinLabelsRoutes structures for each pin.
    Add the pin accessor and create an empty label list to track the assigned pin labels
    """
    for portbank in portio.portBanks:
        for pin in portbank.pins:
            pinAssignments[pin.id] = PinRoutes(pin, [])

    for route in activePinRoutes(portio):
        pinAssignments[route.getPinId()].pin = route.getPin()
        pinAssignments[route.getPinId()].routes.append(route)

    signalSettings = []

    # for module in portio.mode.getPeripherals():
    #     if 'APORT' in module.name:
    #         for attribute in dir(APORT_EFR.SIGNALS):
    #             if 'STAT' in attribute:
    #                 print(attribute + " : " + str(module.signal(getattr(APORT_EFR.SIGNALS, attribute)).get()))

    for pinRoute in pinAssignments.values():
        label = pinRoute.getLabel()
        color = pinRoute.getColor()

        # This is the place to override pin labels for APORT
        labels = label.split(' / ')
        newlabels = []
        for partiallabel in labels:
            newlabel = partiallabel
            # if 'APORT' in partiallabel:
            #     # get reference to aport through mode
            #     modules = portio.mode.getPeripherals()
            #
            #     for module in modules:
            #         if 'APORT' in module.name:
            #             chan = partiallabel.replace('APORT_', '').replace("P", "X").replace("N", "Y")
            #             newlabel = str(module.signal(getattr(APORT_EFR.SIGNALS, chan + "_STAT")).get())
            #             print(chan + " : " + newlabel)
            #
            #     newlabels.append(newlabel)
            # else:
            newlabels.append(newlabel)

        label = ' / '.join(newlabels)

        # Set pin signal assignment
        signalSettings.append((pinRoute.getPin().assignmentSignal, [label, color]))

        for (prop, msg) in pinRoute.errors():
            RuntimeModel.new_warning(prop, msg, state)

    # Filtering out non-aport pinRoutes
    aportPinAssignments = {}
    for pinID in pinAssignments.keys():
        if pinAssignments[pinID].isAportConnected():
            aportPinAssignments[pinID] = pinAssignments[pinID]
            for route in pinAssignments[pinID].getRoutes():
                if not route.getAportName():
                    aportPinAssignments[pinID].getRoutes().remove(route)

    # Generating warnings and infos
    for (prop, msg) in aportWarnings(aportPinAssignments):
        RuntimeModel.new_warning(prop, msg, state)
    for (prop, msg) in aportInfos(aportPinAssignments):
        RuntimeModel.new_info(prop, msg, state)

    # Only apply a signal setting if it isn't the same as the previous value
    for (signal, setting) in signalSettings:
        if not inLastSignalSettings(portio.mode.name, (signal, setting)):
            RuntimeModel.set_signal_value(signal, setting, state)

    # Keep track of settings for next time
    LastSignalSettings[portio.mode.name] = signalSettings

    # Validate that all module routes in use are enabled on the portio
    # validateAllModuleRouteEnablesAndModes(portio)

    if SNIPPET_PROFILE:
        stop = time.time()
        print("validateRouting() completed in {:.3f} ms".format((stop - start) * 1000))


def validateAllModuleRouteEnablesAndModes(portio):
    '''
    Check that the routes used by modules are enabled on the portio
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    '''
    if SNIPPET_PROFILE:
        start = time.time()

    # ensure that this is always in a known mapping group
    RuntimeModel.new_problem_group(None, portio, 'validateAllModuleRouteEnablesAndModes')

    for signal in portio.signals:
        signalNameComponents = signal.name.split('|')
        if len(signalNameComponents) == 3:
            module = signalNameComponents[0]
            route = signalNameComponents[1]
            signalType = signalNameComponents[2]
            if signalType == 'EN':
                # If the validation enable signal is True, validate the route enable property
                if signal.get() == True:
                    validateModuleRouteEnable(portio, module, route)



    if SNIPPET_PROFILE:
        stop = time.time()
        print("validateAllModuleRouteEnablesAndModes() completed in {:.3f} ms".format((stop - start) * 1000))


def validateModuleRouteEnable(portio, module_name, route_name):
    selector_route = findRoute(portio, module_name, route_name)

    if not selector_route:
        return

    # Add an error if the route is not enabled
    if selector_route[1].enablePropertyReference.enumIndex == 0:
        RuntimeModel.new_warning(selector_route[1].enablePropertyReference,
                 '{0}_{1} pin is in use and must be enabled'.format(module_name, route_name))





def findRoute(portio, module_name, route_name):
    '''
    Search the portio routes for a matching module and route name and return a (selector, route) tuple
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    :rtype: (Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ISelectorAccessor, Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IRouteAccessor)
    '''
    if portio.selectors:
        for selector in portio.selectors:
            if False: assert isinstance(selector,
                                        Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ISelectorAccessor)

            module = selector.module
            if False: assert isinstance(module,
                                        Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IModuleAccessor)

            # Found a matching selector with the same module name
            if module.name and module.name == module_name:
                # Search all routes for matching pin name
                if selector.routes:
                    for route in selector.routes:
                        if False: assert isinstance(route,
                                                    Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IRouteAccessor)
                        # Found route with matching route name
                        if route.name == route_name:
                            # Found a route with matching module and route name
                            return (selector, route)

        # No match found
        return None
    else:
        return None


def getCurrentRouteLocation(portio, selector, route):
    '''
    Given a route, return the active location
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    :type selector: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ISelectorAccessor
    :type route: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IRouteAccessor
    :rtype: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ILocationAccessor
    '''
    # Find location if the route has a location property
    for location in route.locations:
        if False: assert isinstance(location,
                                    Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_ILocationAccessor)

        # Not all selectors have a location property
        if selector.locationPropertyReference:
            selectorLocation = selector.locationPropertyReference.get()
        else:
            selectorLocation = None

        # If there isn't a selector location, use the first location
        # Otherwise search for a matching location number
        if (not selectorLocation) or (str(location.locationNumber) == selectorLocation):
            return location

    return None


def isRouteEnabled(portio, module_name, route_name):
    if findRoute(portio, module_name, route_name) is None:
        return False

    (selector, route) = findRoute(portio, module_name, route_name)
    if route:
        if route.enablePropertyReference.enumIndex == 1:
            return True

    return False


def onPortPinPropertyChange(pin, prop, state):
    '''
    :type pin: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPinAccessor
    '''
    validateRouting(pin.mode.portIO, state)


def onPortRoutePropertyChange(portio, prop, state):
    '''
    :type portio: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IPortIOAccessor
    '''
    validateRouting(portio, state)


def onLoad(state):
    '''
    :type dev: Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IDeviceAccessor
    '''
    for mode in state.device.getModes():
        if False: assert isinstance(mode,
                                    Studio._private.StudioClasses.com_silabs_ide_halconf_core_client_accessors_IModeAccessor)
        validateRouting(mode.portIO, state)





