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
# Convenience function for creating a C++ (qtplugin) module for Calamares.
# This function provides cmake-time feedback about the plugin, adds
# targets for compilation and boilerplate information, and creates
# a module.desc with standard values if none is provided (which only
# happens for very unusual plugins).
#
# Usage:
#
# calamares_add_plugin(
#   module-name
#   TYPE <view|job>
#   EXPORT_MACRO macro-name
#   SOURCES source-file...
#   UI ui-file...
#   LINK_LIBRARIES lib...
#   LINK_PRIVATE_LIBRARIES lib...
#   COMPILE_DEFINITIONS def...
#   RESOURCES resource-file
#   [NO_INSTALL]
#   [SHARED_LIB]
# )

include( CMakeParseArguments )
include( CalamaresAddLibrary  )
include( CMakeColors )

function( calamares_add_plugin )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( options NO_INSTALL SHARED_LIB )
    set( oneValueArgs NAME TYPE EXPORT_MACRO RESOURCES )
    set( multiValueArgs SOURCES UI LINK_LIBRARIES LINK_PRIVATE_LIBRARIES COMPILE_DEFINITIONS )
    cmake_parse_arguments( PLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
    set( PLUGIN_NAME ${NAME} )
    set( PLUGIN_DESTINATION ${CMAKE_INSTALL_LIBDIR}/calamares/modules/${PLUGIN_NAME} )
    set( PLUGIN_DESC_FILE module.desc )
    file( GLOB PLUGIN_CONFIG_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.conf" )
    set( PLUGIN_DATA_DESTINATION share/calamares/modules )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )

    message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${PLUGIN_NAME}${ColorReset}" )
    if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
        message( "   ${Green}TYPE:${ColorReset} ${PLUGIN_TYPE}" )
        message( "   ${Green}LINK_LIBRARIES:${ColorReset} ${PLUGIN_LINK_LIBRARIES}" )
        message( "   ${Green}LINK_PRIVATE_LIBRARIES:${ColorReset} ${PLUGIN_LINK_PRIVATE_LIBRARIES}" )
#        message( "   ${Green}SOURCES:${ColorReset} ${PLUGIN_SOURCES}" )
#        message( "   ${Green}UI:${ColorReset} ${PLUGIN_UI}" )
#        message( "   ${Green}EXPORT_MACRO:${ColorReset} ${PLUGIN_EXPORT_MACRO}" )
#        message( "   ${Green}NO_INSTALL:${ColorReset} ${PLUGIN_NO_INSTALL}" )
        message( "   ${Green}PLUGIN_DESTINATION:${ColorReset} ${PLUGIN_DESTINATION}" )
        if( PLUGIN_CONFIG_FILES )
            if ( INSTALL_CONFIG )
                message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${PLUGIN_CONFIG_FILES} => ${PLUGIN_DATA_DESTINATION}" )
            else()
                message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${PLUGIN_CONFIG_FILES} => [Skipping installation]" )
            endif()
        endif()
        if( PLUGIN_RESOURCES )
            message( "   ${Green}RESOURCES:${ColorReset} ${PLUGIN_RESOURCES}" )
        endif()
        message( "" )
    endif()
    # create target name once for convenience
    set( target "calamares_${PLUGIN_TYPE}_${PLUGIN_NAME}" )

    # determine target type
    if( NOT ${PLUGIN_SHARED_LIB} )
        set( target_type "MODULE" )
    else()
        set( target_type "SHARED" )
    endif()

    list( APPEND calamares_add_library_args
        "${target}"
        "EXPORT_MACRO" "${PLUGIN_EXPORT_MACRO}"
        "TARGET_TYPE" "${target_type}"
        "SOURCES" "${PLUGIN_SOURCES}"
    )

    if( PLUGIN_UI )
        list( APPEND calamares_add_library_args "UI" "${PLUGIN_UI}" )
    endif()

    if( PLUGIN_LINK_LIBRARIES )
        list( APPEND calamares_add_library_args "LINK_LIBRARIES" "${PLUGIN_LINK_LIBRARIES}" )
    endif()

    if( PLUGIN_LINK_PRIVATE_LIBRARIES )
        list( APPEND calamares_add_library_args "LINK_PRIVATE_LIBRARIES" "${PLUGIN_LINK_PRIVATE_LIBRARIES}" )
    endif()

    if( PLUGIN_COMPILE_DEFINITIONS )
        list( APPEND calamares_add_library_args "COMPILE_DEFINITIONS" ${PLUGIN_COMPILE_DEFINITIONS} )
    endif()

    list( APPEND calamares_add_library_args "NO_VERSION" )

    list( APPEND calamares_add_library_args "INSTALL_BINDIR" "${PLUGIN_DESTINATION}" )

    if( PLUGIN_RESOURCES )
        list( APPEND calamares_add_library_args "RESOURCES" "${PLUGIN_RESOURCES}" )
    endif()

    calamares_add_library( ${calamares_add_library_args} )

    if ( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_DESC_FILE} )
        configure_file( ${PLUGIN_DESC_FILE} ${PLUGIN_DESC_FILE} COPYONLY )
    else()
        set( _file ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_DESC_FILE} )
        set( _type ${PLUGIN_TYPE} )
        file( WRITE  ${_file} "# AUTO-GENERATED metadata file\n# Syntax is YAML 1.2\n---\n" )
        file( APPEND ${_file} "type: \"${_type}\"\nname: \"${PLUGIN_NAME}\"\ninterface: \"qtplugin\"\nload: \"lib${target}.so\"\n" )
    endif()

    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_DESC_FILE}
             DESTINATION ${PLUGIN_DESTINATION} )

    if ( INSTALL_CONFIG )
        foreach( PLUGIN_CONFIG_FILE ${PLUGIN_CONFIG_FILES} )
            configure_file( ${PLUGIN_CONFIG_FILE} ${PLUGIN_CONFIG_FILE} COPYONLY )
            install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE}
                     DESTINATION ${PLUGIN_DATA_DESTINATION} )
        endforeach()
    endif()
endfunction()
