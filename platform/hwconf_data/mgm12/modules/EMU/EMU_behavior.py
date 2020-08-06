from . import ExporterModel
from . import EMU_model
from . import RuntimeModel


class EMU(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(EMU, self).__init__(name, visible=True, core=True)
        self.model = EMU_model