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
import subprocess
import tempfile

import libcalamares


def mount_partitions(root_mount_point, partitions):
    for partition in partitions:
        if not partition["mountPoint"]:
            continue
        # Create mount point with `+` rather than `os.path.join()` because
        # `partition["mountPoint"]` starts with a '/'.
        mount_point = root_mount_point + partition["mountPoint"]
        libcalamares.utils.mount(
            partition["device"], mount_point,
            partition.get("fs", ""),
            partition.get("options", "")
            )


def run():
    root_mount_point = tempfile.mkdtemp(prefix="calamares-root-")
    partitions = libcalamares.globalstorage.value("partitions")
    extra_mounts = libcalamares.job.configuration["extraMounts"]

    # Sort by mount points to ensure / is mounted before the rest
    partitions.sort(key=lambda x: x["mountPoint"])
    mount_partitions(root_mount_point, partitions)

    mount_partitions(root_mount_point, extra_mounts)

    libcalamares.globalstorage.insert("rootMountPoint", root_mount_point)
    return None
