#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2017 Ghiunhan Mamut <venerix@redcorelinux.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os.path

import libcalamares

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext



def pretty_name():
    return _("Configuring OpenRC dmcrypt service.")


def write_dmcrypt_conf(partitions, root_mount_point, dmcrypt_conf_path):
    crypto_target = ""
    crypto_source = ""
    unencrypted_separate_boot = any(p["mountPoint"] == "/boot" and "luksMapperName" not in p for p in partitions)

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
                # Don't use keyfile if boot is unencrypted, keys must not be stored on unencrypted partitions
                if not unencrypted_separate_boot:
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

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use." ).format("openrcdmcryptcfg"))
    if not root_mount_point:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}".format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use." ).format("openrcdmcryptcfg"))

    dmcrypt_conf_path = dmcrypt_conf_path.lstrip('/')

    return write_dmcrypt_conf(partitions, root_mount_point, dmcrypt_conf_path)
