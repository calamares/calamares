# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(${kfname}Service ${KF_VERSION})
find_package(${kfname}Parts ${KF_VERSION})
set_package_properties(${kfname}Service PROPERTIES PURPOSE "For finding KDE services at runtime")
set_package_properties(${kfname}Parts PROPERTIES PURPOSE "For finding KDE parts at runtime")

if(${kfname}Parts_FOUND AND ${kfname}Service_FOUND)
    calamares_add_plugin(interactiveterminal
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            InteractiveTerminalViewStep.cpp
            InteractiveTerminalPage.cpp
        LINK_LIBRARIES
            ${kfname}::Service
            ${kfname}::Parts
        SHARED_LIB
    )
else()
    calamares_skip_module( "interactiveterminal (missing requirements)" )
endif()
