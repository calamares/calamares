#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014-2018 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2014 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017 Bernhard Landauer <oberon@manjaro.org>
#   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2019 Dominic Hayes <ferenosdev@outlook.com>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import abc
import os
import re
import libcalamares
import configparser

from libcalamares.utils import gettext_path, gettext_languages

import gettext
_translation = gettext.translation("calamares-python",
                                   localedir=gettext_path(),
                                   languages=gettext_languages(),
                                   fallback=True)
_ = _translation.gettext
_n = _translation.ngettext

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

    def _search_executable(self, root_mount_point, pathname):
        """
        Search for @p pathname within @p root_mount_point .
        If the pathname is absolute, just check there inside
        the target, otherwise earch in a sort-of-sensible $PATH.

        Returns the full (including @p root_mount_point) path
        to that executable, or None.
        """
        if pathname.startswith("/"):
            path = [""]
        else:
            path = ["/bin/", "/usr/bin/", "/sbin/", "/usr/local/bin/"]

        for p in path:
            absolute_path = "{!s}{!s}{!s}".format(root_mount_point, p, pathname)
            if os.path.exists(absolute_path):
                return absolute_path
        return None

    def _search_tryexec(self, root_mount_point, absolute_desktop_file):
        """
        Check @p absolute_desktop_file for a TryExec line and, if that is
        found, search for the command (executable pathname) within
        @p root_mount_point. The .desktop file must live within the
        target root.

        Returns the full (including @p root_mount_point) for the executable
        from TryExec, or None.
        """
        assert absolute_desktop_file.startswith(root_mount_point)
        with open(absolute_desktop_file, "r") as f:
            for tryexec_line in [x for x in f.readlines() if x.startswith("TryExec")]:
                try:
                    key, value = tryexec_line.split("=")
                    if key.strip() == "TryExec":
                        return self._search_executable(root_mount_point, value.strip())
                except:
                    pass
        return None

    def find_executable(self, root_mount_point):
        """
        Returns the full path of the configured executable within @p root_mount_point,
        or None if it isn't found. May search in a semi-sensible $PATH.
        """
        return self._search_executable(root_mount_point, self.executable)

    def find_desktop_file(self, root_mount_point):
        """
        Returns the full path of the .desktop file within @p root_mount_point,
        or None if it isn't found.  Searches both X11 and Wayland sessions.
        """
        x11_sessions = "{!s}/usr/share/xsessions/{!s}.desktop".format(root_mount_point, self.desktop_file)
        wayland_sessions = "{!s}/usr/share/wayland-sessions/{!s}.desktop".format(root_mount_point, self.desktop_file)
        for candidate in (x11_sessions, wayland_sessions):
            if os.path.exists(candidate):
                return candidate
        return None

    def is_installed(self, root_mount_point):
        """
        Check if this environment is installed in the
        target system at @p root_mount_point.
        """
        desktop_file = self.find_desktop_file(root_mount_point)
        if desktop_file is None:
            return False

        return (self.find_executable(root_mount_point) is not None or
                self._search_tryexec(root_mount_point, desktop_file) is not None)

    def update_from_desktop_file(self, root_mount_point):
        """
        Find thie DE in the target system at @p root_mount_point.
        This can update the *executable* configuration value if
        the configured executable isn't found but the TryExec line
        from the .desktop file is.

        The .desktop file is mandatory for a DE.

        Returns True if the DE is installed.
        """
        desktop_file = self.find_desktop_file(root_mount_point)
        if desktop_file is None:
            return False

        executable_file = self.find_executable(root_mount_point)
        if executable_file is not None:
            # .desktop found and executable as well.
            return True

        executable_file = self._search_tryexec(root_mount_point, desktop_file)
        if executable_file is not None:
            # Found from the .desktop file, so update own executable config
            if root_mount_point and executable_file.startswith(root_mount_point):
                executable_file = executable_file[len(root_mount_point):]
            if not executable_file:
                # Somehow chopped down to nothing
                return False

            if executable_file[0] != "/":
                executable_file = "/" + executable_file
            self.executable = executable_file
            return True
        # This is to double-check
        return self.is_installed(root_mount_point)


# This is the list of desktop environments that Calamares looks
# for; if no default environment is **explicitly** configured
# in the `displaymanager.conf` then the first one from this list
# that is found, is used.
#
# Each DE has a sample executable to look for, and a .desktop filename.
# If the executable exists, the DE is assumed to be installed
# and to use the given .desktop filename.
#
# If the .desktop file exists and contains a TryExec line and that
# TryExec executable exists (searched in /bin, /usr/bin, /sbin and
# /usr/local/bin) then the DE is assumed to be installed
# and to use that .desktop filename.
desktop_environments = [
    DesktopEnvironment('/usr/bin/startplasma-x11', 'plasma'),  # KDE Plasma 5.17+
    DesktopEnvironment('/usr/bin/startkde', 'plasma'),  # KDE Plasma 5
    DesktopEnvironment('/usr/bin/startkde', 'kde-plasma'),  # KDE Plasma 4
    DesktopEnvironment(
        '/usr/bin/budgie-desktop', 'budgie-desktop'  # Budgie v10
        ),
    DesktopEnvironment(
        '/usr/bin/budgie-session', 'budgie-desktop'  # Budgie v8
        ),
    DesktopEnvironment('/usr/bin/gnome-session', 'gnome'),
    DesktopEnvironment('/usr/bin/cinnamon-session-cinnamon', 'cinnamon'),
    DesktopEnvironment('/usr/bin/mate-session', 'mate'),
    DesktopEnvironment('/usr/bin/enlightenment_start', 'enlightenment'),
    DesktopEnvironment('/usr/bin/lxsession', 'LXDE'),
    DesktopEnvironment('/usr/bin/startlxde', 'LXDE'),
    DesktopEnvironment('/usr/bin/lxqt-session', 'lxqt'),
    DesktopEnvironment('/usr/bin/pekwm', 'pekwm'),
    DesktopEnvironment('/usr/bin/pantheon-session', 'pantheon'),
    DesktopEnvironment('/usr/bin/startdde', 'deepin'),
    DesktopEnvironment('/usr/bin/startxfce4', 'xfce'),
    DesktopEnvironment('/usr/bin/openbox-session', 'openbox'),
    DesktopEnvironment('/usr/bin/i3', 'i3'),
    DesktopEnvironment('/usr/bin/awesome', 'awesome'),
    DesktopEnvironment('/usr/bin/bspwm', 'bspwm'),
    DesktopEnvironment('/usr/bin/herbstluftwm', 'herbstluftwm'),
    DesktopEnvironment('/usr/bin/qtile', 'qtile'),
    DesktopEnvironment('/usr/bin/xmonad', 'xmonad'),
    DesktopEnvironment('/usr/bin/dwm', 'dmw'),
    DesktopEnvironment('/usr/bin/jwm', 'jwm'),
    DesktopEnvironment('/usr/bin/icewm-session', 'icewm-session'),
]


def find_desktop_environment(root_mount_point):
    """
    Checks which desktop environment is currently installed.

    :param root_mount_point:
    :return:
    """
    libcalamares.utils.debug("Using rootMountPoint {!r}".format(root_mount_point))
    for desktop_environment in desktop_environments:
        if desktop_environment.is_installed(root_mount_point):
            libcalamares.utils.debug(".. selected DE {!s}".format(desktop_environment.desktop_file))
            return desktop_environment
    return None


class DisplayManager(metaclass=abc.ABCMeta):
    """
    Display Manager -- a base class for DM configuration.
    """
    name = None
    executable = None

    def __init__(self, root_mount_point):
        self.root_mount_point = root_mount_point

    def have_dm(self):
        """
        Is this DM installed in the target system?
        The default implementation checks for `executable`
        in the target system.
        """
        if self.executable is None:
            return False

        bin_path = "{!s}/usr/bin/{!s}".format(self.root_mount_point, self.executable)
        sbin_path = "{!s}/usr/sbin/{!s}".format(self.root_mount_point, self.executable)
        return os.path.exists(bin_path) or os.path.exists(sbin_path)

    # The four abstract methods below are called in the order listed here.
    # They must all be implemented by subclasses, but not all of them
    # actually do something for all DMs.

    @abc.abstractmethod
    def basic_setup(self):
        """
        Do basic setup (e.g. users, groups, directory creation) for this DM.
        """
        # Some implementations do nothing

    @abc.abstractmethod
    def desktop_environment_setup(self, desktop_environment):
        """
        Configure the given @p desktop_environment as the default one, in
        the configuration files for this DM.
        """
        # Many implementations do nothing

    @abc.abstractmethod
    def greeter_setup(self):
        """
        Additional setup for the greeter.
        """
        # Most implementations do nothing

    @abc.abstractmethod
    def set_autologin(self, username, do_autologin, default_desktop_environment):
        """
        Configure the DM inside the given @p root_mount_point with
        autologin (if @p do_autologin is True) for the given @p username.
        If the DM supports it, set the default DE to @p default_desktop_environment
        as well.
        """


class DMmdm(DisplayManager):
    name = "mdm"
    executable = "mdm"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with MDM as Desktop Manager
        mdm_conf_path = os.path.join(self.root_mount_point, "etc/mdm/custom.conf")

        if os.path.exists(mdm_conf_path):
            with open(mdm_conf_path, 'r') as mdm_conf:
                text = mdm_conf.readlines()

            with open(mdm_conf_path, 'w') as mdm_conf:
                for line in text:
                    if 'AutomaticLogin=' in line:
                        line = ""
                    if 'AutomaticLoginEnable=True' in line:
                        line = ""
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

    def desktop_environment_setup(self, default_desktop_environment):
        os.system(
            "sed -i \"s|default.desktop|{!s}.desktop|g\" "
            "{!s}/etc/mdm/custom.conf".format(
                default_desktop_environment.desktop_file,
                self.root_mount_point
                )
            )

    def greeter_setup(self):
        pass


class DMgdm(DisplayManager):
    name = "gdm"
    executable = "gdm"
    config = None  # Set by have_dm()

    def have_dm(self):
        """
        GDM exists with different executable names, so search
        for one of them and use it.
        """
        for executable, config in (
            ( "gdm", "etc/gdm/custom.conf" ),
            ( "gdm3", "etc/gdm3/daemon.conf" )
        ):
            bin_path = "{!s}/usr/bin/{!s}".format(self.root_mount_point, executable)
            sbin_path = "{!s}/usr/sbin/{!s}".format(self.root_mount_point, executable)
            if os.path.exists(bin_path) or os.path.exists(sbin_path):
                # Keep the found-executable name around for later
                self.executable = executable
                self.config = config
                return True

        return False

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        if self.config is None:
            raise ValueError( "No config file for GDM has been set." )

        # Systems with GDM as Desktop Manager
        gdm_conf_path = os.path.join(self.root_mount_point, self.config)

        if os.path.exists(gdm_conf_path):
            with open(gdm_conf_path, 'r') as gdm_conf:
                text = gdm_conf.readlines()

            with open(gdm_conf_path, 'w') as gdm_conf:
                for line in text:
                    if 'AutomaticLogin=' in line:
                        line = ""
                    if 'AutomaticLoginEnable=True' in line:
                        line = ""
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
                    self.root_mount_point
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

    def desktop_environment_setup(self, desktop_environment):
        pass

    def greeter_setup(self):
        pass


class DMkdm(DisplayManager):
    name = "kdm"
    executable = "kdm"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with KDM as Desktop Manager
        kdm_conf_path = os.path.join(
            self.root_mount_point, "usr/share/config/kdm/kdmrc"
            )
        # Check which path is in use: SUSE does something else.
        # Also double-check the default setting. Pick the first
        # one that exists in the target.
        for candidate_kdmrc in (
            "usr/share/config/kdm/kdmrc",
            "usr/share/kde4/config/kdm/kdmrc",
        ):
            p = os.path.join(self.root_mount_point, candidate_kdmrc)
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
                _("Cannot write KDM configuration file"),
                _("KDM config file {!s} does not exist").format(kdm_conf_path)
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

    def desktop_environment_setup(self, desktop_environment):
        pass

    def greeter_setup(self):
        pass


class DMlxdm(DisplayManager):
    name = "lxdm"
    executable = "lxdm"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with LXDM as Desktop Manager
        lxdm_conf_path = os.path.join(self.root_mount_point, "etc/lxdm/lxdm.conf")
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
                _("Cannot write LXDM configuration file"),
                _("LXDM config file {!s} does not exist").format(lxdm_conf_path)
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

    def desktop_environment_setup(self, default_desktop_environment):
        os.system(
            "sed -i -e \"s|^.*session=.*|session={!s}|\" "
            "{!s}/etc/lxdm/lxdm.conf".format(
                default_desktop_environment.executable,
                self.root_mount_point
                )
            )

    def greeter_setup(self):
        pass


class DMlightdm(DisplayManager):
    name = "lightdm"
    executable = "lightdm"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with LightDM as Desktop Manager
        # Ideally, we should use configparser for the ini conf file,
        # but we just do a simple text replacement for now, as it
        # worksforme(tm)
        lightdm_conf_path = os.path.join(
            self.root_mount_point, "etc/lightdm/lightdm.conf"
            )
        text = []
        addseat = False
        loopcount = 0

        if os.path.exists(lightdm_conf_path):
            with open(lightdm_conf_path, 'r') as lightdm_conf:
                text = lightdm_conf.readlines()
                # Check to make sure [SeatDefaults] or [Seat:*] is in the config,
                # otherwise we'll risk malforming the config
                addseat = '[SeatDefaults]' not in text and '[Seat:*]' not in text

            with open(lightdm_conf_path, 'w') as lightdm_conf:
                if addseat:
                    # Prepend Seat line to start of file rather than leaving it without one
                    # This keeps the config from being malformed for LightDM
                    text = ["[Seat:*]\n"] + text
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
                # read last, after everything in lightdm.conf.d/
                with open(lightdm_conf_path, 'w') as lightdm_conf:
                    if do_autologin:
                        lightdm_conf.write(
                            "[Seat:*]\nautologin-user={!s}\n".format(username))
                    else:
                        lightdm_conf.write(
                            "[Seat:*]\n#autologin-user=\n")
            except FileNotFoundError:
                return (
                    _("Cannot write LightDM configuration file"),
                    _("LightDM config file {!s} does not exist").format(lightdm_conf_path)
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

        libcalamares.utils.target_env_call(['passwd', '-l', 'lightdm'])
        libcalamares.utils.target_env_call(['chown', '-R', 'lightdm:lightdm', '/run/lightdm'])
        libcalamares.utils.target_env_call(['chmod', '+r' '/etc/lightdm/lightdm.conf'])

    def desktop_environment_setup(self, default_desktop_environment):
        os.system(
            "sed -i -e \"s/^.*user-session=.*/user-session={!s}/\" "
            "{!s}/etc/lightdm/lightdm.conf".format(
                default_desktop_environment.desktop_file,
                self.root_mount_point
                )
            )

    def greeter_setup(self):
        lightdm_conf_path = os.path.join(
            self.root_mount_point, "etc/lightdm/lightdm.conf"
            )

        # configure lightdm-greeter
        greeter_path = os.path.join(
            self.root_mount_point, "usr/share/xgreeters"
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
                return (
                    _("Cannot configure LightDM"),
                    _("No LightDM greeter installed.")
                    )


class DMslim(DisplayManager):
    name = "slim"
    executable = "slim"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with Slim as Desktop Manager
        slim_conf_path = os.path.join(self.root_mount_point, "etc/slim.conf")
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
                _("Cannot write SLIM configuration file"),
                _("SLIM config file {!s} does not exist").format(slim_conf_path)
                )


    def basic_setup(self):
        pass

    def desktop_environment_setup(self, desktop_environment):
        pass

    def greeter_setup(self):
        pass


class DMsddm(DisplayManager):
    name = "sddm"
    executable = "sddm"

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        # Systems with Sddm as Desktop Manager
        sddm_conf_path = os.path.join(self.root_mount_point, "etc/sddm.conf")

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

    def desktop_environment_setup(self, desktop_environment):
        pass

    def greeter_setup(self):
        pass


class DMsysconfig(DisplayManager):
    name = "sysconfig"
    executable = None

    def set_autologin(self, username, do_autologin, default_desktop_environment):
        dmauto = "DISPLAYMANAGER_AUTOLOGIN"

        os.system(
            "sed -i -e 's|^{!s}=.*|{!s}=\"{!s}\"|' "
            "{!s}/etc/sysconfig/displaymanager".format(
                            dmauto, dmauto,
                            username if do_autologin else "",
                            self.root_mount_point
                            )
            )


    def basic_setup(self):
        pass

    def desktop_environment_setup(self, desktop_environment):
        pass

    def greeter_setup(self):
        pass

    # For openSUSE-derivatives, there is only sysconfig to configure,
    # and no special DM configuration for it. Instead, check that
    # sysconfig is available in the target.
    def have_dm(self):
        config = "{!s}/etc/sysconfig/displaymanager".format(self.root_mount_point)
        return os.path.exists(config)


# Collect all the subclasses of DisplayManager defined above,
# and index them based on the name property of each class.
display_managers = [
    (c.name, c)
    for c in globals().values()
    if type(c) is abc.ABCMeta and issubclass(c, DisplayManager) and c.name
]


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
    # Get configuration settings for display managers
    displaymanagers = None
    if "displaymanagers" in libcalamares.job.configuration:
        displaymanagers = libcalamares.job.configuration["displaymanagers"]

    if libcalamares.globalstorage.contains("displayManagers"):
        displaymanagers = libcalamares.globalstorage.value("displayManagers")

    if ("sysconfigSetup" in libcalamares.job.configuration
            and libcalamares.job.configuration["sysconfigSetup"]):
        displaymanagers = ["sysconfig"]

    if not displaymanagers:
        return (
            _("No display managers selected for the displaymanager module."),
            _("The displaymanagers list is empty or undefined in both "
            "globalstorage and displaymanager.conf.")
            )

    # Get instances that are actually installed
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    dm_impl = []
    dm_names = displaymanagers[:]
    for dm in dm_names:
        # Find the implementation class
        dm_instance = None
        impl = [ cls for name, cls in display_managers if name == dm ]
        if len(impl) == 1:
            dm_instance = impl[0](root_mount_point)
            if dm_instance.have_dm():
                dm_impl.append(dm_instance)
            else:
                dm_instance = None
        else:
            libcalamares.utils.debug("{!s} has {!d} implementation classes.".format(dm).format(len(impl)))

        if dm_instance is None:
            libcalamares.utils.debug("{!s} selected but not installed".format(dm))
            if dm in displaymanagers:
                displaymanagers.remove(dm)

    if not dm_impl:
        libcalamares.utils.warning(
            "No display managers selected for the displaymanager module. "
            "The list is empty after checking for installed display managers."
            )
        return None

    # Pick up remaining settings
    if "defaultDesktopEnvironment" in libcalamares.job.configuration:
        entry = libcalamares.job.configuration["defaultDesktopEnvironment"]
        default_desktop_environment = DesktopEnvironment(
            entry["executable"], entry["desktopFile"]
            )
        # Adjust if executable is bad, but desktopFile isn't.
        if not default_desktop_environment.update_from_desktop_file(root_mount_point):
            libcalamares.utils.warning(
                "The configured default desktop environment, {!s}, "
                "can not be found.".format(default_desktop_environment.desktop_file))
    else:
        default_desktop_environment = find_desktop_environment(
            root_mount_point
            )

    if "basicSetup" in libcalamares.job.configuration:
        enable_basic_setup = libcalamares.job.configuration["basicSetup"]
    else:
        enable_basic_setup = False

    username = libcalamares.globalstorage.value("autologinUser")
    if username is not None:
        do_autologin = True
        libcalamares.utils.debug("Setting up autologin for user {!s}.".format(username))
    else:
        do_autologin = False
        libcalamares.utils.debug("Unsetting autologin.")

    libcalamares.globalstorage.insert("displayManagers", displaymanagers)

    # Do the actual configuration and collect messages
    dm_setup_message = []
    for dm in dm_impl:
        dm_message = None
        if enable_basic_setup:
            dm_message = dm.basic_setup()
        if default_desktop_environment is not None and dm_message is None:
            dm_message = dm.desktop_environment_setup(default_desktop_environment)
        if dm_message is None:
            dm_message = dm.greeter_setup()
        if dm_message is None:
            dm_message = dm.set_autologin(username, do_autologin, default_desktop_environment)

        if dm_message is not None:
            dm_setup_message.append("{!s}: {!s}".format(*dm_message))

    if dm_setup_message:
        return (
            _("Display manager configuration was incomplete"),
            "\n".join(dm_setup_message)
            )
