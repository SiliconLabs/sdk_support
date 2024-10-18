import os
import shutil
import argparse

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
            # Copy the file to the destination directory
            shutil.copy(full_file_name, dest_dir)
        else:
            # Print a message if the file is not found
            print(f"File {file_name} not found in {source_dir}")

def copy_directories(source_dir, dest_dir, dir_list):
    """
    Copies a list of directories from the source directory to the destination directory.

    Parameters:
    source_dir (str): The directory to copy from.
    dest_dir (str): The directory to copy to.
    dir_list (list): A list of directory names to copy.
    """
    # Iterate over the list of directories to copy
    for dir_name in dir_list:
        full_dir_name = os.path.join(source_dir, dir_name)
        dest_dir_name = os.path.join(dest_dir, dir_name)
        # Check if the directory exists in the source directory
        if os.path.exists(full_dir_name):
            # Copy the entire directory to the destination
            shutil.copytree(full_dir_name, dest_dir_name, dirs_exist_ok=True)
        else:
            # Print a message if the directory is not found
            print(f"Directory {dir_name} not found in {source_dir}")

def main():
    """
    Parses command line arguments and calls the copy_files and copy_directories functions.
    """
    # Set up argument parser
    parser = argparse.ArgumentParser(description='Copy files and directories from source to destination.')
    parser.add_argument('--sdk', metavar='si_sdk_path', required=False, default='../simplicity_sdk',
                        help='Path to Si SDK to use take the librairies from.')
    parser.add_argument('--sdk-support', metavar='sdk_support_path', required=False, default='./',
                        help='Path to SDK support directory.')
    args = parser.parse_args()

    # List of files to copy
    files_to_copy = [['librail_config_mgm240sa22vna_iar.a', 'librail_config_mgm240pa32vna_iar.a', 'librail_config_mgm240pb32vnn_gcc.a', 'librail_config_mgm240sd22vna_iar.a', 'librail_config_mgm240l022vnf_iar.a', 'librail_config_mgm240pa22vna_gcc.a',
                      'librail_config_mgm240sa22vna_gcc.a', 'librail_efr32xg24_gcc_release.a', 'librail_efr32xg24_iar_release.a', 'librail_multiprotocol_efr32xg26_iar_release.a', 'librail_multiprotocol_efr32xg26_gcc_release.a', 'librail_multiprotocol_module_efr32xg24_iar_release.a', 'librail_module_efr32xg26_gcc_release.a', 'librail_module_efr32xg26_iar_release.a', 'librail_multiprotocol_module_efr32xg24_gcc_release.a', 'librail_config_mgm240l022vnf_gcc.a', 'librail_config_mgm240pa22vna_iar.a', 'librail_config_mgm240sd22vna_gcc.a', 'librail_config_mgm240pb32vnn_iar.a', 'librail_config_mgm240pa32vna_gcc.a', 'librail_module_efr32xg24_gcc_release.a', 'librail_multiprotocol_module_efr32xg26_iar_release.a', 'librail_multiprotocol_module_efr32xg26_gcc_release.a', 'librail_module_efr32xg24_iar_release.a', 'librail_config_mgm240pb22vna_iar.a', 'librail_multiprotocol_efr32xg24_iar_release.a', 'librail_multiprotocol_efr32xg24_gcc_release.a', 'librail_config_mgm240pb32vna_gcc.a', 'librail_config_mgm240ld22vif_iar.a', 'librail_efr32xg26_gcc_release.a', 'librail_efr32xg26_iar_release.a', 'librail_config_mgm240pa32vnn_iar.a', 'librail_config_mgm240la22vif_iar.a', 'librail_config_mgm240l022vif_gcc.a', 'librail_config_mgm240la22uif_gcc.a', 'librail_config_mgm240sb22vna_gcc.a', 'librail_config_mgm240l022rnf_gcc.a', 'librail_config_mgm240pa32vnn_gcc.a', 'librail_config_mgm240ld22vif_gcc.a', 'librail_config_mgm240pb32vna_iar.a', 'librail_config_mgm240pb22vna_gcc.a', 'librail_config_mgm240l022rnf_iar.a', 'librail_config_mgm240sb22vna_iar.a', 'librail_config_mgm240la22uif_iar.a', 'librail_config_mgm240l022vif_iar.a', 'librail_config_mgm240la22vif_gcc.a']]

    # List of directories to copy
    directories_to_copy = ['platform/emdrv/nvm3/lib', 'dir2', 'dir3']

    # Call the copy_files function with the parsed arguments
    copy_files(args.sdk, args.sdk_support, files_to_copy)

    # Call the copy_directories function with the parsed arguments
    copy_directories(args.sdk, args.sdk_support, directories_to_copy)

if __name__ == '__main__':
    main()