from . import ExporterModel
from . import DCDC_model
from . import RuntimeModel


class DCDC(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(DCDC, self).__init__(name, visible=True, core=True)
        self.model = DCDC_model

    def set_runtime_hooks(self):
        pass
