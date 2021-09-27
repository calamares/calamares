#   SPDX-FileCopyrightText: no
#   SPDX-License-Identifier: CC0-1.0
#
# Stubs for part of the Python API from libcalamares
# (although the **actual** API is presented through
# Boost::Python, not as a bare C-extension) so that
# pylint doesn't complain about libcalamares internals.

def count(): return 1

def keys(): return []

def contains(_): return True

def value(key):
    if key in ("branding",):
        return dict()
    if key in ("partitions",):
        return list()
    return ""

def insert(key, value): pass

def remove(_): pass
