/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Based on the SetPartFlagsJob class from KDE Partition Manager,
 *   Copyright 2008, 2010, Volker Lanz <vl@fidra.de>
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

#include "SetPartitionFlagsJob.h"

#include "utils/Logger.h"

#include <kpmcore/core/partition.h>
#include <kpmcore/backend/corebackend.h>
#include <kpmcore/backend/corebackenddevice.h>
#include <kpmcore/backend/corebackendmanager.h>
#include <kpmcore/backend/corebackendpartition.h>
#include <kpmcore/backend/corebackendpartitiontable.h>
#include <kpmcore/core/device.h>
#include <kpmcore/util/report.h>

SetPartFlagsJob::SetPartFlagsJob( Device* device,
                                            Partition* partition,
                                            PartitionTable::Flags flags )
    : PartitionJob( partition )
    , m_device( device )
    , m_flags( flags )
{}


QString
SetPartFlagsJob::prettyName() const
{
    if ( !partition()->partitionPath().isEmpty() )
        return tr( "Set flags on partition %1." ).arg( partition()->partitionPath() );

    if ( !partition()->fileSystem().name().isEmpty() )
        return tr( "Set flags on %1MB %2 partition." )
                .arg( partition()->capacity() /1024 /1024)
                .arg( partition()->fileSystem().name() );

    return tr( "Set flags on new partition." );
}


QString
SetPartFlagsJob::prettyDescription() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
            return tr( "Clear flags on partition <strong>%1</strong>." )
                    .arg( partition()->partitionPath() );

        if ( !partition()->fileSystem().name().isEmpty() )
            return tr( "Clear flags on %1MB <strong>%2</strong> partition." )
                    .arg( partition()->capacity() /1024 /1024)
                    .arg( partition()->fileSystem().name() );

        return tr( "Clear flags on new partition." );
    }

    if ( !partition()->partitionPath().isEmpty() )
        return tr( "Flag partition <strong>%1</strong> as "
                   "<strong>%2</strong>." )
                .arg( partition()->partitionPath() )
                .arg( flagsList.join( ", " ) );

    if ( !partition()->fileSystem().name().isEmpty() )
        return tr( "Flag %1MB <strong>%2</strong> partition as "
                   "<strong>%3</strong>." )
                .arg( partition()->capacity() /1024 /1024)
                .arg( partition()->fileSystem().name() )
                .arg( flagsList.join( ", " ) );

    return tr( "Flag new partition as <strong>%1</strong>." )
                .arg( flagsList.join( ", " ) );
}


QString
SetPartFlagsJob::prettyStatusMessage() const
{
    QStringList flagsList = PartitionTable::flagNames( m_flags );
    if ( flagsList.count() == 0 )
    {
        if ( !partition()->partitionPath().isEmpty() )
            return tr( "Clearing flags on partition <strong>%1</strong>." )
                    .arg( partition()->partitionPath() );

        if ( !partition()->fileSystem().name().isEmpty() )
            return tr( "Clearing flags on %1MB <strong>%2</strong> partition." )
                    .arg( partition()->capacity() /1024 /1024)
                    .arg( partition()->fileSystem().name() );

        return tr( "Clearing flags on new partition." );
    }

    if ( !partition()->partitionPath().isEmpty() )
        return tr( "Setting flags <strong>%2</strong> on partition "
                   "<strong>%1</strong>." )
                .arg( partition()->partitionPath() )
                .arg( flagsList.join( ", " ) );

    if ( !partition()->fileSystem().name().isEmpty() )
        return tr( "Setting flags <strong>%3</strong> on "
                   "%1MB <strong>%2</strong> partition." )
                .arg( partition()->capacity() /1024 /1024)
                .arg( partition()->fileSystem().name() )
                .arg( flagsList.join( ", " ) );

    return tr( "Setting flags <strong>%1</strong> on new partition." )
                .arg( flagsList.join( ", " ) );
}


Calamares::JobResult
SetPartFlagsJob::exec()
{
    PartitionTable::Flags oldFlags = partition()->availableFlags();
    if ( oldFlags == m_flags )
        return Calamares::JobResult::ok();

    CoreBackend* backend = CoreBackendManager::self()->backend();

    QString errorMessage = tr( "The installer failed to set flags on partition %1." )
                           .arg( m_partition->partitionPath() );

    QScopedPointer< CoreBackendDevice > backendDevice( backend->openDevice( m_device->deviceNode() ) );
    if ( !backendDevice.data() )
    {
        return Calamares::JobResult::error(
                   errorMessage,
                   tr( "Could not open device '%1'." ).arg( m_device->deviceNode() )
               );
    }

    QScopedPointer< CoreBackendPartitionTable > backendPartitionTable( backendDevice->openPartitionTable() );
    if ( !backendPartitionTable.data() )
    {
        return Calamares::JobResult::error(
                   errorMessage,
                   tr( "Could not open partition table on device '%1'." ).arg( m_device->deviceNode() )
               );
    }

    QScopedPointer< CoreBackendPartition > backendPartition(
            ( partition()->roles().has( PartitionRole::Extended ) )
            ? backendPartitionTable->getExtendedPartition()
            : backendPartitionTable->getPartitionBySector( partition()->firstSector() )
    );
    if ( !backendPartition.data() ) {
        return Calamares::JobResult::error(
                   errorMessage,
                   tr( "Could not find partition '%1'." ).arg( partition()->partitionPath() )
               );
    }

    quint32 count = 0;

    foreach( const PartitionTable::Flag& f, PartitionTable::flagList() )
    {
        emit progress(++count);

        const bool state = ( m_flags & f ) ? true : false;

        Report report( nullptr );
        if ( !backendPartition->setFlag( report, f, state ) )
        {
            cDebug() << QStringLiteral( "WARNING: Could not set flag %2 on "
                                        "partition '%1'." )
                           .arg( partition()->partitionPath() )
                           .arg( PartitionTable::flagName( f ) );
        }
    }

    // HACK: Partition (in KPMcore) declares SetPartFlagsJob as friend, but this actually
    //       refers to an unrelated class SetPartFlagsJob which is in KPMcore but is not
    //       exported.
    //       Obviously here we are relying on having a class in Calamares with the same
    //       name as a private one in KPMcore, which is awful, but it's the least evil
    //       way to call Partition::setFlags (KPMcore's SetPartFlagsJob needs its friend
    //       status for the very same reason).
    m_partition->setFlags( m_flags );

    backendPartitionTable->commit();

    return Calamares::JobResult::ok();
}


#include "SetPartitionFlagsJob.moc"
