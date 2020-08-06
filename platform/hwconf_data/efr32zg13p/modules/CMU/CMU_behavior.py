from . import ExporterModel
from . import CMU_model
from . import RuntimeModel


class CMU(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(CMU, self).__init__(name, visible=True, core=True)
        self.model = CMU_model

    def set_runtime_hooks(self):

        ctune_token = self.get_property("BSP_CLK_HFXO_CTUNE_TOKEN")
        if ctune_token:
            RuntimeModel.set_change_handler(ctune_token, CMU.ctune_use_token)

        hfclk_selection = self.get_property("HAL_CLK_HFCLK_SOURCE")
        pll_config = self.get_property("HAL_CLK_PLL_CONFIGURATION")
        if pll_config:
            RuntimeModel.set_change_handler(hfclk_selection, CMU.hfclk_changed)

    @staticmethod
    def ctune_use_token(studio_module, property, state):
        hide_ctune_input = RuntimeModel.get_property_value(property, module=studio_module) == '1'
        RuntimeModel.set_property_hidden("BSP_CLK_HFXO_CTUNE", hide_ctune_input, module=studio_module, state=state)

    @staticmethod
    def hfclk_changed(studio_module, property, state):
        clk_src = RuntimeModel.get_property_value(property, module=studio_module)

        if clk_src == "HAL_CLK_HFCLK_SOURCE_HFRCODPLL":
            RuntimeModel.set_property_readonly("HAL_CLK_PLL_CONFIGURATION", False, module=studio_module, state=state)
        else:
            RuntimeModel.set_property_readonly("HAL_CLK_PLL_CONFIGURATION", True, module=studio_module, state=state)
