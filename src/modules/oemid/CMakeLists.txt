# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(oemid
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        IDJob.cpp
        OEMViewStep.cpp
    UI
        OEMPage.ui
    LINK_PRIVATE_LIBRARIES
        Qt5::Widgets
    SHARED_LIB
)
