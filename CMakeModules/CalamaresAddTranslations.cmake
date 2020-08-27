# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Calamares is Free Software: see the License-Identifier above.
#
#
###
#
# This file has not yet been documented for use outside of Calamares itself.

include( CMakeParseArguments )

# Installs a directory containing language-code-labeled subdirectories with
# gettext data into the appropriate system directory. Allows renaming the
# .mo files during install to avoid namespace clashes.
#
# install_calamares_gettext_translations(
#   NAME <name of module, for human use>
#   SOURCE_DIR path/to/lang
#   FILENAME <name of file.mo>
#   [RENAME <new-name of.mo>]
# )
#
# For all of the (global) translation languages enabled for Calamares,
# try installing $SOURCE_DIR/$lang/LC_MESSAGES/<filename>.mo into the
# system gettext data directory (e.g. share/locale/), possibly renaming
# filename.mo to renamed.mo in the process.
function( install_calamares_gettext_translations )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( oneValueArgs NAME SOURCE_DIR FILENAME RENAME )
    cmake_parse_arguments( TRANSLATION "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if( NOT TRANSLATION_NAME )
        set( TRANSLATION_NAME ${NAME} )
    endif()
    if( NOT TRANSLATION_FILENAME )
        set( TRANSLATION_FILENAME "${TRANSLATION_NAME}.mo" )
    endif()
    if( NOT TRANSLATION_RENAME )
        set( TRANSLATION_RENAME "${TRANSLATION_FILENAME}" )
    endif()
    string( REGEX REPLACE ".mo$" ".po" TRANSLATION_SOURCE_FILENAME "${TRANSLATION_FILENAME}" )

    message(STATUS "Installing gettext translations for ${TRANSLATION_NAME}")
    message(STATUS "  Installing ${TRANSLATION_FILENAME} from ${TRANSLATION_SOURCE_DIR}")

    set( TARGET_NAME calamares-gettext-translations-${NAME} )
    if( NOT TARGET "${TARGET_NAME}" )
        add_custom_target( "${TARGET_NAME}" ALL )
    endif()

    set( TRANSLATION_NAME "${NAME}" )
    foreach( lang ${CALAMARES_TRANSLATION_LANGUAGES} )  # Global
        string( MAKE_C_IDENTIFIER "${TARGET_NAME}-${lang}" TARGET_SUBNAME )

        set( lang_po "${TRANSLATION_SOURCE_DIR}/${lang}/LC_MESSAGES/${TRANSLATION_SOURCE_FILENAME}" )
        set( lang_mo "${CMAKE_BINARY_DIR}/lang/${lang}/LC_MESSAGES/${TRANSLATION_RENAME}" )
        if( lang STREQUAL "en" )
            message( STATUS "  Skipping ${TRANSLATION_NAME} translations for en_US" )
        else()
            add_custom_command(
                OUTPUT ${lang_mo}
                COMMAND msgfmt
                ARGS -o ${lang_mo} ${lang_po}
                MAIN_DEPENDENCY ${lang_po}
                )
            add_custom_target( "${TARGET_SUBNAME}" DEPENDS ${lang_mo} )
            add_dependencies( "${TARGET_NAME}" "${TARGET_SUBNAME}" )
            install(
                FILES ${lang_mo}
                DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/${lang}/LC_MESSAGES/
            )
        endif()
    endforeach()
endfunction()
