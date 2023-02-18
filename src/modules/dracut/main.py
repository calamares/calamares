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
import subprocess

import libcalamares
from libcalamares.utils import target_env_process_output


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
    try:
        initramfs_name = libcalamares.job.configuration['initramfsName']
        target_env_process_output(['dracut', '-f', initramfs_name])
    except KeyError:
        try:
            target_env_process_output(['dracut', '-f'])
        except subprocess.CalledProcessError as cpe:
            libcalamares.utils.warning(f"Dracut failed with output: {cpe.output}")
            return cpe.returncode
    except subprocess.CalledProcessError as cpe:
        libcalamares.utils.warning(f"Dracut failed with output: {cpe.output}")
        return cpe.returncode

    return 0


def run():
    """
    Starts routine to create initramfs. It passes back the exit code
    if it fails.

    :return:
    """
    return_code = run_dracut()
    if return_code != 0:
        return (_("Failed to run dracut"),
                _(f"Dracut failed to run on the target with return code: {return_code}"))
