#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014, Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
#   Copyright 2015-2017, Teo Mrnjavac <teo@kde.org>
#   Copyright 2016-2017, Kyle Robbertze <kyle@aims.ac.za>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
#   Copyright 2018, Adriaan de Groot <groot@kde.org>
#   Copyright 2018, Philip Müller <philm@manjaro.org>
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
from libcalamares.utils import gettext_path, gettext_languages

import gettext
_translation = gettext.translation("calamares-python",
                                   localedir=gettext_path(),
                                   languages=gettext_languages(),
                                   fallback=True)
_ = _translation.gettext
_n = _translation.ngettext


total_packages = 0  # For the entire job
completed_packages = 0  # Done so far for this job
group_packages = 0  # One group of packages from an -install or -remove entry

INSTALL = object()
REMOVE = object()
mode_packages = None  # Changes to INSTALL or REMOVE


def _change_mode(mode):
    global mode_packages
    mode_packages = mode
    libcalamares.job.setprogress(completed_packages * 1.0 / total_packages)


def pretty_name():
    return _("Install packages.")


def pretty_status_message():
    if not group_packages:
        if (total_packages > 0):
            # Outside the context of an operation
            s = _("Processing packages (%(count)d / %(total)d)")
        else:
            s = _("Install packages.")

    elif mode_packages is INSTALL:
        s = _n("Installing one package.",
               "Installing %(num)d packages.", group_packages)
    elif mode_packages is REMOVE:
        s = _n("Removing one package.",
               "Removing %(num)d packages.", group_packages)
    else:
        # No mode, generic description
        s = _("Install packages.")

    return s % {"num": group_packages,
                "count": completed_packages,
                "total": total_packages}


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
        """
        Install a list of packages (named) into the system.
        Although this handles lists, in practice it is called
        with one package at a time.

        @param pkgs: list[str]
            list of package names
        @param from_local: bool
            if True, then these are local packages (on disk) and the
            pkgs names are paths.
        """
        pass

    @abc.abstractmethod
    def remove(self, pkgs):
        """
        Removes packages.

        @param pkgs: list[str]
            list of package names
        """
        pass

    @abc.abstractmethod
    def update_db(self):
        pass

    def run(self, script):
        if script != "":
            check_target_env_call(script.split(" "))

    def install_package(self, packagedata, from_local=False):
        """
        Install a package from a single entry in the install list.
        This can be either a single package name, or an object
        with pre- and post-scripts. If @p packagedata is a dict,
        it is assumed to follow the documented structure.

        @param packagedata: str|dict
        @param from_local: bool
            see install.from_local
        """
        if isinstance(packagedata, str):
            self.install([packagedata], from_local=from_local)
        else:
            self.run(packagedata["pre-script"])
            self.install([packagedata["package"]], from_local=from_local)
            self.run(packagedata["post-script"])

    def remove_package(self, packagedata):
        """
        Remove a package from a single entry in the remove list.
        This can be either a single package name, or an object
        with pre- and post-scripts. If @p packagedata is a dict,
        it is assumed to follow the documented structure.

        @param packagedata: str|dict
        """
        if isinstance(packagedata, str):
            self.remove([packagedata])
        else:
            self.run(packagedata["pre-script"])
            self.remove([packagedata["package"]])
            self.run(packagedata["post-script"])


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

    def update_system(self):
        check_target_env_call(["pkcon", "-py", "update"])

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

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass

class PMYum(PackageManager):
    backend = "yum"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["yum", "-y", "install"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["yum", "--disablerepo=*", "-C", "-y",
                               "remove"] + pkgs)

    def update_db(self):
        # Doesn't need updates
        pass

    def update_system(self):
        check_target_env_call(["yum", "-y", "upgrade"])

class PMDnf(PackageManager):
    backend = "dnf"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["dnf", "-y", "install"] + pkgs)

    def remove(self, pkgs):
        # ignore the error code for now because dnf thinks removing a
        # nonexistent package is an error
        target_env_call(["dnf", "--disablerepo=*", "-C", "-y",
                         "remove"] + pkgs)

    def update_db(self):
        # Doesn't need updates
        pass

    def update_system(self):
        check_target_env_call(["dnf", "-y", "upgrade"])


class PMUrpmi(PackageManager):
    backend = "urpmi"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["urpmi", "--download-all", "--no-suggests",
                               "--no-verify-rpm", "--fastunsafe",
                               "--ignoresize", "--nolock",
                               "--auto"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["urpme", "--auto"] + pkgs)

    def update_db(self):
        check_target_env_call(["urpmi.update", "-a"])

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass


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

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass


class PMPacman(PackageManager):
    backend = "pacman"

    def install(self, pkgs, from_local=False):
        if from_local:
            pacman_flags = "-U"
        else:
            pacman_flags = "-S"

        check_target_env_call(["pacman", pacman_flags,
                               "--noconfirm"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["pacman", "-Rs", "--noconfirm"] + pkgs)

    def update_db(self):
        check_target_env_call(["pacman", "-Sy"])

    def update_system(self):
        check_target_env_call(["pacman", "-Su", "--noconfirm"])


class PMPortage(PackageManager):
    backend = "portage"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["emerge", "-v"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["emerge", "-C"] + pkgs)
        check_target_env_call(["emerge", "--depclean", "-q"])

    def update_db(self):
        check_target_env_call(["emerge", "--sync"])

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass


class PMEntropy(PackageManager):
    backend = "entropy"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["equo", "i"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["equo", "rm"] + pkgs)

    def update_db(self):
        check_target_env_call(["equo", "update"])

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass


class PMDummy(PackageManager):
    backend = "dummy"

    def install(self, pkgs, from_local=False):
        from time import sleep
        libcalamares.utils.debug("Dummy backend: Installing " + str(pkgs))
        sleep(3)

    def remove(self, pkgs):
        from time import sleep
        libcalamares.utils.debug("Dummy backend: Removing " + str(pkgs))
        sleep(3)

    def update_db(self):
        libcalamares.utils.debug("Dummy backend: Updating DB")

    def update_system(self):
        libcalamares.utils.debug("Dummy backend: Updating System")

    def run(self, script):
        libcalamares.utils.debug("Dummy backend: Running script '" + str(script) + "'")


class PMPisi(PackageManager):
    backend = "pisi"

    def install(self, pkgs, from_local=False):
        check_target_env_call(["pisi", "install" "-y"] + pkgs)

    def remove(self, pkgs):
        check_target_env_call(["pisi", "remove", "-y"] + pkgs)

    def update_db(self):
        check_target_env_call(["pisi", "update-repo"])

    def update_system(self):
        # Doesn't need to update the system explicitly
        pass


class PMApk(PackageManager):
    backend = "apk"

    def install(self, pkgs, from_local=False):
        for pkg in pkgs:
            check_target_env_call(["apk", "add", pkg])

    def remove(self, pkgs):
        for pkg in pkgs:
            check_target_env_call(["apk", "del", pkg])

    def update_db(self):
        check_target_env_call(["apk", "update"])

    def update_system(self):
        check_target_env_call(["apk", "upgrade", "--available"])


# Collect all the subclasses of PackageManager defined above,
# and index them based on the backend property of each class.
backend_managers = [
    (c.backend, c)
    for c in globals().values()
    if type(c) is abc.ABCMeta and issubclass(c, PackageManager) and c.backend]


def subst_locale(plist):
    """
    Returns a locale-aware list of packages, based on @p plist.
    Package names that contain LOCALE are localized with the
    BCP47 name of the chosen system locale; if the system
    locale is 'en' (e.g. English, US) then these localized
    packages are dropped from the list.

    @param plist: list[str|dict]
        Candidate packages to install.
    @return: list[str|dict]
    """
    locale = libcalamares.globalstorage.value("locale")
    if not locale:
        # It is possible to skip the locale-setting entirely.
        # Then pretend it is "en", so that {LOCALE}-decorated
        # package names are removed from the list.
        locale = "en"

    ret = []
    for packagedata in plist:
        if isinstance(packagedata, str):
            packagename = packagedata
        else:
            packagename = packagedata["package"]

        # Update packagename: substitute LOCALE, and drop packages
        # if locale is en and LOCALE is in the package name.
        if locale != "en":
            packagename = Template(packagename).safe_substitute(LOCALE=locale)
        elif 'LOCALE' in packagename:
            packagename = None

        if packagename is not None:
            # Put it back in packagedata
            if isinstance(packagedata, str):
                packagedata = packagename
            else:
                packagedata["package"] = packagename

            ret.append(packagedata)

    return ret


def run_operations(pkgman, entry):
    """
    Call package manager with suitable parameters for the given
    package actions.

    :param pkgman: PackageManager
        This is the manager that does the actual work.
    :param entry: dict
        Keys are the actions -- e.g. "install" -- to take, and the values
        are the (list of) packages to apply the action to. The actions are
        not iterated in a specific order, so it is recommended to use only
        one action per dictionary. The list of packages may be package
        names (strings) or package information dictionaries with pre-
        and post-scripts.
    """
    global group_packages, completed_packages, mode_packages

    for key in entry.keys():
        package_list = subst_locale(entry[key])
        group_packages = len(package_list)
        if key == "install":
            _change_mode(INSTALL)
            if all([isinstance(x, str) for x in package_list]):
                pkgman.install(package_list)
            else:
                for package in package_list:
                    pkgman.install_package(package)
        elif key == "try_install":
            _change_mode(INSTALL)
            # we make a separate package manager call for each package so a
            # single failing package won't stop all of them
            for package in package_list:
                try:
                    pkgman.install_package(package)
                except subprocess.CalledProcessError:
                    warn_text = "Could not install package "
                    warn_text += str(package)
                    libcalamares.utils.warning(warn_text)
        elif key == "remove":
            _change_mode(REMOVE)
            if all([isinstance(x, str) for x in package_list]):
                pkgman.remove(package_list)
            else:
                for package in package_list:
                    pkgman.remove_package(package)
        elif key == "try_remove":
            _change_mode(REMOVE)
            for package in package_list:
                try:
                    pkgman.remove_package(package)
                except subprocess.CalledProcessError:
                    warn_text = "Could not remove package "
                    warn_text += str(package)
                    libcalamares.utils.warning(warn_text)
        elif key == "localInstall":
            _change_mode(INSTALL)
            if all([isinstance(x, str) for x in package_list]):
                pkgman.install(package_list, from_local=True)
            else:
                for package in package_list:
                    pkgman.install_package(package, from_local=True)
        elif key == "source":
            libcalamares.utils.debug("Package-list from {!s}".format(entry[key]))
        else:
            libcalamares.utils.warning("Unknown package-operation key {!s}".format(key))
        completed_packages += len(package_list)
        libcalamares.job.setprogress(completed_packages * 1.0 / total_packages)
        libcalamares.utils.debug("Pretty name: {!s}, setting progress..".format(pretty_name()))

    group_packages = 0
    _change_mode(None)


def run():
    """
    Calls routine with detected package manager to install locale packages
    or remove drivers not needed on the installed system.

    :return:
    """
    global mode_packages, total_packages, completed_packages, group_packages

    backend = libcalamares.job.configuration.get("backend")

    for identifier, impl in backend_managers:
        if identifier == backend:
            pkgman = impl()
            break
    else:
        return "Bad backend", "backend=\"{}\"".format(backend)

    skip_this = libcalamares.job.configuration.get("skip_if_no_internet", False)
    if skip_this and not libcalamares.globalstorage.value("hasInternet"):
        libcalamares.utils.warning( "Package installation has been skipped: no internet" )
        return None

    update_db = libcalamares.job.configuration.get("update_db", False)
    if update_db and libcalamares.globalstorage.value("hasInternet"):
        pkgman.update_db()

    update_system = libcalamares.job.configuration.get("update_system", False)
    if update_system and libcalamares.globalstorage.value("hasInternet"):
        pkgman.update_system()

    operations = libcalamares.job.configuration.get("operations", [])
    if libcalamares.globalstorage.contains("packageOperations"):
        operations += libcalamares.globalstorage.value("packageOperations")

    mode_packages = None
    total_packages = 0
    completed_packages = 0
    for op in operations:
        for packagelist in op.values():
            total_packages += len(subst_locale(packagelist))

    if not total_packages:
        # Avoids potential divide-by-zero in progress reporting
        return None

    for entry in operations:
        group_packages = 0
        libcalamares.utils.debug(pretty_name())
        run_operations(pkgman, entry)

    mode_packages = None

    libcalamares.job.setprogress(1.0)
    libcalamares.utils.debug(pretty_name())

    return None
