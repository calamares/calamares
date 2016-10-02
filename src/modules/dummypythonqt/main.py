#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
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
from time import gmtime, strftime, sleep

from PythonQt.QtGui import *


def run():
    """ Example Python jobmodule.

    A Python jobmodule is a Python program which imports libcalamares and
    has a function run() as entry point. run() must return None if everything
    went well, or a tuple (str,str) with an error message and description
    if something went wrong.

    :return:
    """
    print("foo bar quux")
    os.system("/bin/sh -c \"touch ~/calamares-dummypythonqt\"")
    accumulator = strftime("%Y-%m-%d %H:%M:%S", gmtime()) + "\n"

    box = QLabel(accumulator)
    box.show()
    print(accumulator)

    # To indicate an error, return a tuple of:
    # (message, detailed-error-message)
    return None
