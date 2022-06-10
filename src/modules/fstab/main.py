#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
#   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import re

import libcalamares

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Writing fstab.")


FSTAB_HEADER = """# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a device; this may
# be used with UUID= as a more robust way to name devices that works even if
# disks are added and removed. See fstab(5).
#
# <file system>             <mount point>  <type>  <options>  <dump>  <pass>"""

CRYPTTAB_HEADER = """# /etc/crypttab: mappings for encrypted partitions.
#
# Each mapped device will be created in /dev/mapper, so your /etc/fstab
# should use the /dev/mapper/<name> paths for encrypted devices.
#
# See crypttab(5) for the supported syntax.
#
# NOTE: You need not list your root (/) partition here, but it must be set up
#       beforehand by the initramfs (/etc/mkinitcpio.conf). The same applies
#       to encrypted swap, which should be set up with mkinitcpio-openswap
#       for resume support.
#
# <name>               <device>                         <password> <options>"""

# Turn Parted filesystem names into fstab names
FS_MAP = {
    "fat16": "vfat",
    "fat32": "vfat",
    "linuxswap": "swap",
}


def mkdir_p(path):
    """ Create directory.

    :param path:
    """
    if not os.path.exists(path):
        os.makedirs(path)


def is_ssd_disk(disk_name):
    """ Checks if given disk is actually a ssd disk.

    :param disk_name:
    :return:
    """
    filename = os.path.join("/sys/block", disk_name, "queue/rotational")

    if not os.path.exists(filename):
        # Should not happen unless sysfs changes, but better safe than sorry
        return False

    with open(filename) as sysfile:
        return sysfile.read() == "0\n"


def disk_name_for_partition(partition):
    """ Returns disk name for each found partition.

    :param partition:
    :return:
    """
    name = os.path.basename(partition["device"])

    if name.startswith("mmcblk") or name.startswith("nvme"):
        # Typical mmc device is mmcblk0p1, nvme looks like nvme0n1p2
        return re.sub("p[0-9]+$", "", name)

    return re.sub("[0-9]+$", "", name)


class FstabGenerator(object):
    def __init__(self, partitions, root_mount_point, mount_options_list,
                 crypttab_options, tmp_options):
        self.partitions = partitions
        self.root_mount_point = root_mount_point
        self.mount_options_list = mount_options_list
        self.crypttab_options = crypttab_options
        self.tmp_options = tmp_options
        self.ssd_disks = set()
        self.root_is_ssd = False

    def run(self):
        """ Calls needed sub routines.

        :return:
        """
        self.find_ssd_disks()
        self.generate_fstab()
        self.generate_crypttab()
        self.create_mount_points()

        return None

    def find_ssd_disks(self):
        """ Checks for ssd disks """
        disks = {disk_name_for_partition(x) for x in self.partitions}
        self.ssd_disks = {x for x in disks if is_ssd_disk(x)}

    def generate_crypttab(self):
        """ Create crypttab. """
        mkdir_p(os.path.join(self.root_mount_point, "etc"))
        crypttab_path = os.path.join(self.root_mount_point, "etc", "crypttab")

        with open(crypttab_path, "w") as crypttab_file:
            print(CRYPTTAB_HEADER, file=crypttab_file)

            for partition in self.partitions:
                dct = self.generate_crypttab_line_info(partition)

                if dct:
                    self.print_crypttab_line(dct, file=crypttab_file)

    def generate_crypttab_line_info(self, partition):
        """ Generates information for each crypttab entry. """
        if "luksMapperName" not in partition or "luksUuid" not in partition:
            return None

        mapper_name = partition["luksMapperName"]
        luks_uuid = partition["luksUuid"]
        if not mapper_name or not luks_uuid:
            return None

        password = "/crypto_keyfile.bin"
        crypttab_options = self.crypttab_options

        # Set crypttab password for partition to none and remove crypttab options
        # if root partition was not encrypted
        if any([p["mountPoint"] == "/"
                and "luksMapperName" not in p
                for p in self.partitions]):
            password = "none"
            crypttab_options = ""
        # on root partition when /boot is unencrypted
        elif partition["mountPoint"] == "/":
            if any([p["mountPoint"] == "/boot"
                   and "luksMapperName" not in p
                   for p in self.partitions]):
                password = "none"
                crypttab_options = ""

        return dict(
            name=mapper_name,
            device="UUID=" + luks_uuid,
            password=password,
            options=crypttab_options,
        )

    def print_crypttab_line(self, dct, file=None):
        """ Prints line to '/etc/crypttab' file. """
        line = "{:21} {:<45} {} {}".format(dct["name"],
                                           dct["device"],
                                           dct["password"],
                                           dct["options"],
                                           )

        print(line, file=file)

    def generate_fstab(self):
        """ Create fstab. """
        mkdir_p(os.path.join(self.root_mount_point, "etc"))
        fstab_path = os.path.join(self.root_mount_point, "etc", "fstab")

        with open(fstab_path, "w") as fstab_file:
            print(FSTAB_HEADER, file=fstab_file)

            for partition in self.partitions:
                # Special treatment for a btrfs subvolumes
                if (partition["fs"] == "btrfs"
                   and partition["mountPoint"] == "/"):
                    # Subvolume list has been created in mount.conf and curated in mount module,
                    # so all subvolumes here should be safe to add to fstab
                    btrfs_subvolumes = libcalamares.globalstorage.value("btrfsSubvolumes")
                    for s in btrfs_subvolumes:
                        mount_entry = partition
                        mount_entry["mountPoint"] = s["mountPoint"]
                        mount_entry["subvol"] = s["subvolume"]
                        dct = self.generate_fstab_line_info(mount_entry)
                        if dct:
                            self.print_fstab_line(dct, file=fstab_file)
                elif partition["fs"] != "zfs":  # zfs partitions don't need an entry in fstab
                    dct = self.generate_fstab_line_info(partition)
                    if dct:
                        self.print_fstab_line(dct, file=fstab_file)

            if self.root_is_ssd:
                # Old behavior was to mount /tmp as tmpfs
                # New behavior is to use tmpOptions to decide
                # if mounting /tmp as tmpfs and which options to use
                ssd = self.tmp_options.get("ssd", {})
                if not ssd:
                    ssd = self.tmp_options.get("default", {})
                # Default to True to mimic old behavior
                tmpfs = ssd.get("tmpfs", True)

                if tmpfs:
                    options = ssd.get("options", "defaults,noatime,mode=1777")
                    # Mount /tmp on a tmpfs
                    dct = dict(device="tmpfs",
                               mount_point="/tmp",
                               fs="tmpfs",
                               options=options,
                               check=0,
                               )
                    self.print_fstab_line(dct, file=fstab_file)

    def generate_fstab_line_info(self, partition):
        """
        Generates information (a dictionary of fstab-fields)
        for the given @p partition.
        """
        # Some "fs" names need special handling in /etc/fstab, so remap them.
        filesystem = partition["fs"].lower()
        filesystem = FS_MAP.get(filesystem, filesystem)
        luks_mapper_name = partition.get("luksMapperName", None)
        mount_point = partition["mountPoint"]
        disk_name = disk_name_for_partition(partition)
        is_ssd = disk_name in self.ssd_disks

        # Swap partitions are called "linuxswap" by parted.
        # That "fs" is visible in GS, but that gets mapped
        # to "swap", above, because that's the spelling needed in /etc/fstab
        if not mount_point and not filesystem == "swap":
            return None
        if not mount_point:
            mount_point = "swap"

        if filesystem == "swap" and not partition.get("claimed", None):
            libcalamares.utils.debug("Ignoring foreign swap {!s} {!s}".format(disk_name, partition.get("uuid", None)))
            return None

        options = self.get_mount_options(mount_point)

        if mount_point == "/" and filesystem != "btrfs":
            check = 1
        elif mount_point and mount_point != "swap" and filesystem != "btrfs":
            check = 2
        else:
            check = 0

        if mount_point == "/":
            self.root_is_ssd = is_ssd

        # If there's a set-and-not-empty subvolume set, add it
        if filesystem == "btrfs" and partition.get("subvol",None):
            options = "subvol={},".format(partition["subvol"]) + options

        device = None
        if luks_mapper_name:
            device = "/dev/mapper/" + luks_mapper_name
        elif partition["uuid"]:
            device = "UUID=" + partition["uuid"]
        else:
            device = partition["device"]

        if not device:
            # TODO: we get here when the user mounted a previously encrypted partition
            # This should be catched early in the process
            return None

        return dict(device=device,
                    mount_point=mount_point,
                    fs=filesystem,
                    options=options,
                    check=check,
                    )

    def print_fstab_line(self, dct, file=None):
        """ Prints line to '/etc/fstab' file. """
        line = "{:41} {:<14} {:<7} {:<10} 0 {}".format(dct["device"],
                                                       dct["mount_point"],
                                                       dct["fs"],
                                                       dct["options"],
                                                       dct["check"],
                                                       )
        print(line, file=file)

    def create_mount_points(self):
        """ Creates mount points """
        for partition in self.partitions:
            if partition["mountPoint"]:
                mkdir_p(self.root_mount_point + partition["mountPoint"])

    def get_mount_options(self, mountpoint):
        """
        Returns the mount options for a given mountpoint

        :param mountpoint: A string containing the mountpoint for the fstab entry
        :return: A string containing the mount options for the entry or "defaults" if nothing is found
        """
        mount_options_item = next((x for x in self.mount_options_list if x.get("mountpoint") == mountpoint), None)
        if mount_options_item:
            return mount_options_item.get("option_string", "defaults")
        else:
            return "defaults"


def create_swapfile(root_mount_point, root_btrfs):
    """
    Creates /swapfile in @p root_mount_point ; if the root filesystem
    is on btrfs, then handle some btrfs specific features as well,
    as documented in
        https://wiki.archlinux.org/index.php/Swap#Swap_file

    The swapfile-creation covers progress from 0.2 to 0.5
    """
    libcalamares.job.setprogress(0.2)
    if root_btrfs:
        # btrfs swapfiles must reside on a subvolume that is not snapshotted to prevent file system corruption
        swapfile_path = os.path.join(root_mount_point, "swap/swapfile")
        with open(swapfile_path, "wb") as f:
            pass
        libcalamares.utils.host_env_process_output(["chattr", "+C", "+m", swapfile_path])  # No Copy-on-Write, no compression
    else:
        swapfile_path = os.path.join(root_mount_point, "swapfile")
        with open(swapfile_path, "wb") as f:
            pass
    # Create the swapfile; swapfiles are small-ish
    zeroes = bytes(16384)
    with open(swapfile_path, "wb") as f:
        total = 0
        desired_size = 512 * 1024 * 1024  # 512MiB
        while total < desired_size:
            chunk = f.write(zeroes)
            if chunk < 1:
                libcalamares.utils.debug("Short write on {!s}, cancelling.".format(swapfile_path))
                break
            libcalamares.job.setprogress(0.2 + 0.3 * ( total / desired_size ) )
            total += chunk
    os.chmod(swapfile_path, 0o600)
    libcalamares.utils.host_env_process_output(["mkswap", swapfile_path])
    libcalamares.job.setprogress(0.5)


def run():
    """ Configures fstab.

    :return:
    """
    global_storage = libcalamares.globalstorage
    conf = libcalamares.job.configuration
    partitions = global_storage.value("partitions")
    root_mount_point = global_storage.value("rootMountPoint")

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}"
                                   .format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use.")
                .format("fstab"))
    if not root_mount_point:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}"
                                   .format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use.")
                .format("fstab"))

    # This follows the GS settings from the partition module's Config object
    swap_choice = global_storage.value( "partitionChoices" )
    if swap_choice:
        swap_choice = swap_choice.get( "swap", None )
        if swap_choice and swap_choice == "file":
            # There's no formatted partition for it, so we'll sneak in an entry
            root_partitions = [ p["fs"].lower() for p in partitions if p["mountPoint"] == "/" ]
            root_btrfs = (root_partitions[0] == "btrfs") if root_partitions else False
            if root_btrfs:
                partitions.append( dict(fs="swap", mountPoint=None, claimed=True, device="/swap/swapfile", uuid=None) )
            else:
                partitions.append( dict(fs="swap", mountPoint=None, claimed=True, device="/swapfile", uuid=None) )
        else:
            swap_choice = None

    libcalamares.job.setprogress(0.1)
    mount_options_list = global_storage.value("mountOptionsList")
    crypttab_options = conf.get("crypttabOptions", "luks")
    tmp_options = conf.get("tmpOptions", {})

    # We rely on mount_options having a default; if there wasn't one,
    # bail out with a meaningful error.
    if not mount_options_list:
        libcalamares.utils.warning("No mount options defined, {!s} partitions".format(len(partitions)))
        return (_("Configuration Error"),
                _("No <pre>{!s}</pre> configuration is given for <pre>{!s}</pre> to use.")
                .format("mountOptions", "fstab"))

    generator = FstabGenerator(partitions,
                               root_mount_point,
                               mount_options_list,
                               crypttab_options,
                               tmp_options)

    if swap_choice is not None:
        libcalamares.job.setprogress(0.2)
        root_partitions = [ p["fs"].lower() for p in partitions if p["mountPoint"] == "/" ]
        root_btrfs = (root_partitions[0] == "btrfs") if root_partitions else False
        create_swapfile(root_mount_point, root_btrfs)

    try:
        libcalamares.job.setprogress(0.5)
        return generator.run()
    finally:
        libcalamares.job.setprogress(1.0)
