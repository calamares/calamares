/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */


#include "partition/PartitionSize.h"
#include "utils/Logger.h"
#include "utils/Units.h"

namespace CalamaresUtils
{
namespace Partition
{

static const NamedEnumTable< SizeUnit >&
unitSuffixes()
{
    // *INDENT-OFF*
    // clang-format off
    static const NamedEnumTable< SizeUnit > names {
        { QStringLiteral( "%" ), SizeUnit::Percent },
        { QStringLiteral( "K" ), SizeUnit::KiB },
        { QStringLiteral( "KiB" ), SizeUnit::KiB },
        { QStringLiteral( "M" ), SizeUnit::MiB },
        { QStringLiteral( "MiB" ), SizeUnit::MiB },
        { QStringLiteral( "G" ), SizeUnit::GiB },
        { QStringLiteral( "GiB" ), SizeUnit::GiB },
        { QStringLiteral( "KB" ), SizeUnit::KB },
        { QStringLiteral( "MB" ), SizeUnit::MB },
        { QStringLiteral( "GB" ), SizeUnit::GB }
    };
    // clang-format on
    // *INDENT-ON*

    return names;
}

PartitionSize::PartitionSize( const QString& s )
    : NamedSuffix( unitSuffixes(), s )
{
    if ( ( unit() == SizeUnit::Percent ) && ( value() > 100 || value() < 0 ) )
    {
        cDebug() << "Percent value" << value() << "is not valid.";
        m_value = 0;
    }

    if ( m_unit == SizeUnit::None )
    {
        m_value = s.toLongLong();
        if ( m_value > 0 )
        {
            m_unit = SizeUnit::Byte;
        }
    }

    if ( m_value <= 0 )
    {
        m_value = 0;
        m_unit = SizeUnit::None;
    }
}

qint64
PartitionSize::toSectors( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
    {
        return -1;
    }
    if ( totalSectors < 1 || sectorSize < 1 )
    {
        return -1;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return -1;
    case SizeUnit::Percent:
        if ( value() == 100 )
        {
            return totalSectors;  // Common-case, avoid futzing around
        }
        else
        {
            return totalSectors * value() / 100;
        }
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return CalamaresUtils::bytesToSectors( toBytes(), sectorSize );
    }

    return -1;
}

qint64
PartitionSize::toBytes( qint64 totalSectors, qint64 sectorSize ) const
{
    if ( !isValid() )
    {
        return -1;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return -1;
    case SizeUnit::Percent:
        if ( totalSectors < 1 || sectorSize < 1 )
        {
            return -1;
        }
        if ( value() == 100 )
        {
            return totalSectors * sectorSize;  // Common-case, avoid futzing around
        }
        else
        {
            return totalSectors * value() / 100;
        }
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return toBytes();
    }
    __builtin_unreachable();
}

qint64
PartitionSize::toBytes( qint64 totalBytes ) const
{
    if ( !isValid() )
    {
        return -1;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return -1;
    case SizeUnit::Percent:
        if ( totalBytes < 1 )
        {
            return -1;
        }
        if ( value() == 100 )
        {
            return totalBytes;  // Common-case, avoid futzing around
        }
        else
        {
            return totalBytes * value() / 100;
        }
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return toBytes();
    }
    __builtin_unreachable();
}

qint64
PartitionSize::toBytes() const
{
    if ( !isValid() )
    {
        return -1;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
    case SizeUnit::Percent:
        return -1;
    case SizeUnit::Byte:
        return value();
    case SizeUnit::KB:
        return CalamaresUtils::KBtoBytes( static_cast< unsigned long long >( value() ) );
    case SizeUnit::KiB:
        return CalamaresUtils::KiBtoBytes( static_cast< unsigned long long >( value() ) );
    case SizeUnit::MB:
        return CalamaresUtils::MBtoBytes( static_cast< unsigned long long >( value() ) );
    case SizeUnit::MiB:
        return CalamaresUtils::MiBtoBytes( static_cast< unsigned long long >( value() ) );
    case SizeUnit::GB:
        return CalamaresUtils::GBtoBytes( static_cast< unsigned long long >( value() ) );
    case SizeUnit::GiB:
        return CalamaresUtils::GiBtoBytes( static_cast< unsigned long long >( value() ) );
    }
    __builtin_unreachable();
}

bool
PartitionSize::operator<( const PartitionSize& other ) const
{
    if ( !unitsComparable( m_unit, other.m_unit ) )
    {
        return false;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return false;
    case SizeUnit::Percent:
        return ( m_value < other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return ( toBytes() < other.toBytes() );
    }
    __builtin_unreachable();
}

bool
PartitionSize::operator>( const PartitionSize& other ) const
{
    if ( !unitsComparable( m_unit, other.m_unit ) )
    {
        return false;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return false;
    case SizeUnit::Percent:
        return ( m_value > other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return ( toBytes() > other.toBytes() );
    }
    __builtin_unreachable();
}

bool
PartitionSize::operator==( const PartitionSize& other ) const
{
    if ( !unitsComparable( m_unit, other.m_unit ) )
    {
        return false;
    }

    switch ( m_unit )
    {
    case SizeUnit::None:
        return false;
    case SizeUnit::Percent:
        return ( m_value == other.m_value );
    case SizeUnit::Byte:
    case SizeUnit::KB:
    case SizeUnit::KiB:
    case SizeUnit::MB:
    case SizeUnit::MiB:
    case SizeUnit::GB:
    case SizeUnit::GiB:
        return ( toBytes() == other.toBytes() );
    }
    __builtin_unreachable();
}

}  // namespace Partition
}  // namespace CalamaresUtils
