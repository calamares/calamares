/* === This file is part of Calamares - <https://github.com/calamares> ===
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
#include "utils/Units.h"

// KPMcore
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <ops/setpartflagsoperation.h>
#include <util/report.h>

using CalamaresUtils::BytesToMiB;

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
               .arg( BytesToMiB( partition()->capacity() ) )
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
                   .arg( BytesToMiB( partition()->capacity() ) )
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
               .arg( BytesToMiB( partition()->capacity() ) )
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
                   .arg( BytesToMiB( partition()->capacity() ) )
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
               .arg( BytesToMiB( partition()->capacity() ) )
               .arg( partition()->fileSystem().name() )
               .arg( flagsList.join( ", " ) );

    return tr( "Setting flags <strong>%1</strong> on new partition." )
           .arg( flagsList.join( ", " ) );
}


Calamares::JobResult
SetPartFlagsJob::exec()
{
    Report report ( nullptr );
    SetPartFlagsOperation op( *m_device, *partition(), m_flags );
    op.setStatus( Operation::StatusRunning );
    connect( &op, &Operation::progress, this, &SetPartFlagsJob::iprogress );

    QString errorMessage = tr( "The installer failed to set flags on partition %1." )
                           .arg( m_partition->partitionPath() );
    if ( op.execute( report ) )
        return Calamares::JobResult::ok();

    return Calamares::JobResult::error( errorMessage, report.toText() );
}
