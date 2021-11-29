#   SPDX-FileCopyrightText: no
#   SPDX-License-Identifier: CC0-1.0
#
# Calamares Boilerplate
import libcalamares
libcalamares.globalstorage = libcalamares.GlobalStorage(None)
libcalamares.globalstorage.insert("testing", True)

# Module prep-work
from src.modules.packages import main

# .. we don't have a job in this test, so fake one
class Job(object):
    def __init__(self):
        self.configuration = libcalamares.utils.load_yaml("pm-pacman.yaml")
libcalamares.job = Job()

# Specific PM test
p = main.PMPacman()
assert p.pacman_num_retries == 0
assert p.pacman_disable_timeout == False
assert p.pacman_needed_only == False
