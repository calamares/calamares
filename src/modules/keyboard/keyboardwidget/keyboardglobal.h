/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QStringList>
#include <QList>
#include <QHash>
#include <QMap>
#include <QRegExp>
#include <QDebug>

#define XKB_FILE "/usr/share/X11/xkb/rules/base.lst"

class KeyboardGlobal
{
public:
    struct KeyboardInfo {
        QString description;
        QMap< QString, QString > variants;
    };

    using LayoutsMap = QMap< QString, KeyboardInfo >;

    static LayoutsMap getKeyboardLayouts();
    static QMap< QString, QString > getKeyboardModels();


private:
    static QMap< QString, QString > parseKeyboardModels(QString filepath);
    static LayoutsMap parseKeyboardLayouts(QString filepath);
};

#endif // KEYBOARDGLOBAL_H
