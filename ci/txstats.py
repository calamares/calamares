#! /usr/bin/env python
#
# Uses the Transifex API to get a list of enabled languages,
# and outputs CMake settings for inclusion into CMakeLists.txt.
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
            parser = configparser.SafeConfigParser()
            parser.readfp(f)

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
    out = " ".join(["set( _tx_%s" % label, " ".join(these_langs), ")"])
    width = 68
    prefix = ""

    while len(out) > width - len(prefix):
        chunk = out[:out[:width].rfind(" ")]
        print("%s%s" % (prefix, chunk))
        out = out[len(chunk)+1:]
        prefix = "    "
    print("%s%s" % (prefix, out))

def get_tx_stats(token):
    """
    Does an API request to Transifex with the given API @p token, getting
    the translation statistics for the main body of texts. Then prints
    out CMake settings to replace the _tx_* variables in CMakeLists.txt
    according to standard criteria.
    """
    import requests

    r = requests.get("https://api.transifex.com/organizations/calamares/projects/calamares/resources/calamares-master/", auth=("api", token))
    if r.status_code != 200:
        return 1

    all_langs = []

    j = r.json()
    languages = j["stats"]
    print("# Total %d languages" % len(languages))
    for lang_name in languages:
        stats = languages[lang_name]["translated"]["percentage"]
        all_langs.append((stats, lang_name))

    all_langs.sort(reverse=True)

    output_langs(all_langs, "complete", lambda s : s == 1.0)
    output_langs(all_langs, "good", lambda s : 1.0 > s >= 0.75)
    output_langs(all_langs, "ok", lambda s : 0.75 > s >= 0.05)
    output_langs(all_langs, "bad", lambda s : 0.05 > s)

    return 0


def main():
    cred = get_tx_credentials()
    if cred:
        return get_tx_stats(cred)
    else:
        print("! Could not find API token in ~/.transifexrc")
        return 1
    return 0

if __name__ == "__main__":
    sys.exit(main())
