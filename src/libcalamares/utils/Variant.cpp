/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2010-2011 Leo Franchi <lfranchi@kde.org>
 *   SPDX-FileCopyrightText: 2010-2012 Jeff Mitchell <jeff@tomahawk-player.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "Variant.h"

#include "Logger.h"

#include <QString>
#include <QVariantMap>

namespace CalamaresUtils
{
bool
getBool( const QVariantMap& map, const QString& key, bool d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Bool )
        {
            return v.toBool();
        }
    }
    return d;
}

QString
getString( const QVariantMap& map, const QString& key, const QString& d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::String )
        {
            return v.toString();
        }
    }
    return d;
}

QStringList
getStringList( const QVariantMap& map, const QString& key, const QStringList& d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::StringList )
        {
            return v.toStringList();
        }
    }
    return d;
}

qint64
getInteger( const QVariantMap& map, const QString& key, qint64 d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        return v.toString().toLongLong(nullptr, 0);
    }
    return d;
}

quint64
getUnsignedInteger( const QVariantMap& map, const QString& key, quint64 d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        return v.toString().toULongLong(nullptr, 0);
    }
    return d;
}

double
getDouble( const QVariantMap& map, const QString& key, double d )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Int )
        {
            return v.toInt();
        }
        else if ( v.type() == QVariant::Double )
        {
            return v.toDouble();
        }
    }
    return d;
}

QVariantMap
getSubMap( const QVariantMap& map, const QString& key, bool& success, const QVariantMap& d )
{
    success = false;
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Map )
        {
            success = true;
            return v.toMap();
        }
    }
    return d;
}

}  // namespace CalamaresUtils
