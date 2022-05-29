# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "summaryq (QML is not supported in this build)" )
    return()
endif()

set(_summary ${CMAKE_CURRENT_SOURCE_DIR}/../summary)
include_directories(${_summary})

calamares_add_plugin(summaryq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        SummaryQmlViewStep.cpp
        ${_summary}/Config.cpp
    UI
    RESOURCES
        summaryq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
