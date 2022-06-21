# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(keyboard
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        KeyboardViewStep.cpp
        KeyboardPage.cpp
        KeyboardLayoutModel.cpp
        SetKeyboardLayoutJob.cpp
        keyboardwidget/keyboardglobal.cpp
        keyboardwidget/keyboardpreview.cpp
    UI
        KeyboardPage.ui
    RESOURCES
        keyboard.qrc
    SHARED_LIB
)

calamares_add_test(keyboardtest SOURCES Tests.cpp SetKeyboardLayoutJob.cpp RESOURCES keyboard.qrc)
