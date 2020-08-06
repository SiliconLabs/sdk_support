from . import ExporterModel
from . import VCOM_model
from . import RuntimeModel


class VCOM(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(VCOM, self).__init__(name, visible=True)
        self.model = VCOM_model

    def set_runtime_hooks(self):
        pass