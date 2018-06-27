#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2016, Artoo <artoo@manjaro.org>
#   Copyright 2017, Philip Müller <philm@manjaro.org>
#   Copyright 2018, Artoo <artoo@artixlinux.org>
#   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

from libcalamares.utils import target_env_call, warning
from os.path import exists, join


class OpenrcController:
    """
    This is the openrc service controller.
    All of its state comes from global storage and the job
    configuration at initialization time.
    """

    def __init__(self):
        self.root = libcalamares.globalstorage.value('rootMountPoint')

        # Translate the entries in the config to the actions passed to rc-config
        self.services = dict()
        self.services["add"] = libcalamares.job.configuration.get('services', [])
        self.services["del"] = libcalamares.job.configuration.get('disable', [])

        self.initdDir = libcalamares.job.configuration['initdDir']
        self.runlevelsDir = libcalamares.job.configuration['runlevelsDir']

    def update(self, state):
        """
        Call rc-update for each service listed
        in services for the given @p state. rc-update
        is called with @p state as the command as well.
        """

        for svc in self.services.get(state, []):
            if isinstance(svc, str):
                name = svc
                runlevel = "default"
                mandatory = False
            else:
                name = svc["name"]
                runlevel = svc.get("runlevel", "default")
                mandatory = svc.get("mandatory", False)

            service_path = self.root + self.initdDir + "/" + name
            runlevel_path = self.root + self.runlevelsDir + "/" + runlevel

            if exists(service_path):
                if exists(runlevel_path):
                    ec = target_env_call(["rc-update", state, name, runlevel])
                    if ec != 0:
                        if mandatory:
                            return ("Cannot {} service {} to {}".format(state, name, runlevel),
                                    "rc-update {} call in chroot returned error code {}".format(state, ec)
                                    )
                        else:
                            warning("Could not {} service {} in {}, error {!s}".format(state, name, runlevel, ec))
                else:
                    if mandatory:
                        return ("Target runlevel {} does not exist for {}.".format(runlevel, name),
                                "No {} found.".format(runlevel_path))
                    else:
                        warning("Target runlevel {} does not exist for {}.".format(runlevel, name))
            else:
                if mandatory:
                    return ("Target service {} does not exist.".format(name),
                            "No {} found.".format(service_path))
                else:
                    warning("Target service {} does not exist in {}.".format(name, self.initdDir))


    def run(self):
        """Run the controller
        """

        for state in ("add", "del"):
            r = self.update(state)
            if r is not None:
                return r

def run():
    """
    Setup services
    """

    return OpenrcController().run()
