#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

import libcalamares


def run():
    """
    Setup systemd services
    """
    services = libcalamares.job.configuration['services']
    targets = libcalamares.job.configuration['targets']
    disable = libcalamares.job.configuration['disable']

    # note that the "systemctl enable" and "systemctl disable" commands used
    # here will work in a chroot; in fact, they are the only systemctl commands
    # that support that, see:
    # http://0pointer.de/blog/projects/changing-roots.html

    # enable services
    for svc in services:
        ec = libcalamares.utils.target_env_call(
            ['systemctl', 'enable', '{}.service'.format(svc['name'])]
            )

        if ec != 0:
            if svc['mandatory']:
                return ("Cannot enable systemd service {}".format(svc['name']),
                        "systemctl enable call in chroot returned error code "
                        "{}".format(ec)
                        )
            else:
                libcalamares.utils.debug(
                    "Cannot enable systemd service {}".format(svc['name'])
                    )
                libcalamares.utils.debug(
                    "systemctl enable call in chroot returned error code "
                    "{}".format(ec)
                    )

    # enable targets
    for tgt in targets:
        ec = libcalamares.utils.target_env_call(
            ['systemctl', 'enable', '{}.target'.format(tgt['name'])]
            )

        if ec != 0:
            if tgt['mandatory']:
                return ("Cannot enable systemd target {}".format(tgt['name']),
                        "systemctl enable call in chroot returned error code"
                        "{}".format(ec)
                        )
            else:
                libcalamares.utils.debug(
                    "Cannot enable systemd target {}".format(tgt['name'])
                    )
                libcalamares.utils.debug(
                    "systemctl enable call in chroot returned error code "
                    "{}".format(ec)
                    )

    for dbl in disable:
        ec = libcalamares.utils.target_env_call(
            ['systemctl', 'disable', '{}.service'.format(dbl['name'])]
            )

        if ec != 0:
            if dbl['mandatory']:
                return ("Cannot disable systemd service"
                        "{}".format(dbl['name']),
                        "systemctl disable call in chroot returned error code"
                        "{}".format(ec))
            else:
                libcalamares.utils.debug(
                    "Cannot disable systemd service {}".format(dbl['name'])
                    )
                libcalamares.utils.debug(
                    "systemctl disable call in chroot returned error code "
                    "{}".format(ec)
                    )

    return None
