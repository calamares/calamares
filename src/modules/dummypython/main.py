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
    libcalamares.utils.debug("LocaleDir=" +
                             str(libcalamares.utils.gettext_path()))
    libcalamares.utils.debug("Languages=" +
                             str(libcalamares.utils.gettext_languages()))

    os.system("/bin/sh -c \"touch ~/calamares-dummypython\"")
    accumulator = strftime("%Y-%m-%d %H:%M:%S", gmtime()) + "\n"
    accumulator += "Calamares version: " + libcalamares.VERSION_SHORT + "\n"
    accumulator += "This job's name: " + libcalamares.job.pretty_name + "\n"
    accumulator += "This job's path: " + libcalamares.job.working_path
    libcalamares.utils.debug(accumulator)

    accumulator = "*** Job configuration "
    accumulator += str(libcalamares.job.configuration)
    libcalamares.utils.debug(accumulator)

    accumulator = "*** globalstorage test ***"
    accumulator += "lala: "
    accumulator += str(libcalamares.globalstorage.contains("lala")) + "\n"
    accumulator += "foo: "
    accumulator += str(libcalamares.globalstorage.contains("foo")) + "\n"
    accumulator += "count: " + str(libcalamares.globalstorage.count())
    libcalamares.utils.debug(accumulator)

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

    libcalamares.utils.debug("Run dummy python")

    sleep(1)

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
