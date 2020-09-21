# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Calamares is Free Software: see the License-Identifier above.
#
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
    cmake_parse_arguments( _CABT "" "DIRECTORY" "SUBDIRECTORIES" ${ARGN} )
    if (NOT _CABT_DIRECTORY)
        set(_CABT_DIRECTORY ".")
    endif()

    set( SUBDIRECTORY ${_CABT_DIRECTORY} )
    set( _brand_dir ${_CABT_DIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

    foreach( _subdir "" ${_CABT_SUBDIRECTORIES} )
        file( GLOB BRANDING_COMPONENT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${_brand_dir} "${_brand_dir}/${_subdir}/*" )
        foreach( BRANDING_COMPONENT_FILE ${BRANDING_COMPONENT_FILES} )
            set( _subpath ${_brand_dir}/${BRANDING_COMPONENT_FILE} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${_subpath} )
                set( _src ${CMAKE_CURRENT_SOURCE_DIR}/${_subpath} )
                set( _dst ${CMAKE_CURRENT_BINARY_DIR}/${_subpath} )
                if( ${_src} IS_NEWER_THAN ${_dst} )
                    configure_file( ${_src} ${_dst} COPYONLY )
                endif()

                install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${_subpath}
                            DESTINATION ${BRANDING_COMPONENT_DESTINATION}/${_subdir}/ )
            endif()
        endforeach()
    endforeach()

    message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} branding component: ${BoldRed}${NAME}${ColorReset}" )
    message( "   ${Green}TYPE:${ColorReset} branding component" )
    message( "   ${Green}BRANDING_COMPONENT_DESTINATION:${ColorReset} ${BRANDING_COMPONENT_DESTINATION}" )
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
    cmake_parse_arguments( _CABT "" "DIRECTORY" "" ${ARGN} )
    if (NOT _CABT_DIRECTORY)
        set(_CABT_DIRECTORY ".")
    endif()

    set( SUBDIRECTORY ${_CABT_DIRECTORY} )
    set( _brand_dir ${_CABT_DIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

    file( GLOB BRANDING_TRANSLATION_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SUBDIRECTORY}/lang/calamares-${NAME}_*.ts" )
    if ( BRANDING_TRANSLATION_FILES )
        qt5_add_translation( QM_FILES ${BRANDING_TRANSLATION_FILES} )
        add_custom_target( branding-translation-${NAME} ALL DEPENDS ${QM_FILES}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/lang/
            COMMAND ${CMAKE_COMMAND} -E copy ${QM_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/lang/
        )
        install( FILES ${QM_FILES} DESTINATION ${BRANDING_COMPONENT_DESTINATION}/lang/ )
        list( LENGTH BRANDING_TRANSLATION_FILES _branding_count )
        message( "   ${Green}BRANDING_TRANSLATIONS:${ColorReset} ${_branding_count} language(s)" )
    endif()
endfunction()

# Usage calamares_add_branding_subdirectory( <dir> [NAME <name>] [SUBDIRECTORIES <dir> ...])
#
# Adds a branding component from a subdirectory:
# - if there is a CMakeLists.txt, use that (that CMakeLists.txt should
#   call suitable calamares_add_branding() and other macros to install
#   the branding component).
# - otherwise assume a "standard" setup with top-level files and a lang/
#   subdirectory for translations.
#
# If NAME is given, this is used instead of <dir> as the name of
# the branding component. This is needed if <dir> is more than
# one level deep, or to rename a component as it gets installed.
#
# If SUBDIRECTORIES are given, they are relative to <dir>, and are
# copied (one level deep) to the install location as well.
function( calamares_add_branding_subdirectory SUBDIRECTORY )
    cmake_parse_arguments( _CABS "" "NAME" "SUBDIRECTORIES" ${ARGN} )
    if (NOT _CABS_NAME)
        set(_CABS_NAME "${SUBDIRECTORY}")
    endif()

    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/branding.desc" )
        calamares_add_branding( ${_CABS_NAME} DIRECTORY ${SUBDIRECTORY} SUBDIRECTORIES ${_CABS_SUBDIRECTORIES} )
        if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
            calamares_add_branding_translations( ${_CABS_NAME} DIRECTORY ${SUBDIRECTORY} )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add branding component subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no branding.desc." )
    endif()
    message( "" )
endfunction()
