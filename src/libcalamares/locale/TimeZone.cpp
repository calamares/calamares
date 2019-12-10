/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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

#include "TimeZone.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <cstring>

static const char TZ_DATA_FILE[] = "/usr/share/zoneinfo/zone.tab";

namespace CalamaresUtils
{
namespace Locale
{


CStringPair::CStringPair( CStringPair&& t )
    : m_human( nullptr )
    , m_key()
{
    // My pointers are initialized to nullptr
    std::swap( m_human, t.m_human );
    std::swap( m_key, t.m_key );
}

CStringPair::CStringPair( const CStringPair& t )
    : m_human( t.m_human ? strdup( t.m_human ) : nullptr )
    , m_key( t.m_key )
{
}

/** @brief Massage an identifier into a human-readable form
 *
 * Makes a copy of @p s, caller must free() it.
 */
static char*
munge( const char* s )
{
    char* t = strdup( s );
    if ( !t )
    {
        return nullptr;
    }

    // replace("_"," ") in the Python script
    char* p = t;
    while ( *p )
    {
        if ( ( *p ) == '_' )
        {
            *p = ' ';
        }
        ++p;
    }

    return t;
}

CStringPair::CStringPair( const char* s1 )
    : m_human( s1 ? munge( s1 ) : nullptr )
    , m_key( s1 ? QString( s1 ) : QString() )
{
}


CStringPair::~CStringPair()
{
    free( m_human );
}


QString
TZRegion::tr() const
{
    // NOTE: context name must match what's used in zone-extractor.py
    return QObject::tr( m_human, "tz_regions" );
}

QString
TZZone::tr() const
{
    // NOTE: context name must match what's used in zone-extractor.py
    return QObject::tr( m_human, "tz_names" );
}

TZRegionModel::TZRegionModel()
{

    QFile file( TZ_DATA_FILE );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return;
    }

    QStringList regions;

    QTextStream in( &file );
    while ( !in.atEnd() )
    {
        QString line = in.readLine().trimmed().split( '#', QString::KeepEmptyParts ).first().trimmed();
        if ( line.isEmpty() )
        {
            continue;
        }

        QStringList list = line.split( QRegExp( "[\t ]" ), QString::SkipEmptyParts );
        if ( list.size() < 3 )
        {
            continue;
        }

        QStringList timezoneParts = list.at( 2 ).split( '/', QString::SkipEmptyParts );
        if ( timezoneParts.size() < 2 )
        {
            continue;
        }

        QString region = timezoneParts.first().trimmed();
        ;
        if ( region.isEmpty() )
        {
            continue;
        }

        if ( !regions.contains( region ) )
        {
            regions.append( region );
        }
    }
    regions.sort();

    m_regions.reserve( regions.length() );
    for ( int i = 0; i < regions.length(); ++i )
    {
        m_regions.append( TZRegion( regions[ i ].toUtf8().data() ) );
    }
}

TZRegionModel::~TZRegionModel() {}

int
TZRegionModel::rowCount( const QModelIndex& parent ) const
{
    return m_regions.count();
}

QVariant
TZRegionModel::data( const QModelIndex& index, int role ) const
{
    if ( ( role != LabelRole ) && ( role != Qt::UserRole ) )
    {
        return QVariant();
    }

    if ( !index.isValid() )
    {
        return QVariant();
    }

    const TZRegion& region = m_regions.at( index.row() );
    return role == LabelRole ? region.tr() : region.key();
}

const TZRegion&
TZRegionModel::region( int index ) const
{
    if ( ( index < 0 ) || ( index >= m_regions.count() ) )
    {
        index = 0;
    }
    return m_regions[ index ];
}

}  // namespace Locale
}  // namespace CalamaresUtils
