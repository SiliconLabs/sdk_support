from . import ExporterModel
from . import SERIAL_model
from . import RuntimeModel


class SERIAL(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(SERIAL, self).__init__(name, visible=True)
        self.model = SERIAL_model