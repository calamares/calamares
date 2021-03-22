# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# The variable SKIP_MODULES can be set to skip particular modules;
# individual modules can also decide they must be skipped (e.g. OS-specific
# modules, or ones with unmet dependencies). Collect the skipped modules
# in this list.
set( LIST_SKIPPED_MODULES "" )

include_directories(
    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_BINARY_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src/libcalamaresui
)

string( REPLACE " " ";" SKIP_LIST "${SKIP_MODULES}" )

file( GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*" )
list( SORT SUBDIRECTORIES )

foreach( SUBDIRECTORY ${SUBDIRECTORIES} )
    calamares_add_module_subdirectory( ${SUBDIRECTORY} LIST_SKIPPED_MODULES )
endforeach()

# TODO:3.3: Use FindPython3
if ( BUILD_TESTING AND BUILD_SCHEMA_TESTING AND PYTHONINTERP_FOUND AND PYTHON_EXECUTABLE )
    # The tests for each config file are independent of whether the
    # module is enabled or not: the config file should match its schema
    # regardless.
    foreach( SUBDIRECTORY ${SUBDIRECTORIES} )
        set( _schema_file "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${SUBDIRECTORY}.schema.yaml" )
        set( _conf_file "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${SUBDIRECTORY}.conf" )
        if ( EXISTS "${_schema_file}" AND EXISTS "${_conf_file}" )
            add_test(
                NAME validate-${SUBDIRECTORY}
                COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_SOURCE_DIR}/ci/configvalidator.py" "${_schema_file}" "${_conf_file}"
            )
        endif()
    endforeach()
endif()

