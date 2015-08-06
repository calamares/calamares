#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
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
from libcalamares.utils import check_target_env_call, target_env_call


class PackageManager:
    """ Package manager class.

    :param backend:
    """
    def __init__(self, backend):
        self.backend = backend

    def install(self, pkgs, from_local=False):
        """ Installs packages.

        :param pkgs:
        :param from_local:
        """
        if self.backend == "packagekit":
            for pkg in pkgs:
                check_target_env_call(["pkcon", "-py", "install", pkg])
        elif self.backend == "zypp":
            check_target_env_call(["zypper", "--non-interactive", "--quiet-install", "install",
                               "--auto-agree-with-licenses", "install"] + pkgs)
        elif self.backend == "yum":
            check_target_env_call(["yum", "install", "-y"] + pkgs)
        elif self.backend == "dnf":
            check_target_env_call(["dnf", "install", "-y"] + pkgs)
        elif self.backend == "urpmi":
            check_target_env_call(["urpmi", "--download-all", "--no-suggests", "--no-verify-rpm",
                               "--fastunsafe", "--ignoresize", "--nolock", "--auto"] + pkgs)
        elif self.backend == "apt":
            check_target_env_call(["apt-get", "-q", "-y", "install"] + pkgs)
        elif self.backend == "pacman":
            if from_local:
                pacman_flags = "-U"
            else:
                pacman_flags = "-Sy"

            check_target_env_call(["pacman", pacman_flags, "--noconfirm"] + pkgs)
        elif self.backend == "portage":
            check_target_env_call(["emerge", "-v"] + pkgs)
        elif self.backend == "entropy":
            check_target_env_call(["equo", "i"] + pkgs)

    def remove(self, pkgs):
        """ Removes packages.

        :param pkgs:
        """
        if self.backend == "packagekit":
            for pkg in pkgs:
                check_target_env_call(["pkcon", "-py", "remove", pkg])
        elif self.backend == "zypp":
            check_target_env_call(["zypper", "--non-interactive", "remove"] + pkgs)
        elif self.backend == "yum":
            check_target_env_call(["yum", "--disablerepo=*", "-C", "-y", "remove"] + pkgs)
        elif self.backend == "dnf":
            # ignore the error code for now because dnf thinks removing a nonexistent package is an error
            target_env_call(["dnf", "--disablerepo=*", "-C", "-y", "remove"] + pkgs)
        elif self.backend == "urpmi":
            check_target_env_call(["urpme", "--auto"] + pkgs)
        elif self.backend == "apt":
            check_target_env_call(["apt-get", "--purge", "-q", "-y", "remove"] + pkgs)
            check_target_env_call(["apt-get", "--purge", "-q", "-y", "autoremove"])
        elif self.backend == "pacman":
            check_target_env_call(["pacman", "-Rs", "--noconfirm"] + pkgs)
        elif self.backend == "portage":
            check_target_env_call(["emerge", "-C"] + pkgs)
        elif self.backend == "entropy":
            check_target_env_call(["equo", "rm"] + pkgs)


def run_operations(pkgman, entry):
    """ Call package manager with given parameters.

    :param pkgman:
    :param entry:
    """
    for key in entry.keys():
        if key == "install":
            pkgman.install(entry[key])
        elif key == "remove":
            pkgman.remove(entry[key])
        elif key == "localInstall":
            pkgman.install(entry[key], from_local=True)


def run():
    """ Calls routine with detected package manager to install locale packages
    or remove drivers not needed on the installed system.

    :return:
    """
    backend = libcalamares.job.configuration.get("backend")

    if backend not in ("packagekit", "zypp", "yum", "dnf", "urpmi", "apt", "pacman", "portage", "entropy"):
        return "Bad backend", "backend=\"{}\"".format(backend)

    pkgman = PackageManager(backend)
    operations = libcalamares.job.configuration.get("operations", [])

    for entry in operations:
        run_operations(pkgman, entry)

    if libcalamares.globalstorage.contains("packageOperations"):
        operations = libcalamares.globalstorage.value("packageOperations")

        for entry in operations:
            run_operations(pkgman, entry)

    return None
