from . import ExporterModel
from . import RuntimeModel

PRS_CHANNEL_COUNT = 16
PRS_CHANNEL_GPIO_COUNT = 16
PRS_SOURCE_TO_SIGNALS_MAP = {
    'PRS': ['PRS_CH0', 'PRS_CH1', 'PRS_CH2', 'PRS_CH3', 'PRS_CH4', 'PRS_CH5', 'PRS_CH6', 'PRS_CH7', 'PRS_CH8', 'PRS_CH9', 'PRS_CH10', 'PRS_CH11', 'PRS_CH12', 'PRS_CH13', 'PRS_CH14', 'PRS_CH15', ],
    'ACMP0': ['ACMP0_OUT', ],
    'ACMP1': ['ACMP1_OUT', ],
    'ADC0': ['ADC0_SINGLE', 'ADC0_SCAN', ],
    'RTC': ['RTC_OF', 'RTC_COMP0', 'RTC_COMP1', 'RTC_COMP2', 'RTC_COMP3', 'RTC_COMP4', 'RTC_COMP5', ],
    'RTCC': ['RTCC_CCV0', 'RTCC_CCV1', 'RTCC_CCV2', ],
    'GPIO': ['GPIO_PIN0', 'GPIO_PIN1', 'GPIO_PIN2', 'GPIO_PIN3', 'GPIO_PIN4', 'GPIO_PIN5', 'GPIO_PIN6', 'GPIO_PIN7', 'GPIO_PIN8', 'GPIO_PIN9', 'GPIO_PIN10', 'GPIO_PIN11', 'GPIO_PIN12', 'GPIO_PIN13', 'GPIO_PIN14', 'GPIO_PIN15', ],
    'LETIMER0': ['LETIMER0_CH0', 'LETIMER0_CH1', ],
    'LETIMER1': ['LETIMER1_CH0', 'LETIMER1_CH1', ],
    'PCNT0': ['PCNT0_TCC', 'PCNT0_UFOF', 'PCNT0_DIR', ],
    'PCNT1': ['PCNT1_TCC', 'PCNT1_UFOF', 'PCNT1_DIR', ],
    'PCNT2': ['PCNT2_TCC', 'PCNT2_UFOF', 'PCNT2_DIR', ],
    'CRYOTIMER': ['CRYOTIMER_PERIOD', ],
    'CMU': ['CMU_CLKOUT0', 'CMU_CLKOUT1', 'CMU_CLKOUT2', ],
    'VDAC0': ['VDAC0_CH0', 'VDAC0_CH1', 'VDAC0_OPA0', 'VDAC0_OPA1', 'VDAC0_OPA2', 'VDAC0_OPA3', ],
    'LESENSE': ['LESENSE_SCANRES0', 'LESENSE_SCANRES1', 'LESENSE_SCANRES2', 'LESENSE_SCANRES3', 'LESENSE_SCANRES4', 'LESENSE_SCANRES5', 'LESENSE_SCANRES6', 'LESENSE_SCANRES7', 'LESENSE_SCANRES8', 'LESENSE_SCANRES9', 'LESENSE_SCANRES10', 'LESENSE_SCANRES11', 'LESENSE_SCANRES12', 'LESENSE_SCANRES13', 'LESENSE_SCANRES14', 'LESENSE_SCANRES15', 'LESENSE_DEC0', 'LESENSE_DEC1', 'LESENSE_DEC2', 'LESENSE_DECCMP', 'LESENSE_MEASACT', ],
    'ACMP2': ['ACMP2_OUT', ],
    'ADC1': ['ADC1_SINGLE', 'ADC1_SCAN', ],
    'USART0': ['USART0_IRTX', 'USART0_TXC', 'USART0_RXDATAV', 'USART0_RTS', 'USART0_TX', 'USART0_CS', ],
    'USART1': ['USART1_TXC', 'USART1_RXDATAV', 'USART1_RTS', 'USART1_TX', 'USART1_CS', ],
    'USART2': ['USART2_IRTX', 'USART2_TXC', 'USART2_RXDATAV', 'USART2_RTS', 'USART2_TX', 'USART2_CS', ],
    'USART3': ['USART3_TXC', 'USART3_RXDATAV', 'USART3_RTS', 'USART3_TX', 'USART3_CS', ],
    'USART4': ['USART4_TXC', 'USART4_RXDATAV', 'USART4_RTS', 'USART4_TX', 'USART4_CS', ],
    'UART0': ['UART0_TXC', 'UART0_RXDATAV', 'UART0_RTS', 'UART0_TX', 'UART0_CS', ],
    'UART1': ['UART1_TXC', 'UART1_RXDATAV', 'UART1_RTS', 'UART1_TX', 'UART1_CS', ],
    'TIMER0': ['TIMER0_UF', 'TIMER0_OF', 'TIMER0_CC0', 'TIMER0_CC1', 'TIMER0_CC2', ],
    'TIMER1': ['TIMER1_UF', 'TIMER1_OF', 'TIMER1_CC0', 'TIMER1_CC1', 'TIMER1_CC2', 'TIMER1_CC3', ],
    'TIMER2': ['TIMER2_UF', 'TIMER2_OF', 'TIMER2_CC0', 'TIMER2_CC1', 'TIMER2_CC2', ],
    'USB': ['USB_SOF', 'USB_SOFSR', ],
    'TIMER3': ['TIMER3_UF', 'TIMER3_OF', 'TIMER3_CC0', 'TIMER3_CC1', 'TIMER3_CC2', ],
    'WTIMER0': ['WTIMER0_UF', 'WTIMER0_OF', 'WTIMER0_CC0', 'WTIMER0_CC1', 'WTIMER0_CC2', ],
    'WTIMER1': ['WTIMER1_UF', 'WTIMER1_OF', 'WTIMER1_CC0', 'WTIMER1_CC1', 'WTIMER1_CC2', 'WTIMER1_CC3', ],
    'PDM': ['PDM_DSRPULSE', ],
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
