/***************************************************************************//**
 * @file sl_power_manager_config.h
 * @brief Power Manager configuration file.
 * @version 5.6.0
 *******************************************************************************
 * # License
 * <b>(C) Copyright 2018 Silicon Labs, www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_POWER_MANAGER_CONFIG_H
#define SL_POWER_MANAGER_CONFIG_H

// <h>Power manager configuration

// <q SL_POWER_MANAGER_CMU_CUSTOM_IRQ_HANDLER> Enable custom CMU IRQ handler i.e. Enable if CMU_IRQ_Handler is needed from your application.
// <i> The function sl_power_manager_irq_handler() will have to be called from you custom handler if this is enabled.
// <i> Default: 0
#define SL_POWER_MANAGER_CMU_CUSTOM_IRQ_HANDLER  0

// <o SL_POWER_MANAGER_LOWEST_EM_ALLOWED> Lowest Energy mode allowed
// <2=> EM2
// <3=> EM3
// <i> Default: 2
#define SL_POWER_MANAGER_LOWEST_EM_ALLOWED   3

// <e SL_POWER_MANAGER_DEBUG> Enable debugging feature
// <i> Enable or disable debugging features (trace the different modules that have requirements).
// <i> Default: 0
#define SL_POWER_MANAGER_DEBUG  0

// <o SL_POWER_MANAGER_DEBUG_POOL_SIZE> Maximum numbers of requirements that can be logged
// <i> Default: 10
#define SL_POWER_MANAGER_DEBUG_POOL_SIZE  10
// </e>

#endif /* SL_POWER_MANAGER_CONFIG_H */

// <<< end of configuration section >>>
