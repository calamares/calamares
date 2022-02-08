# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(tracking
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        TrackingJobs.cpp
        TrackingPage.cpp
        TrackingViewStep.cpp
    UI
        page_trackingstep.ui
    RESOURCES
        page_trackingstep.qrc
    SHARED_LIB
    LINK_LIBRARIES
        KF5::CoreAddons
)

calamares_add_test(trackingtest SOURCES Tests.cpp Config.cpp)
