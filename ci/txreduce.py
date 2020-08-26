#! /usr/bin/env python3
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
# Reduce a translation file -- generally, a Timezone translation -- by
# dropping untranslated strings. An untranslated string is one that
# has an empty translation **and** is marked unfinished.
#
# This is mostly useful to cut down the size of the source file:
# far and away most of the zones are not translated, and it's just a
# handful of places that get special treatment.

from xml.dom.minidom import parse
import sys

valid = True
dom = parse(sys.argv[1])
for n in dom.getElementsByTagName("translation"):
    attrs = n.attributes.keys()

    drop = True
    if "type" not in attrs:
        drop = False
    elif "type" in attrs and n.attributes["type"].value != "unfinished":
        # In the samples I've seen, only "unfinished" is a valid type;
        # once something has been translated, the attribute vanishes (see
        # the if branch, above).
        print("WARNING ''{!s}'' unknown type".format(n.attributes["type"].value))
        drop = False
        valid = False
    else:
        t = n.firstChild
        if t is None:
            # Unfinished and empty
            drop = True
        else:
            drop = bool(t.data)
    if drop:
        message = n.parentNode
        message.parentNode.removeChild(message)
        message.unlink()

if valid:
    for line in dom.toxml().split("\n"):
        if line.strip():
            print(line)
