from . import ExporterModel
from . import IDAC_model
from . import RuntimeModel


class IDAC(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(IDAC, self).__init__(name, visible=True, core=True)
        self.model = IDAC_model

    def set_runtime_hooks(self):
        pass