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
import subprocess

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
# NOTE: Do not list your root (/) partition here, it must be set up
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

    if name.startswith("/dev/mmcblk") or name.startswith("/dev/nvme"):
        return re.sub("p[0-9]+$", "", name)

    return re.sub("[0-9]+$", "", name)


class FstabGenerator(object):
    """ Class header

    :param partitions:
    :param root_mount_point:
    :param mount_options:
    :param ssd_extra_mount_options:
    """
    def __init__(self, partitions, root_mount_point, mount_options,
                 ssd_extra_mount_options, crypttab_options):
        self.partitions = partitions
        self.root_mount_point = root_mount_point
        self.mount_options = mount_options
        self.ssd_extra_mount_options = ssd_extra_mount_options
        self.crypttab_options = crypttab_options
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

        return dict(
            name=mapper_name,
            device="UUID=" + luks_uuid,
            password="/crypto_keyfile.bin",
            options=self.crypttab_options,
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
                # Special treatment for a btrfs root with @, @home and @swap
                # subvolumes
                if (partition["fs"] == "btrfs"
                   and partition["mountPoint"] == "/"):
                    output = subprocess.check_output(['btrfs',
                                                      'subvolume',
                                                      'list',
                                                      self.root_mount_point])
                    output_lines = output.splitlines()
                    for line in output_lines:
                        if line.endswith(b'path @'):
                            root_entry = partition
                            root_entry["subvol"] = "@"
                            dct = self.generate_fstab_line_info(root_entry)
                            if dct:
                                self.print_fstab_line(dct, file=fstab_file)
                        elif line.endswith(b'path @home'):
                            home_entry = partition
                            home_entry["mountPoint"] = "/home"
                            home_entry["subvol"] = "@home"
                            dct = self.generate_fstab_line_info(home_entry)
                            if dct:
                                self.print_fstab_line(dct, file=fstab_file)
                        elif line.endswith(b'path @swap'):
                            swap_part_entry = partition
                            swap_part_entry["mountPoint"] = "/swap"
                            swap_part_entry["subvol"] = "@swap"
                            dct = self.generate_fstab_line_info(swap_part_entry)
                            if dct:
                                self.print_fstab_line(dct, file=fstab_file)

                else:
                    dct = self.generate_fstab_line_info(partition)
                    if dct:
                        self.print_fstab_line(dct, file=fstab_file)

            if self.root_is_ssd:
                # Mount /tmp on a tmpfs
                dct = dict(device="tmpfs",
                           mount_point="/tmp",
                           fs="tmpfs",
                           options="defaults,noatime,mode=1777",
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
        has_luks = "luksMapperName" in partition
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

        options = self.get_mount_options(filesystem, mount_point)

        if is_ssd:
            extra = self.ssd_extra_mount_options.get(filesystem)

            if extra:
                options += "," + extra

        if mount_point == "/":
            check = 1
        elif mount_point and mount_point != "swap":
            check = 2
        else:
            check = 0

        if mount_point == "/":
            self.root_is_ssd = is_ssd

        if filesystem == "btrfs" and "subvol" in partition:
            options = "subvol={},".format(partition["subvol"]) + options

        if has_luks:
            device = "/dev/mapper/" + partition["luksMapperName"]
        elif partition["uuid"] is not None:
            device = "UUID=" + partition["uuid"]
        else:
            device = partition["device"]

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

    def get_mount_options(self, filesystem, mount_point):
        efiMountPoint = libcalamares.globalstorage.value("efiSystemPartition")
        job_config = libcalamares.job.configuration

        if (mount_point == efiMountPoint and "efiMountOptions" in job_config):
            return job_config["efiMountOptions"]

        return self.mount_options.get(filesystem,
                                      self.mount_options["default"])


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
        o = subprocess.check_output(["chattr", "+C", swapfile_path])
        libcalamares.utils.debug("swapfile attributes: {!s}".format(o))
        o = subprocess.check_output(["btrfs", "property", "set", swapfile_path, "compression", "none"])
        libcalamares.utils.debug("swapfile compression: {!s}".format(o))
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
    o = subprocess.check_output(["mkswap", swapfile_path])
    libcalamares.utils.debug("swapfile mkswap: {!s}".format(o))
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
    mount_options = conf["mountOptions"]
    ssd_extra_mount_options = conf.get("ssdExtraMountOptions", {})
    crypttab_options = conf.get("crypttabOptions", "luks")
    generator = FstabGenerator(partitions,
                               root_mount_point,
                               mount_options,
                               ssd_extra_mount_options,
                               crypttab_options)

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
