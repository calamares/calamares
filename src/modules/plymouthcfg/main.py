#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2016, Artoo <artoo@manjaro.org>
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

from libcalamares.utils import debug, target_env_call


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

    def detect(self):
        isPlymouth = target_env_call(["which", "plymouth"])
        debug("which plymouth exit code: {!s}".format(isPlymouth))

        if isPlymouth == 0:
            libcalamares.globalstorage.insert("hasPlymouth", True)
        else:
            libcalamares.globalstorage.insert("hasPlymouth", False)

        return isPlymouth

    def run(self):
        if self.detect() == 0:
            if (("plymouth_theme" in libcalamares.job.configuration) and
               (libcalamares.job.configuration["plymouth_theme"] is not None)):
                self.setTheme()
        return None


def run():
    pc = PlymouthController()
    return pc.run()
