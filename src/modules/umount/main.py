#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
#   Copyright 2016, Anke Boersma <demm@kaosx.us>
#   Copyright 2018, Adriaan de Groot <groot@kde.org>
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
import subprocess
import shutil

import libcalamares
from libcalamares.utils import gettext_path, gettext_languages

import gettext
_translation = gettext.translation("calamares-python",
                                   localedir=gettext_path(),
                                   languages=gettext_languages(),
                                   fallback=True)
_ = _translation.gettext
_n = _translation.ngettext


def pretty_name():
    return _( "Unmount file systems." )


def list_mounts(root_mount_point):
    """ List mount points.

    :param root_mount_point:
    :return:
    """
    lst = []

    for line in open("/etc/mtab").readlines():
        device, mount_point, _ = line.split(" ", 2)

        if mount_point.startswith(root_mount_point):
            lst.append((device, mount_point))

    return lst


def run():
    """ Unmounts given mountpoints in decreasing order.

    :return:
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if(libcalamares.job.configuration and
       "srcLog" in libcalamares.job.configuration and
       "destLog" in libcalamares.job.configuration):
        log_source = libcalamares.job.configuration["srcLog"]
        log_destination = libcalamares.job.configuration["destLog"]
        # Relocate log_destination into target system
        log_destination = '{!s}/{!s}'.format(root_mount_point, log_destination)
        # Make sure source is a string
        log_source = '{!s}'.format(log_source)

        # copy installation log before umount
        if os.path.exists(log_source):
            try:
                shutil.copy2(log_source, log_destination)
            except Exception as e:
                libcalamares.utils.warning("Could not preserve file {!s}, "
                                       "error {!s}".format(log_source, e))

    if not root_mount_point:
        return ("No mount point for root partition in globalstorage",
                "globalstorage does not contain a \"rootMountPoint\" key, "
                "doing nothing")

    if not os.path.exists(root_mount_point):
        return ("Bad mount point for root partition in globalstorage",
                "globalstorage[\"rootMountPoint\"] is \"{}\", which does not "
                "exist, doing nothing".format(root_mount_point))

    lst = list_mounts(root_mount_point)
    # Sort the list by mount point in decreasing order. This way we can be sure
    # we unmount deeper dirs first.
    lst.sort(key=lambda x: x[1], reverse=True)

    for device, mount_point in lst:
        subprocess.check_call(["umount", "-lv", mount_point])

    os.rmdir(root_mount_point)

    return None
