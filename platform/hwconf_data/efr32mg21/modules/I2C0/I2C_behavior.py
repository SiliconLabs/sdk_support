from . import ExporterModel
from . import I2C_model
from . import RuntimeModel


class I2C(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(I2C, self).__init__(name, visible=True, core=True)
        self.model = I2C_model

    def set_runtime_hooks(self):
        pass
