#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

"""
=== Example Python jobmodule.

A Python jobmodule is a Python program which imports libcalamares and
has a function run() as entry point. run() must return None if everything
went well, or a tuple (str,str) with an error message and description
if something went wrong.
"""

import libcalamares
import os
from time import gmtime, strftime, sleep

import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext


def pretty_name():
    return _("Dummy python job.")

status = _("Dummy python step {}").format(0)

def pretty_status_message():
    return status

def run():
    """Dummy python job."""
    libcalamares.utils.debug(f"Calamares version: {libcalamares.VERSION} date: {strftime('%Y-%m-%d %H:%M:%S', gmtime())}")
    libcalamares.utils.debug(f"Job name         : {libcalamares.job.pretty_name}")
    libcalamares.utils.debug(f"Job path         : {libcalamares.job.working_path}")

    libcalamares.utils.debug(f"LocaleDir        : {libcalamares.utils.gettext_path()}")
    libcalamares.utils.debug(f"Languages         : {libcalamares.utils.gettext_languages()}")

    os.system("/bin/sh -c \"touch ~/calamares-dummypython\"")

    libcalamares.utils.debug("*** JOB CONFIGURATION ***")
    for k, v in libcalamares.job.configuration.items():
        libcalamares.utils.debug(f"    {k}={v}")

    libcalamares.utils.debug("*** GLOBAL STORAGE ***")
    for k in libcalamares.globalstorage.keys():
        libcalamares.utils.debug(f"    {k}={libcalamares.globalstorage.value(k)}")

    libcalamares.utils.debug("*** GLOBAL STORAGE BOGUS KEYS ***")
    #
    # This is a demonstration of issue #2237, load this module
    # with the dummypython/tests/1.global configuration, e.g.
    #       ./loadmodule -g ../src/modules/dummypython/tests/1.global dummypython
    # in the build directory.
    #
    for k in ("nonexistent", "empty", "numeric", "boolvalue"):
        if libcalamares.globalstorage.value(k) is None:
            libcalamares.utils.debug(f"NONE  {k}={libcalamares.globalstorage.value(k)}")
        else:
            libcalamares.utils.debug(f"      {k}={libcalamares.globalstorage.value(k)}")

    libcalamares.utils.debug("*** GLOBAL STORAGE MODIFICATION ***")
    libcalamares.globalstorage.insert("item2", "value2")
    libcalamares.globalstorage.insert("item3", 3)
    accumulator = "keys: {}\n".format(str(libcalamares.globalstorage.keys()))
    libcalamares.utils.debug(accumulator)

    accumulator = "remove: {}\n".format(
       str(libcalamares.globalstorage.remove("item2")))
    accumulator += "values: {} {} {}\n".format(
        str(libcalamares.globalstorage.value("foo")),
        str(libcalamares.globalstorage.value("item2")),
        str(libcalamares.globalstorage.value("item3")))
    libcalamares.utils.debug(accumulator)

    libcalamares.utils.debug("*** ACTIVITY ***")

    # Expect error message that rootMountPoint is not set
    libcalamares.utils.target_env_call(["ls"])
    libcalamares.utils.target_env_call("ls")

    # Expect error message can't chroot to /tmp
    libcalamares.globalstorage.insert("rootMountPoint", "/tmp")
    libcalamares.utils.target_env_call(["ls"])

    sleep(1)

    million = 1000000
    for i in range(million):
        libcalamares.job.setprogress(i / million)

    try:
        configlist = list(libcalamares.job.configuration["a_list"])
    except KeyError:
        configlist = ["no list"]

    global status
    c = 1
    for k in configlist:
        status = _("Dummy python step {}").format(str(c) + ":" + repr(k))
        libcalamares.utils.debug(_("Dummy python step {}").format(str(k)))
        sleep(1)
        libcalamares.job.setprogress(c * 1.0 / (len(configlist)+1))
        c += 1

    sleep(3)

    # To indicate an error, return a tuple of:
    # (message, detailed-error-message)
    return None
