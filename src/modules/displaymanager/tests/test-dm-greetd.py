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
os.makedirs("/tmp/etc/greetd/", exist_ok=True)
try:
    os.remove("/tmp/etc/greetd/config.toml")
except FileNotFoundError as e:
    pass

# Specific DM test
d = main.DMgreetd("/tmp")
d.set_autologin("d", True, default_desktop_environment)
# .. and again (this time checks load/save)
d.set_autologin("d", True, default_desktop_environment)
d.set_autologin("d", True, default_desktop_environment)
