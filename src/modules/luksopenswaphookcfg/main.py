#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2016, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
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
import os.path


def write_openswap_conf(partitions, root_mount_point, openswap_conf_path):
    swap_outer_uuid = ""
    swap_mapper_name = ""
    mountable_keyfile_device = ""

    for partition in partitions:
        if partition["fs"] == "linuxswap" and "luksMapperName" in partition:
            swap_outer_uuid = partition["luksUuid"]
            swap_mapper_name = partition["luksMapperName"]

        elif partition["mountPoint"] == "/" and "luksMapperName" in partition:
            mountable_keyfile_device = (
                "/dev/mapper/{!s}".format(partition["luksMapperName"])
                )

    if not mountable_keyfile_device or not swap_outer_uuid:
        return None

    swap_device_path = "/dev/disk/by-uuid/{!s}".format(swap_outer_uuid)

    lines = []
    with open(os.path.join(root_mount_point,
                           openswap_conf_path), 'r') as openswap_file:
        lines = [x.strip() for x in openswap_file.readlines()]

    for i in range(len(lines)):
        if lines[i].startswith("swap_device"):
            lines[i] = "swap_device={!s}".format(swap_device_path)

        elif lines[i].startswith("crypt_swap_name"):
            lines[i] = "crypt_swap_name={!s}".format(swap_mapper_name)

        elif lines[i].startswith("keyfile_device"):
            lines[i] = "keyfile_device={!s}".format(mountable_keyfile_device)

        elif lines[i].startswith("keyfile_filename"):
            lines[i] = "keyfile_filename=crypto_keyfile.bin"

    with open(os.path.join(root_mount_point,
                           openswap_conf_path), 'w') as openswap_file:
        openswap_file.write("\n".join(lines) + "\n")

    return None


def run():
    """
    This module sets up the openswap hook for a resumable encrypted swap.
    :return:
    """

    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    openswap_conf_path = libcalamares.job.configuration["configFilePath"]
    partitions = libcalamares.globalstorage.value("partitions")

    openswap_conf_path = openswap_conf_path.lstrip('/')

    return write_openswap_conf(
        partitions, root_mount_point, openswap_conf_path
        )
