#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2014, Anke Boersma <demm@kaosx.us>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
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


def detect_firmware_type():
    # Check for EFI variables support
    if(os.path.exists("/sys/firmware/efi/efivars")):
        fw_type = 'efi'
    else:
        fw_type = 'bios'

    libcalamares.globalstorage.insert("firmwareType", fw_type)
    libcalamares.utils.debug("Firmware type: {!s}".format(fw_type))


def get_uuid():
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    print(root_mount_point)
    partitions = libcalamares.globalstorage.value("partitions")
    print(partitions)
    for partition in partitions:
        if partition["mountPoint"] == "/":
            print(partition["uuid"])
            return partition["uuid"]
    return ""


def create_conf(uuid, conf_path):
    branding = libcalamares.globalstorage.value("branding")
    distribution = branding["productName"]
    kernel = libcalamares.job.configuration["kernel"]
    img = libcalamares.job.configuration["img"]
    partitions = libcalamares.globalstorage.value("partitions")
    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap = partition["uuid"]
        else:
            swap = ""
    lines = [
        '## This is just an exmaple config file.\n',
        '## Please edit the paths and kernel parameters according to your system.\n',
        '\n',
        'title   %s GNU/Linux, with Linux core repo kernel\n' % distribution,
        'linux   %s\n' % kernel,
        'initrd  %s\n' % img,
        'options root=UUID=%s quiet resume=%s rw\n' % (uuid, swap),
    ]

    with open(conf_path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()


def create_fallback(uuid, fallback_path):
    branding = libcalamares.globalstorage.value("branding")
    distribution = branding["productName"]
    kernel = libcalamares.job.configuration["kernel"]
    fb_img = libcalamares.job.configuration["fallback"]
    partitions = libcalamares.globalstorage.value("partitions")
    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap = partition["uuid"]
        else:
            swap = ""
    lines = [
        '## This is just an exmaple config file.\n',
        '## Please edit the paths and kernel parameters according to your system.\n',
        '\n',
        'title   %s GNU/Linux, with Linux fallback kernel\n' % distribution,
        'linux   %s\n' % kernel,
        'initrd  %s\n' % fb_img,
        'options root=UUID=%s quiet resume=%s rw\n' % (uuid, swap),
    ]

    with open(fallback_path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()


def create_loader(loader_path):
    branding = libcalamares.globalstorage.value("branding")
    distribution = branding["productName"]
    timeout = libcalamares.job.configuration["timeout"]
    lines = [
        'timeout %s\n' % timeout,
        'default %s\n' % distribution,
    ]

    with open(loader_path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()


def install_bootloader(boot_loader, fw_type):
    if fw_type == 'efi':
        install_path = libcalamares.globalstorage.value("rootMountPoint")
        uuid = get_uuid()
        branding = libcalamares.globalstorage.value("branding")
        distribution = branding["productName"]
        conf_path = os.path.join(
            install_path, "boot", "loader", "entries", "%s.conf" % distribution)
        fallback_path = os.path.join(
            install_path, "boot", "loader", "entries", "%s-fallback.conf" % distribution)
        loader_path = os.path.join(
            install_path, "boot", "loader", "loader.conf")
        partitions = libcalamares.globalstorage.value("partitions")
        for partition in partitions:
            if partition["mountPoint"] == "/boot":
                print(partition["device"])
                boot_device = partition["device"]
                boot_p = boot_device[-1:]
                device = boot_device[:-1]
                print(device)
        subprocess.call(['sgdisk', '--typecode=%s:EF00 %s' % (boot_p, device)])
        subprocess.call(
            ["gummiboot", "--path=%s/boot" % install_path, "install"])
        create_conf(uuid, conf_path)
        create_fallback(uuid, fallback_path)
        create_loader(loader_path)
    else:
        install_path = boot_loader["installPath"]
        check_chroot_call(
            [libcalamares.job.configuration["grubInstall"], install_path])
        check_chroot_call([libcalamares.job.configuration[
                          "grubMkconfig"], "-o", libcalamares.job.configuration["grubCfg"]])


def run():
    detect_firmware_type()
    boot_loader = libcalamares.globalstorage.value("bootLoader")
    fw_type = libcalamares.globalstorage.value("firmwareType")
    install_bootloader(boot_loader, fw_type)
    return None
