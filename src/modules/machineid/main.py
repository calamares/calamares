#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
#   Copyright 2016, Philip Müller <philm@manjaro.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
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
from libcalamares.utils import check_target_env_call, debug

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Generate machine-id.")


def run():
    """
    Generate machine-id using dbus and systemd.

    :return:
    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    enable_systemd = libcalamares.job.configuration["systemd"]
    enable_dbus = libcalamares.job.configuration["dbus"]
    enable_symlink = libcalamares.job.configuration["symlink"]
    target_systemd_machineid_file = root_mount_point + "/etc/machine-id"
    target_dbus_machineid_file = root_mount_point + "/var/lib/dbus/machine-id"

    if os.path.exists(target_dbus_machineid_file):
        os.remove(target_dbus_machineid_file)

    if enable_systemd:
        if os.path.exists(target_systemd_machineid_file):
            os.remove(target_systemd_machineid_file)
        check_target_env_call("systemd-machine-id-setup")

    if enable_dbus:
        if enable_symlink and os.path.exists(target_systemd_machineid_file):
            check_target_env_call(["ln", "-s", "/etc/machine-id",
                                   "/var/lib/dbus/machine-id"])
        else:
            check_target_env_call(["dbus-uuidgen", "--ensure"])

    return None
