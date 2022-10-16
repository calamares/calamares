#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2022 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import shutil

import libcalamares
from libcalamares.utils import gettext_path, gettext_languages


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Copying zfs generated hostid.")


def run():

    zfs = libcalamares.globalstorage.value("zfsDatasets")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if zfs:
        hostid_source = '/etc/hostid'
        hostid_destination = '{!s}/etc/hostid'.format(root_mount_point)

        try:
            shutil.copy2(hostid_source, hostid_destination)
        except Exception as e:
            libcalamares.utils.warning("Could not copy hostid")

    return None
