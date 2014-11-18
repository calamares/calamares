#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
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


def detect_firmware_type():
    # Check for EFI variables support
    if(os.path.exists("/sys/firmware/efi/efivars")):
        fw_type = 'efi'
    else:
        fw_type = 'bios'

    libcalamares.globalstorage.insert("firmwareType", fw_type)
    libcalamares.utils.debug("Firmware type: {!s}".format(fw_type))


def install_grub(boot_loader, fw_type):
    if fw_type == 'efi':
        efi_directory = "/boot/efi"
        branding = libcalamares.globalstorage.value("branding")
        distribution = branding["shortProductName"]
        file_name_sanitizer = str.maketrans(" /", "_-")
        check_chroot_call([libcalamares.job.configuration["grubInstall"], "--target=x86_64-efi", "--efi-directory={!s}".format(efi_directory), "--bootloader-id={!s}".format(distribution.translate(file_name_sanitizer))])
    else:
        install_path = boot_loader["installPath"]
        check_chroot_call([libcalamares.job.configuration["grubInstall"], install_path])

    check_chroot_call([libcalamares.job.configuration["grubMkconfig"], "-o", libcalamares.job.configuration["grubCfg"]])


def run():
    detect_firmware_type()
    boot_loader = libcalamares.globalstorage.value("bootLoader")
    fw_type = libcalamares.globalstorage.value("firmwareType")
    install_grub(boot_loader, fw_type)
    return None
