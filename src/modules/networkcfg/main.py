#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2021 Anke boersma <demm@koasx.us>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import shutil

import libcalamares

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Saving network configuration.")


def run():
    """
    Setup network configuration
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    user = libcalamares.globalstorage.value("username")
    live_user = os.getlogin()

    if root_mount_point is None:
        libcalamares.utils.warning("rootMountPoint is empty, {!s}".format(root_mount_point))
        return (_("Configuration Error"),
                _("No root mount point is given for <pre>{!s}</pre> to use." ).format("networkcfg"))

    source_nm = "/etc/NetworkManager/system-connections/"
    target_nm = os.path.join(
        root_mount_point, "etc/NetworkManager/system-connections/"
        )

    # Sanity checks.  We don't want to do anything if a network
    # configuration already exists on the target
    if os.path.exists(source_nm) and os.path.exists(target_nm):
        for network in os.listdir(source_nm):
            # Skip LTSP live
            if network == "LTSP":
                continue

            source_network = os.path.join(source_nm, network)
            target_network = os.path.join(target_nm, network)

            if os.path.exists(target_network):
                continue

            try:
                shutil.copy(source_network, target_network, follow_symlinks=False)
                if live_user in open(target_network).read():
                    text = []
                    with open(target_network, "r") as network_conf:
                        text = network_conf.readlines()
                        with open(target_network, "w") as network_conf:
                            for line in text:
                                if 'permissions=user:{}:;'.format(live_user) in line:
                                    line = 'permissions=user:{}:;\n'.format(user)
                                network_conf.write(line)
                    network_conf.close()
            except FileNotFoundError:
                libcalamares.utils.debug(
                    "Can't copy network configuration files in "
                    + "{}".format(source_network)
                    )
            except FileExistsError:
                pass

    # We need to overwrite the default resolv.conf in the chroot.
    source_resolv = "/etc/resolv.conf"
    target_resolv = os.path.join(root_mount_point, "etc/resolv.conf")
    if source_resolv != target_resolv and os.path.exists(source_resolv):
        try:
            os.remove(target_resolv)
        except Exception as err:
            libcalamares.utils.debug(
                "Couldn't remove {}: {}".format(target_resolv, err)
                )

        try:
            shutil.copy(source_resolv, target_resolv, follow_symlinks=False)
        except Exception as err:
            libcalamares.utils.debug(
                "Can't copy resolv.conf from {}: {}".format(source_resolv, err)
                )

    return None
