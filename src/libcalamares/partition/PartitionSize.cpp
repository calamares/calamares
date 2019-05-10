/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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

#include "partition/PartitionSize.h"
#include "utils/Logger.h"
#include "utils/Units.h"

namespace Calamares
{

static const NamedEnumTable<SizeUnit>&
unitSuffixes()
{
    static const NamedEnumTable<SizeUnit> names{
        { QStringLiteral( "%" ), SizeUnit::Percent },
        { QStringLiteral( "K" ), SizeUnit::KiB },
        { QStringLiteral( "KiB" ), SizeUnit::KiB },
        { QStringLiteral( "M" ), SizeUnit::MiB },
        { QStringLiteral( "MiB" ), SizeUnit::MiB },
        { QStringLiteral( "G" ), SizeUnit::GiB },
        { QStringLiteral( "GiB" ), SizeUnit::GiB }
    };

    return names;
}

PartitionSize::PartitionSize( const QString& s )
    : NamedSuffix( unitSuffixes(), s )
{
    if ( ( unit() == unit_t::Percent ) && ( value() > 100 || value() < 0 ) )
    {
        cDebug() << "Percent value" << value() << "is not valid.";
        m_value = 0;
    }

    if ( m_unit == unit_t::None )
    {
        m_value = s.toInt();
        if ( m_value > 0 )
            m_unit = unit_t::Byte;
    }

    if ( m_value <= 0 )
    {
        m_value = 0;
        m_unit = unit_t::None;
    }
}

qint64
PartitionSize::toSectors( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
        return -1;
    if ( totalSectors < 1 || sectorSize < 1 )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( value() == 100 )
            return totalSectors;  // Common-case, avoid futzing around
        else
            return totalSectors * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return CalamaresUtils::bytesToSectors ( toBytes(), sectorSize );
    }

    return -1;
}

qint64
PartitionSize::toBytes( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( totalSectors < 1 || sectorSize < 1 )
            return -1;
        if ( value() == 100 )
            return totalSectors * sectorSize;  // Common-case, avoid futzing around
        else
            return totalSectors * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return toBytes();
    }

    // notreached
    return -1;
}

qint64
PartitionSize::toBytes( qint64 totalBytes ) const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::None:
        return -1;
    case unit_t::Percent:
        if ( totalBytes < 1 )
            return -1;
        if ( value() == 100 )
            return totalBytes;  // Common-case, avoid futzing around
        else
            return totalBytes * value() / 100;
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return toBytes();
    }

    // notreached
    return -1;
}

qint64
PartitionSize::toBytes() const
{
    if ( !isValid() )
        return -1;

    switch ( m_unit )
    {
    case unit_t::Byte:
        return value();
    case unit_t::KiB:
        return CalamaresUtils::KiBtoBytes( static_cast<unsigned long long>( value() ) );
    case unit_t::MiB:
        return CalamaresUtils::MiBtoBytes( static_cast<unsigned long long>( value() ) );
    case unit_t::GiB:
        return CalamaresUtils::GiBtoBytes( static_cast<unsigned long long>( value() ) );
    default:
        break;
    }

    // Reached only when unit is Percent or None
    return -1;
}

bool
PartitionSize::operator< ( const PartitionSize& other ) const
{
    if ( ( m_unit == unit_t::None    || other.m_unit == unit_t::None    ) ||
         ( m_unit == unit_t::Percent && other.m_unit != unit_t::Percent ) ||
         ( m_unit != unit_t::Percent && other.m_unit == unit_t::Percent ) )
        return false;

    switch ( m_unit )
    {
    case unit_t::Percent:
        return ( m_value < other.m_value );
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return ( toBytes() < other.toBytes () );
    }

    return false;
}

bool
PartitionSize::operator> ( const PartitionSize& other ) const
{
    if ( ( m_unit == unit_t::None    || other.m_unit == unit_t::None    ) ||
         ( m_unit == unit_t::Percent && other.m_unit != unit_t::Percent ) ||
         ( m_unit != unit_t::Percent && other.m_unit == unit_t::Percent ) )
        return false;

    switch ( m_unit )
    {
    case unit_t::Percent:
        return ( m_value > other.m_value );
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return ( toBytes() > other.toBytes () );
    }

    return false;
}

bool
PartitionSize::operator== ( const PartitionSize& other ) const
{
    if ( ( m_unit == unit_t::None    || other.m_unit == unit_t::None    ) ||
         ( m_unit == unit_t::Percent && other.m_unit != unit_t::Percent ) ||
         ( m_unit != unit_t::Percent && other.m_unit == unit_t::Percent ) )
        return false;

    switch ( m_unit )
    {
    case unit_t::Percent:
        return ( m_value == other.m_value );
    case unit_t::Byte:
    case unit_t::KiB:
    case unit_t::MiB:
    case unit_t::GiB:
        return ( toBytes() == other.toBytes () );
    }

    return false;
}

} // namespace Calamares
