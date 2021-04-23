#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2016 Artoo <artoo@manjaro.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2018 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares

from libcalamares.utils import debug, target_env_call

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configure Plymouth theme")


def detect_plymouth():
    """
    Checks existence (runnability) of plymouth in the target system.

    @return True if plymouth exists in the target, False otherwise
    """
    # Used to only check existence of path /usr/bin/plymouth in target
    return target_env_call(["sh", "-c", "which plymouth"]) == 0


class PlymouthController:

    def __init__(self):
        self.__root = libcalamares.globalstorage.value('rootMountPoint')

    @property
    def root(self):
        return self.__root

    def setTheme(self):
        plymouth_theme = libcalamares.job.configuration["plymouth_theme"]
        target_env_call(["sed", "-e", 's|^.*Theme=.*|Theme=' +
                         plymouth_theme + '|', "-i",
                         "/etc/plymouth/plymouthd.conf"])

    def run(self):
        if detect_plymouth():
            if (("plymouth_theme" in libcalamares.job.configuration) and
               (libcalamares.job.configuration["plymouth_theme"] is not None)):
                self.setTheme()
        return None


def run():
    pc = PlymouthController()
    return pc.run()
