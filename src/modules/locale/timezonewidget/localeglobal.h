/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#ifndef LOCALEGLOBAL_H
#define LOCALEGLOBAL_H

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

namespace CalamaresUtils
{
namespace Locale
{
class TZZone;
}
}  // namespace CalamaresUtils

class LocaleGlobal
{
public:
    struct Locale
    {
        QString description, locale;
    };

    static void init();
    static QHash< QString, QHash< QString, QList< LocaleGlobal::Locale > > > getLocales();

private:
    static QHash< QString, QHash< QString, QList< LocaleGlobal::Locale > > > locales;

    static void initLocales();
};

#endif  // LOCALEGLOBAL_H
