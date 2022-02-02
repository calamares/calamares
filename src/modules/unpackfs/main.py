#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2014 Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   SPDX-FileCopyrightText: 2014 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2019 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2020 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import re
import shutil
import subprocess
import sys
import tempfile

import libcalamares

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext

def pretty_name():
    return _("Filling up filesystems.")

# This is going to be changed from various methods
status = pretty_name()

def pretty_status_message():
    return status

class UnpackEntry:
    """
    Extraction routine using rsync.

    :param source:
    :param sourcefs:
    :param destination:
    """
    __slots__ = ('source', 'sourcefs', 'destination', 'copied', 'total', 'exclude', 'excludeFile',
                 'mountPoint', 'weight')

    def __init__(self, source, sourcefs, destination):
        """
        @p source is the source file name (might be an image file, or
            a directory, too)
        @p sourcefs is a type indication; "file" is special, as is
            "squashfs".
        @p destination is where the files from the source go. This is
            **already** prefixed by rootMountPoint, so should be a
            valid absolute path within the host system.

        The members copied and total are filled in by the copying process.
        """
        self.source = source
        self.sourcefs = sourcefs
        self.destination = destination
        self.exclude = None
        self.excludeFile = None
        self.copied = 0
        self.total = 0
        self.mountPoint = None
        self.weight = 1

    def is_file(self):
        return self.sourcefs == "file"

    def do_count(self):
        """
        Counts the number of files this entry has.
        """
        # Need a name we can use like a global
        class counter(object):
            count = 0
        def cb_count(s):
            counter.count += 1

        if self.sourcefs == "squashfs":
            libcalamares.utils.host_env_process_output(["unsquashfs", "-l", self.source], cb_count)

        elif self.sourcefs == "ext4":
            libcalamares.utils.host_env_process_output(["find", self.mountPoint, "-type", "f"], cb_count)

        elif self.is_file():
            # Hasn't been mounted, copy directly; find handles both
            # files and directories.
            libcalamares.utils.host_env_process_output(["find", self.source, "-type", "f"], cb_count)

        self.total = counter.count
        return self.total

    def do_mount(self, base):
        """
        Mount given @p entry as loop device underneath @p base

        A *file* entry (e.g. one with *sourcefs* set to *file*)
        is not mounted and just ignored.

        :param base: directory to place all the mounts in.

        :returns: None, but throws if the mount failed
        """
        imgbasename = os.path.splitext(
            os.path.basename(self.source))[0]
        imgmountdir = os.path.join(base, imgbasename)
        os.makedirs(imgmountdir, exist_ok=True)

        # This is where it *would* go (files bail out before actually mounting)
        self.mountPoint = imgmountdir

        if self.is_file():
            return

        if os.path.isdir(self.source):
            r = libcalamares.utils.mount(self.source, imgmountdir, "", "--bind")
        elif os.path.isfile(self.source):
            r = libcalamares.utils.mount(self.source, imgmountdir, self.sourcefs, "loop")
        else: # self.source is a device
            r = libcalamares.utils.mount(self.source, imgmountdir, self.sourcefs, "")

        if r != 0:
            libcalamares.utils.debug("Failed to mount '{}' (fs={}) (target={})".format(self.source, self.sourcefs, imgmountdir))
            raise subprocess.CalledProcessError(r, "mount")


ON_POSIX = 'posix' in sys.builtin_module_names


def global_excludes():
    """
    List excludes for rsync.
    """
    lst = []
    extra_mounts = libcalamares.globalstorage.value("extraMounts")
    if extra_mounts is None:
        extra_mounts = []

    for extra_mount in extra_mounts:
        mount_point = extra_mount["mountPoint"]

        if mount_point:
            lst.extend(['--exclude', mount_point + '/'])

    return lst

def file_copy(source, entry, progress_cb):
    """
    Extract given image using rsync.

    :param source: Source file. This may be the place the entry's
        image is mounted, or if it's a single file, the entry's source value.
    :param entry: The UnpackEntry being copied.
    :param progress_cb: A callback function for progress reporting.
        Takes a number and a total-number.
    """
    import time

    dest = entry.destination

    # `source` *must* end with '/' otherwise a directory named after the source
    # will be created in `dest`: ie if `source` is "/foo/bar" and `dest` is
    # "/dest", then files will be copied in "/dest/bar".
    if not source.endswith("/") and not os.path.isfile(source):
        source += "/"

    num_files_total_local = 0
    num_files_copied = 0  # Gets updated through rsync output

    args = ['rsync', '-aHAXr', '--filter=-x trusted.overlay.*']
    args.extend(global_excludes())
    if entry.excludeFile:
        args.extend(["--exclude-from=" + entry.excludeFile])
    if entry.exclude:
        for f in entry.exclude:
            args.extend(["--exclude", f])
    args.extend(['--progress', source, dest])

    # last_num_files_copied trails num_files_copied, and whenever at least 107 more
    # files (file_count_chunk) have been copied, progress is reported and
    # last_num_files_copied is updated. The chunk size isn't "tidy"
    # so that all the digits of the progress-reported number change.
    #
    file_count_chunk = 107

    class counter(object):
        last_num_files_copied = 0
        last_timestamp_reported = time.time()
        last_total_reported = 0

    def output_cb(line):
        # rsync outputs progress in parentheses. Each line will have an
        # xfer and a chk item (either ir-chk or to-chk) as follows:
        #
        # - xfer#x => Interpret it as 'file copy try no. x'
        # - ir-chk=x/y, where:
        #     - x = number of files yet to be checked
        #     - y = currently calculated total number of files.
        # - to-chk=x/y, which is similar and happens once the ir-chk
        #   phase (collecting total files) is over.
        #
        # If you're copying directory with some links in it, the xfer#
        # might not be a reliable counter (for one increase of xfer, many
        # files may be created).
        m = re.findall(r'xfr#(\d+), ..-chk=(\d+)/(\d+)', line)

        if m:
            # we've got a percentage update
            num_files_remaining = int(m[0][1])
            num_files_total_local = int(m[0][2])
            # adjusting the offset so that progressbar can be continuesly drawn
            num_files_copied = num_files_total_local - num_files_remaining

            now = time.time()
            if (num_files_copied - counter.last_num_files_copied >= file_count_chunk) or (now - counter.last_timestamp_reported > 0.5):
                counter.last_num_files_copied = num_files_copied
                counter.last_timestamp_reported = now
                counter.last_total_reported = num_files_total_local
                progress_cb(num_files_copied, num_files_total_local)

    try:
        returncode = libcalamares.utils.host_env_process_output(args, output_cb)
    except subprocess.CalledProcessError as e:
        returncode = e.returncode

    progress_cb(counter.last_num_files_copied, counter.last_total_reported)  # Push towards 100%

    # Mark this entry as really done
    entry.copied = entry.total

    # 23 is the return code rsync returns if it cannot write extended
    # attributes (with -X) because the target file system does not support it,
    # e.g., the FAT EFI system partition. We need -X because distributions
    # using file system capabilities and/or SELinux require the extended
    # attributes. But distributions using SELinux may also have SELinux labels
    # set on files under /boot/efi, and rsync complains about those. The only
    # clean way would be to split the rsync into one with -X and
    # --exclude /boot/efi and a separate one without -X for /boot/efi, but only
    # if /boot/efi is actually an EFI system partition. For now, this hack will
    # have to do. See also:
    # https://bugzilla.redhat.com/show_bug.cgi?id=868755#c50
    # for the same issue in Anaconda, which uses a similar workaround.
    if returncode != 0 and returncode != 23:
        libcalamares.utils.warning("rsync failed with error code {}.".format(returncode))
        return _("rsync failed with error code {}.").format(returncode)

    return None


class UnpackOperation:
    """
    Extraction routine using unsquashfs.

    :param entries:
    """

    def __init__(self, entries):
        self.entries = entries
        self.entry_for_source = dict((x.source, x) for x in self.entries)
        self.total_weight = sum([e.weight for e in entries])

    def report_progress(self):
        """
        Pass progress to user interface
        """
        progress = float(0)

        current_total = 0
        current_done = 0  # Files count in the current entry
        complete_count = 0
        complete_weight = 0  # This much weight already finished
        for entry in self.entries:
            if entry.total == 0:
                # Total 0 hasn't counted yet
                continue
            if entry.total == entry.copied:
                complete_weight += entry.weight
                complete_count += 1
            else:
                # There is at most *one* entry in-progress
                current_total = entry.total
                current_done = entry.copied
                complete_weight += entry.weight * ( 1.0 * current_done ) / current_total
                break

        if current_total > 0:
            progress = ( 1.0 * complete_weight ) / self.total_weight

        global status
        status = _("Unpacking image {}/{}, file {}/{}").format((complete_count+1), len(self.entries), current_done, current_total)
        libcalamares.job.setprogress(progress)

    def run(self):
        """
        Extract given image using unsquashfs.

        :return:
        """
        global status
        source_mount_path = tempfile.mkdtemp()

        try:
            complete = 0
            for entry in self.entries:
                status = _("Starting to unpack {}").format(entry.source)
                libcalamares.job.setprogress( ( 1.0 * complete ) / len(self.entries) )
                entry.do_mount(source_mount_path)
                entry.do_count()  # Fill in the entry.total

                self.report_progress()
                error_msg = self.unpack_image(entry, entry.mountPoint)

                if error_msg:
                    return (_("Failed to unpack image \"{}\"").format(entry.source),
                            error_msg)
                complete += 1

            return None
        finally:
            shutil.rmtree(source_mount_path, ignore_errors=True, onerror=None)


    def unpack_image(self, entry, imgmountdir):
        """
        Unpacks image.

        :param entry:
        :param imgmountdir:
        :return:
        """
        def progress_cb(copied, total):
            """ Copies file to given destination target.

            :param copied:
            """
            entry.copied = copied
            if total > entry.total:
                entry.total = total
            self.report_progress()

        try:
            if entry.is_file():
                source = entry.source
            else:
                source = imgmountdir

            return file_copy(source, entry, progress_cb)
        finally:
            if not entry.is_file():
                subprocess.check_call(["umount", "-l", imgmountdir])


def get_supported_filesystems_kernel():
    """
    Reads /proc/filesystems (the list of supported filesystems
    for the current kernel) and returns a list of (names of)
    those filesystems.
    """
    PATH_PROCFS = '/proc/filesystems'

    if os.path.isfile(PATH_PROCFS) and os.access(PATH_PROCFS, os.R_OK):
        with open(PATH_PROCFS, 'r') as procfile:
            filesystems = procfile.read()
            filesystems = filesystems.replace(
                "nodev", "").replace("\t", "").splitlines()
            return filesystems

    return []


def get_supported_filesystems():
    """
    Returns a list of all the supported filesystems
    (valid values for the *sourcefs* key in an item.
    """
    return ["file"] + get_supported_filesystems_kernel()


def repair_root_permissions(root_mount_point):
    """
    If the / of the system gets permission 777, change it down
    to 755. Any other permission is left alone. This
    works around standard behavior from squashfs where
    permissions are (easily, accidentally) set to 777.
    """
    existing_root_mode = os.stat(root_mount_point).st_mode & 0o777
    if existing_root_mode == 0o777:
        try:
            os.chmod(root_mount_point, 0o755)  # Want / to be rwxr-xr-x
        except OSError as e:
            libcalamares.utils.warning("Could not set / to safe permissions: {}".format(e))
            # But ignore it


def extract_weight(entry):
    """
    Given @p entry, a dict representing a single entry in
    the *unpack* list, returns its weight (1, or whatever is
    set if it is sensible).
    """
    w =  entry.get("weight", None)
    if w:
        try:
            wi = int(w)
            return wi if wi > 0 else 1
        except ValueError:
            libcalamares.utils.warning("*weight* setting {!r} is not valid.".format(w))
        except TypeError:
            libcalamares.utils.warning("*weight* setting {!r} must be number.".format(w))
    return 1


def run():
    """
    Unsquash filesystem.
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if not root_mount_point:
        libcalamares.utils.warning("No mount point for root partition")
        return (_("No mount point for root partition"),
                _("globalstorage does not contain a \"rootMountPoint\" key."))
    if not os.path.exists(root_mount_point):
        libcalamares.utils.warning("Bad root mount point \"{}\"".format(root_mount_point))
        return (_("Bad mount point for root partition"),
                _("rootMountPoint is \"{}\", which does not exist.".format(root_mount_point)))

    if libcalamares.job.configuration.get("unpack", None) is None:
        libcalamares.utils.warning("No *unpack* key in job configuration.")
        return (_("Bad unpackfs configuration"),
                _("There is no configuration information."))

    supported_filesystems = get_supported_filesystems()

    # Bail out before we start when there are obvious problems
    #   - unsupported filesystems
    #   - non-existent sources
    #   - missing tools for specific FS
    for entry in libcalamares.job.configuration["unpack"]:
        source = os.path.abspath(entry["source"])
        sourcefs = entry["sourcefs"]

        if sourcefs not in supported_filesystems:
            libcalamares.utils.warning("The filesystem for \"{}\" ({}) is not supported by your current kernel".format(source, sourcefs))
            libcalamares.utils.warning(" ... modprobe {} may solve the problem".format(sourcefs))
            return (_("Bad unpackfs configuration"),
                    _("The filesystem for \"{}\" ({}) is not supported by your current kernel").format(source, sourcefs))
        if not os.path.exists(source):
            libcalamares.utils.warning("The source filesystem \"{}\" does not exist".format(source))
            return (_("Bad unpackfs configuration"),
                    _("The source filesystem \"{}\" does not exist").format(source))
        if sourcefs == "squashfs":
            if shutil.which("unsquashfs") is None:
                libcalamares.utils.warning("Failed to find unsquashfs")

                return (_("Bad unpackfs configuration"),
                        _("Failed to find unsquashfs, make sure you have the squashfs-tools package installed.") +
                        " " + _("Failed to unpack image \"{}\"").format(source))

    unpack = list()

    is_first = True
    for entry in libcalamares.job.configuration["unpack"]:
        source = os.path.abspath(entry["source"])
        sourcefs = entry["sourcefs"]
        destination = os.path.abspath(root_mount_point + entry["destination"])

        if not os.path.isdir(destination) and sourcefs != "file":
            libcalamares.utils.warning(("The destination \"{}\" in the target system is not a directory").format(destination))
            if is_first:
                return (_("Bad unpackfs configuration"),
                        _("The destination \"{}\" in the target system is not a directory").format(destination))
            else:
                libcalamares.utils.debug(".. assuming that the previous targets will create that directory.")

        unpack.append(UnpackEntry(source, sourcefs, destination))
        # Optional settings
        if entry.get("exclude", None):
            unpack[-1].exclude = entry["exclude"]
        if entry.get("excludeFile", None):
            unpack[-1].excludeFile = entry["excludeFile"]
        unpack[-1].weight = extract_weight(entry)

        is_first = False

    repair_root_permissions(root_mount_point)
    try:
        unpackop = UnpackOperation(unpack)
        return unpackop.run()
    finally:
        repair_root_permissions(root_mount_point)
