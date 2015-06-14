#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
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
import re

import libcalamares


HEADER = """# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a device; this may
# be used with UUID= as a more robust way to name devices that works even if
# disks are added and removed. See fstab(5).
#
# <file system>                           <mount point>  <type>  <options>  <dump>  <pass>"""

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

    with open(filename) as f:
        return f.read() == "0\n"


def disk_name_for_partition(partition):
    """ Returns disk name for each found partition.

    :param partition:
    :return:
    """
    name = os.path.basename(partition["device"])

    if name.startswith("/dev/mmcblk"):
        return re.sub("p[0-9]+$", "", name)

    return re.sub("[0-9]+$", "", name)


class FstabGenerator(object):
    """ Class header

    :param partitions:
    :param root_mount_point:
    :param mount_options:
    :param ssd_extra_mount_options:
    """
    def __init__(self, partitions, root_mount_point, mount_options, ssd_extra_mount_options):
        self.partitions = partitions
        self.root_mount_point = root_mount_point
        self.mount_options = mount_options
        self.ssd_extra_mount_options = ssd_extra_mount_options
        self.ssd_disks = set()
        self.root_is_ssd = False

    def run(self):
        """ Calls needed sub routines.

        :return:
        """
        self.find_ssd_disks()
        self.generate_fstab()
        self.create_mount_points()

        return None

    def find_ssd_disks(self):
        """ Checks for ssd disks """
        disks = {disk_name_for_partition(x) for x in self.partitions}
        self.ssd_disks = {x for x in disks if is_ssd_disk(x)}

    def generate_fstab(self):
        """ Create fstab. """
        mkdir_p(os.path.join(self.root_mount_point, "etc"))
        fstab_path = os.path.join(self.root_mount_point, "etc", "fstab")

        with open(fstab_path, "w") as fl:
            print(HEADER, file=fl)

            for partition in self.partitions:
                dct = self.generate_fstab_line_info(partition)

                if dct:
                    self.print_fstab_line(dct, file=fl)

            if self.root_is_ssd:
                # Mount /tmp on a tmpfs
                dct = dict(device="tmpfs",
                           mount_point="/tmp",
                           fs="tmpfs",
                           options="defaults,noatime,mode=1777",
                           check=0,
                           )
                self.print_fstab_line(dct, file=fl)

    def generate_fstab_line_info(self, partition):
        """ Generates information for each fstab entry.

        :param partition:
        :return:
        """
        fs = partition["fs"]
        mount_point = partition["mountPoint"]
        disk_name = disk_name_for_partition(partition)
        is_ssd = disk_name in self.ssd_disks
        fs = FS_MAP.get(fs, fs)

        if not mount_point and not fs == "swap":
            return None

        options = self.mount_options.get(fs, self.mount_options["default"])
        if is_ssd:
            extra = self.ssd_extra_mount_options.get(fs)

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

        return dict(device="UUID=" + partition["uuid"],
                    mount_point=mount_point or "swap",
                    fs=fs,
                    options=options,
                    check=check,
                    )

    def print_fstab_line(self, dct, file=None):
        """ Prints line to '/etc/fstab' file.

        :param dct:
        :param file:
        """
        line = "{:41} {:<14} {:<7} {:<10} 0       {}".format(dct["device"],
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
    gs = libcalamares.globalstorage
    conf = libcalamares.job.configuration
    partitions = gs.value("partitions")
    root_mount_point = gs.value("rootMountPoint")
    mount_options = conf["mountOptions"]
    ssd_extra_mount_options = conf.get("ssdExtraMountOptions", {})
    generator = FstabGenerator(partitions, root_mount_point, mount_options, ssd_extra_mount_options)

    return generator.run()
