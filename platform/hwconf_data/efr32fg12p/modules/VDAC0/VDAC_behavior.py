from . import ExporterModel
from . import VDAC_model
from . import RuntimeModel


class VDAC(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(VDAC, self).__init__(name, visible=True, core=True)
        self.model = VDAC_model

    def set_runtime_hooks(self):
        pass