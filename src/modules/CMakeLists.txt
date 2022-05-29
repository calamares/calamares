# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# The variable SKIP_MODULES can be set to skip particular modules;
# individual modules can also decide they must be skipped (e.g. OS-specific
# modules, or ones with unmet dependencies). Collect the skipped modules
# in this list.
set(LIST_SKIPPED_MODULES "")

include_directories(
    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_BINARY_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src/libcalamaresui
)

string(REPLACE " " ";" SKIP_LIST "${SKIP_MODULES}")

file(GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
list(SORT SUBDIRECTORIES)

foreach(SUBDIRECTORY ${SUBDIRECTORIES})
    calamares_add_module_subdirectory( ${SUBDIRECTORY} LIST_SKIPPED_MODULES )
endforeach()

if(BUILD_TESTING AND BUILD_SCHEMA_TESTING AND Python_Interpreter_FOUND)
    # The tests for each config file are independent of whether the
    # module is enabled or not: the config file should match its schema
    # regardless.
    foreach(SUBDIRECTORY ${SUBDIRECTORIES})
        set(_schema_file "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${SUBDIRECTORY}.schema.yaml")
        # Collect config files from the module-directory and from a tests/ subdir,
        # using the same mechanism to find those test-config-files as function
        # calamares_add_module_subdirectory() would do.
        set(_conf_files "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${SUBDIRECTORY}.conf")
        set(_count 1)
        set(_testdir "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/tests")
        while(EXISTS "${_testdir}/${_count}.global" OR EXISTS "${_testdir}/${_count}.job")
            if(EXISTS "${_testdir}/${_count}.job")
                list(APPEND _conf_files "${_testdir}/${_count}.job")
            endif()
            math(EXPR _count "${_count} + 1")
        endwhile()

        if(EXISTS "${_schema_file}")
            foreach(_conf_file ${_conf_files})
                if(EXISTS ${_conf_file})
                    get_filename_component(_conf_base "${_conf_file}" NAME_WE)
                    add_test(
                        NAME validate-${SUBDIRECTORY}-${_conf_base}
                        COMMAND
                            ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/ci/configvalidator.py" "${_schema_file}"
                            "${_conf_file}"
                    )
                endif()
            endforeach()
        endif()
    endforeach()
endif()
