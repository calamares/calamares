#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2014, Anke Boersma <demm@kaosx.us>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
#   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
#   Copyright 2015, Philip Mueller <philm@manjaro.org>
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.

import libcalamares

import os
import subprocess

from libcalamares.utils import check_target_env_call


def get_uuid():
    """ Checks and passes 'uuid' to other routine.

    :return:
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    print("Root mount point: \"{!s}\"".format(root_mount_point))
    partitions = libcalamares.globalstorage.value("partitions")
    print("Partitions: \"{!s}\"".format(partitions))

    for partition in partitions:
        if partition["mountPoint"] == "/":
            print("Root partition uuid: \"{!s}\"".format(partition["uuid"]))
            return partition["uuid"]

    return ""


def get_bootloader_entry_name():
    """ Passes 'bootloader_entry_name' to other routine based on configuration file.

    :return:
    """
    if "bootloaderEntryName" in libcalamares.job.configuration:
        return libcalamares.job.configuration["bootloaderEntryName"]
    else:
        branding = libcalamares.globalstorage.value("branding")
        return branding["bootloaderEntryName"]


def get_kernel_line(kernel_type):
    """ Passes 'kernel_line' to other routine based on configuration file.

    :param kernel_type:
    :return:
    """
    if kernel_type == "fallback":
        if "fallbackKernelLine" in libcalamares.job.configuration:
            return libcalamares.job.configuration["fallbackKernelLine"]
        else:
            return " (fallback)"
    else:
        if "kernelLine" in libcalamares.job.configuration:
            return libcalamares.job.configuration["kernelLine"]
        else:
            return ""


def create_systemd_boot_conf(uuid, conf_path, kernel_line):
    """ Creates systemd-boot configuration files based on given parameters.

    :param uuid:
    :param conf_path:
    :param kernel_line:
    """
    distribution = get_bootloader_entry_name()
    kernel = libcalamares.job.configuration["kernel"]
    img = libcalamares.job.configuration["img"]
    partitions = libcalamares.globalstorage.value("partitions")
    swap = ""

    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap = partition["uuid"]

    lines = [
        '## This is just an example config file.\n',
        '## Please edit the paths and kernel parameters according to your system.\n',
        '\n',
        "title   {!s}{!s}\n".format(distribution, kernel_line),
        "linux   {!s}\n".format(kernel),
        "initrd  {!s}\n".format(img),
        "options root=UUID={!s} quiet resume=UUID={!s} rw\n".format(uuid, swap),
    ]

    with open(conf_path, 'w') as f:
        for l in lines:
            f.write(l)


def create_loader(loader_path):
    """ Writes configuration for loader.

    :param loader_path:
    """
    distribution = get_bootloader_entry_name()
    timeout = libcalamares.job.configuration["timeout"]
    file_name_sanitizer = str.maketrans(" /", "_-")
    distribution_translated = distribution.translate(file_name_sanitizer)
    lines = [
        "timeout {!s}\n".format(timeout),
        "default {!s}\n".format(distribution_translated),
    ]

    with open(loader_path, 'w') as f:
        for l in lines:
            f.write(l)


def install_systemd_boot(efi_directory):
    """ Installs systemd-boot as bootloader for EFI setups.

    :param efi_directory:
    """
    print("Bootloader: systemd-boot")
    install_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = install_path + efi_directory
    fallback_kernel_line = libcalamares.job.configuration["fallbackKernelLine"]
    uuid = get_uuid()
    distribution = get_bootloader_entry_name()
    file_name_sanitizer = str.maketrans(" /", "_-")
    distribution_translated = distribution.translate(file_name_sanitizer)
    conf_path = os.path.join(install_efi_directory, "loader", "entries",
                             "{!s}.conf".format(distribution_translated))
    fallback_path = os.path.join(install_efi_directory, "loader", "entries",
                                 "{!s}-fallback.conf".format(distribution_translated))
    loader_path = os.path.join(install_efi_directory, "loader", "loader.conf")
    subprocess.call(["bootctl", "--path={!s}".format(install_efi_directory), "install"])
    kernel_line = get_kernel_line("default")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_systemd_boot_conf(uuid, conf_path, kernel_line)
    kernel_line = get_kernel_line("fallback")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_systemd_boot_conf(uuid, fallback_path, kernel_line)
    create_loader(loader_path)


def install_grub(efi_directory, fw_type):
    """ Installs grub as bootloader, either in pc or efi mode.

    :param efi_directory:
    :param fw_type:
    """
    if fw_type == "efi":
        print("Bootloader: grub (efi)")
        efi_directory_firmware = efi_directory + "/EFI"
        check_target_env_call(["mkdir", "-p", "{!s}".format(efi_directory)])

        if "efiBootloaderId" in libcalamares.job.configuration:
            efi_bootloader_id = libcalamares.job.configuration["efiBootloaderId"]
        else:
            branding = libcalamares.globalstorage.value("branding")
            distribution = branding["bootloaderEntryName"]
            file_name_sanitizer = str.maketrans(" /", "_-")
            efi_bootloader_id = distribution.translate(file_name_sanitizer)
        # get bitness of the underlying UEFI
        try:
            f = open("/sys/firmware/efi/fw_platform_size", "r")
            efi_bitness = f.read(2)
        except:
            # if the kernel is older than 4.0, the UEFI bitness likely isn't exposed to the userspace
            # so we assume a 64 bit UEFI here
            efi_bitness = "64"
        bitness_translate = {"32": "--target=i386-efi", "64": "--target=x86_64-efi"}
        check_target_env_call([libcalamares.job.configuration["grubInstall"], bitness_translate[efi_bitness],
                           "--efi-directory={!s}".format(efi_directory),
                           "--bootloader-id={!s}".format(efi_bootloader_id),
                           "--force"])
        # Workaround for some UEFI firmwares
        check_target_env_call(["mkdir", "-p", "{!s}/boot".format(efi_directory_firmware)])
        check_target_env_call(["cp", "{!s}/{!s}/grubx64.efi".format(efi_directory_firmware, efi_bootloader_id),
                           "{!s}/boot/bootx64.efi".format(efi_directory_firmware)])
    else:
        print("Bootloader: grub (bios)")
        boot_loader = libcalamares.globalstorage.value("bootLoader")
        check_target_env_call([libcalamares.job.configuration["grubInstall"], "--target=i386-pc",
                           "--recheck", "--force", boot_loader["installPath"]])

    check_target_env_call([libcalamares.job.configuration["grubMkconfig"], "-o",
                       libcalamares.job.configuration["grubCfg"]])


def prepare_bootloader(fw_type):
    """ Prepares bootloader and set proper flags to EFI boot partition (esp,boot).
    Based on value 'efi_boot_loader', it either calls systemd-boot or grub to be installed.

    :param fw_type:
    :return:
    """
    efi_boot_loader = libcalamares.job.configuration["efiBootLoader"]
    efi_directory = libcalamares.globalstorage.value("efiSystemPartition")

    if fw_type == "efi":
        partitions = libcalamares.globalstorage.value("partitions")
        boot_p = ""
        device = ""

        for partition in partitions:
            if partition["mountPoint"] == efi_directory:
                boot_device = partition["device"]
                boot_p = boot_device[-1:]
                device = boot_device[:-1]

                if not boot_p or not device:
                    return ("EFI directory \"{!s}\" not found!".format(efi_directory),
                            "Boot partition: \"{!s}\"".format(boot_p),
                            "Boot device: \"{!s}\"".format(device))
                else:
                    print("EFI directory: \"{!s}\"".format(efi_directory))
                    print("Boot partition: \"{!s}\"".format(boot_p))
                    print("Boot device: \"{!s}\"".format(device))

        if not device:
            print("WARNING: no EFI system partition or EFI system partition mount point not set.")
            print("         >>> no EFI bootloader will be installed <<<")
            return None
        print("Set 'EF00' flag")
        subprocess.call(["sgdisk", "--typecode={!s}:EF00".format(boot_p), "{!s}".format(device)])

    if efi_boot_loader == "systemd-boot" and fw_type == "efi":
        install_systemd_boot(efi_directory)
    else:
        install_grub(efi_directory, fw_type)


def run():
    """ Starts procedure and passes 'fw_type' to other routine.

    :return:
    """
    if libcalamares.globalstorage.value("bootLoader") is None:
        return None

    fw_type = libcalamares.globalstorage.value("firmwareType")
    prepare_bootloader(fw_type)

    return None
