# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(netinstall
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        groupstreeview.cpp
        LoaderQueue.cpp
        NetInstallViewStep.cpp
        NetInstallPage.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    UI
        page_netinst.ui
    LINK_PRIVATE_LIBRARIES
        ${qtname}::Network
    SHARED_LIB
)

if(TARGET ${kfname}::CoreAddons)
    calamares_add_test(
        netinstalltest
        SOURCES Tests.cpp Config.cpp LoaderQueue.cpp PackageTreeItem.cpp PackageModel.cpp
        LIBRARIES ${qtname}::Gui ${qtname}::Network ${kfname}::CoreAddons
    )
endif()
