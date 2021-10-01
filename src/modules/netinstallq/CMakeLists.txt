# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if( NOT WITH_QML )
    calamares_skip_module( "netinstallq (QML is not supported in this build)" )
    return()
endif()

find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED Core )

# Add optional libraries here
set( USER_EXTRA_LIB )

# find_package(Qt5 COMPONENTS Test REQUIRED)

calamares_add_plugin( netinstallq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        LoaderQueue.cpp
        NetInstallQmlViewStep.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    RESOURCES
        netinstallq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${_extra_libraries}
        # Qt5::Test
    SHARED_LIB
)

calamares_add_test(
    netinstallqtest
    SOURCES
        Tests.cpp
        Config.cpp
        LoaderQueue.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    LIBRARIES
        Qt5::Gui
)

