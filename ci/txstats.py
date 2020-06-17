#! /usr/bin/env python3
#
# Uses the Transifex API to get a list of enabled languages,
# and outputs CMake settings for inclusion into CMakeLists.txt.
#
# This is a Python3 script.
#
# Run it with a -v command-line option to get extra output on
# actual translation percentages.
import sys

def get_tx_credentials():
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

def output_langs(all_langs, label, filterfunc):
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
        print("%s%s" % (prefix, chunk))
        out = out[len(chunk)+1:]
        prefix = "    "
    print("%s%s" % (prefix, out))

def get_tx_stats(token, verbose):
    """
    Does an API request to Transifex with the given API @p token, getting
    the translation statistics for the main body of texts. Then prints
    out CMake settings to replace the _tx_* variables in CMakeLists.txt
    according to standard criteria.

    If @p verbose is True, prints out language stats as well.
    """
    import requests

    r = requests.get("https://api.transifex.com/organizations/calamares/projects/calamares/resources/calamares/", auth=("api", token))
    if r.status_code != 200:
        return 1

    suppressed_languages = ( "es_ES", )  # In Transifex, but not used
    # Some languages go into the "incomplete" list by definition,
    # regardless of their completion status: this can have various reasons.
    #
    # Note that Esperanto (eo) is special-cased in CMakeLists.txt
    # during the build; recent Qt releases *do* support the language,
    # and it's at-the-least ok.
    incomplete_languages = (
        "eo",   # Not supported by QLocale < 5.12.1
        )

    all_langs = []

    j = r.json()
    languages = j["stats"]
    print("# Total %d languages" % len(languages))
    for lang_name in languages:
        if lang_name in suppressed_languages:
            continue
        stats = languages[lang_name]["translated"]["percentage"]
        # Make the by-definition-incomplete languages have a percentage
        # lower than zero; this way they end up sorted (in -v output)
        # at the bottom but you can still determine the "actual" percentage.
        if lang_name in incomplete_languages:
            stats = -stats
        all_langs.append((stats, lang_name))

    if verbose:
        for s, l in sorted(all_langs, reverse=True):
            print("#  %16s\t%6.2f" % (l, s * 100.0))
    output_langs(all_langs, "complete", lambda s : s == 1.0)
    output_langs(all_langs, "good", lambda s : 1.0 > s >= 0.75)
    output_langs(all_langs, "ok", lambda s : 0.75 > s >= 0.05)
    output_langs(all_langs, "incomplete", lambda s : 0.05 > s)

    return 0


def main():
    verbose = (sys.argv[-1] == "-v")
    cred = get_tx_credentials()
    if cred:
        return get_tx_stats(cred, verbose)
    else:
        print("! Could not find API token in ~/.transifexrc")
        return 1
    return 0

if __name__ == "__main__":
    sys.exit(main())
