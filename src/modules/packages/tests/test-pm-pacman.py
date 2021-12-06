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
    def __init__(self, filename):
        self.configuration = libcalamares.utils.load_yaml(filename) if filename is not None else dict()

import sys
if len(sys.argv) > 4:
    filename = sys.argv[1]
    retry = int(sys.argv[2])
    timeout = bool(int(sys.argv[3]))
    needed = bool(int(sys.argv[4]))
else:
    filename = None
    retry = 0
    timeout = False
    needed = False

libcalamares.utils.warning("Expecting {!s} retry={!s} timeout={!s} needed={!s}".format(filename, retry, timeout, needed))

# Specific PM test
libcalamares.job = Job(filename)
p = main.PMPacman()
assert p.pacman_num_retries == retry, "{!r} vs {!r}".format(p.pacman_num_retries, retry)
assert p.pacman_disable_timeout == timeout, "{!r} vs {!r}".format(p.pacman_disable_timeout, timeout)
assert p.pacman_needed_only == needed, "{!r} vs {!r}".format(p.pacman_needed_only, needed)
