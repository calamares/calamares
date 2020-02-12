/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include "GlobalStorage.h"
#include "JobQueue.h"

#include "utils/Logger.h"
#include "utils/Units.h"
#include "utils/Yaml.h"

#include <QFile>
#include <QJsonDocument>

using CalamaresUtils::operator""_MiB;

namespace Calamares
{

GlobalStorage::GlobalStorage()
    : QObject( nullptr )
{
}


bool
GlobalStorage::contains( const QString& key ) const
{
    return m.contains( key );
}


int
GlobalStorage::count() const
{
    return m.count();
}


void
GlobalStorage::insert( const QString& key, const QVariant& value )
{
    m.insert( key, value );
    emit changed();
}


QStringList
GlobalStorage::keys() const
{
    return m.keys();
}


int
GlobalStorage::remove( const QString& key )
{
    int nItems = m.remove( key );
    emit changed();
    return nItems;
}


QVariant
GlobalStorage::value( const QString& key ) const
{
    return m.value( key );
}

void
GlobalStorage::debugDump() const
{
    for ( auto it = m.cbegin(); it != m.cend(); ++it )
    {
        cDebug() << it.key() << '\t' << it.value();
    }
}

bool
GlobalStorage::save( const QString& filename )
{
    QFile f( filename );
    if ( !f.open( QFile::WriteOnly ) )
    {
        return false;
    }

    f.write( QJsonDocument::fromVariant( m ).toJson() );
    f.close();
    return true;
}

bool
GlobalStorage::load( const QString& filename )
{
    QFile f( filename );
    if ( !f.open( QFile::ReadOnly ) )
    {
        return false;
    }

    QJsonParseError e;
    QJsonDocument d = QJsonDocument::fromJson( f.read( 1_MiB ), &e );
    if ( d.isNull() )
    {
        cWarning() << filename << e.errorString();
    }
    else if ( !d.isObject() )
    {
        cWarning() << filename << "Not suitable JSON.";
    }
    else
    {
        auto map = d.toVariant().toMap();
        for ( auto i = map.constBegin(); i != map.constEnd(); ++i )
        {
            insert( i.key(), *i );
        }
        return true;
    }
    return false;
}

bool
GlobalStorage::saveYaml( const QString& filename )
{
    return CalamaresUtils::saveYaml( filename, m );
}

bool
GlobalStorage::loadYaml( const QString& filename )
{
    bool ok = false;
    auto gs = CalamaresUtils::loadYaml( filename, &ok );
    if ( ok )
    {
        m = gs;
    }
    return ok;
}


}  // namespace Calamares
