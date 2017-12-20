#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
"""
Testing tool to run a single Python module; optionally a global configuration
and module configuration can be read from YAML files.
"""
argumentepilog = """
moduledir may be a module name (e.g. "welcome") or a full path to the
    module (e.g. "src/modules/welcome"). In the former case, an attempt
    is made to find the module in several sensible places.
globalstorage_yaml may be given as a full path to a YAML file containing
    the global configuration, or as "" or "-" which will leave the
    global storage empty.
configuration_yaml may be given as a full path to a YAML file with the
    module configuration, as "" or "-" to leave the configuration
    empty, or as "+" to load the standard configuration from the
    module-directory (e.g. welcome.conf if the welcome module is given).

The simplest invocation to test a module, with its default configuration, is
to call this program as follows (for, e.g., the welcome module):

    testmodule.py welcome - +"""

import argparse
import os
import sys

import yaml

calamaresimporterror = ("Can not import libcalamares. Ensure the PYTHONPATH "
    "environment variable includes the dir where libcalamares.so is "
    "installed.")
try:
    import libcalamares
except ImportError:
    print(calamaresimporterror)
    print()
    libcalamares = None


class Job:
    """

    :param working_path:
    :param doc:
    :param cfg_doc:
    """

    def __init__(self, working_path, doc, cfg_doc):
        self.module_name = doc["name"]
        self.pretty_name = "Testing job " + doc["name"]
        self.working_path = working_path
        self.configuration = cfg_doc

    def setprogress(self, progress):
        """

        :param progress:
        """
        print("Job set progress to {}%.".format(progress * 100))


def test_module(moduledir, globalconfigfilename, moduleconfigfilename, lang):
    print("Testing module in: " + moduledir)

    confpath = os.path.join(moduledir, "module.desc")
    with open(confpath) as f:
        doc = yaml.load(f)

    if doc["type"] != "job" or doc["interface"] != "python":
        print("Only Python jobs can be tested.")
        return 1

    # Parameter None creates a new, empty GlobalStorage
    libcalamares.globalstorage = libcalamares.GlobalStorage(None)
    libcalamares.globalstorage.insert("testing", True)
    if lang:
        libcalamares.globalstorage.insert("locale", lang)
        libcalamares.globalstorage.insert("localeConf", {"LANG": lang})

    # if a file for simulating globalStorage contents is provided, load it
    if globalconfigfilename:
        with open(globalconfigfilename) as f:
            gs_doc = yaml.load(f)
        for key, value in gs_doc.items():
            libcalamares.globalstorage.insert(key, value)
        print("Global configuration '" + globalconfigfilename + "' loaded.")
    else:
        print("No global configuration loaded.")

    cfg_doc = dict()
    if moduleconfigfilename:
        with open(moduleconfigfilename) as f:
            cfg_doc = yaml.load(f)
            print("Local configuration '" + moduleconfigfilename + "' loaded.")
    else:
        print("No module configuration loaded.")

    libcalamares.job = Job(moduledir, doc, cfg_doc)

    scriptpath = os.path.abspath(moduledir)
    sys.path.append(scriptpath)
    import main  # Assumed to import main from module itself

    print("Output from module:")
    print(main.run())

    return 0


def munge_filename(filename, module=None):
    """
    Maps files "" (empty) and "-" (just a dash) to None,
    to simplify processing elsewhere.
    """
    if not filename or filename == "-":
        return None
    if filename == "+" and module is not None:
        d, name = os.path.split(module)
        if d and not name:
            # Ended in a /
            d, name = os.path.split(module)
        if name:
            return os.path.join(module, name + ".conf")

    return filename


def find_module(modulename):
    if "/" in modulename:
        return modulename
    else:
        for prefix in ("src/modules", "build/src/modules", "../src/modules"):
            mp = os.path.join( prefix, modulename )
            if os.path.exists( mp ):
                return mp
    # Not found? Bail out elsewhere
    return modulename

def main():
    parser = argparse.ArgumentParser(description=globals()["__doc__"], epilog=argumentepilog, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("moduledir",
                        help="Dir containing the Python module.")
    parser.add_argument("globalstorage_yaml", nargs="?",
                        help="A yaml file to initialize GlobalStorage.")
    parser.add_argument("configuration_yaml", nargs="?",
                        help="A yaml file to initialize the Job.")
    parser.add_argument("--lang", "-l", nargs="?", default=None,
                        help="Set translation language.")
    args = parser.parse_args()

    # If we get here, it wasn't a --help invocation, so complain
    # if libcalamares wasn't found.
    if not libcalamares:
        parser.error(calamaresimporterror)

    moduledir = find_module(args.moduledir)
    return test_module(moduledir,
                       munge_filename(args.globalstorage_yaml),
                       munge_filename(args.configuration_yaml, moduledir),
                       args.lang)


if __name__ == "__main__":
    sys.exit(main())
