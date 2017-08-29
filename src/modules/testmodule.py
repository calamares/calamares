#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
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

import argparse
import os
import sys

import yaml

try:
    import libcalamares
except ImportError:
    print("Failed to import libcalamares. Make sure then PYTHONPATH "
          "environment variable includes the dir where libcalamares.so is "
          "installed.")
    print()
    raise


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


def main():
    """


    :return:
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("moduledir",
                        help="Dir containing the Python module.")
    parser.add_argument("globalstorage_yaml", nargs="?",
                        help="A yaml file to initialize GlobalStorage.")
    parser.add_argument("configuration_yaml", nargs="?",
                        help="A yaml file to initialize the Job.")
    parser.add_argument("--lang", "-l", nargs="?", default=None,
                        help="Set translation language.")
    args = parser.parse_args()

    print("Testing module in: " + args.moduledir)

    confpath = os.path.join(args.moduledir, "module.desc")
    with open(confpath) as f:
        doc = yaml.load(f)

    if doc["type"] != "job" or doc["interface"] != "python":
        print("Only Python jobs can be tested.")
        return 1

    # Parameter None creates a new, empty GlobalStorage
    libcalamares.globalstorage = libcalamares.GlobalStorage(None)
    libcalamares.globalstorage.insert("testing", True)
    if args.lang:
        libcalamares.globalstorage.insert("locale", args.lang)
        libcalamares.globalstorage.insert("localeConf", {"LANG": args.lang})

    # if a file for simulating globalStorage contents is provided, load it
    if args.globalstorage_yaml:
        with open(args.globalstorage_yaml) as f:
            gs_doc = yaml.load(f)
        for key, value in gs_doc.items():
            libcalamares.globalstorage.insert(key, value)

    cfg_doc = dict()
    if args.configuration_yaml:
        with open(args.configuration_yaml) as f:
            cfg_doc = yaml.load(f)

    libcalamares.job = Job(args.moduledir, doc, cfg_doc)

    scriptpath = os.path.abspath(args.moduledir)
    sys.path.append(scriptpath)
    import main

    print("Output from module:")
    print(main.run())

    return 0


if __name__ == "__main__":
    sys.exit(main())
