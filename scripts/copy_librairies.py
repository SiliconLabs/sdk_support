#!/usr/bin/env python3

import os
import shutil
import argparse

def list_files_in_directories(directories, exclude_paths):
    """
    Generates a list of files in the given directories with their relative paths,
    including the parent directory name, excluding specified files and directories.

    Parameters:
    directories (list): A list of directories to list files from.
    exclude_paths (list): A list of file and directory paths to exclude from the list.

    Returns:
    list: A list of file paths relative to the given directories, including the parent directory name.
    """
    file_list = []
    for directory in directories:
        parent_dir_name = os.path.basename(directory)
        for root, _, files in os.walk(directory):
            for file in files:
                relative_path = os.path.relpath(os.path.join(root, file), directory)
                full_path = os.path.join(parent_dir_name, relative_path)
                if not any(os.path.commonpath([full_path, exclude]) == exclude for exclude in exclude_paths):
                    file_list.append(full_path)
    return file_list

def copy_files(source_dir, dest_dir, file_list):
    """
    Copies a list of files from the source directory to the destination directory.

    Parameters:
    source_dir (str): The directory to copy files from.
    dest_dir (str): The directory to copy files to.
    file_list (list): A list of filenames to copy.
    """
    # Create the destination directory if it doesn't exist
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    # Iterate over the list of files to copy
    for file_name in file_list:
        full_file_name = os.path.join(source_dir, file_name)
        # Check if the file exists in the source directory
        if os.path.isfile(full_file_name):
            # Create the destination directory structure if it doesn't exist
            dest_file_path = os.path.join(dest_dir, file_name)
            dest_file_dir = os.path.dirname(dest_file_path)
            if not os.path.exists(dest_file_dir):
                os.makedirs(dest_file_dir)
            # Copy the file to the destination directory
            shutil.copy(full_file_name, dest_file_path)
        else:
            # Print a message if the file is not found
            print(f"File {file_name} not found in {source_dir}")

def main():
    """
    Parses command line arguments and calls the copy_files function.
    """
    # Set up argument parser
    parser = argparse.ArgumentParser(description='Copy files from source directories to a destination directory.')
    parser.add_argument('--sdk', metavar='si_sdk_path', required=False, default='../simplicity_sdk',
                        help='Path to Si SDK to use to take the libraries from.')
    parser.add_argument('--sdk-support', metavar='sdk_support_path', required=False, default='./',
                        help='Path to SDK support directory.')
    args = parser.parse_args()

    # List of directories to look for child files
    directories_to_copy = ['platform', 'protocol']

    # List of files and directories to exclude from copying
    exclude_paths = ['platform/security/sl_component']

    # Generate the list of files to copy from the specified directories
    directories_to_copy_full_path = [os.path.join(args.sdk_support, d) for d in directories_to_copy]
    files_to_copy = list_files_in_directories(directories_to_copy_full_path, exclude_paths)

    # Call the copy_files function with the parsed arguments
    copy_files(args.sdk, args.sdk_support, files_to_copy)

if __name__ == '__main__':
    main()