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

find_package(Qt5 COMPONENTS Xml)
if(Qt5Xml_FOUND)
    add_executable(txload txload.cpp)
    target_link_libraries(txload Qt5::Xml)
endif()

install_calamares_gettext_translations(python
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lang/python
    FILENAME python.mo
    RENAME calamares-python.mo
)

### TRANSLATIONS
#
#
set(TS_FILES "")
set(calamares_i18n_qrc_content "")

# calamares and qt language files
foreach(lang ${CALAMARES_TRANSLATION_LANGUAGES})
    foreach(tlsource "calamares_${lang}" "tz_${lang}" "kb_${lang}")
        if(EXISTS "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts")
            string(APPEND calamares_i18n_qrc_content "<file>${tlsource}.qm</file>\n")
            list(APPEND TS_FILES "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts")
        endif()
    endforeach()
endforeach()

set(trans_file calamares_i18n)
set(trans_infile ${CMAKE_CURRENT_BINARY_DIR}/${trans_file}.qrc)
set(trans_outfile ${CMAKE_CURRENT_BINARY_DIR}/calamares-i18n.cxx)
set(CALAMARES_TRANSLATIONS_SOURCE ${trans_outfile})

configure_file(${CMAKE_SOURCE_DIR}/lang/calamares_i18n.qrc.in ${trans_infile} @ONLY)

qt5_add_translation(QM_FILES ${TS_FILES})

# Run the resource compiler (rcc_options should already be set)
add_custom_command(
    OUTPUT ${trans_outfile}
    COMMAND "${Qt5Core_RCC_EXECUTABLE}"
    ARGS ${rcc_options} --format-version 1 -name ${trans_file} -o ${trans_outfile} ${trans_infile}
    MAIN_DEPENDENCY ${trans_infile}
    DEPENDS ${QM_FILES}
)

add_library(calamares-i18n OBJECT ${trans_outfile})
