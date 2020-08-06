from . import ExporterModel
from . import BUTTON_model
from . import RuntimeModel


class BUTTON(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(BUTTON, self).__init__(name, visible=True)
        self.model = BUTTON_model

    def set_runtime_hooks(self):
        RuntimeModel.set_change_handler(self.get_property("BSP_BUTTON_COUNT"),
                                        BUTTON.count_changed)

    @staticmethod
    def count_changed(studio_module, model_property, state):
        new_count = RuntimeModel.get_property_value(model_property, module=studio_module)

        init_string = ""
        for i in range(0, model_property.max):
            hidden = True if i >= int(new_count) else False
            RuntimeModel.set_property_hidden("BSP_BUTTON{}".format(str(i)), hidden, module=studio_module, state=state)
            if not hidden:
                init_string += ("{{ BSP_BUTTON{0}_PORT, BSP_BUTTON{0}_PIN }}, ".format(str(i)))
        if init_string:
            # Strip last comma space from value
            init_string = init_string[:-2]

        RuntimeModel.set_property_value("BSP_BUTTON_INIT", init_string, module=studio_module, state=state)
