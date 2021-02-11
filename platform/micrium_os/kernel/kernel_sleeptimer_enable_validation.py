def validate(project):

    tick_enable = project.config('OS_CFG_TICK_EN')
    
    if tick_enable.value() == '1' and project.is_selected('sleeptimer') == 0:
        project.error('Sleeptimer is needed if OS_CFG_TICK_EN is equal to 1', project.target_for_defines("OS_CFG_TICK_EN"))