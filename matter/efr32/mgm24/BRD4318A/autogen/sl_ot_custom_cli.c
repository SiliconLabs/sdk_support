/***************************************************************************/
/**
 * @file
 * @brief Custom CLI support for OpenThread
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <openthread/cli.h>
#include <common/code_utils.hpp>
#include <string.h>
#include "sl_ot_custom_cli.h"

/*******************************************************************************
 * Example syntax (.slcc or .slcp) for populating this file:
 *
 *   template_contribution:
 *     - name: sl_ot_cli_command    # Register a command
 *       value:
 *         name: status             # Name of command
 *         handler: status_command  # Function to be called. Must be defined
 *
 ******************************************************************************/
extern otError bleCommand(void *aContext, uint8_t aArgsLength, char *aArgs[]);

otCliCommand sl_ot_custom_commands[] = {
#ifdef SL_OPENTHREAD_BLE_CLI_ENABLE
    {"ble", bleCommand},
#endif

};

// This is needed because `sizeof` is calculated at compile time and can't be calculated outside of this source file.
const size_t sl_ot_custom_commands_count = OT_ARRAY_LENGTH(sl_ot_custom_commands);

void printCommands(otCliCommand commands[], size_t commandCount)
{
    for (size_t i = 0; i < commandCount; i++) {
        otCliOutputFormat("%s\r\n", commands[i].mName);
    }
}

void sl_ot_custom_cli_init(void)
{
#if OPENTHREAD_COPROCESSOR
    otCRPCSetUserCommands(sl_ot_custom_commands, sl_ot_custom_commands_count, NULL);
#else
    otCliSetUserCommands(sl_ot_custom_commands, sl_ot_custom_commands_count, NULL);
#endif
}