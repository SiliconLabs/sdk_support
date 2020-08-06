from . import ExporterModel
from . import VUART_model
from . import RuntimeModel


class VUART(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(VUART, self).__init__(name, visible=True)
        self.model = VUART_model
