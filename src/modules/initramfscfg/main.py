#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Rohan Garg <rohan@kde.org>
#   Copyright 2015, Philip Müller <philm@manjaro.org>
#   Copyright 2016, David McKinney <mckinney@subgraph.com>
#   Copyright 2016, Kevin Kofler <kevin.kofler@chello.at>
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

def copy_initramfs_hooks(partitions, root_mount_point):
    """ Copies initramfs hooks so they are picked up by update-initramfs

    :param partitions:
    :param root_mount_point:
    """
    encrypt_hook = False
    unencrypted_separate_boot = False

    for partition in partitions:
        if partition["mountPoint"] == "/" and "luksMapperName" in partition:
            encrypt_hook = True

        if partition["mountPoint"] == "/boot" and "luksMapperName" not in partition:
            unencrypted_separate_boot = True

    if encrypt_hook:
        if unencrypted_separate_boot:
            shutil.copy2("/usr/lib/calamares/modules/initramfscfg/encrypt_hook_nokey", "{!s}/usr/share/initramfs-tools/hooks/encrypt_hook".format(root_mount_point))
        else:
            shutil.copy2("/usr/lib/calamares/modules/initramfscfg/encrypt_hook", "{!s}/usr/share/initramfs-tools/hooks/".format(root_mount_point))
        os.chmod("{!s}/usr/share/initramfs-tools/hooks/encrypt_hook".format(root_mount_point), 0o755)

def run():
    """ Calls routine with given parameters to configure initramfs

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    copy_initramfs_hooks(partitions, root_mount_point)

    return None
