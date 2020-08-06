from . import ExporterModel
from . import BTL_BUTTON_model
from . import RuntimeModel


class BTL_BUTTON(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(BTL_BUTTON, self).__init__(name, visible=True)
        self.model = BTL_BUTTON_model