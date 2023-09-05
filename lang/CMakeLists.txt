# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# This CMakeList handles the following i18n / language targets:
#
# - creating a translation test-tool
# - building the Python (gettext-based) translations
# - compiling all the Qt translations into a C++ file calamares-i18n.cxx
# - defines an OBJECT LIBRARY calamares-i18n for linking the compiled
#   translations into an executable.

include(CalamaresAddTranslations)

find_package(${qtname} COMPONENTS Xml)
if(TARGET ${qtname}::Xml)
    add_executable(txload txload.cpp)
    target_link_libraries(txload ${qtname}::Xml)
endif()

install_calamares_gettext_translations(python
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lang/python
    FILENAME python.mo
    RENAME calamares-python.mo
)

### TRANSLATIONS
#
#
calamares_qrc_translations(calamares-i18n
    OUTPUT_VARIABLE translation_outfile
    PREFIXES calamares tz kb
)

add_library(calamares-i18n OBJECT ${translation_outfile})
