#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2019 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2019-2020 Collabora Ltd
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import tempfile
import subprocess
import os

import libcalamares

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Mounting partitions.")

def mount_partition(root_mount_point, partition, partitions):
    """
    Do a single mount of @p partition inside @p root_mount_point.

    The @p partitions are used to handle btrfs special-cases:
    then subvolumes are created for root and home.
    """
    # Create mount point with `+` rather than `os.path.join()` because
    # `partition["mountPoint"]` starts with a '/'.
    global_storage = libcalamares.globalstorage
    raw_mount_point = partition["mountPoint"]
    if not raw_mount_point:
        return

    mount_point = root_mount_point + raw_mount_point

    # Ensure that the created directory has the correct SELinux context on
    # SELinux-enabled systems.
    os.makedirs(mount_point, exist_ok=True)
    try:
        subprocess.call(['chcon', '--reference=' + raw_mount_point, mount_point])
    except FileNotFoundError as e:
        libcalamares.utils.warning(str(e))
    except OSError:
        libcalamares.utils.error("Cannot run 'chcon' normally.")
        raise

    fstype = partition.get("fs", "").lower()
    if fstype == "unformatted":
        return

    if fstype == "fat16" or fstype == "fat32":
        fstype = "vfat"

    device = partition["device"]

    if "luksMapperName" in partition:
        device = os.path.join("/dev/mapper", partition["luksMapperName"])

    if libcalamares.utils.mount(device,
                                mount_point,
                                fstype,
                                partition.get("options", "")) != 0:
        libcalamares.utils.warning("Cannot mount {}".format(device))

    # If the root partition is btrfs, we create a subvolume "@"
    # for the root mount point.
    # If a separate /home partition isn't defined, we also create
    # a subvolume "@home".
    # If a swapfile is used, we also create a subvolume "@swap".
    # Finally we remount all of the above on the correct paths.
    if fstype == "btrfs" and partition["mountPoint"] == '/':
        has_home_mount_point = False
        for p in partitions:
            if "mountPoint" not in p or not p["mountPoint"]:
                continue
            if p["mountPoint"] == "/home":
                has_home_mount_point = True
                break
        needs_swap_subvolume = False
        swap_choice = global_storage.value( "partitionChoices" )
        if swap_choice:
            swap_choice = swap_choice.get( "swap", None )
            if swap_choice and swap_choice == "file":
                needs_swap_subvolume = True

        subprocess.check_call(['btrfs', 'subvolume', 'create',
                               root_mount_point + '/@'])

        if not has_home_mount_point:
            subprocess.check_call(['btrfs', 'subvolume', 'create',
                                   root_mount_point + '/@home'])
        if needs_swap_subvolume:
            subprocess.check_call(['btrfs', 'subvolume', 'create',
                                       root_mount_point + '/@swap'])

        subprocess.check_call(["umount", "-v", root_mount_point])

        device = partition["device"]

        if "luksMapperName" in partition:
            device = os.path.join("/dev/mapper", partition["luksMapperName"])

        if libcalamares.utils.mount(device,
                                    mount_point,
                                    fstype,
                                    ",".join(["subvol=@", partition.get("options", "")])) != 0:
            libcalamares.utils.warning("Cannot mount {}".format(device))

        if not has_home_mount_point:
            if libcalamares.utils.mount(device,
                                        root_mount_point + "/home",
                                        fstype,
                                        ",".join(["subvol=@home", partition.get("options", "")])) != 0:
                libcalamares.utils.warning("Cannot mount {}".format(device))
        
        if needs_swap_subvolume:
            if libcalamares.utils.mount(device,
                                        root_mount_point + "/swap",
                                        fstype,
                                        ",".join(["subvol=@swap", partition.get("options", "")])) != 0:
                libcalamares.utils.warning("Cannot mount {}".format(device))


def run():
    """
    Mount all the partitions from GlobalStorage and from the job configuration.
    Partitions are mounted in-lexical-order of their mountPoint.
    """
    partitions = libcalamares.globalstorage.value("partitions")

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use." ).format("mount"))

    root_mount_point = tempfile.mkdtemp(prefix="calamares-root-")

    # Guard against missing keys (generally a sign that the config file is bad)
    extra_mounts = libcalamares.job.configuration.get("extraMounts") or []
    extra_mounts_efi = libcalamares.job.configuration.get("extraMountsEfi") or []
    if not extra_mounts and not extra_mounts_efi:
        libcalamares.utils.warning("No extra mounts defined. Does mount.conf exist?")

    if libcalamares.globalstorage.value("firmwareType") == "efi":
        extra_mounts.extend(extra_mounts_efi)

    # Add extra mounts to the partitions list and sort by mount points.
    # This way, we ensure / is mounted before the rest, and every mount point
    # is created on the right partition (e.g. if a partition is to be mounted
    # under /tmp, we make sure /tmp is mounted before the partition)
    mountable_partitions = [ p for p in partitions + extra_mounts if "mountPoint" in p and p["mountPoint"] ]
    mountable_partitions.sort(key=lambda x: x["mountPoint"])
    for partition in mountable_partitions:
        mount_partition(root_mount_point, partition, partitions)

    libcalamares.globalstorage.insert("rootMountPoint", root_mount_point)

    # Remember the extra mounts for the unpackfs module
    libcalamares.globalstorage.insert("extraMounts", extra_mounts)
