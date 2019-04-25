/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019 Adriaan de Groot <groot@kde.org>
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

#ifndef PARTUTILS_H
#define PARTUTILS_H

#include "OsproberEntry.h"
#include "utils/Units.h"
#include "utils/NamedSuffix.h"

// KPMcore
#include <kpmcore/fs/filesystem.h>

// Qt
#include <QString>

class PartitionCoreModule;
class Partition;

namespace PartUtils
{
using CalamaresUtils::MiBtoBytes;

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
class PartSize : public NamedSuffix<SizeUnit, SizeUnit::None>
{
public:
    PartSize() : NamedSuffix() { }
    PartSize( int v, unit_t u ) : NamedSuffix( v, u ) { }
    PartSize( const QString& );

    bool isValid() const
    {
        return ( unit() != SizeUnit::None ) && ( value() > 0 );
    }

    bool operator< ( const PartSize& other ) const;
    bool operator> ( const PartSize& other ) const;
    bool operator== ( const PartSize& other ) const;

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


/**
 * @brief Provides a nice human-readable name for @p candidate
 *
 * The most-specific human-readable name for the partition @p candidate
 * is returned (e.g. device name, or partition path). In the worst
 * case, a string representation of (void *)candidate is returned.
 */
QString convenienceName( const Partition* const candidate );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for replacing it with the new OS.
 * @param candidate the candidate partition to replace.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeReplaced( Partition* candidate );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param candidate the candidate partition to resize.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( Partition* candidate );

/**
 * @brief canBeReplaced checks whether the given Partition satisfies the criteria
 * for resizing (shrinking) it to make room for a new OS.
 * @param core the PartitionCoreModule instance.
 * @param partitionPath the device path of the candidate partition to resize.
 * @return true if the criteria are met, otherwise false.
 */
bool canBeResized( PartitionCoreModule* core, const QString& partitionPath );

/**
 * @brief runOsprober executes os-prober, parses the output and writes relevant
 * data to GlobalStorage.
 * @param core the PartitionCoreModule instance.
 * @return a list of os-prober entries, parsed.
 */
OsproberEntryList runOsprober( PartitionCoreModule* core );

/**
 * @brief Is this system EFI-enabled? Decides based on /sys/firmware/efi
 */
bool isEfiSystem();

/**
 * @brief Is the given @p partition bootable in EFI? Depending on
 * the partition table layout, this may mean different flags.
 */
bool isEfiBootable( const Partition* candidate );

/** @brief translate @p fsName into a recognized name and type
 *
 * Makes several attempts to translate the string into a
 * name that KPMCore will recognize.
 * The corresponding filesystem type is stored in @p fsType, and
 * its value is FileSystem::Unknown if @p fsName is not recognized.
 */
QString findFS( QString fsName, FileSystem::Type* fsType );

/**
 * @brief Convert a partition size to a sectors count.
 * @param size the partition size.
 * @param unit the partition size unit.
 * @param totalSectors the total number of sectors of the selected drive.
 * @param logicalSize the sector size, in bytes.
 * @return the number of sectors to be used for the given partition size.
 */
qint64 sizeToSectors( double size, SizeUnit unit, qint64 totalSectors, qint64 logicalSize );

constexpr qint64 alignBytesToBlockSize( qint64 bytes, qint64 blocksize )
{
    qint64 blocks = bytes / blocksize;

    if ( blocks * blocksize != bytes )
        ++blocks;
    return blocks * blocksize;
}

constexpr qint64 bytesToSectors( qint64 bytes, qint64 blocksize )
{
    return alignBytesToBlockSize( alignBytesToBlockSize( bytes, blocksize), MiBtoBytes(1ULL) ) / blocksize;
}

}

#endif // PARTUTILS_H
