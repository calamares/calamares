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
# Convenience function for creating a C++ (qtplugin) module for Calamares.
# This function provides cmake-time feedback about the plugin, adds
# targets for compilation and boilerplate information, and creates
# a module.desc with standard values (if the module.desc file exists,
# that one is used instead, which happens only for unusual plugins).
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
#   [COMPILE_DEFINITIONS def...]
#   [RESOURCES resource-file]
#   [REQUIRES module-name...]
#   [NO_INSTALL]
#   [NO_CONFIG]
#   [SHARED_LIB]
#   [EMERGENCY]
# )
#
# Function parameters:
#  - COMPILE_DEFINITIONS
#       Definitions are set on the resulting module with a suitable
#       flag (i.e. `-D`) so only state the name (optionally, also the value)
#       without a `-D` prefixed to it.
#  - RESOURCES
#       One (single!) filename for the RCC file for the plugin.
#  - REQUIRES
#       One or more names of modules which are added to the *requiredModules*
#       key in the descriptor. See *Module Requirements* in the module
#       documentation.
#  - NO_INSTALL
#       If this is set, the module is not installed by default; use this to
#       build testing modules or unit-testing modules.
#  - SHARED_LIB
#       In unusual circumstances, this function is used to add a library
#       rather than a normal Calamares module / plugin.
#  - EMERGENCY
#       If this is set, the module is marked as an *emergency* module in the
#       descriptor. See *Emergency Modules* in the module documentation.
#

include( CMakeParseArguments )
include( CalamaresAddLibrary  )
include( CMakeColors )

function( calamares_add_plugin )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( options NO_CONFIG NO_INSTALL SHARED_LIB EMERGENCY )
    set( oneValueArgs NAME TYPE EXPORT_MACRO RESOURCES )
    set( multiValueArgs SOURCES UI LINK_LIBRARIES LINK_PRIVATE_LIBRARIES COMPILE_DEFINITIONS REQUIRES )
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
    message( "   ${Green}TYPE:${ColorReset} ${PLUGIN_TYPE}" )
    message( "   ${Green}LINK_LIBRARIES:${ColorReset} ${PLUGIN_LINK_LIBRARIES}" )
    message( "   ${Green}LINK_PRIVATE_LIBRARIES:${ColorReset} ${PLUGIN_LINK_PRIVATE_LIBRARIES}" )
    message( "   ${Green}PLUGIN_DESTINATION:${ColorReset} ${PLUGIN_DESTINATION}" )
    if( PLUGIN_CONFIG_FILES )
        if( PLUGIN_NO_CONFIG )
            message( FATAL_ERROR "${Red}NO_CONFIG${ColorReset} is set, with configuration ${Red}${PLUGIN_CONFIG_FILES}${ColorReset}" )
        endif()
        set( _destination "(unknown)" )
        if ( INSTALL_CONFIG AND NOT PLUGIN_NO_INSTALL )
            set( _destination "${PLUGIN_DATA_DESTINATION}" )
        elseif( NOT PLUGIN_NO_INSTALL )
            # Not INSTALL_CONFIG
            set( _destination "[Build directory only]" )
        else()
            set( _destination "[Skipping installation]" )
        endif()
        message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${PLUGIN_CONFIG_FILES} => ${_destination}" )
    else()
        if( NOT PLUGIN_NO_CONFIG )
            message( "   ${Red}NO_CONFIG${ColorReset} should be set." )
        endif()
    endif()
    if( PLUGIN_RESOURCES )
        message( "   ${Green}RESOURCES:${ColorReset} ${PLUGIN_RESOURCES}" )
    endif()
    message( "" )

    # create target name once for convenience
    set( target "calamares_${PLUGIN_TYPE}_${PLUGIN_NAME}" )

    # determine target type
    if( NOT ${PLUGIN_SHARED_LIB} )
        set( target_type "MODULE" )
    else()
        set( target_type "SHARED" )
    endif()

    set( calamares_add_library_args
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

    if ( PLUGIN_NO_INSTALL )
        list( APPEND calamares_add_library_args "NO_INSTALL" )
    endif()

    list( APPEND calamares_add_library_args
        "NO_VERSION"
        "INSTALL_BINDIR" "${PLUGIN_DESTINATION}"
    )

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
        if ( PLUGIN_REQUIRES )
            file( APPEND ${_file} "requiredModules:\n" )
            foreach( _r ${PLUGIN_REQUIRES} )
                file( APPEND ${_file} " - ${_r}\n" )
            endforeach()
        endif()
        if ( PLUGIN_EMERGENCY )
            file( APPEND ${_file} "emergency: true\n" )
        endif()
        if ( PLUGIN_NO_CONFIG )
            file( APPEND ${_file} "noconfig: true\n" )
        endif()
    endif()

    if ( NOT PLUGIN_NO_INSTALL )
        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_DESC_FILE}
                DESTINATION ${PLUGIN_DESTINATION} )

        foreach( PLUGIN_CONFIG_FILE ${PLUGIN_CONFIG_FILES} )
            configure_file( ${PLUGIN_CONFIG_FILE} ${PLUGIN_CONFIG_FILE} COPYONLY )
            if ( INSTALL_CONFIG )
                install(
                    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE}
                    DESTINATION ${PLUGIN_DATA_DESTINATION} )
            endif()
        endforeach()
    endif()
endfunction()
