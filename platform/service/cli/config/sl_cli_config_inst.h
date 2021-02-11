/***************************************************************************//**
 * @file
 * @brief Configuration file for CLI.
 * @version x.y.z
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_CLI_CONFIG_INSTANCE_H
#define SL_CLI_CONFIG_INSTANCE_H

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

// <o SL_CLI_INSTANCE_TASK_PRIORITY> Task priority <0-55>
// <i> Default: 16
// <i> Priority of the CLI task using the CMSIS order (55 is highest priority)
  #define SL_CLI_INSTANCE_TASK_PRIORITY      (16)

// <o SL_CLI_INSTANCE_TASK_STACK_SIZE> Task stack size
// <i> Default: 400
// <i> Stack size for the CLI task in words.
  #define SL_CLI_INSTANCE_TASK_STACK_SIZE       (400)

// <o SL_CLI_INSTANCE_TASK_START_DELAY_MS> CLI task start delay
// <i> Default: 0
// <i> Specifies the delay in milliseconds before the cli task start to poll for input.
  #define SL_CLI_INSTANCE_TASK_START_DELAY_MS   (0)

// <o SL_CLI_INSTANCE_TASK_LOOP_DELAY_MS> CLI task loop delay
// <i> Default: 50
// <i> Specifies the delay in milliseconds after the cli task has polled the input.
  #define SL_CLI_INSTANCE_TASK_LOOP_DELAY_MS    (50)

// <o SL_CLI_INSTANCE_IOSTREAM_HANDLE> The iostream handle used by the cli instance
// <i> Default: sl_iostream_get_default()
  #define SL_CLI_INSTANCE_IOSTREAM_HANDLE    sl_iostream_get_default()

// <o SL_CLI_INSTANCE_COMMAND_GROUP> The default command group.
// <i> Default: sl_cli_default_command_group.
// <i> Specifies a pointer to the command group that shall be used as the
// <i> default command group for the cli instance.
// <i> The template file that is creating cli instances will also create one
// <i> command group for each cli instance. During initialization, the
// <i> sl_cli_default_command_group will be updated for each instance to point
// <i> to the instance version of the command group. This makes it possible to
// <i> use the same variable for all instances, but each getting its own
// <i> command group.
// <i> The application can provide a group created elsewhere in the
// <i> application or use an empty definition for no default group.
// <i> Please note: A command group can only be used once.
  #define SL_CLI_INSTANCE_COMMAND_GROUP      sl_cli_default_command_group

#endif // SL_CLI_CONFIG_INSTANCE_H

// <<< end of configuration section >>>
