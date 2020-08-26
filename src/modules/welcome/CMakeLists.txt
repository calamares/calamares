# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network )

find_package( LIBPARTED )
if ( LIBPARTED_FOUND )
    set( PARTMAN_SRC checker/partman_devices.c )
    set( CHECKER_LINK_LIBRARIES ${LIBPARTED_LIBRARY} )
else()
    set( PARTMAN_SRC )
    set( CHECKER_LINK_LIBRARIES )
    add_definitions( -DWITHOUT_LIBPARTED )
endif()

set( CHECKER_SOURCES
    checker/CheckerContainer.cpp
    checker/GeneralRequirements.cpp
    checker/ResultWidget.cpp
    checker/ResultsListWidget.cpp
    ${PARTMAN_SRC}
)

calamares_add_plugin( welcome
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${CHECKER_SOURCES}
        WelcomeViewStep.cpp
        Config.cpp
        Config.h
        WelcomePage.cpp
    UI
        WelcomePage.ui
    RESOURCES
        welcome.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CHECKER_LINK_LIBRARIES}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)
