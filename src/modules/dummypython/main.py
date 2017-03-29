#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
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
import os
from time import gmtime, strftime, sleep


def run():
    """
    Example Python jobmodule.

    A Python jobmodule is a Python program which imports libcalamares and
    has a function run() as entry point. run() must return None if everything
    went well, or a tuple (str,str) with an error message and description
    if something went wrong.

    :return:
    """
    os.system("/bin/sh -c \"touch ~/calamares-dummypython\"")
    accumulator = strftime("%Y-%m-%d %H:%M:%S", gmtime()) + "\n"
    accumulator += "Calamares version: " + libcalamares.VERSION_SHORT + "\n"
    accumulator += "This job's name: " + libcalamares.job.pretty_name + "\n"
    accumulator += "This job's path: " + libcalamares.job.working_path + "\n"
    accumulator += str(libcalamares.job.configuration)
    accumulator += "   *** globalstorage test ***\n"
    accumulator += "lala: "
    accumulator += str(libcalamares.globalstorage.contains("lala")) + "\n"
    accumulator += "foo: "
    accumulator += str(libcalamares.globalstorage.contains("foo")) + "\n"
    accumulator += "count: " + str(libcalamares.globalstorage.count()) + "\n"
    libcalamares.globalstorage.insert("item2", "value2")
    libcalamares.globalstorage.insert("item3", 3)
    accumulator += "keys: {}\n".format(str(libcalamares.globalstorage.keys()))
    accumulator += "remove: {}\n".format(
       str(libcalamares.globalstorage.remove("item2")))
    accumulator += "values: {} {} {}\n".format(
        str(libcalamares.globalstorage.value("foo")),
        str(libcalamares.globalstorage.value("item2")),
        str(libcalamares.globalstorage.value("item3")))

    libcalamares.job.setprogress(0.1)
    libcalamares.utils.debug(accumulator)

    sleep(3)
    # To indicate an error, return a tuple of:
    # (message, detailed-error-message)
    return None
