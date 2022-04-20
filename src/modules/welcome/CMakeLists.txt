# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network)

find_package(LIBPARTED)
if(LIBPARTED_FOUND)
    set(PARTMAN_SRC checker/partman_devices.c)
    set(PARTMAN_LIB ${LIBPARTED_LIBRARY})
else()
    set(PARTMAN_SRC)
    set(PARTMAN_LIB)
    add_definitions(-DWITHOUT_LIBPARTED)
endif()

calamares_add_plugin(welcome
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        checker/CheckerContainer.cpp
        checker/GeneralRequirements.cpp
        checker/ResultDelegate.cpp
        checker/ResultsListWidget.cpp
        ${PARTMAN_SRC}
        WelcomeViewStep.cpp
        Config.cpp
        Config.h
        WelcomePage.cpp
    UI
        WelcomePage.ui
    RESOURCES
        welcome.qrc
    LINK_PRIVATE_LIBRARIES
        ${PARTMAN_LIB}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)

calamares_add_test(
    welcometest
    SOURCES checker/GeneralRequirements.cpp ${PARTMAN_SRC} Config.cpp Tests.cpp
    LIBRARIES ${PARTMAN_LIB} Qt5::DBus Qt5::Network Qt5::Widgets Calamares::calamaresui
)
