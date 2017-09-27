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
#   Copyright 2016-2017, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
#   Copyright 2017, Adriaan de Groot <groot@kde.org>
#   Copyright 2017, Gabriel Craciunescu <crazy@frugalware.org>
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

import os
import shutil
import subprocess

import libcalamares

from libcalamares.utils import check_target_env_call


def get_uuid():
    """
    Checks and passes 'uuid' to other routine.

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


def get_kernel_line(kernel_type):
    """
    Passes 'kernel_line' to other routine based on configuration file.

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
    """
    Creates systemd-boot configuration files based on given parameters.

    :param uuid:
    :param conf_path:
    :param kernel_line:
    """
    distribution = get_bootloader_entry_name()
    kernel = libcalamares.job.configuration["kernel"]
    img = libcalamares.job.configuration["img"]
    kernel_params = ["quiet"]

    partitions = libcalamares.globalstorage.value("partitions")
    swap_uuid = ""

    cryptdevice_params = []

    # Take over swap settings:
    #  - unencrypted swap partition sets swap_uuid
    #  - encrypted root sets cryptdevice_params
    for partition in partitions:
        has_luks = "luksMapperName" in partition
        if partition["fs"] == "linuxswap" and not has_luks:
            swap_uuid = partition["uuid"]

        if partition["mountPoint"] == "/" and has_luks:
            cryptdevice_params = ["cryptdevice=UUID="
                                  + partition["luksUuid"]
                                  + ":"
                                  + partition["luksMapperName"],
                                  "root=/dev/mapper/"
                                  + partition["luksMapperName"],
                                  "resume=/dev/mapper/"
                                  + partition["luksMapperName"]]

    if cryptdevice_params:
        kernel_params.extend(cryptdevice_params)
    else:
        kernel_params.append("root=UUID={!s}".format(uuid))

    if swap_uuid:
        kernel_params.append("resume=UUID={!s}".format(swap_uuid))

    lines = [
        '## This is just an example config file.\n',
        '## Please edit the paths and kernel parameters according\n',
        '## to your system.\n',
        '\n',
        "title   {!s}{!s}\n".format(distribution, kernel_line),
        "linux   {!s}\n".format(kernel),
        "initrd  {!s}\n".format(img),
        "options {!s} rw\n".format(" ".join(kernel_params)),
    ]

    with open(conf_path, 'w') as conf_file:
        for line in lines:
            conf_file.write(line)


def create_loader(loader_path):
    """
    Writes configuration for loader.

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

    with open(loader_path, 'w') as loader_file:
        for line in lines:
            loader_file.write(line)


def install_systemd_boot(efi_directory):
    """
    Installs systemd-boot as bootloader for EFI setups.

    :param efi_directory:
    """
    print("Bootloader: systemd-boot")
    install_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = install_path + efi_directory
    uuid = get_uuid()
    distribution = get_bootloader_entry_name()
    file_name_sanitizer = str.maketrans(" /", "_-")
    distribution_translated = distribution.translate(file_name_sanitizer)
    conf_path = os.path.join(install_efi_directory,
                             "loader",
                             "entries",
                             distribution_translated + ".conf")
    fallback_path = os.path.join(install_efi_directory,
                                 "loader",
                                 "entries",
                                 distribution_translated + "-fallback.conf")
    loader_path = os.path.join(install_efi_directory,
                               "loader",
                               "loader.conf")
    subprocess.call(["bootctl",
                     "--path={!s}".format(install_efi_directory),
                     "install"])
    kernel_line = get_kernel_line("default")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_systemd_boot_conf(uuid, conf_path, kernel_line)
    kernel_line = get_kernel_line("fallback")
    print("Configure: \"{!s}\"".format(kernel_line))
    create_systemd_boot_conf(uuid, fallback_path, kernel_line)
    create_loader(loader_path)


def install_grub(efi_directory, fw_type):
    """
    Installs grub as bootloader, either in pc or efi mode.

    :param efi_directory:
    :param fw_type:
    """
    if fw_type == "efi":
        print("Bootloader: grub (efi)")
        install_path = libcalamares.globalstorage.value("rootMountPoint")
        install_efi_directory = install_path + efi_directory

        if not os.path.isdir(install_efi_directory):
            os.makedirs(install_efi_directory)

        if "efiBootloaderId" in libcalamares.job.configuration:
            efi_bootloader_id = libcalamares.job.configuration[
                                    "efiBootloaderId"]
        else:
            branding = libcalamares.globalstorage.value("branding")
            distribution = branding["bootloaderEntryName"]
            file_name_sanitizer = str.maketrans(" /", "_-")
            efi_bootloader_id = distribution.translate(file_name_sanitizer)
        # get bitness of the underlying UEFI
        try:
            sysfile = open("/sys/firmware/efi/fw_platform_size", "r")
            efi_bitness = sysfile.read(2)
        except Exception:
            # if the kernel is older than 4.0, the UEFI bitness likely isn't
            # exposed to the userspace so we assume a 64 bit UEFI here
            efi_bitness = "64"
        bitness_translate = {"32": "--target=i386-efi",
                             "64": "--target=x86_64-efi"}
        check_target_env_call([libcalamares.job.configuration["grubInstall"],
                               bitness_translate[efi_bitness],
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
        efi_file_source = {"32": os.path.join(install_efi_directory_firmware,
                                              efi_bootloader_id,
                                              "grubia32.efi"),
                           "64": os.path.join(install_efi_directory_firmware,
                                              efi_bootloader_id,
                                              "grubx64.efi")}
        shutil.copy2(efi_file_source[efi_bitness], install_efi_boot_directory)
    else:
        print("Bootloader: grub (bios)")
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

    # The file specified in grubCfg should already be filled out
    # by the grubcfg job module.
    check_target_env_call([libcalamares.job.configuration["grubMkconfig"],
                           "-o", libcalamares.job.configuration["grubCfg"]])


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
    else:
        install_grub(efi_directory, fw_type)


def run():
    """
    Starts procedure and passes 'fw_type' to other routine.

    :return:
    """

    fw_type = libcalamares.globalstorage.value("firmwareType")

    if (libcalamares.globalstorage.value("bootLoader") is None
            and fw_type != "efi"):
        return None

    partitions = libcalamares.globalstorage.value("partitions")

    if fw_type == "efi":
        esp_found = False

        for partition in partitions:
            if (partition["mountPoint"] ==
                    libcalamares.globalstorage.value("efiSystemPartition")):
                esp_found = True

        if not esp_found:
            return None

    prepare_bootloader(fw_type)

    return None
