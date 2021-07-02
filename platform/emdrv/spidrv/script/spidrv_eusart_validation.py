def validate(project):

    for inst in project.component('spidrv_eusart').instances():
        opt = project.config('SL_SPIDRV_EUSART_{}_CS_CONTROL'.format(inst.upper()))
        cs = project.config('SL_SPIDRV_EUSART_{}_CS_PORT'.format(inst.upper()))

        if (opt is not None) and (cs is not None):
            if opt.value() == 'spidrvCsControlAuto' and not cs:
                project.error(
                    'SPIDRV is configured to control CS, but no CS pin is selected',
                    project.target_for_defines(['SL_SPIDRV_EUSART_{}_CS_CONTROL'.format(inst.upper())]),
                    'CS must be controlled by the application, or a CS pin must be configured',
                    project.quickfix('spidrvCsControlApplication')
                )