from . import ExporterModel
from . import BULBPWM_model
from . import RuntimeModel


class BULBPWM(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(BULBPWM, self).__init__(name, visible=True)
        self.model = BULBPWM_model