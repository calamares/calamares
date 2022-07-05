#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2022 shivanandvp <shivanandvp@rebornos.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import libcalamares


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configure systemd units")


def systemctl(command, units):
    """
    For each entry in @p units, run "systemctl <command> <thing>",
    where <thing> is the entry's full name.

    Returns a failure message, or None if this was successful.
    Units that are not mandatory have their failures suppressed
    silently.
    """
    for unit in units:
        if isinstance(unit, str):
            name = unit
            mandatory = False
        else:
            name = unit["name"]
            mandatory = unit.get("mandatory", False)

        exit_code = libcalamares.utils.target_env_call(
            ['systemctl', command, name]
            )

        if exit_code != 0:
            libcalamares.utils.warning(
                "Cannot {} systemd {} {}".format(command, name)
                )
            libcalamares.utils.warning(
                "systemctl {} call in chroot returned error code {}".format(command, exit_code)
                )
            if mandatory:
                title = _("Cannot modify unit")
                diagnostic = _("<code>systemctl {arg!s}</code> call in chroot returned error code {num!s}.").format(arg=command, num=exit_code)

                if command == "enable":
                    description = _("Cannot enable systemd unit <code>{name!s}</code>.")
                elif command == "disable":
                    description = _("Cannot disable systemd unit <code>{name!s}</code>.")
                elif command == "mask":
                    description = _("Cannot mask systemd unit <code>{name!s}</code>.")
                else:
                    description = _("Unknown systemd commands <code>{command!s}</code> for unit {name!s}.")

                return (title,
                        description.format(name=name, command=command) + " " + diagnostic
                        )
    return None


def run():
    """
    Setup systemd units
    """
    cfg = libcalamares.job.configuration

    # note that the "systemctl enable" and "systemctl disable" commands used
    # here will work in a chroot; in fact, they are the only systemctl commands
    # that support that, see:
    # http://0pointer.de/blog/projects/changing-roots.html

    r = systemctl("enable", cfg.get("enable", []))
    if r is not None:
        return r

    r = systemctl("disable", cfg.get("disable", []))
    if r is not None:
        return r

    r = systemctl("mask", cfg.get("mask", []))
    if r is not None:
        return r

    return None
