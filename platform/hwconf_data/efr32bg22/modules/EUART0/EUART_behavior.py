from . import ExporterModel
from . import EUART_model
from . import RuntimeModel


class EUART(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(EUART, self).__init__(name, visible=True, core=True)
        self.model = EUART_model

    def set_runtime_hooks(self):
        pass
