#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

import libcalamares


HEADER = """# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a device; this may
# be used with UUID= as a more robust way to name devices that works even if
# disks are added and removed. See fstab(5).
#
# <file system>                           <mount point>  <type>  <options>  <dump>  <pass>"""

FS_MAP = {
    "fat": "vfat",
    "linuxswap": "swap",
}


def mkdir_p(path):
    if not os.path.exists(path):
        os.makedirs(path)


def generate_fstab_line(partition):
    fs = partition["fs"]
    mount_point = partition["mountPoint"]

    fs = FS_MAP.get(fs, fs)

    if not mount_point and not fs == "swap":
        return

    options = "defaults"

    if mount_point == "/":
        check = 1
    elif mount_point:
        check = 2
    else:
        check = 0

    return "UUID={} {:<14} {:<7} {:<10} 0       {}".format(
        partition["uuid"],
        mount_point or "none",
        fs,
        options,
        check)


def run():
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    # Create fstab
    mkdir_p(os.path.join(root_mount_point, "etc"))
    fstab_path = os.path.join(root_mount_point, "etc", "fstab")
    with open(fstab_path, "w") as fl:
        print(HEADER, file=fl)
        for partition in partitions:
            line = generate_fstab_line(partition)
            if line:
                print(line, file=fl)

    # Create mount points
    for partition in partitions:
        if partition["mountPoint"]:
            mkdir_p(root_mount_point + partition["mountPoint"])

    return None
