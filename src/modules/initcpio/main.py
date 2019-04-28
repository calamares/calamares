#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014, Philip Müller <philm@manjaro.org>
#   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
from libcalamares.utils import check_target_env_call

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Creating initramfs with mkinitcpio.")

def run():
    """ Calls routine to create kernel initramfs image.

    :return:
    """
    from subprocess import CalledProcessError

    kernel = libcalamares.job.configuration['kernel']
    try:
        check_target_env_call(['mkinitcpio', '-p', kernel])
    except CalledProcessError as e:
        libcalamares.utils.warning(str(e))
        return ( _( "Process Failed" ),
                 _( "Process <pre>mkinitcpio</pre> failed with error code {!s}. The command was <pre>{!s}</pre>." ).format( e.returncode, e.cmd ) )

    return None
