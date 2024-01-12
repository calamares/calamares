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

include(CMakeParseArguments)
include(FeatureSummary)

# The Gettext module is still old-fashioned, ALLCAPS variables
find_package( Gettext )
set_package_properties( GETTEXT PROPERTIES
    DESCRIPTION "GNU gettext (translation) tools."
    URL "https://www.gnu.org/software/gettext/"
    PURPOSE "Gettext is used in the translation of Python modules."
    TYPE REQUIRED
)

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

    if ( GETTEXT_FOUND AND GETTEXT_MSGFMT_EXECUTABLE )
        message( STATUS "Installing gettext translations for ${TRANSLATION_NAME}")
        message( STATUS "  Installing ${TRANSLATION_FILENAME} from ${TRANSLATION_SOURCE_DIR}")
    else()
        message( WARNING "Gettext translations requested for ${TRANSLATION_NAME}, but gettext was not found." )
        return()
    endif()

    set( TARGET_NAME calamares-gettext-translations-${NAME} )
    if( NOT TARGET "${TARGET_NAME}" )
        add_custom_target( "${TARGET_NAME}" ALL )
    endif()

    set( TRANSLATION_NAME "${NAME}" )
    foreach( lang ${CALAMARES_TRANSLATION_LANGUAGES} )  # Global
        string( MAKE_C_IDENTIFIER "${TARGET_NAME}-${lang}" TARGET_SUBNAME )

        set( lang_po "${TRANSLATION_SOURCE_DIR}/${lang}/LC_MESSAGES/${TRANSLATION_SOURCE_FILENAME}" )
        set( lang_mo_dir "${CMAKE_BINARY_DIR}/lang/${lang}/LC_MESSAGES" )
        set( lang_mo "${lang_mo_dir}/${TRANSLATION_RENAME}" )
        if( lang STREQUAL "en" )
            message( STATUS "  Skipping ${TRANSLATION_NAME} translations for en_US" )
        else()
            # We **don't** use the gettext macro's here because the source
            # structure doesn't match: we are calling this once per language
            # for all of Calamares's languages, while the gettext module
            # expects it to be called once, for a given language source-dir.
            #
            # Using any of the gettext macros just gets us multiple rules
            # for python.gmo, and it wants to use msgmerge, besides, which
            # doesn't fit our Transifex workflow.
            make_directory( ${lang_mo_dir} )
            add_custom_command(
                OUTPUT ${lang_mo}
                COMMAND ${GETTEXT_MSGFMT_EXECUTABLE}
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

set(_calamares_qrc_translations_qrc_source ${CMAKE_CURRENT_LIST_DIR}/i18n.qrc.in) # Needs to be set outside of function
function(calamares_qrc_translations basename)
    set(options "")
    set(oneValueArgs SUBDIRECTORY OUTPUT_VARIABLE)
    set(multiValueArgs PREFIXES LANGUAGES)
    cmake_parse_arguments(_qrt "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT _qrt_OUTPUT_VARIABLE)
        message(FATAL_ERROR "No output variable")
    endif()
    if(NOT _qrt_PREFIXES)
        set(_qrt_PREFIXES "${basename}")
    endif()
    if(NOT _qrt_LANGUAGES)
        set(_qrt_LANGUAGES ${CALAMARES_TRANSLATION_LANGUAGES})
    endif()
    if(NOT _qrt_SUBDIRECTORY)
        set(_qrt_SUBDIRECTORY "")
    endif()

    set(translations_qrc_infile ${CMAKE_CURRENT_BINARY_DIR}/${basename}.qrc)
    set(translations_qrc_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${basename}.cxx)

    # Must use this variable name because of the @ substitution
    set(calamares_i18n_qrc_content "")
    set(calamares_i18n_ts_filelist "")
    foreach(lang ${_qrt_LANGUAGES})
        foreach(tlsource ${_qrt_PREFIXES})
            if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_qrt_SUBDIRECTORY}/${tlsource}_${lang}.ts")
                string(APPEND calamares_i18n_qrc_content "<file>${tlsource}_${lang}.qm</file>\n")
                list(APPEND calamares_i18n_ts_filelist "${CMAKE_CURRENT_SOURCE_DIR}/${_qrt_SUBDIRECTORY}/${tlsource}_${lang}.ts")
            endif()
        endforeach()
    endforeach()

    configure_file(${_calamares_qrc_translations_qrc_source} ${translations_qrc_infile} @ONLY)
    qt_add_translation(QM_FILES ${calamares_i18n_ts_filelist})

    # Run the resource compiler (rcc_options should already be set)
    add_custom_command(
        OUTPUT ${translations_qrc_outfile}
        COMMAND ${qtname}::rcc
        ARGS
            ${rcc_options}
            --format-version 1
            -name ${basename}
            -o ${translations_qrc_outfile}
            ${translations_qrc_infile}
        MAIN_DEPENDENCY ${translations_qrc_infile}
        DEPENDS ${QM_FILES}
    )

    set(${_qrt_OUTPUT_VARIABLE} ${translations_qrc_outfile} PARENT_SCOPE)
endfunction()
