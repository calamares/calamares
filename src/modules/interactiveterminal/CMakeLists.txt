# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

set(kf5_ver 5.41)

find_package(KF5Service ${kf5_ver})
find_package(KF5Parts ${kf5_ver})
set_package_properties(KF5Service PROPERTIES PURPOSE "For finding KDE services at runtime")
set_package_properties(KF5Parts PROPERTIES PURPOSE "For finding KDE parts at runtime")

if(KF5Parts_FOUND AND KF5Service_FOUND)
    calamares_add_plugin(interactiveterminal
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            InteractiveTerminalViewStep.cpp
            InteractiveTerminalPage.cpp
        LINK_LIBRARIES
            KF5::Service
            KF5::Parts
        SHARED_LIB
    )
else()
    calamares_skip_module( "interactiveterminal (missing requirements)" )
endif()
