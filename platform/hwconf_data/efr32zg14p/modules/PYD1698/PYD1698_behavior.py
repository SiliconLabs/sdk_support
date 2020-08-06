from . import ExporterModel
from . import PYD1698_model
from . import RuntimeModel


class PYD1698(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(PYD1698, self).__init__(name, visible=True, namespace='PYD1698')
        self.model = PYD1698_model