from . import ExporterModel
from . import BATTERYMON_model
from . import RuntimeModel


class BATTERYMON(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(BATTERYMON, self).__init__(name, visible=True)
        self.model = BATTERYMON_model
        
    def set_runtime_hooks(self):
        pass
