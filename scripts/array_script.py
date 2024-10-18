#!/usr/bin/env python3

import os
import argparse

def list_files(directory):
    """
    Generates a list of files in the given directory with their relative paths.

    Parameters:
    directory (str): The directory to list files from.

    Returns:
    list: A list of file paths relative to the given directory.
    """
    file_list = []
    for root, _, files in os.walk(directory):
        for file in files:
            relative_path = os.path.relpath(os.path.join(root, file), directory)
            file_list.append(relative_path)
    return file_list

def main():
    """
    Parses command line arguments and prints the list of files in the given directory.
    """
    parser = argparse.ArgumentParser(description='Generate a list of files in a directory with their relative paths.')
    parser.add_argument('directory', type=str, help='The directory to list files from.')
    args = parser.parse_args()

    files = list_files(args.directory)
    print(files)

if __name__ == '__main__':
    main()