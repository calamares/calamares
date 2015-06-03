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

from libcalamares.utils import check_chroot_call


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


def create_conf(uuid, conf_path, kernel_line):
    """ Creates gummiboot configuration files based on given parameters.

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
        "title   {!s}{!s}\n".format(distribution,kernel_line),
        "linux   {!s}\n".format(kernel),
        "initrd  {!s}\n".format(img),
        "options root=UUID={!s} quiet resume=UUID={!s} rw\n".format(uuid, swap),
    ]

    with open(conf_path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()


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
    f.close()


def install_gummiboot(efi_directory):
    """ Installs gummiboot as bootloader for EFI setups.

    :param efi_directory:
    """
    print("Bootloader: gummiboot")
    install_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = install_path + efi_directory
    fallback_kernel_line = libcalamares.job.configuration["fallbackKernelLine"]
    uuid = get_uuid()
    distribution = get_bootloader_entry_name()
    file_name_sanitizer = str.maketrans(" /", "_-")
    distribution_translated = distribution.translate(file_name_sanitizer)
    conf_path = os.path.join(
        install_efi_directory, "loader", "entries",
        "{!s}.conf".format(distribution_translated))
    fallback_path = os.path.join(
        install_efi_directory, "loader", "entries",
        "{!s}-fallback.conf".format(distribution_translated))
    loader_path = os.path.join(
        install_efi_directory, "loader", "loader.conf")
    subprocess.call(["gummiboot", "--path={!s}".format(install_efi_directory), "install"])
    kernel_line = get_kernel_line("default")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_conf(uuid, conf_path, kernel_line)
    kernel_line = get_kernel_line("fallback")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_conf(uuid, fallback_path, kernel_line)
    create_loader(loader_path)


def install_grub(efi_directory, fw_type):
    """ Installs grub as bootloader, either in pc or efi mode.

    :param efi_directory:
    :param fw_type:
    """
    if fw_type == "efi":
        print("Bootloader: grub (efi)")
        efi_directory_firmware = efi_directory + "/EFI"
        check_chroot_call(["mkdir", "-p", "{!s}".format(efi_directory)])
        if "efiBootloaderId" in libcalamares.job.configuration:
            efi_bootloader_id = libcalamares.job.configuration["efiBootloaderId"]
        else:
            branding = libcalamares.globalstorage.value("branding")
            distribution = branding["bootloaderEntryName"]
            file_name_sanitizer = str.maketrans(" /", "_-")
            efi_bootloader_id = distribution.translate(file_name_sanitizer)
        check_chroot_call(
            [libcalamares.job.configuration["grubInstall"], "--target=x86_64-efi",
             "--efi-directory={!s}".format(efi_directory),
             "--bootloader-id={!s}".format(efi_bootloader_id),
             "--force"])
        # Workaround for some UEFI firmwares
        check_chroot_call(["mkdir", "-p", "{!s}/boot".format(efi_directory_firmware)])
        check_chroot_call(["cp", "{!s}/{!s}/grubx64.efi".format(efi_directory_firmware,
                                                                efi_bootloader_id),
                           "{!s}/boot/bootx64.efi".format(efi_directory_firmware)])
    else:
        print("Bootloader: grub (bios)")
        boot_loader = libcalamares.globalstorage.value("bootLoader")
        check_chroot_call(
            [libcalamares.job.configuration["grubInstall"], "--target=i386-pc",
             "--recheck", "--force", boot_loader["installPath"]])

    check_chroot_call([libcalamares.job.configuration["grubMkconfig"], "-o",
                       libcalamares.job.configuration["grubCfg"]])


def prepare_bootloader(fw_type):
    """ Prepares bootloader and set proper flags to EFI boot partition (esp,boot).
    Based on value 'efi_boot_loader', it either calls gummiboot or grub to be installed.

    :param fw_type:
    :return:
    """
    efi_boot_loader = libcalamares.job.configuration["efiBootLoader"]
    efi_directory = libcalamares.globalstorage.value("efiSystemPartition")
    if fw_type == "efi":
        partitions = libcalamares.globalstorage.value("partitions")
        boot_p = ""
        device = ""
        efi_partition_found = False
        for partition in partitions:
            if partition["mountPoint"] == efi_directory:
                efi_partition_found = True
                boot_device = partition["device"]
                boot_p = boot_device[-1:]
                device = boot_device[:-1]
                if (not boot_p or not device):
                    return ("EFI directory \"{!s}\" not found!",
                            "Boot partition: \"{!s}\"",
                            "Boot device: \"{!s}\"".format(efi_directory,boot_p,device))
                else:
                    print("EFI directory: \"{!s}\"".format(efi_directory))
                    print("Boot partition: \"{!s}\"".format(boot_p))
                    print("Boot device: \"{!s}\"".format(device))
        if efi_partition_found == True:
            print("Set 'EF00' flag")
            subprocess.call(["sgdisk", "--typecode={!s}:EF00".format(boot_p), "{!s}".format(device)])
        else:
            print("Warning: There's no efi system partition selected!")
            print("Bootloader installation will probably fail!")

    if (efi_boot_loader == "gummiboot" and fw_type == "efi"):
        install_gummiboot(efi_directory)
    else:
        install_grub(efi_directory, fw_type)


def run():
    """ Starts procedure and passes 'fw_type' to other routine.

    :return:
    """
    fw_type = libcalamares.globalstorage.value("firmwareType")
    prepare_bootloader(fw_type)
    return None
