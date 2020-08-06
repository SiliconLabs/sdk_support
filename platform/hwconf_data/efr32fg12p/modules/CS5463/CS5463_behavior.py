from . import ExporterModel
from . import CS5463_model
from . import RuntimeModel


class CS5463(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(CS5463, self).__init__(name, visible=True, namespace='CS5463')
        self.model = CS5463_model