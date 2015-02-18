#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
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

import libcalamares


def run():
    """ Setup systemd services """

    services = libcalamares.job.configuration['services']
    targets = libcalamares.job.configuration['targets']

    # enable services
    for svc in services:
        ec = libcalamares.utils.chroot_call(['systemctl',
                                             'enable',
                                             '{}.service'.format(svc['name'])])
        if ec != 0:
            if svc['mandatory']:
                return "Cannot enable systemd service {}".format(svc['name']), \
                       "systemctl enable call in chroot returned error code {}".format(ec)
            else:
                libcalamares.utils.debug(
                    "Cannot enable systemd service {}".format(svc['name']))
                libcalamares.utils.debug(
                    "systemctl enable call in chroot returned error code {}".format(ec))

    # enable targets
    for tgt in targets:
        ec = libcalamares.utils.chroot_call(['systemctl',
                                             'enable',
                                             '{}.target'.format(tgt['name'])])
        if ec != 0:
            if tgt['mandatory']:
                return "Cannot enable systemd target {}".format(tgt['name']), \
                       "systemctl enable call in chroot returned error code {}".format(ec)
            else:
                libcalamares.utils.debug(
                    "Cannot enable systemd target {}".format(tgt['name']))
                libcalamares.utils.debug(
                    "systemctl enable call in chroot returned error code {}".format(ec))

    return None
