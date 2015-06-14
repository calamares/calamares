#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
import shutil

import libcalamares


def run():
    """ Setup network configuration """

    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    source_nm = "/etc/NetworkManager/system-connections/"
    target_nm = os.path.join(root_mount_point, "etc/NetworkManager/system-connections/")

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
                shutil.copy(source_network, target_network)
            except FileNotFoundError:
                libcalamares.utils.debug("Can't copy network configuration files in {}".format(source_network))
            except FileExistsError:
                pass

    return None
