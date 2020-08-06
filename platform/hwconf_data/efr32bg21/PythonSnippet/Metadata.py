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
        "ACMP0",
        "ACMP1",
        "IADC0",
        "CMU",
        "I2C0",
        "LETIMER0",
        "MODEM",
        "PRS",
        "TIMER0",
        "TIMER1",
        "TIMER2",
        "USART0",
        "USART1",
        "PTI",
        "I2C1",
        "TIMER3",
        "USART2",
        "GPIO",
        "LFXO",
    ]
    return available_modules_for_family

def em4_pin_to_loc(pin_name=None):
    pin_loc_map = {
        "PA05": {
            "number": 0,
            "define": "(1 << 0) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PB01": {
            "number": 3,
            "define": "(1 << 3) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PC00": {
            "number": 6,
            "define": "(1 << 6) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PC05": {
            "number": 7,
            "define": "(1 << 7) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PD02": {
            "number": 9,
            "define": "(1 << 9) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
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