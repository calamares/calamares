#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014-2017, Philip Müller <philm@manjaro.org>
#   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
#   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
#   Copyright 2017, Bernhard Landauer <oberon@manjaro.org>
#   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
import os
import re
import libcalamares
import configparser


class DesktopEnvironment:
    """
    Desktop Environment -- some utility functions for a desktop
    environment (e.g. finding out if it is installed). This
    is independent of the *Display Manager*, which is what
    we're configuring in this module.
    """
    def __init__(self, exec, desktop):
        self.executable = exec
        self.desktop_file = desktop

    def find_desktop_environment(self, root_mount_point):
        """
        Check if this environment is installed in the
        target system at @p root_mount_point.
        """
        return (
            os.path.exists("{!s}{!s}".format(root_mount_point, self.executable)) and
            os.path.exists("{!s}/usr/share/xsessions/{!s}.desktop".format(root_mount_point, self.desktop_file))
            )


desktop_environments = [
    DesktopEnvironment('/usr/bin/startkde', 'plasma'),  # KDE Plasma 5
    DesktopEnvironment('/usr/bin/startkde', 'kde-plasma'),  # KDE Plasma 4
    DesktopEnvironment('/usr/bin/gnome-session', 'gnome'),
    DesktopEnvironment('/usr/bin/startxfce4', 'xfce'),
    DesktopEnvironment('/usr/bin/cinnamon-session-cinnamon', 'cinnamon'),
    DesktopEnvironment('/usr/bin/mate-session', 'mate'),
    DesktopEnvironment('/usr/bin/enlightenment_start', 'enlightenment'),
    DesktopEnvironment('/usr/bin/lxsession', 'LXDE'),
    DesktopEnvironment('/usr/bin/startlxde', 'LXDE'),
    DesktopEnvironment('/usr/bin/lxqt-session', 'lxqt'),
    DesktopEnvironment('/usr/bin/pekwm', 'pekwm'),
    DesktopEnvironment('/usr/bin/pantheon-session', 'pantheon'),
    DesktopEnvironment('/usr/bin/budgie-session', 'budgie-session'),
    DesktopEnvironment('/usr/bin/budgie-desktop', 'budgie-desktop'),
    DesktopEnvironment('/usr/bin/i3', 'i3'),
    DesktopEnvironment('/usr/bin/startdde', 'deepin'),
    DesktopEnvironment('/usr/bin/openbox-session', 'openbox')
]


def find_desktop_environment(root_mount_point):
    """
    Checks which desktop environment is currently installed.

    :param root_mount_point:
    :return:
    """
    for desktop_environment in desktop_environments:
        if desktop_environment.find_desktop_environment(root_mount_point):
            return desktop_environment
    return None


class DisplayManager(metaclass=abc.ABCMeta):
    """
    Display Manager -- a base class for DM configuration.
    """
    name = None
    executable = None

    @classmethod
    def have_dm(cls, root_mount_point):
        if cls.executable is None:
            return True

        bin_path = "{!s}/usr/bin/{!s}".format(root_mount_point, cls.executable)
        sbin_path = "{!s}/usr/sbin/{!s}".format(root_mount_point, cls.executable)
        return (
            os.path.exists(bin_path)
            or os.path.exists(sbin_path)
            )

    @abc.abstractmethod
    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        """
        Configure the DM inside the given @p root_mount_point with
        autologin (if @p do_autologin is True) for the given @p username.
        If the DM supports it, set the default DE to @p default_desktop_environment
        as well.
        """

    @abc.abstractmethod
    def basic_setup(self):
        """
        Do basic setup (e.g. users, groups, directory creation) for this DM.
        """


class DMmdm(DisplayManager):
    name = "mdm"
    executable = "mdm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with MDM as Desktop Manager
        mdm_conf_path = os.path.join(root_mount_point, "etc/mdm/custom.conf")

        if os.path.exists(mdm_conf_path):
            with open(mdm_conf_path, 'r') as mdm_conf:
                text = mdm_conf.readlines()

            with open(mdm_conf_path, 'w') as mdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        if do_autologin:
                            line = (
                                "[daemon]\n"
                                "AutomaticLogin={!s}\n"
                                "AutomaticLoginEnable=True\n".format(username)
                                )
                        else:
                            line = (
                                "[daemon]\n"
                                "AutomaticLoginEnable=False\n"
                                )

                    mdm_conf.write(line)
        else:
            with open(mdm_conf_path, 'w') as mdm_conf:
                mdm_conf.write(
                    '# Calamares - Configure automatic login for user\n'
                    )
                mdm_conf.write('[daemon]\n')

                if do_autologin:
                    mdm_conf.write("AutomaticLogin={!s}\n".format(username))
                    mdm_conf.write('AutomaticLoginEnable=True\n')
                else:
                    mdm_conf.write('AutomaticLoginEnable=False\n')

    def basic_setup(self):
        if libcalamares.utils.target_env_call(
                    ['getent', 'group', 'mdm']
                    ) != 0:
            libcalamares.utils.target_env_call(
                ['groupadd', '-g', '128', 'mdm']
                )

        if libcalamares.utils.target_env_call(
                ['getent', 'passwd', 'mdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['useradd',
                    '-c', '"Linux Mint Display Manager"',
                    '-u', '128',
                    '-g', 'mdm',
                    '-d', '/var/lib/mdm',
                    '-s', '/usr/bin/nologin',
                    'mdm'
                    ]
                )

        libcalamares.utils.target_env_call(
            ['passwd', '-l', 'mdm']
            )
        libcalamares.utils.target_env_call(
            ['chown', 'root:mdm', '/var/lib/mdm']
            )
        libcalamares.utils.target_env_call(
            ['chmod', '1770', '/var/lib/mdm']
            )


class DMgdm(DisplayManager):
    name = "gdm"
    executable = "gdm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with GDM as Desktop Manager
        gdm_conf_path = os.path.join(root_mount_point, "etc/gdm/custom.conf")

        if os.path.exists(gdm_conf_path):
            with open(gdm_conf_path, 'r') as gdm_conf:
                text = gdm_conf.readlines()

            with open(gdm_conf_path, 'w') as gdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        if do_autologin:
                            line = (
                                "[daemon]\n"
                                "AutomaticLogin={!s}\n"
                                "AutomaticLoginEnable=True\n".format(username)
                                )
                        else:
                            line = "[daemon]\nAutomaticLoginEnable=False\n"

                    gdm_conf.write(line)
        else:
            with open(gdm_conf_path, 'w') as gdm_conf:
                gdm_conf.write(
                    '# Calamares - Enable automatic login for user\n'
                    )
                gdm_conf.write('[daemon]\n')

                if do_autologin:
                    gdm_conf.write("AutomaticLogin={!s}\n".format(username))
                    gdm_conf.write('AutomaticLoginEnable=True\n')
                else:
                    gdm_conf.write('AutomaticLoginEnable=False\n')

        if (do_autologin):
            accountservice_dir = "{!s}/var/lib/AccountsService/users".format(
                    root_mount_point
                    )
            userfile_path = "{!s}/{!s}".format(accountservice_dir, username)
            if os.path.exists(accountservice_dir):
                with open(userfile_path, "w") as userfile:
                    userfile.write("[User]\n")

                    if default_desktop_environment is not None:
                        userfile.write("XSession={!s}\n".format(
                            default_desktop_environment.desktop_file))

                    userfile.write("Icon=\n")


    def basic_setup(self):
        if libcalamares.utils.target_env_call(
                ['getent', 'group', 'gdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['groupadd', '-g', '120', 'gdm']
                )

        if libcalamares.utils.target_env_call(
                ['getent', 'passwd', 'gdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['useradd',
                    '-c', '"Gnome Display Manager"',
                    '-u', '120',
                    '-g', 'gdm',
                    '-d', '/var/lib/gdm',
                    '-s', '/usr/bin/nologin',
                    'gdm'
                    ]
                )

        libcalamares.utils.target_env_call(
            ['passwd', '-l', 'gdm']
            )
        libcalamares.utils.target_env_call(
            ['chown', '-R', 'gdm:gdm', '/var/lib/gdm']
            )


class DMkdm(DisplayManager):
    name = "kdm"
    executable = "kdm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with KDM as Desktop Manager
        kdm_conf_path = os.path.join(
            root_mount_point, "usr/share/config/kdm/kdmrc"
            )
        # Check which path is in use: SUSE does something else.
        # Also double-check the default setting. Pick the first
        # one that exists in the target.
        for candidate_kdmrc in (
            "usr/share/config/kdm/kdmrc",
            "usr/share/kde4/config/kdm/kdmrc",
        ):
            p = os.path.join(root_mount_point, candidate_kdmrc)
            if os.path.exists(p):
                kdm_conf_path = p
                break
        text = []

        if os.path.exists(kdm_conf_path):
            with open(kdm_conf_path, 'r') as kdm_conf:
                text = kdm_conf.readlines()

            with open(kdm_conf_path, 'w') as kdm_conf:
                for line in text:
                    if 'AutoLoginEnable=' in line:
                        if do_autologin:
                            line = 'AutoLoginEnable=true\n'
                        else:
                            line = 'AutoLoginEnable=false\n'

                    if do_autologin and 'AutoLoginUser=' in line:
                        line = "AutoLoginUser={!s}\n".format(username)

                    kdm_conf.write(line)
        else:
            return (
                "Cannot write KDM configuration file",
                "KDM config file {!s} does not exist".format(kdm_conf_path)
                )

    def basic_setup(self):
        if libcalamares.utils.target_env_call(
                ['getent', 'group', 'kdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['groupadd', '-g', '135', 'kdm']
                )

        if libcalamares.utils.target_env_call(
                ['getent', 'passwd', 'kdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['useradd',
                    '-u', '135',
                    '-g', 'kdm',
                    '-d', '/var/lib/kdm',
                    '-s', '/bin/false',
                    '-r',
                    '-M',
                    'kdm'
                    ]
                )

        libcalamares.utils.target_env_call(
            ['chown', '-R', '135:135', 'var/lib/kdm']
            )


class DMlxdm(DisplayManager):
    name = "lxdm"
    executable = "lxdm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with LXDM as Desktop Manager
        lxdm_conf_path = os.path.join(root_mount_point, "etc/lxdm/lxdm.conf")
        text = []

        if os.path.exists(lxdm_conf_path):
            with open(lxdm_conf_path, 'r') as lxdm_conf:
                text = lxdm_conf.readlines()

            with open(lxdm_conf_path, 'w') as lxdm_conf:
                for line in text:
                    if 'autologin=' in line:
                        if do_autologin:
                            line = "autologin={!s}\n".format(username)
                        else:
                            line = "# autologin=\n"

                    lxdm_conf.write(line)
        else:
            return (
                "Cannot write LXDM configuration file",
                "LXDM config file {!s} does not exist".format(lxdm_conf_path)
                )

    def basic_setup(self):
        if libcalamares.utils.target_env_call(
                ['getent', 'group', 'lxdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['groupadd', '--system', 'lxdm']
                )

        libcalamares.utils.target_env_call(
            ['chgrp', '-R', 'lxdm', '/var/lib/lxdm']
            )
        libcalamares.utils.target_env_call(
            ['chgrp', 'lxdm', '/etc/lxdm/lxdm.conf']
            )
        libcalamares.utils.target_env_call(
            ['chmod', '+r', '/etc/lxdm/lxdm.conf']
            )


class DMlightdm(DisplayManager):
    name = "lightdm"
    executable = "lightdm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with LightDM as Desktop Manager
        # Ideally, we should use configparser for the ini conf file,
        # but we just do a simple text replacement for now, as it
        # worksforme(tm)
        lightdm_conf_path = os.path.join(
            root_mount_point, "etc/lightdm/lightdm.conf"
            )
        text = []

        if os.path.exists(lightdm_conf_path):
            with open(lightdm_conf_path, 'r') as lightdm_conf:
                text = lightdm_conf.readlines()

            with open(lightdm_conf_path, 'w') as lightdm_conf:
                for line in text:
                    if 'autologin-user=' in line:
                        if do_autologin:
                            line = "autologin-user={!s}\n".format(username)
                        else:
                            line = "#autologin-user=\n"

                    lightdm_conf.write(line)
        else:
            try:
                # Create a new lightdm.conf file; this is documented to be
                # read last, after aeverything in lightdm.conf.d/
                with open(lightdm_conf_path, 'w') as lightdm_conf:
                    if do_autologin:
                        lightdm_conf.write(
                            "autologin-user={!s}\n".format(username))
                    else:
                        lightdm_conf.write(
                            "#autologin-user=\n")
            except FileNotFoundError:
                return (
                    "Cannot write LightDM configuration file",
                    "LightDM config file {!s} does not exist".format(
                        lightdm_conf_path
                        )
                    )


    def basic_setup(self):
        libcalamares.utils.target_env_call(
            ['mkdir', '-p', '/run/lightdm']
            )

        if libcalamares.utils.target_env_call(
                ['getent', 'group', 'lightdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['groupadd', '-g', '620', 'lightdm']
                )

        if libcalamares.utils.target_env_call(
                ['getent', 'passwd', 'lightdm']
                ) != 0:
            libcalamares.utils.target_env_call(
                ['useradd', '-c',
                    '"LightDM Display Manager"',
                    '-u', '620',
                    '-g', 'lightdm',
                    '-d', '/var/run/lightdm',
                    '-s', '/usr/bin/nologin',
                    'lightdm'
                    ]
                )

        libcalamares.utils.target_env_call('passwd', '-l', 'lightdm')
        libcalamares.utils.target_env_call(
            ['chown', '-R', 'lightdm:lightdm', '/run/lightdm']
            )
        libcalamares.utils.target_env_call(
            ['chmod', '+r' '/etc/lightdm/lightdm.conf']
            )


class DMslim(DisplayManager):
    name = "slim"
    executable = "slim"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with Slim as Desktop Manager
        slim_conf_path = os.path.join(root_mount_point, "etc/slim.conf")
        text = []

        if os.path.exists(slim_conf_path):
            with open(slim_conf_path, 'r') as slim_conf:
                text = slim_conf.readlines()

            with open(slim_conf_path, 'w') as slim_conf:
                for line in text:
                    if 'auto_login' in line:
                        if do_autologin:
                            line = 'auto_login yes\n'
                        else:
                            line = 'auto_login no\n'

                    if do_autologin and 'default_user' in line:
                        line = "default_user {!s}\n".format(username)

                    slim_conf.write(line)
        else:
            return (
                "Cannot write SLIM configuration file",
                "SLIM config file {!s} does not exist".format(slim_conf_path)
                )


    def basic_setup(self):
        pass


class DMsddm(DisplayManager):
    name = "sddm"
    executable = "sddm"

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        # Systems with Sddm as Desktop Manager
        sddm_conf_path = os.path.join(root_mount_point, "etc/sddm.conf")

        sddm_config = configparser.ConfigParser(strict=False)
        # Make everything case sensitive
        sddm_config.optionxform = str

        if os.path.isfile(sddm_conf_path):
            sddm_config.read(sddm_conf_path)

        if 'Autologin' not in sddm_config:
            sddm_config.add_section('Autologin')

        if do_autologin:
            sddm_config.set('Autologin', 'User', username)
        elif sddm_config.has_option('Autologin', 'User'):
            sddm_config.remove_option('Autologin', 'User')

        if default_desktop_environment is not None:
            sddm_config.set(
                'Autologin',
                'Session',
                default_desktop_environment.desktop_file
                )

        with open(sddm_conf_path, 'w') as sddm_config_file:
            sddm_config.write(sddm_config_file, space_around_delimiters=False)


    def basic_setup(self):
        pass


class DMsysconfig(DisplayManager):
    name = "sysconfig"
    executable = None

    def set_autologin(self, username, do_autologin, root_mount_point, default_desktop_environment):
        dmauto = "DISPLAYMANAGER_AUTOLOGIN"

        os.system(
            "sed -i -e 's|^{!s}=.*|{!s}=\"{!s}\"|' "
            "{!s}/etc/sysconfig/displaymanager".format(
                            dmauto, dmauto,
                            username if do_autologin else "",
                            root_mount_point
                            )
            )


    def basic_setup(self):
        pass


# Collect all the subclasses of DisplayManager defined above,
# and index them based on the name property of each class.
display_managers = [
    (c.name, c)
    for c in globals().values()
    if type(c) is abc.ABCMeta and issubclass(c, DisplayManager) and c.name
]


def have_dm(dm_name, root_mount_point):
    """
    Checks if display manager is properly installed.

    :param dm_name:
    :param root_mount_point:
    :return:
    """
    bin_path = "{!s}/usr/bin/{!s}".format(root_mount_point, dm_name)
    sbin_path = "{!s}/usr/sbin/{!s}".format(root_mount_point, dm_name)
    return (os.path.exists(bin_path)
            or os.path.exists(sbin_path)
            )



_ = """
    if "mdm" == displaymanager:

    if "gdm" == displaymanager:

    if "kdm" == displaymanager:

    if "lxdm" == displaymanager:

    if "lightdm" == displaymanager:

    if "slim" == displaymanager:

    if "sddm" == displaymanager:

    if "sysconfig" == displaymanager:
"""

def run():
    """
    Configure display managers.

    We acquire a list of displaymanagers, either from config or (overridden)
    from globalstorage. This module will try to set up (including autologin)
    all the displaymanagers in the list, in that specific order. Most distros
    will probably only ship one displaymanager.
    If a displaymanager is in the list but not installed, a debugging message
    is printed and the entry ignored.
    """
    displaymanagers = None
    if "displaymanagers" in libcalamares.job.configuration:
        displaymanagers = libcalamares.job.configuration["displaymanagers"]

    if libcalamares.globalstorage.contains("displayManagers"):
        displaymanagers = libcalamares.globalstorage.value("displayManagers")

    if displaymanagers is None:
        return (
            "No display managers selected for the displaymanager module.",
            "The displaymanagers list is empty or undefined in both"
            "globalstorage and displaymanager.conf."
            )

    username = libcalamares.globalstorage.value("autologinUser")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if "default_desktop_environment" in libcalamares.job.configuration:
        entry = libcalamares.job.configuration["defaultDesktopEnvironment"]
        default_desktop_environment = DesktopEnvironment(
            entry["executable"], entry["desktopFile"]
            )
    else:
        default_desktop_environment = find_desktop_environment(
            root_mount_point
            )

    if "basicSetup" in libcalamares.job.configuration:
        enable_basic_setup = libcalamares.job.configuration["basicSetup"]
    else:
        enable_basic_setup = False

    # Setup slim
    if "slim" in displaymanagers:
        if not have_dm("slim", root_mount_point):
            libcalamares.utils.debug("slim selected but not installed")
            displaymanagers.remove("slim")

    # Setup sddm
    if "sddm" in displaymanagers:
        if not have_dm("sddm", root_mount_point):
            libcalamares.utils.debug("sddm selected but not installed")
            displaymanagers.remove("sddm")

    # setup lightdm
    if "lightdm" in displaymanagers:
        if have_dm("lightdm", root_mount_point):
            lightdm_conf_path = os.path.join(
                root_mount_point, "etc/lightdm/lightdm.conf"
                )

            if default_desktop_environment is not None:
                os.system(
                    "sed -i -e \"s/^.*user-session=.*/user-session={!s}/\" "
                    "{!s}".format(
                        default_desktop_environment.desktop_file,
                        lightdm_conf_path
                        )
                    )

            # configure lightdm-greeter
            greeter_path = os.path.join(
                root_mount_point, "usr/share/xgreeters"
                )

            if (os.path.exists(greeter_path)):
                # configure first found lightdm-greeter
                for entry in os.listdir(greeter_path):
                    if entry.endswith('.desktop'):
                        greeter = entry.split('.')[0]
                        libcalamares.utils.debug(
                            "found greeter {!s}".format(greeter)
                            )
                        os.system(
                            "sed -i -e \"s/^.*greeter-session=.*"
                            "/greeter-session={!s}/\" {!s}".format(
                                greeter,
                                lightdm_conf_path
                                )
                            )
                        libcalamares.utils.debug(
                            "{!s} configured as greeter.".format(greeter)
                            )
                        break
                else:
                    return ("No lightdm greeter installed.")
        else:
            libcalamares.utils.debug("lightdm selected but not installed")
            displaymanagers.remove("lightdm")

    # Setup gdm
    if "gdm" in displaymanagers:
        if have_dm("gdm", root_mount_point):
            pass
        else:
            libcalamares.utils.debug("gdm selected but not installed")
            displaymanagers.remove("gdm")

    # Setup mdm
    if "mdm" in displaymanagers:
        if have_dm("mdm", root_mount_point):
            if default_desktop_environment is not None:
                os.system(
                    "sed -i \"s|default.desktop|{!s}.desktop|g\" "
                    "{!s}/etc/mdm/custom.conf".format(
                        default_desktop_environment.desktop_file,
                        root_mount_point
                        )
                    )
        else:
            libcalamares.utils.debug("mdm selected but not installed")
            displaymanagers.remove("mdm")

    # Setup lxdm
    if "lxdm" in displaymanagers:
        if have_dm("lxdm", root_mount_point):
            if default_desktop_environment is not None:
                os.system(
                    "sed -i -e \"s|^.*session=.*|session={!s}|\" "
                    "{!s}/etc/lxdm/lxdm.conf".format(
                        default_desktop_environment.executable,
                        root_mount_point
                        )
                    )
        else:
            libcalamares.utils.debug("lxdm selected but not installed")
            displaymanagers.remove("lxdm")

    # Setup kdm
    if "kdm" in displaymanagers:
        if have_dm("kdm", root_mount_point):
            pass
        else:
            libcalamares.utils.debug("kdm selected but not installed")
            displaymanagers.remove("kdm")

    if username is not None:
        libcalamares.utils.debug(
            "Setting up autologin for user {!s}.".format(username)
            )
    else:
        libcalamares.utils.debug("Unsetting autologin.")

    libcalamares.globalstorage.insert("displayManagers", displaymanagers)

    dm_setup_message = []
    for dm in displaymanagers:
        impl = [ cls for name, cls in display_managers if name == dm ]
        if len(impl) == 1:
            dm_impl = impl[0]()  # Instantiate the class that was named
            dm_message = None
            if enable_basic_setup:
                dm_message = dm_impl.basic_setup()
            if dm_message is None:
                dm_message = dm_impl.set_autologin(username, default_desktop_environment, root_mount_point)
        else:
            dm_message = ("Can not configure {!s}".format(dm), "{!s} has {!d} implementation classes.".format(dm).format(len(impl)))

        if dm_message is not None:
            dm_setup_message.append("{!s}: {!s}".format(*dm_message))

    if ("sysconfigSetup" in libcalamares.job.configuration
            and libcalamares.job.configuration["sysconfigSetup"]):
        set_autologin(username, "sysconfig", None, root_mount_point)

    if dm_setup_message:
        return ("Display manager configuration was incomplete",
                "\n".join(dm_setup_message))
