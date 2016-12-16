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
import PythonQt.calamares as calamares

# Set up translations.
# You may skip this if your Calamares module has no user visible strings.
# DO NOT install _ into the builtin namespace because each module loads
# its own catalog.
# DO use the gettext class-based API and manually alias _ as described in:
# https://docs.python.org/3.5/library/gettext.html#localizing-your-module
import gettext
import inspect
import os
_filename = inspect.getframeinfo(inspect.currentframe()).filename
_path = os.path.dirname(os.path.abspath(_filename))

_ = gettext.gettext

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
class DummyPythonQtViewStep:
    def __init__(self):
        self.main_widget = QFrame()

        self.main_widget.setLayout(QVBoxLayout())

        label = QLabel()
        self.main_widget.layout().addWidget(label)

        accumulator = "\nCalamares+PythonQt running embedded Python " +\
                      platform.python_version()
        label.text = accumulator

        btn = QPushButton()
        btn.setText(_("Click me!"))
        self.main_widget.layout().addWidget(btn)
        btn.connect("clicked(bool)", self.on_btn_clicked)

    def on_btn_clicked(self):
        self.main_widget.layout().addWidget(QLabel(_("A new QLabel.")))

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

    def jobs(self):
        return [DummyPQJob("Dummy PythonQt job reporting for duty")]

    def widget(self):
        return self.main_widget

    def retranslate(self, locale_name):
        calamares.utils.debug("PythonQt retranslation event "
                              "for locale name: {}".format(locale_name))

        try:
            global _
            _t = gettext.translation('dummypythonqt',
                                     localedir=os.path.join(_path, 'lang'),
                                     languages=[locale_name])
            _ = _t.gettext
        except OSError as e:
            calamares.utils.debug(e)
            pass


class DummyPQJob:
    def __init__(self, my_msg):
        self.my_msg = my_msg

    def pretty_name(self):
        return _("The Dummy PythonQt Job")

    def pretty_description(self):
        return _("This is the Dummy PythonQt Job. "
                 "The dummy job says: {}").format(self.my_msg)

    def pretty_status_message(self):
        return _("A status message for Dummy PythonQt Job.")

    def exec(self):
        rmp = calamares.global_storage['rootMountPoint']
        os.system("touch {}/calamares_dpqt_was_here".format(rmp))
        calamares.utils.debug("the dummy job says {}".format(self.my_msg))
        return {'ok': True}
