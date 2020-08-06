from . import ExporterModel
from . import GPIO_model
from . import RuntimeModel


class GPIO(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(GPIO, self).__init__(name, visible=True, core=True)
        self.model = GPIO_model

    def set_runtime_hooks(self):
        pass
