from . import ExporterModel
from . import MODEM_model
from . import RuntimeModel


class MODEM(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(MODEM, self).__init__(name, visible=True, core=True)
        self.model = MODEM_model

    def set_runtime_hooks(self):
        pass