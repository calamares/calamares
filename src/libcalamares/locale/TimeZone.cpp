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

#include "locale/TranslatableString.h"
#include "utils/Logger.h"
#include "utils/String.h"

#include <QFile>
#include <QString>

static const char TZ_DATA_FILE[] = "/usr/share/zoneinfo/zone.tab";

namespace CalamaresUtils
{
namespace Locale
{

/** @brief Turns a string longitude or latitude notation into a double
 *
 * This handles strings like "+4230+00131" from zone.tab,
 * which is degrees-and-minutes notation, and + means north or east.
 */
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


TimeZoneData::TimeZoneData( const QString& region,
                            const QString& zone,
                            const QString& country,
                            double latitude,
                            double longitude )
    : TranslatableString( zone )
    , m_region( region )
    , m_country( country )
    , m_latitude( latitude )
    , m_longitude( longitude )
{
}

QString
TimeZoneData::tr() const
{
    // NOTE: context name must match what's used in zone-extractor.py
    return QObject::tr( m_human, "tz_names" );
}


class RegionData : public TranslatableString
{
public:
    using TranslatableString::TranslatableString;
    QString tr() const override;
};

QString
RegionData::tr() const
{
    // NOTE: context name must match what's used in zone-extractor.py
    return QObject::tr( m_human, "tz_regions" );
}

static void
loadTZData( QVector< RegionData >& regions, QVector< TimeZoneData* >& zones )
{
    QFile file( TZ_DATA_FILE );
    if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
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

            QString countryCode = list.at( 0 ).trimmed();
            if ( countryCode.size() != 2 )
            {
                continue;
            }

            timezoneParts.removeFirst();
            QString zone = timezoneParts.join( '/' );
            if ( zone.length() < 2 )
            {
                continue;
            }

            QString position = list.at( 1 );
            int cooSplitPos = position.indexOf( QRegExp( "[-+]" ), 1 );
            double latitude;
            double longitude;
            if ( cooSplitPos > 0 )
            {
                latitude = getRightGeoLocation( position.mid( 0, cooSplitPos ) );
                longitude = getRightGeoLocation( position.mid( cooSplitPos ) );
            }
            else
            {
                continue;
            }

            // Now we have region, zone, country, lat and longitude
            RegionData r( region );
            if ( regions.indexOf( r ) < 0 )
            {
                regions.append( std::move( r ) );
            }
            zones.append( new TimeZoneData( region, zone, countryCode, latitude, longitude ) );
        }
    }
}


struct Private
{
    QVector< RegionData > m_regions;
    QVector< TimeZoneData* > m_zones;

    Private()
    {
        m_regions.reserve( 12 );  // reasonable guess
        m_zones.reserve( 452 );  // wc -l /usr/share/zoneinfo/zone.tab

        loadTZData( m_regions, m_zones );
    }
};

static Private*
privateInstance()
{
    static Private* s_p = new Private;
    return s_p;
}

RegionsModel::RegionsModel( QObject* parent )
    : QAbstractListModel( parent )
    , m_private( privateInstance() )
{
}

RegionsModel::~RegionsModel() {}

int
RegionsModel::rowCount( const QModelIndex& ) const
{
    return m_private->m_regions.count();
}

QVariant
RegionsModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || index.row() < 0 || index.row() >= m_private->m_regions.count() )
    {
        return QVariant();
    }

    const auto& region = m_private->m_regions[ index.row() ];
    if ( role == NameRole )
    {
        return region.tr();
    }
    if ( role == KeyRole )
    {
        return region.key();
    }
    return QVariant();
}

QHash< int, QByteArray >
RegionsModel::roleNames() const
{
    return { { NameRole, "name" }, { KeyRole, "key" } };
}


ZonesModel::ZonesModel( QObject* parent )
    : QAbstractListModel( parent )
    , m_private( privateInstance() )
{
}

ZonesModel::~ZonesModel() {}

int
ZonesModel::rowCount( const QModelIndex& ) const
{
    return m_private->m_zones.count();
}

QVariant
ZonesModel::data( const QModelIndex& index, int role ) const
{
    if ( !index.isValid() || index.row() < 0 || index.row() >= m_private->m_zones.count() )
    {
        return QVariant();
    }

    const auto* zone = m_private->m_zones[ index.row() ];
    switch ( role )
    {
    case NameRole:
        return zone->tr();
    case KeyRole:
        return zone->key();
    case RegionRole:
        return zone->region();
    default:
        return QVariant();
    }
}

QHash< int, QByteArray >
ZonesModel::roleNames() const
{
    return { { NameRole, "name" }, { KeyRole, "key" } };
}

const TimeZoneData*
ZonesModel::find( const QString& region, const QString& zone ) const
{
    for ( const auto* p : m_private->m_zones )
    {
        if ( p->region() == region && p->zone() == zone )
        {
            return p;
        }
    }
    return nullptr;
}

ZonesModel::Iterator::operator bool() const
{
    return 0 <= m_index && m_index < m_p->m_zones.count();
}

const TimeZoneData* ZonesModel::Iterator::operator*() const
{
    if ( *this )
    {
        return m_p->m_zones[ m_index ];
    }
    return nullptr;
}

RegionalZonesModel::RegionalZonesModel( CalamaresUtils::Locale::ZonesModel* source, QObject* parent )
    : QSortFilterProxyModel( parent )
    , m_private( privateInstance() )
{
    setSourceModel( source );
}

RegionalZonesModel::~RegionalZonesModel() {}

void
RegionalZonesModel::setRegion( const QString& r )
{
    if ( r != m_region )
    {
        m_region = r;
        invalidateFilter();
        emit regionChanged( r );
    }
}

bool
RegionalZonesModel::filterAcceptsRow( int sourceRow, const QModelIndex& ) const
{
    if ( m_region.isEmpty() )
    {
        return true;
    }

    if ( sourceRow < 0 || sourceRow >= m_private->m_zones.count() )
    {
        return false;
    }

    const auto& zone = m_private->m_zones[ sourceRow ];
    return ( zone->m_region == m_region );
}


}  // namespace Locale
}  // namespace CalamaresUtils
