from . import ExporterModel
from . import EXTFLASH_model
from . import RuntimeModel
from . import halconfig_dependency


class EXTFLASH(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(EXTFLASH, self).__init__(name, visible=True)
        self.model = EXTFLASH_model

    def set_runtime_hooks(self):
        RuntimeModel.set_change_handler(self.get_property("BSP_EXTFLASH_INTERNAL"), EXTFLASH.flash_selection_changed, args=self)

    @staticmethod
    def flash_selection_changed(studio_mod, property, state):
        runtime_mod = state.args
        selection = RuntimeModel.get_property_value(property, studio_mod)

        if selection == '1':
            # Trying to select internal flash, are we allowed to?
            if runtime_mod.family.flash_type != halconfig_dependency.FlashType.STACKED_FLASH:
                RuntimeModel.set_property_value(property,
                                                RuntimeModel.get_property_values(property, studio_mod)[0],
                                                module=studio_mod,
                                                state=state)
                return
            # Grey out and reset the other options since we'll be taking over
            RuntimeModel.set_property_value('BSP_EXTFLASH_HOLD', 'Disabled', module=studio_mod, state=state)
            RuntimeModel.set_property_value('BSP_EXTFLASH_CS', 'Disabled', module=studio_mod, state=state)
            RuntimeModel.set_property_value('BSP_EXTFLASH_WP', 'Disabled', module=studio_mod, state=state)
            RuntimeModel.set_property_value('BSP_EXTFLASH_USART',
                                            RuntimeModel.get_property_values('BSP_EXTFLASH_USART', module=studio_mod)[2],
                                            module=studio_mod,
                                            state=state)

            RuntimeModel.set_property_readonly('BSP_EXTFLASH_HOLD', True, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_CS', True, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_WP', True, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_USART', True, module=studio_mod, state=state)
        else:
            # (Re-)enable properties
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_HOLD', False, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_CS', False, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_WP', False, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly('BSP_EXTFLASH_USART', False, module=studio_mod, state=state)

    def generate_define_override(self, studio_mod):
        from . import Metadata
        # if actual external flash, generate as usual
        if RuntimeModel.get_property_value(self.get_property('BSP_EXTFLASH_INTERNAL'), module=studio_mod, check_pending=False) == '0':
            return []
        # if stacked flash, generate from metadata
        proplist = []
        for define, value in Metadata.stacked_flash.items():
            pin, loc = value
            if loc is not None:
                proplist.append({"region": studio_mod.name,
                                 "label": define,
                                 "pin_name": pin,
                                 "loc": loc,
                                 "is_array": False,
                                 "is_str_prop": False})
            else:
                proplist.append({"region": studio_mod.name,
                                 "label": define,
                                 "pin_name": pin,
                                 "is_array": False,
                                 "is_str_prop": False})
        return proplist
