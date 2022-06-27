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
    find_package(KPMcore 20.04.0)
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
        find_package(Qt5 REQUIRED DBus) # Needed for KPMCore
        find_package(KF5 REQUIRED I18n WidgetsAddons) # Needed for KPMCore

        target_link_libraries(calapmcore INTERFACE kpmcore Qt5::DBus KF5::I18n KF5::WidgetsAddons)
        target_include_directories(calapmcore INTERFACE ${KPMCORE_INCLUDE_DIR})
        # If there were KPMcore API variations, figure them out here
        # target_compile_definitions(calapmcore INTERFACE WITH_KPMcore)
        set_target_properties(calapmcore PROPERTIES KPMcore_FOUND TRUE)
    else()
        target_compile_definitions(calapmcore INTERFACE WITHOUT_KPMcore)
        set_target_properties(calapmcore PROPERTIES KPMcore_FOUND FALSE)
    endif()

    add_library(calamares::kpmcore ALIAS calapmcore)
else()
    get_target_property(KPMcore_FOUND calapmcore KPMcore_FOUND)
    if(KPMcore_FOUND)
        message(STATUS "KPMcore has already been found")
        set(KPMcore_FOUND TRUE)
    else()
        message(STATUS "KPMcore has been searched-for and not found")
        set(KPMcore_FOUND FALSE)
    endif()
endif()
