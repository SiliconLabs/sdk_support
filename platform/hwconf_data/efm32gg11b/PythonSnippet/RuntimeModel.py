"""
Collection of functions to exercise the model at Studio runtime
"""

import Studio
import sys
if sys.version_info[0] == 2:
    import ExporterModel
    import Metadata
else:
    from . import ExporterModel
    from . import Metadata

class State(object):
    def __init__(self, device=None, module=None, mode=None, args=None):
        self.changes = []
        self.device = device
        self.studio_module = module
        self.mode = mode
        self.args = args
        self.exported_modules = {}

    def update(self, device=None, module=None, mode=None, args=None):
        self.changes = []
        if device:
            self.device = device
        if module:
            self.studio_module = module
        if mode:
            self.mode = mode
        self.args = args

    def set_module_object(self, module_name, module_object):
        self.exported_modules[module_name] = module_object

    def get_module_object(self, module_name):
        return self.exported_modules.get(module_name)

class StateManager():
    instance = None
    class __StateManager():
        def __init__(self):
            self.states = {}
        def register_state(self, document, state):
#            if document in self.states:
#                print("WARNING: State already exists for {}!".format(document))
            self.states[document] = state
        def get_state(self, document):

            return self.states[document]
    def __init__(self):
        if not StateManager.instance:
#            print("Creating first SM instance")
            StateManager.instance = StateManager.__StateManager()
#        else:
#            print("SM inst already exists")
    def __getattr__(self, name):
        return getattr(self.instance, name)

def bind_document_upgrade(func):

    def upgradeCall(event, device):
        return func(event, device)
    ##END: upgradeCall()

    Studio.halConfig.addEventHandler(Studio.halConfig.UPGRADE_DOCUMENT, None, upgradeCall)

    return func

def bind_document_load(func):
    '''
    Binds the decorated function to run whenever the document is loaded
    :param func: Python function func(device) to run on document load
    '''
    def realCall(event, device):
        state_manager = StateManager()
        state = State(device=device, mode=device.getModes()[0])
        state_manager.register_state(state.device.getDocument().getPath(), state)
        func(state)
        return state.changes
    ##END: realCall()

    oFilter = Studio.halConfig.newObjectNameEventFilter('.*')
    Studio.halConfig.addEventHandler(Studio.halConfig.DOCUMENT_LOAD, oFilter, realCall)

    return func


def set_change_handler(property, func, on_enable=False, args=None):
    """
    Sets up a change handler on the given property
    :param property: ExporterModel Property on which the callback will get registered
    :param func: Python function of the form func(studio_module, exportmodel_prop)
    :param on_enable: If true, register callback on enable checkbox too
    :return: property
    """

    def realCall(event, prop):
        state = StateManager().get_state(prop.object.getDocument().getPath())
        state.update(module=prop.object, mode=prop.object.getMode(), args=args)
        # Execute bound function
        if on_enable:
            is_enable = True if prop.propertyId == 'ABPeripheral.included' else False
            func(state.studio_module, property, state, is_enable)
        else:
            func(state.studio_module, property, state)
        # Return possibly changed properties to Studio for execution
        return state.changes

    prop = property.id
    if on_enable:
        prop = "({}|ABPeripheral.included)".format(prop)

    eFilter = Studio.halConfig.newObjectPropertyEventFilter(property.parent.name, prop)
    Studio.halConfig.addEventHandler(Studio.halConfig.PROPERTY_CHANGE, eFilter, realCall)
    return property


def set_enable_handler(module, func, args=None):
    """
    Sets up a enable handler on the given property
    :param module: ExporterModel Module on which the callback will get registered
    :param func: Python function of the form func(studio_module, exportmodel_module)
    :return: property
    """

    def realCall(event, prop):
        state = StateManager().get_state(prop.object.getDocument().getPath())
        state.update(module=prop.object, mode=prop.object.getMode(), args=args)
        # Execute bound function
        func(state.studio_module, module, state)
        # Return possibly changed properties to Studio for execution
        return state.changes

    eFilter = Studio.halConfig.newObjectPropertyEventFilter(module.name, 'ABPeripheral.included')
    Studio.halConfig.addEventHandler(Studio.halConfig.PROPERTY_CHANGE, eFilter, realCall)
    return property


def set_change_handler_regex(module_re, property_re, func, args = None, on_enable=False):
    """
    Sets up a change handler on the given modules' property/ies
    :param module_re: Regular expression matching the module(s) on which to look for properties
    :type module_re: str
    :param property_re: Regular expression matching the property/ies
    :type property_re: str
    :param func: Python callback function of form func(studio_module, studio_prop, args)
    :param args: arguments to pass to callback
    :return: None
    """
    def realCall(event, prop):
        state = StateManager().get_state(prop.object.getDocument().getPath())
        state.update(module=prop.object, mode=prop.object.getMode(), args=args)
        # Execute bound function
        if on_enable:
            is_enable = True if prop.propertyId == 'ABPeripheral.included' else False
            func(state.studio_module, prop, state, is_enable)
        else:
            func(state.studio_module, prop, state)
        # Return possibly changed properties to Studio for execution
        return state.changes

    if on_enable:
        property_re = "({}|ABPeripheral.included)".format(property_re)

    eFilter = Studio.halConfig.newObjectPropertyEventFilter(module_re, property_re)
    Studio.halConfig.addEventHandler(Studio.halConfig.PROPERTY_CHANGE, eFilter, realCall)


def get_module_checked(module, mode):
    if isinstance(module, str):
        module = get_studio_module_by_name(module, mode)

    return module.getProperty("ABPeripheral.included")


def set_module_checked(module, checked, state, readonly=False):
    if isinstance(module, str):
        module = get_studio_module_by_name(module, state.mode)

    property = module.getPropertyReference("ABPeripheral.included")
    state.changes.append(Studio.halConfig.newPropertySetting(property, checked))
    state.changes.append(Studio.halConfig.newIsReadOnlySetting(property, readonly))


def set_module_visible(module, state, visible):
    if isinstance(module, str):
        module = get_studio_module_by_name(module, state.mode)

    property = module.getPropertyReference("ABPeripheral.included")
    state.changes.append(Studio.halConfig.newIsHiddenSetting(property, not visible))


def get_property_reference(property, module):
    """
    Tries to get a Studio property reference from a 'property' object through type-checking
    :param property: property-like object
    :param module: Studio module object
    :return: Studio property ID or None
    """
    if isinstance(property, ExporterModel.Property):
        return module.ref(property.id)
    elif isinstance(property, str):
        if '.' in property:
            return module.ref(property)
        else:
            # Get ExporterModel module object related to this Studio module object
            emodule = StateManager().get_state(module.getDocument().getPath()).get_module_object(module.name)
            assert emodule is not None
            property = ExporterModel.get_property(emodule, property)
            if property is not None:
                return module.ref(property.id)
            else:
                return None
    else:
        return property


def get_property_model(property, module):
    """
    Tries to get a property model object from a 'property' object
    :param property: property-like object
    :return: Model property object or None
    """
    if isinstance(property, ExporterModel.Property):
        return property
    elif isinstance(property, str):
        # Get ExporterModel module object related to this Studio module object
        emodule = StateManager().get_state(module.getDocument().getPath()).get_module_object(module.name)

        if '.' in property:
            return ExporterModel.get_property(emodule, property.split('.')[1])
        else:
            return ExporterModel.get_property(emodule, property)
    else:
        # Get ExporterModel module object related to this Studio module object
        emodule = StateManager().get_state(property.getDocument().getPath()).get_module_object(module.name)

        # Studio properties get tricky
        return ExporterModel.get_property(emodule, property.id.split('.')[1])


def get_property_value(property, module, check_pending=True):
    """
    Get the runtime setting of a property
    :param module: Studio Module object.
    :param property: ExporterModel Property, Studio property or property string
    :return: String value of the property
    """
    if module is None:
        return None

    prop = get_property_reference(property, module)

    if prop is not None:
        # Default to getting the value from the document
        prop_value = prop.get()

        # Check if we have a pending change with a newer value
        if check_pending:
            state = StateManager().get_state(prop.object.getDocument().getPath())
            for change in state.changes:
                if "PropertyChange" in str(change) and change.propertyReference == prop and hasattr(change, 'newValue'):
                    prop_value = change.newValue

        return str(prop_value)
    else:
        return None


def get_property_define(property, module):
    """
    Get the runtime #define setting of a property
    :param module: Studio Module object.
    :param property: ExporterModel Property, Studio property or property string
    :return: String value of the value property
    """
    if module is None:
        return None

    prop = get_property_reference(property, module)
    if prop is not None:
        return str(prop.get())

    return ""


def get_property_values(property, module):
    """
    Get the possible values for a property
    :param module: Studio Module object.
    :param property: ExporterModel Property, Studio property or property string
    :return: List of possible values. Empty list if not an enum-based property.
    """
    if module is None:
        return []

    propref = get_property_reference(property, module)

    if propref.getEnumValues():
        return [str(p) for p in propref.getEnumValues()]
    else:
        return []


def set_property_value(property, value, state, module=None):
    """
    Set the runtime setting of a property
    :param property: ExporterModel Property, Studio property or property string
    :param value: Value to set the property to
    :param state: Context variable
    :param module: Studio Module object. If not given, module is taken from state
    :return: None
    """
    if not module:
#        if isinstance(property, ExporterModel.Property):
#            module = get_studio_module_by_name(property.parent.name, state.mode)
#        else:
        module = state.studio_module
    propref = get_property_reference(property, module)

    assert propref is not None

    state.changes.append(Studio.halConfig.newPropertySetting(propref, value))

    return None


def set_signal_value(signal, value, state):
    """
    Set the runtime value of a signal
    :param signal: Studio signal
    :param value: Value to set the signal to
    :param state: Context variable
    :return: None
    """
    state.changes.append(Studio.halConfig.newSignalSetting(signal, value))

    return None


def set_property_readonly(property, readonly, state, module=None):
    """
    Set a property to read-only (greyed out)
    :param property: ExporterModel Property, Studio property or property string
    :param readonly: True if property needs to be read-only
    :param state: Context variable
    :param module: Studio Module object. If not given, module is taken from state
    :return: None
    """
    if not module:
        module = state.studio_module
    propref = get_property_reference(property, module)

    state.changes.append(Studio.halConfig.newIsReadOnlySetting(propref, readonly))

    return None


def get_property_readonly(property, module):
    """
    Get the read-only setting of a property
    :param property: ExporterModel Property, Studio property or property string
    :param module: Studio Module object.
    :return: True if property is set to read-only
    """
    #TODO: implement this function?
    pass


def set_property_hidden(property, hidden, state, module=None):
    """
    Set a property hidden (invisible)
    :param property: ExporterModel Property, Studio property or property string
    :param readonly: True if property needs to be read-only
    :param state: Context variable
    :param module: Studio Module object. If not given, module is taken from state
    :return: None
    """
    if not module:
        module = state.studio_module
    propref = get_property_reference(property, module)

    state.changes.append(Studio.halConfig.newIsHiddenSetting(propref, hidden))

    return None


def get_property_hidden(property, module):
    """
    Get the hidden setting of a property
    :param property: ExporterModel Property, Studio property or property string
    :param module: Studio Module object.
    :return: True if property is set to hidden
    """
    #TODO: implement this function?
    pass


def set_module_ownership(owner_name, owned_name, possible_owned_list, state, greyout=False):
    """
    Tries to set the owner property on a peripheral to the owner module
    :param owner_name: Name of the owner module
    :param owned_name: Name of the requested owned module
    :param possible_owned_list: List over all modules the owner module might have had ownership of
    :param state: Context variable
    :param greyout: Disable owned module's properties from user changes
    :return: True if owner_name is the only owner, False if the requested module is also owned by another module
    """
    # Changed selection to no longer own module
    for owned_mod in [m for m in possible_owned_list if m not in ["None", owned_name]]:
        prev_owner = get_property_value("owner", module=get_studio_module_by_name(owned_mod, state.mode))
        if prev_owner and ', ' in prev_owner:
            owner_list = prev_owner.split(", ")
            if owner_name in owner_list:
                    owner_list.remove(owner_name)
                    new_owner = ", ".join(owner_list)
                    set_property_value("owner", new_owner, state=state, module=get_studio_module_by_name(owned_mod, state.mode))
                    set_module_checked(owned_mod, get_module_checked(owned_mod, state.mode), state, readonly=True)
        elif prev_owner and prev_owner == owner_name:
            set_property_value("owner", "", state=state, module=get_studio_module_by_name(owned_mod, state.mode))
            set_module_checked(owned_mod, get_module_checked(owned_mod, state.mode), state, readonly=False)
        if greyout:
            # TODO: return module properties back to changeable state
                pass

    if owned_name == 'None':
        return True
    else:
        # try to own requested module
        prev_owner = get_property_value("owner", module=get_studio_module_by_name(owned_name, state.mode))
        if not prev_owner:
            # Nobody owns the module; take it
            set_property_value("owner", owner_name, state=state, module=get_studio_module_by_name(owned_name, state.mode))
            set_module_checked(owned_name, True, state, readonly=True)
            # TODO: set enable checkbox to read-only and possibly properties too
            return True
        elif owner_name in prev_owner:
            # We already own the module
            return True
        else:
            # Somebody else owns the module - setting double ownership
            set_property_value("owner", "{0}, {1}".format(prev_owner, owner_name), state=state, module=get_studio_module_by_name(owned_name, state.mode))
            return False


def get_studio_module_by_name(module_name, mode):
    for p in mode.getPeripherals():
        if p.name == module_name:
            return p
    return None


def get_studio_pin_modules(mode):
    pin_list = []
    for port in mode.portIO.getPortBanks():
        for pin in port.getPins():
            pin_list.append(pin)

    return pin_list


def owning_module_property_callback(studio_module, model_property, state, is_enable):
    owner_name = model_property.parent.name + model_property.define_name_postfix
    if get_module_checked(studio_module, studio_module.getMode()):
        new_owned_name = get_property_value(model_property, module=studio_module)
        print("Module prop on {} changed to {}".format(owner_name, new_owned_name))
        if set_module_ownership(owner_name, new_owned_name, get_property_values(model_property, module=studio_module), state):
            # Studio_module is only owner, so apply owner-decided mode for owned module
            if model_property.owned_mode is not None and new_owned_name != "None":
                print("Changing mode on {} to {}".format(new_owned_name, model_property.owned_mode))
                prop_id = get_property_id_from_label("mode", new_owned_name, studio_module.getMode())
                if prop_id:
                    prop_name = prop_id.split('.')[1]
                    set_property_value(str(prop_name),
                                       model_property.owned_mode,
                                       state=state,
                                       module=get_studio_module_by_name(new_owned_name, state.mode))
        else:
            # Successfully added multiple owners. Mode is not changed for owned module
            pass

    else:
        set_module_ownership(owner_name, 'None',
                             get_property_values(model_property, module=studio_module),
                             state)


def module_mode_callback(studio_module, model_property, state):
    owner_module_name = model_property.parent.name
    new_mode_name = get_property_define(model_property, module=studio_module)

    show_advanced = get_property_value(model_property.parent.get_property('showadvanced'), studio_module) == '1'

    print("Mode on {} changed to {} (advanced = {})".format(owner_module_name, new_mode_name, show_advanced))

    if not model_property.hide_properties:
        return

    for modprop in model_property.parent.get_properties():
        if not show_advanced and modprop.is_advanced:
            # Do nothing to advanced properties if not in advanced mode
            continue
        if modprop.mode is not None:
            # Setting visibility for relevant properties
            if isinstance(modprop.mode, list):
                if new_mode_name in modprop.mode:
                    set_property_hidden(modprop, False, state=state)
                else:
                    set_property_hidden(modprop, True, state=state)
            else:
                if modprop.mode == new_mode_name:
                    set_property_hidden(modprop, False, state=state)
                else:
                    set_property_hidden(modprop, True, state=state)


def pin_selection_callback(studio_module, model_property, state, selected_pin=None):
    module_enabled = get_property_value('ABPeripheral.included', studio_module) == 'True'
    if not module_enabled and not selected_pin:
        return

    if not selected_pin:
        selected_pin = get_property_value(model_property, module=studio_module)

    for instance in get_studio_pin_modules(studio_module.getMode()):
        vals = get_property_value('ports.settings.halpinname', module=instance).split(',')
        if vals == ['']:
            vals = []
        if instance.name == selected_pin:
            # This is the pin we're taking ownership of
            if vals:
                if model_property.name not in vals:
                    # Add name to pin if not already present
                    vals.append(model_property.name)
                else:
                    # Name already added to pin, do nothing
                    pass
            else:
                # We're the first owner
                vals.append(model_property.name)
            set_property_value('ports.settings.halpinname', ','.join(vals), state=state, module=instance)
        elif model_property.name in vals:
            # Remove the pin name on other GPIO
            vals.remove(model_property.name)
            set_property_value('ports.settings.halpinname', ','.join(vals), state=state, module=instance)


def route_selection_callback(studio_module, pin_property, state, selected_pin=None):
    """
    Callback when a PinProperty changed in some module, requiring PORTIO to be updated
    :param studio_module:  The peripheral module that contains the changed PinProperty
    :param pin_property: The changed PinProperty (ExporterModel object)
    :return:
    """
    module_enabled = get_property_value('ABPeripheral.included', studio_module) == 'True'
    if not module_enabled and not selected_pin:
        return

    mod = pin_property.referenced_module
    route_name = pin_property.referenced_route
    if not selected_pin:
        selected_pin = get_property_value(pin_property, module=studio_module)

    portio = studio_module.mode.portIO
    _route_selection_callback_internal(mod, route_name, selected_pin, portio, state)


def aport_single_selection_callback(studio_module, pin_property, state, selected_pin=None):
    """
    Callback when an APORT PinProperty changed in some module, requiring PORTIO to be updated
    :param studio_module:
    :param pin_property:
    :param state:
    :return:
    """
    module_enabled = get_property_value('ABPeripheral.included', studio_module) == 'True'
    if not module_enabled and not selected_pin:
        return

    prop_id = pin_property.getPropertyId()
    bus = prop_id.split('.')[1].split('_')[-1]

    mod = studio_module.getName()
    bus_prop = state.args['model_prop']

    route_name = "{}_{}".format(bus_prop.signal, bus)
    if not selected_pin:
        selected_pin = pin_property.get()
    _route_selection_callback_internal(mod, route_name, selected_pin, studio_module.mode.portIO, state)


def _route_selection_callback_internal(mod, route_name, selected_pin, portio, state):
    """
    :param mod: Module name
    :param route_name: Route name
    :param selected_pin: Selected pin on route
    :param portio: Portio object
    :param state: Current state
    :return:
    """
    # Get the selectors for the given peripheral
    selectors = filter(lambda x: str(x.module).split('::')[1] == mod, portio.selectors)
    route = None

    for selector in selectors:
        # Search all selectors to find the one containing our route, and select the route
        route = list(filter(lambda x: str(x.name) == route_name, selector.routes))
        if route:
            # Selector contains route matching desired signal
            enable = route[0].enablePropertyReference
            if selected_pin != "Disabled":
                # Setting pin to something not-Disabled means we need to update the location on the route
                if selector.locationPropertyReference:
                    try:
                        # Selector has multiple locations for each route -- find the location number matching the
                        # pin name for our selected route
                        location = list(filter(lambda x: str(x.pin).split('::')[1] == selected_pin, route[0].locations))[0]
                        # Set location on referenced location property
                        set_property_value(selector.locationPropertyReference, str(location.locationNumber), module=portio, state=state)
                    except Exception as e:
                        print("WARNING :: Selected a pin with no valid location for route {}::{}".format(e.message, mod, route_name))
                        # Switch Enable property of route to Disabled
                        set_property_value(enable, "Disabled", module=portio, state=state)
                        break
                else:
                    # Selector has only a single location per route -- do nothing
                    pass
                # Switch Enable property of route to Enabled
                set_property_value(enable, "Enabled", module=portio, state=state)
            else:
                # Switch Enable property of route to Disabled
                set_property_value(enable, "Disabled", module=portio, state=state)
            break

    if not route:
        print("ERROR: Route {} does not exist in module {}".format(route_name, mod))


def module_usedbysdk_callback(studio_module, model_property, state):
    used = get_property_value(model_property, module=studio_module)
    set_module_checked(studio_module, used == '1', state, readonly=(used == '1'))

    for property_id in studio_module.getPropertyIds():
        prop_ref = studio_module.ref(property_id)
        set_property_readonly(prop_ref, True, state=state)


def module_hiddenbysdk_callback(studio_module, model_property, state):
    hidden = get_property_value(model_property, module=studio_module)
    # TODO: Actually hide modules when this thing starts working
    # set_module_visible(studio_module, studio_module.getMode(), not (hidden == 'True'))
    set_module_checked(studio_module, hidden != '1', state, readonly=True)

    for property_id in studio_module.getPropertyIds():
        prop_ref = studio_module.ref(property_id)
        set_property_hidden(prop_ref, True, state=state)


def module_showadvanced_callback(studio_module, model_property, state):
    show_advanced = get_property_value(model_property, module=studio_module) == '1'

    for property in model_property.parent.get_properties():
        if property.is_advanced and show_advanced:
            set_property_hidden(property, False, state)


def module_enabled_callback(studio_module, exporter_module, state):
    enabled = get_property_value('ABPeripheral.included', studio_module) == 'True'
    for prop in exporter_module.properties:
        if isinstance(prop, ExporterModel.PinProperty):
            selected_pin = get_property_value(prop, module=studio_module)
            if prop.referenced_module:
                if enabled and selected_pin != "Disabled":
                    # This pin had a selection when it was off, reapply it in portio
                    route_selection_callback(studio_module, prop, state)
                if not enabled and selected_pin != "Disabled":
                    # This pin had a selection when on, wipe it in portio
                    route_selection_callback(studio_module, prop, state, selected_pin="Disabled")
            else:
                if enabled and selected_pin != "Disabled":
                    # This pin had a selection when it was off, set it to halpinname
                    pin_selection_callback(studio_module, prop, state)
                if not enabled and selected_pin != "Disabled":
                    # Pin had a selection when on, wipe it from halpinname
                    pin_selection_callback(studio_module, prop, state, selected_pin="Disabled")
        if isinstance(prop, ExporterModel.AportBusProperty):
            for bus_name in [exporter_module.name + 'X', exporter_module.name + 'Y', 'AX', 'AY', 'BX', 'BY', 'CX', 'CY', 'DX', 'DY']:
                bus_property_prefix = "{}_".format(prop.define_name_prefix.lower())
                bus_property_name = bus_property_prefix + bus_name
                prop_id = exporter_module.namespace + '.' + bus_property_name + '.PIN'
                studio_property = studio_module.ref(prop_id)
                if studio_property:
                    selected_pin = get_property_value(prop, module=studio_module)
                    if not state.args:
                        state.args = {}
                    if enabled and selected_pin != "Disabled":
                        # This pin had a selection when it was off, reapply it in portio
                        state.args['model_prop'] = prop
                        aport_single_selection_callback(studio_module, studio_property, state)
                    if not enabled and selected_pin != "Disabled":
                        # This pin had a selection when on, wipe it in portio
                        state.args['model_prop'] = prop
                        aport_single_selection_callback(studio_module, studio_property, state, selected_pin="Disabled")



def route_selection_portio_callback(portio, portio_property, state):
    """
    Callback when a PORTIO changed on a module that has a PinProperty shadowing PORTIO
    :param portio:           Reference to the PORTIO studio module
    :param portio_property:  The changed PORTIO property object
    :param args:             Arbitrary arguments -- used to give us the PinProperty that needs updating
    :return:
    """
    pin_property = state.args['model_prop']
    if not pin_property:
        pin_property = state.args['studio_prop']

    signal_module = state.args['module_name']
    signal_route = state.args['route']
    studio_module = state.args['module']

    if get_property_value(state.args['enable'], module=portio) == "Enabled":
        # PORTIO property is enabled -- need to find the new pin name from the new location set in PORTIO
        # Get the selectors for the given peripheral

        selectors = filter(lambda x: str(x.module).split('::')[1] == signal_module, portio.selectors)
        location = None

        for selector in selectors:
            # Search all selectors to find the one containing our route, and select the route
            route = list(filter(lambda x: str(x.name) == signal_route, selector.routes))
            if route:
                # Selector contains route matching desired signal
                # Get the selected location from the route
                if selector.locationPropertyReference:
                    # Selector has multiple locations for each route -- find the location object matching the
                    # location number for our selected route
                    try:
                        location = list(filter(lambda x: str(x.locationNumber) == selector.locationPropertyReference.get(), route[0].locations))[0]
                    except:
                        # No pin on this location
                        print("WARNING: {} has no pin on location {}".format(signal_module, signal_route))
                        set_property_value(pin_property,
                                           "Disabled",
                                           module=studio_module,
                                           state=state)
                        return
                else:
                    # Selector has only a single location per route -- choose the first (and only one)
                    location = route[0].locations[0]
                break
        # Get the pin name from the location object
        if location:
            pin = str(location.pin).split('::')[-1]
            set_property_value(pin_property,
                               pin,
                               module=studio_module,
                               state=state)
    else:
        # PORTIO property was changed to disabled; disable PinProperty too
        # Note: Only disable PinProperty if parent module is enabled. If it is disabled, assume that we're reacting
        # on a callback to disable PORTIO routing after disabling the parent module. In this case, we want the
        # user selection to survive in the PinProperty, such that it can be reapplied by re-enabling the parent.
        if hasattr(pin_property, 'parent'):
            pp_owner = get_studio_module_by_name(pin_property.parent.name, studio_module.getMode())
        else:
            pp_owner = pin_property.getObject()
        enabled = get_property_value('ABPeripheral.included', pp_owner) == 'True'
        if enabled:
            set_property_value(pin_property,
                               "Disabled",
                               module=studio_module,
                               state=state)


def _configure_route_handler(prop, studio_prop, mod_name, route, module = None):
    location = "portio.{0}.location..+".format(mod_name.lower(), route.lower())
    enable = "portio.{0}.enable.{1}".format(mod_name.lower(), route.lower())
    set_change_handler_regex("PORTIO",
                             location,
                             route_selection_portio_callback,
                             {"model_prop": prop,
                              "studio_prop": studio_prop,
                              "enable": enable,
                              "module": module,
                              "module_name": mod_name,
                              "route": route})
    set_change_handler_regex("PORTIO",
                             enable,
                             route_selection_portio_callback,
                             {"model_prop": prop,
                              "studio_prop": studio_prop,
                              "enable": enable,
                              "module": module,
                              "module_name": mod_name,
                              "route": route})


def configure_route_handler(model_property, state):
    # If the property changes on the Peripheral Properties page, update port IO
    set_change_handler(model_property, route_selection_callback)

    mod = model_property.referenced_module
    route = model_property.referenced_route

    # If port IO changes, update the property
    _configure_route_handler(model_property, None, mod, route, module=get_studio_module_by_name(model_property.parent.name, state.mode))

def configure_aport_single_route_handler(aport, state):
    studio_module = get_studio_module_by_name(aport.parent.name, state.mode)

    # A change to PORTIO should propagate to peripherals view
    id = aport.define_name_prefix.lower()
    for prop_id in studio_module.getPropertyIds():
        if id in prop_id:
            bus = prop_id.split('.')[1].split('_')[-1]
            route_name = "{}_{}".format(aport.signal, bus)
            _configure_route_handler(None,
                                     studio_module.ref(prop_id),
                                     aport.parent.name,
                                     route_name,
                                     module=studio_module)

    # A change to the Peripherals view should propagate to PORTIO
    set_change_handler_regex(aport.parent.name,
                             "{}.{}.+PIN".format(aport.parent.namespace, aport.define_name_prefix.lower()),
                             aport_single_selection_callback,
                             {"model_prop": aport})

    # A change to the input selection should change which element is visible
    set_change_handler(aport, aport_single_bus_selection_callback, on_enable=True)


def aport_single_bus_selection_callback(studio_module, aport, state, is_enable):
    selected = get_property_value(aport, studio_module)
    id = aport.define_name_prefix.lower()
    selected_prop = selected[-2:].lower()
    for prop_id in studio_module.getPropertyIds():
        if id not in prop_id:
            continue
        busname = prop_id.lower().split('.')[1].split('_')[-1] # ax, bx, etc
        aportname = ExporterModel.busname_to_aportname(aport.parent.name, busname) # 1x, 2x, etc
        if selected_prop == aportname:
            # This is the selected property -- show
            set_property_hidden(studio_module.ref(prop_id), False, state, module=studio_module)
        else:
            # This is not the selected property -- hide
            set_property_hidden(studio_module.ref(prop_id), True, state, module=studio_module)
            set_property_value(studio_module.ref(prop_id), "Disabled", state, module=studio_module)


def new_problem_group(prop, studio_module, state, src=""):
    """ Creates a problem group. Old problems in the group will be erased when the problem group is called again """
    if prop is not None:
        identifier = "{}__{}__{}".format(prop.getObject().getName(), prop.getId().split("::")[1], src)
    else:
        identifier = "{}__{}".format(studio_module.getName(), src)
    state.changes.append(Studio.halConfig.newProblemGroup(studio_module.getMode(), identifier))


def new_error(prop, msg, state):
    """ Causes the passed error msg to be applied to the the passed property when realCall returns """
    state.changes.append(Studio.halConfig.newError(prop, msg))


def new_warning(prop, msg, state):
    """ Causes the passed warning msg to be applied to the the passed property when realCall returns """
    state.changes.append(Studio.halConfig.newWarning(prop, msg))


def new_info(prop, msg, state):
    """ Causes the passed problem msg to be applied to the the passed property when realCall returns """
    state.changes.append(Studio.halConfig.newProblem(prop, 1, msg))


def owner_changed_callback(studio_module, property, state):
    """ Generates warning for current module if there are multiple owners """
    owner = get_property_value(property, studio_module)
    prop_ref = get_property_reference(property, studio_module)
    new_problem_group(prop_ref, studio_module, state, src="owner_changed_callback")
    if ', ' in owner:
        msg = "{0} has multiple owners: {1}".format(studio_module.getName(), owner)
        new_info(prop_ref, msg, state)


def get_property_id_from_label(prop_label, studio_module_name, mode):
    """
    Searching through properties, returning the property ID with correct label, else None
    :param prop_label: string containing property label (i.e. the label in Studio XML files)
    :param studio_module_name: string representing a studio module
    :param mode: Mode to get Studio module from
    :return: Property ID, or None
    """
    studio_module = get_studio_module_by_name(studio_module_name, mode)
    for property_id in studio_module.getPropertyIds():
        prop_ref = studio_module.ref(property_id)
        if prop_ref.getLabel() == prop_label:
            return property_id
    return None


def prs_channel_changed_callback(studio_mod, channel_property, state, is_enable):
    """
    Callback for PRSChannelProperty class.
    Hides and unhides the the prs output pin selectors, based on the choice of channel.
    Sets relevant custom names in the PRS module
    """
    prs_channel_count = Metadata.get_prs_chan_with_gpio_count()
    selected_channel = get_property_value(channel_property, module=studio_mod)
    prs_studio_module = get_studio_module_by_name("PRS", studio_mod.getMode())
    subcategories = [sub_cat for sub_cat in prs_studio_module.getCategories()[0].getSubcategories()]

    # Removing old custom name
    custom_name = channel_property.custom_name if channel_property.custom_name else studio_mod.getName()
    for subcategory in subcategories:
        for property_id in subcategory.getPropertyIds():
            if str(subcategory.getLabel()) != "CH{} properties".format(selected_channel):
                # Remove custom name if the selection has changed
                prop_ref = prs_studio_module.ref(property_id)
                if "custom_name" in property_id and get_property_value(prop_ref, prs_studio_module) == custom_name:
                    set_property_value(prop_ref, "", module=prs_studio_module, state=state)
                    set_property_readonly(prop_ref, readonly=False, module=prs_studio_module, state=state)
            elif is_enable and not get_module_checked(module=studio_mod, mode=studio_mod.getMode()):
                # If callback is from disabling the module, always remove custom name from PRS module
                prop_ref = prs_studio_module.ref(property_id)
                if "custom_name" in property_id and get_property_value(prop_ref, prs_studio_module) == custom_name:
                    set_property_value(prop_ref, "", state, module=prs_studio_module)
                    set_property_readonly(prop_ref, readonly=False, state=state, module=prs_studio_module)

    # if module is enabled, set properties hidden/unhidden and custom names
    if get_module_checked(module=studio_mod, mode=studio_mod.getMode()):
        # Checking the selected value, to determine what to do
        if selected_channel == "Disabled":
            if channel_property.gpio:
                # Hiding all properties, except prs_disabled_chn_pin which should be displayed when selection is "Disabled"
                set_property_hidden("prs_disabled_chn_{}_pin".format(channel_property.custom_name if channel_property.custom_name else ""),
                                    hidden=False,
                                    state=state)
                for i in range(prs_channel_count):
                    set_property_hidden(channel_property.name.replace("_CHANNEL", str(i)),
                                        hidden=True,
                                        state=state)
        else:
            # Set custom name in PRS module, or return channel property to Disabled if custom name already set
            for subcategory in subcategories:
                label = str(subcategory.getLabel())
                if label == "CH{} properties".format(selected_channel):
                    for property_id in subcategory.getPropertyIds():
                        if "custom_name" in property_id:
                            custom_name_prop_ref = prs_studio_module.ref(property_id)
                            if get_property_value(custom_name_prop_ref, prs_studio_module) != "" and \
                                    get_property_value(custom_name_prop_ref, prs_studio_module) != custom_name:
                                # If channel is already taken, show warning
                                new_warning(get_property_reference(channel_property, studio_mod),
                                            "PRS channel already reserved for {}".format(get_property_value(custom_name_prop_ref, prs_studio_module)),
                                            state)
                            else:
                                # Set custom name and make it readonly
                                set_property_value(custom_name_prop_ref,
                                                   custom_name,
                                                   module=prs_studio_module,
                                                   state=state)
                                set_property_readonly(custom_name_prop_ref,
                                                      readonly=True,
                                                      module=prs_studio_module,
                                                      state=state)

            if channel_property.gpio:
                # Hide and unhide the different properties depending on channel selection
                selected_channel = int(selected_channel.replace("CH", ""))
                for i in range(prs_channel_count):
                    set_property_hidden("prs_disabled_chn_{}_pin".format(channel_property.custom_name if channel_property.custom_name else ""),
                                        hidden=True,
                                        state=state)
                    hidden = False if i == selected_channel else True
                    set_property_hidden(channel_property.name.replace("_CHANNEL", str(i)),
                                        hidden=hidden,
                                        state=state)


def aport_scan_update_scan_mask(studio_module, state, show_hide_channels=False):
    scan_mask = 0

    channels_enabled = {
        "0": [False, False],
        "1": [False, False, False, False],
        "2": [False, False, False, False],
        "3": [False, False, False, False],
        "4": [False, False, False, False],
    }

    prefix = state.args['scan_mask'].name.rsplit('_', 1)[0].lower()
    namespace = state.args['scan_mask'].parent.namespace

    for i in range(state.args['scan_mask'].channel_start, state.args['scan_mask'].channel_start + 32):
        pin_id = "{}.{}_INPUT{}.PIN".format(namespace, prefix.upper(), i)
        pin_prop = get_property_reference(pin_id, studio_module)
        set_property_value(pin_prop, 'Disabled', state=state, module=studio_module)

    for input in state.args['scan_mask'].channel_selectors:
        # Figure out which channel range was selected for this input
        aportname, channel_range = get_property_value(input, studio_module).replace('APORT', '').split('CH')
        channel_start, channel_end = channel_range.split('TO')
        # Mark channel range on this APORT as enabled
        channels_enabled[aportname][int(channel_start) // 8] = True

        busname = ExporterModel.aportname_to_busname(state.args['scan_mask'].parent.name, aportname)

        # Get the enable state for each channel in the range selected for this input
        for idx, i in enumerate(range(int(channel_start), int(channel_end) + 1)):
            id = "{}.{}_{}_ch{}.CHECKBOX".format(namespace, prefix, busname, i)
            prop = get_property_reference(id, studio_module)
            val = 1 if get_property_value(prop, studio_module) == 'True' else 0
            scan_mask_shift = (input.start + idx) % 32
            scan_mask = scan_mask + (val << scan_mask_shift)

            if val and prop and '(' in prop.getLabel():
                pin_name = prop.getLabel().split('(')[1].split(')')[0]
                pin_id = "{}.{}_INPUT{}.PIN".format(namespace, prefix.upper(), input.start + idx)
                pin_prop = get_property_reference(pin_id, studio_module)
                set_property_value(pin_prop, pin_name, state=state, module=studio_module)

    set_property_value(state.args['scan_mask'], scan_mask, state=state, module=studio_module)

    for sm in state.args['scan_mask'].other_scan_masks:
        # Get info about selections on other scan masks on the same module
        for input in sm.channel_selectors:
            # Figure out which channel range was selected for this input
            aportname, channel_range = get_property_value(input, studio_module).replace('APORT', '').split('CH')
            channel_start, channel_end = channel_range.split('TO')
            # Mark channel range on this APORT as enabled
            channels_enabled[aportname][int(channel_start) // 8] = True

    # Show/hide all channel enable properties
    for aport, banks in channels_enabled.items():
        busname = ExporterModel.aportname_to_busname(state.args['scan_mask'].parent.name, aport)
        for idx, enable in enumerate(banks):
            for channel in range(idx * 8, (idx + 1) * 8):
                id = "{}.{}_{}_ch{}.CHECKBOX".format(namespace, prefix, busname, channel)
                prop = get_property_reference(id, studio_module)
                if prop:
                    # Channel exists in this family -- show it if the bank is selected and it maps to a pin on this part
                    if enable and "(" in prop.getLabel():
                        set_property_hidden(prop, False, state=state, module=studio_module)
                    else:
                        set_property_hidden(prop, True, state=state, module=studio_module)


def aport_scan_input_changed(studio_module, input_property, state, is_enable):
    aport_scan_update_scan_mask(studio_module, state, True)


def aport_scan_channel_changed(studio_module, channel_property, state):
    aport_scan_update_scan_mask(studio_module, state)


def configure_aport_scan(scan_mask, state):
    assert isinstance(scan_mask, ExporterModel.AportScanMaskProperty)

    args = {
        'scan_mask': scan_mask
    }

    for input in scan_mask.channel_selectors:
        set_change_handler(input, aport_scan_input_changed, True, args)

    namespace = scan_mask.parent.namespace
    prefix = scan_mask.name.rsplit('_', 1)[0].lower()
    id = "{}.{}_.*.CHECKBOX".format(namespace, prefix)
    set_change_handler_regex(scan_mask.parent.name, id, aport_scan_channel_changed, args)


def aport_bonded_input_changed(studio_module, input_property, state):
    bonded_mask = 0

    prefix = state.args['bonded_mask'].name.rsplit('_', 1)[0].lower()
    namespace = state.args['bonded_mask'].parent.namespace

    for num, input in enumerate(state.args['bonded_mask'].input_props):
        val = 1 if get_property_value(input, studio_module) == 'True' else 0

        bonded_mask += val << num

        prop = get_property_reference(input, studio_module)
        pin_id = "{}.{}_INPUT{}.PIN".format(namespace, prefix.upper(), num + state.args['bonded_mask'].channel_start)
        pin_prop = get_property_reference(pin_id, studio_module)
        if val and prop and '(' in prop.getLabel():
            pin_name = prop.getLabel().split('(')[1].split(')')[0]
            set_property_value(pin_prop, pin_name, state=state, module=studio_module)
        else:
            set_property_value(pin_prop, 'Disabled', state=state, module=studio_module)

    set_property_value(state.args['bonded_mask'], bonded_mask, state=state, module=studio_module)


def configure_aport_bonded(bonded_mask, state):
    assert isinstance(bonded_mask, ExporterModel.AportBondedMaskProperty)

    args = {
        'bonded_mask': bonded_mask
    }

    namespace = bonded_mask.parent.namespace
    prefix = bonded_mask.name.rsplit('_', 1)[0].lower()
    id = "{}.{}_.*.CHECKBOX".format(namespace, prefix)
    set_change_handler_regex(bonded_mask.parent.name, id, aport_bonded_input_changed, args)
