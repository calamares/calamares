#   SPDX-FileCopyrightText: no
#   SPDX-License-Identifier: CC0-1.0
#
# Stubs for part of the Python API from libcalamares
# (although the **actual** API is presented through
# Boost::Python, not as a bare C-extension) so that
# pylint doesn't complain about libcalamares internals.

def debug(_): pass

def warning(_): pass

def error(_): pass

def gettext_path(): pass

def gettext_languages(): pass

def target_env_call(_): return 0

def check_target_env_call(_): pass

def target_env_process_output(cmd, *args): return 0

def host_env_process_output(cmd, *args): return 0

def mount(device, mountpoint, fstype, options): return 0
