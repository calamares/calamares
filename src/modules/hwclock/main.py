#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014-2015 Philip Müller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017-2018 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
    return _("Setting hardware clock.")


def run():
    """
    Set hardware clock.
    """
    hwclock_rtc = ["hwclock", "--systohc", "--utc"]
    hwclock_isa = ["hwclock", "--systohc", "--utc", "--directisa"]
    is_broken_rtc = False
    is_broken_isa = False

    ret = libcalamares.utils.target_env_call(hwclock_rtc)
    if ret != 0:
        is_broken_rtc = True
        libcalamares.utils.debug("Hwclock returned error code {}".format(ret))
        libcalamares.utils.debug("  .. RTC method failed, trying ISA bus method.")
    else:
        libcalamares.utils.debug("Hwclock set using RTC method.")
    if is_broken_rtc:
        ret = libcalamares.utils.target_env_call(hwclock_isa)
        if  ret != 0:
            is_broken_isa = True
            libcalamares.utils.debug("Hwclock returned error code {}".format(ret))
            libcalamares.utils.debug("  .. ISA bus method failed.")
        else:
            libcalamares.utils.debug("Hwclock set using ISA bus method.")
    if is_broken_rtc and is_broken_isa:
        libcalamares.utils.debug("BIOS or Kernel BUG: Setting hwclock failed.")

    return None
