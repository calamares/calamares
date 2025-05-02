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
import fileinput
import os
import re
import shutil

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
            default_config_file = "00calamares.cfg"

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


def update_existing_config(default_grub, grub_config_items):
    """
    Updates the existing grub configuration file with any items present in @p grub_config_items

    Items that exist in the file will be updated and new items will be appended to the end

    :param default_grub: The absolute path to the grub config file
    :param grub_config_items: A dict holding the key value pairs representing the items
    """
    
    default_grub_orig = default_grub + ".calamares"
    shutil.move(default_grub, default_grub_orig)

    with open(default_grub, "w") as grub_file:
        with open(default_grub_orig, "r") as grub_orig_file:
            for line in grub_orig_file.readlines():
                line = line.strip()
                if "=" in line:
                    # This may be a key, strip the leading comment if it has one
                    key = line.lstrip("#").split("=")[0].strip()

                    # check if this is noe of the keys we care about
                    if key in grub_config_items.keys():
                        print(f"{key}={grub_config_items[key]}", file=grub_file)
                        del grub_config_items[key]
                    else:
                        print(line, file=grub_file)
                else:
                    print(line, file=grub_file)

            if len(grub_config_items) != 0:
                for dict_key, dict_val in grub_config_items.items():
                    print(f"{dict_key}={dict_val}", file=grub_file)

    os.remove(default_grub_orig)


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
    distributor = distributor.replace("'", "'\\''")
    dracut_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which dracut"]
        )
    plymouth_bin = libcalamares.utils.target_env_call(
        ["sh", "-c", "which plymouth"]
        )
    uses_systemd_hook = libcalamares.utils.target_env_call(
        ["sh", "-c", "grep -q \"^HOOKS.*systemd\" /etc/mkinitcpio.conf"]
        ) == 0
    # Shell exit value 0 means success
    have_plymouth = plymouth_bin == 0
    use_systemd_naming = dracut_bin == 0 or uses_systemd_hook

    use_splash = ""
    swap_uuid = ""
    swap_outer_uuid = ""
    swap_outer_mappername = None
    no_save_default = False
    unencrypted_separate_boot = any(p["mountPoint"] == "/boot" and "luksMapperName" not in p for p in partitions)
    # If there is no dracut, and the root partition is ZFS, this gets set below
    zfs_root_path = None

    for partition in partitions:
        if partition["mountPoint"] in ("/", "/boot") and partition["fs"] in ("btrfs", "f2fs", "zfs"):
            no_save_default = True
            break

    if have_plymouth:
        use_splash = "splash"

    cryptdevice_params = []

    if use_systemd_naming:
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
                if not unencrypted_separate_boot and uses_systemd_hook:
                    cryptdevice_params.append("rd.luks.key=/crypto_keyfile.bin")
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

    if use_systemd_naming and swap_outer_uuid:
        kernel_params.append(f"rd.luks.uuid={swap_outer_uuid}")
    if swap_outer_mappername:
        kernel_params.append(f"resume=/dev/mapper/{swap_outer_mappername}")

    overwrite = libcalamares.job.configuration.get("overwrite", False)

    grub_config_items = {}
    # read the lines we need from the existing config
    if os.path.exists(default_grub) and not overwrite:
        with open(default_grub, 'r') as grub_file:
            lines = [x.strip() for x in grub_file.readlines()]

        for line in lines:
            if line.startswith("GRUB_CMDLINE_LINUX_DEFAULT"):
                existing_params = re.sub(r"^GRUB_CMDLINE_LINUX_DEFAULT\s*=\s*", "", line).strip("\"'").split()

                for existing_param in existing_params:
                    existing_param_name = existing_param.split("=")[0].strip()

                    # Ensure we aren't adding duplicated params
                    param_exists = False
                    for param in kernel_params:
                        if param.split("=")[0].strip() == existing_param_name:
                            param_exists = True
                            break
                    if not param_exists and existing_param_name not in ["quiet", "resume", "splash"]:
                        kernel_params.append(existing_param)

            elif line.startswith("GRUB_DISTRIBUTOR") and libcalamares.job.configuration.get("keep_distributor", False):
                distributor_parts = line.split("=")
                if len(distributor_parts) > 1:
                    distributor = distributor_parts[1].strip("'\"")

            # If a filesystem grub can't write to is used, disable save default
            if no_save_default and line.strip().startswith("GRUB_SAVEDEFAULT"):
                grub_config_items["GRUB_SAVEDEFAULT"] = "false"

    always_use_defaults = libcalamares.job.configuration.get("always_use_defaults", False)

    # If applicable add the items from defaults to the dict containing the grub config to wirte/modify
    if always_use_defaults or overwrite or not os.path.exists(default_grub):
        if "defaults" in libcalamares.job.configuration:
            for key, value in libcalamares.job.configuration["defaults"].items():
                if isinstance(value, bool):
                    if value:
                        escaped_value = "true"
                    else:
                        escaped_value = "false"
                else:
                    escaped_value = str(value).replace("'", "'\\''")

                grub_config_items[key] = f"'{escaped_value}'"

    grub_config_items['GRUB_CMDLINE_LINUX_DEFAULT'] = f"'{' '.join(kernel_params)}'"
    grub_config_items["GRUB_DISTRIBUTOR"] = f"'{distributor}'"

    if cryptdevice_params and not unencrypted_separate_boot:
        grub_config_items["GRUB_ENABLE_CRYPTODISK"] = "y"

    if overwrite or not os.path.exists(default_grub) or libcalamares.job.configuration.get("prefer_grub_d", False):
        with open(default_grub, 'w') as grub_file:
            for key, value in grub_config_items.items():
                grub_file.write(f"{key}={value}\n")
    else:
        update_existing_config(default_grub, grub_config_items)

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
