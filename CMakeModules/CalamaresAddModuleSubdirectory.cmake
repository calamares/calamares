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
# Function and support code for adding a Calamares module (either a Qt / C++ plugin,
# or a Python module, or whatever) to the build.
#
# # Usage
#
# The public API is one single function:
#
# - calamares_add_module_subdirectory(subdirectory [skiplistvar])
#   Adds a given *subdirectory* to the modules list, building the
#   module that is there. The *subdirectory* must contain a `module.desc`
#   (generally non-C++ modules) or a `CMakeLists.txt` (for C++ modules,
#   or special cases). The module is assumed to be named after the
#   (last component of) the subdirectory.
#
#   If the module would be skipped (by the global SKIP_MODULES setting
#   or a USE_* setting) or the module itself sets a reason to skip
#   via the calamares_skip_module() function, the module is added to
#   the list of skipped-modules in *skiplistvar*. If no variable is
#   given, the reason is set in the parent scope variable
#   SKIPPED_MODULES . Do **not** use SKIPPED_MODULES as the name of
#   *skiplistvar*, things will get weird.
#
#   Do note that the name of a module must be the same as the name of
#   the directory containing it (as documented in src/modules/README.md).
#   This applies to both C++ and Python modules, and allows the use of
#   the subdirectory as a proxy for the module name inside.
#

include( CalamaresAddTranslations )
include( CalamaresCheckModuleSelection )

set( MODULE_DATA_DESTINATION share/calamares/modules )

# We look for Pylint (just once) so that unittests can be added that
# check the syntax / variables of Python modules. This should help
# avoid more typo's-in-releases.
if(BUILD_TESTING AND NOT PYLINT_COMMAND_SEARCHED)
    set(PYLINT_COMMAND_SEARCHED TRUE)
    find_program(
        PYLINT_COMMAND
        NAMES pylint3 pylint
        PATHS $ENV{HOME}/.local/bin
        )
endif()

function( _calamares_add_module_subdirectory_impl )
    set( SUBDIRECTORY ${ARGV0} )

    # Set SKIPPED_MODULES here, so CMake-based modules have a
    # parent scope to set it in; this function, in turn sets it
    # in **its** parent scope.
    set( SKIPPED_MODULES "" )
    set( MODULE_CONFIG_FILES "" )

    # The module subdirectory may be given as a/b/c, but the module
    # needs to be installed as "c", so we split off any intermediate
    # directories.
    #
    # Compute _modulename (the last directory name) and _mod_dir
    # (the full path to the module sources).
    get_filename_component(_dirname "${SUBDIRECTORY}" DIRECTORY)
    if( _dirname )
        # Remove the dirname and any leftover leading /s
        string( REGEX REPLACE "^${_dirname}/*" "" _modulename "${SUBDIRECTORY}" )
    else()
        set( _modulename ${SUBDIRECTORY} )
    endif()
    # Strip any remaining /
    string( REGEX REPLACE "/" "" _modulename "${_modulename}" )
    set( _mod_dir "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}" )

    # Skip list check applies to all kinds of modules
    calamares_check_skip( ${_modulename} SKIPPED_MODULES )
    if ( SKIPPED_MODULES )
        # If it's skipped by infrastucture, the message already includes the module
        # name. We don't need to do any further checking.
        set( SKIPPED_MODULES "${SKIPPED_MODULES}" PARENT_SCOPE )
        return()
    endif()

    # If this subdirectory has a CMakeLists.txt, we add_subdirectory it...
    if( EXISTS "${_mod_dir}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
        file( GLOB MODULE_CONFIG_FILES RELATIVE ${_mod_dir} "${SUBDIRECTORY}/*.conf" )
        # Module has indicated it should be skipped, show that in
        # the calling CMakeLists (which is src/modules/CMakeLists.txt normally).
        if ( SKIPPED_MODULES )
            set( SKIPPED_MODULES ${SKIPPED_MODULES} PARENT_SCOPE )
            set( MODULE_CONFIG_FILES "" )
        else()
            # The SKIPPED_MODULES may be set in the directory itself
            get_directory_property( _skip DIRECTORY ${SUBDIRECTORY} DEFINITION SKIPPED_MODULES )
            if ( _skip )
                set( SKIPPED_MODULES ${_skip} PARENT_SCOPE )
                set( MODULE_CONFIG_FILES "" )
            endif()
        endif()
        if ( SKIPPED_MODULES )
            return()
        endif()
    # ...otherwise, we look for a module.desc.
    elseif( EXISTS "${_mod_dir}/module.desc" )
        set( MODULES_DIR ${CMAKE_INSTALL_LIBDIR}/calamares/modules )
        set( MODULE_DESTINATION ${MODULES_DIR}/${_modulename} )

        # Read module.desc, check that the interface type is supported.
        #
        # _mod_enabled boolean if the module should be built (only if the interface is supported)
        # _mod_reason is a human-readable explanation why it isn't built
        # _mod_testing boolean if the module should be added to the loadmodule tests
        file(STRINGS "${_mod_dir}/module.desc" MODULE_INTERFACE REGEX "^interface")
        if ( MODULE_INTERFACE MATCHES "pythonqt" )
            message( FATAL_ERROR "PythonQt is no longer supported" )
            set( _mod_enabled OFF )
            set( _mod_reason "No PythonQt support" )
            set( _mod_testing OFF )
        elseif ( MODULE_INTERFACE MATCHES "python" )
            set( _mod_enabled ${Calamares_WITH_PYTHON} )
            set( _mod_reason "No Python support" )
            set( _mod_testing ON )  # Will check syntax and imports, at least
        elseif ( MODULE_INTERFACE MATCHES "qtplugin" )
            set( _mod_enabled OFF )
            set( _mod_reason "C++ modules must have a CMakeLists.txt instead" )
            set( _mod_testing OFF )
        elseif ( MODULE_INTERFACE MATCHES "process" )
            set( _mod_enabled ON )
            set( _mod_reason "" )
            set( _mod_testing OFF )
        else()
            set( _mod_enabled OFF )
            set( _mod_reason "Unknown module interface '${MODULE_INTERFACE}'" )
            set( _mod_testing OFF )
        endif()

        if ( _mod_enabled )
            # We glob all the files inside the subdirectory, and we make sure they are
            # synced with the bindir structure and installed.
            file( GLOB MODULE_FILES RELATIVE ${_mod_dir} "${SUBDIRECTORY}/*" )
            foreach( MODULE_FILE ${MODULE_FILES} )
                if( NOT IS_DIRECTORY ${_mod_dir}/${MODULE_FILE} )
                    configure_file( ${SUBDIRECTORY}/${MODULE_FILE} ${SUBDIRECTORY}/${MODULE_FILE} COPYONLY )

                    get_filename_component( FLEXT ${MODULE_FILE} EXT )
                    if( "${FLEXT}" STREQUAL ".conf" )
                        if( INSTALL_CONFIG )
                            install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                                    DESTINATION ${MODULE_DATA_DESTINATION} )
                        endif()
                        list( APPEND MODULE_CONFIG_FILES ${MODULE_FILE} )
                    else()
                        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                                 DESTINATION ${MODULE_DESTINATION} )
                    endif()
                endif()
            endforeach()

            message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${_modulename}${ColorReset}" )
            message( "   ${Green}TYPE:${ColorReset} jobmodule" )
            message( "   ${Green}MODULE_DESTINATION:${ColorReset} ${MODULE_DESTINATION}" )
            if( MODULE_CONFIG_FILES )
                if ( INSTALL_CONFIG )
                    set( _destination "${MODULE_DATA_DESTINATION}" )
                else()
                    set( _destination "[Build directory only]" )
                endif()
                message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${MODULE_CONFIG_FILES} => ${_destination}" )
            endif()
            message( "" )
            # We copy over the lang directory, if any
            if( IS_DIRECTORY "${_mod_dir}/lang" )
                install_calamares_gettext_translations(
                    ${SUBDIRECTORY}
                    SOURCE_DIR "${_mod_dir}/lang"
                    FILENAME ${SUBDIRECTORY}.mo
                    RENAME calamares-${SUBDIRECTORY}.mo
                )
            endif()
        else()
            # Module disabled due to missing dependencies / unsupported interface
            set( SKIPPED_MODULES "${SUBDIRECTORY} (${_mod_reason})" PARENT_SCOPE )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add module subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no CMakeLists.txt or module.desc." )
        message( "" )
    endif()

    # Check any config files for basic correctness
    if ( BUILD_TESTING AND MODULE_CONFIG_FILES )
        set( _count 0 )
        foreach( _config_file ${MODULE_CONFIG_FILES} )
            set( _count_str "-${_count}" )
            if ( _count EQUAL 0 )
                set( _count_str "" )
            endif()
            add_test(
                NAME config-${SUBDIRECTORY}${_count_str}
                COMMAND test_conf ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${_config_file} )
            math( EXPR _count "${_count} + 1" )
        endforeach()
    endif()

    # Adding general tests
    #
    # Add a check that the module can be loaded. Since this calls exec(), the module
    # may try to do things to the running system. Needs work to make that a
    # safe thing to do.
    #
    # If the module has a tests/ subdirectory with *.global and *.job
    # files (YAML files holding global and job-configurations for
    # testing purposes) then those files are used to drive additional
    # tests. The files must be numbered (starting from 1) for this to work;
    # 1.global and 1.job together make the configuration for test 1.
    #
    # If the module has a tests/CMakeLists.txt while it doesn't have its
    # own CMakeLists.txt (e.g. a Python module), then the subdirectory
    # for tests/ is added on its own.
    #
    if ( BUILD_TESTING AND _mod_enabled AND _mod_testing )
        add_test(
            NAME load-${SUBDIRECTORY}
            COMMAND loadmodule ${SUBDIRECTORY}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
        # Try it with the tests/ configurations shipped with the module
        set( _count 1 )
        set( _testdir ${_mod_dir}/tests )
        while ( EXISTS "${_testdir}/${_count}.global" OR EXISTS "${_testdir}/${_count}.job" )
            set( _dash_g "" )
            set( _dash_j "" )
            if ( EXISTS "${_testdir}/${_count}.global" )
                set( _dash_g -g ${_testdir}/${_count}.global )
            endif()
            if ( EXISTS "${_testdir}/${_count}.job" )
                set( _dash_j -j ${_testdir}/${_count}.job )
            endif()
            add_test(
                NAME load-${SUBDIRECTORY}-${_count}
                COMMAND loadmodule ${_dash_g} ${_dash_j} ${SUBDIRECTORY}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                )
            math( EXPR _count "${_count} + 1" )
        endwhile()
        if ( EXISTS ${_testdir}/CMakeTests.txt AND NOT EXISTS ${_mod_dir}/CMakeLists.txt )
            include( ${_testdir}/CMakeTests.txt )
        endif()
        if ( PYLINT_COMMAND AND MODULE_INTERFACE MATCHES "python" )
            # Python modules get an additional test via pylint; this
            # needs to run at top-level because the ci/libcalamares directory
            # contains API stubs.
            #
            # TODO: the entry point is assumed to be `main.py`, but that is
            #       configurable through module.desc
            add_test(
                NAME lint-${SUBDIRECTORY}
                COMMAND env PYTHONPATH=ci: ${PYLINT_COMMAND} -E ${_mod_dir}/main.py
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                )
        endif()
    endif()
endfunction()

function( calamares_add_module_subdirectory )
    set( SUBDIRECTORY ${ARGV0} )
    set( _ams_SKIP_LIST ${ARGV1} )

    set( SKIPPED_MODULES "" )
    _calamares_add_module_subdirectory_impl( ${SUBDIRECTORY} )
    if ( SKIPPED_MODULES )
        if ( _ams_SKIP_LIST )
            list( APPEND ${_ams_SKIP_LIST} "${SKIPPED_MODULES}" )
            set( ${_ams_SKIP_LIST} "${${_ams_SKIP_LIST}}" PARENT_SCOPE )
        else()
            set( SKIPPED_MODULES "${SKIPPED_MODULES}" PARENT_SCOPE )
        endif()
    endif()
endfunction()
