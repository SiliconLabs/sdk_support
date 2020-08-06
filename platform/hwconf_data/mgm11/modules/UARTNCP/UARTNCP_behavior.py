from . import ExporterModel
from . import UARTNCP_model
from . import RuntimeModel


class UARTNCP(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(UARTNCP, self).__init__(name, visible=True)
        self.model = UARTNCP_model