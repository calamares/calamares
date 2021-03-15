/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "GlobalStorage.h"

#include "utils/Logger.h"
#include "utils/Units.h"
#include "utils/Yaml.h"

#include <QFile>
#include <QJsonDocument>
#include <QMutexLocker>

using namespace CalamaresUtils::Units;

namespace Calamares
{

class GlobalStorage::ReadLock : public QMutexLocker
{
public:
    ReadLock( const GlobalStorage* gs )
        : QMutexLocker( &gs->m_mutex )
    {
    }
};

class GlobalStorage::WriteLock : public QMutexLocker
{
public:
    WriteLock( GlobalStorage* gs )
        : QMutexLocker( &gs->m_mutex )
        , m_gs( gs )
    {
    }
    ~WriteLock() { m_gs->changed(); }

    GlobalStorage* m_gs;
};

GlobalStorage::GlobalStorage( QObject* parent )
    : QObject( parent )
{
}


bool
GlobalStorage::contains( const QString& key ) const
{
    ReadLock l( this );
    return m.contains( key );
}


int
GlobalStorage::count() const
{
    ReadLock l( this );
    return m.count();
}


void
GlobalStorage::insert( const QString& key, const QVariant& value )
{
    WriteLock l( this );
    m.insert( key, value );
}


QStringList
GlobalStorage::keys() const
{
    ReadLock l( this );
    return m.keys();
}


int
GlobalStorage::remove( const QString& key )
{
    WriteLock l( this );
    int nItems = m.remove( key );
    return nItems;
}


QVariant
GlobalStorage::value( const QString& key ) const
{
    ReadLock l( this );
    return m.value( key );
}

void
GlobalStorage::debugDump() const
{
    ReadLock l( this );
    cDebug() << "GlobalStorage" << Logger::Pointer( this ) << m.count() << "items";
    for ( auto it = m.cbegin(); it != m.cend(); ++it )
    {
        cDebug() << Logger::SubEntry << it.key() << '\t' << it.value();
    }
}

bool
GlobalStorage::saveJson( const QString& filename ) const
{
    ReadLock l( this );
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
GlobalStorage::loadJson( const QString& filename )
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
        WriteLock l( this );
        // Do **not** use method insert() here, because it would
        //   recursively lock the mutex, leading to deadlock. Also,
        //   that would emit changed() for each key.
        auto map = d.toVariant().toMap();
        for ( auto i = map.constBegin(); i != map.constEnd(); ++i )
        {
            m.insert( i.key(), *i );
        }
        return true;
    }
    return false;
}

bool
GlobalStorage::saveYaml( const QString& filename ) const
{
    ReadLock l( this );
    return CalamaresUtils::saveYaml( filename, m );
}

bool
GlobalStorage::loadYaml( const QString& filename )
{
    bool ok = false;
    auto map = CalamaresUtils::loadYaml( filename, &ok );
    if ( ok )
    {
        WriteLock l( this );
        // Do **not** use method insert() here, because it would
        //   recursively lock the mutex, leading to deadlock. Also,
        //   that would emit changed() for each key.
        for ( auto i = map.constBegin(); i != map.constEnd(); ++i )
        {
            m.insert( i.key(), *i );
        }
        return true;
    }
    return false;
}


}  // namespace Calamares
