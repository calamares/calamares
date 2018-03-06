#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2016, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
#   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

from libcalamares.utils import check_target_env_call


def run():
    """
    This module sets up a file crypto_keyfile.bin on the rootfs, assuming the
    rootfs is LUKS encrypted and a passphrase is provided. This file is then
    included in the initramfs and used for unlocking the rootfs from a
    previously unlocked GRUB2 session.
    :return:
    """

    partitions = libcalamares.globalstorage.value("partitions")

    luks_root_device = ""
    luks_root_passphrase = ""

    additional_luks_devices = []

    for partition in partitions:
        if partition["mountPoint"] == "/" and "luksMapperName" in partition:
            luks_root_device = partition["device"]
            luks_root_passphrase = partition["luksPassphrase"]
        elif "luksMapperName" in partition and\
             (partition["mountPoint"] or partition["fs"] == "linuxswap"):
            additional_luks_devices.append((partition["device"],
                                            partition["luksPassphrase"]))

    if not luks_root_device:
        return None

    if not luks_root_passphrase:
        return (
            "Encrypted rootfs setup error",
            "Rootfs partition {!s} is LUKS but no passphrase found."
            .format(luks_root_device))

    # Generate random keyfile
    check_target_env_call(["dd",
                           "bs=512",
                           "count=4",
                           "if=/dev/urandom",
                           "of=/crypto_keyfile.bin"])

    check_target_env_call(["cryptsetup",
                           "luksAddKey",
                           luks_root_device,
                           "/crypto_keyfile.bin"],
                          luks_root_passphrase,
                          15)  # timeout 15s

    for additional_device in additional_luks_devices:
        check_target_env_call(["cryptsetup",
                               "luksAddKey",
                               additional_device[0],
                               "/crypto_keyfile.bin"],
                              additional_device[1],
                              15)  # timeout 15s

    check_target_env_call(["chmod",
                           "g-rwx,o-rwx",
                           "/crypto_keyfile.bin"])

    return None
