def validate(project):
    if project.is_selected("device_init_lfrco") and not project.is_selected("device_init_hfxo"):
        if project.config("SL_DEVICE_INIT_LFRCO_PRECISION").value() == "cmuPrecisionHigh":
            project.warning('HFXO is not automatically initialized', project.target_for_project(), "LFRCO is configured in high precision mode. Ensure that HFXO is initialized by adding (Device Init: HFXO)")

