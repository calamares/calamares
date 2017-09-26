#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Rohan Garg <rohan@kde.org>
#   Copyright 2015, Philip Müller <philm@manjaro.org>
#   Copyright 2017, Alf Gaida <agaida@sidution.org>
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
from collections import OrderedDict


def cpuinfo():
    """
    Return the information in /proc/cpuinfo as a dictionary in the following
    format:

    cpu_info['proc0']={...}
    cpu_info['proc1']={...}
    """
    cpu_info = OrderedDict()
    procinfo = OrderedDict()

    nprocs = 0

    with open('/proc/cpuinfo') as cpuinfo_file:
        for line in cpuinfo_file:
            if not line.strip():
                # end of one processor
                cpu_info["proc{!s}".format(nprocs)] = procinfo
                nprocs += 1
                # Reset
                procinfo = OrderedDict()
            else:
                if len(line.split(':')) == 2:
                    splitted_line = line.split(':')[1].strip()
                    procinfo[line.split(':')[0].strip()] = splitted_line
                else:
                    procinfo[line.split(':')[0].strip()] = ''

    return cpu_info


def write_mkinitcpio_lines(hooks, modules, files, root_mount_point):
    """
    Set up mkinitcpio.conf.

    :param hooks:
    :param modules:
    :param files:
    :param root_mount_point:
    """
    hostfile = "/etc/mkinitcpio.conf"
    try:
        with open(hostfile, "r") as mkinitcpio_file:
            mklins = [x.strip() for x in mkinitcpio_file.readlines()]
    except FileNotFoundError:
        libcalamares.utils.debug("Could not open host file '%s'" % hostfile)
        mklins = []

    for i in range(len(mklins)):
        if mklins[i].startswith("HOOKS"):
            joined_hooks = ' '.join(hooks)
            mklins[i] = "HOOKS=\"{!s}\"".format(joined_hooks)
        elif mklins[i].startswith("MODULES"):
            joined_modules = ' '.join(modules)
            mklins[i] = "MODULES=\"{!s}\"".format(joined_modules)
        elif mklins[i].startswith("FILES"):
            joined_files = ' '.join(files)
            mklins[i] = "FILES=\"{!s}\"".format(joined_files)

    path = os.path.join(root_mount_point, "etc/mkinitcpio.conf")

    with open(path, "w") as mkinitcpio_file:
        mkinitcpio_file.write("\n".join(mklins) + "\n")


def modify_mkinitcpio_conf(partitions, root_mount_point):
    """
    Modifies mkinitcpio.conf

    :param partitions:
    :param root_mount_point:
    """
    cpu = cpuinfo()
    swap_uuid = ""
    btrfs = ""
    hooks = ["base", "udev", "autodetect", "modconf", "block", "keyboard",
             "keymap"]
    modules = []
    files = []
    encrypt_hook = False
    openswap_hook = False
    unencrypted_separate_boot = False

    # It is important that the plymouth hook comes before any encrypt hook
    plymouth_bin = os.path.join(root_mount_point, "usr/bin/plymouth")
    if os.path.exists(plymouth_bin):
        hooks.append("plymouth")

    for partition in partitions:
        if partition["fs"] == "linuxswap":
            swap_uuid = partition["uuid"]
            if "luksMapperName" in partition:
                openswap_hook = True

        if partition["fs"] == "btrfs":
            btrfs = "yes"

        if partition["mountPoint"] == "/" and "luksMapperName" in partition:
            encrypt_hook = True

        if (partition["mountPoint"] == "/boot"
                and "luksMapperName" not in partition):
            unencrypted_separate_boot = True

    if encrypt_hook:
        hooks.append("encrypt")
        if not unencrypted_separate_boot and \
           os.path.isfile(
               os.path.join(root_mount_point, "crypto_keyfile.bin")
               ):
            files.append("/crypto_keyfile.bin")

    if swap_uuid != "":
        if encrypt_hook and openswap_hook:
            hooks.extend(["openswap"])
        hooks.extend(["resume", "filesystems"])
    else:
        hooks.extend(["filesystems"])

    if btrfs == "yes" and cpu['proc0']['vendor_id'].lower() != "genuineintel":
        modules.append("crc32c")
    elif (btrfs == "yes"
          and cpu['proc0']['vendor_id'].lower() == "genuineintel"):
        modules.append("crc32c-intel")
    else:
        hooks.append("fsck")

    write_mkinitcpio_lines(hooks, modules, files, root_mount_point)


def run():
    """
    Calls routine with given parameters to modify '/etc/mkinitcpio.conf'.

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    modify_mkinitcpio_conf(partitions, root_mount_point)

    return None
