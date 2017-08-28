#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
#   Copyright 2015-2017, Teo Mrnjavac <teo@kde.org>
#   Copyright 2016-2017, Kyle Robbertze <kyle@aims.ac.za>
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

import abc
from string import Template
import subprocess

import libcalamares
from libcalamares.utils import check_target_env_call, target_env_call


class PackageManager(metaclass=abc.ABCMeta):
    """
    Package manager base class. A subclass implements package management
    for a specific backend, and must have a class property `backend`
    with the string identifier for that backend.

    Subclasses are collected below to populate the list of possible
    backends.
    """
    backend = None

    @abc.abstractmethod
    def install(self, pkgs, from_local=False):
        pass

    @abc.abstractmethod
    def remove(self, pkgs):
        """ Removes packages.

        :param pkgs:
        """
        pass

    @abc.abstractmethod
    def update_db(self):
        pass

    def run(self, script):
        if script != "":
            check_target_env_call(script.split(" "))


class PMPackageKit(PackageManager):
    backend = "packagekit"

    def install(self, pkgs, from_local=False):
        for pkg in pkgs:
            check_target_env_call(["pkcon", "-py", "install", pkg])

    def remove(self, pkgs):
        for pkg in pkgs:
            check_target_env_call(["pkcon", "-py", "remove", pkg])

    def update_db(self):
        check_target_env_call(["pkcon", "refresh"])


class PMZypp(PackageManager):
    backend = "zypp"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["zypper", "--non-interactive",
                                "--quiet-install", "install",
                                "--auto-agree-with-licenses",
                                "install"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["zypper", "--non-interactive",
                                "remove"] + pkgs)

    def update_db(self):
        check_target_env_call(["zypper", "--non-interactive", "update"])


class PMYum(PackageManager):
    backend = "yum"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["yum", "install", "-y"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["yum", "--disablerepo=*", "-C", "-y",
                                "remove"] + pkgs)

    def update_db(self):
        # Doesn't need updates
        pass


class PMDnf(PackageManager):
    backend = "dnf"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["dnf", "install", "-y"] + pkgs)

    def remove(self, pkgs):
        # ignore the error code for now because dnf thinks removing a
        # nonexistent package is an error
        target_env_call(["dnf", "--disablerepo=*", "-C", "-y",
                            "remove"] + pkgs)

    def update_db(self):
        # Doesn't need to update explicitly
        pass


class PMUrpmi(PackageManager):
    backend = "urpmi";

    def install(self, pkgs, from_local=False):
        check_target_env_call(["urpmi", "--download-all", "--no-suggests",
                                "--no-verify-rpm", "--fastunsafe",
                                "--ignoresize", "--nolock",
                                "--auto"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["urpme", "--auto"] + pkgs)

    def update_db(self):
        check_target_env_call(["urpmi.update", "-a"])


class PMApt(PackageManager):
    backend = "apt"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["apt-get", "-q", "-y", "install"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["apt-get", "--purge", "-q", "-y",
                                "remove"] + pkgs)
        check_target_env_call(["apt-get", "--purge", "-q", "-y",
                                "autoremove"])

    def update_db(self):
        check_target_env_call(["apt-get", "update"])


class PMPacman(PackageManager):
    backend = "pacman"

    def install(self, pkgs, from_local=False):
        if from_local:
            pacman_flags = "-U"
        else:
            pacman_flags = "-Sy"

        check_target_env_call(["pacman", pacman_flags,
                                "--noconfirm"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["pacman", "-Rs", "--noconfirm"] + pkgs)

    def update_db(self):
        check_target_env_call(["pacman", "-Sy"])


class PMPortage(PackageManager):
    backend = "portage"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["emerge", "-v"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["emerge", "-C"] + pkgs)
        check_target_env_call(["emerge", "--depclean", "-q"])

    def update_db(self):
        check_target_env_call(["emerge", "--sync"])


class PMEntropy(PackageManager):
    backend = "entropy"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["equo", "i"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["equo", "rm"] + pkgs)

    def update_db(self):
        check_target_env_call(["equo", "update"])


class PMDummy(PackageManager):
    backend = "dummy"

    def install(self, pkgs, from_local=False):
        libcalamares.utils.debug("Installing " + str(pkgs))

    def remove(self, pkgs):
        libcalamares.utils.debug("Removing " + str(pkgs))

    def update_db(self):
        libcalamares.utils.debug("Updating DB")


backend_managers = [
    (c.backend, c)
    for c in globals().values()
    if type(c) is abc.ABCMeta and issubclass(c, PackageManager) and c.backend ]


def subst_locale(list):
    ret = []
    locale = libcalamares.globalstorage.value("locale")
    if locale:
        for e in list:
            if locale != "en":
                entry = Template(e)
                ret.append(entry.safe_substitute(LOCALE=locale))
            elif 'LOCALE' not in e:
                ret.append(e)
    else:
        ret = list
    return ret


def run_operations(pkgman, entry):
    """
    Call package manager with given parameters.

    :param pkgman:
    :param entry:
    """
    for key in entry.keys():
        entry[key] = subst_locale(entry[key])
        if key == "install":
            if isinstance(entry[key], list):
                for package in entry[key]:
                    pkgman.run(package["pre-script"])
                    pkgman.install([package["package"]])
                    pkgman.run(package["post-script"])
            else:
                pkgman.install(entry[key])
        elif key == "try_install":
            # we make a separate package manager call for each package so a
            # single failing package won't stop all of them
            for package in entry[key]:
                if isinstance(package, str):
                    try:
                        pkgman.install([package])
                    except subprocess.CalledProcessError:
                        warn_text = "WARNING: could not install package "
                        warn_text += package
                        libcalamares.utils.debug(warn_text)
                else:
                    try:
                        pkgman.run(package["pre-script"])
                        pkgman.install([package["package"]])
                        pkgman.run(package["post-script"])
                    except subprocess.CalledProcessError:
                        warn_text = "WARNING: could not install packages "
                        warn_text += package["package"]
                        libcalamares.utils.debug(warn_text)
        elif key == "remove":
            pkgman.remove(entry[key])
        elif key == "try_remove":
            for package in entry[key]:
                try:
                    pkgman.remove([package])
                except subprocess.CalledProcessError:
                    warn_text = "WARNING: could not remove package "
                    warn_text += package
                    libcalamares.utils.debug(warn_text)
        elif key == "localInstall":
            pkgman.install(entry[key], from_local=True)


def run():
    """
    Calls routine with detected package manager to install locale packages
    or remove drivers not needed on the installed system.

    :return:
    """
    backend = libcalamares.job.configuration.get("backend")

    for identifier, impl in backend_managers:
        if identifier == backend:
            pkgman = impl()
            break
    else:
        return "Bad backend", "backend=\"{}\"".format(backend)

    operations = libcalamares.job.configuration.get("operations", [])

    update_db = libcalamares.job.configuration.get("update_db", False)
    if update_db and libcalamares.globalstorage.value("hasInternet"):
        pkgman.update_db()

    for entry in operations:
        run_operations(pkgman, entry)

    if libcalamares.globalstorage.contains("packageOperations"):
        run_operations(pkgman,
                       libcalamares.globalstorage.value("packageOperations"))

    return None
