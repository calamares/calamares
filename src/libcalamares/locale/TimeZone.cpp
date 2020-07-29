/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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

#include "TimeZone.h"

#include "utils/Logger.h"
#include "utils/String.h"

#include <QFile>
#include <QStringList>
#include <QTextStream>

#include <cstring>

static const char TZ_DATA_FILE[] = "/usr/share/zoneinfo/zone.tab";

static double
getRightGeoLocation( QString str )
{
    double sign = 1, num = 0.00;

    // Determine sign
    if ( str.startsWith( '-' ) )
    {
        sign = -1;
        str.remove( 0, 1 );
    }
    else if ( str.startsWith( '+' ) )
    {
        str.remove( 0, 1 );
    }

    if ( str.length() == 4 || str.length() == 6 )
    {
        num = str.mid( 0, 2 ).toDouble() + str.mid( 2, 2 ).toDouble() / 60.0;
    }
    else if ( str.length() == 5 || str.length() == 7 )
    {
        num = str.mid( 0, 3 ).toDouble() + str.mid( 3, 2 ).toDouble() / 60.0;
    }

    return sign * num;
}


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

TZRegion::~TZRegion()
{
    qDeleteAll( m_zones );
}

const CStringPairList&
TZRegion::fromZoneTab()
{
    static CStringPairList zoneTab = TZRegion::fromFile( TZ_DATA_FILE );
    return zoneTab;
}

CStringPairList
TZRegion::fromFile( const char* fileName )
{
    CStringPairList model;

    QFile file( fileName );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        return model;
    }

    TZRegion* thisRegion = nullptr;
    QTextStream in( &file );
    while ( !in.atEnd() )
    {
        QString line = in.readLine().trimmed().split( '#', SplitKeepEmptyParts ).first().trimmed();
        if ( line.isEmpty() )
        {
            continue;
        }

        QStringList list = line.split( QRegExp( "[\t ]" ), SplitSkipEmptyParts );
        if ( list.size() < 3 )
        {
            continue;
        }

        QStringList timezoneParts = list.at( 2 ).split( '/', SplitSkipEmptyParts );
        if ( timezoneParts.size() < 2 )
        {
            continue;
        }

        QString region = timezoneParts.first().trimmed();
        if ( region.isEmpty() )
        {
            continue;
        }

        auto keyMatch = [&region]( const CStringPair* r ) { return r->key() == region; };
        auto it = std::find_if( model.begin(), model.end(), keyMatch );
        if ( it != model.end() )
        {
            thisRegion = dynamic_cast< TZRegion* >( *it );
        }
        else
        {
            thisRegion = new TZRegion( region.toUtf8().data() );
            model.append( thisRegion );
        }

        QString countryCode = list.at( 0 ).trimmed();
        if ( countryCode.size() != 2 )
        {
            continue;
        }

        timezoneParts.removeFirst();
        thisRegion->m_zones.append(
            new TZZone( region, timezoneParts.join( '/' ).toUtf8().constData(), countryCode, list.at( 1 ) ) );
    }

    auto sorter = []( const CStringPair* l, const CStringPair* r ) { return *l < *r; };
    std::sort( model.begin(), model.end(), sorter );
    for ( auto& it : model )
    {
        TZRegion* r = dynamic_cast< TZRegion* >( it );
        if ( r )
        {
            std::sort( r->m_zones.begin(), r->m_zones.end(), sorter );
        }
    }

    return model;
}

TZZone::TZZone( const QString& region, const char* zoneName, const QString& country, QString position )
    : CStringPair( zoneName )
    , m_region( region )
    , m_country( country )
{
    int cooSplitPos = position.indexOf( QRegExp( "[-+]" ), 1 );
    if ( cooSplitPos > 0 )
    {
        m_latitude = getRightGeoLocation( position.mid( 0, cooSplitPos ) );
        m_longitude = getRightGeoLocation( position.mid( cooSplitPos ) );
    }
}

QString
TZZone::tr() const
{
    // NOTE: context name must match what's used in zone-extractor.py
    return QObject::tr( m_human, "tz_names" );
}


CStringListModel::CStringListModel( CStringPairList l )
    : m_list( l )
{
}

void
CStringListModel::setList( CalamaresUtils::Locale::CStringPairList l )
{
    beginResetModel();
    m_list = l;
    endResetModel();
}

int
CStringListModel::rowCount( const QModelIndex& ) const
{
    return m_list.count();
}

QVariant
CStringListModel::data( const QModelIndex& index, int role ) const
{
    if ( ( role != Qt::DisplayRole ) && ( role != Qt::UserRole ) )
    {
        return QVariant();
    }

    if ( !index.isValid() )
    {
        return QVariant();
    }

    const auto* item = m_list.at( index.row() );
    return item ? ( role == Qt::DisplayRole ? item->tr() : item->key() ) : QVariant();
}

void
CStringListModel::setCurrentIndex( int index )
{
    if ( ( index < 0 ) || ( index >= m_list.count() ) )
    {
        return;
    }

    m_currentIndex = index;
    emit currentIndexChanged();
}

int
CStringListModel::currentIndex() const
{
    return m_currentIndex;
}

QHash< int, QByteArray >
CStringListModel::roleNames() const
{
    return { { Qt::DisplayRole, "label" }, { Qt::UserRole, "key" } };
}

const CStringPair*
CStringListModel::item( int index ) const
{
    if ( ( index < 0 ) || ( index >= m_list.count() ) )
    {
        return nullptr;
    }
    return m_list[ index ];
}

}  // namespace Locale
}  // namespace CalamaresUtils
