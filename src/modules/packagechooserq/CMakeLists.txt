# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "packagechooserq (QML is not supported in this build)" )
    return()
endif()

find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED Core)

# Add optional libraries here
set(USER_EXTRA_LIB)

# include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../packagechooser )
set(_packagechooser ${CMAKE_CURRENT_SOURCE_DIR}/../packagechooser)
include_directories(${_packagechooser})

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
        list(APPEND _extra_src ${_packagechooser}/ItemAppData.cpp)
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
        list(APPEND _extra_src ${_packagechooser}/ItemAppStream.cpp)
    endif()
endif()

calamares_add_plugin(packagechooserq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PackageChooserQmlViewStep.cpp
        ${_packagechooser}/Config.cpp
        ${_packagechooser}/PackageModel.cpp
        ${_extra_src}
    RESOURCES
        packagechooserq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${_extra_libraries}
    SHARED_LIB
)
