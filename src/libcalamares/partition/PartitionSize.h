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

#ifndef PARTITION_PARTITIONSIZE_H
#define PARTITION_PARTITIONSIZE_H

#include "utils/NamedSuffix.h"
#include "utils/Units.h"

// Qt
#include <QString>

namespace CalamaresUtils
{
namespace Partition
{

enum class SizeUnit
{
    None,
    Percent,
    Byte,
    KB,
    KiB,
    MB,
    MiB,
    GB,
    GiB
};

/** @brief Partition size expressions
 *
 * Sizes can be specified in bytes, KiB, MiB, GiB or percent (of
 * the available drive space are on). This class handles parsing
 * of such strings from the config file.
 */
class PartitionSize : public NamedSuffix< SizeUnit, SizeUnit::None >
{
public:
    PartitionSize()
        : NamedSuffix()
    {
    }
    PartitionSize( int v, SizeUnit u )
        : NamedSuffix( v, u )
    {
    }
    PartitionSize( const QString& );

    bool isValid() const { return ( unit() != SizeUnit::None ) && ( value() > 0 ); }

    bool operator<( const PartitionSize& other ) const;
    bool operator>( const PartitionSize& other ) const;
    bool operator==( const PartitionSize& other ) const;

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
     * It will return -1 in any other case. Note that 0KiB and 0MiB and
     * 0GiB are considered **invalid** sizes and return -1.
     *
     * @return  the size in bytes, or -1 if it cannot be calculated.
     */
    qint64 toBytes() const;

    /** @brief Are the units comparable?
     *
     * None units cannot be compared with anything. Percentages can
     * be compared with each other, and all the explicit sizes (KiB, ...)
     * can be compared with each other.
     */
    static constexpr bool unitsComparable( const SizeUnit u1, const SizeUnit u2 )
    {
        return !( ( u1 == SizeUnit::None || u2 == SizeUnit::None )
                  || ( u1 == SizeUnit::Percent && u2 != SizeUnit::Percent )
                  || ( u1 != SizeUnit::Percent && u2 == SizeUnit::Percent ) );
    }
};

}  // namespace Partition
}  // namespace CalamaresUtils

#endif  // PARTITION_PARTITIONSIZE_H
