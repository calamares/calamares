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
        set( MODULE_DESTINATION ${MODULES_DIR}/${SUBDIRECTORY} )

        # Read module.desc, check that the interface type is supported.
        file(STRINGS "${_mod_dir}/module.desc" MODULE_INTERFACE REGEX "^interface")
        if ( MODULE_INTERFACE MATCHES "pythonqt" )
            set( _mod_enabled ${WITH_PYTHONQT} )
            set( _mod_reason "No PythonQt support" )
        elseif ( MODULE_INTERFACE MATCHES "python" )
            set( _mod_enabled ${WITH_PYTHON} )
            set( _mod_reason "No Python support" )
        else()
            set( _mod_enabled ON )
            set( _mod_reason "" )
        endif()

        if ( _mod_enabled )
            # We glob all the files inside the subdirectory, and we make sure they are
            # synced with the bindir structure and installed.
            file( GLOB MODULE_FILES RELATIVE ${_mod_dir} "${SUBDIRECTORY}/*" )
            foreach( MODULE_FILE ${MODULE_FILES} )
                if( NOT IS_DIRECTORY ${_mod_dir}/${MODULE_FILE} )
                    configure_file( ${SUBDIRECTORY}/${MODULE_FILE} ${SUBDIRECTORY}/${MODULE_FILE} COPYONLY )

                    get_filename_component( FLEXT ${MODULE_FILE} EXT )
                    if( "${FLEXT}" STREQUAL ".conf" AND INSTALL_CONFIG)
                        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                                 DESTINATION ${MODULE_DATA_DESTINATION} )
                        list( APPEND MODULE_CONFIG_FILES ${MODULE_FILE} )
                    else()
                        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                                 DESTINATION ${MODULE_DESTINATION} )
                    endif()
                endif()
            endforeach()

            message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${SUBDIRECTORY}${ColorReset}" )
            if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
                message( "   ${Green}TYPE:${ColorReset} jobmodule" )
                message( "   ${Green}MODULE_DESTINATION:${ColorReset} ${MODULE_DESTINATION}" )
                if( MODULE_CONFIG_FILES )
                    if ( INSTALL_CONFIG )
                        message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${MODULE_CONFIG_FILES} => ${MODULE_DATA_DESTINATION}" )
                    else()
                        message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${MODULE_CONFIG_FILES} => [Skipping installation]" )
                    endif()
                endif()
                message( "" )
            endif()
            # We copy over the lang directory, if any
            if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
                install_calamares_gettext_translations(
                    ${SUBDIRECTORY}
                    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang"
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
endfunction()
