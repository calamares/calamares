#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014-2015, Philip Müller <philm@manjaro.org>
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Alf Gaida <agaid@siduction.org>
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
from libcalamares.utils import target_env_call


def run_dracut():
    """
    Creates initramfs, even when initramfs already exists.

    :return:
    """
    return target_env_call(['dracut', '-f'])


def run():
    """
    Starts routine to create initramfs. It passes back the exit code
    if it fails.

    :return:
    """
    return_code = run_dracut()

    if return_code != 0:
        return ("Failed to run dracut on the target",
                "The exit code was {}".format(return_code))
