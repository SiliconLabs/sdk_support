def get_prs_chan_count(family_name=""):
        """
        Returns the number of available PRS channels for the given family
            :param family_name: string representation of the family name
        :return: integer representing the number of available PRS channels
        """

        return 24

def get_prs_chan_with_gpio_count(family_name=""):
        """
        Returns the number of available PRS channels for the given family
            :param family_name: string representation of the family name
        :return: integer representing the number of available PRS channels
        """

        return 24

def get_available_modules_for_family():
    available_modules_for_family = [
        "CMU",
        "LESENSE",
        "EBI",
        "ETH",
        "SDIO",
        "PRS",
        "CAN0",
        "CAN1",
        "TIMER0",
        "TIMER1",
        "TIMER2",
        "TIMER3",
        "TIMER4",
        "TIMER5",
        "TIMER6",
        "WTIMER0",
        "WTIMER1",
        "WTIMER2",
        "WTIMER3",
        "USART0",
        "USART1",
        "USART2",
        "USART3",
        "USART4",
        "USART5",
        "UART0",
        "UART1",
        "QSPI0",
        "LEUART0",
        "LEUART1",
        "LETIMER0",
        "LETIMER1",
        "PCNT0",
        "PCNT1",
        "PCNT2",
        "I2C0",
        "I2C1",
        "I2C2",
        "ACMP0",
        "ACMP1",
        "ACMP2",
        "ACMP3",
        "USB",
        "GPIO",
        "ADC0",
        "ADC1",
        "VDAC0",
        "IDAC0",
        "CSEN",
        "LCD",
        "LFXO",
    ]
    return available_modules_for_family

def em4_pin_to_loc(pin_name=None):
    pin_loc_map = {
        "PA0": {
            "number": 0,
            "define": "(1 << 0) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PA6": {
            "number": 1,
            "define": "(1 << 1) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PC9": {
            "number": 2,
            "define": "(1 << 2) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PF1": {
            "number": 3,
            "define": "(1 << 3) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PF2": {
            "number": 4,
            "define": "(1 << 4) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PE13": {
            "number": 5,
            "define": "(1 << 5) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PC4": {
            "number": 6,
            "define": "(1 << 6) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PB11": {
            "number": 7,
            "define": "(1 << 7) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PF8": {
            "number": 8,
            "define": "(1 << 8) << _GPIO_EM4WUEN_EM4WUEN_SHIFT",
        },
        "PE10": {
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
            "BSP_EXTFLASH_MISO": ('PC7', '11'),
            "BSP_EXTFLASH_MOSI": ('PF6', '30'),
            "BSP_EXTFLASH_CLK": ('PC9', '12'),
            "BSP_EXTFLASH_CS": ('PC6', None),
            "BSP_EXTFLASH_WP": ('PF7', None),
            "BSP_EXTFLASH_HOLD": ('PC8', None),
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