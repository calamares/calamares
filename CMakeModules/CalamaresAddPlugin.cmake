# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Calamares is Free Software: see the License-Identifier above.
#
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
#   [WEIGHT w]
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
#  - WEIGHT
#       If this is set, writes an explicit weight into the module.desc;
#       module weights are used in progress reporting.
#
#
# This function follows the global SKIP_MODULES and USE_* settings, so
# a plugin may be skipped -- then nothing will be built. In that case,
# SKIPPED_MODULES is set in the parent (i.e. caller's) scope with the
# reason why. This should rarely be a concern as AddModuleSubdirectory
# already handles skip-reasons and collects them for reporting.

include( CMakeParseArguments )

include( CalamaresAddLibrary  )
include( CalamaresCheckModuleSelection )
include( CMakeColors )

function( calamares_add_plugin )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( options NO_CONFIG NO_INSTALL SHARED_LIB EMERGENCY )
    set( oneValueArgs NAME TYPE EXPORT_MACRO RESOURCES WEIGHT )
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

    calamares_check_skip( ${NAME} _skip)
    if ( _skip )
        set( SKIPPED_MODULES "${_skip}" PARENT_SCOPE )
        return()
    endif()

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

    # automatic library linkage
    if(PLUGIN_TYPE STREQUAL "view" OR PLUGIN_TYPE STREQUAL "viewmodule")
        list(APPEND PLUGIN_LINK_PRIVATE_LIBRARIES Calamares::calamaresui)
    elseif(PLUGIN_TYPE STREQUAL "job")
        list(APPEND PLUGIN_LINK_PRIVATE_LIBRARIES Calamares::calamares)
    else()
        message(FATAL_ERROR "Unknown plugin type ${PLUGIN_TYPE}")
    endif()

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
        if ( PLUGIN_WEIGHT )
            file( APPEND ${_file} "weight: ${PLUGIN_WEIGHT}\n" )
        endif()
    endif()

    if ( NOT PLUGIN_NO_INSTALL )
        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_DESC_FILE}
                DESTINATION ${PLUGIN_DESTINATION} )

        set( _warned_config OFF )
        foreach( PLUGIN_CONFIG_FILE ${PLUGIN_CONFIG_FILES} )
            if( ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN_CONFIG_FILE} IS_NEWER_THAN ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE} OR INSTALL_CONFIG )
                configure_file( ${PLUGIN_CONFIG_FILE} ${PLUGIN_CONFIG_FILE} COPYONLY )
            else()
                message( "   ${BoldYellow}Not updating${ColorReset} ${PLUGIN_CONFIG_FILE}" )
                set( _warned_config ON )
            endif()
            if ( INSTALL_CONFIG )
                install(
                    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE}
                    DESTINATION ${PLUGIN_DATA_DESTINATION} )
            endif()
        endforeach()
        if ( _warned_config )
            message( "" )
        endif()
    endif()
endfunction()
