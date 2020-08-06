from . import ExporterModel
from . import LEUART_model
from . import RuntimeModel


class LEUART(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(LEUART, self).__init__(name, visible=True, core=True)
        self.model = LEUART_model

    def set_runtime_hooks(self):
        pass
