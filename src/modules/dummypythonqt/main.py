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

import platform

from PythonQt.QtGui import *
from PythonQt.calamares import *

# Example Python ViewModule.
# A Python ViewModule is a Python program which defines a ViewStep class.
# This class must be marked with the @calamares_module decorator. A
# ViewModule may define other classes, but only one may be decorated with
# @calamares_module. Such a class must conform to the Calamares ViewStep
# interface and functions as the entry point of the module.
# A ViewStep manages one or more "wizard pages" through methods like
# back/next, and reports its status through isNextEnabled/isBackEnabled/
# isAtBeginning/isAtEnd. The whole UI, including all the pages, must be
# exposed as a single QWidget, returned by the widget function.
@calamares_module
class DummyPythonQtViewStep():
    def __init__(self):
        self.main_widget = QLabel()

        accumulator = "\nCalamares+PythonQt running embedded Python " +\
                      platform.python_version()
        self.main_widget.text = accumulator

    def prettyName(self):
        return "Dummy PythonQt ViewStep"

    def isNextEnabled(self):
        return True

    def isBackEnabled(self):
        return True

    def isAtBeginning(self):
        return True

    def isAtEnd(self):
        return True

    def widget(self):
        return self.main_widget
