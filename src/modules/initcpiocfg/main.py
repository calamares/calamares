#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Rohan Garg <rohan@kde.org>
#   SPDX-FileCopyrightText: 2015 2019-2020, Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@sidution.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares
from libcalamares.utils import debug, target_env_call
import os
from collections import OrderedDict

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configuring mkinitcpio.")


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


def detect_plymouth():
    """
    Checks existence (runnability) of plymouth in the target system.

    @return True if plymouth exists in the target, False otherwise
    """
    # Used to only check existence of path /usr/bin/plymouth in target
    return target_env_call(["sh", "-c", "which plymouth"]) == 0


def modify_mkinitcpio_conf(partitions, root_mount_point):
    """
    Modifies mkinitcpio.conf

    :param partitions:
    :param root_mount_point:
    """
    cpu = cpuinfo()
    swap_uuid = ""
    btrfs = ""
    lvm2 = ""
    hooks = ["base", "udev", "autodetect", "modconf", "block", "keyboard",
             "keymap"]
    modules = []
    files = []
    encrypt_hook = False
    openswap_hook = False
    unencrypted_separate_boot = False

    # It is important that the plymouth hook comes before any encrypt hook
    if detect_plymouth():
        hooks.append("plymouth")

    for partition in partitions:
        if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
            # Skip foreign swap
            continue

        if partition["fs"] == "linuxswap":
            swap_uuid = partition["uuid"]
            if "luksMapperName" in partition:
                openswap_hook = True

        if partition["fs"] == "btrfs":
            btrfs = "yes"

        if "lvm2" in partition["fs"]:
            lvm2 = "yes"

        if partition["mountPoint"] == "/" and "luksMapperName" in partition:
            encrypt_hook = True

        if (partition["mountPoint"] == "/boot" and "luksMapperName" not in partition):
            unencrypted_separate_boot = True

        if partition["mountPoint"] == "/usr":
            hooks.append("usr")

    if encrypt_hook:
        if detect_plymouth() and unencrypted_separate_boot:
            hooks.append("plymouth-encrypt")
        else:
            hooks.append("encrypt")
        if not unencrypted_separate_boot and \
           os.path.isfile(
               os.path.join(root_mount_point, "crypto_keyfile.bin")
               ):
            files.append("/crypto_keyfile.bin")

    if lvm2:
        hooks.append("lvm2")

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

    if not partitions:
        libcalamares.utils.warning("partitions is empty, {!s}".format(partitions))
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>{!s}</pre> to use." ).format("initcpiocfg"))
    if not root_mount_point:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}".format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use." ).format("initcpiocfg"))

    modify_mkinitcpio_conf(partitions, root_mount_point)

    return None
