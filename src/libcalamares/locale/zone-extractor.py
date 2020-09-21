#! /usr/bin/env python3
#
#  === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
"""
Python3 script to scrape some data out of zoneinfo/zone.tab.

To use this script, you must have a zone.tab in a standard location,
/usr/share/zoneinfo/zone.tab (this is usual on FreeBSD and Linux).

Prints out a few tables of zone names for use in translations.
"""

def scrape_file(file, regionset, zoneset):
    for line in file.readlines():
        if line.startswith("#"):
            continue
        parts = line.split("\t")
        if len(parts) < 3:
            continue

        zoneid = parts[2]
        if not "/" in zoneid:
            continue

        region, zone = zoneid.split("/", 1)

        zone = zone.strip().replace("_", " ")

        regionset.add(region)
        assert(zone not in zoneset)
        zoneset.add(zone)

def write_set(file, label, set):
    file.write("/* This returns a reference to local, which is a terrible idea.\n * Good thing it's not meant to be compiled.\n */\n")
    # Note {{ is an escaped { for Python string formatting
    file.write("static const QStringList& {!s}_table()\n{{\n\treturn QStringList {{\n".format(label))
    for x in sorted(set):
        file.write("""\t\tQObject::tr("{!s}", "{!s}"),\n""".format(x, label))
    file.write("\t\tQString()\n\t};\n}\n\n")

cpp_header_comment = """/*   GENERATED FILE DO NOT EDIT
*
*  === This file is part of Calamares - <https://calamares.io> ===
*
* SPDX-FileCopyrightText: 2009 Arthur David Olson
* SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
* SPDX-License-Identifier: CC0-1.0
*
* This file is derived from zone.tab, which has its own copyright statement:
*
* This file is in the public domain, so clarified as of
* 2009-05-17 by Arthur David Olson.
*
* From Paul Eggert (2018-06-27):
* This file is intended as a backward-compatibility aid for older programs.
* New programs should use zone1970.tab.  This file is like zone1970.tab (see
* zone1970.tab's comments), but with the following additional restrictions:
*
* 1.  This file contains only ASCII characters.
* 2.  The first data column contains exactly one country code.
*
*/

/** THIS FILE EXISTS ONLY FOR TRANSLATIONS PURPOSES **/

// *INDENT-OFF*
// clang-format off
"""

if __name__ == "__main__":
    regions=set()
    zones=set()
    with open("/usr/share/zoneinfo/zone.tab", "r") as f:
        scrape_file(f, regions, zones)
    with open("ZoneData_p.cpp", "w") as f:
        f.write(cpp_header_comment)
        write_set(f, "tz_regions", regions)
        write_set(f, "tz_names", zones)

