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
from libcalamares.utils import check_chroot_call, chroot_call


class PackageManager:
    """ Package manager class

    :param backend:
    """
    def __init__(self, backend):
        self.backend = backend

    def install(self, pkgs):
        """ Installs packages.

        :param pkgs:
        """
        if self.backend == "packagekit":
            for pkg in pkgs:
                check_chroot_call(["pkcon", "-py", "install", pkg])
        elif self.backend == "zypp":
            check_chroot_call(
                ["zypper", "--non-interactive", "--quiet-install", "install",
                 "--auto-agree-with-licenses", "install"] + pkgs)
        elif self.backend == "yum":
            check_chroot_call(["yum", "install", "-y"] + pkgs)
        elif self.backend == "dnf":
            check_chroot_call(["dnf", "install", "-y"] + pkgs)
        elif self.backend == "urpmi":
            check_chroot_call(
                ["urpmi", "--download-all", "--no-suggests", "--no-verify-rpm",
                 "--fastunsafe", "--ignoresize", "--nolock", "--auto"] + pkgs)
        elif self.backend == "apt":
            check_chroot_call(["apt-get", "-q", "-y", "install"] + pkgs)
        elif self.backend == "pacman":
            check_chroot_call(["pacman", "-Sy", "--noconfirm"] + pkgs)

    def remove(self, pkgs):
        """ Removes packages.

        :param pkgs:
        """
        if self.backend == "packagekit":
            for pkg in pkgs:
                check_chroot_call(["pkcon", "-py", "remove", pkg])
        elif self.backend == "zypp":
            check_chroot_call(["zypper", "--non-interactive", "remove"] + pkgs)
        elif self.backend == "yum":
            check_chroot_call(["yum", "--disablerepo=*", "-C", "-y", "remove"] + pkgs)
        elif self.backend == "dnf":
            # ignore the error code for now because dnf thinks removing a nonexistent package is an error
            chroot_call(["dnf", "--disablerepo=*", "-C", "-y", "remove"] + pkgs)
        elif self.backend == "urpmi":
            check_chroot_call(["urpme", "--auto"] + pkgs)
        elif self.backend == "apt":
            check_chroot_call(["apt-get", "--purge", "-q", "-y", "remove"] + pkgs)
            check_chroot_call(["apt-get", "--purge", "-q", "-y", "autoremove"])
        elif self.backend == "pacman":
            check_chroot_call(["pacman", "-Rs", "--noconfirm"] + pkgs)


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


def run():
    """ Calls routine with detected package manager to install locale packages
    or remove drivers not needed on the installed system.

    :return:
    """
    backend = libcalamares.job.configuration.get("backend")
    if backend not in ("packagekit", "zypp", "yum", "dnf", "urpmi", "apt", "pacman"):
        return ("Bad backend", "backend=\"{}\"".format(backend))

    pkgman = PackageManager(backend)

    operations = libcalamares.job.configuration.get("operations", [])
    for entry in operations:
        run_operations(pkgman, entry)

    if libcalamares.globalstorage.contains("packageOperations"):
        operations = libcalamares.globalstorage.value("packageOperations")
        for entry in operations:
            run_operations(pkgman, entry)

    return None
