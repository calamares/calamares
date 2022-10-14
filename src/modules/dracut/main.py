#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014-2015 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaid@siduction.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2022 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import shutil
import libcalamares
from libcalamares.utils import check_target_env_call


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Creating initramfs with dracut.")


def run_dracut():
    """
    Creates initramfs, even when initramfs already exists.

    :return:
    """
    kernelName = libcalamares.job.configuration['kernelName']
    zfs = libcalamares.globalstorage.value("zfsDatasets")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if zfs:
        hostid_source = '/etc/hostid'
        hostid_destination = '{!s}/etc/hostid'.format(root_mount_point)

        # copy hostid before kernel image creation with zfs
        if os.path.exists(hostid_source):
            try:
                shutil.copy2(hostid_source, hostid_destination)
            except Exception as e:
                libcalamares.utils.warning("Could not copy hostid")

    if not kernelName:
        return check_target_env_call(['dracut', '-f'])
    else:
        return check_target_env_call(['dracut', '-f', '{}'.format(kernelName)])


def run():
    """
    Starts routine to create initramfs. It passes back the exit code
    if it fails.

    :return:
    """
    return_code = run_dracut()

    if return_code != 0:
        return (_("Failed to run dracut on the target"),
                _("The exit code was {}").format(return_code))
