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
#   SPDX-License-Identifier: GPL-3.0+
#   License-Filename: LICENSE
#
###
#
# Support macros for creating Calamares branding components.
#
# Calamares branding components have two parts:
# - a branding.desc file that tells Calamares how to describe the product
#   (e.g. strings like "Generic GNU/Linux") and the name of a QML file
#   (the "slideshow") that is displayed during installation.
# - the QML files themselves, plus supporting images etc.
#
# Branding components can be created inside the Calamares source tree
# (there is one example the `default/` branding, which is also connected
# to the default configuration shipped with Calamares), but they can be
# built outside of, and largely independently of, Calamares by using
# these CMake macros.
#
# See the calamares-examples repository for more examples.
#
include( CMakeParseArguments)

include( CMakeColors )

# Usage calamares_add_branding( <name> [DIRECTORY <dir>] [SUBDIRECTORIES <dir> ...])
#
# Adds a branding component to the build:
# - the component's top-level files are copied into the build-dir;
#   CMakeLists.txt is excluded from the glob.
# - the component's top-level files are installed into the component branding dir
#
# The branding component lives in <dir> if given, otherwise the
# current source directory. The branding component is installed
# with the given <name>, which is usually the name of the
# directory containing the component, and which must match the
# *componentName* in `branding.desc`.
#
# If SUBDIRECTORIES are given, then those are copied (each one level deep)
# to the installation location as well, preserving the subdirectory name.
function( calamares_add_branding NAME )
    set( _CABT_DIRECTORY "." )
    cmake_parse_arguments( _CABT "" "DIRECTORY" "SUBDIRECTORIES" ${ARGN} )
    set( SUBDIRECTORY ${_CABT_DIRECTORY} )
    set( _brand_dir ${_CABT_DIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

    foreach( _subdir "" ${_CABT_SUBDIRECTORIES} )
        file( GLOB BRANDING_COMPONENT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${_brand_dir} "${_brand_dir}/${_subdir}/*" )
        message(STATUS "${BRANDING_COMPONENT_FILES}")
        foreach( BRANDING_COMPONENT_FILE ${BRANDING_COMPONENT_FILES} )
            set( _subpath ${_brand_dir}/${BRANDING_COMPONENT_FILE} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_subpath} )
                configure_file( ${_subpath} ${_subpath} COPYONLY )

                install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${_subpath}
                            DESTINATION ${BRANDING_COMPONENT_DESTINATION}/${_subdir}/ )
            endif()
        endforeach()
    endforeach()

    message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} branding component: ${BoldRed}${NAME}${ColorReset}" )
    if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
        message( "   ${Green}TYPE:${ColorReset} branding component" )
        message( "   ${Green}BRANDING_COMPONENT_DESTINATION:${ColorReset} ${BRANDING_COMPONENT_DESTINATION}" )
    endif()
endfunction()

# Usage calamares_add_branding_translations( <name> [DIRECTORY <dir>])
#
# Adds the translations for a branding component to the build:
# - the component's lang/ directory is scanned for .ts files
# - the component's translations are installed into the component branding dir
#
# Translation files must be called calamares-<name>_<lang>.ts . Optionally
# the lang/ dir is found in the given <dir> instead of the current source
# directory.
function( calamares_add_branding_translations NAME )
    set( _CABT_DIRECTORY "." )
    cmake_parse_arguments( _CABT "" "DIRECTORY" "" ${ARGN} )
    set( SUBDIRECTORY ${_CABT_DIRECTORY} )
    set( _brand_dir ${_CABT_DIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

    file( GLOB BRANDING_TRANSLATION_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SUBDIRECTORY}/lang/calamares-${NAME}_*.ts" )
    if ( BRANDING_TRANSLATION_FILES )
        qt5_add_translation( QM_FILES ${BRANDING_TRANSLATION_FILES} )
        add_custom_target( branding-translation-${NAME} ALL DEPENDS ${QM_FILES} )
        install( FILES ${QM_FILES} DESTINATION ${BRANDING_COMPONENT_DESTINATION}/lang/ )
        list( LENGTH BRANDING_TRANSLATION_FILES _branding_count )
        message( "   ${Green}BRANDING_TRANSLATIONS:${ColorReset} ${_branding_count} language(s)" )
    endif()
endfunction()

# Usage calamares_add_branding_subdirectory( <dir> [SUBDIRECTORIES <dir> ...])
#
# Adds a branding component from a subdirectory:
# - if there is a CMakeLists.txt, use that
# - otherwise assume a "standard" setup with top-level files and a lang/ dir for translations
#
# If SUBDIRECTORIES are given, they are relative to <dir>, and are
# copied (one level deep) to the install location as well.
function( calamares_add_branding_subdirectory SUBDIRECTORY )
    cmake_parse_arguments( _CABS "" "" "SUBDIRECTORIES" ${ARGN} )

    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/branding.desc" )
        calamares_add_branding( ${SUBDIRECTORY} DIRECTORY ${SUBDIRECTORY} SUBDIRECTORIES ${_CABS_SUBDIRECTORIES} )
        if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
            calamares_add_branding_translations( ${SUBDIRECTORY} DIRECTORY ${SUBDIRECTORY} )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add branding component subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no branding.desc." )
    endif()
    message( "" )
endfunction()
