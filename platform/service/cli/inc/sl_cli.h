/***************************************************************************//**
 * @file
 * @brief Backbone of CLI framework
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

#ifndef SL_CLI_H
#define SL_CLI_H

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#include "sl_cli_types.h"
#include "sl_cli_command.h"
#include "sl_cli_arguments.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup cli
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *  Obtain the number of command arguments.
 *
 * @details
 *  Users obtain the number of command arguments with this macro.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @return
 *   The number of command arguments.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the number of arguments (after the command strings).
 *     int arg_count = sl_cli_get_argument_count(args); // arg_count = 4
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_count(a)      ((int)(a->argc - a->arg_ofs))

/***************************************************************************//**
 * @brief
 *  Obtain the type of argument.
 *
 * @details
 *  Users obtain the type of the argument with this macro.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   enum of the argument type.
 *
 * @details
 *   For auto-generated commands, it could be useful in the handler to know
 *   the type of the argument.
 *
 ******************************************************************************/
#define sl_cli_get_argument_type(a, n)      ((sl_cli_arg_t)(a->arg_type_list[n]))

/***************************************************************************//**
 * @brief
 *  Obtain int8 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_int8(a, n)    (*(int8_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain int16 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_int16(a, n)   (*(int16_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain int32 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_int32(a, n)   (*(int32_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain uint8 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_uint8(a, n)   (*(uint8_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain uint16 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_uint16(a, n)  (*(uint16_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain uint32 arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_uint32(a, n)  (*(uint32_t *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain string arguments.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is the number 0, the next 1, etc.
 *
 * @return
 *   The argument value.
 *   For hex arguments, the return value is a pointer to a buffer containing
 *   decoded values. For string arguments, the return value is a pointer to the
 *   string.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the arguments (after the command strings).
 *     char *text_ptr = sl_cli_get_argument_string(args, 0);  // char ptr to
 *     // "hello"
 *     uint8_t num1_u8 = sl_cli_get_argument_uint8(args, 1);  // num1_u8 = 255
 *     int16_t num2_i16 = sl_cli_get_argument_int16(args, 2); // num2_i16 = -100
 *     size_t hex_array_size;
 *     uint8_t *hex_array_ptr = sl_cli_get_argument_hex(args, 3, &hex_array_size);
 *     // uint8_t ptr to {0xAA, 0xBB, 0xCC}, hex_array_size = 3
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_argument_string(a, n)  ((char *)(a->argv[a->arg_ofs + n]))

/***************************************************************************//**
 * @brief
 *  Obtain the number of command strings.
 *
 * @details
 *  Users obtain the number of command strings with this macro.
 *
 * @param[in] a
 *   The number of command strings.
 *
 * @return
 *   The number of command strings.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the number of command strings (before the arguments).
 *     int cmd_count = sl_cli_get_command_count(args); // cmd_count = 2
 *     // (first string being "example_sub_menu" and second "example_command")
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_command_count(a)       ((int)(a->arg_ofs))

/***************************************************************************//**
 * @brief
 *  Obtain the command string(s).
 *
 * @details
 *  Users get the command string with this macro. If the command is
 *  used in a group, both the group string(s) and command string can be obtained.
 *  The total number of command strings is available in the command argument
 *  arg_ofs variable.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The command string number. The first string is number 0, the next 1, etc.
 *
 * @details
 *   An example could be the CLI input of
 *   `example_sub_menu example_command hello 255 -100 {AA BB CC}`
 *   with corresponding C code of:
 *   ```c
 *   void example_command(sl_cli_command_arg_t *args)
 *   {
 *     // Get the command strings (before the arguments).
 *     char *cmd1_ptr = sl_cli_get_command_string(args, 0); // char ptr to
 *     // "example_sub_menu"
 *     char *cmd2_ptr = sl_cli_get_command_string(args, 1); // char ptr to
 *     // "example_command"
 *   }
 *   ```
 ******************************************************************************/
#define sl_cli_get_command_string(a, n)   ((char *)(a->argv[n]))

/***************************************************************************//**
 *  @brief The default CLI handle.
 ******************************************************************************/
extern sl_cli_handle_t sl_cli_default_handle;

/***************************************************************************//**
 *  @brief The default CLI command group.
 ******************************************************************************/
extern sl_cli_command_group_t *sl_cli_default_command_group;

/***************************************************************************//**
 * @brief
 *  Get the hex argument length and value.
 *
 * @param[in] a
 *   A pointer to the command arguments.
 *
 * @param[in] n
 *   The argument number. The first argument is number 0, the next 1, etc.
 *
 * @param[in] l
 *   A pointer to the variable that receives the argument value length.
 *   Note: The length is stored in a 2 byte variable. Valid lengths are
 *   in the range 0 .. 65535.
 *
 * @return
 *   A pointer to the value buffer.
 ******************************************************************************/
uint8_t *sl_cli_get_argument_hex(sl_cli_command_arg_t *a, size_t n, size_t *l);

/***************************************************************************//**
 * @brief
 *  Clear (reset) a CLI.
 *
 * @param[in] handle
 *   A handle to the CLI that will be cleared.
 ******************************************************************************/
void sl_cli_clear(sl_cli_handle_t handle);

/***************************************************************************//**
 * @brief
 *  Redirect user input.
 *  Normally, an input string is passed to the CLI command handler for execution,
 *  but with the redirect function the input string will be passed to the
 *  alternative function.
 *  If the alternative input function should not to be used, this function
 *  can be called with NULL in the command_function, prompt and aux.
 *
 * @param[in] handle
 *   A handle to the CLI.
 *
 * @param[in] command_function
 *   A pointer to the function that will receive user input when the re-direct
 *   is active. NULL to stop the redirect.
 *
 * @param[in] prompt
 *   A pointer to a string that will be used as command prompt in the redirect
 *   function. NULL to stop the redirect.
 *
 * @param[in] aux
 *   A pointer that will be added to the redirect function arguments.
 *   NULL to stop the redirect.
 ******************************************************************************/
void sl_cli_redirect_command(sl_cli_handle_t handle, sl_cli_command_function_t command_function, const char *prompt, void *aux);

/***************************************************************************//**
 * @brief
 *  Handle input. Execute a complete command line with command and arguments.
 *
 * @param[in] handle
 *   A handle to the CLI.
 *
 * @param[in] string
 *   A pointer to the string containing the command line that shall be executed.
 *
 * @return
 *   Execution status.
 *   Note: If the command is redirected, the function will always return
 *   SL_STATUS_OK.
 ******************************************************************************/
sl_status_t sl_cli_handle_input(sl_cli_handle_t handle, char *string);

/***************************************************************************//**
 * @brief
 *  Initialize a CLI instance.
 *
 * @param[in] handle
 *   A handle to the CLI.
 *
 * @param[in] parameters
 *   A pointer to the structure containing instance parameters.
 *
 * @return
 *   Initialization status.
 ******************************************************************************/
sl_status_t sl_cli_instance_init(sl_cli_handle_t handle,
                                 sl_cli_instance_parameters_t *parameters);

#if !defined(SL_CATALOG_KERNEL_PRESENT) || defined(DOXYGEN)
/***************************************************************************//**
 * @brief
 *  Check if the CLI instance can allow sleep.
 *  This function is available in a bare metal configuration only.
 *
 * @param[in] handle
 *   A handle to the CLI instance.
 *
 * @return
 *   A boolean that is true if the CLI allows sleep, else false.
 ******************************************************************************/
bool sl_cli_is_ok_to_sleep(sl_cli_handle_t handle);

/***************************************************************************//**
 * @brief
 *  The bare metal tick function.
 *
 * @param[in] handle
 *   A handle to the CLI instance.
 ******************************************************************************/
void sl_cli_tick_instance(sl_cli_handle_t handle);
#endif

#ifdef __cplusplus
}
#endif

/** @} (end addtogroup cli) */

/* *INDENT-OFF* */
/* THE REST OF THE FILE IS DOCUMENTATION ONLY! */
/***************************************************************************//**
 * @addtogroup cli Command Line Interface
 * @brief Command Line Interface (CLI)
 *
 * @{
@details

# Introduction

The Command Line Interface (CLI) software component simplifies creating command line user interfaces for programs. It handles tasks such as receiving keyboard input, parsing the input strings for commands and arguments, and finally call the proper C function with decoded and validated arguments. Functions can use standard output functions such as printf to write information to the console.

Multiple components (parts of an application) may define CLI commands where the running program will typically merge all commands into a super-set of commands with common input and output, I/O. The CLI uses I/O functions provided by the I/O Streams framework, iostream.

The CLI component supports multiple instances where separate CLI instances will use separate iostream instances. Groups of commands can be assigned to specific CLI instances, making it possible for one application to use multiple CLI instances where each is customized for its particular use.

# Content

* [Features](#features)
* [Design](#design)
* [Configuration](#configuration)
* [Examples](#examples)
* [Extensions](#extensions)

# Features
The CLI has several built in features that will be inherited by all applications using the CLI component. The following sections will explain some of the CLI features.

<b>Please note:</b> Some of the features can be simplified or removed to reduce code size by changing the configuration of the application.

## Command Groups
The CLI support both stand alone commands and commands that belong to groups. A stand alone command is executed by typing just the command name and arguments. If a command belong to a group, the group name must be typed before the command name. Groups can be nested, and in that case, all group names must be typed before the command name.

If an application has implemented the commands `on` and `off` that are part of the groups `green` and `red` in group `led`, the user can type: `led green on` or `led red off` to control the LEDs.

## Help
The CLI has a built in help command, which can be used as follows:

By typing `help`, all commands are listed.

By typing `help group`, all commands in the `group` are listed.

By typing `help command`, help for the `command` is shown.

The information that is displayed when using the `help` command must be supplied by the implementer. Details for each command must be placed in command tables. See the [Command tables](#command-tables) section for more details.

## Auto-Complete
The CLI can complete a partially typed command by pressing the TAB key.

## Cursor Movement
The up-arrow and down-arrow keys can be used to navigate up and down in the history buffer.

The left-arrow and right-arrow keys are used to move the cursor in the current command line. The BACKSPACE key is used to delete the character to the left of the cursor. The DEL key is used to delete the character under the cursor. Typed characters will be inserted at the cursor position.

## Command History
Commands will be stored in the history buffer when executed. Previous commands can be executed again by pressing the up-arrow key one or more times.

<b>Please note:</b> The history buffer is a simple character array, which does not define how many command lines can be stored. The history buffer will store command lines sequentially, making room for more short commands than long.

## Dynamic Registration of New Commands
An application using the CLI component can define commands that must be installed either at compile time or at run time. Defining commands at compile time may be sufficient for simple applications, while more advanced applications with several CLI instances, may utilize that the CLI can add command groups at run time.

## Central decoding and validation of command arguments
The CLI has built in functions to decode and validate command arguments. The command handler will not be called unless the command is entered with correct arguments.

The CLI argument validation can handle signed and unsigned numeric values with 8, 16 and 32 bit sizes, hexadecimal and string arguments. The command handler will be called with decoded arguments using an `arc, argv` pattern similar to how C/C++ applications pass command line arguments to the main function.

If none of the built in argument types can be used by the command, it can use string arguments and decode the strings in the command handler.

<b>Please note:</b> For the last argument, it is possible to specify that it is optional, mandatory or can have multiple values.

## Input and output
The CLI is using iostreams for input and output. Each CLI instance must have a dedicated iostream instance.

Assigning an iostream instance to a CLI instance is usually done with an application configuration. If the application has only one CLI and one iostream instance, the configuration will automatically assign the iostream instance to the CLI instance.

## Requirements not defined by the CLI
Command naming rules or output formats are not defined by the CLI.

# Design
To fully understand how to use the CLI, it is crucial to understand the design and some implementation details. The following sections will try to explain the basics and how to create user commands.

## Modules
The CLI has been implemented as two independent software modules: `input handler` and `command interpreter`. The `input handler` handles the user input and allows the user to enter command lines. When the user types the ENTER key, the input string is passed to the `command interpreter` where the string will be interpreted and the appropriate command handler will be called with the command arguments.

Normally both modules are used together, but an application can use the `command interpreter` directly. In that case, the `command interpreter` must be called with a command line as input parameter.

## Command signature
All command handlers must have the same signature, defined in `sl_cli_types.h`:

```c
typedef void (*sl_cli_command_func_t)(sl_cli_command_arg_t *arguments);
```

## Command arguments
Command arguments are available via the arguments pointer passed to the command handler function.

The arguments pointer will point to a struct holding the actual argument values.

The arguments struct has the following definition:
```c
typedef struct {
  struct sl_cli *handle;                        ///< The current cli handle.
  int argc;                                     ///< The total number of input strings (command group names, if any + command + corresponding arguments).
  void **argv;                                  ///< A pointer to the input string array.
  int arg_ofs;                                  ///< The offset in the input string array where the arguments start (after the command group names, if any and command).
  const sl_cli_argument_type_t* arg_type_list;  ///< List of argument types
} sl_cli_command_arg_t;
```

The `handle` identifies the CLI instance where the command was issued. By including the instance handle, it is possible to share the same command handler between multiple CLI instances.

By using the `argc`, `argv` way of passing argument values, it is possible to have a common command handler signature but support variable number of arguments.

When the command handler is called, the `argc`, `argv` arguments will contain all commands and arguments. Because the CLI supports command groups, the command may consist of multiple command groups along with the command itself. The `arg_ofs` tells the command handler the offset where the command arguments begin.

The 'arg_type_list' points to the array of argument type contained in the sl_cli_command_info_t struct of the command. With this, inside the handler it is possible to call the sl_cli_get_argument_type(a, n) macro and retrieve the type of an argument. Although this should be known at compile time, there are some scenarios
when autogenerating commands where knowing their type could be usefull.

The cli.h has defined the following macros that can be used to get argument values. The macros use `a` for the arguments pointer and `n` for the argument offset, starting on 0 for the first argument.
```c
sl_cli_get_argument_int8(a, n)
sl_cli_get_argument_int16(a, n)
sl_cli_get_argument_int32(a, n)
sl_cli_get_argument_uint8(a, n)
sl_cli_get_argument_uint16(a, n)
sl_cli_get_argument_uint32(a, n)
sl_cli_get_argument_hex(a, n, l)
sl_cli_get_argument_string(a, n)
```

## Command tables
Adding commands to the CLI requires use of three different data structures. The data structures have a root node referred to as a "command group", where sub-structures defining command details are nested. The "command group" may contain details for one or more commands, and it is possible to install multiple "command groups" in each CLI instance.

The "command group" must be of the type:
```c
typedef struct {
  sl_slist_node_t node;
  bool in_use;
  const sl_cli_command_entry_t *command_table;
} sl_cli_command_group_t;
```

<b>Please note:</b> Each time a command group shall be installed in a CLI instance, the application must support one unique command group data structure. Command groups cannot be re-used or shared between CLI instances.

The next level is an array where each of the elements must be a "command entry". There will typically be one array element for each command. If a command has both a long and a short (shortcut) name, it will take two array elements.

Each of the "command entries" must be of the type:
```c
typedef struct {
  const char                  *name;        ///< String associated with command/group
  const sl_cli_command_info_t *command;     ///< Pointer to command information
  const bool                  is_shortcut;  ///< Indicating if the entry is a shortcut
} sl_cli_command_entry_t;
```
A "command entries" array can be re-used and shared between multiple CLI instances.

And finally "command information" for commands are defined in one data structure for each command. The "command information" structure is defined with the type:
```c
typedef struct {
  sl_cli_command_func_t function;             ///< Command function
    #if SL_CLI_HELP_DESCRIPTION_ENABLED
  char                   *help;               ///< Info displayed by "help" command
  char                   *arg_help;           ///< Info for arguments.
    #endif // SL_CLI_HELP_DESCRIPTION_ENABLED
  sl_cli_argument_type_t arg_type_list[];     ///< List of argument types
} sl_cli_command_info_t;
```
A "command information" data structure can be re-used and shared between multiple CLI commands and instances.

## Command handler
In addition to the tables described above, each command must have a command handler. The command handler is typically written in C-code, and all command handlers have the same signature. The command handler function prototype has the following defition:
```c
typedef void (*sl_cli_command_func_t)(sl_cli_command_arg_t *arguments);
```

## Differences between bare-metal and kernel configurations
The CLI component can be used in both bare-metal and kernel configurations. There are some differences between the two configurations that is explained in the following sections.

<b>Bare-metal</b>

In a bare-metal configuraton, the `input handler` has a process-action (tick) function that will poll the iostream for input. When generating a project with uc, the CLI process-action function will be installed into the system framework. Calling the `sl_system_process_action` function will call the CLI process-action function.

<b>Please note:</b> Cli command handlers that take a long time to execute can (should) return from the process-action function before they are complete to not stall other component process-action functions. Execution will in that case be split into several calls to the process-action function. The application should not make any assumptions about when any of the command handlers have completed execution based on when the `sl_system_process_action` returns.

<b>Kernel</b>

In a kernel configuration, the CLI will create a task where the `input handler` will poll the iostream for input data. There will be created one task for each CLI instance, and the task(s) must be started by the application by calling the `sl_system_kernel_start` function.

# Configuration
The CLI has two sets of configurations. One is common for all CLI instances and is placed in the `sl_cli_config.h` file. The other is a configuration file for each CLI instance with the file name `sl_cli_config_<instance-name>.h`.

# Examples
The following steps demonstrates how to create and install a CLI command.

<b>Please note:</b> To avoid forward definitions in the C-code, the following steps will typically be implemented in reverse order.

Include the `cli` and `iostream` components to the project. Both `cli` and `iostream_usart` instances must specify instance names. The `iostream_usart` component has some pre-defined instance names while the `cli` instance name can be anything.

```
component:
  - id: cli
    instance:
    - example
  - id: iostream_usart
    instance:
    - vcom
```

Create the command group at the top level:

```c
static sl_cli_command_group_t a_group_0 = {
  { NULL },
  false,
  a_table
};
```

Create the array of commands, containing two elements in this example:

```c
static sl_cli_command_entry_t a_table[] = {
  { "echo_str", &cmd__echostr, false },
  { "echo_int", &cmd__echoint, false },
  { NULL, NULL, false },
};
```

Create command details for the two commands:

```c
static const sl_cli_command_info_t cmd__echostr = \
  SL_CLI_COMMAND(echo_str,
                 "echoes string arguments to the output",
                 "Just a string...",
                 {SLI_CLI_ARG_WILDCARD, SLI_CLI_ARG_END, });

static const sl_cli_command_info_t cmd__echoint = \
  SL_CLI_COMMAND(echo_int,
                 "echoes integer arguments to the output",
                 "Just a number...",
                 {SLI_CLI_ARG_INT8, SLI_CLI_ARG_ADDITIONAL, SLI_CLI_ARG_END, });
```

Create command handlers for the two commands:

```c
void echo_str(sl_cli_command_arg_t *arguments)
{
  char *ptr_string;

  for (int i = 0; i < sl_cli_get_argument_count(arguments); i++) {
    ptr_string = sl_cli_get_argument_string(arguments, i);
    ...
  }
}

void echo_int(sl_cli_command_arg_t *arguments)
{
  int8_t argument_value;

  for (int i = 0; i < sl_cli_get_argument_count(arguments); i++) {
    argument_value = sl_cli_get_argument_int8(arguments, i);
    ...
  }
}
```

And finally call the function to install the commands.

```c
  status = sl_cli_command_add_command_group(cli_handle, &a_group_0);
```

The output from executing `help` will in this case be:
```
> help
  echostr                       echoes string arguments to the output
                                [*] Just a string...
  echoint                       echoes integer arguments to the output
                                [int8+] Just a number...
```

# Extensions
The CLI comes with some pre-made components that can be useful for some applications. To take advantage of these components, the user must:
1. Define the command(s) in the command tables. Use the command handlers supplied with the component(s).
2. Include the component(s) in the project.

The components come with the command handlers and do all the necessary integration with the CLI. The components do however not define the command name, it must be defined by the application implementer.

<b>Please note:</b> The CLI extensions described here will use the method of splitting some of the command handler operations into multiple process-action calls for bare-metal configuration.

<b>Common properties for the storage components:</b> The storage components share some common properties although data is stored in different locations. The most important are: New commands can be added, existing commands can be deleted and stored commands can be executed.

One benefit of running commands from a storage compared to typing the commands at user input is that the next command in the list will be executed immediately after the previous command has completed. Commands will be executed in the sequence they are added and stored, and there will be zero or little delay between commands.

## CLI Storage NVM3
The `cli_storage_nvm3` component has been designed to store command lines in NVM3 storage. In addition to letting the user control when the commands are executed, the stored commands will automatically be executed at program start.

The `cli_storage_nvm3` component does not define the user commands, but it implements a few functions where the following four are designed to be used as CLI command handlers directly.
```c
void sl_cli_storage_nvm3_clear(sl_cli_command_arg_t *arguments);
void sl_cli_storage_nvm3_list(sl_cli_command_arg_t *arguments);
void sl_cli_storage_nvm3_define(sl_cli_command_arg_t *arguments);
void sl_cli_storage_nvm3_execute(sl_cli_command_arg_t *arguments);
```

In addition, it is possible to get the number of command lines stored in NVM3 storage by calling:
```c
size_t sl_cli_storage_nvm3_count(sl_cli_handle_t cli_handle);
```

The `cli_storage_nvm3` depends on the `cli_default` component that defines the NVM3 storage area. This area is typically shared between different parts of the application, where each has its own range of NVM3 object keys to avoid collisions. The `cli_storage_nvm3` component has got a range with 256 keys.

It is possible to configure each CLI instance to use a sub-set of the available 256 keys to separate commands between different CLI instances.

## CLI Storage RAM
The `cli_storage_ram` component has been designed to store command lines in a ram buffer.

The `cli_storage_ram` component does not define the user commands, but it implements a few functions where the following four are designed to be used as CLI command handlers directly.
```c
void sl_cli_storage_ram_clear(sl_cli_command_arg_t *arguments);
void sl_cli_storage_ram_list(sl_cli_command_arg_t *arguments);
void sl_cli_storage_ram_define(sl_cli_command_arg_t *arguments);
void sl_cli_storage_ram_execute(sl_cli_command_arg_t *arguments);
```

In addition, it is possible to get the number of command lines stored in RAM by calling:
```c
size_t sl_cli_storage_ram_count(sl_cli_handle_t cli_handle);
```

Each instance of the CLI will have its own RAM buffer. Commands defined in one CLI instance will not be available for other instances.

## CLI Delay

The `cli_delay` component may be useful to add delays between commands when running command sequences from a storage. The function will delay for the specified number of milliseconds. During the delay, it will allow other components to run in the background.

The command handler has the following function prototype:

```
void sl_cli_delay_command(sl_cli_command_arg_t *arguments);
```

 *
 * @} (end addtogroup cli)
 ******************************************************************************/

#endif // SL_CLI_H
