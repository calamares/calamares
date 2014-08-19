#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
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

import libcalamares
import os
import subprocess
from libcalamares.utils import check_chroot_call


def get_cpu():
    """ Check if system is an intel system. """

    process1 = subprocess.Popen(["hwinfo", "--cpu"], stdout=subprocess.PIPE)
    process2 = subprocess.Popen(["grep", "Model:[[:space:]]"],
                                stdin=process1.stdout, stdout=subprocess.PIPE)
    process1.stdout.close()
    out, err = process2.communicate()
    return out.decode().lower()


def set_mkinitcpio_hooks_and_modules(hooks, modules, root_mount_point):
    """ Set up mkinitcpio.conf """

    with open("/etc/mkinitcpio.conf", "r") as mkinitcpio_file:
        mklins = [x.strip() for x in mkinitcpio_file.readlines()]

    for i in range(len(mklins)):
        if mklins[i].startswith("HOOKS"):
            mklins[i] = 'HOOKS="%s"' % ' '.join(hooks)
        elif mklins[i].startswith("MODULES"):
            mklins[i] = 'MODULES="%s"' % ' '.join(modules)

    path = os.path.join(root_mount_point, "etc/mkinitcpio.conf")
    with open(path, "w") as mkinitcpio_file:
        mkinitcpio_file.write("\n".join(mklins) + "\n")

def modify_mkinitcpio_conf(partitions, root_mount_point):
    """ Modifies mkinitcpio.conf """

    cpu = get_cpu()
    swap_uuid = ""
    btrfs = ""
    hooks = ["base", "udev", "autodetect", "modconf", "block", "keyboard", "keymap"]
    modules = []

    # It is important that the plymouth hook comes before any encrypt hook
    plymouth_bin = os.path.join(root_mount_point, "usr/bin/plymouth")
    if os.path.exists(plymouth_bin):
        hooks.append("plymouth")

    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap_uuid = partition["uuid"]
        if partition["fs"] == "btrfs":
            btrfs = "yes"

    if swap_uuid is not "":
        hooks.extend(["resume", "filesystems"])
    else:
        hooks.extend(["filesystems"])

    if btrfs is "yes" and cpu is not "genuineintel":
        modules.append("crc32c")
    elif btrfs is "yes" and cpu is "genuineintel":
        modules.append("crc32c-intel")
    else:
        hooks.append("fsck")

    set_mkinitcpio_hooks_and_modules(hooks, modules, root_mount_point)


def run():
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    modify_mkinitcpio_conf(partitions, root_mount_point)
    return None
