#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
#   SPDX-FileCopyrightText: 2014 Anke Boersma <demm@kaosx.us>
#   SPDX-FileCopyrightText: 2014 Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   SPDX-FileCopyrightText: 2014 Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
#   SPDX-FileCopyrightText: 2014-2019 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2015-2018 Philip Mueller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2016-2017 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-FileCopyrightText: 2017 Ben Green <Bezzy1999@hotmail.com>
#   SPDX-FileCopyrightText: 2021 Neal Gompa <ngompa13@gmail.com>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import shutil
import subprocess

import libcalamares

from libcalamares.utils import check_target_env_call


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext

# This is the sanitizer used all over to tidy up filenames
# to make identifiers (or to clean up names to make filenames).
file_name_sanitizer = str.maketrans(" /()", "_-__")

def pretty_name():
    return _("Install bootloader.")


def get_uuid():
    """
    Checks and passes 'uuid' to other routine.

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")

    for partition in partitions:
        if partition["mountPoint"] == "/":
            libcalamares.utils.debug("Root partition uuid: \"{!s}\"".format(partition["uuid"]))
            return partition["uuid"]

    return ""


def get_bootloader_entry_name():
    """
    Passes 'bootloader_entry_name' to other routine based
    on configuration file.

    :return:
    """
    if "bootloaderEntryName" in libcalamares.job.configuration:
        return libcalamares.job.configuration["bootloaderEntryName"]
    else:
        branding = libcalamares.globalstorage.value("branding")
        return branding["bootloaderEntryName"]


def create_systemd_boot_conf(installation_root_path, efi_dir, uuid, entry, kernel, kernel_type, kernel_version):
    """
    Creates systemd-boot configuration files based on given parameters.

    :param installation_root_path: A string containing the absolute path to the root of the installation
    :param efi_dir: A string containing the path to the efi dir relative to the root of the installation
    :param uuid: A string containing the UUID of the root volume
    :param entry: A string containing the name of the entry as it will be displayed on boot
    :param kernel: A string containing the path to the kernel relative to the root of the installation
    :param kernel_type: A string which should be set if there is a special version of the entry, for example "fallback"
    :param kernel_version: The kernel version string
    """
    kernel_params = ["quiet"]

    partitions = libcalamares.globalstorage.value("partitions")
    swap_uuid = ""
    swap_outer_mappername = None

    cryptdevice_params = []

    # Take over swap settings:
    #  - unencrypted swap partition sets swap_uuid
    #  - encrypted root sets cryptdevice_params
    for partition in partitions:
        if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
            continue
        has_luks = "luksMapperName" in partition
        if partition["fs"] == "linuxswap" and not has_luks:
            swap_uuid = partition["uuid"]

        if (partition["fs"] == "linuxswap" and has_luks):
            swap_outer_mappername = partition["luksMapperName"]

        if partition["mountPoint"] == "/" and has_luks:
            cryptdevice_params = ["cryptdevice=UUID="
                                  + partition["luksUuid"]
                                  + ":"
                                  + partition["luksMapperName"],
                                  "root=/dev/mapper/"
                                  + partition["luksMapperName"]]

    # systemd-boot with a BTRFS root filesystem needs to be told
    # about the root subvolume.
    for partition in partitions:
        if partition["mountPoint"] == "/" and partition["fs"] == "btrfs":
            kernel_params.append("rootflags=subvol=@")

    if cryptdevice_params:
        kernel_params.extend(cryptdevice_params)
    else:
        kernel_params.append("root=UUID={!s}".format(uuid))

    if swap_uuid:
        kernel_params.append("resume=UUID={!s}".format(swap_uuid))

    if swap_outer_mappername:
        kernel_params.append("resume=/dev/mapper/{!s}".format(
            swap_outer_mappername))

    libcalamares.utils.debug("Configure: \"{!s}\"".format(f"{entry} {kernel_version}"))

    if kernel_type == "fallback":
        version_string = kernel_version + "-fallback"
        initrd = "initrd-fallback"
    else:
        version_string = kernel_version
        initrd = "initrd"

    # get the machine-id
    with open(os.path.join(installation_root_path, "etc", "machine-id"), 'r') as machineid_file:
        machine_id = machineid_file.read().rstrip('\n')

    # Copy kernel to a subdirectory of /efi partition
    machine_dir = os.path.join(installation_root_path + efi_dir, machine_id)
    os.makedirs(machine_dir, exist_ok=True)

    target_efi_files_dir = os.path.join(machine_dir, kernel_version)
    os.makedirs(target_efi_files_dir, exist_ok=True) 
    
    kernel_path = os.path.join(installation_root_path, kernel)
    kernel_name = os.path.basename(kernel_path)
    shutil.copyfile(kernel_path, os.path.join(target_efi_files_dir, "linux"))

    # write the entry
    lines = [
        '## Generated by Calamares\n',
        '\n',
        "title      {!s}\n".format(entry),
        "version    {!s}\n".format(version_string),
        "machine-id {!s}\n".format(machine_id),
        "linux      {!s}\n".format(os.path.join("/", machine_id, kernel_version, "linux")),
    ]

    try:
        additional_initrd_files = libcalamares.job.configuration["additionalInitrdFiles"]
        for initrd_file in additional_initrd_files:
            libcalamares.utils.debug("Attempting to handle initrd image " + initrd_file)
            if os.path.isfile(os.path.join(installation_root_path, initrd_file.lstrip('/'))):
                libcalamares.utils.debug("Found image " + initrd_file)
                shutil.copyfile(os.path.join(installation_root_path, initrd_file.lstrip('/')), os.path.join(target_efi_files_dir, os.path.basename(initrd_file)))
                lines.append("initrd     {!s}\n".format(os.path.join("/", machine_id, kernel_version, os.path.basename(initrd_file))))
    except KeyError: # If the configuration option isn't set, we can just move on
        libcalamares.utils.debug("Failed to find key additionalInitrdFiles")
        pass
    
    lines.append("initrd     {!s}\n".format(os.path.join("/", machine_id, kernel_version, initrd)))
    lines.append("options    {!s} rw\n".format(" ".join(kernel_params)))

    conf_path = os.path.join(installation_root_path + efi_dir,
                             "loader",
                             "entries",
                             machine_id + "-" + version_string + ".conf")
                             
    with open(conf_path, 'w') as conf_file:
        for line in lines:
            conf_file.write(line)


def create_loader(loader_path, entry):
    """
    Writes configuration for loader.

    :param loader_path:
    :param entry:
    """
    timeout = libcalamares.job.configuration["timeout"]
    lines = [
        "timeout {!s}\n".format(timeout),
        "default {!s}\n".format(entry),
    ]

    with open(loader_path, 'w') as loader_file:
        for line in lines:
            loader_file.write(line)


def efi_label():
    if "efiBootloaderId" in libcalamares.job.configuration:
        efi_bootloader_id = libcalamares.job.configuration[
                                "efiBootloaderId"]
    else:
        branding = libcalamares.globalstorage.value("branding")
        efi_bootloader_id = branding["bootloaderEntryName"]

    return efi_bootloader_id.translate(file_name_sanitizer)


def efi_word_size():
    # get bitness of the underlying UEFI
    try:
        sysfile = open("/sys/firmware/efi/fw_platform_size", "r")
        efi_bitness = sysfile.read(2)
    except Exception:
        # if the kernel is older than 4.0, the UEFI bitness likely isn't
        # exposed to the userspace so we assume a 64 bit UEFI here
        efi_bitness = "64"
    return efi_bitness


def efi_boot_next():
    """
    Tell EFI to definitely boot into the just-installed
    system next time.
    """
    boot_mgr = libcalamares.job.configuration["efiBootMgr"]
    boot_entry = None
    efi_bootvars = subprocess.check_output([boot_mgr], text=True)
    for line in efi_bootvars.split('\n'):
        if not line:
            continue
        words = line.split()
        if len(words) >= 2 and words[0] == "BootOrder:":
            boot_entry = words[1].split(',')[0]
            break
    if boot_entry:
        subprocess.call([boot_mgr, "-n", boot_entry])

def get_kernels(installation_root_path):
    """
    Gets a list of kernels and associated values for each kernel.  This will work as is for many distros.
    If not, it should be safe to modify it to better support your distro

    :param installation_root_path: A string with the absolute path to the root of the installation

    Returns a list of 3-tuples

    Each 3-tuple contains the kernel, kernel_type and kernel_version
    """
    kernel_search_path = libcalamares.job.configuration["kernelSearchPath"]
    source_kernel_name = libcalamares.job.configuration["kernelName"]
    kernel_list = []

    # find all the installed kernels and generate default and fallback entries for each
    for root, dirs, files in os.walk(os.path.join(installation_root_path, kernel_search_path.lstrip('/'))): 
        for file in files:  
            if file == source_kernel_name:
                rel_root = os.path.relpath(root, installation_root_path)
                kernel_list.append((os.path.join(rel_root, file),"default",os.path.basename(root)))
                kernel_list.append((os.path.join(rel_root, file),"fallback",os.path.basename(root)))

    return kernel_list

def install_systemd_boot(efi_directory):
    """
    Installs systemd-boot as bootloader for EFI setups.

    :param efi_directory:
    """
    libcalamares.utils.debug("Bootloader: systemd-boot")
    installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = installation_root_path + efi_directory
    uuid = get_uuid()
    distribution = get_bootloader_entry_name()
    distribution_translated = distribution.translate(file_name_sanitizer)
    loader_path = os.path.join(install_efi_directory,
                               "loader",
                               "loader.conf")
    subprocess.call(["bootctl",
                     "--path={!s}".format(install_efi_directory),
                     "install"])

    for (kernel, kernel_type, kernel_version) in get_kernels(installation_root_path):
        create_systemd_boot_conf(installation_root_path,
                                efi_directory,
                                uuid,
                                distribution,
                                kernel,
                                kernel_type,
                                kernel_version)

    create_loader(loader_path, distribution_translated)

def get_grub_efi_parameters():
    """
    Returns a 3-tuple of suitable parameters for GRUB EFI installation,
    depending on the host machine architecture. The return is
        - target name
        - grub.efi name
        - boot.efi name
    all three are strings. May return None if there is no suitable
    set for the current machine. May return unsuitable values if the
    host architecture is unknown (e.g. defaults to x86_64).
    """
    import platform
    efi_bitness = efi_word_size()
    cpu_type = platform.machine()

    if efi_bitness == "32":
        # Assume all 32-bitters are legacy x86
        return ("i386-efi", "grubia32.efi", "bootia32.efi")
    elif efi_bitness == "64" and cpu_type == "aarch64":
        return ("arm64-efi", "grubaa64.efi", "bootaa64.efi")
    elif efi_bitness == "64":
        # If it's not ARM, must by AMD64
        return ("x86_64-efi", "grubx64.efi", "bootx64.efi")
    libcalamares.utils.warning("Could not find GRUB parameters for bits {b} and cpu {c}".format(b=repr(efi_bitness), c=repr(cpu_type)))
    return None


def install_grub(efi_directory, fw_type):
    """
    Installs grub as bootloader, either in pc or efi mode.

    :param efi_directory:
    :param fw_type:
    """
    if fw_type == "efi":
        libcalamares.utils.debug("Bootloader: grub (efi)")
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
        install_efi_directory = installation_root_path + efi_directory

        if not os.path.isdir(install_efi_directory):
            os.makedirs(install_efi_directory)

        efi_bootloader_id = efi_label()

        efi_target, efi_grub_file, efi_boot_file = get_grub_efi_parameters()

        check_target_env_call([libcalamares.job.configuration["grubInstall"],
                               "--target=" + efi_target,
                               "--efi-directory=" + efi_directory,
                               "--bootloader-id=" + efi_bootloader_id,
                               "--force"])

        # VFAT is weird, see issue CAL-385
        install_efi_directory_firmware = (vfat_correct_case(
                                              install_efi_directory,
                                              "EFI"))
        if not os.path.exists(install_efi_directory_firmware):
            os.makedirs(install_efi_directory_firmware)

        # there might be several values for the boot directory
        # most usual they are boot, Boot, BOOT

        install_efi_boot_directory = (vfat_correct_case(
                                          install_efi_directory_firmware,
                                          "boot"))
        if not os.path.exists(install_efi_boot_directory):
            os.makedirs(install_efi_boot_directory)

        # Workaround for some UEFI firmwares
        FALLBACK = "installEFIFallback"
        libcalamares.utils.debug("UEFI Fallback: " + str(libcalamares.job.configuration.get(FALLBACK, "<unset>")))
        if libcalamares.job.configuration.get(FALLBACK, True):
            libcalamares.utils.debug("  .. installing '{!s}' fallback firmware".format(efi_boot_file))
            efi_file_source = os.path.join(install_efi_directory_firmware,
                                        efi_bootloader_id,
                                        efi_grub_file)
            efi_file_target = os.path.join(install_efi_boot_directory,
                                        efi_boot_file)

            shutil.copy2(efi_file_source, efi_file_target)
    else:
        libcalamares.utils.debug("Bootloader: grub (bios)")
        if libcalamares.globalstorage.value("bootLoader") is None:
            return

        boot_loader = libcalamares.globalstorage.value("bootLoader")
        if boot_loader["installPath"] is None:
            return

        check_target_env_call([libcalamares.job.configuration["grubInstall"],
                               "--target=i386-pc",
                               "--recheck",
                               "--force",
                               boot_loader["installPath"]])

    # The input file /etc/default/grub should already be filled out by the
    # grubcfg job module.
    check_target_env_call([libcalamares.job.configuration["grubMkconfig"],
                           "-o", libcalamares.job.configuration["grubCfg"]])


def install_secureboot(efi_directory):
    """
    Installs the secureboot shim in the system by calling efibootmgr.
    """
    efi_bootloader_id = efi_label()

    installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = installation_root_path + efi_directory

    if efi_word_size() == "64":
        install_efi_bin = "shimx64.efi"
    elif efi_word_size() == "32":
        install_efi_bin = "shimia32.efi"

    # Copied, roughly, from openSUSE's install script,
    # and pythonified. *disk* is something like /dev/sda,
    # while *drive* may return "(disk/dev/sda,gpt1)" ..
    # we're interested in the numbers in the second part
    # of that tuple.
    efi_drive = subprocess.check_output([
        libcalamares.job.configuration["grubProbe"],
        "-t", "drive", "--device-map=", install_efi_directory]).decode("ascii")
    efi_disk = subprocess.check_output([
        libcalamares.job.configuration["grubProbe"],
        "-t", "disk", "--device-map=", install_efi_directory]).decode("ascii")

    efi_drive_partition = efi_drive.replace("(","").replace(")","").split(",")[1]
    # Get the first run of digits from the partition
    efi_partition_number = None
    c = 0
    start = None
    while c < len(efi_drive_partition):
        if efi_drive_partition[c].isdigit() and start is None:
            start = c
        if not efi_drive_partition[c].isdigit() and start is not None:
            efi_partition_number = efi_drive_partition[start:c]
            break
        c += 1
    if efi_partition_number is None:
        raise ValueError("No partition number found for %s" % install_efi_directory)

    subprocess.call([
        libcalamares.job.configuration["efiBootMgr"],
        "-c",
        "-w",
        "-L", efi_bootloader_id,
        "-d", efi_disk,
        "-p", efi_partition_number,
        "-l", install_efi_directory + "/" + install_efi_bin])

    efi_boot_next()

    # The input file /etc/default/grub should already be filled out by the
    # grubcfg job module.
    check_target_env_call([libcalamares.job.configuration["grubMkconfig"],
                           "-o", os.path.join(efi_directory, "EFI",
                                              efi_bootloader_id, "grub.cfg")])


def vfat_correct_case(parent, name):
    for candidate in os.listdir(parent):
        if name.lower() == candidate.lower():
            return os.path.join(parent, candidate)
    return os.path.join(parent, name)


def prepare_bootloader(fw_type):
    """
    Prepares bootloader.
    Based on value 'efi_boot_loader', it either calls systemd-boot
    or grub to be installed.

    :param fw_type:
    :return:
    """
    efi_boot_loader = libcalamares.job.configuration["efiBootLoader"]
    efi_directory = libcalamares.globalstorage.value("efiSystemPartition")

    if efi_boot_loader == "systemd-boot" and fw_type == "efi":
        install_systemd_boot(efi_directory)
    elif efi_boot_loader == "sb-shim" and fw_type == "efi":
        install_secureboot(efi_directory)
    elif efi_boot_loader == "grub" or fw_type != "efi":
        install_grub(efi_directory, fw_type)
    else:
        libcalamares.utils.debug( "WARNING: the combination of "
            "boot-loader '{!s}' and firmware '{!s}' "
            "is not supported.".format(efi_boot_loader, fw_type) )


def run():
    """
    Starts procedure and passes 'fw_type' to other routine.

    :return:
    """

    fw_type = libcalamares.globalstorage.value("firmwareType")

    if (libcalamares.globalstorage.value("bootLoader") is None and fw_type != "efi"):
        libcalamares.utils.warning( "Non-EFI system, and no bootloader is set." )
        return None

    partitions = libcalamares.globalstorage.value("partitions")
    if fw_type == "efi":
        efi_system_partition = libcalamares.globalstorage.value("efiSystemPartition")
        esp_found = [ p for p in partitions if p["mountPoint"] == efi_system_partition ]
        if not esp_found:
            libcalamares.utils.warning( "EFI system, but nothing mounted on {!s}".format(efi_system_partition) )
            return None

    try:
        prepare_bootloader(fw_type)
    except subprocess.CalledProcessError as e:
        libcalamares.utils.warning(str(e))
        libcalamares.utils.debug("stdout:" + str(e.stdout))
        libcalamares.utils.debug("stderr:" + str(e.stderr))
        return (_("Bootloader installation error"),
                _("The bootloader could not be installed. The installation command <pre>{!s}</pre> returned error code {!s}.")
                .format(e.cmd, e.returncode))

    return None
