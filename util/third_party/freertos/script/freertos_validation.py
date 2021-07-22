def validate(project):
    if not project.is_selected("device_init_nvic") and not project.is_provided("cortexm0plus"):
        project.warning('Interrupts priorities are not automatically configured since device_init_nvic is not selected', \
                        project.target_for_project(), "To prevent corruption caused by concurrent calls to the FreeRTOS API, interrupts priorities need to be configured according to the FreeRTOS configMAX_SYSCALL_INTERRUPT_PRIORITY setting in FreeRTOSConfig.h")

