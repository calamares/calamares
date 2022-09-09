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

import libcalamares


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Configure systemd units")


def systemctl(units):
    """
    For each entry in @p units, run "systemctl <action> <name>",
    where each unit is a mapping of unit name, action, and a flag.

    Returns a failure message, or None if this was successful.
    Units that are not mandatory have their failures suppressed
    silently.
    """

    for unit in units:
        if isinstance(unit, str):
            name = unit
            action = "enable"
            mandatory = False
        else:
            if "name" not in unit:
                libcalamares.utils.error("The key 'name' is missing from the mapping {_unit!s}. Continuing to the next unit.".format(_unit=str(unit)))
                continue 
            name = unit["name"]
            action = unit.get("action", "enable")
            mandatory = unit.get("mandatory", False)

        exit_code = libcalamares.utils.target_env_call(
            ['systemctl', action, name]
        )

        if exit_code != 0:
            libcalamares.utils.warning(
                "Cannot {} systemd unit {}".format(action, name)
            )
            libcalamares.utils.warning(
                "systemctl {} call in chroot returned error code {}".format(action, exit_code)
            )
            if mandatory:
                title = _("Cannot modify unit")
                diagnostic = _("<code>systemctl {_action!s}</code> call in chroot returned error code {_exit_code!s}.").format(_action=action, _exit_code=exit_code)
                description = _("Cannot {_action!s} systemd unit <code>{_name!s}</code>.").format(_action=action, _name=name)
                return (
                    title,
                    description + " " + diagnostic
                )
    return None


def run():
    """
    Setup systemd units
    """
    cfg = libcalamares.job.configuration

    return_value = systemctl(
        cfg.get("units", [])
    )
    if return_value is not None:
        return return_value

    return None
