# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(${qtname} COMPONENTS Core Gui Widgets REQUIRED)
set(_extra_libraries "")
set(_extra_src "")

### OPTIONAL AppData XML support in PackageModel
#
#
option(BUILD_APPDATA "Support appdata: items in PackageChooser (requires QtXml)" OFF)
if(BUILD_APPDATA)
    find_package(${qtname} REQUIRED COMPONENTS Xml)
    if(TARGET ${qtname}::Xml)
        add_definitions(-DHAVE_APPDATA)
        list(APPEND _extra_libraries ${qtname}::Xml)
        list(APPEND _extra_src ItemAppData.cpp)
    endif()
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
        ${_extra_src}
    RESOURCES
        packagechooser.qrc
    UI
        page_package.ui
    LINK_PRIVATE_LIBRARIES
        ${_extra_libraries}
    SHARED_LIB
)

if(AppStreamQt_FOUND)
    target_link_libraries(calamares_viewmodule_packagechooser PRIVATE calamares::appstreamqt)
    target_sources(calamares_viewmodule_packagechooser PRIVATE ItemAppStream.cpp)
endif()

calamares_add_test(
    packagechoosertest
    GUI
    SOURCES Tests.cpp
    LIBRARIES calamares_viewmodule_packagechooser ${_extra_libraries}
)
