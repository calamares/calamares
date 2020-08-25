#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares
import os
import stat
import subprocess
from time import gmtime, strftime, sleep
from math import gcd

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext

def pretty_name():
    return _("Installing data.")

def lcm(a, b):
    """
    Computes the Least Common Multiple of 2 numbers
    """
    return a * b / gcd(a, b)

def get_device_size(device):
    """
    Returns a filesystem's total size and block size in bytes.
    For block devices, block size is the device's block size.
    For other files (fs images), block size is 1 byte.

    @param device: str
        Absolute path to the device or filesystem image.
    @return: tuple(int, int)
        The filesystem's size and its block size.
    """
    mode = os.stat(device).st_mode
    if stat.S_ISBLK(mode):
        basedevice = ""
        partition = os.path.basename(device)
        tmp = partition
        while len(tmp) > 0:
            tmp = tmp[:-1]
            if os.path.exists("/sys/block/" + tmp):
                basedevice = tmp
                break
        # Get device block size
        file = open("/sys/block/" + basedevice + "/queue/hw_sector_size")
        blocksize = int(file.readline())
        file.close()
        # Get partition size
        file = open("/sys/block/" + basedevice + "/" + partition + "/size")
        size = int(file.readline()) * blocksize
        file.close()
    else:
        size = os.path.getsize(device)
        blocksize = 1

    return size, blocksize

class RawFSLowSpaceError(Exception):
    pass

class RawFSItem:
    __slots__ = ['source', 'destination', 'filesystem', 'resize']

    def copy(self, current=0, total=1):
        """
        Copies a raw filesystem on a disk partition, and grow it to the full destination
        partition's size if required.

        @param current: int
            The index of the current item in the filesystems list
            (used for progress reporting)
        @param total: int
            The number of items in the filesystems list
            (used for progress reporting)
        """
        count = 0

        libcalamares.utils.debug("Copying {} to {}".format(self.source, self.destination))
        if libcalamares.job.configuration.get("bogus", False):
            return

        srcsize, srcblksize = get_device_size(self.source)
        destsize, destblksize = get_device_size(self.destination)

        if destsize < srcsize:
            raise RawFSLowSpaceError
            return

        # Compute transfer block size (100x the LCM of the block sizes seems a good fit)
        blksize = int(100 * lcm(srcblksize, destblksize))

        # Execute copy
        src = open(self.source, "rb")
        dest = open(self.destination, "wb")
        buffer = src.read(blksize)
        while len(buffer) > 0:
            dest.write(buffer)
            count += len(buffer)
            # Compute job progress
            progress = ((count / srcsize) + (current)) / total
            libcalamares.job.setprogress(progress)
            # Read next data block
            buffer = src.read(blksize)
        src.close()
        dest.close()

        if self.resize:
            if "ext" in self.filesystem:
                libcalamares.utils.debug("Resizing filesystem on {}".format(self.destination))
                subprocess.run(["e2fsck", "-f", "-y", self.destination])
                subprocess.run(["resize2fs", self.destination])

    def __init__(self, config, device, fs):
        libcalamares.utils.debug("Adding an entry for raw copy of {} to {}".format(
                config["source"], device))
        self.source = os.path.realpath(config["source"])
        # If source is a mount point, look for the actual device mounted on it
        if os.path.ismount(self.source):
            procmounts = open("/proc/mounts", "r")
            for line in procmounts:
                if self.source in line.split():
                    self.source = line.split()[0]
                    break

        self.destination = device
        self.filesystem = fs
        try:
            self.resize = bool(config["resize"])
        except KeyError:
            self.resize = False

def update_global_storage(item, gs):
    for partition in gs:
        if partition["device"] == item.destination:
            ret = subprocess.run(["blkid", "-s", "UUID", "-o", "value", item.destination],
                    stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
            if ret.returncode == 0:
                libcalamares.utils.debug("Setting {} UUID to {}".format(item.destination,
                        ret.stdout.rstrip()))
                gs[gs.index(partition)]["uuid"] = ret.stdout.rstrip()
                gs[gs.index(partition)]["source"] = item.source

    libcalamares.globalstorage.remove("partitions")
    libcalamares.globalstorage.insert("partitions", gs)

def run():
    """Raw filesystem copy module"""
    filesystems = list()
    partitions = libcalamares.globalstorage.value("partitions")

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use." ).format("rawfs"))

    libcalamares.utils.debug("Copying {!s} raw partitions.".format(len(partitions)))
    for partition in partitions:
        if partition["mountPoint"]:
            for src in libcalamares.job.configuration["targets"]:
                if src["mountPoint"] == partition["mountPoint"]:
                    filesystems.append(RawFSItem(src, partition["device"], partition["fs"]))

    for item in filesystems:
        try:
            item.copy(filesystems.index(item), len(filesystems))
        except RawFSLowSpaceError:
            return ("Not enough free space",
                "{} partition is too small to copy {} on it".format(item.destination, item.source))
        update_global_storage(item, partitions)

    return None
