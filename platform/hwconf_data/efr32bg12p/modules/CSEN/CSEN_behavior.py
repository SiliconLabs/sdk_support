from . import ExporterModel
from . import CSEN_model
from . import RuntimeModel


class CSEN(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(CSEN, self).__init__(name, visible=True, core=True)
        self.model = CSEN_model

    def set_runtime_hooks(self):
        pass