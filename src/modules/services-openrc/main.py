#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaida@siduction.org>
#   Copyright 2018, Gabriel Craciunescu <crazy@frugalware.org>
#   Copyright 2018, Ghiunhan Mamut <venerix@redcorelinux.org>
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
    Setup openrc services
    """
    services = libcalamares.job.configuration['services']
    disable = libcalamares.job.configuration['disable']

    # enable services
    for svc in services:
        ec = libcalamares.utils.target_env_call(
            ['rc-update', 'add', '{}'.format(svc['name']), 'default']
            )

        if ec != 0:
            if svc['mandatory']:
                return ("Cannot enable openrc service {}".format(svc['name']),
                        "rc-update add  call in chroot returned error code "
                        "{}".format(ec)
                        )
            else:
                libcalamares.utils.debug(
                    "Cannot enable openrc service {}".format(svc['name'])
                    )
                libcalamares.utils.debug(
                    "rc-update call in chroot returned error code "
                    "{}".format(ec)
                    )

    # disable services
    for dbl in disable:
        ec = libcalamares.utils.target_env_call(
            ['rc-update', 'del', '{}'.format(dbl['name']), 'default']
            )

        if ec != 0:
            if dbl['mandatory']:
                return ("Cannot disable openrc service"
                        "{}".format(dbl['name']),
                        "rc-update del call in chroot returned error code"
                        "{}".format(ec))
            else:
                libcalamares.utils.debug(
                    "Cannot disable openrc service {}".format(dbl['name'])
                    )
                libcalamares.utils.debug(
                    "rc-update del call in chroot returned error code"
                    "{}".format(ec)
                    )

    return None
