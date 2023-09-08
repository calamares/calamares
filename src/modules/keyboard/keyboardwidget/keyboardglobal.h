/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017 2019, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef KEYBOARDGLOBAL_H
#define KEYBOARDGLOBAL_H

#include <QMap>
#include <QString>

class KeyboardGlobal
{
public:
    struct KeyboardInfo
    {
        QString description;
        QMap< QString, QString > variants;
    };

    using LayoutsMap = QMap< QString, KeyboardInfo >;
    using ModelsMap = QMap< QString, QString >;
    using GroupsMap = QMap< QString, QString >;

    static LayoutsMap getKeyboardLayouts();
    static ModelsMap getKeyboardModels();
    static GroupsMap getKeyboardGroups();
};

#endif  // KEYBOARDGLOBAL_H
