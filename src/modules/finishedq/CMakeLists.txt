# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "finishedq (QML is not supported in this build)" )
    return()
endif()

find_package(Qt5 ${QT_VERSION} CONFIG COMPONENTS DBus Network)
if(NOT TARGET Qt5::DBus OR NOT TARGET Qt5::Network)
    calamares_skip_module( "finishedq (missing DBus or Network)" )
    return()
endif()

set(_finished ${CMAKE_CURRENT_SOURCE_DIR}/../finished)
include_directories(${_finished})

calamares_add_plugin(finishedq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        FinishedQmlViewStep.cpp
        ${_finished}/Config.cpp
    RESOURCES
        finishedq.qrc
    LINK_PRIVATE_LIBRARIES
        Qt5::DBus
    SHARED_LIB
)
