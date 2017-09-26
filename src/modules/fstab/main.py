#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2016, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
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
import re
import subprocess

import libcalamares


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
        mount_point = partition["mountPoint"]
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
                # Special treatment for a btrfs root with @ and @home
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
        """ Generates information for each fstab entry. """
        filesystem = partition["fs"].lower()
        has_luks = "luksMapperName" in partition
        mount_point = partition["mountPoint"]
        disk_name = disk_name_for_partition(partition)
        is_ssd = disk_name in self.ssd_disks
        filesystem = FS_MAP.get(filesystem, filesystem)

        if not mount_point and not filesystem == "swap":
            return None
        if not mount_point:
            mount_point = "swap"

        options = self.mount_options.get(filesystem,
                                         self.mount_options["default"])
        if is_ssd:
            extra = self.ssd_extra_mount_options.get(filesystem)

            if extra:
                options += "," + extra

        if mount_point == "/":
            check = 1
        elif mount_point:
            check = 2
        else:
            check = 0

        if mount_point == "/":
            self.root_is_ssd = is_ssd

        if filesystem == "btrfs" and "subvol" in partition:
            options="subvol={},".format(partition["subvol"]) + options

        if has_luks:
            device="/dev/mapper/" + partition["luksMapperName"]
        else:
            device="UUID=" + partition["uuid"]

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


def run():
    """ Configures fstab.

    :return:
    """
    global_storage = libcalamares.globalstorage
    conf = libcalamares.job.configuration
    partitions = global_storage.value("partitions")
    root_mount_point = global_storage.value("rootMountPoint")
    mount_options = conf["mountOptions"]
    ssd_extra_mount_options = conf.get("ssdExtraMountOptions", {})
    crypttab_options = conf.get("crypttabOptions", "luks")
    generator = FstabGenerator(partitions,
                               root_mount_point,
                               mount_options,
                               ssd_extra_mount_options,
                               crypttab_options)

    return generator.run()
