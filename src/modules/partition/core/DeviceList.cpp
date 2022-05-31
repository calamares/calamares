/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "DeviceList.h"

#include "partition/PartitionIterator.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"

#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QProcess>

using CalamaresUtils::Partition::PartitionIterator;

namespace PartUtils
{

/**
 * Does the given @p device contain the root filesystem? This is true if
 * the device contains a partition which is currently mounted at / .
 */
static bool
hasRootPartition( Device* device )
{
    for ( auto it = PartitionIterator::begin( device ); it != PartitionIterator::end( device ); ++it )
        if ( ( *it )->mountPoint() == "/" )
        {
            return true;
        }
    return false;
}

/** @brief Check if @p path holds an iso9660 filesystem
 *
 * The @p path should point to a device; blkid is used to check the FS type.
 */
static bool
blkIdCheckIso9660( const QString& path )
{
    // If blkid fails, there's no output, but we don't care
    auto r = CalamaresUtils::System::runCommand( { "blkid", path }, std::chrono::seconds( 30 ) );
    return r.getOutput().contains( "iso9660" );
}

/// @brief Convenience to check if @p partition holds an iso9660 filesystem
static bool
blkIdCheckIso9660P( const Partition* partition )
{
    return blkIdCheckIso9660( partition->partitionPath() );
}

/** @brief Check if the @p device is an iso9660 device
 *
 * An iso9660 device is **probably** a CD-ROM. If the device holds an
 * iso9660 FS, or any of its partitions do, then we call it an iso9660 device.
 */
static bool
isIso9660( const Device* device )
{
    const QString path = device->deviceNode();
    if ( path.isEmpty() )
    {
        return false;
    }
    if ( blkIdCheckIso9660( path ) )
    {
        return true;
    }

    if ( device->partitionTable() && !device->partitionTable()->children().isEmpty() )
    {
        const auto& p = device->partitionTable()->children();
        return std::any_of( p.cbegin(), p.cend(), blkIdCheckIso9660P );
    }
    return false;
}

static inline bool
isZRam( const Device* device )
{
    const QString path = device->deviceNode();
    return path.startsWith( "/dev/zram" );
}

static inline bool
isFloppyDrive( const Device* device )
{
    const QString path = device->deviceNode();
    return path.startsWith( "/dev/fd" ) || path.startsWith( "/dev/floppy" );
}

static inline QDebug&
operator<<( QDebug& s, QList< Device* >::iterator& it )
{
    s << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
    return s;
}

using DeviceList = QList< Device* >;

static inline DeviceList::iterator
erase( DeviceList& l, DeviceList::iterator& it )
{
    Device* p = *it;
    auto r = l.erase( it );
    delete p;
    return r;
}

QList< Device* >
getDevices( DeviceType which )
{
    CoreBackend* backend = CoreBackendManager::self()->backend();
    if ( !backend )
    {
        cWarning() << "No KPM backend found.";
        return {};
    }
    DeviceList devices = backend->scanDevices( /* not includeReadOnly, not includeLoopback */ ScanFlag( 0 ) );

    /* The list of devices is cleaned up for use:
     *  - some devices can **never** be used (e.g. floppies, nullptr)
     *  - some devices can be used if unsafe mode is on, but not in normal operation
     * Two lambda's are defined,
     *  - removeInAllModes()
     *  - removeInSafeMode()
     * To handle the difference.
     */
#ifdef DEBUG_PARTITION_UNSAFE
    cWarning() << "Allowing unsafe partitioning choices." << devices.count() << "candidates.";
#ifdef DEBUG_PARTITION_BAIL_OUT
    cDebug() << Logger::SubEntry << "unsafe partitioning has been lamed, and will fail.";
#endif

    // Unsafe partitioning
    auto removeInAllModes = []( DeviceList& l, DeviceList::iterator& it ) { return erase( l, it ); };
    auto removeInSafeMode = []( DeviceList&, DeviceList::iterator& it ) { return ++it; };
#else
    // Safe partitioning
    auto removeInAllModes = []( DeviceList& l, DeviceList::iterator& it ) { return erase( l, it ); };
    auto& removeInSafeMode = removeInAllModes;
#endif

    cDebug() << "Removing unsuitable devices:" << devices.count() << "candidates.";

    bool writableOnly = ( which == DeviceType::WritableOnly );
    // Remove the device which contains / from the list
    for ( DeviceList::iterator it = devices.begin(); it != devices.end(); )
    {
        if ( !( *it ) )
        {
            cDebug() << Logger::SubEntry << "Skipping nullptr device";
            it = removeInAllModes( devices, it );
        }
        else if ( isZRam( *it ) )
        {
            cDebug() << Logger::SubEntry << "Removing zram" << it;
            it = removeInAllModes( devices, it );
        }
        else if ( isFloppyDrive( ( *it ) ) )
        {
            cDebug() << Logger::SubEntry << "Removing floppy disk" << it;
            it = removeInAllModes( devices, it );
        }
        else if ( writableOnly && hasRootPartition( *it ) )
        {
            cDebug() << Logger::SubEntry << "Removing device with root filesystem (/) on it" << it;
            it = removeInSafeMode( devices, it );
        }
        else if ( writableOnly && isIso9660( *it ) )
        {
            cDebug() << Logger::SubEntry << "Removing device with iso9660 filesystem (probably a CD) on it" << it;
            it = removeInSafeMode( devices, it );
        }
        else
        {
            ++it;
        }
    }
    cDebug() << Logger::SubEntry << "there are" << devices.count() << "devices left.";
    return devices;
}

}  // namespace PartUtils
