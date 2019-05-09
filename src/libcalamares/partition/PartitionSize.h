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

#ifndef PARTITION_PARTITIONSIZE_H
#define PARTITION_PARTITIONSIZE_H

#include "utils/Units.h"
#include "utils/NamedSuffix.h"

// Qt
#include <QString>

namespace Calamares
{

enum class SizeUnit
{
    None,
    Percent,
    Byte,
    KiB,
    MiB,
    GiB
};

/** @brief Partition size expressions
 *
 * Sizes can be specified in bytes, KiB, MiB, GiB or percent (of
 * the available drive space are on). This class handles parsing
 * of such strings from the config file.
 */
class PartitionSize : public NamedSuffix<SizeUnit, SizeUnit::None>
{
public:
    PartitionSize() : NamedSuffix() { }
    PartitionSize( int v, unit_t u ) : NamedSuffix( v, u ) { }
    PartitionSize( const QString& );

    bool isValid() const
    {
        return ( unit() != SizeUnit::None ) && ( value() > 0 );
    }

    bool operator< ( const PartitionSize& other ) const;
    bool operator> ( const PartitionSize& other ) const;
    bool operator== ( const PartitionSize& other ) const;

    /** @brief Convert the size to the number of sectors @p totalSectors .
     *
     * Each sector has size @p sectorSize, for converting sizes in Bytes,
     * KiB, MiB or GiB to sector counts.
     *
     * @return  the number of sectors needed, or -1 for invalid sizes.
     */
    qint64 toSectors( qint64 totalSectors, qint64 sectorSize ) const;

    /** @brief Convert the size to bytes.
     *
     * The device's sectors count @p totalSectors and sector size
     * @p sectoreSize are used to calculated the total size, which
     * is then used to calculate the size when using Percent.
     *
     * @return  the size in bytes, or -1 for invalid sizes.
     */
    qint64 toBytes( qint64 totalSectors, qint64 sectorSize ) const;

    /** @brief Convert the size to bytes.
     *
     * Total size @p totalBytes is needed for sizes in Percent. This
     * parameter is unused in any other case.
     *
     * @return  the size in bytes, or -1 for invalid sizes.
     */
    qint64 toBytes( qint64 totalBytes ) const;

    /** @brief Convert the size to bytes.
     *
     * This method is only valid for sizes in Bytes, KiB, MiB or GiB.
     * It will return -1 in any other case.
     *
     * @return  the size in bytes, or -1 if it cannot be calculated.
     */
    qint64 toBytes() const;
};

} // namespace Calamares

#endif // PARTITION_PARTITIONSIZE_H
