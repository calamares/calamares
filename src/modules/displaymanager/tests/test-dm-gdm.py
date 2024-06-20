#   SPDX-FileCopyrightText: no
#   SPDX-License-Identifier: CC0-1.0
#
# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)

# Module prep-work
from src.modules.displaymanager import main
default_desktop_environment = main.DesktopEnvironment("startplasma-x11", "kde-plasma.desktop")

import os
import tempfile
with tempfile.TemporaryDirectory(prefix="calamares-gdm") as tempdir:
    os.makedirs(tempdir + "/usr/bin")
    os.makedirs(tempdir + "/etc/gdm3")
    with open(tempdir + "/usr/bin/gdm3", "w") as f:
        f.write("#! /bin/sh\n:\n")
    # Specific DM test
    d = main.DMgdm(tempdir)
    assert(d.have_dm())
    d.set_autologin("d", True, default_desktop_environment)
    # .. and again (this time checks load/save)
    d.set_autologin("d", True, default_desktop_environment)
    d.set_autologin("d", True, default_desktop_environment)
