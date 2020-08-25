#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Rohan Garg <rohan@kde.org>
#   SPDX-FileCopyrightText: 2015 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2016 David McKinney <mckinney@subgraph.com>
#   SPDX-FileCopyrightText: 2016 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares

import inspect
import os
import shutil


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configuring initramfs.")


def copy_initramfs_hooks(partitions, root_mount_point):
    """
    Copies initramfs hooks so they are picked up by update-initramfs

    :param partitions:
    :param root_mount_point:
    """
    encrypt_hook = False
    unencrypted_separate_boot = False

    for partition in partitions:
        if partition["mountPoint"] == "/" and "luksMapperName" in partition:
            encrypt_hook = True

        if (partition["mountPoint"] == "/boot"
                and "luksMapperName" not in partition):
            unencrypted_separate_boot = True

    if encrypt_hook:
        target = "{!s}/usr/share/initramfs-tools/hooks/encrypt_hook".format(
                    root_mount_point)

        # Find where this module is installed
        _filename = inspect.getframeinfo(inspect.currentframe()).filename
        _path = os.path.dirname(os.path.abspath(_filename))

        if unencrypted_separate_boot:
            shutil.copy2(
                os.path.join(_path, "encrypt_hook_nokey"),
                target
                )
        else:
            shutil.copy2(
                os.path.join(_path, "encrypt_hook"),
                target
                )
        os.chmod(target, 0o755)


def run():
    """
    Calls routine with given parameters to configure initramfs

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use." ).format("initramfscfg"))
    if not root_mount_point:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}".format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use." ).format("initramfscfg"))

    copy_initramfs_hooks(partitions, root_mount_point)

    return None
