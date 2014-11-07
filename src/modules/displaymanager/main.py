#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
import subprocess


DesktopEnvironment = collections.namedtuple('DesktopEnvironment', ['executable', 'desktop_file'])

desktop_environments = [
    DesktopEnvironment('/usr/bin/startkde', 'plasma'), # KDE Plasma 5
    DesktopEnvironment('/usr/bin/startkde', 'kde-plasma'), # KDE Plasma 4
    DesktopEnvironment('/usr/bin/gnome-session', 'gnome'),
    DesktopEnvironment('/usr/bin/startxfce4', 'xfce'),
    DesktopEnvironment('/usr/bin/cinnamon-session', 'cinnamon-session'),
    DesktopEnvironment('/usr/bin/mate-session', 'mate'),
    DesktopEnvironment('/usr/bin/enlightenment_start', 'enlightenment'),
    DesktopEnvironment('/usr/bin/openbox-session', 'openbox'),
    DesktopEnvironment('/usr/bin/lxsession', 'LXDE')
]

def find_desktop_environment(root_mount_point):
    for desktop_environment in desktop_environments:
        if os.path.exists('%s%s' % (root_mount_point, desktop_environment.executable)) \
           and os.path.exists('%s/usr/share/xsessions/%s.desktop' % (root_mount_point, desktop_environment.desktop_file)):
            return desktop_environment
    return None

def set_autologin(username, displaymanagers, root_mount_point):
    """ Enables automatic login for the installed desktop managers """

    if "mdm" in displaymanagers:
        # Systems with MDM as Desktop Manager
        mdm_conf_path = os.path.join(root_mount_point, "etc/mdm/custom.conf")
        if os.path.exists(mdm_conf_path):
            with open(mdm_conf_path, 'r') as mdm_conf:
                text = mdm_conf.readlines()
            with open(mdm_conf_path, 'w') as mdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        line = '[daemon]\nAutomaticLogin=%s\nAutomaticLoginEnable=True\n' % username
                    mdm_conf.write(line)
        else:
            with open(mdm_conf_path, 'w') as mdm_conf:
                mdm_conf.write(
                    '# Calamares - Enable automatic login for user\n')
                mdm_conf.write('[daemon]\n')
                mdm_conf.write('AutomaticLogin=%s\n' % username)
                mdm_conf.write('AutomaticLoginEnable=True\n')

    if "gdm" in displaymanagers:
        # Systems with GDM as Desktop Manager
        gdm_conf_path = os.path.join(root_mount_point, "etc/gdm/custom.conf")
        if os.path.exists(gdm_conf_path):
            with open(gdm_conf_path, 'r') as gdm_conf:
                text = gdm_conf.readlines()
            with open(gdm_conf_path, 'w') as gdm_conf:
                for line in text:
                    if '[daemon]' in line:
                        line = '[daemon]\nAutomaticLogin=%s\nAutomaticLoginEnable=True\n' % username
                    gdm_conf.write(line)
        else:
            with open(gdm_conf_path, 'w') as gdm_conf:
                gdm_conf.write(
                    '# Calamares - Enable automatic login for user\n')
                gdm_conf.write('[daemon]\n')
                gdm_conf.write('AutomaticLogin=%s\n' % username)
                gdm_conf.write('AutomaticLoginEnable=True\n')

    if "kdm" in displaymanagers:
        # Systems with KDM as Desktop Manager
        kdm_conf_path = os.path.join(
            root_mount_point, "usr/share/config/kdm/kdmrc")
        text = []
        if os.path.exists(kdm_conf_path):
            with open(kdm_conf_path, 'r') as kdm_conf:
                text = kdm_conf.readlines()
            with open(kdm_conf_path, 'w') as kdm_conf:
                for line in text:
                    if '#AutoLoginEnable=true' in line:
                        line = 'AutoLoginEnable=true\n'
                    if 'AutoLoginUser=' in line:
                        line = 'AutoLoginUser=%s\n' % username
                    kdm_conf.write(line)
        else:
            return "Cannot write KDM configuration file", "KDM config file %s does not exist" % kdm_conf_path

    if "lxdm" in displaymanagers:
        # Systems with LXDM as Desktop Manager
        lxdm_conf_path = os.path.join(root_mount_point, "etc/lxdm/lxdm.conf")
        text = []
        if os.path.exists(lxdm_conf_path):
            with open(lxdm_conf_path, 'r') as lxdm_conf:
                text = lxdm_conf.readlines()
            with open(lxdm_conf_path, 'w') as lxdm_conf:
                for line in text:
                    if '# autologin=dgod' in line:
                        line = 'autologin=%s\n' % username
                    lxdm_conf.write(line)
        else:
            return "Cannot write LXDM configuration file", "LXDM config file %s does not exist" % lxdm_conf_path

    if "lightdm" in displaymanagers:
        # Systems with LightDM as Desktop Manager
        # Ideally, we should use configparser for the ini conf file,
        # but we just do a simple text replacement for now, as it
        # worksforme(tm)
        lightdm_conf_path = os.path.join(
            root_mount_point, "etc/lightdm/lightdm.conf")
        text = []
        if os.path.exists(lightdm_conf_path):
            with open(lightdm_conf_path, 'r') as lightdm_conf:
                text = lightdm_conf.readlines()
            with open(lightdm_conf_path, 'w') as lightdm_conf:
                for line in text:
                    if '#autologin-user=' in line:
                        line = 'autologin-user=%s\n' % username
                    lightdm_conf.write(line)
        else:
            return "Cannot write LightDM configuration file", "LightDM config file %s does not exist" % lightdm_conf_path

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
                        line = 'auto_login yes\n'
                    if 'default_user' in line:
                        line = 'default_user %s\n' % username
                    slim_conf.write(line)
        else:
            return "Cannot write SLIM configuration file", "SLIM config file %s does not exist" % slim_conf_path

    if "sddm" in displaymanagers:
        # Systems with Sddm as Desktop Manager
        sddm_conf_path = os.path.join(root_mount_point, "etc/sddm.conf")
        if os.path.isfile(sddm_conf_path):
            print('SDDM config file exists')
        else:
            libcalamares.utils.check_chroot_call("sddm --example-config > /etc/sddm.conf")
        text = []
        with open(sddm_conf_path, 'r') as sddm_conf:
            text = sddm_conf.readlines()
        with open(sddm_conf_path, 'w') as sddm_conf:
            for line in text:
                # User= line, possibly commented out
                if re.match('\\s*(?:#\\s*)?User=', line):
                    line = 'User={}\n'.format(username)
                sddm_conf.write(line)
       
    return None


def run():
    """ Configure display managers """
    # We acquire a list of displaymanagers, either from config or (overridden) from globalstorage.
    # This module will try to set up (including autologin) all the displaymanagers in the list, in that specific order.
    # Most distros will probably only ship one displaymanager.
    # If a displaymanager is in the list but not installed, this module quits with error.

    if "displaymanagers" in libcalamares.job.configuration:
        displaymanagers = libcalamares.job.configuration["displaymanagers"]

    if libcalamares.globalstorage.contains("displaymanagers"):
        displaymanagers = libcalamares.globalstorage.value("displaymanagers")

    if displaymanagers is None:
        return "No display managers selected for the displaymanager module.",\
               "The displaymanagers list is empty or undefined in both globalstorage and displaymanager.conf."

    username = libcalamares.globalstorage.value("autologinUser")
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    # Setup slim
    if "slim" in displaymanagers:
        if not os.path.exists("%s/usr/bin/slim" % root_mount_point):
            return "slim selected but not installed", ""

    # Setup sddm
    if "sddm" in displaymanagers:
        if not os.path.exists("%s/usr/bin/sddm" % root_mount_point):
            return "sddm selected but not installed", ""

    # setup lightdm
    if "lightdm" in displaymanagers:
        if os.path.exists("%s/usr/bin/lightdm" % root_mount_point):
            libcalamares.utils.chroot_call(['mkdir', '-p', '/run/lightdm'])
            libcalamares.utils.chroot_call(['getent', 'group', 'lightdm'])
            libcalamares.utils.chroot_call(
                ['groupadd', '-g', '620', 'lightdm'])
            libcalamares.utils.chroot_call(['getent', 'passwd', 'lightdm'])
            libcalamares.utils.chroot_call(['useradd', '-c', '"LightDM Display Manager"',
                                            '-u', '620', '-g', 'lightdm', '-d', '/var/run/lightdm',
                                            '-s', '/usr/bin/nologin', 'lightdm'])
            libcalamares.utils.chroot_call(['passwd', '-l', 'lightdm'])
            libcalamares.utils.chroot_call(
                ['chown', '-R', 'lightdm:lightdm', '/run/lightdm'])
            default_desktop_environment = find_desktop_environment(root_mount_point)
            if default_desktop_environment != None:
                os.system(
                    "sed -i -e 's/^.*user-session=.*/user-session=%s/' %s/etc/lightdm/lightdm.conf" % (default_desktop_environment.desktop_file, root_mount_point))
            libcalamares.utils.chroot_call(['ln', '-s',
                                            '/usr/lib/lightdm/lightdm/gdmflexiserver',
                                            '/usr/bin/gdmflexiserver'])
            libcalamares.utils.chroot_call(
                ['chmod', '+r' '/etc/lightdm/lightdm.conf'])
        else:
            return "lightdm selected but not installed", ""

    # Setup gdm
    if "gdm" in displaymanagers:
        if os.path.exists("%s/usr/bin/gdm" % root_mount_point):
            libcalamares.utils.chroot_call(['getent', 'group', 'gdm'])
            libcalamares.utils.chroot_call(['groupadd', '-g', '120', 'gdm'])
            libcalamares.utils.chroot_call(['getent', 'passwd', 'gdm'])
            libcalamares.utils.chroot_call(['useradd', '-c', '"Gnome Display Manager"',
                                            '-u', '120', '-g', 'gdm', '-d', '/var/lib/gdm',
                                            '-s', '/usr/bin/nologin', 'gdm'])
            libcalamares.utils.chroot_call(['passwd', '-l', 'gdm'])
            libcalamares.utils.chroot_call(
                ['chown', '-R', 'gdm:gdm', '/var/lib/gdm'])
            if os.path.exists("%s/var/lib/AccountsService/users" % root_mount_point):
                os.system(
                    "echo \"[User]\" > %s/var/lib/AccountsService/users/gdm" % root_mount_point)
            default_desktop_environment = find_desktop_environment(root_mount_point)
            if default_desktop_environment != None:
                os.system(
                    "echo \"XSession=%s\" >> %s/var/lib/AccountsService/users/gdm" % (default_desktop_environment.desktop_file, root_mount_point))
            os.system(
                "echo \"Icon=\" >> %s/var/lib/AccountsService/users/gdm" % root_mount_point)
        else:
            return "gdm selected but not installed", ""

    # Setup mdm
    if "mdm" in displaymanagers:
        if os.path.exists("%s/usr/bin/mdm" % root_mount_point):
            libcalamares.utils.chroot_call(['getent', 'group', 'mdm'])
            libcalamares.utils.chroot_call(['groupadd', '-g', '128', 'mdm'])
            libcalamares.utils.chroot_call(['getent', 'passwd', 'mdm'])
            libcalamares.utils.chroot_call(['useradd', '-c', '"Linux Mint Display Manager"',
                                            '-u', '128', '-g', 'mdm', '-d', '/var/lib/mdm',
                                            '-s', '/usr/bin/nologin', 'mdm'])
            libcalamares.utils.chroot_call(['passwd', '-l', 'mdm'])
            libcalamares.utils.chroot_call(
                ['chown', 'root:mdm', '/var/lib/mdm'])
            libcalamares.utils.chroot_call(['chmod', '1770', '/var/lib/mdm'])
            default_desktop_environment = find_desktop_environment(root_mount_point)
            if default_desktop_environment != None:
                os.system(
                    "sed -i 's|default.desktop|%s.desktop|g' %s/etc/mdm/custom.conf" % (default_desktop_environment.desktop_file, root_mount_point))
        else:
            return "mdm selected but not installed", ""

    # Setup lxdm
    if "lxdm" in displaymanagers:
        if os.path.exists("%s/usr/bin/lxdm" % root_mount_point):
            libcalamares.utils.chroot_call(['groupadd', '--system', 'lxdm'])
            default_desktop_environment = find_desktop_environment(root_mount_point)
            if default_desktop_environment != None:
                os.system(
                    "sed -i -e 's|^.*session=.*|session=%s|' %s/etc/lxdm/lxdm.conf" % (default_desktop_environment.executable, root_mount_point))
            libcalamares.utils.chroot_call(
                ['chgrp', '-R', 'lxdm', '/var/lib/lxdm'])
            libcalamares.utils.chroot_call(
                ['chgrp', 'lxdm', '/etc/lxdm/lxdm.conf'])
            libcalamares.utils.chroot_call(
                ['chmod', '+r', '/etc/lxdm/lxdm.conf'])
        else:
            return "lxdm selected but not installed", ""

    # Setup kdm
    if "kdm" in displaymanagers:
        if os.path.exists("%s/usr/bin/kdm" % root_mount_point):
            libcalamares.utils.chroot_call(['getent', 'group', 'kdm'])
            libcalamares.utils.chroot_call(['groupadd', '-g', '135', 'kdm'])
            libcalamares.utils.chroot_call(['getent', 'passwd', 'kdm'])
            libcalamares.utils.chroot_call(['useradd', '-u', '135', '-g', 'kdm', '-d',
                                            '/var/lib/kdm', '-s', '/bin/false', '-r', '-M', 'kdm'])
            libcalamares.utils.chroot_call(
                ['chown', '-R', '135:135', 'var/lib/kdm'])
            libcalamares.utils.chroot_call(
                ['xdg-icon-resource', 'forceupdate', '--theme', 'hicolor'])
            libcalamares.utils.chroot_call(['update-desktop-database', '-q'])
        else:
            return "kdm selected but not installed", ""

    if username != None:
        libcalamares.utils.debug(
            "Setting up autologin for user %s." % username)
        return set_autologin(username, displaymanagers, root_mount_point)

    return None
