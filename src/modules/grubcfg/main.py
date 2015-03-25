#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014-2015, Philip Müller <philm@manjaro.org>
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

import libcalamares
import os


def modify_grub_default(partitions, root_mount_point, distributor):
    """ Configures '/etc/default/grub' for hibernation and plymouth.

    :param partitions:
    :param root_mount_point:
    :param distributor:
    :return:
    """
    default_dir = os.path.join(root_mount_point, "etc/default")
    default_grub = os.path.join(default_dir, "grub")
    distributor_replace = distributor.replace("'", "'\\''")
    plymouth_bin = libcalamares.utils.chroot_call("sh -c \"which plymouth\"")
    use_splash = ""
    swap_uuid = ""

    if plymouth_bin == 0:
        use_splash = "splash"

    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap_uuid = partition["uuid"]

    if swap_uuid != "":
        kernel_cmd = "GRUB_CMDLINE_LINUX_DEFAULT=\"resume=UUID={!s} quiet {!s}\"".format(swap_uuid, use_splash)
    else:
        kernel_cmd = "GRUB_CMDLINE_LINUX_DEFAULT=\"quiet {!s}\"".format(use_splash)

    distributor_line = "GRUB_DISTRIBUTOR=\"{!s}\"".format(distributor_replace)

    if not os.path.exists(default_dir):
        os.mkdir(default_dir)

    have_kernel_cmd = False
    have_distributor_line = False

    if "overwrite" in libcalamares.job.configuration:
        overwrite = libcalamares.job.configuration["overwrite"]
    else:
        overwrite = False

    if os.path.exists(default_grub) and not overwrite:
        with open(default_grub, 'r') as grub_file:
            lines = [x.strip() for x in grub_file.readlines()]

        for i in range(len(lines)):
            if lines[i].startswith("#GRUB_CMDLINE_LINUX_DEFAULT"):
                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif lines[i].startswith("GRUB_CMDLINE_LINUX_DEFAULT"):
                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif lines[i].startswith("#GRUB_DISTRIBUTOR") or lines[i].startswith("GRUB_DISTRIBUTOR"):
                lines[i] = distributor_line
                have_distributor_line = True
    else:
        lines = []
        if "defaults" in libcalamares.job.configuration:
            for key, value in libcalamares.job.configuration["defaults"].items():
                if value.__class__.__name__ == "bool":
                    if value:
                        escaped_value = "true"
                    else:
                        escaped_value = "false"
                else:
                    escaped_value = str(value).replace("'", "'\\''")
                lines.append("{!s}=\"{!s}\"".format(key, escaped_value))

    if not have_kernel_cmd:
        lines.append(kernel_cmd)

    if not have_distributor_line:
        lines.append(distributor_line)

    with open(default_grub, 'w') as grub_file:
        grub_file.write("\n".join(lines) + "\n")

    return None


def run():
    """ Calls routine with given parameters to modify '/etc/default/grub'.

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    branding = libcalamares.globalstorage.value("branding")
    distributor = branding["bootloaderEntryName"]
    return modify_grub_default(partitions, root_mount_point, distributor)
