#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2016-2017, Teo Mrnjavac <teo@kde.org>
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

import platform

from PythonQt.QtGui import *
import PythonQt.calamares as calamares

# WARNING: the Calamares PythonQt API is considered EXPERIMENTAL as of
# Calamares 2.5. It comes with no promise or commitment to API stability.


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
# One UI module ==> one ViewStep.
# This class must be marked with the @calamares_module decorator. A
# ViewModule may define other classes, but only one may be decorated with
# @calamares_module. Such a class must conform to the Calamares ViewStep
# interface and functions as the entry point of the module.
# A ViewStep manages one or more "wizard pages" through methods like
# back/next, and reports its status through isNextEnabled/isBackEnabled/
# isAtBeginning/isAtEnd. The whole UI, including all the pages, must be
# exposed as a single QWidget, returned by the widget function.
#
# For convenience, both C++ and PythonQt ViewSteps are considered to be
# implementations of ViewStep.h. Additionally, the Calamares PythonQt API
# allows Python developers to keep their identifiers more Pythonic on the
# Python side. Thus, all of the following are considered valid method
# identifiers in a ViewStep implementation: isNextEnabled, isnextenabled,
# is_next_enabled.


@calamares_module
class DummyPythonQtViewStep:
    def __init__(self):
        # Importing PythonQt.QtGui provides access to most Qt widget classes.
        self.main_widget = QFrame()

        self.main_widget.setLayout(QVBoxLayout())

        label = QLabel()
        self.main_widget.layout().addWidget(label)

        accumulator = "\nCalamares+PythonQt running embedded Python " +\
                      platform.python_version()
        label.text = accumulator

        btn = QPushButton()

        # Python strings can be used wherever a method wants a QString. Python
        # gettext translations can be used seamlessly as well.
        btn.setText(_("Click me!"))
        self.main_widget.layout().addWidget(btn)

        # The syntax for signal-slot connections is very simple, though
        # slightly different from the C++ equivalent. There are no SIGNAL and
        # SLOT macros, and a signal can be connected to any Python method
        # (without a special "slot" designation).
        btn.connect("clicked(bool)", self.on_btn_clicked)

    def on_btn_clicked(self):
        self.main_widget.layout().addWidget(QLabel(_("A new QLabel.")))

    def prettyName(self):
        return _("Dummy PythonQt ViewStep")

    def isNextEnabled(self):
        return True  # The "Next" button should be clickable

    def isBackEnabled(self):
        return True  # The "Back" button should be clickable

    def isAtBeginning(self):
        # True means the currently shown UI page is the first page of this
        # module, thus a "Back" button click will not be handled by this
        # module and will cause a skip to the previous ViewStep instead
        # (if any). False means that the present ViewStep provides other UI
        # pages placed logically "before" the current one, thus a "Back" button
        # click will be handled by this module instead of skipping to another
        # ViewStep. A module (ViewStep) with only one page will always return
        # True here.
        return True

    def isAtEnd(self):
        # True means the currently shown UI page is the last page of this
        # module, thus a "Next" button click will not be handled by this
        # module and will cause a skip to the next ViewStep instead (if any).
        # False means that the present ViewStep provides other UI pages placed
        # logically "after" the current one, thus a "Next" button click will
        # be handled by this module instead of skipping to another ViewStep.
        # A module (ViewStep) with only one page will always return True here.
        return True

    def jobs(self):
        # Returns a list of objects that implement Calamares::Job.
        return [DummyPQJob("Dummy PythonQt job reporting for duty")]

    def widget(self):
        # Returns the base QWidget of this module's UI.
        return self.main_widget

    def retranslate(self, locale_name):
        # This is where it gets slightly weird. In most desktop applications we
        # shouldn't need this kind of mechanism, because we could assume that
        # the operating environment is configured to use a certain language.
        # Usually the user would change the system-wide language in a settings
        # UI, restart the application, done.
        # Alas, Calamares runs on an unconfigured live system, and one of the
        # core features of Calamares is to allow the user to pick a language.
        # Unfortunately, strings in the UI do not automatically react to a
        # runtime language change. To get UI strings in a new language, all
        # user-visible strings must be retranslated (by calling tr() in C++ or
        # _() in Python) and reapplied on the relevant widgets.
        # When the user picks a new UI translation language, Qt raises a QEvent
        # of type LanguageChange, which propagates through the QObject
        # hierarchy. By catching and reacting to this event, we can show
        # user-visible strings in the new language at the right time.
        # The C++ side of the Calamares PythonQt API catches the LanguageChange
        # event and calls the present method. It is then up to the module
        # developer to add here all the needed code to load the module's
        # translation catalog for the new language (which is separate from the
        # main Calamares strings catalog) and reapply any user-visible strings.
        calamares.utils.debug("PythonQt retranslation event "
                              "for locale name: {}".format(locale_name))

        # First we load the catalog file for the new language...
        try:
            global _
            _t = gettext.translation('dummypythonqt',
                                     localedir=os.path.join(_path, 'lang'),
                                     languages=[locale_name])
            _ = _t.gettext
        except OSError as e:
            calamares.utils.debug(e)
            pass

        # ... and then we can call setText(_("foo")) and similar methods on
        # the relevant widgets here to reapply the strings.

# An example Job class. Implements Calamares::Job. For method identifiers, the
# same rules apply as for ViewStep. No decorators are necessary here, because
# only the ViewStep implementation is the unique entry point, and a module can
# have any number of jobs.


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
        # As an example, we touch a file in the target root filesystem.
        rmp = calamares.global_storage['rootMountPoint']
        os.system("touch {}/calamares_dpqt_was_here".format(rmp))
        calamares.utils.debug("the dummy job says {}".format(self.my_msg))
        return {'ok': True}
