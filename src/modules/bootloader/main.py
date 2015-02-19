#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2014, Anke Boersma <demm@kaosx.us>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
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
import shutil
import subprocess

from libcalamares.utils import check_chroot_call


def get_uuid():
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
    if "bootloaderEntryName" in libcalamares.job.configuration:
        return libcalamares.job.configuration["bootloaderEntryName"]
    else:
        branding = libcalamares.globalstorage.value("branding")
        return branding["bootloaderEntryName"]


def create_conf(uuid, conf_path, kernel_line):
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
        "title   {!s} GNU/Linux, with {!s}\n".format(distribution,kernel_line),
        "linux   {!s}\n".format(kernel),
        "initrd  {!s}\n".format(img),
        "options root=UUID={!s} quiet resume=UUID={!s} rw\n".format(uuid, swap),
    ]

    with open(conf_path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()


def create_loader(loader_path):
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


def install_bootloader(boot_loader, fw_type):
    if fw_type == 'efi':
        install_path = libcalamares.globalstorage.value("rootMountPoint")
        efi_directory = libcalamares.globalstorage.value("efiSystemPartition")
        install_efi_directory = install_path + efi_directory
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
        partitions = libcalamares.globalstorage.value("partitions")
        boot_p = ""
        device = ""
        for partition in partitions:
            if partition["mountPoint"] == efi_directory:
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
        subprocess.call(["sgdisk", "--typecode={!s}:EF00".format(boot_p), "{!s}".format(device)])
        subprocess.call(["gummiboot", "--path={!s}".format(install_efi_directory), "install"])
        kernel_line = libcalamares.job.configuration("kernelLine")
        fallback_kernel_line = libcalamares.job.configuration("fallbackKernelLine")
        print("Configure: \"{!s}\"".format(kernel_line))
        create_conf(uuid, conf_path, kernel_line)
        print("Configure: \"{!s}\"".format(fallback_kernel_line))
        create_conf(uuid, fallback_path, fallback_kernel_line)
        create_loader(loader_path)
    else:
        install_path = boot_loader["installPath"]
        check_chroot_call(
            [libcalamares.job.configuration["grubInstall"], "--target=i386-pc",
             install_path])
        check_chroot_call([libcalamares.job.configuration["grubMkconfig"], "-o",
                           libcalamares.job.configuration["grubCfg"]])


def run():
    boot_loader = libcalamares.globalstorage.value("bootLoader")
    fw_type = libcalamares.globalstorage.value("firmwareType")
    install_bootloader(boot_loader, fw_type)
    return None
