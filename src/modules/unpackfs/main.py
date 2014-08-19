#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#   Copyright 2014, Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   Copyright 2014, Philip Müller <philm@manjaro.org>
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
import shutil
import subprocess
import sys
import tempfile
from collections import namedtuple

from libcalamares import *

class UnpackEntry:
    __slots__= ['source', 'sourcefs', 'destination', 'copied', 'total']

    def __init__(self, source, sourcefs, destination):
        self.source = source
        self.sourcefs = sourcefs
        self.destination = destination
        self.copied = 0
        self.total = 0

ON_POSIX = 'posix' in sys.builtin_module_names


def file_copy(source, dest, progress_cb):
    # Environment used for executing rsync properly
    # Setting locale to C (fix issue with tr_TR locale)
    at_env = os.environ
    at_env["LC_ALL"] = "C"

    # `source` *must* end with '/' otherwise a directory named after the source
    # will be created in `dest`: ie if `source` is "/foo/bar" and `dest` is
    # "/dest", then files will be copied in "/dest/bar".
    source += "/"

    process = subprocess.Popen(['rsync', '-ar', '--progress', source, dest],
                               env=at_env,
                               bufsize=1,
                               stdout=subprocess.PIPE,
                               close_fds=ON_POSIX)

    for line in iter(process.stdout.readline, b''):
        # small comment on this regexp.
        # rsync outputs three parameters in the progress.
        # xfer#x => i try to interpret it as 'file copy try no. x'
        # to-check=x/y, where:
        #  - x = number of files yet to be checked
        #  - y = currently calculated total number of files.
        # but if you're copying directory with some links in it, the xfer#
        # might not be a reliable counter (for one increase of xfer, many
        # files may be created).
        # In case of manjaro, we pre-compute the total number of files.
        # therefore we can easily subtract x from y in order to get real files
        # copied / processed count.
        m = re.findall(r'xfr#(\d+), ir-chk=(\d+)/(\d+)', line.decode())
        if m:
            # we've got a percentage update
            num_files_remaining = int(m[0][1])
            num_files_total_local = int(m[0][2])
            # adjusting the offset so that progressbar can be continuesly drawn
            num_files_copied = num_files_total_local - num_files_remaining

            # I guess we're updating every 100 files...
            if num_files_copied % 100 == 0:
                progress_cb(num_files_copied)
    process.wait()
    if process.returncode != 0:
        return "rsync failed with error code {}.".format(process.returncode)
    return None


class UnpackOperation:

    def __init__(self, entries):
        self.entries = entries
        self.entry_for_source = dict((x.source, x) for x in self.entries)

    def report_progress(self):
        progress = float(0)
        for entry in self.entries:
            if entry.total == 0:
                continue

            partialprogress = 0.05  # Having a total !=0 gives 5%

            partialprogress += 0.95 * \
                (entry.copied / float(entry.total))
            progress += partialprogress / len(self.entries)

        job.setprogress(progress)

    def run(self):
        source_mount_path = tempfile.mkdtemp()
        try:
            for entry in self.entries:
                imgbasename = os.path.splitext(
                    os.path.basename(entry.source))[0]
                imgmountdir = os.path.join(source_mount_path, imgbasename)
                os.mkdir(imgmountdir)

                self.mount_image(entry, imgmountdir)

                fslist = ""

                if entry.sourcefs == "squashfs":
                    fslist = subprocess.check_output(["unsquashfs",
                                                        "-l",
                                                        entry.source])
                if entry.sourcefs == "ext4":
                    fslist = subprocess.check_output(["find",
                                                      imgmountdir,
                                                      "-type", "f"])
                entry.total = len(fslist.splitlines())

                self.report_progress()
                error_msg = self.unpack_image(entry, imgmountdir)
                if error_msg:
                    return ("Failed to unpack image {}".format(entry.source),
                        error_msg)
            return None
        finally:
            shutil.rmtree(source_mount_path)

    def mount_image(self, entry, imgmountdir):
        subprocess.check_call(["mount",
                               entry.source,
                               imgmountdir,
                               "-t",
                               entry.sourcefs,
                               "-o", "loop"])

    def unpack_image(self, entry, imgmountdir):
        def progress_cb(copied):
            entry.copied = copied
            self.report_progress()

        try:
            return file_copy(imgmountdir,
                      entry.destination,
                      progress_cb)
        finally:
            subprocess.check_call(["umount", "-l", imgmountdir])


def run():
    # from globalstorage: rootMountPoint
    # from job.configuration:
    # the path to where to mount the source image(s) for copying
    # an ordered list of unpack mappings for image file <-> target dir relative
    # to rootMountPoint, e.g.:
    # configuration:
    #     unpack:
    #         - source: "/path/to/filesystem.img"
    #           sourcefs: "ext4"
    #           destination: ""
    #         - source: "/path/to/another/filesystem.sqfs"
    #           sourcefs: "squashfs"
    #           destination: ""

    root_mount_point = globalstorage.value("rootMountPoint")
    if not root_mount_point:
        return ("No mount point for root partition in globalstorage",
                "globalstorage does not contain a \"rootMountPoint\" key, "
                "doing nothing")
    if not os.path.exists(root_mount_point):
        return ("Bad mount point for root partition in globalstorage",
                "globalstorage[\"rootMountPoint\"] is \"{}\", which does not "
                "exist, doing nothing".format(root_mount_point))
    unpack = list()

    for entry in job.configuration["unpack"]:
        source = os.path.abspath(entry["source"])

        sourcefs = entry["sourcefs"]
        if sourcefs not in ["ext4", "squashfs"]:
            return "Bad filesystem", "sourcefs=\"{}\"".format(sourcefs)

        destination = os.path.abspath(root_mount_point + entry["destination"])

        if not os.path.isfile(source):
            return ("Bad source", "source=\"{}\"".format(source))
        # Add test for supported filesystems
        if not os.path.isdir(destination):
            return ("Bad destination",
                    "destination=\"{}\"".format(destination))

        unpack.append(UnpackEntry(source, sourcefs, destination))

    unpackop = UnpackOperation(unpack)
    return unpackop.run()
