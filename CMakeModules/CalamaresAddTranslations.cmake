# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
#
#   SPDX-License-Identifier: GPL-3.0-or-later
#   License-Filename: LICENSE
#
###
#
# This file has not yet been documented for use outside of Calamares itself.

include( CMakeParseArguments )

if( NOT _rcc_version_support_checked )
    set( _rcc_version_support_checked TRUE )

    # Extract the executable name
    get_property( _rcc_executable
        TARGET ${Qt5Core_RCC_EXECUTABLE}
        PROPERTY IMPORTED_LOCATION
    )
    if( NOT _rcc_executable )
        # Weird, probably now uses Qt5::rcc which is wrong too
        set( _rcc_executable ${Qt5Core_RCC_EXECUTABLE} )
    endif()

    # Try an empty RCC file with explicit format-version
    execute_process(
        COMMAND echo "<RCC version='1.0'></RCC>"
        COMMAND ${Qt5Core_RCC_EXECUTABLE} --format-version 1 --list -
        RESULT_VARIABLE _rcc_version_rv
        ERROR_VARIABLE _rcc_version_dump
    )
    if ( _rcc_version_rv EQUAL 0 )
        # Supported: force to the reproducible version
        set( _rcc_version_support --format-version 1 )
    else()
        # Older Qt versions (5.7, 5.8) don't support setting the
        # rcc format-version, so won't be reproducible if they
        # default to version 2.
        set( _rcc_version_support "" )
    endif()
    unset( _rcc_version_rv )
    unset( _rcc_version_dump )
endif()


# Internal macro for adding the C++ / Qt translations to the
# build and install tree. Should be called only once, from
# src/calamares/CMakeLists.txt.
macro(add_calamares_translations language)
    list( APPEND CALAMARES_LANGUAGES ${ARGV} )

    set( calamares_i18n_qrc_content "<!DOCTYPE RCC><RCC version=\"1.0\">\n" )

    # calamares and qt language files
    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<qresource prefix=\"/lang\">\n" )
    foreach( lang ${CALAMARES_LANGUAGES} )
        foreach( tlsource "calamares_${lang}" "tz_${lang}" )
            if( EXISTS "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts" )
                set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<file>${tlsource}.qm</file>\n" )
                list( APPEND TS_FILES "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts" )
            endif()
        endforeach()
    endforeach()

    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}</qresource>\n" )
    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}</RCC>\n" )

    file( WRITE ${CMAKE_BINARY_DIR}/lang/calamares_i18n.qrc "${calamares_i18n_qrc_content}" )

    qt5_add_translation(QM_FILES ${TS_FILES})

    ## HACK HACK HACK - around rcc limitations to allow out of source-tree building
    set( trans_file calamares_i18n )
    set( trans_srcfile ${CMAKE_BINARY_DIR}/lang/${trans_file}.qrc )
    set( trans_infile ${CMAKE_CURRENT_BINARY_DIR}/${trans_file}.qrc )
    set( trans_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${trans_file}.cxx )

    # Copy the QRC file to the output directory
    add_custom_command(
        OUTPUT ${trans_infile}
        COMMAND ${CMAKE_COMMAND} -E copy ${trans_srcfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_srcfile}
    )

    # Run the resource compiler (rcc_options should already be set)
    add_custom_command(
        OUTPUT ${trans_outfile}
        COMMAND "${Qt5Core_RCC_EXECUTABLE}"
        ARGS ${rcc_options} ${_rcc_version_support} -name ${trans_file} -o ${trans_outfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_infile}
        DEPENDS ${QM_FILES}
    )
endmacro()

# Internal macro for Python translations
#
# Translations of the Python modules that don't have their own
# lang/ subdirectories -- these are collected in top-level
# lang/python/<lang>/LC_MESSAGES/python.mo
macro(add_calamares_python_translations language)
    set( CALAMARES_LANGUAGES "" )
    list( APPEND CALAMARES_LANGUAGES ${ARGV} )

    install_calamares_gettext_translations( python
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/lang/python
        FILENAME python.mo
        RENAME calamares-python.mo
    )
endmacro()

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

    message(STATUS "Installing gettext translations for ${TRANSLATION_NAME}")
    message(STATUS "  Installing ${TRANSLATION_FILENAME} from ${TRANSLATION_SOURCE_DIR}")

    set( TRANSLATION_NAME "${NAME}" )
    set( INSTALLED_TRANSLATIONS "" )
    foreach( lang ${CALAMARES_TRANSLATION_LANGUAGES} )  # Global
        set( lang_mo "${TRANSLATION_SOURCE_DIR}/${lang}/LC_MESSAGES/${TRANSLATION_FILENAME}" )
        if( lang STREQUAL "en" )
            message( STATUS "  Skipping ${TRANSLATION_NAME} translations for en_US" )
        else( EXISTS ${lang_mo} )
            list( APPEND INSTALLED_LANGUAGES "${lang}" )
            install(
                FILES ${lang_mo}
                DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/${lang}/LC_MESSAGES/
                RENAME ${TRANSLATION_RENAME}
            )
            # TODO: make translations available in build dir too, for
            #       translation when running calamares -d from builddir.
            set(_build_lc ${CMAKE_BINARY_DIR}/lang/${lang}/LC_MESSAGES/)
            file(COPY ${lang_mo} DESTINATION ${_build_lc})
            if (NOT TRANSLATION_FILENAME STREQUAL TRANSLATION_RENAME)
                file(RENAME ${_build_lc}${TRANSLATION_FILENAME} ${_build_lc}${TRANSLATION_RENAME})
            endif()

        endif()
    endforeach()
endfunction()
