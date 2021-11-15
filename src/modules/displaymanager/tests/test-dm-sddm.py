# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)
# Module prep-work
# Module test
from src.modules.displaymanager import main
d = main.DMsddm("/tmp")
d.set_autologin("d", True, "kde")
# .. and again (this time checks load/save)
d.set_autologin("d", True, "kde")
d.set_autologin("d", True, "kde")
