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
# Function and support code for adding a Calamares module (either a Qt / C++ plugin,
# or a Python module, or whatever) to the build.
#
include( CalamaresAddTranslations )

set( MODULE_DATA_DESTINATION share/calamares/modules )

# Convenience function to indicate that a module has been skipped
# (optionally also why). Call this in the module's CMakeLists.txt
macro( calamares_skip_module )
    set( SKIPPED_MODULES ${SKIPPED_MODULES} ${ARGV} PARENT_SCOPE )
endmacro()

function( calamares_explain_skipped_modules )
    if ( ARGN )
        message( "${ColorReset}-- Skipped modules:" )
        foreach( SUBDIRECTORY ${ARGN} )
            message( "${ColorReset}--   Skipped ${BoldRed}${SUBDIRECTORY}${ColorReset}." )
        endforeach()
        message( "" )
    endif()
endfunction()

function( calamares_add_module_subdirectory )
    set( SUBDIRECTORY ${ARGV0} )

    set( SKIPPED_MODULES )
    set( MODULE_CONFIG_FILES "" )

    set( _mod_dir "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}" )
    # If this subdirectory has a CMakeLists.txt, we add_subdirectory it...
    if( EXISTS "${_mod_dir}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
        file( GLOB MODULE_CONFIG_FILES RELATIVE ${_mod_dir} "${SUBDIRECTORY}/*.conf" )
        # Module has indicated it should be skipped, show that in
        # the calling CMakeLists (which is src/modules/CMakeLists.txt normally).
        if ( SKIPPED_MODULES )
            set( SKIPPED_MODULES ${SKIPPED_MODULES} PARENT_SCOPE )
            set( MODULE_CONFIG_FILES "" )
        endif()
    # ...otherwise, we look for a module.desc.
    elseif( EXISTS "${_mod_dir}/module.desc" )
        set( MODULES_DIR ${CMAKE_INSTALL_LIBDIR}/calamares/modules )
        # The module subdirectory may be given as a/b/c, but the module
        # needs to be installed as "c", so we split off any intermediate
        # directories.
        get_filename_component(_dirname "${SUBDIRECTORY}" DIRECTORY)
        if( _dirname )
            # Remove the dirname and any leftover leading /s
            string( REGEX REPLACE "^${_dirname}/*" "" _modulename "${SUBDIRECTORY}" )
            set( MODULE_DESTINATION ${MODULES_DIR}/${_modulename} )
        else()
            set( MODULE_DESTINATION ${MODULES_DIR}/${SUBDIRECTORY} )
        endif()

        # Read module.desc, check that the interface type is supported.
        #
        # _mod_enabled boolean if the module should be built (only if the interface is supported)
        # _mod_reason is a human-readable explanation why it isn't built
        # _mod_testing boolean if the module should be added to the loadmodule tests
        file(STRINGS "${_mod_dir}/module.desc" MODULE_INTERFACE REGEX "^interface")
        if ( MODULE_INTERFACE MATCHES "pythonqt" )
            set( _mod_enabled ${Calamares_WITH_PYTHONQT} )
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

            message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${SUBDIRECTORY}${ColorReset}" )
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

    # Check that the module can be loaded. Since this calls exec(), the module
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
    endif()
endfunction()
