# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# This is a re-write of the welcome module using QML view steps
# instead of widgets.

if(NOT WITH_QML)
    calamares_skip_module( "welcomeq (QML is not supported in this build)" )
    return()
endif()

set(_welcome ${CMAKE_CURRENT_SOURCE_DIR}/../welcome)

include_directories(${_welcome})

# DUPLICATED WITH WELCOME MODULE
find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network)

find_package(LIBPARTED)
if(LIBPARTED_FOUND)
    set(PARTMAN_SRC ${_welcome}/checker/partman_devices.c)
    set(CHECKER_LINK_LIBRARIES ${LIBPARTED_LIBRARY})
else()
    set(PARTMAN_SRC)
    set(CHECKER_LINK_LIBRARIES)
    add_definitions(-DWITHOUT_LIBPARTED)
endif()

set(CHECKER_SOURCES ${_welcome}/checker/GeneralRequirements.cpp ${PARTMAN_SRC})

calamares_add_plugin(welcomeq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${CHECKER_SOURCES}
        WelcomeQmlViewStep.cpp
        ${_welcome}/Config.cpp
    RESOURCES
        welcomeq.qrc
    LINK_PRIVATE_LIBRARIES
        ${CHECKER_LINK_LIBRARIES}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)
