from . import ExporterModel
from . import UART_model
from . import RuntimeModel


class UART(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(UART, self).__init__(name, visible=True, core=True)
        self.model = UART_model

    def set_runtime_hooks(self):
        pass
