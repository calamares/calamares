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


def get_btrfs_subvolumes(partitions):
    """
    Gets the job-configuration for btrfs subvolumes, or if there is
    none given, returns a default configuration that matches
    the setup (/ and /home) from before configurability was introduced.

    @param partitions
        The partitions (from the partitioning module) that will exist on disk.
        This is used to filter out subvolumes that don't need to be created
        because they get a dedicated partition instead.
    """
    btrfs_subvolumes = libcalamares.job.configuration.get("btrfsSubvolumes", None)
    # Warn if there's no configuration at all, and empty configurations are
    # replaced by a simple root-only layout.
    if btrfs_subvolumes is None:
        libcalamares.utils.warning("No configuration for btrfsSubvolumes")
    if not btrfs_subvolumes:
        btrfs_subvolumes = [ dict(mountPoint="/", subvolume="/@"), dict(mountPoint="/home", subvolume="/@home") ]

    # Filter out the subvolumes which have a dedicated partition
    non_root_partition_mounts = [ m for m in [ p.get("mountPoint", None) for p in partitions ] if m is not None and m != '/' ]
    btrfs_subvolumes = list(filter(lambda s : s["mountPoint"] not in non_root_partition_mounts, btrfs_subvolumes))

    # If we have a swap **file**, give it a separate subvolume.
    swap_choice = libcalamares.globalstorage.value( "partitionChoices" )
    if swap_choice and swap_choice.get( "swap", None ) == "file":
        btrfs_subvolumes.append({'mountPoint': '/swap', 'subvolume': '/@swap'})

    return btrfs_subvolumes


def mount_partition(root_mount_point, partition, partitions):
    """
    Do a single mount of @p partition inside @p root_mount_point.
    """
    # Create mount point with `+` rather than `os.path.join()` because
    # `partition["mountPoint"]` starts with a '/'.
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

    # Special handling for btrfs subvolumes. Create the subvolumes listed in mount.conf
    if fstype == "btrfs" and partition["mountPoint"] == '/':
        # Root has been mounted to btrfs volume -> create subvolumes from configuration
        btrfs_subvolumes = get_btrfs_subvolumes(partitions)

        # Store created list in global storage so it can be used in the fstab module
        libcalamares.globalstorage.insert("btrfsSubvolumes", btrfs_subvolumes)
        # Create the subvolumes that are in the completed list
        for s in btrfs_subvolumes:
            subprocess.check_call(['btrfs', 'subvolume', 'create',
                               root_mount_point + s['subvolume']])

        subprocess.check_call(["umount", "-v", root_mount_point])

        device = partition["device"]

        if "luksMapperName" in partition:
            device = os.path.join("/dev/mapper", partition["luksMapperName"])

        # Mount the subvolumes
        for s in btrfs_subvolumes:
            mount_option = "subvol={}".format(s['subvolume'])
            subvolume_mountpoint = mount_point[:-1] + s['mountPoint']
            if libcalamares.utils.mount(device,
                                    subvolume_mountpoint,
                                    fstype,
                                    ",".join([mount_option, partition.get("options", "")])) != 0:
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
