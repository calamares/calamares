#! /usr/bin/env python3
#
#   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
# Uses the Transifex API to get a list of enabled languages,
# and outputs CMake settings for inclusion into CMakeLists.txt.
#
# This is a Python3 script.
#
# Run it with a -v command-line option to get extra output on
# actual translation percentages.
import sys
import os
import argparse

class TXError(Exception):
    pass


class TransifexGetter(object):
    """
    Get language data from Transifex.

    The object does all the work in __init__, after that
    the only relevant data is .languages, a dictionary
    of language data.
    """
    def __init__(self):
        token = self.get_tx_credentials()
        if token is None:
            raise TXError("Could not get Transifex API token")

        import requests
        r = requests.get("https://api.transifex.com/organizations/calamares/projects/calamares/resources/calamares/", auth=("api", token))
        if r.status_code != 200:
            raise TXError("Could not get Transifex data from API")

        j = r.json()
        self.languages = j["stats"]


    def get_tx_credentials(self):
        """
        Gets the API token out of the user's .transifexrc (this is supposed
        to be secure).
        """
        import configparser
        import os
        txconfig_name = os.path.expanduser("~/.transifexrc")
        try:
            with open(txconfig_name, "r") as f:
                parser = configparser.ConfigParser()
                parser.read_file(f)

                return parser.get("https://www.transifex.com", "password")
        except IOError as e:
            return None


class BogusGetter(object):
    """
    Fake language data.

    This object pretends to retrieve data, and returns fixed language lists and percentages,
    for testing purposes without hitting Transifex servers all the time.
    """
    def __init__(self):
        self.languages = dict()
        for lang, completion in ( ("sq", 100), ("ar", 44), ("as", 28), ("de", 15), ("da", 4), ("ts", 82) ):
            self.languages[lang] = dict(translated=dict(stringcount=686, percentage=(completion/100.0)))


class PrintOutputter(object):
    """
    Output via print-statements.
    """
    def __init__(self):
        pass

    def print(self, s):
        print(s)

    def __enter__(self):
        return self

    def __exit__(self, e, v, tb):
        pass


class EditingOutputter(object):
    """
    Edit CMakeLists in-place.
    """
    def __init__(self):
        with open("CMakeLists.txt", "r") as f:
            lines = f.readlines()

        mark = None
        mark_text = None
        for l in lines:
            # Note that we didn't strip the lines, so need the \n here
            if l.startswith("# Total ") and l.endswith(" languages\n"):
                mark = lines.index(l)
                mark_text = l
                break
        if mark is None:
            raise TXError("No CMakeLists.txt lines for TX stats found")
        self.pre_lines = lines[:mark]

        nextmark = mark + 1
        for l in lines[mark+1:]:
            nextmark += 1
            if l.startswith(mark_text):
                break
        if nextmark > mark + 100 or nextmark > len(lines) - 4:
            # Try to catch runaway nextmarks: we know there should
            # be four set-lines, which are unlikely to be 3 lines each;
            # similarly the CMakeLists.txt is supposed to end with
            # some boilerplate.
            #
            # However, gersemi will reformat to one-language-per-line,
            # so we can get really long sections, that's why we use 100 as a limit.
            raise TXError("Could not find end of TX settings in CMakeLists.txt")
        self.post_lines = lines[nextmark:]

        self.mid_lines = []
        print("# Editing CMakeLists.txt in-place")

    def print(self, s):
        # Add the implicit \n from print()
        self.mid_lines.append(s + "\n")
        if s.startswith("#"):
            print(s)

    def __enter__(self):
        return self

    def __exit__(self, e, v, tb):
        if e is None:
            with open("CMakeLists.txt", "w") as f:
                f.write("".join(self.pre_lines + self.mid_lines + self.post_lines))
            print("# CMakeLists.txt updated")


def output_langs(all_langs, outputter, label, filterfunc):
    """
    Output (via print) all of the languages in @p all_langs
    that satisfy the translation-percentage filter @p filterfunc.
    Prints a CMake set() command with the @p label as part
    of the variable name.

    Performs line-wrapping.
    """
    these_langs = [l for s, l in all_langs if filterfunc(s)]
    out = " ".join(["set( _tx_%s" % label, " ".join(sorted(these_langs)), ")"])
    width = 68
    prefix = ""

    while len(out) > width - len(prefix):
        chunk = out[:out[:width].rfind(" ")]
        outputter.print("%s%s" % (prefix, chunk))
        out = out[len(chunk)+1:]
        prefix = "    "
    outputter.print("%s%s" % (prefix, out))


def get_tx_stats(languages, outputter, verbose):
    """
    Does an API request to Transifex with the given API @p token, getting
    the translation statistics for the main body of texts. Then prints
    out CMake settings to replace the _tx_* variables in CMakeLists.txt
    according to standard criteria.

    If @p verbose is True, prints out language stats as well.
    """
    # Some languages go into the "incomplete" list by definition,
    # regardless of their completion status: this can have various reasons.
    #
    # Note that Esperanto (eo) is special-cased in CMakeLists.txt
    # during the build; recent Qt releases *do* support the language,
    # and it's at-the-least ok.
    incomplete_languages = (
        "eo",   # Not supported by QLocale < 5.12.1
        "ie",   # Not supported by Qt at least through 5.15.0
        )

    all_langs = []
    mark_text = "# Total %d languages" % len(languages)
    outputter.print(mark_text)
    for lang_name in languages:
        stats = languages[lang_name]["translated"]["percentage"]
        # Make the by-definition-incomplete languages have a percentage
        # lower than zero; this way they end up sorted (in -v output)
        # at the bottom but you can still determine the "actual" percentage.
        if lang_name in incomplete_languages:
            stats = -stats
        all_langs.append((stats, lang_name))

    if verbose:
        for s, l in sorted(all_langs, reverse=True):
            outputter.print("#  %16s\t%6.2f" % (l, s * 100.0))
    output_langs(all_langs, outputter, "complete", lambda s : s == 1.0)
    output_langs(all_langs, outputter, "good", lambda s : 1.0 > s >= 0.75)
    output_langs(all_langs, outputter, "ok", lambda s : 0.75 > s >= 0.05)
    output_langs(all_langs, outputter, "incomplete", lambda s : 0.05 > s)
    outputter.print(mark_text)

    # Audit the languages that are in TX, mapped to git
    for lang_name in languages:
        if not os.path.exists("lang/calamares_{}.ts".format(lang_name)):
            print("# !! Missing translation file for {}".format(lang_name))
        if not os.path.isdir("lang/python/{}/LC_MESSAGES".format(lang_name)):
            print("# !! Missing Python translation file for {}".format(lang_name))

    # Audit the files that are in git, mapped to TX
    special_cases = ("python.pot", "python", "CMakeLists.txt", "txload.cpp", "calamares_i18n.qrc.in")
    for file_name in os.listdir("lang"):
        if file_name in special_cases:
            continue
        elif file_name.startswith("calamares_") and file_name.endswith(".ts"):
            key = file_name[10:-3]
            if not key in languages and not key == "en":
                print("# !! Translation file for {} not in TX".format(key))
        elif file_name.startswith("tz_") and file_name.endswith(".ts"):
            key = file_name[3:-3]
            if not key in languages and not key == "en":
                print("# !! Translation file for TZ {} not in TX".format(key))
        elif file_name.startswith("kb_") and file_name.endswith(".ts"):
            key = file_name[3:-3]
            if not key in languages and not key == "en":
                print("# !! Translation file for KB {} not in TX".format(key))
        else:
            print("# !! Weird translation file {} not in TX".format(file_name))

    # Audit the python translation files that are in git, mapped to TX
    for file_name in os.listdir("lang/python"):
        if file_name not in languages:
            print("# !! Translation file for Python {} not in TX".format(file_name))

    return 0


def main():
    parser = argparse.ArgumentParser(description="Update Transifex Statistics")
    parser.add_argument("--verbose", "-v", help="Show statistics", action="store_true")
    parser.add_argument("--bogus", "-n", help="Use bogus data (do not query Transifex)", action="store_true")
    parser.add_argument("--edit", "-e", help="Edit CMakeLists.txt in-place", action="store_true")
    args = parser.parse_args()
    try:
        if args.bogus:
            getter = BogusGetter()
        else:
            getter = TransifexGetter()
        if args.edit:
            outputter = EditingOutputter()
        else:
            outputter = PrintOutputter()
        with outputter:
            return get_tx_stats(getter.languages, outputter, args.verbose)
    except TXError as e:
        print("! " + str(e))
        return 1;
    return 0

if __name__ == "__main__":
    sys.exit(main())
