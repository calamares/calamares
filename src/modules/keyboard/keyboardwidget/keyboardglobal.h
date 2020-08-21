/* === This file is part of Calamares - <https://github.com/calamares> ===
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
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEYBOARDGLOBAL_H
#define KEYBOARDGLOBAL_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QHash>
#include <QList>
#include <QMap>
#include <QRegExp>
#include <QString>
#include <QStringList>
#include <QTextStream>

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

    static LayoutsMap getKeyboardLayouts();
    static ModelsMap getKeyboardModels();
};

#endif  // KEYBOARDGLOBAL_H
