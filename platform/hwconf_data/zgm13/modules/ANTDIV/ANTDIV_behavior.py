from . import ExporterModel
from . import ANTDIV_model
from . import RuntimeModel


class ANTDIV(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(ANTDIV, self).__init__(name, visible=True)
        self.model = ANTDIV_model

    def set_runtime_hooks(self):
        rx_selection = self.get_property("HAL_ANTDIV_RX_MODE")
        RuntimeModel.set_change_handler(rx_selection, ANTDIV.modem_or_antdiv_sel_nsel_visible)


    @staticmethod
    def modem_or_antdiv_sel_nsel_visible(studio_module, property, state):
        rx_mode = RuntimeModel.get_property_value(property, module=studio_module)
        modem_sel_nsel = RuntimeModel.get_property_reference("BSP_ANTDIV", module=studio_module)
        antdiv_sel = RuntimeModel.get_property_reference("BSP_ANTDIV_SEL", module=studio_module)
        antdiv_nsel = RuntimeModel.get_property_reference("BSP_ANTDIV_NSEL", module=studio_module)
        if rx_mode == 'HAL_ANTENNA_MODE_DISABLED':
            RuntimeModel.set_property_hidden(modem_sel_nsel, True, state, studio_module)
            RuntimeModel.set_property_hidden(antdiv_sel, False, state, studio_module)
            RuntimeModel.set_property_hidden(antdiv_nsel, False, state, studio_module)
        else:
            RuntimeModel.set_property_hidden(modem_sel_nsel, False, state, studio_module)
            RuntimeModel.set_property_hidden(antdiv_sel, True, state, studio_module)
            RuntimeModel.set_property_hidden(antdiv_nsel, True, state, studio_module)
