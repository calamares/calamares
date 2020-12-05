#! /usr/bin/env python3
#
#  === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
"""
Python3 script to scrape x keyboard layout file and produce translations.

To use this script, you must have a base.lst in a standard location,
/usr/local/share/X11/xkb/rules/base.lst (this is usual on FreeBSD).

Prints out a few tables of keyboard model, layout, variant names for
use in translations.
"""

def scrape_file(file, modelsset, layoutsset, variantsset):
    import re
    # These RE's match what is in keyboardglobal.cpp
    model_re = re.compile("^\\s+(\\S+)\\s+(\\w.*)\n$")
    layout_re = re.compile("^\\s+(\\S+)\\s+(\\w.*)\n$")
    variant_re = re.compile("^\\s+(\\S+)\\s+(\\S+): (\\w.*)\n$")

    MODEL, LAYOUT, VARIANT = range(3)
    state = None
    for line in file.readlines():
        # Handle changes in section
        if line.startswith("! model"):
            state = MODEL
            continue
        elif line.startswith("! layout"):
            state = LAYOUT
            continue
        elif line.startswith("! variant"):
            state = VARIANT
            continue
        elif not line.strip():
            state = None
        # Unchanged from last blank
        if state is None:
            continue

        if state == MODEL:
            m = model_re.match(line)
            name = m.groups()[1]
            modelsset.add(name)
        if state == LAYOUT:
            l = layout_re.match(line)
            name = l.groups()[1]
            layoutsset.add(name)
        if state == VARIANT:
            v = variant_re.match(line)
            name = v.groups()[2]
            variantsset.add(name)


def write_set(file, label, set):
    file.write("/* This returns a reference to local, which is a terrible idea.\n * Good thing it's not meant to be compiled.\n */\n")
    # Note {{ is an escaped { for Python string formatting
    file.write("class {!s} : public QObject {{\nQ_OBJECT\npublic:\n".format(label))
    file.write("\tconst QStringList& table()\n\t{\n\treturn QStringList {\n")
    for x in sorted(set):
        file.write("""\t\ttr("{!s}", "{!s}"),\n""".format(x, label))
    file.write("\t\tQString()\n\t};\n}\n}\n\n")

cpp_header_comment = """/*   GENERATED FILE DO NOT EDIT
*
*  === This file is part of Calamares - <https://calamares.io> ===
*
* SPDX-FileCopyrightText: no
* SPDX-License-Identifier: CC0-1.0
*
* This file is derived from base.lst in the Xorg distribution
*
*/

/** THIS FILE EXISTS ONLY FOR TRANSLATIONS PURPOSES **/

// *INDENT-OFF*
// clang-format off
"""

if __name__ == "__main__":
    models=set()
    layouts=set()
    variants=set()
    variants.add( "Default" )
    with open("/usr/local/share/X11/xkb/rules/base.lst", "r") as f:
        scrape_file(f, models, layouts, variants)
    with open("KeyboardData_p.cxxtr", "w") as f:
        f.write(cpp_header_comment)
        write_set(f, "kb_models", models)
        write_set(f, "kb_layouts", layouts)
        write_set(f, "kb_variants", variants)

