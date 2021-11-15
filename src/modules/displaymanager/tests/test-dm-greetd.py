# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)
# Module prep-work
import os
os.makedirs("/tmp/etc/greetd/", exist_ok=True)
try:
    os.remove("/tmp/etc/greetd/config.toml")
except FileNotFoundError as e:
    pass
# Module test
from src.modules.displaymanager import main
d = main.DMgreetd("/tmp")
d.set_autologin("d", True, "kde")
# .. and again (this time checks load/save)
d.set_autologin("d", True, "kde")
d.set_autologin("d", True, "kde")
