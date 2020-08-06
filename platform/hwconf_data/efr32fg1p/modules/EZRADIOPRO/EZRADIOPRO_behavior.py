from . import ExporterModel
from . import EZRADIOPRO_model
from . import RuntimeModel


class EZRADIOPRO(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(EZRADIOPRO, self).__init__(name, visible=True)
        self.model = EZRADIOPRO_model