#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2017, Ghiunhan Mamut <venerix@redcorelinux.org>
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

def write_dmcrypt_conf(partitions, root_mount_point, dmcrypt_conf_path):
    crypto_target = ""
    crypto_source = ""

    for partition in partitions:
        has_luks = "luksMapperName" in partition
        skip_partitions = partition["mountPoint"] == "/" or partition["fs"] == "linuxswap"

        if not has_luks and not skip_partitions:
            libcalamares.utils.debug(
                "Skip writing OpenRC LUKS configuration for partition {!s}".format(partition["mountPoint"]))

        if has_luks and not skip_partitions:
            crypto_target = partition["luksMapperName"]
            crypto_source = "/dev/disk/by-uuid/{!s}".format(partition["uuid"])
            libcalamares.utils.debug(
                "Writing OpenRC LUKS configuration for partition {!s}".format(partition["mountPoint"]))

            with open(os.path.join(root_mount_point, dmcrypt_conf_path), 'a+') as dmcrypt_file:
                dmcrypt_file.write("\ntarget=" + crypto_target)
                dmcrypt_file.write("\nsource=" + crypto_source)
                dmcrypt_file.write("\nkey=/crypto_keyfile.bin")
                dmcrypt_file.write("\n")

        if has_luks and skip_partitions:
            pass  # root and swap partitions should be handled by initramfs generators

    return None

def run():
    """
    This module configures OpenRC dmcrypt service for LUKS encrypted partitions.
    :return:
    """

    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    dmcrypt_conf_path = libcalamares.job.configuration["configFilePath"]
    partitions = libcalamares.globalstorage.value("partitions")

    dmcrypt_conf_path = dmcrypt_conf_path.lstrip('/')

    return write_dmcrypt_conf(partitions, root_mount_point, dmcrypt_conf_path)
