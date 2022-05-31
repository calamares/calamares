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


def detect_plymouth():
    """
    Checks existence (runnability) of plymouth in the target system.

    @return True if plymouth exists in the target, False otherwise
    """
    # Used to only check existence of path /usr/bin/plymouth in target
    return target_env_call(["sh", "-c", "which plymouth"]) == 0


class cpuinfo(object):
    """
    Object describing the current CPU's characteristics. It may be
    be considered a named tuple, there's no behavior here.

    Fields in the object:
        - is_intel (if it's definitely an Intel CPU)
        - is_amd (if it's definitely an AMD CPU)
        - number_of_cores
    It is possible for both is_* fields to be False.
    """
    def __init__(self):
        self.is_intel = False
        self.is_amd = False
        self.number_of_cores = 0

        cpu = self._cpuinfo()
        self.is_intel = cpu['proc0']['vendor_id'].lower() == "genuineintel"
        self.is_amd = cpu['proc0']['vendor_id'].lower() == "authenticamd"
        self.number_of_cores = len(cpu)

    @staticmethod
    def _cpuinfo():
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


def get_host_initcpio():
    """
    Reads the host system mkinitcpio.conf and returns all
    the lines from that file, or an empty list if it does
    not exist.
    """
    hostfile = "/etc/mkinitcpio.conf"
    try:
        with open(hostfile, "r") as mkinitcpio_file:
            mklins = [x.strip() for x in mkinitcpio_file.readlines()]
    except FileNotFoundError:
        libcalamares.utils.debug(f"Could not open host file {hostfile}")
        mklins = []

    return mklins


def write_mkinitcpio_lines(hooks, modules, files, root_mount_point):
    """
    Set up mkinitcpio.conf.

    :param hooks:
    :param modules:
    :param files:
    :param root_mount_point:
    """
    mklins = get_host_initcpio()

    target_path = os.path.join(root_mount_point, "etc/mkinitcpio.conf")
    with open(target_path, "w") as mkinitcpio_file:
        for line in mklins:
            # Replace HOOKS, MODULES and FILES lines with what we
            # have found via find_initcpio_features()
            if line.startswith("HOOKS"):
                line = 'HOOKS="{!s}"'.format(' '.join(hooks))
            elif line.startswith("MODULES"):
                line = 'MODULES="{!s}"'.format(' '.join(modules))
            elif lines.startswith("FILES"):
                line = 'FILES="{!s}"'.format(' '.join(files))
            mkinitcpio_file.write(line + "\n")


def find_initcpio_features(partitions, root_mount_point):
    """
    Returns a tuple (hooks, modules, files) needed to support
    the given @p partitions (filesystems types, encryption, etc)
    in the target.

    :param partitions: (from GS)
    :param root_mount_point: (from GS)

    :return 3-tuple of lists
    """
    hooks = [
        "base",
        "udev",
        "autodetect",
        "modconf",
        "block",
        "keyboard",
        "keymap",
        "consolefont",
    ]
    modules = []
    files = []

    swap_uuid = ""
    uses_btrfs = False
    uses_zfs = False
    uses_lvm2 = False
    encrypt_hook = False
    openswap_hook = False
    unencrypted_separate_boot = False

    # It is important that the plymouth hook comes before any encrypt hook
    if detect_plymouth():
        hooks.append("plymouth")

    for partition in partitions:
        hooks.extend(["filesystems"])

        if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
            # Skip foreign swap
            continue

        if partition["fs"] == "linuxswap":
            swap_uuid = partition["uuid"]
            if "luksMapperName" in partition:
                openswap_hook = True

        if partition["fs"] == "btrfs":
            uses_btrfs = True

        # In addition to checking the filesystem, check to ensure that zfs is enabled
        if partition["fs"] == "zfs" and libcalamares.globalstorage.contains("zfsPoolInfo"):
            uses_zfs = True

        if "lvm2" in partition["fs"]:
            uses_lvm2 = True

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
        crypto_file = "crypto_keyfile.bin"
        if not unencrypted_separate_boot and \
           os.path.isfile(
               os.path.join(root_mount_point, crypto_file)
               ):
            files.append(f"/{crypto_file}")

    if uses_lvm2:
        hooks.append("lvm2")

    if uses_zfs:
        hooks.append("zfs")

    if swap_uuid != "":
        hooks.extend(["resume"])
        if encrypt_hook and openswap_hook:
            hooks.extend(["openswap"])

    if uses_btrfs:
        modules.append("crc32c-intel" if cpuinfo().is_intel else "crc32c")
    else:
        hooks.append("fsck")

    return (hooks, modules, files)


def run():
    """
    Calls routine with given parameters to modify "/etc/mkinitcpio.conf".

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if not partitions:
        libcalamares.utils.warning(f"partitions are empty, {partitions}")
        return (_("Configuration Error"),
                _("No partitions are defined for <pre>initcpiocfg</pre>."))
    if not root_mount_point:
        libcalamares.utils.warning(f"rootMountPoint is empty, {root_mount_point}")
        return (_("Configuration Error"),
                _("No root mount point for <pre>initcpiocfg</pre>."))

    hooks, modules, files = find_initcpio_features(partitions, root_mount_point)
    write_mkinitcpio_lines(hooks, modules, files, root_mount_point)

    return None
