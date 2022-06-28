#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014-2015 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2015-2017 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2017-2018 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares
import os
import re

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configure GRUB.")


def get_grub_config_path(root_mount_point):
    """
    Figures out where to put the grub config files. Returns
    a the full path of a file inside that
    directory, as "the config file".

    Returns a path into @p root_mount_point.
    """
    default_dir = os.path.join(root_mount_point, "etc/default")
    default_config_file = "grub"

    if "prefer_grub_d" in libcalamares.job.configuration and libcalamares.job.configuration["prefer_grub_d"]:
        possible_dir = os.path.join(root_mount_point, "etc/default/grub.d")
        if os.path.exists(possible_dir) and os.path.isdir(possible_dir):
            default_dir = possible_dir
            default_config_file = "00calamares"

    if not os.path.exists(default_dir):
        try:
            os.mkdir(default_dir)
        except Exception as error:
            # exception as error is still redundant, but it print out the error
            # identify a solution for each exception and
            # if possible and code it within.
            libcalamares.utils.debug(f"Failed to create {default_dir}")
            libcalamares.utils.debug(f"{error}")
            raise

    return os.path.join(default_dir, default_config_file)


def get_zfs_root():
    """
    Looks in global storage to find the zfs root

    :return: A string containing the path to the zfs root or None if it is not found
    """

    zfs = libcalamares.globalstorage.value("zfsDatasets")

    if not zfs:
        libcalamares.utils.warning("Failed to locate zfs dataset list")
        return None

    # Find the root dataset
    for dataset in zfs:
        try:
            if dataset["mountpoint"] == "/":
                return dataset["zpool"] + "/" + dataset["dsName"]
        except KeyError:
            # This should be impossible
            libcalamares.utils.warning("Internal error handling zfs dataset")
            raise

    return None


def modify_grub_default(partitions, root_mount_point, distributor):
    """
    Configures '/etc/default/grub' for hibernation and plymouth.

    @see bootloader/main.py, for similar handling of kernel parameters

    :param partitions:
    :param root_mount_point:
    :param distributor: name of the distributor to fill in for
        GRUB_DISTRIBUTOR. Must be a string. If the job setting
        *keep_distributor* is set, then this is only used if no
        GRUB_DISTRIBUTOR is found at all (otherwise, when *keep_distributor*
        is set, the GRUB_DISTRIBUTOR lines are left unchanged).
        If *keep_distributor* is unset or false, then GRUB_DISTRIBUTOR
        is always updated to set this value.
    :return:
    """
    default_grub = get_grub_config_path(root_mount_point)
    distributor_replace = distributor.replace("'", "'\\''")
    dracut_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which dracut"]
        )
    plymouth_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which plymouth"]
        )

    # Shell exit value 0 means success
    have_plymouth = plymouth_bin == 0
    have_dracut = dracut_bin == 0

    use_splash = ""
    swap_uuid = ""
    swap_outer_uuid = ""
    swap_outer_mappername = None
    no_save_default = False
    unencrypted_separate_boot = any(p["mountPoint"] == "/boot" and "luksMapperName" not in p for p in partitions)
    # If there is no dracut, and the root partition is ZFS, this gets set below
    zfs_root_path = None

    for partition in partitions:
        if partition["mountPoint"] in ("/", "/boot") and partition["fs"] in ("btrfs", "f2fs"):
            no_save_default = True
            break

    if have_plymouth:
        use_splash = "splash"

    cryptdevice_params = []

    if have_dracut:
        for partition in partitions:
            if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
                # Skip foreign swap
                continue
            has_luks = "luksMapperName" in partition
            if partition["fs"] == "linuxswap" and not has_luks:
                swap_uuid = partition["uuid"]

            if partition["fs"] == "linuxswap" and has_luks:
                swap_outer_uuid = partition["luksUuid"]
                swap_outer_mappername = partition["luksMapperName"]

            if partition["mountPoint"] == "/" and has_luks:
                cryptdevice_params = [f"rd.luks.uuid={partition['luksUuid']}"]
    else:
        for partition in partitions:
            if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
                # Skip foreign swap
                continue
            has_luks = "luksMapperName" in partition
            if partition["fs"] == "linuxswap" and not has_luks:
                swap_uuid = partition["uuid"]

            if partition["fs"] == "linuxswap" and has_luks:
                swap_outer_mappername = partition["luksMapperName"]

            if partition["mountPoint"] == "/" and has_luks:
                cryptdevice_params = [
                    f"cryptdevice=UUID={partition['luksUuid']}:{partition['luksMapperName']}",
                    f"root=/dev/mapper/{partition['luksMapperName']}"
                ]

            if partition["fs"] == "zfs" and partition["mountPoint"] == "/":
                zfs_root_path = get_zfs_root()

    kernel_params = libcalamares.job.configuration.get("kernel_params", ["quiet"])

    # Currently, grub doesn't detect this properly so it must be set manually
    if zfs_root_path:
        kernel_params.insert(0, "zfs=" + zfs_root_path)

    if cryptdevice_params:
        kernel_params.extend(cryptdevice_params)

    if use_splash:
        kernel_params.append(use_splash)

    if swap_uuid:
        kernel_params.append(f"resume=UUID={swap_uuid}")

    if have_dracut and swap_outer_uuid:
        kernel_params.append(f"rd.luks.uuid={swap_outer_uuid}")
    if swap_outer_mappername:
        kernel_params.append(f"resume=/dev/mapper/{swap_outer_mappername}")

    if "overwrite" in libcalamares.job.configuration:
        overwrite = libcalamares.job.configuration["overwrite"]
    else:
        overwrite = False

    distributor_line = f"GRUB_DISTRIBUTOR='{distributor_replace}'"
    kernel_cmd = f'GRUB_CMDLINE_LINUX_DEFAULT="{" ".join(kernel_params)}"'
    have_kernel_cmd = False
    have_distributor_line = False
    if os.path.exists(default_grub) and not overwrite:
        with open(default_grub, 'r') as grub_file:
            lines = [x.strip() for x in grub_file.readlines()]

        for i in range(len(lines)):
            if lines[i].startswith("#GRUB_CMDLINE_LINUX_DEFAULT"):
                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif lines[i].startswith("GRUB_CMDLINE_LINUX_DEFAULT"):
                regex = re.compile(r"^GRUB_CMDLINE_LINUX_DEFAULT\s*=\s*")
                line = regex.sub("", lines[i])
                line = line.lstrip()
                line = line.lstrip("\"")
                line = line.lstrip("'")
                line = line.rstrip()
                line = line.rstrip("\"")
                line = line.rstrip("'")
                existing_params = line.split()

                for existing_param in existing_params:
                    existing_param_name = existing_param.split("=")[0]

                    # the only ones we ever add
                    if existing_param_name not in [
                            "quiet", "resume", "splash"]:
                        kernel_params.append(existing_param)

                lines[i] = kernel_cmd
                have_kernel_cmd = True
            elif (lines[i].startswith("#GRUB_DISTRIBUTOR")
                  or lines[i].startswith("GRUB_DISTRIBUTOR")):
                if libcalamares.job.configuration.get("keep_distributor", False):
                    lines[i] = distributor_line
                    have_distributor_line = True
                else:
                    # We're not updating because of *keep_distributor*, but if
                    # this was a comment line, then it's still not been set.
                    have_distributor_line = have_distributor_line or not lines[i].startswith("#")
            # If btrfs or f2fs is used, don't save default
            if no_save_default and lines[i].startswith("GRUB_SAVEDEFAULT="):
                lines[i] = "#GRUB_SAVEDEFAULT=\"true\""
    else:
        lines = []

        if "defaults" in libcalamares.job.configuration:
            for key, value in libcalamares.job.configuration[
                    "defaults"].items():
                if value.__class__.__name__ == "bool":
                    if value:
                        escaped_value = "true"
                    else:
                        escaped_value = "false"
                else:
                    escaped_value = str(value).replace("'", "'\\''")

                lines.append(f"{key}='{escaped_value}'")

    if not have_kernel_cmd:
        lines.append(kernel_cmd)

    if not have_distributor_line:
        lines.append(distributor_line)

    if cryptdevice_params and not unencrypted_separate_boot:
        lines.append("GRUB_ENABLE_CRYPTODISK=y")

    with open(default_grub, 'w') as grub_file:
        grub_file.write("\n".join(lines) + "\n")

    return None


def run():
    """
    Calls routine with given parameters to modify '/etc/default/grub'.

    :return:
    """
    fw_type = libcalamares.globalstorage.value("firmwareType")
    partitions = libcalamares.globalstorage.value("partitions")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    branding = libcalamares.globalstorage.value("branding")
    if branding is None:
        distributor = None
    else:
        distributor = branding["bootloaderEntryName"]

    if libcalamares.globalstorage.value("bootLoader") is None and fw_type != "efi":
        return None

    if fw_type == "efi":
        esp_found = False

        for partition in partitions:
            if partition["mountPoint"] == libcalamares.globalstorage.value("efiSystemPartition"):
                esp_found = True

        if not esp_found:
            return None

    return modify_grub_default(partitions, root_mount_point, distributor)
