# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Finds KPMcore and consistently sets API flags based on the version.
#
# If KPMcore is not found, still create calamares::kpmcore interface
# library, which will add definition WITHOUT_KPMcore.
#
if(NOT TARGET calapmcore)
    find_package(${kfname}Config CONFIG)
    find_package(${kfname}I18n CONFIG)
    find_package(${kfname}WidgetsAddons CONFIG)

    if( WITH_QT6)
        find_package(KPMcore 24.01.75)
    else()
        find_package(KPMcore 20.04.0)
    endif()
    set_package_properties(
        KPMcore
        PROPERTIES
        URL "https://invent.kde.org/kde/kpmcore"
        DESCRIPTION "KDE Partitioning library"
        TYPE RECOMMENDED
        PURPOSE "For disk partitioning support"
    )

    # Create an internal Calamares interface to KPMcore
    # and give it a nice alias name. If kpmcore is not found,
    # then make a "no KPMcore" library.
    add_library(calapmcore INTERFACE)

    if(KPMcore_FOUND)
        find_package(${qtname} REQUIRED DBus) # Needed for KPMCore
        find_package(${kfname} REQUIRED I18n WidgetsAddons) # Needed for KPMCore

        target_link_libraries(calapmcore INTERFACE kpmcore ${qtname}::DBus ${kfname}::I18n ${kfname}::WidgetsAddons)
        target_include_directories(calapmcore INTERFACE ${KPMCORE_INCLUDE_DIR})
        # If there were KPMcore API variations, figure them out here
        # target_compile_definitions(calapmcore INTERFACE WITH_KPMcore)

        # Flag that this library has KPMcore support. A variable
        # set here has the wrong scope. ENV{} would be visible
        # everywhere but seems the wrong thing to do. Setting
        # properties on calapmcore requires a newer CMake than
        # Debian 11 has, so runs into support issues.
        add_library(calamares::kpmcore ALIAS calapmcore)
    else()
        target_compile_definitions(calapmcore INTERFACE WITHOUT_KPMcore)
    endif()
else()
    if(TARGET calamares::kpmcore)
        message(STATUS "KPMcore has already been found")
        set(KPMcore_FOUND TRUE)
    else()
        message(STATUS "KPMcore has been searched-for and not found")
        set(KPMcore_FOUND FALSE)
    endif()
endif()
