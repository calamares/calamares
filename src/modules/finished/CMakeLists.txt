# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network)

include_directories(${PROJECT_BINARY_DIR}/src/libcalamaresui)

calamares_add_plugin(finished
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        FinishedViewStep.cpp
        FinishedPage.cpp
    UI
        FinishedPage.ui
    LINK_PRIVATE_LIBRARIES
        Qt5::DBus
    SHARED_LIB
)
