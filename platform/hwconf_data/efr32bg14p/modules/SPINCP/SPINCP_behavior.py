from . import ExporterModel
from . import SPINCP_model
from . import RuntimeModel


class SPINCP(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(SPINCP, self).__init__(name, visible=True)
        self.model = SPINCP_model