#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014-2015, Philip Müller <philm@manjaro.org>
#   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
#   Copyright 2014, Kevin Kofler <kevin.kofler@chello.at>
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

import os
import collections
import re
import libcalamares


DesktopEnvironment = collections.namedtuple('DesktopEnvironment', ['executable', 'desktop_file'])

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
    DesktopEnvironment('/usr/bin/openbox-session', 'openbox')
]


def find_desktop_environment(root_mount_point):
    """ Checks which desktop environment is currently installed.

    :param root_mount_point:
    :return:
    """
    for desktop_environment in desktop_environments:
        if os.path.exists(
            "{!s}{!s}".format(root_mount_point, desktop_environment.executable)) \
            and os.path.exists("{!s}/usr/share/xsessions/{!s}.desktop".format(root_mount_point,
                                                                              desktop_environment.desktop_file)):
            return desktop_environment

    return None


def have_dm(dm_name, root_mount_point):
    """ Checks if display manager is properly installed.

    :param dm_name:
    :param root_mount_point:
    :return:
    """
    return os.path.exists(
        "{!s}/usr/bin/{!s}".format(root_mount_point, dm_name)) or os.path.exists(
        "{!s}/usr/sbin/{!s}".format(root_mount_point, dm_name))


def set_autologin(username, displaymanagers, default_desktop_environment, root_mount_point):
    """ Enables automatic login for the installed desktop managers.

    :param username:
    :param displaymanagers:
    :param default_desktop_environment:
    :param root_mount_point:
    """
    do_autologin = True

    if username is None:
        do_autologin = False

    if "mdm" in displaymanagers:
        # Systems with MDM as Desktop Manager
        mdm_conf_path = os.path.join(root_mount_point, "etc/mdm/custom.conf")

        if os.path.exists(mdm_conf_path):
            with open(mdm_conf_path, 'r') as mdm_conf:
                text = mdm_conf.readlines()

            with open(mdm_conf_path, 'w') as mdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        if do_autologin:
                            line = "[daemon]\nAutomaticLogin={!s}\nAutomaticLoginEnable=True\n".format(username)
                        else:
                            line = "[daemon]\nAutomaticLoginEnable=False\n"

                    mdm_conf.write(line)
        else:
            with open(mdm_conf_path, 'w') as mdm_conf:
                mdm_conf.write('# Calamares - Configure automatic login for user\n')
                mdm_conf.write('[daemon]\n')

                if do_autologin:
                    mdm_conf.write("AutomaticLogin={!s}\n".format(username))
                    mdm_conf.write('AutomaticLoginEnable=True\n')
                else:
                    mdm_conf.write('AutomaticLoginEnable=False\n')

    if "gdm" in displaymanagers:
        # Systems with GDM as Desktop Manager
        gdm_conf_path = os.path.join(root_mount_point, "etc/gdm/custom.conf")

        if os.path.exists(gdm_conf_path):
            with open(gdm_conf_path, 'r') as gdm_conf:
                text = gdm_conf.readlines()

            with open(gdm_conf_path, 'w') as gdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        if do_autologin:
                            line = "[daemon]\nAutomaticLogin={!s}\nAutomaticLoginEnable=True\n".format(username)
                        else:
                            line = "[daemon]\nAutomaticLoginEnable=False\n"

                    gdm_conf.write(line)
        else:
            with open(gdm_conf_path, 'w') as gdm_conf:
                gdm_conf.write('# Calamares - Enable automatic login for user\n')
                gdm_conf.write('[daemon]\n')

                if do_autologin:
                    gdm_conf.write("AutomaticLogin={!s}\n".format(username))
                    gdm_conf.write('AutomaticLoginEnable=True\n')
                else:
                    gdm_conf.write('AutomaticLoginEnable=False\n')

        if do_autologin and os.path.exists("{!s}/var/lib/AccountsService/users".format(root_mount_point)):
            os.system("echo \"[User]\" > {!s}/var/lib/AccountsService/users/{!s}".format(root_mount_point, username))

            if default_desktop_environment is not None:
                os.system("echo \"XSession={!s}\" >> {!s}/var/lib/AccountsService/users/{!s}".format(
                          default_desktop_environment.desktop_file, root_mount_point, username))

            os.system("echo \"Icon=\" >> {!s}/var/lib/AccountsService/users/{!s}".format(
                      root_mount_point, username))

    if "kdm" in displaymanagers:
        # Systems with KDM as Desktop Manager
        kdm_conf_path = os.path.join(root_mount_point, "usr/share/config/kdm/kdmrc")
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
            return "Cannot write KDM configuration file", "KDM config file {!s} does not exist".format(kdm_conf_path)

    if "lxdm" in displaymanagers:
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
            return "Cannot write LXDM configuration file", "LXDM config file {!s} does not exist".format(lxdm_conf_path)

    if "lightdm" in displaymanagers:
        # Systems with LightDM as Desktop Manager
        # Ideally, we should use configparser for the ini conf file,
        # but we just do a simple text replacement for now, as it
        # worksforme(tm)
        lightdm_conf_path = os.path.join(root_mount_point, "etc/lightdm/lightdm.conf")
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
            return "Cannot write LightDM configuration file", "LightDM config file {!s} does not exist".format(lightdm_conf_path)

    if "slim" in displaymanagers:
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
            return "Cannot write SLIM configuration file", "SLIM config file {!s} does not exist".format(slim_conf_path)

    if "sddm" in displaymanagers:
        # Systems with Sddm as Desktop Manager
        sddm_conf_path = os.path.join(root_mount_point, "etc/sddm.conf")

        if os.path.isfile(sddm_conf_path):
            libcalamares.utils.debug('SDDM config file exists')
        else:
            libcalamares.utils.check_target_env_call(["sh", "-c", "sddm --example-config > /etc/sddm.conf"])

        text = []

        with open(sddm_conf_path, 'r') as sddm_conf:
            text = sddm_conf.readlines()

        with open(sddm_conf_path, 'w') as sddm_conf:
            for line in text:
                # User= line, possibly commented out
                if re.match('\\s*(?:#\\s*)?User=', line):
                    if do_autologin:
                        line = 'User={}\n'.format(username)
                    else:
                        line = '#User=\n'

                # Session= line, commented out or with empty value
                if re.match('\\s*#\\s*Session=|\\s*Session=$', line):
                    if default_desktop_environment is not None:
                        if do_autologin:
                            line = 'Session={}.desktop\n'.format(default_desktop_environment.desktop_file)
                        else:
                            line = '#Session={}.desktop\n'.format(default_desktop_environment.desktop_file)

                sddm_conf.write(line)

    return None


def run():
    """ Configure display managers.

    We acquire a list of displaymanagers, either from config or (overridden) from globalstorage.
    This module will try to set up (including autologin) all the displaymanagers in the list, in that specific order.
    Most distros will probably only ship one displaymanager.
    If a displaymanager is in the list but not installed, a debugging message is printed and the entry ignored.
    """
    if "displaymanagers" in libcalamares.job.configuration:
        displaymanagers = libcalamares.job.configuration["displaymanagers"]

    if libcalamares.globalstorage.contains("displaymanagers"):
        displaymanagers = libcalamares.globalstorage.value("displaymanagers")

    if displaymanagers is None:
        return "No display managers selected for the displaymanager module.", \
               "The displaymanagers list is empty or undefined in both globalstorage and displaymanager.conf."

    username = libcalamares.globalstorage.value("autologinUser")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if "default_desktop_environment" in libcalamares.job.configuration:
        entry = libcalamares.job.configuration["defaultDesktopEnvironment"]
        default_desktop_environment = DesktopEnvironment(entry["executable"],
                                                         entry["desktopFile"])
    else:
        default_desktop_environment = find_desktop_environment(root_mount_point)

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
            if enable_basic_setup:
                libcalamares.utils.target_env_call(['mkdir', '-p', '/run/lightdm'])

                if libcalamares.utils.target_env_call(['getent', 'group', 'lightdm']) != 0:
                    libcalamares.utils.target_env_call(['groupadd', '-g', '620', 'lightdm'])

                if libcalamares.utils.target_env_call(['getent', 'passwd', 'lightdm']) != 0:
                    libcalamares.utils.target_env_call(['useradd', '-c', '"LightDM Display Manager"',
                                                    '-u', '620', '-g', 'lightdm', '-d', '/var/run/lightdm',
                                                    '-s', '/usr/bin/nologin', 'lightdm'])

                libcalamares.utils.target_env_call(['passwd', '-l', 'lightdm'])
                libcalamares.utils.target_env_call(['chown', '-R', 'lightdm:lightdm', '/run/lightdm'])
                libcalamares.utils.target_env_call(['chmod', '+r' '/etc/lightdm/lightdm.conf'])

            if default_desktop_environment is not None:
                os.system("sed -i -e \"s/^.*user-session=.*/user-session={!s}/\" {!s}/etc/lightdm/lightdm.conf".format(
                          default_desktop_environment.desktop_file, root_mount_point))
        else:
            libcalamares.utils.debug("lightdm selected but not installed")
            displaymanagers.remove("lightdm")

    # Setup gdm
    if "gdm" in displaymanagers:
        if have_dm("gdm", root_mount_point):
            if enable_basic_setup:
                if libcalamares.utils.target_env_call(['getent', 'group', 'gdm']) != 0:
                    libcalamares.utils.target_env_call(['groupadd', '-g', '120', 'gdm'])

                if libcalamares.utils.target_env_call(['getent', 'passwd', 'gdm']) != 0:
                    libcalamares.utils.target_env_call(['useradd', '-c', '"Gnome Display Manager"',
                                                    '-u', '120', '-g', 'gdm', '-d', '/var/lib/gdm',
                                                    '-s', '/usr/bin/nologin', 'gdm'])

                libcalamares.utils.target_env_call(['passwd', '-l', 'gdm'])
                libcalamares.utils.target_env_call(['chown', '-R', 'gdm:gdm', '/var/lib/gdm'])
        else:
            libcalamares.utils.debug("gdm selected but not installed")
            displaymanagers.remove("gdm")

    # Setup mdm
    if "mdm" in displaymanagers:
        if have_dm("mdm", root_mount_point):
            if enable_basic_setup:
                if libcalamares.utils.target_env_call(['getent', 'group', 'mdm']) != 0:
                    libcalamares.utils.target_env_call(['groupadd', '-g', '128', 'mdm'])

                if libcalamares.utils.target_env_call(['getent', 'passwd', 'mdm']) != 0:
                    libcalamares.utils.target_env_call(['useradd', '-c', '"Linux Mint Display Manager"',
                                                    '-u', '128', '-g', 'mdm', '-d', '/var/lib/mdm',
                                                    '-s', '/usr/bin/nologin', 'mdm'])

                libcalamares.utils.target_env_call(['passwd', '-l', 'mdm'])
                libcalamares.utils.target_env_call(['chown', 'root:mdm', '/var/lib/mdm'])
                libcalamares.utils.target_env_call(['chmod', '1770', '/var/lib/mdm'])

            if default_desktop_environment is not None:
                os.system("sed -i \"s|default.desktop|{!s}.desktop|g\" {!s}/etc/mdm/custom.conf".format(
                          default_desktop_environment.desktop_file, root_mount_point))
        else:
            libcalamares.utils.debug("mdm selected but not installed")
            displaymanagers.remove("mdm")

    # Setup lxdm
    if "lxdm" in displaymanagers:
        if have_dm("lxdm", root_mount_point):
            if enable_basic_setup:
                if libcalamares.utils.target_env_call(['getent', 'group', 'lxdm']) != 0:
                    libcalamares.utils.target_env_call(['groupadd', '--system', 'lxdm'])

                libcalamares.utils.target_env_call(['chgrp', '-R', 'lxdm', '/var/lib/lxdm'])
                libcalamares.utils.target_env_call(['chgrp', 'lxdm', '/etc/lxdm/lxdm.conf'])
                libcalamares.utils.target_env_call(['chmod', '+r', '/etc/lxdm/lxdm.conf'])

            if default_desktop_environment is not None:
                os.system("sed -i -e \"s|^.*session=.*|session={!s}|\" {!s}/etc/lxdm/lxdm.conf".format(
                          default_desktop_environment.executable, root_mount_point))
        else:
            libcalamares.utils.debug("lxdm selected but not installed")
            displaymanagers.remove("lxdm")

    # Setup kdm
    if "kdm" in displaymanagers:
        if have_dm("kdm", root_mount_point):
            if enable_basic_setup:
                if libcalamares.utils.target_env_call(['getent', 'group', 'kdm']) != 0:
                    libcalamares.utils.target_env_call(['groupadd', '-g', '135', 'kdm'])

                if libcalamares.utils.target_env_call(['getent', 'passwd', 'kdm']) != 0:
                    libcalamares.utils.target_env_call(['useradd', '-u', '135', '-g', 'kdm', '-d',
                                                    '/var/lib/kdm', '-s', '/bin/false', '-r', '-M', 'kdm'])

                libcalamares.utils.target_env_call(['chown', '-R', '135:135', 'var/lib/kdm'])
        else:
            libcalamares.utils.debug("kdm selected but not installed")
            displaymanagers.remove("kdm")

    if username is not None:
        libcalamares.utils.debug("Setting up autologin for user {!s}.".format(username))
    else:
        libcalamares.utils.debug("Unsetting autologin.")

    return set_autologin(username, displaymanagers, default_desktop_environment, root_mount_point)
