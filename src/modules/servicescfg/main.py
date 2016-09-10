#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2016, Artoo <artoo@manjaro.org>
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
from os.path import exists, join

class ServicesController:
    def __init__(self):
        self.__root = libcalamares.globalstorage.value('rootMountPoint')
        self.__services = libcalamares.job.configuration.get('services', [])

    @property
    def root(self):
        return self.__root

    @property
    def services(self):
        return self.__services

    def setExpression(self, pattern, file):
        check_target_env_call(["sed", "-e", pattern, "-i", file])

    def configure(self):
        self.setExpression('s|^.*rc_shell=.*|rc_shell="/usr/bin/sulogin"|', "/etc/rc.conf")
        self.setExpression('s|^.*rc_controller_cgroups=.*|rc_controller_cgroups="YES"|', "/etc/rc.conf")
        exp = 's|^.*keymap=.*|keymap="' + libcalamares.globalstorage.value("keyboardLayout") + '"|'
        self.setExpression(exp, "/etc/conf.d/keymaps")
        self.setExpression('s|pam_systemd.so|pam_ck_connector.so nox11|', "/etc/pam.d/system-login")
        for dm in libcalamares.globalstorage.value("displayManagers"):
            exp = 's|^.*DISPLAYMANAGER=.*|DISPLAYMANAGER="' + dm + '"|'
            self.setExpression(exp, "/etc/conf.d/xdm")
            if dm == "lightdm":
                self.setExpression('s|^.*minimum-vt=.*|minimum-vt=7|', "/etc/lightdm/lightdm.conf")
                self.setExpression('s|pam_systemd.so|pam_ck_connector.so nox11|', "/etc/pam.d/lightdm-greeter")

    def update(self, action, state):
        for svc in self.services[state]:
            if exists(self.root + "/etc/init.d/" + svc["name"]):
                check_target_env_call(["rc-update", action, svc["name"], svc["runlevel"]])

    def run(self):
        self.configure()
        for state in self.services.keys():
            if state == "enabled":
                self.update("add", "enabled")
            elif state == "disabled":
                self.update("del", "disabled")

        return None

def run():
    """ Setup openrc services """
    sc = ServicesController()
    return sc.run()
