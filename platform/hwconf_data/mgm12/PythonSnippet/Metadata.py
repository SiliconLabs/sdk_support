def get_prs_chan_count(family_name=""):
        """
        Returns the number of available PRS channels for the given family
            :param family_name: string representation of the family name
        :return: integer representing the number of available PRS channels
        """

        return 12

def get_prs_chan_with_gpio_count(family_name=""):
        """
        Returns the number of available PRS channels for the given family
            :param family_name: string representation of the family name
        :return: integer representing the number of available PRS channels
        """

        return 12

def get_available_modules_for_family():
    available_modules_for_family = [
        "CMU",
        "PRS",
        "TIMER0",
        "TIMER1",
        "WTIMER0",
        "WTIMER1",
        "USART0",
        "USART1",
        "USART2",
        "USART3",
        "LEUART0",
        "LETIMER0",
        "PCNT0",
        "PCNT1",
        "PCNT2",
        "I2C0",
        "I2C1",
        "ACMP0",
        "ACMP1",
        "LESENSE",
        "GPIO",
        "PTI",
        "MODEM",
        "ADC0",
        "IDAC0",
        "VDAC0",
        "CSEN",
        "LFXO",
    ]
    return available_modules_for_family

def em4_pin_to_loc(pin_name=None):
    pin_loc_map = {
        "PF2": {
            "number": 0,
            "define": "(1 << 0) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PF7": {
            "number": 1,
            "define": "(1 << 1) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PD14": {
            "number": 4,
            "define": "(1 << 4) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PA3": {
            "number": 8,
            "define": "(1 << 8) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PB13": {
            "number": 9,
            "define": "(1 << 9) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PC10": {
            "number": 12,
            "define": "(1 << 12) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
    }
    if pin_name is not None:
        return pin_loc_map[pin_name]
    else:
        return pin_loc_map

class stacked_flash(object):
    
    @staticmethod
    def items():
        props = {
        }
        return props.items()

def allowed_route_conflicts(route):
    allowed_conflicts = {
     "BSP_BTL_BUTTON": ['BSP_LED', 'BSP_BUTTON'],
     "BSP_BUTTON_COUNT": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON0": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON1": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON2": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON3": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON4": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON5": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON6": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_BUTTON7": ['BSP_LED', 'BSP_BTL_BUTTON'],
     "BSP_CSEN_SCAN_MASK0": ['BSP_CSEN_BONDED_INPUT', 'BSP_CSEN_SCAN_INPUT'],
     "BSP_CSEN_SCAN_MASK1": ['BSP_CSEN_BONDED_INPUT', 'BSP_CSEN_SCAN_INPUT'],
     "BSP_CSEN_BONDED_MASK0": ['BSP_CSEN_BONDED_INPUT', 'BSP_CSEN_SCAN_INPUT'],
     "BSP_CSEN_BONDED_MASK1": ['BSP_CSEN_BONDED_INPUT', 'BSP_CSEN_SCAN_INPUT'],
     "BSP_LED_COUNT": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED0": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED1": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED2": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED3": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED4": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED5": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED6": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_LED7": ['BSP_BUTTON', 'BSP_BTL_BUTTON'],
     "BSP_SPIDISPLAY_EXTCOMIN": ['PRS_CH'],
    }

    return allowed_conflicts.get(route, [])