from . import ExporterModel
from . import RuntimeModel

PRS_CHANNEL_COUNT = 12
PRS_CHANNEL_GPIO_COUNT = 12
PRS_SOURCE_TO_SIGNALS_MAP = {
    'PRS': ['PRS_CH0', 'PRS_CH1', 'PRS_CH2', 'PRS_CH3', 'PRS_CH4', 'PRS_CH5', 'PRS_CH6', 'PRS_CH7', 'PRS_CH8', 'PRS_CH9', 'PRS_CH10', 'PRS_CH11', ],
    'RTCC': ['RTCC_CCV0', 'RTCC_CCV1', 'RTCC_CCV2', ],
    'GPIO': ['GPIO_PIN0', 'GPIO_PIN1', 'GPIO_PIN2', 'GPIO_PIN3', 'GPIO_PIN4', 'GPIO_PIN5', 'GPIO_PIN6', 'GPIO_PIN7', 'GPIO_PIN8', 'GPIO_PIN9', 'GPIO_PIN10', 'GPIO_PIN11', 'GPIO_PIN12', 'GPIO_PIN13', 'GPIO_PIN14', 'GPIO_PIN15', ],
    'LETIMER0': ['LETIMER0_CH0', 'LETIMER0_CH1', ],
    'PCNT0': ['PCNT0_TCC', 'PCNT0_UFOF', 'PCNT0_DIR', ],
    'CMU': ['CMU_CLKOUT0', 'CMU_CLKOUT1', ],
    'RFSENSE': ['RFSENSE_WU', ],
    'CRYOTIMER': ['CRYOTIMER_PERIOD', ],
    'USART0': ['USART0_IRTX', 'USART0_TXC', 'USART0_RXDATAV', 'USART0_RTS', 'USART0_TX', 'USART0_CS', ],
    'USART1': ['USART1_TXC', 'USART1_RXDATAV', 'USART1_RTS', 'USART1_TX', 'USART1_CS', ],
    'TIMER0': ['TIMER0_UF', 'TIMER0_OF', 'TIMER0_CC0', 'TIMER0_CC1', 'TIMER0_CC2', ],
    'TIMER1': ['TIMER1_UF', 'TIMER1_OF', 'TIMER1_CC0', 'TIMER1_CC1', 'TIMER1_CC2', 'TIMER1_CC3', ],
    'WTIMER0': ['WTIMER0_UF', 'WTIMER0_OF', 'WTIMER0_CC0', 'WTIMER0_CC1', 'WTIMER0_CC2', ],
    'RAC': ['RAC_ACTIVE', 'RAC_TX', 'RAC_RX', 'RAC_LNAEN', 'RAC_PAEN', ],
    'PROTIMER': ['PROTIMER_LBTS', 'PROTIMER_LBTR', 'PROTIMER_LBTF', ],
    'MODEM': ['MODEM_FRAMEDET', 'MODEM_PREDET', 'MODEM_TIMDET', 'MODEM_FRAMESENT', 'MODEM_SYNCSENT', 'MODEM_PRESENT', 'MODEM_ANT0', 'MODEM_ANT1', ],
}


class PRS(ExporterModel.Module):
    def __init__(self, name="PRS"):
        if not name:
            name = self.__class__.__name__
        super(PRS, self).__init__(name, visible=True)

    def load_halconfig_model(self, available_module_names_list, family):
        for i in range(PRS_CHANNEL_COUNT):
            # creating custom name object for each channel
            custom_name_prop = ExporterModel.StringProperty(name="custom_name_CH{}".format(i), description="Custom name", visible=True)
            custom_name_prop.subcategory = "CH{} properties".format(i)
            self.add_property(custom_name_prop)
            # creating property object for possible sources
            source_prop_obj = ExporterModel.EnumProperty(name="BSP_PRS_CH{}_SOURCE".format(i), description="Source", visible=True)
            source_prop_obj.add_enum("Disabled")
            source_prop_obj.subcategory = "CH{} properties".format(i)
            self.add_property(source_prop_obj)

            # Adding values to the drop downs
            for source, signals in PRS_SOURCE_TO_SIGNALS_MAP.items():
                source_prop_obj.add_enum(source)

                signal_prop_obj = ExporterModel.EnumProperty(name="BSP_PRS_CH{}_SIGNAL_{}".format(i, source), description="Signal", visible=False)
                for signal in signals:
                    signal_prop_obj.add_enum(signal)
                signal_prop_obj.subcategory = "CH{} properties".format(i)
                self.add_property(signal_prop_obj)

            # Adding readonly properties, to be be displayed when selected source option is "Disabled"
            disabled_signal_prop_obj = ExporterModel.StringProperty(name="bsp_prs_ch{0}_signal_disabled".format(i), description="Signal", visible=True, readonly=True)
            disabled_signal_prop_obj.subcategory = "CH{} properties".format(i)
            self.add_property(disabled_signal_prop_obj)
            if i < PRS_CHANNEL_GPIO_COUNT:
                pin_prop = ExporterModel.PinProperty(name="BSP_PRS_CH{}".format(i),
                                                     description="Output pin".format(i),
                                                     visible=True)

                pin_prop.set_reference("PRS", "CH{}".format(i))

                pin_prop.subcategory = "CH{} properties".format(i)
                self.add_property(pin_prop)

    def set_runtime_hooks(self):
        for i in range(PRS_CHANNEL_COUNT):
            RuntimeModel.set_change_handler(self.get_property("BSP_PRS_CH{}_SOURCE".format(i)), PRS.mode_changed)

    @staticmethod
    def mode_changed(studio_mod, property, state):
        new_source_name = RuntimeModel.get_property_define(property, studio_mod)
        print("PRS source on {} changed to {}".format(property.name, new_source_name))

        # Getting channel number
        chan = property.name.split("CH")[1]
        for i, char in enumerate(chan):
            if not char.isdigit():
                chan = chan[:i]
                break

        # Hiding and showing properties depending on source choice
        for mod_prop in [prop for prop in property.parent.get_properties() if prop.subcategory == property.subcategory]:
            mod_prop_name = mod_prop.name.upper()
            if "CH" + chan + "_SIGNAL" in mod_prop_name:
                if mod_prop_name.endswith("_" + new_source_name.upper()):
                    RuntimeModel.set_property_hidden(mod_prop, False, state=state)
                else:
                    RuntimeModel.set_property_hidden(mod_prop, True, state=state)
