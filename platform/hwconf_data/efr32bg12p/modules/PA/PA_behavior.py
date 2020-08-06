from . import ExporterModel
from . import PA_model
from . import RuntimeModel


class PA(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(PA, self).__init__(name, visible=True, core=True)
        self.model = PA_model