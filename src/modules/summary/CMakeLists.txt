# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( summary
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        SummaryViewStep.cpp
        SummaryPage.cpp
    UI
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
    NO_CONFIG
)
