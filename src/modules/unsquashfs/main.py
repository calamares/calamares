#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

UnpackEntry = namedtuple(
    'UnpackEntry', ['source', 'destination'])

class UnpackStatusEntry:
    __slots__= ['copied', 'total']

    def __init__(self):
        self.copied = 0
        self.total = 0

ON_POSIX = 'posix' in sys.builtin_module_names


def file_copy(source, dest, progress_cb):
    # Environment used for executing rsync properly
    # Setting locale to C (fix issue with tr_TR locale)
    at_env = os.environ
    at_env["LC_ALL"] = "C"

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


class UnsquashOperation:

    def __init__(self, unpack):
        self.unpacklist = unpack
        self.unpackstatus = dict()
        for entry in unpack:
            self.unpackstatus[entry.source] = UnpackStatusEntry()

    def update_copy_progress(self, source, nfiles):
        if source in self.unpackstatus:
            self.unpackstatus[source].copied = nfiles
            self.report_progress()

    def report_progress(self):
        progress = float(0)
        for status_entry in self.unpackstatus:
            if status_entry.total == 0:
                continue

            partialprogress = 0.05  # Having a total !=0 gives 5%

            partialprogress += 0.95 * \
                (status_entry.copied / float(status_entry.total))
            progress += partialprogress / len(self.unpackstatus)

        job.setprogress(progress)

    def run(self):
        source_mount_path = tempfile.mkdtemp()
        try:
            for entry in self.unpacklist:
                sqfslist = subprocess.check_output(["unsquashfs",
                                                    "-l",
                                                    entry.source])
                filescount = len(sqfslist.splitlines())
                self.unpackstatus[entry.source].total = filescount

                imgbasename = os.path.splitext(
                    os.path.basename(entry.source))[0]
                imgmountdir = os.path.join(source_mount_path, imgbasename)
                os.mkdir(imgmountdir)
                self.report_progress()
                self.unsquash_image(entry, imgmountdir)
        finally:
            shutil.rmtree(source_mount_path)

    def unsquash_image(self, entry, imgmountdir):
        subprocess.check_call(["mount",
                               entry.source,
                               imgmountdir,
                               "-t", "squashfs", "-o", "loop"])
        try:
            file_copy(imgmountdir,
                      entry.destination,
                      self.report_progress)
        finally:
            subprocess.check_call(["umount", "-l", imgmountdir])


def run():
    # from globalstorage: rootMountPoint
    # from job.configuration:
    # the path to where to mount the source image(s) for copying
    # an ordered list of unpack mappings for sqfs file <-> target dir relative
    # to rootMountPoint, e.g.:
    # configuration:
    #     unpack:
    #         - source: "/path/to/squashfs/image.sqfs"
    #           destination: ""
    #         - source: "/path/to/another/image.sqfs"
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
        destination = os.path.abspath(root_mount_point + entry["destination"])

        if not os.path.isfile(source):
            return ("Bad source", "source=\"{}\"".format(source))
        if not os.path.isdir(destination):
            return ("Bad destination",
                    "destination=\"{}\"".format(destination))

        unpack.append(UnpackEntry(source, destination))

    unsquashop = UnsquashOperation(unpack)
    return unsquashop.run()
