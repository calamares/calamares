#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014-2015, Philip Müller <philm@manjaro.org>
#   Copyright 2015,      Teo Mrnjavac <teo@kde.org>
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

from libcalamares import debug, target_env_call

class PlymouthController:
    def __init__(self):
        self.__root = libcalamares.globalstorage.value('rootMountPoint')
        self._hasPlymouth = 1

    @property
	def root(self):
		return self.__root

    @property
	def hasPlymouth(self):
		return self._hasPlymouth

    @hasPlymouth.setter
	def hasPlymouth(self, value):
		self._hasPlymouth = value

    def setExpression(self, pattern, file):
        target_env_call(["sed", "-e", pattern, "-i", file])

    def setTheme(self):
        plymouth_theme = libcalamares.job.configuration["plymouth_theme"]
        setExpression('s|^.*Theme=.*|Theme=' + plymouth_theme + '|', "/etc/plymouth/plymouthd.conf")

    def detect_plymouth(self):
        plymouth_bin = target_env_call(["which", "plymouth"])
        debug("which plymouth exit code: {!s}".format(plymouth_bin))

        if plymouth_bin:
            libcalamares.globalstorage.insert("hasPlymouth", "true")
        else:
            libcalamares.globalstorage.insert("hasPlymouth", "false")

    def run(self):

        self.detect_plymouth()
        if plymouth_bin == 0:
            if "plymouth_theme" in libcalamares.job.configuration and libcalamares.job.configuration["plymouth_theme"] is not None:
                self.setTheme()

        return None

def run():

