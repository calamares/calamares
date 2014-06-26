/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>

#include <CalaPM.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>
#include <backend/corebackenddevice.h>
#include <backend/corebackendpartition.h>
#include <backend/corebackendpartitiontable.h>
#include <core/device.h>
#include <fs/filesystem.h>
#include <fs/ext4.h>
#include <fs/linuxswap.h>
#include <core/partition.h>
#include <core/partitiontable.h>
#include <util/report.h>

#include <iostream>
using namespace std;

static const char* SCRATCH_DEVICE_NAME = "/dev/sdb";

static ostream& operator<<( ostream& out, const QString& s )
{
    return out << qPrintable( s );
}

void dumpChildren( const PartitionNode* parent, int depth )
{
    QString prefix( depth, ' ' );
    for ( const auto& partition : parent->children() )
    {
        cout << prefix + "- " + partition->partitionPath() << endl;
        cout << prefix + "  fs: " + partition->fileSystem().name() << endl;
        cout << prefix + "  mount point: " + partition->mountPoint() << endl;
        dumpChildren( partition, depth + 2 );
    }
}

void showInfo( CoreBackend* backend )
{
    QList<Device*> devices = backend->scanDevices();
    cout << devices.count() << " device(s)\n";
    for ( auto device : devices )
    {
        cout << "\n# Device: " << device->name() << endl;
        cout << "node: " << device->deviceNode() << endl;
        cout << "capacity: " << ( device->capacity() / 1024 / 1024 / 1024 ) << endl;

        PartitionNode* parent = device->partitionTable();
        dumpChildren( parent, 0 );
    }
    qDeleteAll( devices );
}

void wipe( CoreBackend* backend )
{
    Report report( 0 );

    QScopedPointer<Device> device( backend->scanDevice( SCRATCH_DEVICE_NAME ) );
    Q_ASSERT( device.data() );

    QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( device->deviceNode() ) );
    Q_ASSERT( backendDevice.data() );

    PartitionTable* table = device->partitionTable();
    Q_ASSERT( table );
    bool ok = backendDevice->createPartitionTable( report, *table );
    if ( !ok )
    {
        cerr << "Failed to recreate partition table\n";
    }
    cerr << report.toText() << endl;
}

bool createPartition( CoreBackend* backend, Report* report, Device* device, PartitionNode* parent, FileSystem* fs, PartitionTable::Flags flags = PartitionTable::FlagNone )
{
    QScopedPointer<CoreBackendDevice> backendDevice( backend->openDevice( device->deviceNode() ) );
    Q_ASSERT( backendDevice.data() );

    QScopedPointer<Partition> partition( new Partition( parent, *device, PartitionRole( PartitionRole::Primary ),
                                         fs, fs->firstSector(), fs->lastSector(), QString() /* path */
                                                      ) );

    QScopedPointer<CoreBackendPartitionTable> backendPartitionTable( backendDevice->openPartitionTable() );
    Q_ASSERT( backendPartitionTable );

    cout << "Creating partition\n";
    QString partitionPath = backendPartitionTable->createPartition( *report, *partition );
    if ( partitionPath.isEmpty() )
    {
        cerr << "Failed to create partition\n";
        return false;
    }
    cout << "Partition created at " << partitionPath << endl;
    backendPartitionTable->commit();

    // Create filesystem
    cout << "Creating filesystem\n";
    if ( !fs->create( *report, partitionPath ) )
    {
        cerr << "Failed to create filesystem\n";
        return false;
    }

    cout << "Updating partition table\n";
    if ( !backendPartitionTable->setPartitionSystemType( *report, *partition ) )
    {
        cerr << "Failed to update partition table\n";
        return false;
    }

    if ( flags != PartitionTable::FlagNone )
    {
        QScopedPointer<CoreBackendPartition> backendPartition( backendPartitionTable->getPartitionBySector( partition->firstSector() ) );
        Q_ASSERT( backendPartition );
        for ( auto flag : PartitionTable::flagList() )
        {
            if ( !backendPartition->setFlag( *report, flag, true ) )
            {
                cerr << "Failed to set flag " << flag << endl;
                return false;
            }
        }
    }

    backendPartitionTable->commit();
    return true;
}

void createPartitions( CoreBackend* backend )
{
    Report report( 0 );

    QScopedPointer<Device> device( backend->scanDevice( SCRATCH_DEVICE_NAME ) );
    Q_ASSERT( device.data() );

    PartitionTable* table = device->partitionTable();
    Q_ASSERT( table );

    const int SWAP_SIZE = 200 * 1024 * 1024;

    qint64 rootStart = table->firstUsable();
    qint64 rootEnd = table->lastUsable() - SWAP_SIZE / device->logicalSectorSize();
    cout << "sectors for /: " << rootStart << " - " << rootEnd << endl;
    FileSystem* fs = new FS::ext4::ext4( rootStart, rootEnd, 0, "Calamares" );

    if ( !createPartition( backend, &report, device.data(), table, fs, PartitionTable::FlagBoot ) )
    {
        cerr << report.toText() << endl;
        return;
    }

    qint64 swapStart = rootEnd + 1;
    qint64 swapEnd = table->lastUsable();
    cout << "sectors for swap: " << swapStart << " - " << swapEnd << endl;
    fs = new FS::linuxswap::linuxswap( swapStart, swapEnd, 0, "swap" );
    if ( !createPartition( backend, &report, device.data(), table, fs ) )
    {
        cerr << report.toText() << endl;
        return;
    }
}

int main( int argc, char** argv )
{
    QCoreApplication app( argc, argv );

    if ( !CalaPM::init() )
    {
        return 1;
    }
    CoreBackend* backend = CoreBackendManager::self()->backend();
    Q_ASSERT( backend );

    QString cmd( argv[1] );
    if ( cmd == "info" )
    {
        showInfo( backend );
    }
    else if ( cmd == "wipe" )
    {
        wipe( backend );
    }
    else if ( cmd == "partitions" )
    {
        createPartitions( backend );
    }
    else
    {
        cerr << "Unknown command " << cmd << endl;
        return 1;
    }
    return 0;
}
