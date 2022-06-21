# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
set(_extra_libraries "")
set(_extra_src "")

### OPTIONAL AppData XML support in PackageModel
#
#
# TODO:3.3:WITH->BUILD (this doesn't affect the ABI offered by Calamares)
option(WITH_APPDATA "Support appdata: items in PackageChooser (requires QtXml)" ON)
if(WITH_APPDATA)
    find_package(Qt5 COMPONENTS Xml)
    if(Qt5Xml_FOUND)
        add_definitions(-DHAVE_APPDATA)
        list(APPEND _extra_libraries Qt5::Xml)
        list(APPEND _extra_src ItemAppData.cpp)
    endif()
endif()

### OPTIONAL AppStream support in PackageModel
#
#
option(WITH_APPSTREAM "Support appstream: items in PackageChooser (requires libappstream-qt)" ON)
if(WITH_APPSTREAM)
    find_package(AppStreamQt)
    set_package_properties(
        AppStreamQt
        PROPERTIES
        DESCRIPTION "Support for AppStream (cache) data"
        URL "https://github.com/ximion/appstream"
        PURPOSE "AppStream provides package data"
        TYPE OPTIONAL
    )
    if(AppStreamQt_FOUND)
        add_definitions(-DHAVE_APPSTREAM)
        list(APPEND _extra_libraries AppStreamQt)
        list(APPEND _extra_src ItemAppStream.cpp)
    endif()
endif()

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

calamares_add_test(
    packagechoosertest
    GUI
    SOURCES Tests.cpp
    LIBRARIES calamares_viewmodule_packagechooser ${_extra_libraries}
)
