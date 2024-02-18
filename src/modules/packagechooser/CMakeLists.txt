# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(${qtname} COMPONENTS Core Gui Widgets REQUIRED)

### OPTIONAL AppData XML support in PackageModel
#
#
option(BUILD_APPDATA "Support appdata: items in PackageChooser (requires QtXml)" OFF)
if(BUILD_APPDATA)
    find_package(${qtname} REQUIRED COMPONENTS Xml)
endif()

### OPTIONAL AppStream support in PackageModel
#
#
include(AppStreamHelper)

calamares_add_plugin(packagechooser
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        PackageChooserPage.cpp
        PackageChooserViewStep.cpp
        PackageModel.cpp
    RESOURCES
        packagechooser.qrc
    UI
        page_package.ui
    SHARED_LIB
)

if(AppStreamQt_FOUND)
    target_link_libraries(${packagechooser_TARGET} PRIVATE calamares::appstreamqt)
    target_sources(${packagechooser_TARGET} PRIVATE ItemAppStream.cpp)
endif()

if(BUILD_APPDATA AND TARGET ${qtname}::Xml)
    target_compile_definitions(${packagechooser_TARGET} PRIVATE HAVE_APPDATA)
    target_link_libraries(${packagechooser_TARGET} PRIVATE ${qtname}::Xml)
    target_sources(${packagechooser_TARGET} PRIVATE ItemAppData.cpp)
endif()

calamares_add_test(
    packagechoosertest
    GUI
    SOURCES Tests.cpp
    LIBRARIES ${packagechooser_TARGET}
)
