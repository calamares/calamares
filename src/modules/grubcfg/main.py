#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014-2015, Philip Müller <philm@manjaro.org>
#   Copyright 2015-2017, Teo Mrnjavac <teo@kde.org>
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

import libcalamares
import os
import re


def modify_grub_default(partitions, root_mount_point, distributor):
    """
    Configures '/etc/default/grub' for hibernation and plymouth.

    @see bootloader/main.py, for similar handling of kernel parameters

    :param partitions:
    :param root_mount_point:
    :param distributor:
    :return:
    """
    default_dir = os.path.join(root_mount_point, "etc/default")
    default_grub = os.path.join(default_dir, "grub")
    distributor_replace = distributor.replace("'", "'\\''")
    dracut_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which dracut"]
        )
    have_dracut = dracut_bin == 0  # Shell exit value 0 means success

    use_splash = ""
    swap_uuid = ""
    swap_outer_uuid = ""
    swap_outer_mappername = None

    if libcalamares.globalstorage.contains("hasPlymouth"):
        if libcalamares.globalstorage.value("hasPlymouth"):
            use_splash = "splash"

    cryptdevice_params = []

    if have_dracut:
        for partition in partitions:
            has_luks = "luksMapperName" in partition
            if partition["fs"] == "linuxswap" and not has_luks:
                swap_uuid = partition["uuid"]

            if (partition["fs"] == "linuxswap" and has_luks):
                swap_outer_uuid = partition["luksUuid"]
                swap_outer_mappername = partition["luksMapperName"]

            if (partition["mountPoint"] == "/" and has_luks):
                cryptdevice_params = [
                    "rd.luks.uuid={!s}".format(partition["luksUuid"])
                    ]
    else:
        for partition in partitions:
            has_luks = "luksMapperName" in partition
            if partition["fs"] == "linuxswap" and not has_luks:
                swap_uuid = partition["uuid"]

            if (partition["mountPoint"] == "/" and has_luks):
                cryptdevice_params = [
                    "cryptdevice=UUID={!s}:{!s}".format(
                        partition["luksUuid"], partition["luksMapperName"]
                        ),
                    "root=/dev/mapper/{!s}".format(
                        partition["luksMapperName"]
                        ),
                    "resume=/dev/mapper/{!s}".format(
                        partition["luksMapperName"]
                        )
                ]

    kernel_params = ["quiet"]

    if cryptdevice_params:
        kernel_params.extend(cryptdevice_params)

    if use_splash:
        kernel_params.append(use_splash)

    if swap_uuid:
        kernel_params.append("resume=UUID={!s}".format(swap_uuid))

    if have_dracut and swap_outer_uuid:
        kernel_params.append("rd.luks.uuid={!s}".format(swap_outer_uuid))
    if have_dracut and swap_outer_mappername:
        kernel_params.append("resume=/dev/mapper/{!s}".format(
            swap_outer_mappername))

    distributor_line = "GRUB_DISTRIBUTOR='{!s}'".format(distributor_replace)

    if not os.path.exists(default_dir):
        os.mkdir(default_dir)

    have_kernel_cmd = False
    have_distributor_line = False

    if "overwrite" in libcalamares.job.configuration:
        overwrite = libcalamares.job.configuration["overwrite"]
    else:
        overwrite = False

    if os.path.exists(default_grub) and not overwrite:
        with open(default_grub, 'r') as grub_file:
            lines = [x.strip() for x in grub_file.readlines()]

        for i in range(len(lines)):
            if lines[i].startswith("#GRUB_CMDLINE_LINUX_DEFAULT"):
                kernel_cmd = "GRUB_CMDLINE_LINUX_DEFAULT=\"{!s}\"".format(
                    " ".join(kernel_params)
                    )
                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif lines[i].startswith("GRUB_CMDLINE_LINUX_DEFAULT"):
                regex = re.compile(r"^GRUB_CMDLINE_LINUX_DEFAULT\s*=\s*")
                line = regex.sub("", lines[i])
                line = line.lstrip()
                line = line.lstrip("\"")
                line = line.lstrip("'")
                line = line.rstrip()
                line = line.rstrip("\"")
                line = line.rstrip("'")
                existing_params = line.split()

                for existing_param in existing_params:
                    existing_param_name = existing_param.split("=")[0]

                    # the only ones we ever add
                    if existing_param_name not in [
                            "quiet", "resume", "splash"]:
                        kernel_params.append(existing_param)

                kernel_cmd = "GRUB_CMDLINE_LINUX_DEFAULT=\"{!s}\"".format(
                    " ".join(kernel_params)
                    )
                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif (lines[i].startswith("#GRUB_DISTRIBUTOR")
                  or lines[i].startswith("GRUB_DISTRIBUTOR")):
                lines[i] = distributor_line
                have_distributor_line = True
    else:
        lines = []

        if "defaults" in libcalamares.job.configuration:
            for key, value in libcalamares.job.configuration[
                    "defaults"].items():
                if value.__class__.__name__ == "bool":
                    if value:
                        escaped_value = "true"
                    else:
                        escaped_value = "false"
                else:
                    escaped_value = str(value).replace("'", "'\\''")

                lines.append("{!s}='{!s}'".format(key, escaped_value))

    if not have_kernel_cmd:
        kernel_cmd = "GRUB_CMDLINE_LINUX_DEFAULT=\"{!s}\"".format(
            " ".join(kernel_params)
            )
        lines.append(kernel_cmd)

    if not have_distributor_line:
        lines.append(distributor_line)

    if cryptdevice_params:
        lines.append("GRUB_ENABLE_CRYPTODISK=y")

    with open(default_grub, 'w') as grub_file:
        grub_file.write("\n".join(lines) + "\n")

    return None


def run():
    """
    Calls routine with given parameters to modify '/etc/default/grub'.

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
            if (partition["mountPoint"]
                    == libcalamares.globalstorage.value("efiSystemPartition")):
                esp_found = True

        if not esp_found:
            return None

    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    branding = libcalamares.globalstorage.value("branding")
    distributor = branding["bootloaderEntryName"]

    return modify_grub_default(partitions, root_mount_point, distributor)
