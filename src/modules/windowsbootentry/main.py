#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#   SPDX-License-Identifier: GPL-3.0-or-later
#

import fileinput
import os
import shutil
import subprocess
import tempfile

import libcalamares

from libcalamares.utils import check_target_env_call
from libcalamares.utils import check_target_env_output

import gettext

_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Install bootloader.")


def handle_systemdboot(efi_directory):
    """
    For systemd-boot, we copy the Microsoft EFI entry to the EFI partition where systemd-boot is installed
    """

    # Get the root mount point and build the full path to the mounted ESP
    try:
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    except KeyError:
        libcalamares.utils.warning('Global storage value "rootMountPoint" missing')

    install_efi_directory = installation_root_path + efi_directory

    # espList holds the list of EFI partitions from the partition module
    try:
        efi_partition_list = libcalamares.globalstorage.value("espList")
    except KeyError:
        libcalamares.utils.warning("No ESP list in global storage")
        return None

    # Get the partitions from global storage
    try:
        partitions = libcalamares.globalstorage.value("partitions")
    except KeyError:
        libcalamares.utils.warning("partitions missing from global storage")
        return None

    # Iterate over the partitions and search for an EFI partition containing the Microsoft data
    for partition in partitions:
        try:
            if partition["device"] in efi_partition_list and partition["mountPoint"] != efi_directory:
                libcalamares.utils.debug(f"Found foreign efi at {partition['device']}")
                temp_path = tempfile.mkdtemp()
                libcalamares.utils.debug(f"Attempting to mount {partition['device'].strip()} at {temp_path}")
                libcalamares.utils.host_env_process_output(["mount", partition["device"].strip(), temp_path])
                source_path = os.path.join(temp_path, "EFI", "Microsoft")
                if os.path.isdir(source_path):
                    target_path = os.path.join(install_efi_directory, "EFI", "Microsoft")
                    shutil.copytree(source_path, target_path)
                libcalamares.utils.host_env_process_output(["umount", temp_path])
        except KeyError:
            pass
        except subprocess.CalledProcessError:
            libcalamares.utils.warning("Failed to mount foreign EFI dir")
            pass
        except shutil.Error:
            libcalamares.utils.warning("Failed to copy Windows files from foreign EFI dir")
            pass


def enable_osprober(installation_root_path, enable):
    """
    Enabled or disabled os-prober in the target based on the value of the enable parameter
    """

    # Update the config in the file to enable or disable os-prober
    for line in fileinput.input(os.path.join(installation_root_path, "etc/default/grub"), inplace=True):
        line = line.strip()
        if line.startswith("#GRUB_DISABLE_OS_PROBER=false") and enable:
            print(line.lstrip("#"))
        if line.startswith("GRUB_DISABLE_OS_PROBER=false") and not enable:
            print("#" + line)
        print(line)


def write_grub_config(installation_root_path, filename, entry):
    """
    Creates a custom grub entry with the data found in "entry" with the name "filename"
    """

    conf_path = os.path.join(installation_root_path, "etc", "grub.d", filename)
    with open(conf_path, 'w') as conf_file:
        conf_file.write("#!/bin/sh\n")
        conf_file.write("exec tail -n +3 $0\n\n")
        conf_file.writelines(entry)

    return None


def handle_grub():
    """
    Enables os-prober and checks for a windows entry.  If it finds one, it is written to /etc/grub.d/45_eos_windows.
    """

    # Get the root mount point
    try:
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    except KeyError:
        libcalamares.utils.warning('Global storage value "rootMountPoint" missing')
        return None

    enable_osprober(installation_root_path, True)

    mkconfig_output = check_target_env_output(["grub-mkconfig"])

    # Find the contents of the entry
    found_osprober = False
    found_windows = False
    for line in mkconfig_output.splitlines():
        if line.strip() == "### BEGIN /etc/grub.d/30_os-prober ###":
            found_osprober = True
        elif "menuentry" in line and "Windows" in line and found_osprober:
            found_windows = True
            entry = [line]
        elif found_windows and found_osprober:
            entry.append(line)
            if line.strip().startswith("}"):
                break

    if found_windows:
        write_grub_config(installation_root_path, "45_eos_windows", entry)
    else:
        libcalamares.utils.debug("No Windows entry found by os-prober")

    # We are done, disable os-prober
    enable_osprober(installation_root_path, False)
    return None


def run():
    fw_type = libcalamares.globalstorage.value("firmwareType")

    partitions = libcalamares.globalstorage.value("partitions")
    efi_directory = libcalamares.globalstorage.value("efiSystemPartition")
    if fw_type == "efi":
        esp_found = [p for p in partitions if p["mountPoint"] == efi_directory]
        if not esp_found:
            libcalamares.utils.warning(f"EFI system, but nothing mounted on {efi_directory}")
            return None

    # Get the boot loader selection from global storage if it is set in the config file
    try:
        gs_name = libcalamares.job.configuration["bootLoaderVar"]
        boot_loader = libcalamares.globalstorage.value(gs_name)
    except KeyError:
        libcalamares.utils.warning(
            f"Specified global storage value not found in global storage")
        return None

    # If the user has selected not to install bootloader, bail out here
    if boot_loader.casefold() == "none":
        libcalamares.utils.debug("No bootloader selecting, skipping Windows boot entry creation")
        return None

    if boot_loader == "systemd-boot":
        handle_systemdboot(efi_directory)
    elif boot_loader == "grub":
        handle_grub()
    else:
        libcalamares.utils.debug(f"No manual Windows entry creation available for {boot_loader}")

    return None
