# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "notesqml (QML is not supported in this build)" )
    return()
endif()

calamares_add_plugin(notesqml
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        NotesQmlViewStep.cpp
    RESOURCES
        notesqml.qrc
    SHARED_LIB
)
