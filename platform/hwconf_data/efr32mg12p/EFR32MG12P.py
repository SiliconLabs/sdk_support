#!/usr/bin/env python3

import os
import glob
import time
import Studio.halConfig as hal
import efr32mg12p.PythonSnippet.RuntimeModel as RuntimeModel
import efr32mg12p.PythonSnippet.ExporterModel as ExporterModel
import efr32mg12p.PythonSnippet.Metadata as Metadata
import efr32mg12p.modules.PIN.PIN_Snippets as PIN_Snippets
import efr32mg12p.modules.PORTIO.PORTIO_Snippets as PORTIO_Snippets
import efr32mg12p.halconfig.halconfig_dependency as dep

import efr32mg12p.modules.ACMP0.ACMP_behavior as ACMP_behavior
import efr32mg12p.modules.ACMP1.ACMP_behavior as ACMP_behavior
import efr32mg12p.modules.ADC0.ADC_behavior as ADC_behavior
import efr32mg12p.modules.ANTDIV.ANTDIV_behavior as ANTDIV_behavior
import efr32mg12p.modules.BATTERYMON.BATTERYMON_behavior as BATTERYMON_behavior
import efr32mg12p.modules.BTL_BUTTON.BTL_BUTTON_behavior as BTL_BUTTON_behavior
import efr32mg12p.modules.BULBPWM.BULBPWM_behavior as BULBPWM_behavior
import efr32mg12p.modules.BULBPWM_COLOR.BULBPWM_COLOR_behavior as BULBPWM_COLOR_behavior
import efr32mg12p.modules.BUTTON.BUTTON_behavior as BUTTON_behavior
import efr32mg12p.modules.CMU.CMU_behavior as CMU_behavior
import efr32mg12p.modules.COEX.COEX_behavior as COEX_behavior
import efr32mg12p.modules.CS5463.CS5463_behavior as CS5463_behavior
import efr32mg12p.modules.CSEN.CSEN_behavior as CSEN_behavior
import efr32mg12p.modules.DCDC.DCDC_behavior as DCDC_behavior
import efr32mg12p.modules.EMU.EMU_behavior as EMU_behavior
import efr32mg12p.modules.EXTFLASH.EXTFLASH_behavior as EXTFLASH_behavior
import efr32mg12p.modules.EZRADIOPRO.EZRADIOPRO_behavior as EZRADIOPRO_behavior
import efr32mg12p.modules.FEM.FEM_behavior as FEM_behavior
import efr32mg12p.modules.GPIO.GPIO_behavior as GPIO_behavior
import efr32mg12p.modules.I2C0.I2C_behavior as I2C_behavior
import efr32mg12p.modules.I2C1.I2C_behavior as I2C_behavior
import efr32mg12p.modules.I2CSENSOR.I2CSENSOR_behavior as I2CSENSOR_behavior
import efr32mg12p.modules.IDAC0.IDAC_behavior as IDAC_behavior
import efr32mg12p.modules.IOEXP.IOEXP_behavior as IOEXP_behavior
import efr32mg12p.modules.LED.LED_behavior as LED_behavior
import efr32mg12p.modules.LEUART0.LEUART_behavior as LEUART_behavior
import efr32mg12p.modules.MODEM.MODEM_behavior as MODEM_behavior
import efr32mg12p.modules.PA.PA_behavior as PA_behavior
import efr32mg12p.modules.PRS.PRS_behavior as PRS_behavior
import efr32mg12p.modules.PTI.PTI_behavior as PTI_behavior
import efr32mg12p.modules.PYD1698.PYD1698_behavior as PYD1698_behavior
import efr32mg12p.modules.SERIAL.SERIAL_behavior as SERIAL_behavior
import efr32mg12p.modules.SPIDISPLAY.SPIDISPLAY_behavior as SPIDISPLAY_behavior
import efr32mg12p.modules.SPINCP.SPINCP_behavior as SPINCP_behavior
import efr32mg12p.modules.TIMER0.TIMER_behavior as TIMER_behavior
import efr32mg12p.modules.TIMER1.TIMER_behavior as TIMER_behavior
import efr32mg12p.modules.UARTNCP.UARTNCP_behavior as UARTNCP_behavior
import efr32mg12p.modules.USART0.USART_behavior as USART_behavior
import efr32mg12p.modules.USART1.USART_behavior as USART_behavior
import efr32mg12p.modules.USART2.USART_behavior as USART_behavior
import efr32mg12p.modules.USART3.USART_behavior as USART_behavior
import efr32mg12p.modules.VCOM.VCOM_behavior as VCOM_behavior
import efr32mg12p.modules.VDAC0.VDAC_behavior as VDAC_behavior
import efr32mg12p.modules.VUART.VUART_behavior as VUART_behavior
import efr32mg12p.modules.WDOG.WDOG_behavior as WDOG_behavior
import efr32mg12p.modules.WTIMER0.WTIMER_behavior as WTIMER_behavior
import efr32mg12p.modules.WTIMER1.WTIMER_behavior as WTIMER_behavior
import efr32mg12p.upgrade as upgrade
import efr32mg12p.upgrade.upgradeDispatch as upgradeDispatch
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


    module_instance = ACMP_behavior.ACMP('ACMP0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('ACMP0', module_instance)
    modules.append(module_instance)

    module_instance = ACMP_behavior.ACMP('ACMP1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('ACMP1', module_instance)
    modules.append(module_instance)

    module_instance = ADC_behavior.ADC('ADC0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('ADC0', module_instance)
    modules.append(module_instance)

    module_instance = ANTDIV_behavior.ANTDIV('ANTDIV')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('ANTDIV', module_instance)
    modules.append(module_instance)

    module_instance = BATTERYMON_behavior.BATTERYMON('BATTERYMON')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BATTERYMON', module_instance)
    modules.append(module_instance)

    module_instance = BTL_BUTTON_behavior.BTL_BUTTON('BTL_BUTTON')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BTL_BUTTON', module_instance)
    modules.append(module_instance)

    module_instance = BULBPWM_behavior.BULBPWM('BULBPWM')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BULBPWM', module_instance)
    modules.append(module_instance)

    module_instance = BULBPWM_COLOR_behavior.BULBPWM_COLOR('BULBPWM_COLOR')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BULBPWM_COLOR', module_instance)
    modules.append(module_instance)

    module_instance = BUTTON_behavior.BUTTON('BUTTON')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('BUTTON', module_instance)
    modules.append(module_instance)

    module_instance = CMU_behavior.CMU('CMU')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('CMU', module_instance)
    modules.append(module_instance)

    module_instance = COEX_behavior.COEX('COEX')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('COEX', module_instance)
    modules.append(module_instance)

    module_instance = CS5463_behavior.CS5463('CS5463')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('CS5463', module_instance)
    modules.append(module_instance)

    module_instance = CSEN_behavior.CSEN('CSEN')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('CSEN', module_instance)
    modules.append(module_instance)

    module_instance = DCDC_behavior.DCDC('DCDC')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('DCDC', module_instance)
    modules.append(module_instance)

    module_instance = EMU_behavior.EMU('EMU')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('EMU', module_instance)
    modules.append(module_instance)

    module_instance = EXTFLASH_behavior.EXTFLASH('EXTFLASH')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('EXTFLASH', module_instance)
    modules.append(module_instance)

    module_instance = EZRADIOPRO_behavior.EZRADIOPRO('EZRADIOPRO')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('EZRADIOPRO', module_instance)
    modules.append(module_instance)

    module_instance = FEM_behavior.FEM('FEM')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('FEM', module_instance)
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

    module_instance = IDAC_behavior.IDAC('IDAC0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('IDAC0', module_instance)
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

    module_instance = MODEM_behavior.MODEM('MODEM')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('MODEM', module_instance)
    modules.append(module_instance)

    module_instance = PA_behavior.PA('PA')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('PA', module_instance)
    modules.append(module_instance)

    module_instance = PRS_behavior.PRS('PRS')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('PRS', module_instance)
    modules.append(module_instance)

    module_instance = PTI_behavior.PTI('PTI')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('PTI', module_instance)
    modules.append(module_instance)

    module_instance = PYD1698_behavior.PYD1698('PYD1698')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('PYD1698', module_instance)
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

    module_instance = USART_behavior.USART('USART3')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('USART3', module_instance)
    modules.append(module_instance)

    module_instance = VCOM_behavior.VCOM('VCOM')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('VCOM', module_instance)
    modules.append(module_instance)

    module_instance = VDAC_behavior.VDAC('VDAC0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('VDAC0', module_instance)
    modules.append(module_instance)

    module_instance = VUART_behavior.VUART('VUART')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('VUART', module_instance)
    modules.append(module_instance)

    module_instance = WDOG_behavior.WDOG('WDOG')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('WDOG', module_instance)
    modules.append(module_instance)

    module_instance = WTIMER_behavior.WTIMER('WTIMER0')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('WTIMER0', module_instance)
    modules.append(module_instance)

    module_instance = WTIMER_behavior.WTIMER('WTIMER1')
    module_instance.load_halconfig_model(available_modules, familyobj)
    state.set_module_object('WTIMER1', module_instance)
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
