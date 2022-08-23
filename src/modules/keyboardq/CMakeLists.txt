# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "keyboardq (QML is not supported in this build)" )
    return()
endif()

set(_keyboard ${CMAKE_CURRENT_SOURCE_DIR}/../keyboard)

include_directories(${_keyboard})

calamares_add_plugin(keyboardq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        KeyboardQmlViewStep.cpp
        ${_keyboard}/Config.cpp
        ${_keyboard}/KeyboardLayoutModel.cpp
        ${_keyboard}/SetKeyboardLayoutJob.cpp
        ${_keyboard}/keyboardwidget/keyboardglobal.cpp
    RESOURCES
        keyboardq.qrc
    SHARED_LIB
)
