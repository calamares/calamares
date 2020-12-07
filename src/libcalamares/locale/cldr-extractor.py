#! /usr/bin/env python3
#
#  === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
"""
Python3 script to scrape some data out of ICU CLDR supplemental data.

To use this script, you must have downloaded the CLDR data, e.g.
http://unicode.org/Public/cldr/35.1/, and extracted the zip file.
Run the script from **inside** the common/ durectory that is created
(or fix the hard-coded path).

The script tries to print C++ code that compiles; if there are encoding
problems, it will print some kind of representation of the problematic
lines.

To avoid having to cross-reference multiple XML files, the script
cheats: it reads the comments as well to get names. So it looks for
pairs of lines like this:

   <likelySubtag from="und_BQ" to="pap_Latn_BQ"/>
   <!--{ ?; ?; Caribbean Netherlands } => { Papiamento; Latin; Caribbean Netherlands }-->

It extracts the 2-character country code "BQ" from the sub-tag, and
parses the comment to get a language and country name (instead of looking up
"pap" and "BQ" in other tables). This may be considered a hack.

A large collection of exceptions can be found in the two *_mapper tables,
which massage the CLDR names to Qt enum values.
"""
#
### END USAGE

import sys

# These are languages listed in CLDR that don't match
# the enum-values in QLocale::Language.
language_mapper = {
    "?" : "AnyLanguage",
    "Bangla" : "Bengali",
    "Kalaallisut" : "Greenlandic",
    "Haitian Creole" : "Haitian",
    "Kyrgyz" : "Kirghiz",
    "Norwegian Bokmål" : "NorwegianBokmal",
    "Tokelau" : "TokelauLanguage",
    "Tuvalu" : "TuvaluLanguage",
    }

country_mapper = {
    "Åland Islands" : "AlandIslands",
    "St. Barthélemy" : "SaintBarthelemy",
    "Côte d’Ivoire" : "IvoryCoast",
    "Curaçao" : "CuraSao",
    "Réunion" : "Reunion",
    "São Tomé & Príncipe" : "SaoTomeAndPrincipe",
    "Bosnia & Herzegovina" : "BosniaAndHerzegowina",
    "Czechia" : "CzechRepublic",
    "St. Pierre & Miquelon" : "SaintPierreAndMiquelon",
    "Vatican City" : "VaticanCityState",
    "South Georgia & South Sandwich Islands" : "SouthGeorgiaAndTheSouthSandwichIslands",
    "Timor-Leste" : "EastTimor",
    "Wallis & Futuna" : "WallisAndFutunaIslands",
    "Myanmar (Burma)" : "Myanmar",
    "Svalbard & Jan Mayen" : "SvalbardAndJanMayenIslands",
    "St. Martin" : "SaintMartin",
    "North Macedonia" : "Macedonia",
    "Hong Kong SAR China" : "HongKong",
    "Macao SAR China" : "Macau",
    "Eurozone" : "AnyCountry",  # Not likely for GeoIP
    "Caribbean Netherlands" : "Bonaire",  # Bonaire, Saba, St.Eustatius
    }

class CountryData:
    def __init__(self, country_code, language_name, country_name):
        """
        Takes a 2-letter country name, and enum names from
        QLocale::Language and QLocale::Country. An empty
        @p country code is acceptable, for the terminating
        entry in the data array (and yields a 0,0 code).
        """
        if country_code:
            assert len(country_code) == 2
            self.country_code = country_code
            self.language_enum = language_name
            self.country_enum = country_name
        else:
            self.country_code = ""
            self.language_enum = "AnyLanguage"
            self.country_enum = "AnyCountry"

    def __str__(self):
        if self.country_code:
            char0 = "'{!s}'".format(self.country_code[0])
            char1 = "'{!s}'".format(self.country_code[1])
        else:
            char0 = "0"
            char1 = "0"

        return "{!s} QLocale::Language::{!s}, QLocale::Country::{!s}, {!s}, {!s} {!s},".format(
            "{",
            self.language_enum,
            self.country_enum,
            char0,
            char1,
            "}")

    # Must match type name below
    cpp_classname = "CountryData"

    # Must match the output format of __str__ above
    cpp_declaration = """
struct CountryData
{
    QLocale::Language l;
    QLocale::Country c;
    char cc1;
    char cc2;
};
"""


def extricate_subtags(l1, l2):
    """
    Given two lines @p l1 and @p l2 which are the <likelySubtag> element-line
    and the comment-line underneath it, return a CountryData for them,
    or None if the two lines are not relevant (e.g. not the right subtag from,
    or 3-letter country codes.
    """
    if 'from="und_' not in l1:
        return
    if '{ ?; ?;' not in l2:
        return

    # This is extremely crude "parsing" which chops up the string
    # by delimiter and then extracts some substring.
    l1_parts = l1.split("und_")
    l2_parts = l2.split(";")

    l1_first_quote = l1_parts[1].find('"')
    l1_code = l1_parts[1][:l1_first_quote]
    if len(l1_code) != 2:
        return

    l2_brace = l2_parts[2].find("{")
    l2_language = l2_parts[2][l2_brace+1:].strip()
    l2_brace = l2_parts[2].find("}")
    l2_country = l2_parts[2][:l2_brace-1].strip()

    # Handle mapped cases
    l2_language = language_mapper.get(l2_language, l2_language)
    l2_language = l2_language.replace(" ", "")

    # Handle mapped cases and then do a bunch of standard replacements.
    l2_country = country_mapper.get(l2_country, l2_country)
    l2_country = l2_country.replace(" ", "").replace("-", "").replace(".","").replace("&","And")

    return CountryData(l1_code, l2_language, l2_country)


def read_subtags_file():
    """
    Returns a list of CountryData objects from the likelySubtags file.
    """
    data = []

    with open("supplemental/likelySubtags.xml", "rt", encoding="UTF-8") as f:
        l1 = "a line"
        while l1:
            l1 = f.readline()
            if '<likelySubtag from="und_' not in l1:
                continue
            l2 = f.readline()

            if l1:
                assert "likelySubtag" in l1, l1;
                assert "<!--" in l2, l2;

                data.append(extricate_subtags(l1, l2))

    data.append(CountryData("", None, None))
    return [c for c in data if c is not None]


cpp_header_comment = """/*   GENERATED FILE DO NOT EDIT
*
*  === This file is part of Calamares - <https://calamares.io> ===
*
* SPDX-FileCopyrightText: 1991-2019 Unicode, Inc.
* SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
* SPDX-License-Identifier: CC0
*
* This file is derived from CLDR data from Unicode, Inc. Applicable terms
* are listed at http://unicode.org/copyright.html , of which the most
* important are:
*
* A. Unicode Copyright
*    1. Copyright © 1991-2019 Unicode, Inc. All rights reserved.
* B. Definitions
*    Unicode Data Files ("DATA FILES") include all data files under the directories:
*    https://www.unicode.org/Public/
* C. Terms of Use
*    1. Certain documents and files on this website contain a legend indicating
*       that "Modification is permitted." Any person is hereby authorized,
*       without fee, to modify such documents and files to create derivative
*       works conforming to the Unicode® Standard, subject to Terms and
*       Conditions herein.
*    2. Any person is hereby authorized, without fee, to view, use, reproduce,
*       and distribute all documents and files, subject to the Terms and
*       Conditions herein.
*/

// BEGIN Generated from CLDR data
// *INDENT-OFF*
// clang-format off

"""

cpp_footer_comment = """
// END Generated from CLDR data
"""


def make_identifier(classname):
    """
    Given a class name (e.g. CountryData) return an identifer
    for the data-table for that class.
    """
    identifier = [ classname[0].lower() ]
    for c in classname[1:]:
        if c.isupper():
            identifier.extend(["_", c.lower()])
        else:
            identifier.append(c)

    return "".join(identifier)


def export_class(cls, data):
    """
    Given a @p cls and a list of @p data objects from that class,
    print (to stdout) a C++ file for that data.
    """
    identifier = make_identifier(cls.cpp_classname)

    with open("{!s}_p.cpp".format(cls.cpp_classname), "wt", encoding="UTF-8") as f:
        f.write(cpp_header_comment)
        f.write(cls.cpp_declaration)
        f.write("\nstatic constexpr int const {!s}_size = {!s};\n".format(
            identifier,
            len(data)))
        f.write("\nstatic const {!s} {!s}_table[] = {!s}\n".format(
            cls.cpp_classname,
            identifier,
            "{"))
        for d in data:
            f.write(str(d))
            f.write("\n")
        f.write("};\n\n");
        f.write("static_assert( (sizeof({!s}_table) / sizeof({!s})) == {!s}_size, \"Table size mismatch for {!s}\" );\n\n".format(
            identifier,
            cls.cpp_classname,
            identifier,
            cls.cpp_classname))
        f.write(cpp_footer_comment)


if __name__ == "__main__":
    export_class(CountryData, read_subtags_file())
