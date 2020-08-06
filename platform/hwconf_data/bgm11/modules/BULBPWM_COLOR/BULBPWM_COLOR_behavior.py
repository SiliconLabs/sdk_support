from . import ExporterModel
from . import BULBPWM_COLOR_model
from . import RuntimeModel


class BULBPWM_COLOR(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(BULBPWM_COLOR, self).__init__(name, visible=True)
        self.model = BULBPWM_COLOR_model