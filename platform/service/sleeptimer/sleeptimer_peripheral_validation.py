def validate(project):

    sleeptimer_peripheral = project.config('SL_SLEEPTIMER_PERIPHERAL')
    
    if sleeptimer_peripheral.value() == 'SL_SLEEPTIMER_PERIPHERAL_RTCC' and project.is_provided("device_has_rtcc") == 0:
        project.error('RTCC peripheral is not available on the selected target.', project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))
    elif sleeptimer_peripheral.value() == 'SL_SLEEPTIMER_PERIPHERAL_RTC' and project.is_provided("device_has_rtc") == 0:
        project.error('RTC peripheral is not available on the selected target.', project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))
    elif sleeptimer_peripheral.value() == 'SL_SLEEPTIMER_PERIPHERAL_PRORTC' and project.is_provided("device_has_prortc") == 0:
        project.error('PRORTC peripheral is not available on the selected target.', project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))
    elif sleeptimer_peripheral.value() == 'SL_SLEEPTIMER_PERIPHERAL_SYSRTC' and project.is_provided("device_has_sysrtc") == 0:
        project.error('SYSRTC peripheral is not available on the selected target.', project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))        
    elif sleeptimer_peripheral.value() == 'SL_SLEEPTIMER_PERIPHERAL_BURTC':
        if project.is_provided("device_has_burtc") == 0:
            project.error('BURTC peripheral is not available on the selected target.', project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))
        elif project.is_provided("device_series_0"):
            project.error("sleeptimer doesn't support BURTC for Series 0 devices.", project.target_for_defines("SL_SLEEPTIMER_PERIPHERAL"))
