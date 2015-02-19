#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
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
from libcalamares.utils import check_chroot_call
import subprocess


def install_grub(boot_loader, fw_type):
    if fw_type == 'efi':
        efi_directory = libcalamares.globalstorage.value("efiSystemPartition")
        efi_directory_firmware = efi_directory + "/EFI"
        check_chroot_call(["mkdir", "-p", "{!s}".format(efi_directory)])
        if "efiBootloaderId" in libcalamares.job.configuration:
            efi_bootloader_id = libcalamares.job.configuration["efiBootloaderId"]
        else:
            branding = libcalamares.globalstorage.value("branding")
            distribution = branding["bootloaderEntryName"]
            file_name_sanitizer = str.maketrans(" /", "_-")
            efi_bootloader_id = distribution.translate(file_name_sanitizer)
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
        check_chroot_call(
            [libcalamares.job.configuration["grubInstall"], "--target=x86_64-efi",
             "--efi-directory={!s}".format(efi_directory),
             "--bootloader-id={!s}".format(efi_bootloader_id)])
        # Workaround for some UEFI firmwares
        check_chroot_call(["mkdir", "-p", "{!s}/boot".format(efi_directory_firmware)])
        check_chroot_call(["cp", "{!s}/{!s}/grubx64.efi".format(efi_directory_firmware,
                                                                efi_bootloader_id),
                           "{!s}/boot/bootx64.efi".format(efi_directory_firmware)])
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
    install_grub(boot_loader, fw_type)
    return None
