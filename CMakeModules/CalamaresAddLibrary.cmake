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
# Support functions for building plugins.
#
# Usage:
#
# calamares_add_library(
#   library-name
#   EXPORT_MACRO macro-name
#   TARGET_TYPE <STATIC|MODULE|...>
#   EXPORT export-name
#   VERSION version
#   SOVERSION version
#   INSTALL_BINDIR dir
#   RESOURCES resource-file
#   SOURCES source-file...
#   UI ui-file...
#   LINK_LIBRARIES lib...
#   LINK_PRIVATE_LIBRARIES lib...
#   COMPILE_DEFINITIONS def...
#   [NO_INSTALL]
#   [NO_VERSION]
# )
#
# The COMPILE_DEFINITIONS are set on the resulting module with a suitable
# flag (i.e. `-D`) so only state the name (optionally, also the value)
# without a `-D` prefixed to it. Pass in a CMake list as needed.
include( CMakeParseArguments )
include( CalamaresAutomoc )

function(calamares_add_library)
    # parse arguments (name needs to be saved before passing ARGN into the macro)
    set(NAME ${ARGV0})
    set(options NO_INSTALL NO_VERSION)
    set(oneValueArgs NAME EXPORT_MACRO TARGET_TYPE EXPORT VERSION SOVERSION INSTALL_BINDIR RESOURCES)
    set(multiValueArgs SOURCES UI LINK_LIBRARIES LINK_PRIVATE_LIBRARIES COMPILE_DEFINITIONS)
    cmake_parse_arguments(LIBRARY "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    set(LIBRARY_NAME ${NAME})

    set(target ${LIBRARY_NAME})

    # qt stuff
    include_directories(${CMAKE_CURRENT_LIST_DIR})
    include_directories(${CMAKE_CURRENT_BINARY_DIR})

    # add resources from current dir
    if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${LIBRARY_RESOURCES}")
        qt5_add_resources(LIBRARY_RC_SOURCES "${LIBRARY_RESOURCES}")
        list(APPEND LIBRARY_SOURCES ${LIBRARY_RC_SOURCES})
        unset(LIBRARY_RC_SOURCES)
    endif()

    # add target
    if(LIBRARY_TARGET_TYPE STREQUAL "STATIC")
        add_library(${target} STATIC ${LIBRARY_SOURCES})
    elseif(LIBRARY_TARGET_TYPE STREQUAL "MODULE")
        add_library(${target} MODULE ${LIBRARY_SOURCES})
    else() # default
        add_library(${target} SHARED ${LIBRARY_SOURCES})
    endif()

    calamares_automoc(${target})
    if(LIBRARY_UI)
        calamares_autouic(${target} ${LIBRARY_UI})
    endif()

    if(LIBRARY_EXPORT_MACRO)
        set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS ${LIBRARY_EXPORT_MACRO})
    endif()

    if(LIBRARY_COMPILE_DEFINITIONS)
        set( _lib_definitions "${LIBRARY_EXPORT_MACRO}" ${LIBRARY_COMPILE_DEFINITIONS} )
        set_target_properties(${target} PROPERTIES COMPILE_DEFINITIONS "${_lib_definitions}")
    endif()

    # add link targets
    target_link_libraries(${target}
        LINK_PUBLIC ${Calamares_LIBRARIES}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
    )
    if(LIBRARY_LINK_LIBRARIES)
        target_link_libraries(${target} LINK_PUBLIC ${LIBRARY_LINK_LIBRARIES})
    endif()
    if(LIBRARY_LINK_PRIVATE_LIBRARIES)
        target_link_libraries(${target} LINK_PRIVATE ${LIBRARY_LINK_PRIVATE_LIBRARIES})
    endif()

    # add soversion
    if(NOT LIBRARY_NO_VERSION)
        set_target_properties(${target} PROPERTIES VERSION ${LIBRARY_VERSION})

        if(NOT LIBRARY_SOVERSION)
            set(LIBRARY_SOVERSION ${LIBRARY_VERSION})
        endif()

        set_target_properties(${target} PROPERTIES SOVERSION ${LIBRARY_SOVERSION})
    endif()


    if(NOT LIBRARY_INSTALL_BINDIR)
        set(LIBRARY_INSTALL_BINDIR "${CMAKE_INSTALL_BINDIR}")
        set(LIBRARY_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}")
    else()
        set(LIBRARY_INSTALL_LIBDIR "${LIBRARY_INSTALL_BINDIR}")
    endif()

    # make installation optional, maybe useful for dummy plugins one day
    if(NOT LIBRARY_NO_INSTALL)
        include(GNUInstallDirs)
        if(NOT LIBRARY_EXPORT)
            install( TARGETS ${target}
                RUNTIME DESTINATION ${LIBRARY_INSTALL_BINDIR}
                LIBRARY DESTINATION ${LIBRARY_INSTALL_LIBDIR}
                ARCHIVE DESTINATION ${LIBRARY_INSTALL_LIBDIR}
            )
        else()
            install( TARGETS ${target}
                EXPORT ${LIBRARY_EXPORT}
                RUNTIME DESTINATION ${LIBRARY_INSTALL_BINDIR}
                LIBRARY DESTINATION ${LIBRARY_INSTALL_LIBDIR}
                ARCHIVE DESTINATION ${LIBRARY_INSTALL_LIBDIR}
            )
        endif()
    endif()
endfunction()
