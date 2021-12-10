#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares
import os.path


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configuring encrypted swap.")


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

        elif lines[i].startswith("#keyfile_device_mount_options"):
            if libcalamares.globalstorage.contains("btrfsRootSubvolume"):
                btrfs_root_subvolume = libcalamares.globalstorage.value("btrfsRootSubvolume")
                lines[i] = "keyfile_device_mount_options=--options=subvol=" + btrfs_root_subvolume.lstrip("/")

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

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use.").format("luksopenswaphookcfg"))
    if not root_mount_point:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}".format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use.").format("luksopenswaphookcfg"))

    openswap_conf_path = openswap_conf_path.lstrip('/')

    return write_openswap_conf(partitions, root_mount_point, openswap_conf_path)
