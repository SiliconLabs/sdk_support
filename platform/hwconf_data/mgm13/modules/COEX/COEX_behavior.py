from . import ExporterModel
from . import COEX_model
from . import RuntimeModel


class COEX(ExporterModel.Module):
    def __init__(self, name=None):
        if not name:
            name = self.__class__.__name__
        super(COEX, self).__init__(name, visible=True)
        self.model = COEX_model

    def post_load(self):
        # Default assert levels to hidden because pins default to disabled
        self.get_property("BSP_COEX_RHO_ASSERT_LEVEL").set_readonly(True)
        self.get_property("BSP_COEX_GNT_ASSERT_LEVEL").set_readonly(True)
        self.get_property("BSP_COEX_PRI_ASSERT_LEVEL").set_readonly(True)
        self.get_property("BSP_COEX_REQ_ASSERT_LEVEL").set_readonly(True)
        self.get_property("HAL_COEX_REQ_SHARED").set_readonly(True)
        self.get_property("HAL_COEX_REQ_BACKOFF").set_readonly(True)
        self.get_property("HAL_COEX_REQ_WINDOW").set_readonly(True)
        self.get_property("HAL_COEX_RETRYRX_ENABLE").set_readonly(True)
        self.get_property("HAL_COEX_RETRYRX_TIMEOUT").set_readonly(True)
        self.get_property("HAL_COEX_RETRYRX_HIPRI").set_readonly(True)
        self.get_property("HAL_COEX_PRI_SHARED").set_readonly(True)
        self.get_property("HAL_COEX_TX_HIPRI").set_readonly(True)
        self.get_property("HAL_COEX_RX_HIPRI").set_readonly(True)
        self.get_property("HAL_COEX_TX_ABORT").set_readonly(True)
        self.get_property("HAL_COEX_ACKHOLDOFF").set_readonly(True)
        self.get_property("BSP_COEX_RX_ACTIVE_ASSERT_LEVEL").set_readonly(True)
        self.get_property("BSP_COEX_PHY_SELECT_ASSERT_LEVEL").set_readonly(True)
        self.get_property("HAL_COEX_DEFAULT_PHY_SELECT_TIMEOUT").set_readonly(True)

    def set_runtime_hooks(self):
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_RHO"), COEX.pin_changed)
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_GNT"), COEX.pin_changed)
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_PRI"), COEX.pri_changed)
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_REQ"), COEX.req_changed)
        RuntimeModel.set_change_handler(self.get_property("HAL_COEX_REQ_SHARED"), COEX.reqshared_changed)
        RuntimeModel.set_change_handler(self.get_property("HAL_COEX_RETRYRX_ENABLE"), COEX.retryrx_changed)
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_RX_ACTIVE_CHANNEL"), COEX.channel_changed)
        RuntimeModel.set_change_handler(self.get_property("BSP_COEX_PHY_SELECT"), COEX.pin_changed)

    @staticmethod
    def channel_changed(studio_mod, property, state):
        channel = RuntimeModel.get_property_value(property, module=studio_mod)
        if "Disabled" in channel:
            readonly = True
        else:
            readonly = False
        if "BSP_COEX_RX_ACTIVE" in str(property.name):
            RuntimeModel.set_property_readonly("BSP_COEX_RX_ACTIVE_ASSERT_LEVEL", readonly, module=studio_mod, state=state)

    @staticmethod
    def setREQ_readonly(studio_mod, readonly, state):
        # assert level, req_shared, req_window, and retry enable are all directly dependent on REQ
        RuntimeModel.set_property_readonly("BSP_COEX_REQ_ASSERT_LEVEL", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_REQ_SHARED", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_REQ_WINDOW", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_ENABLE", readonly, module=studio_mod, state=state)
        # Also allow mass disable of retryrx_hipri, req_backoff, and retryrx_timeout which are indirectly dependent
        if readonly is True:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", readonly, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly("HAL_COEX_REQ_BACKOFF", readonly, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_TIMEOUT", readonly, module=studio_mod, state=state)

        # re-enable REQ_BACKOFF if REQ_SHARED is enabled
        shared = RuntimeModel.get_property_value(RuntimeModel.get_property_model("HAL_COEX_REQ_SHARED", studio_mod), module=studio_mod)
        if shared and readonly is False:
            RuntimeModel.set_property_readonly("HAL_COEX_REQ_BACKOFF", readonly, module=studio_mod, state=state)

        # re-enable RETRY_TIMEOUT if RETRYRX is enabled
        retryrx = RuntimeModel.get_property_value(RuntimeModel.get_property_model("HAL_COEX_RETRYRX_ENABLE", studio_mod), module=studio_mod)
        if retryrx and readonly is False:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_TIMEOUT", readonly, module=studio_mod, state=state)

        # re-enable RETRYRX_HIPRI if PRI and RETRYRX are both enabled
        pri = RuntimeModel.get_property_value(RuntimeModel.get_property_model("BSP_COEX_PRI", studio_mod), module=studio_mod)
        if "Disabled" not in pri and retryrx == "1" and readonly is False:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", readonly, module=studio_mod, state=state)

    @staticmethod
    def setPRI_readonly(studio_mod, readonly, state):
        # assert level, pri_shared, tx_hipri, rx_hipri are all directly dependent on PRI
        RuntimeModel.set_property_readonly("BSP_COEX_PRI_ASSERT_LEVEL", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_PRI_SHARED", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_TX_HIPRI", readonly, module=studio_mod, state=state)
        RuntimeModel.set_property_readonly("HAL_COEX_RX_HIPRI", readonly, module=studio_mod, state=state)

        # re-enable RETRYRX_HIPRI if RETRYRX and REQ are enabled
        retryrx = RuntimeModel.get_property_value(RuntimeModel.get_property_model("HAL_COEX_RETRYRX_ENABLE", studio_mod), module=studio_mod)
        req = RuntimeModel.get_property_value(RuntimeModel.get_property_model("BSP_COEX_REQ", studio_mod), module=studio_mod)
        if readonly is True:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", readonly, module=studio_mod, state=state)
        elif retryrx == "1" and "Disabled" not in req:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", readonly, module=studio_mod, state=state)

    @staticmethod
    def pin_changed(studio_mod, property, state):
        # Generic assert level disable/enable used for RHO and GNT
        pin = RuntimeModel.get_property_value(property, module=studio_mod)
        if "Disabled" in pin:
            readonly = True
        else:
            readonly = False
        RuntimeModel.set_property_readonly(str(property.name)+"_ASSERT_LEVEL", readonly, module=studio_mod, state=state)
        if "BSP_COEX_GNT" in str(property.name):
            RuntimeModel.set_property_readonly("HAL_COEX_TX_ABORT", readonly, module=studio_mod, state=state)
            RuntimeModel.set_property_readonly("HAL_COEX_ACKHOLDOFF", readonly, module=studio_mod, state=state)
        if "BSP_COEX_PHY_SELECT" in str(property.name):
            RuntimeModel.set_property_readonly("HAL_COEX_DEFAULT_PHY_SELECT_TIMEOUT", readonly, module=studio_mod, state=state)

    @staticmethod
    def pri_changed(studio_mod, property, state):
        pin = RuntimeModel.get_property_value(property, module=studio_mod)
        COEX.setPRI_readonly(studio_mod, "Disabled" in pin, state)

    @staticmethod
    def req_changed(studio_mod, property, state):
        pin = RuntimeModel.get_property_value(property, module=studio_mod)
        COEX.setREQ_readonly(studio_mod, "Disabled" in pin, state)

    @staticmethod
    def reqshared_changed(studio_mod, property, state):
        reqshared = RuntimeModel.get_property_value(property, module=studio_mod)
        req = RuntimeModel.get_property_value(RuntimeModel.get_property_model("BSP_COEX_REQ", studio_mod), module=studio_mod)
        if reqshared == "1" and "Disabled" not in req:
            RuntimeModel.set_property_readonly("HAL_COEX_REQ_BACKOFF", False, module=studio_mod, state=state)
        else:
            RuntimeModel.set_property_readonly("HAL_COEX_REQ_BACKOFF", True, module=studio_mod, state=state)

    @staticmethod
    def retryrx_changed(studio_mod, property, state):
        retryrx = RuntimeModel.get_property_value(property, module=studio_mod)
        req = RuntimeModel.get_property_value(RuntimeModel.get_property_model("BSP_COEX_REQ", studio_mod), module=studio_mod)
        if retryrx == "1" and "Disabled" not in req:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_TIMEOUT", False, module=studio_mod, state=state)
        else:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_TIMEOUT", True, module=studio_mod, state=state)
        # check if BSP_COEX_PRI is enabled
        pri = RuntimeModel.get_property_value(RuntimeModel.get_property_model("BSP_COEX_PRI", studio_mod), module=studio_mod)
        if "Disabled" not in pri and retryrx == "1" and "Disabled" not in req:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", False, module=studio_mod, state=state)
        else:
            RuntimeModel.set_property_readonly("HAL_COEX_RETRYRX_HIPRI", True, module=studio_mod, state=state)
