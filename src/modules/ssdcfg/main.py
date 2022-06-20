#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#   SPDX-FileCopyrightText: 2020 Arjen Balfoort <arjenbalfoort@hotmail.com>
#   SPDX-License-Identifier: GPL-3.0-or-later
#

import os
import re
import libcalamares


def is_ssd_disk(partition):
    """
    Checks if given disk is actually a ssd disk.
    """
    rotational = os.path.join("/sys/block",
                              disk_name_for_partition(partition),
                              "queue/rotational")

    if not os.path.exists(rotational):
        # Should not happen unless sysfs changes, but better safe than sorry
        return False

    with open(rotational, "r") as sysfile:
        return sysfile.read() == "0\n"


def disk_name_for_partition(partition):
    """
    Returns disk name for each found partition.
    """
    device = os.path.basename(partition["device"])

    if device.startswith("mmcblk") or device.startswith("nvme"):
        return re.sub("p[0-9]+$", "", device)

    return re.sub("[0-9]+$", "", device)


def enable_fstrim():
    """
    Enable fstrim
    """
    systemctl_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which systemctl"])
    if systemctl_bin:
        libcalamares.utils.check_target_env_call(
            ["systemctl", "enable", "fstrim.timer"])


def configure_swappiness():
    """
    Configure swappiness
    """
    etc_dir = os.path.join(libcalamares.globalstorage.value("rootMountPoint"), "etc")
    sysctl_path = os.path.join(etc_dir, "sysctl.conf")
    if os.path.exists(os.path.join(etc_dir, "sysctl.d")):
        sysctl_path = os.path.join(etc_dir, "sysctl.d/swappiness.conf")

    lines = []
    if "swappiness" in libcalamares.job.configuration:
        for key, value in libcalamares.job.configuration["swappiness"].items():
            lines.append(f"{key}={value}")

    if lines:
        with open(sysctl_path, "a") as sysctl:
            sysctl.write("\n".join(lines) + "\n")


def configure_sysfs(partition):
    """
    Set IO scheduler to deadline in /etc/sysfs.conf
    """
    if "nvme" in partition["device"]:
        return

    # For the time being, only configure this when sysfsutils is available
    sysfsutils_path = os.path.join(libcalamares.globalstorage.value("rootMountPoint"),
                                   "etc/init.d/sysfsutils")
    if not os.path.exists(sysfsutils_path):
        return

    sysfs_path = os.path.join(libcalamares.globalstorage.value("rootMountPoint"),
                              "etc/sysfs.conf")
    disk_name = disk_name_for_partition(partition)
    sysfs_cont = f"block/{disk_name}/queue/scheduler=deadline\n"

    with open(sysfs_path, "a") as sysfs:
        sysfs.write(sysfs_cont)


def run():
    """
    Configure SSD
    """
    # Find root partition
    partitions = libcalamares.globalstorage.value("partitions")
    search_list = [_p for _p in partitions if _p["mountPoint"] == "/"]
    partition = search_list[0] if search_list else None

    if not partition:
        return

    # Check if partition is on ssd
    if is_ssd_disk(partition):
        enable_fstrim()
        configure_swappiness()
        configure_sysfs(partition)
