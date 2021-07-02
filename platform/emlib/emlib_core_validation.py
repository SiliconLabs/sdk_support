def validate(project):
  interrupt_disabled_timing = project.config('SL_EMLIB_CORE_ENABLE_INTERRUPT_DISABLED_TIMING')

  if interrupt_disabled_timing.value() == '1' and project.is_provided("cycle_counter") == 0:
    project.error("Interrupt disabled timing requires cycle_counter", project.target_for_defines("SL_EMLIB_CORE_ENABLE_INTERRUPT_DISABLED_TIMING"))
