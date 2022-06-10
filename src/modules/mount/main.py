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
import re

import libcalamares

import gettext

_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


class ZfsException(Exception):
    """Exception raised when there is a problem with zfs

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message


def pretty_name():
    return _("Mounting partitions.")


def disk_name_for_partition(partition):
    """ Returns disk name for each found partition.

    :param partition:
    :return:
    """
    name = os.path.basename(partition["device"])

    if name.startswith("/dev/mmcblk") or name.startswith("/dev/nvme"):
        return re.sub("p[0-9]+$", "", name)

    return re.sub("[0-9]+$", "", name)


def is_ssd_disk(partition):
    """ Checks if given partition is on an ssd disk.

    :param partition: A dict containing the partition information
    :return: True is the partition in on an ssd, False otherwise
    """

    try:
        disk_name = disk_name_for_partition(partition)
        filename = os.path.join("/sys/block", disk_name, "queue/rotational")

        with open(filename) as sysfile:
            return sysfile.read() == "0\n"
    except:
        return False


def get_mount_options(filesystem, mount_options, partition):
    """
    Returns the mount options for the partition object and filesystem

    :param filesystem: A string containing the filesystem
    :param mount_options: A list of dicts that descripes the mount options for each mountpoint
    :param partition: A dict containing information about the partition
    :return: A comma seperated string containing the mount options suitable for passing to mount
    """

    # Extra mounts can optionally have "options" set, in this case, they override other all other settings
    if "options" in partition:
        return ",".join(partition["options"])

    # If there are no mount options defined then we use the defaults
    if mount_options is None:
        return "defaults"

    options = next((x for x in mount_options if x["filesystem"] == filesystem), None)

    # If there is no match then check for default options
    if options is None:
        options = next((x for x in mount_options if x["filesystem"] == "default"), None)

    # If it is still None, then fallback to returning defaults
    if options is None:
        return "defaults"

    option_items = options.get("options", []).copy()

    # Append the appropriate options for ssd or hdd if set
    if is_ssd_disk(partition):
        option_items.extend(options.get("ssdOptions", []))
    else:
        option_items.extend(options.get("hddOptions", []))

    if option_items:
        return ",".join(option_items)
    else:
        return "defaults"


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
        btrfs_subvolumes = [dict(mountPoint="/", subvolume="/@"), dict(mountPoint="/home", subvolume="/@home")]

    # Filter out the subvolumes which have a dedicated partition
    non_root_partition_mounts = [m for m in [p.get("mountPoint", None) for p in partitions] if
                                 m is not None and m != '/']
    btrfs_subvolumes = list(filter(lambda s: s["mountPoint"] not in non_root_partition_mounts, btrfs_subvolumes))

    # If we have a swap **file**, give it a separate subvolume.
    swap_choice = libcalamares.globalstorage.value("partitionChoices")
    if swap_choice and swap_choice.get("swap", None) == "file":
        swap_subvol = libcalamares.job.configuration.get("btrfsSwapSubvol", "/@swap")
        btrfs_subvolumes.append({'mountPoint': '/swap', 'subvolume': swap_subvol})
        libcalamares.globalstorage.insert("btrfsSwapSubvol", swap_subvol)

    return btrfs_subvolumes


def mount_zfs(root_mount_point, partition):
    """ Mounts a zfs partition at @p root_mount_point

    :param root_mount_point: The absolute path to the root of the install
    :param partition: The partition map from global storage for this partition
    :return:
    """
    # Get the list of zpools from global storage
    zfs_pool_list = libcalamares.globalstorage.value("zfsPoolInfo")
    if not zfs_pool_list:
        libcalamares.utils.warning("Failed to locate zfsPoolInfo data in global storage")
        raise ZfsException(_("Internal error mounting zfs datasets"))

    # Find the zpool matching this partition
    for zfs_pool in zfs_pool_list:
        if zfs_pool["mountpoint"] == partition["mountPoint"]:
            pool_name = zfs_pool["poolName"]
            ds_name = zfs_pool["dsName"]

    # import the zpool
    try:
        libcalamares.utils.host_env_process_output(["zpool", "import", "-N", "-R", root_mount_point, pool_name], None)
    except subprocess.CalledProcessError:
        raise ZfsException(_("Failed to import zpool"))

    # Get the encrpytion information from global storage
    zfs_info_list = libcalamares.globalstorage.value("zfsInfo")
    encrypt = False
    if zfs_info_list:
        for zfs_info in zfs_info_list:
            if zfs_info["mountpoint"] == partition["mountPoint"] and zfs_info["encrypted"] is True:
                encrypt = True
                passphrase = zfs_info["passphrase"]

    if encrypt is True:
        # The zpool is encrypted, we need to unlock it
        try:
            libcalamares.utils.host_env_process_output(["zfs", "load-key", pool_name], None, passphrase)
        except subprocess.CalledProcessError:
            raise ZfsException(_("Failed to unlock zpool"))

    if partition["mountPoint"] == '/':
        # Get the zfs dataset list from global storage
        zfs = libcalamares.globalstorage.value("zfsDatasets")

        if not zfs:
            libcalamares.utils.warning("Failed to locate zfs dataset list")
            raise ZfsException(_("Internal error mounting zfs datasets"))

        zfs.sort(key=lambda x: x["mountpoint"])
        for dataset in zfs:
            try:
                if dataset["canMount"] == "noauto" or dataset["canMount"] is True:
                    libcalamares.utils.host_env_process_output(["zfs", "mount",
                                                                dataset["zpool"] + '/' + dataset["dsName"]])
            except subprocess.CalledProcessError:
                raise ZfsException(_("Failed to set zfs mountpoint"))
    else:
        try:
            libcalamares.utils.host_env_process_output(["zfs", "mount", pool_name + '/' + ds_name])
        except subprocess.CalledProcessError:
            raise ZfsException(_("Failed to set zfs mountpoint"))


def mount_partition(root_mount_point, partition, partitions, mount_options, mount_options_list):
    """
    Do a single mount of @p partition inside @p root_mount_point.

    :param root_mount_point: A string containing the root of the install
    :param partition: A dict containing information about the partition
    :param partitions: The full list of partitions used to filter out btrfs subvols which have duplicate mountpoints
    :param mount_options: The mount options from the config file
    :param mount_options_list: A list of options for each mountpoint to be placed in global storage for future modules
    :return:
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

    if fstype == "zfs":
        mount_zfs(root_mount_point, partition)
    else:  # fstype == "zfs"
        mount_options_string = get_mount_options(fstype, mount_options, partition)
        if libcalamares.utils.mount(device,
                                    mount_point,
                                    fstype,
                                    mount_options_string) != 0:
            libcalamares.utils.warning("Cannot mount {}".format(device))
        mount_options_list.append({"mountpoint": raw_mount_point, "option_string": mount_options_string})

    # Special handling for btrfs subvolumes. Create the subvolumes listed in mount.conf
    if fstype == "btrfs" and partition["mountPoint"] == '/':
        # Root has been mounted to btrfs volume -> create subvolumes from configuration
        btrfs_subvolumes = get_btrfs_subvolumes(partitions)

        # Store created list in global storage so it can be used in the fstab module
        libcalamares.globalstorage.insert("btrfsSubvolumes", btrfs_subvolumes)
        # Create the subvolumes that are in the completed list
        for s in btrfs_subvolumes:
            if not s["subvolume"]:
                continue
            os.makedirs(root_mount_point + os.path.dirname(s["subvolume"]), exist_ok=True)
            subprocess.check_call(["btrfs", "subvolume", "create",
                                   root_mount_point + s["subvolume"]])
            if s["mountPoint"] == "/":
                # insert the root subvolume into global storage
                libcalamares.globalstorage.insert("btrfsRootSubvolume", s["subvolume"])
        subprocess.check_call(["umount", "-v", root_mount_point])

        device = partition["device"]

        if "luksMapperName" in partition:
            device = os.path.join("/dev/mapper", partition["luksMapperName"])

        # Mount the subvolumes
        swap_subvol = libcalamares.job.configuration.get("btrfsSwapSubvol", "/@swap")
        for s in btrfs_subvolumes:
            mount_option = "subvol={}".format(s['subvolume'])
            if s['subvolume'] == swap_subvol:
                mount_option += "," + get_mount_options("btrfs_swap", mount_options, partition)
            else:
                mount_option += "," + get_mount_options(fstype, mount_options, partition)
            subvolume_mountpoint = mount_point[:-1] + s['mountPoint']
            mount_options_list.append({"mountpoint": s['mountPoint'], "option_string": mount_option})
            if libcalamares.utils.mount(device,
                                        subvolume_mountpoint,
                                        fstype,
                                        mount_option) != 0:
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
                _("No partitions are defined for <pre>{!s}</pre> to use.").format("mount"))

    root_mount_point = tempfile.mkdtemp(prefix="calamares-root-")

    # Get the mountOptions, if this is None, that is OK and will be handled later
    mount_options = libcalamares.job.configuration.get("mountOptions")

    # Guard against missing keys (generally a sign that the config file is bad)
    extra_mounts = libcalamares.job.configuration.get("extraMounts") or []
    if not extra_mounts:
        libcalamares.utils.warning("No extra mounts defined. Does mount.conf exist?")

    if libcalamares.globalstorage.value("firmwareType") != "efi":
        for mount in extra_mounts:
            if mount.get("efi", None) is True:
                extra_mounts.remove(mount)

    # Add extra mounts to the partitions list and sort by mount points.
    # This way, we ensure / is mounted before the rest, and every mount point
    # is created on the right partition (e.g. if a partition is to be mounted
    # under /tmp, we make sure /tmp is mounted before the partition)
    mountable_partitions = [p for p in partitions + extra_mounts if "mountPoint" in p and p["mountPoint"]]
    mountable_partitions.sort(key=lambda x: x["mountPoint"])

    # mount_options_list will be inserted into global storage for use in fstab later
    mount_options_list = []
    try:
        for partition in mountable_partitions:
            mount_partition(root_mount_point, partition, partitions, mount_options, mount_options_list)
    except ZfsException as ze:
        return _("zfs mounting error"), ze.message

    if not mount_options_list:
        libcalamares.utils.warning("No mount options defined, {!s} partitions, {!s} mountable".format(len(partitions), len(mountable_partitions)))

    libcalamares.globalstorage.insert("rootMountPoint", root_mount_point)
    libcalamares.globalstorage.insert("mountOptionsList", mount_options_list)

    # Remember the extra mounts for the unpackfs module
    libcalamares.globalstorage.insert("extraMounts", extra_mounts)
