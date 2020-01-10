/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2013-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "Variant.h"

#include "Logger.h"

#include <QString>
#include <QVariantMap>

namespace CalamaresUtils
{
bool
getBool( const QVariantMap& map, const QString& key, bool d )
{
    bool result = d;
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Bool )
        {
            result = v.toBool();
        }
    }

    return result;
}

QString
getString( const QVariantMap& map, const QString& key )
{
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::String )
        {
            return v.toString();
        }
    }
    return QString();
}

qint64
getInteger( const QVariantMap& map, const QString& key, qint64 d )
{
    qint64 result = d;
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Int )
        {
            result = v.toInt();
        }
        else if ( v.type() == QVariant::LongLong )
        {
            result = v.toLongLong();
        }
    }

    return result;
}

double
getDouble( const QVariantMap& map, const QString& key, double d )
{
    double result = d;
    if ( map.contains( key ) )
    {
        auto v = map.value( key );
        if ( v.type() == QVariant::Int )
        {
            result = v.toInt();
        }
        else if ( v.type() == QVariant::Double )
        {
            result = v.toDouble();
        }
    }

    return result;
}

QVariantMap
getSubMap( const QVariantMap& map, const QString& key, bool& success )
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
    return QVariantMap();
}

}  // namespace CalamaresUtils
