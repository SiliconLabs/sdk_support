#ifndef SL_BT_RTOS_CONFIG_H
#define SL_BT_RTOS_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Priority Configuration for Bluetooth RTOS Tasks

// <o SL_BT_RTOS_LINK_LAYER_TASK_PRIORITY> The priority of Link Layer task
// <i> Default: 52 (CMSIS-RTOS2 osPriorityRealtime4)
// <i> Define Link Layer task priority. This must be a valid priority value
// <i> from CMSIS-RTOS2 osPriority_t definition. Link Layer task must have the
// <i> highest priority in these three Bluetooth RTOS tasks.
#define SL_BT_RTOS_LINK_LAYER_TASK_PRIORITY     (52)

// <o SL_BT_RTOS_HOST_STACK_TASK_PRIORITY> The priority of host stack task
// <i> Default: 51 (CMSIS-RTOS2 osPriorityRealtime3)
// <i> Define host stack task priority. This must be a valid priority value
// <i> from CMSIS-RTOS2 osPriority_t definition.
#define SL_BT_RTOS_HOST_STACK_TASK_PRIORITY     (51)

// <o SL_BT_RTOS_EVENT_HANDLER_TASK_PRIORITY> The priority of host stack task
// <i> Default: 50 (CMSIS-RTOS2 osPriorityRealtime2)
// <i> Define event handler task priority. This must be a valid priority value
// <i> from CMSIS-RTOS2 osPriority_t definition. Event handler task must have
// <i> the lowest priority in these three Bluetooth RTOS tasks.
#define SL_BT_RTOS_EVENT_HANDLER_TASK_PRIORITY  (50)

// </h> End Priority Configuration for Bluetooth RTOS Tasks

// <<< end of configuration section >>>

#endif // SL_BT_RTOS_CONFIG_H
