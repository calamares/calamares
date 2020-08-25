# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin( netinstall
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        NetInstallViewStep.cpp
        NetInstallPage.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    UI
        page_netinst.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        Qt5::Network
        yamlcpp
    SHARED_LIB
)

calamares_add_test(
    netinstalltest
    SOURCES
        Tests.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    LIBRARIES
        Qt5::Gui
        yamlcpp
)

