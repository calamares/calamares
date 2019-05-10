#! /usr/bin/env python3
#
# Python3 script to scrape some data out of ICU CLDR supplemental data.
#
# To use this script, you must have downloaded the CLDR data, e.g.
# http://unicode.org/Public/cldr/35.1/, and extracted the zip file.
# Run the script from **inside** the common/ durectory that is created
# (or fix the hard-coded path).
#
# The script tries to print C++ code that compiles; if there are encoding
# problems, it will print some kind of representation of the problematic
# lines.
#
# To avoid having to cross-reference multiple XML files, the script
# cheats: it reads the comments as well to get names. So it looks for
# pairs of lines like this:
#
#    <likelySubtag from="und_BQ" to="pap_Latn_BQ"/>
#    <!--{ ?; ?; Caribbean Netherlands } => { Papiamento; Latin; Caribbean Netherlands }-->
#
# It extracts the 2-character country code "BQ" from the sub-tag, and
# parses the comment to get a language and country name (instead of looking up
# "pap" and "BQ" in other tables). This may be considered a hack.
#
# A large collection of exceptions can be found in the two *_mapper tables,
# which massage the CLDR names to Qt enum values.


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
    
def extricate(l1, l2):
    if '"und_' not in l1:
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
      
    # There shouldn't be any UTF-8 left in there.
    try:
        print("{!s} QLocale::Language::{!s}, QLocale::Country::{!s}, '{!s}', '{!s}' {!s},".format(
            "{",
            l2_language, 
            l2_country,
            l1_code[0], 
            l1_code[1],
            "}"))
    except UnicodeEncodeError:
        print(list(map(lambda x : '?' if x > 128 else chr(x), map(lambda x:ord(x), l2_country))))
        raise

print("""// Generated from CLDR data
#include <QLocale>
struct CountryData
{
    QLocale::Language l;
    QLocale::Country c;
    char cc1;
    char cc2;
};

static const CountryData countryMap[] = {
""")

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
            
            extricate(l1, l2)
        
print("""{ QLocale::Language::AnyLanguage, QLocale::Country::AnyCountry, 0, 0 } // Terminator
};
// END Generated from CLDR data
""")
