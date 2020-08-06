#!/usr/bin/env python3

import os
import glob
import time
import Studio.halConfig as hal
import efm32gg.PythonSnippet.RuntimeModel as RuntimeModel
import efm32gg.PythonSnippet.ExporterModel as ExporterModel
import efm32gg.PythonSnippet.Metadata as Metadata
import efm32gg.modules.PIN.PIN_Snippets as PIN_Snippets
import efm32gg.modules.PORTIO.PORTIO_Snippets as PORTIO_Snippets
import efm32gg.halconfig.halconfig_dependency as dep

import efm32gg.modules.BTL_BUTTON.BTL_BUTTON_behavior as BTL_BUTTON_behavior
import efm32gg.modules.BUTTON.BUTTON_behavior as BUTTON_behavior
import efm32gg.modules.CMU.CMU_behavior as CMU_behavior
import efm32gg.modules.EMU.EMU_behavior as EMU_behavior
import efm32gg.modules.EXTFLASH.EXTFLASH_behavior as EXTFLASH_behavior
import efm32gg.modules.GPIO.GPIO_behavior as GPIO_behavior
import efm32gg.modules.I2C0.I2C_behavior as I2C_behavior
import efm32gg.modules.I2C1.I2C_behavior as I2C_behavior
import efm32gg.modules.I2CSENSOR.I2CSENSOR_behavior as I2CSENSOR_behavior
import efm32gg.modules.IOEXP.IOEXP_behavior as IOEXP_behavior
import efm32gg.modules.LED.LED_behavior as LED_behavior
import efm32gg.modules.LEUART0.LEUART_behavior as LEUART_behavior
import efm32gg.modules.LEUART1.LEUART_behavior as LEUART_behavior
import efm32gg.modules.PRS.PRS_behavior as PRS_behavior
import efm32gg.modules.SERIAL.SERIAL_behavior as SERIAL_behavior
import efm32gg.modules.SPIDISPLAY.SPIDISPLAY_behavior as SPIDISPLAY_behavior
import efm32gg.modules.SPINCP.SPINCP_behavior as SPINCP_behavior
import efm32gg.modules.TIMER0.TIMER_behavior as TIMER_behavior
import efm32gg.modules.TIMER1.TIMER_behavior as TIMER_behavior
import efm32gg.modules.TIMER2.TIMER_behavior as TIMER_behavior
import efm32gg.modules.TIMER3.TIMER_behavior as TIMER_behavior
import efm32gg.modules.UART0.UART_behavior as UART_behavior
import efm32gg.modules.UART1.UART_behavior as UART_behavior
import efm32gg.modules.UARTNCP.UARTNCP_behavior as UARTNCP_behavior
import efm32gg.modules.USART0.USART_behavior as USART_behavior
import efm32gg.modules.USART1.USART_behavior as USART_behavior
import efm32gg.modules.USART2.USART_behavior as USART_behavior
import efm32gg.modules.VCOM.VCOM_behavior as VCOM_behavior
import efm32gg.modules.WDOG.WDOG_behavior as WDOG_behavior
import efm32gg.upgrade as upgrade
import efm32gg.upgrade.upgradeDispatch as upgradeDispatch
PROFILE = True

@RuntimeModel.bind_document_upgrade
def onUpgrade(event, xmlDevice):
    print("Triggering upgrade")
    upgradeResults = upgradeDispatch.upgradeMain(upgrade, xmlDevice)
    # return without xmlDevice if upgradeResults is empty
    if type(upgradeResults) != tuple:
        return []
    (newXmlDevice, changeText) = upgradeResults
    evs = []
    change = hal.newXMLDeviceChange(newXmlDevice)
    try:
        change.setUpgradeText(changeText)
    except AttributeError:
        print("Could not set upgrade text -- using old Studio?")
        print("Text was: {}".format(changeText))
    evs.append(change)
    return evs

@RuntimeModel.bind_document_load
def onLoad(state):
    # Prevent changed properties from enabling parent peripheral
    try:
        hal.registerDeviceOverride(hal.OVERRIDE_PERIPHERAL_AUTO_ENABLE, True)
    except:
        # Fall back to misspelled version of the function argument
        try:
            hal.registerDeviceOverride(hal.OVERRIDE_PERIPHRAL_AUTO_ENABLE, True)
        except:
            pass

    available_modules = Metadata.get_available_modules_for_family()

    if PROFILE:
        start = time.time()

    familyobj = dep.Family(state.device.name)

    modules = []


    module_instance = BTL_BUTTON_behavior.BTL_BUTTON('BTL_BUTTON')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BTL_BUTTON', module_instance)
    modules.append(module_instance)

    module_instance = BUTTON_behavior.BUTTON('BUTTON')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BUTTON', module_instance)
    modules.append(module_instance)

    module_instance = CMU_behavior.CMU('CMU')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('CMU', module_instance)
    modules.append(module_instance)

    module_instance = EMU_behavior.EMU('EMU')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('EMU', module_instance)
    modules.append(module_instance)

    module_instance = EXTFLASH_behavior.EXTFLASH('EXTFLASH')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('EXTFLASH', module_instance)
    modules.append(module_instance)

    module_instance = GPIO_behavior.GPIO('GPIO')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('GPIO', module_instance)
    modules.append(module_instance)

    module_instance = I2C_behavior.I2C('I2C0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('I2C0', module_instance)
    modules.append(module_instance)

    module_instance = I2C_behavior.I2C('I2C1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('I2C1', module_instance)
    modules.append(module_instance)

    module_instance = I2CSENSOR_behavior.I2CSENSOR('I2CSENSOR')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('I2CSENSOR', module_instance)
    modules.append(module_instance)

    module_instance = IOEXP_behavior.IOEXP('IOEXP')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('IOEXP', module_instance)
    modules.append(module_instance)

    module_instance = LED_behavior.LED('LED')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('LED', module_instance)
    modules.append(module_instance)

    module_instance = LEUART_behavior.LEUART('LEUART0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('LEUART0', module_instance)
    modules.append(module_instance)

    module_instance = LEUART_behavior.LEUART('LEUART1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('LEUART1', module_instance)
    modules.append(module_instance)

    module_instance = PRS_behavior.PRS('PRS')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('PRS', module_instance)
    modules.append(module_instance)

    module_instance = SERIAL_behavior.SERIAL('SERIAL')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('SERIAL', module_instance)
    modules.append(module_instance)

    module_instance = SPIDISPLAY_behavior.SPIDISPLAY('SPIDISPLAY')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('SPIDISPLAY', module_instance)
    modules.append(module_instance)

    module_instance = SPINCP_behavior.SPINCP('SPINCP')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('SPINCP', module_instance)
    modules.append(module_instance)

    module_instance = TIMER_behavior.TIMER('TIMER0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('TIMER0', module_instance)
    modules.append(module_instance)

    module_instance = TIMER_behavior.TIMER('TIMER1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('TIMER1', module_instance)
    modules.append(module_instance)

    module_instance = TIMER_behavior.TIMER('TIMER2')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('TIMER2', module_instance)
    modules.append(module_instance)

    module_instance = TIMER_behavior.TIMER('TIMER3')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('TIMER3', module_instance)
    modules.append(module_instance)

    module_instance = UART_behavior.UART('UART0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('UART0', module_instance)
    modules.append(module_instance)

    module_instance = UART_behavior.UART('UART1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('UART1', module_instance)
    modules.append(module_instance)

    module_instance = UARTNCP_behavior.UARTNCP('UARTNCP')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('UARTNCP', module_instance)
    modules.append(module_instance)

    module_instance = USART_behavior.USART('USART0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('USART0', module_instance)
    modules.append(module_instance)

    module_instance = USART_behavior.USART('USART1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('USART1', module_instance)
    modules.append(module_instance)

    module_instance = USART_behavior.USART('USART2')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('USART2', module_instance)
    modules.append(module_instance)

    module_instance = VCOM_behavior.VCOM('VCOM')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('VCOM', module_instance)
    modules.append(module_instance)

    module_instance = WDOG_behavior.WDOG('WDOG')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('WDOG', module_instance)
    modules.append(module_instance)


    if PROFILE:
        stop = time.time()
        print("  construction of all modules completed in {:.3f} ms".format((stop - start) * 1000))
        start = time.time()

    # Do the hook installing after all modules have initialized
    PIN_Snippets.activate_runtime()
    PORTIO_Snippets.activate_runtime()

    for module_instance in modules:
        module_instance.activate_runtime(state)
        force_enable_module = RuntimeModel.get_property_value(
            module_instance.get_property('forceenable'),
            RuntimeModel.get_studio_module_by_name(module_instance.name, state.mode),
            False
        )
        if force_enable_module == '1':
            RuntimeModel.set_module_checked(
                RuntimeModel.get_studio_module_by_name(module_instance.name, state.mode),
                True,
                state,
                readonly=True
            )


    PORTIO_Snippets.onLoad(state)

    if PROFILE:
        stop = time.time()
        print("  activate_runtime() for all modules completed in {:.3f} ms".format((stop - start) * 1000))
