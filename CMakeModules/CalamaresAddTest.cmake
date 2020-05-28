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
# Support functions for building Calamares tests.
# This extends KDE's ECM tests with some custom patterns.
#
# calamares_add_test(
#   <NAME>
#   [GUI]
#   SOURCES <FILE..>
#   )

include( CMakeParseArguments )
include( CalamaresAutomoc )

function( calamares_add_test )
    # parse arguments (name needs to be saved before passing ARGN into the macro)
    set( NAME ${ARGV0} )
    set( options GUI )
    set( multiValueArgs SOURCES LIBRARIES DEFINITIONS )
    cmake_parse_arguments( TEST "${options}" "" "${multiValueArgs}" ${ARGN} )
    set( TEST_NAME ${NAME} )

    if( ECM_FOUND AND BUILD_TESTING )
        ecm_add_test(
            ${TEST_SOURCES}
            TEST_NAME
                ${TEST_NAME}
            LINK_LIBRARIES
                calamares
                ${TEST_LIBRARIES}
                Qt5::Core
                Qt5::Test
            )
        calamares_automoc( ${TEST_NAME} )
        target_compile_definitions( ${TEST_NAME} PRIVATE -DBUILD_AS_TEST="${CMAKE_CURRENT_SOURCE_DIR}"  ${TEST_DEFINITIONS} )
        if( TEST_GUI )
            target_link_libraries( ${TEST_NAME} calamaresui Qt5::Gui )
        endif()
    endif()
endfunction()
