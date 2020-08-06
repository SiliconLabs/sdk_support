from . import ExporterModel
from . import I2CSENSOR_model
from . import RuntimeModel


class I2CSENSOR(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(I2CSENSOR, self).__init__(name, visible=True)
        self.model = I2CSENSOR_model