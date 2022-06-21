#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
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
    return _("Configure systemd services")


def systemctl(targets, command, suffix):
    """
    For each entry in @p targets, run "systemctl <command> <thing>",
    where <thing> is the entry's name plus the given @p suffix.
    (No dot is added between name and suffix; suffix may be empty)

    Returns a failure message, or None if this was successful.
    Services that are not mandatory have their failures suppressed
    silently.
    """
    for svc in targets:
        if isinstance(svc, str):
            name = svc
            mandatory = False
        else:
            name = svc["name"]
            mandatory = svc.get("mandatory", False)

        ec = libcalamares.utils.target_env_call(
            ['systemctl', command, "{}{}".format(name, suffix)]
            )

        if ec != 0:
            libcalamares.utils.warning(
                "Cannot {} systemd {} {}".format(command, suffix, name)
                )
            libcalamares.utils.warning(
                "systemctl {} call in chroot returned error code {}".format(command, ec)
                )
            if mandatory:
                title = _("Cannot modify service")
                diagnostic = _("<code>systemctl {arg!s}</code> call in chroot returned error code {num!s}.").format(arg=command, num=ec)

                if command == "enable" and suffix == ".service":
                    description = _("Cannot enable systemd service <code>{name!s}</code>.")
                elif command == "enable" and suffix == ".target":
                    description = _("Cannot enable systemd target <code>{name!s}</code>.")
                elif command == "enable" and suffix == ".timer":
                    description = _("Cannot enable systemd timer <code>{name!s}</code>.")
                elif command == "disable" and suffix == ".service":
                    description = _("Cannot enable systemd service <code>{name!s}</code>.")
                elif command == "disable" and suffix == ".target":
                    description = _("Cannot disable systemd target <code>{name!s}</code>.")
                elif command == "mask":
                    description = _("Cannot mask systemd unit <code>{name!s}</code>.")
                else:
                    description = _("Unknown systemd commands <code>{command!s}</code> and <code>{suffix!s}</code> for unit {name!s}.")

                return (title,
                        description.format(name=name, command=command, suffix=suffix) + " " + diagnostic
                        )
    return None


def run():
    """
    Setup systemd services
    """
    cfg = libcalamares.job.configuration

    # note that the "systemctl enable" and "systemctl disable" commands used
    # here will work in a chroot; in fact, they are the only systemctl commands
    # that support that, see:
    # http://0pointer.de/blog/projects/changing-roots.html

    r = systemctl(cfg.get("services", []), "enable", ".service")
    if r is not None:
        return r

    r = systemctl(cfg.get("targets", []), "enable", ".target")
    if r is not None:
        return r

    r = systemctl(cfg.get("timers", []), "enable", ".timer")
    if r is not None:
        return r

    r = systemctl(cfg.get("disable", []), "disable", ".service")
    if r is not None:
        return r

    r = systemctl(cfg.get("disable-targets", []), "disable", ".target")
    if r is not None:
        return r

    r = systemctl(cfg.get("mask", []), "mask", "")
    if r is not None:
        return r

    return None
