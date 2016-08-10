#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Anke Boersma <demm@kaosx.us>
#   Copyright 2015, Philip Müller <philm@manjaro.org>
#   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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
import shutil

import libcalamares


def run():
    """ Create locale """
    en_us_locale = '#en_US'
    locale = libcalamares.globalstorage.value("localeConf")

    if not locale:
        locale = 'en_US.UTF-8 UTF-8'

    install_path = libcalamares.globalstorage.value("rootMountPoint")

    # restore backup if available
    if os.path.exists('/etc/locale.gen.bak'):
        shutil.copy2("{!s}/etc/locale.gen.bak".format(install_path),
                     "{!s}/etc/locale.gen".format(install_path))

    # run locale-gen if detected
    if os.path.exists('/etc/locale.gen'):
        text = []

        with open("{!s}/etc/locale.gen".format(install_path), "r") as gen:
            text = gen.readlines()

        # always enable en_US
        with open("{!s}/etc/locale.gen".format(install_path), "w") as gen:
            for line in text:
                if en_us_locale in line and line[0] == "#":
                    # uncomment line
                    line = line[1:].lstrip()

                if locale in line and line[0] == "#":
                    # uncomment line
                    line = line[1:].lstrip()

                gen.write(line)

        libcalamares.utils.target_env_call(['locale-gen'])
        print('locale.gen done')

    # write /etc/locale.conf
    locale_conf_path = os.path.join(install_path, "etc/locale.conf")
    with open(locale_conf_path, "w") as locale_conf:
        locale_split = locale.split(' ')[0]
        locale_conf.write("LANG={!s}\n".format(locale_split))
        locale_conf.write("LC_NUMERIC={!s}\n".format(locale_split))
        locale_conf.write("LC_TIME={!s}\n".format(locale_split))
        locale_conf.write("LC_MONETARY={!s}\n".format(locale_split))
        locale_conf.write("LC_PAPER={!s}\n".format(locale_split))
        locale_conf.write("LC_NAME={!s}\n".format(locale_split))
        locale_conf.write("LC_ADDRESS={!s}\n".format(locale_split))
        locale_conf.write("LC_TELEPHONE={!s}\n".format(locale_split))
        locale_conf.write("LC_MEASUREMENT={!s}\n".format(locale_split))
        locale_conf.write("LC_IDENTIFICATION={!s}\n".format(locale_split))

    # write /etc/default/locale if /etc/default exists and is a dir
    etc_default_path = os.path.join(install_path, "etc/default")
    if os.path.isdir(etc_default_path):
        with open(os.path.join(etc_default_path, "locale"), "w") as etc_default_locale:
            locale_split = locale.split(' ')[0]
            etc_default_locale.write("LANG={!s}\n".format(locale_split))

    return None
