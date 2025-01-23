#!/usr/bin/env python3

"""generate_boards.py: Script generate slc files for all boards """

import sys
import argparse
import subprocess
from enum import Enum
from dataclasses import dataclass
from pathlib import Path
import os
import shutil


class Boards(str, Enum):
    BRD4186A = "BRD4186A"
    BRD4186C = "BRD4186C"
    BRD4187A = "BRD4187A"
    BRD4187C = "BRD4187C"
    BRD2601B = "BRD2601B"
    BRD2703A = "BRD2703A"
    BRD2608A = "BRD2608A"
    BRD4116A = "BRD4116A"
    BRD4117A = "BRD4117A"
    BRD4118A = "BRD4118A"
    BRD2709A = "BRD2709A"
    BRD2704A = "BRD2704A"
    BRD4316A = "BRD4316A"
    BRD4317A = "BRD4317A"
    BRD4318A = "BRD4318A"
    BRD4319A = "BRD4319A"
    BRD4350A = "BRD4350A"
    BRD4351A = "BRD4351A"
    ALL = "ALL"

    @classmethod
    def is_board(boards, board) -> bool:
        if isinstance(board, boards):
            board = board.value
        if board not in boards.__members__:
            return False
        else:
            return True


class Family(str, Enum):
    MG26 = "efr32mg26"
    MG24 = "efr32mg24"
    MGM24 = "mgm24"
    MGM26 = "mgm26"


class BoardDict(dict):
    def __setitem__(self, key, value):
        if not isinstance(key, Boards):
            raise KeyError("Key must be an instance of MyEnum")
        super().__setitem__(key, value)

    def __getitem__(self, key):
        if not isinstance(key, Boards):
            raise KeyError("Key must be an instance of MyEnum")
        return super().__getitem__(key)


@dataclass
class Board:
    board: Boards
    slc_arguments: str
    family: Family


class InvalidInput(Exception):
    def __init__(self, message):
        super().__init__(message)


# Configuring slc arguments per board
_boards = BoardDict()
_boards[Boards.BRD4186A] = Board(board=Boards.BRD4186A, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4186a")
_boards[Boards.BRD4186C] = Board(board=Boards.BRD4186C, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4186a")
_boards[Boards.BRD4187A] = Board(board=Boards.BRD4187A, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4186c")
_boards[Boards.BRD4187C] = Board(board=Boards.BRD4187C, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4187c")
_boards[Boards.BRD2601B] = Board(board=Boards.BRD2601B, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,i2cspm:sensor,brd2601b")
_boards[Boards.BRD2703A] = Board(board=Boards.BRD2703A, family=Family.MG24,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,brd2703a")
_boards[Boards.BRD2704A] = Board(board=Boards.BRD2704A, family=Family.MGM24,
                                 slc_arguments="simple_led:led0,uartdrv_eusart:vcom,brd2704a")
_boards[Boards.BRD4316A] = Board(board=Boards.BRD4316A, family=Family.MGM24,
                                 slc_arguments="simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,brd4316a")
_boards[Boards.BRD4317A] = Board(board=Boards.BRD4317A, family=Family.MGM24,
                                 slc_arguments="simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,i2cspm:sensor,memlcd_usart,dmd_memlcd,brd4317a")
_boards[Boards.BRD4318A] = Board(board=Boards.BRD4318A, family=Family.MGM24,
                                 slc_arguments="simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,i2cspm:sensor,memlcd_usart,dmd_memlcd,brd4318a")
_boards[Boards.BRD4319A] = Board(board=Boards.BRD4319A, family=Family.MGM24,
                                 slc_arguments="simple_button:btn0:btn1,uartdrv_eusart:vcom,brd4319a")
_boards[Boards.BRD4116A] = Board(board=Boards.BRD4116A, family=Family.MG26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4116a")
_boards[Boards.BRD2709A] = Board(board=Boards.BRD2709A, family=Family.MG26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,brd2709a")
_boards[Boards.BRD4117A] = Board(board=Boards.BRD4117A, family=Family.MG26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4117a")
_boards[Boards.BRD4118A] = Board(board=Boards.BRD4118A, family=Family.MG26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,memlcd_usart,dmd_memlcd,i2cspm:sensor,brd4118a")
_boards[Boards.BRD2608A] = Board(board=Boards.BRD2608A, family=Family.MG26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,mx25_flash_shutdown_usart,i2cspm:sensor,brd2608a")
_boards[Boards.BRD4350A] = Board(board=Boards.BRD4350A, family=Family.MGM26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,i2cspm:sensor,brd4350a")
_boards[Boards.BRD4351A] = Board(board=Boards.BRD4351A, family=Family.MGM26,
                                 slc_arguments="simple_led:led0:led1,simple_button:btn0:btn1,uartdrv_eusart:vcom,i2cspm:sensor,brd4350a")


def _parse_args():
    """Parses and returns the command line arguments"""

    parser = argparse.ArgumentParser(description="Script to generate slc autogen and configuration files.",
                                     formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument("--sdk", metavar="si_sdk_path", required=False, default="../simplicity_sdk",
                        help="Path to Si SDK to use to generate the slc autogen and configuration files.")
    parser.add_argument("--slcp", metavar="slcp_path", required=False,
                        default="../../../examples/platform/silabs/matter-platform.slcp", help="Path to project slcp to use to generate slc files.")
    parser.add_argument("--board", metavar="board", required=False, default="all",
                        help="Board for which to generaten autogen and configuration files.")
    parser.add_argument("--output", metavar="output_path", required=False, default="matter/efr32",
                        help="Directory where the board genenration will be created. Fomart: ./family/board/output")
    parser.add_argument("--delete-files", metavar="delete-files", required=False, type=_convertStrToBool, default=True,
                        help="Option to delete files step for each generation.")
    parser.add_argument("--revert-changes", metavar="revert-changes", required=False, type=_convertStrToBool, default=False,
                        help="Option to revert changes to all files that changed. Should only be used after validating the changes aren't necessary.")

    return parser.parse_args()


def _convertStrToBool(value):
    """
    Converts a string representation of truth to a boolean value.

    Args:
        value (str or bool): The value to convert. Can be a string like 'yes', 'true', 't', 'y', '1' for True,
                             or 'no', 'false', 'f', 'n', '0' for False. If the value is already a boolean, it is returned as is.

    Returns:
        bool: The corresponding boolean value.

    Raises:
        argparse.ArgumentTypeError: If the string value does not match any of the expected true/false values.
    """
    if isinstance(value, bool):
        return value
    if value.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif value.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Boolean value expected.')


def _configure_sdk(si_sdk_path):
    """
    Configures slc sdk permissions to enable generation
    """
    subprocess.run(["slc", "configuration", "--sdk", si_sdk_path], check=True)
    subprocess.run(["slc", "signature", "trust", "--sdk", si_sdk_path], check=True)


def _generate_slc(args):
    """
    Main application function

    Args:
        args (Namespace): The arguments passed to the function. It should contain:
                          - board (str): The name of the board to generate the SLC for.
                          - sdk (str): The path to the SI SDK.
                          - slcp (str): The path to the SLCP.
                          - output (str): The path where the output should be saved.
                          - delete_files (bool): A flag indicating whether to delete files after generation.

    Raises:
        InvalidInput: If the specified board is not part of the supported boards.

    """

    if args.board not in Boards.__members__:
        raise InvalidInput("Board is not part of the supported boards!")

    board = Boards(args.board)

    if board == Boards.ALL:
        _generate_all_boards(si_sdk_path=args.sdk, slcp_path=args.slcp, output_path=args.output,
                             delete_files=args.delete_files, revert_changes=args.revert_changes)
    else:
        _generate_board(board=_boards[board], si_sdk_path=args.sdk, slcp_path=args.slcp,
                        output_path=args.output, delete_files=args.delete_files, revert_changes=args.revert_changes)


def _generate_all_boards(si_sdk_path: str, slcp_path: str, output_path: str, delete_files: bool, revert_changes: bool):
    """
    Generates slc files for all supported boards.

    Args:
        si_sdk_path (str): The path to the SI SDK.
        slcp_path (str): The path to the SLCP.
        output_path (str): The path where the output should be saved.
        delete_files (bool): A flag indicating whether to delete files after generation.
        revert_changes (bool); A flag indicating whether to revert changes after generation
    """

    for board in _boards:
        _generate_board(board=_boards[board], si_sdk_path=si_sdk_path,
                        slcp_path=slcp_path, output_path=output_path, delete_files=delete_files, revert_changes=revert_changes)


def _generate_board(board: Board, si_sdk_path: str, slcp_path: str, output_path: str, delete_files: bool, revert_changes: bool):
    """
    Generates the SLC (System Level Configuration) for a specific board.

    Args:
        board (Board): The board for which the SLC is to be generated.
        si_sdk_path (str): The path to the SI SDK.
        slcp_path (str): The path to the SLCP.
        output_path (str): The path where the output should be saved.
        delete_files (bool): A flag indicating whether to delete files after generation.
        revert_changes (bool); A flag indicating whether to revert changes after generation
    """

    # Configure path variables
    si_sdk_path = Path(si_sdk_path)
    slcp_path = Path(slcp_path)
    output_path = Path(output_path)
    output_path = os.path.join(output_path, board.family.value, board.board.value)

    # run slc generate command
    subprocess.run(["slc", "generate", slcp_path, "-d", output_path, "--with", board.slc_arguments], check=True)

    # delete files generated files
    if delete_files:
        _delete_files(output_path)
        _delete_directories(output_path)

    # Revert changes
    if revert_changes:
        _revert_changes(output_path)


def _delete_files(output_path: Path):
    """
    Deletes specified files from the output path after each generation.

    Args:
        output_path (Path): The path where the files to be deleted are located.

    """

    # Files to delete after each generation
    files_to_delete = ["autogen/.crc_config.crc",
                       "autogen/linkerfile.ld",
                       "config/prioconf/priority_config.prioconf",
                       "config/FreeRTOSConfig.h",
                       "config/SEGGER_RTT_Conf.h",
                       "config/sl_openthread_ble_cli_config.h",
                       "config/sl_openthread_generic_config.h",
                       "config/sl_debug_swo_config.h",
                       "matter-platform.Makefile",
                       "matter-platform.project.mak",
                       "vscode.conf"]

    # Loop and delete files if they exist
    for file_name in files_to_delete:
        path = os.path.join(output_path, file_name)
        if os.path.isfile(path):
            os.remove(path)
            print(f"{path} has been deleted.")
        else:
            print(f"{path} does not exist.")


def _delete_directories(output_path: Path):
    """
    Deletes specified directories from the output path after each generation.

    Args:
        output_path (Path): The path where the directories to be deleted are located.

    """
    # Directories to delete after each generation
    directories_to_delete = ["linker_options",
                             "matter-platform_cmake"]

    # Loop and delete directories if they exist
    for dir_path in directories_to_delete:
        path = os.path.join(output_path, dir_path)
        if os.path.isdir(path):
            shutil.rmtree(path)
            print(f"{path} and its contents have been deleted.")
        else:
            print(f"{path} does not exist or is not a directory.")


def _revert_changes(output_path: Path):
    """
    Reverts changes to specified files in the output path using Git.

    Args:
        output_path (Path): The path where the files to be reset are located.

    """
    files_to_reset = ["autogen/gatt_db.h",
                      "autogen//sl_component_catalog.h",
                      "autogen/sl_simple_led_instances.h",
                      "autogen/sl_event_handler.c",
                      "autogen/sl_event_handler.h",
                      "autogen/sl_ot_init.c",
                      "autogen/sli_mbedtls_config_autogen.h",
                      "autogen/sli_psa_builtin_config_autogen.h",
                      ]

    for file in files_to_reset:
        path = os.path.join(output_path, file)
        try:
            subprocess.run(['git', 'checkout', '--', path], check=True)
            print(f"Changes removed for {path}")
        except subprocess.CalledProcessError as e:
            print(f"Failed to remove changes for {path}: {e}")


def main(args) -> int:
    args.board = args.board.upper()

    # Step 1: Configure slc sdk permissions for generation
    _configure_sdk(args.sdk)

    # Step 2: Generate slc files
    _generate_slc(args)


if __name__ == "__main__":
    args = _parse_args()
    sys.exit(main(args))
