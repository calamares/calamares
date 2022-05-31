# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Calamares is Free Software: see the License-Identifier above.
#
#
###
#
# Support functions for building Calamares tests.
# This extends KDE's ECM tests with some custom patterns.
#
# calamares_add_test(
#   <NAME>
#   [GUI]
#   [RESOURCES FILE]
#   SOURCES <FILE..>
#   )

include(CMakeParseArguments)
include(CalamaresAutomoc)

function(calamares_add_test name)
    set(options GUI)
    set(oneValueArgs RESOURCES)
    set(multiValueArgs SOURCES LIBRARIES DEFINITIONS)
    cmake_parse_arguments(TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(TEST_NAME ${name})

    if(ECM_FOUND AND BUILD_TESTING)
        ecm_add_test(
            ${TEST_SOURCES} ${TEST_RESOURCES}
            TEST_NAME
                ${TEST_NAME}
            LINK_LIBRARIES
                Calamares::calamares
                ${TEST_LIBRARIES}
                Qt5::Core
                Qt5::Test
        )
        calamares_automoc( ${TEST_NAME} )
        # We specifically pass in the source directory of the test-being-
        # compiled, so that it can find test-files in that source dir.
        target_compile_definitions(
            ${TEST_NAME}
            PRIVATE -DBUILD_AS_TEST="${CMAKE_CURRENT_SOURCE_DIR}" ${TEST_DEFINITIONS}
        )
        if(TEST_GUI)
            target_link_libraries(${TEST_NAME} Calamares::calamaresui Qt5::Gui)
        endif()
        if(TEST_RESOURCES)
            calamares_autorcc( ${TEST_NAME} ${TEST_RESOURCES} )
        endif()
    endif()
endfunction()
